#include "m2c_prelude.h"
M2C_UNK func_080EBF24(s32);
extern u32 D_00000004;

void sub_080EB888(void) {
    s32 *var_r5;
    u32 temp_r0;
    u32 var_r4;

    temp_r0 = (u32)&D_00000004;
    temp_r0 = temp_r0 << 0x10;
    temp_r0 = temp_r0 >> 0x10;
    if (temp_r0 != 0) {
        var_r5 = (s32 *)0x086A4694;
        var_r4 = temp_r0;
        do {
            func_080EBF24(*var_r5);
            var_r5 += 3;
            var_r4 -= 1;
        } while (var_r4 != 0);
    }
}
