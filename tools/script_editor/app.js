'use strict';
const $ = selector => document.querySelector(selector);
const languages = ['en', 'es'];
const state = {entries: [], byOffset: new Map(), contexts: new Map(), currentContext: null,
  selected: null, savedText: '', page: 0, previewPage: 0, previewResult: null,
  lang: new URLSearchParams(location.search).get('lang') || localStorage.getItem('zoidsEditorLanguage') || 'en',
  translateUi: localStorage.getItem('zoidsEditorTranslateUi') !== 'false'};
if (!languages.includes(state.lang)) state.lang = 'en';
const uiLanguage = () => state.translateUi ? state.lang : 'en';
function t(key, values = {}) {
  const one = Number(values.count) === 1 ? `${key}.one` : null;
  const text = (one && (UI_TEXT[uiLanguage()]?.[one] ?? UI_TEXT.en[one])) ?? UI_TEXT[uiLanguage()]?.[key] ?? UI_TEXT.en[key] ?? key;
  return text.replace(/\{(\w+)\}/g, (match, name) => name in values ? values[name] : match);
}
const listItem = (key, index) => t(key).split('|')[index];
const category = name => UI_TEXT[uiLanguage()]?.[`category.${name}`] ?? name;
const command = name => (COMMAND_TEXT[uiLanguage()] || []).reduce(
  (text, [pattern, replacement]) => pattern.test(text) ? text.replace(pattern, replacement) : text, name);
function applyStaticText() {
  document.documentElement.lang = uiLanguage();
  for (const element of document.querySelectorAll('[data-i18n]')) element.textContent = t(element.dataset.i18n);
  for (const [attribute, key] of [['placeholder', 'i18nPlaceholder'], ['aria-label', 'i18nAriaLabel'], ['title', 'i18nTitle']])
    for (const element of document.querySelectorAll(`[data-${key.replace(/[A-Z]/g, c => '-' + c.toLowerCase())}]`))
      element.setAttribute(attribute, t(element.dataset[key]));
  for (const option of $('#control-type').options) option.textContent = t(`control.${option.value}.name`);
  for (const option of [...$('#category').options].slice(1)) option.textContent = category(option.value);
  $('#draft-label').textContent = t(`draft.${state.lang}`);
  $('#translate-ui').checked = state.translateUi;
}
$('#player-name').value = localStorage.getItem('zoidsPreviewPlayerName') || 'Zeru';
const pageSize = 120;
const palette = {
  0: '#e7f7d6',
  5: '#adb59c', 6: '#737b6b', 7: '#394239',
  9: '#e7ad8c', 10: '#e76342', 11: '#e71800',
  13: '#bdadde', 14: '#9463ef', 15: '#7321ff'
};
let previewTimer;
let previewRevision = 0;
let creditsPreview;
let creditsAnimation;
const controlInfo = {
  '01': {syntax: '{01 nn}', labels: 1, max: 2},
  '02': {syntax: '{02 xx yy}', labels: 2, max: 255},
  '03': {syntax: '{03}', labels: 0},
  '04': {syntax: '{04 nn}', labels: 1, max: 2},
  '06': {syntax: '{06 nn}', labels: 1, max: 255},
  '07': {syntax: '{07 xx yy}', labels: 2, max: 255},
  '08': {syntax: '{08 ll rr}', labels: 2, max: 255},
  '0A': {syntax: '{0A}', labels: 0}
};
const controlName = code => t(`control.${code}.name`);
const controlHelp = code => t(`control.${code}.help`);
const controlSyntax = code => code === '0A' ? t('control.0A.syntax') : (controlInfo[code]?.syntax ?? '{00}');
const controlLabel = (code, index) => t(`control.${code}.labels`).split('|')[index];

function renderControlGuide() {
  const guide = $('#control-guide-list');
  guide.replaceChildren();
  for (const code of ['00', ...Object.keys(controlInfo)]) {
    const row = document.createElement('section');
    row.className = 'guide-item';
    row.dataset.control = code;
    const heading = document.createElement('h3');
    const syntax = document.createElement('code');
    syntax.textContent = controlSyntax(code);
    heading.append(syntax, ` ${controlName(code)}`);
    const body = document.createElement('p');
    body.textContent = controlHelp(code);
    row.append(heading, body);
    guide.append(row);
  }
}

function updateControlFields() {
  const code = $('#control-type').value;
  const info = controlInfo[code];
  for (const [index, suffix] of ['a', 'b'].entries()) {
    const input = $(`#control-${suffix}`);
    const label = $(`#control-${suffix}-label`);
    label.hidden = input.hidden = index >= info.labels;
    if (!input.hidden) {
      label.textContent = controlLabel(code, index);
      input.max = index === 0 ? info.max : 255;
      if (Number(input.value) > Number(input.max)) input.value = input.max;
    }
  }
  const help = state.selected?.category === 'ending credits' && code === '01' ? t('credits.colorHelp') : controlHelp(code);
  $('#control-help').textContent = `${controlSyntax(code)}: ${help}`;
  for (const row of $('#control-guide-list').children)
    row.classList.toggle('active', row.dataset.control === $('#control-type').value);
}

