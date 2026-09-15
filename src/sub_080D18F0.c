#include "m2c_prelude.h"

extern void func_080ECD34(s32, s32);
extern void func_0809AC30(s32, s32, u8, s32);
extern volatile u16 D_0300004C;
extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;
extern volatile u8 D_02034860;
extern volatile u8 D_02033F36;

struct D18F0State {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

void sub_080D18F0(void)
{
    register u8 *state_base asm("r4");
    register u32 state asm("r1");

    {
        register u8 *state_init asm("r0") = (u8 *)&D_02034860;

        state = *state_init;
        state_base = state_init;
    }

    if (state == 0) {
        return;
    }

    if (state == 1) {
        D_0300004C |= 0x200;
        *(u16 *)0x0400000A = 0x170B;
        {
            struct D18F0State *work = (struct D18F0State *)0x03000054;

            work->unkC = 0;
            work->unk8 = 0;
        }
        func_080ECD34(0x08108C78, 0x0600A740);
        func_080ECD34(0x08108DA8, 0x05000100);
        func_0809AC30(0x08108DD0, 0x17, D_02033F36, 0x02002880);
        D_0300004E = 0x442;
        D_03000050 = 0x1000;
        *state_base += 1;
        return;
    }

    if (state <= 0x20) {
        if (state != 0x20) {
            register volatile u16 *fade asm("r3") = &D_03000050;
            register u32 current asm("r2") = *state_base;
            register u32 remaining asm("r0") = 0x20 - current;
            register u32 sign asm("r1") = remaining >> 31;

            remaining += sign;
            remaining = (s32)remaining >> 1;
            remaining <<= 8;
            current >>= 1;
            current |= remaining;
            *fade = current;
        } else {
            D_0300004E = 0x740;
            D_03000050 = 0x810;
            D_0300004C &= 0xFBFF;
        }
        *state_base += 1;
    }

    if (D_02033F36 == 0) {
        ((struct D18F0State *)0x03000054)->unk8 += 0xFFFFF000;
    } else {
        ((struct D18F0State *)0x03000054)->unk8 += 0x1000;
    }
}
