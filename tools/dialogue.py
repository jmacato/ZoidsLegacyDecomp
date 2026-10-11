#!/usr/bin/env python3
"""Read Zoids Legacy text and load the translation edits."""

from __future__ import annotations

from functools import lru_cache
import hashlib
from difflib import SequenceMatcher
import json
from pathlib import Path
import re
import struct

ROM_SHA1 = "460fa2158606097f6e6f63ce966d2d6ecdd58d70"
COPYRIGHT_CODE = 0x8760
PROFILE = {"roots": 0x7A0BF8, "lengths": 0x7A17FC, "glyphs": 0x7A0A98, "menu": 0x98BB4,
           "code_start": 0x923E0, "code_end": 0xED000, "attract": 0x091D5D}
ROM_SIZE = 0x800000
BASE = 0x08000000
EVENT_JUMP = 0x0A
TOKEN = re.compile(r"\{([0-9A-Fa-f]{2}(?: [0-9A-Fa-f]{2})*)\}")
SPANISH_CODES = {char: 0x9F40 + index for index, char in
                 enumerate('áéíóúüñÁÉÍÓÚÜÑ¿¡')}
SPANISH_COMPACT_CODES = {char: 0xE0 + index for index, char in
                         enumerate('áéíóúüñÁÉÍÓÚÜÑ¿¡')}
SPANISH_CHARACTERS = {code: char for codes in (SPANISH_CODES, SPANISH_COMPACT_CODES)
                      for char, code in codes.items()}
MENU_LENGTHS = {1: 7, 2: 2, 3: 2, 4: 1, 6: 2, 7: 3, 8: 2,
                10: 2, 11: 3, 12: 1, 13: 4}
MENU_WINDOW_EDITS = {
    0x0022D5: (bytes.fromhex('01070f000f1000'), bytes.fromhex('01070f000f1040')),
    0x002C13: (bytes.fromhex('01030000101008'), bytes.fromhex('010300000f1008')),
    0x002C1A: (bytes.fromhex('010410000e0a00'), bytes.fromhex('01040f000f0a00')),
    0x002C21: (bytes.fromhex('0105100c0e0400'), bytes.fromhex('01050f0c0f0400')),
    0x002DFB: (bytes.fromhex('01000f000f0c08'), bytes.fromhex('01000d00110c08')),
    0x002E09: (bytes.fromhex('01020f0c0f0300'), bytes.fromhex('01020d0c110300')),
    0x00405D: (bytes.fromhex('010801090c0300'), bytes.fromhex('010801090d0300')),
    0x00407C: (bytes.fromhex('010201010c0800'), bytes.fromhex('010201010d0800')),
    0x004132: (bytes.fromhex('010400000c0400'), bytes.fromhex('010400000d0400')),
    0x004148: (bytes.fromhex('010500040c0400'), bytes.fromhex('010500040d0400')),
    0x00415E: (bytes.fromhex('010600080c0400'), bytes.fromhex('010600080d0400')),
    0x006861: (bytes.fromhex('01040008080400'), bytes.fromhex('010400080a0400')),
    0x006868: (bytes.fromhex('01050808160400'), bytes.fromhex('01050a08140400')),
    0x019A46: (bytes.fromhex('010300020f0c08'), bytes.fromhex('01030002100c08')),
    0x019A8A: (bytes.fromhex('010400020f0c08'), bytes.fromhex('01040002100c08')),
    0x0234E0: (bytes.fromhex('01060303180a00'), bytes.fromhex('01060303190a00')),
}
TEXT_BANKS = ((0x928, 0x920E5), (0xED930, 0xED93C), (0x103A38, 0x103E1C),
              (0x1061A0, 0x1065C8), (0x106E54, 0x106F38), (0x107058, 0x1076AC),
              (0x10811C, 0x108228), (0x108B5C, 0x108C78), (0x108FBC, 0x1094C8),
              (0x7C397C, 0x7C4434))
