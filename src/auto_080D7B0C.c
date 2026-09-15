#include "m2c_prelude.h"
s32 func_080ECD5C(s32);                             /* extern */

void sub_080D7B0C(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, u32 *, 0x94) = (u32) ((u32) (func_080ECD5C(*(s32 *)0x03000010) * 0x21) >> 0xF);
}
