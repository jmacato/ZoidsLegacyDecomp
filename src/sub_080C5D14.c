#include "m2c_prelude.h"

void sub_080C5D14(void) {
    s32 outer;
    u8 middle;
    u8 inner;
    s32 middle_stride;
    s32 middle_base;
    s32 record_offset;
    s32 entry_offset;
    s32 next_middle;
    register s32 outer_step asm("r10");
    register s32 field_a asm("r9");
    register s32 field_b asm("r8");
    register s32 zero asm("r6");
    register s32 next_outer asm("r12");
    register s32 outer_stride asm("r4");

    outer = 0;
    {
        register s32 setup asm("r1");

        setup = 0x1218;
        outer_step = setup;
    }
    zero = 0;
    {
        register s32 setup asm("r2");

        setup = 0x7C30;
        asm volatile("" : "+r"(setup));
        field_a = setup;
    }
    {
        register s32 setup asm("r5");

        setup = 0x7DB0;
        asm volatile("" : "+r"(setup));
        field_b = setup;
    }
    do {
        middle = 0;
        {
            register s32 successor asm("r7");

            successor = outer + 1;
            next_outer = successor;
        }
        outer_stride = outer_step;
        outer_stride *= outer;
        do {
            middle_stride = middle << 1;
            middle_stride += middle;
            middle_stride <<= 6;
            middle_stride += middle;
            middle_stride <<= 2;
            record_offset = middle_stride + outer_stride;
            record_offset += 0x02034B4C;
            *(u16 *)(record_offset + 0x7C2A) = zero;
            *(u16 *)(record_offset + 0x7C28) = zero;
            inner = 0;
            next_middle = middle + 1;
            middle_base = middle_stride;
            do {
                entry_offset = inner << 1;
                entry_offset += inner;
                entry_offset <<= 2;
                entry_offset += middle_base;
                entry_offset += outer_stride;
                entry_offset += 0x02034B4C;
                *(u16 *)(entry_offset + field_a) = zero;
                *(u16 *)(entry_offset + field_b) = zero;
                inner += 1;
            } while ((u32)inner <= 0x1F);
            middle = (u8)next_middle;
        } while ((u32)middle <= 5);
        {
            register s32 tail_outer asm("r1");
            s32 outer_shift;

            tail_outer = next_outer;
            outer_shift = tail_outer << 24;
            outer = (u32)outer_shift >> 24;
        }
    } while ((u32)outer <= 1);
}