TEXT_RUN = re.compile(rb'(?:[\x80-\x9f][\x40-\x7e\x80-\xfc]|[\x20-\x7f\xa0-\xff\x0a])+\x00')
KEYBOARDS = ((0x7A11D8, 3, 262),)
FIXED_STRINGS = ((0x7A0F28, 20, 31, 'copyright'), (0x7A5962, 13, 35, 'Zoid type'),
                 (0x7A5B29, 13, 35, 'Zoid type'), (0x7C397C, 196, 14, 'map name'))
SYSTEM_STRINGS = (0xED208, 0x7A099C, 0x7A0A4C)


def read_rom(path: Path) -> bytes:
    data = path.read_bytes()
    if len(data) != ROM_SIZE or hashlib.sha1(data).hexdigest() != ROM_SHA1:
        raise ValueError("Input must be the clean USA ROM.")
    return data


def menu_window_command(rom: bytes, offset: int) -> bytes:
    command = rom[offset:offset + 7]
    if offset in MENU_WINDOW_EDITS:
        original, replacement = MENU_WINDOW_EDITS[offset]
        if command != original:
            raise ValueError(f'Window definition differs at 0x{offset:X}.')
        return replacement
    return command


UNIT_WIDTHS = bytes({1: 2, 2: 3, 4: 2, 6: 2, 7: 3, 8: 3}.get(value, 2 if 0x80 <= value <= 0x9F else 1)
                    for value in range(256))


def text_units(data: bytes, start: int):
    pos = start
    size = len(data)
    while pos < size:
        value = data[pos]
        if value == 0:
            return
        width = UNIT_WIDTHS[value]
        if pos + width > size:
            raise ValueError(f"Truncated text at 0x{pos:X}.")
        yield data[pos:pos + width]
        pos += width
    raise ValueError(f"Missing text terminator at 0x{start:X}.")


def readable(unit: bytes) -> str:
    return _readable(bytes(unit))


@lru_cache(maxsize=None)
def _readable(unit: bytes) -> str:
    if unit in (b"@", COPYRIGHT_CODE.to_bytes(2, "big")):
        return "©"
    code = int.from_bytes(unit, 'big')
    if code in SPANISH_CHARACTERS:
        return SPANISH_CHARACTERS[code]
    if unit == b"\x0a":
        return "\n"
    if unit[0] < 0x20:
        return "{" + unit.hex(" ").upper() + "}"
    if len(unit) == 1 and 0x20 <= unit[0] <= 0x7E and unit not in (b"{", b"}"):
        return chr(unit[0])
    try:
        char = unit.decode("shift_jis")
        if len(unit) == 1 and 0xA1 <= unit[0] <= 0xDF:
            return char
        # Only narrow full-width ASCII. Other characters retain their exact mapping.
        if len(unit) == 2 and len(char) == 1:
            if char == "\u3000":
                return " "
            if 0xFF01 <= ord(char) <= 0xFF5E and char not in "｛｝":
                return chr(ord(char) - 0xFEE0)
            if char.encode("shift_jis") == unit and char not in "{}":
                return char
    except UnicodeError:
        pass
    return "{" + unit.hex(" ").upper() + "}"


def decode_text(data: bytes, start: int) -> tuple[str, int]:
    if not 0 <= start < len(data):
        raise ValueError("Text offset is outside the ROM.")
    units = list(text_units(data, start))
    return "".join(map(readable, units)), start + sum(map(len, units)) + 1


def entry_source(entry: dict) -> bytes:
    raw = bytes.fromhex(entry['original'])
    return raw if entry.get('terminated', True) else raw + b'\0'


