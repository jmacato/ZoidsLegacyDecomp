// The battle field in the page: decodes the field's images from the user's ROM (terrain, sky, unit icons, gauge) to RGBA,
// hands them and the ROM tables the engine needs (sine table, unit positions) to the engine (battle-engine.js), and reads
// back finished frames.
(function (scope) {
  "use strict";
  const TERRAIN = 0x7af614, ICON_TILES = 0x7aa70c, ICON_PALETTES = 0x7aa96c, POSITIONS = 0x7a2790, SINE = 0xed184, ZOID_RECORDS = 0x7afcc4;
  const GAUGE_TILES = 0x277be4, GAUGE_COLORS = 0x277ce4, DOUBLE_ICON = 4;

  const rgba = color => { const r = color & 31, g = color >> 5 & 31, b = color >> 10 & 31; return (((r << 3) | (r >> 2)) | (((g << 3) | (g >> 2)) << 8) | (((b << 3) | (b >> 2)) << 16) | 0xff000000) >>> 0; };
  const colorsOf = bytes => Array.from({ length: bytes.length >> 1 }, (_, i) => bytes[i * 2] | (bytes[i * 2 + 1] << 8));

  // The palettes the field's loader builds: a compressed palette is copied in whole 32-byte blocks of its decoded size,
  // and the first background color (the backdrop) keeps its previous value.
  function loadedColors(archive, pointerAt, colors, offset, keepFirst) {
    const data = archive.lz(archive.pointer(pointerAt)), bytes = Math.ceil(((data.length << 9) >>> 11) / 8) * 32;
    const loaded = colorsOf(data.subarray(0, Math.min(bytes, data.length)));
    for (let i = 0; i < loaded.length && offset + i < colors.length; i++) if (!(keepFirst && offset + i === 0)) colors[offset + i] = loaded[i];
    return colors;
  }
  // 8-bit tiles laid out `columns` tiles wide, index 0 left transparent.
  function tiles8(data, columns, rows, colors) {
    const width = columns * 8, out = new Uint32Array(width * rows * 8);
    for (let tile = 0; tile < columns * rows; tile++) for (let y = 0; y < 8; y++) for (let x = 0; x < 8; x++) {
      const index = data[tile * 64 + y * 8 + x], at = ((tile / columns | 0) * 8 + y) * width + (tile % columns) * 8 + x;
      out[at] = index ? rgba(colors[index]) : 0;
    }
    return out;
  }
  // 4-bit tiles laid out `columns` tiles wide (one-dimensional sprite layout), index 0 left transparent.
  function tiles4(data, columns, rows, colors) {
    const width = columns * 8, out = new Uint32Array(width * rows * 8);
    for (let tile = 0; tile < columns * rows; tile++) for (let y = 0; y < 8; y++) for (let x = 0; x < 8; x++) {
      const index = (data[tile * 32 + y * 4 + (x >> 1)] >> ((x & 1) * 4)) & 15, at = ((tile / columns | 0) * 8 + y) * width + (tile % columns) * 8 + x;
      out[at] = index ? rgba(colors[index]) : 0;
    }
    return out;
  }

  // Terrains whose four graphics pointers all point into the ROM; the rest are unused slots.
  const terrainAvailable = (archive, terrain) => [0, 4, 8, 12].every(offset => { const value = archive.u32(TERRAIN + terrain * 16 + offset); return value >= 0x08000000 && value < 0x08000000 + archive.rom.length; });
  function terrainImages(archive, terrain) {
    const record = TERRAIN + terrain * 16, colors = new Array(256).fill(0);
    loadedColors(archive, record + 4, colors, 0, true);
    loadedColors(archive, record + 12, colors, 0x40, false);
    return { ground: tiles8(archive.lz(archive.pointer(record)), 8, 8, colors), sky: tiles8(archive.lz(archive.pointer(record + 8)), 16, 16, colors), backdrop: rgba(colors[0]) };
  }
  function iconImage(archive, zoid, palette) {
    const colors = loadedColors(archive, ICON_PALETTES + zoid * 32 + palette * 4, new Array(16).fill(0), 0, false);
    return tiles4(archive.lz(archive.pointer(ICON_TILES + zoid * 4)), 8, 8, colors);
  }
  const gaugeImage = archive => tiles4(archive.rom.subarray(GAUGE_TILES, GAUGE_TILES + 256), 4, 2, colorsOf(archive.rom.subarray(GAUGE_COLORS, GAUGE_COLORS + 32)));

  const Engine = scope.ZoidsBattleEngine || (typeof require === "function" ? require("./battle-engine.js") : null);
  const CAMERA = { overview: [0], intro: [1], "player-near": [2, 0], "enemy-near": [2, 1], "player-wide": [3, 0], "enemy-wide": [3, 1], "player-far": [4, 0], "enemy-far": [4, 1] };
  const bytesOf = pixels => new Uint8ClampedArray(pixels.buffer, pixels.byteOffset, pixels.length * 4).slice();

  class BattleField {
    // sides: two arrays of six {zoid, palette} or null.
    constructor(archive, { terrain = 0, sides = [[], []] } = {}) {
      const images = terrainImages(archive, terrain), image = (width, height, pixels) => ({ width, height, pixels });
      const icons = [0, 1].map(side => Array.from({ length: 6 }, (_, unit) => {
        const entry = sides[side]?.[unit];
        return image(64, 64, entry ? iconImage(archive, entry.zoid, entry.palette || 0) : new Uint32Array(64 * 64));
      }));
      this.field = new Engine.Field({
        sine: Array.from({ length: 65 }, (_, i) => archive.u16(SINE + i * 2)),
        ground: image(64, 64, images.ground), sky: image(128, 128, images.sky), gauge: image(32, 16, gaugeImage(archive)), icons, backdrop: images.backdrop,
        positions: Array.from({ length: 12 }, (_, i) => [0, 4, 8].map(offset => archive.i32(POSITIONS + i * 12 + offset))),
      });
      for (let side = 0; side < 2; side++) for (let unit = 0; unit < 6; unit++) {
        const entry = sides[side]?.[unit];
        this.field.setUnit(side, unit, !!entry, !!entry && archive.u8(ZOID_RECORDS + entry.zoid * 56 + 2) === DOUBLE_ICON);
      }
      this.pixels = new Uint32Array(240 * 160);
      this.updates = 0;
    }
    camera(name, immediate) { const [mode, side = 0] = CAMERA[name] || CAMERA.overview; this.field.cameraStart(mode, side, 0, name === "intro" || immediate); this.updates = 0; this.settled = false; }
    // The camera pose, to hand a running view over to a new field.
    pose() { const p = this.field.camera.pose; return [p.x, p.z, p.depth, p.pitch, p.yaw, p.roll]; }
    // Continue a camera move from another field's pose: same mode and target, starting where that view was.
    resume(name, [x, z, depth, pitch, yaw, roll]) {
      const [mode, side = 0] = CAMERA[name] || CAMERA.overview;
      this.field.camera.pose = { x, z, depth, pitch, yaw, roll };
      this.field.cameraStart(mode, side, 0, false); this.updates = 0; this.settled = false;
    }
    // One field update; returns true once the camera has stopped moving.
    step() { this.field.update(); this.settled = this.field.camera.settled; this.updates++; return this.settled; }
    // The current frame as 240x160 RGBA bytes.
    frame() { this.field.render(this.pixels); return bytesOf(this.pixels); }
    // The frame during the battle's opening fade from black, `steps` camera updates after the intro started.
    fadedFrame(steps) { this.field.render(this.pixels); Engine.darken(this.pixels, Engine.openingFadeLevel(steps)); return bytesOf(this.pixels); }
  }

  const Z_OUTLINE = 0x7ed854, Z_DURATION = 36;

  // Encounters (TrySelectFieldRandomEncounter, SelectFieldRandomEncounterTable): a world-map cell's group and threshold, or
  // the current map's {map, threshold, group} record; a group holds 20 encounters of a song and six unit records.
  const ENCOUNTERS = 0x7b9454, WORLD_GRID = 0x478fa0, WORLD_THRESHOLDS = 0x7c3864, MAP_ENCOUNTERS = 0x7c3884;
  function worldEncounter(archive, cellX, cellY, widthTiles) {
    const tile = archive.u16(WORLD_GRID + ((((cellY & 0xff) * widthTiles) >>> 1) + (cellX & 0xff)) * 2);
    return { group: tile & 0xff, threshold: archive.u16(WORLD_THRESHOLDS + (tile >>> 8) * 2) };
  }
  function mapEncounter(archive, map) {
    let index = 0;
    if (archive.u16(MAP_ENCOUNTERS)) while (archive.u16(MAP_ENCOUNTERS + index * 6) && archive.u16(MAP_ENCOUNTERS + index * 6) !== map) index++;
    const at = MAP_ENCOUNTERS + index * 6;
    return { group: archive.u16(at + 4), threshold: archive.u16(at + 2), matched: archive.u16(at) === map };
  }
  function encounterGroup(archive, group) {
    return Array.from({ length: 20 }, (_, index) => {
      const at = ENCOUNTERS + group * 2000 + index * 100;
      const units = Array.from({ length: 6 }, (_, slot) => {
        const unit = at + 4 + slot * 16;
        return archive.u8(unit) ? { zoid: archive.u8(unit), palette: archive.u8(unit + 1), pilot: archive.u8(unit + 2), equipment: [0, 1, 2, 3].map(k => archive.u8(unit + 4 + k)), experience: archive.u32(unit + 8), money: archive.u32(unit + 12) } : null;
      });
      return { index, song: archive.u8(at), units, address: at, candidate: units.some(Boolean) };
    });
  }

  // The field a battle starts from, stepped update by update and closed by a screen transition. spec: { world, clouds,
  // sea, widthTiles, heightTiles, bg0Tilemap, bg1Tilemap, follow, backdrop, player: {x, y} (1/256 pixels), blend,
  // layers: [{ index, role, priority, image: {width, height, rgba}, left, top, wrapWidth, wrapHeight }],
  // sprites: [{ x, y, priority, frames: [{width, height, left, top, rgba}], steps, hold, loop, decoration, tileX, tileY }] }.
  const pixelsOf = image => ({ width: image.width, height: image.height, pixels: new Uint32Array(image.rgba.buffer, image.rgba.byteOffset, image.width * image.height) });
  class FieldStart {
    constructor(archive, spec) {
      this.outlines = [0, 1].map(w => Array.from({ length: 160 }, (_, y) => [archive.i16(Z_OUTLINE + (w * 160 + y) * 4), archive.i16(Z_OUTLINE + (w * 160 + y) * 4 + 2)]));
      const layers = [null, null, null, null], roles = [0, 0, 0, 0];
      for (const layer of spec.layers) {
        layers[layer.index] = { enabled: true, priority: layer.priority, image: pixelsOf(layer.image), scrollX: 0, scrollY: 0, left: layer.left || 0, top: layer.top || 0, wrapWidth: layer.wrapWidth || 0, wrapHeight: layer.wrapHeight || 0 };
        roles[layer.index] = layer.role;
      }
      const sprites = spec.sprites.map(sprite => ({ ...sprite, frames: sprite.frames.map(frame => ({ image: pixelsOf(frame), left: frame.left, top: frame.top })) }));
      this.state = new Engine.FieldStartState({ world: spec.world, clouds: spec.clouds, sea: spec.sea, widthTiles: spec.widthTiles, heightTiles: spec.heightTiles,
        bg0Tilemap: spec.bg0Tilemap && spec.follow, bg1Tilemap: spec.bg1Tilemap && spec.follow, playerX: spec.player.x, playerY: spec.player.y, layers, roles, blend: spec.blend, sprites, backdrop: spec.backdrop >>> 0 });
      this.state.center();
      this.backdrop = spec.backdrop >>> 0;
      this.scene = new Uint32Array(240 * 160);
      this.pixels = new Uint32Array(240 * 160);
    }
    // Updates before the encounter: the player walks with this velocity (1/256 pixels per update).
    walk(velocityX, velocityY, updates) { Object.assign(this.state, { velocityX, velocityY, locked: false }); for (let i = 0; i < updates; i++) this.state.update(); }
    // The encounter locks the player; every later update is one frame of the closing field.
    lock() { this.state.locked = true; }
    update() { this.state.update(); this.state.draw(this.scene); }
    camera() { return this.state.camera.scroll.slice(0, 2); }
    // The field under the Z after `progress` updates of it, or without a transition for a negative progress.
    frame(progress) {
      if (progress >= 0) Engine.zFrame(this.scene, this.backdrop, this.outlines, progress, this.pixels); else this.pixels.set(this.scene);
      return bytesOf(this.pixels);
    }
    dithered(progress) { Engine.ditherConceal(this.scene, progress, this.pixels); return bytesOf(this.pixels); }
    faded(level) { this.pixels.set(this.scene); Engine.darken(this.pixels, level); return bytesOf(this.pixels); }
  }

  scope.ZoidsBattleField = { FieldStart, Z_OUTLINE, BattleField, Z_DURATION, CAMERA, terrainAvailable, terrainImages, iconImage, gaugeImage, worldEncounter, mapEncounter, encounterGroup };
  if (typeof module === "object" && module.exports) module.exports = scope.ZoidsBattleField;
})(globalThis);