function controlAtCaret() {
  const draft = $('#draft');
  if (draft.selectionStart !== draft.selectionEnd) return null;
  const cursor = draft.selectionStart;
  for (const match of draft.value.matchAll(/\{[0-9A-Fa-f]{2}(?: [0-9A-Fa-f]{2})*\}/g)) {
    if (match.index <= cursor && cursor < match.index + match[0].length) {
      const bytes = match[0].slice(1, -1).split(' ');
      const info = controlInfo[bytes[0].toUpperCase()];
      if (info && bytes.length === info.labels + 1)
        return {start: match.index, end: match.index + match[0].length, bytes};
    }
  }
  return null;
}

function readControlAtCaret() {
  const match = controlAtCaret();
  if (!match) return;
  $('#control-type').value = match.bytes[0].toUpperCase();
  updateControlFields();
  for (const [index, suffix] of ['a', 'b'].entries()) {
    if (match.bytes[index + 1]) $(`#control-${suffix}`).value = parseInt(match.bytes[index + 1], 16);
  }
}

function insertControl() {
  const draft = $('#draft');
  const type = $('#control-type').value;
  if ((state.selected?.kind === 'menu' || state.selected?.templateFormat) && type === '02')
    throw Error(t('control.noTemplatePosition'));
  const info = controlInfo[type];
  const values = ['a', 'b'].slice(0, info.labels).map(suffix => {
    const input = $(`#control-${suffix}`);
    const value = Number(input.value);
    if (!input.value || !Number.isInteger(value) || value < 0 || value > Number(input.max))
      throw Error(t('control.badInput', {label: input.labels[0].textContent, max: input.max}));
    return value.toString(16).toUpperCase().padStart(2, '0');
  });
  const token = type === '0A' ? '\n' : `{${[type, ...values].join(' ')}}`;
  const match = controlAtCaret();
  const start = match?.start ?? draft.selectionStart;
  const end = match?.end ?? draft.selectionEnd;
  draft.setRangeText(token, start, end, 'select');
  draft.focus();
  draft.dispatchEvent(new Event('input', {bubbles: true}));
}

function controlPreviewLabel(bytes, playerName, result) {
  const [code, first, second] = bytes.split(' ').map(part => parseInt(part, 16));
  switch (code) {
    case 0x00: return t('preview.end');
    case 0x01: return t('preview.color', {color: listItem(result.profile === 'credits' ? 'color.credits' : 'color.text', first) ?? first});
    case 0x02: return t('preview.position', {x: first, y: second});
    case 0x03: return t('preview.player', {name: playerName});
    case 0x04: return t('preview.align', {side: listItem('side', first) ?? first});
    case 0x06: return t('preview.advance', {pixels: first});
    case 0x07:
      if (result.profile === 'menu' && result.windowSource !== 'unknown')
        return t('preview.anchorWindow', {id: result.windowId, x: first, y: second,
          where: t(result.windowSource === 'script' ? 'preview.screen' : 'preview.estimated'),
          px: result.textX + first * 8, py: result.textY + second * 8});
      return t('preview.anchor', {x: first, y: second});
    case 0x08: return t('preview.area', {left: first, right: second});
    case 0x0A: return t('preview.newLine');
    default: return t('preview.control', {bytes});
  }
}

