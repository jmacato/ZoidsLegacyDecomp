#include "m2c_prelude.h"

M2C_UNK func_08092E84(u16);
extern u8 D_020348D4[];

M2C_UNK sub_080D2790(s32 arg0) {
    u8 *base;

    arg0 <<= 0x18;
    base = D_020348D4;
    asm volatile("" : "+r"(base));
    arg0 = (u32)arg0 >> 0x17;
    arg0 += (u32)base;
    return func_08092E84(*(u16 *)arg0);
}
