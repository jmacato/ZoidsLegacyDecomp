// Test oracle for the battle simulator (never shipped): the decomp's own C (src/) compiled to one WebAssembly module whose linear memory uses the GBA
// address map (EWRAM at 0x02000000, IWRAM at 0x03000000, the user's ROM copied to 0x08000000).
// usage: node extract/sim/oracle/build.mjs PLAN.json ROOT_ADDRESS...
//
// Source changes are mechanical and keep the C's meaning: every function gets the label fn_<address> (from its asm("func_...")
// label or, for unlabeled definitions, the start of its file's matched region in the plan); data externs become macros over
// their absolute addresses (asm("D_...") labels or symbols.ld); register-pinning asm("rN") bindings and top-level ARM
// directives are dropped; inline ARM templates are rewritten as the C they compute. Anything the rewriter cannot express is
// reported, not guessed.
import fs from "node:fs";
import path from "node:path";
import { execFileSync } from "node:child_process";

const ROOT = path.resolve(new URL("../../..", import.meta.url).pathname);
const OUT = path.join(ROOT, "build/sim/oracle");
const CLANG = process.env.CLANG || "/opt/homebrew/opt/llvm/bin/clang", LD = process.env.WASM_LD || "wasm-ld";
const [planPath, ...rootArgs] = process.argv.slice(2);
if (!planPath) { console.error("usage: node extract/sim/oracle/build.mjs PLAN.json ROOT_ADDRESS..."); process.exit(2); }
const plan = JSON.parse(fs.readFileSync(planPath, "utf8"));
const hex = value => "0x" + value.toString(16).toUpperCase().padStart(8, "0");
const label = address => `fn_${(address & ~1).toString(16).toUpperCase().padStart(8, "0")}`;

// ---------- lexing ----------
// Splits C text into top-level items: preprocessor lines, declarations ending in ';', and braced definitions.
function topLevel(text) {
  const items = [];
  let i = 0, start = 0, depth = 0, paren = 0, bodyStart = -1;
  const n = text.length;
  const skip = () => {
    const c = text[i], d = text[i + 1];
    if (c === "/" && d === "/") { while (i < n && text[i] !== "\n") i++; return true; }
    if (c === "/" && d === "*") { i = text.indexOf("*/", i + 2); i = i < 0 ? n : i + 2; return true; }
    if (c === '"' || c === "'") { const q = c; i++; while (i < n && text[i] !== q) { if (text[i] === "\\") i++; i++; } i++; return true; }
    return false;
  };
  while (i < n) {
    if (depth === 0 && paren === 0 && text[i] === "#" && /(^|\n)[ \t]*$/.test(text.slice(Math.max(0, i - 200), i))) {
      let end = i;
      while (end < n) { const nl = text.indexOf("\n", end); if (nl < 0) { end = n; break; } if (text[nl - 1] === "\\") { end = nl + 1; continue; } end = nl + 1; break; }
      if (i > start) items.push({ kind: "text", start, end: i });
      items.push({ kind: "pre", start: i, end }); i = end; start = end; continue;
    }
    if (skip()) continue;
    const c = text[i];
    if (c === "(") paren++;
    else if (c === ")") paren--;
    else if (c === "{") { if (depth === 0) bodyStart = i; depth++; }
    else if (c === "}") {
      depth--;
      if (depth === 0) {
        const header = text.slice(start, bodyStart);
        if (/\)\s*$/.test(header.replace(/\b__attribute__\s*\(\(.*?\)\)/g, "")) && !/=\s*$/.test(header) && !/^\s*(typedef|struct|union|enum)\b[^()]*$/.test(header)) {
          items.push({ kind: "function", start, end: i + 1, header, bodyStart }); start = i + 1;
        }
      }
    } else if (c === ";" && depth === 0 && paren === 0) { items.push({ kind: "decl", start, end: i + 1 }); start = i + 1; }
    i++;
  }
  if (start < n && text.slice(start).trim()) items.push({ kind: "text", start, end: n });
  return items;
}

