#include "m2c_prelude.h"
extern s32 func_08092A90(s32);
extern s32 func_08093E30(void *, void *, void *);

void sub_080A6DB0(s32 *arg0) {
    s32 temp;
    u8 sp0;
    s32 v;

    temp = func_08092A90(*(s16 *)((u8 *)arg0 + 0x34));
    temp = (s16)temp;
    if (temp < 0) {
        temp += 0x1F;
    }
    *(s16 *)((u8 *)arg0 + 0xA) = (temp >> 5) - 0x20;
    arg0[0xD] += 2;
    v = func_08093E30((u8 *)arg0 + 0x28, (u8 *)arg0 + 4, &sp0);
    *(s16 *)((u8 *)arg0 + 0xC) = v;
    if (sp0 == 0 || ((s16)v << 0x10) > 0x03000000) {
        arg0[0] |= 0x20000;
    } else {
        arg0[0] &= ~0x20000;
    }
}
