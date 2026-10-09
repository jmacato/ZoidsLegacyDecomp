#!/usr/bin/env python3
"""Check that game text fits the windows the decompiled code draws it in.

Each draw call in src/ names its text, window and column. Window boxes come from the menu
scripts that the same function (or its caller) runs. Every string is laid out by the shared
text core at that width, and the renderer's own clip flag decides whether it fits.
"""

import argparse
import csv
from functools import lru_cache
import json
from pathlib import Path
import re
import struct
import sys

from decomp_calls import (CAST, OPEN_WINDOW, RUN_SCRIPT, callers, evaluate, sources,
                          symbols)
import dialogue
import game_text
import scene_layout
import script_context
import text_core

ROOT = Path(__file__).resolve().parent.parent
LANGUAGE_NAMES = {'en': 'en', 'eng': 'en', 'english': 'en', 'es': 'es', 'esp': 'es', 'spanish': 'es'}
# Native helpers: argument positions of text, window and column.
DRAWS = {
    'func_080981F0': {'text': 0, 'window': 2, 'column': 3, 'row': 4},
    'func_08098248': {'text': 0, 'window': 2},
    'func_080988C8': {'text': 1, 'window': 0},
    'func_080989EC': {'text': 2, 'window': 0},
}
RAM_TEXT = range(0x02000000, 0x02040000)
SCROLLING_TEXT = 'func_080E2DCC'
COPIES = {'func_080ED128': 'copy', 'func_080ED038': 'copy', 'func_08099F5C': 'append'}
PILOT_NAME = 'func_080E7B64'
@lru_cache(maxsize=1)
def table_bounds():
    rom = game_text.clean_rom()
    starts = sorted({value for name, value in symbols().items() if 0x087E0000 <= value < 0x087F8000} |
                    {value for source in sources() for value in source.names.values()
                     if isinstance(value, int) and 0x087E0000 <= value < 0x087F8000})
    bounds = {}
    for index, start in enumerate(starts):
        end = starts[index + 1] if index + 1 < len(starts) else start + 0x400
        entries = []
        for at in range(start - dialogue.BASE, min(end - dialogue.BASE, start - dialogue.BASE + 0x2000), 4):
            pointer = struct.unpack_from('<I', rom, at)[0]
            if not dialogue.BASE <= pointer < dialogue.BASE + len(rom):
                break
            entries.append(pointer - dialogue.BASE)
        bounds[start] = entries
    return bounds


def text_targets(expression, source, function, names, depth=0):
    """Return ROM text offsets an argument can point at, and how they were found."""
    expression = CAST.sub(' ', expression).strip().strip('()').strip()
    value = evaluate(expression, names)
    if value is not None and dialogue.BASE <= value < dialogue.BASE + 0x1000000:
        return {value - dialogue.BASE}, 'literal'
    if PILOT_NAME in [source.aliases.get(word, word) for word in re.findall(r'\b(\w+)\s*\(', expression)]:
        return set(table_bounds().get(symbols().get('D_087EDFB4', 0x087EDFB4), [])), 'pilot names'
    for candidate in [*re.findall(r'\b(\w+)\s*\[', expression), *re.findall(r'0x087E[0-9A-Fa-f]{4}', expression),
                      *re.findall(r'\b\w+\b', expression)]:
        base = evaluate(candidate, names)
        if base is not None and base in table_bounds():
            if re.search(r'\[|\*\s*4|<<\s*2|M2C_FIELD', expression) or candidate != expression:
                return set(table_bounds()[base]), f'table 0x{base:08X}'
    if depth < 2 and function is not None and re.fullmatch(r'[a-z_]\w*', expression):
        body = source.text[function[2]:function[3]]
        targets = set()
        for match in re.finditer(rf'(?<![\w*.>]){re.escape(expression)}\b(?:\s+asm\("\w+"\))?\s*(?<![=!<>+\-*/|&^])=(?!=)\s*([^;]+);', body):
            targets |= text_targets(match[1], source, function, names, depth + 1)[0]
        if targets:
            return targets, 'local'
    if depth < 2 and function is not None:
        targets, how = set(), None
        key = expression if value is None else None
        for target, arguments, _ in source.calls(function[2], function[3]):
            if target in COPIES and len(arguments) >= 2:
                destination = CAST.sub(' ', arguments[0]).strip()
                same = destination == key or (value is not None and evaluate(destination, names) == value)
                if same:
                    found, _ = text_targets(arguments[1], source, function, names, depth + 1)
                    targets |= found
                    how = 'buffer'
        if targets:
            return targets, how
    return set(), None


