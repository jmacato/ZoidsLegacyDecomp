// Differential test of the battle field engine against the decomp's own C (the oracle): camera ground rows, horizon,
// rotation matrix, point projection and camera transitions must be identical for random inputs.
// usage: node extract/sim/test_field.mjs ROM [CASES]
import fs from "node:fs";
import path from "node:path";
import { createRequire } from "node:module";

const ROOT = path.resolve(new URL("../..", import.meta.url).pathname), require = createRequire(import.meta.url);
const [romPath, casesArg] = process.argv.slice(2);
const CASES = Number(casesArg || 2000);
const rom = fs.readFileSync(romPath);
let seed = 0x1234567;
const random = () => { seed = (Math.imul(seed, 1103515245) + 12345) >>> 0; return seed >>> 8; };
const between = (low, high) => low + (random() % (high - low + 1));

const J = require(path.join(ROOT, "extract/sim/web/battle-engine.js"));
const sine = Array.from({ length: 65 }, (_, i) => rom.readUInt16LE(0xed184 + i * 2));
const positions = Array.from({ length: 12 }, (_, i) => [0, 4, 8].map(offset => rom.readInt32LE(0x7a2790 + i * 12 + offset)));

const memory = new WebAssembly.Memory({ initial: 0x0a000000 >>> 16, maximum: 0x0a000000 >>> 16 });
const oracleBytes = fs.readFileSync(path.join(ROOT, "build/sim/oracle/oracle.wasm")), env = { memory };
for (const entry of WebAssembly.Module.imports(new WebAssembly.Module(oracleBytes))) if (entry.kind === "function") env[entry.name] = () => { throw Error(`oracle reached ${entry.name}, which it does not include`); };
const oracleModule = await WebAssembly.instantiate(oracleBytes, { env });
const O = oracleModule.instance.exports, om = new DataView(memory.buffer);
new Uint8Array(memory.buffer).set(rom, 0x08000000);
const CAMERA = 0x030033c4, BUFFERS = 0x0202f094;
om.setUint32(0x03003428, BUFFERS, true);
om.setInt32(CAMERA + 0x14, 0x78, true); om.setInt32(CAMERA + 0x18, 0x78, true); om.setInt32(CAMERA + 0x1c, 0x80, true); om.setInt32(CAMERA + 0x60, 0x20000, true);
const setOraclePose = ([x, z, depth, pitch, yaw, roll]) => {
  om.setInt32(CAMERA, x, true); om.setInt32(CAMERA + 4, z, true); om.setInt32(CAMERA + 8, depth, true);
  om.setUint16(CAMERA + 0xc, pitch, true); om.setUint16(CAMERA + 0xe, yaw, true); om.setUint16(CAMERA + 0x10, roll, true);
};
const oraclePose = () => [om.getInt32(CAMERA, true), om.getInt32(CAMERA + 4, true), om.getInt32(CAMERA + 8, true), om.getUint16(CAMERA + 0xc, true), om.getUint16(CAMERA + 0xe, true), om.getUint16(CAMERA + 0x10, true)];
const forceOracleRefresh = () => { om.setUint8(0x03005f70, 1); om.setInt32(CAMERA + 0x2c, ~om.getInt32(CAMERA + 0xc, true), true); om.setInt16(CAMERA + 0x30, ~om.getInt16(CAMERA + 0x10, true), true); };

let failures = 0;
const fail = message => { if (failures++ < 12) console.log("FAIL " + message); };
const rowsOf = (view, base) => Array.from({ length: 160 }, (_, line) => { const at = base + line * 16; return [view.getInt16(at, true), view.getInt16(at + 2, true), view.getInt16(at + 4, true), view.getInt16(at + 6, true), view.getInt32(at + 8, true), view.getInt32(at + 12, true)].join(","); });

