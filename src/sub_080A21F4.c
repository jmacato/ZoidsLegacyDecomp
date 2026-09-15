#include "m2c_prelude.h"
extern u8 D_020316F4;
extern u32 D_02032494[];

void func_80A016C(s32, s32, s32);

s32 sub_080A21F4(u8 arg0, u8 **arg1) {
    s32 mul;
    u8 *p;
    u8 v;
    u32 *out;

    v = D_020316F4;
    mul = 8;
    if (v == 0)
        mul = 16;
    out = D_02032494;
    p = *arg1;
    out[0] = (p[1] * mul) << 8;
    out[1] = (p[2] * mul) << 8;
    func_80A016C(arg0, -1, 0);
    return 0;
}
