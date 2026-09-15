#include "m2c_prelude.h"

void *func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_0809A4CC(u8, u8, s32, u8);
u8 func_080E9D88(u8, u8);
u8 func_080ECF00(u8, s32);
u8 func_080ECF78(u8, s32);

extern void *D_02033FB4[];

void sub_080CCA6C(u8 arg0)
{
    u8 i;
    s32 x, y;
    u32 w;
    s32 n;
    u8 ret;
    u8 *p;
    void *win;

    i = 0;
    do {
        ret = func_080E9D88(arg0, i);
        if (ret != 0) {
            x = (u16)(((1 - func_080ECF00(i, 3)) << 5) + 0x18);
            y = (u32)(((2 - func_080ECF78(i, 3)) << 0x15) + 0x280000) >> 0x10;
            if (arg0 == 0) {
                s32 m;
                m = 0x50;
                m -= (s16)x;
                m <<= 16;
                x = (u32)m >> 16;
                m = 0x90;
                m -= (s16)y;
                m <<= 16;
                y = (u32)m >> 16;
            }
            p = (u8 *)(i * 0x270 + arg0 * 0x1380 + 0x02034B4C);
            func_0809A4CC(p[0], p[1],
                w = (u32)((i << 0x16) + 0x1800000) >> 0x10,
                n = i + 3);
            win = func_08094484(0x0821024C, 0x08210258, 0, (s16)x, (s16)y, w, n,
                (arg0 != 0) ? 0x8148 : 0x148, 0);
            D_02033FB4[i] = win;
            *(u16 *)((u32)win + 0xC) = 0x80;
        } else {
            D_02033FB4[i] = (void *)ret;
        }
        i++;
    } while (i <= 5);
}
