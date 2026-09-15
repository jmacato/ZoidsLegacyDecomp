#include "m2c_prelude.h"
extern s32 D_03000000[];
void sub_080942E0(s32 arg0) {
    s32 *base;
    s32 temp_r0, temp_r1, t;
    t = arg0 << 0x18;
    base = D_03000000;
    *(s32 *)(((u32)t >> 0x16) + (s32)base) = 0x08092555;
    temp_r0 = base[0];
    if (temp_r0 == 0x08092555) {
        temp_r1 = base[1];
        if (temp_r1 == temp_r0 && base[2] == temp_r1) {
            *(u16 *)0x04000200 &= 0xFFFD;
            *(u16 *)0x04000004 &= 0xFFEF;
        }
    }
}
