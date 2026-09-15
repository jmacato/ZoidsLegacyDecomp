#include "m2c_prelude.h"

void func_0809F850(void);

void sub_0809FCB0(void) {
    register u32 outer asm("r2");
    register u8 *secondary_flag asm("r3");
    register s32 *state asm("r4");
    register u8 *third_flag asm("r6");
    u8 *fourth_flag;

    *(u8 *)0x02030664 = 0;
    outer = 0;
    secondary_flag = (u8 *)0x02030666;
    asm volatile("" : "+r"(secondary_flag));
    state = (s32 *)0x02031744;
    asm volatile("" : "+r"(state));
    third_flag = (u8 *)0x02031749;
    asm volatile("" : "+r"(third_flag));
    fourth_flag = (u8 *)0x020316F6;
    asm volatile("" : "+r"(fourth_flag));
    {
        register s32 zero asm("r0");
        register s32 *entries asm("r1");

        zero = 0;
        entries = (s32 *)0x020314C4;
        do {
            *entries++ = zero;
            outer += 1;
        } while (outer <= 69);
    }

    *secondary_flag = 0;
    *state = 0;
    outer = 0;
    {
        register u8 *grid asm("r5");
        register s32 *row_flags asm("r4");
        register s32 zero asm("r3");

        grid = (u8 *)0x02030668;
        asm volatile("" : "+r"(grid));
        zero = 0;
        row_flags = (s32 *)0x02031468;
        asm volatile("" : "+r"(row_flags));
        do {
            register u32 inner asm("r1");
            register s32 row_offset asm("r0");
            register u8 *entry asm("r0");

            inner = 0;
            asm volatile("" : "+r"(grid));
            row_offset = outer << 8;
            entry = (u8 *)(row_offset + (s32)grid);
            do {
                *(s16 *)entry = zero;
                entry += 8;
                inner += 1;
            } while (inner <= 31);
            *row_flags++ = zero;
            outer += 1;
        } while (outer <= 13);
    }

    *third_flag = 0;
    *fourth_flag = 0;
    outer = 0;
    {
        register u8 *available asm("r3");
        register s32 one asm("r1");

        available = (u8 *)0x020316FC;
        one = 1;
        do {
            register u8 *slot asm("r0");

            slot = (u8 *)(outer + (s32)available);
            *slot = one;
            outer += 1;
        } while (outer <= 69);
    }
    func_0809F850();
}