def script_windows(source, function, names, before=None, depth=0):
    """Return window definitions by id, in effect at a point of the function."""
    windows = {}
    for target, arguments, at in source.calls(function[2], function[3]):
        if before is not None and at > before or not arguments:
            continue
        if target == OPEN_WINDOW and len(arguments) >= 6:
            values = [literal(argument, names) for argument in arguments[:6]]
            if None not in values:
                number, x, y, width, height, flags = values
                windows[number] = [{'id': number, 'x': x * 8, 'y': y * 8, 'width': width * 8,
                                    'height': height * 8, 'runtimeFlags': flags | 1,
                                    'sourceRoot': f'{source.path.relative_to(ROOT)}:{source.line(at)}'}]
            continue
        if target != RUN_SCRIPT:
            continue
        root = evaluate(arguments[0], names)
        if root is None:
            continue
        block = script_context.menu_scripts()[0].get(f'menu:0x{root - dialogue.BASE:06X}')
        for window in (block or {}).get('windowDefinitions', []):
            windows[window['id']] = [window]
    if depth < 1:
        inherited = {}
        for caller_source, caller in callers().get(function[1], ()):
            found = script_windows(caller_source, caller, caller_source.locals(caller), None, depth + 1)
            for number, boxes in found.items():
                inherited.setdefault(number, []).extend(boxes)
        # A window the function opens itself wins over windows its callers opened.
        for number, boxes in inherited.items():
            windows.setdefault(number, boxes)
    return windows


def literal(expression, names, source=None, function=None, at=None):
    text = CAST.sub(' ', expression).strip()
    if re.fullmatch(r'-?\s*(?:0[xX][0-9A-Fa-f]+|\d+)|[A-Z_][A-Z0-9_]*', text):
        return evaluate(text, names)
    if source is not None and re.fullmatch(r'[a-z_]\w*', text):
        value = value_before(source, function, text, at, names)
        if value is not None and re.fullmatch(r'-?\s*(?:0[xX][0-9A-Fa-f]+|\d+)|[A-Z_][A-Z0-9_]*',
                                              CAST.sub(' ', value).strip()):
            return evaluate(value, names)
    return None


def value_before(source, function, name, at, names):
    """Return the expression last assigned to a local before a position in the function."""
    body = source.text[function[2]:at]
    found = None
    for match in re.finditer(rf'(?<![\w*.>]){re.escape(name)}\b(?:\s+asm\("\w+"\))?\s*(?<![=!<>+\-*/|&^])=(?!=)\s*([^;]+);', body):
        found = match[1]
    return found


def ram_address(expression, source, function, at, names, depth=0):
    """Resolve a pointer expression to a RAM text buffer address, ignoring element sizes."""
    text = CAST.sub(' ', expression).strip()
    value = evaluate(text, names)
    if value is not None:
        return value if value in RAM_TEXT else None
    if depth > 3:
        return None
    match = re.fullmatch(r'\(?\s*([A-Za-z_]\w*)\s*([+-]\s*\d+)?\s*\)?', text)
    if match:
        assigned = value_before(source, function, match[1], at, names)
        if assigned is not None:
            base = ram_address(assigned, source, function, at, names, depth + 1)
            if base is not None:
                return base
    for constant in re.findall(r'0x0203[0-9A-Fa-f]{4}', text):
        return int(constant, 16)
    for word in re.findall(r'\b[a-z_]\w*\b', text):
        assigned = value_before(source, function, word, at, names)
        if assigned is not None and depth < 3:
            base = ram_address(assigned, source, function, at, names, depth + 1)
            if base is not None:
                return base
    return None


def buffer_pieces(source, function, buffer, at, names):
    """Return the text pieces written into a RAM buffer since the previous draw from it."""
    pieces = []
    for target, arguments, position in source.calls(function[2], at):
        if target in DRAWS:
            spec = DRAWS[target]
            if len(arguments) > spec['text']:
                drawn = ram_address(arguments[spec['text']], source, function, position, names)
                if drawn is not None and abs(drawn - buffer) <= 8:
                    pieces = []
            continue
        if target not in COPIES or len(arguments) < 2:
            continue
        destination = ram_address(arguments[0], source, function, position, names)
        if destination is None or not -8 <= destination - buffer <= 8:
            continue
        if COPIES[target] == 'copy' and destination <= buffer + 2:
            pieces = []
        offsets, _ = text_targets(arguments[1], source, function, names)
        if offsets:
            pieces.append(offsets)
    return pieces


