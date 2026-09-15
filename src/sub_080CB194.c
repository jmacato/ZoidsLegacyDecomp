#include "m2c_prelude.h"

extern u8 func_080CA570(u32, u32);

void sub_080CB194(int arg0)
{
    register u32 mid asm("r8");
    register u32 subnext asm("r9");
    register u8 *base asm("sl");
    register s32 recoff asm("ip");
    register u32 found asm("r5");
    register u32 sub asm("r4");
    register u32 inner asm("r3");
    u32 outer;
    volatile u32 sp0;
    u8 *volatile sp4;
    volatile u32 sp8;
    volatile u32 sp12;

    sp0 = (u8)arg0;
    outer = 0;
    goto outer_test;
outer_loop:
    {
        register u32 z asm("r0");
        z = 0;
        mid = z;
    }
    {
        register u8 *c0 asm("r0");
        register u8 *cs asm("r1");
        register u32 cnt asm("r1");
        c0 = (u8 *)0x0203EFA9;
        asm volatile("" : "+r"(c0));
        cs = (u8 *)(outer + (u32)c0);
        cnt = *cs;
        if (mid >= cnt) goto outer_next;
    }
mid_loop:
    found = 0;
    sub = 0;
    {
        register u8 *p1 asm("r1");
        p1 = (u8 *)0x0203EF70;
        asm volatile("" : "+r"(p1));
        p1 = (u8 *)(outer + (u32)p1);
        sp4 = p1;
    }
    {
        register u32 e6 asm("r0");
        e6 = outer << 1;
        e6 += outer;
        e6 <<= 1;
        e6 += mid;
        sp8 = e6;
    }
sub_loop:
    inner = 0;
    {
        register u32 tn asm("r2");
        tn = sub + 1;
        asm volatile("" : "+r"(tn));
        subnext = tn;
    }
    if (found == 0) {
        {
            register u8 *t6 asm("r6");
            register u32 ri asm("r1");
            register s32 stride asm("r0");
            register s32 ro asm("r2");
            t6 = sp4;
            ri = *t6;
            asm volatile("" : "+r"(ri));
            stride = 0xA8C;
            ro = ri;
            ro *= stride;
            recoff = ro;
        }
        {
            register u8 *b6 asm("r6");
            b6 = (u8 *)0x02034B4C;
            asm volatile("" : "+r"(b6));
            base = b6;
        }
        {
            register u8 *rp asm("r0");
            register u32 row asm("r1");
            register u32 t asm("r0");
            rp = (u8 *)0x0203ECFB;
            asm volatile("" : "+r"(rp));
            row = *rp;
            t = row << 3;
            t -= row;
            t <<= 5;
            t += row;
            t <<= 2;
            sp12 = t;
        }
inner_loop:
        asm volatile("" : "+r"(sub));
        {
            register u32 w asm("r1");
            register u32 t12 asm("r2");
            register u32 e asm("r2");
            register s32 m asm("r0");
            register u32 h asm("r1");
            register u32 mask asm("r0");

            w = 0x27C8;
            asm volatile("" : "+r"(w));
            w += (u32)base;
            t12 = sp12;
            w = t12 + w;
            w += (u32)recoff;
            {
                register u32 t8 asm("r6");
                register u8 *et asm("r2");
                register u8 *es asm("r0");
                t8 = sp8;
                et = (u8 *)0x0203EF78;
                asm volatile("" : "+r"(et));
                es = (u8 *)(t8 + (u32)et);
                e = *es;
            }
            m = 0x94;
            m *= e;
            m += 12;
            w += m;
            {
                register u32 s72 asm("r0");
                s72 = sub << 3;
                s72 += sub;
                s72 <<= 3;
                s72 += 4;
                w += s72;
            }
            {
                register u32 i12 asm("r0");
                i12 = inner << 1;
                i12 += inner;
                i12 <<= 2;
                w += i12;
            }
            h = *(u16 *)w;
            mask = 1;
            mask &= h;
            if (mask != 0) {
                register u32 q asm("r0");
                register u32 s13 asm("r1");
                q = inner << 2;
                q += inner;
                q <<= 3;
                q -= inner;
                q <<= 4;
                s13 = sub << 2;
                s13 += sub;
                s13 <<= 3;
                s13 -= sub;
                s13 <<= 7;
                q += s13;
                q += (u32)base;
                q += 112;
                {
                    register u32 val asm("r0");
                    register u32 a0v asm("r6");
                    val = *(u8 *)q;
                    a0v = sp0;
                    if (val == a0v) {
                        found = 1;
                    }
                }
            }
        }
        {
            register u32 ti asm("r0");
            ti = inner + 1;
            ti <<= 24;
            inner = ti >> 24;
        }
        if (inner <= 5 && found == 0) goto inner_loop;
    }
    {
        register u32 t1 asm("r1");
        register u32 t0 asm("r0");
        t1 = subnext;
        t0 = t1 << 24;
        sub = t0 >> 24;
    }
    if (sub <= 1 && found == 0) goto sub_loop;
    if (found == 0) {
        if (func_080CA570(outer, mid) == 0) {
            register u32 td asm("r0");
            td = outer - 1;
            td <<= 24;
            outer = td >> 24;
            goto outer_next;
        }
        {
            register u32 tm asm("r0");
            tm = mid;
            tm -= 1;
            tm <<= 24;
            tm >>= 24;
            mid = tm;
        }
    }
    {
        register u32 tp asm("r0");
        tp = mid;
        tp += 1;
        tp <<= 24;
        tp >>= 24;
        mid = tp;
    }
    {
        register u8 *c2 asm("r2");
        register u8 *cs2 asm("r0");
        register u32 cnt2 asm("r0");
        c2 = (u8 *)0x0203EFA9;
        asm volatile("" : "+r"(c2));
        cs2 = (u8 *)(outer + (u32)c2);
        cnt2 = *cs2;
        if (mid < cnt2) goto mid_loop;
    }
outer_next:
    {
        register u32 tu asm("r0");
        tu = outer + 1;
        tu <<= 24;
        outer = tu >> 24;
    }
outer_test:
    {
        register u8 *cc asm("r0");
        register u32 ct asm("r0");
        cc = (u8 *)0x0203EFA8;
        asm volatile("" : "+r"(cc));
        ct = *cc;
        if (outer < ct) goto outer_loop;
    }
}
