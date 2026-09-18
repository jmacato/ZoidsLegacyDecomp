'use strict';
const $ = id => document.getElementById(id);
let font, state, byCode, byChar, timer, saving = false, revision = 0, savedRevision = 0;
let previewLayout = [];
const palette = ['#e7f7d6', '#adb59c', '#737b6b', '#394239'];
const label = glyph => glyph.char === ' ' ? 'Space' : glyph.char;
const key = () => `${$('left').value}:${$('right').value}`;
const advance = glyph => state.advances[glyph.code] ?? (state.spacing === 'original' ? 8 : glyph.advance);
const base = glyph => advance(glyph) + (state.letter_spacing || 0);
const trim = glyph => state.spacing === 'original' ? 0 : glyph.left;
const status = text => { $('save-state').textContent = text; };

function changed() {
  revision++;
  localStorage.setItem('zoids-kerning-pending', JSON.stringify(state));
  status('Unsaved changes…');
  clearTimeout(timer);
  timer = setTimeout(save, 350);
  render();
}
async function save() {
  if (saving) return;
  saving = true;
  try {
    while (savedRevision < revision) {
      const current = revision;
      const response = await fetch('/choices', {method:'POST', headers:{'Content-Type':'application/json'}, body:JSON.stringify(state)});
      const result = await response.json();
      if (!response.ok) throw new Error(result.error || 'Save failed');
      savedRevision = current;
    }
    localStorage.removeItem('zoids-kerning-pending');
    status('Saved to kerning-choices.json · ' + new Date().toLocaleTimeString());
  } catch (error) {
    status('Not saved to disk: ' + error.message + '. Retrying…');
    timer = setTimeout(save, 2000);
  } finally { saving = false; }
}
function selectPair(value) {
  const [left, right] = value.split(':');
  if (!byCode.has(left) || !byCode.has(right)) return;
  $('left').value = left; $('right').value = right;
  render();
}
function setPair(value) {
  if (!Number.isInteger(value)) return;
  value = Math.max(-6, Math.min(8, value));
  if (value === 0) delete state.pairs[key()]; else state.pairs[key()] = value;
  changed();
}
function layout(text) {
  const lines = text.split('\n');
  const placed = [], missing = new Set();
  let extent = 0;
  lines.forEach((line, row) => {
    let pen = 2, previous = null;
    [...line].forEach(char => {
      let glyph = byChar.get(char);
      if (!glyph) { missing.add(char); glyph = byChar.get('?'); }
      if (previous) pen += Math.max(1, base(previous) + (state.pairs[`${previous.code}:${glyph.code}`] || 0));
      placed.push({glyph, pen, row, char});
      extent = Math.max(extent, pen + (state.spacing === 'original' ? glyph.left + glyph.width : glyph.width));
      previous = glyph;
    });
  });
  return {placed, extent, rows:lines.length, missing:[...missing]};
}
function paint(canvas, data, scale, width, guides) {
  const native = document.createElement('canvas');
  native.width = Math.max(width + 8, data.extent + 4);
  native.height = Math.max(20, data.rows * 20);
  const ctx = native.getContext('2d');
  ctx.fillStyle = palette[0]; ctx.fillRect(0, 0, native.width, native.height);
  const ink = new Uint8Array(native.width * native.height);
  let overlaps = 0;
  for (const item of data.placed) {
    for (let y = 0; y < 16; y++) for (let x = 0; x < 8; x++) {
      const value = item.glyph.pixels[y * 8 + x];
      if (!value) continue;
      const dx = item.pen + x - trim(item.glyph), dy = item.row * 20 + y + 2;
      if (dx < 0 || dx >= native.width) continue;
      const index = dy * native.width + dx;
      if (ink[index]) overlaps++;
      ink[index] = Math.max(ink[index], value);
      ctx.fillStyle = palette[ink[index]]; ctx.fillRect(dx, dy, 1, 1);
    }
  }
  canvas.width = native.width * scale; canvas.height = native.height * scale;
  const output = canvas.getContext('2d'); output.imageSmoothingEnabled = false;
  output.drawImage(native, 0, 0, canvas.width, canvas.height);
  if (guides) {
    output.strokeStyle = '#506c6430'; output.lineWidth = 1;
    for (let x = 0; x <= canvas.width; x += scale) { output.beginPath(); output.moveTo(x+.5,0); output.lineTo(x+.5,canvas.height); output.stroke(); }
    for (let y = 0; y <= canvas.height; y += scale) { output.beginPath(); output.moveTo(0,y+.5); output.lineTo(canvas.width,y+.5); output.stroke(); }
    output.strokeStyle = '#19729b'; output.setLineDash([4,3]);
    for (const item of data.placed) { output.beginPath(); output.moveTo(item.pen*scale+.5,0); output.lineTo(item.pen*scale+.5,canvas.height); output.stroke(); }
    output.setLineDash([]);
  } else {
    output.strokeStyle = '#ba563d'; output.setLineDash([5,4]);
    output.beginPath(); output.moveTo((width+2)*scale+.5,0); output.lineTo((width+2)*scale+.5,canvas.height); output.stroke(); output.setLineDash([]);
  }
  return overlaps;
}
function pairButton(value, count) {
  const [a,b] = value.split(':');
  const button = document.createElement('button');
  button.textContent = [a,b].map(code => byCode.get(code).char === ' ' ? '␣' : byCode.get(code).char).join('');
  if (value in state.pairs) button.textContent += ` ${state.pairs[value] > 0 ? '+' : ''}${state.pairs[value]}`;
  button.classList.toggle('active', value === key());
  button.classList.toggle('changed', value in state.pairs);
  button.title = count ? `${count} occurrences` : 'Edited pair';
  button.onclick = () => selectPair(value);
  return button;
}
function render() {
  const first = byCode.get($('left').value), second = byCode.get($('right').value);
  const value = state.pairs[key()] || 0;
  $('adjust').value = $('slider').value = value;
  $('spacing').value = state.spacing;
  if (document.activeElement !== $('advance')) $('advance').value = advance(first);
  if (document.activeElement !== $('letter-spacing')) $('letter-spacing').value = state.letter_spacing || 0;
  $('letter-spacing-slider').value = state.letter_spacing || 0;
  for (const input of document.querySelectorAll('[data-advance]')) {
    const glyph = byCode.get(input.dataset.advance);
    if (document.activeElement !== input) input.value = advance(glyph);
    input.closest('.letter-cell').classList.toggle('edited', glyph.code in state.advances);
  }
  const pair = layout(first.char + second.char);
  const overlaps = paint($('pair'), pair, 12, 30, $('grid').checked);
  $('pair-info').textContent = `Second origin: ${pair.placed[1].pen - pair.placed[0].pen} px after the first. Ink overlaps: ${overlaps} pixels.`;
  $('readout').textContent = `${label(first)}: ${first.width} px ink · ${base(first)} px advance\n${label(second)}: ${second.width} px ink · ${base(second)} px advance` + (base(first)+value < 1 ? '\nAdvance is clamped to one pixel.' : '');
  const data = layout($('text').value); previewLayout = data.placed;
  paint($('preview'), data, Number($('zoom').value), Number($('width').value), false);
  const overflow = Math.max(0, data.extent - 2 - Number($('width').value));
  $('preview-info').textContent = `${Math.max(0,data.extent-2)} px maximum ink width. ` + (overflow ? `${overflow} px outside the text box.` : 'Text fits the box.') + (data.missing.length ? ` Unsupported characters shown as ?: ${data.missing.join(' ')}` : '');
  const filter = $('filter').value;
  $('common').replaceChildren(...font.common.filter(p => !filter || p.key.split(':').some(c => byCode.get(c).char.includes(filter))).map(p => pairButton(p.key,p.count)));
  const edited = Object.keys(state.pairs).sort().map(p => pairButton(p));
  $('edited').replaceChildren(...edited);
  if (!edited.length) $('edited').textContent = 'No pair adjustments yet.';
}
function renderLetters() {
  const mode = $('letter-filter').value;
  const glyphs = font.glyphs.filter(g => mode === 'all' || (mode === 'edited' ? g.code in state.advances : /^[\x20-\x7e“”‘’…]$/.test(g.char)));
  $('letters').replaceChildren(...glyphs.map(g => {
    const cell = document.createElement('div'); cell.className = 'letter-cell';
    const labelElement = document.createElement('label'); labelElement.textContent = label(g);
    const input = document.createElement('input'); input.type = 'number'; input.min = 1; input.max = 16;
    input.value = advance(g); input.dataset.advance = g.code; input.setAttribute('aria-label', `Default advance for ${label(g)}`);
    const reset = document.createElement('button'); reset.textContent = 'Reset';
    input.oninput = () => { const n = Number(input.value); if (input.value !== '' && Number.isInteger(n) && n >= 1 && n <= 16) { state.advances[g.code] = n; changed(); } };
    reset.onclick = () => { delete state.advances[g.code]; input.value = advance(g); changed(); };
    labelElement.append(input); cell.append(labelElement, reset); return cell;
  }));
  render();
}
async function start() {
  const responses = await Promise.all([fetch('/font'), fetch('/choices')]);
  if (responses.some(r => !r.ok)) throw new Error('Could not load editor data.');
  [font,state] = await Promise.all(responses.map(r => r.json()));
  byCode = new Map(font.glyphs.map(g => [g.code,g])); byChar = new Map(font.glyphs.map(g => [g.char,g]));
  for (const id of ['left','right']) for (const glyph of font.glyphs) {
    const option = document.createElement('option'); option.value = glyph.code; option.textContent = `${label(glyph)} · ${glyph.code}`; $(id).append(option);
  }
  $('sample').append(new Option('Choose a script entry…',''));
  font.samples.forEach((sample,i) => $('sample').append(new Option(`${i+1}. ${sample.label} — ${sample.text.replaceAll('\n',' ').slice(0,65)}`,String(i))));
  $('left').value = byChar.get('A').code; $('right').value = byChar.get('V').code;
  for (const id of ['left','right','grid','zoom','width','filter']) $(id).addEventListener('input',render);
  $('text').addEventListener('input',() => { localStorage.setItem('zoids-kerning-preview',$('text').value); render(); });
  $('sample').onchange = () => { if ($('sample').value !== '') { $('text').value = font.samples[Number($('sample').value)].text; render(); } };
  $('adjust').oninput = () => { if ($('adjust').value !== '') setPair(Number($('adjust').value)); };
  $('slider').oninput = () => setPair(Number($('slider').value));
  $('minus').onclick = () => setPair((state.pairs[key()] || 0)-1);
  $('plus').onclick = () => setPair((state.pairs[key()] || 0)+1);
  $('reset-pair').onclick = () => setPair(0);
  $('letter-filter').onchange = renderLetters;
  const setDefaultSpacing = value => { if (Number.isInteger(value) && value >= -4 && value <= 8) { state.letter_spacing = value; changed(); } };
  $('letter-spacing').oninput = () => { if ($('letter-spacing').value !== '') setDefaultSpacing(Number($('letter-spacing').value)); };
  $('letter-spacing-slider').oninput = () => setDefaultSpacing(Number($('letter-spacing-slider').value));
  $('reset-letter-spacing').onclick = () => { $('letter-spacing').value = 0; setDefaultSpacing(0); };
  $('spacing').onchange = () => { state.spacing = $('spacing').value; changed(); };
  $('advance').oninput = () => { const n = Number($('advance').value); if (Number.isInteger(n) && n>=1 && n<=16) { state.advances[$('left').value]=n; changed(); } };
  $('reset-advance').onclick = () => { delete state.advances[$('left').value]; changed(); };
  $('preview').onclick = event => {
    const rect = $('preview').getBoundingClientRect(), scale = Number($('zoom').value);
    const x = (event.clientX-rect.left)/scale, row = Math.floor((event.clientY-rect.top)/scale/20);
    const line = previewLayout.filter(p => p.row === row);
    let index = -1;
    line.forEach((p,i) => { if (p.pen<=x) index=i; });
    if (index>=0 && index<line.length-1) selectPair(`${line[index].glyph.code}:${line[index+1].glyph.code}`);
  };
  $('export').onclick = () => { const url=URL.createObjectURL(new Blob([JSON.stringify(state,null,2)+'\n'],{type:'application/json'})); const link=document.createElement('a'); link.href=url; link.download='kerning-choices.json'; link.click(); setTimeout(()=>URL.revokeObjectURL(url),1000); };
  $('import').onchange = async () => {
    try {
      const candidate=JSON.parse(await $('import').files[0].text());
      const response=await fetch('/choices',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(candidate)});
      const result=await response.json(); if(!response.ok) throw new Error(result.error);
      state=candidate; changed();
    } catch(error) { status('Import failed: '+error.message); }
  };
  const preview=localStorage.getItem('zoids-kerning-preview'); if(preview) $('text').value=preview;
  const pending=localStorage.getItem('zoids-kerning-pending');
  if(pending) {
    const button=document.createElement('button'); button.textContent='Restore unsaved browser draft';
    button.onclick=()=>{ try { state=JSON.parse(pending); changed(); button.remove(); } catch(error) { status(error.message); } };
    $('save-state').after(button);
  }
  window.addEventListener('beforeunload',event=>{ if(savedRevision<revision) { event.preventDefault(); event.returnValue=''; } });
  status('Autosave ready · kerning-choices.json'); renderLetters();
}
start().catch(error=>status('Could not start: '+error.message));
