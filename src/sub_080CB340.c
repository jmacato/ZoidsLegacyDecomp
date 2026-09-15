#include "m2c_prelude.h"

extern s32 func_0809A1F8(u32, u32, s32, s32, u32, s32);
extern void func_0809AA64(u8 *, u32, u32, u32);
extern s32 func_080D22B4(u8 *, u32, s32, s32, s32, u32, u32, u32, s32, u32);

void sub_080CB340(u8 *arg0, int arg1)
{
    register u8 *rec asm("r8");
    register u32 flag asm("r10");
    register u32 kind asm("r9");
    register u32 i asm("r5");
    register s32 off asm("r6");
    volatile u32 sp18;

    rec = arg0;
    arg1 = arg1 << 24;
    arg1 = (u32)arg1 >> 24;
    flag = arg1;
    kind = *arg0;
    {
        register u8 *rv0 asm("r2");
        rv0 = rec;
        asm volatile("" : "+r"(rv0));
        *(s32 *)0x02033F3C = func_0809A1F8(kind, rv0[1], 1, 0,
            ({ register u32 t asm("r7"); t = flag; asm volatile("" : "+r"(t)); t; }),
            0x02002880);
    }
    i = 0;
loop_head:
    {
        register u32 t4 asm("r1");
        register u16 *slot asm("r2");
        register u32 vm1 asm("r0");

        t4 = i << 2;
        {
            register u8 *rv asm("r2");
            register u8 *ptmp asm("r0");
            rv = rec;
            asm volatile("" : "+r"(rv));
            ptmp = rv + t4;
            slot = (u16 *)(ptmp + 0x52);
        }
        vm1 = *slot;
        vm1 -= 1;
        vm1 = vm1 << 16;
        vm1 = vm1 >> 16;
        off = t4;
        if (vm1 <= 0x63) {
            register u8 *tbl asm("r3");
            register u32 v2 asm("r0");
            register u32 w asm("r1");
            register u32 x asm("r0");
            register u32 y16 asm("r4");
            register u32 v23 asm("r4");
            register s32 d asm("r3");
            register u32 kind32 asm("r2");
            register u8 *eckeep asm("ip");

            tbl = (u8 *)0x087ABC6C;
            asm volatile("" : "+r"(tbl));
            v2 = *slot;
            w = v2 << 1;
            if (i != 0) {
                x = (w + 1) << 24;
            } else {
                x = v2 << 25;
            }
            func_0809AA64(tbl, x >> 24, (v23 = i << 23) >> 16, i);
            {
                register u32 v3 asm("r0");
                register u32 w2 asm("r1");
                register u32 yv asm("r0");

                {
                    register u8 *rv2 asm("r7");
                    rv2 = rec;
                    asm volatile("" : "+r"(rv2));
                    v3 = *(u16 *)(rv2 + off + 0x52);
                }
                w2 = v3 << 1;
                sp18 = v23;
                if (i != 0) {
                    yv = (w2 + 1) << 16;
                } else {
                    yv = v3 << 17;
                }
                y16 = yv >> 16;
            }
            {
                register u8 *eclo asm("r0");
                register u32 kv asm("r1");
                eclo = (u8 *)0x087EC38C;
                asm volatile("" : "+r"(eclo));
                kv = kind;
                kind32 = kv << 5;
                d = *(s16 *)((off + (s32)kind32) + (s32)eclo);
                eckeep = eclo;
            }
            if (i == 2) {
                register u8 *acbase asm("r0");
                register u32 hv asm("r1");
                register s32 sv asm("r0");
                acbase = (u8 *)0x087AC90C;
                asm volatile("" : "+r"(acbase));
                hv = *(u16 *)(rec + 0x5A);
                hv <<= 1;
                hv += (u32)acbase;
                sv = *(s16 *)hv;
                d = (s16)(d - sv);
            }
            {
                register s32 res asm("r0");
                register u8 *outp asm("r1");
                res = func_080D22B4(
                (u8 *)0x087AC2BC,
                y16,
                0,
                d,
                ({
                    register s32 esum asm("r0");
                    register u8 *eck2 asm("r1");
                    register s32 ev asm("r0");
                    esum = off + (s32)kind32;
                    eck2 = eckeep + 2;
                    asm volatile("" : "+r"(eck2));
                    esum += (s32)eck2;
                    ev = *(s16 *)esum;
                    ev;
                }),
                ({
                    register u32 sv18 asm("r2");
                    register u32 shv asm("r0");
                    sv18 = sp18;
                    asm volatile("" : "+r"(sv18));
                    shv = sv18 >> 16;
                    shv;
                }),
                i,
                ({
                    register u8 *t2 asm("r1");
                    register u32 k3 asm("r0");
                    register u32 fv asm("r0");
                    register u32 fl asm("r1");
                    register u32 kv2 asm("r7");
                    t2 = (u8 *)0x087ED68C;
                    asm volatile("" : "+r"(t2));
                    kv2 = kind;
                    asm volatile("" : "+r"(kv2));
                    k3 = kv2 << 1;
                    k3 += (u32)kind;
                    k3 = i + k3;
                    k3 += (u32)t2;
                    fv = *(u8 *)k3;
                    fl = fv << 6;
                    fl |= 0x1218;
                    {
                        register u32 flv asm("r0");
                        flv = flag;
                        asm volatile("" : "+r"(flv));
                        if (flv != 0) {
                            fl |= 0x8000;
                        }
                    }
                    fl;
                }),
                0,
                ({ register u32 t9 asm("r1"); t9 = flag; asm volatile("" : "+r"(t9)); t9; }));
                outp = (u8 *)0x02033F40;
                asm volatile("" : "+r"(outp));
                outp = (u8 *)(off + (s32)outp);
                *(s32 *)outp = res;
            }
        } else {
            register u8 *zp asm("r0");
            register u32 zv asm("r1");
            zp = (u8 *)0x02033F40;
            asm volatile("" : "+r"(zp));
            zp = (u8 *)(t4 + (s32)zp);
            zv = 0;
            *(s32 *)zp = zv;
        }
    }
    {
        register u32 tinc asm("r0");
        tinc = i + 1;
        tinc <<= 24;
        i = tinc >> 24;
    }
    if (i <= 2) {
        goto loop_head;
    }
}
