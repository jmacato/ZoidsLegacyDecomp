#include "m2c_prelude.h"
extern u8 D_020218E4[];
extern u8 D_off_6A04;
s32 sub_080E5E90(u32 arg0) {
    register s32 base asm("r0");
    register s32 off asm("r3");
    u32 *p;
    base = (s32)D_020218E4;
    off = (s32)&D_off_6A04;
    p = (u32 *)(base + off);
    {
        u32 v = *p;
        if (v > arg0) { *p = v - arg0; return 1; }
        *p = 0;
        return 0;
    }
}
