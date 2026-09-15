#include "m2c_prelude.h"

void func_80ECD2C(void *, void *, void *);
extern u8 D_080EC901, D_080EB605, D_080EB619, D_080ECA59, D_080EB59D, D_080EBB9D,
    D_080EB329, D_080EBF65, D_080EC02D, D_080EC241, D_080EC189, D_080EC0E1, D_zero;

void sub_080EB98C(void *arg0) {
    void *temp_r4;
    s32 temp_r6;
    s32 local;
    register s32 z asm("r1");
    register s32 sv asm("r0");
    u8 *p;
    register s16 *reg80 asm("r3");
    s32 *p74B0;
    u8 *p1;

    *(s16 *)0x04000084 = 0x8F;
    reg80 = (s16 *)0x04000080;
    *reg80 = 0;
    p = (u8 *)0x04000063;
    p[0] = 8;
    p += 6;
    p[0] = 8;
    p += 0x10;
    p[0] = 8;
    p -= 0x14;
    p[0] = 0x80;
    p += 8;
    p[0] = 0x80;
    p += 0x10;
    p[0] = 0x80;
    p -= 0xD;
    p[0] = 0;
    *(u8 *)reg80 = 0x77;
    temp_r4 = *(void **)0x03007FF0;
    temp_r6 = *(s32 *)temp_r4;
    if (temp_r6 == 0x68736D53) {
        *(s32 *)temp_r4 = temp_r6 + 1;
        p74B0 = (s32 *)0x030074B0;
        p74B0[0x20 / 4] = (s32) &D_080EC901;
        p74B0[0x44 / 4] = (s32) &D_080EB605;
        p74B0[0x4C / 4] = (s32) &D_080EB619;
        p74B0[0x70 / 4] = (s32) &D_080ECA59;
        p74B0[0x74 / 4] = (s32) &D_080EB59D;
        p74B0[0x78 / 4] = (s32) &D_080EBB9D;
        p74B0[0x7C / 4] = (s32) &D_080EB329;
        p74B0[0x80 / 4] = (s32) &D_080EBF65;
        p74B0[0x84 / 4] = (s32) &D_080EC02D;
        *(void **)((u8 *)temp_r4 + 0x1C) = arg0;
        *(s32 *)((u8 *)temp_r4 + 0x28) = (s32) &D_080EC241;
        *(s32 *)((u8 *)temp_r4 + 0x2C) = (s32) &D_080EC189;
        *(s32 *)((u8 *)temp_r4 + 0x30) = (s32) &D_080EC0E1;
        sv = (s32) &D_zero;
        z = 0;
        *(s8 *)((u8 *)temp_r4 + 0xC) = sv;
        local = z;
        func_80ECD2C(&local, arg0, (void *)0x05000040);
        *(s8 *)((u8 *)arg0 + 1) = 1;
        *(s8 *)((u8 *)arg0 + 0x1C) = 0x11;
        p1 = (u8 *)arg0 + 0x41;
        *p1 = 2;
        p1 += 0x1B;
        *p1 = 0x22;
        p1 += 0x25;
        *p1 = 3;
        p1 += 0x1B;
        *p1 = 0x44;
        p1 += 0x24;
        p1[1] = 4;
        p1[0x1C] = 0x88;
        *(s32 *)temp_r4 = temp_r6;
    }
}

/*
 * This wrapper calls a BIOS service with swi 0x2A.
 * C has no expression for this software interrupt.
 */
__attribute__((naked)) void sub_080EBAA4(void) {
    asm(".syntax unified\n"
        "swi 0x2a\n"
        "bx lr\n"
        ".syntax divided");
}
