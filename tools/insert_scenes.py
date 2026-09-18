"""Build a USA test ROM with a lookup table for edited event text."""

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile

import dialogue
import scene_layout

ROOT = Path(__file__).resolve().parent.parent


HOOK_OFFSET = 0xA150C
HOOK_ORIGINAL = bytes.fromhex('0649306801300860')
PAYLOAD_OFFSET = 0x800000
TABLE_OFFSET = PAYLOAD_OFFSET + 0x40
OUTPUT_SIZE = 0x1000000


def validate_document(document, rom):
    if (document.get('format') != 'zoids-scene-translation-v1'
            or document.get('usa_rom_sha1') != dialogue.ROM_SHA1):
        raise ValueError('Unsupported scene draft or ROM version.')
    entries = document.get('entries', [])
    if not entries or document.get('entry_count') != len(entries):
        raise ValueError('Incorrect entry count.')
    offsets = set()
    for entry in entries:
        offset = int(entry['english_offset'], 16)
        if offset in offsets:
            raise ValueError('Duplicate scene offset.')
        offsets.add(offset)
        original = bytes.fromhex(entry['english_original_hex'])
        if not 0 < offset < len(rom) or rom[offset - 1] != 0x20 or rom[offset:offset + len(original)] != original:
            raise ValueError(f'Event text does not match at {entry["english_offset"]}.')
        decoded, end = dialogue.decode_text(original, 0)
        if end != len(original) or decoded != entry['english_original']:
            raise ValueError(f'Changed source at {entry["english_offset"]}.')
        scene_layout.check_entry(entry)
        new = dialogue.encode_text(entry['english_draft'])
        if dialogue.control_units(original) != dialogue.control_units(new):
            raise ValueError(f'Changed control tokens at {entry["english_offset"]}.')
        if offset == 0x050F28 and len(entry['english_draft'].splitlines()) != 2:
            raise ValueError('The battle menu must keep two choices.')


def assemble_hook():
    assembler = shutil.which('arm-none-eabi-as')
    objcopy = shutil.which('arm-none-eabi-objcopy')
    if not assembler or not objcopy:
        raise ValueError('Install GNU Arm binutils: arm-none-eabi-as and arm-none-eabi-objcopy.')
    with tempfile.TemporaryDirectory() as directory:
        obj = Path(directory) / 'hook.o'
        binary = Path(directory) / 'hook.bin'
        subprocess.run([assembler, '-o', str(obj), str(Path(__file__).with_name('scene_text_hook.s'))], check=True)
        subprocess.run([objcopy, '-O', 'binary', '-j', '.text', str(obj), str(binary)], check=True)
        code = binary.read_bytes()
    if len(code) != TABLE_OFFSET - PAYLOAD_OFFSET:
        raise ValueError('Unexpected hook size.')
    return code


def build_rom(rom, document):
    if len(rom) != dialogue.ROM_SIZE or hashlib.sha1(rom).hexdigest() != dialogue.ROM_SHA1:
        raise ValueError('Input must be the clean USA ROM.')
    validate_document(document, rom)
    if rom[HOOK_OFFSET:HOOK_OFFSET + 8] != HOOK_ORIGINAL:
        raise ValueError('Original text handler does not match.')
    entries = sorted(document['entries'], key=lambda entry: int(entry['english_offset'], 16))
    glyphs = [struct.unpack_from('<HB', rom, dialogue.FONT_TABLE + i * 8)
              for i in range(22)]
    strings = bytearray()
    table = bytearray()
    text_start = TABLE_OFFSET + (len(entries) + 1) * 8
    for entry in entries:
        offset = int(entry['english_offset'], 16)
        original = bytes.fromhex(entry['english_original_hex'])
        if rom[offset - 1] != 0x20 or rom[offset:offset + len(original)] != original:
            raise ValueError(f'Event text does not match at {entry["english_offset"]}.')
        encoded = dialogue.encode_text(entry['english_draft'])
        for unit in dialogue.text_units(encoded, 0):
            if unit[0] >= 0x20 and (len(unit) != 2 or not any(
                    low <= int.from_bytes(unit, 'big') < low + count for low, count in glyphs)):
                raise ValueError(f'Unsupported glyph {unit.hex()} at {entry["english_offset"]}.')
        table.extend(struct.pack('<II', dialogue.BASE + offset, dialogue.BASE + text_start + len(strings)))
        strings.extend(encoded)
    table.extend(bytes(8))
    payload = assemble_hook() + table + strings
    if PAYLOAD_OFFSET + len(payload) > OUTPUT_SIZE:
        raise ValueError('Edited text exceeds the expanded ROM size.')
    result = bytearray(rom)
    result.extend(b'\xff' * (OUTPUT_SIZE - len(result)))
    result[PAYLOAD_OFFSET:PAYLOAD_OFFSET + len(payload)] = payload
    # This aligned Thumb jump replaces only the display-pointer assignment.
    result[HOOK_OFFSET:HOOK_OFFSET + 8] = struct.pack('<HHI', 0x4800, 0x4700,
                                                  dialogue.BASE + PAYLOAD_OFFSET + 1)
    verify_rom(rom, bytes(result), document)
    return bytes(result)


def verify_rom(original, patched, document):
    if len(patched) != OUTPUT_SIZE:
        raise ValueError('Unexpected output ROM size.')
    if (patched[:HOOK_OFFSET] != original[:HOOK_OFFSET]
            or patched[HOOK_OFFSET + 8:len(original)] != original[HOOK_OFFSET + 8:]):
        raise ValueError('Unexpected changes outside the text handler.')
    expected_hook = struct.pack('<HHI', 0x4800, 0x4700, dialogue.BASE + PAYLOAD_OFFSET + 1)
    if patched[HOOK_OFFSET:HOOK_OFFSET + 8] != expected_hook:
        raise ValueError('Incorrect text handler jump.')
    entries = sorted(document['entries'], key=lambda entry: int(entry['english_offset'], 16))
    cursor = TABLE_OFFSET + (len(entries) + 1) * 8
    for index, entry in enumerate(entries):
        source, target = struct.unpack_from('<II', patched, TABLE_OFFSET + index * 8)
        if source != dialogue.BASE + int(entry['english_offset'], 16) or target != dialogue.BASE + cursor:
            raise ValueError('Incorrect text lookup pointer.')
        text, end = dialogue.decode_text(patched, cursor)
        if text != entry['english_draft']:
            raise ValueError(f'Text readback failed at {entry["english_offset"]}.')
        cursor = end
    if patched[TABLE_OFFSET + len(entries) * 8:TABLE_OFFSET + (len(entries) + 1) * 8] != bytes(8):
        raise ValueError('Missing text lookup terminator.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path, default=ROOT / 'Zoids Legacy (USA).gba')
    parser.add_argument('--draft', type=Path, default=ROOT / 'scene-translation.json')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    try:
        document = json.loads(args.draft.read_text(encoding='utf-8'))
        patched = build_rom(args.rom.read_bytes(), document)
        with args.output.open('xb') as stream:
            stream.write(patched)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        parser.exit(1, f'Error: {error}\n')
    print(f'Wrote {args.output}: {document["entry_count"]} entries, {len(patched)} bytes.')
    print('Original event scripts are unchanged. In-game testing remains required.')


if __name__ == '__main__':
    main()
