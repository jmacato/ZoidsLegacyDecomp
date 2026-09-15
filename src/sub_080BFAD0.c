#include "m2c_prelude.h"

M2C_UNK func_080BF514(u8, u8, u8);
M2C_UNK func_080E8B08(u8, u8);
s32 func_080E9D88(u8, u8);

void sub_080BFAD0(u8 arg0, u8 arg1, u8 arg2) {
    u8 slot;
    s32 row_offset;
    s32 col_offset;
    s32 slot_offset;
    s32 arg2_next;
    s32 arg2_offset;
    s32 arg1_4;
    u8 *entry;
    u32 *flags;
    register s32 arg0_4 asm("r9");
    register s32 arg2_saved asm("r10");
    register u8 *base asm("r8");
    register s32 field asm("r1");

    arg2_saved = arg2;
    if ((func_080E9D88(arg0, arg1) << 24) != 0) {
        slot = 0;
        arg0_4 = arg0 << 2;
        arg1_4 = arg1 << 2;
        {
            register u8 *base_input asm("r1");

            base_input = (u8 *)0x02034B4C;
            asm volatile("" : "+r"(base_input));
            base = base_input;
        }
        do {
            {
                register s32 row4 asm("r2");

                row4 = arg0_4;
                row_offset = row4 + arg0;
                asm volatile("" :: "r"(row4));
            }
            row_offset <<= 3;
            row_offset -= arg0;
            row_offset <<= 7;
            col_offset = arg1_4 + arg1;
            col_offset <<= 3;
            col_offset -= arg1;
            col_offset <<= 4;
            col_offset += (s32)base;
            row_offset += col_offset;
            slot_offset = slot << 1;
            slot_offset += slot;
            slot_offset <<= 2;
            slot_offset += 0xE4;
            entry = (u8 *)(row_offset + slot_offset);
            field = *(u16 *)(entry + 4);
            if (field != 0) {
                register s32 mask asm("r2");
                register s32 bits asm("r0");

                mask = 0xE000;
                asm volatile("" : "+r"(mask));
                bits = mask;
                bits &= field;
                if (bits == 0x2000) {
                    field = arg0 << 1;
                    field += arg0;
                    field <<= 3;
                    field = arg1_4 + field;
                    arg2_next = arg2_saved + 1;
                    arg2_offset = arg2_next << 1;
                    arg2_offset += arg2_next;
                    arg2_offset <<= 4;
                    field += arg2_offset;
                    flags = (u32 *)(field + 0x0203ED28);
                    asm volatile("" :: "r"(arg2_offset));
                    if (*flags & (1 << slot)) {
                        func_080BF514(arg0, arg1, slot);
                    }
                }
            }
            slot += 1;
        } while ((u32)slot <= 0x1F);
        func_080E8B08(arg0, arg1);
    }
}
