#include "m2c_prelude.h"

extern void func_08094290(s32, s32);
extern void func_080942E0(s32);
extern u8 D_02031C98;
extern u8 D_02031C99;
extern u8 D_02031C9A[];
extern s32 D_03000054[];
extern u8 D_03000074;

void sub_080A8ED4(s32 arg0)
{
    u8 value;

    if ((arg0 << 24) != 0) {
        value = D_02031C98;
        if (value == 1) {
            s16 *interrupt = (s16 *)0x04000208;

            *interrupt = 0;
            func_08094290(2, 0x030060FC);
            *interrupt = value;
            D_02031C98 = 2;
        } else if (value == 3) {
            s16 *interrupt = (s16 *)0x04000208;

            *interrupt = 0;
            func_080942E0(2);
            D_03000074 &= 0xDF;
            *interrupt = 1;
            D_02031C98 = 0;
            return;
        }
        D_02031C99 ^= 1;
    }

    if (D_02031C98 == 2) {
        register u16 *display asm("r4") = (u16 *)0x04000014;
        register u8 *base asm("r3") = D_02031C9A;
        register u8 *toggle asm("r2") = &D_02031C99;
        u8 *second;

        asm volatile("" : "+r"(display), "+r"(base), "+r"(toggle));
        display[0] = *(u16 *)(base + *toggle * 0x280);
        display++;
        asm volatile("" : "+r"(display));
        {
            register u32 selected asm("r1") = *toggle;
            register u32 offset asm("r0");
            register u8 *second_view asm("r5");

            offset = selected << 2;
            offset += selected;
            offset <<= 7;
            second_view = base + 2;
            second = second_view;
            display[0] = *(u16 *)(offset + (u32)second_view);
        }
        {
            register s32 *state asm("r4") = D_03000054;

            state[2] = *(s16 *)(base + *toggle * 0x280) << 8;
            state[3] = *(s16 *)(second + *toggle * 0x280) << 8;
        }
    }
}
