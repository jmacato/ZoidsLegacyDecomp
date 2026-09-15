#include "m2c_prelude.h"
void sub_080EB5F8(int arg0, void *arg1) {
    register u8 *temp_r2 asm("r2");

    temp_r2 = M2C_FIELD(arg1, u8 **, 0x40);
    {
        register u8 *temp_r3 asm("r3");

        temp_r3 = temp_r2 + 1;
        M2C_FIELD(arg1, u8 **, 0x40) = temp_r3;
    }
    {
        register u8 temp_r3 asm("r3");

        temp_r3 = *(volatile u8 *)temp_r2;
    }
}
