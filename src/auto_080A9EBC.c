#include "m2c_prelude.h"
M2C_UNK func_80A9AFC(s32);                             /* extern */

void sub_080A9EBC(void) {
    s32 temp_r0;
    u8 var_r4;

    var_r4 = 0;
    do {
        temp_r0 = var_r4 * 0x48;
        if (M2C_FIELD(temp_r0, s32 *, 0x020325A0) & 1) {
            func_80A9AFC(temp_r0 + 0x020325A0);
        }
        var_r4 += 1;
    } while ((u32) var_r4 <= 0xDU);
}
