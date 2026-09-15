#include "m2c_prelude.h"
M2C_UNK func_08095114(void *);                      /* extern */
s32 func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32); /* extern */
M2C_UNK func_080D2790(s32);                         /* extern */

void sub_080DB17C(void *arg0) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x8C);
    if (temp_r1 == 0) {
        M2C_FIELD(arg0, s32 *, 0xC) = func_080D2450(arg0, 0, 0, (s16) (M2C_FIELD(arg0, s32 *, 4) + 0x80), (s32) M2C_FIELD(arg0, s16 *, 8), temp_r1, temp_r1, 1);
        func_080D2790(0);
        M2C_FIELD(arg0, s32 *, 0x8C) = (s32) (M2C_FIELD(arg0, s32 *, 0x8C) + 1);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
        func_08095114(arg0);
    }
}
