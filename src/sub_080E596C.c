#include "m2c_prelude.h"
s16 func_80ECD98(s32, s16);                            /* extern */

void sub_080E596C(s16 arg0, s16 arg1, void *arg2) {
    s16 temp_r2;
    s16 temp_r3;

    temp_r3 = arg0;
    temp_r2 = arg1;
    if ((s32) temp_r3 > (s32) temp_r2) {
        if ((s32) (temp_r3 - temp_r2) < (s32) temp_r2) {
            M2C_FIELD(arg2, s16 *, 0xC) = func_80ECD98(M2C_FIELD(arg2, s16 *, 0xC) * ((temp_r2 * 2) - temp_r3), temp_r2);
        } else {
            M2C_FIELD(arg2, s16 *, 0xC) = 0;
        }
    }
}