function label(entry) {
  return entry.text.replace(/\{[^}]+\}/g, ' ').replace(/\s+/g, ' ').trim() || t('label.controls');
}
function searchValues(entry) {
  return [entry.offset, entry.text, entry.original, entry.reference, entry.category];
}
function editStatus(entry, status) {
  if (status === 'clipped') return Boolean(entry.clipped);
  return (status === 'edited') === (entry.text !== entry.original);
}
function filtered() {
  const query = $('#search').value.trim().toLowerCase();
  const kind = $('#kind').value;
  const chosenCategory = $('#category').value;
  return state.entries.filter(entry =>
    (!kind || entry.kind === kind) &&
    (!chosenCategory || entry.category === chosenCategory) &&
    (!$('#changed').value || editStatus(entry, $('#changed').value)) &&
    (!query || searchValues(entry)
      .some(value => value && value.toLowerCase().includes(query))));
}
function renderList() {
  const entries = filtered();
  const list = $('#list');
  const selectedIndex = entries.indexOf(state.selected);
  if (selectedIndex >= (state.page + 1) * pageSize) state.page = Math.floor(selectedIndex / pageSize);
  const visible = entries.slice(0, (state.page + 1) * pageSize);
  $('#count').textContent = t('list.count', {count: entries.length.toLocaleString(uiLanguage())});
  // Keep the first visible row where it was; rebuilding the rows drops the browser's own anchor.
  const listTop = list.getBoundingClientRect().top;
  const anchor = [...list.children].find(item => item.getBoundingClientRect().bottom > listTop);
  const anchorOffset = anchor?.dataset.offset;
  const anchorGap = anchor ? anchor.getBoundingClientRect().top - listTop : 0;
  list.replaceChildren();
  for (const entry of visible) {
    const item = document.createElement('button');
    item.dataset.offset = entry.offset;
    item.className = 'item' + (entry.offset === state.selected?.offset ? ' selected' : '');
    item.type = 'button';
    item.setAttribute('role', 'option');
    item.setAttribute('aria-selected', String(entry.offset === state.selected?.offset));
    const top = document.createElement('div');
    top.className = 'item-top';
    const place = document.createElement('span');
    place.textContent = entry.offset;
    const type = document.createElement('span');
    type.textContent = category(entry.category || entry.kind);
    top.append(place, type);
    const title = document.createElement('strong');
    title.textContent = label(entry);
    item.append(top, title);
    if (entry.text !== entry.original || entry.clipped) {
      const changed = document.createElement('em');
      changed.textContent = [entry.text !== entry.original && t('list.edited'), entry.clipped && t('list.clipped')]
        .filter(Boolean).join(' · ');
      item.append(changed);
    }
    item.addEventListener('click', () => select(entry));
    list.append(item);
  }
  const kept = anchorOffset && list.querySelector(`[data-offset="${anchorOffset}"]`);
  if (kept) list.scrollTop += kept.getBoundingClientRect().top - list.getBoundingClientRect().top - anchorGap;
  const chosen = state.selected && list.querySelector(`[data-offset="${state.selected.offset}"]`);
  if (chosen) {
    const box = chosen.getBoundingClientRect(), view = list.getBoundingClientRect();
    if (box.top < view.top || box.bottom > view.bottom) chosen.scrollIntoView({block: 'center'});
  }
}
function select(entry) {
  state.selected = entry;
  state.savedText = entry.text;
  $('#empty').hidden = true;
  $('#detail').hidden = false;
  $('#detail').classList.toggle('credits-preview', entry.category === 'ending credits');
  $('#type').textContent = t(`kindBadge.${entry.kind}`);
  $('#offset').textContent = entry.offset;
  $('#context').replaceChildren(category(entry.category));
  const role = peer => peer.pairRole === 'Name' ? 'Description' : peer.pairRole === 'Description' ? 'Name'
    : peer.category === 'menu title' ? 'Title'
    : entry.category === 'story choice' ? 'Question' : peer.category === 'story choice' ? 'Choices' : 'Same screen';
  const related = [...new Set([...(entry.screenTexts || []),
    ...(entry.windowTitle && entry.windowTitle !== entry.offset ? [entry.windowTitle] : []),
    ...(entry.windowBodies || [])])];
  const partners = related.filter(offset => state.byOffset.has(offset))
    .map(offset => [entry.windowBodies?.includes(offset) && !entry.screenTexts?.includes(offset)
      ? 'Window text' : role(state.byOffset.get(offset)), offset]);
  for (const [name, offset] of partners.slice(0, 6)) {
    const peer = state.byOffset.get(offset);
    if (!peer) continue;
    const link = document.createElement('button');
    link.type = 'button';
    link.className = 'partner-link';
    link.textContent = `${t(`role.${name}`)} ${offset}`;
    link.title = label(peer);
    link.addEventListener('click', () => select(peer));
    $('#context').append(' · ', link);
  }
  if (partners.length > 6) $('#context').append(` · ${t('partners.more', {count: partners.length - 6})}`);
  $('#size').textContent = t('size', {count: entry.originalBytes});
  $('#original').textContent = entry.original;
  $('#reference-panel').hidden = state.lang === 'en';
  $('#reference').textContent = entry.reference ?? t('source.noReference');
  $('#clipped-note').hidden = !entry.clipped;
  if (entry.clipped)
    $('#clipped-note').textContent = t('clipped.note', {needed: entry.clipped.needed,
      available: entry.clipped.available, site: entry.clipped.example}) +
      (entry.clipped.screens > 1 ? t('clipped.more', {count: entry.clipped.screens - 1}) : '') +
      (entry.clipped.exact ? '.' : t('clipped.inferred')) + t('clipped.render');
  state.previewPage = 0;
  $('#draft').value = entry.text;
  state.currentContext = null;
  const template = entry.kind === 'menu' || entry.templateFormat;
  $('#control-type option[value="02"]').disabled = template;
  if (template && $('#control-type').value === '02') $('#control-type').value = '07';
  updateControlFields();
  $('#rule').textContent = t(template ? 'rule.template' : entry.kind === 'event' ? 'rule.event'
    : entry.kind === 'string' ? 'rule.string' : 'rule.scene');
  $('#preview-result').hidden = true;
  $('#script-context').textContent = t('script.loading');
  stopCredits();
  creditsPreview = null;
  $('#credits-controls').hidden = true;
  setPreviewTab(entry.category === 'ending credits' ? 'render' : 'script');
  $('#save-status').textContent = '';
  updateSave();
  renderList();
  loadScriptContext(entry);
  schedulePreview(0);
}

