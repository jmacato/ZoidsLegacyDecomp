// The asset extractor over the extractor's plan.json. Every asset is an item read by a Rust port of byte-matched C and
// links to the exact ROM ranges it read; previews decode the user's own ROM with decode.js and are checked against Rust.
(function () {
  "use strict";
  const D = globalThis.ZoidsDecode;
  const BASE = D.BASE;
  const PAGE = 48;
  const FRAME_HZ = 16777216 / 280896;
  const SONG_TABLE = 0x086a46c4, SONGS = 134;
  const content = document.getElementById("content");
  const statusLine = document.getElementById("rom-status");
  const CLASS_INFO = {
    declared_unread: ["Declared unread", "inside an item, never read by the C it ports (reason cites the C)"],
    declared_unreachable: ["Declared unreachable", "no decomp code reaches it (reason names the check)"],
    explained: ["Explained", "a referenced address no port reads, with the C reason"],
    fill_ff: ["Fill 0xFF", "0xFF fill that nothing points into"],
    zero: ["Zero fill", "zero bytes that nothing points into"],
    undeclared_gap: ["Undeclared gap", "must be 0"],
    referenced_unread: ["Referenced unread", "must be 0"],
    undeclared_unreferenced: ["Undeclared unreferenced", "must be 0"],
  };
  const COLORS = { code: [64, 72, 78], known: [84, 161, 139], declared_unread: [110, 118, 129], declared_unreachable: [87, 96, 106], explained: [163, 113, 247], fill_ff: [33, 38, 45], zero: [28, 33, 40], open: [230, 120, 90] };
  const VIEW_TITLES = { lz77: v => `LZ77 · ${v.use}`, palette: () => "Palette", tiles: v => `Raw tiles · ${v.bpp}bpp`, bg: () => "Background · 256 colours", glyphs: () => "Font glyphs", tilemap: () => "Tilemap", layer: v => `Map layer ${v.name}`, text: v => `Text · ${v.g}`, wav: v => `PCM · ${v.rate} Hz`, sprite: v => `Sprite · tile ${hex(v.tile, 3)}, palette ${v.palette}`, unbound: () => "No image: tiles and palette set at runtime", songs: () => "Where each song plays" };

  let plan = null, rom = null, player = null, objects = null;
  const views = new Map();

  // ---------- helpers ----------
  const hex = (value, width = 8) => "0x" + value.toString(16).toUpperCase().padStart(width, "0");
  const node = (tag, props = {}, ...children) => {
    const element = document.createElement(tag);
    for (const [key, value] of Object.entries(props)) {
      if (key === "class") element.className = value;
      else if (key.startsWith("on")) element.addEventListener(key.slice(2), value);
      else element.setAttribute(key, value);
    }
    for (const child of children.flat()) if (child != null) element.append(child instanceof Node ? child : document.createTextNode(String(child)));
    return element;
  };
  const link = (href, text, cls) => node("a", { href, class: cls || "" }, text);
  const romLink = (start, end) => link(`#/rom/${start.toString(16).toUpperCase()}` + (end ? `/${end.toString(16).toUpperCase()}` : ""), end ? `${hex(start)}..${hex(end)}` : hex(start), "mono");
  const item = index => {
    const [kind, address, basis, count, reached, spans, itemViews, reason, via] = plan.items[index];
    return { index, kind: plan.kinds[kind], address, basis: plan.bases[basis], count, reached, spans, views: itemViews, reason, via: via || [] };
  };
  const itemLabel = info => `${info.kind} @ ${hex(info.address)}`;
  const itemLink = index => link(`#/item/${index}`, itemLabel(item(index)), "mono");
  const bytesOf = info => info.spans.reduce((sum, [start, end]) => sum + end - start, 0);
  const button = (text, action, cls) => node("button", { onclick: action, class: cls || "", type: "button" }, text);
  let generation = 0;
  const clear = () => { generation++; player?.stop?.(); soundUI = null; stopAnimations(); observers.forEach(observer => observer.disconnect()); observers = []; content.replaceChildren(); window.scrollTo(0, 0); };
  const panel = (title, note) => node("section", { class: "panel" }, node("div", { class: "panel-heading" }, node("h2", {}, title), note ? node("p", {}, note) : null));
  const notFound = message => content.append(node("div", { class: "empty" }, node("p", {}, message), node("p", {}, link("#/gallery", "Open the gallery"))));
  const replaceHash = hash => globalThis.history?.replaceState?.(null, "", hash);
  const halfWidth = text => text.replace(/[\uff01-\uff5e]/g, char => String.fromCharCode(char.charCodeAt(0) - 0xfee0)).replace(/\u3000/g, " ");
  const fileName = (label, extension) => `${label.replace(/ · /g, " - ").replace(/[\\/:*?"<>|\n]+/g, "_").trim() || "asset"}.${extension}`;
  const debounce = (fn, ms = 200) => { let timer = null; return (...args) => { clearTimeout(timer); timer = setTimeout(() => fn(...args), ms); }; };

  function canvasOf(img, scale = 1) {
    const canvas = node("canvas", { width: img.width, height: img.height });
    canvas.getContext("2d").putImageData(new ImageData(img.rgba, img.width, img.height), 0, 0);
    if (scale !== 1) canvas.style.width = `${img.width * scale}px`;
    return canvas;
  }

  // A static picture as <img> (object-fit keeps its aspect ratio in the 4:3 card stage).
  function imageOf(img) {
    const canvas = canvasOf(img), out = node("img", { alt: "", src: canvas.toDataURL ? canvas.toDataURL() : "" });
    return out;
  }

  // An animated canvas at the largest whole-number scale (at most 4x) that fits a 160 px tall card stage.
  function fitStage(canvas) {
    const factor = Math.max(1, Math.min(4, Math.floor(160 / Math.max(canvas.height, 1)), Math.floor(220 / Math.max(canvas.width, 1))));
    canvas.style.width = `${canvas.width * factor}px`;
    canvas.style.height = `${canvas.height * factor}px`;
  }

  function save(blob, name) {
    const url = URL.createObjectURL(blob);
    node("a", { href: url, download: name }).click();
    setTimeout(() => URL.revokeObjectURL(url), 10000);
  }
  const pngBytes = canvas => new Promise(resolve => canvas.toBlob(resolve)).then(blob => blob.arrayBuffer()).then(buffer => new Uint8Array(buffer));

  const CRC_TABLE = Array.from({ length: 256 }, (_, n) => { for (let k = 0; k < 8; k++) n = n & 1 ? 0xedb88320 ^ (n >>> 1) : n >>> 1; return n >>> 0; });
  const crc32 = bytes => { let crc = ~0; for (let i = 0; i < bytes.length; i++) crc = CRC_TABLE[(crc ^ bytes[i]) & 0xff] ^ (crc >>> 8); return ~crc >>> 0; };
  // An uncompressed ZIP of [name, bytes] entries (PNG and WAV gain little from deflate).
  function zip(entries) {
    const encoder = new TextEncoder(), parts = [], central = [], used = new Set();
    const record = (size, fields) => { const view = new DataView(new ArrayBuffer(size)); for (const [at, value, width] of fields) width === 4 ? view.setUint32(at, value, true) : view.setUint16(at, value, true); return new Uint8Array(view.buffer); };
    let offset = 0;
    for (const [wanted, bytes] of entries) {
      let name = wanted;
      for (let n = 2; used.has(name.toLowerCase()); n++) name = wanted.replace(/(\.[a-z0-9]+)$/i, ` (${n})$1`);
      used.add(name.toLowerCase());
      const path = encoder.encode(name), crc = crc32(bytes);
      const shared = [[0x0800, 2], [0, 2], [0, 2], [33, 2], [crc, 4], [bytes.length, 4], [bytes.length, 4], [path.length, 2], [0, 2]];
      parts.push(record(30, [[0, 0x04034b50, 4], [4, 20, 2], ...shared.map(([value, width], i) => [[6, 8, 10, 12, 14, 18, 22, 26, 28][i], value, width])]), path, bytes);
      central.push(record(46, [[0, 0x02014b50, 4], [4, 20, 2], [6, 20, 2], ...shared.map(([value, width], i) => [[8, 10, 12, 14, 16, 20, 24, 28, 30][i], value, width]), [42, offset, 4]]), path);
      offset += 30 + path.length + bytes.length;
    }
    const size = central.reduce((sum, part) => sum + part.length, 0);
    return new Blob([...parts, ...central, record(22, [[0, 0x06054b50, 4], [8, entries.length, 2], [10, entries.length, 2], [12, size, 4], [16, offset, 4]])], { type: "application/zip" });
  }

  // A button that packs `list` into a ZIP, one `entry(item)` -> [name, bytes] at a time; clicking again cancels.
  function zipButton(label, archive, list, entry) {
    let running = false;
    const control = button(label, async () => {
      if (running) { running = false; return; }
      running = true;
      const files = [], page = generation;
      for (const [i, value] of list.entries()) {
        if (!running || page !== generation) break;
        control.textContent = `Packing ${(i + 1).toLocaleString()} of ${list.length.toLocaleString()} (click to cancel)`;
        try { const file = await entry(value); if (file) files.push(file); } catch { /* an entry that fails to decode is left out of the ZIP */ }
      }
      if (running && page === generation && files.length) save(zip(files), archive);
      running = false;
      control.textContent = label;
    });
    control.disabled = !list.length;
    return control;
  }

  // Appends `list` to `container` in batches as the reader scrolls near the end; `status` shows the total.
  let observers = [];
  function infinite(container, list, renderOne, status, noun = "items") {
    let next = 0, busy = false;
    const page = generation, live = () => page === generation && container.isConnected !== false;
    const sentinel = node("div", { class: "sentinel" });
    container.after(sentinel);
    const report = () => { if (status) status.textContent = !list.length ? "No matches" : next ? `${list.length.toLocaleString()} ${noun}` : "Loading..."; };
    const near = () => { const box = sentinel.getBoundingClientRect(); return box.top < (window.innerHeight || 0) + 1200; };
    async function more() {
      if (busy || next >= list.length) return;
      busy = true;
      const end = Math.min(list.length, next + PAGE);
      for (let i = next; i < end; i++) {
        if (!live()) return;
        await renderOne(list[i], i);
      }
      next = end;
      busy = false;
      report();
      if (next < list.length && near()) more();
    }
    if (globalThis.IntersectionObserver) {
      const observer = new IntersectionObserver(entries => { if (entries.some(entry => entry.isIntersecting)) more(); }, { rootMargin: "1200px 0px" });
      observer.observe(sentinel);
      observers.push(observer);
    }
    report();
    more();
  }

  // ---------- indexes ----------
  let spanStarts, spanEnds, spanMaxEnd, spanItems, spanFormats, kindItems, unreadByClass, unreadStarts, unreadInside, assets;
  function buildIndexes() {
    const spans = [];
    plan.items.forEach(([, , , , , itemSpans], index) => { for (const [start, end, format] of itemSpans) spans.push([start, end, format, index]); });
    spans.sort((a, b) => a[0] - b[0] || a[1] - b[1]);
    spanStarts = new Uint32Array(spans.map(s => s[0])); spanEnds = new Uint32Array(spans.map(s => s[1]));
    spanFormats = new Uint16Array(spans.map(s => s[2])); spanItems = new Uint32Array(spans.map(s => s[3]));
    spanMaxEnd = new Uint32Array(spans.length);
    spans.forEach((span, i) => { spanMaxEnd[i] = Math.max(span[1], i ? spanMaxEnd[i - 1] : 0); });
    kindItems = new Map();
    plan.items.forEach(([kind], index) => { if (!kindItems.has(kind)) kindItems.set(kind, []); kindItems.get(kind).push(index); });
    unreadByClass = new Map(); unreadInside = new Map();
    plan.unread.forEach((range, index) => {
      const name = plan.classes[range[2]];
      if (!unreadByClass.has(name)) unreadByClass.set(name, []);
      unreadByClass.get(name).push(index);
      if (range[5] >= 0) { if (!unreadInside.has(range[5])) unreadInside.set(range[5], []); unreadInside.get(range[5]).push(index); }
    });
    unreadStarts = new Uint32Array(plan.unread.map(range => range[0]));
  }

  function lowerBound(array, value) { let lo = 0, hi = array.length; while (lo < hi) { const mid = (lo + hi) >> 1; if (array[mid] < value) lo = mid + 1; else hi = mid; } return lo; }

  function ownersAt(address) {
    const out = { code: null, spans: [], unread: null };
    for (const region of plan.regions) if (region[0] <= address && address < region[1]) { out.code = region; return out; }
    for (let i = lowerBound(spanStarts, address + 1) - 1; i >= 0 && spanMaxEnd[i] > address; i--) {
      if (spanStarts[i] <= address && address < spanEnds[i]) out.spans.push({ item: spanItems[i], format: plan.formats[spanFormats[i]], start: spanStarts[i], end: spanEnds[i] });
    }
    const u = lowerBound(unreadStarts, address + 1) - 1;
    if (u >= 0 && address < plan.unread[u][1]) out.unread = u;
    return out;
  }

  function stateAt(address, owners = ownersAt(address)) {
    if (owners.code) return "code";
    if (owners.spans.length) return "known";
    if (owners.unread != null) { const cls = plan.classes[plan.unread[owners.unread][2]]; return COLORS[cls] ? cls : "open"; }
    return "open";
  }

  function findItem(kindName, address) {
    const kind = plan.kinds.indexOf(kindName);
    return (kindItems.get(kind) || []).find(index => plan.items[index][1] === address) ?? null;
  }

  // ---------- names ----------
  // Names from the game's own tables, indexed the way the C indexes them.
  const names = new Map();
  const word = address => (rom[address - BASE] | (rom[address - BASE + 1] << 8) | (rom[address - BASE + 2] << 16) | (rom[address - BASE + 3] << 24)) >>> 0;
  const tableOf = kind => { const list = kindItems.get(plan.kinds.indexOf(kind)); return list && list.length ? plan.items[list[0]][1] : null; };
  const ascii = text => halfWidth(text).replace(/\s+/g, " ").trim();
  function nameIn(kind, index) {
    const key = `${kind}:${index}`;
    if (!names.has(key)) {
      const table = tableOf(kind);
      let text = "";
      try { const pointer = table != null && index >= 0 ? word(table + index * 4) : 0; if (pointer >= BASE && pointer < BASE + plan.rom_size) text = ascii(D.text(rom, pointer, "item").text); } catch { text = ""; }
      names.set(key, text);
    }
    return names.get(key);
  }
  const zoidName = id => nameIn("table.zoid_names", id) || `Zoid ${id}`;
  const pilotName = id => nameIn("table.pilot_names", id) || `Pilot ${id}`;
  const weaponName = id => nameIn("table.equipment_names", id) || `Weapon ${id}`;
  const indexIn = (text, prefix) => { const match = text && text.startsWith(prefix) ? /\[(\d+)\]/.exec(text) : null; return match ? Number(match[1]) : null; };
  const fromReached = (info, prefix) => { for (const reached of info.reached) { const index = indexIn(reached, prefix); if (index != null) return index; } return null; };
  function mapLabel(map) {
    const definitions = tableOf("table.field_map_definitions"), group = definitions != null ? rom[definitions + map * 32 + 0x1d - BASE] : 0;
    const groupName = group ? nameIn("table.field_map_group_names", group) : "";
    return groupName ? `${groupName} · map ${map}` : map === 0 ? "World map" : `Map ${map}`;
  }
  function terrainLabel(terrain) {
    const fields = tableOf("table.link_battle_field_terrains");
    if (fields != null) for (let field = 1; field < 15; field++) if (rom[fields + field - 1 - BASE] === terrain) return nameIn("table.link_battle_field_names", field);
    return `Terrain ${terrain}`;
  }
  const SPRITE_TABLES = {
    0x087aa244: index => `${zoidName(index)} · body parts`,
    0x087ac2bc: index => `${weaponName(index >> 1)} · ${index & 1 ? "rear" : "front"}`,
    0x087ac9e0: index => `Battle cursor ${index}`,
    0x087ac9f0: index => `Battle numbers ${index}`,
    0x087acdd8: index => `Battle effect ${index}`,
    0x087ad1d0: index => `Combination effect ${index}`,
    0x087ad208: index => nameIn("table.pilot_names", index) || `Field actor ${index}`,
    0x087adaf8: index => `Field actor special ${index}`,
    0x087afa94: index => `Scene effect ${index}`,
  };
  // Streamed sprite resource tables: which {frames, animations, tiles, palette} entry loads a tiles or palette address.
  let owners = null;
  function resourceOwners() {
    if (owners) return owners;
    owners = new Map();
    for (const table of [0x087ac9e0, 0x087ac9f0, 0x087acdd8, 0x087ad1d0, 0x087ad208, 0x087adaf8, 0x087afa94]) {
      const owner = findItem("sprite.resources", table);
      if (owner == null) continue;
      const end = Math.max(...plan.items[owner][5].map(span => span[1]));
      for (let entry = table, index = 0; entry + 16 <= end; entry += 16, index++) for (const offset of [8, 12]) {
        const key = `${offset}:${word(entry + offset)}`;
        if (!owners.has(key)) owners.set(key, [table, index]);
      }
    }
    return owners;
  }
  const humanize = file => { const base = file.split("/").pop().replace(/\.c$|\.s$/, "").replace(/^(run|create|show|initialize|update|play|load|draw)_/, "").replace(/_/g, " "); return base.charAt(0).toUpperCase() + base.slice(1); };
  function codeFile(address) { for (const [start, end, file] of plan.regions) if (start <= address && address < end) return file; return null; }

  // A readable name for an item, from its view (if any) or what reached it.
  function assetName(info, view = info.views[0]) {
    if (view?.t === "sprite") {
      let match;
      if (view.label && (match = /^pilot (\d+), expression (\d+)(?:, alternate palette (\d+))?/.exec(view.label))) return `${pilotName(+match[1])} · expression ${+match[2] + 1}${match[3] != null ? ` · palette ${+match[3] + 1}` : ""}`;
      if (view.label && (match = /^zoid (\d+), palette (\d+)/.exec(view.label))) return `${zoidName(+match[1])} · palette ${+match[2] + 1}`;
      if (view.streamed && view.site?.[0]) { const [, table, index] = /^0x([0-9A-F]+)\[(\d+)\]/i.exec(view.site[0]) || []; const name = SPRITE_TABLES[parseInt(table, 16)]; if (name) return name(+index); }
      if (view.family) return view.family.label === "pilot portrait" ? "Pilot portrait frame" : "Zoid icon frame";
      const file = view.site && codeFile(parseInt(view.site[view.site.length - 1], 16));
      if (file) return `${humanize(file)} · ${hex(view.frames).slice(2)}`;
    }
    if (info.kind === "sprite.palette" || info.kind === "sprite.streamed_tiles") {
      const owner = resourceOwners().get(`${info.kind === "sprite.palette" ? 12 : 8}:${info.address}`);
      if (owner) return `${SPRITE_TABLES[owner[0]](owner[1])} · ${info.kind === "sprite.palette" ? "palette" : "tiles"}`;
    }
    const FONTS = { "font.single": "Single-byte font", "font.sjis": "Shift-JIS font", "font.sjis_fallback": "Shift-JIS fallback font" };
    if (FONTS[info.kind]) return `${FONTS[info.kind]} · ${hex(info.address).slice(2)}`;
    let index;
    if ((index = fromReached(info, "table.zoid_body_graphics")) != null) return zoidName(index);
    if ((index = fromReached(info, "table.zoid_icon_tiles")) != null) return `${zoidName(index)} · icon`;
    if ((index = fromReached(info, "table.pilot_portraits")) != null) return `${pilotName(index)} · portrait`;
    if ((index = fromReached(info, "table.field_map_definitions")) != null) return mapLabel(index);
    if ((index = fromReached(info, "table.scene_background_graphics")) != null) {
      const record = tableOf("table.scene_background_graphics") + index * 24, slot = [0, 1, 2].find(slot => word(record + slot * 8) === info.address);
      return `Scene background ${index}${slot != null ? ` · ${["size classes 0-2", "size class 3", "size class 4"][slot]}` : ""}`;
    }
    if ((index = fromReached(info, "table.battle_terrain_graphics")) != null) return `${terrainLabel(index)} · ${view?.t === "bg" && view.columns === 16 ? "sky" : "terrain"}`;
    if ((index = fromReached(info, "table.compressed_sprite_graphics")) != null) return `Sprite graphics ${index}`;
    const file = info.reached.map(reached => /^src\/([^:]+):/.exec(reached)?.[1]).find(Boolean);
    if (file) return humanize(file);
    return null;
  }

  // ---------- gallery catalogue ----------
  const KIND_NAMES = { "sprite.palette": "Sprite palette", "field_map.decoration_palette": "Map decoration palette" };
  const CATEGORY_ORDER = ["Zoids", "Portraits", "Zoid icons", "Sprites", "Maps", "Scenes", "Battle backgrounds", "Fonts", "Palettes"];
  // Only views drawn the way the game arranges them; raw tile sheets stay on item pages.
  function category(info, view) {
    const from = (info.reached[0] || "").split("@")[0];
    if (view.t === "sprite") return { "table.pilot_portraits": "Portraits", "table.zoid_icon_tiles": "Zoid icons" }[from] || "Sprites";
    if (view.t === "tilemap") return "Zoids";
    if (view.t === "layer") return "Maps";
    if (view.t === "bg") return from === "table.scene_background_graphics" ? "Scenes" : "Battle backgrounds";
    if (view.t === "glyphs") return "Fonts";
    if (view.t === "palette") return "Palettes";
    return null;
  }

  // A sprite view with its VRAM and palette loads made relative to its tile and palette bank, so load sites that draw the same picture match.
  const viewKey = view => {
    if (view.t !== "sprite" || !view.memory) return JSON.stringify(view);
    const memory = view.memory.map(([start, end, source, offset]) => { const base = start >= 0x06000000 ? 0x06010000 + view.tile * 32 : 0x05000200 + view.palette * 32; return [start - base, end - base, source, offset]; });
    return JSON.stringify({ ...view, memory, tile: null, palette: null, site: null, sha1: null });
  };
  // One card per item and picture: views that differ only in where the game loads them collapse into the first;
  // different pictures that share a name are numbered.
  function galleryAssets() {
    const out = [], seen = new Set(), named = new Map();
    plan.items.forEach(([kind, address, , , reached, , itemViews], index) => itemViews.forEach((view, v) => {
      const cat = category({ reached }, view);
      if (!cat) return;
      const key = `${index}:${viewKey(view)}`;
      if (seen.has(key)) return;
      seen.add(key);
      const info = item(index), name = assetName(info, view);
      let label = view.t === "layer" ? `${name || `Map ${hex(address).slice(2)}`} · layer ${view.name.toUpperCase()}` : name || `${KIND_NAMES[plan.kinds[kind]] || plan.kinds[kind]} · ${hex(address).slice(2)}`;
      const repeat = (named.get(label) || 0) + 1;
      named.set(label, repeat);
      if (repeat > 1) label += ` · ${repeat}`;
      const model = cat === "Zoids" ? fromReached(info, "table.zoid_body_graphics") : null;
      const href = model >= 1 && model <= 151 ? `#/zoid/${model}` : `#/item/${index}`;
      out.push({ index, v, category: cat, label, href, model, search: halfWidth(`${label} ${hex(address)} ${plan.kinds[kind]}`).toLowerCase() });
    }));
    return out.sort((a, b) => CATEGORY_ORDER.indexOf(a.category) - CATEGORY_ORDER.indexOf(b.category));
  }

  // ---------- ROM intake ----------
  const fail = (...message) => { statusLine.className = "error"; statusLine.replaceChildren(...message); };
  async function useRom(buffer) {
    const bytes = new Uint8Array(buffer);
    statusLine.className = ""; statusLine.textContent = "";
    if (bytes.length !== plan.rom_size) { fail(`This file is ${bytes.length.toLocaleString()} bytes. The Zoids Legacy (USA) ROM is ${plan.rom_size.toLocaleString()} bytes. Check that you chose the .gba file.`); return; }
    statusLine.textContent = "Checking the ROM...";
    const hash = await D.sha1(bytes);
    if (hash !== plan.rom_sha1) {
      fail(node("p", {}, "This is not the original Zoids Legacy (USA) ROM. A patched ROM or a ROM from another region does not work. Open the unpatched ROM."),
        node("details", {}, node("summary", {}, "SHA-1 details"), node("p", { class: "mono" }, `This file: ${hash}`), node("p", { class: "mono" }, `Expected: ${plan.rom_sha1}`)));
      return;
    }
    rom = bytes; views.clear();
    objects = new globalThis.ZoidsObjects.Archive(rom, plan, D.lz77, D.text);
    names.clear(); owners = null;
    assets = galleryAssets();
    statusLine.textContent = "";
    route();
  }
  document.getElementById("rom-input").addEventListener("change", event => { const file = event.target.files[0]; if (file) file.arrayBuffer().then(useRom); });
  const keyboardFile = (label, input) => label.addEventListener("keydown", event => { if (event.key === "Enter" || event.key === " ") { event.preventDefault(); input.click(); } });
  const openRom = document.getElementById("open-rom");
  if (openRom) keyboardFile(openRom, document.getElementById("rom-input"));
  window.addEventListener("message", event => {
    if (event.origin !== location.origin || event.data?.type !== "zoids-extractor-rom" || !event.data.file) return;
    event.data.file.arrayBuffer().then(useRom);
  });
  let dragDepth = 0;
  const dragging = on => document.body?.classList.toggle("rom-dragging", on);
  const carriesFiles = event => [...(event.dataTransfer?.types || [])].includes("Files");
  document.addEventListener("dragenter", event => { if (carriesFiles(event)) { dragDepth++; dragging(true); } });
  document.addEventListener("dragleave", event => { if (carriesFiles(event) && --dragDepth <= 0) { dragDepth = 0; dragging(false); } });
  document.addEventListener("dragover", event => event.preventDefault());
  document.addEventListener("drop", event => { event.preventDefault(); dragDepth = 0; dragging(false); const file = event.dataTransfer.files[0]; if (file) file.arrayBuffer().then(useRom); });
  const researchMenu = document.querySelector?.("nav details");
  document.addEventListener("click", event => { if (researchMenu?.open && !researchMenu.contains(event.target)) researchMenu.open = false; });
  document.addEventListener("keydown", event => { if (event.key === "Escape" && researchMenu?.open) { researchMenu.open = false; researchMenu.querySelector("summary")?.focus(); } });

  // ---------- decoding ----------
  function decodedViews(index) {
    if (!views.has(index)) {
      const info = item(index);
      views.set(index, Promise.all(info.views.map(view => D.render(rom, info.address, view).catch(error => ({ kind: "error", error: error.message })))));
    }
    return views.get(index);
  }

  // The ROM sources a view's recipe reads, as links to their items or ranges.
  function sourceLinks(view) {
    const out = [], seen = new Set();
    const add = recipe => {
      if (!Array.isArray(recipe)) return;
      const key = JSON.stringify(recipe);
      if (seen.has(key)) return;
      seen.add(key);
      if (recipe[0] === "rom") out.push(romLink(recipe[1], recipe[2]));
      else if (recipe[0] === "lz77") { const owner = findItem("lz77", recipe[1]); out.push(owner != null ? itemLink(owner) : romLink(recipe[1])); }
      else recipe.slice(1).forEach(add);
    };
    for (const key of ["tiles", "palette", "map", "entries", "colors", "data", "samples"]) add(view[key]);
    if (view.t === "sprite") {
      const animations = findItem("sprite.animation_table", view.animations);
      if (animations != null) out.push(itemLink(animations));
      for (const [, , src] of view.memory) add(src);
    }
    return out;
  }

  // One clock steps every sprite animation, so a single control pauses them all.
  let motion = !globalThis.matchMedia?.("(prefers-reduced-motion: reduce)").matches, clock = null;
  const clockSteps = new Set();
  function stopAnimations() { clockSteps.clear(); clearInterval(clock); clock = null; }
  function motionButton() {
    const label = () => motion ? "Pause animations" : "Play animations";
    const control = button(label(), () => { motion = !motion; control.textContent = label(); });
    return control;
  }

  // Plays animation `which` (or each frame in turn when the table has none) on `canvas`.
  function animate(canvas, result, which = 0, onFrame) {
    const steps = (result.animations || []).filter(Boolean)[which] || result.frames.map((_, frame) => ({ frame, duration: 8 }));
    const images = result.frames.map(frame => D.spriteImage(frame, result.pram));
    const box = { left: Math.min(...result.frames.map(f => f.left)), top: Math.min(...result.frames.map(f => f.top)) };
    const right = Math.max(...result.frames.map(f => f.left + f.width)), bottom = Math.max(...result.frames.map(f => f.top + f.height));
    canvas.width = Math.max(right - box.left, 1); canvas.height = Math.max(bottom - box.top, 1);
    const context = canvas.getContext("2d");
    let step = 0, left = 0;
    const draw = () => {
      const entry = steps[step % steps.length], frame = result.frames[entry.frame];
      context.clearRect(0, 0, canvas.width, canvas.height);
      if (frame && frame.width) {
        const scratch = canvasOf(images[entry.frame]);
        context.drawImage(scratch, frame.left - box.left, frame.top - box.top);
      }
      onFrame?.(entry, step % steps.length, steps.length);
    };
    draw();
    left = steps[0]?.duration || 1;
    if (steps.length > 1) {
      const tick = () => { if (--left > 0) return; step++; left = steps[step % steps.length].duration || 1; draw(); };
      clockSteps.add(tick);
      clock ||= setInterval(() => { if (motion) for (const each of clockSteps) each(); }, 1000 / FRAME_HZ);
      return () => clockSteps.delete(tick);
    }
    return () => {};
  }

  function checkBadge(check) {
    return check && !check.ok ? node("span", { class: "check bad" }, `Differs from the Rust port: ${check.detail}`) : null;
  }

  async function viewElement(info, result, view) {
    const box = node("div", { class: "view" }, node("h3", {}, VIEW_TITLES[view.t] ? VIEW_TITLES[view.t](view) : view.t));
    if (result.kind === "error") { box.append(node("p", { class: "error" }, result.error)); return box; }
    const badge = checkBadge(result.check);
    if (badge) box.append(badge);
    const sources = sourceLinks(view);
    if (sources.length) box.append(node("p", { class: "muted" }, "Sources ", ...sources.flatMap((s, i) => [i ? ", " : "", s])));
    const base = `${assetName(info, view) || info.kind} ${hex(info.address).slice(2)}`;
    if (view.t === "sprite") { box.append(await spriteControls(info, view, result, base)); return box; }
    if (view.t === "songs") { box.append(node("p", {}, link("#/sound", "Open the songs in Sound"))); return box; }
    if (view.t === "script_battles") { box.append(node("p", {}, `${view.battles.length} battles started by event scripts · `, link("#/battle", "Open them on the battle field"))); return box; }
    if (view.t === "unbound") {
      const table = node("table", {}, node("tr", {}, node("th", {}, "Created at"), node("th", {}, "Why")));
      for (const [site, reason] of view.reasons) table.append(node("tr", {}, node("td", { class: "mono" }, site), node("td", { class: "muted" }, reason)));
      box.append(table);
      return box;
    }
    const links = node("div", { class: "detail-links" });
    if (result.image) {
      const canvas = canvasOf(result.image, result.image.width <= 160 ? 2 : 1);
      box.append(canvas);
      links.append(button("Download PNG", () => canvas.toBlob(blob => save(blob, fileName(`${base} ${view.t}${view.name ? " " + view.name : ""}`, "png")))));
    }
    if (result.text != null) box.append(node("pre", {}, result.text));
    if (result.wav) {
      box.append(node("audio", { controls: "", src: URL.createObjectURL(new Blob([result.wav], { type: "audio/wav" })) }));
      links.append(button("Download WAV", () => save(new Blob([result.wav], { type: "audio/wav" }), fileName(base, "wav"))));
    }
    if (result.bytes) links.append(button(`Download decoded .bin (${result.bytes.length.toLocaleString()} bytes)`, () => save(new Blob([result.bytes]), fileName(base, "bin"))));
    if (links.children.length) box.append(links);
    return box;
  }

  // Animation player for a bound sprite, with the family choice (pilot, Zoid) when its graphics come from an indexed loader.
  async function spriteControls(info, view, first, base) {
    const wrap = node("div", { class: "workbench" });
    const stage = node("div", { class: "object-stage sprite-stage" }), canvas = node("canvas");
    stage.append(canvas);
    const controls = node("div", { class: "object-controls" }), status = node("span", { class: "frame-count" });
    let result = first, which = 0, stop = () => {};
    const animationsAvailable = (first.animations || []).filter(Boolean);
    const restart = () => { stop(); stop = animate(canvas, result, which, (entry, step, total) => { status.textContent = `step ${step + 1}/${total} · frame ${entry.frame} · ${entry.duration} ticks`; }); canvas.style.width = `${canvas.width * Math.max(1, Math.min(8, Math.floor(400 / canvas.width), Math.floor(280 / canvas.height)))}px`; };
    if (animationsAvailable.length) {
      const select = node("select", { "aria-label": "Animation" }, ...animationsAvailable.map((_, i) => node("option", { value: String(i) }, `Animation ${i}`)));
      select.addEventListener("change", () => { which = Number(select.value); restart(); });
      controls.append(node("label", {}, "Animation", select));
    }
    if (view.family) {
      const select = node("select", { "aria-label": view.family.label }, ...view.family.choices.map(([name], i) => node("option", { value: String(i) }, name)));
      select.addEventListener("change", () => {
        const choice = Number(select.value), { vram, pram } = D.spriteMemory(rom, view, choice);
        result = { ...result, frames: D.spritePixels(D.spriteFrames(rom, view), view.tile, view.palette, vram), pram };
        restart();
      });
      controls.append(node("label", {}, view.family.label, select));
    }
    controls.append(node("div", { class: "playback" }, motionButton(), status));
    controls.append(node("p", { class: "object-facts" }, `${result.frames.length} frames from `, romLink(view.frames, view.frames + view.count * 4), `; tile offset ${hex(view.tile, 3)}, palette bank ${view.palette}`));
    const sheet = canvasOf(D.spriteSheet(result.frames, result.pram));
    controls.append(node("div", { class: "detail-links" },
      button("Download frame sheet PNG", () => canvasOf(D.spriteSheet(result.frames, result.pram)).toBlob(blob => save(blob, fileName(`${base} sheet`, "png")))),
      button("Download current frame PNG", () => canvas.toBlob(blob => save(blob, fileName(`${base} frame`, "png"))))));
    controls.append(node("details", { class: "source-details" }, node("summary", {}, "All frames"), sheet));
    wrap.append(stage, controls);
    queueMicrotask(restart);
    return wrap;
  }

  // ---------- gallery ----------
  // The image without its fully transparent border.
  function trimmed(img) {
    let left = img.width, top = img.height, right = 0, bottom = 0;
    for (let y = 0; y < img.height; y++) for (let x = 0; x < img.width; x++) if (img.rgba[(y * img.width + x) * 4 + 3]) { left = Math.min(left, x); top = Math.min(top, y); right = Math.max(right, x + 1); bottom = Math.max(bottom, y + 1); }
    if (!right) return img;
    const width = right - left, height = bottom - top, rgba = new Uint8ClampedArray(width * height * 4);
    for (let y = 0; y < height; y++) rgba.set(img.rgba.subarray(((top + y) * img.width + left) * 4, ((top + y) * img.width + right) * 4), y * width * 4);
    return { width, height, rgba };
  }
  const cardImage = (asset, img) => asset.category === "Zoids" ? trimmed(img) : img;

  async function assetCard(asset, grid) {
    const result = (await decodedViews(asset.index))[asset.v];
    const stage = node("div", { class: "art-stage" });
    if (result.kind === "sprite") { const canvas = node("canvas"); stage.append(canvas); animate(canvas, result); fitStage(canvas); }
    else if (result.image) stage.append(imageOf(cardImage(asset, result.image)));
    else stage.append(node("span", { class: "error" }, result.error || "no image"));
    grid.append(node("a", { href: asset.href, class: "art-card", "data-category": asset.category }, stage,
      node("span", { class: "art-copy" }, asset.label),
      result.check && !result.check.ok ? node("small", { class: "error" }, "Differs from Rust") : null));
  }

  // The asset as a PNG: sprites as their frame sheet, pictures at their stored size.
  async function assetFile(asset) {
    const info = item(asset.index), result = await D.render(rom, info.address, info.views[asset.v]);
    const image = result.kind === "sprite" ? D.spriteSheet(result.frames, result.pram) : result.image && cardImage(asset, result.image);
    return image ? [fileName(asset.label, "png"), await pngBytes(canvasOf(image))] : null;
  }

  function gallery(cat, query) {
    clear();
    const counts = new Map(CATEGORY_ORDER.map(c => [c, 0]));
    for (const asset of assets) counts.set(asset.category, (counts.get(asset.category) || 0) + 1);
    const href = (c, s) => `#/gallery/${encodeURIComponent(c || "all")}${s ? "/" + encodeURIComponent(s) : ""}`;
    const filters = [[null, "All assets", assets.length], ...[...counts].filter(([, n]) => n).map(([c, n]) => [c, c, n])];
    const rail = node("div", { class: "categories" }), picker = node("select", { class: "category-select", "aria-label": "Category" });
    const railLinks = filters.map(([c, label, n]) => {
      const anchor = node("a", { href: href(c, query), class: "category-filter" + (c === cat ? " active" : "") }, label, node("span", { class: "category-count" }, n.toLocaleString()));
      rail.append(anchor);
      picker.append(node("option", { value: c || "all", ...(c === cat ? { selected: "" } : {}) }, `${label} (${n.toLocaleString()})`));
      return [anchor, c];
    });
    const search = node("input", { type: "search", placeholder: "Search by name or address", value: query || "", "aria-label": "Search assets" });
    picker.addEventListener("change", () => { location.hash = href(picker.value === "all" ? null : picker.value, search.value.trim()); });
    const status = node("span", { class: "muted" }), results = node("div"), actions = node("div", { class: "toolbar-actions" });
    content.append(node("div", { class: "asset-browser" }, rail, node("div", { class: "browser-results" }, node("div", { class: "gallery-toolbar" }, picker, search, status, actions), results)));
    const show = text => {
      const q = halfWidth(text).toLowerCase();
      const list = assets.filter(asset => (!cat || asset.category === cat) && (!q || asset.search.includes(q)));
      for (const [anchor, c] of railLinks) anchor.setAttribute("href", href(c, text));
      const grid = node("div", { class: "gallery" });
      results.replaceChildren(grid);
      actions.replaceChildren(motionButton(), zipButton(`Download ${list.length.toLocaleString()} as ZIP`, fileName(`Zoids Legacy ${cat || "assets"}${text ? " " + text : ""}`, "zip"), list, assetFile));
      infinite(grid, list, asset => assetCard(asset, grid), status, list.length === 1 ? "asset" : "assets");
    };
    const update = debounce(() => { const text = search.value.trim(); replaceHash(href(cat, text)); show(text); });
    search.addEventListener("input", update);
    show(query || "");
  }

  // ---------- Zoids, CAS and equipment ----------
  const MOUNT_COLORS = ["#ffc36c", "#79c7b1", "#e58ad8"];
  const A = () => globalThis.ZoidsZoidAnimation;
  const OBJ = globalThis.ZoidsObjects?.BASE ?? 0x08000000;

  function frameCanvas(img) {
    const canvas = node("canvas", { width: img.width, height: img.height });
    canvas.getContext("2d").putImageData(new ImageData(new Uint8ClampedArray(img.pixels.buffer), img.width, img.height), 0, 0);
    return canvas;
  }

  // The image cropped to its non-black pixels.
  function cropped(img) {
    let left = img.width, top = img.height, right = 0, bottom = 0;
    for (let i = 0; i < img.pixels.length; i++) if ((img.pixels[i] & 0xffffff) !== 0) { const x = i % img.width, y = i / img.width | 0; left = Math.min(left, x); top = Math.min(top, y); right = Math.max(right, x + 1); bottom = Math.max(bottom, y + 1); }
    if (!right) return img;
    const width = right - left, height = bottom - top, pixels = new Uint32Array(width * height);
    for (let y = 0; y < height; y++) pixels.set(img.pixels.subarray((top + y) * img.width + left, (top + y) * img.width + right), y * width);
    for (let i = 0; i < pixels.length; i++) if ((pixels[i] & 0xffffff) === 0) pixels[i] = 0;
    return { width, height, pixels };
  }

  function sourceList(sources) {
    const table = node("table", {}, node("tr", {}, node("th", {}, "Role"), node("th", {}, "ROM range"), node("th", {}, "Item")));
    const seen = new Set();
    for (const { start, end, role } of sources) {
      const key = `${start}:${end}:${role}`;
      if (seen.has(key)) continue;
      seen.add(key);
      const owner = findItem("lz77", start + OBJ);
      table.append(node("tr", {}, node("td", {}, role), node("td", {}, romLink(start + OBJ, end + OBJ)), node("td", {}, owner != null ? itemLink(owner) : "")));
    }
    return node("details", { class: "source-details" }, node("summary", {}, `ROM sources (${seen.size})`), node("div", { class: "table-wrap" }, table));
  }

  const zoidTitle = model => `${String(model).padStart(3, "0")} ${zoidName(model)}`;
  const zoidStill = model => cropped(new (A().Player)(objects, { model, slot: 0 }).image());

  function zoids() {
    clear();
    const grid = node("div", { class: "gallery" }), status = node("span", { class: "muted" });
    const models = Array.from({ length: 151 }, (_, i) => i + 1);
    content.append(panel("Zoids"), node("div", { class: "gallery-toolbar" }, status, node("div", { class: "toolbar-actions" },
      zipButton("Download all as ZIP", "Zoids Legacy Zoids.zip", models, async model => [fileName(zoidTitle(model), "png"), await pngBytes(frameCanvas(zoidStill(model)))]))), grid);
    infinite(grid, models, model => {
      const canvas = frameCanvas(zoidStill(model));
      canvas.style.maxWidth = "100%";
      grid.append(node("a", { href: `#/zoid/${model}`, class: "art-card" }, node("div", { class: "art-stage" }, canvas), node("span", { class: "art-copy" }, zoidTitle(model))));
    }, status, "Zoids");
  }

  function mountPoint(model, slot, item, side) {
    const at = 0x7ec38c + model * 32 + slot * 4;
    let x = objects.i16(at);
    const y = objects.i16(at + 2);
    if (slot === 2 && item) x = (x - objects.i16(0x7ac90c + item * 2)) << 16 >> 16;
    return { x: side ? 256 - x : x, y, at, priority: objects.u8(0x7ed68c + model * 3 + slot) };
  }

  function zoidPage(model) {
    clear();
    if (!(model >= 1 && model <= 151)) { notFound("There is no Zoid with that number."); return; }
    content.append(panel(zoidTitle(model)));
    const canvas = node("canvas", { class: "zoid-stage" }), context = canvas.getContext("2d");
    const SCREEN = { left: 0, top: 0, width: 240, height: 160 };
    let box = SCREEN, scale = 3;
    const select = (label, options, value = "0") => {
      const element = node("select", { "aria-label": label }, ...options.map(([v, text]) => node("option", { value: String(v), ...(String(v) === value ? { selected: "" } : {}) }, text)));
      return element;
    };
    const racks = [0, 1, 2].map(slot => A().rackAcceptsWeapons(objects, model, slot));
    const REASONS = { model: id => `${A().groupName(objects, id)} only`, mount: id => ["", "mount 1 only", "mounts 2 and 3 only", "mount 2 only"][A().itemMountMode(objects, id)], size: () => "needs a larger Zoid", kind: () => "parts only", smoke: () => "not on this Zoid" };
    const mounts = [0, 1, 2].map(slot => {
      const options = A().equipmentOptions(objects, slot, model), fits = options.filter(o => o.visible && o.status === "accepted");
      const option = (o, reason) => node("option", { value: String(o.id), ...(reason == null ? {} : { disabled: "" }) }, o.id ? `${o.id}: ${o.label}${reason ? ` (${reason})` : ""}` : "None");
      const element = node("select", { "aria-label": `Mount ${slot + 1}` }, ...fits.map(o => option(o)),
        node("optgroup", { label: "Not for this mount" }, ...options.filter(o => o.visible && o.status !== "accepted").map(o => option(o, REASONS[o.status](o.id)))),
        node("optgroup", { label: "No sprite: defense and command parts" }, ...options.filter(o => !o.visible).map(o => option(o, ""))));
      element.disabled = !racks[slot];
      return element;
    });
    const wide = node("p", { class: "muted" });
    const showPoints = node("input", { type: "checkbox" });
    showPoints.checked = true;
    const palette = select("Palette", Array.from({ length: 8 }, (_, i) => [i, `Palette ${i + 1}`]));
    const side = select("Side", [[0, "Original"], [1, "Mirrored"]]);
    const framing = select("Framing", [["zoid", "Zoid"], ["screen", "Battle screen"]], "zoid");
    const animation = node("select", { "aria-label": "Animation" });
    const scrub = node("input", { type: "range", min: "0", value: "0", "aria-label": "Time" }), status = node("span", { class: "frame-count" });
    const points = node("table"), sources = node("div");
    let timeline = null, update = 0, playing = false, request = 0, last = 0, elapsed = 0;
    const equipment = () => mounts.map(m => Number(m.value));
    const seconds = updates => `${(updates / FRAME_HZ).toFixed(2)} s`;
    // The first update that shows each distinct frame, in play order.
    const frameUpdates = () => { const first = new Map(); timeline.states.forEach((state, u) => { if (!first.has(state.frame)) first.set(state.frame, u); }); return [...first.values()]; };
    function frameBox() {
      if (framing.value === "screen") return SCREEN;
      let left = 240, top = 160, right = 0, bottom = 0;
      const include = (x, y) => { left = Math.min(left, x); top = Math.min(top, y); right = Math.max(right, x + 1); bottom = Math.max(bottom, y + 1); };
      for (const u of frameUpdates()) { const { pixels } = A().image(timeline, u); for (let i = 0; i < pixels.length; i++) if (pixels[i] & 0xffffff) include(i % 240, i / 240 | 0); }
      equipment().forEach((item, slot) => { if (!racks[slot]) return; const { x, y } = mountPoint(model, slot, item, Number(side.value)); include(x, y); });
      if (!right) return SCREEN;
      left = Math.max(0, left - 4); top = Math.max(0, top - 4); right = Math.min(240, right + 4); bottom = Math.min(160, bottom + 4);
      return { left, top, width: right - left, height: bottom - top };
    }
    // The framed part of one update at native size, with the black backdrop made transparent.
    function still(u) {
      const { pixels } = A().image(timeline, u), out = new Uint32Array(box.width * box.height);
      for (let y = 0; y < box.height; y++) for (let x = 0; x < box.width; x++) { const value = pixels[(box.top + y) * 240 + box.left + x]; out[y * box.width + x] = value & 0xffffff ? value : 0; }
      return frameCanvas({ width: box.width, height: box.height, pixels: out });
    }
    function drawPoints() {
      if (!showPoints.checked) return;
      equipment().forEach((item, slot) => {
        if (!racks[slot]) return;
        const point = mountPoint(model, slot, item, Number(side.value)), x = (point.x - box.left) * scale, y = (point.y - box.top) * scale, color = MOUNT_COLORS[slot];
        context.fillStyle = color;
        context.fillRect(x, y, scale, scale);
        context.strokeStyle = color; context.lineWidth = 1;
        context.strokeRect(x - 4.5, y - 4.5, scale + 8, scale + 8);
        context.font = "12px ui-monospace, monospace";
        context.fillText(String(slot + 1), x + 8, y - 6);
      });
    }
    function draw() {
      const img = A().image(timeline, update);
      context.imageSmoothingEnabled = false;
      context.clearRect(0, 0, canvas.width, canvas.height);
      context.drawImage(frameCanvas(img), box.left, box.top, box.width, box.height, 0, 0, box.width * scale, box.height * scale);
      drawPoints();
      scrub.max = String(timeline.states.length - 1);
      scrub.value = String(update);
      status.textContent = `${seconds(update)} of ${seconds(timeline.states.length - 1)}`;
    }
    function refreshPoints() {
      points.replaceChildren(node("tr", {}, node("th", {}, "Mount"), node("th", {}, "Pixel (x, y)"), node("th", {}, "Layer"), node("th", {}, "ROM")));
      equipment().forEach((item, slot) => {
        if (!racks[slot]) return;
        const { x, y, at, priority } = mountPoint(model, slot, item, Number(side.value));
        const swatch = node("span", { class: "mount-swatch" }); swatch.style.background = MOUNT_COLORS[slot];
        points.append(node("tr", {}, node("td", {}, swatch, ` ${slot + 1}`), node("td", { class: "mono" }, `${x}, ${y}`), node("td", {}, `${priority} · ${priority > 2 ? "behind the body" : "in front of the body"}`),
          node("td", {}, romLink(at + OBJ, at + OBJ + 4), slot === 2 && item ? node("span", {}, " − ", romLink(0x7ac90c + item * 2 + OBJ, 0x7ac90c + item * 2 + 2 + OBJ)) : null)));
      });
    }
    function retime() {
      stop();
      timeline = A().timeline(objects, { model, slot: Number(animation.value), side: Number(side.value), variant: Number(palette.value), equipment: equipment() });
      update = 0;
      box = frameBox();
      scale = box === SCREEN ? 3 : Math.max(2, Math.min(6, Math.floor(720 / box.width), Math.floor(560 / box.height)));
      canvas.setAttribute("width", String(box.width * scale)); canvas.setAttribute("height", String(box.height * scale));
      const moving = timeline.states.length > 1;
      playback.hidden = timeRow.hidden = framesButton.hidden = !moving;
      refreshPoints();
      sources.replaceChildren(sourceList(timeline.source.sources));
      draw();
    }
    function rebuild() {
      const rows = A().bindings(objects, model, equipment()), previous = animation.value, rear = Number(mounts[1].value);
      wide.textContent = takesBothRear(rear) ? `${weaponName(rear)} takes mounts 2 and 3.` : "";
      animation.replaceChildren(node("option", { value: "0" }, "Still (no animation)"), ...rows.filter(row => row.slot !== 0).map(row => node("option", { value: String(row.slot) }, row.label)));
      animation.value = [...animation.children].some(option => option.getAttribute?.("value") === previous || option.value === previous) ? previous : "0";
      retime();
    }
    function stop() { playing = false; cancelAnimationFrame(request); play.textContent = "Play"; }
    function tick(time) {
      if (!playing) return;
      if (last) elapsed += Math.min(time - last, 250);
      last = time;
      const period = 1000 / FRAME_HZ;
      while (elapsed >= period) {
        elapsed -= period;
        if (update + 1 < timeline.states.length) update++;
        else if (timeline.terminal === "loop") update = timeline.loop_start_update;
        else { stop(); break; }
      }
      draw();
      if (playing) request = requestAnimationFrame(tick);
    }
    const play = button("Play", () => {
      if (playing) { stop(); return; }
      if (update >= timeline.states.length - 1 && timeline.terminal === "end") update = 0;
      playing = true; play.textContent = "Pause"; last = 0; elapsed = 0; request = requestAnimationFrame(tick);
    });
    scrub.addEventListener("input", () => { stop(); update = Number(scrub.value); draw(); });
    // A mode-3 weapon on mount 2 takes mount 3 too; RunPlayerEquipmentMenu removes whichever of the two was there.
    const takesBothRear = item => item && A().itemMountMode(objects, item) === 3;
    mounts.forEach((element, slot) => element.addEventListener("change", () => {
      if (slot === 1 && takesBothRear(Number(element.value))) mounts[2].value = "0";
      if (slot === 2 && Number(element.value) && takesBothRear(Number(mounts[1].value))) mounts[1].value = "0";
      rebuild();
    }));
    for (const element of [palette, side]) element.addEventListener("change", rebuild);
    animation.addEventListener("change", retime);
    framing.addEventListener("change", retime);
    showPoints.addEventListener("change", draw);
    const playback = node("div", { class: "playback" }, play, button("Restart", () => { stop(); update = 0; draw(); }), status);
    const timeRow = node("label", {}, node("span", {}, "Time"), scrub);
    const animationName = () => animation.value === "0" ? "still" : animation.options?.[animation.selectedIndex]?.textContent || `animation ${animation.value}`;
    const framesButton = button("Download animation frames (ZIP)", async () => {
      const files = [];
      for (const [n, u] of frameUpdates().entries()) files.push([fileName(`${zoidTitle(model)} ${animationName()} frame ${String(n + 1).padStart(3, "0")}`, "png"), await pngBytes(still(u))]);
      save(zip(files), fileName(`${zoidTitle(model)} ${animationName()}`, "zip"));
    });
    const itemOf = assets.find(asset => asset.model === model);
    const controls = node("div", { class: "object-controls" },
      ...mounts.map((element, slot) => node("label", {}, node("span", {}, racks[slot] ? `Weapon on mount ${slot + 1}` : `Mount ${slot + 1}: parts only, no weapon rack`), element)), wide,
      node("label", {}, node("span", {}, "Show attachment points"), showPoints),
      node("label", {}, node("span", {}, "Animation"), animation),
      node("label", {}, node("span", {}, "Palette"), palette),
      node("label", {}, node("span", {}, "Side"), side),
      node("label", {}, node("span", {}, "Framing"), framing),
      playback, timeRow,
      node("div", { class: "detail-links" }, button("Download frame PNG", () => still(update).toBlob(blob => save(blob, fileName(`${zoidTitle(model)} ${animationName()}${timeline.states.length > 1 ? ` ${seconds(update)}` : ""}`, "png")))), framesButton),
      node("h3", {}, "Attachment points"), points,
      itemOf ? node("div", { class: "detail-links" }, link(`#/item/${itemOf.index}`, "Battle image item and ROM ranges")) : null);
    if (globalThis.ZoidsCAS?.FAMILIES.some(family => family.includes(model))) controls.append(node("div", { class: "detail-links" }, button("CAS transformation", () => { const bench = casWorkbench(model); content.append(bench); bench.scrollIntoView?.(); })));
    content.append(node("div", { class: "workbench" }, node("div", { class: "object-stage" }, canvas), controls), sources);
    rebuild();
  }

  function casWorkbench(model) {
    const CAS = globalThis.ZoidsCAS, family = CAS.FAMILIES.find(models => models.includes(model));
    const canvas = node("canvas", { width: 240, height: 160, class: "zoid-stage" }), context = canvas.getContext("2d");
    canvas.style.width = "720px";
    const target = node("select", { "aria-label": "Transform into" }, ...family.filter(m => m !== model).map(m => node("option", { value: String(m) }, zoidName(m))));
    const side = node("select", { "aria-label": "Side" }, node("option", { value: "0" }, "Original"), node("option", { value: "1" }, "Mirrored"));
    const palette = node("select", { "aria-label": "Palette" }, ...Array.from({ length: 8 }, (_, i) => node("option", { value: String(i) }, `Palette ${i + 1}`)));
    const slot = node("select", { "aria-label": "Battle slot" }, ...Array.from({ length: 6 }, (_, i) => node("option", { value: String(i) }, `Slot ${i + 1}`)));
    const scrub = node("input", { type: "range", min: "0", max: "689", value: "0", "aria-label": "CAS frame" }), status = node("span", { class: "frame-count" }), sources = node("div");
    let scene, frame, skipFrame = null, playing = false, request = 0, last = 0, elapsed = 0;
    const parameters = () => ({ source: model, target: Number(target.value), side: Number(side.value), variant: Number(palette.value), slot: Number(slot.value), skipFrame });
    function draw() {
      const img = CAS.image(frame);
      context.putImageData(new ImageData(new Uint8ClampedArray(img.pixels.buffer), 240, 160), 0, 0);
      scrub.max = String(scene.frameCount - 1); scrub.value = String(frame.display_frame);
      status.textContent = `frame ${frame.display_frame + 1} / ${scene.frameCount}`;
    }
    function seek(index) {
      if (!scene || index < frame.display_frame) { scene = new CAS.CasScene(objects, parameters()); frame = scene.nextFrame(); sources.replaceChildren(sourceList(scene.sourceTrace().sources)); }
      while (frame.display_frame < index && !frame.done) frame = scene.nextFrame();
      draw();
    }
    function stop() { playing = false; cancelAnimationFrame(request); play.textContent = "Play"; }
    function tick(time) {
      if (!playing) return;
      if (last) elapsed += Math.min(time - last, 250);
      last = time;
      while (elapsed >= 1000 / FRAME_HZ) { elapsed -= 1000 / FRAME_HZ; if (frame.done) { stop(); break; } frame = scene.nextFrame(); }
      draw();
      if (playing) request = requestAnimationFrame(tick);
    }
    const play = button("Play", () => { if (playing) { stop(); return; } if (frame.done) { scene = null; seek(0); } playing = true; play.textContent = "Pause"; last = 0; elapsed = 0; request = requestAnimationFrame(tick); });
    const reset = () => { stop(); skipFrame = null; scene = null; seek(0); };
    for (const element of [target, side, palette, slot]) element.addEventListener("change", reset);
    scrub.addEventListener("input", () => { stop(); seek(Number(scrub.value)); });
    const skip = button("Skip (B)", () => { if (scene.requestSkip()) { skipFrame = scene.skipFrame; draw(); } });
    reset();
    return node("section", { class: "panel" }, node("div", { class: "panel-heading" }, node("h2", {}, "CAS transformation")),
      node("div", { class: "workbench" }, node("div", { class: "object-stage" }, canvas), node("div", { class: "object-controls" },
        node("label", {}, node("span", {}, "Transform into"), target), node("label", {}, node("span", {}, "Side"), side),
        node("label", {}, node("span", {}, "Palette"), palette), node("label", {}, node("span", {}, "Battle slot"), slot),
        node("div", { class: "playback" }, play, button("Restart", reset), skip, status), node("label", {}, node("span", {}, "Frame"), scrub))), sources);
  }

  // Each mountable weapon's sprite (front: mount 1; rear: mounts 2 and 3) from the mounted-graphics and sprite-definition tables.
  function equipmentEntries() {
    const out = [];
    for (let item = 1; item <= 100; item++) for (const rear of [0, 1]) {
      const selector = item * 2 + rear, graphics = 0x7abc6c + selector * 8, definition = 0x7ac2bc + selector * 8;
      if (![graphics, graphics + 4, definition, definition + 4].every(at => objects.u32(at))) continue;
      out.push({ item, rear, graphics, definition });
    }
    return out;
  }

  function equipmentSprite({ graphics, definition }) {
    const record = objects.sprite({ record: definition }), tiles = objects.lz(objects.pointer(graphics)), pram = new Uint8Array(0x200);
    pram.set(objects.lz(objects.pointer(graphics + 4)).subarray(0, 0x200));
    const frames = record.frames.map(frame => frame.pieces.map(piece => ({ tile: piece.tile, x: piece.x, y: piece.y, width: piece.width, height: piece.height, flips: piece.flags & 3, color256: !!(piece.tail & 0x2000) })));
    return { kind: "sprite", frames: D.spritePixels(frames, 0, 0, tiles), pram, animations: record.animations.map(animation => animation.steps.map(step => ({ frame: step.frame, duration: step.duration_updates }))) };
  }

  function equipmentList() {
    clear();
    const grid = node("div", { class: "gallery" }), status = node("span", { class: "muted" }), entries = equipmentEntries();
    const label = entry => `${weaponName(entry.item)} · ${entry.rear ? "rear" : "front"}`;
    content.append(panel("Equipment"), node("div", { class: "gallery-toolbar" }, status, node("div", { class: "toolbar-actions" }, motionButton(),
      zipButton("Download all as ZIP", "Zoids Legacy equipment.zip", entries, async entry => { const sprite = equipmentSprite(entry); return [fileName(label(entry), "png"), await pngBytes(canvasOf(D.spriteSheet(sprite.frames, sprite.pram)))]; }))), grid);
    infinite(grid, entries, entry => {
      const canvas = node("canvas");
      animate(canvas, equipmentSprite(entry));
      fitStage(canvas);
      const tiles = findItem("lz77", objects.pointer(entry.graphics) + OBJ);
      grid.append(node(tiles != null ? "a" : "div", { ...(tiles != null ? { href: `#/item/${tiles}` } : {}), class: "art-card" }, node("div", { class: "art-stage" }, canvas),
        node("span", { class: "art-copy" }, label(entry))));
    }, status, "weapon sprites");
  }

  // ---------- maps ----------
  async function maps(selected) {
    clear();
    const list = (kindItems.get(plan.kinds.indexOf("field_map")) || []).filter(index => plan.items[index][6].some(view => view.t === "map"));
    if (!list.length) { content.append(node("p", { class: "empty" }, "No maps in this plan.")); return; }
    const index = list.includes(selected) ? selected : list[0], info = item(index);
    const mapView = info.views.find(view => view.t === "map"), id = mapView.map;
    const layerViews = info.views.map((view, v) => [view, v]).filter(([view]) => view.t === "layer");
    const page = generation;
    content.append(node("p", { class: "muted" }, "Loading the map..."));
    const results = await decodedViews(index);
    if (page !== generation) return;
    content.replaceChildren();
    const collision = results[info.views.indexOf(mapView)];
    const layerImages = new Map(layerViews.map(([view, v]) => [view.name, { view, result: results[v], entries: D.u16s(D.source(rom, view.entries)) }]));
    const names = node("select", { "aria-label": "Map" }, ...list.map(i => {
      const mapId = plan.items[i][6].find(view => view.t === "map").map;
      return node("option", { value: String(i), ...(i === index ? { selected: "" } : {}) }, `${String(mapId).padStart(3, "0")} ${mapLabel(mapId)}`);
    }));
    names.addEventListener("change", () => { location.hash = `#/maps/${names.value}`; });

    const viewport = node("div", { class: "map-viewport", tabindex: "0", "aria-label": "Map. Drag or use the arrow keys to pan; wheel or + and - to zoom." });
    const canvas = node("canvas", { class: "map-canvas" }), context = canvas.getContext("2d");
    const highlight = node("div", { class: "map-cell-highlight" }), tooltip = node("div", { class: "map-tooltip" });
    highlight.hidden = tooltip.hidden = true;
    viewport.append(canvas, highlight, tooltip);
    const information = node("span"), coordinates = node("span");
    const details = node("dl", { class: "map-cell-info" }, node("dt", {}, "Cell details"), node("dd", {}, "Hover over a cell, or click it, for details."));

    // Bottom to top as the field stacks them: BG0 and BG2 at priority 3 under BG1 and BG3 at priority 2, the lower number on top.
    const order = ["bg2", "bg0", "bg3", "bg1"].filter(name => layerImages.has(name)), worldLike = id === 0 || id === 64;
    const toggles = new Map(order.map(name => {
      const input = node("input", { type: "checkbox" });
      input.checked = !(name === "bg1" && (id === 0 || id === 64));
      input.addEventListener("change", () => draw());
      return [name, input];
    }));
    const showCollision = node("input", { type: "checkbox" });
    const actor = node("select", { "aria-label": "Collision actor" }, node("option", { value: "player" }, "Player"), node("option", { value: "npc" }, "NPC"));
    const model = node("select", { "aria-label": "Terrain model" }, ...[[0x69, "Model 0x69"], [0x6a, "Model 0x6A"], [0x6b, "Model 0x6B"], [0, "Other models"]].map(([value, text]) => node("option", { value: String(value) }, text)));
    const conditional = node("input", { type: "checkbox" });
    for (const input of [showCollision, actor, model, conditional]) input.addEventListener("change", () => draw());
    const settings = () => ({ model: Number(model.value), conditional: conditional.checked, npc: actor.value === "npc" });

    let scale = 1, panX = 0, panY = 0, last = null;
    const size = () => [viewport.clientWidth || 960, viewport.clientHeight || 640];
    function position() {
      canvas.style.transform = `translate(${panX}px, ${panY}px) scale(${scale})`;
      information.textContent = `${canvas.width} × ${canvas.height} px · ${Math.round(scale * 100)}%`;
      if (last) inspect(last);
    }
    function fit() { const [w, h] = size(); scale = Math.min(w / canvas.width, h / canvas.height); panX = (w - canvas.width * scale) / 2; panY = (h - canvas.height * scale) / 2; position(); }
    function zoom(factor, x = size()[0] / 2, y = size()[1] / 2) { const next = Math.max(1 / 64, Math.min(16, scale * factor)); panX = x - (x - panX) * next / scale; panY = y - (y - panY) * next / scale; scale = next; position(); }

    const base = layerImages.get("bg0") || layerImages.get(order[order.length - 1]);
    canvas.width = base.result.image.width; canvas.height = base.result.image.height;
    const backdrop = "rgb(0,0,0)";
    const layerCanvas = new Map([...layerImages].map(([name, layer]) => [name, canvasOf(layer.result.image)]));
    // A first-target layer (the clouds, or the world overlay) over the layers below it, alpha-blended 10/12 like
    // UpdateFieldDisplay's BLDCNT 0x1542 | 0x0808; `at` places a non-repeating layer, otherwise it repeats.
    function blendLayer(top, at, topName) {
      const [left, top0, width, height] = at ? [at[0], at[1], Math.min(top.width, canvas.width - at[0]), Math.min(top.height, canvas.height - at[1])] : [0, 0, canvas.width, canvas.height];
      const below = context.getImageData(left, top0, width, height), out = below.data;
      const lower = order.slice(0, order.indexOf(topName)).filter(name => toggles.get(name).checked).map(name => ({ image: layerImages.get(name).result.image, at: id === 0 && name === "bg3" ? WORLD_OVERLAY : null }));
      const covered = (x, y) => lower.some(({ image, at }) => {
        const lx = at ? x - at[0] : x % image.width, ly = at ? y - at[1] : y % image.height;
        return lx >= 0 && ly >= 0 && lx < image.width && ly < image.height && image.rgba[(ly * image.width + lx) * 4 + 3];
      });
      for (let y = top0; y < top0 + height; y++) for (let x = left; x < left + width; x++) {
        const from = at ? ((y - top0) * top.width + x - left) * 4 : ((y % top.height) * top.width + x % top.width) * 4;
        if (!top.rgba[from + 3]) continue;
        const to = ((y - top0) * width + x - left) * 4, blend = covered(x, y);
        for (let k = 0; k < 3; k++) {
          const a = top.rgba[from + k] >> 3, b = out[to + k] >> 3, c = blend ? Math.min(31, (a * 10 + b * 12) >> 4) : a;
          out[to + k] = (c << 3) | (c >> 2);
        }
      }
      context.putImageData(below, left, top0);
    }
    function draw(reset = false) {
      context.fillStyle = backdrop;
      context.fillRect(0, 0, canvas.width, canvas.height);
      for (const name of order) {
        if (!toggles.get(name).checked) continue;
        const layer = layerCanvas.get(name);
        if (id === 0 && name === "bg3") blendLayer(layerImages.get(name).result.image, WORLD_OVERLAY, name);
        else if (worldLike && name === "bg1") blendLayer(layerImages.get(name).result.image, null, name);
        else if (layer.width >= canvas.width && layer.height >= canvas.height) context.drawImage(layer, 0, 0);
        else { context.fillStyle = context.createPattern(layer, "repeat"); context.fillRect(0, 0, canvas.width, canvas.height); }
      }
      if (showCollision.checked) {
        const options = settings(), cell = mapView.cell;
        context.fillStyle = "rgba(230, 70, 60, 0.45)";
        for (let y = 0; y < mapView.rows; y++) for (let x = 0; x < mapView.columns; x++) {
          if (D.cellBlocked(mapView, D.collisionCell(mapView, collision.cells, x, y) ?? 0xff, options)) context.fillRect(x * cell, y * cell, cell, cell);
        }
      }
      actorLabel.hidden = !showCollision.checked || mapView.packed;
      modelLabel.hidden = conditionalLabel.hidden = !showCollision.checked || !mapView.packed;
      if (reset) fit(); else position();
    }

    function inspect(point) {
      last = point;
      const x = Math.floor((point.x - panX) / scale), y = Math.floor((point.y - panY) / scale);
      if (x < 0 || y < 0 || x >= canvas.width || y >= canvas.height) { highlight.hidden = tooltip.hidden = true; coordinates.textContent = ""; return; }
      const cellX = Math.floor(x / mapView.cell), cellY = Math.floor(y / mapView.cell);
      const value = D.collisionCell(mapView, collision.cells, cellX, cellY), options = settings();
      const blocked = value === undefined || D.cellBlocked(mapView, value, options);
      const who = mapView.packed ? (options.model ? `model 0x${options.model.toString(16).toUpperCase()}` : "other models") : options.npc ? "NPCs" : "the player";
      coordinates.textContent = `Pixel ${x}, ${y} · tile ${x >> 3}, ${y >> 3} · cell ${cellX}, ${cellY}`;
      Object.assign(highlight.style, { left: `${panX + cellX * mapView.cell * scale}px`, top: `${panY + cellY * mapView.cell * scale}px`, width: `${mapView.cell * scale}px`, height: `${mapView.cell * scale}px` });
      highlight.hidden = false;
      tooltip.hidden = !!point.touch;
      tooltip.textContent = `Cell ${cellX}, ${cellY}\nRaw ${value === undefined ? "outside the decoded cells" : hex(value, 2)} · ${blocked ? "Blocked" : "Clear"} for ${who}`;
      tooltip.style.left = `${Math.max(4, Math.min(point.x + 14, size()[0] - 300))}px`;
      tooltip.style.top = `${Math.max(4, Math.min(point.y + 18, size()[1] - 58))}px`;
      const offset = mapView.packed ? (cellX & 0xff) + (((cellY & 0xff) * mapView.stride) >> 1) : cellX + mapView.columns * cellY;
      const rows = [
        ["Position", `Pixel ${x}, ${y} · tile ${x >> 3}, ${y >> 3}`],
        ["Collision cell", `${cellX}, ${cellY} · ${mapView.cell} × ${mapView.cell} px · byte +${hex(offset, 4)}`],
        ["Raw byte", value === undefined ? "outside the decoded cells" : `${hex(value, 2)} · ${value.toString(2).padStart(8, "0")}`],
        ["Result", `${blocked ? "Blocked" : "Clear"} for ${who}`],
      ];
      if (value !== undefined) {
        if (mapView.packed) rows.push(["Terrain", `type ${value & 0x1f} · bit 0x40 ${value & 0x40 ? "set: no terrain collision" : "clear"} · conditional bit 0x20 ${value & 0x20 ? "set" : "clear"}`]);
        else rows.push(["Flags", `0x80 blocks the player and NPCs: ${value & 0x80 ? "set" : "clear"} · 0x40 blocks NPCs: ${value & 0x40 ? "set" : "clear"} · low five bits ${value & 0x1f}`]);
      }
      if (value !== undefined) {
        const battleTerrain = value & 0x1f, encounter = id === 0 ? BF().worldEncounter(objects, x >> 4, y >> 4, canvas.width >> 3) : BF().mapEncounter(objects, id);
        rows.push(["Battle terrain", `${battleTerrain}: ${terrainLabel(battleTerrain)}`]);
        rows.push(["Random battles", value & 0x40 ? "none on this cell (bit 0x40 set)" : !encounter.group ? "none on this map" :
          node("span", {}, `group ${encounter.group}, threshold ${encounter.threshold} of 1,000 per roll · `, link(`#/battle/${battleTerrain}/${encounter.group}/-/${id}/${cellX}/${cellY}`, "Open on the battle field"))]);
      }
      rows.push(["Collision source", mapView.collision[0] === "lz77" ? `LZ77 ${hex(mapView.collision[1])}, decoded byte +${hex(offset, 4)}` : `ROM ${hex(mapView.collision[1] + offset)}`]);
      for (const name of [...order].reverse()) {
        const layer = layerImages.get(name), columns = layer.view.columns, tx = (x >> 3) % columns, ty = (y >> 3) % layer.view.rows, word = layer.entries[ty * columns + tx];
        if (word !== undefined) rows.push([`Layer ${name}${toggles.get(name).checked ? "" : " (hidden)"}`, `tile ${word & 0x3ff} · palette ${word >> 12} · flip X ${word & 0x400 ? "yes" : "no"}, Y ${word & 0x800 ? "yes" : "no"} · entry ${hex(word, 4)}`]);
      }
      details.replaceChildren(...rows.flatMap(([key, value]) => [node("dt", {}, key), node("dd", {}, value)]));
    }

    const pointers = new Map();
    const local = event => { const box = viewport.getBoundingClientRect(); return { x: event.clientX - box.left, y: event.clientY - box.top }; };
    viewport.addEventListener("pointerdown", event => {
      if (event.pointerType === "mouse" && event.button !== 0) return;
      viewport.setPointerCapture?.(event.pointerId);
      const point = { ...local(event), touch: event.pointerType === "touch" };
      pointers.set(event.pointerId, point); viewport.classList.add("panning"); inspect(point);
    });
    viewport.addEventListener("pointermove", event => {
      const point = { ...local(event), touch: event.pointerType === "touch" }, previous = pointers.get(event.pointerId);
      if (previous && pointers.size === 1) { panX += point.x - previous.x; panY += point.y - previous.y; pointers.set(event.pointerId, point); position(); }
      else if (!previous) inspect(point);
    });
    const release = event => { pointers.delete(event.pointerId); if (!pointers.size) viewport.classList.remove("panning"); };
    viewport.addEventListener("pointerup", release); viewport.addEventListener("pointercancel", release);
    viewport.addEventListener("pointerleave", () => { if (!pointers.size) { highlight.hidden = tooltip.hidden = true; } });
    viewport.addEventListener("wheel", event => { event.preventDefault(); const point = local(event); zoom(event.deltaY < 0 ? 1.25 : 0.8, point.x, point.y); }, { passive: false });
    const PAN = { ArrowLeft: [1, 0], ArrowRight: [-1, 0], ArrowUp: [0, 1], ArrowDown: [0, -1] };
    viewport.addEventListener("keydown", event => {
      if (event.key === "+" || event.key === "=") zoom(2);
      else if (event.key === "-") zoom(0.5);
      else if (PAN[event.key]) {
        event.preventDefault();
        const [dx, dy] = PAN[event.key], [w, h] = size(), step = event.shiftKey ? 256 : 64;
        panX += dx * step; panY += dy * step;
        last = { x: w / 2, y: h / 2, touch: true };
        position();
      }
    });

    const label = (input, text) => node("label", {}, input, node("span", {}, text));
    const actorLabel = node("label", {}, node("span", {}, "Collision actor"), actor);
    const modelLabel = node("label", {}, node("span", {}, "Terrain actor"), model);
    const conditionalLabel = label(conditional, "Conditional collision (flag 0x04)");
    const zoomOut = button("−", () => zoom(0.5)), zoomIn = button("+", () => zoom(2));
    zoomOut.setAttribute("aria-label", "Zoom out"); zoomIn.setAttribute("aria-label", "Zoom in");
    const toolbar = node("div", { class: "map-toolbar" }, names, zoomOut, zoomIn, button("Fit", fit), button("1:1", () => zoom(1 / scale)),
      ...order.map(name => label(toggles.get(name), name === "bg3" && id === 0 ? "Overlay (BG3)" : `Layer ${name.toUpperCase()}`)), label(showCollision, "Collision"), actorLabel, modelLabel, conditionalLabel,
      button("Save view PNG", () => canvas.toBlob(blob => save(blob, fileName(`${String(id).padStart(3, "0")} ${mapLabel(id)}`, "png")))));
    content.append(toolbar, viewport, node("div", { class: "map-status" }, information, coordinates, checkBadge(collision.check)), details,
      node("p", { class: "muted" }, "Sources ", itemLink(index), ", ", ...sourceLinks({ tiles: mapView.collision })));
    draw(true);
  }

  // ---------- battle field ----------
  const BF = () => globalThis.ZoidsBattleField;
  const BATTLE_JINGLE = 82, TERRAINS = 24, GROUPS = 21, FIELD_HZ = FRAME_HZ / 2;
  const CAMERAS = [["intro", "Intro (enemy side, flying in)"], ["overview", "Overview"], ["player-near", "Player side"], ["enemy-near", "Enemy side"], ["player-wide", "Player side, wide"], ["enemy-wide", "Enemy side, wide"], ["player-far", "Player side, far"], ["enemy-far", "Enemy side, far"]];
  const slotLabel = (side, unit) => `${unit < 3 ? "Front line" : "Back line"}, ${(side ? ["near", "middle", "far"] : ["far", "middle", "near"])[unit % 3]} lane`;

  // Where each encounter group can start: world map cells (by battle terrain) and the maps whose encounter record names it.
  let groupPlaces = null;
  function encounterPlaces() {
    if (groupPlaces) return groupPlaces;
    groupPlaces = Array.from({ length: GROUPS }, () => ({ worldCells: 0, maps: [] }));
    for (let y = 0; y < 256; y++) for (let x = 0; x < 256; x++) { const { group } = BF().worldEncounter(objects, x, y, 512); if (group < GROUPS) groupPlaces[group].worldCells++; }
    for (const index of kindItems.get(plan.kinds.indexOf("field_map")) || []) {
      const view = plan.items[index][6].find(entry => entry.t === "map");
      if (!view || view.map === 0) continue;
      const { group, matched } = BF().mapEncounter(objects, view.map);
      if (matched && group && group < GROUPS) groupPlaces[group].maps.push([view.map, index]);
    }
    return groupPlaces;
  }
  // A battle's terrain: a script battle's own (EventStartBattle), else the most likely player cell value & 0x1F for the group.
  let battleDefaults = null;
  async function battleTerrainDefaults() {
    if (battleDefaults) return battleDefaults;
    const counts = Array.from({ length: GROUPS }, () => new Map()), cells = Array.from({ length: GROUPS }, () => new Map());
    const add = (view, group, value, weight, x, y) => {
      if (!group || group >= GROUPS || !weight || value === undefined || value & 0x40 || D.cellBlocked(view, value)) return;
      const terrain = value & 0x1f, best = cells[group].get(terrain);
      counts[group].set(terrain, (counts[group].get(terrain) || 0) + weight);
      if (!best || weight > best.weight) cells[group].set(terrain, { map: view.map, x, y, weight, transports: TRANSPORTS.filter(([model]) => !D.cellBlocked(view, value, { model })).map(([model]) => model) });
    };
    for (const index of kindItems.get(plan.kinds.indexOf("field_map")) || []) {
      const view = plan.items[index][6].find(entry => entry.t === "map");
      if (!view) continue;
      const encounter = view.map === 0 ? null : BF().mapEncounter(objects, view.map);
      if (encounter && !(encounter.matched && encounter.group)) continue;
      const decoded = (await D.render(rom, plan.items[index][1], view)).cells;
      if (view.map === 0) for (let y = 0; y < 256; y++) for (let x = 0; x < 256; x++) { const cell = BF().worldEncounter(objects, x, y, 512); add(view, cell.group, D.collisionCell(view, decoded, x, y), cell.threshold, x, y); }
      else for (let y = 0; y < view.rows; y++) for (let x = 0; x < view.columns; x++) add(view, encounter.group, D.collisionCell(view, decoded, x, y), encounter.threshold, x, y);
    }
    const formations = tableOf("table.encounter_formations"), scripts = new Map();
    for (const battle of formations != null ? plan.items[findItem("table.encounter_formations", formations)][6].find(view => view.t === "script_battles")?.battles || [] : []) {
      const key = `${battle.group}/${battle.formation}/${battle.terrain}`, entry = scripts.get(key) || { group: battle.group, formation: battle.formation, terrain: battle.terrain, maps: new Set(), commands: [], field: battle.field };
      battle.maps.forEach(map => entry.maps.add(map)); entry.commands.push(battle.at); scripts.set(key, entry);
    }
    battleDefaults = { byGroup: counts.map(map => [...map].sort((a, b) => b[1] - a[1])), cells, scripts: [...scripts.values()].map(entry => ({ ...entry, maps: [...entry.maps] })) };
    return battleDefaults;
  }
  // ---------- the field a battle starts from ----------
  const TRANSPORTS = [[0x69, "Gustav"], [0x6a, "Hover Cargo"], [0x6b, "Dragoon Nest"]], ZERU = 1, FACING_DOWN = 4;
  const ACTOR_SPRITES = 0x087ad208, MAP_DEFINITIONS = 0x087c4434;
  const FRAMES_FIXED = [0x0827a1bc, 0x0827a1e4], FRAMES_TWO_VIEW = 0x0827a224, FRAMES_EIGHT_VIEW = [0x08279a64, 0x0827a0c4], FRAMES_IDLE_MOVING = 0x0827a28c;
  let actorSpriteViews = null;
  function actorSpriteView(model) {
    if (!actorSpriteViews) {
      actorSpriteViews = new Map();
      plan.items.forEach((entry, index) => entry[6].forEach((view, v) => {
        if (view.t !== "sprite") return;
        for (const site of view.site || []) { const m = /^0x087AD208\[(\d+)\]$/.exec(site); if (m && !actorSpriteViews.has(Number(m[1]))) actorSpriteViews.set(Number(m[1]), [index, v]); }
      }));
    }
    return actorSpriteViews.get(model);
  }
  // GetFieldActorAnimationIndex for a standing actor.
  function actorAnimation(model, direction) {
    const frameTable = objects.u32(ACTOR_SPRITES - BASE + model * 16), table = at => rom[at - BASE + (direction & 7)];
    if (FRAMES_FIXED.includes(frameTable)) return 0;
    if (frameTable === FRAMES_TWO_VIEW) return table(0x087a1be8);
    if (FRAMES_EIGHT_VIEW.includes(frameTable)) return table(0x087a1bf8) + 4;
    if (frameTable === FRAMES_IDLE_MOVING) return table(0x087a1c00);
    return table(0x087a1bf0) + 4;
  }
  const expandColor = value => [0, 5, 10].map(shift => { const v = value >> shift & 31; return (v << 3) | (v >> 2); });
  const rgbaWord = ([r, g, b]) => (r | g << 8 | b << 16 | 0xff000000) >>> 0;
  // Field layers, priorities and blend as InitializeFieldMapGraphics and UpdateFieldDisplay set them; GetFieldBackgroundTile places the BG3 overlay.
  const WORLD_OVERLAY = [0x16c * 8, 0x104 * 8], CROP = [240 + 128, 160 + 128];
  const DECORATIONS = [0x087afbb4, 42], ALTERNATE_DECORATIONS = [0x087afcb0, 3], DECORATION_RESOURCES = 0x087afb54, DECORATION_FRAMES = 0x0842558c, DECORATION_ANIMATIONS = 0x08425598;
  function crop(image, left, top, wrap) {
    const [width, height] = CROP, rgba = new Uint8ClampedArray(width * height * 4);
    for (let y = 0; y < height; y++) for (let x = 0; x < width; x++) {
      let sx = left + x, sy = top + y;
      if (wrap) { sx = ((sx % image.width) + image.width) % image.width; sy = ((sy % image.height) + image.height) % image.height; }
      else if (sx < 0 || sy < 0 || sx >= image.width || sy >= image.height) continue;
      const from = (sy * image.width + sx) * 4;
      rgba.set(image.rgba.subarray(from, from + 4), (y * width + x) * 4);
    }
    return { width, height, rgba };
  }
  const spriteFrame = (frame, pram) => {
    const rgba = new Uint8ClampedArray(Math.max(1, frame.width * frame.height) * 4);
    frame.pixels.forEach((color, i) => { if (color) rgba.set([...expandColor(pram[color * 2] | pram[color * 2 + 1] << 8), 255], i * 4); });
    return { width: Math.max(1, frame.width), height: Math.max(1, frame.height), left: frame.left, top: frame.top, rgba };
  };
  // A sprite's frames and one animation's steps, with the frames renumbered to the ones the animation uses.
  function spriteAnimation(frames, pram, steps) {
    const used = [...new Set(steps.map(step => step.frame))];
    return { frames: used.map(index => spriteFrame(frames[index], pram)), steps: steps.map(step => ({ frame: used.indexOf(step.frame), duration: step.duration })) };
  }
  async function actorSprite(actor) {
    const found = actorSpriteView(actor.model);
    if (!found) return null;
    const sprite = (await decodedViews(found[0]))[found[1]];
    const steps = sprite.frames && sprite.animations?.[actorAnimation(actor.model, actor.direction)];
    if (!steps?.length) return null;
    return { x: actor.x, y: actor.y, priority: 3, loop: true, ...spriteAnimation(sprite.frames, sprite.pram, steps) };
  }
  function decorationSprites(map) {
    const [table, count] = map === 0 ? DECORATIONS : ALTERNATE_DECORATIONS, isPointer = value => value >= BASE && value < BASE + rom.length;
    let frameCount = 0;
    while (isPointer(objects.u32(DECORATION_FRAMES - BASE + frameCount * 4))) frameCount++;
    const frames = D.spriteFrames(rom, { frames: DECORATION_FRAMES, count: frameCount }), steps = D.spriteAnimations(rom, { animations: DECORATION_ANIMATIONS, animation_count: 1 })[0] || [];
    return Array.from({ length: count }, (_, i) => {
      const at = table - BASE + i * 6, type = objects.u16(at), tileX = objects.i16(at + 2), tileY = objects.i16(at + 4);
      const graphics = rom.subarray(objects.u32(DECORATION_RESOURCES - BASE + type * 8) - BASE, objects.u32(DECORATION_RESOURCES - BASE + type * 8) - BASE + 0x200);
      const pram = new Uint8Array(0x200); pram.set(rom.subarray(objects.u32(DECORATION_RESOURCES - BASE + type * 8 + 4) - BASE, objects.u32(DECORATION_RESOURCES - BASE + type * 8 + 4) - BASE + 32));
      const pixels = D.spritePixels(frames, 0, 0, graphics);
      return { x: tileX * 8, y: tileY * 8, priority: 3, hold: true, decoration: true, tileX, tileY, ...spriteAnimation(pixels, pram, steps) };
    });
  }
  // The engine spec of the field a battle starts from (FieldStart in battle-field.js).
  async function fieldStartSpec(start, overlay) {
    const map = start.map, index = (kindItems.get(plan.kinds.indexOf("field_map")) || []).find(i => plan.items[i][6].some(view => view.t === "map" && view.map === map));
    if (index == null) throw Error(`map ${map} is not in this plan`);
    const info = item(index), results = await decodedViews(index);
    const image = name => { const v = info.views.findIndex(view => view.t === "layer" && view.name === name); return v < 0 ? null : results[v].image || null; };
    const world = map === 0, worldLike = map === 0 || map === 64;
    const widthTiles = objects.u16(MAP_DEFINITIONS - BASE + map * 32), heightTiles = objects.u16(MAP_DEFINITIONS - BASE + map * 32 + 2);
    const [focusX, focusY] = start.focus, left = Math.floor(focusX) - CROP[0] / 2, top = Math.floor(focusY) - CROP[1] / 2;
    const layers = [], bg0 = image("bg0"), bg1 = image("bg1");
    if (bg0) layers.push({ index: 0, role: 0, priority: 3, image: crop(bg0, left, top, world), left: world ? ((left % bg0.width) + bg0.width) % bg0.width : left, top: world ? ((top % bg0.height) + bg0.height) % bg0.height : top, wrapWidth: world ? bg0.width : 0, wrapHeight: world ? bg0.height : 0 });
    if (worldLike && bg1) layers.push({ index: 1, role: 2, priority: 2, image: bg1, wrapWidth: bg1.width, wrapHeight: bg1.height });
    else if (bg1) layers.push({ index: 1, role: 1, priority: 2, image: crop(bg1, left, top, false), left, top });
    if (world && image("bg2")) layers.push({ index: 2, role: 3, priority: 3, image: image("bg2"), wrapWidth: image("bg2").width, wrapHeight: image("bg2").height });
    if (world && overlay && image("bg3")) layers.push({ index: 3, role: 0, priority: 2, image: image("bg3"), left: WORLD_OVERLAY[0], top: WORLD_OVERLAY[1], wrapWidth: bg0.width, wrapHeight: bg0.height });
    const withOverlay = world && overlay && image("bg3");
    const blend = worldLike ? { first: 0b10 | (withOverlay ? 0b1000 : 0), second: 0b10101 | (withOverlay ? 0b1000 : 0), eva: 10, evb: 12 } : null;
    const actors = [];
    for (const actor of [...start.actors].sort((a, b) => b.y - a.y || a.id - b.id)) { const sprite = await actorSprite(actor); if (sprite) actors.push(sprite); }
    return { world, clouds: worldLike, sea: world, widthTiles, heightTiles, bg0Tilemap: !!bg0, bg1Tilemap: !worldLike && !!bg1, follow: start.follow, backdrop: rgbaWord([0, 0, 0]),
      layers, blend, player: { x: start.from[0], y: start.from[1] }, sprites: [...actors, ...(worldLike ? decorationSprites(map) : [])] };
  }
  // Where a battle starts: a script battle's replayed scene, else the player walking onto the group's most likely cell.
  const FIELD_WALK = 300, DIRECTIONS = ["up", "up and right", "right", "down and right", "down", "down and left", "left", "up and left"];
  const directionVector = direction => [objects.i32(0x087a1b98 - BASE + direction * 8), objects.i32(0x087a1b98 - BASE + direction * 8 + 4)];
  function battleStart(defaults, state, script, choice) {
    if (script?.field) {
      const field = script.field, map = field.map ?? script.maps[0] ?? 0, cell = map === 0 ? 16 : 8;
      const actors = field.actors.map(([id, model, x, y, direction]) => ({ id, model, x, y, direction }));
      const find = id => actors.find(actor => actor.id === id);
      let player = find(0);
      if (!player) {
        const near = field.trigger ? [(field.trigger[0] + field.trigger[2]) >> 1, (field.trigger[1] + field.trigger[3]) >> 1] : find(field.talked_to) ? [find(field.talked_to).x, find(field.talked_to).y + cell] : null;
        if (near) { player = { id: 0, model: map === 0 ? choice.transport : ZERU, x: near[0], y: near[1], direction: choice.direction }; actors.push(player); }
      }
      const followed = find(field.focus) || (field.center ? { x: field.center[0], y: field.center[1] } : player || actors[0] || { x: 0, y: 0 });
      const conceal = field.conceal?.[0] === "CONCEAL_FIELD_WITH_SCALED_Z" ? "z" : field.conceal?.[0] === "FADE_SCREEN_TO_BLACK" ? "fade" : field.conceal?.[0] === "CONCEAL_FIELD_WITH_DITHER" ? "dither" : "cut";
      return { map, focus: [followed.x, followed.y], from: [followed.x << 8, followed.y << 8], velocity: [0, 0], follow: false, actors, conceal, duration: field.conceal?.[2] || 16, jingle: field.song === BATTLE_JINGLE,
        place: `${mapLabel(map)}, from the event script at ${field.conceal?.[1] || "?"}` };
    }
    const place = state.place || defaults.cells[state.group].get(state.terrain) || [...defaults.cells[state.group].values()].sort((a, b) => b.weight - a.weight)[0];
    if (!place) return null;
    const cell = place.map === 0 ? 16 : 8, x = place.x * cell + cell / 2, y = place.y * cell + cell / 2;
    const model = place.transports && !place.transports.includes(choice.transport) && place.transports.length ? place.transports[0] : choice.transport;
    const [vx, vy] = directionVector(choice.direction).map(v => v * choice.speed);
    return { map: place.map, focus: [x, y], from: [(x << 8) - vx * FIELD_WALK, (y << 8) - vy * FIELD_WALK], velocity: [vx, vy], follow: true,
      actors: [{ id: 0, model, x, y, direction: choice.direction }], conceal: "z", jingle: true,
      place: `${mapLabel(place.map)}, cell ${place.x}, ${place.y}, in the ${TRANSPORTS.find(([m]) => m === model)?.[1] || "transport"}, ${choice.speed > 1 ? "running" : "driving"} ${DIRECTIONS[choice.direction]}` };
  }
  const formationLabel = encounter => encounter.candidate ? encounter.units.filter(Boolean).map(unit => zoidName(unit.zoid)).join(", ") : "empty";

  async function battlePage(terrainArg, groupArg, formationArg, placeArg) {
    clear();
    const page = generation;
    content.append(node("p", { class: "muted" }, "Reading the encounter tables..."));
    const defaults = await battleTerrainDefaults();
    if (page !== generation) return;
    content.replaceChildren();
    const terrains = Array.from({ length: TERRAINS }, (_, t) => t).filter(t => BF().terrainAvailable(objects, t)), places = encounterPlaces();
    const state = { terrainChoice: terrains.includes(terrainArg) ? terrainArg : "auto", group: groupArg >= 0 && groupArg < GROUPS ? groupArg : 1, formation: formationArg, terrain: terrains[0], script: null };
    const scriptFor = () => defaults.scripts[state.script] || defaults.scripts.find(battle => battle.group === state.group && battle.formation === state.formation);
    const defaultTerrain = () => {
      const script = scriptFor(), common = defaults.byGroup[state.group][0], scripted = new Map();
      for (const battle of defaults.scripts) if (battle.group === state.group) scripted.set(battle.terrain, (scripted.get(battle.terrain) || 0) + battle.commands.length);
      const terrain = script ? script.terrain : common ? common[0] : scripted.size ? [...scripted].sort((a, b) => b[1] - a[1])[0][0] : terrains[0];
      return terrains.includes(terrain) ? terrain : terrains[0];
    };
    let encounters = [], encounter = null;
    const choose = (label, options, value, onChange) => {
      const element = node("select", { "aria-label": label });
      const fill = (list, selected) => element.replaceChildren(...list.map(([v, text, disabled]) => node("option", { value: String(v), ...(String(v) === String(selected) ? { selected: "" } : {}), ...(disabled ? { disabled: "" } : {}) }, text)));
      fill(options, value);
      element.addEventListener("change", () => onChange(element.value));
      return { label: node("label", {}, node("span", {}, label), element), element, fill };
    };
    const groupText = g => { const p = places[g], where = [p.worldCells ? `world map, ${p.worldCells.toLocaleString()} cells` : "", ...p.maps.slice(0, 2).map(([map]) => mapLabel(map))].filter(Boolean); return `Group ${g}${where.length ? ` (${where.join("; ")}${p.maps.length > 2 ? ` +${p.maps.length - 2}` : ""})` : ""}`; };
    const formationOptions = () => encounters.map(entry => [entry.index, `${entry.index + 1}: ${formationLabel(entry)}${defaults.scripts.some(battle => battle.group === state.group && battle.formation === entry.index) ? " (script battle)" : ""}`, !entry.candidate]);
    const terrainOptions = () => [["auto", `Encounter default (${defaultTerrain()}: ${terrainLabel(defaultTerrain())})`], ...terrains.map(t => [t, `${t}: ${terrainLabel(t)}`])];
    const terrainPick = choose("Battle terrain", [], "auto", value => change({ terrainChoice: value === "auto" ? "auto" : Number(value) }));
    const scriptGroups = new Set(defaults.scripts.map(battle => battle.group));
    const groupPick = choose("Encounter group", Array.from({ length: GROUPS }, (_, g) => [g, scriptGroups.has(g) && !places[g].worldCells && !places[g].maps.length ? `Group ${g} (story and boss battles)` : groupText(g)]), state.group, value => change({ group: Number(value), formation: NaN, terrainChoice: "auto", script: null, place: null }));
    const scriptLabel = battle => `${battle.maps.length ? battle.maps.map(mapLabel).join(", ") : "Event script"}: ${BF().encounterGroup(objects, battle.group)[battle.formation].units.filter(Boolean).map(unit => zoidName(unit.zoid)).join(", ")}`;
    const scriptPick = choose("Script battle", [["none", "Random encounter (choose group and formation)"], ...defaults.scripts.map((battle, i) => [i, scriptLabel(battle)])], "none", value => {
      if (value === "none") { change({ script: null }); return; }
      const battle = defaults.scripts[Number(value)];
      change({ group: battle.group, formation: battle.formation, terrainChoice: "auto", script: Number(value) });
    });
    const formationPick = choose("Formation", [], 0, value => change({ formation: Number(value), script: null }));
    if (Number.isInteger(placeArg?.[0]) && placeArg[0] >= 0) state.place = { map: placeArg[0], x: placeArg[1] || 0, y: placeArg[2] || 0 };
    const transportOptions = () => TRANSPORTS.map(([model, name]) => [model, name]);
    const transportPick = choose("Transport", transportOptions(), TRANSPORTS[0][0], () => {});
    const facingPick = choose("Facing", DIRECTIONS.map((name, d) => [d, `Driving ${name}`]), FACING_DOWN, () => {});
    const speedPick = choose("Speed", [[1, "Normal (1 pixel per update)"], [2, "With B held (2 pixels per update)"]], 1, () => {});
    const overlayPick = choose("World overlay", [["on", "Shown (event flag 0 set, game not completed)"], ["off", "Hidden (before event flag 0, or after the ending)"]], "on", () => {});
    const playerTeam = battlePlayerTeam;
    const SCALE = 3, canvas = node("canvas", { width: 240, height: 160, class: "zoid-stage" }), context = canvas.getContext("2d");
    canvas.style.width = `${240 * SCALE}px`;
    const status = node("span", { class: "frame-count" }), note = node("p", { class: "muted stage-note" }, "Press Play battle to start the battle field and its music.");
    const camera = node("select", { "aria-label": "Camera" }, ...CAMERAS.map(([value, text]) => node("option", { value }, text)));
    camera.value = "intro";

    // Play battle runs the field closing (60 updates a second), the hold until the jingle ends, then the battle (30 a second).
    let field = null, battlePlaying = false, request = 0, last = 0, elapsed = 0, updates = 0, settledAt = null, nextSong = null, jingle = 0, jingleStarted = false;
    let phase = "idle", closing = null, closingUpdate = 0, holdSince = 0, battleSteps = 0, jingleFailed = false;
    const show = pixels => context.putImageData(new ImageData(pixels, 240, 160), 0, 0);
    const draw = () => {
      show(battleSteps && battleSteps <= 9 ? field.fadedFrame(battleSteps) : field.frame());
      status.textContent = `${settledAt == null ? "camera moving" : `camera settled after ${settledAt} updates`} · update ${updates}`;
    };
    const player = () => songPlayer();
    const jingleDone = () => !closing?.jingle || jingleFailed || (jingleStarted && player()?.status === "stopped") || performance.now() - holdSince > 6000;
    // A fade to black only darkens off the world maps; there UpdateFieldDisplay rewrites the cloud blend every update.
    function closingFrame() {
      const { scene, conceal } = closing;
      if (closingUpdate === 0) scene.lock();
      if (closingUpdate <= closingLength()) scene.update();
      if (conceal === "z") return scene.frame(Math.min(closingUpdate, BF().Z_DURATION));
      if (conceal === "fade") return closing.worldLike ? (closingUpdate > closingLength() ? scene.faded(16) : scene.frame(-1)) : scene.faded(Math.min(16, closingUpdate * 16 / closing.duration | 0));
      if (conceal === "dither") return scene.dithered(Math.min(closingUpdate, 28));
      return scene.faded(closingUpdate ? 16 : 0);
    }
    const closingLength = () => closing.conceal === "z" ? BF().Z_DURATION : closing.conceal === "fade" ? closing.duration : closing.conceal === "dither" ? 28 : 1;
    function openBattle() {
      phase = "battle"; battleSteps = 0; settledAt = null; updates = 0;
      if (!field) replaceField(false);
      camera.value = "intro"; field.camera("intro", true);
      const song = encounter.song; nextSong = null;
      player()?.play(rom, song).catch(musicError);
    }
    function tick(time) {
      if (!battlePlaying || page !== generation) return;
      if (last) elapsed += Math.min(time - last, 250);
      last = time;
      if (phase === "closing") {
        let stepped = false;
        let pixels = null;
        while (elapsed >= 1000 / FRAME_HZ && phase === "closing") {
          elapsed -= 1000 / FRAME_HZ; stepped = true;
          pixels = closingFrame();
          if (++closingUpdate > closingLength()) { phase = "hold"; holdSince = performance.now(); }
        }
        if (stepped) { show(pixels); status.textContent = phase === "hold" ? "waiting for the encounter jingle to end" : `field closing · update ${closingUpdate}`; }
      } else if (phase === "hold") {
        elapsed = 0;
        if (jingleDone()) openBattle();
      } else if (phase === "battle") {
        let stepped = false;
        while (elapsed >= 1000 / FIELD_HZ) { elapsed -= 1000 / FIELD_HZ; field.step(); updates++; battleSteps++; stepped = true; if (field.settled && settledAt == null) settledAt = updates; }
        if (stepped) draw();
        const music = player();
        if (nextSong != null && jingleStarted && music?.status === "stopped") { const song = nextSong; nextSong = null; music.play(rom, song).catch(musicError); }
      }
      request = requestAnimationFrame(tick);
    }
    const sides = () => [playerTeam.map(entry => entry && { zoid: entry.zoid, palette: entry.palette }), encounter.units];
    // A new field for the current setup that carries on the running view's camera.
    function replaceField(redraw = true) {
      const previous = field;
      try { field = new (BF().BattleField)(objects, { terrain: state.terrain, sides: sides() }); }
      catch (error) { status.textContent = error.message; return; }
      if (previous) field.resume(camera.value, previous.pose());
      if (redraw && phase === "battle") draw();
    }
    function aim() { if (!field || phase !== "battle") return; field.camera(camera.value, false); settledAt = null; updates = 0; }
    const musicError = error => { status.textContent = `Music: ${error.message}`; };
    // As in the game: the encounter jingle (run_field.c) plays out, then RunBattle plays the formation's song.
    function playSong(withSong = true) {
      const music = player();
      if (!music) return;
      const token = ++jingle;
      nextSong = withSong ? encounter.song : null; jingleStarted = false;
      jingleFailed = false;
      music.play(rom, BATTLE_JINGLE, { loop: false }).then(() => { if (token === jingle) jingleStarted = true; }, error => { jingleFailed = true; musicError(error); });
    }
    const startNote = node("p", { class: "muted" });
    let startToken = 0;
    async function startBattle() {
      const token = ++startToken;
      phase = "preparing"; closingUpdate = 0; battleSteps = 0; nextSong = null; jingle++; jingleStarted = false;
      const start = battleStart(defaults, state, scriptFor(), { transport: Number(transportPick.element.value), direction: Number(facingPick.element.value), speed: Number(speedPick.element.value) });
      if (start) {
        status.textContent = "drawing the field...";
        try {
          const spec = await fieldStartSpec(start, overlayPick.element.value === "on");
          if (!battlePlaying || token !== startToken) return;
          const scene = new (BF().FieldStart)(objects, spec);
          scene.walk(start.velocity[0], start.velocity[1], FIELD_WALK);
          closing = { ...start, scene, worldLike: start.map === 0 || start.map === 64 };
          startNote.textContent = `Starts from ${start.place}; the field closes with ${start.conceal === "z" ? "the scaled Z" : start.conceal === "fade" ? "a fade to black" : start.conceal === "dither" ? "the dither" : "a cut to black"}.`;
        } catch (error) { closing = null; startNote.textContent = `The field could not be drawn: ${error.message}`; }
      } else { closing = null; startNote.textContent = "No map cell starts this battle; it opens from black."; }
      if (!battlePlaying || token !== startToken) return;
      if (closing?.jingle !== false) playSong(false);
      phase = closing ? "closing" : "hold"; holdSince = performance.now();
      last = 0; elapsed = 0; request = requestAnimationFrame(tick);
    }
    const playBattle = button("Play battle", () => {
      if (battlePlaying) {
        battlePlaying = false; phase = "idle"; cancelAnimationFrame(request); player()?.stop(); nextSong = null; jingle++; jingleStarted = false;
        playBattle.textContent = "Play battle"; return;
      }
      battlePlaying = true; playBattle.textContent = "Stop battle";
      note.hidden = true; replay.disabled = download.disabled = false;
      player()?.context?.resume?.();
      startBattle();
    });
    const replay = button("Replay camera", aim), download = button("Download PNG", () => canvas.toBlob(blob => save(blob, fileName(`Battle field ${terrainLabel(state.terrain)} group ${state.group} formation ${state.formation + 1}`, "png"))));
    replay.disabled = download.disabled = true;
    camera.addEventListener("change", aim);

    const enemies = node("table"), music = node("p", { class: "muted" }), foundOn = node("p", { class: "muted" }), romDetails = node("p", { class: "muted" });
    function showEncounter() {
      enemies.replaceChildren(node("tr", {}, ...["Position", "Zoid", "Pilot", "Equipment", "Experience", "Money"].map(text => node("th", {}, text))));
      encounter.units.forEach((unit, slot) => {
        if (!unit) return;
        enemies.append(node("tr", {}, node("td", {}, slotLabel(1, slot)), node("td", {}, link(`#/zoid/${unit.zoid}`, `${zoidTitle(unit.zoid)} (palette ${unit.palette + 1})`)),
          node("td", {}, unit.pilot ? pilotName(unit.pilot) : "None"), node("td", {}, unit.equipment.filter(Boolean).map(weaponName).join(", ") || "None"),
          node("td", { class: "num" }, unit.experience.toLocaleString()), node("td", { class: "num" }, unit.money.toLocaleString())));
      });
      const where = places[state.group];
      music.replaceChildren(`Battle music: song ${String(encounter.song).padStart(3, "0")} · `, link("#/sound", "Sound"));
      foundOn.replaceChildren("Encounter group found on: ", where.worldCells ? `the world map (${where.worldCells.toLocaleString()} cells)` : "",
        ...where.maps.flatMap(([map, index], i) => [i || where.worldCells ? ", " : "", link(`#/maps/${index}`, mapLabel(map))]), !where.worldCells && !where.maps.length ? "no map" : "");
      romDetails.replaceChildren("Encounter record ", romLink(encounter.address + BASE, encounter.address + BASE + 100), " · formations of group ", String(state.group), " ", romLink(0x087b9454 + state.group * 2000, 0x087b9454 + state.group * 2000 + 2000));
    }
    // A new encounter restarts a running battle from the field; terrain and team changes keep it running.
    function change(next = {}) {
      const before = encounter;
      Object.assign(state, next);
      encounters = BF().encounterGroup(objects, state.group);
      if (!(state.formation >= 0 && state.formation < 20)) state.formation = Math.max(0, encounters.findIndex(entry => entry.candidate));
      encounter = encounters[state.formation];
      state.terrain = state.terrainChoice === "auto" ? defaultTerrain() : state.terrainChoice;
      groupPick.element.value = String(state.group);
      formationPick.fill(formationOptions(), state.formation);
      terrainPick.fill(terrainOptions(), state.terrainChoice);
      formationPick.element.value = String(state.formation); terrainPick.element.value = String(state.terrainChoice);
      const script = scriptFor();
      if (script) state.script = defaults.scripts.indexOf(script);
      scriptPick.element.value = script ? String(state.script) : "none";
      replaceHash(`#/battle/${state.terrainChoice}/${state.group}/${state.formation}${state.place ? `/${state.place.map}/${state.place.x}/${state.place.y}` : ""}`);
      showEncounter();
      transportPick.fill(transportOptions(), transportPick.element.value || TRANSPORTS[0][0]);
      if (field) replaceField();
      if (battlePlaying && encounter.address !== before?.address) { cancelAnimationFrame(request); player()?.stop(); field = null; startBattle(); }
    }

    const zoidOptions = [[0, "None"], ...Array.from({ length: 151 }, (_, i) => [i + 1, zoidTitle(i + 1)])];
    const team = node("table", {}, node("tr", {}, node("th", {}, "Position"), node("th", {}, "Zoid"), node("th", {}, "Palette")));
    playerTeam.forEach((entry, unit) => {
      const zoid = node("select", { "aria-label": `Player ${slotLabel(0, unit)} Zoid` }, ...zoidOptions.map(([v, text]) => node("option", { value: String(v), ...(v === (entry?.zoid || 0) ? { selected: "" } : {}) }, text)));
      const palette = node("select", { "aria-label": `Player ${slotLabel(0, unit)} palette` }, ...Array.from({ length: 8 }, (_, i) => node("option", { value: String(i), ...(i === (entry?.palette || 0) ? { selected: "" } : {}) }, `Palette ${i + 1}`)));
      const pick = () => { playerTeam[unit] = Number(zoid.value) ? { zoid: Number(zoid.value), palette: Number(palette.value) } : null; if (field) replaceField(); };
      zoid.addEventListener("change", pick); palette.addEventListener("change", pick);
      team.append(node("tr", {}, node("td", {}, slotLabel(0, unit)), node("td", {}, zoid), node("td", {}, palette)));
    });
    const controls = node("div", { class: "object-controls" }, scriptPick.label, groupPick.label, formationPick.label, terrainPick.label, transportPick.label, facingPick.label, speedPick.label, overlayPick.label,
      node("label", {}, node("span", {}, "Camera"), camera),
      node("div", { class: "playback" }, playBattle, replay, status),
      node("div", { class: "detail-links" }, download), startNote, music, foundOn);
    content.append(node("div", { class: "workbench" }, node("div", { class: "object-stage" }, canvas, note), controls),
      node("h3", {}, "Enemy formation"), node("div", { class: "table-wrap" }, enemies),
      node("h3", {}, "Player team"), node("div", { class: "table-wrap" }, team),
      node("details", { class: "source-details" }, node("summary", {}, "ROM details"), romDetails));
    change();
  }
  const battlePlayerTeam = [null, null, null, null, null, null];

  // ---------- text ----------
  // Every text view decoded once, merged by address and text; the game stores most text as full-width characters, so search and display use half-width.
  let textReady = null, textProgress = null;
  function textEntries() {
    textReady ||= (async () => {
      const entries = [];
      for (const [index, entry] of plan.items.entries()) entry[6].forEach((view, v) => { if (view.t === "text") entries.push({ index, v, view }); });
      for (const [n, entry] of entries.entries()) {
        try { entry.text = halfWidth((await D.render(rom, plan.items[entry.index][1], entry.view)).text); } catch (error) { entry.text = `(${error.message})`; }
        entry.search = `${entry.text} ${hex(plan.items[entry.index][1])}`.toLowerCase();
        if (n % 250 === 0) { textProgress?.(n, entries.length); await new Promise(resolve => setTimeout(resolve)); }
      }
      const merged = new Map();
      for (const entry of entries) {
        const key = `${plan.items[entry.index][1]}:${entry.text}`;
        if (merged.has(key)) merged.get(key).kinds.add(item(entry.index).kind);
        else merged.set(key, { ...entry, kinds: new Set([item(entry.index).kind]) });
      }
      return [...merged.values()];
    })();
    return textReady;
  }
  const csvCell = value => /[",\n]/.test(value) ? `"${value.replace(/"/g, '""')}"` : value;

  async function textLibrary(query) {
    clear();
    const page = generation, status = node("span", { class: "muted" }, "Reading the text...");
    const search = node("input", { type: "search", placeholder: "Search text or address", value: query || "", "aria-label": "Search text" });
    const actions = node("div", { class: "toolbar-actions" }), results = node("div");
    content.append(panel("Text"), node("div", { class: "gallery-toolbar" }, search, status, actions), results);
    textProgress = (done, total) => { if (page === generation) status.textContent = `Reading the text: ${done.toLocaleString()} of ${total.toLocaleString()}`; };
    const entries = await textEntries();
    if (page !== generation) return;
    const show = text => {
      const q = halfWidth(text).toLowerCase(), list = q ? entries.filter(entry => entry.search.includes(q)) : entries;
      const table = node("table", {}, node("tr", {}, node("th", {}, "Text"), node("th", {}, "Address")));
      const wrap = node("div", { class: "table-wrap" }, table);
      results.replaceChildren(wrap);
      actions.replaceChildren(button(`Download ${list.length.toLocaleString()} as CSV`, () => {
        const rows = [["address", "end", "kinds", "text"], ...list.map(entry => { const info = item(entry.index), [start, end] = info.spans[0] || [info.address, entry.view.end]; return [hex(start), hex(end), [...entry.kinds].join(" "), entry.text]; })];
        save(new Blob([rows.map(row => row.map(csvCell).join(",")).join("\r\n")], { type: "text/csv" }), fileName(`Zoids Legacy text${text ? " " + text : ""}`, "csv"));
      }));
      infinite(wrap, list, entry => {
        table.append(node("tr", { class: "text-row" }, node("td", {}, entry.text), node("td", {}, link(`#/item/${entry.index}`, hex(plan.items[entry.index][1]), "mono"))));
      }, status, list.length === 1 ? "string" : "strings");
    };
    search.addEventListener("input", debounce(() => { const text = search.value.trim(); replaceHash(`#/text/${encodeURIComponent(text)}`); show(text); }));
    show(query || "");
  }

  // ---------- sound ----------
  const SONG_TABLE_ENTRY = 8;
  let soundUI = null;
  function songPlayer() {
    if (!player && globalThis.ZoidsM4A) player = new globalThis.ZoidsM4A.Player({ onchange: state => soundUI?.update(state), onerror: error => soundUI?.error(error) });
    return player;
  }
  const time = seconds => `${Math.floor(seconds / 60)}:${String(Math.floor(seconds % 60)).padStart(2, "0")}`;
  const NOTES = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];
  const noteName = key => key == null ? "" : `${NOTES[key % 12]}${Math.floor(key / 12) - 2}`;

  // Each song id: its header, music player, stored tracks, and where it plays (maps, event scripts, code).
  function songCatalog() {
    const songsItem = findItem("table.songs", SONG_TABLE), uses = new Map();
    const view = songsItem != null ? plan.items[songsItem][6].find(entry => entry.t === "songs") : null;
    for (const [id, found] of view?.uses || []) uses.set(id, found);
    const mapGroup = map => { const label = mapLabel(map); return label.replace(/ · map \d+$/, ""); };
    return Array.from({ length: SONGS }, (_, id) => {
      const entry = SONG_TABLE + id * SONG_TABLE_ENTRY, header = word(entry), playerIndex = rom[entry + 4 - BASE] | (rom[entry + 5 - BASE] << 8);
      const tracks = header >= BASE && header < BASE + plan.rom_size ? rom[header - BASE] : 0;
      const capacity = rom[0x086a4694 + playerIndex * 12 + 8 - BASE];
      const found = { maps: [], battles: [], scripts: [], code: [], ...uses.get(id) };
      const enemies = new Map();
      for (const [, , zoids] of found.battles) for (const zoid of zoids) enemies.set(zoid, (enemies.get(zoid) || 0) + 1);
      const topEnemies = [...enemies].sort((a, b) => b[1] - a[1] || a[0] - b[0]).slice(0, 3).map(([zoid]) => zoidName(zoid));
      const places = [...new Set([
        ...(topEnemies.length ? [`Battle: ${topEnemies.join(", ")}`] : []),
        ...found.maps.map(mapGroup),
        ...found.scripts.flatMap(([, maps]) => maps.length ? maps.map(mapGroup) : ["Event script"]),
        ...found.code.map(humanize),
      ])];
      const label = places.length ? places.slice(0, 3).join(" · ") + (places.length > 3 ? ` +${places.length - 3}` : "") : "";
      return { id, entry, header, playerIndex, tracks, playable: Math.min(tracks, 16, capacity), found, places, label,
        search: `${String(id).padStart(3, "0")} ${places.join(" ")}`.toLowerCase() };
    });
  }

  // PCM samples with the DirectSound instruments that play them (voicegroup entries whose wave pointer is the sample).
  function sampleCatalog() {
    const voices = new Map();
    for (const index of kindItems.get(plan.kinds.indexOf("mp2k.voicegroup")) || []) {
      const group = plan.items[index][1], end = Math.max(...plan.items[index][5].map(span => span[1]));
      for (let at = group, voice = 0; at + 12 <= end; at += 12, voice++) {
        if ([0x00, 0x08, 0x10, 0x18].includes(rom[at - BASE])) {
          const wave = word(at + 4);
          if (!voices.has(wave)) voices.set(wave, []);
          voices.get(wave).push(voice);
        }
      }
    }
    return (kindItems.get(plan.kinds.indexOf("mp2k.pcm_wave")) || []).map((index, n) => {
      const info = item(index), view = info.views.find(entry => entry.t === "wav");
      const status = rom[info.address + 3 - BASE], loopStart = word(info.address + 8), length = view ? view.samples[2] - view.samples[1] : 0;
      return { index, n, info, view, loop: (status & 0x40) !== 0, loopStart, length, voices: voices.get(info.address) || [] };
    }).filter(sample => sample.view);
  }

  function waveform(sample) {
    const width = 220, height = 36, canvas = node("canvas", { width, height, class: "waveform" }), context = canvas.getContext("2d");
    const data = D.source(rom, sample.view.samples);
    context.fillStyle = "#79c7b1";
    for (let x = 0; x < width; x++) {
      const from = Math.floor(x / width * data.length), to = Math.max(from + 1, Math.floor((x + 1) / width * data.length));
      let low = 127, high = -128;
      for (let i = from; i < to; i++) { const value = data[i] << 24 >> 24; if (value < low) low = value; if (value > high) high = value; }
      const top = Math.round((127 - high) / 255 * (height - 1)), bottom = Math.round((127 - low) / 255 * (height - 1));
      context.fillRect(x, top, 1, Math.max(1, bottom - top + 1));
    }
    if (sample.loop && sample.length) { context.fillStyle = "#ffc36c"; context.fillRect(Math.round(sample.loopStart / sample.length * width), 0, 1, height); }
    return canvas;
  }

  let sampleContext = null, sampleSource = null;
  function playSample(sample, onend) {
    sampleSource?.stop();
    sampleContext ||= new (globalThis.AudioContext || globalThis.webkitAudioContext)();
    const data = D.source(rom, sample.view.samples), buffer = sampleContext.createBuffer(1, data.length, sample.view.rate), channel = buffer.getChannelData(0);
    for (let i = 0; i < data.length; i++) channel[i] = (data[i] << 24 >> 24) / 128;
    const source = sampleContext.createBufferSource();
    source.buffer = buffer; source.connect(sampleContext.destination);
    source.onended = () => { if (sampleSource === source) { sampleSource = null; onend?.(); } };
    sampleContext.resume(); source.start(); sampleSource = source;
  }

  function sound(tab = "music", query = "") {
    clear();
    sampleSource?.stop();
    const catalog = songCatalog().filter(song => song.tracks > 0), music = catalog.filter(song => song.playerIndex === 0), effects = catalog.filter(song => song.playerIndex !== 0), samples = sampleCatalog();
    const tabs = node("div", { class: "sound-tabs" }, ...[["music", `Music (${music.length})`], ["effects", `Sound effects (${effects.length})`], ["samples", `PCM samples (${samples.length})`]]
      .map(([key, label]) => link(`#/sound/${key}${query ? "/" + encodeURIComponent(query) : ""}`, label, key === tab ? "active" : "")));
    const search = node("input", { type: "search", placeholder: tab === "samples" ? "Filter by sample or voice" : "Filter by number or where it plays", value: query, "aria-label": "Filter" });
    search.addEventListener("input", () => filter(search.value.trim().toLowerCase()));
    search.addEventListener("change", () => globalThis.history?.replaceState?.(null, "", `#/sound/${tab}${search.value.trim() ? "/" + encodeURIComponent(search.value.trim()) : ""}`));
    const toolbar = node("div", { class: "toolbar" }, tabs, search);
    content.append(panel("Sound"), toolbar);
    const list = node("div", { class: "sound-list", role: "list" });
    let rows = [];
    const filter = q => { for (const [row, text] of rows) row.hidden = q && !text.includes(q); };

    if (tab === "samples") {
      toolbar.append(zipButton(`Download all ${samples.length} as ZIP`, "Zoids Legacy samples.zip", samples, async sample => {
        const result = await D.render(rom, sample.info.address, sample.view);
        return [`Sample ${String(sample.n + 1).padStart(3, "0")}.wav`, result.wav instanceof Uint8Array ? result.wav : new Uint8Array(result.wav)];
      }));
      content.append(list);
      for (const sample of samples) {
        const play = node("button", { class: "sound-play", "aria-label": `Play sample ${sample.n + 1}` }, "Play");
        const row = node("div", { class: "sound-row sample-row", role: "listitem" }, play,
          node("div", { class: "sound-name" }, node("strong", {}, `Sample ${sample.n + 1}`), node("small", {}, `${sample.view.rate.toLocaleString()} Hz · ${(sample.length / sample.view.rate).toFixed(2)} s${sample.loop ? " · loops" : ""}${sample.voices.length ? ` · voice ${sample.voices.join(", ")}` : ""}`)),
          waveform(sample),
          node("div", { class: "sound-links" }, itemLink(sample.index), button("WAV", () => D.render(rom, sample.info.address, sample.view).then(result => save(new Blob([result.wav], { type: "audio/wav" }), `Sample ${String(sample.n + 1).padStart(3, "0")}.wav`)))));
        const start = () => {
          for (const [other] of rows) other.classList.remove("playing");
          row.classList.add("playing");
          playSample(sample, () => row.classList.remove("playing"));
        };
        play.addEventListener("click", event => { event.stopPropagation(); start(); });
        row.addEventListener("click", event => { if (event.target.tagName !== "A" && event.target.tagName !== "BUTTON") start(); });
        list.append(row);
        rows.push([row, `sample ${sample.n + 1} ${sample.view.rate} ${sample.voices.map(voice => "voice " + voice).join(" ")}`.toLowerCase()]);
      }
      filter(query.toLowerCase());
      return;
    }

    const songs = tab === "effects" ? effects : music;
    const deck = node("aside", { class: "now-playing" });
    content.append(node("div", { class: "sound-layout" }, list, deck));
    let current = null;
    const songRows = new Map();
    const title = node("h3", {}, "Nothing playing"), where = node("p", { class: "muted" }), status = node("span", { class: "m4a-time" }, "0:00");
    const playButton = button("Play", () => togglePlay()), loop = node("input", { type: "checkbox" }), volume = node("input", { type: "range", min: "0", max: "100", value: "65", "aria-label": "Volume" });
    loop.checked = songPlayer()?.loop ?? true;
    loop.addEventListener("change", () => songPlayer().setLoop(loop.checked));
    volume.addEventListener("input", () => songPlayer().setVolume(Number(volume.value) / 100));
    const step = delta => { const playable = songs.filter(song => song.playable); if (!playable.length) return; const at = current ? playable.indexOf(current) : -1; start(playable[(at + delta + playable.length) % playable.length]); };
    const wav = button("Download WAV", async () => {
      if (!current) return;
      wav.disabled = true;
      try {
        const result = await globalThis.ZoidsM4A.renderWav(rom, current.id, { onprogress: seconds => { wav.textContent = `Rendering ${time(seconds)}`; } });
        save(new Blob([result.bytes], { type: "audio/wav" }), fileName(`Song ${String(current.id).padStart(3, "0")}${current.label ? " " + current.label : ""}`, "wav"));
      } catch (error) { where.textContent = error.message; }
      wav.disabled = false; wav.textContent = "Download WAV";
    });
    const tracks = node("table", { class: "m4a-tracks" }), uses = node("div", { class: "song-uses" });
    let trackRows = [];
    deck.append(title, where, node("div", { class: "m4a-controls" }, button("Previous", () => step(-1)), playButton, button("Next", () => step(1)), button("Stop", () => songPlayer().stop()), status),
      node("div", { class: "m4a-controls" }, node("label", {}, loop, "Loop"), node("label", {}, "Volume", volume), wav), tracks, uses);

    function buildTracks(count) {
      tracks.replaceChildren(node("tr", {}, ...["Track", "Voice", "Note", "Vol", "Pan", "Mute", ""].map(text => node("th", {}, text))));
      trackRows = Array.from({ length: count }, (_, index) => {
        const mute = node("input", { type: "checkbox", "aria-label": `Mute track ${index + 1}` });
        mute.addEventListener("change", () => songPlayer().mute(index, mute.checked));
        const solo = button("Solo", () => { for (let other = 0; other < count; other++) { const muted = other !== index; songPlayer().mute(other, muted); trackRows[other].mute.checked = muted; } });
        const cells = [node("td", {}), node("td", {}), node("td", {}), node("td", {})];
        tracks.append(node("tr", {}, node("td", {}, String(index + 1)), ...cells, node("td", {}, mute), node("td", {}, solo)));
        return { cells, mute };
      });
    }
    function showUses(song) {
      const parts = [];
      const mapLinks = song.found.maps.map(map => { const index = (kindItems.get(plan.kinds.indexOf("field_map")) || []).find(i => plan.items[i][6].some(view => view.t === "map" && view.map === map)); return index != null ? link(`#/maps/${index}`, mapLabel(map)) : mapLabel(map); });
      if (mapLinks.length) parts.push(node("p", {}, "Map music: ", ...mapLinks.flatMap((entry, i) => [i ? ", " : "", entry])));
      if (song.found.battles.length) {
        const formations = findItem("table.encounter_formations", 0x087b9454);
        const shown = song.found.battles.slice(0, 12).map(([group, encounter, zoids]) => `group ${group} formation ${encounter} (${[...new Set(zoids)].map(zoidName).join(", ")})`);
        parts.push(node("p", {}, `Battle music in ${song.found.battles.length} encounter formation${song.found.battles.length === 1 ? "" : "s"}: `, shown.join("; "), song.found.battles.length > 12 ? `; +${song.found.battles.length - 12} more` : "", formations != null ? node("span", {}, " · ", itemLink(formations)) : null));
      }
      const scripts = song.found.scripts.map(([script]) => { const owner = findItem("event_script", script); return owner != null ? itemLink(owner) : romLink(script); });
      if (scripts.length) parts.push(node("p", {}, "Event scripts: ", ...scripts.flatMap((entry, i) => [i ? ", " : "", entry])));
      if (song.found.code.length) parts.push(node("p", {}, "Code: ", song.found.code.map(humanize).join(", ")));
      const header = findItem("mp2k.song", song.header);
      parts.push(node("p", { class: "muted" }, "Header ", header != null ? itemLink(header) : romLink(song.header), " · table entry ", romLink(song.entry, song.entry + SONG_TABLE_ENTRY)));
      uses.replaceChildren(...parts);
    }
    async function start(song) {
      if (!song.playable) return;
      current = song;
      for (const [row] of rows) row.classList.remove("playing");
      songRows.get(song.id)?.classList.add("playing");
      title.textContent = `Song ${String(song.id).padStart(3, "0")}${song.label ? " · " + song.label : ""}`;
      where.textContent = `${song.tracks} tracks${song.playable < song.tracks ? `, ${song.playable} played` : ""} · music player ${song.playerIndex}`;
      buildTracks(song.playable);
      showUses(song);
      try { await songPlayer().play(rom, song.id); } catch (error) { where.textContent = error.message; }
    }
    async function togglePlay() {
      const engine = songPlayer();
      if (!current) { step(1); return; }
      if (engine.status === "playing") await engine.pause();
      else if (engine.status === "paused") await engine.resume();
      else start(current);
    }
    soundUI = {
      update(state) {
        playButton.textContent = state.status === "playing" ? "Pause" : "Play";
        status.textContent = `${time(state.elapsed || 0)}${state.state?.tempo ? ` · tempo ${state.state.tempo}` : ""}${state.status === "loading" ? " · loading" : ""}`;
        (state.state?.tracks || []).forEach((track, index) => {
          const row = trackRows[index];
          if (!row) return;
          const values = [track.voice ?? "", track.active ? noteName(track.key) : "", track.volume ?? "", track.pan ?? ""];
          values.forEach((value, cell) => { if (row.cells[cell].textContent !== String(value)) row.cells[cell].textContent = String(value); });
        });
        if (state.status === "stopped") for (const [row] of rows) row.classList.remove("playing");
      },
      error(error) { where.textContent = error.message; },
    };
    for (const song of songs) {
      const row = node("div", { class: "sound-row" + (song.playable ? "" : " silent"), role: "listitem" },
        node("span", { class: "sound-number mono" }, String(song.id).padStart(3, "0")),
        node("button", { class: "sound-name", type: "button", ...(song.playable ? {} : { disabled: "" }) }, node("strong", {}, song.label || `Song ${song.id}`), node("small", {}, song.playable ? `${song.tracks} tracks` : "no tracks")));
      songRows.set(song.id, row);
      if (song.playable) row.addEventListener("click", () => start(song));
      list.append(row);
      rows.push([row, song.search]);
    }
    filter(query.toLowerCase());
  }

  // ---------- ROM tools ----------
  function coverage() {
    clear();
    const s = plan.summary;
    const cards = node("div", { class: "cards" });
    for (const [title, value, detail] of [
      ["Known data", `${(100 * s.known_data_bytes / s.data_bytes).toFixed(2)}%`, `${s.known_data_bytes.toLocaleString()} of ${s.data_bytes.toLocaleString()} data bytes read by ported C`],
      ["Items", plan.items.length.toLocaleString(), `${plan.kinds.length} kinds`],
      ["Matched code", s.code_bytes.toLocaleString(), `bytes in ${plan.regions.length} regions`],
      ["Unported roots / dangling pointers", `${s.unported_roots} / ${s.dangling_pointers}`, "both must be 0"]]) {
      cards.append(node("div", { class: "card" }, node("p", {}, title), node("strong", {}, value), node("small", {}, detail)));
    }
    content.append(panel("Coverage"), cards, coverageStrip(), legend());
    const table = node("table", {}, node("tr", {}, node("th", {}, "Unread class"), node("th", {}, "Meaning"), node("th", { class: "num" }, "Ranges"), node("th", { class: "num" }, "Bytes")));
    for (const name of plan.classes) {
      const [ranges, bytes] = s.classes[name] || [0, 0];
      const [label, meaning] = CLASS_INFO[name];
      table.append(node("tr", {}, node("td", {}, ranges ? link(`#/class/${name}`, label) : label), node("td", { class: "muted" }, meaning), node("td", { class: "num" }, ranges.toLocaleString()), node("td", { class: "num" }, bytes.toLocaleString())));
    }
    content.append(panel("Unread data"), table);
    const largest = plan.unread.map((range, index) => [range, index]).filter(([range]) => !["zero", "fill_ff"].includes(plan.classes[range[2]])).sort((a, b) => (b[0][1] - b[0][0]) - (a[0][1] - a[0][0])).slice(0, 20);
    if (largest.length) {
      const gaps = node("table", {}, node("tr", {}, node("th", {}, "ROM range"), node("th", { class: "num" }, "Bytes"), node("th", {}, "Class"), node("th", {}, "Item"), node("th", {}, "Reason")));
      for (const [[start, end, cls, reason, , inside, before]] of largest) {
        const owner = inside >= 0 ? itemLink(inside) : before >= 0 ? node("span", {}, "after ", itemLink(before)) : "";
        gaps.append(node("tr", {}, node("td", {}, romLink(start, end)), node("td", { class: "num" }, (end - start).toLocaleString()), node("td", {}, CLASS_INFO[plan.classes[cls]]?.[0] || plan.classes[cls]), node("td", {}, owner), node("td", { class: "muted" }, reason >= 0 ? plan.reasons[reason] : "")));
      }
      content.append(panel("Largest unread ranges", "Fill bytes left out"), node("div", { class: "table-wrap" }, gaps));
    }
    content.append(node("div", { class: "detail-links" }, button("Download plan.json", () => save(new Blob([JSON.stringify(plan)], { type: "application/json" }), "plan.json"))));
  }

  function legend() {
    const box = node("div", { class: "legend" });
    for (const [key, label] of [["known", "read by a port"], ["code", "matched code"], ["declared_unread", "declared unread"], ["declared_unreachable", "declared unreachable"], ["explained", "explained"], ["fill_ff", "0xFF fill"], ["zero", "zero fill"], ["open", "unaccounted"]]) {
      const span = node("span", {}, label); span.style.setProperty("--c", `rgb(${COLORS[key].join(",")})`); box.append(span);
    }
    return box;
  }

  let stripImage = null;
  function coverageStrip() {
    const width = 1024, perPixel = Math.ceil(plan.rom_size / (width * 128)), height = Math.ceil(plan.rom_size / (width * perPixel));
    if (!stripImage) {
      const state = new Uint8Array(plan.rom_size), keys = Object.keys(COLORS), code = keys.indexOf("code"), known = keys.indexOf("known");
      for (const [start, end] of plan.regions) state.fill(code, start - BASE, end - BASE);
      for (const [, , , , , spans] of plan.items) for (const [start, end] of spans) state.fill(known, start - BASE, end - BASE);
      for (const [start, end, cls] of plan.unread) { const key = keys.indexOf(plan.classes[cls]); state.fill(key >= 0 ? key : keys.indexOf("open"), start - BASE, end - BASE); }
      const img = { width, height, rgba: new Uint8ClampedArray(width * height * 4) }, tally = new Uint32Array(keys.length);
      for (let pixel = 0; pixel < width * height; pixel++) {
        tally.fill(0);
        const from = pixel * perPixel, to = Math.min(plan.rom_size, from + perPixel);
        for (let at = from; at < to; at++) tally[state[at]]++;
        let best = 0; for (let k = 1; k < keys.length; k++) if (tally[k] > tally[best]) best = k;
        const rgb = from < to ? COLORS[keys[best]] : [0, 0, 0];
        img.rgba.set([rgb[0], rgb[1], rgb[2], 255], pixel * 4);
      }
      stripImage = img;
    }
    const canvas = canvasOf(stripImage);
    canvas.className = "strip";
    canvas.title = `${perPixel} bytes per pixel; click to open that address`;
    canvas.addEventListener("click", event => {
      const rect = canvas.getBoundingClientRect();
      const x = Math.floor((event.clientX - rect.left) / rect.width * width), y = Math.floor((event.clientY - rect.top) / rect.height * height);
      location.hash = `#/rom/${(BASE + (y * width + x) * perPixel).toString(16).toUpperCase()}`;
    });
    return canvas;
  }

  function kinds() {
    clear();
    const table = node("table", {}, node("tr", {}, node("th", {}, "Kind"), node("th", { class: "num" }, "Items"), node("th", { class: "num" }, "Bytes read"), node("th", {}, "Previews")));
    plan.kinds.forEach((name, kind) => {
      const list = kindItems.get(kind) || [];
      const bytes = list.reduce((sum, index) => sum + bytesOf(item(index)), 0);
      const previews = new Set(list.flatMap(index => plan.items[index][6].map(view => view.t)));
      table.append(node("tr", {}, node("td", {}, link(`#/kind/${encodeURIComponent(name)}`, name, "mono")), node("td", { class: "num" }, list.length.toLocaleString()), node("td", { class: "num" }, bytes.toLocaleString()), node("td", { class: "muted" }, [...previews].join(", ") || "bytes")));
    });
    content.append(panel("All items"), node("div", { class: "table-wrap" }, table));
  }

  function kindPage(name) {
    clear();
    const kind = plan.kinds.indexOf(name), list = kindItems.get(kind) || [], status = node("p", { class: "muted" });
    if (kind < 0) { notFound(`There is no item kind named "${name}".`); return; }
    const table = node("table", {}, node("tr", {}, node("th", {}, "Item"), node("th", {}, "ROM ranges read"), node("th", { class: "num" }, "Bytes"), node("th", {}, "Count from")));
    const wrap = node("div", { class: "table-wrap" }, table);
    content.append(panel(name), status, wrap);
    infinite(wrap, list, index => {
      const info = item(index), spans = info.spans;
      const ranges = spans.length
        ? node("td", {}, ...spans.slice(0, 3).flatMap(([s, e], i) => [i ? " " : "", romLink(s, e)]), spans.length > 3 ? ` +${spans.length - 3}` : "")
        : node("td", {}, info.via.length ? "via " : romLink(info.address), ...info.via.slice(0, 2).flatMap((owner, i) => [i ? ", " : "", itemLink(owner)]));
      table.append(node("tr", {}, node("td", {}, itemLink(index)), ranges, node("td", { class: "num" }, bytesOf(info).toLocaleString()), node("td", { class: "muted" }, info.count || "")));
    }, status);
  }

  async function itemPage(index) {
    clear();
    if (!(index >= 0 && index < plan.items.length)) { notFound("There is no item with that number."); return; }
    const info = item(index), named = assetName(info), page = generation;
    content.append(panel(named || itemLabel(info)));
    const previews = node("div", { class: "views" });
    if (info.views.length) content.append(previews);
    const facts = node("dl", { class: "facts" });
    const fact = (k, ...v) => facts.append(node("dt", {}, k), node("dd", {}, ...v));
    fact("Kind", link(`#/kind/${encodeURIComponent(info.kind)}`, info.kind, "mono"));
    fact("Address", romLink(info.address));
    fact("Size", `${bytesOf(info).toLocaleString()} bytes in ${info.spans.length} range${info.spans.length === 1 ? "" : "s"}`);
    content.append(facts);

    const research = node("details", { class: "source-details", ...(info.views.length ? {} : { open: "" }) }, node("summary", {}, "ROM details"));
    const more = node("dl", { class: "facts" });
    const detail = (k, ...v) => more.append(node("dt", {}, k), node("dd", {}, ...v));
    detail("Ported from", node("span", { class: "mono" }, info.basis));
    if (info.count) detail("Count from", info.count);
    if (info.reason) detail("Reason", info.reason);
    detail("Reached from", node("span", { class: "mono" }, info.reached.join(" · ") || "none"));
    research.append(more);
    if (info.spans.length) {
      const spans = node("table", {}, node("tr", {}, node("th", {}, "ROM range"), node("th", { class: "num" }, "Bytes"), node("th", {}, "Read as")));
      for (const [start, end, format] of info.spans.slice(0, 400)) spans.append(node("tr", {}, node("td", {}, romLink(start, end)), node("td", { class: "num" }, end - start), node("td", { class: "mono" }, plan.formats[format])));
      research.append(node("h3", {}, "ROM ranges read"), node("div", { class: "table-wrap" }, spans));
      if (info.spans.length > 400) research.append(node("p", { class: "muted" }, `${info.spans.length - 400} more ranges; open the ROM bytes to walk them.`));
    } else {
      research.append(node("h3", {}, "ROM ranges"), node("p", { class: "muted" }, info.via.length ? "This item reads no bytes of its own; these items read the bytes at its address or the ones it reaches:" : "This item reads no bytes (see its reason)."));
      const via = node("table", {}, node("tr", {}, node("th", {}, "Item"), node("th", {}, "Its ROM range")));
      for (const owner of info.via) {
        const ownerInfo = item(owner), shown = ownerInfo.spans.find(([s, e]) => s <= info.address && info.address < e) || ownerInfo.spans[0];
        via.append(node("tr", {}, node("td", {}, itemLink(owner)), node("td", {}, shown ? romLink(shown[0], shown[1]) : "")));
      }
      if (info.via.length) research.append(via);
    }
    const inside = unreadInside.get(index) || [];
    if (inside.length) {
      const table = node("table", {}, node("tr", {}, node("th", {}, "Unread range"), node("th", { class: "num" }, "Bytes"), node("th", {}, "Reason")));
      for (const u of inside.slice(0, 200)) { const range = plan.unread[u]; table.append(node("tr", {}, node("td", {}, romLink(range[0], range[1])), node("td", { class: "num" }, range[1] - range[0]), node("td", { class: "muted" }, plan.reasons[range[3]] || ""))); }
      research.append(node("h3", {}, `Bytes inside this item the C never reads (${inside.length})`), node("div", { class: "table-wrap" }, table));
    }
    content.append(research);
    if (!info.views.length) return;
    previews.append(node("p", { class: "muted" }, "Loading the preview..."));
    const results = await decodedViews(index);
    if (page !== generation) return;
    previews.replaceChildren();
    for (const [i, result] of results.entries()) previews.append(await viewElement(info, result, info.views[i]));
  }

  let focusBytes = false;
  const romHash = address => `#/rom/${address.toString(16).toUpperCase()}`;
  function romPage(start, highlightEnd) {
    clear();
    if (!Number.isFinite(start)) { notFound("That is not a ROM address."); return; }
    const anchor = Math.max(BASE, Math.min(start < BASE ? start + BASE : start, BASE + plan.rom_size - 1));
    const first = Math.max(BASE, (anchor & ~0xf) - 0x80), rows = 40, last = Math.min(BASE + plan.rom_size, first + rows * 16);
    content.append(panel(`ROM bytes at ${hex(anchor)}`, highlightEnd ? `Highlighted: ${hex(start)}..${hex(highlightEnd)}` : null));
    const input = node("input", { placeholder: "0x08xxxxxx", spellcheck: "false", "aria-label": "Go to ROM address" });
    const jump = node("form", { class: "jump" }, input, node("button", {}, "Go"));
    jump.addEventListener("submit", event => { event.preventDefault(); const value = parseInt(input.value.trim().replace(/^0x/i, ""), 16); if (Number.isFinite(value)) location.hash = romHash(value < BASE ? value + BASE : value); });
    content.append(node("div", { class: "byte-controls" }, jump, link(romHash(Math.max(BASE, first - rows * 16)), "‹ Earlier"), link(romHash(last), "Later ›"), legend()));
    const side = node("div", { class: "byte-panel" });
    const table = node("table", { class: "hex", tabindex: "0", "aria-label": "ROM bytes. Arrow keys move the selection; Page Up and Page Down move a screen." });
    const cells = new Map();
    let selected = [], current = anchor;
    const select = (pair, address) => { for (const cell of selected) cell.classList.remove("sel"); selected = pair; current = address; for (const cell of pair) cell.classList.add("sel"); showByte(side, address); };
    const STEPS = { ArrowLeft: -1, ArrowRight: 1, ArrowUp: -16, ArrowDown: 16, PageUp: -rows * 16, PageDown: rows * 16 };
    table.addEventListener("keydown", event => {
      if (!(event.key in STEPS)) return;
      event.preventDefault();
      const next = Math.max(BASE, Math.min(BASE + plan.rom_size - 1, current + STEPS[event.key]));
      if (cells.has(next)) select(cells.get(next), next);
      else { focusBytes = true; location.hash = romHash(next); }
    });
    for (let row = first; row < last; row += 16) {
      const tr = node("tr", {}, node("td", { class: "offset" }, hex(row)));
      const ascii = node("td", { class: "ascii" });
      for (let address = row; address < row + 16 && address < last; address++) {
        const rgb = COLORS[stateAt(address)], byte = rom[address - BASE];
        const cell = node("td", { title: hex(address) }, byte.toString(16).toUpperCase().padStart(2, "0"));
        const char = node("span", { title: hex(address) }, byte >= 0x20 && byte < 0x7f ? String.fromCharCode(byte) : ".");
        cell.style.background = char.style.background = `rgba(${rgb.join(",")},0.35)`;
        if (highlightEnd && address >= start && address < highlightEnd) { cell.classList.add("hl"); char.classList.add("hl"); }
        const pick = () => select([cell, char], address);
        cells.set(address, [cell, char]);
        cell.addEventListener("click", pick);
        char.addEventListener("click", pick);
        if (address === anchor) queueMicrotask(pick);
        tr.append(cell);
        ascii.append(char);
      }
      tr.append(ascii);
      table.append(tr);
    }
    content.append(node("div", { class: "rom-layout" }, node("div", { class: "table-wrap" }, table), side));
    if (focusBytes) { focusBytes = false; queueMicrotask(() => table.focus?.()); }
  }

  function showByte(side, address) {
    const owners = ownersAt(address);
    side.replaceChildren(node("h3", { class: "mono" }, `${hex(address)} = ${rom[address - BASE].toString(16).toUpperCase().padStart(2, "0")}`));
    if (owners.code) { side.append(node("p", {}, "Matched code: ", node("span", { class: "mono" }, owners.code[2]), " ", romLink(owners.code[0], owners.code[1]))); return; }
    for (const span of owners.spans) side.append(node("p", {}, itemLink(span.item), node("br"), "read as ", node("span", { class: "mono" }, span.format), " in ", romLink(span.start, span.end)));
    if (owners.unread != null) {
      const [start, end, cls, reason, basis, inside, before] = plan.unread[owners.unread];
      side.append(node("p", {}, node("strong", {}, CLASS_INFO[plan.classes[cls]][0]), " ", romLink(start, end), ` (${end - start} bytes)`));
      if (reason >= 0) side.append(node("p", { class: "muted" }, plan.reasons[reason]));
      if (basis >= 0) side.append(node("p", { class: "mono" }, plan.bases[basis]));
      if (inside >= 0) side.append(node("p", {}, "Inside ", itemLink(inside)));
      else if (before >= 0) side.append(node("p", {}, "After ", itemLink(before)));
    }
    if (!owners.spans.length && owners.unread == null) side.append(node("p", { class: "muted" }, "Not data."));
  }

  function unreadPage() {
    clear();
    const table = node("table", {}, node("tr", {}, node("th", {}, "Class"), node("th", {}, "Meaning"), node("th", { class: "num" }, "Ranges"), node("th", { class: "num" }, "Bytes")));
    for (const name of plan.classes) {
      const [ranges, bytes] = plan.summary.classes[name] || [0, 0];
      table.append(node("tr", {}, node("td", {}, ranges ? link(`#/class/${name}`, CLASS_INFO[name][0]) : CLASS_INFO[name][0]), node("td", { class: "muted" }, CLASS_INFO[name][1]), node("td", { class: "num" }, ranges.toLocaleString()), node("td", { class: "num" }, bytes.toLocaleString())));
    }
    content.append(panel("Unread data"), table);
  }

  function classPage(name) {
    clear();
    if (!CLASS_INFO[name]) { notFound(`There is no unread class named "${name}".`); return; }
    const list = unreadByClass.get(name) || [], status = node("p", { class: "muted" });
    const table = node("table", {}, node("tr", {}, node("th", {}, "ROM range"), node("th", { class: "num" }, "Bytes"), node("th", {}, "Item"), node("th", {}, "Reason")));
    const wrap = node("div", { class: "table-wrap" }, table);
    content.append(panel(CLASS_INFO[name] ? CLASS_INFO[name][0] : name, CLASS_INFO[name] ? CLASS_INFO[name][1] : ""), status, wrap);
    infinite(wrap, list, index => {
      const [start, end, , reason, , inside, before] = plan.unread[index];
      const owner = inside >= 0 ? itemLink(inside) : before >= 0 ? node("span", {}, "after ", itemLink(before)) : "";
      table.append(node("tr", {}, node("td", {}, romLink(start, end)), node("td", { class: "num" }, (end - start).toLocaleString()), node("td", {}, owner), node("td", { class: "muted" }, reason >= 0 ? plan.reasons[reason] : "")));
    }, status);
  }

  // ---------- routing ----------
  function intake() {
    clear();
    const input = node("input", { type: "file", accept: ".gba,.bin", hidden: "" });
    input.addEventListener("change", () => { const file = input.files[0]; if (file) file.arrayBuffer().then(useRom); });
    const choose = node("label", { tabindex: "0", role: "button" }, "Choose ROM file", input);
    keyboardFile(choose, input);
    content.append(node("div", { class: "intake" },
      node("h1", {}, "Open your Zoids Legacy (USA) ROM"),
      choose,
      node("p", { class: "muted" }, "or drop the .gba file here")));
  }

  function route() {
    if (!plan) return;
    document.getElementById("site-nav").hidden = !rom;
    if (!rom) { intake(); return; }
    const parts = location.hash.replace(/^#\/?/, "").split("/").map(part => { try { return decodeURIComponent(part); } catch { return part; } });
    const section = parts[0] || "gallery", tab = { zoid: "zoids", sprites: "gallery", kind: "kinds", unread: "coverage", class: "coverage" }[section] ?? section;
    for (const anchor of document.querySelectorAll("nav a")) anchor.classList.toggle("active", anchor.hash.split("/")[1] === tab);
    for (const menu of document.querySelectorAll("nav details")) { menu.open = false; menu.classList.toggle("active", ["coverage", "kinds", "rom"].includes(tab)); }
    if (section === "gallery") gallery(parts[1] && parts[1] !== "all" ? parts[1] : null, parts[2] || "");
    else if (section === "sprites") gallery("Sprites", "");
    else if (section === "zoids") zoids();
    else if (section === "zoid") zoidPage(parseInt(parts[1], 10));
    else if (section === "equipment") equipmentList();
    else if (section === "maps") maps(parts[1] != null ? parseInt(parts[1], 10) : null);
    else if (section === "battle") battlePage(...[1, 2, 3].map(i => parts[i] != null ? parseInt(parts[i], 10) : NaN), [4, 5, 6].map(i => parts[i] != null ? parseInt(parts[i], 10) : NaN));
    else if (section === "text") textLibrary(parts[1] || "");
    else if (section === "sound") sound(parts[1] || "music", parts[2] || "");
    else if (section === "coverage") coverage();
    else if (section === "kinds") kinds();
    else if (section === "kind") kindPage(parts[1]);
    else if (section === "item") itemPage(parseInt(parts[1], 10));
    else if (section === "rom") romPage(parseInt(parts[1], 16), parts[2] ? parseInt(parts[2], 16) : null);
    else if (section === "unread") unreadPage();
    else if (section === "class") classPage(parts[1]);
    else { clear(); notFound("This page does not exist."); }
  }
  window.addEventListener("hashchange", route);

  async function loadPlan() {
    const text = document.getElementById("plan-data").textContent.trim();
    const binary = Uint8Array.from(atob(text), c => c.charCodeAt(0));
    const stream = new Blob([binary]).stream().pipeThrough(new DecompressionStream("gzip"));
    plan = JSON.parse(await new Response(stream).text());
    buildIndexes();
    statusLine.textContent = "";
    route();
    if (window.opener) window.opener.postMessage({ type: "zoids-extractor-ready" }, location.origin);
  }
  loadPlan().catch(error => { content.textContent = `Could not load the plan: ${error.message}`; });
})();
