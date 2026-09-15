#include "m2c_prelude.h"

extern void func_0809AA64(u8 *, u32, u32, u32);
extern s32 func_080D22B4(u8 *, u32, s32, s32, s32, u32, u32, u32, s32, u32);
extern void func_080A016C(u32, s32, s32);

s32 sub_080A3510(int arg0, u8 **arg1)
{
    register u32 a0 asm("r9");
    register u8 *base asm("sl");
    register u32 y asm("r8");
    register u8 *ec asm("r4");
    register u8 *rec4 asm("r3");
    register u32 i asm("r5");
    register s32 d2 asm("r5");
    register s32 d asm("r6");
    register u8 *kpk asm("ip");
    register u8 *fp asm("r1");

    a0 = (u8)arg0;
    {
        register u8 *tbl asm("r4");
        register u8 *rec asm("r0");
        register u32 v2 asm("r1");
        register u32 w asm("r2");
        register u32 t asm("r0");
        register u32 x asm("r0");
        tbl = (u8 *)0x087ABC6C;
        asm volatile("" : "+r"(tbl));
        rec = *arg1;
        v2 = rec[2];
        w = v2 << 1;
        t = rec[1];
        if (t != 0) {
            x = (w + 1) << 24;
        } else {
            x = v2 << 25;
        }
        {
            register u32 a2 asm("r1");
            register u8 *rec2 asm("r0");
            register u32 v asm("r3");
            a2 = x >> 24;
            rec2 = *arg1;
            v = rec2[1];
            func_0809AA64(tbl, a2, v << 7, v);
        }
    }
    {
        register u8 *b0 asm("r0");
        b0 = (u8 *)0x087AC2BC;
        asm volatile("" : "+r"(b0));
        base = b0;
    }
    {
        register u8 *rec3 asm("r0");
        register u32 v2b asm("r1");
        register u32 w2 asm("r2");
        register u32 t2 asm("r0");
        rec3 = *arg1;
        v2b = rec3[2];
        w2 = v2b << 1;
        t2 = rec3[1];
        if (t2 != 0) {
            register u32 tmp asm("r0");
            tmp = w2 + 1;
            asm volatile("" : "+r"(tmp));
            y = tmp;
        } else {
            v2b <<= 1;
            y = v2b;
        }
    }
    {
        register u8 *kp asm("r2");
        register u32 idx4 asm("r1");
        register u32 k asm("r0");
        ec = (u8 *)0x087EC38C;
        asm volatile("" : "+r"(ec));
        rec4 = *arg1;
        i = rec4[1];
        idx4 = i << 2;
        kp = (u8 *)0x020317D6;
        asm volatile("" : "+r"(kp));
        k = *kp;
        k <<= 5;
        idx4 += k;
        idx4 += (u32)ec;
        d = *(s16 *)idx4;
        kpk = kp;
        if (i == 2) {
            register u8 *ac asm("r0");
            register u32 hv asm("r1");
            register s32 sv asm("r0");
            ac = (u8 *)0x087AC90C;
            asm volatile("" : "+r"(ac));
            hv = rec4[2];
            hv <<= 1;
            hv += (u32)ac;
            sv = *(s16 *)hv;
            d2 = (s16)(d - sv);
        } else {
            d2 = d;
        }
    }
    {
        register s32 res asm("r0");
        register u8 *outp asm("r2");
        res = func_080D22B4(
            base,
            y,
            0,
            d2,
            ({
                register u32 s asm("r1");
                register u8 *kp2 asm("r2");
                register u32 k2 asm("r0");
                register u8 *e2 asm("r0");
                register s32 ev asm("r0");
                s = rec4[1];
                s <<= 2;
                kp2 = kpk;
                asm volatile("" : "+r"(kp2));
                k2 = *kp2;
                k2 <<= 5;
                s += k2;
                e2 = ec + 2;
                s += (u32)e2;
                ev = *(s16 *)s;
                ev;
            }),
            ({
                register u32 t6 asm("r0");
                t6 = rec4[1];
                t6 <<= 7;
                t6;
            }),
            ({
                register u32 t7 asm("r0");
                t7 = rec4[1];
                t7;
            }),
            ({
                register u8 *ft asm("r2");
                register u8 *kp3 asm("r0");
                register u32 k3 asm("r1");
                register u32 sum asm("r0");
                register u32 u3 asm("r3");
                register u32 fv asm("r0");
                register u32 fl asm("r2");
                ft = (u8 *)0x087ED68C;
                asm volatile("" : "+r"(ft));
                kp3 = kpk;
                asm volatile("" : "+r"(kp3));
                k3 = *kp3;
                sum = k3 << 1;
                sum += k3;
                u3 = rec4[1];
                sum += u3;
                sum += (u32)ft;
                fv = *(u8 *)sum;
                fl = fv << 6;
                fl |= 0x1318;
                fp = (u8 *)0x02033F36;
                asm volatile("" : "+r"(fp));
                if (*fp != 0) {
                    fl |= 0x8000;
                }
                fl;
            }),
            0,
            ({
                register u32 t9 asm("r0");
                t9 = *fp;
                t9;
            }));
        outp = (u8 *)0x02033F40;
        asm volatile("" : "+r"(outp));
        {
            register u8 *rc asm("r1");
            register u32 ix asm("r1");
            rc = *arg1;
            ix = rc[1];
            ix <<= 2;
            ix += (u32)outp;
            *(s32 *)ix = res;
        }
    }
    func_080A016C(a0, -1, 0);
    return 0;
}
