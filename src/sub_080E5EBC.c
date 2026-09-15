#include "m2c_prelude.h"
extern u8 D_020218E4[];
extern u8 D_off_69FC[];
s32 sub_080E5EBC(s32 arg0) {
    u32 temp_r0 = arg0 << 0x18;
    s32 val, bit, base, word, idx;
    s32 *p;
    u32 sh;
    word = temp_r0 >> 0x1D;
    sh = 0x1F000000;
    sh &= temp_r0;
    sh >>= 0x18;
    bit = 1 << sh;
    base = (s32)D_020218E4;
    idx = word * 4;
    base += (s32)D_off_69FC;
    p = (s32 *)(idx + base);
    val = *p;
    if (val & bit) {
        return 0;
    }
    *p = val | bit;
    return 1;
}
