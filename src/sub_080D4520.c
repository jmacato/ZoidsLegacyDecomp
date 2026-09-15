#include "m2c_prelude.h"
extern s32 D_03000010;
s32 func_80ECD5C(s32);

void sub_080D4520(s32 *arg0) {
    s32 *p;
    s32 y;
    s32 r;

    arg0[0x23] = 0;
    arg0[0x24] = (arg0[1] + ((u32)(func_80ECD5C(D_03000010) * 0x41) >> 0xF)) - 0x20;
    r = func_80ECD5C(D_03000010);
    p = &arg0[0x25];
    y = arg0[2] - 0x10;
    *p = y + ((u32)(r * 0x21) >> 0xF);
}
