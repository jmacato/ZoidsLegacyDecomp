#include "m2c_prelude.h"

extern volatile u16 D_0300004C;
extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;
extern s32 D_03000054[];
extern volatile u8 D_02034861;
extern volatile u8 D_02033F36;

void sub_080D1A44(void)
{
    u8 *state_base;
    u32 state;

    {
        register u8 *state_init asm("r0") = (u8 *)&D_02034861;

        state = *state_init;
        state_base = state_init;
    }

    if (state != 0) {
        if (state == 1) {
            D_0300004C |= 0x200;
            *(u16 *)0x0400000A = *(u16 *)0x04000008;
            D_03000054[2] = D_03000054[0];
            D_03000054[3] = D_03000054[1];
            D_0300004E = 0x641;
        }

        {
            u32 phase = *state_base;

            if (phase <= 0x40) {
                if (phase <= 0x20) {
                    if (phase != 0x20) {
                        volatile u16 *fade = &D_03000050;
                        u32 blend = *(volatile u8 *)state_base;

                        blend >>= 1;
                        blend <<= 8;
                        blend |= 0x10;
                        *fade = blend;
                    }
                } else {
                    if (phase != 0x40) {
                        volatile u16 *fade = &D_03000050;
                        register u32 remaining asm("r0") =
                            0x40 - *(volatile u8 *)state_base;
                        u32 sign = remaining >> 31;

                        remaining += sign;
                        remaining = (s32)remaining >> 1;
                        remaining <<= 8;
                        remaining |= 0x10;
                        *fade = remaining;
                    } else {
                        D_0300004E = 0x740;
                        D_03000050 = 0x810;
                        D_0300004C &= 0xFDFF;
                    }
                    if (D_02033F36 == 0) {
                        if (D_03000054[2] > -0x10000) {
                            D_03000054[2] += -0x800;
                        }
                    } else {
                        if (D_03000054[2] <= 0xFFFF) {
                            D_03000054[2] += 0x800;
                        }
                    }
                }

                *state_base += 1;
            }
        }
    }
}
