#include "m2c_prelude.h"
s32 func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32); /* extern */

void sub_080D27A8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = func_080D2450(arg0, 0, 0, M2C_FIELD(arg0, s16 *, 4), (s32) M2C_FIELD(arg0, s16 *, 8), 0x400, 0, 0);
}