def character_modes(text: str, original: bytes) -> dict[int, bool]:
    source_chars = []
    source_modes = []
    for unit in text_units(original, 0):
        char = readable(unit)
        if len(char) == 1:
            source_chars.append(char)
            source_modes.append(len(unit) == 1)

    target_chars = []
    target_positions = []
    pos = 0
    while pos < len(text):
        if text[pos] == "{":
            match = TOKEN.match(text, pos)
            if match is None:
                raise ValueError(f"Invalid byte token at character {pos}.")
            pos = match.end()
            continue
        target_chars.append(text[pos])
        target_positions.append(pos)
        pos += 1

    modes = {}
    for source, target, size in SequenceMatcher(
            None, source_chars, target_chars, autojunk=False).get_matching_blocks():
        for step in range(size):
            modes[target_positions[target + step]] = source_modes[source + step]

    source_lines = "".join(source_chars).split("\n")
    target_lines = "".join(target_chars).split("\n")
    target_start = 0
    for line_number, line in enumerate(target_lines):
        positions = target_positions[target_start:target_start + len(line)]
        known = [modes[pos] for pos in positions if pos in modes]
        source_line = source_lines[min(line_number, len(source_lines) - 1)]
        source_start = sum(len(part) + 1 for part in source_lines[:line_number])
        source_known = source_modes[source_start:source_start + len(source_line)]
        fallback = known[0] if known else source_known[0] if source_known else False
        for pos in positions:
            modes.setdefault(pos, fallback)
        target_start += len(line) + 1
    return modes


def encode_text(text: str, original: bytes | None = None,
                compact: bool = False) -> bytes:
    text = text.replace("(c)", "©")
    result = bytearray()
    if original is not None:
        source_text, end = decode_text(original, 0)
        if not compact and text == source_text and end == len(original):
            return original
    modes = character_modes(text, original) if original is not None else {}
    pos = 0
    while pos < len(text):
        char = text[pos]
        if char == "{":
            match = TOKEN.match(text, pos)
            if match is None:
                raise ValueError(f"Invalid byte token at character {pos}.")
            raw = bytes.fromhex(match[1])
            result.extend(raw)
            pos = match.end()
            continue
        if char == "\n":
            result.append(10)
        else:
            raw_ascii = compact or modes.get(pos, False)
            if char == "©":
                result.extend(b"@" if raw_ascii else COPYRIGHT_CODE.to_bytes(2, "big"))
            elif char == " ":
                result.extend(b"\x20" if raw_ascii else b"\x81\x40")
            elif char == '-':
                result.extend(b'-' if raw_ascii else b'\x81\x7c')
            elif "!" <= char <= "~" and char not in "{}":
                result.extend(bytes((ord(char),)) if raw_ascii else
                              chr(ord(char) + 0xFEE0).encode("shift_jis"))
            elif char in SPANISH_CODES:
                code = SPANISH_COMPACT_CODES[char] if raw_ascii else SPANISH_CODES[char]
                result.extend(code.to_bytes(1 if raw_ascii else 2, 'big'))
            elif ord(char) >= 0x80:
                result.extend(char.encode("shift_jis"))
            else:
                raise ValueError(f"Use a byte token for character {char!r}.")
        pos += 1
    result.append(0)
    _, end = decode_text(bytes(result), 0)
    if end != len(result):
        raise ValueError("Text contains an early terminator.")
    return bytes(result)


def encode_menu_format(text: str, original: bytes, compact: bool = False) -> bytes:
    sequential = 0
    fields = {'%%': '%'}
    def replace(match):
        nonlocal sequential
        field = match[0]
        if field in ('%d', '%s'):
            sequential += 1
            field = f'%{sequential}${field[-1]}'
        if field in fields:
            return fields[field]
        ordinal = int(field[1:-2])
        if ordinal > 63:
            raise ValueError('Menu format argument must be between 1 and 63.')
        return ''.join(f'{{{ord(char):02X}}}' for char in field)
    encoded = re.sub(r'%[1-9][0-9]*\$[dsv]|%[ds%]', replace, text)
    return encode_text(encoded, original, compact=compact)


