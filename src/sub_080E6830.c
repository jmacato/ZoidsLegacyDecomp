#include "m2c_prelude.h"
s32 func_080E522C(s16, s16);                        /* extern */
s32 func_080E74F0(void *, s32, u8);                 /* extern */
s16 func_080ECD98(s32, u8);                         /* extern */

void sub_080E6830(void *arg0, void *arg1, void *arg2) {
    u8 var_r4;
    void *temp_r4;

    if (arg1 != (void *)0) {
        var_r4 = M2C_FIELD(arg1, u8 *, 0x30);
        if ((func_080E74F0(arg1, 3, M2C_FIELD(arg0, u8 *, 0)) << 0x10) != 0) {
            var_r4 += 5;
        }
        if ((func_080E74F0(arg1, 4, M2C_FIELD(arg0, u8 *, 0)) << 0x10) != 0) {
            var_r4 += 0xA;
        }
        if ((func_080E74F0(arg1, 5, M2C_FIELD(arg0, u8 *, 0)) << 0x10) != 0) {
            var_r4 += 0x14;
        }
        if (arg2 != (void *)0) {
            var_r4 += M2C_FIELD(arg2, u8 *, 0x28);
        }
        if ((u32) var_r4 > 0x63U) {
            var_r4 = 0x63;
        }
        M2C_FIELD(arg0, s16 *, 0x3A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x3A) + func_080E522C(M2C_FIELD(arg0, s16 *, 0x3A), M2C_FIELD(arg1, s16 *, 0x34)));
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) + func_080E522C(M2C_FIELD(arg0, s16 *, 0x4A), M2C_FIELD(arg1, s16 *, 0x38)));
        M2C_FIELD(arg0, s16 *, 0x44) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x44) + func_080E522C(M2C_FIELD(arg0, s16 *, 0x44), M2C_FIELD(arg1, s16 *, 0x36)));
        M2C_FIELD(arg0, s16 *, 0x3C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x3C) + func_080E522C(M2C_FIELD(arg0, s16 *, 0x3C), M2C_FIELD(arg1, s16 *, 0x3C)));
        if ((u32) var_r4 < (u32) M2C_FIELD(arg0, u8 *, 0x39)) {
            M2C_FIELD(arg0, s16 *, 0x3A) = func_080ECD98(M2C_FIELD(arg0, s16 *, 0x3A) * var_r4, M2C_FIELD(arg0, u8 *, 0x39));
            M2C_FIELD(arg0, s16 *, 0x4A) = func_080ECD98(M2C_FIELD(arg0, s16 *, 0x4A) * var_r4, M2C_FIELD(arg0, u8 *, 0x39));
            M2C_FIELD(arg0, s16 *, 0x44) = func_080ECD98(M2C_FIELD(arg0, s16 *, 0x44) * var_r4, M2C_FIELD(arg0, u8 *, 0x39));
            M2C_FIELD(arg0, s16 *, 0x3C) = func_080ECD98(M2C_FIELD(arg0, s16 *, 0x3C) * var_r4, M2C_FIELD(arg0, u8 *, 0x39));
        }
    }
    if (arg2 != (void *)0) {
        M2C_FIELD(arg0, s16 *, 0x4A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) + func_080E522C(M2C_FIELD(arg0, s16 *, 0x4A), M2C_FIELD(arg2, s16 *, 0x2E)));
        temp_r4 = (arg0 + 0x4A) - 8;
        M2C_FIELD(temp_r4, s16 *, 0) = (s16) ((u16) M2C_FIELD(temp_r4, s16 *, 0) + func_080E522C(M2C_FIELD(temp_r4, s16 *, 0), M2C_FIELD(arg2, s16 *, 0x30)));
        temp_r4 += 4;
        M2C_FIELD(temp_r4, s16 *, 0) = (s16) ((u16) M2C_FIELD(temp_r4, s16 *, 0) + func_080E522C(M2C_FIELD(temp_r4, s16 *, 0), M2C_FIELD(arg2, s16 *, 0x32)));
    }
}
