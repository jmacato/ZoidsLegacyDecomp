// Differential test of the engine's Z transition spans against the decomp's own BuildScaledScanlineWindows (the oracle):
// every progress of the Z conceal and random scale pairs must give the same window spans on every row.
// usage: node extract/sim/test_transition.mjs ROM [CASES]
import fs from "node:fs";
import path from "node:path";
import { createRequire } from "node:module";

const ROOT = path.resolve(new URL("../..", import.meta.url).pathname);
const [romPath, casesArg] = process.argv.slice(2);
const CASES = Number(casesArg || 3000);
const rom = fs.readFileSync(romPath);
let seed = 0x2468ace;
const random = () => { seed = (Math.imul(seed, 1103515245) + 12345) >>> 0; return seed >>> 8; };
const Z_OUTLINE = 0x7ed854, ROWS = 160;

const require = createRequire(import.meta.url), J = require(path.join(ROOT, "extract/sim/web/battle-engine.js"));
const outlines = [0, 1].map(w => Array.from({ length: ROWS }, (_, y) => [rom.readInt16LE(Z_OUTLINE + (w * ROWS + y) * 4), rom.readInt16LE(Z_OUTLINE + (w * ROWS + y) * 4 + 2)]));

const memory = new WebAssembly.Memory({ initial: 0x0a000000 >>> 16, maximum: 0x0a000000 >>> 16 });
const oracleBytes = fs.readFileSync(path.join(ROOT, "build/sim/oracle/oracle.wasm")), env = { memory };
for (const entry of WebAssembly.Module.imports(new WebAssembly.Module(oracleBytes))) if (entry.kind === "function") env[entry.name] = () => { throw Error(`oracle reached ${entry.name}, which it does not include`); };
const O = (await WebAssembly.instantiate(oracleBytes, { env })).instance.exports, om = new DataView(memory.buffer);
new Uint8Array(memory.buffer).set(rom, 0x08000000);
O.abi_080954D8(0x08000000 + Z_OUTLINE, 0, 0, 0x08000000 + Z_OUTLINE + ROWS * 4, 0, 0, 0, 0x3f, 8);

