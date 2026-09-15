#include "m2c_prelude.h"
extern s32 D_03000A84[];
void sub_08092E0C(u8 arg0) {
    s32 base = (s32)D_03000A84;
    s32 i;
    s32 *p1, *p2;
    i = 0x4C;
    i *= arg0;
    p1 = (s32 *)(base + 4);
    *(s32 *)(i + (s32)p1) = -1;
    p2 = (s32 *)(base + 8);
    *(s32 *)(i + (s32)p2) = -1;
}
