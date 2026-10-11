"""Extract the ROM font and call the shared text core from the host."""

from __future__ import annotations

import ctypes
from dataclasses import dataclass
import hashlib
import json
import os
from pathlib import Path
import struct
import subprocess
import tempfile
import unicodedata

import dialogue

ROOT = Path(__file__).resolve().parent.parent
SOURCE = Path(__file__).with_suffix('.c')
HEADER = Path(__file__).with_suffix('.h')
TALL_TABLE = dialogue.PROFILE['glyphs']
COMPACT_TABLE = 0x7A0B48

TEXT_FACE_AUTO = 0
TEXT_FACE_TALL = 1
TEXT_FACE_COMPACT = 2
TEXT_OK = 0
TEXT_END = 1
TEXT_ALIGN_LEFT = 0
TEXT_ALIGN_CENTER = 1
TEXT_ALIGN_RIGHT = 2
TEXT_BOUND_ADVANCE = 0
TEXT_BOUND_INK = 1
TEXT_WRAP_NONE = 0
TEXT_WRAP_WORD = 1
TEXT_OVERFLOW_ERROR = 0
TEXT_OVERFLOW_CLIP = 1
TEXT_PROFILE_PORTRAIT_DIALOGUE = 0
TEXT_PROFILE_FULL_DIALOGUE = 1
TEXT_PROFILE_LABEL = 2
TEXT_PROFILE_NUMBER = 3
TEXT_PROFILE_COMPACT_ROW = 4
TEXT_PROFILE_STARTUP = 5
TEXT_PROFILE_CREDITS = 6
TEXT_PROFILE_BATTLE_CHOICE = 7
TEXT_PROFILE_SPEAKER = 8
TEXT_EVENT_GLYPH = 0
TEXT_EVENT_LINE = 3
TEXT_EVENT_PAGE = 4

STATUS_NAMES = {0: 'ok', 1: 'end', 2: 'malformed input', 3: 'missing field',
                4: 'capacity failure', 5: 'layout overflow', 6: 'tile exhaustion'}
PROFILE_KINDS = {
    'portrait_dialogue': (TEXT_PROFILE_PORTRAIT_DIALOGUE, 160, 64),
    'full_dialogue': (TEXT_PROFILE_FULL_DIALOGUE, 224, 64),
    'label': (TEXT_PROFILE_LABEL, 224, 16),
    'number': (TEXT_PROFILE_NUMBER, 224, 16),
    'compact_row': (TEXT_PROFILE_COMPACT_ROW, 224, 8),
    'startup': (TEXT_PROFILE_STARTUP, 8, 8),
    'credits': (TEXT_PROFILE_CREDITS, 240, 16),
    'battle_choice': (TEXT_PROFILE_BATTLE_CHOICE, 72, 32),
    'speaker': (TEXT_PROFILE_SPEAKER, 160, 16),
}


class CFont(ctypes.Structure):
    _fields_ = [('metrics', ctypes.c_char_p), ('metric_count', ctypes.c_uint16),
                ('ranges', ctypes.c_char_p), ('range_count', ctypes.c_uint16),
                ('pairs', ctypes.c_char_p), ('pair_count', ctypes.c_uint16),
                ('pair_offsets', ctypes.c_char_p), ('glyphs', ctypes.c_char_p),
                ('glyph_stride', ctypes.c_uint8), ('tall_fallback', ctypes.c_uint16),
                ('compact_fallback', ctypes.c_uint16)]


class CCheck(ctypes.Structure):
    _fields_ = [('text', ctypes.c_char_p), ('player', ctypes.c_char_p),
                ('text_length', ctypes.c_uint16), ('player_length', ctypes.c_uint16),
                ('left', ctypes.c_int16), ('right', ctypes.c_int16),
                ('bottom', ctypes.c_int16), ('x', ctypes.c_int16), ('y', ctypes.c_int16),
                ('kind', ctypes.c_uint8), ('wrap', ctypes.c_uint8),
                ('overflow', ctypes.c_uint8), ('resume', ctypes.c_uint8),
                ('color', ctypes.c_uint8), ('lines', ctypes.c_uint8),
                ('missing_count', ctypes.c_uint8), ('missing', ctypes.c_uint16 * 128)]


class CSpan(ctypes.Structure):
    _fields_ = [('data', ctypes.POINTER(ctypes.c_uint8)), ('length', ctypes.c_size_t),
                ('field_id', ctypes.c_uint8)]


