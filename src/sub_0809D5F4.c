#include "m2c_prelude.h"
extern u16 D_020324A4[];
u16 sub_0809D5F4(u8 layer, s32 x, s32 y) {
    s32 sxs;
    register u16 *ptr asm("r3");
    x &= 0x1FF;
    y &= 0x1FF;
    if (*(u16 *)0x0202ECF4 == 0) {
        { register s32 stg asm("r2") = x << 16; asm volatile("" : "+r"(stg)); sxs = stg; }
        if (layer == 1) {
            x = (u32)(sxs + 0xFE940000) >> 16;
            if ((u32)x < 80) { s32 yy; { register s32 stg2 asm("r2") = y; asm volatile("" : "+r"(stg2)); yy = stg2; }
                if (yy > 0x103) {
                    if (yy <= 0x153) { s32 y4 = yy - 0x104; u32 tb = 0x02036E98; asm volatile("" : "+r"(tb));
                    { s32 lxs = x << 16; s32 lx = lxs >> 16; s32 j = lx & layer; s32 lys = y4 << 16; s32 ly = lys >> 16; u32 *pE; u16 tile;
                        j = (j + (ly & layer) * 2) * 2; pE = (u32 *)0x02032E88;
                        { s32 xh = (lx + (s32)((u32)lxs >> 31)) >> 1; s32 yh = (ly + (s32)((u32)lys >> 31)) >> 1; tile = *(u16 *)(yh * 80 + (xh * 2 + pE[1])); }
                        ptr = (u16 *)(j + tile * 8 + tb); goto done;
                    }
                    }
                }
            }
            return 0;
        }
    } else {
        s32 t0 = x << 16; asm volatile("" : "+r"(t0));
        { s32 c1 = t0 >> 16; u16 *wp = D_020324A4; sxs = t0;
            if (c1 >= wp[0]) return 0;
            if ((s16)y >= wp[1]) return 0;
        }
    }
    { u32 pmb = 0x02032E88; register u32 *pm asm("r5"); s32 sx16; s32 xh; s32 sys; s32 sy16; s32 yh; s32 t1; s32 j; u32 m3; u16 tile;
        asm volatile("" : "+r"(pmb)); pm = (u32 *)((layer << 2) + pmb); sx16 = sxs >> 16; xh = (sx16 + (s32)((u32)sxs >> 31)) >> 1; sys = y << 16; sy16 = sys >> 16; yh = (sy16 + (s32)((u32)sys >> 31)) >> 1;
        tile = *(u16 *)((D_020324A4[0] >> 1) * yh * 2 + (xh * 2 + *pm)); t1 = sx16 & 1; j = (sy16 & 1) * 2 + t1; m3 = *(u32 *)0x02032E90; ptr = (u16 *)(j * 2 + (tile * 8 + m3));
    }
done: return *ptr;
}
