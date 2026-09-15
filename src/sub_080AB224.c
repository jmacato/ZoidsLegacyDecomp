#include "m2c_prelude.h"
extern s32 D_02032E94;
extern u16 D_020324A4;
u16 func_80AB18C(u8);
u16 sub_080AB224(u8 arg0, s32 arg1, s32 arg2) {
    s32 m, base, index, t;
    t = 0xFF;
    m = arg2 & t;
    m *= D_020324A4;
    m = (s32)m >> 1;
    base = D_02032E94;
    t = t & arg1;
    index = t + m;
    if (0x40 & *(u8 *)(base + index)) {
        return 0;
    }
    return func_80AB18C(arg0);
}
