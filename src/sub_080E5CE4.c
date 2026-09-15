#include "m2c_prelude.h"
extern u8 D_020217B4[];
extern u8 D_020218E4[];
extern u8 D_off_6934[];
s32 sub_080E5CE4(u16 arg0, s32 arg1) {
    u16 temp_r4; s32 temp_r1; u32 temp_r0;
    s32 base, idx, base2; s32 *q, *p; u8 *q2; u32 sh;
    temp_r0 = arg0 << 0x10;
    temp_r4 = temp_r0 >> 0x10;
    arg1 = arg1 << 0x18;
    base = (s32)D_020217B4;
    idx = (temp_r0 >> 0x15) * 4;
    q = (s32 *)(base + 0x24);
    p = (s32 *)((s32)q + idx);
    sh = 0x1F; sh &= temp_r4;
    *p |= 1 << sh;
    base2 = (s32)D_020218E4;
    base2 += (s32)D_off_6934;
    q2 = (u8 *)(temp_r4 + base2);
    temp_r1 = ((u32)arg1 >> 0x18) + *q2;
    if (temp_r1 <= 0x63) { *q2 = (u8)temp_r1; return 1; }
    *q2 = 0x63;
    return 0;
}
