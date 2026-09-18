import copy
import json
import struct
import unittest

import dialogue
import insert_scenes as patcher

try:
    from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
    from unicorn.arm_const import (
        UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
        UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
        UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC,
    )
except ImportError:
    Uc = None


class InsertionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.original = (patcher.ROOT / 'Zoids Legacy (USA).gba').read_bytes()
        cls.document = json.loads((patcher.ROOT / 'scene-translation.json').read_text())
        cls.patched = patcher.build_rom(cls.original, cls.document)
        cls.entries = sorted(cls.document['entries'], key=lambda entry: int(entry['english_offset'], 16))

    def test_readback_and_unchanged_original_scripts(self):
        patcher.verify_rom(self.original, self.patched, self.document)
        for entry in self.entries:
            start = int(entry['english_offset'], 16)
            end = start + len(bytes.fromhex(entry['english_original_hex']))
            self.assertEqual(self.patched[start:end], self.original[start:end])

    def test_rejects_modified_input_rom(self):
        changed = bytearray(self.original)
        changed[0x200] ^= 1
        with self.assertRaisesRegex(ValueError, 'clean USA'):
            patcher.build_rom(bytes(changed), self.document)

    def test_rejects_unsupported_font_glyph(self):
        changed = copy.deepcopy(self.document)
        entry = next(e for e in changed['entries'] if '“' in e['english_draft'])
        entry['english_draft'] = entry['english_draft'].replace('“', '{FF}', 1)
        with self.assertRaisesRegex(ValueError, 'Unsupported glyph'):
            patcher.build_rom(self.original, changed)

    def test_rejects_changed_sources_and_controls(self):
        for field, value in [('english_original', 'Changed source'), ('english_original_hex', '00')]:
            changed = copy.deepcopy(self.document)
            changed['entries'][0][field] = value
            with self.subTest(field=field), self.assertRaises(ValueError):
                patcher.build_rom(self.original, changed)
        changed = copy.deepcopy(self.document)
        entry = next(e for e in changed['entries'] if '{03}' in e['english_draft'])
        entry['english_draft'] = entry['english_draft'].replace('{03}', 'Zeru')
        with self.assertRaisesRegex(ValueError, 'control tokens'):
            patcher.build_rom(self.original, changed)

    def test_rejects_duplicate_offsets_and_incorrect_count(self):
        changed = copy.deepcopy(self.document)
        changed['entries'][1] = changed['entries'][0]
        with self.assertRaisesRegex(ValueError, 'Duplicate'):
            patcher.build_rom(self.original, changed)
        changed = copy.deepcopy(self.document)
        changed['entry_count'] += 1
        with self.assertRaisesRegex(ValueError, 'entry count'):
            patcher.build_rom(self.original, changed)

    def test_detects_damaged_pointer(self):
        changed = bytearray(self.patched)
        changed[patcher.TABLE_OFFSET + 4] ^= 1
        with self.assertRaisesRegex(ValueError, 'lookup pointer'):
            patcher.verify_rom(self.original, bytes(changed), self.document)

    def cpu(self):
        cpu = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        cpu.mem_map(dialogue.BASE, len(self.patched))
        cpu.mem_write(dialogue.BASE, self.patched)
        cpu.mem_map(0x02000000, 0x40000)
        cpu.mem_map(0x03000000, 0x8000)
        return cpu

    @unittest.skipIf(Uc is None, 'Unicorn is required for ARM execution tests.')
    def test_arm_lookup_all_entries_and_fallback(self):
        cpu = self.cpu()
        cases = [(int(entry['english_offset'], 16),
                  struct.unpack_from('<I', self.patched, patcher.TABLE_OFFSET + i * 8 + 4)[0])
                 for i, entry in enumerate(self.entries)]
        selected = {offset for offset, _ in cases}
        untouched = [int(entry['offset'], 16) for entry in dialogue.extract_rom(self.original)['entries']
                     if entry['kind'] == 'event' and int(entry['offset'], 16) not in selected]
        cases.extend((offset, dialogue.BASE + offset) for offset in (untouched[0], untouched[-1]))
        preserved = [UC_ARM_REG_R2, UC_ARM_REG_R3, UC_ARM_REG_R4,
                     UC_ARM_REG_R5, UC_ARM_REG_R7]
        for offset, expected in cases:
            with self.subTest(offset=hex(offset)):
                for i, reg in enumerate(preserved):
                    cpu.reg_write(reg, 0x12340000 + i)
                cpu.reg_write(UC_ARM_REG_R6, 0x020314C4)
                cpu.reg_write(UC_ARM_REG_SP, 0x03007000)
                cpu.reg_write(UC_ARM_REG_LR, 0x08012345)
                cpu.mem_write(0x020314C4, struct.pack('<I', dialogue.BASE + offset - 1))
                cpu.emu_start(dialogue.BASE + patcher.HOOK_OFFSET + 1, 0x080A1514, count=10000)
                self.assertEqual(cpu.reg_read(UC_ARM_REG_PC), 0x080A1514)
                self.assertEqual(struct.unpack('<I', cpu.mem_read(0x0200A888, 4))[0], expected)
                self.assertEqual(cpu.reg_read(UC_ARM_REG_R1), 0x0200A888)
                self.assertEqual(cpu.reg_read(UC_ARM_REG_R6), 0x020314C4)
                self.assertEqual(cpu.reg_read(UC_ARM_REG_SP), 0x03007000)
                self.assertEqual(cpu.reg_read(UC_ARM_REG_LR), 0x08012345)
                for i, reg in enumerate(preserved):
                    self.assertEqual(cpu.reg_read(reg), 0x12340000 + i)

    @unittest.skipIf(Uc is None, 'Unicorn is required for ARM execution tests.')
    def test_original_handler_and_scanner_with_new_text(self):
        cpu = self.cpu()
        displayed = []

        def skip_window_render(cpu, address, size, user_data):
            if cpu.reg_read(UC_ARM_REG_R0) in (0x080177D0, 0x080177D5):
                displayed.append(struct.unpack('<I', cpu.mem_read(0x0200A888, 4))[0])
            cpu.reg_write(UC_ARM_REG_PC, cpu.reg_read(UC_ARM_REG_LR))

        cpu.hook_add(UC_HOOK_CODE, skip_window_render, begin=0x08098BB4, end=0x08098BB4)
        for index, entry in enumerate(self.entries):
            for portrait in (0, 1):
                with self.subTest(offset=entry['english_offset'], portrait=portrait):
                    offset = int(entry['english_offset'], 16)
                    expected = struct.unpack_from('<I', self.patched, patcher.TABLE_OFFSET + index * 8 + 4)[0]
                    cpu.reg_write(UC_ARM_REG_R0, 0)
                    cpu.reg_write(UC_ARM_REG_R1, 0x020314C4)
                    cpu.reg_write(UC_ARM_REG_SP, 0x03007000)
                    cpu.reg_write(UC_ARM_REG_LR, 0x08000201)
                    cpu.mem_write(0x020314C4, struct.pack('<I', dialogue.BASE + offset - 1))
                    cpu.mem_write(0x02031744, struct.pack('<I', portrait))
                    cpu.mem_write(0x02030666, bytes(1))
                    displayed.clear()
                    cpu.emu_start(0x080A147D, 0x08000200, count=30000)
                    self.assertEqual(cpu.reg_read(UC_ARM_REG_PC), 0x08000200)
                    self.assertEqual(displayed, [expected])
                    original_end = dialogue.BASE + offset + len(bytes.fromhex(entry['english_original_hex']))
                    self.assertEqual(struct.unpack('<I', cpu.mem_read(0x020314C4, 4))[0], original_end)


if __name__ == '__main__':
    unittest.main()
