import json
import struct
import unittest

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import *

import dialogue
import insert_vwf

WINDOW = 0x0200A8A0
TEXT = 0x02030000
BUFFER = 0x02010000
STOP = 0x08000200


class VwfTests(unittest.TestCase):

    def setup_cpu(self, text, width=22, height=8):
        cpu = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        cpu.mem_map(0x08000000, len(self.rom))
        cpu.mem_write(0x08000000, self.rom)
        cpu.mem_map(0x02000000, 0x40000)
        cpu.mem_map(0x03000000, 0x8000)
        self.cpu = cpu
        self.frames = []
        self.arrows = []
        self.width, self.height = width, height
        self.put32(0x02021654, BUFFER)
        self.put32(0x02021658, 512)
        self.put32(0x02021664, 768)
        self.put32(0x02021670, 0)
        self.put32(0x0200A888, TEXT)
        self.put32(WINDOW, 0x51)
        cpu.mem_write(WINDOW + 8, struct.pack('<HH', width, height))
        cpu.mem_write(WINDOW + 30, struct.pack('<H', 769) * width * height)
        cpu.mem_write(TEXT, text)
        cpu.mem_write(0x02021774, dialogue.encode_text('Zeru'))
        cpu.mem_write(0x0300000E, b'\x01\x00')
        cpu.reg_write(UC_ARM_REG_R0, WINDOW)
        cpu.reg_write(UC_ARM_REG_R1, TEXT)
        cpu.reg_write(UC_ARM_REG_SP, 0x03007000)
        cpu.reg_write(UC_ARM_REG_LR, STOP | 1)
        for reg in range(UC_ARM_REG_R4, UC_ARM_REG_R11 + 1):
            cpu.reg_write(reg, 0x12340000 + reg)

        def external(cpu, address, size, _):
            if address == 0x080972C8:
                used = int.from_bytes(cpu.mem_read(0x0200DD90, 128), 'little')
                freed = int.from_bytes(cpu.mem_read(0x0200DE10, 128), 'little')
                self.assertEqual(freed & ~used, 0)
                cpu.mem_write(0x0200DD90, (used ^ freed).to_bytes(128, 'little'))
                cpu.mem_write(0x0200DE10, bytes(128))
            elif address == 0x080ED17C:
                self.frames.append(self.canvas())
            elif address == 0x08094484:
                self.arrows.append(True)
                cpu.reg_write(UC_ARM_REG_R0, 0x02031000)
            elif address not in (0x08094554, 0x08092E84):
                return
            cpu.reg_write(UC_ARM_REG_PC, cpu.reg_read(UC_ARM_REG_LR))

        cpu.hook_add(UC_HOOK_CODE, external)
        return cpu

    def put32(self, address, value):
        self.cpu.mem_write(address, struct.pack('<I', value))

    def run_renderer(self):
        self.cpu.emu_start(0x08097DA9, STOP, count=3000000)
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_PC), STOP)
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_SP), 0x03007000)
        for reg in range(UC_ARM_REG_R4, UC_ARM_REG_R11 + 1):
            self.assertEqual(self.cpu.reg_read(reg), 0x12340000 + reg)

    def canvas(self):
        data = self.cpu.mem_read(WINDOW + 30, self.width * self.height * 2)
        tiles = struct.unpack('<' + 'H' * (self.width * self.height), data)
        result = [[0] * ((self.width - 2) * 8) for _ in range((self.height - 2) * 8)]
        for ty in range(1, self.height - 1):
            for tx in range(1, self.width - 1):
                index = tiles[ty * self.width + tx] & 1023
                if index >= 768:
                    continue
                raw = self.cpu.mem_read(BUFFER + index * 32, 32)
                for y in range(8):
                    for x in range(8):
                        value = (raw[y * 4 + x // 2] >> ((x % 2) * 4)) & 15
                        result[(ty - 1) * 8 + y][(tx - 1) * 8 + x] = value if value & 3 else 0
        return result


    def assert_no_tile_leaks(self):
        used = int.from_bytes(self.cpu.mem_read(0x0200DD90, 128), 'little')
        raw = self.cpu.mem_read(WINDOW + 30, self.width * self.height * 2)
        ids = [t & 1023 for t in struct.unpack('<' + 'H' * (self.width * self.height), raw)]
        expected = sum(1 << t for t in set(ids) if t < 768)
        self.assertEqual(used, expected)

    def test_pixel_composition_and_registers(self):
        for sample in ['William AVATAR!', 'iiii WWWW 0125', 'αβγδε ΩΨΦ', 'Hello, world!\nNext line.']:
            with self.subTest(sample=sample):
                text = dialogue.encode_text(sample)
                self.setup_cpu(text)
                self.run_renderer()
                expected, x = self.reference(text)
                self.assertEqual(self.canvas(), expected)
                self.assertEqual(self.cpu.reg_read(UC_ARM_REG_R0), TEXT + len(text) - 1)
                self.assert_no_tile_leaks()

    def test_color_and_player_name(self):
        text = dialogue.encode_text('Hi ' )[:-1] + b'\x03' + b'\x01\x01' + dialogue.encode_text('!')
        expanded = dialogue.encode_text('Hi Zeru')[:-1] + b'\x01\x01' + dialogue.encode_text('!')
        self.setup_cpu(text)
        self.run_renderer()
        self.assertEqual(self.canvas(), self.reference(expanded)[0])
        self.assert_no_tile_leaks()

    def test_scroll_releases_tiles_and_preserves_last_lines(self):
        text = dialogue.encode_text('First\nSecond\nThird\nFourth\nFifth')
        self.setup_cpu(text)
        self.run_renderer()
        self.assertEqual(self.canvas(), self.reference(dialogue.encode_text('Third\nFourth\nFifth'))[0])
        self.assertEqual(len(self.arrows), 1)
        self.assert_no_tile_leaks()

    def test_menu_uses_original_prologue(self):
        self.setup_cpu(b'Menu\0')
        self.put32(0x0200A888, TEXT + 100)
        self.cpu.emu_start(0x08097DA9, 0x08097DB0, count=10000)
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_PC), 0x08097DB0)
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_R0), WINDOW)
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_R1), TEXT)
        self.assertLessEqual(self.cpu.reg_read(UC_ARM_REG_SP), 0x03007000 - 20)
        self.cpu.emu_start(0x08097DB1, STOP, count=3000000)
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_PC), STOP)
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_SP), 0x03007000)
        for reg in range(UC_ARM_REG_R4, UC_ARM_REG_R11 + 1):
            self.assertEqual(self.cpu.reg_read(reg), 0x12340000 + reg)

    def test_allocation_failure_consumes_text(self):
        text = dialogue.encode_text('No tiles')
        self.setup_cpu(text)
        self.put32(0x02021658, 0)
        self.run_renderer()
        self.assertEqual(self.cpu.reg_read(UC_ARM_REG_R0), TEXT + len(text) - 1)


    def test_wide_and_negative_bearing_glyphs(self):
        text = dialogue.encode_text('jW…WWj')
        self.setup_cpu(text)
        self.run_renderer()
        self.assertEqual(self.canvas(), self.reference(text)[0])
        self.assert_no_tile_leaks()


    def test_all_translated_entries(self):
        document = json.loads((insert_vwf.ROOT / 'scene-translation.json').read_text())
        for entry in document['entries']:
            with self.subTest(offset=entry['english_offset']):
                text = dialogue.encode_text(entry['english_draft'])
                self.setup_cpu(text, width=entry['text_columns'] + 2)
                def reject_fallback(cpu, address, size, data):
                    self.fail('Translated entry used the original renderer')
                address = self.symbols['original_render'] & ~1
                self.cpu.hook_add(UC_HOOK_CODE, reject_fallback, begin=address, end=address)
                self.run_renderer()
                self.assertEqual(self.cpu.reg_read(UC_ARM_REG_R0), TEXT + len(text) - 1)
                self.assert_no_tile_leaks()
