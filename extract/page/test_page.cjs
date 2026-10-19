// Smoke test of the built page in Node with a minimal DOM: loads the embedded plan, verifies the ROM, and drives
// every route (overview, kinds, item pages of each view type, ROM view, unread classes, gallery). Fails on any error.
// usage: node extract/page/test_page.cjs PAGE.html ROM
const fs = require("fs");

class Element {
  constructor(tag) { this.tagName = tag.toUpperCase(); this.children = []; this.attributes = {}; this.listeners = {}; this.style = { setProperty() {} }; this._text = ""; this.className = ""; }
  set textContent(value) { this.children = []; this._text = String(value); }
  get textContent() { return this._text + this.children.map(child => child.textContent ?? "").join(""); }
  append(...nodes) { for (const child of nodes) if (child instanceof Element) child.parent = this; this.children.push(...nodes); }
  replaceChildren(...nodes) { this.children = nodes; this._text = ""; }
  setAttribute(key, value) { this.attributes[key] = value; }
  get value() { if (this._value !== undefined) return this._value; if (this.tagName === "SELECT") { const options = this.children.filter(child => child.tagName === "OPTION"); const chosen = options.find(option => "selected" in option.attributes) || options[0]; return chosen ? String(chosen.attributes.value) : ""; } return this.attributes.value ?? ""; }
  set value(value) { this._value = String(value); }
  addEventListener(type, fn) { (this.listeners[type] ||= []).push(fn); }
  get classList() { const self = this; return { add(c) { self.className += " " + c; }, remove() {}, toggle() {} }; }
  getContext() { return { putImageData() {}, getImageData(x, y, width, height) { return { width, height, data: new Uint8ClampedArray(width * height * 4) }; }, drawImage() {}, clearRect() {}, fillRect() {}, strokeRect() {}, fillText() {}, createPattern() { return null; } }; }
  get dataset() { return this._dataset ||= {}; }
  toDataURL() { return "data:image/png;base64,"; }
  getBoundingClientRect() { return { left: 0, top: 100000, width: 1024, height: 64 }; }
  after(...nodes) { this.parent?.children.push(...nodes); }
  click() {}
  toBlob(fn) { fn(new Blob([])); }
}
class TextNode { constructor(text) { this.textContent = text; } }

function count(element, predicate) { let n = predicate(element) ? 1 : 0; for (const child of element.children || []) if (child instanceof Element) n += count(child, predicate); return n; }

