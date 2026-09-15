#include "m2c_prelude.h"

extern u8 D_02034B4C[];
extern u8 D_0203055C;
extern u8 D_0300603C;

u32 func_080E9D88(u32, u32);
u8 func_080BF464(u32, u32, s32);
void func_080C00B0(u32, u32);

void sub_080C030C(u8 value)
{
    volatile s32 frame[2];
    register s32 outer asm("r5");
    register u8 *scan_base asm("sl");

    {
        register u8 *base asm("r1");
        register u8 *address asm("r2");
        register s32 offset asm("r3");
        register s32 zero asm("r3");
        register s32 offset_2711 asm("r4");
        register s32 offset_2710 asm("r2");
        register u8 *address_2711 asm("r0");
        register u8 *address_2710 asm("r0");

        base = D_02034B4C;
        offset = 0x270F;
        address = base + offset;
        zero = 0;
        *address = value;
        offset_2711 = 0x2711;
        asm volatile("" : : "r"(offset_2711));
        address_2711 = base + offset_2711;
        *address_2711 = zero;
        offset_2710 = 0x2710;
        address_2710 = base + offset_2710;
        *address_2710 = zero;
        frame[1] = zero;
        outer = 0;
        scan_base = base;
    }

    do {
        register u16 inner asm("r6");
        register u32 outer_byte asm("r8");
        register s32 outer_shift asm("r9");
        s32 outer_signed;
        register u32 outer_byte_shift asm("r0");
        register s32 outer_shift_temp asm("r4");

        inner = 0;
        outer_byte_shift = outer << 24;
        outer_shift_temp = outer << 16;
        outer_shift = outer_shift_temp;
        outer_byte = outer_byte_shift >> 24;
        outer_signed = outer_shift_temp >> 16;

        do {
            register u32 inner_byte asm("r4");
            register u32 inner_byte_shift asm("r0");

            inner_byte_shift = inner << 24;
            inner_byte = inner_byte_shift >> 24;
            if ((func_080E9D88(outer_byte, inner_byte) << 24) != 0 &&
                func_080BF464(outer_byte, inner_byte, 25) == 0xFF &&
                func_080BF464(outer_byte, inner_byte, 26) == 0xFF) {
                register s32 inner_shift asm("r2");
                register s32 record_outer asm("r3");
                register s32 inner_signed asm("r0");
                register s32 record_offset asm("r1");
                register s32 raw_best asm("r4");
                register s32 best_shift asm("r0");
                s16 field;
                s16 best;
                register u8 *record asm("r1");

                asm volatile("" : "+r"(inner));
                inner_shift = inner << 16;
                inner_signed = inner_shift >> 16;
                record_offset = inner_signed * 0x270;
                record_outer = outer_shift >> 16;
                record_offset += record_outer * 0x1380;
                record = scan_base + record_offset;
                raw_best = frame[1];
                best_shift = raw_best << 16;
                asm volatile("" : "+r"(best_shift));
                best = best_shift >> 16;
                field = *(s16 *)(record + 10);

                if (best < field)
                    goto choose;
                if (D_0203055C != 1)
                    goto next_inner;
                if (best != field)
                    goto next_inner;
                if (D_0300603C != 0) {
                    if (record_outer == 0)
                        goto choose;
                    goto next_inner;
                }
                if (record_outer == 0)
                    goto next_inner;

choose:
                inner_signed = inner_shift >> 16;
                record_offset = inner_signed * 0x270;
                record_offset += outer_signed * 0x1380;
                record = scan_base + record_offset;
                {
                    register u32 chosen_value asm("r1");
                    register u8 *chosen_outer asm("r1");

                    chosen_value = *(u16 *)(record + 10);
                    frame[1] = chosen_value;
                    chosen_outer = (u8 *)0x0203725E;
                    *chosen_outer = (u8)outer;
                }
            }

next_inner:
            {
                register s32 next asm("r0");
                register s32 step asm("r2");

                next = inner << 16;
                step = 0x10000;
                next += step;
                inner = next >> 16;
                if ((next >> 16) <= 5)
                    continue;

                next = outer << 16;
                next += step;
                outer = (u16)(next >> 16);
                if ((next >> 16) <= 1)
                    break;
                goto first_done;
            }
        } while (1);
    } while (1);

first_done:
    outer = 0;
    do {
        register u16 inner asm("r6");
        register s32 outer_shift asm("r9");
        register u32 outer_byte_shift asm("r0");

        inner = 0;
        outer_byte_shift = outer << 24;
        outer <<= 16;
        outer_shift = outer;
        outer = outer_byte_shift >> 24;

        do {
            register u32 inner_byte asm("r4");
            register u32 inner_byte_shift asm("r0");

            inner_byte_shift = inner << 24;
            inner_byte = inner_byte_shift >> 24;
            if ((func_080E9D88(outer, inner_byte) << 24) != 0 &&
                func_080BF464(outer, inner_byte, 25) == 0xFF &&
                func_080BF464(outer, inner_byte, 26) == 0xFF) {
                func_080C00B0(outer, inner_byte);
            }

            {
                register s32 next asm("r0");
                register s32 step asm("r3");

                asm volatile("" : "+r"(inner));
                next = inner << 16;
                step = 0x10000;
                next += step;
                inner = next >> 16;
                if ((next >> 16) <= 5)
                    continue;

                next = step;
                asm volatile("" : "+r"(next));
                next += outer_shift;
                outer = (u16)(next >> 16);
                if ((next >> 16) <= 1)
                    break;
                goto second_done;
            }
        } while (1);
    } while (1);

second_done:
    {
        register u8 *tail_base asm("r1");
        register s32 index asm("r5");
        register s32 shifted asm("r2");
        s32 index_offset;
        register u8 *index_address asm("r0");
        register s32 index_scratch asm("r0");
        register s32 index_scratch2 asm("r2");
        register s32 index_scratch3 asm("r3");

        tail_base = D_02034B4C;
        index_offset = 0x2711;
        asm volatile("" : "=&r"(index_scratch), "=&r"(index_scratch2),
                       "=&r"(index_scratch3)
                     : "r"(index_offset));
        index_address = index_offset + tail_base;
        index = *index_address;
        shifted = index << 16;
        if (index <= 35) {
            u8 *first;
            u8 *second;
            register u32 mask asm("r4");
            s32 first_offset;
            register s32 second_offset asm("r3");

            first_offset = 0x2713;
            asm volatile("" : : "r"(first_offset));
            first = first_offset + tail_base;
            second_offset = 0x2714;
            second = second_offset + tail_base;
            mask = 0xFF;
            do {
                s32 offset;
                u8 *first_entry;
                u8 *second_entry;

                shifted >>= 16;
                offset = shifted << 1;
                first_entry = (u8 *)((u32)offset + (u32)first);
                second_entry = (u8 *)((u32)offset + (u32)second);
                *second_entry |= mask;
                *first_entry |= mask;
                shifted++;
                shifted <<= 16;
            } while ((shifted >> 16) <= 35);
        }
    }
}
