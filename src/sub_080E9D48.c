#include "m2c_prelude.h"
extern u8 D_0203ED02[];

void sub_080E9D48(void) {
    u8 var_r1;
    u8 var_r4;
    u8 temp_r3;
    u8 *base;
    u8 *other;
    s32 offset;

    var_r1 = 0;
    base = D_0203ED02;
    other = base + 6;
    do {
        var_r4 = 0;
        do {
            offset = var_r4 + var_r1 * 0xC;
            temp_r3 = *(u8 *)((s32)offset + (s32)base);
            *(u8 *)((s32)offset + (s32)base) = *(u8 *)((s32)offset + (s32)other);
            *(u8 *)((s32)offset + (s32)other) = temp_r3;
            var_r4 += 1;
        } while ((u32)var_r4 <= 5U);
        var_r1 += 1;
    } while ((u32)var_r1 <= 2U);
}
