#include "m2c_prelude.h"
s32 func_080ECD5C(s32);

void sub_080DDF24(void *arg0) {
    s32 temp_r1;

    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = (s32)((M2C_FIELD(arg0, s32 *, 4) + ((u32)(func_080ECD5C(*(s32 *)0x03000010) * 0x41) >> 0xF)) - 0x20);
    {
        s32 temp_r0;
        s32 temp_r2;
        s32 *temp_r3;

        temp_r0 = func_080ECD5C(*(s32 *)0x03000010);
        temp_r3 = &M2C_FIELD(arg0, s32 *, 0x94);
        temp_r2 = M2C_FIELD(arg0, s32 *, 8);
        temp_r2 -= 0x10;
        temp_r2 += (u32)(temp_r0 * 0x21) >> 0xF;
        *temp_r3 = temp_r2;
    }
    temp_r1 = M2C_FIELD(arg0, s32 *, 0xA8) & ~0xC0;
    if (temp_r1 == 0) {
        M2C_FIELD(arg0, s32 *, 0x98) = temp_r1;
    } else {
        M2C_FIELD(arg0, s32 *, 0x98) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0xA8) = (s32)(M2C_FIELD(arg0, s32 *, 0xA8) & 0xC0);
}