def extract(data: bytes, event_roots: list[int], menu_roots: list[int]) -> dict:
    entries = {}

    def add(start: int, kind: str) -> int:
        text, end = decode_text(data, start)
        raw = data[start:end]
        if start not in entries:
            entries[start] = {"offset": f"0x{start:06X}", "kind": kind,
                              "original": raw.hex(), "text": text}
        return end

    for kind, roots in (("event", event_roots), ("menu", menu_roots)):
        visited = set()
        pending = list(roots)
        while pending:
            pos = pending.pop()
            try:
                while pos not in visited:
                    if not 0 <= pos < ROM_SIZE:
                        raise ValueError(f"Invalid {kind} address 0x{pos:X}.")
                    visited.add(pos)
                    opcode = data[pos]
                    if opcode == 0 or kind == 'event' and opcode == 0x83:
                        break
                    if kind == "event":
                        if opcode > 0x97:
                            raise ValueError(f"Unsupported event opcode 0x{opcode:02X} at 0x{pos:X}.")
                        if opcode == 0x20:
                            pos = add(pos + 1, kind)
                            continue
                        if opcode == 9:
                            count = data[pos + 1]
                            end = pos + 2 + count * 4
                            if end > ROM_SIZE:
                                raise ValueError("Truncated event pointer list.")
                            for at in range(pos + 2, end, 4):
                                pending.append(struct.unpack_from("<I", data, at)[0] - BASE)
                            pos = end
                            continue
                        if opcode == EVENT_JUMP:
                            pending.append(struct.unpack_from("<I", data, pos + 1)[0] - BASE)
                        width = data[PROFILE["lengths"] + opcode]
                    else:
                        if opcode in (5, 9):
                            pos = add(pos + 2, kind)
                            continue
                        width = MENU_LENGTHS.get(opcode, 0)
                    if not width or pos + width > ROM_SIZE:
                        raise ValueError(f"Unsupported {kind} command at 0x{pos:X}.")
                    pos += width
            except (ValueError, IndexError, struct.error):
                pass
    ordered = [entries[key] for key in sorted(entries)]
    end = 0
    for entry in ordered:
        start = int(entry["offset"], 16)
        if start < end:
            raise ValueError(f"Overlapping text at 0x{start:X}.")
        end = start + len(bytes.fromhex(entry["original"]))
    return {"entries": ordered}


def control_units(raw: bytes) -> list[bytes]:
    return [unit for unit in text_units(raw, 0) if unit[0] < 0x20 and unit != b"\n"]


def rom_roots(data: bytes) -> list[int]:
    # The title timeout installs the attract script directly, outside the event table.
    return [struct.unpack_from("<I", data, PROFILE["roots"] + i * 4)[0] - BASE
            for i in range(196)] + [PROFILE['attract']]


def direct_menu_roots(data: bytes) -> list[int]:
    roots = set()
    # Accept only a literal load into r0 immediately before a Thumb BL.
    for at in range(PROFILE["code_start"], PROFILE["code_end"] - 6, 2):
        load, high, low = struct.unpack_from("<HHH", data, at)
        if load & 0xFF00 != 0x4800 or high & 0xF800 != 0xF000 or low & 0xF800 != 0xF800:
            continue
        displacement = ((high & 0x7FF) << 12) | ((low & 0x7FF) << 1)
        if displacement & 0x400000:
            displacement -= 0x800000
        if at + 6 + displacement != PROFILE["menu"]:
            continue
        literal = ((at + 4) & ~3) + (load & 0xFF) * 4
        target = struct.unpack_from("<I", data, literal)[0] - BASE
        if 0 <= target < PROFILE["code_start"]:
            roots.add(target)
    return sorted(roots)


@lru_cache(maxsize=2)
def data_pointers(data: bytes) -> dict[int, list[int]]:
    pointers = {}
    for low, high in ((PROFILE['code_start'], PROFILE['code_end']),
                      (PROFILE['glyphs'], len(data))):
        for at in range((low + 3) & ~3, high - 3, 4):
            target = struct.unpack_from('<I', data, at)[0] - BASE
            if 0 <= target < len(data):
                pointers.setdefault(target, []).append(at)
    return pointers


@lru_cache(maxsize=2)
def menu_roots(data: bytes) -> list[int]:
    roots = set(direct_menu_roots(data))
    event_doc = extract(data, rom_roots(data), [])
    limit = min(int(entry['offset'], 16) for entry in event_doc['entries']) - 1
    for target in data_pointers(data):
        if not 0x928 <= target < limit or target in roots:
            continue
        try:
            commands = menu_commands(data, target)
            if any(command['text'] is not None for command in commands):
                roots.add(target)
        except ValueError:
            pass
    occupied = bytearray(limit)

    def mark(root):
        pos = root
        for command in menu_commands(data, root):
            if command['text'] is not None:
                _, pos = decode_text(data, command['text'])
            else:
                pos += MENU_LENGTHS.get(data[pos], 1)
        occupied[root:pos] = b'\1' * (pos - root)

    for root in roots:
        mark(root)
    for at in range(0x928, limit - 2):
        if occupied[at] or data[at] not in (5, 9) or data[at + 1] > 31:
            continue
        try:
            commands = menu_commands(data, at)
            offsets = [command['text'] for command in commands if command['text'] is not None]
            if offsets and all(valid_text(data, offset) for offset in offsets):
                roots.add(at)
                mark(at)
        except ValueError:
            pass
    return sorted(roots)


