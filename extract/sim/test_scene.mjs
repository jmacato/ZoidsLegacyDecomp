// Tests of the field scene a battle starts from: the engine's camera follow against the decomp's own UpdateFieldCameraFollow
// (the oracle), and the engine's compositor against the reference display for random backgrounds, sprites, priorities and
// alpha blends.
// usage: node extract/sim/test_scene.mjs ROM [CASES]
import fs from "node:fs";
import path from "node:path";
import { createRequire } from "node:module";

const ROOT = path.resolve(new URL("../..", import.meta.url).pathname), require = createRequire(import.meta.url);
const [romPath, casesArg] = process.argv.slice(2);
const CASES = Number(casesArg || 2000);
const rom = fs.readFileSync(romPath);
let seed = 0x13579b;
const random = () => { seed = (Math.imul(seed, 1103515245) + 12345) >>> 0; return seed >>> 8; };
const between = (low, high) => low + (random() % (high - low + 1));
let failures = 0;
const fail = message => { if (failures++ < 12) console.log("FAIL " + message); };

const J = require(path.join(ROOT, "extract/sim/web/battle-engine.js"));
const memory = new WebAssembly.Memory({ initial: 0x0a000000 >>> 16, maximum: 0x0a000000 >>> 16 });
const oracleBytes = fs.readFileSync(path.join(ROOT, "build/sim/oracle/oracle.wasm")), env = { memory };
for (const entry of WebAssembly.Module.imports(new WebAssembly.Module(oracleBytes))) if (entry.kind === "function") env[entry.name] = () => { throw Error(`oracle reached ${entry.name}`); };
const O = (await WebAssembly.instantiate(oracleBytes, { env })).instance.exports, om = new DataView(memory.buffer);
new Uint8Array(memory.buffer).set(rom, 0x08000000);

// 1. Camera follow.
const ACTOR = 0x02001000, CAMERA = 0x03000054, DIMENSIONS = 0x020324a4, TILEMAPS = 0x02032e88, MAP = 0x0202ecf4;
let follows = 0;
for (let n = 0; n < CASES; n++) {
  const world = n % 3 === 0, width = world ? 512 : between(30, 300), height = world ? 512 : between(20, 300), bg0 = random() % 8 !== 0, bg1 = random() % 2 === 0;
  const camera = [0, 1, 2, 3].map(() => between(0, 0xfffff));
  if (!world) { camera[0] = between(0, (width - 30) << 11); camera[1] = between(0, (height - 20) << 11); }
  om.setUint16(MAP, world ? 0 : between(1, 200), true); om.setUint16(DIMENSIONS, width, true); om.setUint16(DIMENSIONS + 2, height, true);
  om.setUint32(TILEMAPS, bg0 ? 0x02032e98 : 0, true); om.setUint32(TILEMAPS + 4, bg1 ? 0x02034e98 : 0, true);
  const view = { scroll: camera.slice(), world, widthTiles: width, heightTiles: height, bg0Tilemap: bg0, bg1Tilemap: bg1 };
  camera.forEach((value, i) => om.setInt32(CAMERA + i * 4, value, true));
  for (let step = 0; step < 6; step++) {
    const x = world ? between(0, 0xfffff) : between(-0x2000, (width << 11) + 0x2000), y = world ? between(0, 0xfffff) : between(-0x2000, (height << 11) + 0x2000);
    om.setUint16(ACTOR + 6, random() % 6 ? 0 : 6, true); om.setInt32(ACTOR + 8, x, true); om.setInt32(ACTOR + 12, y, true);
    O.abi_080ABE70(ACTOR);
    J.fieldCameraFollow(view, x, y);
    const oracle = [0, 1, 2, 3].map(i => om.getInt32(CAMERA + i * 4, true)), engine = view.scroll;
    if (oracle.join() !== engine.join()) { fail(`camera follow case ${n} step ${step}: engine ${engine}, oracle ${oracle}`); break; }
    follows++;
  }
}

