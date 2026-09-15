#include "m2c_prelude.h"

extern u8 D_0203EFA8;
extern u8 D_0203EFA9[];
extern u8 D_0203EF70[];
extern u8 D_0203EF78[];

u8 sub_080CA570(s32 arg0, s32 arg1)
{
    register u32 row asm("r5");
    arg0 <<= 24;
    row = (u32)arg0 >> 24;
    arg1 <<= 24;
    arg1 = (u32)arg1 >> 24;
    if (arg1 != 0xFF) {
        register u8 *count_slot asm("r4");
        register u8 *count_base asm("r0");
        u32 count;

        count_base = D_0203EFA9;
        count_slot = (u8 *)(row + (s32)count_base);
        count = *count_slot - 1;
        *count_slot = count;
        count = (u8)count;
        if (count != 0) {
            register u32 index asm("r3");

            index = arg1;
            if (index < count) {
                register u8 *rows asm("r6");
                register u32 triple asm("r0");
                register u32 row_offset asm("r2");
                register u32 next_row_byte asm("r5");

                rows = D_0203EF78;
                triple = row * 2;
                triple += row;
                row_offset = triple * 2;
                next_row_byte = row_offset + 1;
                do {
                    register u32 next asm("r0");
                    register u8 *destination asm("r1");
                    register u8 *source asm("r0");

                    destination = (u8 *)(index + row_offset);
                    destination += (s32)rows;
                    source = (u8 *)(index + next_row_byte);
                    source += (s32)rows;
                    *destination = *source;
                    next = index + 1;
                    index = (u8)next;
                } while (index < *count_slot);
            }
            return 1;
        }
    }

    {
        register u8 *count_slot asm("r9");
        register u8 *count_ptr asm("r1");
        u32 count;
        register u32 index asm("r3");

        count_ptr = &D_0203EFA8;
        count = *count_ptr - 1;
        *count_ptr = count;
        index = row;
        count = (u8)count;
        count_slot = count_ptr;
        if (index < count) {
            register u8 *outer asm("r8");
            u8 *rows;
            register u8 *counts asm("ip");
            register u8 *outer_load asm("r1");
            register u8 *counts_load asm("r2");

            outer_load = D_0203EF70;
            asm volatile("" : "+r"(outer_load));
            outer = outer_load;
            rows = D_0203EF78;
            counts_load = D_0203EFA9;
            asm volatile("" : "+r"(counts_load));
            counts = counts_load;
            do {
                register u32 next asm("r1");
                register u32 inner asm("r2");
                register u32 current_offset asm("r6");
                register u32 next_offset asm("r5");
                register u32 triple asm("r0");
                register u32 next_index asm("r4");

                {
                    register u8 *outer_view asm("r4");
                    register u8 *destination asm("r2");
                    register u8 *source asm("r0");

                    outer_view = outer;
                    destination = (u8 *)(index + (s32)outer_view);
                    next = index + 1;
                    source = (u8 *)(next + (s32)outer_view);
                    *destination = *source;
                }
                inner = 0;
                {
                    next_index = next;
                    asm volatile("" : "+r"(next_index));

                    triple = index * 2;
                    triple += index;
                    current_offset = triple * 2;
                    triple = next_index * 2;
                    triple += next_index;
                    next_offset = triple * 2;
                }
                do {
                    register u8 *destination asm("r1");
                    register u8 *source asm("r0");
                    register u32 next_inner asm("r0");

                    destination = (u8 *)(inner + current_offset);
                    destination += (s32)rows;
                    source = (u8 *)(inner + next_offset);
                    source += (s32)rows;
                    *destination = *source;
                    next_inner = inner + 1;
                    inner = (u8)next_inner;
                } while (inner <= 5);
                {
                    register u8 *base asm("r0") = counts;
                    register u8 *destination asm("r1") = (u8 *)(index + (s32)base);
                    register u8 *source asm("r0") = (u8 *)(next_index + (s32)base);
                    register u32 normalized asm("r0");

                    *destination = *source;
                    normalized = next_index << 24;
                    index = normalized >> 24;
                }
            } while (index < ({
                register u8 *check asm("r1") = count_slot;
                asm volatile("" : "+r"(check));
                *check;
            }));
        }
    }
    return 0;
}