def valid_text(data: bytes, start: int) -> bool:
    units = list(text_units(data, start))
    return (any(unit[0] >= 0x20 or unit == b'\3' for unit in units) and
            all((unit[0] in (1, 2, 3, 4, 6, 7, 8, 10) or
                 TEXT_RUN.fullmatch(unit + b'\0')) for unit in units))


def extract_rom(data: bytes) -> dict:
    events = rom_roots(data)
    menus = menu_roots(data)
    document = extract(data, events, menus)
    occupied = bytearray(len(data))

    def mark(start, end):
        occupied[start:end] = b'\1' * (end - start)

    pending = list(events)
    visited = set()
    while pending:
        start = pending.pop()
        if start in visited:
            continue
        visited.add(start)
        commands = event_commands(data, start)
        for command in commands:
            pending.extend(command['children'])
        pos = start
        for command in commands:
            opcode = data[pos]
            if command['text'] is not None:
                _, pos = decode_text(data, command['text'])
            elif opcode == 9:
                pos += 2 + data[pos + 1] * 4
            else:
                pos += data[PROFILE['lengths'] + opcode]
        mark(start, pos)
    for start in menus:
        pos = start
        for command in menu_commands(data, start):
            if command['text'] is not None:
                _, pos = decode_text(data, command['text'])
            else:
                pos += MENU_LENGTHS.get(data[pos], 1)
        mark(start, pos)
    for entry in document['entries']:
        start = int(entry['offset'], 16)
        mark(start, start + len(bytes.fromhex(entry['original'])))

    def add(start, end, kind='string'):
        if any(occupied[start:end]):
            return
        raw = data[start:end]
        text, decoded_end = decode_text(data, start)
        if decoded_end != end:
            raise ValueError(f'Invalid string boundary at 0x{start:X}.')
        entry = {'offset': f'0x{start:06X}', 'kind': kind,
                 'original': raw.hex(), 'text': text,
                 'capacity': len(raw)}
        document['entries'].append(entry)
        mark(start, end)
        return entry

    event_start = min(int(entry['offset'], 16) for entry in document['entries'] if entry['kind'] == 'event')
    for at in range(event_start - 1, TEXT_BANKS[0][1] - 1):
        if (occupied[at] or data[at] != 0x20 or
                data[at + 1] not in (1, 3, 0x20, 0x22, *range(0x80, 0xA0))):
            continue
        try:
            if valid_text(data, at + 1):
                _, end = decode_text(data, at + 1)
                add(at + 1, end, 'event')
                mark(at, end)
        except ValueError:
            pass
    for start in sorted(data_pointers(data)):
        if not any(low <= start < high for low, high in TEXT_BANKS) or occupied[start]:
            continue
        try:
            text, end = decode_text(data, start)
            if text and valid_text(data, start):
                add(start, end)
        except ValueError:
            pass
    for base, count, stride, category in FIXED_STRINGS:
        for index in range(count):
            start = base + index * stride
            _, end = decode_text(data, start)
            if end > start + stride:
                raise ValueError(f'Invalid {category} boundary at 0x{start:X}.')
            if end > start + 1:
                entry = add(start, end)
                if entry is not None:
                    entry['capacity'] = stride
    for start in SYSTEM_STRINGS:
        _, end = decode_text(data, start)
        add(start, end)
    for low, high in TEXT_BANKS:
        if low == TEXT_BANKS[0][0]:
            high = event_start - 1
        for match in TEXT_RUN.finditer(data, low, high):
            start, end = match.span()
            if end - start >= 5 and not any(occupied[start:end]):
                add(start, end)
    for base, count, stride in KEYBOARDS:
        for index in range(count):
            at = base + index * stride
            length = struct.unpack_from('<H', data, at)[0] * 2
            if length > stride - 2:
                raise ValueError(f'Invalid keyboard length at 0x{at:X}.')
            raw = data[at + 2:at + 2 + length]
            text, end = decode_text(raw + b'\0', 0)
            if end != length + 1:
                raise ValueError(f'Invalid keyboard text at 0x{at:X}.')
            document['entries'].append({'offset': f'0x{at + 2:06X}', 'kind': 'string',
                                        'original': raw.hex(), 'text': text,
                                        'terminated': False,
                                        'capacity': length})
    document['entries'].sort(key=lambda entry: int(entry['offset'], 16))
    return document


