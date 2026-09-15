#include "m2c_prelude.h"
extern u32 func_80ECD5C(s32);
extern s32 D_03000010;

void sub_080DF630(s32 *p) {
    u32 ret;
    s32 *d;
    s32 f;
    p[0x23] = p[0x26] = 0;
    p[0x24] = p[1] + ((func_80ECD5C(D_03000010) * 65) >> 15) - 0x20;
    ret = func_80ECD5C(D_03000010);
    d = p + 0x25;
    f = p[2] - 0x10;
    *d = f + ((ret * 33) >> 15);
}
