import en from './locales/en.js';
import es from './locales/es.js';

const languages = { en, es };
const attributes = ['aria-label', 'alt', 'content', 'src', 'title'];

export function text(key, language) {
  return languages[language]?.[key] ?? en[key] ?? key;
}

export function localizePage(language) {
  document.documentElement.lang = language;
  for (const element of document.querySelectorAll('[data-i18n]')) {
    element.textContent = text(element.dataset.i18n, language);
  }
  for (const attribute of attributes) {
    for (const element of document.querySelectorAll(`[data-i18n-${attribute}]`)) {
      element.setAttribute(attribute, text(element.getAttribute(`data-i18n-${attribute}`), language));
    }
  }
}