let failures = 0, checked = 0;
const fail = message => { if (failures++ < 12) console.log("FAIL " + message); };
function compare(scales) {
  [0, 1].forEach(w => { om.setUint16(0x03005eea + w * 2, scales[w * 2], true); om.setUint16(0x03005eee + w * 2, scales[w * 2 + 1], true); });
  O.abi_0809570C();
  const bank = 1 ^ om.getUint8(0x03005f12);
  for (let w = 0; w < 2; w++) {
    const spans = J.zSpans(outlines[w], scales[w * 2], scales[w * 2 + 1]);
    for (let y = 0; y < ROWS; y++) {
      const oracle = om.getUint16(0x02000000 + bank * 0x500 + y * 8 + w * 2, true), engine = spans[y][0] << 8 | spans[y][1];
      if (oracle !== engine) { fail(`window ${w} scales ${scales.join(",")} row ${y}: engine ${engine.toString(16)}, oracle ${oracle.toString(16)}`); return; }
    }
  }
  checked++;
}
for (let progress = 0; progress < 256; progress++) { const s = (progress * progress) & 0xffff; compare([s, s, s, s]); }
for (let n = 0; n < CASES; n++) compare([random() & 0xffff, random() & 0xffff, random() & 0x7ff, (random() & 0x3ff) + 1]);
// Pixels: the engine's Z over a scene against the reference display with the oracle's spans fed to the window registers
// the way the game's VBlank and HBlank handlers do (row 0 at VBlank, then row v during HBlank of line v for line v + 1).
const Display = require(path.join(ROOT, "extract/sim/reference/display.js"));
function zOver(scene, backdrop) {
  const pixels = new Uint32Array(scene.buffer, scene.byteOffset, 240 * 160), out = new Uint32Array(240 * 160);
  return { frame: progress => { J.zFrame(pixels, backdrop, outlines, progress, out); return new Uint8Array(out.buffer); } };
}
const expand = v => { const r = v & 31, g = v >> 5 & 31, b = v >> 10 & 31; return [(r << 3) | (r >> 2), (g << 3) | (g >> 2), (b << 3) | (b >> 2)]; };
let pixelFrames = 0;
for (let n = 0; n < 4; n++) {
  const state = { vram: new Uint8Array(0x18000).map(() => random() & 0xff), palette: new Uint8Array(1024).map(() => random() & 0xff), oam: new Uint8Array(1024), registers: new Uint8Array(0x60) };
  for (let i = 0; i < 128; i++) state.oam[i * 8 + 1] = 2;
  const io = new DataView(state.registers.buffer);
  io.setUint16(0, 0x0100, true); io.setUint16(8, (random() & 3) << 2 | (random() & 31) << 8, true);
  const plain = Display.render(state), scene = new Uint8Array(240 * 160 * 4);
  plain.forEach((v, i) => { scene.set([...expand(v), 255], i * 4); });
  const backdropColor = new DataView(state.palette.buffer).getUint16(0, true) & 0x7fff, [r, g, b] = expand(backdropColor);
  const z = zOver(scene, (r | g << 8 | b << 16 | 0xff000000) >>> 0);
  for (let progress = 0; progress <= 36; progress++) {
    const s = (progress * progress) & 0xffff;
    [0, 1].forEach(w => { om.setUint16(0x03005eea + w * 2, s, true); om.setUint16(0x03005eee + w * 2, s, true); });
    O.abi_0809570C();
    const bank = 1 ^ om.getUint8(0x03005f12), expected = new Uint16Array(240 * 160);
    io.setUint16(0, 0x6100, true); io.setUint16(0x44, 0xa0, true); io.setUint16(0x46, 0xa0, true); io.setUint16(0x48, 0, true); io.setUint16(0x4a, 0x3f, true);
    io.setUint16(0x50, progress === 36 ? 0xff : 0, true); io.setUint16(0x54, progress === 36 ? 16 : 0, true);
    for (let line = 0; line < 160; line++) {
      const row = line ? line - 1 : 0;
      io.setUint16(0x40, om.getUint16(0x02000000 + bank * 0x500 + row * 8, true), true); io.setUint16(0x42, om.getUint16(0x02000000 + bank * 0x500 + row * 8 + 2, true), true);
      expected.set(Display.render(state, { firstLine: line, lastLine: line + 1 }).subarray(line * 240, line * 240 + 240), line * 240);
    }
    const frame = z.frame(progress);
    const bad = expected.findIndex((v, i) => expand(v).some((c, k) => c !== frame[i * 4 + k]));
    if (bad >= 0) fail(`Z pixels scene ${n} progress ${progress}: pixel ${bad % 240},${bad / 240 | 0} engine ${frame.slice(bad * 4, bad * 4 + 3)} reference ${expand(expected[bad])}`);
    else pixelFrames++;
    io.setUint16(0, 0x0100, true);
  }
}
console.log(`${pixelFrames} Z frames pixel-identical to the reference display`);
// The dither conceal: the oracle's BuildScreenTransitionFrame row masks for every progress against the engine's rule.
let ditherFrames = 0;
for (let progress = 0; progress < 28; progress++) {
  for (const bank of [0, 1]) {
    om.setUint8(0x03005f70, 18); om.setUint8(0x03005f71, 28); om.setUint8(0x03005f72, progress); om.setUint8(0x03005f7a, bank);
    O.fn_08096774(0);
    const written = 0x02002740 + (bank ^ 1) * 160, other = 0x02002740 + bank * 160;
    const target = [written, other].find(at => Array.from({ length: 160 }, (_, r) => om.getUint8(at + r)).some((v, r) => v !== (J.ditherRowBlack(progress, r) ? 0 : 1)) === false);
    if (target === undefined) { fail(`dither progress ${progress} bank ${bank}: masks ${Array.from({ length: 160 }, (_, r) => om.getUint8(written + r)).join("")} / ${Array.from({ length: 160 }, (_, r) => om.getUint8(other + r)).join("")}`); break; }
    ditherFrames++;
  }
}
console.log(`${ditherFrames} dither row masks identical to BuildScreenTransitionFrame`);
console.log(`${checked} scale sets compared over 2 windows x ${ROWS} rows: ${failures ? `${failures} differ` : "identical"}`);
process.exit(failures ? 1 : 0);
