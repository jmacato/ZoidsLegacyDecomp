// Test reference only (never shipped): the battle field screen of InitializeBattleFieldDisplay (src/battle/initialize_battle_field_display.c), ported without
// emulation: the camera (start_battle_camera_transition.c, update_battle_camera_transition.c, update_camera_rotation_matrix.c,
// project_camera_point.c), the ground's per-scanline BG2 records (update_perspective_scanline_buffers.c, copied each HBlank by
// the IWRAM routine at 0x08000638), terrain and sky (load_battle_terrain_and_sky_graphics.c), the units and their gauges
// (create_battle_unit_sprites.c, configure_battle_unit_sprites.c, update_projected_sprite.c, update_*_battle_gauge_sprite.c,
// update_battle_unit_gauge_graphics.c) and the per-piece OAM packing of UpdateSpritesAndBuildOam.
(function (scope) {
  "use strict";
  const TERRAIN = 0x7af614, ICON_TILES = 0x7aa70c, ICON_PALETTES = 0x7aa96c, POSITIONS = 0x7a2790, SINE = 0xed184, ZOID_RECORDS = 0x7afcc4;
  const ICON_FRAMES = 0x21024c, ICON_ANIMATIONS = 0x210258, GAUGE_FRAMES = 0x106f50, GAUGE_ANIMATIONS = 0x106f5c;
  const GAUGE_TEMPLATE = 0x277be4, GAUGE_PALETTE = 0x277ce4, ENCOUNTERS = 0x7b9454, WORLD_GRID = 0x478fa0, WORLD_THRESHOLDS = 0x7c3864, MAP_ENCOUNTERS = 0x7c3884;
  const DOUBLE_ICON = 4, HIDDEN = 0x20000;
  const SHAPES = new Map([["8,8",[0,0]],["16,16",[0,1]],["32,32",[0,2]],["64,64",[0,3]],["16,8",[1,0]],["32,8",[1,1]],["32,16",[1,2]],["64,32",[1,3]],
    ["8,16",[2,0]],["8,32",[2,1]],["16,32",[2,2]],["32,64",[2,3]]]);
  const s16 = value => (value << 16) >> 16, u16 = value => value & 0xffff;
  const shift8 = value => (value < 0 ? value + 0xff : value) >> 8;
  const half = value => (value + (value >>> 31)) >> 1;
  const div = (a, b) => { if (!b) throw Error("The battle field divides by zero."); return Math.trunc(a / b) | 0; };

  function sin256(archive, angle) {
    const wrapped = angle & 0xff, index = (wrapped & 0x7f) <= 0x3f ? wrapped & 0x3f : 0x40 - (wrapped & 0x3f), sample = archive.u16(SINE + index * 2);
    return wrapped <= 0x7f ? s16(sample) : s16(-sample);
  }
  const cos256 = (archive, angle) => sin256(archive, s16(angle + 0x40));

  // MultiplyMatrix3x3Fixed8: column-major s16 matrices, products rounded toward zero.
  function multiply(left, right) {
    const out = new Array(9);
    for (let column = 0; column < 3; column++) for (let row = 0; row < 3; row++) {
      let value = 0;
      for (let k = 0; k < 3; k++) value += left[k * 3 + row] * right[column * 3 + k];
      out[column * 3 + row] = s16(shift8(value));
    }
    return out;
  }
  function rotationXYZ(archive, [x, y, z]) {
    const sin = angle => sin256(archive, angle), cos = angle => cos256(archive, angle);
    const first = [0x100, 0, 0, 0, cos(x), sin(x), 0, s16(-sin(x)), cos(x)];
    const second = [cos(y), 0, s16(-sin(y)), 0, 0x100, 0, sin(y), 0, cos(y)];
    const third = [cos(z), sin(z), 0, s16(-sin(z)), cos(z), 0, 0, 0, 0x100];
    return multiply(multiply(first, second), third);
  }
  const transform = (m, [x, y, z]) => [0, 1, 2].map(i => shift8(m[i] * x + y * m[3 + i] + z * m[6 + i]));

  class Camera {
    constructor(archive) {
      this.archive = archive;
      this.pose = { x: 0, z: 0, depth: 0, pitch: 0, yaw: 0, roll: 0 };
      this.target = { ...this.pose };
      this.projection = { cx: 0x78, cy: 0x78, focal: 0x80 };
      this.far = 0x20000; this.mode = 0; this.done = 1; this.matrix = rotationXYZ(archive, [0, 0, 0]);
    }

    // StartBattleCameraTransition: each mode's target pose.
    start(mode, side = 0, unit = 0, immediate = 0) {
      const t = this.target, position = index => [this.archive.i32(POSITIONS + index * 12), this.archive.i32(POSITIONS + index * 12 + 8)];
      const set = (x, z, depth, pitch) => Object.assign(t, { x, z, depth, pitch, roll: 0, yaw: 0 });
      this.mode = mode;
      if (mode === 1) set(-0xd000, 0x20000, 0x8000, 4);
      else if (mode === 8) set(0, 0x20000, 0x8000, 4);
      else if (mode >= 2 && mode <= 4) set(side ? [-0xd000, -0xf000, -0x10000][mode - 2] : [0xd000, 0xb000, 0xc000][mode - 2], 0, 0x8000, 0x20);
      else if (mode === 5 || mode === 9) { const [x, z] = position(side * 6 + unit); set(x, z, mode === 5 ? 0x8000 : 0x4000, 0x20); }
      else if (mode === 0 || mode === 6) set(0, 0, 0x8000, 0x20);
      if (immediate === 1) Object.assign(this.pose, t);
      this.done = 0;
    }

    // UpdateBattleCameraTransition: the intro modes fly in on world z; the rest ease a quarter of the way per update.
    update() {
      if (this.done) return;
      const p = this.pose, t = this.target;
      if (this.mode === 1 || this.mode === 8) {
        if (p.z <= 0x7fff) { p.z -= (p.z < 0 ? p.z + 7 : p.z) >> 3; if (s16(p.pitch) <= 0x1f) p.pitch = u16(p.pitch + 1); }
        else p.z = (p.z - 0x1000) | 0;
        if (s16(p.pitch) !== 0x20 || p.z > 0x3f) return;
        p.z = 0; this.done = 1; return;
      }
      for (const key of ["x", "z", "depth"]) {
        const delta = t[key] - p[key], next = p[key] + ((delta < 0 ? delta + 3 : delta) >> 2);
        p[key] = (t[key] > next && t[key] - next <= 0x7f) || (t[key] < next && t[key] - next > -0x80) ? t[key] : next;
      }
      for (const key of ["pitch", "yaw", "roll"]) {
        const current = s16(p[key]), wanted = s16(t[key]);
        if (current === wanted) continue;
        const down = current < wanted ? wanted - current > 0x80 : current - wanted <= 0x80;
        p[key] = u16(p[key] + (down ? -1 : 1));
      }
      if (p.x !== t.x || p.z !== t.z || p.depth !== t.depth || p.pitch !== t.pitch || p.yaw !== t.yaw || s16(p.roll) !== s16(t.roll)) return;
      this.done = 1;
    }

    // UpdateCameraRotationMatrix builds the matrix from pitch and negated yaw with zero roll.
    rotate() { this.matrix = rotationXYZ(this.archive, [s16(this.pose.pitch), s16(-this.pose.yaw), 0]); }

    // UpdatePerspectiveScanlineBuffers: one BG2 {pa, pb, pc, pd, x, y} record per scanline and the horizon row (0xff for none).
    scanlines() {
      const a = this.archive, p = this.pose, { cx, cy, focal } = this.projection, records = [];
      const pitchCos = s16(cos256(a, -s16(p.pitch))), pitchSin = s16(sin256(a, -s16(p.pitch)));
      const yawCos = s16(cos256(a, -s16(p.yaw))), yawSin = s16(sin256(a, -s16(p.yaw)));
      const numerator = (div(p.depth, 0x100) * (focal * pitchSin)) | 0;
      for (let line = 0; line < 160; line++) {
        const denominator = div((cy - line) * pitchCos + focal * pitchSin, 0x100) * focal;
        if (!denominator) { records.push({ pa: 0, pb: 0, pc: 0, pd: 0, x: 0, y: 0 }); continue; }
        const perspective = div(numerator, denominator), pa = s16(div(yawCos * perspective, 0x100)), pb = s16(div(yawSin * perspective, 0x100)), pc = s16(-pb), pd = pa;
        if (!pitchSin) { records.push({ pa: 0, pb: 0, pc: 0, pd: 0, x: 0, y: 0 }); continue; }
        const step = div((line - cy) << 8, pitchSin);
        records.push({ pa, pb, pc, pd, x: (pa * -cx - pb * step + p.x) | 0, y: (pc * -cx - pd * step + p.z) | 0 });
      }
      let horizon = 0xff;
      if (pitchCos) {
        const row = (div(shift8Signed((this.far - p.depth) * pitchSin) * focal, div(pitchCos * this.far, 0x100)) + cy) >>> 0;
        if (row <= 159) horizon = row;
      }
      return { records, horizon };
    }

    // ProjectCameraPoint: screen position and the fixed-8 scale of a world point.
    project([x, y, z]) {
      const p = this.pose, t = transform(this.matrix, [x - p.x, y, p.z - z]), depth = t[2] + p.depth, { cx, cy, focal } = this.projection;
      if (depth < 0 || depth >= this.far || !focal) return { visible: 0, x: 0, y: 0, scale: 0 };
      return { visible: 1, x: cx + div(t[0] * focal, depth), y: cy + div(t[1] * focal, depth), scale: s16(div(focal << 16, depth)) };
    }
  }
  const shift8Signed = value => div(value, 0x100);

  // The battle field: terrain, sky, twelve unit and gauge sprite pairs, and the camera that frames them.
  class Field {
    constructor(archive, { terrain = 0, sides = [[], []] } = {}) {
      this.archive = archive; this.terrain = terrain; this.sides = sides; this.sources = [];
      this.vram = new Uint8Array(0x18000); this.palette = new Uint8Array(1024); this.registers = new Uint8Array(0x60); this.oam = new Uint8Array(1024);
      this.io = new DataView(this.registers.buffer); this.oamView = new DataView(this.oam.buffer);
      this.camera = new Camera(archive); this.sprites = [];
      this.io.setUint16(0, 0x1741 & ~0x200 | 0x2000, true);
      this.io.setUint16(8, 0x87, true); this.io.setUint16(0xc, 0x218b, true);
      this.io.setUint16(0x48, 0x3b, true); this.io.setUint16(0x4a, 0x3e, true); this.io.setUint16(0x40, 0xf0, true);
      this._loadTerrain(); this._createSprites();
      this.palette.set(this._bytes(GAUGE_PALETTE, 32, "gauge palette"), 0x3c0);
      for (let side = 0; side < 2; side++) for (let unit = 0; unit < 6; unit++) if (sides[side]?.[unit]) this._configure(side, unit, sides[side][unit]);
    }

    _source(start, end, role) { this.sources.push({ start, end, role }); }
    _bytes(at, length, role) { this._source(at, at + length, role); return this.archive.rom.subarray(at, at + length); }
    _lz(pointerAt, role) {
      const start = this.archive.pointer(pointerAt), data = this.archive.lz(start);
      this._source(pointerAt, pointerAt + 4, `${role} pointer`); this._source(start, start + 4, `${role} (LZ77)`);
      return data;
    }
    // LoadCompressedPalette: BIOS CpuFastSet copies the decoded size in 8-word blocks; BG palette 0 keeps the backdrop color.
    _palette(pointerAt, offset, role) {
      const data = this._lz(pointerAt, role), words = ((data.length << 9) >>> 11), bytes = Math.ceil(words / 8) * 32, keep = this.palette.slice(0, 2);
      this.palette.set(data.subarray(0, Math.min(bytes, 1024 - offset)), offset);
      if (offset === 0) this.palette.set(keep, 0);
    }

    // LoadBattleTerrainAndSkyGraphics(terrain, 2, 1, 1, 0): ground tiles at char block 2 with an 8x8-tile block repeated 2x2
    // over a 16x16 affine map at screen block 1; sky tiles at char block 1 with 16x16 tiles repeated across screen block 0.
    _loadTerrain() {
      const record = TERRAIN + this.terrain * 16;
      this.vram.set(this._lz(record, "terrain tiles"), 0x8000);
      this._palette(record + 4, 0, "terrain palette");
      const map = new DataView(this.vram.buffer, 0x800, 0x800);
      let entries = 0x100, at = 0;
      for (let row = 0; row < 8; row++) {
        for (let column = 0; column < 4; column++, at++, entries = u16(entries + 0x202)) for (const offset of [0, 4, 0x40, 0x44]) map.setUint16((at + offset) * 2, entries, true);
        at += 4;
      }
      this.vram.set(this._lz(record + 8, "sky tiles"), 0x4000);
      this._palette(record + 12, 0x80, "sky palette");
      const sky = new DataView(this.vram.buffer, 0, 0x800);
      entries = 0; at = 0;
      for (let row = 0; row < 16; row++) {
        for (let column = 0; column < 16; column++, at++, entries = u16(entries + 1)) { sky.setUint16(at * 2, entries, true); sky.setUint16((at + 0x10) * 2, entries, true); }
        at += 0x10;
      }
    }

    _sprite(frames, animations, tile, palette, flags) {
      const record = this.archive.sprite({ frame_table: frames, animation_table: animations });
      const sprite = { record, flags: flags | 1, x: 0, y: 0, offset_x: 0, offset_y: 0, rotation: 0, scale: 0x100, tile_offset: tile, palette_bank: palette, animation: 0, step: 0, age: 0, slot: 127 - this.sprites.length, world: null, update: null };
      this.sprites.push(sprite);
      return sprite;
    }

    // CreateBattleUnitSprites: per side and unit a gauge (tile 768 + index * 8, palette 14) then a unit icon (tile index * 64,
    // palette index), both hidden; side 1 is mirrored and the three rows take priorities 3, 2, 1 front to back.
    _createSprites() {
      this.gauges = [[], []]; this.units = [[], []];
      for (let side = 0; side < 2; side++) for (let unit = 0; unit < 6; unit++) {
        const index = side * 6 + unit;
        this.gauges[side][unit] = this._sprite(GAUGE_FRAMES, GAUGE_ANIMATIONS, index << 3, 14, 0x20048);
        this.units[side][unit] = this._sprite(ICON_FRAMES, ICON_ANIMATIONS, index << 6, index, side ? (((unit % 3) << 6) + 0x40) | 0x28308 : ((3 - unit % 3) << 6) | 0x20308);
      }
      this._source(ICON_FRAMES, ICON_FRAMES + 4, "unit icon frame table"); this._source(GAUGE_FRAMES, GAUGE_FRAMES + 4, "gauge frame table");
    }

    // ConfigureBattleUnitSprites with LoadZoidIconGraphics and full HP and EP gauges (UpdateBattleUnitGaugeGraphics: a full
    // DrawBattleGaugeFill leaves the gauge template unchanged).
    _configure(side, unit, { zoid, palette = 0 }) {
      const index = side * 6 + unit, sprite = this.units[side][unit], gauge = this.gauges[side][unit];
      this.vram.set(this._lz(ICON_TILES + zoid * 4, "unit icon tiles").subarray(0, 0x8000 - sprite.tile_offset * 32), 0x10000 + sprite.tile_offset * 32);
      this._palette(ICON_PALETTES + zoid * 32 + palette * 4, 0x200 + sprite.palette_bank * 32, "unit icon palette");
      const sizeClass = this.archive.u8(ZOID_RECORDS + zoid * 56 + 2);
      this._source(ZOID_RECORDS + zoid * 56 + 2, ZOID_RECORDS + zoid * 56 + 3, "size class");
      sprite.double = sizeClass === DOUBLE_ICON;
      if (sprite.double) sprite.flags |= 0x80000; else sprite.flags &= ~0x80000;
      sprite.flags &= ~HIDDEN; gauge.flags &= ~HIDDEN;
      gauge.update = side ? "left" : "right"; gauge.unit = sprite;
      sprite.world = [0, 4, 8].map(offset => this.archive.i32(POSITIONS + index * 12 + offset));
      this._source(POSITIONS + index * 12, POSITIONS + index * 12 + 12, "unit world position");
      this.vram.set(this._bytes(GAUGE_TEMPLATE, 256, "gauge template"), 0x16000 + gauge.tile_offset * 32);
    }

    // One update of RunBattleCameraTask and the sprite callbacks, then the OAM it produces.
    frame() {
      const camera = this.camera;
      camera.update();
      const { records, horizon } = camera.scanlines();
      camera.rotate();
      this.io.setUint16(0x10, u16(((camera.pose.x < 0 ? camera.pose.x + 3 : camera.pose.x) >> 2) >> 8), true);
      this.io.setUint16(0x12, u16(((0x80 - horizon) << 8) >> 8), true);
      this.io.setUint16(0x44, horizon === 0xff ? 0xff00 : horizon, true);
      for (const sprite of [...this.sprites].sort((a, b) => a.slot - b.slot)) {
        if (!(sprite.flags & 1)) continue;
        if (sprite.world) {
          const point = camera.project(sprite.world);
          if (point.visible) { sprite.x = u16(point.x); sprite.y = u16(point.y); }
          sprite.scale = sprite.double ? u16(point.scale << 1) : s16(point.scale);
          const limit = sprite.double ? (point.scale << 17) : (point.scale << 16);
          if (!point.visible || limit > 0x3000000) sprite.flags |= HIDDEN; else sprite.flags &= ~HIDDEN;
        } else if (sprite.update) {
          sprite.flags &= ~HIDDEN;
          if (sprite.unit.flags & HIDDEN) sprite.flags |= HIDDEN;
          else { sprite.x = u16(sprite.unit.x + (sprite.update === "right" ? 16 : -0x30)); sprite.y = sprite.unit.y; }
        }
      }
      this._buildOam();
      return { vram: this.vram, palette: this.palette, oam: this.oam, registers: this.registers, affine: records, horizon };
    }

    // SortActiveSprites then UpdateSpritesAndBuildOam's per-piece packing, including sprite scale, rotation and double size.
    _buildOam() {
      const active = [];
      for (const sprite of [...this.sprites].sort((a, b) => a.slot - b.slot)) {
        if (!(sprite.flags & 1)) continue;
        let position = active.length;
        while (position) {
          const previous = active[position - 1], a = sprite.flags, b = previous.flags;
          let shift;
          if ((a & 0xc0) < (b & 0xc0)) shift = true;
          else if ((a & 0xc0) !== (b & 0xc0)) shift = false;
          else if ((a & 0x300) < (b & 0x300)) shift = true;
          else if (!(a & 0x40000)) shift = false;
          else if (!(b & 0x40000)) shift = true;
          else shift = s16(sprite.y) > s16(previous.y);
          if (!shift) break;
          position--;
        }
        active.splice(position, 0, sprite);
      }
      let index = 0, matrix = 0;
      for (const sprite of active) {
        if (sprite.flags & 0x200000) throw Error("A blinking battle field sprite requires its blink state.");
        if (sprite.flags & HIDDEN || !s16(sprite.scale) || index >= 128) continue;
        const animation = sprite.record.animations[sprite.animation], step = animation.steps[sprite.step];
        for (const piece of sprite.record.frames[step.frame].pieces) {
          if (index >= 128) break;
          const entry = this._piece(sprite, piece, matrix);
          if (!entry) continue;
          if (entry.matrix) { entry.matrix.forEach((value, k) => this.oamView.setUint16((matrix * 4 + k) * 8 + 6, u16(value), true)); matrix++; }
          this.oamView.setUint16(index * 8, entry.attr0, true); this.oamView.setUint16(index * 8 + 2, entry.attr1, true); this.oamView.setUint16(index * 8 + 4, entry.attr2, true);
          index++;
        }
        if (!(sprite.flags & 8) && ++sprite.age === step.duration_updates) {
          sprite.age = 0;
          if (sprite.step + 1 < animation.steps.length) sprite.step++;
          else if ((sprite.flags & 0x30) === 0x20) sprite.step = 0;
        }
      }
      for (; index < 128; index++) this.oamView.setUint16(index * 8, 0x200, true);
    }

    _piece(sprite, piece, slot) {
      const a = this.archive, flags = sprite.flags, scale = s16(sprite.scale), rotation = sprite.rotation, w = piece.width, h = piece.height, tail = (piece.tail >>> 8) & 0xff;
      let x, y, fieldWidth, fieldHeight;
      if (rotation === 0 && scale === 0x100) { x = u16(piece.x); y = u16(piece.y); }
      else {
        let cx = u16(half(w) + piece.x), cy = u16(half(h) + piece.y);
        if (scale !== 0x100) { cx = u16(shift8(s16(cx) * scale)); cy = u16(shift8(s16(cy) * scale)); }
        if (rotation === 0) { x = u16(s16(cx) + half(-w)); y = u16(s16(cy) + half(-h)); }
        else {
          const sn = s16(sin256(a, rotation)), cs = s16(cos256(a, rotation));
          x = u16(shift8(s16(cx) * cs - s16(cy) * sn) + half(-w)); y = u16(half(-h) + shift8(s16(cx) * sn + s16(cy) * cs));
        }
      }
      if (!(tail & 2)) {
        if (flags & 0x8000) x = u16(-s16(x) - w);
        if (flags & 0x10000) y = u16(-s16(y) - h);
        if (!(flags & 0x80000)) { fieldWidth = w; fieldHeight = h; }
        else { x = u16(s16(x) - half(w)); y = u16(s16(y) - half(h)); fieldWidth = w * 2; fieldHeight = h * 2; }
      } else {
        fieldWidth = w * 2; fieldHeight = h * 2;
        if (flags & 0x8000) x = u16(-s16(x) - fieldWidth);
        if (flags & 0x10000) y = u16(-s16(y) - fieldHeight);
      }
      if (flags & 0x1000) throw Error("A camera-relative battle field sprite requires its scroll offsets.");
      const left = s16(s16(x) + u16(sprite.offset_x + sprite.x)), top = s16(s16(y) + u16(sprite.offset_y + sprite.y));
      let clipWidth = w, clipHeight = h;
      if (!(piece.scale_x_fixed8 === 0x100 && piece.scale_y_fixed8 === 0x100 && scale === 0x100)) {
        clipWidth = u16(shift8(piece.scale_x_fixed8 * shift8(w * scale))); clipHeight = u16(shift8(piece.scale_y_fixed8 * shift8(h * scale)));
        if (s16(clipWidth) > s16(fieldWidth)) clipWidth = fieldWidth;
        if (s16(clipHeight) > s16(fieldHeight)) clipHeight = fieldHeight;
      }
      clipWidth = s16(clipWidth); clipHeight = s16(clipHeight);
      if (left <= -clipWidth || top <= -clipHeight || left >= 0xf0 - half(s16(fieldWidth) - clipWidth) || top >= 0xa0 - half(s16(fieldHeight) - clipHeight)) return null;
      const shape = SHAPES.get(`${w},${h}`);
      if (!shape) throw Error("A battle field sprite piece has no OAM shape.");
      let attr0 = (top & 0xff) | (flags & 0xc00) | (tail << 8) | (shape[0] << 14), attr1 = (left & 0x1ff) | (shape[1] << 14);
      const flips = (piece.flags & 0xff) ^ ((flags & 0x18000) >>> 15);
      let matrix = null;
      if (!(tail & 1) && rotation === 0 && scale === 0x100 && !(flags & 0x80000)) attr1 |= (flips & 15) << 12;
      else {
        const sx = piece.scale_x_fixed8, sy = piece.scale_y_fixed8, angle = (piece.flags >>> 8) & 0xff;
        if (angle === 0 && rotation === 0) {
          const pa = div(0x1000000, scale * sx), pd = div(0x1000000, scale * sy);
          matrix = [flips & 1 ? -pa : pa, 0, 0, flips & 2 ? -pd : pd];
        } else {
          const sn = u16(sin256(a, angle + rotation)), cs = u16(cos256(a, angle + rotation));
          if (sx === 0x100 && sy === 0x100 && scale === 0x100) {
            matrix = [flips & 1 ? -s16(cs) : cs, flips & 2 ? -s16(sn) : sn, flips & 1 ? sn : -s16(sn), flips & 2 ? -s16(cs) : cs];
          } else {
            const cosine = s16(cs) * 0x10000, sine = s16(sn) * 0x10000;
            matrix = [flips & 1 ? -div(cosine, scale * sx) : div(cosine, scale * sx), flips & 2 ? -div(sine, sx * scale) : div(sine, sx * scale),
              flips & 1 ? div(sine, scale * sy) : -div(sine, scale * sy), flips & 2 ? -div(cosine, scale * sy) : div(cosine, scale * sy)];
          }
        }
        attr0 |= flags & 0x80000 ? 0x300 : 0x100;
        attr1 |= slot << 9;
      }
      const attr2 = ((sprite.tile_offset + piece.tile) | (sprite.palette_bank << 12) | ((flags & 0xc0) << 4)) & 0xffff;
      return { attr0: attr0 & 0xffff, attr1: attr1 & 0xffff, attr2, matrix };
    }
  }

  // Encounters: TrySelectFieldRandomEncounter and SelectFieldRandomEncounterTable read a world-map cell's group and threshold
  // index, or the current map's {map, threshold, group} record; a group holds 20 encounters of a song and six unit records.
  function worldEncounter(archive, cellX, cellY, widthTiles) {
    const at = WORLD_GRID + ((((cellY & 0xff) * widthTiles) >>> 1) + (cellX & 0xff)) * 2, tile = archive.u16(at);
    return { group: tile & 0xff, threshold: archive.u16(WORLD_THRESHOLDS + (tile >>> 8) * 2), tileAddress: at, thresholdAddress: WORLD_THRESHOLDS + (tile >>> 8) * 2 };
  }
  function mapEncounter(archive, map) {
    let index = 0;
    if (archive.u16(MAP_ENCOUNTERS)) while (archive.u16(MAP_ENCOUNTERS + index * 6) && archive.u16(MAP_ENCOUNTERS + index * 6) !== map) index++;
    const at = MAP_ENCOUNTERS + index * 6;
    return { group: archive.u16(at + 4), threshold: archive.u16(at + 2), recordAddress: at, matched: archive.u16(at) === map };
  }
  function encounterGroup(archive, group) {
    const encounters = [];
    for (let index = 0; index < 20; index++) {
      const at = ENCOUNTERS + group * 2000 + index * 100, units = [];
      for (let slot = 0; slot < 6; slot++) {
        const unit = at + 4 + slot * 16;
        units.push(archive.u8(unit) ? { zoid: archive.u8(unit), palette: archive.u8(unit + 1), pilot: archive.u8(unit + 2), equipment: [0, 1, 2, 3].map(k => archive.u8(unit + 4 + k)), experience: archive.u32(unit + 8), money: archive.u32(unit + 12) } : null);
      }
      encounters.push({ index, song: archive.u8(at), units, address: at, candidate: units.some(Boolean) });
    }
    return encounters;
  }

  const api = { Camera, Field, worldEncounter, mapEncounter, encounterGroup, sin256, cos256 };
  scope.ZoidsBattlefield = api;
  if (typeof module === "object" && module.exports) module.exports = api;
})(globalThis);
