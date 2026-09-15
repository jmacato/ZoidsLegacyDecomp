#include "m2c_prelude.h"
extern s32 D_0203404C; extern s8 D_02034054; extern u8 D_02033FD0[];
void sub_080D12A0(u8 arg0, s32 arg1) {
    u8 var_r2 = arg0;
    if (((var_r2 == 6) || (var_r2 == 8)) && (D_02033FD0[0xD] == 4)) {
        var_r2 = 9;
    }
    *(u8 *)0x02034030 = var_r2;
    D_0203404C = arg1;
    D_02034054 = 0;
}
