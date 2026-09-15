#include "m2c_prelude.h"

struct GridCellE7AE0 {
    u8 pad00[0xBA];
    u8 tags[10];
    s16 values[10];
};

u8 func_080BF464(u8, u8, s32);

s32 sub_080E7AE0(s32 arg0, s32 arg1, s32 arg2) {
    u32 row;
    u32 column;
    u32 tag;

    arg0 <<= 24;
    row = (u32)arg0 >> 24;
    arg1 <<= 24;
    column = (u32)arg1 >> 24;
    arg2 <<= 24;
    tag = (u32)arg2 >> 24;
    if ((u8)func_080BF464(row, column, 0x17) != 0xFF) {
        register s32 row_offset asm("r1");
        register s32 column_offset asm("r0");
        register u8 *base asm("r2");
        register struct GridCellE7AE0 *cell asm("r1");
        register u8 *value_base asm("r3");
        register u32 index asm("r2");
        register u8 *first_tag asm("r0");
        register s32 current_tag asm("r0");

        row_offset = row << 2;
        row_offset += row;
        row_offset <<= 3;
        row_offset -= row;
        row_offset <<= 7;
        column_offset = column << 2;
        column_offset += column;
        column_offset <<= 3;
        column_offset -= column;
        column_offset <<= 4;
        base = (u8 *)0x02034B4C;
        column_offset += (s32)base;
        cell = (struct GridCellE7AE0 *)(row_offset + column_offset);
        value_base = (u8 *)cell;
        value_base += 0xB0;
        index = 0;
        first_tag = (u8 *)cell;
        first_tag += 0xBA;
        current_tag = *first_tag;
        if (current_tag != tag) {
            register u8 *tags asm("r1");

            tags = (u8 *)cell;
            tags += 0xBA;
            do {
                register u32 next_index asm("r0");
                register u8 *tag_slot asm("r0");

                next_index = index + 1;
                next_index <<= 24;
                index = next_index >> 24;
                if (index > 9) {
                    return 0;
                }
                tag_slot = (u8 *)((s32)tags + index);
                current_tag = *tag_slot;
            } while (current_tag != tag);
        }
        if (index <= 9) {
            register s32 value_offset asm("r0");
            register u8 *value_slot asm("r1");
            register s32 zero asm("r2");
            register s32 value asm("r0");

            value_offset = index << 1;
            value_slot = value_base;
            value_slot += 0x14;
            asm volatile("" : "+r"(value_slot));
            value_slot = (u8 *)((s32)value_slot + value_offset);
            asm volatile("" : "+r"(value_slot));
            zero = 0;
            value = *(s16 *)(value_slot + zero);
            if (value == 0) {
                return 1;
            }
            return value;
        }
    }
    return 0;
}
