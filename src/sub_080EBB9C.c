#include "m2c_prelude.h"

struct TimerStateEBB9C {
    u8 pad0[8];
    u8 mode;
    u8 pad9[2];
    s8 rate;
    u8 padC[4];
    s32 period;
    s32 scaled;
    s32 half_step;
};

s32 func_080ECD98(s32, s32);
void func_080EBD90(void);

void sub_080EBB9C(s32 arg0)
{
    register s32 input asm("r2") = arg0;
    struct TimerStateEBB9C *state;
    u32 mask;
    register u32 mode asm("r2");
    register s32 zero asm("r6");
    u32 period;
    s32 scaled;

    asm volatile("" : "+r"(input));
    state = *(struct TimerStateEBB9C **)0x03007FF0;
    mask = 0xF0;
    mask <<= 12;
    mask &= input;
    mode = mask >> 16;
    asm volatile("" : "+r"(mode));
    zero = 0;
    state->mode = mode;
    {
        register u16 *table asm("r1") = (u16 *)0x086A32E4;
        register u32 table_offset asm("r0");
        asm volatile("" : "+r"(table));
        table_offset = mode - 1;
        asm volatile("" : "+r"(table_offset));
        table_offset <<= 1;
        table_offset += (u32)table;
        period = *(u16 *)table_offset;
    }
    state->period = period;
    state->rate = func_080ECD98(0x630, period);
    scaled = func_080ECD98((0x91D1B * period) + 0x1388, 0x2710);
    state->scaled = scaled;
    state->half_step = (func_080ECD98(0x01000000, scaled) + 1) >> 1;

    *(volatile u16 *)0x04000102 = zero;
    {
        register volatile u16 *reload asm("r4") =
            (volatile u16 *)0x04000100;
        *reload = -func_080ECD98(0x44940, period);
    }
    func_080EBD90();

    {
        volatile u8 *vcount = (volatile u8 *)0x04000006;
        do {
        } while (*vcount == 0x9F);
    }
    {
        volatile u8 *vcount = (volatile u8 *)0x04000006;
        do {
        } while (*vcount != 0x9F);
    }
    *(volatile u16 *)0x04000102 = 0x80;
}
