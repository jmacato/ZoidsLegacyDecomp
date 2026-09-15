#include "m2c_prelude.h"
extern s32 D_0200DD90[];
void sub_0809795C(s32 arg0) {
    u32 temp_r0 = arg0 << 0x10;
    s32 base = (s32)D_0200DD90;
    s32 *p = (s32 *)(base + (temp_r0 >> 0x15) * 4);
    u32 sh = 0x1F0000;
    sh &= temp_r0;
    sh >>= 0x10;
    *p |= 1 << sh;
}
