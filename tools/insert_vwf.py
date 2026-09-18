"""Build a USA test ROM with custom dialogue spacing."""

import argparse
import hashlib
import json
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile

import dialogue
import insert_scenes
import kerning_editor

ROOT = Path(__file__).resolve().parent.parent
HOOK = 0x97DA8
ORIGINAL = bytes.fromhex('f0b557464e464546')
PAYLOAD = 0x900000
BASE = 0x08000000

def original_metrics(rom, choices):
    glyphs = kerning_editor.font_data(rom)['glyphs']
    choices = kerning_editor.validate(choices, {g['code'] for g in glyphs})
    result = []
    for g in glyphs:
        trim = g['left'] if choices['spacing'] == 'proportional' else 0
        width = g['left'] + g['width'] - trim if g['width'] else 0
        rows = [g['pixels'][y * 8 + trim:y * 8 + trim + width] + [0] * (16 - width)
                for y in range(16)]
        default = g['advance'] if choices['spacing'] == 'proportional' else 8
        advance = choices['advances'].get(g['code'], default) + choices['letter_spacing']
        result.append((int(g['code'], 16), 0, width, advance, rows))
    return result


def pack_glyph(rows):
    return bytes(sum(row[x + i] << (i * 2) for i in range(4))
                 for row in rows for x in range(0, 16, 4))


def pair_table(metrics, choices=None):
    result = bytearray(len(metrics) ** 2)
    indices = {f'{m[0]:04X}': i for i, m in enumerate(metrics)}
    for key, value in (choices or {}).get('pairs', {}).items():
        left, right = key.split(':')
        result[indices[left] * len(metrics) + indices[right]] = value & 255
    return bytes(result)


def compile_payload(rom, choices=None):
    for tool in ('arm-none-eabi-gcc', 'arm-none-eabi-objcopy', 'arm-none-eabi-nm'):
        if not shutil.which(tool):
            raise ValueError(f'Missing tool: {tool}')
    choices = kerning_editor.defaults() if choices is None else choices
    metrics = original_metrics(rom, choices)
    pairs = pair_table(metrics, choices)
    with tempfile.TemporaryDirectory() as tmp:
        path = Path(tmp)
        metric_bytes = b''.join(struct.pack('<HbBb3x', *m[:4]) for m in metrics)
        (path / 'metrics.bin').write_bytes(metric_bytes)
        glyph_bytes = b''.join(pack_glyph(m[4]) for m in metrics)
        (path / 'glyphs.bin').write_bytes(glyph_bytes)
        (path / 'pairs.bin').write_bytes(pairs)
        (path / 'entry.s').write_text(f'''.syntax unified
.cpu arm7tdmi
.thumb
.section .entry,"ax"
.global vwf_entry
.thumb_func
vwf_entry:
    ldr r3, =vwf_render
    bx r3
.ltorg
.section .text,"ax"
.global original_render
.thumb_func
original_render:
    push {{r4, r5, r6, r7, lr}}
    mov r7, r10
    mov r6, r9
    mov r5, r8
    ldr r3, =0x08097db1
    bx r3
.ltorg
.section .rodata,"a"
.balign 4
.global metric_count
metric_count: .word {len(metrics)}
.global metrics
metrics: .incbin "{path / 'metrics.bin'}"
.global glyphs
glyphs: .incbin "{path / 'glyphs.bin'}"
.global pairs
pairs: .incbin "{path / 'pairs.bin'}"
''')
        (path / 'link.ld').write_text(f'''SECTIONS {{
 . = {BASE + PAYLOAD};
 .text : {{ *(.entry) *(.text*) *(.rodata*) }}
 /DISCARD/ : {{ *(.comment*) *(.ARM.attributes*) *(.ARM.exidx*) }}
}}
''')
        elf = path / 'vwf.elf'
        subprocess.run(['arm-none-eabi-gcc', '-mcpu=arm7tdmi', '-mthumb', '-Os',
                        '-ffreestanding', '-fno-jump-tables', '-fno-builtin', '-fno-unwind-tables', '-nostdlib',
                        '-Wall', '-Wextra', '-Werror', '-Wl,--build-id=none',
                        '-T', str(path / 'link.ld'), str(path / 'entry.s'),
                        str(Path(__file__).with_name('dialogue_vwf.c')), '-o', str(elf)], check=True)
        subprocess.run(['arm-none-eabi-objcopy', '-O', 'binary', str(elf), str(path / 'vwf.bin')], check=True)
        symbols = subprocess.check_output(['arm-none-eabi-nm', str(elf)], text=True)
        addresses = {parts[2]: int(parts[0], 16) for line in symbols.splitlines()
                     if len(parts := line.split()) == 3}
        return (path / 'vwf.bin').read_bytes(), addresses


def build_rom(original, document=None, choices=None):
    if hashlib.sha1(original).hexdigest() != dialogue.ROM_SHA1:
        raise ValueError('Input must be the clean USA ROM.')
    if original[HOOK:HOOK + 8] != ORIGINAL:
        raise ValueError('Original renderer does not match.')
    rom = bytearray(insert_scenes.build_rom(original, document) if document else original)
    rom.extend(b'\xff' * (insert_scenes.OUTPUT_SIZE - len(rom)))
    payload, symbols = compile_payload(original, choices)
    if PAYLOAD + len(payload) > len(rom) or any(b != 255 for b in rom[PAYLOAD:PAYLOAD + len(payload)]):
        raise ValueError('Renderer payload overlaps existing data.')
    rom[PAYLOAD:PAYLOAD + len(payload)] = payload
    rom[HOOK:HOOK + 8] = struct.pack('<HHI', 0x4B00, 0x4718, BASE + PAYLOAD + 1)
    return bytes(rom), symbols


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path, default=ROOT / 'Zoids Legacy (USA).gba')
    parser.add_argument('--draft', type=Path)
    parser.add_argument('--kerning', type=Path, default=ROOT / 'kerning-choices.json', help='Original-font choices from the web editor')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    try:
        document = json.loads(args.draft.read_text()) if args.draft else None
        choices = json.loads(args.kerning.read_text()) if args.kerning else None
        rom, _ = build_rom(args.rom.read_bytes(), document, choices)
        with args.output.open('xb') as stream:
            stream.write(rom)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        parser.exit(1, f'Error: {error}\n')
    print(f'Wrote {args.output}.')


if __name__ == '__main__':
    main()
