#include "m2c_prelude.h"
void sub_0809370C(void *arg0, void *arg1, void *arg2) {
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;

    var_r0 = (M2C_FIELD(arg0, s16 *, 0) * M2C_FIELD(arg1, s32 *, 0)) + (M2C_FIELD(arg1, s32 *, 4) * M2C_FIELD(arg0, s16 *, 6)) + (M2C_FIELD(arg1, s32 *, 8) * M2C_FIELD(arg0, s16 *, 0xC));
    if (var_r0 < 0) {
        var_r0 += 0xFF;
    }
    M2C_FIELD(arg2, s32 *, 0) = (s32) (var_r0 >> 8);
    var_r0_2 = (M2C_FIELD(arg0, s16 *, 2) * M2C_FIELD(arg1, s32 *, 0)) + (M2C_FIELD(arg1, s32 *, 4) * M2C_FIELD(arg0, s16 *, 8)) + (M2C_FIELD(arg1, s32 *, 8) * M2C_FIELD(arg0, s16 *, 0xE));
    if (var_r0_2 < 0) {
        var_r0_2 += 0xFF;
    }
    M2C_FIELD(arg2, s32 *, 4) = (s32) (var_r0_2 >> 8);
    var_r0_3 = (M2C_FIELD(arg0, s16 *, 4) * M2C_FIELD(arg1, s32 *, 0)) + (M2C_FIELD(arg1, s32 *, 4) * M2C_FIELD(arg0, s16 *, 0xA)) + (M2C_FIELD(arg1, s32 *, 8) * M2C_FIELD(arg0, s16 *, 0x10));
    if (var_r0_3 < 0) {
        var_r0_3 += 0xFF;
    }
    M2C_FIELD(arg2, s32 *, 8) = (s32) (var_r0_3 >> 8);
}
