import { createAnalogPanels } from './crt.js';
import { createHudMotion } from './hud-motion.js';

const FRAME_MS = 40;
const motionAllowed = () => !document.hidden && !matchMedia('(prefers-reduced-motion: reduce)').matches &&
  !document.documentElement.matches('.intro-pending, .intro-running');

export function createEffects() {
  for (const feature of document.querySelectorAll('.feature')) {
    const template = document.querySelector(`#feature-frame-${feature.dataset.frame}`);
    const frame = template.content.firstElementChild.cloneNode(true);
    feature.prepend(frame);
  }
  for (const frame of document.querySelectorAll('.feature-frame, .section-frame')) {
    const { width: baseWidth, height: baseHeight } = frame.viewBox.baseVal;
    const split = Number(frame.dataset.stretchY);
    const paths = [...frame.querySelectorAll('path')].map(path => [path, path.getAttribute('d')]);
    const title = frame.classList.contains('patcher-frame') ? frame.parentElement.querySelector('.patcher-title') : null;
    const hatches = title ? [...frame.querySelectorAll('.feature-hatch')] : [];
    let resizeFrame;
    let ratchet;
    let size;
    let drawnWidth;
    let drawnRibbon = 230;
    const observer = new ResizeObserver(entries => {
      size = entries.find(entry => entry.target === frame)?.contentRect ?? size;
      cancelAnimationFrame(resizeFrame);
      if (!size?.width) return;
      const { width, height } = size;
      // Defer geometry writes so WebKit can finish delivering resize notifications.
      resizeFrame = requestAnimationFrame(() => {
        if (frame.classList.contains('section-frame')) {
          frame.parentElement.style.minHeight = `${width * baseHeight / baseWidth}px`;
        }
        const frameHeight = Math.round(baseWidth * height / width);
        frame.setAttribute('viewBox', `0 0 ${baseWidth} ${frameHeight}`);
        const scale = width / baseWidth;
        const draw = ribbon => {
          drawnRibbon = ribbon;
          if (title) drawPatcherTitle(title, ribbon, scale);
          // Grow the title ribbon to its text and slide the notch over; the hatch row narrows to fit.
          const shift = ribbon - 230;
          const hatchScale = (155 - shift) / 155;
          for (const [path, original] of paths) {
            const hatch = hatches.indexOf(path);
            const source = hatch < 0 ? original : hatchPath(Math.round(335 + shift + hatch * 42 * hatchScale), Math.round(29 * hatchScale));
            path.setAttribute('d', source.replace(/([ML])([\d.]+) ([\d.]+)/g, (_, command, x, y) => {
              const notch = hatch < 0 && shift && Number(y) <= 61 && Number(x) >= 246 && Number(x) <= 372;
              return `${command}${Number(x) + (notch ? shift : 0)} ${Number(y) + (Number(y) > split ? frameHeight - baseHeight : 0)}`;
            }));
          }
        };
        const target = title ? fitPatcherTitle(title, scale) : 230;
        const from = drawnRibbon;
        // Text changes ratchet the ribbon over in HUD frames; window resizes snap.
        const steps = width === drawnWidth && target !== from && motionAllowed() ? [.35, .7, 1] : [1];
        drawnWidth = width;
        clearTimeout(ratchet);
        const step = index => {
          draw(Math.round(from + (target - from) * steps[index]));
          if (index + 1 < steps.length) ratchet = setTimeout(() => step(index + 1), FRAME_MS);
        };
        step(0);
      });
    });
    observer.observe(frame);
    if (title) observer.observe(title.querySelector('span'));
  }

  for (const picker of document.querySelectorAll('.language-picker')) {
    markWrappedRows(picker);
    animateLanguageChanges(picker);
  }
  for (const tablist of document.querySelectorAll('.edition-tabs')) animateTabChanges(tablist);
  ghostOnInteraction();

  const reducedMotion = matchMedia('(prefers-reduced-motion: reduce)');
  const analogPanels = createAnalogPanels(document.querySelectorAll('.actions, .project-overview, .feature'), reducedMotion);
  const hudMotion = createHudMotion(document.querySelectorAll('.page-header, .actions, .project-overview, .feature'));
  let introAnimations = [];
  const introActive = () => document.documentElement.matches('.intro-pending, .intro-running');

  function wakeScreen(screen) {
    if (introActive() || document.hidden || screen.dataset.crtStarted) return;
    screen.dataset.crtStarted = 'true';
    const panel = screen.querySelector('.game-panel:not([hidden])');
    panel.querySelector('img').decode().then(() => {
      if (!panel.hidden && screen.classList.contains('crt-active')) powerCrt(panel, true);
    }).catch(() => {});
  }

  const crtObserver = new IntersectionObserver(entries => {
    for (const { target, isIntersecting } of entries) {
      target.classList.toggle('crt-active', isIntersecting);
      if (isIntersecting) wakeScreen(target);
    }
  });
  document.querySelectorAll('.game-shot').forEach(screen => {
    crtObserver.observe(screen);
  });

  function updateMotion() {
    analogPanels.refresh();
    hudMotion.refresh(!document.hidden && !reducedMotion.matches && !introActive());
    document.documentElement.classList.toggle('motion-paused', document.hidden);
    if (document.hidden || reducedMotion.matches) {
      finishIntro();
      for (const animation of document.getAnimations()) {
        if (animation.id === 'crt-power') animation.finish();
      }
    }
    if (!document.hidden && !introActive()) {
      document.querySelectorAll('.game-shot.crt-active').forEach(wakeScreen);
    }
  }
  document.addEventListener('visibilitychange', updateMotion);
  reducedMotion.addEventListener('change', updateMotion);
  updateMotion();

  function finishIntro() {
    clearTimeout(window.introFallback);
    document.documentElement.classList.remove('intro-pending', 'intro-running');
    introAnimations.forEach(animation => animation.cancel());
    introAnimations = [];
  }

  function startIntro() {
    if (!introActive()) return;
    const remaining = 3600 - (performance.now() - window.introStartedAt);
    if (remaining <= 0 || reducedMotion.matches || document.hidden) {
      finishIntro();
      updateMotion();
      return;
    }
    // Staged geometry, short signal breaks, then populated panels: https://dlew.me/oblivion
    const rate = remaining / 3600;
    const reveal = (selector, delay, duration, horizontal = false) => {
      const slit = horizontal ? 'inset(0 48% 0 48%)' : 'inset(48% 0 48% 0)';
      for (const element of typeof selector === 'string' ? document.querySelectorAll(selector) : [selector]) {
        const timing = { id: 'page-intro', delay: delay * rate, duration: duration * rate, fill: 'both' };
        introAnimations.push(element.animate([
          { visibility: 'hidden', clipPath: slit, offset: 0, easing: 'steps(1, end)' },
          { visibility: 'visible', clipPath: slit, offset: .12 },
          { clipPath: slit, offset: .3, easing: 'cubic-bezier(.16, 1, .3, 1)' },
          { visibility: 'visible', clipPath: 'inset(0)', offset: 1 },
        ], timing));
        // Keep opacity pulses separate so the frame keeps opening during each signal break.
        const flicker = [
          { opacity: 0, offset: 0 },
          { opacity: .7, offset: .12 },
          { opacity: .25, offset: .22 },
          { opacity: 1, offset: .3 },
        ];
        const burst = .42 + Math.random() * .08;
        const pulses = duration >= 430 ? 3 : 2;
        for (let pulse = 0; pulse < pulses; pulse++) {
          flicker.push({ opacity: .25, offset: burst + pulse * 60 / duration });
          flicker.push({ opacity: 1, offset: burst + (pulse * 60 + 30) / duration });
        }
        flicker.push({ opacity: 1, offset: 1 });
        introAnimations.push(element.animate(flicker.map(frame => ({ ...frame, easing: 'steps(1, end)' })), timing));
      }
    };
    reveal('.wordmark', 260, 420, true);
    reveal('.edition-label', 570, 460, true);
    reveal('.page-header nav', 960, 360, true);
    reveal('.actions .frame-body, .actions .crt-texture', 650, 850);
    reveal('.actions .frame-indicators', 920, 480, true);
    reveal('.actions .frame-bottom', 1120, 480, true);
    reveal('#patcher-title', 1170, 400, true);
    const languages = document.querySelectorAll('.language-option');
    languages.forEach((option, index) => reveal(option, 1330 + index * 90, 380, true));
    const tailDelay = 1330 + languages.length * 90;
    reveal('.language-tail', tailDelay, 380, true);
    const powerOn = (element, frames, delay) => introAnimations.push(element.animate(
      frames.map(frame => ({ ...frame, easing: 'steps(1, end)' })),
      { id: 'page-intro', delay: (tailDelay + 200 + delay * FRAME_MS) * rate, duration: (frames.length - 1) * FRAME_MS * rate, fill: 'both' },
    ));
    for (const wedge of document.querySelectorAll('.language-wedge')) {
      powerOn(wedge, ['0', '0', '.35', '.35', '.7', '1'].map(x => ({ transform: `scaleX(${x})` })), 0);
    }
    for (const group of [document.querySelectorAll('.language-chevrons path'), document.querySelectorAll('.language-signal > span')]) {
      group.forEach((cell, index) => powerOn(cell, [
        ...[...group].map((_, frame) => ({ opacity: frame === index ? 1 : .2 })), { opacity: 1 },
      ], group[0].closest('.language-signal') ? 3 : 0));
    }
    reveal('#drop-zone', 1510, 490, true);
    reveal('#patch-button', 1810, 410, true);
    reveal('.message-panel', 2160, 300, true);
    reveal('.actions .panel-markings', 2320, 240, true);
    reveal('.overview-frame, .project-overview .crt-texture', 2170, 550);
    reveal('#about-title', 2320, 380, true);
    reveal('.project-intro', 2530, 440);
    reveal('.project-overview .panel-markings', 2650, 240, true);
    for (let index = 1; index <= document.querySelectorAll('.feature').length; index++) {
      const feature = `.feature:nth-child(${index})`;
      reveal(`${feature} .feature-frame, ${feature} .crt-texture`, 2490 + index * 80, 400);
      reveal(`${feature} .game-shot`, 2730 + index * 80, 350);
      reveal(`${feature} .feature-copy`, 2820 + index * 80, 340);
      reveal(`${feature} .edition-tabs`, 2930 + index * 80, 300, true);
      reveal(`${feature} .panel-markings`, 2800 + index * 80, 240, true);
    }
    reveal('footer', 3300, 300);
    for (const [index, joint] of document.querySelectorAll('.joint-cap svg').entries()) {
      const delay = joint.closest('.edition-label') ? 800 : 1370;
      introAnimations.push(joint.animate([
        { transform: `rotate(${index % 2 ? 160 : -160}deg) scale(.7)` },
        { transform: 'rotate(0deg) scale(1)' },
      ], { id: 'page-intro', delay: delay * rate, duration: 520 * rate, fill: 'both', easing: 'cubic-bezier(.2, .8, .2, 1)' }));
    }
    document.documentElement.classList.replace('intro-pending', 'intro-running');
    Promise.allSettled(introAnimations.map(animation => animation.finished)).then(() => {
      finishIntro();
      updateMotion();
    });
  }

  function powerCrt(panel, turnOn) {
    for (const animation of panel.getAnimations({ subtree: true })) {
      if (animation.id === 'crt-power') animation.cancel();
    }
    if (document.hidden || reducedMotion.matches) return null;
    // Android 4.0: separate RGB collapse, white highlight, then a one-pixel line shrinking shut.
    // https://android.googlesource.com/platform/frameworks/base/+/android-4.0.4_r2.1/services/surfaceflinger/SurfaceFlinger.cpp
    const curve = (value, slope) => ((1 / (1 + Math.exp((.5 - value) * slope))) - .5) * (1 + Math.exp(-slope / 2)) + .5;
    const frames = turnOn ? 12 : 24;
    const split = turnOn ? 2 / 3 : .5;
    const lineHeight = 1 / panel.clientHeight;
    const colors = ['red', 'green', 'blue'];
    const channelFrames = colors.map(() => []);
    const beamFrames = [];
    for (let frame = 0; frame <= frames; frame++) {
      const offset = frame / frames;
      const vertical = turnOn ? offset >= split : offset < split;
      const stretch = vertical
        ? (turnOn ? (1 - offset) / (1 - split) : offset / split)
        : (turnOn ? 1 - offset / split : (offset - split) / (1 - split));
      const scales = colors.map((_, index) => curve(stretch, 7.5 + index * .5));
      for (const [index, scale] of scales.entries()) {
        channelFrames[index].push({ offset, opacity: vertical ? 1 : 0,
          transform: `scale(${1 + scale}, ${1 - scale})` });
      }
      const width = vertical ? 1 + scales[2] : 1 - scales[1];
      const height = vertical ? Math.max(lineHeight, 1 - scales[2]) : lineHeight;
      beamFrames.push({ offset, transform: `scale(${width}, ${height})`,
        opacity: vertical ? (turnOn ? 0 : scales[1]) : 1 - scales[1] });
    }
    const layer = document.createElement('div');
    layer.className = 'crt-beam';
    layer.setAttribute('aria-hidden', 'true');
    const timing = { duration: 256, easing: 'linear', fill: 'both' };
    const parts = [];
    for (const [index, color] of colors.entries()) {
      const channel = document.createElement('img');
      channel.src = panel.querySelector('img').currentSrc;
      channel.alt = '';
      channel.style.filter = `url(#crt-${color})`;
      layer.append(channel);
      parts.push(channel.animate(channelFrames[index], timing));
    }
    const beam = document.createElement('span');
    beam.className = 'crt-beam-light';
    layer.append(beam);
    parts.push(beam.animate(beamFrames, timing));
    panel.append(layer);
    const animation = layer.animate([{ opacity: 1 }, { opacity: 1 }], { ...timing, id: 'crt-power' });
    const cleanup = () => {
      parts.forEach(part => part.cancel());
      layer.remove();
      animation.cancel();
    };
    animation.finished.then(cleanup, cleanup);
    return animation;
  }

  analogPanels.prepare().then(startIntro).catch(finishIntro);
  return { powerCrt };
}

