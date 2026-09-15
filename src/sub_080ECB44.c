#include "m2c_prelude.h"
void sub_080ECB44(int arg0, void *arg1) {
    u8 *temp_r0;

    temp_r0 = M2C_FIELD(arg1, u8 **, 0x40);
    M2C_FIELD(arg1, u8 *, 0x1F) = *temp_r0;
    M2C_FIELD(arg1, u8 **, 0x40) = temp_r0 + 1;
}
