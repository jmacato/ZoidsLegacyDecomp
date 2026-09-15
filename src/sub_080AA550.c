#include "m2c_prelude.h"
extern u8 D_02030668[];
void sub_080AA550(s32 arg0) {
    register s32 temp_r4 asm("r4");
    register s32 r5 asm("r5");
    register s32 r6 asm("r6");
    register s32 var_r1 asm("r1");
    register s32 w asm("r0");
    s32 base, temp_r3, t;
    u8 var_r2;
    s32 temp_r0;
    t = arg0 << 0x18;
    var_r1 = 0;
    temp_r4 = (u32)t >> 0x10;
    base = (s32)D_02030668;
loop_1:
    var_r2 = 0;
    temp_r3 = var_r1 + 1;
    r6 = var_r1 * 8;
    r5 = temp_r3 * 8;
    do {
        temp_r0 = var_r2 * 2;
        *(u16 *)(temp_r0 + r6 + temp_r4 + base) = *(u16 *)(temp_r0 + r5 + temp_r4 + base);
        var_r2 = var_r2 + 1;
    } while ((u32) var_r2 <= 3U);
    if (*(u16 *)(temp_r3 * 8 + temp_r4 + base) != 0) {
        w = temp_r3 << 0x18;
        var_r1 = (u32)w >> 0x18;
        if ((u32) var_r1 <= 0x1EU) {
            goto loop_1;
        }
    }
}
