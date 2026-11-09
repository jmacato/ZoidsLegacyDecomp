import { readFileSync, writeFileSync, existsSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import katex from 'katex';
import { marked } from 'marked';
import hljs from 'highlight.js/lib/core';
import c from 'highlight.js/lib/languages/c';
import armasm from 'highlight.js/lib/languages/armasm';

hljs.registerLanguage('c', c);
hljs.registerLanguage('armasm', armasm);

const repo = fileURLToPath(new URL('../../', import.meta.url));
const args = process.argv.slice(2);
const fill = args[0] === '--fill';
if (fill) args.shift();
const [src = repo + 'BATTLE_MECHANICS.md', out = repo + 'site/battle-mechanics.html'] = args;
const rom = repo + 'Zoids Legacy (USA).gba';
const githubRepo = 'https://github.com/jmacato/ZoidsLegacyDecomp';
const githubRef = process.env.BATTLE_MECHANICS_REF || 'origin/main';
const git = (...a) => execFileSync('git', ['-C', repo, ...a], { encoding: 'utf8', stdio: ['ignore', 'pipe', 'ignore'] });
let md = readFileSync(src, 'utf8');

const esc = s => s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
const hex = n => '0x' + n.toString(16).toUpperCase().padStart(8, '0');
const ranges = spec => spec.split(',').map(r => { const [a, b = a] = r.split('-').map(Number); return [a, b]; });

const excerpt = (kind, where) => {
  if (kind === 'c') {
    const [file, spec] = where.split(':');
    const lines = readFileSync(repo + file, 'utf8').split('\n');
    const rows = [];
    ranges(spec).forEach(([a, b], k) => {
      if (k) rows.push({ n: null, text: '...' });
      const part = lines.slice(a - 1, b).map((text, i) => ({ n: a + i, text }));
      while (part.length && !part[0].text.trim()) part.shift();
      while (part.length && !part.at(-1).text.trim()) part.pop();
      const indent = Math.min(...part.filter(r => r.text.trim()).map(r => r.text.match(/^ */)[0].length));
      part.forEach(r => rows.push({ n: r.n, text: r.text.slice(indent).trimEnd() }));
    });
    return rows;
  }
  if (!existsSync(rom)) return null;
  const rows = [];
  ranges(where).forEach(([start, stop], k) => {
    if (k) rows.push({ n: null, text: '...' });
    const dump = execFileSync('arm-none-eabi-objdump', ['-D', '-b', 'binary', '-m', 'armv4t', ...(kind === 'thumb' ? ['-M', 'force-thumb'] : []),
      '--adjust-vma=0x08000000', `--start-address=${start}`, `--stop-address=${stop}`, rom], { encoding: 'utf8' });
    for (const l of dump.split('\n')) {
      const m = l.match(/^\s+([0-9a-f]+):\t/);
      if (m) rows.push({ n: parseInt(m[1], 16), text: l.trim().replace(/\t+/g, '  ').replace(/\s+@ \(0x[0-9a-f]+\)$/, '') });
    }
  });
  return rows;
};
const rowsText = rows => rows.map(r => r.text).join('\n');
const fence = /^```(c|thumb|arm) (\S+)\n([\s\S]*?)^```$/gm;

let drift = 0;
md = md.replace(fence, (all, kind, where, text) => {
  const rows = excerpt(kind, where);
  if (rows === null) { console.warn(`skipped ${kind} ${where}: ROM not found`); return all; }
  const want = rowsText(rows);
  if (fill) return '```' + `${kind} ${where}\n${want}\n` + '```';
  if (text.replace(/\n$/, '') !== want) { console.error(`excerpt differs from source: ${kind} ${where}`); drift++; }
  return all;
});
if (fill) { writeFileSync(src, md); console.log('filled excerpts'); process.exit(0); }
if (drift) process.exit(1);

const sha = git('rev-parse', githubRef).trim();
const excerpts = [];
for (const m of md.matchAll(fence)) {
  const [, kind, where, text] = m;
  const rows = excerpt(kind, where) ?? text.replace(/\n$/, '').split('\n').map(t => ({ n: t === '...' ? null : parseInt(t, 16), text: t }));
  const file = kind === 'c' ? where.split(':')[0] : 'rom';
  if (kind === 'c' && git('show', `${sha}:${file}`) !== readFileSync(repo + file, 'utf8')) throw new Error(`${file} differs from ${githubRef}; GitHub links would point at the wrong lines`);
  excerpts.push({ id: `src-${excerpts.length + 1}`, kind, where, file, rows, pos: m.index, keys: new Set(rows.filter(r => r.n !== null).map(r => r.n)) });
}

const refs = [];
const parseRef = ref => {
  const [file, spec] = ref.startsWith('rom:') ? ['rom', ref.slice(4)] : ref.split(':');
  const keys = ranges(spec).flatMap(([a, b]) => {
    if (file !== 'rom') return Array.from({ length: b - a + 1 }, (_, i) => a + i);
    return [a, b];
  });
  return { file, keys };
};
const mathSpans = text => [...text.matchAll(/\$\$[\s\S]+?\$\$|\$[^$\n]+?\$/g)].map(m => ({ start: m.index, end: m.index + m[0].length }));
const srcComment = /<!-- src\n([\s\S]*?)-->\n?/g;
for (const sm of md.matchAll(srcComment)) {
  const [, list] = sm, offset = sm.index, whole = md;
  const before = whole.slice(0, offset);
  const regionStart = Math.max(before.lastIndexOf('\n## '), before.lastIndexOf('\n### '), 0);
  for (const line of list.split('\n').filter(l => l.trim())) {
    const [tex, ref] = line.split(' => ').map(s => s.trim());
    const { file, keys } = parseRef(ref);
    const owners = excerpts.filter(e => e.file === file && keys.every(k => file === 'rom' ? (k >= Math.min(...e.keys) && k <= Math.max(...e.keys)) : e.keys.has(k)));
    if (!owners.length) throw new Error(`no excerpt covers ${ref}`);
    owners.sort((a, b) => Math.abs(a.pos - offset) - Math.abs(b.pos - offset));
    const owner = owners[0];
    const hits = mathSpans(whole).filter(s => s.start >= regionStart && s.end <= offset).filter(s => whole.slice(s.start, s.end).includes(tex));
    const count = hits.reduce((n, s) => n + whole.slice(s.start, s.end).split(tex).length - 1, 0);
    if (count !== 1) throw new Error(`"${tex}" found ${count} times before its src comment`);
    refs.push({ tex, owner: owner.id, keys: file === 'rom' ? [...owner.keys].filter(k => k >= keys[0] && k <= keys[1]) : keys, label: ref, at: md.indexOf(tex, hits[0].start) });
  }
}
for (const [i, r] of [...refs.entries()].sort((a, b) => b[1].at - a[1].at)) {
  md = md.slice(0, r.at) + `{\\color{#${(0xa00000 + i).toString(16)}}{${r.tex}}}` + md.slice(r.at + r.tex.length);
}
md = md.replace(srcComment, '');

const highlightLines = (kind, rows) => {
  if (kind === 'c') {
    const html = hljs.highlight(rowsText(rows), { language: 'c' }).value;
    const out = [];
    let stack = [], line = '';
    for (const tok of html.split(/(<span[^>]*>|<\/span>|\n)/)) {
      if (tok === '\n') { out.push(line + '</span>'.repeat(stack.length)); line = stack.join(''); }
      else if (tok.startsWith('<span')) { stack.push(tok); line += tok; }
      else if (tok === '</span>') { stack.pop(); line += tok; }
      else line += tok;
    }
    out.push(line + '</span>'.repeat(stack.length));
    return out;
  }
  return rows.map(r => {
    const m = r.text.match(/^([0-9a-f]+:)\s+((?:[0-9a-f]{4,8} ?)+?)\s{2,}(.*)$/);
    if (!m) return esc(r.text);
    return `<span class="addr">${m[1]} ${m[2].padEnd(10)}</span>  ${hljs.highlight(m[3], { language: 'armasm' }).value}`;
  });
};

const code = [];
md = md.replace(fence, () => {
  const e = excerpts[code.length];
  const lines = highlightLines(e.kind, e.rows);
  let label, link = '';
  if (e.kind === 'c') {
    const [file, spec] = e.where.split(':');
    const nums = [...e.keys];
    label = `${file}, lines ${spec.replace(/,/g, ', ')}`;
    link = `<a class="source-link" href="${githubRepo}/blob/${sha}/${file}#L${Math.min(...nums)}-L${Math.max(...nums)}" data-base="${githubRepo}/blob/${sha}/${file}">View on GitHub</a>`;
  } else {
    label = `ROM disassembly, ${ranges(e.where).map(([a, b]) => { const ks = [...e.keys].filter(k => k >= a && k < b); return `${hex(Math.min(...ks))}-${hex(Math.max(...ks))}`; }).join(', ')} (${e.kind === 'arm' ? 'ARM' : 'Thumb'})`;
  }
  const body = e.rows.map((r, i) => {
    const gutter = r.n === null || e.kind !== 'c' ? '' : `<span class="ln" aria-hidden="true">${r.n}</span>`;
    return `<span class="row${r.n === null ? ' gap' : ''}"${r.n === null ? '' : ` data-n="${r.n}"`}>${e.kind === 'c' ? gutter || '<span class="ln"></span>' : ''}<span class="tx">${lines[i] || ' '}</span></span>`;
  }).join('');
  code.push(`<details class="source-details" id="${e.id}"><summary>${esc(label)}</summary>${link}<pre><code class="${e.kind === 'c' ? 'lang-c' : 'lang-asm'}">${body}</code></pre></details>`);
  return `@@C${code.length - 1}@@`;
});

const markers = new Map(refs.map((r, i) => [`#${(0xa00000 + i).toString(16)}`, r]));
const stripMarkers = tex => {
  let outTex = tex, m;
  const open = /\{\\color\{#a[0-9a-f]{5}\}\{/;
  while ((m = outTex.match(open))) {
    let depth = 1, j = m.index + m[0].length;
    for (; depth; j++) depth += outTex[j] === '{' ? 1 : outTex[j] === '}' ? -1 : 0;
    outTex = outTex.slice(0, m.index) + outTex.slice(m.index + m[0].length, j - 1) + outTex.slice(j + 1);
  }
  return outTex;
};
const math = [];
const stash = (tex, display) => {
  let m = katex.renderToString(tex.trim(), { displayMode: display, throwOnError: true, output: 'mathml' });
  m = m.replace(/<mstyle mathcolor="(#a[0-9a-f]{5})">/g, (_, color) => {
    const r = markers.get(color);
    return `<mstyle class="src-ref" tabindex="0" role="button" aria-controls="${r.owner}" aria-expanded="false" title="Show ${esc(r.label)}" data-target="${r.owner}" data-lines="${r.keys.join(' ')}">`;
  });
  m = m.replace(/<annotation encoding="application\/x-tex">[\s\S]*?<\/annotation>/, () => `<annotation encoding="application/x-tex">${esc(stripMarkers(tex.trim()))}</annotation>`);
  math.push(display ? `<div class="math">${m}</div>` : m);
  return `@@M${math.length - 1}@@`;
};
md = md.replace(/\$\$([\s\S]+?)\$\$/g, (_, t) => stash(t, true));
md = md.replace(/\$([^$\n]+?)\$/g, (_, t) => stash(t, false));

const tokens = marked.lexer(md);
const title = tokens.find(t => t.type === 'heading' && t.depth === 1).text;
const sections = [];
const slug = s => s.toLowerCase().replace(/[^a-z0-9]+/g, '-').replace(/^-|-$/g, '');
const renderer = new marked.Renderer();
renderer.heading = (text, level, raw) => {
  if (level === 1) return '';
  const id = slug(raw);
  if (level === 2) sections.push({ id, text });
  return `<h${level} id="${id}">${text}</h${level}>\n`;
};
renderer.table = (header, body) => `<div class="table-wrap"><table><thead>${header}</thead><tbody>${body}</tbody></table></div>\n`;
let body = marked.parser(tokens, { renderer });
body = body.replace(/<p>(@@M\d+@@)<\/p>/g, '$1');
body = body.replace(/@@M(\d+)@@/g, (_, i) => math[+i]);
body = body.replace(/<p>(@@C\d+@@)<\/p>/g, '$1').replace(/@@C(\d+)@@/g, (_, i) => code[+i]);
if (/@@[MC]/.test(body) || /[$]/.test(body.replace(/<annotation[\s\S]*?<\/annotation>/g, '').replace(/<pre[\s\S]*?<\/pre>/g, ''))) throw new Error('unrendered math left');

const rail = sections.map(s => `<a href="#${s.id}">${s.text}</a>`).join('');
const options = sections.map(s => `<option value="${s.id}">${s.text}</option>`).join('');
const page = `<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta name="color-scheme" content="dark">
  <meta name="theme-color" content="#0d1318">
  <title>Zoids Legacy Battle Mechanics</title>
  <style>
@font-face { font-family: "Xolonium"; src: url("fonts/Xolonium-Bold.ttf") format("truetype"); font-weight: 700; font-display: swap; }
:root {
  color-scheme: dark;
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
  color: var(--text);
  background: var(--background);
  font-synthesis: none;
  --background: #0d1318;
  --panel: #131c22;
  --raised: #1a272e;
  --text: #e9e8dd;
  --muted: #96a0a1;
  --line: #253037;
  --rail: #586164;
  --amber: #f09e38;
  --amber-bright: #ffc36c;
  --bronze: #ae7838;
  --teal: #54a18b;
  --teal-bright: #79c7b1;
  --heading-font: "Xolonium", Arial, sans-serif;
}
* { box-sizing: border-box; }
.visually-hidden { position: absolute; width: 1px; height: 1px; overflow: hidden; clip-path: inset(50%); white-space: nowrap; }
html { scroll-padding-top: 16px; }
body { margin: 0; background: var(--background); }
a { color: inherit; text-decoration: none; }
a:hover { text-decoration: underline; }
:focus-visible { outline: 2px solid var(--amber); outline-offset: 3px; }
h1, h2, h3, p { margin-top: 0; }
h1, h2, h3 { font-family: var(--heading-font); font-weight: 700; }
h1 { font-size: 21px; margin-bottom: 20px; }
h2 { font-size: 18px; margin: 40px 0 12px; }
h3 { font-size: 15px; margin: 28px 0 10px; }
p, li { font-size: 14px; line-height: 1.6; }
ul, ol { padding-left: 22px; margin: 0 0 16px; }
li { margin-bottom: 6px; }
code { font-family: ui-monospace, SFMono-Regular, Consolas, monospace; font-size: 12px; }
select { font: inherit; color: inherit; border: 1px solid var(--rail); border-radius: 2px; padding: 7px 10px; background: var(--panel); }
.site-header { display: flex; align-items: center; gap: 24px; padding: 0 24px; min-height: 58px; background: var(--panel); border-bottom: 1px solid var(--bronze); }
.brand { font: 700 15px/1.5 var(--heading-font); white-space: nowrap; }
.brand span { color: var(--amber); }
.site-header nav { display: flex; align-items: stretch; gap: 4px; }
.site-header nav > a { display: block; padding: 20px 10px 18px; font-size: 13px; color: var(--muted); white-space: nowrap; border-bottom: 2px solid transparent; }
.site-header nav > a:hover { text-decoration: none; color: var(--text); }
main { display: grid; grid-template-columns: 160px minmax(0, 760px); gap: 24px; padding: 20px 24px 60px; }
.sections { position: sticky; top: 16px; align-self: start; padding-top: 2px; }
.sections a { display: block; padding: 10px 10px 10px 12px; border-left: 2px solid transparent; font-size: 13px; color: var(--muted); }
.sections a:hover { text-decoration: none; color: var(--text); background: var(--raised); }
.sections a.active { border-left-color: var(--amber); color: var(--amber-bright); background: var(--panel); }
article { min-width: 0; }
article > h2:first-of-type { margin-top: 0; }
.section-select { display: none; width: 100%; height: 36px; font-size: 12px; margin-bottom: 16px; }
.table-wrap { width: 100%; overflow-x: auto; margin-bottom: 20px; }
table { width: 100%; border-collapse: collapse; font-size: 12px; text-align: left; }
th, td { padding: 12px 10px; border-bottom: 1px solid var(--line); vertical-align: top; }
th { font-weight: 500; color: var(--muted); }
math { font-size: 1.1em; }
.math { margin: 14px 0 18px; overflow-x: auto; overflow-y: hidden; }
.src-ref { color: var(--teal-bright); cursor: pointer; text-decoration: underline; text-decoration-color: var(--teal); text-underline-offset: 3px; }
.src-ref:hover { color: var(--amber-bright); }
.src-ref:focus-visible { outline-offset: 2px; }
.source-details { padding: 16px 0; border-top: 1px solid var(--line); }
.source-details summary { font-size: 12px; cursor: pointer; color: var(--muted); }
.source-details[open] summary { margin-bottom: 10px; }
.source-link { display: inline-block; margin-bottom: 10px; font-size: 12px; text-decoration: underline; }
pre { position: relative; margin: 0; padding: 16px 0; background: var(--background); border: 1px solid var(--line); font-family: ui-monospace, SFMono-Regular, Consolas, monospace; font-size: 11px; line-height: 1.6; white-space: pre; overflow: auto; max-height: 400px; }
pre code { font-size: inherit; display: inline-block; min-width: 100%; }
.row { display: block; padding: 0 16px 0 0; border-left: 2px solid transparent; }
.lang-asm .row { padding-left: 16px; }
.row.hit { background: #3b2b18; border-left-color: var(--amber); }
.row.gap .tx { color: var(--muted); }
.ln { display: inline-block; width: 4.5em; padding-right: 1.2em; text-align: right; color: var(--muted); user-select: none; }
.addr { color: var(--muted); }
.hljs-keyword, .hljs-type, .hljs-meta .hljs-keyword { color: var(--amber); }
.hljs-built_in { color: var(--teal-bright); }
.hljs-number, .hljs-literal { color: var(--teal-bright); }
.hljs-string { color: var(--amber-bright); }
.hljs-comment { color: var(--muted); font-style: italic; }
.hljs-meta { color: var(--bronze); }
.hljs-title { color: var(--text); font-weight: 600; }
@media (max-width: 900px) {
  main { grid-template-columns: 135px minmax(0, 1fr); gap: 18px; }
  .sections a { padding-left: 8px; font-size: 12px; }
}
@media (max-width: 640px) {
  .site-header { padding: 12px 16px 0; gap: 8px; flex-wrap: wrap; }
  .brand { font-size: 14px; white-space: normal; }
  .site-header nav { width: 100%; flex-wrap: wrap; gap: 0 2px; }
  .site-header nav > a { padding: 12px 5px; font-size: 12px; }
  main { display: block; padding: 16px 16px 48px; }
  .sections { display: none; }
  .section-select { display: block; }
  .ln { width: 3.5em; padding-right: 0.8em; }
}
@media (prefers-reduced-motion: no-preference) { html { scroll-behavior: smooth; } }
  </style>
</head>
<body>
  <header class="site-header">
    <a class="brand" href="./index.html"><span>Zoids Legacy</span> Battle Mechanics</a>
    <nav aria-label="Site">
      <a href="./rom-tool.html">Asset extractor</a>
    </nav>
  </header>
  <main>
    <nav class="sections" aria-label="Contents">${rail}</nav>
    <article>
      <h1 class="visually-hidden">${title}</h1>
      <select class="section-select" aria-label="Jump to section">${options}</select>
${body}    </article>
  </main>
  <script>
const links = [...document.querySelectorAll('.sections a')];
const targets = links.map(a => document.getElementById(a.hash.slice(1)));
const select = document.querySelector('.section-select');
select.addEventListener('change', () => document.getElementById(select.value).scrollIntoView());
const mark = () => {
  let current = 0;
  targets.forEach((t, i) => { if (t.getBoundingClientRect().top < 120) current = i; });
  if (innerHeight + scrollY >= document.documentElement.scrollHeight - 4) current = targets.length - 1;
  links.forEach((a, i) => { a.classList.toggle('active', i === current); if (i === current) a.setAttribute('aria-current', 'location'); else a.removeAttribute('aria-current'); });
  select.value = targets[current].id;
};
addEventListener('scroll', mark, { passive: true });
mark();
const scrollable = () => document.querySelectorAll('.math, .table-wrap, pre').forEach(el => {
  if (el.scrollWidth > el.clientWidth + 1 || el.scrollHeight > el.clientHeight + 1) el.setAttribute('tabindex', '0'); else el.removeAttribute('tabindex');
});
addEventListener('resize', scrollable);
document.addEventListener('toggle', scrollable, true);
scrollable();
const clearHits = () => {
  document.querySelectorAll('.row.hit').forEach(r => { r.classList.remove('hit'); r.removeAttribute('aria-current'); });
  document.querySelectorAll('.src-ref[aria-expanded="true"]').forEach(r => r.setAttribute('aria-expanded', 'false'));
};
document.addEventListener('toggle', e => { if (e.target.matches && e.target.matches('.source-details') && !e.target.open) {
  e.target.querySelectorAll('.row.hit').forEach(r => { r.classList.remove('hit'); r.removeAttribute('aria-current'); });
  document.querySelectorAll('.src-ref[aria-controls="' + e.target.id + '"]').forEach(r => r.setAttribute('aria-expanded', 'false'));
} }, true);
const show = (ref, viaKeyboard) => {
  const details = document.getElementById(ref.getAttribute('data-target'));
  const wanted = new Set(ref.getAttribute('data-lines').split(' '));
  clearHits();
  details.open = true;
  ref.setAttribute('aria-expanded', 'true');
  const rows = [...details.querySelectorAll('.row[data-n]')].filter(r => wanted.has(r.dataset.n));
  rows.forEach(r => { r.classList.add('hit'); r.setAttribute('aria-current', 'true'); });
  if (!rows.length) return;
  const link = details.querySelector('.source-link');
  if (link) link.href = link.dataset.base + '#L' + rows[0].dataset.n + (rows.length > 1 ? '-L' + rows.at(-1).dataset.n : '');
  const pre = details.querySelector('pre');
  details.scrollIntoView({ block: 'nearest' });
  pre.scrollTop = rows[0].offsetTop - pre.clientHeight / 3;
  if (viaKeyboard) { if (!pre.hasAttribute('tabindex')) pre.setAttribute('tabindex', '-1'); pre.focus({ preventScroll: true }); }
};
document.addEventListener('click', e => { const ref = e.target.closest('.src-ref'); if (ref) show(ref, false); });
document.addEventListener('keydown', e => { const ref = e.target.closest && e.target.closest('.src-ref'); if (ref && (e.key === 'Enter' || e.key === ' ')) { e.preventDefault(); show(ref, true); } });
  </script>
</body>
</html>
`;
writeFileSync(out, page);
console.log(`sections=${sections.length} math=${math.length} excerpts=${excerpts.length} links=${refs.length} bytes=${page.length}`);