async function main() {
  const [pagePath, romPath] = process.argv.slice(2);
  const html = fs.readFileSync(pagePath, "utf8");
  const scripts = [...html.matchAll(/<script(?:\s[^>]*)?>([\s\S]*?)<\/script>/g)].map(match => match[0]);
  const planText = /<script id="plan-data"[^>]*>([\s\S]*?)<\/script>/.exec(html)[1];
  const code = scripts.filter(tag => !tag.includes('id="plan-data"')).map(tag => tag.replace(/^<script[^>]*>/, "").replace(/<\/script>$/, ""));

  const elements = {};
  for (const id of ["content", "rom-status", "rom-input", "site-nav"]) elements[id] = new Element("div");
  elements["plan-data"] = Object.assign(new Element("script"), { _text: planText });
  const windowListeners = {}, errors = [];
  global.Node = Element;
  Object.assign(global.Node, {});
  global.document = {
    getElementById: id => elements[id],
    createElement: tag => new Element(tag),
    createTextNode: text => new TextNode(text),
    addEventListener() {},
    querySelectorAll: () => [],
  };
  global.window = global;
  global.window.addEventListener = (type, fn) => { (windowListeners[type] ||= []).push(fn); };
  global.window.scrollTo = () => {};
  global.window.opener = null;
  global.location = { hash: "", origin: "http://localhost" };
  global.ImageData = class { constructor(data, width, height) { if (data.length !== width * height * 4) throw new Error("ImageData size mismatch"); } };
  global.queueMicrotask = fn => Promise.resolve().then(fn);
  global.requestAnimationFrame = () => 0;
  global.cancelAnimationFrame = () => {};
  const intersections = [];
  global.IntersectionObserver = class { constructor(callback) { this.callback = callback; intersections.push(this); } observe() {} disconnect() { this.callback = null; } };
  const scrollToEnd = () => { for (const observer of intersections) observer.callback?.([{ isIntersecting: true }]); };
  process.on("unhandledRejection", error => errors.push(String(error && error.stack || error)));

  for (const source of code) new Function(source)();
  const settle = () => new Promise(resolve => setTimeout(resolve, 50));
  const go = async hash => { global.location.hash = hash; for (const fn of windowListeners.hashchange || []) fn(); await settle(); await settle(); };
  for (let i = 0; i < 100 && !count(elements.content, e => e.className === "intake"); i++) await settle();
  const content = elements.content;
  if (!content.children.length) throw new Error("plan did not load");

  const checks = [];
  const gated = elements["site-nav"].hidden === true && count(content, e => e.className === "intake") === 1 && count(content, e => e.tagName === "TABLE") === 0;
  checks.push(["before a ROM: only the intake shows", gated]);
  // ROM through the file input path; a modified copy first must be refused with a plain message.
  const rom = fs.readFileSync(romPath);
  const modified = Buffer.from(rom); modified[0x200000] ^= 1;
  elements["rom-input"].listeners.change[0]({ target: { files: [{ arrayBuffer: async () => modified.buffer.slice(modified.byteOffset, modified.byteOffset + modified.length) }] } });
  for (let i = 0; i < 100 && !elements["rom-status"].textContent.includes("not the original"); i++) await settle();
  checks.push([`a modified ROM is refused ("${elements["rom-status"].textContent.slice(0, 60)}...")`, elements["rom-status"].textContent.includes("not the original") && elements["site-nav"].hidden === true]);
  const file = { arrayBuffer: async () => rom.buffer.slice(rom.byteOffset, rom.byteOffset + rom.length) };
  elements["rom-input"].listeners.change[0]({ target: { files: [file] } });
  for (let i = 0; i < 100 && elements["site-nav"].hidden !== false; i++) await settle();
  if (elements["site-nav"].hidden !== false) throw new Error("ROM not accepted: " + elements["rom-status"].textContent);
  checks.push([`no status text after a good ROM ("${elements["rom-status"].textContent}")`, elements["rom-status"].textContent === ""]);

  const plan = JSON.parse(require("zlib").gunzipSync(Buffer.from(planText.trim(), "base64")));

  await go("#/coverage"); checks.push(["coverage tables", count(content, e => e.tagName === "TABLE") >= 1]);
  await go("#/unread"); checks.push(["unread classes", count(content, e => e.tagName === "TR") === plan.classes.length + 1]);
  await go("#/kinds"); checks.push(["kind rows", count(content, e => e.tagName === "TR") === plan.kinds.length + 1]);
  await go("#/kind/lz77"); checks.push(["kind page links", count(content, e => e.tagName === "A") > 50]);
  const firstOf = {};
  plan.items.forEach((entry, index) => { for (const view of entry[6]) if (!(view.t in firstOf)) firstOf[view.t] = index; });
  firstOf.none = plan.items.findIndex(entry => entry[6].length === 0);
  firstOf.via = plan.items.findIndex(entry => entry[5].length === 0 && entry[8].length > 0);
  for (const [type, index] of Object.entries(firstOf)) {
    await go(`#/item/${index}`);
    for (let i = 0; i < 40 && type !== "none" && type !== "via" && !count(content, e => e.className.includes("view")); i++) await settle();
    const ranges = count(content, e => e.tagName === "A" && String(e.attributes.href || "").startsWith("#/rom/"));
    const bad = count(content, e => e.className.includes("check bad") || e.className === "error");
    checks.push([`item ${type} (#${index}): ROM range links ${ranges}, failed checks ${bad}`, ranges > 0 && bad === 0 && (type === "none" || type === "via" || count(content, e => e.className.includes("view")) > 0)]);
  }
  await go("#/rom/087B2524"); checks.push(["ROM view cells", count(content, e => e.tagName === "TD") > 600]);
  checks.push(["after the ROM: navigation shows", elements["site-nav"].hidden === false]);
  await go("#/rom/08092634");
  const values = []; (function walk(e) { if (e instanceof Element) { if (e.tagName === "TD" && /^([0-9A-F]{2}|··)$/.test(e.textContent)) values.push(e.textContent); e.children.forEach(walk); } })(content);
  checks.push([`ROM view shows byte values in matched code (first ${values.slice(0, 4).join(" ")})`, values.length >= 600 && values.every(v => v !== "··")]);
  await go("#/rom/0870927C/0870C9EC"); checks.push(["ROM view of an unread range", count(content, e => e.tagName === "TD") > 600]);
  for (const name of Object.keys(plan.summary.classes)) { await go(`#/class/${name}`); checks.push([`class ${name}`, count(content, e => e.tagName === "TR") > 1]); }
  const cards = async (hash, want) => { await go(hash); for (let i = 0; i < 200 && count(content, e => e.className === "art-card") < want; i++) await settle(); return count(content, e => e.className === "art-card"); };
  const errorsIn = () => count(content, e => e.className === "error" || e.className.includes("check bad"));
  for (const category of ["all", "Sprites", "Zoids", "Zoid%20icons", "Portraits", "Maps", "Scenes", "Battle%20backgrounds", "Fonts", "Palettes"]) {
    const n = await cards(`#/gallery/${category}`, 1);
    checks.push([`gallery ${category}: ${n} cards, errors ${errorsIn()}`, n > 0 && errorsIn() === 0]);
  }
  await cards("#/gallery/Portraits", 48);
  scrollToEnd(); for (let i = 0; i < 200 && count(content, e => e.className === "art-card") < 96; i++) await settle();
  checks.push([`scrolling to the end loads the next batch (${count(content, e => e.className === "art-card")} portraits)`, count(content, e => e.className === "art-card") === 96]);
  const searched = await cards("#/gallery/all/0x0835", 1);
  checks.push([`gallery search (${searched} cards)`, searched > 0]);
  const spriteCards = await cards("#/sprites", 1);
  checks.push([`sprites page: ${spriteCards} animated cards`, spriteCards > 0 && errorsIn() === 0]);
  await go("#/maps"); for (let i = 0; i < 100 && !count(content, e => e.className === "map-viewport"); i++) await settle();
  checks.push([`maps page: viewport, collision check, errors ${errorsIn()}`, count(content, e => e.className === "map-viewport") === 1 && errorsIn() === 0]);
  const worldIndex = plan.items.findIndex(entry => entry[6].some(view => view.t === "map" && view.packed));
  await go(`#/maps/${worldIndex}`); for (let i = 0; i < 100 && !count(content, e => e.className === "map-viewport"); i++) await settle();
  checks.push([`world map viewer: errors ${errorsIn()}`, count(content, e => e.className === "map-viewport") === 1 && errorsIn() === 0]);
  await go("#/text"); for (let i = 0; i < 200 && count(content, e => e.className === "text-row") === 0; i++) await settle();
  checks.push([`text page rows ${count(content, e => e.className === "text-row")}`, count(content, e => e.className === "text-row") === 48]);
  await go("#/text/Water"); for (let i = 0; i < 100 && count(content, e => e.className === "text-row") === 0; i++) await settle();
  checks.push([`text search rows ${count(content, e => e.className === "text-row")}`, count(content, e => e.className === "text-row") > 0]);
  const rowsOf = cls => { const out = []; (function walk(e) { if (e instanceof Element) { if (String(e.className).split(" ").includes(cls)) out.push(e); e.children.forEach(walk); } })(content); return out; };
  await go("#/text/Zeru"); for (let i = 0; i < 100 && count(content, e => e.className === "text-row") === 0; i++) await settle();
  checks.push([`text search folds full-width text ("Zeru": ${count(content, e => e.className === "text-row")} rows)`, count(content, e => e.className === "text-row") > 0]);
  const cardKeys = () => { const out = []; (function walk(e) { if (e instanceof Element) { if (e.className === "art-card") out.push(`${e.attributes.href}|${e.textContent}`); e.children.forEach(walk); } })(content); return out; };
  await cards("#/gallery/all", 48);
  checks.push([`gallery cards are distinct (${new Set(cardKeys()).size} of ${cardKeys().length})`, cardKeys().length > 0 && new Set(cardKeys()).size === cardKeys().length]);
  await cards("#/gallery/Zoids", 1);
  checks.push([`gallery Zoid cards open the Zoid page (${cardKeys()[0]?.split("|")[0]})`, cardKeys()[0]?.startsWith("#/zoid/1|")]);
  for (const hash of ["#/item/99999999", "#/kind/nonsense", "#/class/nonsense", "#/zoid/999", "#/rom/zz", "#/nonsense"]) {
    await go(hash);
    checks.push([`${hash} shows a not-found message`, count(content, e => e.className === "empty") === 1]);
  }
  await go("#/sound");
  const musicRows = rowsOf("sound-row"), named = musicRows.filter(row => !/^Song \d+$/.test(row.children[1].children[0].textContent));
  checks.push([`sound music tab: ${musicRows.length} songs, ${named.length} named (e.g. "${named[1]?.children[1].children[0].textContent}")`, musicRows.length >= 30 && named.length >= 20 && musicRows.every(row => !row.textContent.includes("no tracks"))]);
  musicRows.find(row => !String(row.className).includes("silent")).listeners.click[0]();
  await settle();
  checks.push([`clicking a song opens it in the player ("${rowsOf("now-playing")[0].children[0].textContent}")`, /^Song \d{3}/.test(rowsOf("now-playing")[0].children[0].textContent)]);
  await go("#/sound/effects"); checks.push([`sound effects tab: ${rowsOf("sound-row").length} songs`, rowsOf("sound-row").length === 64]);
  await go("#/sound/samples"); checks.push([`samples tab: ${rowsOf("sample-row").length} samples with waveforms`, rowsOf("sample-row").length === 88 && count(content, e => e.className === "waveform") === 88]);
  const labelsOf = () => { const out = []; (function walk(e) { if (e instanceof Element) { if (e.className === "art-copy") out.push(e.textContent); e.children.forEach(walk); } })(content); return out; };
  for (const [hash, expect] of [["#/gallery/Portraits", /^Zeru · expression 1$/], ["#/gallery/Zoids", /^Iron Kong$/], ["#/gallery/Battle%20backgrounds", /^Flatlands · terrain$/], ["#/gallery/Maps", /^World map · layer BG0$/]]) {
    await cards(hash, 1);
    const labels = labelsOf();
    checks.push([`${hash} names: "${labels[0]}", none raw`, expect.test(labels[0]) && labels.every(label => !/^(sprite\.|lz77 |pilot \d|zoid \d|font\.)/.test(label))]);
  }
  const zoidCards = await cards("#/zoids", 48);
  checks.push([`Zoids list: ${zoidCards} cards, errors ${errorsIn()}`, zoidCards === 48 && errorsIn() === 0]);
  const equipmentCards = await cards("#/equipment", 48);
  checks.push([`Equipment list: ${equipmentCards} cards, errors ${errorsIn()}`, equipmentCards === 48 && errorsIn() === 0]);
  await go("#/zoid/64"); for (let i = 0; i < 100 && !count(content, e => e.className === "zoid-stage"); i++) await settle();
  const mountSelects = count(content, e => e.tagName === "SELECT" && String(e.attributes["aria-label"] || "").startsWith("Mount"));
  checks.push([`Zoid 64 workbench: stage, ${mountSelects} weapon selects, ${count(content, e => e.tagName === "BUTTON" && e.textContent === "CAS transformation")} CAS button, errors ${errorsIn()}`, count(content, e => e.className === "zoid-stage") === 1 && mountSelects === 3 && errorsIn() === 0]);
  const find = (element, predicate) => { if (!(element instanceof Element)) return null; if (predicate(element)) return element; for (const child of element.children) { const hit = find(child, predicate); if (hit) return hit; } return null; };
  const rackSelects = () => { const out = []; (function walk(e) { if (e instanceof Element) { if (e.tagName === "SELECT" && String(e.attributes["aria-label"] || "").startsWith("Mount")) out.push(e); e.children.forEach(walk); } })(content); return out; };
  const optionIn = (select, id) => find(select, e => e.tagName === "OPTION" && e.attributes.value === String(id));
  const zoidBench = async model => { await go(`#/zoid/${model}`); for (let i = 0; i < 100 && !count(content, e => e.className === "zoid-stage"); i++) await settle(); return rackSelects(); };
  let racks = await zoidBench(1);
  checks.push([`Iron Kong mount 1 has no weapon rack (disabled ${racks[0].disabled}); Pulse Lsr is disabled on mount 2`, racks[0].disabled === true && racks[1].disabled === false && "disabled" in optionIn(racks[1], 94).attributes]);
  checks.push(["defense parts are listed but disabled", "disabled" in optionIn(racks[1], 101).attributes && !("disabled" in optionIn(racks[1], 1).attributes)]);
  racks = await zoidBench(17);
  checks.push(["Lightning Saix takes its Pulse Lsr on mount 1", racks[0].disabled === false && !("disabled" in optionIn(racks[0], 94).attributes)]);
  racks = await zoidBench(40);
  racks[2].value = "1"; racks[2].listeners.change.forEach(fn => fn());
  racks[1].value = "91"; racks[1].listeners.change.forEach(fn => fn());
  checks.push([`a mode-3 weapon on mount 2 clears mount 3 (mount 3 now ${racks[2].value})`, racks[2].value === "0" && racks[1].value === "91"]);
  racks[2].value = "1"; racks[2].listeners.change.forEach(fn => fn());
  checks.push([`a weapon on mount 3 clears a mode-3 weapon on mount 2 (mount 2 now ${racks[1].value})`, racks[1].value === "0" && racks[2].value === "1"]);
  await go("#/battle/1/1/0"); for (let i = 0; i < 100 && !count(content, e => e.className === "zoid-stage"); i++) await settle();
  const battleRows = count(content, e => e.tagName === "TR"), battleStatus = () => find(content, e => e.className === "frame-count")?.textContent || "";
  checks.push([`battle field waits for Play battle: stage, ${battleRows} table rows, errors ${errorsIn()}, nothing drawn ("${battleStatus()}")`, count(content, e => e.className === "zoid-stage") === 1 && battleRows >= 9 && errorsIn() === 0 && battleStatus() === ""]);
  const frames = [];
  global.requestAnimationFrame = fn => { frames.push(fn); return frames.length; };
  global.cancelAnimationFrame = () => { frames.length = 0; };
  const playButton = find(content, e => e.tagName === "BUTTON" && e.textContent === "Play battle");
  playButton.listeners.click.forEach(fn => fn());
  let clock = 0;
  const seen = new Set();
  const run = count => { for (let i = 0; i < count && frames.length; i++, clock += 34) { frames.shift()(clock); seen.add(battleStatus().replace(/\d+/g, "N")); } };
  for (let i = 0; i < 400 && !frames.length; i++) await settle();
  const startText = find(content, e => e.tagName === "P" && /^Starts from |could not|No map cell/.test(e.textContent))?.textContent || "";
  run(20);
  const closed = [...seen].some(text => /field closing/.test(text));
  run(260);
  checks.push([`Play battle closes the field with the Z ("${startText}") and then runs the intro until it settles ("${battleStatus()}")`, closed && /scaled Z/.test(startText) && playButton.textContent === "Stop battle" && /camera settled after 72 updates/.test(battleStatus())]);
  const formationSelect = find(content, e => e.tagName === "SELECT" && e.attributes["aria-label"] === "Formation");
  const before = Number(/update (\d+)/.exec(battleStatus())?.[1]);
  formationSelect.value = "1"; formationSelect.listeners.change.forEach(fn => fn());
  for (let i = 0; i < 400 && !frames.length; i++) await settle();
  run(60);
  const after = Number(/update (\d+)/.exec(battleStatus())?.[1]);
  checks.push([`switching the formation restarts the battle from the field (update ${before} -> ${after}, "${battleStatus()}")`, after < before && playButton.textContent === "Stop battle" && frames.length > 0]);
  const pick = (label, value) => { const select = find(content, e => e.tagName === "SELECT" && e.attributes["aria-label"] === label); select.value = String(value); select.listeners.change.forEach(fn => fn()); return select; };
  const terrainSelect = () => find(content, e => e.tagName === "SELECT" && e.attributes["aria-label"] === "Battle terrain");
  const defaultText = () => terrainSelect().children.find(option => option.attributes.value === "auto")?.textContent || "";
  pick("Encounter group", 1); const groupOne = defaultText();
  pick("Encounter group", 5); const groupFive = defaultText();
  for (let i = 0; i < 400 && !frames.length; i++) await settle();
  checks.push([`battle: changing the encounter group resets the terrain to that group's default ("${groupOne}" -> "${groupFive}")`, terrainSelect().value === "auto" && /^Encounter default \(\d+: /.test(groupFive) && frames.length > 0]);
  const scriptSelect = find(content, e => e.tagName === "SELECT" && e.attributes["aria-label"] === "Script battle");
  const scriptCount = scriptSelect ? scriptSelect.children.length - 1 : 0;
  pick("Script battle", 0);
  const groupSelect = find(content, e => e.tagName === "SELECT" && e.attributes["aria-label"] === "Encounter group");
  checks.push([`script battles listed (${scriptCount}); picking one selects its group and formation (group ${groupSelect.value}, "${scriptSelect?.children[1]?.textContent}")`, scriptCount >= 20 && groupSelect.value !== "5" && scriptSelect.value === "0" && terrainSelect().value === "auto"]);
  playButton.listeners.click.forEach(fn => fn());
  checks.push(["Stop battle stops the loop", playButton.textContent === "Play battle" && frames.length === 0]);
  global.requestAnimationFrame = () => 0; global.cancelAnimationFrame = () => {};
  await go("#/battle/99/99/99"); for (let i = 0; i < 100 && !count(content, e => e.className === "zoid-stage"); i++) await settle();
  checks.push(["out-of-range battle field values fall back to defaults", count(content, e => e.className === "zoid-stage") === 1]);
  const spriteItem = plan.items.findIndex(entry => entry[6].some(view => view.t === "sprite" && view.family));
  await go(`#/item/${spriteItem}`); for (let i = 0; i < 100 && !count(content, e => e.className.includes("sprite-stage")); i++) await settle();
  checks.push([`family sprite item #${spriteItem}: player, ${count(content, e => e.tagName === "OPTION")} choices, errors ${errorsIn()}`, count(content, e => e.className.includes("sprite-stage")) > 0 && count(content, e => e.tagName === "OPTION") > 10 && errorsIn() === 0]);

  let failed = errors.length;
  for (const [label, ok] of checks) { console.log((ok ? "ok   " : "FAIL ") + label); if (!ok) failed++; }
  for (const error of errors) console.log("ERROR " + error);
  process.exit(failed ? 1 : 0);
}

main().catch(error => { console.error(error); process.exit(1); });
