#include "m2c_prelude.h"

void func_08095254(void *, s32, u16, u16);

#define PUT_VALUE(n) do {                                                    \
    asm volatile("" : : "i"(n));                                            \
    *dst++ = *attribute | (n);                                               \
} while (0)

void sub_080972D4(void)
{
    u16 *attribute;
    volatile s32 *base_tile;
    register u32 final_tile asm("r7");
    register s32 decorated asm("r9");
    s32 any;
    s8 slot;

    if (*(u8 *)0x02021674 == 0) {
        return;
    }
    decorated = 0;
    any = 0;
    slot = 9;
    attribute = (u16 *)0x02021668;
    base_tile = (volatile s32 *)0x02021664;
    {
        register u32 final_init asm("r3") = 0x374;
        asm volatile("" : "+r"(final_init));
    final_tile = final_init;
    }
    do {
        u8 *record;
        u32 flags;
        register s32 calc_r0 asm("r0");
        register s32 calc_r1 asm("r1");

        asm volatile(
            "mov %1, %2\n\t"
            "lsl %0, %1, #24\n\t"
            "asr %0, %0, #24"
            : "=r"(calc_r0), "=r"(calc_r1)
            : "r"(slot));
        calc_r1 = 0x4D0;
        asm volatile("" : "+r"(calc_r0), "+r"(calc_r1));
        calc_r1 *= calc_r0;
        calc_r0 = 0x0200A8A0;
        asm volatile("" : "+r"(calc_r0), "+r"(calc_r1));
        record = (u8 *)(calc_r1 + calc_r0);
        flags = *(u32 *)record;

        if ((!(flags & 1) || (!any && !(flags & 2))) && !(flags & 8)) {
            continue;
        }
        func_08095254(record + 0x1E,
            *(s32 *)0x0202165C +
                ((*(u16 *)(record + 6) * 32 + *(u16 *)(record + 4)) * 2),
            *(u16 *)(record + 8), *(u16 *)(record + 10));
        if (*(u32 *)record & 8) {
            register u16 *dst asm("r2");
            register u32 product asm("r0");
            register u32 width asm("r1");
            register u32 tail_tile asm("r0");

            width = *(u16 *)(record + 8);
            product = *(u16 *)(record + 10);
            asm volatile("" : "+r"(product), "+r"(width));
            product *= width;
            product <<= 1;
            product += 0x1E;
            dst = (u16 *)(record + product);

            {
            register s32 decorated_test asm("r0") = decorated;
            asm volatile("" : "+r"(decorated_test));
            if (decorated_test == 0) {
                switch (*(u8 *)(record + 0x18)) {
                case 0:
                    PUT_VALUE(0x38E); PUT_VALUE(0x38F); PUT_VALUE(0x390);
                    PUT_VALUE(0x391); PUT_VALUE(0x392); PUT_VALUE(0x3A7);
                    PUT_VALUE(0x3A8); PUT_VALUE(0x3A9); PUT_VALUE(0x3AA);
                    PUT_VALUE(0x3AB);
                    tail_tile = *base_tile + 8;
                    asm volatile("" : : "i"(0));
                    goto first_tail;
                case 1:
                    PUT_VALUE(0x393); PUT_VALUE(0x394); PUT_VALUE(0x395);
                    PUT_VALUE(0x396); PUT_VALUE(0x397); PUT_VALUE(0x398);
                    PUT_VALUE(0x3AC); PUT_VALUE(0x3AD); PUT_VALUE(0x3AE);
                    PUT_VALUE(0x3AF); PUT_VALUE(0x3B0); PUT_VALUE(0x3B1);
                    PUT_VALUE(0x38D);
                    tail_tile = *base_tile + 1;
                    goto first_tail;
                case 2:
                    PUT_VALUE(0x39B); PUT_VALUE(0x39C); PUT_VALUE(0x39D);
                    PUT_VALUE(0x39E); PUT_VALUE(0x39F); PUT_VALUE(0x3B4);
                    PUT_VALUE(0x3B5); PUT_VALUE(0x3B6); PUT_VALUE(0x3B7);
                    PUT_VALUE(0x3B8);
                    tail_tile = *base_tile + 8;
                    asm volatile("" : : "i"(2));
                    goto first_tail;
                case 3:
                    PUT_VALUE(0x3A0); PUT_VALUE(0x3A1); PUT_VALUE(0x3A2);
                    PUT_VALUE(0x3A3); PUT_VALUE(0x3A4); PUT_VALUE(0x3A5);
                    PUT_VALUE(0x3B9); PUT_VALUE(0x3BA); PUT_VALUE(0x3BB);
                    PUT_VALUE(0x3BC); PUT_VALUE(0x3BD); PUT_VALUE(0x3BE);
                    PUT_VALUE(0x38D);
                    tail_tile = *base_tile + 1;
first_tail:
                    tail_tile |= *attribute;
                    *dst++ = tail_tile;
                    *dst++ = *attribute | (*base_tile + 1);
                    *dst++ = *attribute | (*base_tile + 1);
                    *dst++ = *attribute | (*base_tile + 1);
                    *dst = *attribute | final_tile;
                    break;
                }
                decorated = (u8)(decorated + 1);
            } else {
                switch (*(u8 *)(record + 0x18)) {
                case 0:
                    PUT_VALUE(0x35C); PUT_VALUE(0x35D); PUT_VALUE(0x35E);
                    PUT_VALUE(0x35F); PUT_VALUE(0x360); PUT_VALUE(0x375);
                    PUT_VALUE(0x376); PUT_VALUE(0x377); PUT_VALUE(0x378);
                    PUT_VALUE(0x379);
                    tail_tile = *base_tile + 8;
                    asm volatile("" : : "i"(4));
                    goto later_tail;
                case 1:
                    PUT_VALUE(0x361); PUT_VALUE(0x362); PUT_VALUE(0x363);
                    PUT_VALUE(0x364); PUT_VALUE(0x365); PUT_VALUE(0x366);
                    PUT_VALUE(0x37A); PUT_VALUE(0x37B); PUT_VALUE(0x37C);
                    PUT_VALUE(0x37D); PUT_VALUE(0x37E); PUT_VALUE(0x37F);
                    PUT_VALUE(0x38D);
                    tail_tile = *base_tile + 1;
                    goto later_tail;
                case 2:
                    PUT_VALUE(0x369); PUT_VALUE(0x36A); PUT_VALUE(0x36B);
                    PUT_VALUE(0x36C); PUT_VALUE(0x36D); PUT_VALUE(0x382);
                    PUT_VALUE(0x383); PUT_VALUE(0x384); PUT_VALUE(0x385);
                    PUT_VALUE(0x386);
                    tail_tile = *base_tile + 8;
                    asm volatile("" : : "i"(6));
                    goto later_tail;
                case 3:
                    PUT_VALUE(0x36E); PUT_VALUE(0x36F); PUT_VALUE(0x370);
                    PUT_VALUE(0x371); PUT_VALUE(0x372); PUT_VALUE(0x373);
                    PUT_VALUE(0x387); PUT_VALUE(0x388); PUT_VALUE(0x389);
                    PUT_VALUE(0x38A); PUT_VALUE(0x38B); PUT_VALUE(0x38C);
                    PUT_VALUE(0x38D);
                    tail_tile = *base_tile + 1;
later_tail:
                    tail_tile |= *attribute;
                    *dst++ = tail_tile;
                    *dst++ = *attribute | (*base_tile + 1);
                    *dst++ = *attribute | (*base_tile + 1);
                    *dst++ = *attribute | (*base_tile + 1);
                    *dst = *attribute | final_tile;
                    break;
                }
            }
            }
            func_08095254(record + 0x1E +
                    *(u16 *)(record + 8) * *(u16 *)(record + 10) * 2,
                *(s32 *)0x0202165C +
                    ((*(u16 *)(record + 4) + *(u8 *)(record + 0x19) +
                      ((*(u16 *)(record + 6) - 2) << 5)) * 2),
                *(u8 *)(record + 0x1A), 3);
        }
        flags = *(u32 *)record & ~2;
        *(u32 *)record = flags;
        if (flags & 4) {
            *(u32 *)record = flags & ~1;
        }
        any = 1;
    } while (--slot >= 0);

    {
    register u8 *gate asm("ip");

    slot = 0;
    gate = (u8 *)0x02021674;
    asm volatile("" : "+r"(gate));
    do {
        s32 offset = slot * 4;
        *(u32 *)(0x0200DD90 + offset) ^=
            *(u32 *)(0x0200DE10 + offset);
        *(u32 *)(0x0200DE10 + offset) = 0;
        slot++;
    } while (slot <= 0x1F);
    {
        register u32 clear asm("r0") = 0;
        asm volatile("" : "+r"(clear));
        *gate = clear;
    }
    }
}

#undef PUT_VALUE