function setPreviewTab(tab) {
  if (tab === 'script') stopCredits();
  const panel = $('#preview-result');
  panel.classList.toggle('show-script', tab === 'script');
  panel.classList.toggle('show-render', tab === 'render');
  $('#show-script').setAttribute('aria-pressed', String(tab === 'script'));
  $('#show-render').setAttribute('aria-pressed', String(tab === 'render'));
}

async function loadScriptContext(entry) {
  const key = `${entry.offset}:${entry.eventId ?? ''}`;
  let pending = state.contexts.get(key);
  if (!pending) {
    const query = entry.eventId == null ? '' : `?eventId=${entry.eventId}`;
    pending = request(`/api/context/${entry.offset}${query}`);
    state.contexts.set(key, pending);
  }
  try {
    const data = await pending;
    if (state.selected === entry) {
      state.currentContext = data;
      renderScriptContext(data);
    }
  } catch (error) {
    state.contexts.delete(key);
    if (state.selected === entry) $('#script-context').textContent = error.message;
  }
}

async function openScriptBlock(key) {
  const entry = state.selected;
  try {
    const block = await request(`/api/script?key=${encodeURIComponent(key)}`);
    if (state.selected === entry)
      renderScriptContext({location: {commandIndex: -1}, block}, true);
  } catch (error) {
    if (state.selected === entry) $('#script-context').textContent = error.message;
  }
}

async function chooseScriptLocation(index) {
  const entry = state.selected;
  const current = state.currentContext;
  const location = current.locations[index];
  try {
    const block = location.block === current.location.block ? current.block :
      await request(`/api/script?key=${encodeURIComponent(location.block)}`);
    if (state.selected !== entry || state.currentContext !== current) return;
    state.currentContext = {...current, location, block, selectedLocationIndex: index};
    renderScriptContext(state.currentContext);
  } catch (error) {
    if (state.selected === entry) $('#script-context').textContent = error.message;
  }
}

