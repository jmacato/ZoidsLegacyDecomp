#include "m2c_prelude.h"

s32 sub_080929C0(s32 arg0, s32 arg1) {
    s32 temp_r2;
    s32 temp_r3;
    s32 var_r0;
    s32 var_r4;
    s32 var_r5;

    var_r5 = arg0;
    if (arg0 < 0) {
        var_r5 = 0 - arg0;
    }
    var_r4 = arg1;
    if (arg1 < 0) {
        var_r4 = 0 - arg1;
    }
    temp_r2 = var_r5 >> 0xC;
    temp_r3 = var_r4 >> 0xC;
    var_r5 &= 0xFFF;
    var_r4 &= 0xFFF;
    var_r0 = ((temp_r2 * temp_r3) << 0xC) +
             (temp_r2 * var_r4) +
             (var_r5 * temp_r3) +
             ((s32)(var_r5 * var_r4) >> 0xC);
    if (arg0 < 0) {
        goto first_negative;
    }
    if (arg1 >= 0) {
        goto done;
    }
    goto negate;
first_negative:
    if (arg1 < 0) {
        goto done;
    }
negate:
    var_r0 = 0 - var_r0;
done:
    return var_r0;
}
