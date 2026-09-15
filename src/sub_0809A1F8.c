#include "m2c_prelude.h"

extern void func_080ECD34(void *, u32);
extern void func_080ECD38(void *, void *);
extern void func_080ECD28(void *, u32, u32);
extern void func_0809A1BC(void *, u32, void *);
extern s32 func_08095098(s32, void *, void *);

extern u8 D_087A5CF0[];
extern u8 D_087A641C[];
extern u8 D_087A8F24[];
extern u8 D_087A3164[];

s32 sub_0809A1F8(s32 a0, s32 a1, u32 a2, s32 a3, s32 a4, u8 *buf)
{
    s32 a0n;
    s32 a1n;
    u32 a2n;
    s32 a4n;
    s32 two;
    s32 twelve;
    s32 two_saved;
    u32 vrambase;
    u8 *table;
    u8 *p2;
    u8 *p3;
    u8 *q;
    s32 idx;
    void *r1v;
    void *r2v;
    void *third;
    s32 rv;
    s32 zerov;

    a0n = (u8)a0;
    a1n = (u8)a1;
    a2n = a2 << 24;
    a3 = a3 << 24;
    a3 = (u32)a3 >> 24;
    a4n = (u8)a4;
    asm volatile("" :: "r"(a3), "r"(a3), "r"(a3));

    table = D_087A5CF0;
    two = a0n * 2;
    twelve = (two + a0n) << 2;
    func_080ECD34(*(void **)(table + twelve), (a2n >> 10) + (vrambase = 0x06000000));
    p2 = D_087A641C;
    func_0809A1BC(*(void **)(a0n * 32 + a1n * 4 + p2), 0x05000000, buf);

    a3 <<= 11;
    vrambase += a3;
    if (a4n == 0) {
        u8 *t4;

        t4 = table + 4;
        func_080ECD34(*(void **)(t4 + twelve), vrambase);
        two_saved = two;
    } else {
        u32 i, j;
        u32 next_i;
        u32 row;
        u32 v;
        u32 thirtyone;
        u32 m0;
        u32 mask;

        u8 *t4b;

        t4b = table + 4;
        func_080ECD38(*(void **)(t4b + twelve), buf);
        i = 0;
        two_saved = two;
        thirtyone = 31;
        {
            register u32 m0r asm("r3");
            m0r = 0x400;
            asm volatile("" : "+r"(m0r));
            mask = m0r;
        }
        do {
            j = 0;
            next_i = i + 1;
            row = i << 6;
            do {
                v = *(u16 *)(row + ((thirtyone - j) * 2 + (u32)buf));
                v ^= mask;
                *(u16 *)vrambase = v;
                vrambase += 2;
                j = (u16)(j + 1);
            } while (j <= 31);
            i = (u16)next_i;
        } while (i <= 15);
        asm volatile("");
        asm volatile("");
        asm volatile("");
        asm volatile("");
        asm volatile("");
        asm volatile("");
        asm volatile("");
        asm volatile("" :: "r"(mask));
    }

    zerov = 0;
    {
        register u32 k asm("r1");
        k = 0x06000400;
        asm volatile("" : "+r"(k));
        func_080ECD28(&zerov, a3 + k, 0x01000300);
    }
    {
        u8 *base;
        s32 t;

        base = D_087A5CF0;
        t = (two_saved + a0n) * 4;
        base += 8;
        third = *(void **)(base + t);
    }
    if (third != 0) {
        func_080ECD34(third, 0x06010000);
        p3 = D_087A8F24;
        func_0809A1BC(*(void **)(a0n * 32 + a1n * 4 + p3), 0x05000200, buf);
        rv = a4n ? 2 : 0;
        q = D_087A3164;
        idx = a0n * 8;
        r1v = *(void **)(q + idx);
        q += 4;
        r2v = *(void **)(q + idx);
        return func_08095098(rv, r1v, r2v);
    }
    return 0;
}
