#include "m2c_prelude.h"
s32 func_080ECD5C(s32);                             /* extern */

void sub_0809B970(void *arg0, s32 arg1, s32 arg2) {
    u8 *temp_r1;
    s32 temp_r0;
    s32 temp_r0_3;
    u32 temp_r0_2;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x30);
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r0_2 = M2C_FIELD(arg0, u32 *, 0x2C) + 0x80;
        M2C_FIELD(arg0, u32 *, 0x2C) = temp_r0_2;
        if (temp_r0_2 > 0x67FFU) {
            M2C_FIELD(arg0, s32 *, 0x34) = (s32) (((u32) (func_080ECD5C(*(s32 *)0x03000010) * 0x81) >> 0xF) - 0x40);
            M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + 1);
        }
        break;
    case 1:
        M2C_FIELD(arg0, u32 *, 0x28) = (u32) (M2C_FIELD(arg0, u32 *, 0x28) + M2C_FIELD(arg0, s32 *, 0x34));
        M2C_FIELD(arg0, u32 *, 0x2C) = (u32) (M2C_FIELD(arg0, u32 *, 0x2C) + 0x40);
        temp_r0_3 = arg2 + 3;
        temp_r0_3 *= 4;
        temp_r1 = arg0 + 0x28;
        temp_r1 += temp_r0_3;
        temp_r0_3 = *(s32 *) temp_r1;
        if (temp_r0_3 != 0) {
            *(s32 *) temp_r1 = temp_r0_3 - 0x10;
        }
        break;
    }
    M2C_FIELD(arg0, s16 *, 4) = (s16) ((u32) M2C_FIELD(arg0, u32 *, 0x28) >> 8);
    M2C_FIELD(arg0, s16 *, 6) = (s16) ((u32) M2C_FIELD(arg0, u32 *, 0x2C) >> 8);
}