function fitPatcherTitle(title, scale) {
  const label = title.querySelector('span');
  title.style.fontSize = '';
  const fontSize = parseFloat(getComputedStyle(title).fontSize);
  const needed = (label.offsetWidth + 2 * fontSize) / scale;
  const fit = Math.min(1, (230 + 93 - 28) / needed);
  if (fit < 1) title.style.fontSize = `${fontSize * fit}px`;
  return Math.max(230, Math.ceil(needed * fit + 28));
}

function drawPatcherTitle(title, ribbon, scale) {
  title.style.width = `${ribbon * scale}px`;
  title.style.height = `${28 * scale}px`;
  title.querySelector('svg').setAttribute('viewBox', `0 0 ${ribbon} 28`);
  title.querySelector('path').setAttribute('d', `M0 28 L28 0 L${ribbon} 0 L${ribbon - 28} 28 Z`);
}

function hatchPath(x, width) {
  return `M${x} 9 L${x + width} 9 L${x + width + 44} 53 L${x + 44} 53 Z`;
}

function markWrappedRows(container) {
  let resizeFrame;
  // Items that start a wrapped line drop their leading slant, so rows read like the first one.
  const mark = () => {
    const items = [...container.children];
    for (const item of items) item.classList.remove('row-start');
    for (let pass = 0; pass < items.length; pass++) {
      let changed = false;
      let top = -Infinity;
      for (const item of items) {
        const start = item.offsetTop > top + 1;
        top = item.offsetTop;
        if (start !== item.classList.contains('row-start')) {
          item.classList.toggle('row-start', start);
          changed = true;
        }
      }
      if (!changed) break;
    }
  };
  const observer = new ResizeObserver(() => {
    cancelAnimationFrame(resizeFrame);
    resizeFrame = requestAnimationFrame(mark);
  });
  for (const element of [container, ...container.children]) observer.observe(element);
}

