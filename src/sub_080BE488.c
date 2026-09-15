#include "m2c_prelude.h"
s32 func_080E74F0(void *, s32, s32);                /* extern */
u16 func_080ECD3C(s16);                             /* extern */
s32 func_080ECD5C(s32);                             /* extern */

s32 sub_080BE488(u8 arg0, u8 arg1, u16 arg2) {
    s32 temp_r6;
    s32 temp_r7;
    s32 row_base;
    s32 col_base;
    s32 var_r0;
    u16 var_r4;
    void *temp_r5;
    register s32 base asm("r8");

    row_base = arg0 * 0x27;
    temp_r7 = row_base << 7;
    col_base = arg1 * 0x27;
    temp_r6 = col_base << 4;
    base = 0x02034B4C;
    temp_r5 = temp_r7 + (temp_r6 + base) + 0x70;
    {
        s32 signed_angle;
        s32 adjustment;

        adjustment = func_080ECD3C(M2C_FIELD(temp_r5, s16 *, 0x3C)) * 3;
        signed_angle = (s16)arg2;
        var_r4 = signed_angle + adjustment;
    }
    if ((func_080E74F0(temp_r5, 0x15, 0) << 0x10) != 0) {
        var_r4 += 0x1E;
    }
    if ((func_080E74F0(temp_r5, 0x16, 0) << 0x10) != 0) {
        var_r4 -= 0x1E;
    }
    if (((u32) var_r4 <= 0x5FU) && (0x40 & M2C_FIELD((temp_r6 + temp_r7 + base), u16 *, 4))) {
        var_r0 = (0x64 - var_r4) * 3;
        if (var_r0 < 0) {
            var_r0 += 3;
        }
        var_r4 += var_r0 >> 2;
    }
    if ((u32) var_r4 > 0x63U) {
        var_r4 = 0x63;
    }
    if ((s32) ((u32) (func_080ECD5C(*(s32 *)0x03000010) * 0x64) >> 0xF) <= (s32) var_r4) {
        return 1;
    }
    return 0;
}
