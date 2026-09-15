#include "m2c_prelude.h"
extern u8 D_02034B4C[];
extern u8 D_off_2713[];
extern u8 D_off_2714[];
void sub_080C007C(s32 arg0, s8 arg1, s8 arg2, s16 arg3) {
    register s32 base asm("r5");
    register s32 off1 asm("r6");
    u32 t, idx;
    s32 a1, a2;
    t = arg0 << 0x18;
    base = (s32)D_02034B4C;
    idx = (u32)t >> 0x17;
    off1 = (s32)D_off_2713;
    a1 = base + off1;
    *(s8 *)(idx + a1) = arg1;
    a1 = (s32)D_off_2714;
    a2 = base + a1;
    *(s8 *)(idx + a2) = arg2;
    off1 += 0x49;
    base += off1;
    *(s16 *)(idx + base) = arg3;
}
