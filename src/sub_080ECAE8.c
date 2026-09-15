#include "m2c_prelude.h"
void sub_080ECAE8(int arg0, void *arg1) {
    register u8 *temp_r0 asm("r0");
    register u8 temp_r2 asm("r2");

    temp_r0 = M2C_FIELD(arg1, u8 **, 0x40);
    temp_r2 = *temp_r0;
    temp_r0 = arg1;
    temp_r0 += 0x2C;
    *temp_r0 = temp_r2;
    temp_r0 = M2C_FIELD(arg1, u8 **, 0x40);
    M2C_FIELD(arg1, u8 **, 0x40) = temp_r0 + 1;
}
