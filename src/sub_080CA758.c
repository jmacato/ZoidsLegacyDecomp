#include "m2c_prelude.h"

void func_080CA570(u8, u8);

void sub_080CA758(void)
{
    u32 index;

    index = 0;
    if (index < *(u8 *)0x0203EFA8) {
        u8 *base;
        u8 **active_slot;

        base = (u8 *)0x02034B4C;
        active_slot = (u8 **)(base + 0x27A8);
        do {
            register u8 *index_table asm("r0");
            register s32 record_index asm("r1");
            register s32 record_offset asm("r2");
            register s32 record_stride asm("r0");
            register s32 row_base_offset asm("r1");
            register u8 *row_slot asm("r0");
            register s32 row asm("r1");
            register s32 row_offset asm("r0");
            register s32 record_base_offset asm("r3");
            register u8 *record_base asm("r1");
            register u8 *record asm("r2");
            register s32 active_value asm("r3");
            register s32 base_value asm("r0");
            register s32 record_value asm("r1");
            register u32 next_index asm("r0");

            index_table = (u8 *)0x0203EF70;
            asm volatile("" : "+r"(index_table));
            index_table = (u8 *)(index + (s32)index_table);
            record_index = *index_table;
            record_stride = 0xA8C;
            record_offset = record_index;
            record_offset *= record_stride;
            row_base_offset = 0xA1AF;
            row_slot = base + row_base_offset;
            row = *row_slot;
            row_offset = row << 3;
            row_offset -= row;
            row_offset <<= 5;
            row_offset += row;
            row_offset <<= 2;
            record_base_offset = 0x27C8;
            record_base = base + record_base_offset;
            row_offset += (s32)record_base;
            record_offset += row_offset;
            record = (u8 *)record_offset;

            active_value = M2C_FIELD(*active_slot, s16 *, 8);
            base_value = M2C_FIELD((void *)0x0203EFB2, s16 *, 0);
            record_value = M2C_FIELD(record, s16 *, 8);
            base_value += record_value;
            if (active_value < base_value) {
                func_080CA570(index, 0xFF);
                next_index = index - 1;
                index = (u8)next_index;
            }
            index = (u8)(index + 1);
        } while (index < *(u8 *)0x0203EFA8);
    }
}
