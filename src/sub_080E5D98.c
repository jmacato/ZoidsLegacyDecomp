#include "m2c_prelude.h"
extern u8 D_020217F4[];
s32 sub_080E5D98(u8 arg0, u8 arg1) {
    u8 v = D_020217F4[arg0];
    if (v > arg1) { v -= arg1; D_020217F4[arg0] = v; return 1; }
    D_020217F4[arg0] = 0;
    return 0;
}
