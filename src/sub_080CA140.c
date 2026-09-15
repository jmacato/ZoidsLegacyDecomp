#include "m2c_prelude.h"
extern s32 *D_02032F64[];

s32 sub_080CA140(void) {
    s32 *temp_r0;
    s32 *temp_r1;
    register s32 var_r0 asm("r0");
    u8 var_r2;

    var_r2 = 0;
    temp_r1 = D_02032F64[0];
    if (temp_r1 == 0) {
        goto loop_3;
    }
    var_r0 = *temp_r1;
    goto block_6;
loop_3:
    var_r2 += 1;
    if ((u32) var_r2 > 5U) {
        goto block_7;
    }
    temp_r0 = D_02032F64[var_r2];
    if (temp_r0 == 0) {
        goto loop_3;
    }
    var_r0 = *temp_r0;
block_6:
    var_r0 &= 1;
    if (var_r0 == 0) {
        goto loop_3;
    }
block_7:
    if (var_r2 == 6) {
        return 1;
    }
    return 0;
}
