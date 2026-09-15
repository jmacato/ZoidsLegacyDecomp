#include "m2c_prelude.h"
extern u8 D_0203725F[];

void sub_080C02B4(u8 arg0, u8 arg1) {
    register int mask asm("r5");
    u8 *base;
    u8 *base1;
    s32 i;

    i = 0;
    base = D_0203725F;
    base1 = base + 1;
    mask = 0xff;
    do {
        s32 o = i * 2;
        u8 *pa = (u8 *)(o + (int)base);
        if (*pa == arg0) {
            u8 *pb = (u8 *)(o + (int)base1);
            if (*pb == arg1) {
                *pa = *pa | mask;
                *pb = *pb | mask;
            }
        }
        i = (u8)(i + 1);
    } while ((u32)i <= 0x23);
}