function stepped(element, frames, delay = 0) {
  return element.animate(frames.map(frame => ({ ...frame, easing: 'steps(1, end)' })), {
    duration: (frames.length - 1) * FRAME_MS,
    delay: delay * FRAME_MS,
  });
}

// Zentrix stutter, slam, echo, and chase, fired once when the selected language changes.
function animateLanguageChanges(picker) {
  const options = () => [...picker.querySelectorAll('.language-option')];
  let selected = options().find(option => option.getAttribute('aria-pressed') === 'true');
  let running = [];
  new MutationObserver(() => {
    const previous = selected;
    selected = options().find(option => option.getAttribute('aria-pressed') === 'true');
    if (!selected || selected === previous || !motionAllowed()) return;
    for (const animation of running) animation.cancel();
    const forward = !previous || options().indexOf(selected) > options().indexOf(previous);
    const code = selected.querySelector('span');
    running = [
      stepped(selected, [{ opacity: .3 }, { opacity: 1 }, { opacity: .5 }, { opacity: 1 }, { opacity: .7 }, { opacity: 1 }]),
      stepped(code, [
        { transform: 'scale(1.45)', opacity: .2 },
        { transform: 'scale(1.18)', opacity: .55 },
        { transform: 'scale(1.04)', opacity: 1 },
        { transform: 'scale(1)', opacity: 1 },
        { transform: 'scale(1)', opacity: .5 },
        { transform: 'scale(1)', opacity: 1 },
      ]),
    ];
    running.push(...ghost(code));
    if (previous) {
      running.push(stepped(previous, [{ opacity: 1 }, { opacity: .4 }, { opacity: 1 }, { opacity: 1 }, { opacity: .5 }, { opacity: 1 }]));
    }
    const stripes = [...picker.querySelectorAll('.language-chevrons path')];
    if (!forward) stripes.reverse();
    stripes.forEach((stripe, index) => running.push(stepped(stripe, [
      ...stripes.map((_, frame) => ({ opacity: frame === index ? 1 : .2 })), { opacity: .2 }, { opacity: 1 },
    ], 1)));
    const wedge = picker.querySelector('.language-wedge');
    if (wedge) {
      running.push(stepped(wedge, [
        { transform: 'scaleX(0)' }, { transform: 'scaleX(0)' }, { transform: 'scaleX(.35)' }, { transform: 'scaleX(.35)' },
        { transform: 'scaleX(.7)' }, { transform: 'scaleX(1)' },
      ]));
    }
    const segments = [...picker.querySelectorAll('.language-signal > span')];
    if (!forward) segments.reverse();
    segments.forEach((segment, index) => running.push(stepped(segment, [
      ...segments.map((_, frame) => ({ opacity: frame === index ? 1 : .2 })), { opacity: 1 },
    ], 3)));
    const title = document.querySelector('.patcher-title span');
    if (title) {
      running.push(stepped(title, [
        { opacity: 0 }, { opacity: 0 }, { opacity: .6 }, { opacity: .2 }, { opacity: 1 }, { opacity: .5 }, { opacity: 1 },
      ]));
    }
  }).observe(picker, { subtree: true, attributeFilter: ['aria-pressed'] });
}

