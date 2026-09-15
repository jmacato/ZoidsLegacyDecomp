#include "m2c_prelude.h"
void *func_809716C(u8);                                /* extern */

void sub_080981D0(u8 arg0, u16 arg1, u16 arg2) {
    void *temp_r0;

    temp_r0 = func_809716C(arg0);
    M2C_FIELD(temp_r0, u16 *, 0xC) = arg1;
    M2C_FIELD(temp_r0, u16 *, 0xE) = arg2;
}
