#include "m2c_prelude.h"
void sub_080EAF3C(s32 unused, void *arg1) {
    register s32 temp_r2 asm("r2");
    register void *temp_r3 asm("r3");

    temp_r2 = M2C_FIELD(arg1, u8 *, 2);
    if (temp_r2 != 0) {
        temp_r2--;
        M2C_FIELD(arg1, u8 *, 2) = temp_r2;
        temp_r3 = arg1 + temp_r2 * 4;
        temp_r2 = M2C_FIELD(temp_r3, s32 *, 0x44);
        M2C_FIELD(arg1, s32 *, 0x40) = temp_r2;
    }
}
