#include "m2c_prelude.h"

s32 func_080ECF78(s32, s32);

struct Range97A2C {
    u16 start;
    u8 length;
    u8 pad;
    u8 *data;
};

s32 sub_08097A2C(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3)
{
    register u32 first asm("r4");
    register u32 variant asm("r6");
    register struct Range97A2C *ranges asm("r3");
    register u32 i asm("r2");
    register u8 *source asm("r5");
    s16 *output_slots[2];

    arg0 <<= 16;
    first = (u32)arg0 >> 16;
    arg1 <<= 24;
    variant = (u32)arg1 >> 24;
    output_slots[0] = arg2;
    output_slots[1] = arg3;
    {
        register u32 result asm("r0") = func_080ECF78(variant, 3);

        result += 1;
        result <<= 24;
        variant = result >> 24;
    }

    i = 0;
    {
        register u32 current_start asm("r0");
        register u32 current_length asm("r1");
        register struct Range97A2C *initial asm("r0") =
            (struct Range97A2C *)0x087A0A98;
        register u32 first_start asm("r1");

        first_start = initial->start;
        ranges = initial;
        if (first_start <= first) {
            current_start = ranges->start;
            current_length = ranges->length;
            goto check_range;
        }

next_range:
        {
            register u32 next asm("r0") = i + 1;

            next <<= 24;
            i = next >> 24;
        }
        if (i > 21U) {
            goto end_search;
        }
        {
            register u32 offset asm("r0") = i << 3;
            register u8 *entry asm("r1") =
                (u8 *)(offset + (u32)ranges);

            current_start = *(u16 *)entry;
            if (current_start > first) {
                goto next_range;
            }
            current_length = entry[2];
        }
check_range:
        current_start += current_length;
        if ((s32)current_start <= (s32)first) {
            goto next_range;
        }
    }

end_search:
    if (i == 22U) {
        i = 0;
        first = 0x81A0;
    }
    if (i > 21U) {
        goto failed;
    }
    {
        register u32 offset asm("r0") = i << 3;
        register u8 *data_base asm("r1") = (u8 *)ranges + 4;
        register u8 **data_slot asm("r1");
        register u32 delta asm("r0");
        register u8 *data asm("r1");

        data_slot = (u8 **)(offset + (u32)data_base);
        delta = first - *(u16 *)(offset + (u32)ranges);
        delta <<= 5;
        data = *data_slot;
        source = data + delta;
    }
    {
        register u32 outer asm("r2") = 0;
        register u32 lane0 asm("r10") = variant << 2;
        register u32 lane1 asm("r9");
        register u32 lane2 asm("r8");
        register u32 lane3 asm("r12");
        s16 **outputs;

        {
            register u32 lane_init asm("r1") = variant << 4;

            asm volatile("" :: "r"(lane_init));
            lane1 = lane_init;
        }
        {
            register u32 lane_init asm("r7") = variant << 6;

            asm volatile("" :: "r"(lane_init));
            lane2 = lane_init;
        }
        lane3 = variant << 8;
        {
            register s16 **outputs_init asm("r0") = output_slots;

            asm volatile("" : "+r"(outputs_init));
            outputs = outputs_init;
        }

        do {
            register u32 inner asm("r6") = 0;
            u32 next_outer;
            s16 **current;

            {
                register u32 next_init asm("r1") = outer + 1;

                asm volatile("" : "+r"(next_init));
                next_outer = next_init;
            }
            {
                register u32 offset_init asm("r0") = outer << 2;
                register s16 **base_init asm("r2") = outputs;

                asm volatile("" : "+r"(offset_init), "+r"(base_init));
                current = (s16 **)(offset_init + (u32)base_init);
            }

            do {
                register s16 *out asm("r3") = *current;
                register u32 value asm("r2") = *source;
                register u32 packed asm("r1") = 3;
                register u32 temp asm("r0");
                u32 lane_view;
                register u32 next asm("r0");

                packed &= value;
                lane_view = lane0;
                packed |= lane_view;
                temp = 0xC;
                temp &= value;
                lane_view = lane1;
                temp |= lane_view;
                temp <<= 2;
                packed |= temp;
                temp = 0x30;
                temp &= value;
                lane_view = lane2;
                temp |= lane_view;
                temp <<= 4;
                packed |= temp;
                temp = 0xC0;
                temp &= value;
                lane_view = lane3;
                temp |= lane_view;
                temp <<= 6;
                packed |= temp;
                *out++ = packed;
                *current = out;
                source += 1;
                next = inner + 1;
                next <<= 24;
                inner = next >> 24;
            } while (inner <= 15U);

            {
                register u32 next_reload asm("r7") = next_outer;
                register u32 outer_value asm("r0");

                asm volatile("" : "+r"(next_reload));
                outer_value = next_reload;
                outer_value <<= 24;
                outer = outer_value >> 24;
            }
        } while (outer <= 1U);
    }
    return 1;

failed:
    return 0;
}
