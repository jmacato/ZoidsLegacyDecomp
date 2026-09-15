#include "m2c_prelude.h"

extern u8 D_02034B4C[];
extern u8 D_087AFCC4[];
extern u8 D_02032F7C[];

void func_080C02B4(u8, u8);
void func_080BE560(u8, u8);
void func_080E90AC(u8, u8);
void func_080E8B08(u8, u8);
void func_080C00B0(u8, u8);

void sub_080C34A4(u8 a, u8 b, u8 c)
{
    u8 *record;
    u8 *flags24;
    u8 *flags18;
    u8 *grid30;
    register u8 *words80 asm("r10");
    u8 *table;
    register u8 *template asm("r1");
    s32 row;
    s32 col;
    u32 row4;
    u8 i, j;
    u8 v;
    u8 zero;
    register u16 hzero asm("r2");
    register u16 t asm("r2");
    register u16 m asm("r0");

    row = a * 0x1380;
    col = b * 0x270 + (s32)D_02034B4C;
    record = (u8 *)(row + col);
    template = (u8 *)(c * 56 + (s32)D_087AFCC4);
    record[0] = c;
    t = *(u16 *)(record + 4);
    asm volatile("" : : "r"(t));
    m = 32;
    m |= t;
    *(u16 *)(record + 4) = m;

    i = 0;
    zero = 0;
    grid30 = record + 30;
    asm volatile("" : : "r"(grid30));
    words80 = (u8 *)80;
    words80 += (s32)record;
    table = template + 24;
    flags18 = (u8 *)18;
    flags18 += (s32)record;
    {
        register u32 guard0 asm("r0");
        register u32 guard1 asm("r1");
        asm volatile("" : "=r"(guard0), "=r"(guard1));
        flags24 = (u8 *)24;
        flags24 += (s32)record;
        asm volatile("" : : "r"(guard0), "r"(guard1));
    }

    do {
        flags18[i] = zero;
        flags24[i] = zero;
        j = 0;
        row4 = i * 4;
        asm volatile("" : : "r"(row4), "r"(row4), "r"(row4));
        do {
            grid30[j + row4] = zero;
            j++;
        } while (j <= 3);
        i++;
    } while (i <= 5);

    {
        u32 hzero_off;
        u32 hzero_addr;

        i = 0;
        hzero = 0;
        do {
            hzero_off = i * 4;
            hzero_addr = (u32)record;
            hzero_addr += hzero_off;
            *(u16 *)(hzero_addr + 82) = hzero;
            i++;
        } while (i <= 3);
    }

    i = 4;
    {
        u8 *copy_dst = words80;
        u8 *copy_src = table;
        u32 copy_off;
        u32 copy_dst_addr;
        u32 copy_src_addr;
        do {
            copy_off = i * 4;
            copy_dst_addr = (u32)copy_dst;
            copy_dst_addr += copy_off;
            copy_src_addr = (u32)copy_src;
            copy_src_addr += copy_off;
            *(u32 *)copy_dst_addr = *(u32 *)copy_src_addr;
            i++;
        } while (i <= 7);
    }

    func_080C02B4(a, b);
    func_080BE560(a, b);
    func_080E90AC(a, b);
    func_080E8B08(a, b);
    func_080C00B0(a, b);

    {
        register u8 *base asm("r1") = D_02034B4C;
        register u32 off asm("r2") = 0x2700;
        v = *(u8 *)(b + (s32)(base + off));
        off += 6;
        *(u8 *)((u32)v + (u32)(base + off)) = v;
        D_02032F7C[b] = 0xFF;
    }
}
