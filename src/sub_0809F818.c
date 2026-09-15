#include "m2c_prelude.h"
extern u8 D_0202ECF4[];
s32 sub_0809F818(s32 arg0) {
    u32 temp_r0 = arg0 << 0x18;
    s32 base = (s32)D_0202ECF4;
    s32 idx = (temp_r0 >> 0x1D) * 4;
    s32 *q = (s32 *)(base + 0x150);
    s32 *p = (s32 *)((s32)q + idx);
    s32 bit;
    u32 sh = 0x1F000000;
    sh &= temp_r0;
    sh >>= 0x18;
    bit = 1 << sh;
    if (*p & bit) {
        return 1;
    }
    return 0;
}
