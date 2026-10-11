#!/usr/bin/env python3
"""Browse, preview and edit the game text for English or Spanish in a local web editor."""

import argparse
from functools import lru_cache
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import re
import struct
import threading
from urllib.parse import parse_qs, unquote, urlparse

import decomp_calls
import dialogue
from game_text import (LANGUAGES, ROM_PATH, ROOT, clean_rom, data_path, encode_direct, expand, load_language,
                       player_bytes, translation)
import insert_vwf
import scene_layout
import script_context
import text_core
import text_fit_check

STATIC = Path(__file__).with_name('script_editor')
CREDITS_OFFSET = 0x029043
SPEAKER = re.compile(r'^\{01 02\}[^\n]+\n')
WINDOWS = {'portrait_dialogue': (64, 96, 176, 64), 'full_dialogue': (0, 96, 240, 64),
           'battle_choice': (0, 112, 88, 48)}
LOCK = threading.Lock()


def language(query):
    value = query.get('lang', ['en'])[0]
    if value not in LANGUAGES:
        raise ValueError(f'Unknown language {value}.')
    return value


@lru_cache(maxsize=1)
def deck_names():
    rom = clean_rom()
    return {pointer - dialogue.BASE for pointer in struct.unpack_from('<52I', rom, insert_vwf.DECK_NAME_TABLE)}


@lru_cache(maxsize=1)
def checker():
    return text_core.TextChecker(scene_layout.engine().data)


@lru_cache(maxsize=1)
def window_groups():
    """Pair menu titles (opcode 09) with the body text (opcode 05) drawn into the same window."""
    blocks, index = script_context.menu_scripts()
    titles, bodies, owner = {}, {}, {}
    for offset, locations in index.items():
        location = locations[0]
        window = location.get('window')
        if not window:
            continue
        key = (window['sourceRoot'], window['id'])
        command = blocks[location['block']]['commands'][location['commandIndex']]
        (titles if command['opcode'] == '09' else bodies).setdefault(key, []).append(offset)
        owner[offset] = (key, command['opcode'] == '09', window)
    groups = {}
    for offset, (key, is_title, window) in owner.items():
        if is_title:
            groups[offset] = {'window': window, 'title': offset, 'bodies': sorted(bodies.get(key, []), key=lambda o: int(o, 16))}
            continue
        candidates = titles.get(key, [])
        # Several titles can share a window; the nearest one before the body in the ROM belongs to it.
        before = [title for title in candidates if int(title, 16) <= int(offset, 16)]
        title = max(before, key=lambda o: int(o, 16)) if before else (min(candidates, key=lambda o: int(o, 16)) if candidates else None)
        groups[offset] = {'window': window, 'title': title, 'bodies': [offset]}
    return groups


def command_window(command):
    if 'windowId' in command:
        return command['windowId']
    if 'window' in command:
        return command['window']['id']
    raw = command.get('raw', '').split()
    return int(raw[1], 16) if len(raw) > 1 else None


@lru_cache(maxsize=1)
def menu_screens():
    """Replay the menu scripts each C function runs and keep what is on screen with each text."""
    blocks, index = script_context.menu_scripts()
    screens = {}
    for source in decomp_calls.sources():
        for function in source.functions:
            names = source.locals(function)
            roots = []
            for target, arguments, _ in source.calls(function[2], function[3]):
                if target == decomp_calls.RUN_SCRIPT and arguments:
                    root = decomp_calls.evaluate(arguments[0], names)
                    if root and f'menu:0x{root - dialogue.BASE:06X}' in blocks:
                        roots.append(f'menu:0x{root - dialogue.BASE:06X}')
            state, recent, local = {}, [], {}
            for key in roots:
                printed = []
                for command in blocks[key]['commands']:
                    opcode, number = command['opcode'], command_window(command)
                    if opcode == '01':
                        state[number] = {'window': command['window'], 'title': None, 'texts': [], 'prompt': None}
                    elif opcode == '02' and number in state:
                        state[number].update(texts=[], prompt=None)
                    elif opcode == '03':
                        state.pop(number, None)
                    elif opcode == '0A' and number in state:
                        state[number]['title'] = None
                    elif opcode in ('05', '09') and 'textOffset' in command:
                        if number not in state:
                            location = next((item for item in index.get(command['textOffset'], [])
                                             if item['block'] == key), None)
                            if not location or not location.get('window'):
                                continue
                            state[number] = {'window': location['window'], 'title': None, 'texts': [], 'prompt': None}
                        if opcode == '09':
                            state[number]['title'] = command['textOffset']
                        else:
                            state[number]['texts'].append(command['textOffset'])
                        printed.append(command['textOffset'])
                    elif opcode in ('07', '08') and number in state:
                        state[number]['prompt'] = 'yes/no' if opcode == '08' else 'select'
                if printed:
                    recent = printed
                # Prompt scripts that only add a cursor still belong to the texts printed before them.
                for offset in recent:
                    if any(offset == item['title'] or offset in item['texts'] for item in state.values()):
                        local[offset] = [dict(item, texts=list(item['texts'])) for item in state.values()]
            for offset, screen in local.items():
                screens.setdefault(offset, screen)
    return screens