function renderScriptContext({location, block, locations, selectedLocationIndex, codeSites}, exploring = false) {
  const panel = $('#script-context');
  panel.replaceChildren();
  if (!location) {
    const note = document.createElement('p');
    note.className = 'script-note';
    note.textContent = codeSites?.length ? t('script.codeDrawn', {sites: codeSites.slice(0, 8).join(', ')}) +
      (codeSites.length > 8 ? ` ${t('partners.more', {count: codeSites.length - 8})}` : '') : t('script.none');
    panel.append(note);
    return;
  }
  const overview = document.createElement('div');
  overview.className = 'script-overview';
  const title = document.createElement('h3');
  title.className = 'script-title';
  const commandPart = exploring ? '' : t('script.command', {index: location.commandIndex});
  title.textContent = (block.kind === 'menu' ? t('script.menu', {root: block.root})
    : exploring ? t('script.event', {root: block.root}) : t('script.eventNumber', {event: location.event, root: block.root})) + commandPart;
  overview.append(title);
  if (!exploring && locations?.length > 1) {
    const picker = document.createElement('select');
    picker.className = 'script-owner-select';
    picker.setAttribute('aria-label', t('script.pathAria'));
    for (const [index, item] of locations.entries()) {
      const option = document.createElement('option');
      option.value = index;
      const branch = item.path?.length ? t('script.children', {path: item.path.map(step => step.child).join('→')}) : '';
      option.textContent = `${index + 1}/${locations.length}: ` +
        (item.event == null ? t('script.optionMenu') : t('script.optionEvent', {event: item.event})) +
        ` · ${item.block}${t('script.command', {index: item.commandIndex})}${branch}`;
      picker.append(option);
    }
    picker.value = String(selectedLocationIndex);
    picker.addEventListener('change', () => chooseScriptLocation(Number(picker.value)));
    overview.append(picker);
  }
  if (exploring) {
    const back = document.createElement('button');
    back.type = 'button';
    back.className = 'script-open';
    back.textContent = t('script.back');
    back.addEventListener('click', () => renderScriptContext(state.currentContext));
    overview.append(back);
  }
  const note = value => {
    const item = document.createElement('p');
    item.className = 'script-note';
    item.textContent = value;
    overview.append(item);
  };
  if (block.kind === 'menu') {
    if (block.callSites?.length) note(t('script.calledFrom', {sites: block.callSites.join(', ')}));
    if (!exploring && location.window && location.windowSource !== 'script') {
      const setup = document.createElement('button');
      setup.type = 'button';
      setup.className = 'script-open';
      setup.textContent = t('script.openSetup', {root: location.window.sourceRoot});
      setup.addEventListener('click', () => openScriptBlock(`menu:${location.window.sourceRoot}`));
      overview.append(setup);
    }
    if (exploring) {
      note(t('script.declarations'));
      const windows = document.createElement('div');
      windows.className = 'script-windows';
      for (const item of block.windowDefinitions) {
        const badge = document.createElement('span');
        badge.className = 'script-window';
        badge.textContent = `#${item.id} (${item.x}, ${item.y}) ${item.width}×${item.height}`;
        windows.append(badge);
      }
      overview.append(windows);
    } else if (location.window) {
      const window = location.window;
      const source = location.windowSource === 'script' ? t('script.declared') : t('script.earlier', {root: window.sourceRoot});
      note(t('script.window', {id: window.id, x: window.x, y: window.y, width: window.width, height: window.height, source}));
      note(t('script.origin', {x: window.x + 8, y: window.y + 4}));
      const windows = document.createElement('div');
      windows.className = 'script-windows';
      for (const item of location.windows) {
        const badge = document.createElement('span');
        badge.className = `script-window ${item.id === location.windowId ? 'target' : ''}`;
        badge.textContent = `#${item.id} (${item.x}, ${item.y}) ${item.width}×${item.height}`;
        windows.append(badge);
      }
      overview.append(windows);
    } else note(t('script.noWindow', {id: location.windowId}));
  } else if (!exploring) {
    const branch = location.path.map(step => t('script.branch', {child: step.child, at: step.at, to: step.to}));
    note(t('script.root', {root: location.eventRoot}) + (branch.length ? ' · ' + branch.join(' · ') : ''));
  }
  panel.append(overview);
  const commands = document.createElement('div');
  commands.className = 'script-commands';
  let active;
  for (const [index, step] of block.commands.entries()) {
    const peer = state.byOffset.get(step.textOffset);
    const row = document.createElement('button');
    row.type = 'button';
    row.className = `script-command ${index === location.commandIndex ? 'active' : ''}`;
    row.disabled = !peer || peer === state.selected;
    const header = document.createElement('span');
    header.textContent = `${step.at} · ${command(step.name)}`;
    const raw = document.createElement('code');
    raw.textContent = `  [${step.raw}]`;
    header.append(raw);
    row.append(header);
    if (step.textOffset) {
      const text = document.createElement('span');
      text.className = 'script-text';
      text.textContent = `${step.textOffset} · ${peer ? label(peer) : t('script.gameText')}`;
      row.append(text);
    }
    if (step.children?.length) {
      const children = document.createElement('span');
      children.className = 'script-text';
      children.textContent = t('script.childList', {children: step.children.join(', ')});
      row.append(children);
    }
    if (peer && peer !== state.selected) row.addEventListener('click', () => select(peer));
    if (index === location.commandIndex) active = row;
    commands.append(row);
    if (step.children?.length) {
      const links = document.createElement('div');
      links.className = 'script-children';
      for (const [number, child] of step.children.entries()) {
        const link = document.createElement('button');
        link.type = 'button';
        link.textContent = t('script.child', {number, target: child});
        link.addEventListener('click', () => openScriptBlock(`event:${child}`));
        links.append(link);
      }
      commands.append(links);
    }
  }
  panel.append(commands);
  if (active) {
    const top = active.getBoundingClientRect().top - commands.getBoundingClientRect().top;
    commands.scrollTop += top - Math.max(0, (commands.clientHeight - active.offsetHeight) / 2);
  }
}
function updateSave() {
  $('#save').disabled = !state.selected || $('#draft').value === state.savedText;
}
async function request(url, options) {
  url += `${url.includes('?') ? '&' : '?'}lang=${state.lang}`;
  const response = await fetch(url, options);
  const body = await response.json();
  if (!response.ok) throw Error(body.error || `HTTP ${response.status}`);
  return body;
}
async function save() {
  const entry = state.selected;
  if (!entry) return;
  const text = $('#draft').value;
  $('#save').disabled = true;
  $('#save-status').textContent = t('save.checking');
  try {
    await request(`/api/entry/${entry.offset}`, {
      method: 'PUT', headers: {'Content-Type': 'application/json'},
      body: JSON.stringify({text, expected: state.savedText})
    });
    entry.text = text;
    state.savedText = text;
    $('#save-status').textContent = t('save.done');
    renderList();
  } catch (error) {
    $('#save-status').textContent = error.message;
  } finally { updateSave(); }
}
function schedulePreview(delay = 300) {
  stopCredits();
  clearTimeout(previewTimer);
  const revision = ++previewRevision;
  previewTimer = setTimeout(() => preview(revision), delay);
}

function stopCredits() {
  cancelAnimationFrame(creditsAnimation);
  creditsAnimation = null;
  $('#credits-play').textContent = t('credits.play');
}

function drawCredits(position) {
  if (!creditsPreview) return;
  const context = $('#canvas').getContext('2d');
  context.fillStyle = creditsPreview.result.background;
  context.fillRect(0, 0, 240, 160);
  context.drawImage(creditsPreview.surface, 0, -position);
  $('#credits-position').value = position;
  $('#credits-line').textContent = t('credits.line', {line: Math.min(creditsPreview.result.lineCount,
    Math.floor(position / 16) + 1), total: creditsPreview.result.lineCount});
}

function playCredits() {
  if (creditsAnimation !== null) {
    stopCredits();
    return;
  }
  if (!creditsPreview) return;
  const maximum = Number($('#credits-position').max);
  let position = Number($('#credits-position').value);
  if (position >= maximum) position = 0;
  let started;
  const frame = time => {
    started ??= time;
    const scroll = Math.min(maximum, position + (time - started) * 0.03);
    drawCredits(Math.floor(scroll));
    if (scroll >= maximum) stopCredits();
    else creditsAnimation = requestAnimationFrame(frame);
  };
  $('#credits-play').textContent = t('credits.pause');
  creditsAnimation = requestAnimationFrame(frame);
}