const stripComments = text => text.replace(/\/\*[\s\S]*?\*\//g, " ").replace(/\/\/[^\n]*/g, " ");
// The function name and parameter count of a prototype or definition header.
function signature(header) {
  const clean = stripComments(header).replace(/\b__attribute__\s*\(\(.*?\)\)/g, "").replace(/\basm\s*\(\s*"[^"]*"\s*\)/g, "");
  let depth = 0, open = -1;
  for (let i = 0; i < clean.length; i++) {
    if (clean[i] === "(") { if (depth === 0 && open < 0) open = i; depth++; }
    else if (clean[i] === ")") depth--;
  }
  if (open < 0) return null;
  const before = clean.slice(0, open), match = /([A-Za-z_]\w*)\s*$/.exec(before);
  if (!match || /\b(typedef)\b/.test(before) || /=/.test(before)) return null;
  let close = open, d = 0;
  for (; close < clean.length; close++) { if (clean[close] === "(") d++; else if (clean[close] === ")" && --d === 0) break; }
  const params = clean.slice(open + 1, close).trim();
  let count = 0;
  if (params && params !== "void") { count = 1; let e = 0; for (const ch of params) { if (ch === "(" || ch === "[") e++; else if (ch === ")" || ch === "]") e--; else if (ch === "," && e === 0) count++; } }
  return { name: match[1], params: params === "" ? null : count, isStatic: /\bstatic\b/.test(before), returnType: before.slice(0, match.index).replace(/\b(extern|static|inline)\b/g, "").trim() };
}
const asmLabel = text => { const m = /\basm\s*\(\s*"([^"]*)"\s*\)\s*;?\s*$/.exec(stripComments(text).trim()); return m ? m[1] : null; };
const labelAddress = name => { const m = /^func_([0-9A-Fa-f]{6,8})$/.exec(name || ""); return m ? parseInt(m[1], 16) & ~1 : null; };

// ---------- index ----------
const symbols = new Map();
for (const line of fs.readFileSync(path.join(ROOT, "symbols.ld"), "utf8").split("\n")) {
  const m = /^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;/.exec(line);
  if (m) symbols.set(m[1], parseInt(m[2], 16));
}
const regionStart = new Map(plan.regions.filter(([, , file]) => file.endsWith(".c")).map(([start, , file]) => [file, start]));
const sources = [];
(function walk(dir) { for (const entry of fs.readdirSync(dir, { withFileTypes: true })) { const full = path.join(dir, entry.name); if (entry.isDirectory()) walk(full); else if (/\.(c|h)$/.test(entry.name)) sources.push(full); } })(path.join(ROOT, "src"));
const files = new Map(), nameAddress = new Map(), definedAt = new Map(), definitionAt = new Map(), declaredCount = new Map();
for (const file of sources) {
  const text = fs.readFileSync(file, "utf8"), rel = path.relative(path.join(ROOT, "src"), file), items = topLevel(text), labels = new Map(), definitions = [];
  for (const item of items) {
    const body = text.slice(item.start, item.end);
    if (item.kind === "decl") {
      const sig = signature(body), l = labelAddress(asmLabel(body));
      if (sig && l != null && !/\bextern\b[^(]*$/.test(body.split("(")[0] + "x")) labels.set(sig.name, l);
      if (sig && l != null && sig.params != null) declaredCount.set(l, Math.max(declaredCount.get(l) || 0, sig.params));
    }
    if (item.kind === "function") { const sig = signature(item.header); if (sig) definitions.push({ ...sig, item, label: labelAddress(asmLabel(item.header)) }); }
  }
  const exported = definitions.filter(d => !d.isStatic);
  for (const d of definitions) {
    let address = d.label ?? labels.get(d.name) ?? null;
    if (address == null && !d.isStatic && exported.length === 1 && regionStart.has(rel)) address = regionStart.get(rel);
    d.address = address;
    if (address != null) { definedAt.set(address, rel); definitionAt.set(address, d); if (!nameAddress.has(d.name)) nameAddress.set(d.name, address); }
  }
  files.set(rel, { file, text, items, definitions });
}

// ---------- inline asm ----------
// Parses `asm volatile("template" : outputs : inputs : clobbers)` and rewrites ARM/Thumb templates as C statements.
function splitTop(text, separator) {
  const parts = []; let depth = 0, cur = "", quote = null;
  for (let i = 0; i < text.length; i++) {
    const c = text[i];
    if (quote) { cur += c; if (c === "\\") { cur += text[++i]; continue; } if (c === quote) quote = null; continue; }
    if (c === '"' || c === "'") { quote = c; cur += c; continue; }
    if ("([{".includes(c)) depth++; else if (")]}".includes(c)) depth--;
    if (c === separator && depth === 0) { parts.push(cur); cur = ""; continue; }
    cur += c;
  }
  parts.push(cur);
  return parts;
}
function operands(list) {
  return splitTop(list || "", ",").map(s => s.trim()).filter(Boolean).map(s => { const m = /^"([^"]*)"\s*\(([\s\S]*)\)$/.exec(s); return m ? { constraint: m[1], expr: m[2].trim() } : null; });
}
function translateAsm(tmpl, outs, ins) {
  const all = [...outs, ...ins];
  for (const op of ins) { const tie = /^\d+$/.test(op.constraint) ? Number(op.constraint) : null; if (tie != null) op.tied = tie; }
  const ref = token => {
    token = token.trim();
    let m = /^%(\d+)$/.exec(token); if (m) { const op = all[Number(m[1])]; if (!op) throw Error(`operand ${token}`); return `(${op.expr})`; }
    m = /^#(-?(?:0x[0-9a-fA-F]+|\d+))$/.exec(token); if (m) return `(${m[1]})`;
    m = /^(r\d+|sp|lr|pc|ip|sl|fp|sb)$/.exec(token); if (m) throw Error(`fixed register ${token}`);
    throw Error(`operand ${token}`);
  };
  const lines = tmpl.split(/\\n|\n|;/).map(s => s.replace(/\\t/g, " ").trim()).filter(s => s && !/^\.syntax\b/.test(s));
  const out = [];
  for (const line of lines) {
    const m = /^([a-z]+)\s*(.*)$/.exec(line);
    if (!m) throw Error(`instruction ${line}`);
    let [, op, args] = m;
    op = op.replace(/s$/, "") === "mov" ? "mov" : op.replace(/^(add|sub|lsl|lsr|asr|mul|and|orr|eor|neg|mvn)s$/, "$1");
    const memory = /^(\S+?),\s*\[([^\]]*)\]$/.exec(args);
    if (memory && /^(ldr|ldrb|ldrh|ldrsh|ldrsb|str|strb|strh)$/.test(op)) {
      const [, reg, addr] = memory, parts = addr.split(",").map(s => s.trim());
      if (parts[0] === "sp") throw Error(`stack access ${line}`);
      const address = parts.length === 1 ? ref(parts[0]) : `(${ref(parts[0])} + ${ref(parts[1])})`;
      const type = { ldr: "u32", ldrb: "u8", ldrh: "u16", ldrsh: "s16", ldrsb: "s8", str: "u32", strb: "u8", strh: "u16" }[op];
      if (op.startsWith("ldr")) out.push(`${ref(reg)} = *(volatile ${type} *)(u32)${address};`);
      else out.push(`*(volatile ${type} *)(u32)${address} = (${type})${ref(reg)};`);
      continue;
    }
    const a = splitTop(args, ",").map(s => s.trim());
    const binary = { add: "+", sub: "-", lsl: "<<", and: "&", orr: "|", eor: "^", mul: "*" }[op];
    if (op === "mov" && a.length === 2) out.push(`${ref(a[0])} = ${ref(a[1])};`);
    else if (binary && a.length === 3) out.push(`${ref(a[0])} = (u32)${ref(a[1])} ${binary} (u32)${ref(a[2])};`);
    else if (binary && a.length === 2) out.push(`${ref(a[0])} = (u32)${ref(a[0])} ${binary} (u32)${ref(a[1])};`);
    else if (op === "lsr" && a.length === 3) out.push(`${ref(a[0])} = (u32)${ref(a[1])} >> ${ref(a[2])};`);
    else if (op === "asr" && a.length === 3) out.push(`${ref(a[0])} = (s32)${ref(a[1])} >> ${ref(a[2])};`);
    else if (op === "neg" && a.length === 2) out.push(`${ref(a[0])} = -(s32)${ref(a[1])};`);
    else if (op === "mvn" && a.length === 2) out.push(`${ref(a[0])} = ~(u32)${ref(a[1])};`);
    else throw Error(`instruction ${line}`);
  }
  return out.join(" ");
}
// Rewrites every asm volatile(...) statement in a function body; returns the new text and a list of failures.
function rewriteInlineAsm(text, failures, where) {
  let out = "", i = 0;
  const re = /\b(?:__asm__|asm)\s+(?:volatile|__volatile__)?\s*\(/g;
  let m;
  while ((m = re.exec(text))) {
    let j = m.index + m[0].length, depth = 1, quote = null;
    for (; j < text.length && depth; j++) { const c = text[j]; if (quote) { if (c === "\\") j++; else if (c === quote) quote = null; continue; } if (c === '"') quote = c; else if (c === "(") depth++; else if (c === ")") depth--; }
    const inner = text.slice(m.index + m[0].length, j - 1), parts = splitTop(inner, ":");
    const tmpl = (parts[0].match(/"((?:[^"\\]|\\.)*)"/g) || []).map(s => s.slice(1, -1)).join("");
    let replacement = "";
    if (tmpl.trim()) {
      try { replacement = `{ ${translateAsm(tmpl, operands(parts[1]), operands(parts[2]))} }`; }
      catch (error) { failures.push(`${where}: ${error.message} in "${tmpl.slice(0, 60)}"`); replacement = `__builtin_trap()`; }
    }
    let end = j;
    while (end < text.length && /\s/.test(text[end])) end++;
    out += text.slice(i, m.index) + (replacement || "(void)0");
    i = j;
    re.lastIndex = j;
  }
  return out + text.slice(i);
}

// ---------- calling convention ----------
// Every defined function gets abi_<address>, taking and returning 32-bit values like the GBA's registers. Declarations in
// other files become inline shims that convert arguments and the result with the caller's own declared types.
const abiName = address => `abi_${(address & ~1).toString(16).toUpperCase().padStart(8, "0")}`;
const abiCount = address => Math.max(definitionAt.get(address).params || 0, declaredCount.get(address) || 0);
const abiPrototype = address => { const count = abiCount(address); return `int abi_${abiName(address).slice(4)}(${count ? Array.from({ length: count }, () => "int").join(", ") : "void"});`; };
function paramList(header) {
  const clean = stripComments(header).replace(/\b__attribute__\s*\(\(.*?\)\)/g, "").replace(/\basm\s*\(\s*"[^"]*"\s*\)/g, "");
  const open = clean.indexOf("(", clean.search(/[A-Za-z_]\w*\s*\(/));
  let depth = 0, close = open;
  for (; close < clean.length; close++) { if (clean[close] === "(") depth++; else if (clean[close] === ")" && --depth === 0) break; }
  const inner = clean.slice(open + 1, close).trim();
  if (!inner || inner === "void") return [];
  return splitTop(inner, ",").map(s => s.trim());
}
function named(param, index) {
  const name = `p${index}`;
  if (/\(\s*\*\s*\w*\s*\)/.test(param)) return param.replace(/\(\s*\*\s*\w*\s*\)/, `(*${name})`);
  const m = /^(.*?)([A-Za-z_]\w*)(\s*(?:\[[^\]]*\])*)$/.exec(param);
  const types = /^(?:const|volatile|unsigned|signed|struct|union|enum|u8|s8|u16|s16|u32|s32|u64|s64|int|char|short|long|void|f32|float|double|M2C_UNK|M2C_UNK8|M2C_UNK16|M2C_UNK32|M2C_UNK64)$/;
  if (m && !types.test(m[2]) && /\S/.test(m[1])) return `${m[1]}${name}${m[3]}`;
  return `${param} ${name}`;
}
function shim(sig, body, address) {
  const params = paramList(body), count = abiCount(address), ret = sig.returnType || "int", isVoid = /^void$/.test(ret.trim());
  const name = sig.name, abi = abiName(address);
  if (sig.params === null) {
    return `\n${abiPrototype(address)}\n#define ${name}(...) (${isVoid ? "(void)" : `(${ret})`}${abi}(__VA_ARGS__))\n`;
  }
  const args = params.map((_, i) => `(int)p${i}`);
  while (args.length < count) args.push("0 /* argument the caller left in a register */");
  return `\n${abiPrototype(address)}\nstatic inline ${ret} ${name}(${params.length ? params.map(named).join(", ") : "void"}) { ${isVoid ? "" : `return (${ret})`}${abi}(${args.slice(0, count).join(", ")}); }\n`;
}
function wrapper(definition) {
  const count = abiCount(definition.address), ret = definition.returnType || "int", isVoid = /^void$/.test(ret.trim());
  const args = Array.from({ length: count }, (_, i) => `a${i}`), passed = args.slice(0, definition.params || 0);
  return `\nint ${abiName(definition.address)}(${count ? args.map(a => `int ${a}`).join(", ") : "void"}) { ${isVoid ? "" : "return (int)"}${definition.name}(${passed.join(", ")}); ${isVoid ? "return 0;" : ""} }\n`;
}

// ---------- transform ----------
function transform(rel, failures) {
  const { text, items } = files.get(rel);
  let out = "";
  for (const item of items) {
    let body = text.slice(item.start, item.end);
    if (item.kind === "pre") { out += body; continue; }
    if (item.kind === "text") { out += body; continue; }
    if (item.kind === "decl") {
      const trimmed = stripComments(body).trim();
      if (/^(__asm__|asm)\s*\(/.test(trimmed)) { out += "\n"; continue; }
      const sig = signature(body), lab = asmLabel(body);
      if (sig && body.includes("(") && !/^\s*(typedef)\b/.test(trimmed) && sig.params !== undefined && /\)\s*(asm\s*\(\s*"[^"]*"\s*\))?\s*;\s*$/.test(trimmed) && !/\(\s*\*/.test(trimmed.split(sig.name)[0] + "")) {
        const address = labelAddress(lab) ?? nameAddress.get(sig.name) ?? null;
        const noLabel = body.replace(/\s*\basm\s*\(\s*"[^"]*"\s*\)\s*;\s*$/, ";");
        const ownDefinition = files.get(rel).definitions.some(d => d.address === address || d.name === sig.name);
        if (address != null && !sig.isStatic && !ownDefinition && definitionAt.has(address)) { out += shim(sig, body, address); continue; }
        out += address != null && !sig.isStatic ? noLabel.replace(/;\s*$/, ` __asm__("${label(address)}");`) : noLabel;
        continue;
      }
      const data = /^\s*extern\s+((?:const\s+|volatile\s+)*(?:struct\s+\w+|union\s+\w+|\w+)(?:\s*\*+\s*|\s+)(?:const\s+|volatile\s+)*)\s*\**\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(?:asm\s*\(\s*"([^"]*)"\s*\))?\s*;\s*$/.exec(trimmed);
      if (data) {
        const stars = /extern[\s\S]*?(\*+)\s*[A-Za-z_]\w*\s*(?:\[|asm|;)/.exec(trimmed)?.[1] || "";
        const type = data[1].replace(/\*/g, "").trim() + (stars ? " " + stars : ""), name = data[2], dims = data[3], lab2 = data[4];
        const address = lab2 ? (/^D_([0-9A-Fa-f]+)$/.test(lab2) ? parseInt(lab2.slice(2), 16) : symbols.get(lab2)) : symbols.get(name);
        if (address != null) { out += dims ? `\n#define ${name} (*(${type} (*)${dims})${hex(address)})\n` : `\n#define ${name} (*(${type} *)${hex(address)})\n`; continue; }
      }
      out += body.replace(/(\bregister\b[^;]*?)\s*\basm\s*\(\s*"[a-z0-9]+"\s*\)/g, "$1");
      continue;
    }
    if (item.kind === "function") {
      const sig = signature(item.header), definition = files.get(rel).definitions.find(d => d.item === item);
      let header = item.header.replace(/\s*\basm\s*\(\s*"[^"]*"\s*\)\s*$/, "");
      let prefix = "";
      if (definition && definition.address != null && !definition.isStatic) prefix = `\n${header.trim()} __asm__("${label(definition.address)}");\n`;
      let functionBody = text.slice(item.bodyStart, item.end).replace(/(\bregister\b[^;=]*?)\s*\basm\s*\(\s*"[a-z0-9]+"\s*\)/g, "$1");
      functionBody = rewriteInlineAsm(functionBody, failures, `${rel} ${sig?.name}`);
      out += prefix + header + functionBody;
      if (definition && definition.address != null && !definition.isStatic) out += wrapper(definition);
    }
  }
  return out;
}

// ---------- build ----------
fs.mkdirSync(path.join(OUT, "src"), { recursive: true });
fs.mkdirSync(path.join(OUT, "obj"), { recursive: true });
const failures = [], transformed = new Set();
function emit(rel) {
  if (transformed.has(rel)) return;
  transformed.add(rel);
  const target = path.join(OUT, "src", rel);
  fs.mkdirSync(path.dirname(target), { recursive: true });
  fs.writeFileSync(target, transform(rel, failures));
}
for (const rel of files.keys()) if (rel.endsWith(".h")) emit(rel);
for (const name of ["m2c_prelude.h", "m2c_macros.h"]) fs.copyFileSync(path.join(ROOT, "tools", name), path.join(OUT, "src", name));

const wanted = new Set(rootArgs.map(a => parseInt(a, 16) & ~1));
const compiled = new Map(), compileErrors = [];
function compile(rel) {
  if (compiled.has(rel)) return compiled.get(rel);
  emit(rel);
  const object = path.join(OUT, "obj", rel.replace(/\//g, "__").replace(/\.c$/, ".o"));
  try {
    execFileSync(CLANG, ["--target=wasm32", "-std=gnu11", "-O2", "-flto", "-ffreestanding", "-fno-builtin", "-funsigned-char", "-fwrapv", "-fno-strict-aliasing",
      "-Wno-everything", "-I", path.join(OUT, "src"), "-I", path.join(OUT, "src", path.dirname(rel)), "-include", path.join(ROOT, "extract/sim/oracle/runtime.h"), "-c", path.join(OUT, "src", rel), "-o", object], { stdio: ["ignore", "ignore", "pipe"] });
    compiled.set(rel, object);
  } catch (error) { compileErrors.push(`${rel}: ${String(error.stderr).split("\n").filter(l => /error/.test(l)).slice(0, 3).join(" | ")}`); compiled.set(rel, null); }
  return compiled.get(rel);
}
const runtime = path.join(OUT, "obj", "runtime.o");
execFileSync(CLANG, ["--target=wasm32", "-std=gnu11", "-O2", "-flto", "-ffreestanding", "-fno-builtin", "-funsigned-char", "-fwrapv", "-Wno-everything", "-c", path.join(ROOT, "extract/sim/oracle/runtime.c"), "-o", runtime]);
const exclude = new Set([...(process.env.SIM_EXCLUDE || "").split(",").filter(Boolean), ...[...files.keys()].filter(rel => /^runtime\/bios_/.test(rel))]);
let undefinedNames = [];
for (let round = 0; round < 40; round++) {
  for (const address of wanted) { const rel = definedAt.get(address); if (rel && !exclude.has(rel)) compile(rel); }
  const objects = [runtime, ...[...compiled.values()].filter(Boolean)];
  let output = "";
  try { output = execFileSync(LD, ["--no-entry", "--export-all", "--allow-undefined", "--import-memory", `--global-base=${0x09000000}`, "-z", "stack-size=1048576", "--max-memory=" + 0x0a000000, "--initial-memory=" + 0x0a000000, "-o", path.join(OUT, "oracle.wasm"), ...objects], { encoding: "utf8", stdio: ["ignore", "pipe", "pipe"] }); }
  catch (error) { output = String(error.stderr || error.stdout); if (!fs.existsSync(path.join(OUT, "oracle.wasm"))) { console.error(output.split("\n").slice(0, 30).join("\n")); process.exit(1); } }
  const module = new WebAssembly.Module(fs.readFileSync(path.join(OUT, "oracle.wasm")));
  undefinedNames = WebAssembly.Module.imports(module).filter(i => i.kind === "function").map(i => i.name);
  let added = 0;
  for (const name of undefinedNames) {
    const m = /^(?:fn|abi)_([0-9A-F]{8})$/.exec(name);
    if (!m) continue;
    const address = parseInt(m[1], 16);
    if (!wanted.has(address) && definedAt.has(address) && !exclude.has(definedAt.get(address))) { wanted.add(address); added++; }
  }
  if (!added) break;
}
const report = { files: [...compiled].filter(([, o]) => o).map(([rel]) => rel).sort(), compileErrors, asmFailures: failures.filter(f => [...compiled.keys()].some(rel => f.startsWith(rel + " "))), imports: undefinedNames.sort() };
fs.writeFileSync(path.join(OUT, "report.json"), JSON.stringify(report, null, 1));
console.log(`compiled ${report.files.length} files; compile errors ${compileErrors.length}; asm rewrites failed ${report.asmFailures.length}; imports ${report.imports.length}`);
