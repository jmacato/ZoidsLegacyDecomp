#include "m2c_prelude.h"
extern u8 D_02031840[];
extern void *D_02031940[];

void sub_0809FA24(u8 arg0, int arg1, u16 arg2, u8 arg3) {
    u8 *p = &D_02031840[arg0 * 0x10];
    int dx, dy, fx, fy;
    s8 v;
    int z;
    p[0] = 1;
    fx = *(u16 *)((u8 *)D_02031940[arg0] + 4);
    dx = (s16)arg1 - fx;
    *(s16 *)(p + 4) = dx;
    if ((dx << 0x10) < 0) { *(s16 *)(p + 4) = -dx; p[1] = 1; } else { p[1] = 0; }
    fy = *(u16 *)((u8 *)D_02031940[arg0] + 6);
    dy = (s16)arg2 - fy;
    *(s16 *)(p + 6) = dy;
    if ((dy << 0x10) < 0) { *(s16 *)(p + 6) = -dy; v = 1; } else { v = 0; }
    p[2] = v;
    z = 0;
    p[0xC] = arg3;
    *(s16 *)(p + 0xA) = z;
    *(s16 *)(p + 8) = z;
    p[0xD] = 0;
}