function creditsScrollPosition(previous, next, position) {
  const before = previous.lineKeys;
  const after = next.lineKeys;
  const row = Math.floor(position / 16);
  const lengths = Array.from({length: before.length + 1},
    () => new Uint32Array(after.length + 1));
  for (let old = before.length - 1; old >= 0; old--)
    for (let current = after.length - 1; current >= 0; current--)
      lengths[old][current] = before[old] === after[current]
        ? lengths[old + 1][current + 1] + 1
        : Math.max(lengths[old + 1][current], lengths[old][current + 1]);
  let old = 0;
  let current = 0;
  let shift = 0;
  while (old <= row && old < before.length && current < after.length) {
    if (before[old] === after[current]) {
      shift = current - old;
      old++;
      current++;
    } else if (lengths[old + 1][current] >= lengths[old][current + 1]) old++;
    else current++;
  }
  return Math.max(0, Math.min(next.height, position + shift * 16));
}

function renderPreview(result) {
  const canvas = $('#canvas');
  canvas.width = 240;
  canvas.height = 160;
  const credits = result.profile === 'credits';
  $('#preview-result').classList.toggle('credits-preview', credits);
  const position = credits && creditsPreview
    ? creditsScrollPosition(creditsPreview.result, result, Number($('#credits-position').value)) : 0;
  const surface = document.createElement('canvas');
  surface.width = 240;
  surface.height = credits ? result.height : 160;
  const context = surface.getContext('2d');
  const colors = result.palette || palette;
  context.fillStyle = result.background || '#26343a';
  context.fillRect(0, 0, surface.width, surface.height);
  for (const window of result.windows) {
    context.fillStyle = '#424242';
    context.fillRect(window.x, window.y, window.width, window.height);
    context.fillStyle = '#8c8c84';
    context.fillRect(window.x + 1, window.y + 1, window.width - 2, window.height - 2);
    context.fillStyle = colors[0];
    context.fillRect(window.x + 2, window.y + 2, window.width - 4, window.height - 4);
  }
  const target = result.windows.find(window => window.id === result.windowId) || result.windows[0];
  context.save();
  if (target) {
    context.beginPath();
    context.rect(target.x + 2, target.y + 2, target.width - 4, target.height - 4);
    context.clip();
  }
  const pages = result.pages?.length ? result.pages : [result.spans];
  state.previewPage = Math.min(state.previewPage, pages.length - 1);
  if (result.layers) {
    for (const layer of result.layers) {
      // Titles sit on the window's top border row, outside the text area clip.
      if (layer.title) {
        context.restore();
        context.save();
        context.fillStyle = colors[0];
        context.fillRect(layer.x - 7, layer.y, layer.spans.reduce((right, [x, , width]) => Math.max(right, x + width), 0) + 9, 8);
        context.fillStyle = colors[7];
        context.fillRect(layer.x - 6, layer.y + 2, 4, 4);
      }
      for (const [x, y, width, color] of layer.spans) {
        context.fillStyle = colors[color] || colors[7];
        context.fillRect(layer.x + x, layer.y + y, width, 1);
      }
    }
  } else {
    for (const [x, y, width, color] of credits ? result.spans : pages[state.previewPage]) {
      context.fillStyle = colors[color] || colors[7];
      context.fillRect(result.textX + x, result.textY + y, width, 1);
    }
  }
  context.restore();
  const lastStop = state.previewPage + 1 >= pages.length;
  const drawFrame = window => {
    context.fillStyle = '#424242';
    context.fillRect(window.x, window.y, window.width, window.height);
    context.fillStyle = '#8c8c84';
    context.fillRect(window.x + 1, window.y + 1, window.width - 2, window.height - 2);
    context.fillStyle = colors[0];
    context.fillRect(window.x + 2, window.y + 2, window.width - 4, window.height - 4);
  };
  const drawCursor = ({x, y}) => {
    context.fillStyle = colors[7];
    context.beginPath();
    context.moveTo(x, y - 3);
    context.lineTo(x + 5, y);
    context.lineTo(x, y + 3);
    context.closePath();
    context.fill();
  };
  if (result.choice && lastStop) {
    drawFrame(result.choice.window);
    for (const layer of result.choice.layers)
      for (const [x, y, width, color] of layer.spans) {
        context.fillStyle = colors[color] || colors[7];
        context.fillRect(layer.x + x, layer.y + y, width, 1);
      }
    for (const prompt of result.choice.prompts) drawCursor(prompt);
  }
  const dialogueBox = !credits && result.profile.endsWith('_dialogue');
  if (dialogueBox && target) {
    const x = target.x + target.width - 16;
    const y = target.y + target.height - 12;
    context.fillStyle = colors[7];
    context.beginPath();
    context.moveTo(x, y);
    context.lineTo(x + 7, y);
    context.lineTo(x + 3.5, y + 5);
    context.closePath();
    context.fill();
  }
  $('#page-controls').hidden = !dialogueBox;
  $('#page-label').textContent = t('page.label', {current: state.previewPage + 1, total: pages.length}) +
    ' · ' + t(state.previewPage + 1 < pages.length ? 'page.more' : 'page.end');
  $('#page-previous').disabled = state.previewPage === 0;
  $('#page-next').disabled = state.previewPage + 1 >= pages.length;
  canvas.getContext('2d').drawImage(surface, 0, 0);
  $('#credits-controls').hidden = !credits;
  creditsPreview = credits ? {surface, result} : null;
  if (credits) {
    $('#credits-position').max = result.height;
    drawCredits(position);
  }
}

