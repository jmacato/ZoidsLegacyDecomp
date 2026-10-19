/* Text background addressing: https://github.com/mgba-emu/mgba/blob/0.10.5/src/gba/renderers/software-mode0.c */
(function (scope) {
  "use strict";
  const WIDTH = 240, HEIGHT = 160, EMPTY = 0x8000;
  const shapes = [
    [[8,8],[16,16],[32,32],[64,64]],
    [[16,8],[32,8],[32,16],[64,32]],
    [[8,16],[8,32],[16,32],[32,64]],
  ];
  const view = bytes => new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  function memory(bytes, size, name) {
    if (!(bytes instanceof Uint8Array) || bytes.length !== size) throw Error(`Invalid ${name} display memory.`);
    return view(bytes);
  }
  function interval(position, bounds) {
    const start = bounds >>> 8, end = bounds & 255;
    return start <= end ? position >= start && position < end : position >= start || position < end;
  }
  function channels(first, second, operation, a, b) {
    let result = 0;
    for (let shift = 0; shift < 15; shift += 5) {
      const x = (first >>> shift) & 31, y = (second >>> shift) & 31;
      const value = operation === 1 ? Math.min(31, (x*a + y*b) >>> 4) :
        operation === 2 ? x + (((31-x)*a) >>> 4) : x - ((x*a) >>> 4);
      result |= value << shift;
    }
    return result;
  }
  function render(state, {firstLine=0, lastLine=HEIGHT}={}) {
    if (!Number.isInteger(firstLine) || !Number.isInteger(lastLine) || firstLine<0 || lastLine>HEIGHT || firstLine>=lastLine) {
      throw Error("Invalid display scanline range.");
    }
    const {vram, palette, oam, registers} = state;
    const tiles = memory(vram, 0x18000, "VRAM"), colors = memory(palette, 1024, "palette");
    const objects = memory(oam, 1024, "OAM"), io = memory(registers, 0x60, "register");
    const reg = at => io.getUint16(at, true), control = reg(0), result = new Uint16Array(WIDTH*HEIGHT);
    if (control & 0x80) { result.fill(0x7fff,firstLine*WIDTH,lastLine*WIDTH); return result; }
    if (control & 7) throw Error("The CAS display renderer requires mode 0.");
    if (control & 0x8000) throw Error("Object windows require a separate display implementation.");
    const backgrounds = [], mosaic = reg(0x4c), mosaicX = (mosaic & 15)+1, mosaicY = ((mosaic >>> 4)&15)+1;
    for (let layer = 0; layer < 4; layer++) {
      if (!(control & (0x100 << layer))) continue;
      const config = reg(8+layer*2), size = config >>> 14, width = size&1 ? 512 : 256, height = size&2 ? 512 : 256;
      const tileBase = ((config >>> 2)&3)*0x4000, mapBase = ((config >>> 8)&31)*0x800;
      const depth8 = !!(config & 0x80), horizontal = reg(0x10+layer*4)&511, vertical = reg(0x12+layer*4)&511;
      const pixels = new Uint16Array(WIDTH*HEIGHT); pixels.fill(EMPTY);
      for (let y = firstLine; y < lastLine; y++) {
        const sy = ((config&0x40 ? y-y%mosaicY : y)+vertical)&(height-1), cellY = sy >>> 3;
        for (let x = 0; x < WIDTH; x++) {
          const sx = ((config&0x40 ? x-x%mosaicX : x)+horizontal)&(width-1), cellX = sx >>> 3;
          const block = (cellX >>> 5)+(cellY >>> 5)*(width >>> 8);
          const entry = tiles.getUint16((mapBase+block*0x800+((cellY&31)*32+(cellX&31))*2)&0xffff, true);
          const px = entry&0x400 ? 7-(sx&7) : sx&7, py = entry&0x800 ? 7-(sy&7) : sy&7;
          const address = tileBase+(entry&1023)*(depth8?64:32)+py*(depth8?8:4)+(depth8?px:px>>>1);
          if (address >= 0x10000) continue;
          const index = depth8 ? vram[address] : (vram[address] >>> ((px&1)*4))&15;
          if (index) pixels[y*WIDTH+x] = colors.getUint16((depth8 ? index : (entry>>>12)*16+index)*2, true)&0x7fff;
        }
      }
      backgrounds.push({layer, priority:config&3, pixels});
    }
    backgrounds.sort((a,b)=>a.priority-b.priority || a.layer-b.layer);
    const objectPixels = new Uint16Array(WIDTH*HEIGHT); objectPixels.fill(EMPTY);
    const objectPriority = new Uint8Array(WIDTH*HEIGHT); objectPriority.fill(4);
    const translucent = new Uint8Array(WIDTH*HEIGHT);
    const scanlineCost = new Uint16Array(HEIGHT); scanlineCost.fill(256);
    if (control & 0x1000) for (let index = 0; index < 128; index++) {
      const a0 = objects.getUint16(index*8,true), a1 = objects.getUint16(index*8+2,true), a2 = objects.getUint16(index*8+4,true);
      const affine = !!(a0&0x100), mode = (a0>>>10)&3;
      if ((!affine && (a0&0x200)) || (a0>>>14) === 3) continue;
      if (mode >= 2) throw Error("The CAS display renderer cannot draw this object mode.");
      if ((a0&0x1000) && (mosaic&0xff00)) throw Error("Object mosaic requires a separate display implementation.");
      const [width,height] = shapes[a0>>>14][a1>>>14], double = affine && !!(a0&0x200);
      const fieldWidth = width*(double?2:1), fieldHeight = height*(double?2:1);
      let left = a1&511, top = a0&255;
      if (left >= 256) left -= 512;
      // Affine double-size fields wrap as a whole: https://github.com/mgba-emu/mgba/issues/2824
      if (top+fieldHeight >= 256) top -= 256;
      // A conservative bound avoids relying on mGBA 0.10.5's inaccurate OBJ cycle accounting.
      for (let y=Math.max(firstLine,top); y<Math.min(lastLine,top+fieldHeight); y++) {
        scanlineCost[y] += affine ? 10+2*fieldWidth : width;
        if (scanlineCost[y]>(control&0x20?954:1210)) throw Error("This scanline requires a native OBJ cycle-budget check.");
      }
      const matrix = ((a1>>>9)&31)*32, depth8 = !!(a0&0x2000), priority = (a2>>>10)&3;
      const oneDimensional = !!(control&0x40), first = (a2&1023)&(depth8&&!oneDimensional?~1:~0);
      const stride = oneDimensional ? (width>>>3)*(depth8?2:1) : 32;
      const pa = objects.getInt16(matrix+6,true), pb = objects.getInt16(matrix+14,true);
      const pc = objects.getInt16(matrix+22,true), pd = objects.getInt16(matrix+30,true);
      for (let y = Math.max(firstLine,top); y < Math.min(lastLine,top+fieldHeight); y++) {
        for (let x = Math.max(0,left); x < Math.min(WIDTH,left+fieldWidth); x++) {
          const at = y*WIDTH+x;
          if (priority >= objectPriority[at]) continue;
          let dx = x-left, dy = y-top;
          if (affine) {
            const cx = dx-fieldWidth/2, cy = dy-fieldHeight/2;
            dx = ((pa*cx+pb*cy)>>8)+width/2; dy = ((pc*cx+pd*cy)>>8)+height/2;
            if (dx<0 || dy<0 || dx>=width || dy>=height) continue;
          } else {
            if (a1&0x1000) dx = width-1-dx;
            if (a1&0x2000) dy = height-1-dy;
          }
          const column = (dx>>>3)*(depth8?2:1), row = (dy>>>3)*stride;
          const tile = oneDimensional ? first+row+column : ((first+row)&~31)|((first+column)&31);
          const address = 0x10000+((tile*32+(dy&7)*(depth8?8:4)+(depth8?dx&7:(dx&7)>>>1))&0x7fff);
          const pixel = depth8 ? vram[address] : (vram[address]>>>((dx&1)*4))&15;
          if (!pixel) {
            // Hardware promotes an earlier opaque pixel's priority without replacing its color or alpha flag.
            if (objectPixels[at]!==EMPTY) objectPriority[at]=priority;
            continue;
          }
          objectPixels[at] = colors.getUint16(512+(depth8?pixel:(a2>>>12)*16+pixel)*2,true)&0x7fff;
          objectPriority[at] = priority; translucent[at] = mode===1;
        }
      }
    }
    const backdrop = colors.getUint16(0,true)&0x7fff, blend = reg(0x50), operation = (blend>>>6)&3;
    const firstTargets = blend&63, secondTargets = (blend>>>8)&63;
    const alphaA = Math.min(16,reg(0x52)&31), alphaB = Math.min(16,(reg(0x52)>>>8)&31), brightness = Math.min(16,reg(0x54)&31);
    const windows = !!(control&0x6000), win0H = reg(0x40), win1H = reg(0x42), win0V = reg(0x44), win1V = reg(0x46);
    for (let y = firstLine; y < lastLine; y++) for (let x = 0; x < WIDTH; x++) {
      const at = y*WIDTH+x;
      let mask = 63;
      if (windows) {
        mask = reg(0x4a)&63;
        if ((control&0x4000) && interval(y,win1V) && interval(x,win1H)) mask = (reg(0x48)>>>8)&63;
        if ((control&0x2000) && interval(y,win0V) && interval(x,win0H)) mask = reg(0x48)&63;
      }
      let first = backdrop, firstLayer = 5, second = backdrop, secondLayer = 5, priority = 4;
      for (const background of backgrounds) {
        if (!(mask&(1<<background.layer)) || background.pixels[at]===EMPTY) continue;
        if (firstLayer===5) {first=background.pixels[at]; firstLayer=background.layer; priority=background.priority;}
        else {second=background.pixels[at]; secondLayer=background.layer; break;}
      }
      if ((mask&16) && objectPixels[at]!==EMPTY) {
        if (objectPriority[at]<=priority) {
          second=first; secondLayer=firstLayer; first=objectPixels[at]; firstLayer=4;
        } else {
          const behind = backgrounds.find(background=>background.layer===secondLayer);
          if (!behind || objectPriority[at]<=behind.priority) {second=objectPixels[at]; secondLayer=4;}
        }
      }
      if (firstLayer!==5 && (secondTargets&(1<<secondLayer)) &&
          ((firstLayer===4 && translucent[at]) || ((mask&32) && operation===1 && (firstTargets&(1<<firstLayer))))) {
        result[at] = channels(first,second,1,alphaA,alphaB);
      } else if ((mask&32) && (firstTargets&(1<<firstLayer)) && operation>=2) {
        result[at] = channels(first,0,operation,brightness,0);
      } else result[at] = first;
    }
    if (reg(2)&1) for (let at=firstLine*WIDTH; at<lastLine*WIDTH; at+=2) {
      const green = result[at]&0x3e0;
      result[at] = (result[at]&~0x3e0)|(result[at+1]&0x3e0);
      result[at+1] = (result[at+1]&~0x3e0)|green;
    }
    return result;
  }
  const api = {render};
  scope.ZoidsDisplay = api;
  if (typeof module === "object" && module.exports) module.exports = api;
})(globalThis);
