import json
import struct
import unittest

import dialogue
import insert_scenes
import insert_vwf
import kerning_editor
import vwf_test_support as test_insert_vwf


class KerningRomTests(test_insert_vwf.VwfTests):
    @classmethod
    def setUpClass(cls):
        cls.original = (insert_vwf.ROOT / 'Zoids Legacy (USA).gba').read_bytes()
        cls.choices = json.loads((insert_vwf.ROOT / 'kerning-choices.json').read_text())
        cls.document = json.loads((insert_vwf.ROOT / 'scene-translation.json').read_text())
        cls.rom, cls.symbols = insert_vwf.build_rom(cls.original, cls.document, cls.choices)
        cls.metrics = insert_vwf.original_metrics(cls.original, cls.choices)
        cls.indices = {m[0]: i for i, m in enumerate(cls.metrics)}
        cls.glyphs = {int(g['code'], 16): g for g in kerning_editor.font_data(cls.original)['glyphs']}

    def reference(self, text, inset=2):
        result = [[0] * ((self.width - 2) * 8) for _ in range((self.height - 2) * 8)]
        x, y, previous, color = inset, 0, None, 0
        for unit in dialogue.text_units(text, 0):
            if unit[0] == 0:
                break
            if unit[0] == 1:
                color = unit[1]
                continue
            if unit[0] == 10:
                x, y, previous = inset, y + 16, None
                continue
            glyph = self.glyphs[int.from_bytes(unit, 'big')]
            if previous:
                advance = self.choices['advances'].get(previous['code'], previous['advance'])
                pair = self.choices['pairs'].get(previous['code'] + ':' + glyph['code'], 0)
                x += max(1, advance + self.choices['letter_spacing'] + pair)
            for yy in range(16):
                for xx in range(8):
                    ink = glyph['pixels'][yy * 8 + xx]
                    dx = x + xx - glyph['left']
                    if ink and 0 <= dx < len(result[0]):
                        old = result[y + yy][dx]
                        value = ink + (color + 1) * 4
                        result[y + yy][dx] = max(old, value) if old >> 2 == color + 1 else value
            previous = glyph
        return result, x

    def test_native_font_metrics_and_baseline(self):
        for pair in self.choices['pairs']:
            text = b''.join(bytes.fromhex(code) for code in pair.split(':')) + b'\0'
            with self.subTest(pair=pair):
                self.setup_cpu(text)
                self.run_renderer()
                self.assertEqual(self.canvas(), self.reference(text)[0])
                self.assert_no_tile_leaks()
        for code, advance in self.choices['advances'].items():
            self.assertEqual(self.metrics[self.indices[int(code, 16)]][3], advance)

    def menu_reference(self, text):
        return self.reference(text, inset=0)[0]

    def test_menu_uses_shared_spacing_without_waits(self):
        text = dialogue.encode_text('Status\nEquipment')
        self.setup_cpu(text, height=6)
        self.put32(test_insert_vwf.WINDOW, 1)
        self.put32(0x0200A888, 0)
        self.run_renderer()
        self.assertEqual(self.canvas(), self.menu_reference(text))
        self.assertEqual(self.frames, [])
        self.assertEqual(self.arrows, [])
        self.assertEqual(struct.unpack('<h', self.cpu.mem_read(test_insert_vwf.WINDOW + 12, 2))[0], 9)
        self.assert_no_tile_leaks()

    def test_large_menu_reuses_tiles_without_refresh(self):
        text = dialogue.encode_text('\n'.join(['W' * 26] * 7))
        self.setup_cpu(text, width=30, height=18)
        self.put32(test_insert_vwf.WINDOW, 1)
        self.run_renderer()
        self.assertEqual(self.canvas(), self.menu_reference(text))
        self.assertFalse(self.frames)
        self.assert_no_tile_leaks()

    def test_menu_stack_leaves_room_for_sound(self):
        for sample in ['Which Zoids is pilot riding?', 'Participants earned', 'Zeru', 'HP']:
            with self.subTest(sample=sample):
                self.setup_cpu(dialogue.encode_text(sample), width=30, height=4)
                self.put32(test_insert_vwf.WINDOW, 1)
                minimum = [0x03007000]
                def observe(cpu, address, size, data):
                    minimum[0] = min(minimum[0], cpu.reg_read(test_insert_vwf.UC_ARM_REG_SP))
                self.cpu.hook_add(test_insert_vwf.UC_HOOK_CODE, observe)
                self.run_renderer()
                # Chg Zd has 532 bytes left; sound calls also use this task stack.
                self.assertLessEqual(0x03007000 - minimum[0], 320)

    def test_menu_redraw_erases_previous_label(self):
        self.setup_cpu(dialogue.encode_text('WWWWWW'), height=4)
        self.put32(test_insert_vwf.WINDOW, 1)
        self.run_renderer()
        self.cpu.mem_write(test_insert_vwf.WINDOW + 12, bytes(4))
        text = dialogue.encode_text('iiiiii')
        self.cpu.mem_write(test_insert_vwf.TEXT, text)
        self.cpu.reg_write(test_insert_vwf.UC_ARM_REG_R0, test_insert_vwf.WINDOW)
        self.cpu.reg_write(test_insert_vwf.UC_ARM_REG_R1, test_insert_vwf.TEXT)
        self.cpu.reg_write(test_insert_vwf.UC_ARM_REG_LR, test_insert_vwf.STOP | 1)
        self.run_renderer()
        self.assertEqual(self.canvas(), self.menu_reference(text))
        self.assertFalse(self.frames)

    def test_menu_wrap_consumes_explicit_newline_once(self):
        text = dialogue.encode_text('WWWW\nWWWW')
        self.setup_cpu(text, width=6, height=6)
        self.put32(test_insert_vwf.WINDOW, 0x41)
        self.run_renderer()
        self.assertEqual(self.canvas(), self.menu_reference(text))
        self.assertFalse(self.frames)
        self.assert_no_tile_leaks()

    def test_menu_position_and_overflow(self):
        text = b'\x02\x03\x00' + dialogue.encode_text('Status')
        self.setup_cpu(text, height=4)
        self.put32(test_insert_vwf.WINDOW, 1)
        self.run_renderer()
        expected = self.menu_reference(dialogue.encode_text('Status'))
        expected = [[0] * 24 + row[:-24] for row in expected]
        self.assertEqual(self.canvas(), expected)
        self.setup_cpu(dialogue.encode_text('EquipmentEquipment'), width=7, height=4)
        self.put32(test_insert_vwf.WINDOW, 1)
        self.run_renderer()
        self.assertEqual(struct.unpack('<h', self.cpu.mem_read(test_insert_vwf.WINDOW + 14, 2))[0], 0)
        self.assertFalse(self.frames)

    def test_menu_font_and_compact_labels(self):
        self.assertEqual(self.rom[0x7A0A98:0x7A0BF8], self.original[0x7A0A98:0x7A0BF8])
        self.assertEqual(self.rom[0xED948:0xEE548], self.original[0xED948:0xEE548])

    def test_only_renderer_and_main_font_pointers_change(self):
        restored = bytearray(self.rom[:len(self.original)])
        for offset in (insert_vwf.HOOK, insert_scenes.HOOK_OFFSET):
            restored[offset:offset + 8] = self.original[offset:offset + 8]
        self.assertEqual(restored, self.original)


if __name__ == '__main__':
    unittest.main()