@lru_cache(maxsize=1)
def event_choices():
    """Map each story choice list to the dialogue line that asks it."""
    blocks, _ = script_context.event_scripts()
    choices = {}
    for block in blocks.values():
        commands = block['commands']
        for position, command in enumerate(commands):
            if command['opcode'] != '11':
                continue
            choice = f'0x{int(command["at"], 16) + 2:06X}'
            question = next((item['textOffset'] for item in reversed(commands[:position]) if 'textOffset' in item), None)
            if question or choice not in choices:
                choices[choice] = question
    return choices


@lru_cache(maxsize=1)
def name_descriptions():
    """Pair names with descriptions from the decomp's parallel name and description tables."""
    declared = {}
    for source in decomp_calls.sources():
        for name, address in re.findall(r'\b(g\w+?(?:NameTable|DescriptionTable))\[\]\s*asm\("D_(08[0-9A-F]{6})"\)',
                                        source.text):
            declared[name] = int(address, 16)
    bounds = text_fit_check.table_bounds()
    pairs = {}
    for name, address in declared.items():
        if not name.endswith('NameTable'):
            continue
        partner = declared.get(name[:-len('NameTable')] + 'DescriptionTable')
        names, descriptions = bounds.get(address, []), bounds.get(partner, [])
        if partner and len(names) == len(descriptions):
            for left, right in zip(names, descriptions):
                pairs[f'0x{left:06X}'] = ('Description', f'0x{right:06X}')
                pairs[f'0x{right:06X}'] = ('Name', f'0x{left:06X}')
    return pairs


@lru_cache(maxsize=1)
def code_sites():
    """Map texts drawn by C code to the draw calls in src/ that show them."""
    sites = {}
    for site in text_fit_check.draw_sites():
        for number in site['offsets']:
            sites.setdefault(f'0x{number:06X}', []).append(site['site'])
    return {offset: sorted(set(found)) for offset, found in sites.items()}


@lru_cache(maxsize=1)
def choice_questions():
    return {question: choice for choice, question in event_choices().items() if question}


def category(offset, entry, scene):
    number = int(offset, 16)
    if scene:
        return 'scene dialogue'
    if number == CREDITS_OFFSET:
        return 'ending credits'
    if insert_vwf.is_battle_quote(number):
        return 'battle quote'
    if number in deck_names():
        return 'deck command name'
    group = window_groups().get(offset)
    if group and group['title'] == offset:
        return 'menu title'
    if offset in event_choices():
        return 'story choice'
    return {'event': 'event dialogue', 'menu': 'menu template', 'string': 'string'}[entry['kind']]


def original_text(entry):
    if 'english_original_hex' in entry:
        return dialogue.decode_text(bytes.fromhex(entry['english_original_hex']), 0)[0]
    return dialogue.decode_text(dialogue.entry_source(entry), 0)[0]


def fit_report(lang):
    path = ROOT / 'build' / f'text-fit-{lang}.json'
    if not path.exists():
        return {}
    return _fit_report(path, path.stat().st_mtime_ns)


@lru_cache(maxsize=4)
def _fit_report(path, _stamp):
    return {item['offset']: item for item in json.loads(path.read_text())['clipped'] if item.get('offset')}


def screen_texts(offset):
    partners = []
    for item in menu_screens().get(offset, []):
        partners.extend(text for text in [item['title'], *item['texts']] if text and text != offset)
    if offset in event_choices() and event_choices()[offset]:
        partners.append(event_choices()[offset])
    if offset in choice_questions():
        partners.append(choice_questions()[offset])
    if offset in name_descriptions():
        partners.append(name_descriptions()[offset][1])
    return list(dict.fromkeys(partners))


