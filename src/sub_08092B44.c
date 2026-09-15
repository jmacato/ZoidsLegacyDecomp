#include "m2c_prelude.h"
M2C_UNK func_080ECD2C(s32, s32, u16);
void sub_08092B44(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r5;
    s32 var_r6;
    u16 temp_r2;
    u16 temp_r7;
    u16 var_r4;
    var_r6 = arg0;
    var_r5 = arg1;
    arg2 = arg2 << 16;
    arg2 = (u32)arg2 >> 16;
    temp_r2 = arg2;
    arg3 = arg3 << 16;
    arg3 = (u32)arg3 >> 16;
    temp_r7 = arg3;
    var_r4 = 0;
    if (var_r4 < temp_r7) do {
        func_080ECD2C(var_r5, var_r6, temp_r2);
        var_r5 += temp_r2 * 2;
        var_r6 += 0x40;
        var_r4++;
    } while (var_r4 < temp_r7);
}
