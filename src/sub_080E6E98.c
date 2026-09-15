#include "m2c_prelude.h"
extern u8 D_02027378[];
extern u8 D_off_0E78[];
void func_80E6020(u32);
void func_80E700C(u8);
void sub_080E6E98(u8 arg0) {
    s32 temp_r0;
    s32 base;
    u8 var_r2;
    u8 temp_r5;
    u8 *temp_r4;
    temp_r5 = arg0;
    temp_r0 = temp_r5 << 6;
    base = (s32)D_02027378;
    temp_r4 = (u8 *)(temp_r0 + base);
    if (*(u16 *)(temp_r4 + 2) & 4) {
        var_r2 = 0;
        base += (s32)D_off_0E78;
        goto test;
inc:
        var_r2 = var_r2 + 1;
test:
        if (var_r2 > 5) goto after;
        if (temp_r4[1] != *(u8 *)(var_r2 + base)) goto inc;
        func_80E6020(var_r2);
    }
after:
    func_80E700C(temp_r5);
    *(s8 *)temp_r4 = 0;
}
