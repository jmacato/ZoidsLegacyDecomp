#include "m2c_prelude.h"

extern void func_080D2790(s32);
extern void func_080DCDC4(u8 *, s32);
extern u8 *func_080D2450(u8 *, s32, s32, s32, s32, s32, s32, s32);
extern u8 *func_080D2660(u8 *, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_08094554(u8 *);
extern s32 func_080ECD5C(s32);
extern s32 func_080ECD98(s32, s32);
extern s32 func_080ECF78(s32, s32);
extern void func_080D12A0(s32, s32);
extern void func_08095114(u8 *);

extern s32 D_03000010;
extern s32 D_02034034;
extern s32 D_03000054[];

void sub_080DF84C(u8 *owner)
{
    u32 i;
    u32 *timer;
    u8 **children;
    s32 **p88;
    u32 *sp;

    switch (*(u32 *)(owner + 140)) {
    case 0:
    {
        u32 t;

        t = *(u32 *)(owner + 144);
        timer = (u32 *)(owner + 144);
        if (t == 0) {
            func_080D2790(0);
        }
        t = *timer;
        if (t <= 48 || *(u16 *)(*(u8 **)(owner + 12) + 20) <= 7) {
            t &= 1;
            if (t == 0) {
                func_080DCDC4(owner, 1);
            }
        }
        if (*timer == 48) {
            *(u8 **)(owner + 12) = func_080D2450(owner, 0, 0, *(s16 *)(owner + 4),
                                                 *(s16 *)(owner + 8), 0x500, 0, 0);
        } else if (*timer > 48 && *(u8 **)(owner + 12) == 0) {
            i = 1;
            sp = (u32 *)(owner + 140);
            owner += 12;
            children = (u8 **)owner;
            do {
                u8 *child = children[i];
                if (child != 0) {
                    func_08094554(child);
                }
                i = (u8)(i + 1);
            } while (i <= 31);
            (*sp)++;
        }
        (*timer)++;
        break;
    }
    case 1:
    {
        u32 *p94;
        u32 *p98;
        s32 *rng;
        s32 rand;
        s32 v;
        s32 ang;
        u8 *res;

        i = 0;
        sp = (u32 *)(owner + 140);
        timer = (u32 *)(owner + 144);
        children = (u8 **)(owner + 12);
        p88 = (s32 **)(owner + 136);
        p94 = (u32 *)(owner + 148);
        p98 = (u32 *)(owner + 152);
        rng = &D_03000010;
        do {
            rand = func_080ECD5C(*rng);
            v = func_080ECD98(i << 5, 7);
            v += 108;
            v += (u32)(rand * 9) >> 15;
            v <<= 24;
            v = (u32)v >> 24;
            ang = ((u32)(func_080ECD5C(*rng) * 513) >> 15) + 0x200;
            children[i] = func_080D2660(owner, 2, 0, *(s16 *)(owner + 4),
                                        *(s16 *)(owner + 8), 0x500, v, ang, 0);
            i = (u8)(i + 1);
        } while (i <= 7);
        i = 0;
        do {
            ang = ((u32)(func_080ECD5C(D_03000010) * 257) >> 15) + 0x300;
            *(u8 **)((u8 *)children + ((i + 8) << 2)) =
                func_080D2660(owner, 3, 0, *(s16 *)(owner + 4),
                              *(s16 *)(owner + 8), 0x400,
                              (i << 2) - 10, ang, 0);
            i = (u8)(i + 1);
        } while (i <= 5);
        res = func_080D2450(owner, 4, 0, *(s16 *)(owner + 4), *(s16 *)(owner + 8),
                            0x520, 0x080D2529, 0);
        *p88 = (s32 *)res;
        *(s32 *)(res + 40) = 16;
        func_080D12A0(5, 0);
        *timer = 0;
        *p94 = D_02034034;
        *p98 = D_03000054[1];
        func_080D2790(1);
        (*sp)++;
        break;
    }
    case 2:
    {
        u32 masked;

        masked = *(u32 *)(owner + 144);
        masked &= 3;
        asm volatile("" :: "r"(masked));
        asm volatile("" :: "r"(masked));
        asm volatile("" :: "r"(masked));
        timer = (u32 *)(owner + 144);
        if (masked == 0) {
            s32 rand;
            s32 dy;
            s32 y;
            s32 dx;
            s32 x;
            s32 t2;
            u8 *res;

            rand = func_080ECD5C(D_03000010);
            {
                s32 ybase = *(s32 *)(owner + 8);
                s32 *pD = (s32 *)(owner + 152);
                s32 *pB = D_03000054;

                dy = *pD;
                dy -= pB[1];
                if (dy < 0) {
                    dy += 255;
                }
                y = dy >> 8;
                y = ybase + ({ s32 q = y; q; });
            }
            t2 = func_080ECF78(*timer, 6);
            t2 += (u32)rand >> 14;
            t2 += 0xFFFE;
            y += t2;
            y <<= 16;
            y >>= 16;
            rand = *(s32 *)(owner + 4);
            {
                s32 *pE = (s32 *)(owner + 148);
                s32 *pF = &D_02034034;

                dx = *pE;
                {
                    register s32 blk asm("r3");
                    asm volatile("" : "=r"(blk));
                    asm volatile("" :: "r"(blk));
                }
                dx -= *pF;
                if (dx < 0) {
                    dx += 255;
                }
                x = dx >> 8;
                x = rand + ({ s32 q2 = x; q2; });
            }
            x <<= 16;
            x >>= 16;
            res = func_080D2660(owner, 2, 0, x, y, 0x400, 128, 0x180, masked);
            {
                u32 idx = *timer >> 2;
                u8 *c2;
                idx += 14;
                idx <<= 2;
                c2 = (u8 *)owner + 12;
                *(u8 **)(c2 + idx) = res;
            }
        }
        (*timer)++;
        if (*timer == 50) {
            (*(u32 *)(owner + 140))++;
        }
        break;
    }
    case 3:
        i = 0;
        if (*(u8 **)(owner + 12) == 0) {
            u8 **ch = (u8 **)(owner + 12);
            for (;;) {
                i = (u8)(i + 1);
                if (i > 31) {
                    break;
                }
                if (*(u8 **)((u8 *)ch + (i << 2)) != 0) {
                    break;
                }
            }
        }
        if (i == 32) {
            func_08095114(owner);
        }
        break;
    }
}
