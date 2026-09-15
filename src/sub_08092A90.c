#include "m2c_prelude.h"
extern u16 D_080ED184[];

s32 sub_08092A90(s32 arg0) {
    s32 var_r0;
    u16 temp_r0;
    u16 var_r0_2;
    register u32 temp_r2 asm("r2");
    register u32 r1v asm("r1");
    u32 v;

    v = arg0 << 0x10;
    r1v = 0xFF0000;
    r1v &= v;
    temp_r2 = r1v >> 0x10;
    r1v = temp_r2;
    if ((s32) (0x7F & r1v) <= 0x3F) {
        var_r0_2 = 0x3F & r1v;
    } else {
        r1v &= 0x3F;
        var_r0_2 = 0x40 - r1v;
    }
    temp_r0 = D_080ED184[(s32) (var_r0_2 << 0x10) >> 0x10];
    if ((s32) temp_r2 <= 0x7F) {
        var_r0 = temp_r0 << 0x10;
    } else {
        var_r0 = 0 - (temp_r0 << 0x10);
    }
    return var_r0 >> 0x10;
}
