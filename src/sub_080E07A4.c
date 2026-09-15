#include "m2c_prelude.h"
s32 func_080ECD5C(s32);

void sub_080E07A4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    {
        s32 temp_r0;
        s32 temp_r2;
        s32 *temp_r3;

        temp_r0 = func_080ECD5C(*(s32 *)0x03000010);
        temp_r3 = &M2C_FIELD(arg0, s32 *, 0x90);
        temp_r2 = M2C_FIELD(arg0, s32 *, 8);
        temp_r2 -= 0x10;
        temp_r2 += (u32)(temp_r0 * 0x21) >> 0xF;
        *temp_r3 = temp_r2;
    }
}
