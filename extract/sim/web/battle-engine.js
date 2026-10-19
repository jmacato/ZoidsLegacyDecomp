// The battle simulator engine: the battle field (camera, perspective ground rows, point projection, unit sprites), the
// screen transitions around a battle (the scaled Z, the dither, fades) and the field a battle starts from (layers,
// sprites, field camera). Integer math follows the game's code: 32-bit wrapping products, 16-bit truncation where the game
// stores 16 bits, divisions and fixed-point shifts that round toward zero. Images are { width, height, pixels } with
// pixels a Uint32Array of RGBA words (alpha 0 where nothing is drawn).
(function (scope) {
  "use strict";
  const SCREEN_WIDTH = 240, SCREEN_HEIGHT = 160, SIDE_COUNT = 2, UNITS_PER_SIDE = 6, NO_HORIZON = 0xff;
  const CAMERA_OVERVIEW = 0, CAMERA_INTRO_OFFSET = 1, CAMERA_SIDE_NEAR = 2, CAMERA_SIDE_WIDE = 3, CAMERA_SIDE_FAR = 4,
    CAMERA_FOCUS_UNIT = 5, CAMERA_OVERVIEW_ALTERNATE = 6, CAMERA_INTRO_CENTERED = 8, CAMERA_FOCUS_UNIT_CLOSE = 9;

  const s16 = value => value << 16 >> 16;
  const u16 = value => value & 0xffff;
  const div = (a, b) => Math.trunc(a / b) | 0;
  const half = value => div(value, 2);
  const shift8 = value => ((value < 0 ? value + 0xff : value) | 0) >> 8;
  const eighth = value => ((value < 0 ? value + 7 : value) | 0) >> 3;

  // ---------- 3D math ----------
  // sine: the game's 65-entry quarter-wave table (fixed 8.8).
  function sin256(sine, angle) {
    const wrapped = angle & 0xff, index = (wrapped & 0x7f) <= 0x3f ? wrapped & 0x3f : 0x40 - (wrapped & 0x3f);
    return wrapped <= 0x7f ? s16(sine[index]) : s16(-sine[index]);
  }
  const cos256 = (sine, angle) => sin256(sine, s16(angle + 0x40));

  // Column-major 3x3 fixed 8.8 product, each element rounded toward zero and kept to 16 bits.
  function multiply(left, right) {
    const out = new Array(9);
    for (let column = 0; column < 3; column++) for (let row = 0; row < 3; row++) {
      let value = 0;
      for (let k = 0; k < 3; k++) value = (value + Math.imul(left[k * 3 + row], right[column * 3 + k])) | 0;
      out[column * 3 + row] = s16(shift8(value));
    }
    return out;
  }
  // Rotation about X, then Y, then Z.
  function buildRotationXyz(sine, x, y, z) {
    const rx = [0x100, 0, 0, 0, cos256(sine, x), sin256(sine, x), 0, s16(-sin256(sine, x)), cos256(sine, x)];
    const ry = [cos256(sine, y), 0, s16(-sin256(sine, y)), 0, 0x100, 0, sin256(sine, y), 0, cos256(sine, y)];
    const rz = [cos256(sine, z), sin256(sine, z), 0, s16(-sin256(sine, z)), cos256(sine, z), 0, 0, 0, 0x100];
    return multiply(multiply(rx, ry), rz);
  }
  const transform = (m, [x, y, z]) => [
    shift8((Math.imul(m[0], x) + Math.imul(y, m[3]) + Math.imul(z, m[6])) | 0),
    shift8((Math.imul(m[1], x) + Math.imul(y, m[4]) + Math.imul(z, m[7])) | 0),
    shift8((Math.imul(m[2], x) + Math.imul(y, m[5]) + Math.imul(z, m[8])) | 0),
  ];

  // ---------- the battle camera ----------
  // pose: { x, z, depth, pitch, yaw, roll } with angles as 16-bit values.
  const cameraPose = (x = 0, z = 0, depth = 0, pitch = 0, yaw = 0, roll = 0) => ({ x, z, depth, pitch, yaw, roll });
  function createCamera() {
    return { pose: cameraPose(), target: cameraPose(), centerX: 0x78, centerY: 0x78, focalLength: 0x80, farClip: 0x20000, mode: 0, settled: true, matrix: new Array(9).fill(0) };
  }
  // The target pose of each battle camera mode (StartBattleCameraTransition).
  const SIDE_X = [[0xd000, -0xd000], [0xb000, -0xf000], [0xc000, -0x10000]];
  function cameraStart(camera, positions, mode, side, unit, immediate) {
    camera.mode = mode;
    const target = (x, z, depth, pitch) => { camera.target = cameraPose(x, z, depth, pitch); };
    switch (mode) {
      case CAMERA_INTRO_OFFSET: target(-0xd000, 0x20000, 0x8000, 4); break;
      case CAMERA_INTRO_CENTERED: target(0, 0x20000, 0x8000, 4); break;
      case CAMERA_SIDE_NEAR: case CAMERA_SIDE_WIDE: case CAMERA_SIDE_FAR: target(SIDE_X[mode - CAMERA_SIDE_NEAR][side ? 1 : 0], 0, 0x8000, 0x20); break;
      case CAMERA_FOCUS_UNIT: case CAMERA_FOCUS_UNIT_CLOSE: {
        const [x, , z] = positions[side * UNITS_PER_SIDE + unit];
        target(x, z, mode === CAMERA_FOCUS_UNIT ? 0x8000 : 0x4000, 0x20);
        break;
      }
      case CAMERA_OVERVIEW: case CAMERA_OVERVIEW_ALTERNATE: target(0, 0, 0x8000, 0x20); break;
    }
    if (immediate) camera.pose = { ...camera.target };
    camera.settled = false;
  }
  function ease(value, target) {
    const delta = (target - value) | 0, next = (value + (((delta < 0 ? delta + 3 : delta) | 0) >> 2)) | 0;
    return (target > next && ((target - next) | 0) <= 0x7f) || (target < next && ((target - next) | 0) > -0x80) ? target : next;
  }
  function turn(angle, target) {
    const current = s16(angle), wanted = s16(target);
    if (current === wanted) return angle;
    const down = current < wanted ? wanted - current > 0x80 : current - wanted <= 0x80;
    return u16(angle + (down ? -1 : 1));
  }
  // One update of the camera move (UpdateBattleCameraTransition): the intro modes descend on z and tilt down to pitch 0x20;
  // the others ease toward the target a quarter of the remaining distance per update and turn one step per update.
  function cameraUpdate(camera) {
    const p = camera.pose, t = camera.target;
    if (camera.settled) return;
    if (camera.mode === CAMERA_INTRO_OFFSET || camera.mode === CAMERA_INTRO_CENTERED) {
      if (p.z <= 0x7fff) {
        p.z = (p.z - (((p.z < 0 ? p.z + 7 : p.z) | 0) >> 3)) | 0;
        if (s16(p.pitch) <= 0x1f) p.pitch = u16(p.pitch + 1);
      } else p.z = (p.z - 0x1000) | 0;
      if (s16(p.pitch) !== 0x20 || p.z > 0x3f) return;
      p.z = 0;
      camera.settled = true;
      return;
    }
    p.x = ease(p.x, t.x); p.z = ease(p.z, t.z); p.depth = ease(p.depth, t.depth);
    p.pitch = turn(p.pitch, t.pitch); p.yaw = turn(p.yaw, t.yaw); p.roll = turn(p.roll, t.roll);
    if (p.x !== t.x || p.z !== t.z || p.depth !== t.depth || p.pitch !== t.pitch || p.yaw !== t.yaw || s16(p.roll) !== s16(t.roll)) return;
    camera.settled = true;
  }
  // The camera matrix uses pitch and negated yaw; roll is tracked but not applied (UpdateCameraRotationMatrix).
  function cameraRotate(camera, sine) { camera.matrix = buildRotationXyz(sine, s16(camera.pose.pitch), s16(-camera.pose.yaw), 0); }

  // For each screen row, the ground point under its left edge and the step per pixel (UpdatePerspectiveScanlineBuffers);
  // returns the first row below the far clip distance, or NO_HORIZON. rows: 160 { uStep, uRowStep, vStep, vRowStep, uOrigin, vOrigin }.
  function cameraGroundRows(camera, sine, rows) {
    const p = camera.pose;
    const pitchCos = cos256(sine, -s16(p.pitch)), pitchSin = sin256(sine, -s16(p.pitch)), yawCos = cos256(sine, -s16(p.yaw)), yawSin = sin256(sine, -s16(p.yaw));
    const focal = camera.focalLength, cx = camera.centerX, cy = camera.centerY;
    const numerator = Math.imul(div(p.depth, 0x100), Math.imul(focal, pitchSin));
    for (let line = 0; line < SCREEN_HEIGHT; line++) {
      const row = rows[line];
      const denominator = Math.imul(div((Math.imul(cy - line, pitchCos) + Math.imul(focal, pitchSin)) | 0, 0x100), focal);
      if (denominator === 0 || pitchSin === 0) { row.uStep = row.uRowStep = row.vStep = row.vRowStep = row.uOrigin = row.vOrigin = 0; continue; }
      const perspective = div(numerator, denominator);
      row.uStep = row.vRowStep = s16(div(Math.imul(yawCos, perspective), 0x100));
      row.uRowStep = s16(div(Math.imul(yawSin, perspective), 0x100));
      row.vStep = s16(-row.uRowStep);
      const forward = div((line - cy) << 8, pitchSin);
      row.uOrigin = (Math.imul(row.uStep, -cx) - Math.imul(row.uRowStep, forward) + p.x) | 0;
      row.vOrigin = (Math.imul(row.vStep, -cx) - Math.imul(row.vRowStep, forward) + p.z) | 0;
    }
    if (s16(pitchCos) !== 0) {
      const row = (div(Math.imul(div(Math.imul((camera.farClip - p.depth) | 0, pitchSin), 0x100), focal), div(Math.imul(pitchCos, camera.farClip), 0x100)) + cy) | 0;
      if ((row >>> 0) <= 159) return row;
    }
    return NO_HORIZON;
  }
  // Screen position and fixed 8.8 scale of a world point in front of the camera and nearer than the far clip
  // (ProjectBattleWorldPoint); positions are kept to 16 bits like the game.
  function cameraProject(camera, [x, y, z]) {
    const p = camera.pose, view = transform(camera.matrix, [(x - p.x) | 0, y, (p.z - z) | 0]);
    const depth = (view[2] + p.depth) | 0, focal = camera.focalLength;
    if (depth < 0 || depth >= camera.farClip || focal === 0) return { visible: false, x: 0, y: 0, scale: 0 };
    return { visible: true, x: s16(camera.centerX + div(Math.imul(view[0], focal), depth)), y: s16(camera.centerY + div(Math.imul(view[1], focal), depth)), scale: s16(div(focal << 16, depth)) };
  }

  // ---------- the battle field ----------
  // images: { sine, ground (64x64), sky (128x128), gauge (32x16), icons[side][unit] (64x64), backdrop }.
  // Each unit has a gauge then an icon, created in that order from slot 127 downward. Side 1 is mirrored; front-to-back
  // rows draw with priorities 3, 2, 1 on side 0 and 1, 2, 3 on side 1.
  class Field {
    constructor({ sine, ground, sky, gauge, icons, backdrop, positions }) {
      Object.assign(this, { sine, ground, sky, gauge, icons, backdrop, positions });
      this.camera = createCamera();
      this.rows = Array.from({ length: SCREEN_HEIGHT }, () => ({ uStep: 0, uRowStep: 0, vStep: 0, vRowStep: 0, uOrigin: 0, vOrigin: 0 }));
      this.horizon = NO_HORIZON; this.skyScrollX = 0; this.skyScrollY = 0; this.updates = 0;
      this.sprites = [];
      for (let side = 0; side < SIDE_COUNT; side++) for (let unit = 0; unit < UNITS_PER_SIDE; unit++) {
        const index = side * UNITS_PER_SIDE + unit;
        const base = { pieceX: 0, pieceY: 0, mirrored: false, doubleSize: false, hidden: true, used: false, x: 0, y: 0, scale: 0x100, rotation: 0, projected: false, world: [0, 0, 0], follows: null, followX: 0 };
        const icon = { ...base, image: icons[side][unit], pieceX: -32, pieceY: -64, priority: side ? unit % 3 + 1 : 3 - unit % 3, layer: 3, mirrored: side === 1, slot: 126 - index * 2, projected: true };
        const gauge = { ...base, image: this.gauge, pieceY: -16, priority: 1, layer: 0, slot: 127 - index * 2, follows: icon, followX: side ? -0x30 : 16 };
        this.sprites.push(gauge, icon);
      }
    }
    setUnit(side, unit, present, doubleIcon) {
      const index = side * UNITS_PER_SIDE + unit, gauge = this.sprites[index * 2], icon = this.sprites[index * 2 + 1];
      icon.used = gauge.used = present;
      icon.hidden = gauge.hidden = !present;
      icon.doubleSize = present && doubleIcon;
      icon.world = this.positions[index];
    }
    cameraStart(mode, side, unit, immediate) { cameraStart(this.camera, this.positions, mode, side, unit, immediate); }
    // One field update (RunBattleCameraTask): the camera move, the ground rows and sky scroll, the camera matrix, then each
    // sprite in slot order (icons project themselves; gauges follow their icon).
    update() {
      const camera = this.camera;
      cameraUpdate(camera);
      this.horizon = cameraGroundRows(camera, this.sine, this.rows);
      cameraRotate(camera, this.sine);
      const x = camera.pose.x;
      this.skyScrollX = ((x < 0 ? x + 3 : x) | 0) >> 2 >> 8;
      this.skyScrollY = 0x80 - this.horizon;
      for (const s of this.bySlot()) {
        if (!s.used) continue;
        if (s.projected) {
          const point = cameraProject(camera, s.world);
          if (point.visible) { s.x = u16(point.x); s.y = u16(point.y); }
          const limit = s.doubleSize ? point.scale << 17 : point.scale << 16;
          s.scale = s.doubleSize ? s16(point.scale << 1) : point.scale;
          s.hidden = !point.visible || limit > 0x3000000;
        } else if (s.follows) {
          s.hidden = s.follows.hidden;
          if (!s.hidden) { s.x = u16(s.follows.x + s.followX); s.y = s.follows.y; }
        }
      }
      this.updates++;
    }
    bySlot() { return [...this.sprites].sort((a, b) => a.slot - b.slot); }
    // Insertion order of the game's sprite sort (SortActiveSprites): by priority, then layer, keeping slot order otherwise.
    drawOrder() {
      const order = [];
      for (const s of this.bySlot()) {
        let at = order.length;
        while (at > 0 && (s.priority < order[at - 1].priority || (s.priority === order[at - 1].priority && s.layer < order[at - 1].layer))) at--;
        order.splice(at, 0, s);
      }
      return order;
    }
    sampleSky(x, y) {
      const u = (x + this.skyScrollX) & 255, v = (y + this.skyScrollY) & 255, pixels = this.sky.pixels;
      return v < 128 ? pixels[v * 128 + (u & 127)] : pixels[(v & 7) * 128 + (u & 7)];
    }
    sampleGround(row, x) {
      const u = (((row.uOrigin << 4) >> 4) + Math.imul(row.uStep, x)) >> 8, v = (((row.vOrigin << 4) >> 4) + Math.imul(row.vStep, x)) >> 8;
      return this.ground.pixels[(v & 63) * 64 + (u & 63)];
    }
    // The sky shows above the horizon row and the ground below it; sprites draw over both, the first sprite in draw order
    // winning where several overlap at the same priority. Each row has mGBA 0.10.5's object budget of 1210 units: a sprite
    // costs its width, or 10 plus twice its area width when transformed, and a row stops taking sprites once it is spent.
    render(out) {
      const placed = [];
      for (const s of this.drawOrder()) {
        if (!s.used || s.hidden || s.scale === 0) continue;
        const p = place(s);
        if (!p) continue;
        const rawX = p.left & 0x1ff, rawY = p.top & 0xff;
        if (rawY >= SCREEN_HEIGHT && rawY + p.areaHeight < 228) continue;
        if (rawX >= SCREEN_WIDTH && rawX + p.areaWidth < 512) continue;
        placed.push(p);
      }
      const claimed = new Uint8Array(SCREEN_WIDTH), drawn = new Uint8Array(SCREEN_WIDTH);
      for (let y = 0; y < SCREEN_HEIGHT; y++) {
        const sky = this.horizon !== NO_HORIZON && y < this.horizon, line = y * SCREEN_WIDTH, row = this.rows[y];
        for (let x = 0; x < SCREEN_WIDTH; x++) {
          const texel = sky ? this.sampleSky(x, y) : this.sampleGround(row, x);
          out[line + x] = texel >>> 24 ? texel : this.backdrop;
        }
        claimed.fill(4); drawn.fill(0);
        let budget = 1210;
        for (const p of placed) {
          if (y < p.top || y >= p.top + p.areaHeight) continue;
          for (let x = p.left < 0 ? 0 : p.left; x < p.left + p.areaWidth && x < SCREEN_WIDTH; x++) {
            if (p.priority >= claimed[x]) continue;
            let dx = x - p.left, dy = y - p.top;
            if (p.transformed) {
              const cx = dx - div(p.areaWidth, 2), cy = dy - div(p.areaHeight, 2);
              dx = ((Math.imul(p.m[0], cx) + Math.imul(p.m[1], cy)) >> 8) + div(p.width, 2);
              dy = ((Math.imul(p.m[2], cx) + Math.imul(p.m[3], cy)) >> 8) + div(p.height, 2);
              if (dx < 0 || dy < 0 || dx >= p.width || dy >= p.height) continue;
            } else if (p.flipX) dx = p.width - 1 - dx;
            const texel = p.image.pixels[dy * p.width + dx];
            if (!(texel >>> 24)) { if (drawn[x]) claimed[x] = p.priority; continue; }
            out[line + x] = texel; claimed[x] = p.priority; drawn[x] = 1;
          }
          budget -= p.transformed ? 10 + p.areaWidth * 2 : p.width;
          if (budget <= 0) break;
        }
      }
    }
  }
  // Where a sprite's piece lands: its offset scaled about the piece centre by the sprite scale, mirrored for side 1, doubled
  // in area when the icon is drawn at double size, then culled when no part of the scaled image reaches the screen. The
  // transform maps screen offsets from the area centre back to image offsets (fixed 8.8).
  function place(s) {
    const w = s.image.width, h = s.image.height, scale = s.scale;
    let x, y;
    if (s.rotation === 0 && scale === 0x100) { x = u16(s.pieceX); y = u16(s.pieceY); }
    else {
      let cx = u16(half(w) + s.pieceX), cy = u16(half(h) + s.pieceY);
      if (scale !== 0x100) { cx = u16(shift8(Math.imul(s16(cx), scale))); cy = u16(shift8(Math.imul(s16(cy), scale))); }
      x = u16(s16(cx) + half(-w));
      y = u16(s16(cy) + half(-h));
    }
    let areaWidth = w, areaHeight = h;
    if (s.mirrored) x = u16(-s16(x) - w);
    if (s.doubleSize) { x = u16(s16(x) - half(w)); y = u16(s16(y) - half(h)); areaWidth = w * 2; areaHeight = h * 2; }
    let left = s16(s16(x) + s.x), top = s16(s16(y) + s.y), clipWidth = w, clipHeight = h;
    if (scale !== 0x100) {
      clipWidth = Math.min(s16(shift8(0x100 * shift8(Math.imul(w, scale)))), areaWidth);
      clipHeight = Math.min(s16(shift8(0x100 * shift8(Math.imul(h, scale)))), areaHeight);
    }
    if (left <= -clipWidth || top <= -clipHeight || left >= SCREEN_WIDTH - half(areaWidth - clipWidth) || top >= SCREEN_HEIGHT - half(areaHeight - clipHeight)) return null;
    left &= 0x1ff; if (left >= 256) left -= 512;
    top &= 0xff; if (top + areaHeight >= 256) top -= 256;
    const placement = { image: s.image, left, top, width: w, height: h, areaWidth, areaHeight, priority: s.priority, transformed: false, flipX: false, m: [0, 0, 0, 0] };
    if (!(s.rotation !== 0 || scale !== 0x100 || s.doubleSize)) { placement.flipX = s.mirrored; return placement; }
    const pa = div(0x1000000, Math.imul(scale, 0x100));
    placement.transformed = true;
    placement.m = [s16(s.mirrored ? -pa : pa), 0, 0, s16(pa)];
    return placement;
  }

  // ---------- screen transitions ----------
  const Z_WINDOWS = 2, Z_DURATION = 36, FADE_DURATION = 8, FULL_DARK = 16, DITHER_DURATION = 28;
  // The Z's outline rows (160 [left, right] source columns) scaled about the screen centre by scaleX, the source rows
  // advanced by 0x10000 / scaleY (BuildScaledScanlineWindows); returns 160 [left, right) covered screen columns.
  function zSpans(outline, scaleX, scaleY) {
    const out = Array.from({ length: SCREEN_HEIGHT }, () => [0, 0]);
    if (scaleX === 0 || scaleY === 0) return out;
    const clamp = x => x < 0 ? 0 : x > SCREEN_WIDTH ? SCREEN_WIDTH : x, rowStep = u16(div(0x10000, scaleY));
    let sourceY = 0x5000 - rowStep * 80;
    for (let y = 0; y < SCREEN_HEIGHT; y++) {
      sourceY = (sourceY + rowStep) | 0;
      if ((sourceY >>> 0) > 0x9fff) continue;
      const [rowLeft, rowRight] = outline[shift8(sourceY)];
      if (rowLeft >= rowRight) continue;
      out[y] = [clamp(s16(shift8(Math.imul(rowLeft - 120, scaleX)) + 120)), clamp(s16(shift8(Math.imul(rowRight - 120, scaleX)) + 120))];
    }
    return out;
  }
  const zScale = progress => u16((progress & 0xff) * (progress & 0xff));
  const fadeFromBlackLevel = (progress, duration) => FULL_DARK - div(progress * 16, duration);
  // The display's brightness decrease by level / 16: c - (c * level >> 4) per 5-bit channel.
  function darkenPixel(pixel, level) {
    let out = pixel & 0xff000000;
    for (let shift = 0; shift < 24; shift += 8) {
      let c = (pixel >>> shift & 0xff) >> 3;
      c -= (c * level) >> 4;
      out |= ((c << 3) | (c >> 2)) << shift;
    }
    return out >>> 0;
  }
  function darken(pixels, level) {
    if (level <= 0) return;
    level = Math.min(level, FULL_DARK);
    for (let i = 0; i < pixels.length; i++) pixels[i] = darkenPixel(pixels[i], level);
  }
  // Close the Z over a scene: covered pixels show the backdrop, the rest the scene darkened by `level`. Screen row y takes
  // the spans of row y - 1 (row 0 for the first two rows), as the game's HBlank routine sets them one line ahead.
  function zConceal(scene, backdrop, spans, level, out) {
    level = Math.min(level, FULL_DARK);
    for (let y = 0; y < SCREEN_HEIGHT; y++) {
      const row = y ? y - 1 : 0;
      for (let x = 0; x < SCREEN_WIDTH; x++) {
        const covered = spans.some(window => window[row][0] <= x && x < window[row][1]), pixel = scene[y * SCREEN_WIDTH + x];
        out[y * SCREEN_WIDTH + x] = covered ? backdrop : level > 0 ? darkenPixel(pixel, level) : pixel;
      }
    }
  }
  // The scene under the Z after `progress` updates; at the last update the screen outside the Z is fully dark.
  function zFrame(scene, backdrop, outlines, progress, out) {
    progress = Math.min(progress, Z_DURATION);
    const scale = zScale(progress);
    zConceal(scene, backdrop, outlines.map(outline => zSpans(outline, scale, scale)), progress === Z_DURATION ? FULL_DARK : 0, out);
  }
  // The dither conceal (BuildScreenTransitionFrame kind 18): rows in groups of eight go black one row per update, group g
  // starting at update g; a line shows the mask of the row above it. At the last update the whole screen is black.
  function ditherRowBlack(progress, row) {
    const group = row >> 3, subrow = row & 7;
    if (progress < group) return false;
    if (progress >= group + 8) return true;
    return (progress - group) % 8 > subrow;
  }
  function ditherConceal(scene, progress, out) {
    for (let y = 0; y < SCREEN_HEIGHT; y++) {
      const black = progress >= DITHER_DURATION || ditherRowBlack(progress, y ? y - 1 : 0);
      for (let x = 0; x < SCREEN_WIDTH; x++) out[y * SCREEN_WIDTH + x] = black ? 0xff000000 : scene[y * SCREEN_WIDTH + x];
    }
  }
  // The battle frame `steps` camera updates into the opening fade from black (the camera's first update shares the fade's first frame).
  function openingFadeLevel(steps) {
    const progress = steps - 1;
    return progress < 0 ? FULL_DARK : progress > FADE_DURATION ? 0 : fadeFromBlackLevel(progress, FADE_DURATION);
  }

  // ---------- the field a battle starts from ----------
  // Up to four background layers and a list of sprites, composed the way the display stacks them (priority, then sprites
  // over backgrounds of the same priority, then the lower layer number) with one alpha blend between a first-target pixel
  // and the second-target pixel under it. Target bits: layers 0-3, sprites 4, backdrop 5.
  // layers[i]: { enabled, priority, image, scrollX, scrollY, left, top, wrapWidth, wrapHeight }; sprites (earlier drawn
  // over later): { image, x, y, priority }; blend: { first, second, eva, evb } or null.
  function layerPixel(layer, x, y) {
    let lx = x + layer.scrollX - layer.left, ly = y + layer.scrollY - layer.top;
    if (layer.wrapWidth) lx = ((lx % layer.wrapWidth) + layer.wrapWidth) % layer.wrapWidth;
    if (layer.wrapHeight) ly = ((ly % layer.wrapHeight) + layer.wrapHeight) % layer.wrapHeight;
    if (lx < 0 || ly < 0 || lx >= layer.image.width || ly >= layer.image.height) return 0;
    return layer.image.pixels[ly * layer.image.width + lx];
  }
  function blendPixel(a, b, eva, evb) {
    let out = 0xff000000;
    for (let shift = 0; shift < 24; shift += 8) {
      const c = Math.min(31, (((a >>> shift & 0xff) >> 3) * eva + ((b >>> shift & 0xff) >> 3) * evb) >> 4);
      out |= ((c << 3) | (c >> 2)) << shift;
    }
    return out >>> 0;
  }
  function composeScene({ layers, sprites, blend, backdrop }, out) {
    const eva = blend ? Math.min(blend.eva, 16) : 0, evb = blend ? Math.min(blend.evb, 16) : 0;
    for (let y = 0; y < SCREEN_HEIGHT; y++) for (let x = 0; x < SCREEN_WIDTH; x++) {
      let sprite = 0, spritePriority = 4;
      for (const s of sprites) {
        const sx = x - s.x, sy = y - s.y;
        if (sx < 0 || sy < 0 || sx >= s.image.width || sy >= s.image.height) continue;
        const pixel = s.image.pixels[sy * s.image.width + sx];
        if (!(pixel >>> 24)) continue;
        sprite = pixel; spritePriority = s.priority;
        break;
      }
      const colors = [backdrop, backdrop], targets = [5, 5];
      let found = 0;
      for (let priority = 0; priority < 4 && found < 2; priority++) {
        if (sprite && spritePriority === priority) { colors[found] = sprite; targets[found++] = 4; }
        for (let l = 0; l < layers.length && found < 2; l++) {
          const layer = layers[l];
          if (!layer?.enabled || layer.priority !== priority) continue;
          const pixel = layerPixel(layer, x, y);
          if (pixel >>> 24) { colors[found] = pixel; targets[found++] = l; }
        }
      }
      let pixel = colors[0];
      if (blend && found >= 1 && (blend.first >> targets[0] & 1) && (blend.second >> targets[1] & 1)) pixel = blendPixel(colors[0], colors[1], eva, evb);
      out[y * SCREEN_WIDTH + x] = (pixel | 0xff000000) >>> 0;
    }
  }
  // The field camera (UpdateFieldCameraFollow): background scroll offsets in 1/256 pixels [BG0 x, y, BG1 x, y], eased an
  // eighth of the way toward the followed actor minus (120, 80) each update; off the world map the step stops at the edges.
  // camera: { scroll, world, widthTiles, heightTiles, bg0Tilemap, bg1Tilemap }.
  function fieldCameraFollow(camera, actorX, actorY) {
    const scroll = camera.scroll, cameraX = scroll[0], unclampedX = eighth((actorX - 0x7800 - cameraX) | 0);
    let stepX = unclampedX, stepY = eighth((actorY - 0x5000 - scroll[1]) | 0);
    if (camera.world) {
      if (stepX < -0x800) stepX += camera.widthTiles << 8; else if (stepX > 0x800) stepX -= camera.widthTiles << 8;
      if (stepY < -0x800) stepY += camera.heightTiles << 8; else if (stepY > 0x800) stepY -= camera.heightTiles << 8;
    } else {
      if (unclampedX < 0) stepX = Math.max(stepX, eighth(-cameraX));
      else if (unclampedX > 0) stepX = Math.min(stepX, eighth((((camera.widthTiles - 30) << 11) - cameraX) | 0));
      if (stepY < 0) stepY = Math.max(stepY, eighth(-scroll[1]));
      else if (stepY > 0) stepY = Math.min(stepY, eighth((((camera.heightTiles - 20) << 11) - scroll[1]) | 0));
    }
    if (camera.bg0Tilemap) { scroll[0] = (scroll[0] + stepX) & 0xfffff; scroll[1] = (scroll[1] + stepY) & 0xfffff; }
    if (camera.bg1Tilemap) { scroll[2] = (scroll[2] + stepX) & 0xfffff; scroll[3] = (scroll[3] + stepY) & 0xfffff; }
  }
  // Layer roles: scrolled by the camera, by the camera's BG1 offsets, the world map's drifting clouds, the world map's sea.
  const LAYER_CAMERA = 0, LAYER_CAMERA_BG1 = 1, LAYER_CLOUDS = 2, LAYER_SEA = 3;
  // The field at the moment a battle starts, update by update: the followed actor (moving until the encounter locks it),
  // the field camera, the world map's cloud layer (BG1, -0x40 / +0x30 per update) and sea layer (BG2, +0x10), and the
  // field sprites with their animations (UpdateFieldDisplay, UpdateFieldActors, UpdateSpritesAndBuildOam).
  // sprites (display order): { x, y, priority, frames: [{ image, left, top }], steps: [{ frame, duration }], hold, loop,
  // decoration, tileX, tileY }; a decoration is drawn only while its tile is within the camera window plus two tiles.
  class FieldStartState {
    constructor({ world, clouds, sea, widthTiles, heightTiles, bg0Tilemap, bg1Tilemap, playerX, playerY, layers, roles, blend, sprites, backdrop }) {
      Object.assign(this, { clouds, sea, playerX, playerY, roles, velocityX: 0, velocityY: 0, locked: false, bg1DeltaX: 0, bg1DeltaY: 0, bg2DeltaY: 0 });
      this.camera = { scroll: [0, 0, 0, 0], world, widthTiles, heightTiles, bg0Tilemap, bg1Tilemap };
      this.scene = { layers, sprites: [], blend, backdrop };
      this.sprites = sprites.map(sprite => ({ ...sprite, step: 0, age: 0 }));
    }
    // Centre the camera on the player the way InitializeFieldMapGraphics does when the map loads.
    center() {
      let x = (this.playerX - 0x7800) | 0, y = (this.playerY - 0x5000) | 0;
      const camera = this.camera;
      if (!camera.world) {
        x = Math.max(0, Math.min(x, (camera.widthTiles - 30) << 11));
        y = Math.max(0, Math.min(y, (camera.heightTiles - 20) << 11));
      }
      camera.scroll = [x, y, x, y];
    }
    update() {
      if (!this.locked) { this.playerX = (this.playerX + this.velocityX) | 0; this.playerY = (this.playerY + this.velocityY) | 0; }
      fieldCameraFollow(this.camera, this.playerX, this.playerY);
      if (this.clouds) { this.bg1DeltaX -= 0x40; this.bg1DeltaY += 0x30; }
      if (this.sea) this.bg2DeltaY += 0x10;
    }
    draw(out) {
      const scroll = this.camera.scroll, pixels = value => value >> 8;
      this.scene.layers.forEach((layer, l) => {
        if (!layer) return;
        switch (this.roles[l]) {
          case LAYER_CAMERA: layer.scrollX = pixels(scroll[0]); layer.scrollY = pixels(scroll[1]); break;
          case LAYER_CAMERA_BG1: layer.scrollX = pixels(scroll[2]); layer.scrollY = pixels(scroll[3]); break;
          case LAYER_CLOUDS: layer.scrollX = pixels(scroll[0] + this.bg1DeltaX); layer.scrollY = pixels(scroll[1] + this.bg1DeltaY); break;
          case LAYER_SEA: layer.scrollX = pixels(scroll[0]); layer.scrollY = pixels(scroll[1] + this.bg2DeltaY); break;
        }
      });
      const shown = [];
      for (const sprite of this.sprites) {
        if (!sprite.steps.length) continue;
        const step = sprite.steps[sprite.step];
        const visible = !sprite.decoration ||
          ((sprite.tileX + 2) * 0x800 > scroll[0] && (sprite.tileX - 2) * 0x800 < scroll[0] + 0xf000 &&
           (sprite.tileY + 2) * 0x800 > scroll[1] && (sprite.tileY - 2) * 0x800 < scroll[1] + 0xa000);
        if (visible) {
          const frame = sprite.frames[step.frame];
          let x = sprite.x, y = sprite.y;
          if (this.camera.world) {
            if (scroll[0] > 0xeffff && (x << 8) < scroll[0] - 0x10000) x += 0x1000;
            if (scroll[1] > 0xeffff && (y << 8) < scroll[1] - 0x10000) y += 0x1000;
          }
          shown.push({ image: frame.image, x: s16(x - pixels(scroll[0]) + frame.left), y: s16(y - pixels(scroll[1]) + frame.top), priority: sprite.priority });
        }
        if (!sprite.hold && ++sprite.age === step.duration) {
          sprite.age = 0;
          if (sprite.step + 1 < sprite.steps.length) sprite.step++;
          else if (sprite.loop) sprite.step = 0;
        }
      }
      this.scene.sprites = shown;
      composeScene(this.scene, out);
    }
  }

  const api = {
    SCREEN_WIDTH, SCREEN_HEIGHT, NO_HORIZON, Z_DURATION, DITHER_DURATION, FULL_DARK, Z_WINDOWS,
    sin256, cos256, buildRotationXyz, createCamera, cameraStart, cameraUpdate, cameraRotate, cameraGroundRows, cameraProject, Field,
    zSpans, zScale, zFrame, zConceal, darken, darkenPixel, fadeFromBlackLevel, openingFadeLevel, ditherRowBlack, ditherConceal,
    composeScene, fieldCameraFollow, FieldStartState, LAYER_CAMERA, LAYER_CAMERA_BG1, LAYER_CLOUDS, LAYER_SEA,
  };
  scope.ZoidsBattleEngine = api;
  if (typeof module === "object" && module.exports) module.exports = api;
})(globalThis);
