// Pixel test of the battle field engine: every frame must equal, pixel for pixel, the GBA-style reference renderer
// (tiles, palettes, OAM, per-scanline affine; extract/sim/reference) for the same terrain, units and camera.
// usage: node extract/sim/test_pixels.mjs ROM PLAN [CASES]
import fs from "node:fs";
import path from "node:path";
import { createRequire } from "node:module";

const ROOT = path.resolve(new URL("../..", import.meta.url).pathname), require = createRequire(import.meta.url);
const [romPath, planPath, casesArg] = process.argv.slice(2);
const CASES = Number(casesArg || 60);
const D = require(path.join(ROOT, "extract/page/decode.js"));
require(path.join(ROOT, "extract/page/objects.js"));
const Display = require(path.join(ROOT, "extract/sim/reference/display.js"));
const Reference = require(path.join(ROOT, "extract/sim/reference/battlefield.js"));
const { BattleField, terrainAvailable } = require(path.join(ROOT, "extract/sim/web/battle-field.js"));
const plan = JSON.parse(fs.readFileSync(planPath, "utf8")), rom = new Uint8Array(fs.readFileSync(romPath));
const archive = new globalThis.ZoidsObjects.Archive(rom, plan, D.lz77, D.text), terrains = Array.from({ length: 24 }, (_, t) => t).filter(t => terrainAvailable(archive, t));
let seed = 0x5eed;
const random = () => { seed = (Math.imul(seed, 1103515245) + 12345) >>> 0; return seed >>> 8; };
const pick = list => list[random() % list.length];
const toRgb = colors => { const out = new Uint8Array(colors.length * 3); colors.forEach((v, i) => { const r = v & 31, g = v >> 5 & 31, b = v >> 10 & 31; out.set([(r << 3) | (r >> 2), (g << 3) | (g >> 2), (b << 3) | (b >> 2)], i * 3); }); return out; };
const CAMERAS = [["overview", [0, 0]], ["player-near", [2, 0]], ["enemy-near", [2, 1]], ["player-wide", [3, 0]], ["enemy-wide", [3, 1]], ["player-far", [4, 0]], ["enemy-far", [4, 1]]];

let frames = 0, failures = 0, overBudget = 0;
const compare = (label, engine, reference) => {
  frames++;
  for (let i = 0; i < 240 * 160; i++) if (engine[i * 4] !== reference[i * 3] || engine[i * 4 + 1] !== reference[i * 3 + 1] || engine[i * 4 + 2] !== reference[i * 3 + 2]) {
    if (failures++ < 10) console.log(`FAIL ${label}: pixel ${i % 240},${i / 240 | 0} engine ${engine.slice(i * 4, i * 4 + 3)} reference ${reference.slice(i * 3, i * 3 + 3)}`);
    return false;
  }
  return true;
};
for (let n = 0; n < CASES; n++) {
  const terrain = terrains[n % terrains.length], group = 1 + random() % 20, encounters = Reference.encounterGroup(archive, group).filter(e => e.candidate);
  const enemies = encounters.length ? pick(encounters).units : [];
  const players = Array.from({ length: 6 }, () => random() % 3 ? { zoid: 1 + random() % 151, palette: random() % 8 } : null);
  const sides = [players, enemies];
  const [name, [mode, side]] = n % 3 === 0 ? ["intro", [1, 0]] : pick(CAMERAS);
  const engine = new BattleField(archive, { terrain, sides }), reference = new Reference.Field(archive, { terrain, sides });
  engine.camera(n % 3 === 0 ? "intro" : "overview", true);
  reference.camera.start(n % 3 === 0 ? 1 : 0, 0, 0, 1);
  for (let update = 0; update < 3; update++) { engine.step(); reference.frame(); }
  if (n % 3) { engine.camera(name, false); reference.camera.start(mode, side, 0, 0); }
  for (let update = 0; update < 200; update++) {
    const settled = engine.step(), frame = reference.frame();
    let referencePixels;
    try { referencePixels = toRgb(Display.render(frame)); } catch (error) { if (!/cycle-budget/.test(error.message)) throw error; overBudget++; if (settled && reference.camera.done) break; continue; }
    if (!compare(`terrain ${terrain} group ${group} camera ${name} update ${update}`, engine.frame(), referencePixels)) break;
    if (settled && reference.camera.done) break;
  }
}
// The opening fade from black: the intro camera's first update shares the fade's first frame, brightness 16 - 2 * (step - 1).
let fades = 0;
for (let n = 0; n < Math.max(4, CASES >> 3); n++) {
  const terrain = pick(terrains), encounters = Reference.encounterGroup(archive, 1 + random() % 20).filter(e => e.candidate);
  const sides = [Array.from({ length: 6 }, () => random() % 2 ? { zoid: 1 + random() % 151, palette: random() % 8 } : null), encounters.length ? pick(encounters).units : []];
  const engine = new BattleField(archive, { terrain, sides }), reference = new Reference.Field(archive, { terrain, sides });
  engine.camera("intro", true); reference.camera.start(1, 0, 0, 1);
  for (let step = 1; step <= 11; step++) {
    engine.step();
    const frame = reference.frame(), registers = frame.registers.slice(), io = new DataView(registers.buffer), progress = step - 1;
    io.setUint16(0x50, 0xff, true); io.setUint16(0x54, progress > 8 ? 0 : 16 - (progress * 16 / 8 | 0), true);
    let referencePixels;
    try { referencePixels = toRgb(Display.render({ ...frame, registers })); } catch (error) { if (!/cycle-budget/.test(error.message)) throw error; overBudget++; continue; }
    if (!compare(`fade terrain ${terrain} step ${step}`, engine.fadedFrame(step), referencePixels)) break;
    fades++;
  }
}
// A running view handed to a new field (the page does this when the encounter changes mid-battle) must continue exactly.
let handovers = 0;
for (const [name, at] of [["intro", 20], ["intro", 70], ["player-near", 5], ["enemy-far", 0], ["overview", 30]]) {
  const sides = [[{ zoid: 23, palette: 0 }], [null, { zoid: 47, palette: 0 }]], a = new BattleField(archive, { terrain: 1, sides });
  a.camera("overview", true); a.step(); a.camera(name); for (let i = 0; i < at; i++) a.step();
  const b = new BattleField(archive, { terrain: 1, sides });
  b.resume(name, a.pose());
  for (let i = 0; i < 100; i++) {
    a.step(); b.step();
    const fa = a.frame(), fb = b.frame();
    if (a.pose().join() !== b.pose().join() || fa.some((v, k) => v !== fb[k])) { failures++; console.log(`FAIL hand-over ${name} after ${at}: update ${i} differs`); break; }
  }
  handovers++;
}
console.log(`terrains ${terrains.join(",")}; ${fades} fade frames; ${handovers} camera hand-overs checked; ${CASES} fields, ${frames} frames compared: ${failures ? failures + " differ" : "pixel-identical"}; ${overBudget} frames over the OBJ line budget not compared`);
process.exit(failures ? 1 : 0);
