"""Lay out event dialogue with the shared text core."""

from __future__ import annotations

import re
from dataclasses import replace

import dialogue
import text_core

SPEAKER = re.compile(r"^(\{01 02\}[^\n]+\n)(.*)$", re.S)
PROFILE_WIDTHS = {
    'portrait_dialogue': 160,
    'full_dialogue': 224,
    'battle_choice': 72,
}
LINE_HEIGHT = 16
BOX_LINES = 3

_ENGINE = None


def engine():
    global _ENGINE
    if _ENGINE is None:
        _ENGINE = text_core.load_engine()
    return _ENGINE


def profile_name(entry):
    name = entry.get('layout_profile')
    if name in PROFILE_WIDTHS:
        return name
    columns = entry.get('text_columns')
    legacy = {20: 'portrait_dialogue', 28: 'full_dialogue', 9: 'battle_choice'}
    if columns in legacy:
        return legacy[columns]
    raise ValueError(f'Missing layout profile at {entry["english_offset"]}.')


def layout_profile(entry, height=512):
    name = profile_name(entry)
    profile = text_core.named_profile(name, width=PROFILE_WIDTHS[name],
                                      height=height)
    profile.overflow = text_core.TEXT_OVERFLOW_ERROR
    return profile


def widest_player(text_engine):
    tall = [metric for metric in text_engine.data['metrics']
            if metric['face'] == text_core.TEXT_FACE_TALL and metric['width']]
    metric = max(tall, key=lambda item: (item['advance'], item['width'], item['code']))
    code = metric['code']
    unit = code.to_bytes(2, 'big') if code > 0xff else bytes([code])
    return unit * 8 + b'\0'


def layout_entry(entry, text=None, *, player=None, compose=False, height=512):
    text_engine = engine()
    value = entry['english_draft'] if text is None else text
    body_profile = layout_profile(entry, height)
    match = SPEAKER.match(value)
    if player is None:
        player = widest_player(text_engine)
    if not player or player[-1] != 0:
        raise ValueError('The player name must end with zero.')
    if not match:
        output = text_engine.layout(dialogue.encode_text(value), body_profile,
                                    player=player, compose=compose)
        return replace(output, field='choice' if profile_name(entry) ==
                       'battle_choice' else 'body')
    speaker_text = match[1][:-1]
    body_text = match[2]
    speaker_profile = text_core.named_profile(
        'speaker', width=body_profile.right, height=16)
    speaker_profile.left = body_profile.left
    speaker_profile.overflow = text_core.TEXT_OVERFLOW_ERROR
    speaker = text_engine.layout(dialogue.encode_text(speaker_text),
                                 speaker_profile, player=player,
                                 compose=compose)
    if speaker.status != 'end':
        return replace(speaker, field='speaker')
    body = text_engine.layout(
        dialogue.encode_text(body_text), body_profile, player=player,
        initial=(body_profile.left, 16, -1, speaker.state[3]),
        compose=compose)
    placements = speaker.placements + body.placements
    missing = speaker.missing + body.missing
    if placements:
        bounds = (min(item['ink_x'] for item in placements),
                  min(item['ink_y'] for item in placements),
                  max(item['ink_x'] + item['width'] for item in placements),
                  max(item['ink_y'] + item['height'] for item in placements))
    else:
        bounds = body.bounds
    pixels = body.pixels
    if compose and pixels is not None and speaker.pixels is not None:
        pixels = list(pixels)
        for index, speaker_value in enumerate(speaker.pixels):
            pixels[index] = pixels[index] or speaker_value
    return text_core.LayoutOutput(
        body.status, len(dialogue.encode_text(value)), placements, body.breaks,
        missing, bounds, speaker.overflowed or body.overflowed, body.state,
        pixels, body.pixel_width, body.pixel_height,
        'speaker' if speaker.missing and body.status == 'end' and
        not body.missing else 'body')


def layout_problem(entry, output):
    if output.status == 'end' and not output.missing:
        return None
    name = 'speaker' if output.field == 'speaker' else profile_name(entry)
    if name == 'speaker':
        body = layout_profile(entry)
        profile = text_core.named_profile('speaker', width=body.right, height=16)
        profile.left = body.left
    else:
        profile = layout_profile(entry)
    bounds = f'[{profile.left},{profile.top},{profile.right},{profile.bottom}]'
    offset = entry['english_offset']
    if output.status != 'end':
        return (f'{output.status} in {output.field} at {offset}; '
                f'profile {name} bounds {bounds}.')
    codes = ', '.join(f'{code:04X}' for code in output.missing)
    return (f'Missing glyphs {codes} in {output.field} at {offset}; '
            f'profile {name} bounds {bounds}.')


def check_entry(entry):
    name = profile_name(entry)
    if entry.get('layout_profile', name) != name:
        raise ValueError(f'Invalid layout profile at {entry["english_offset"]}.')
    output = layout_entry(entry)
    problem = layout_problem(entry, output)
    if problem:
        raise ValueError(problem)
    if name == 'battle_choice' and len(entry['english_draft'].splitlines()) != 2:
        raise ValueError('The battle choice must contain two lines.')


def pixel_spans(pixels, width, top=0, bottom=None):
    spans = []
    bottom = len(pixels) // width if bottom is None and width else bottom or 0
    for y in range(top, bottom):
        x = 0
        while x < width:
            value = pixels[y * width + x]
            if not value:
                x += 1
                continue
            end = x + 1
            while end < width and pixels[y * width + end] == value:
                end += 1
            spans.append([x, y - top, end - x, value])
            x = end
    return spans


def box_pages(output):
    # The window scrolls one line at a time and waits for A after every three new lines.
    lines = max(1, -(-max(output.bounds[3], 1) // LINE_HEIGHT))
    stops = sorted({min(last, lines - 1) for last in range(BOX_LINES - 1, lines - 1 + BOX_LINES, BOX_LINES)})
    return [pixel_spans(output.pixels or [], output.pixel_width,
                        max(0, last - BOX_LINES + 1) * LINE_HEIGHT, (last + 1) * LINE_HEIGHT)
            for last in stops]


def preview(entry, text, *, player=None):
    output = layout_entry(entry, text, player=player, compose=True)
    problem = layout_problem(entry, output)
    if problem:
        raise ValueError(problem)
    spans = pixel_spans(output.pixels or [], output.pixel_width, 0, output.pixel_height)
    pages = [spans] if profile_name(entry) == 'battle_choice' else box_pages(output)
    return {
        'status': output.status,
        'profile': profile_name(entry),
        'width': output.pixel_width,
        'height': min(output.pixel_height, max(16, output.bounds[3])),
        'bounds': output.bounds,
        'colors': sorted({item['color'] for item in output.placements}),
        'overflowed': output.overflowed,
        'missing': [f'{code:04X}' for code in output.missing],
        'breaks': output.breaks,
        'spans': spans,
        'pages': pages,
    }
