#include "m2c_prelude.h"
s32 func_080ECD5C(s32);                             /* extern */

void sub_080DE254(void *arg0) {
    s32 temp_r1;
    register s32 random asm("r0");
    u32 *var_r2;
    u32 var_r1;

    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    temp_r1 = M2C_FIELD(arg0, s32 *, 0xA8) & ~0xC0;
    if (temp_r1 == 0) {
        M2C_FIELD(arg0, s32 *, 0x90) = temp_r1;
        random = func_080ECD5C(*(s32 *)0x03000010);
        var_r2 = arg0 + 0x94;
        var_r1 = ((u32) (random * 0x21) >> 0xF) - 0x10;
    } else {
        M2C_FIELD(arg0, s32 *, 0x90) = 1;
        random = func_080ECD5C(*(s32 *)0x03000010);
        var_r2 = arg0 + 0x94;
        var_r1 = (u32) (random * 0x21) >> 0xF;
    }
    *var_r2 = var_r1;
    M2C_FIELD(arg0, s32 *, 0xA8) = (s32) (M2C_FIELD(arg0, s32 *, 0xA8) & 0xC0);
}
