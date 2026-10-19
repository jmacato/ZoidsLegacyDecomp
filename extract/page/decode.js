// Decoders for the plan's render recipes. They only draw what the Rust port already established; each recipe
// carries the SHA-1 or end address Rust computed, and verify() checks the JS result against it.
(function (scope) {
  "use strict";
  const BASE = 0x08000000;

  function romSlice(rom, start, end) {
    if (start < BASE || end > BASE + rom.length || end < start) throw new Error(`range 0x${start.toString(16)}..0x${end.toString(16)} is outside the ROM`);
    return rom.subarray(start - BASE, end - BASE);
  }

  // BIOS LZ77UnComp (type 0x10), as port/bios.rs decodes it.
  function lz77(rom, address) {
    let at = address - BASE;
    const header = rom[at] | (rom[at + 1] << 8) | (rom[at + 2] << 16) | (rom[at + 3] << 24);
    if ((header & 0xff) !== 0x10) throw new Error(`LZ77 at 0x${address.toString(16)}: header type is not 0x10`);
    const size = header >>> 8;
    const out = new Uint8Array(size);
    let written = 0;
    at += 4;
    while (written < size) {
      const flags = rom[at++];
      for (let bit = 7; bit >= 0 && written < size; bit--) {
        if (!(flags & (1 << bit))) { out[written++] = rom[at++]; continue; }
        const first = rom[at++], second = rom[at++];
        const length = (first >> 4) + 3, distance = (((first & 0xf) << 8) | second) + 1;
        if (distance > written || written + length > size) throw new Error(`LZ77 at 0x${address.toString(16)}: bad back-reference`);
        for (let i = 0; i < length; i++, written++) out[written] = out[written - distance];
      }
    }
    return out;
  }

  function u16s(bytes) {
    const out = new Uint16Array(bytes.length >> 1);
    for (let i = 0; i < out.length; i++) out[i] = bytes[i * 2] | (bytes[i * 2 + 1] << 8);
    return out;
  }

  function bytesOfU16(entries) {
    const out = new Uint8Array(entries.length * 2);
    entries.forEach((entry, i) => { out[i * 2] = entry & 0xff; out[i * 2 + 1] = entry >> 8; });
    return out;
  }

  // Source recipes: ["rom", start, end], ["lz77", address], ["screen", source], ["metatiles", map, defs, columns, rows, stride].
  function source(rom, recipe) {
    const [op, a, b, c, d, e] = recipe;
    if (op === "rom") return romSlice(rom, a, b);
    if (op === "lz77") return lz77(rom, a);
    if (op === "screen") return bytesOfU16(u16s(source(rom, a)).subarray(0, 0x400));
    if (op === "metatiles") {
      const map = u16s(source(rom, a)), defs = u16s(source(rom, b));
      const entries = new Uint16Array(c * d);
      for (let y = 0; y < d; y++) for (let x = 0; x < c; x++) {
        const metatile = map[e * (y >> 1) + (x >> 1)];
        entries[y * c + x] = defs[metatile * 4 + (y & 1) * 2 + (x & 1)];
      }
      return bytesOfU16(entries);
    }
    throw new Error(`unknown source op ${op}`);
  }

  function bgr555(value) {
    const expand = v => ((v & 0x1f) << 3) | ((v & 0x1f) >> 2);
    return [expand(value), expand(value >> 5), expand(value >> 10)];
  }

  function colors(bytes) {
    const out = [];
    for (let i = 0; i + 1 < bytes.length; i += 2) out.push(bgr555(bytes[i] | (bytes[i + 1] << 8)));
    return out;
  }

  function image(width, height) { return { width, height, rgba: new Uint8ClampedArray(width * height * 4) }; }
  function put(img, x, y, rgb) { const i = (y * img.width + x) * 4; img.rgba[i] = rgb[0]; img.rgba[i + 1] = rgb[1]; img.rgba[i + 2] = rgb[2]; img.rgba[i + 3] = 255; }

  function swatch(bytes) {
    const list = colors(bytes), rows = Math.max(1, Math.ceil(list.length / 16)), img = image(128, rows * 8);
    list.forEach((rgb, index) => { for (let y = 0; y < 8; y++) for (let x = 0; x < 8; x++) put(img, (index % 16) * 8 + x, Math.floor(index / 16) * 8 + y, rgb); });
    return img;
  }

  function tilePixels(data, bpp, tile) {
    const out = new Uint8Array(64), size = bpp * 8;
    const at = tile * size;
    for (let p = 0; p < 64; p++) {
      if (bpp === 8) out[p] = data[at + p];
      else if (bpp === 4) { const byte = data[at + (p >> 1)]; out[p] = p & 1 ? byte >> 4 : byte & 0xf; }
      else { const byte = data[at + (p >> 2)]; out[p] = (byte >> ((p & 3) * 2)) & 3; }
    }
    return out;
  }

  // A tile sheet, 16 tiles per row; with no palette, grey levels.
  function tiles(data, bpp, paletteBytes, perRow = 16) {
    const size = bpp * 8, count = Math.floor(data.length / size), columns = Math.max(1, Math.min(perRow, count)), rows = Math.max(1, Math.ceil(count / columns));
    const img = image(columns * 8, rows * 8), levels = (1 << bpp) - 1;
    const palette = paletteBytes ? colors(paletteBytes) : null;
    for (let tile = 0; tile < count; tile++) {
      const pixels = tilePixels(data, bpp, tile), x0 = (tile % columns) * 8, y0 = Math.floor(tile / columns) * 8;
      for (let p = 0; p < 64; p++) {
        const value = pixels[p];
        if (palette) { if (value) put(img, x0 + (p & 7), y0 + (p >> 3), palette[value] || [255, 0, 255]); }
        else { const g = Math.round((value / levels) * 255); put(img, x0 + (p & 7), y0 + (p >> 3), [g, g, g]); }
      }
    }
    return img;
  }

  // Font glyphs: 2bpp, Shift-JIS glyphs are a top and a bottom tile (size 32), single-byte glyphs one tile (size 16).
  function glyphs(data, size) {
    const count = Math.floor(data.length / size), perRow = 16, rows = Math.ceil(count / perRow), tall = size === 32;
    const img = image(perRow * 8, rows * (tall ? 16 : 8)), grey = [255, 170, 85, 0];
    for (let glyph = 0; glyph < count; glyph++) for (let half = 0; half < (tall ? 2 : 1); half++) {
      const pixels = tilePixels(data, 2, glyph * (tall ? 2 : 1) + half);
      const x0 = (glyph % perRow) * 8, y0 = Math.floor(glyph / perRow) * (tall ? 16 : 8) + half * 8;
      for (let p = 0; p < 64; p++) { const g = grey[pixels[p]]; put(img, x0 + (p & 7), y0 + (p >> 3), [g, g, g]); }
    }
    return img;
  }

  // BG text tilemap (u16: tile 0-9, h-flip 10, v-flip 11, bank 12-15).
  function tilemap(tileData, entries, paletteBytes, columns, eightBpp) {
    const rows = Math.max(1, Math.ceil(entries.length / columns)), img = image(columns * 8, rows * 8), palette = colors(paletteBytes);
    const bpp = eightBpp ? 8 : 4, size = bpp * 8;
    entries.forEach((entry, index) => {
      const tile = entry & 0x3ff;
      if ((tile + 1) * size > tileData.length) return;
      const pixels = tilePixels(tileData, bpp, tile), bank = eightBpp ? 0 : entry >> 12;
      const x0 = (index % columns) * 8, y0 = Math.floor(index / columns) * 8;
      for (let y = 0; y < 8; y++) for (let x = 0; x < 8; x++) {
        const sx = entry & 0x400 ? 7 - x : x, sy = entry & 0x800 ? 7 - y : y, value = pixels[sy * 8 + sx];
        if (value) put(img, x0 + x, y0 + y, palette[bank * 16 + value] || [255, 0, 255]);
      }
    });
    return img;
  }

  const sjisDecoder = (() => { try { return new TextDecoder("shift_jis"); } catch { return null; } })();
  function sjis(lead, trail) {
    if (sjisDecoder) { const text = sjisDecoder.decode(new Uint8Array([lead, trail])); if (text && !text.includes("�")) return text; }
    return `{sjis:${((lead << 8) | trail).toString(16).toUpperCase().padStart(4, "0")}}`;
  }
  function glyph(byte) { return byte >= 0x20 && byte < 0x7f && byte !== 0x7b && byte !== 0x7d ? String.fromCharCode(byte) : `{${byte.toString(16).toUpperCase().padStart(2, "0")}}`; }

  // Text grammars of port/text.rs, names.rs and credits.rs. Returns the display text and the end address (one past the terminator).
  function text(rom, address, grammar) {
    let at = address - BASE, out = "";
    const u8 = () => { if (at >= rom.length) throw new Error("text runs off the ROM"); return rom[at++]; };
    if (grammar === "credits") {
      for (;;) {
        const command = u8();
        if (command === 0) break;
        if (command === 0x0a) { out += "\n"; continue; }
        at--;
        for (;;) {
          if (u8() === 1) out += `{palette:${u8()}}`; else at--;
          const lead = u8(), trail = u8();
          out += sjis(lead, trail);
          const next = rom[at];
          if (next === 0) { at++; return { text: out, end: BASE + at }; }
          if (next === 0x0a) { at++; out += "\n"; break; }
        }
      }
      return { text: out, end: BASE + at };
    }
    for (;;) {
      const byte = u8();
      if (byte === 0) break;
      if (grammar === "plain") { if (byte >= 0x80 && byte <= 0x9f && rom[at] !== 0) out += sjis(byte, u8()); else out += byte === 0x0a ? "\n" : glyph(byte); continue; }
      if (grammar === "item") {
        if (byte === 1) { out += `{color:${u8()}}`; continue; }
        if (byte >= 0x80 && byte <= 0x9f && rom[at] !== 0 && rom[at] !== 1) { out += sjis(byte, u8()); continue; }
        out += byte === 0x0a ? "\n" : glyph(byte); continue;
      }
      if (grammar === "scrolling") {
        if (byte === 1) { at += 1; out += "{color}"; continue; }
        if (byte === 2) { at += 2; out += "{pos}"; continue; }
        if (byte === 3) { out += "{name}"; continue; }
        if (byte === 0x0a) { out += "\n"; continue; }
        if (byte < 0x20) throw new Error(`scrolling text: byte 0x${byte.toString(16)} never advances`);
        const second = u8();
        out += byte >= 0x80 && byte <= 0x9f ? sjis(byte, second) : glyph(byte) + glyph(second);
        continue;
      }
      // window (DrawWindowText)
      if (byte === 1) { out += `{color:${u8()}}`; continue; }
      if (byte === 2) { const column = u8(), row = u8(); out += `{pos:${column},${row}}`; continue; }
      if (byte === 3) { out += "{name}"; continue; }
      if (byte === 0x0a) { out += "\n"; continue; }
      if (byte < 0x20) throw new Error(`DrawWindowText: byte 0x${byte.toString(16)} never advances`);
      if (byte >= 0x80 && byte <= 0x9f) { out += sjis(byte, u8()); continue; }
      out += glyph(byte);
    }
    return { text: out, end: BASE + at };
  }

  // 8-bit signed PCM -> WAV (unsigned 8-bit), as music.rs writes it.
  function wav(samples, rate) {
    const out = new Uint8Array(44 + samples.length), view = new DataView(out.buffer);
    const ascii = (at, s) => { for (let i = 0; i < s.length; i++) out[at + i] = s.charCodeAt(i); };
    ascii(0, "RIFF"); view.setUint32(4, 36 + samples.length, true); ascii(8, "WAVE"); ascii(12, "fmt ");
    view.setUint32(16, 16, true); view.setUint16(20, 1, true); view.setUint16(22, 1, true); view.setUint32(24, rate, true);
    view.setUint32(28, rate, true); view.setUint16(32, 1, true); view.setUint16(34, 8, true); ascii(36, "data"); view.setUint32(40, samples.length, true);
    for (let i = 0; i < samples.length; i++) out[44 + i] = (samples[i] + 128) & 0xff;
    return out;
  }

  function word(rom, address) { const at = address - BASE; return (rom[at] | (rom[at + 1] << 8) | (rom[at + 2] << 16) | (rom[at + 3] << 24)) >>> 0; }
  function half(rom, address) { const at = address - BASE; return rom[at] | (rom[at + 1] << 8); }
  function signed16(value) { return value >= 0x8000 ? value - 0x10000 : value; }

  // Frame pieces as UpdateSpritesAndBuildOam reads them (port/sprite_bindings.rs Piece): 20 bytes until s16 -1.
  function pieces(rom, frame) {
    const out = [];
    for (let at = frame; ; at += 20) {
      if (half(rom, at) === 0xffff) return out;
      out.push({ tile: half(rom, at), x: signed16(half(rom, at + 4)), y: signed16(half(rom, at + 6)), width: half(rom, at + 8), height: half(rom, at + 10),
        flips: rom[at + 2 - BASE] & 3, color256: (rom[at + 0x11 - BASE] & 0x20) !== 0 });
    }
  }

  function spriteFrames(rom, view) {
    return Array.from({ length: view.count }, (_, index) => pieces(rom, word(rom, view.frames + index * 4)));
  }

  // Animation commands {s16 frame, s16 duration} until frame -1, for each entry of the animation table (null for empty slots).
  function spriteAnimations(rom, view) {
    return Array.from({ length: view.animation_count }, (_, index) => {
      const pointer = word(rom, view.animations + index * 4);
      if (!pointer) return null;
      const steps = [];
      for (let at = pointer; half(rom, at) !== 0xffff; at += 4) steps.push({ frame: half(rom, at), duration: half(rom, at + 2) });
      return steps;
    });
  }

  // OBJ VRAM (32 KiB) and OBJ palette RAM (512 bytes) from the binding's memory recipe, with family slots taken from `choice`.
  function spriteMemory(rom, view, choice) {
    if (view.streamed) {
      const pram = new Uint8Array(0x200);
      pram.set(romSlice(rom, view.streamed[2], view.streamed[2] + 32));
      return { vram: romSlice(rom, view.streamed[0], view.streamed[1]), pram };
    }
    const vram = new Uint8Array(0x8000), pram = new Uint8Array(0x200), decoded = new Map();
    for (const [start, end, src, offset] of view.memory) {
      const recipe = src.slot === undefined ? src : view.family.choices[choice][1][src.slot];
      const key = JSON.stringify(recipe);
      if (!decoded.has(key)) decoded.set(key, recipe[0] === "rom" ? romSlice(rom, recipe[1], recipe[2]) : source(rom, recipe));
      const bytes = decoded.get(key).subarray(offset, offset + end - start);
      if (bytes.length !== end - start) throw new Error(`sprite memory 0x${start.toString(16)}: source is shorter than its span`);
      if (start >= 0x06010000) vram.set(bytes, start - 0x06010000); else pram.set(bytes, start - 0x05000200);
    }
    return { vram, pram };
  }

  // Each frame as indexes into the 256-colour OBJ palette (0 = transparent), pieces at their x/y with flips, earlier pieces
  // in front; the same rules as render() in port/sprite_bindings.rs.
  function spritePixels(frames, tileOffset, paletteBank, vram) {
    return frames.map(list => {
      if (!list.length) return { left: 0, top: 0, width: 0, height: 0, pixels: new Uint8Array(0) };
      const left = Math.min(...list.map(p => p.x)), top = Math.min(...list.map(p => p.y));
      const width = Math.max(...list.map(p => p.x + p.width)) - left, height = Math.max(...list.map(p => p.y + p.height)) - top;
      const pixels = new Uint8Array(width * height), filled = new Uint8Array(width * height);
      for (const piece of list) {
        const base = (tileOffset + piece.tile) * 32;
        for (let row = 0; row < piece.height; row++) for (let column = 0; column < piece.width; column++) {
          const sx = piece.flips & 1 ? piece.width - 1 - column : column, sy = piece.flips & 2 ? piece.height - 1 - row : row;
          const tile = (sy >> 3) * (piece.width >> 3) + (sx >> 3);
          const wrap = at => vram.length === 0x8000 ? at & 0x7fff : at;
          let color;
          if (piece.color256) color = vram[wrap(base + tile * 64 + (sy & 7) * 8 + (sx & 7))];
          else {
            const nibble = (vram[wrap(base + tile * 32 + (sy & 7) * 4 + ((sx & 7) >> 1))] >> ((sx & 1) * 4)) & 15;
            color = nibble ? (paletteBank & 15) * 16 + nibble : 0;
          }
          if (!color) continue;
          const index = (piece.y - top + row) * width + piece.x - left + column;
          if (!filled[index]) { filled[index] = 1; pixels[index] = color; }
        }
      }
      return { left, top, width, height, pixels };
    });
  }

  function spriteImage(frame, pram) {
    const img = image(Math.max(frame.width, 1), Math.max(frame.height, 1)), palette = colors(pram);
    frame.pixels.forEach((index, i) => { if (index) put(img, i % frame.width, Math.floor(i / frame.width), palette[index]); });
    return img;
  }

  function spriteSheet(frames, pram) {
    const width = Math.max(frames.reduce((sum, f) => sum + f.width + 2, 0), 1), height = Math.max(...frames.map(f => f.height), 1);
    const img = image(width, height), palette = colors(pram);
    let left = 0;
    for (const f of frames) {
      f.pixels.forEach((index, i) => { if (index) put(img, left + i % f.width, Math.floor(i / f.width), palette[index]); });
      left += f.width + 2;
    }
    return img;
  }

  // IsFieldTerrainBlockedForActorModel (is_field_terrain_blocked_for_actor_model.c).
  function terrainBlocked(model, cell, conditional) {
    if (conditional && cell & 0x20) return true;
    switch (cell & 0x1f) {
      case 4: case 6: case 7: case 9: return ((model - 0x69) & 0xff) <= 2;
      case 8: case 10: return model === 0x69;
      case 11: return ((model - 0x69) & 0xff) <= 1;
      default: return false;
    }
  }

  // The cell byte GetPackedFieldMapCellCollision (map 0) or GetFieldMapCellCollisionMask (other maps) reads.
  function collisionCell(view, cells, x, y) {
    return view.packed ? cells[(x & 0xff) + (((y & 0xff) * view.stride) >> 1)] : cells[x + view.columns * y];
  }

  // Whether the cell blocks: map 0 for terrain model `model` (bit 0x40 bypasses), other maps for the player (0x80) or an NPC (0xC0).
  function cellBlocked(view, cell, { model = 0x69, conditional = false, npc = false } = {}) {
    if (view.packed) return !(cell & 0x40) && terrainBlocked(model, cell, conditional);
    return (cell & (npc ? 0xc0 : 0x80)) !== 0;
  }

  function bgPram(rom, view) {
    const pram = new Uint8Array(0x200);
    for (const [offset, recipe] of view.palettes) { const colorsBytes = source(rom, recipe); pram.set(colorsBytes.subarray(0, Math.min(colorsBytes.length, 0x200 - offset)), offset); }
    return pram;
  }

  async function sha1(bytes) {
    const digest = await crypto.subtle.digest("SHA-1", bytes);
    return Array.from(new Uint8Array(digest), b => b.toString(16).padStart(2, "0")).join("");
  }

  // Decode one view of an item at `address`. Returns {kind, image?, text?, bytes?, wav?, check} where check is
  // {ok, detail} comparing the JS result with what Rust recorded (null when the recipe has nothing to compare).
  async function render(rom, address, view) {
    if (view.t === "lz77") {
      const bytes = lz77(rom, address), hash = await sha1(bytes);
      const out = { kind: "lz77", bytes, use: view.use, check: { ok: hash === view.sha1, detail: `decoded ${bytes.length} bytes, SHA-1 ${hash === view.sha1 ? "matches" : "differs from"} the Rust decode` } };
      if (view.use === "palette") out.image = swatch(bytes);
      else if (view.use === "tiles" || view.use === "raw") out.image = tiles(bytes, 4, null);
      return out;
    }
    if (view.t === "palette") return { kind: "palette", image: swatch(source(rom, view.colors)), check: null };
    if (view.t === "tiles") {
      const data = source(rom, view.tiles), palette = view.palette ? source(rom, view.palette) : null;
      return { kind: "tiles", image: tiles(data, view.bpp, palette), check: null };
    }
    if (view.t === "glyphs") return { kind: "glyphs", image: glyphs(source(rom, view.data), view.size), check: null };
    if (view.t === "tilemap") {
      const tileData = source(rom, view.tiles), entries = u16s(source(rom, view.map));
      return { kind: "tilemap", image: tilemap(tileData, entries, source(rom, view.palette), view.width, view.bpp === 8), check: null };
    }
    if (view.t === "layer") {
      const entryBytes = source(rom, view.entries), hash = await sha1(entryBytes);
      const img = tilemap(source(rom, view.tiles), u16s(entryBytes), source(rom, view.palette), view.columns, false);
      return { kind: "layer", name: view.name, image: img, check: { ok: hash === view.sha1, detail: `${view.columns}x${view.rows} tilemap entries, SHA-1 ${hash === view.sha1 ? "matches" : "differs from"} the Rust layer` } };
    }
    if (view.t === "text") {
      const result = text(rom, address, view.g);
      return { kind: "text", text: result.text, grammar: view.g, check: { ok: result.end === view.end, detail: `${view.g} grammar stops at 0x${result.end.toString(16).toUpperCase()}, Rust read up to 0x${view.end.toString(16).toUpperCase()}` } };
    }
    if (view.t === "bg") {
      const data = source(rom, view.tiles), pram = bgPram(rom, view);
      const width = view.columns * 8, height = view.rows * 8, pixels = new Uint8Array(width * height);
      for (let tile = 0; tile < view.columns * view.rows; tile++) {
        if ((tile + 1) * 64 > data.length) continue;
        for (let i = 0; i < 64; i++) pixels[((tile / view.columns | 0) * 8 + (i >> 3)) * width + (tile % view.columns) * 8 + (i & 7)] = data[tile * 64 + i];
      }
      const all = new Uint8Array(pixels.length + 0x200); all.set(pixels); all.set(pram, pixels.length);
      const hash = await sha1(all), img = image(width, height), palette = colors(pram);
      pixels.forEach((value, i) => { if (value) put(img, i % width, i / width | 0, palette[value]); });
      return { kind: "bg", image: img, check: { ok: hash === view.sha1, detail: `${view.columns}x${view.rows} 256-colour tiles, SHA-1 of pixels and palette ${hash === view.sha1 ? "matches" : "differs from"} the Rust render` } };
    }
    if (view.t === "map") {
      const cells = source(rom, view.collision), mask = new Uint8Array(view.columns * view.rows);
      for (let y = 0; y < view.rows; y++) for (let x = 0; x < view.columns; x++) {
        const cell = collisionCell(view, cells, x, y);
        mask[y * view.columns + x] = view.packed ? (cell & 0x40 ? 0 : terrainBlocked(0x69, cell, false) ? 1 : 0) : cell === undefined ? 0xff : cell & 0x80;
      }
      const hash = await sha1(mask);
      return { kind: "map", cells, check: { ok: hash === view.sha1, detail: `${view.columns}x${view.rows} collision cells, SHA-1 of the default collision mask ${hash === view.sha1 ? "matches" : "differs from"} the Rust port` } };
    }
    if (view.t === "songs") return { kind: "note", check: null };
    if (view.t === "script_battles") return { kind: "note", check: null };
    if (view.t === "unbound") return { kind: "note", reasons: view.reasons, check: null };
    if (view.t === "sprite") {
      const frames = spriteFrames(rom, view), choices = view.family ? view.family.choices.length : 1, parts = [];
      let first = null;
      for (let choice = 0; choice < choices; choice++) {
        const { vram, pram } = spriteMemory(rom, view, choice), rendered = spritePixels(frames, view.tile, view.palette, vram);
        for (const f of rendered) { parts.push(new Uint8Array([f.width & 0xff, f.width >> 8, f.height & 0xff, f.height >> 8]), f.pixels); }
        parts.push(pram);
        if (choice === 0) first = { rendered, pram };
      }
      const all = new Uint8Array(parts.reduce((n, p) => n + p.length, 0));
      let at = 0;
      for (const p of parts) { all.set(p, at); at += p.length; }
      const hash = await sha1(all);
      return { kind: "sprite", image: spriteSheet(first.rendered, first.pram), frames: first.rendered, pram: first.pram, animations: spriteAnimations(rom, view),
        check: { ok: hash === view.sha1, detail: `${frames.length} frame(s)${view.family ? ` x ${choices} ${view.family.label} choices` : ""}, SHA-1 of pixels and palette ${hash === view.sha1 ? "matches" : "differs from"} the Rust render` } };
    }
    if (view.t === "wav") {
      const samples = source(rom, view.samples);
      return { kind: "wav", wav: wav(new Int8Array(samples.buffer, samples.byteOffset, samples.length), view.rate), rate: view.rate, check: null };
    }
    throw new Error(`unknown view ${view.t}`);
  }

  scope.ZoidsDecode = { BASE, lz77, source, swatch, tiles, glyphs, tilemap, text, wav, sha1, render, u16s, spriteFrames, spriteMemory, spritePixels, spriteImage, spriteSheet, spriteAnimations, terrainBlocked, collisionCell, cellBlocked };
  if (typeof module !== "undefined") module.exports = scope.ZoidsDecode;
})(typeof globalThis !== "undefined" ? globalThis : this);
