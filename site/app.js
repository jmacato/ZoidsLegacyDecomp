import { localizePage, text } from './i18n.js';

let effects;
let language = 'en';
try { if (localStorage.getItem('zoids-language') === 'es') language = 'es'; } catch {}

const themeButton = document.querySelector('#theme-toggle');
function updateThemeButton() {
  const dark = document.documentElement.dataset.theme === 'dark';
  const background = getComputedStyle(document.documentElement).getPropertyValue('--background').trim();
  document.documentElement.style.backgroundColor = background;
  document.body.style.backgroundColor = background;
  themeButton.setAttribute('aria-label', text(dark ? 'theme.lightAria' : 'theme.darkAria', language));
  document.querySelector('#theme-label').textContent = text(dark ? 'theme.lightLabel' : 'theme.darkLabel', language);
  document.querySelector('meta[name="theme-color"]').content = background;
}
updateThemeButton();
themeButton.addEventListener('click', () => {
  const next = document.documentElement.dataset.theme === 'dark' ? 'light' : 'dark';
  document.documentElement.dataset.theme = next;
  try { localStorage.setItem('zoids-theme', next); } catch {}
  updateThemeButton();
});

for (const tabList of document.querySelectorAll('.edition-tabs')) {
  const tabs = [...tabList.querySelectorAll('[role="tab"]')];
  const screen = tabList.closest('.feature').querySelector('.game-shot');
  let transition = 0;
  async function selectTab(selected) {
    const request = ++transition;
    const previous = screen.querySelector('.game-panel:not([hidden])');
    const next = document.getElementById(selected.getAttribute('aria-controls'));
    if (previous !== next) {
      const closing = effects?.powerCrt(previous, false);
      if (closing) await closing.finished.catch(() => {});
      if (request !== transition) return;
    } else {
      if (previous.querySelector('.crt-beam')) effects?.powerCrt(previous, true);
      return;
    }
    for (const tab of tabs) {
      const active = tab === selected;
      tab.setAttribute('aria-selected', String(active));
      tab.tabIndex = active ? 0 : -1;
      document.getElementById(tab.getAttribute('aria-controls')).hidden = !active;
    }
    effects?.powerCrt(next, true);
  }
  for (const tab of tabs) {
    tab.addEventListener('click', () => selectTab(tab));
    tab.addEventListener('keydown', event => {
      let next;
      const index = tabs.indexOf(tab);
      if (event.key === 'ArrowRight') next = (index + 1) % tabs.length;
      else if (event.key === 'ArrowLeft') next = (index + tabs.length - 1) % tabs.length;
      else if (event.key === 'Home') next = 0;
      else if (event.key === 'End') next = tabs.length - 1;
      else return;
      event.preventDefault();
      selectTab(tabs[next]);
      tabs[next].focus();
    });
  }
}

const input = document.querySelector('#rom-input');
const languageButtons = document.querySelectorAll('.language-option');
const zone = document.querySelector('#drop-zone');
const status = document.querySelector('#status');
const statusDots = document.querySelectorAll('.status-dot');
const patchButton = document.querySelector('#patch-button');
const buttonLabel = document.querySelector('#button-label');
const WORKER_TIMEOUT_MS = 30_000;
let rom = null;
let worker = null;
let workerTimer;
let busy = false;
let buttonMessage = 'patch.button';
let statusMessage = 'patch.start';
let statusState = 'muted';
const supported = Boolean(window.Worker && window.crypto?.subtle);

