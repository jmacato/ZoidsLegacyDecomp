#include "m2c_prelude.h"

u8 func_080E523C(u8);
void func_080E5880(void *, void *);

s32 sub_080E5A18(s32 arg0, s32 arg1)
{
    volatile u32 group;
    u8 * volatile copy_dst;
    register u32 id asm("r9");
    register u32 index;
    register u8 *record asm("r5");
    register u32 outer asm("r4");

    arg0 <<= 24;
    id = (u32)arg0 >> 24;
    arg1 <<= 24;
    arg1 = (u32)arg1 >> 24;
    index = 1;
    {
        register u8 *base asm("r2") = (u8 *)0x020218E8;

        record = base + 0x70;
        goto check_slot;
next_slot:
        {
            register u32 next asm("r0") = index + 1;

            next <<= 24;
            index = next >> 24;
            if (index > 0xCEU) {
                goto scan_done;
            }
            {
                register u32 offset asm("r0");

                offset = index << 3;
                offset -= index;
                offset <<= 4;
                record = (u8 *)(offset + (u32)base);
            }
        }
check_slot:
        if (record[0] != 0) {
            goto next_slot;
        }
    }
scan_done:
    if (index == 0xCF) {
        return 0xFF;
    }

    outer = 0;
    record[0] = id;
    record[1] = arg1;
    record[2] = outer;
    {
        register u32 one asm("r2");
        register u32 flags asm("r1");
        register u32 shift asm("r0");

        shift = func_080E523C(record[0]);
        shift <<= 24;
        shift >>= 24;
        one = 1;
        flags = one;
        flags <<= shift;
        flags |= 1;
        record[3] = flags;
        *(u16 *)(record + 4) = one;
    }
    *(u16 *)(record + 0x10) = outer;

    {
        register u32 id_scaled asm("r10");
        register u8 *first asm("r8");
        register u8 *grid asm("r6");
        register u8 *second asm("r12");
        register u32 zero asm("r1");
        u8 inner;

        id_scaled = id << 3;
        {
            register u8 *copy_init asm("r2") = record;

            copy_init += 0x50;
            asm volatile("" : "+r"(copy_init));
            copy_dst = copy_init;
        }
        {
            register u32 group_init asm("r0") = id;

            asm volatile("" : "+r"(group_init));
            group_init >>= 5;
            group = group_init;
        }
        {
            register u8 *first_init asm("r1") = (u8 *)0x12;

            asm volatile("" : "+r"(first_init));
            first_init += (u32)record;
            first = first_init;
        }
        zero = 0;
        grid = record + 0x1E;
        second = record + 0x18;
        do {
            first[outer] = zero;
            second[outer] = zero;
            inner = 0;
            do {
                grid[inner + (outer << 2)] = zero;
                inner += 1;
            } while (inner <= 3);
            {
                register u32 next asm("r0") = outer + 1;

                outer = (u8)next;
            }
        } while (outer <= 5);

        {
            register u32 scaled asm("r1") = id_scaled;
            register u32 current asm("r2") = id;
            register u32 offset asm("r0");
            register u8 *table asm("r1");
            register u8 *src asm("r2");
            register u8 *dst asm("r3");

            offset = scaled - current;
            offset <<= 3;
            table = (u8 *)0x087AFCC4;
            asm volatile("" : "+r"(table));
            offset += (u32)table;
            asm volatile("" : "+r"(offset));
            outer = 0;
            dst = copy_dst;
            src = (u8 *)offset + 0x18;
            do {
                register u32 word_offset asm("r0") = outer << 2;

                *(u32 *)(dst + word_offset) = *(u32 *)(src + word_offset);
                {
                    register u32 next asm("r0") = outer + 1;

                    outer = (u8)next;
                }
            } while (outer <= 3);
        }
    }

    func_080E5880(record, 0);
    *(u16 *)(record + 6) = *(u16 *)(record + 0x3A);
    *(u16 *)(record + 8) = *(u16 *)(record + 0x3E);
    {
        register u8 *globals asm("r1") = (u8 *)0x020218E4;

        globals[1] += 1;
    }
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
    return index;
}