def draw_sites():
    """Yield text offsets with the window the code draws them in."""
    for source in sources():
        for function in source.functions:
            names = source.locals(function)
            for target, arguments, at in source.calls(function[2], function[3]):
                spec = DRAWS.get(target)
                if not spec or len(arguments) <= max(spec.values()):
                    continue
                offsets, how = text_targets(arguments[spec['text']], source, function, names)
                parts = None
                buffer = ram_address(arguments[spec['text']], source, function, at, names)
                if buffer is not None:
                    parts = buffer_pieces(source, function, buffer, at, names)
                    if parts:
                        offsets, how = max(parts, key=len), 'composed buffer'
                if not offsets:
                    continue
                window_id = literal(arguments[spec['window']], names, source, function, at)
                column = literal(arguments[spec['column']], names, source, function, at) if 'column' in spec else 0
                row = literal(arguments[spec['row']], names, source, function, at) if 'row' in spec else 0
                site = f'{source.path.relative_to(ROOT)}:{source.line(at)}'
                boxes = script_windows(source, function, names, at).get(window_id, []) if window_id is not None else []
                if not boxes:
                    yield {'offsets': offsets, 'site': site, 'how': how, 'window': None,
                           'reason': 'window not resolved'}
                    continue
                # Callers can open the same window id with different sizes; the widest avoids false alarms.
                box = max(boxes, key=lambda item: (item['width'], item['height']))
                yield {'offsets': offsets, 'parts': parts if how == 'composed buffer' else None,
                       'site': site, 'how': how, 'window': box,
                       'windowLabel': f'#{box["id"]} from {box["sourceRoot"]}',
                       'column': column or 0, 'row': row or 0,
                       'exact': column is not None and row is not None and len({b['width'] for b in boxes}) == 1}


def script_sites():
    blocks, index = script_context.menu_scripts()
    for offset, locations in index.items():
        for location in locations:
            window = location.get('window')
            title = blocks[location['block']]['commands'][location['commandIndex']]['opcode'] == '09'
            if window and window['width']:
                yield {'offsets': {int(offset, 16)}, 'site': f'{location["block"]} at {location["at"]}',
                       'how': 'menu script title' if title else 'menu script', 'window': window,
                       'windowLabel': f'#{window["id"]} from {window["sourceRoot"]}', 'column': 0,
                       'row': -1 if title else 0, 'exact': location.get('windowSource') == 'script'}


def language_text(lang):
    entries, scenes, *_ = game_text.load_language(lang)
    return entries, scenes


def encoded(lang, entry):
    text = game_text.expand(lang, game_text.translation(entry))
    return game_text.encode_direct(entry, text, preview=True)


def composed(lang, by_number, main, parts):
    """Join the subject string with the widest variant of every other buffer piece."""
    chunks = []
    for piece in parts:
        if main in piece:
            chunks.append(encoded(lang, by_number[main])[:-1])
            continue
        variants = [encoded(lang, by_number[number])[:-1] for number in piece if number in by_number]
        if variants:
            chunks.append(max(variants, key=lambda data: fits(data + b'\0', WIDE, 0, 0)[1]))
    return b''.join(chunks) + b'\0'


WIDE = {'id': 0, 'width': 2048, 'height': 64, 'flags': 0}


def window_profile(window, row):
    """Mirror the runtime's text area for a script window (dialogue_vwf.c vwf_render)."""
    # Menu scripts store window flags shifted right by four (run_menu_script.c MENU_OPEN_WINDOW).
    flags = window.get('runtimeFlags', window.get('flags', 0) * 0x10 | 1)
    width, height = window['width'] // 8, window['height'] // 8
    title = row == -1
    kind = 'compact_row' if title else (
        ('portrait_dialogue' if width <= 22 else 'full_dialogue') if flags & 0x40 else 'label')
    profile = text_core.named_profile(kind, width=(width - 2) * 8, height=8 if title else (height - 2) * 8)
    profile.left = 2 if flags & 0x10 else 0
    profile.top = -8 if title else 0
    profile.bottom = 0 if title else (height - 2) * 8
    profile.wrap = text_core.TEXT_WRAP_WORD if flags & 0x50 else text_core.TEXT_WRAP_NONE
    profile.overflow = text_core.TEXT_OVERFLOW_CLIP
    profile.paginate = int(bool(flags & 0x10))
    return profile


