#include "m2c_prelude.h"
extern u32 D_0202ECF4[];
extern s8 D_020324B2;
void sub_0809E204(s16 arg0, s32 arg1, s32 arg2, u8 arg3) {
    D_020324B2 = arg3 + 1;
    *(s16 *)0x020324B4 = arg0;
    D_0202ECF4[1] = arg1;
    D_0202ECF4[2] = arg2;
}
