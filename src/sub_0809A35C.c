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

s32 sub_0809A35C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u8 *buf)
{
    s32 a0n;
    s32 a1n;
    s32 a2n;
    register s32 a3n asm("r5");
    s32 a4n;
    register s32 two asm("r8");
    register s32 twelve asm("r7");
    s32 two_saved;
    register u32 base asm("r6");
    u32 tiles;
    register u8 *table asm("r9");
    u8 *p2;
    u8 *p3;
    u8 *q;
    s32 idx;
    void *r1v;
    void *r2v;
    void *third;
    s32 rv;
    s32 zerov;
    register u8 *bufp asm("sl");
    register s32 raw_a4 asm("r2");

    a3n = a3;
    raw_a4 = a4;
    bufp = buf;
    asm volatile("" : "+r"(a3n), "+r"(raw_a4), "+r"(bufp));
    a0n = (u8)a0;
    a1n = (u8)a1;
    a2n = (u8)a2;
    a3n = (u8)a3n;
    a4n = (u8)raw_a4;

    table = D_087A5CF0;
    two = a0n * 2;
    twelve = (two + a0n) << 2;
    {
        register u32 table_call asm("r2");
        register u32 entry asm("r0");

        table_call = (u32)table;
        asm volatile("" : "+r"(table_call));
        entry = twelve + table_call;
        func_080ECD38(*(void **)(u32)entry, bufp);
    }
    tiles = a2n << 14;
    base = 0x06000000;
    tiles += base;
    func_080ECD28(bufp, tiles, 0x1000);
    p2 = D_087A641C;
    func_0809A1BC(*(void **)(a0n * 32 + a1n * 4 + p2), 0x05000000, bufp);

    a3n <<= 11;
    tiles = a3n + base;
    if (a4n == 0) {
        u32 t4;

        t4 = (u32)table + 4;
        func_080ECD34(*(void **)(twelve + t4), tiles);
        two_saved = two;
    } else {
        u32 i, j;
        register u32 next_i asm("r6");
        u32 row;
        u32 v;
        register u32 thirtyone asm("r1");
        register u32 mask_seed asm("r2");
        u32 mask;
        u32 t4b;

        t4b = (u32)table + 4;
        func_080ECD38(*(void **)(twelve + t4b), bufp);
        i = 0;
        two_saved = two;
        thirtyone = 31;
        mask_seed = 0x400;
        mask = mask_seed;
        asm volatile("" : "+r"(mask_seed));
        do {
            j = 0;
            next_i = i + 1;
            row = i << 6;
            do {
                v = *(u16 *)(row + ((thirtyone - j) * 2 + (u32)bufp));
                v ^= mask;
                *(u16 *)tiles = v;
                tiles += 2;
                j = (u16)(j + 1);
            } while (j <= 31);
            i = (u16)next_i;
            asm volatile("" :: "r"(next_i));
        } while (i <= 15);
    }

    zerov = 0;
    func_080ECD28(&zerov, a3n + 0x06000800, 0x01000200);
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
        func_0809A1BC(*(void **)(a0n * 32 + a1n * 4 + p3), 0x05000200, bufp);
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