def fits(encoded_text, window, column, row):
    profile = window_profile(window, row)
    start = (profile.left + column * 8, profile.top if row == -1 else row * 8, -1, 0)
    if start[0] >= profile.right:
        return True, 0, profile.right - profile.left
    output = scene_layout.engine().layout(encoded_text, profile, player=game_text.player_bytes('Zeru'),
                                          initial=start)
    right = max((item['ink_x'] + item['width'] - item['clip_right'] for item in output.placements), default=0)
    available = profile.right - start[0]
    # Only horizontal loss counts: lists scroll and wrapped windows page, so extra lines are not clipped.
    lost = profile.wrap == text_core.TEXT_WRAP_NONE and right > profile.right + (profile.alignment == text_core.TEXT_ALIGN_RIGHT)
    lost |= any(item['clip_right'] for item in output.placements)
    return not lost, right - start[0], available


def scrolling_texts():
    """Text started with InitializeScrollingTextWindow wraps and pages, so it never clips."""
    offsets = set()
    for source in sources():
        for function in source.functions:
            names = source.locals(function)
            for target, arguments, _ in source.calls(function[2], function[3]):
                if target == SCROLLING_TEXT and len(arguments) >= 2:
                    offsets |= text_targets(arguments[1], source, function, names)[0]
    return offsets


def check(lang):
    entries, _ = language_text(lang)
    scrolling = scrolling_texts()
    by_number = {int(offset, 16): entry for offset, entry in entries.items()}
    results, unresolved, checked = {}, [], 0
    for site in [*draw_sites(), *script_sites()]:
        if site['window'] is None:
            unresolved.append(site)
            continue
        for number in site['offsets'] - scrolling:
            entry = by_number.get(number)
            if entry is None:
                continue
            try:
                data = composed(lang, by_number, number, site['parts']) if site.get('parts') else encoded(lang, entry)
                ok, needed, available = fits(data, site['window'], site['column'], site['row'])
            except (ValueError, KeyError):
                continue
            checked += 1
            if ok:
                continue
            offset = f'0x{number:06X}'
            item = results.setdefault(offset, {
                'offset': offset, 'text': game_text.translation(entry), 'needed': needed,
                'available': available, 'left': 0, 'right': available, 'exact': False, 'sites': []})
            if available - needed < item['available'] - item['needed']:
                item.update(needed=needed, available=available, right=available)
            item['exact'] |= site['exact']
            item['table'] = item.get('table', True) and site['how'].startswith(('table', 'pilot'))
            item['sites'].append({'site': site['site'], 'how': site['how'], 'window': site['windowLabel'],
                                  'column': site['column'], 'row': site['row'], 'exact': site['exact']})
    clipped = sorted(results.values(), key=lambda item: int(item['offset'], 16))
    for item in clipped:
        item['screens'] = len(item['sites'])
        item['example'] = item['sites'][0]['site']
    return {'language': lang, 'checked': checked, 'clipped': clipped,
            'exact': sum(1 for item in clipped if item['exact']),
            'unresolvedSites': len(unresolved)}


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--language', default='es', help='eng or esp (also en, es)')
    parser.add_argument('--output', type=Path, help='JSON report path (default: build/text-fit-<lang>.json)')
    parser.add_argument('--csv', type=Path, help='Also write a CSV list')
    args = parser.parse_args()
    lang = LANGUAGE_NAMES.get(args.language.lower())
    if lang is None:
        parser.error('--language must be eng or esp.')
    if not game_text.ROM_PATH.exists():
        parser.exit(1, f'Place the clean USA ROM at {game_text.ROM_PATH.name} in the repository root.\n')
    report = check(lang)
    output = args.output or ROOT / 'build' / f'text-fit-{lang}.json'
    output.parent.mkdir(exist_ok=True)
    output.write_text(json.dumps(report, indent=1, ensure_ascii=False) + '\n')
    if args.csv:
        with args.csv.open('w', newline='', encoding='utf-8') as handle:
            writer = csv.writer(handle)
            writer.writerow(['offset', 'text', 'needed_px', 'available_px', 'exact', 'sites'])
            for item in report['clipped']:
                writer.writerow([item['offset'], item['text'].replace('\n', ' / '), item['needed'],
                                 item['available'], item['exact'], '; '.join(site['site'] for site in item['sites'])])
    print(f'{lang}: {report["checked"]} text placements checked. {report["exact"]} strings clip in fully resolved '
          f'windows; {len(report["clipped"]) - report["exact"]} more clip where the window or position was inferred. '
          f'{report["unresolvedSites"]} draw sites have unknown windows. Report: {output.relative_to(ROOT) if output.is_relative_to(ROOT) else output}')
    return 1 if report['exact'] else 0


if __name__ == '__main__':
    sys.exit(main())
