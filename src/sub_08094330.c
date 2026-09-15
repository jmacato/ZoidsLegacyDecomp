#include "m2c_prelude.h"
void sub_08094330(void) {
    s32 temp_r0;
    u8 var_r1;
    s32 base2;
    var_r1 = 0;
    do {
        *(s32 *)(var_r1 * 0x38 + 0x03003FE4) = 0;
        temp_r0 = (var_r1 + 1) << 0x18;
        var_r1 = (u32)temp_r0 >> 0x18;
    } while (temp_r0 >= 0);
    var_r1 = 0;
    base2 = 0x030034A4;
    do {
        *(s32 *)(var_r1 * 0xB4 + base2) = 0;
        var_r1 = var_r1 + 1;
    } while (var_r1 <= 0xF);
}
