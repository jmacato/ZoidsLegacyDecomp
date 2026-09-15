#include "m2c_prelude.h"

void sub_080CD5CC(void)
{
    u32 offC_g;
    u32 offA_s;
    u8 *base3;
    register u8 *py asm("r4");
    register u8 *pairX asm("ip");
    u8 *q;
    register u32 n asm("r3");
    s32 t;
    register u32 i asm("r2");
    register u32 y asm("r6");
    register u32 x asm("r5");
    u32 v;
    register s32 zz asm("sl");
    register s32 yy asm("r8");
    volatile s32 znext;
    register s32 ynext asm("r9");
    s32 xnext;
    u32 mm;
    u32 mm2;

    offC_g = 0xA1AF;
    offA_s = 0xA058;
    i = 0;
    {
        register u8 *bb asm("r0") = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(bb));
        py = bb + 0xA058;
    }
    n = 0xFF;
    asm volatile("" : "+r"(n));
    do {
        u8 *p = (u8 *)((u32)(i * 2) + (u32)py);
        t = *p;
        t = t | n;
        *p = t;
        {
            register s32 t2 asm("r0");
            t2 = i + 1;
            i = (u8)t2;
        }
    } while (i <= 11);
    i = 0;
    {
        register u8 *base2 asm("r3") = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(base2));
        if (i < (u32)*(base2 + offC_g)) {
            {
                u32 t9 = 0xA059;
                asm volatile("" : "+r"(t9));
                pairX = (u8 *)((u32)base2 + t9);
            }
loopB:
            base3 = (u8 *)0x02034B4C;
            y = 0;
            {
                s32 tt = i * 2;
                znext = i + 1;
                zz = (tt + i) * 4;
            }
loopC:
            x = 0;
            {
                s32 tt2 = y * 2;
                ynext = y + 1;
                yy = (tt2 + y) * 2;
            }
loopD:
            {
                register s32 yv asm("r3");
                register s32 fs asm("r0");
                yv = yy;
                asm volatile("" : "+r"(yv));
                fs = x + yv + zz;
                v = *(u8 *)(fs + 0x0203ED02);
            }
            xnext = x + 1;
            if (v != 0) {
                n = 0;
                if (({ register u8 *pe asm("r2") = (u8 *)0x0203EBA4; *pe; }) == y) {
                    register u8 *pd asm("r1") = pairX;
                    asm volatile("" : "+r"(pd));
                    if (*pd == x) goto skip;
                }
scan_top:
                mm = n * 2;
                py = (u8 *)(offA_s + (u32)base3);
                q = (u8 *)(mm + (u32)py);
                if (*q == 0xFF) {
                    *q = y;
                    {
                        register u8 *pxc asm("r3");
                        register u8 *ps asm("r0");
                        pxc = pairX;
                        asm volatile("" : "+r"(pxc));
                        ps = (u8 *)(mm + (u32)pxc);
                        *ps = x;
                    }
                    goto skip;
                }
                {
                    register s32 t3 asm("r0");
                    t3 = n + 1;
                    n = (u8)t3;
                }
                if (n > 11) goto skip;
                mm2 = n * 2;
                {
                    register u8 *qy asm("r0") = (u8 *)(mm2 + (u32)py);
                    if (*qy != y) goto scan_top;
                }
                if (*(u8 *)(mm2 + (u32)pairX) != x) goto scan_top;
            }
skip:
            {
                register s32 tx asm("r0");
                tx = xnext << 24;
                x = (u32)tx >> 24;
            }
            if (x <= 5) goto loopD;
            {
                register s32 tmpy asm("r3") = ynext;
                asm volatile("" : "+r"(tmpy));
                {
                    register s32 ty asm("r0");
                    ty = tmpy << 24;
                    y = (u32)ty >> 24;
                }
            }
            if (y <= 1) goto loopC;
            {
                register s32 tz1 asm("r1");
                register s32 tz asm("r0");
                tz1 = znext;
                tz = tz1 << 24;
                i = (u32)tz >> 24;
            }
            {
                register u8 *b3 asm("r3") = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(b3));
                {
                    register u8 *pf asm("r0") = b3 + 0xA1AF;
                    if (i < (u32)*pf) goto loopB;
                }
            }
        }
    }
}