const ghosted = new WeakMap();
// Zentrix 04_054.42 echoes: two copies of the control's label drift apart and fade.
function ghost(source) {
  const now = performance.now();
  if (!source || now - (ghosted.get(source) ?? -Infinity) < 120) return [];
  ghosted.set(source, now);
  const rect = source.getBoundingClientRect();
  return [-1, 1].map(direction => {
    const copy = source.cloneNode(true);
    for (const element of [copy, ...copy.querySelectorAll('*')]) {
      element.removeAttribute('id');
      element.removeAttribute('data-i18n');
    }
    copy.classList.add('control-ghost');
    copy.setAttribute('aria-hidden', 'true');
    copy.style.left = '0px';
    copy.style.top = '0px';
    source.after(copy);
    const placed = copy.getBoundingClientRect();
    copy.style.left = `${rect.left - placed.left}px`;
    copy.style.top = `${rect.top - placed.top}px`;
    copy.style.width = `${rect.width}px`;
    copy.style.height = `${rect.height}px`;
    const animation = stepped(copy, [0, .65, .45, .3, .15, 0].map((opacity, index) => ({
      transform: `translateX(${direction * index * 3}px) scale(${1 + index * .04})`, opacity,
    })));
    animation.finished.catch(() => {}).finally(() => copy.remove());
    return animation;
  });
}

