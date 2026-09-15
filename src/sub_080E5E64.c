#include "m2c_prelude.h"
extern u8 D_020218E4[];
extern u8 D_off_6A04;
s32 sub_080E5E64(s32 arg0) {
    register s32 base asm("r1");
    register s32 off asm("r3");
    u32 *p;
    base = (s32)D_020218E4;
    off = (s32)&D_off_6A04;
    p = (u32 *)(base + off);
    {
        u32 v = *p + arg0;
        if (v <= 0x98967FU) { *p = v; return 1; }
        *p = 0x98967F;
        return 0;
    }
}
