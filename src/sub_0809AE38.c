#include "m2c_prelude.h"
extern s32 func_8092D8C(s32, s32);
extern u8 func_809ACC4(s32);

s32 sub_0809AE38(void) {
    u8 temp_r2;
    s32 temp_r1;

    if (*(u8 *)0x0300605B == 0) {
        *(u16 *)0x030009EC |= 1;
        *(u8 *)0x0300605B = 1;
    }
    temp_r2 = func_809ACC4(0);
    if (temp_r2 == 1) {
        temp_r1 = *(s32 *)0x030009E8 & 0x80;
        if (temp_r1 != 0) {
            *(u8 *)0x0300603C = temp_r2;
        } else {
            *(u8 *)0x0300603C = temp_r1;
        }
        func_8092D8C(9, 0x0809AD2D);
        return 1;
    }
    return 0;
}
