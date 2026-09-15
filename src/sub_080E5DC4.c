#include "m2c_prelude.h"
extern u8 D_020217F4[];
extern s32 D_020217B4[];
s32 sub_080E5DC4(s32 arg0) {
    u32 temp_r0 = arg0 << 0x18;
    s32 val, bit, baseX, word;
    s32 *p, *p2;
    s32 idx;
    s32 *q;
    u32 sh;
    word = temp_r0 >> 0x1D;
    sh = 0x1F000000;
    sh &= temp_r0;
    sh >>= 0x18;
    bit = 1 << sh;
    baseX = (s32)D_020217F4;
    idx = word * 4;
    q = (s32 *)(baseX + 0x64);
    p = (s32 *)(idx + (s32)q);
    val = *p;
    if (val & bit) {
        return 0;
    }
    *p = val | bit;
    p2 = (s32 *)(word * 4 + (s32)D_020217B4);
    *p2 |= bit;
    return 1;
}
