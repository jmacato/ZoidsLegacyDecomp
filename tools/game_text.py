"""Load and encode the game text for one language."""

from functools import lru_cache
from pathlib import Path
import re

import dialogue
import insert_vwf

ROOT = Path(__file__).resolve().parent.parent
ROM_PATH = ROOT / 'Zoids Legacy (USA).gba'
LANGUAGES = {
    'en': {'name': 'English', 'dialogue': 'dialogue-en.json', 'scenes': 'scene-translation.json', 'version': 'VERSION'},
    'es': {'name': 'Español', 'dialogue': 'dialogue-es.json', 'scenes': 'scene-translation-es.json', 'version': 'VERSION_ES'},
}


def data_path(lang, kind):
    return ROOT / LANGUAGES[lang][kind]


@lru_cache(maxsize=1)
def clean_rom():
    return dialogue.read_rom(ROM_PATH)


def load_language(lang):
    stamp = tuple(data_path(lang, kind).stat().st_mtime_ns for kind in ('dialogue', 'scenes'))
    return _load_language(lang, stamp)


@lru_cache(maxsize=4)
def _load_language(lang, _stamp):
    document = insert_vwf.load_translation(data_path(lang, 'dialogue'), ROM_PATH)
    scenes = dialogue.load_scenes(data_path(lang, 'scenes'), ROM_PATH)
    scene_rows = {entry['english_offset']: entry for entry in scenes['entries']}
    entries = {offset: entry for offset, entry in rom_entries().items() if offset not in scene_rows}
    entries.update((entry['offset'], entry) for entry in document['entries'])
    return entries, scene_rows, document, scenes


@lru_cache(maxsize=1)
def rom_entries():
    return dialogue.rom_catalog(ROM_PATH)


def expand(lang, text):
    return text.replace('{VERSION}', insert_vwf.release_version(data_path(lang, 'version')))


def translation(entry):
    if 'english_draft' in entry:
        return entry['english_draft']
    return entry.get('build_text', entry['text'])


def encode_direct(entry, text, preview=False):
    source = dialogue.entry_source(entry)
    template_format = entry['kind'] == 'menu' or entry.get('template_format', False)
    compact = entry.get('compact_format', False)
    if not template_format:
        return dialogue.encode_text(text, source, compact=compact)
    encoded = dialogue.encode_menu_format(text, source, compact)
    if preview:
        return re.sub(rb'%[1-9][0-9]*\$[dsv]|%[ds]', lambda match: dialogue.encode_text(
            '9999' if match[0][-1:] in (b'd', b'v') else 'G', source, compact=compact)[:-1], encoded)
    return encoded


def player_bytes(name):
    name = name or 'Zeru'
    if not 1 <= len(name) <= 8 or any(char in '{}\n\r' or ord(char) < 0x20 for char in name):
        raise ValueError('The preview player name must contain 1 to 8 text characters.')
    return dialogue.encode_text(name)
