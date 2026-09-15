#include "m2c_prelude.h"

extern u8 D_02034B4C[];
extern u8 D_0203ED28[];
extern s32 D_03000010;
extern s32 func_80BE488(s32, s32, s32);
extern s32 func_80E522C(s32, s32);
extern s32 func_80ECD5C(s32);

void sub_080BFB90(void)
{
    s32 outer;
    s32 group_stride;
    s32 outer_stride;
    s32 row4;
    u32 *flags_base;
    s32 group4;
    s32 next_outer;
    s32 next_group;
    s32 next_row;
    u32 *current_flags;
    s32 group_record_stride;
    s32 row_record_stride;
    u32 roll;
    register u32 group asm("r10");
    register u32 row asm("r9");
    register u32 slot asm("r8");
    u8 *entry;

    outer = 0;
    do {
        register s32 outer_twice asm("r0");

        group = 0;
        outer_twice = outer << 1;
        next_outer = outer + 1;
        {
            register s32 outer_reload asm("r1") = outer;

            asm volatile("" : "+r"(outer_reload));
            outer_stride = (outer_twice + outer_reload) << 4;
        }
        for (;;) {
            register s32 group_twice asm("r0");
            register s32 group_source asm("r1");
            register s32 row_zero asm("r2");
            register s32 next_group_carrier asm("r2");

            asm volatile("1:");
            row_zero = 0;
            asm volatile("" : "+r"(row_zero));
            row = row_zero;
            group_source = group;
            group_twice = group_source << 1;
            group4 = group_source << 2;
            next_group_carrier = group + 1;
            asm volatile("" : "+r"(next_group_carrier));
            next_group = next_group_carrier;
            group_stride = (group_twice + group) << 3;
            do {
                register u32 low0 asm("r0");
                register s32 group_reload asm("r1");
                register s32 row4_now asm("r2");
                register s32 flag_offset asm("r3");
                register u32 *row_flags asm("r1");
                register u8 *flags_base_reload asm("r2");

                low0 = row;
                row4_now = low0 << 2;
                group_reload = group_stride;
                asm volatile("" : "+r"(group_reload));
                flag_offset = row4_now + group_reload;
                low0 = outer_stride;
                row_flags = (u32 *)(flag_offset + low0);
                low0 = (u32)D_0203ED28;
                row_flags = (u32 *)((u32)row_flags + low0);
                *row_flags = 0;
                slot = 0;
                low0 = row;
                next_row = low0 + 1;
                row4 = row4_now;
                flags_base_reload = D_0203ED28;
                flag_offset += (u32)flags_base_reload;
                asm volatile("" : "+r"(flag_offset));
                flags_base = (u32 *)flag_offset;
                current_flags = row_flags;
                do {
                    register u8 *record_base asm("r1");
                    register s32 slot_offset asm("r0");

                    asm volatile("" : "+r"(group), "+r"(row));
                    group_record_stride = (((group4 + group) * 8) - group) << 7;
                    row_record_stride = (((row4 + row) * 8) - row) << 4;
                    record_base = D_02034B4C + group_record_stride + row_record_stride;
                    slot_offset = (slot * 0xC) + 0xE4;
                    entry = record_base + slot_offset;
                    if (outer == 0) {
                        if ((func_80BE488(group, row, 0) << 24) != 0)
                            *flags_base |= 1 << slot;
                    } else {
                        register s32 current_stat asm("r0");
                        register s32 threshold_value asm("r1");
                        register u32 threshold_address asm("r1");
                        register u8 *threshold_symbol asm("r2");

                        roll = (func_80ECD5C(D_03000010) * 100U) >> 15;
                        current_stat = *(s16 *)(entry + 8);
                        threshold_address = row_record_stride + group_record_stride;
                        threshold_symbol = D_02034B4C;
                        threshold_address += (u32)threshold_symbol;
                        threshold_address += 0xA6;
                        threshold_value = *(s16 *)threshold_address;
                        if ((s32)roll > func_80E522C(current_stat,
                                threshold_value + 100))
                            *current_flags |= 1 << slot;
                    }
                    slot = (u8)(slot + 1);
                } while (slot <= 0x1F);
                row = (u8)next_row;
            } while (row <= 5);
            asm volatile("" : "+g"(next_group));
            group = (u8)next_group;
            asm volatile(".macro bhi target\n\tbls 1b\n\t.endm\n\t"
                         ".macro b target\n\t.endm");
            switch (group) {
            case 0:
            case 1:
                continue;
            }
            break;
        }
        asm volatile(".purgem bhi\n\t.purgem b");
        asm volatile("" : "+g"(next_outer));
        outer = (u8)next_outer;
    } while ((u32)outer <= 3);
}