class CDecoder(ctypes.Structure):
    _fields_ = [('data', ctypes.POINTER(ctypes.c_uint8) * 2), ('lengths', ctypes.c_uint16 * 2),
                ('positions', ctypes.c_uint16 * 2), ('depth', ctypes.c_uint8),
                ('ended', ctypes.c_uint8), ('invalid', ctypes.c_uint8), ('limit_end', ctypes.c_uint8)]


class CProfile(ctypes.Structure):
    _fields_ = [('left', ctypes.c_int16), ('top', ctypes.c_int16), ('right', ctypes.c_int16),
                ('bottom', ctypes.c_int16), ('baseline', ctypes.c_int8), ('line_height', ctypes.c_uint8),
                ('line_gap', ctypes.c_uint8), ('face', ctypes.c_uint8), ('position_scale', ctypes.c_uint8),
                ('alignment', ctypes.c_uint8), ('alignment_bound', ctypes.c_uint8), ('wrap', ctypes.c_uint8),
                ('overflow', ctypes.c_uint8), ('tabular_advance', ctypes.c_uint8), ('paginate', ctypes.c_uint8),
                ('compact_tabular_advance', ctypes.c_uint8)]


class CState(ctypes.Structure):
    _fields_ = [('x', ctypes.c_int16), ('y', ctypes.c_int16), ('previous', ctypes.c_int16),
                ('color', ctypes.c_uint8), ('initialized', ctypes.c_uint8)]


class CPlacement(ctypes.Structure):
    _fields_ = [('metric', ctypes.c_uint16), ('code', ctypes.c_uint16), ('pen_x', ctypes.c_int16),
                ('ink_x', ctypes.c_int16), ('ink_y', ctypes.c_int16), ('width', ctypes.c_uint8),
                ('height', ctypes.c_uint8), ('color', ctypes.c_uint8), ('missing', ctypes.c_uint8),
                ('consumed', ctypes.c_uint16), ('clip_left', ctypes.c_uint8), ('clip_right', ctypes.c_uint8)]


class CEventData(ctypes.Structure):
    _fields_ = [('x', ctypes.c_int16), ('y', ctypes.c_int16), ('value', ctypes.c_uint8),
                ('explicit_break', ctypes.c_uint8), ('left', ctypes.c_int16), ('top', ctypes.c_int16),
                ('right', ctypes.c_int16), ('bottom', ctypes.c_int16), ('consumed', ctypes.c_uint16),
                ('next_consumed', ctypes.c_uint16)]


class CEventPayload(ctypes.Union):
    _anonymous_ = ('data',)
    _fields_ = [('glyph', CPlacement), ('data', CEventData)]


class CEvent(ctypes.Structure):
    _anonymous_ = ('payload',)
    _fields_ = [('kind', ctypes.c_uint8), ('payload', CEventPayload)]


class CResult(ctypes.Structure):
    _fields_ = [('consumed', ctypes.c_uint16), ('glyph_count', ctypes.c_uint16),
                ('missing_count', ctypes.c_uint16), ('ink_left', ctypes.c_int16),
                ('ink_top', ctypes.c_int16), ('ink_right', ctypes.c_int16),
                ('ink_bottom', ctypes.c_int16), ('status', ctypes.c_uint8), ('overflowed', ctypes.c_uint8)]


GET_PIXEL = ctypes.CFUNCTYPE(ctypes.c_uint8, ctypes.c_void_p, ctypes.c_int, ctypes.c_int)
SET_PIXEL = ctypes.CFUNCTYPE(None, ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_uint8)
EMIT = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_void_p, ctypes.POINTER(CEvent))


class CSurface(ctypes.Structure):
    _fields_ = [('context', ctypes.c_void_p), ('width', ctypes.c_int16), ('height', ctypes.c_int16),
                ('get', GET_PIXEL), ('set', SET_PIXEL)]


def _library_path() -> Path:
    digest = hashlib.sha256(SOURCE.read_bytes() + HEADER.read_bytes()).hexdigest()[:16]
    suffix = '.dylib' if os.uname().sysname == 'Darwin' else '.so'
    directory = Path(tempfile.gettempdir()) / f'zoids-text-core-{os.getuid()}'
    directory.mkdir(mode=0o700, exist_ok=True)
    output = directory / f'{digest}{suffix}'
    if output.exists():
        return output
    temporary = output.with_suffix(output.suffix + '.tmp')
    command = ['cc', '-std=c99', '-O2', '-fPIC', '-Wall', '-Wextra', '-Werror']
    command += ['-dynamiclib' if suffix == '.dylib' else '-shared',
                str(SOURCE), '-o', str(temporary)]
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode:
        raise ValueError(f'Host build of text_core.c failed:\n{result.stderr}')
    temporary.replace(output)
    return output