function setStatus(message, state = 'muted') {
  statusMessage = message;
  statusState = state;
  status.textContent = `${text('patch.version', language)} · ${text(message, language)}`;
  status.dataset.error = String(state === 'error');
  for (const dot of statusDots) dot.className = `status-dot ${state}`;
}
function setButton(message) {
  buttonMessage = message;
  buttonLabel.textContent = text(message, language);
}
function selectLanguage(selected) {
  if (selected !== language && rom) {
    buttonMessage = 'patch.button';
    statusMessage = 'patch.verified';
    statusState = 'ready';
  }
  language = selected;
  try { localStorage.setItem('zoids-language', language); } catch {}
  for (const button of languageButtons) button.setAttribute('aria-pressed', String(button.dataset.language === language));
  localizePage(language);
  updateThemeButton();
  setButton(buttonMessage);
  setStatus(statusMessage, statusState);
}
function setBusy(value) {
  busy = value;
  input.disabled = value || !supported;
  for (const button of languageButtons) button.disabled = value;
  zone.classList.toggle('busy', value);
  for (const dot of statusDots) dot.dataset.busy = String(value);
  patchButton.disabled = value || !rom || !supported;
  patchButton.setAttribute('aria-busy', String(value && Boolean(rom)));
}
function stopWorker() {
  clearTimeout(workerTimer);
  worker?.terminate();
  worker = null;
}
function failWorker(message) {
  stopWorker();
  setBusy(false);
  setButton('patch.button');
  setStatus(message, 'error');
}
function startWorker(action, file) {
  stopWorker();
  const selectedLanguage = language;
  const task = new Worker(new URL('./worker.js', import.meta.url), { type: 'module' });
  worker = task;
  workerTimer = setTimeout(() => {
    failWorker('error.timeout');
  }, WORKER_TIMEOUT_MS);
  task.onerror = () => {
    if (worker !== task) return;
    failWorker('error.worker');
  };
  task.onmessage = ({ data }) => {
    if (worker !== task) return;
    stopWorker();
    setButton('patch.button');
    if (data.error) {
      if (action === 'validate') {
        rom = null;
        zone.classList.remove('selected');
      }
      setBusy(false);
      setStatus(data.error, 'error');
      return;
    }
    if (data.validated) {
      rom = file;
      zone.classList.add('selected');
      setBusy(false);
      setStatus('patch.verified', 'ready');
    } else if (data.target) {
      const url = URL.createObjectURL(new Blob([data.target], { type: 'application/octet-stream' }));
      const link = document.createElement('a');
      link.href = url;
      link.download = text('download.filename', selectedLanguage);
      document.body.append(link);
      link.click();
      link.remove();
      setTimeout(() => URL.revokeObjectURL(url), 60000);
      setBusy(false);
      setStatus('patch.complete', 'ready');
      setButton('patch.downloadAgain');
    }
  };
  task.postMessage({ action, language: selectedLanguage, rom: file });
}
function selectRom(files) {
  if (busy || !supported || !files.length) return;
  rom = null;
  zone.classList.remove('selected');
  patchButton.disabled = true;
  setButton('patch.button');
  if (files.length !== 1) {
    setStatus('error.fileCount', 'error');
    return;
  }
  const file = files[0];
  if (!/\.gba$/i.test(file.name)) {
    setStatus('error.fileType', 'error');
    return;
  }
  if (file.size !== 8 * 1024 * 1024) {
    setStatus('error.romSize', 'error');
    return;
  }
  setBusy(true);
  setStatus('patch.checking');
  try { startWorker('validate', file); } catch {
    failWorker('error.worker');
  }
}
input.addEventListener('change', () => {
  selectRom(input.files);
  input.value = '';
});
for (const button of languageButtons) button.addEventListener('click', () => {
  if (!busy) selectLanguage(button.dataset.language);
});
for (const event of ['dragenter', 'dragover']) {
  zone.addEventListener(event, e => {
    e.preventDefault();
    if (!busy && supported) zone.classList.add('drag-over');
  });
}
zone.addEventListener('dragleave', e => {
  if (!zone.contains(e.relatedTarget)) zone.classList.remove('drag-over');
});
zone.addEventListener('drop', e => {
  e.preventDefault();
  zone.classList.remove('drag-over');
  selectRom(e.dataTransfer.files);
});
window.addEventListener('dragover', e => e.preventDefault());
window.addEventListener('drop', e => e.preventDefault());
patchButton.addEventListener('click', () => {
  if (!rom || busy) return;
  setBusy(true);
  setButton('patch.applyingButton');
  setStatus('patch.applyingStatus');
  try { startWorker('patch', rom); } catch {
    failWorker('error.worker');
  }
});
selectLanguage(language);
if (!supported) {
  input.disabled = true;
  setStatus('error.insecureContext', 'error');
}
import('./effects.js').then(({ createEffects }) => {
  effects = createEffects();
}).catch(() => {
  clearTimeout(window.introFallback);
  document.documentElement.classList.remove('intro-pending', 'intro-running');
});
