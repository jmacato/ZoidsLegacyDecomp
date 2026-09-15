#include "m2c_prelude.h"
u32 func_80ECD5C(s32);                                 /* extern */

void sub_080AA4E0(void *arg0) {
    s32 temp_r0;
    s32 var_r0;

    if (!(M2C_FIELD(arg0, s32 *, 0) & 2) && (*(s32 *)0x02032990 != 0)) {
        if (M2C_FIELD(arg0, u8 *, 0x18) == 0) {
            if ((func_80ECD5C(*(s32 *)0x03000010) >> 8) == 0) {
                M2C_FIELD(arg0, s8 *, 0x1A) = (s8) ((func_80ECD5C(*(s32 *)0x03000010) >> 0xD) * 2);
                M2C_FIELD(arg0, u8 *, 0x18) = 2U;
                var_r0 = (func_80ECD5C(*(s32 *)0x03000010) >> 8) + 0x40;
                goto block_10;
            }
            return;
        }
        if (!((M2C_FIELD(arg0, s32 *, 0x10) == 0) && (M2C_FIELD(arg0, s32 *, 0x14) == 0))) {
            temp_r0 = M2C_FIELD(arg0, s32 *, 0x28);
            if (temp_r0 != 0) {
                goto decrement;
            }
        }
    }
block_8:
    M2C_FIELD(arg0, u8 *, 0x18) = 0U;
    return;
decrement:
    var_r0 = temp_r0 - 1;
block_10:
    M2C_FIELD(arg0, s32 *, 0x28) = var_r0;
}