def catalog(lang):
    entries, scenes, *_ = load_language(lang)
    reference = load_language('en') if lang != 'en' else None
    clipped = fit_report(lang)
    rows = []
    for offset, entry in [*scenes.items(), *entries.items()]:
        scene = offset in scenes
        other = (reference[1] if scene else reference[0]).get(offset) if reference else None
        source = bytes.fromhex(entry['english_original_hex'] if scene else entry['original'])
        rows.append({
            'offset': offset,
            'kind': 'scene' if scene else entry['kind'],
            'category': category(offset, entry, scene),
            'original': original_text(entry),
            'text': translation(entry),
            'reference': translation(other) if other else None,
            'templateFormat': not scene and (entry['kind'] == 'menu' or entry.get('template_format', False)),
            'originalBytes': len(source),
            'clipped': clipped.get(offset),
            'screenTexts': screen_texts(offset),
            'pairRole': name_descriptions().get(offset, (None,))[0],
            'windowTitle': window_groups().get(offset, {}).get('title'),
            'windowBodies': window_groups().get(offset, {}).get('bodies', []) if window_groups().get(offset, {}).get('title') == offset else [],
        })
    rows.sort(key=lambda row: int(row['offset'], 16))
    return {'entries': rows, 'count': len(rows), 'language': lang,
            'languages': {key: value['name'] for key, value in LANGUAGES.items()}}


def encoded_units(encoded):
    groups = []
    for unit in dialogue.text_units(encoded, 0):
        kind = 'control' if unit[0] < 0x20 else 'ASCII' if len(unit) == 1 else 'Shift-JIS'
        label = '↵' if unit == b'\x0a' else dialogue.readable(unit)
        if groups and kind != 'control' and groups[-1]['kind'] == kind and len(groups[-1]['text']) < 24:
            groups[-1]['text'] += label
            groups[-1]['bytes'] += ' ' + unit.hex(' ').upper()
        else:
            groups.append({'kind': kind, 'text': label, 'bytes': unit.hex(' ').upper()})
    groups.append({'kind': 'control', 'text': '{00}', 'bytes': '00'})
    return groups


def window_preview(output, window, *, text_x, text_y, profile_name, source='inferred', window_id=0):
    spans = scene_layout.pixel_spans(output.pixels or [], output.pixel_width, 0, output.pixel_height)
    return {'profile': profile_name, 'width': output.pixel_width, 'height': output.pixel_height,
            'bounds': output.bounds, 'breaks': output.breaks,
            'colors': sorted({item['color'] for item in output.placements}),
            'overflowed': output.overflowed, 'missing': [f'{code:04X}' for code in output.missing],
            'spans': spans, 'pages': [spans], 'windows': [window], 'textX': text_x, 'textY': text_y,
            'windowId': window_id, 'windowSource': source, 'windowSetup': None}


def dialogue_preview(entry, text, player, *, profile_name, source):
    candidate = {'english_offset': entry.get('english_offset', entry.get('offset')), 'english_draft': text,
                 'layout_profile': profile_name}
    result = scene_layout.preview(candidate, text, player=player)
    x, y, width, height = WINDOWS[profile_name]
    result.update(windows=[{'id': 0, 'x': x, 'y': y, 'width': width, 'height': height}],
                  textX=x + 8, textY=y + 4, windowId=0, windowSource=source, windowSetup=None)
    return result