async function preview(revision) {
  const entry = state.selected;
  if (!entry) return;
  const value = $('#draft').value;
  const playerName = $('#player-name').value;
  $('#preview-meta').textContent = t('preview.rendering');
  $('#preview-result').hidden = false;
  try {
    const result = await request(`/api/preview/${entry.offset}`, {
      method: 'POST', headers: {'Content-Type': 'application/json'},
      body: JSON.stringify({text: value, expected: state.savedText, playerName})
    });
    if (revision !== previewRevision || state.selected !== entry ||
        $('#draft').value !== value || $('#player-name').value !== playerName) return;
    state.previewResult = result;
    renderPreview(result);
    state.previewPlayer = playerName;
    renderPreviewDetails(result, playerName);
  } catch (error) {
    if (revision === previewRevision) {
      $('#preview-meta').textContent = error.message;
      $('#encoded-units').replaceChildren();
    }
  }
}
function renderPreviewDetails(result, playerName) {
  const auto = result.breaks.filter(item => !item.explicit).length;
  const parts = [t(`profile.${result.profile}`), t('meta.breaks', {count: auto}),
    t('meta.colors', {colors: result.colors.join(', ')}), t('meta.bounds', {bounds: result.bounds.join(', ')})];
  if (result.profile === 'menu') parts.push(t('meta.window', {id: result.windowId, source: result.windowSource}) +
    (result.windowSetup ? ` ${result.windowSetup}` : ''));
  if (result.missing?.length) parts.push(t('meta.missing', {count: result.missing.length}));
  if (result.pages?.length > 1) parts.push(t('meta.stops', {count: result.pages.length}));
  if (result.screen) parts.push(t('meta.screen', {count: result.screen.texts.length}) + (result.screen.prompts.length
    ? t('meta.prompt', {kinds: result.screen.prompts.map(kind => t(`prompt.${kind}`)).join(t('meta.and'))}) : ''));
  if (result.choice) parts.push(t('meta.choice'));
  if (result.windowGroup) parts.push(t('meta.group', {title: result.windowGroup.title, body: result.windowGroup.body}) +
    (result.windowGroup.bodies > 1 ? t('meta.groupCount', {count: result.windowGroup.bodies}) : ''));
  if (result.overflowed && !result.profile.endsWith('_dialogue') && !result.choice) parts.push(t('meta.clipped'));
  $('#preview-meta').textContent = parts.join(' · ');
  const units = $('#encoded-units');
  units.replaceChildren();
  const size = document.createElement('span');
  size.textContent = t('units.bytes', {count: result.encodedBytes});
  units.append(size);
  for (const unit of result.encodedUnits) {
    const chip = document.createElement('span');
    chip.className = `encoded-unit ${unit.kind === 'control' ? 'control' : ''}`;
    if (unit.kind === 'control') {
      chip.textContent = controlPreviewLabel(unit.bytes, playerName, result);
      const raw = document.createElement('code');
      raw.textContent = `{${unit.bytes}}`;
      chip.append(raw);
      const code = unit.bytes.slice(0, 2);
      chip.title = controlInfo[code] ? controlHelp(code) : t('units.end');
    } else {
      chip.textContent = `${t(`unit.${unit.kind}`)}: ${unit.text.replaceAll('\n', '↵')}`;
      chip.title = unit.bytes;
    }
    units.append(chip);
  }
}

