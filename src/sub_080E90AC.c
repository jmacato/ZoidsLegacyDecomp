#include "m2c_prelude.h"

struct Item {
    u16 field0;
    u16 flags;
    u32 data;
    u8 field8;
    u8 type;
    u8 rest[14];
};

s32 func_080BEE04(void *, s32, s32, s32);

void sub_080E90AC(s32 arg0, s32 arg1) {
    register u32 row asm("r6");
    register u32 column asm("r5");
    u8 *grid;
    u8 index;
    register s32 row_offset asm("r1");
    register s32 column_offset asm("r0");
    register u8 *grid_base asm("r2");

    arg0 <<= 24;
    row = (u32)arg0 >> 24;
    arg1 <<= 24;
    column = (u32)arg1 >> 24;

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
    grid_base = (u8 *)0x02034B4C;
    column_offset += (s32)grid_base;
    grid = (u8 *)(row_offset + column_offset);

    index = 0;
    do {
        register s32 slot_offset asm("r0");
        register u8 *slot asm("r0");
        register u8 *slot_value asm("r1");
        register s32 item_id asm("r0");

        slot_offset = index << 2;
        slot = (u8 *)((s32)grid + slot_offset);
        asm volatile("" : "+r"(slot));
        slot_value = slot;
        slot_value += 0x52;
        item_id = *(u16 *)slot_value;
        if (item_id != 0) {
            register s32 item_copy asm("r1");
            register s32 item_offset asm("r0");
            register struct Item *item_base asm("r1");
            register struct Item *item asm("r2");
            register s32 flags asm("r1");
            register s32 masked asm("r0");

            item_copy = item_id;
            item_offset = item_copy << 1;
            item_offset += item_copy;
            item_offset <<= 3;
            item_base = (struct Item *)0x087B2524;
            item = (struct Item *)(item_offset + (s32)item_base);
            flags = item->flags;
            masked = 7;
            masked &= flags;
            if (masked == 3 && item->type == 6) {
                /* This local occupies the callback's fifth ABI argument slot. */
                volatile s32 callback_type;
                register void *call_item asm("r0");
                register u32 call_row asm("r1");
                register u32 call_column asm("r2");
                register u32 call_index asm("r3");

                callback_type = 1;
                call_item = item;
                asm volatile("" : "+r"(call_item));
                call_row = row;
                asm volatile("" : "+r"(call_row));
                call_column = column;
                asm volatile("" : "+r"(call_column));
                call_index = index;
                asm volatile("" : "+r"(call_index));
                func_080BEE04(call_item, call_row, call_column, call_index);
            }
        }
        index = (u8)(index + 1);
    } while (index <= 7);
}