def credits_preview(entry, text, player):
    encoded = encode_direct(entry, text)
    lines, line = [], bytearray()
    for unit in dialogue.text_units(encoded, 0):
        if unit == b'\n':
            lines.append(bytes(line))
            line.clear()
        else:
            if len(line) + len(unit) > 159:
                lines.append(bytes(line))
                line.clear()
            line.extend(unit)
    if line or not lines:
        lines.append(bytes(line))
    color, spans, bounds, missing, colors, overflowed = 0, [], [], [], set(), False
    for index, line in enumerate(lines):
        while line.startswith(b'\x01'):
            color, line = line[1], line[2:]
        leading = trailing = 0
        while line.startswith(b'\x81\x40'):
            leading, line = leading + 1, line[2:]
        while line.endswith(b'\x81\x40'):
            trailing, line = trailing + 1, line[:-2]
        profile = text_core.named_profile('credits')
        if abs(leading - trailing) <= 1:
            profile.alignment = text_core.TEXT_ALIGN_CENTER
        else:
            profile.left = leading * 8
        output = scene_layout.engine().layout(line + b'\0', profile, player=player,
                                              initial=(profile.left, 0, -1, color), compose=True)
        if output.status != 'end':
            raise ValueError(f'Preview failed: {output.status}')
        color = output.state[3]
        top = index * 16
        spans.extend([x, row + top, width, value] for x, row, width, value in
                     scene_layout.pixel_spans(output.pixels or [], output.pixel_width, 0, output.pixel_height))
        if output.bounds[2] > output.bounds[0]:
            left, upper, right, lower = output.bounds
            bounds.append((left, upper + top, right, lower + top))
        missing.extend(f'{value:04X}' for value in output.missing)
        colors.update(item['color'] for item in output.placements)
        overflowed |= output.overflowed
    palette = ['#%02x%02x%02x' % tuple((value >> shift & 31) * 255 // 31 for shift in (0, 5, 10))
               for value in struct.unpack_from('<16H', clean_rom(), 0x7A57F0)]
    return {'profile': 'credits', 'width': 240, 'height': len(lines) * 16, 'lineCount': len(lines),
            'lineKeys': [line.hex() for line in lines], 'palette': palette, 'background': palette[0],
            'bounds': (min(item[0] for item in bounds), min(item[1] for item in bounds),
                       max(item[2] for item in bounds), max(item[3] for item in bounds)) if bounds else (0, 0, 0, 0),
            'breaks': [{'explicit': True, 'y': index * 16} for index in range(1, len(lines))],
            'colors': sorted(colors), 'overflowed': overflowed, 'missing': missing, 'spans': spans,
            'pages': [spans], 'windows': [], 'textX': 0, 'textY': 0, 'windowId': None,
            'windowSource': 'credits', 'windowSetup': None}


def window_text_layer(lang, entries, offset, text, player, window, *, title, selected, initial=None):
    entry = entries[offset]
    encoded = encode_direct(entry, expand(lang, text), preview=True)
    width = max(8, window['width'] - 16)
    if title:
        profile = text_core.named_profile('compact_row', width=width, height=8)
    else:
        profile = text_core.named_profile('label', width=width, height=max(8, window['height'] - 16))
    profile.overflow = text_core.TEXT_OVERFLOW_CLIP
    output = scene_layout.engine().layout(encoded, profile, player=player, compose=True, initial=initial)
    return {'offset': offset, 'title': title, 'selected': selected, 'x': window['x'] + 8,
            'y': window['y'] + (0 if title else 8), 'overflowed': output.overflowed,
            'spans': scene_layout.pixel_spans(output.pixels or [], output.pixel_width, 0, output.pixel_height),
            'output': output}


def screen_preview(lang, entry, text, player):
    """Render every window on screen when this menu text appears."""
    screen = menu_screens().get(entry['offset'])
    if not screen:
        return None
    entries, *_ = load_language(lang)
    layers, prompts, chosen = [], [], None
    for item in screen:
        window = item['window']
        state = None
        for offset, is_title in [*([(item['title'], True)] if item['title'] else []),
                                 *((offset, False) for offset in item['texts'])]:
            if offset not in entries:
                continue
            value = text if offset == entry['offset'] else translation(entries[offset])
            layer = window_text_layer(lang, entries, offset, value, player, window, title=is_title,
                                      selected=offset == entry['offset'], initial=None if is_title else state)
            if not is_title:
                state = layer['output'].state
            if layer['selected']:
                chosen = (layer, window)
            layers.append(layer)
        if item['prompt']:
            prompts.append({'x': window['x'] + 1, 'y': window['y'] + 12, 'kind': item['prompt'], 'window': window['id']})
    if chosen is None:
        return None
    layer, window = chosen
    output = layer['output']
    for item in layers:
        item.pop('output', None)
    result = window_preview(output, window, text_x=layer['x'], text_y=layer['y'],
                            profile_name='menu title' if layer['title'] else 'menu', source='script',
                            window_id=window['id'])
    result.update(windows=[item['window'] for item in screen], layers=layers, prompts=prompts,
                  windowSetup=window['sourceRoot'],
                  screen={'texts': [item['offset'] for item in layers], 'prompts': [item['kind'] for item in prompts]})
    return result


def choice_window(lang, offset, text, player, *, selected):
    """Lay out a story choice box the way ShowEventChoices sizes it under the patch."""
    entries, *_ = load_language(lang)
    entry = entries[offset]
    encoded = encode_direct(entry, expand(lang, text), preview=True)
    lines = [line for line in re.split(rb'\n', encoded[:-1])]
    measure = text_core.named_profile('label', width=0x7FFF, height=0x7FFF)
    cells = 0
    for line in lines:
        output = scene_layout.engine().layout(line + b'\0', measure, player=player)
        right = max([output.state[0], *(item['ink_x'] + item['width'] for item in output.placements)])
        cells = max(cells, (right + 7) >> 3)
    x, y = max(0, 28 - cells), max(0, 9 - 2 * len(lines))
    window = {'id': 3, 'x': x * 8, 'y': y * 8, 'width': (cells + 2) * 8, 'height': (2 * len(lines) + 2) * 8}
    layers = []
    for row, line in enumerate(lines):
        profile = text_core.named_profile('label', width=cells * 8, height=16)
        profile.overflow = text_core.TEXT_OVERFLOW_CLIP
        output = scene_layout.engine().layout(line + b'\0', profile, player=player, compose=True)
        layers.append({'offset': offset, 'title': False, 'selected': selected, 'x': window['x'] + 8,
                       'y': window['y'] + 8 + row * 16,
                       'spans': scene_layout.pixel_spans(output.pixels or [], output.pixel_width, 0, output.pixel_height)})
    return {'window': window, 'layers': layers,
            'prompts': [{'x': window['x'] + 1, 'y': window['y'] + 12, 'kind': 'choice', 'window': 3}]}


def window_group_preview(lang, entry, text, player):
    """Render a menu window with its title bar and body text together."""
    group = window_groups().get(entry['offset'])
    if not group or not group['title'] or not group['bodies']:
        return None
    entries, *_ = load_language(lang)
    window = group['window']
    body = entry['offset'] if entry['offset'] in group['bodies'] else group['bodies'][0]
    layers = []
    for offset, is_title in ((group['title'], True), (body, False)):
        if offset not in entries:
            continue
        value = text if offset == entry['offset'] else translation(entries[offset])
        layers.append(window_text_layer(lang, entries, offset, value, player, window,
                                        title=is_title, selected=offset == entry['offset']))
    chosen = next(layer for layer in layers if layer['selected'])
    output = chosen.pop('output')
    for layer in layers:
        layer.pop('output', None)
    result = window_preview(output, window, text_x=chosen['x'], text_y=chosen['y'],
                            profile_name='menu title' if chosen['title'] else 'menu',
                            source='script', window_id=window['id'])
    result.update(layers=layers, windowSetup=window['sourceRoot'],
                  windowGroup={'title': group['title'], 'body': body, 'bodies': len(group['bodies'])})
    return result


def direct_preview(lang, entry, text, player):
    number = int(entry['offset'], 16)
    if number == CREDITS_OFFSET:
        return credits_preview(entry, text, player)
    if entry['offset'] in event_choices():
        return choice_preview(lang, entry, text, player)
    if not fit_report(lang).get(entry['offset']):
        grouped = screen_preview(lang, entry, text, player) or window_group_preview(lang, entry, text, player)
        if grouped:
            return grouped
    encoded = encode_direct(entry, text, preview=True)
    clipped = fit_report(lang).get(entry['offset'])
    if clipped:
        width = clipped['right'] - clipped['left']
        profile = text_core.named_profile('label', width=width, height=16)
        profile.overflow = text_core.TEXT_OVERFLOW_CLIP
        output = scene_layout.engine().layout(encoded, profile, player=player, compose=True)
        window = {'id': 0, 'x': 8, 'y': 96, 'width': width + 16, 'height': 24}
        return window_preview(output, window, text_x=16, text_y=100, profile_name='measured window',
                              source=f'text-fit report, {width} px at {clipped["example"]}')
    if entry['kind'] == 'event' and not insert_vwf.is_battle_quote(number):
        name = 'portrait_dialogue' if SPEAKER.match(text) else 'full_dialogue'
        return dialogue_preview(entry, text, player, profile_name=name, source='inferred dialogue window')
    context = script_context.menu_contexts().get(number) if entry['kind'] == 'menu' else None
    battle_quote = insert_vwf.is_battle_quote(number)
    if battle_quote:
        context = script_context.battle_quote_context()
    windows = [item for item in context['windows'] if item['width'] and item['height'] and
               item['x'] < 240 and item['y'] < 160] if context else []
    target = next((item for item in windows if item['id'] == context['windowId']), None) if context else None
    if target is None:
        target = {'id': 0, 'x': 0, 'y': 96, 'width': 240, 'height': 64}
        windows = [target]
    label = entry['kind'] == 'menu' or battle_quote
    width = max(8, target['width'] - 16)
    padding = 16 if label else 8
    height = max(8, target['height'] - padding)
    profile = (text_core.named_profile('label', width=width, height=height) if label else
               text_core.profile(width, height, wrap=text_core.TEXT_WRAP_WORD, overflow=text_core.TEXT_OVERFLOW_CLIP))
    if battle_quote:
        profile.wrap = text_core.TEXT_WRAP_WORD
        profile.left = 2
    output = scene_layout.engine().layout(encoded, profile, player=player, compose=True)
    if output.status != 'end':
        raise ValueError(f'Preview failed: {output.status}')
    result = window_preview(output, target, text_x=target['x'] + 8, text_y=target['y'] + padding // 2,
                            profile_name='battle quote' if battle_quote else 'menu' if label else 'string',
                            source=context['windowSource'] if context else 'unknown', window_id=target['id'])
    result['windows'] = windows
    result['windowSetup'] = context['window']['sourceRoot'] if context and context['window'] else None
    return result


def question_preview(lang, offset, player):
    entries, scenes, *_ = load_language(lang)
    if offset in scenes:
        scene = scenes[offset]
        return dialogue_preview(scene, expand(lang, translation(scene)), player,
                                profile_name=scene_layout.profile_name(scene), source='script')
    if offset in entries:
        value = expand(lang, translation(entries[offset]))
        return dialogue_preview(entries[offset], value, player,
                                profile_name='portrait_dialogue' if SPEAKER.match(value) else 'full_dialogue',
                                source='inferred dialogue window')
    return None


def choice_preview(lang, entry, text, player):
    question = event_choices().get(entry['offset'])
    base = question_preview(lang, question, player) if question else None
    choice = choice_window(lang, entry['offset'], expand(lang, text), player, selected=True)
    if base is None:
        base = {'profile': 'story choice', 'width': 0, 'height': 0, 'bounds': (0, 0, 0, 0), 'breaks': [],
                'colors': [], 'overflowed': False, 'missing': [], 'spans': [], 'pages': [[]], 'windows': [],
                'textX': 0, 'textY': 0, 'windowId': 3, 'windowSource': 'event', 'windowSetup': None}
    base['pages'] = [base['pages'][-1]]
    base.update(choice=choice, profile='story choice', question=question)
    return base


def preview(lang, offset, text, player_name):
    entries, scenes, *_ = load_language(lang)
    player = player_bytes(player_name)
    text = expand(lang, text)
    if offset in scenes:
        scene = scenes[offset]
        dialogue.encode_text(text)
        result = dialogue_preview(scene, text, player, profile_name=scene_layout.profile_name(scene), source='script')
        encoded = dialogue.encode_text(text)
        if offset in choice_questions():
            choice = choice_questions()[offset]
            entries_all = load_language(lang)[0]
            if choice in entries_all:
                result['choice'] = choice_window(lang, choice, translation(entries_all[choice]), player, selected=False)
    elif offset in entries:
        entry = entries[offset]
        result = direct_preview(lang, entry, text, player)
        encoded = encode_direct(entry, text)
        if offset in choice_questions() and choice_questions()[offset] in entries:
            choice = choice_questions()[offset]
            result['choice'] = choice_window(lang, choice, translation(entries[choice]), player, selected=False)
    else:
        raise KeyError('Game text was not found.')
    result.update(encodedUnits=encoded_units(encoded), encodedBytes=len(encoded))
    return result


def check_edit(entry, text, scene):
    if scene:
        scene_layout.check_entry(dict(entry, english_draft=text))
        return
    source = dialogue.entry_source(entry)
    template_format = entry['kind'] == 'menu' or entry.get('template_format', False)
    compact = entry.get('compact_format', False)
    if 'build_text' in entry or entry['kind'] == 'menu':
        replacement = dialogue.encode_menu_format(text, source, compact)
    else:
        replacement = dialogue.encode_text(text, source, compact=compact)
    insert_vwf.check_game_text(checker(), entry, source, replacement, template_format)


def save(lang, offset, text, expected):
    with LOCK:
        entries, scenes, *_ = load_language(lang)
        scene = offset in scenes
        entry = scenes.get(offset) or entries.get(offset)
        if entry is None:
            raise KeyError('Game text was not found.')
        if translation(entry) != expected:
            raise ValueError('This text changed on disk. Reload before saving.')
        check_edit(entry, expand(lang, text), scene)
        path = data_path(lang, 'scenes' if scene else 'dialogue')
        document = json.loads(path.read_text())
        key = 'english_offset' if scene else 'offset'
        row = next((item for item in document['entries'] if item[key] == offset), None)
        if row is None:
            row = {key: offset}
            document['entries'].append(row)
            document['entries'].sort(key=lambda item: int(item[key], 16))
        row.pop('replace_lines', None)
        row['english_draft' if scene else 'build_text' if 'build_text' in row else 'text'] = text
        path.write_text(json.dumps(document, indent=1, ensure_ascii=False) + '\n')
    return {'saved': True}


def build(lang):
    *_, document, scenes = load_language(lang)
    choices = json.loads((ROOT / 'kerning-choices.json').read_text())
    rom = insert_vwf.build_rom(clean_rom(), scenes, choices, document,
                               insert_vwf.release_version(data_path(lang, 'version')))
    output = ROOT / 'build' / f'zoids-legacy-{lang}.gba'
    output.parent.mkdir(exist_ok=True)
    output.write_bytes(rom)
    return {'bytes': len(rom), 'path': str(output.relative_to(ROOT))}


class Handler(SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(STATIC), **kwargs)

    def end_headers(self):
        self.send_header('Cache-Control', 'no-store')
        super().end_headers()

    def log_message(self, *_):
        pass

    def reply(self, status, body):
        data = json.dumps(body, ensure_ascii=False).encode()
        self.send_response(status)
        self.send_header('Content-Type', 'application/json; charset=utf-8')
        self.send_header('Content-Length', str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def body(self):
        return json.loads(self.rfile.read(int(self.headers.get('Content-Length', 0))) or b'{}')

    def api(self, method):
        url = urlparse(self.path)
        query = parse_qs(url.query)
        parts = [unquote(part) for part in url.path.split('/')[2:]]
        try:
            lang = language(query)
            if method == 'GET' and parts == ['catalog']:
                return self.reply(200, catalog(lang))
            if method == 'GET' and len(parts) == 2 and parts[0] == 'context':
                data = script_context.catalog()
                matches = data['index'].get(parts[1])
                if not matches:
                    return self.reply(200, {'location': None, 'codeSites': code_sites().get(parts[1], [])})
                return self.reply(200, {'location': matches[0], 'block': data['blocks'][matches[0]['block']],
                                        'locations': matches, 'selectedLocationIndex': 0})
            if method == 'GET' and parts == ['script']:
                block = script_context.catalog()['blocks'].get(query.get('key', [''])[0])
                return self.reply(200, block) if block else self.reply(404, {'error': 'Script was not found.'})
            if method == 'POST' and len(parts) == 2 and parts[0] == 'preview':
                request = self.body()
                return self.reply(200, preview(lang, parts[1], request['text'], request.get('playerName')))
            if method == 'PUT' and len(parts) == 2 and parts[0] == 'entry':
                request = self.body()
                return self.reply(200, save(lang, parts[1], request['text'], request['expected']))
            if method == 'POST' and parts == ['build']:
                return self.reply(200, build(lang))
            return self.reply(404, {'error': 'Unknown request.'})
        except KeyError as error:
            return self.reply(404, {'error': str(error).strip("'")})
        except (ValueError, TypeError, UnicodeError) as error:
            return self.reply(400, {'error': str(error)})

    def translate_path(self, path):
        if path.startswith('/fonts/'):
            return str(ROOT / 'site' / 'fonts' / Path(unquote(urlparse(path).path)).name)
        return super().translate_path(path)

    def do_GET(self):
        if self.path.startswith('/api/'):
            return self.api('GET')
        return super().do_GET()

    def do_POST(self):
        return self.api('POST')

    def do_PUT(self):
        return self.api('PUT')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=5097)
    args = parser.parse_args()
    if not ROM_PATH.exists():
        parser.exit(1, f'Place the clean USA ROM at {ROM_PATH.name} in the repository root.\n')
    server = ThreadingHTTPServer(('127.0.0.1', args.port), Handler)
    print(f'Script editor: http://127.0.0.1:{args.port}/')
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass


if __name__ == '__main__':
    main()
