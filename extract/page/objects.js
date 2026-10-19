// The ROM interface the Zoid and CAS engines (zoid-animation.js, cas.js) read through. Offsets are ROM offsets
// (address - 0x08000000), as the engines use them. Every LZ77 resource and code routine an engine loads must be an item
// or a matched region of the extraction plan; the engines record each one as a source range.
(function (scope) {
  "use strict";
  const BASE = 0x08000000;
  const SHAPES = new Set(["8,8", "16,16", "32,32", "64,64", "16,8", "32,8", "32,16", "64,32", "8,16", "8,32", "16,32", "32,64"]);
  const signed = (value, bits = 16) => (value << (32 - bits)) >> (32 - bits);
  const quotient = (a, b) => { if (!b) throw Error("A sprite matrix divides by zero."); return Math.trunc(a / b); };
  const EQUIPMENT_NAMES = 0x7ee170, ZOID_NAMES = 0x7edd54;

  // Frame dedupe key for timelines (FNV-1a over the bytes, two lanes).
  function key(bytes) {
    let a = 0x811c9dc5, b = 0x01000193 ^ bytes.length;
    for (let i = 0; i < bytes.length; i++) { a = Math.imul(a ^ bytes[i], 0x01000193); b = Math.imul(b ^ bytes[i] ^ (i & 255), 0x01000193); }
    return (a >>> 0).toString(16) + ":" + (b >>> 0).toString(16) + ":" + bytes.length;
  }

  // UpdateZoidEquipmentAnimation's tilemap script player (port of the old extractor's ZoidTilemapPlayer).
  class ZoidTilemapPlayer {
    constructor(script, tilemap, side = 0) {
      this.script = script; this.side = side; this.tilemap = tilemap.slice();
      this.frames = new Map(script.frames.map(frame => [frame.offset, frame]));
      this.index = 0; this.elapsed = 0; this.state = 1; this.ready = 0; this.updates = 0;
    }
    update() {
      const songs = []; let patch = null;
      this.updates++;
      if (this.state !== 1) return { patch, songs };
      const commands = this.script.commands;
      if (this.elapsed === commands[this.index].duration_or_song) {
        for (let visited = 0; visited <= commands.length; visited++) {
          const command = commands[++this.index];
          if (!command) throw Error("A Zoid animation leaves its command stream.");
          const value = command.frame_offset_or_command;
          if (value === -3) { songs.push(command.duration_or_song & 65535); continue; }
          if (value === -1) { this.state = 0; this.ready = 1; return { patch, songs }; }
          if (value < 0) throw Error("A Zoid animation reached an invalid command.");
          const complete = commands[this.index + 1]?.frame_offset_or_command === -2;
          if (complete) this.ready = 1;
          if (complete || command.duration_or_song !== 0) {
            if (value) {
              patch = this.frames.get(value);
              if (!patch) throw Error("A Zoid animation frame has no tilemap patch.");
              const { x_tiles: x, y_tiles: y, width_tiles: w, height_tiles: h } = patch;
              const view = new DataView(this.tilemap.buffer, this.tilemap.byteOffset, this.tilemap.byteLength);
              for (let row = 0; row < h; row++) for (let column = 0; column < w; column++) {
                const source = row * w + (this.side ? w - 1 - column : column), destination = (y + row) * 32 + (this.side ? 32 - x - w : x) + column;
                view.setUint16(destination * 2, patch.tilemap[source] ^ (this.side ? 0x400 : 0), true);
              }
              if (complete) this.index = 0;
            }
            this.elapsed = 0;
            break;
          }
        }
      }
      this.elapsed = (this.elapsed + 1) & 65535;
      return { patch, songs };
    }
  }

  class Archive {
    constructor(rom, plan, lz77, text) {
      this.rom = rom; this.view = new DataView(rom.buffer, rom.byteOffset, rom.byteLength); this.verified = true;
      this.decodeLz77 = lz77; this.decodeText = text; this.decoded = new Map(); this.byID = new Map();
      const lzKind = plan.kinds.indexOf("lz77");
      this.assets = plan.regions.map(([start, end, name]) => ({ kind: "code", start: start - BASE, end: end - BASE, name, details: {} }));
      for (const [kind, address, , , , spans] of plan.items) {
        if (kind !== lzKind || !spans.length) continue;
        this.assets.push({ kind: "lz77", start: address - BASE, end: Math.max(...spans.map(span => span[1])) - BASE, details: { encoding: "gba-lz77" } });
      }
    }
    check(at, size = 1) { if (!Number.isSafeInteger(at) || at < 0 || at + size > this.rom.length) throw Error(`ROM read outside its bounds at 0x${at.toString(16)}.`); }
    u8(at) { this.check(at); return this.rom[at]; }
    u16(at) { this.check(at, 2); return this.view.getUint16(at, true); }
    i16(at) { return signed(this.u16(at)); }
    u32(at) { this.check(at, 4); return this.view.getUint32(at, true); }
    i32(at) { return this.u32(at) | 0; }
    pointer(at) { const value = this.u32(at) - BASE; this.check(value); return value; }
    lz(at) { if (!this.decoded.has(at)) this.decoded.set(at, this.decodeLz77(this.rom, at + BASE)); return this.decoded.get(at); }
    sourceSpan(start, end, role = "data", transform = "identity") { this.check(start, end - start); return { start, end, role, transform }; }

    name(table, index) {
      const text = this.decodeText(this.rom, this.pointer(table + index * 4) + BASE, "item").text;
      return text.replace(/[\uFF01-\uFF5E]/g, char => String.fromCharCode(char.charCodeAt(0) - 0xfee0)).replace(/\u3000/g, " ").trim();
    }

    pointers(at) {
      const values = [];
      for (let pos = at; pos < Math.min(at + 0x4000, this.rom.length - 3); pos += 4) { const value = this.u32(pos) - BASE; if (value < 0 || value >= this.rom.length) break; values.push(value); }
      if (!values.length) throw Error("Empty sprite pointer table.");
      return values;
    }

    assetID(kind, start, end) { const id = `${kind}/${start}-${end}`; if (!this.byID.has(id)) this.byID.set(id, { id, kind, start, end }); return id; }

    sprite(root) {
      const frameTable = root.record == null ? root.frame_table : this.pointer(root.record), animationTable = root.record == null ? root.animation_table : this.pointer(root.record + 4);
      const record = { ...root, frame_table: frameTable, animation_table: animationTable, frames: [], animations: [] };
      for (const start of this.pointers(frameTable)) {
        let pos = start; const pieces = [];
        while (this.i16(pos) !== -1) {
          if (pieces.length >= 128) throw Error("Missing sprite frame terminator.");
          const width = this.i16(pos + 8), height = this.i16(pos + 10);
          if (!SHAPES.has(`${width},${height}`)) break;
          pieces.push({ tile: this.u16(pos), flags: this.u16(pos + 2), x: this.i16(pos + 4), y: this.i16(pos + 6), width, height, scale_x_fixed8: this.i16(pos + 12), scale_y_fixed8: this.i16(pos + 14), tail: this.u32(pos + 16) });
          pos += 20;
        }
        if (this.i16(pos) !== -1) break;
        pos += 4;
        record.frames.push({ asset: this.assetID("sprites.frame", start, pos), pieces });
      }
      for (const start of this.pointers(animationTable)) {
        let pos = start; const steps = []; let valid = true;
        while (this.i16(pos) !== -1) {
          const frame = this.i16(pos), duration = this.i16(pos + 2);
          if (steps.length >= 4096 || frame < 0 || frame >= record.frames.length || duration < 0) { valid = false; break; }
          steps.push({ frame, duration_updates: duration });
          pos += 4;
        }
        if (!valid) break;
        pos += 4;
        record.animations.push({ asset: this.assetID("sprites.animation", start, pos), steps });
      }
      return record;
    }

    objects(pieces, { x, y, flags = 8, tile_offset = 0, palette_bank = 0 } = {}) {
      const objects = [];
      for (const piece of pieces) {
        const width = piece.width, height = piece.height, nativeDouble = Boolean(piece.tail & 0x200), canvasWidth = width * (nativeDouble ? 2 : 1), canvasHeight = height * (nativeDouble ? 2 : 1);
        let left = piece.x, top = piece.y;
        if (flags & 0x8000) left = -left - width * (nativeDouble ? 2 : 1);
        if (flags & 0x10000) top = -top - height * (nativeDouble ? 2 : 1);
        left = signed(left + x); top = signed(top + y);
        const sx = piece.scale_x_fixed8, sy = piece.scale_y_fixed8, angle = (piece.flags >>> 8) & 255, affine = angle !== 0 || sx !== 256 || sy !== 256;
        const clipWidth = Math.min(canvasWidth, quotient(sx * width, 256)), clipHeight = Math.min(canvasHeight, quotient(sy * height, 256));
        if (!(left > -clipWidth && top > -clipHeight && left < 240 - quotient(canvasWidth - clipWidth, 2) && top < 160 - quotient(canvasHeight - clipHeight, 2))) continue;
        const flips = (piece.flags & 3) ^ ((flags >>> 15) & 3);
        let matrix = null;
        const sine = angle => { angle &= 255; const index = (angle & 127) < 64 ? angle & 63 : 64 - (angle & 63); return this.u16(0xed184 + index * 2) * (angle >= 128 ? -1 : 1); };
        if (affine) { const sn = sine(angle), cs = sine(angle + 64); matrix = [quotient(cs * 256, sx) * (flips & 1 ? -1 : 1), quotient(sn * 256, sx) * (flips & 2 ? -1 : 1), -quotient(sn * 256, sy) * (flips & 1 ? -1 : 1), quotient(cs * 256, sy) * (flips & 2 ? -1 : 1)]; }
        const attr0 = (top & 255) | (flags & 0xc00) | (piece.tail & 0xff00) | (affine ? 0x100 : 0);
        if (matrix === null && (attr0 & 0x100)) matrix = [0, 0, 0, 0];
        objects.push({ x: left, y: top, width, height, field_width: width * ((attr0 & 0x300) === 0x300 ? 2 : 1), field_height: height * ((attr0 & 0x300) === 0x300 ? 2 : 1), flips, matrix, tile: tile_offset + piece.tile, color256: Boolean(attr0 & 0x2000), palette_bank, priority: (flags >>> 6) & 3, piece });
      }
      return objects;
    }

    // UpdateZoidEquipmentAnimation's LZ77 script: {s32 frame offset or command, s32 duration or song} pairs and the
    // {x, y, width, height, entries} tilemap patches they point at.
    equipmentScript(start) {
      const data = this.lz(start), view = new DataView(data.buffer, data.byteOffset, data.byteLength), commands = [], frames = [], seen = new Set();
      for (let at = 0; at < data.length; at += 8) {
        const frame = view.getInt32(at, true);
        if (frame === -1 || frame === -2) { commands.push({ offset: at, frame_offset_or_command: frame }); break; }
        commands.push({ offset: at, frame_offset_or_command: frame, duration_or_song: view.getInt32(at + 4, true) });
        if (frame === -3 || frame === 0 || seen.has(frame)) continue;
        if (frame < 0 || frame + 8 > data.length) throw Error("Invalid equipment frame offset.");
        seen.add(frame);
        const x = view.getUint16(frame, true), y = view.getUint16(frame + 2, true), width = view.getUint16(frame + 4, true), height = view.getUint16(frame + 6, true);
        frames.push({ offset: frame, x_tiles: x, y_tiles: y, width_tiles: width, height_tiles: height, tilemap: Array.from({ length: width * height }, (_, i) => view.getUint16(frame + 8 + i * 2, true)) });
      }
      return { commands, frames };
    }

    equipmentAsset(start) {
      const asset = this.assets.find(item => item.start === start && item.details.encoding === "gba-lz77");
      if (!asset) throw Error("A built-in animation has no source item.");
      return asset;
    }

    equipmentBindings(model) {
      const entries = [];
      for (let slot = 4; slot <= 13; slot++) {
        const selector = 0x7a773c + model * 40 + (slot - 4) * 4;
        if (!this.u32(selector)) continue;
        const asset = this.equipmentAsset(this.pointer(selector));
        const equipmentSlot = slot >= 9 ? slot - 5 : slot, item = equipmentSlot < 8 ? this.u16(0x7afcc4 + model * 56 + 24 + equipmentSlot * 4 + 2) : null;
        entries.push({ model, slot, selector, asset, item, label: item ? `${this.name(EQUIPMENT_NAMES, item)} · slot ${slot}` : `Slot ${slot}` });
      }
      return entries;
    }

    equipmentPlayback(model, slot, { side = 0 } = {}) {
      const selector = 0x7a773c + model * 40 + (slot - 4) * 4;
      if (!this.u32(selector)) return null;
      const asset = this.equipmentAsset(this.pointer(selector));
      const body = this.lz(this.pointer(0x7a5cf0 + model * 12 + 4)), tilemap = new Uint8Array(2048);
      tilemap.set(body.subarray(0, 2048));
      if (side) {
        const view = new DataView(tilemap.buffer), original = tilemap.slice(), source = new DataView(original.buffer);
        for (let row = 0; row < 16; row++) for (let x = 0; x < 32; x++) view.setUint16((row * 32 + x) * 2, source.getUint16((row * 32 + 31 - x) * 2, true) ^ 0x400, true);
      }
      tilemap.fill(0, 0x400);
      const player = new ZoidTilemapPlayer(this.equipmentScript(asset.start), tilemap, side);
      player.model = model; player.slot = slot; player.asset = asset; player.selector = selector;
      return player;
    }

    zoidName(model) { return this.name(ZOID_NAMES, model); }
    equipmentName(item) { return this.name(EQUIPMENT_NAMES, item); }
  }

  scope.ZoidsObjects = { Archive, key, BASE };
  if (typeof module !== "undefined" && module.exports) module.exports = scope.ZoidsObjects;
})(typeof globalThis !== "undefined" ? globalThis : this);