def _load_library():
    library = ctypes.CDLL(str(_library_path()))
    library.text_check.argtypes = [ctypes.POINTER(CFont), ctypes.POINTER(CCheck)]
    library.text_check.restype = ctypes.c_int
    library.text_decoder_init.argtypes = [ctypes.POINTER(CDecoder), CSpan, ctypes.POINTER(CSpan), ctypes.c_uint8]
    library.text_layout.argtypes = [ctypes.POINTER(CFont), ctypes.POINTER(CProfile), ctypes.POINTER(CDecoder),
                                    ctypes.POINTER(CState), EMIT, ctypes.c_void_p, ctypes.POINTER(CResult)]
    library.text_layout.restype = ctypes.c_int
    library.text_profile_init.argtypes = [ctypes.POINTER(CProfile), ctypes.c_int, ctypes.c_int16, ctypes.c_int16]
    library.text_profile_init.restype = ctypes.c_int
    library.text_compose_glyph.argtypes = [ctypes.POINTER(CFont), ctypes.POINTER(CPlacement),
                                           ctypes.POINTER(CSurface), ctypes.c_uint8]
    library.text_compose_glyph.restype = ctypes.c_int
    return library


LIBRARY = None


def library():
    global LIBRARY
    if LIBRARY is None:
        LIBRARY = _load_library()
    return LIBRARY