// 1. Ground rows, horizon, matrix and projection for random poses.
for (let n = 0; n < CASES; n++) {
  const pose = [between(-0x30000, 0x30000), between(-0x30000, 0x30000), between(0x400, 0x18000), between(1, 0x3f), between(0, 0xffff), 0];
  if (n % 3 === 0) pose[4] = between(0, 255); else if (n % 3 === 1) pose[4] = 0;
  setOraclePose(pose); forceOracleRefresh();
  const oracleHorizon = O.abi_08093B7C() & 0xff;
  O.abi_080BB764();
  const camera = J.createCamera();
  camera.pose = { x: pose[0], z: pose[1], depth: pose[2], pitch: pose[3], yaw: pose[4], roll: 0 };
  J.cameraRotate(camera, sine);
  const rows = Array.from({ length: 160 }, () => ({})), engineHorizon = J.cameraGroundRows(camera, sine, rows);
  const oracleRows = rowsOf(om, BUFFERS + (1 ^ om.getUint8(0x0300342c)) * 0xa00), engineRows = rows.map(r => [r.uStep, r.uRowStep, r.vStep, r.vRowStep, r.uOrigin, r.vOrigin].join(","));
  if (oracleHorizon !== engineHorizon) fail(`pose ${pose}: horizon ${engineHorizon}, oracle ${oracleHorizon}`);
  const row = oracleRows.findIndex((value, i) => value !== engineRows[i]);
  if (row >= 0) fail(`pose ${pose}: row ${row} ${engineRows[row]}, oracle ${oracleRows[row]}`);
  const oracleMatrix = Array.from({ length: 9 }, (_, i) => om.getInt16(CAMERA + 0x40 + i * 2, true)).join(), engineMatrix = camera.matrix.join();
  if (oracleMatrix !== engineMatrix) fail(`pose ${pose}: matrix ${engineMatrix}, oracle ${oracleMatrix}`);
  for (let k = 0; k < 4; k++) {
    const point = [between(-0x20000, 0x20000), between(-0x4000, 0x4000), between(-0x20000, 0x20000)];
    point.forEach((value, i) => om.setInt32(0x02000000 + i * 4, value, true));
    om.setUint8(0x02000010, 0);
    const scale = O.abi_08093E30(0x02000000, 0x02000020, 0x02000010), visible = om.getUint8(0x02000010);
    const projected = J.cameraProject(camera, point), engine = [projected.visible ? 1 : 0, projected.x, projected.y, projected.scale];
    const oracle = visible ? [1, om.getInt16(0x02000020, true), om.getInt16(0x02000022, true), (scale << 16) >> 16] : [0];
    if (engine[0] !== oracle[0] || (oracle[0] && engine.join() !== oracle.join())) fail(`pose ${pose} point ${point}: ${engine}, oracle ${oracle}`);
  }
}

// 2. Camera transitions: every mode from random start poses, stepped until settled.
let steps = 0;
for (let n = 0; n < CASES / 10; n++) {
  const mode = [0, 1, 2, 3, 4, 5, 6, 8, 9][n % 9], side = between(0, 1), unit = between(0, 5), immediate = n % 4 === 0 ? 1 : 0;
  const start = [between(-0x20000, 0x20000), between(-0x8000, 0x28000), between(0x2000, 0x10000), between(0, 0x40), between(0, 0x20) - 0x10 & 0xffff, between(0, 8)];
  setOraclePose(start); om.setUint8(0x02032f62, 1);
  const camera = J.createCamera();
  camera.pose = { x: start[0], z: start[1], depth: start[2], pitch: start[3], yaw: start[4], roll: start[5] };
  O.abi_080BB224(mode, side, unit, immediate);
  J.cameraStart(camera, positions, mode, side, unit, immediate);
  for (let update = 0; update < 400; update++) {
    O.abi_080BB474(); J.cameraUpdate(camera); steps++;
    const p = camera.pose, oracle = oraclePose().join(), engine = [p.x, p.z, p.depth, p.pitch, p.yaw, p.roll].join();
    if (oracle !== engine) { fail(`mode ${mode} side ${side} unit ${unit} immediate ${immediate} from ${start}: update ${update} pose ${engine}, oracle ${oracle}`); break; }
    if (om.getUint8(0x02032f62)) break;
  }
}
console.log(`${CASES} poses (160 rows, horizon, matrix, 4 projections each), ${Math.floor(CASES / 10)} camera transitions (${steps} updates): ${failures ? failures + " differences" : "identical"}`);
process.exit(failures ? 1 : 0);
