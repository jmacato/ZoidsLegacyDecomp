#include "m2c_prelude.h"

extern void func_080ED038(u8 *, u8 *, s32);
extern void func_080ED128(u8 *, u8 *);
extern void func_080988C8(s32, s32);

void sub_080C098C(int arg0)
{
    register u32 sel asm("r8");
    register u32 index asm("r4");
    u32 next;
    u8 *scratch;
    register u32 value asm("r3");
    register u8 *avail asm("r6");
    register u8 *dest asm("r9");
    register u8 *ttab asm("ip");
    register u32 wi asm("r2");
    register u32 scan asm("r1");
    register u32 v asm("r0");

    {
        register u32 slk asm("sl");
        asm volatile("" :: "r"(slk));
    }
    sel = (u8)arg0;
    index = 0;
    scratch = (u8 *)0x02030564;
    asm volatile("" : "+r"(scratch));
    do {
    {
        register u8 *ep asm("r0");
        ep = (u8 *)0x087A2820;
        asm volatile("" : "+r"(ep));
        ep = (u8 *)(index + (u32)ep);
        value = *ep;
    }
    {
        register u32 s1 asm("r1");
        s1 = sel;
        asm volatile("" : "+r"(s1));
        if (s1 != 0) {
            next = index + 1;
            if (value == 0) goto next_entry;
        }
    }
    if (value == 0) {
        register u32 c1 asm("r0");
        c1 = 0x101;
        *(u16 *)scratch = c1;
        func_080ED038(scratch + 2, (u8 *)0x08107154, 13);
        next = index + 1;
        goto submit;
    }
    scan = 0;
    avail = (u8 *)0x020218E4;
    wi = value >> 5;
    {
        register u8 *d0 asm("r0");
        d0 = (u8 *)0x02030566;
        dest = d0;
    }
    {
        register u8 *t0 asm("r0");
        t0 = (u8 *)0x087EF130;
        ttab = t0;
    }
    asm volatile("" : "+r"(index));
    next = index + 1;
    goto scan_test;
scan_inc:
    {
        register u32 t asm("r0");
        t = scan + 1;
        t <<= 24;
        scan = t >> 24;
    }
scan_test:
    if (scan > 9) goto not_found;
    {
        if (sel == 0) {
            register u32 off asm("r4");
            register u8 *p asm("r0");
            register u32 vv asm("r0");
            off = 0x6912;
            p = avail + off;
            p = (u8 *)(scan + (u32)p);
            vv = *p;
            if (vv == value) goto found_check;
            goto scan_inc;
        } else {
            register u8 *rb asm("r0");
            register u32 off2 asm("r4");
            register u32 vv2 asm("r0");
            rb = (u8 *)0x02034B4C;
            off2 = 0x27B4;
            asm volatile("" : "+r"(off2));
            rb = rb + off2;
            rb = (u8 *)(scan + (u32)rb);
            vv2 = *rb;
            if (vv2 != value) goto scan_inc;
        }
    }
found_check:
    if (scan > 9) goto not_found;
    v = 0x201;
    goto store_status;
not_found:
    v = 1;
store_status:
    *(u16 *)scratch = v;
    wi <<= 2;
    {
        register u32 off3 asm("r1");
        register u8 *ap asm("r0");
        off3 = 0x69FC;
        ap = avail + off3;
        wi += (u32)ap;
    }
    {
        register u32 b asm("r0");
        register u32 bit asm("r1");
        register u32 w asm("r0");
        b = 31;
        b &= value;
        bit = 1;
        bit <<= b;
        w = *(u32 *)wi;
        w &= bit;
        if (w != 0) {
            register u32 vi asm("r0");
            register u8 *ta asm("r1");
            vi = value << 2;
            vi += (u32)ttab;
            ta = *(u8 **)vi;
            func_080ED128(dest, ta);
        } else {
            register u8 *t4 asm("r4");
            register u8 *ta2 asm("r1");
            t4 = ttab;
            ta2 = *(u8 **)t4;
            func_080ED128(dest, ta2);
        }
    }
submit:
    func_080988C8(4, (s32)0x02030564);
next_entry:
    {
        register u32 t2 asm("r0");
        t2 = next << 24;
        index = t2 >> 24;
    }
    } while (index <= 0x33);
}
