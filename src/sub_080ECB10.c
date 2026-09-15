#include "m2c_prelude.h"
void sub_080ECB10(int arg0, void *arg1) {
    u8 temp_r0;
    u8 *temp_r2;

    temp_r0 = *M2C_FIELD(arg1, u8 **, 0x40);
    temp_r2 = arg1;
    temp_r2 += 0x2E;
    *temp_r2 = temp_r0;
    temp_r0 = 0;
    M2C_FIELD(arg1, u8 **, 0x40) = M2C_FIELD(arg1, u8 **, 0x40) + 1;
}
