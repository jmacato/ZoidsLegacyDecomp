#include "m2c_prelude.h"
struct S {
    /* 0x00 */ u8 f0;
    /* 0x01 */ u8 pad_01[3];
    /* 0x04 */ u16 f4;
    /* 0x06 */ s16 f6;
    /* 0x08 */ u8 pad_08[0x32];
    /* 0x3a */ u16 f3a;
    /* 0x3c */ u8 pad_3c[0x34];
};

extern struct S D_020218E8[];

s32 sub_080BA540(void) {
    s32 result;
    u8 i;
    struct S *p;

    result = 0;
    i = 1;
    do {
        p = &D_020218E8[i];
        if (p->f0 != 0 && !(p->f4 & 8) && p->f6 < (s16)p->f3a) {
            p->f6 = p->f3a;
            result = 1;
        }
        i += 1;
    } while ((u32)i <= 0xCE);
    return result;
}
