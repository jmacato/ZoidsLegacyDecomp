#include "m2c_prelude.h"

void func_080E5880(void *, void *);

void sub_080E5B44(u8 *arg0, s32 arg1, s32 arg2)
{
    volatile u32 group;
    register u8 *owner asm("r4") = arg0;
    register u32 shifted asm("r1") = arg1 << 24;
    register u32 id asm("r8") = shifted >> 24;
    u8 zero;
    register u32 outer asm("r2");
    u8 inner;
    u8 *grid;
    register u8 *first asm("ip");
    u8 *second;
    register u8 *copy_dst asm("sl");
    register u32 id_scaled asm("r9");

    {
        register u32 initial_zero asm("r3") = 0;

        owner[0] = id;
        owner[1] = arg2;
        {
            register u32 scratch asm("r2") = *(u16 *)(owner + 4);
            register u32 value asm("r0") = 1;

            value |= scratch;
            scratch = 0xFFF7;
            value &= scratch;
            *(u16 *)(owner + 4) = value;
        }
        *(u16 *)(owner + 0x10) = initial_zero;
    }

    outer = 0;
    zero = 0;
    grid = owner + 0x1E;
    id_scaled = id << 3;
    asm volatile("" : "+r"(id_scaled));
    copy_dst = owner + 0x50;
    group = shifted >> 29;
    first = owner + 0x12;
    second = owner + 0x18;
    do {
        first[outer] = zero;
        second[outer] = zero;
        inner = 0;
        do {
            grid[inner + (outer << 2)] = zero;
            inner++;
        } while (inner <= 3);
        {
            register u32 next asm("r0") = outer + 1;
            outer = (u8)next;
        }
    } while (outer <= 5);

    {
        register u32 scaled asm("r2");
        register u32 current asm("r1");
        register u32 offset asm("r0");
        register u8 *src asm("r3");
        register u8 *dst asm("r5");

        asm volatile("" : "+r"(id_scaled), "+r"(id));
        scaled = id_scaled;
        current = id;
        offset = scaled - current;
        offset <<= 3;
        scaled = 0x087AFCC4;
        asm volatile("" : "+r"(scaled));
        offset += scaled;
        asm volatile("" : "+r"(offset));

        outer = 0;
        dst = copy_dst;
        src = (u8 *)offset;
        src += 0x18;
        do {
            u32 offset = outer << 2;
            *(u32 *)(dst + offset) = *(u32 *)(src + offset);
            {
                register u32 next asm("r0") = outer + 1;
                outer = (u8)next;
            }
        } while (outer <= 3);
    }

    {
        register u32 selector asm("r0") = owner[2];
        register u32 value asm("r1");

        if (selector != 0) {
            selector <<= 6;
            asm volatile("" : "+r"(selector));
            value = 0x02027378;
            asm volatile("" : "+r"(value));
            value = selector + value;
        } else {
            value = 0;
        }
        func_080E5880(owner, (void *)value);
    }

    *(u16 *)(owner + 6) = *(u16 *)(owner + 0x3A);
    *(u16 *)(owner + 8) = *(u16 *)(owner + 0x3E);
    {
        register u32 base asm("r0") = 0x020217B4;
        register u32 index asm("r1");
        register u32 offset asm("r2");

        asm volatile("" : "+r"(base));
        index = group;
        offset = index << 2;
        asm volatile("" : "+r"(offset));
        offset += base;
        *(u32 *)offset |= 1 << (id & 31);
    }
}