def event_commands(data: bytes, start: int) -> list[dict]:
    commands = []
    pos = start
    while 0 <= pos < len(data):
        opcode = data[pos]
        if opcode > 0x97:
            raise ValueError(f"Unsupported event opcode at 0x{pos:X}.")
        item = {"text": None, "children": []}
        if opcode == 0x20:
            item["text"] = pos + 1
            _, end = decode_text(data, pos + 1)
        elif opcode == 9:
            count = data[pos + 1]
            end = pos + 2 + count * 4
            item["children"] = [struct.unpack_from("<I", data, at)[0] - BASE
                                for at in range(pos + 2, end, 4)]
        else:
            end = pos + data[PROFILE["lengths"] + opcode]
            if end <= pos or end > len(data):
                raise ValueError(f"Invalid event command at 0x{pos:X}.")
            if opcode == EVENT_JUMP:
                item["children"] = [struct.unpack_from("<I", data, pos + 1)[0] - BASE]
        commands.append(item)
        if opcode in (0, 0x83):
            return commands
        pos = end
    raise ValueError("Event stream leaves the ROM.")


def menu_commands(data: bytes, start: int) -> list[dict]:
    commands = []
    pos = start
    while 0 <= pos < len(data):
        opcode = data[pos]
        item = {"text": None}
        if opcode == 0:
            commands.append(item)
            return commands
        if opcode in (5, 9):
            item["text"] = pos + 2
            _, pos = decode_text(data, pos + 2)
        else:
            width = MENU_LENGTHS.get(opcode, 0)
            if not width or pos + width > len(data):
                raise ValueError(f"Unsupported menu command at 0x{pos:X}.")
            pos += width
        commands.append(item)
    raise ValueError("Menu stream leaves the ROM.")


@lru_cache(maxsize=2)
def rom_catalog(rom_path: Path) -> dict:
    """Return the USA ROM text entries by offset."""
    data = read_rom(rom_path)
    return {entry["offset"]: entry for entry in extract_rom(data)["entries"]}


def load_dialogue(path: Path, rom_path: Path) -> dict:
    """Load the text catalog, filling an edits file from the user's ROM."""
    document = json.loads(Path(path).read_text(encoding="utf-8"))
    catalog = rom_catalog(rom_path)
    entries = []
    for edit in document["entries"]:
        entry = dict(catalog.get(edit["offset"], {}))
        entry.update(edit)
        if "replace_lines" in entry:
            lines = entry["text"].split("\n")
            for index, line in entry.pop("replace_lines"):
                lines[index] = line
            entry["text"] = "\n".join(lines)
        if "original" not in entry or "text" not in entry:
            raise ValueError(f"No ROM text at {edit['offset']}.")
        entries.append(entry)
    return {**document, "entries": entries}


def load_scenes(path: Path, rom_path: Path) -> dict:
    """Load the scene drafts, filling an edits file from the user's ROM."""
    document = json.loads(Path(path).read_text(encoding="utf-8"))
    catalog = rom_catalog(rom_path)
    entries = []
    for edit in document["entries"]:
        base = catalog.get(edit["english_offset"])
        if base is None:
            raise ValueError(f"No ROM text at {edit['english_offset']}.")
        entries.append({**edit, "english_original_hex": base["original"]})
    return {"entries": entries}