def _unpack_rows(raw: bytes, height: int) -> list[list[int]]:
    rows = [[(raw[y * 2 + x // 4] >> ((x % 4) * 2)) & 3
             for x in range(8)] for y in range(height)]
    return rows + [[0] * 8 for _ in range(16 - height)]


def _pack_rows(rows: list[list[int]]) -> bytes:
    return bytes(sum((rows[y][x + offset] if x + offset < len(rows[y]) else 0)
                     << (2 * offset) for offset in range(4))
                 for y in range(16) for x in range(0, 16, 4))


def _ranges(metrics: list[dict]) -> list[tuple[int, int, int, int]]:
    result = []
    for index, metric in enumerate(metrics):
        if (result and metric['face'] == result[-1][3] and
                metric['code'] == result[-1][0] + result[-1][1] and
                index == result[-1][2] + result[-1][1]):
            first, count, base, face = result[-1]
            result[-1] = first, count + 1, base, face
        else:
            result.append((metric['code'], 1, index, metric['face']))
    return result


AT_CODE = 0x8197


def extract_font(rom: bytes, choices: dict) -> dict:
    metrics = []
    advances = choices.get('advances', {})
    letter_spacing = choices.get('letter_spacing', 0)
    proportional = choices.get('spacing') == 'proportional'
    for face, table, table_format, height in (
            (TEXT_FACE_TALL, TALL_TABLE, '<HBBI', 16),
            (TEXT_FACE_COMPACT, COMPACT_TABLE, '<BBHI', 8)):
        baseline = 14 if face == TEXT_FACE_TALL else 7
        glyph_size = 32 if face == TEXT_FACE_TALL else 16
        for table_index in range(22):
            first, count, _, pointer = struct.unpack_from(table_format, rom, table + table_index * 8)
            start = pointer - dialogue.BASE
            for offset, code in enumerate(range(first, first + count)):
                raw = rom[start + offset * glyph_size:start + (offset + 1) * glyph_size]
                rows = _unpack_rows(raw, height)
                if face == TEXT_FACE_TALL and code == AT_CODE:
                    at_rows = rows
                columns = [x for x in range(8) if any(rows[y][x] for y in range(height))]
                ink_rows = [y for y in range(height) if any(rows[y])]
                if columns:
                    left, right = min(columns), max(columns) + 1
                    top, bottom = min(ink_rows), max(ink_rows) + 1
                else:
                    left = right = top = bottom = 0
                advance = 8
                if face == TEXT_FACE_TALL:
                    default = min(right - left + 1, 8) if columns else 4
                    if 0x824F <= code <= 0x8258:
                        default -= 1
                    advance = advances.get(f'{code:04X}', default) + letter_spacing
                elif ord('0') <= code <= ord('9'):
                    advance = 7
                if not 1 <= advance <= 16:
                    raise ValueError(f'Invalid advance for glyph {code:04X}.')
                width = right - left
                ink_height = bottom - top
                bitmap = [[0] * 16 for _ in range(16)]
                for y in range(ink_height):
                    bitmap[y][:width] = rows[top + y][left:right]
                metrics.append(dict(code=code,
                                    bearing_x=0 if face == TEXT_FACE_TALL and proportional else left,
                                    bearing_y=top - baseline if ink_height else 0,
                                    width=width, height=ink_height, advance=advance,
                                    face=face, line_height=height, baseline=baseline,
                                    bitmap=bitmap))
    source_at = next(metric for metric in metrics
                     if metric['face'] == TEXT_FACE_TALL and metric['code'] == AT_CODE)
    rows = [row[:] for row in at_rows]
    rows[5:12] = [[int(pixel) for pixel in row] for row in (
        '21033021', '21210221', '21210021', '21210021',
        '21210221', '21033021', '21000021')]
    bitmap = [row[:] for row in source_at['bitmap']]
    top = source_at['baseline'] + source_at['bearing_y']
    for y in range(source_at['height']):
        bitmap[y][:8] = rows[top + y]
    advance = advances.get(f'{dialogue.COPYRIGHT_CODE:04X}', 8) + letter_spacing
    if not 1 <= advance <= 16:
        raise ValueError(f'Invalid advance for glyph {dialogue.COPYRIGHT_CODE:04X}.')
    metrics.append(dict(source_at, code=dialogue.COPYRIGHT_CODE, advance=advance, bitmap=bitmap))
    metrics.extend(spanish_metric(metrics, char, code)
                   for char, code in dialogue.SPANISH_CODES.items())
    metrics.extend(spanish_metric(metrics, char, code, compact=True)
                   for char, code in dialogue.SPANISH_COMPACT_CODES.items())
    indices = {(metric['face'], metric['code']): index
               for index, metric in enumerate(metrics)}
    pairs = []
    for key, adjust in choices.get('pairs', {}).items():
        try:
            left, right = (indices[(TEXT_FACE_TALL, int(part, 16))] for part in key.split(':'))
        except (KeyError, ValueError) as error:
            raise ValueError(f'Unknown glyph in pair {key}.') from error
        if not -128 <= adjust <= 127:
            raise ValueError(f'Invalid pair adjustment for {key}.')
        pairs.append((left, right, adjust))
    pairs.sort()
    return dict(metrics=metrics, ranges=_ranges(metrics), pairs=pairs,
                glyphs=b''.join(_pack_rows(metric['bitmap']) for metric in metrics),
                tall_fallback=indices[(TEXT_FACE_TALL, 0x8148)],
                compact_fallback=indices[(TEXT_FACE_COMPACT, ord('?'))])


def spanish_metric(metrics: list[dict], char: str, code: int, compact: bool = False) -> dict:
    base = {'¿': '?', '¡': '!'}.get(char, unicodedata.normalize('NFD', char)[0])
    face = TEXT_FACE_COMPACT if compact else TEXT_FACE_TALL
    base_code = ord(base) if compact else int.from_bytes(dialogue.encode_text(base)[:-1], 'big')
    original = next(metric for metric in metrics if metric['face'] == face and
                    metric['code'] == base_code)
    bitmap = [[0] * 16 for _ in range(16)]
    if char in '¿¡':
        for y in range(original['height']):
            for x in range(original['width']):
                bitmap[y][x] = original['bitmap'][original['height'] - y - 1][original['width'] - x - 1]
        return {**original, 'code': code, 'bitmap': bitmap}
    accent = unicodedata.normalize('NFD', char)[1]
    dotted_i = base == 'i'
    if compact:
        shift = original['baseline'] + original['bearing_y']
        marks = ({'\u0301': ('   33', '  33 '), '\u0303': ('  33  ', '33  33'),
                  '\u0308': ('33 33',)} if shift > 1 else
                 {'\u0301': ('  33',), '\u0303': ('33 33',),
                  '\u0308': ('33 33',)})[accent]
    else:
        # Use the source font's dark center and medium edges for accent strokes.
        marks = {'\u0301': ('   32', '  32 '), '\u0303': ('  233 ', '23 332'),
                 '\u0308': ('32 32',)}[accent]
        shift = 0 if dotted_i else 2 if accent == '\u0308' else 3
    width = max(original['width'], len(marks[0]))
    start = (width - original['width']) // 2
    for y in range(2 if dotted_i else 0, original['height']):
        bitmap[y + shift][start:start + original['width']] = original['bitmap'][y][:original['width']]
    start = (width - len(marks[0])) // 2
    for y, row in enumerate(marks):
        for x, pixel in enumerate(row):
            bitmap[y][start + x] = int(pixel) if pixel != ' ' else 0
    return {**original, 'code': code, 'bitmap': bitmap, 'width': width,
            'height': original['height'] + shift, 'bearing_y': original['bearing_y'] - shift,
            'advance': original['advance'] if compact else max(original['advance'], width + 1)}


def pack_font(font: dict) -> dict:
    metrics = b''.join(struct.pack(
        '<HbbBBbBBB', metric['code'], metric['bearing_x'], metric['bearing_y'],
        metric['width'], metric['height'], metric['advance'], metric['face'],
        metric['line_height'], metric['baseline'])
        for metric in font['metrics'])
    pair_offsets = []
    position = 0
    for left in range(len(font['metrics']) + 1):
        while position < len(font['pairs']) and font['pairs'][position][0] < left:
            position += 1
        pair_offsets.append(position)
    return dict(
        metrics=metrics,
        pairs=b''.join(struct.pack('<HHbB', left, right, adjust, 0)
                       for left, right, adjust in font['pairs']),
        pair_offsets=struct.pack(f'<{len(pair_offsets)}H', *pair_offsets),
        ranges=b''.join(struct.pack('<HHHBB', first, count, base, face, 0)
                        for first, count, base, face in font['ranges']))


class TextChecker:
    def __init__(self, font: dict):
        self.packed = pack_font(font)
        self.glyphs = font['glyphs']
        self.font = CFont(self.packed['metrics'], len(font['metrics']),
                          self.packed['ranges'], len(font['ranges']),
                          self.packed['pairs'], len(font['pairs']),
                          self.packed['pair_offsets'], self.glyphs, 4,
                          font['tall_fallback'], font['compact_fallback'])
        tall = max((metric for metric in font['metrics']
                    if metric['face'] == TEXT_FACE_TALL and metric['width']),
                   key=lambda metric: (metric['advance'], metric['width'], metric['code']))
        self.widest_player = tall['code'].to_bytes(2, 'big') * 8 + b'\0'

    def check(self, text: bytes, kind: int, right: int, bottom: int, *,
              wrap: int, overflow: int, left: int = -1, player: bytes | None = None,
              start: tuple[int, int, int] | None = None) -> CCheck:
        player = self.widest_player if player is None else player
        check = CCheck(text, player, len(text), len(player), left, right, bottom,
                       *(start[:2] if start else (0, 0)), kind, wrap, overflow,
                       int(start is not None), start[2] if start else 0)
        check.status = library().text_check(ctypes.byref(self.font), ctypes.byref(check))
        check.missing_codes = list(check.missing[:check.missing_count])
        return check


@dataclass
class LayoutOutput:
    status: str
    consumed: int
    placements: list[dict]
    breaks: list[dict]
    missing: list[int]
    bounds: tuple[int, int, int, int]
    overflowed: bool
    state: tuple[int, int, int, int]
    pixels: list[int] | None = None
    pixel_width: int = 0
    pixel_height: int = 0
    field: str = 'text'


class TextEngine:
    def __init__(self, rom: bytes, choices: dict):
        self.data = extract_font(rom, choices)
        self.checker = TextChecker(self.data)
        self.font = self.checker.font

    def layout(self, encoded: bytes, profile: CProfile, player: bytes | None = b'\0',
               initial: tuple[int, int, int, int] | None = None, compose: bool = False) -> LayoutOutput:
        if not encoded or encoded[-1] != 0 or (player is not None and (not player or player[-1] != 0)):
            raise ValueError('Encoded text and fields must end with zero.')
        if profile.tabular_advance == 0xff:
            faces = (profile.face,) if profile.face != TEXT_FACE_AUTO else (TEXT_FACE_TALL, TEXT_FACE_COMPACT)
            profile.tabular_advance = max((
                metric['advance'] for metric in self.data['metrics'] if metric['face'] in faces and (
                    (metric['face'] == TEXT_FACE_TALL and 0x824F <= metric['code'] <= 0x8258) or
                    (metric['face'] == TEXT_FACE_COMPACT and ord('0') <= metric['code'] <= ord('9')))),
                default=1)
        input_buffer = (ctypes.c_uint8 * len(encoded)).from_buffer_copy(encoded)
        fields = (CSpan * 2)()
        field_count = 0
        if player is not None:
            player_buffer = (ctypes.c_uint8 * len(player)).from_buffer_copy(player)
            fields[1] = CSpan(player_buffer, len(player), 1)
            field_count = len(fields)
        decoder = CDecoder()
        library().text_decoder_init(ctypes.byref(decoder), CSpan(input_buffer, len(encoded), 0xff),
                                    fields, field_count)
        state = CState()
        if initial is not None:
            state.x, state.y, state.previous, state.color = initial
            state.initialized = 1
        placements, breaks, missing = [], [], []

        @EMIT
        def receive(_context, event_pointer):
            event = event_pointer.contents
            if event.kind == TEXT_EVENT_GLYPH:
                glyph = event.glyph
                placements.append(dict(
                    metric=glyph.metric, code=glyph.code, pen_x=glyph.pen_x, ink_x=glyph.ink_x,
                    ink_y=glyph.ink_y, width=glyph.width, height=glyph.height, color=glyph.color,
                    missing=bool(glyph.missing), consumed=glyph.consumed,
                    clip_left=glyph.clip_left, clip_right=glyph.clip_right))
                if glyph.missing:
                    missing.append(glyph.code)
            elif event.kind in (TEXT_EVENT_LINE, TEXT_EVENT_PAGE):
                breaks.append(dict(explicit=bool(event.explicit_break), page=event.kind == TEXT_EVENT_PAGE,
                                   consumed=event.consumed, next_consumed=event.next_consumed, y=event.y))
            return 0

        result = CResult()
        status = library().text_layout(ctypes.byref(self.font), ctypes.byref(profile), ctypes.byref(decoder),
                                       ctypes.byref(state), receive, None, ctypes.byref(result))
        bounds = (result.ink_left, result.ink_top, result.ink_right, result.ink_bottom)
        final = (state.x, state.y, state.previous, state.color)
        if status != TEXT_END:
            return LayoutOutput(STATUS_NAMES.get(status, f'status {status}'), result.consumed, placements,
                                breaks, missing, bounds, bool(result.overflowed), final)
        width, height = max(profile.right, 0), max(profile.bottom, 0)
        pixels = None
        if compose:
            pixels = [0] * (width * height)

            @GET_PIXEL
            def get_pixel(_context, x, y):
                return pixels[y * width + x]

            @SET_PIXEL
            def set_pixel(_context, x, y, value):
                pixels[y * width + x] = value

            surface = CSurface(None, width, height, get_pixel, set_pixel)
            for item in placements:
                placement = CPlacement(item['metric'], item['code'], item['pen_x'], item['ink_x'],
                                       item['ink_y'], item['width'], item['height'], item['color'],
                                       item['missing'], item['consumed'], item['clip_left'], item['clip_right'])
                compose_status = library().text_compose_glyph(ctypes.byref(self.font), ctypes.byref(placement),
                                                              ctypes.byref(surface), item['color'] % 3 + 1)
                if compose_status:
                    raise ValueError(STATUS_NAMES.get(compose_status, str(compose_status)))
        return LayoutOutput('end', result.consumed, placements, breaks, missing, bounds,
                            bool(result.overflowed), final, pixels, width, height)


def load_engine(rom_path: Path = ROOT / 'Zoids Legacy (USA).gba',
                choices_path: Path = ROOT / 'kerning-choices.json') -> TextEngine:
    return TextEngine(dialogue.read_rom(rom_path), json.loads(choices_path.read_text()))


def profile(width: int, height: int = 160, *, face: int = TEXT_FACE_AUTO,
            alignment: int = TEXT_ALIGN_LEFT, alignment_bound: int = TEXT_BOUND_ADVANCE,
            wrap: int = TEXT_WRAP_WORD, overflow: int = TEXT_OVERFLOW_ERROR,
            tabular_digits: bool = False, paginate: bool = False) -> CProfile:
    return CProfile(0, 0, width, height, 14, 16, 0, face, 8, alignment, alignment_bound, wrap,
                    overflow, 0xff if tabular_digits else 0, int(paginate))


def named_profile(name: str, *, width: int | None = None, height: int | None = None) -> CProfile:
    try:
        kind, default_width, default_height = PROFILE_KINDS[name]
    except KeyError as error:
        raise ValueError(f'Unknown text profile {name}.') from error
    result = CProfile()
    status = library().text_profile_init(ctypes.byref(result), kind,
                                         default_width if width is None else width,
                                         default_height if height is None else height)
    if status != TEXT_OK:
        raise ValueError(STATUS_NAMES.get(status, str(status)))
    return result
