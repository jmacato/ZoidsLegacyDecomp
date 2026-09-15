#include "m2c_prelude.h"
void sub_080E6090(void *arg0) {
    register void *var_r1 asm("r1") = arg0;
    register u16 temp_r2 asm("r2") = M2C_FIELD(var_r1, u16 *, 4);
    if (temp_r2 & 8) {
        u16 temp_r0 = 0xFFF7;
        temp_r0 &= temp_r2;
        M2C_FIELD(var_r1, u16 *, 4) = temp_r0;
        M2C_FIELD(var_r1, u16 *, 6) = M2C_FIELD(var_r1, u16 *, 0x3A);
    }
}