async function build() {
  $('#build').disabled = true;
  $('#global-status').textContent = t('build.running');
  try {
    const result = await request('/api/build', {method: 'POST'});
    $('#global-status').textContent = t('build.done', {path: result.path});
  } catch (error) { $('#global-status').textContent = error.message; }
  finally { $('#build').disabled = false; }
}
$('#search').addEventListener('input', () => {state.page = 0; renderList();});
$('#kind').addEventListener('change', () => {state.page = 0; renderList();});
$('#category').addEventListener('change', () => {state.page = 0; renderList();});
$('#changed').addEventListener('change', () => {state.page = 0; renderList();});
$('#list').addEventListener('scroll', () => {
  const list = $('#list');
  if (list.scrollTop + list.clientHeight >= list.scrollHeight - 200 &&
      (state.page + 1) * pageSize < filtered().length) {
    state.page++;
    renderList();
  }
});
$('#draft').addEventListener('input', () => { updateSave(); schedulePreview(); });
$('#draft').addEventListener('click', readControlAtCaret);
$('#draft').addEventListener('keyup', readControlAtCaret);
$('#control-type').addEventListener('change', updateControlFields);
$('#insert-control').addEventListener('click', () => {
  try { insertControl(); }
  catch (error) { $('#save-status').textContent = error.message; }
});
$('#open-control-guide').addEventListener('click', () => $('#control-guide').showModal());
$('#close-control-guide').addEventListener('click', () => $('#control-guide').close());
$('#player-name').addEventListener('input', () => {
  localStorage.setItem('zoidsPreviewPlayerName', $('#player-name').value);
  schedulePreview();
});
$('#save').addEventListener('click', save);
$('#preview').addEventListener('click', () => schedulePreview(0));
$('#show-script').addEventListener('click', () => setPreviewTab('script'));
$('#show-render').addEventListener('click', () => setPreviewTab('render'));
$('#credits-play').addEventListener('click', playCredits);
$('#credits-position').addEventListener('input', () => {
  stopCredits();
  drawCredits(Number($('#credits-position').value));
});
$('#build').addEventListener('click', build);
applyStaticText();
renderControlGuide();
function changePage(step) {
  if (!state.previewResult) return;
  const pages = state.previewResult.pages?.length || 1;
  const next = Math.max(0, Math.min(pages - 1, state.previewPage + step));
  if (next === state.previewPage) return;
  state.previewPage = next;
  renderPreview(state.previewResult);
}
$('#page-previous').addEventListener('click', () => changePage(-1));
$('#page-next').addEventListener('click', () => changePage(1));
$('#canvas').addEventListener('keydown', event => {
  if (event.key === 'a' || event.key === 'A' || event.key === 'ArrowRight' || event.key === 'Enter') changePage(1);
  else if (event.key === 'b' || event.key === 'B' || event.key === 'ArrowLeft') changePage(-1);
  else return;
  event.preventDefault();
});

function setLanguage(lang) {
  state.lang = lang;
  localStorage.setItem('zoidsEditorLanguage', lang);
  for (const button of document.querySelectorAll('.language-switch button'))
    button.setAttribute('aria-pressed', String(button.dataset.lang === lang));
  applyStaticText();
  const url = new URL(location);
  url.searchParams.set('lang', lang);
  history.replaceState(null, '', url);
}

async function loadCatalog(lang, offset) {
  setLanguage(lang);
  $('#global-status').textContent = t('status.loading');
  $('#build').disabled = true;
  try {
    const data = await request('/api/catalog');
    state.entries = data.entries;
    state.byOffset = new Map(data.entries.map(entry => [entry.offset, entry]));
    state.contexts.clear();
    const categorySelect = $('#category');
    const chosen = categorySelect.value;
    categorySelect.replaceChildren(categorySelect.options[0]);
    for (const name of [...new Set(data.entries.map(entry => entry.category).filter(Boolean))].sort()) {
      const option = document.createElement('option');
      option.value = name;
      option.textContent = category(name);
      categorySelect.append(option);
    }
    categorySelect.value = chosen;
    const clipped = data.entries.filter(entry => entry.clipped).length;
    state.catalogSummary = {language: data.languages[lang], count: data.count, clipped};
    renderCatalogSummary();
    $('#build').disabled = false;
    state.page = 0;
    renderList();
    const requested = offset?.toLowerCase();
    const selected = state.entries.find(entry => entry.offset.toLowerCase() === requested);
    if (state.entries.length) select(selected || state.entries[0]);
  } catch (error) { $('#global-status').textContent = error.message; }
}

function renderCatalogSummary() {
  const summary = state.catalogSummary;
  if (!summary) return;
  $('#search').placeholder = t('search.count', {count: summary.count.toLocaleString(uiLanguage())});
  $('#global-status').textContent = t('status.loaded', {language: summary.language,
    count: summary.count.toLocaleString(uiLanguage())}) +
    (summary.clipped ? t('status.clippedCount', {count: summary.clipped}) : '.');
}

function refreshInterface() {
  applyStaticText();
  renderControlGuide();
  updateControlFields();
  renderCatalogSummary();
  renderList();
  const entry = state.selected;
  if (entry) {
    const draft = $('#draft').value;
    select(entry);
    $('#draft').value = draft;
    updateSave();
    schedulePreview(0);
  }
}

$('#translate-ui').addEventListener('change', () => {
  state.translateUi = $('#translate-ui').checked;
  localStorage.setItem('zoidsEditorTranslateUi', String(state.translateUi));
  refreshInterface();
});

for (const button of document.querySelectorAll('.language-switch button'))
  button.addEventListener('click', () => {
    if (button.dataset.lang !== state.lang) loadCatalog(button.dataset.lang, state.selected?.offset);
  });
const params = new URLSearchParams(location.search);
$('#changed').value = params.get('status') || '';
loadCatalog(state.lang, params.get('offset'));
