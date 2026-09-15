#include "m2c_prelude.h"
u8 sub_08098B58(u8 *arg0) {
    u8 *var_r4;
    u8 temp_r0;
    u8 var_r5;

    var_r4 = arg0;
    var_r5 = 0;
    while ((temp_r0 = *var_r4) != 0) {
        if ((u32) temp_r0 <= 0x1FU) {
            switch (*var_r4) {
            case 1:
                var_r4 += 1;
                goto block_11;
            case 2:
                var_r4 += 2;
                goto block_11;
            case 3:
                sub_08098B58((u8 *)0x02021774);
            default:
block_11:
                var_r4 += 1;
                break;
            }
        } else {
            if ((u32) (u8) (temp_r0 + 0x80) <= 0x1FU) {
                var_r4 += 2;
            } else {
                var_r4 += 1;
            }
            var_r5 += 1;
        }
    }
    return var_r5;
}
