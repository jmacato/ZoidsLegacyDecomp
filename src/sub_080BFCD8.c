#include "m2c_prelude.h"
extern u8 D_0203ED28[];

void sub_080BFCD8(void) {
    u8 outer;
    u8 inner;
    u8 saved;
    u32 offset;
    u32 *left;
    u32 *right;
    u8 *base;
    u8 *other;

    outer = 0;
    base = D_0203ED28;
    other = base + 24;
    do {
        inner = 0;
        do {
            offset = inner * 4 + outer * 0x30;
            left = (u32 *)(offset + (u32)base);
            saved = *(u8 *)left;
            right = (u32 *)(offset + (u32)other);
            *left = *right;
            *right = saved;
            inner += 1;
        } while (inner <= 5);
        outer += 1;
    } while (outer <= 3);
}