function ghostSource(control) {
  const visible = element => element.getClientRects().length > 0;
  return [...control.querySelectorAll('.control-label'), ...control.querySelectorAll(':scope > span:not([aria-hidden])')].find(visible) ??
    control.querySelector(':scope > svg');
}

function ghostOnInteraction() {
  const controls = '.menu-control, .small-control, .edition-tab, .language-option';
  for (const type of ['click', 'drop']) {
    document.addEventListener(type, event => {
      const control = event.target.closest?.(controls);
      if (control && !control.matches(':disabled') && motionAllowed()) ghost(ghostSource(control));
    });
  }
}

function animateTabChanges(tablist) {
  let running = [];
  new MutationObserver(records => {
    const selected = records.map(record => record.target).find(tab => tab.getAttribute('aria-selected') === 'true');
    const previous = records.map(record => record.target).find(tab => tab.getAttribute('aria-selected') !== 'true');
    if (!selected || !motionAllowed()) return;
    for (const animation of running) animation.cancel();
    const label = ghostSource(selected);
    running = [
      stepped(selected, [{ opacity: .3 }, { opacity: 1 }, { opacity: .5 }, { opacity: 1 }, { opacity: .7 }, { opacity: 1 }]),
      stepped(label, [
        { transform: 'scale(1.3)', opacity: .2 },
        { transform: 'scale(1.12)', opacity: .55 },
        { transform: 'scale(1.03)', opacity: 1 },
        { transform: 'scale(1)', opacity: 1 },
        { transform: 'scale(1)', opacity: .5 },
        { transform: 'scale(1)', opacity: 1 },
      ]),
      ...ghost(label),
    ];
    if (previous) running.push(stepped(previous, [{ opacity: 1 }, { opacity: .4 }, { opacity: 1 }, { opacity: 1 }, { opacity: .5 }, { opacity: 1 }]));
  }).observe(tablist, { subtree: true, attributeFilter: ['aria-selected'] });
}
