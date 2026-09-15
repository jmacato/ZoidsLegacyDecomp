#include "m2c_prelude.h"
M2C_UNK func_80ECBBC(s32, s32, s32);
s32 func_80ECD68(s32, s32, s32, s32);

s32 sub_080ECCE4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r3;
    u32 var_r7;

    var_r3 = arg3;
    for (var_r7 = 0; var_r7 <= 2U; var_r7 = (u32) (u8) (var_r7 + 1)) {
        func_80ECBBC(arg0, arg1, arg2);
        var_r3 = func_80ECD68(arg0, arg1, arg2, *(s32 *)0x03007754);
        if (var_r3 == 0) {
            break;
        }
    }
    return var_r3;
}
