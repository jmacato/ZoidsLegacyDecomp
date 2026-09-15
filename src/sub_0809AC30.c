#include "m2c_prelude.h"
void func_80ECD34();
void func_80ECD38();

void sub_0809AC30(s32 arg0, u8 arg1, s32 arg2, s32 arg3) {
    s16 *var_r1;
    u8 var_r0, var_r2;
    u8 temp_r4 = arg1;

    if ((arg2 << 0x18) == 0) {
        func_80ECD34(arg0, (temp_r4 << 0xB) + 0x06000000);
        return;
    }
    func_80ECD38(arg0, arg3);
    var_r1 = (s16 *)((temp_r4 << 0xB) + 0x06000000);
    var_r0 = 0;
    do {
        var_r2 = 0;
        do {
            *var_r1 = *(s16 *)((var_r0 << 6) + (((0x1F - var_r2) * 2) + arg3)) ^ 0x400;
            var_r1 += 1;
            var_r2 += 1;
        } while ((u32)var_r2 <= 0x1F);
        var_r0 += 1;
    } while ((u32)var_r0 <= 0x1F);
}
