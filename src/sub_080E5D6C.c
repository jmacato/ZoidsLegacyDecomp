#include "m2c_prelude.h"
extern u8 D_020217F4[];
s32 sub_080E5D6C(u8 arg0, u8 arg1) {
    s32 v = arg1 + D_020217F4[arg0];
    if (v <= 0x63) {
        D_020217F4[arg0] = (u8)v;
        return 1;
    }
    D_020217F4[arg0] = 0x63;
    return 0;
}