// 2. Compositor.
const Display = require(path.join(ROOT, "extract/sim/reference/display.js"));
const SENTINEL = 0x7fff, rgba = v => { const r = v & 31, g = v >> 5 & 31, b = v >> 10 & 31; return ((r << 3) | (r >> 2)) | (((g << 3) | (g >> 2)) << 8) | (((b << 3) | (b >> 2)) << 16) | 0xff000000; };
let frames = 0;
for (let n = 0; n < Math.max(20, CASES / 40 | 0); n++) {
  const state = { vram: new Uint8Array(0x18000).map(() => random() & 0xff), palette: new Uint8Array(1024).map(() => random() & 0xff), oam: new Uint8Array(1024), registers: new Uint8Array(0x60) };
  const colors = new DataView(state.palette.buffer), io = new DataView(state.registers.buffer);
  for (let i = 0; i < 512; i++) if ((colors.getUint16(i * 2, true) & 0x7fff) === SENTINEL) colors.setUint16(i * 2, 0x7ffe, true);
  for (let i = 0; i < 128; i++) state.oam[i * 8 + 1] = 2;
  const spritePriority = random() & 3, sprites = random() % 6;
  for (let i = 0; i < sprites; i++) {
    const at = i * 8;
    new DataView(state.oam.buffer).setUint16(at, between(0, 150) | (random() % 3) << 14, true);
    new DataView(state.oam.buffer).setUint16(at + 2, between(0, 230) | (random() & 3) << 14, true);
    new DataView(state.oam.buffer).setUint16(at + 4, (random() & 0x3ff) | spritePriority << 10 | (random() & 15) << 12, true);
  }
  const enabled = [0, 1, 2, 3].filter(() => random() % 4 !== 0);
  let control = 0x1040; enabled.forEach(l => { control |= 0x100 << l; });
  io.setUint16(0, control, true);
  for (let l = 0; l < 4; l++) { io.setUint16(8 + l * 2, (random() & 3) | (random() & 3) << 2 | (28 + l) << 8, true); io.setUint16(0x10 + l * 4, random() & 0x1ff, true); io.setUint16(0x12 + l * 4, random() & 0x1ff, true); }
  const blend = random() % 4 !== 0, first = random() & 63, second = random() & 63, eva = random() % 18, evb = random() % 18;
  io.setUint16(0x50, blend ? first | 0x40 | second << 8 : 0, true); io.setUint16(0x52, eva | evb << 8, true);
  const expected = Display.render(state);
  const alone = (dispcnt, oam) => { const copy = { ...state, oam: oam || state.oam, registers: state.registers.slice() }, cio = new DataView(copy.registers.buffer); cio.setUint16(0, dispcnt, true); cio.setUint16(0x50, 0, true); const saved = colors.getUint16(0, true); colors.setUint16(0, SENTINEL, true); const out = Display.render(copy); colors.setUint16(0, saved, true); return out; };
  const image = pixels => ({ width: 240, height: 160, pixels: Uint32Array.from(pixels, v => v === SENTINEL ? 0 : rgba(v) >>> 0) });
  const scene = { layers: [], sprites: [], blend: blend ? { first, second, eva, evb } : null, backdrop: rgba(colors.getUint16(0, true) & 0x7fff) >>> 0 };
  for (let l = 0; l < 4; l++) {
    const on = enabled.includes(l);
    scene.layers.push({ enabled: on, priority: io.getUint16(8 + l * 2, true) & 3, image: on ? image(alone(0x0040 | 0x100 << l)) : image([]), scrollX: 0, scrollY: 0, left: 0, top: 0, wrapWidth: 0, wrapHeight: 0 });
  }
  for (let i = 0; i < sprites; i++) {
    const oam = new Uint8Array(1024); for (let k = 0; k < 128; k++) oam[k * 8 + 1] = 2; oam.set(state.oam.subarray(i * 8, i * 8 + 8), 0);
    scene.sprites.push({ image: image(alone(0x1040 | 0x1000, oam)), x: 0, y: 0, priority: spritePriority });
  }
  const frame = new Uint32Array(240 * 160);
  J.composeScene(scene, frame);
  const bad = expected.findIndex((v, i) => (rgba(v) >>> 0) !== frame[i]);
  if (bad >= 0) fail(`compose case ${n}: pixel ${bad % 240},${bad / 240 | 0} engine ${frame[bad].toString(16)} reference ${(rgba(expected[bad]) >>> 0).toString(16)} (layers ${enabled}, sprites ${sprites} at priority ${spritePriority}, blend ${blend})`);
  else frames++;
}
console.log(`camera follow: ${follows} updates identical to UpdateFieldCameraFollow; compositor: ${frames} frames pixel-identical to the reference display${failures ? `; ${failures} failures` : ""}`);
process.exit(failures ? 1 : 0);
