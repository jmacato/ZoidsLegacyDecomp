#include "m2c_prelude.h"
extern u8 D_0202ECF4[];
void sub_0809F7F0(s32 arg0) {
    u32 temp_r0 = arg0 << 0x18;
    s32 base = (s32)D_0202ECF4;
    s32 idx = (temp_r0 >> 0x1D) * 4;
    s32 *q = (s32 *)(base + 0x150);
    s32 *p = (s32 *)((s32)q + idx);
    u32 sh = 0x1F000000;
    sh &= temp_r0;
    sh >>= 0x18;
    *p &= ~(1 << sh);
}
