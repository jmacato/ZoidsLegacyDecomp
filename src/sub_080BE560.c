#include "m2c_prelude.h"
extern u8 D_02034B4C[];

void sub_080BE560(u8 arg0, u8 arg1) {
    u8 i;
    s8 *base;
    s32 t1, t0;
    i = 0;
    base = (s8 *)D_02034B4C;
    t1 = arg1 * 0x270;
    t0 = arg0 * 0x1380;
    do {
        *(s16 *)((i * 0xC) + t1 + t0 + (s32)base + 0xE8) = 0;
        i += 1;
    } while ((u32)i <= 0x1F);
}

void sub_080BE5A8(u8 arg0, u8 arg1) {
    u8 i;
    s8 *base;
    s32 qa, qb, kb;
    register s32 zero asm("r0");
    i = 0;
    qa = arg0 * 0x1380;
    qb = arg1 * 0x270;
    kb = 0x02034B4C;
    base = (s8 *)(qa + (qb + kb));
    do {
        u16 *p = (u16 *)(base + ((i * 0xC) + 0xE4));
        if (p[2] & 0x1000) {
            zero = 0;
            p[2] = zero;
        }
        i += 1;
    } while ((u32)i <= 0x1F);
}
