#include "m2c_prelude.h"

s32 func_080ECF78(s32, s32);

struct Range97C24 {
    u8 start;
    u8 length;
    u16 pad;
    u8 *data;
};

s32 sub_08097C24(s32 arg0, s32 arg1, s16 *arg2)
{
    register u32 first asm("r4");
    register u32 variant asm("r5");
    s16 *out = arg2;
    register struct Range97C24 *ranges asm("r3");
    register u32 i asm("r2");
    register u8 *source asm("r3");

    arg0 <<= 24;
    first = (u32)arg0 >> 24;
    arg1 <<= 24;
    variant = (u32)arg1 >> 24;
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
        register struct Range97C24 *initial asm("r0") =
            (struct Range97C24 *)0x087A0B48;
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
            goto failed;
        }
        {
            register u32 offset asm("r0") = i << 3;
            register u8 *entry asm("r1") =
                (u8 *)(offset + (u32)ranges);

            current_start = entry[0];
            if (current_start > first) {
                goto next_range;
            }
            current_length = entry[1];
        }
check_range:
        current_start += current_length;
        if ((s32)current_start <= (s32)first) {
            goto next_range;
        }
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
        delta = first - *(u8 *)(offset + (u32)ranges);
        delta <<= 4;
        data = *data_slot;
        source = data + delta;
    }
    {
        register u32 count asm("r4") = 0;
        register u32 lane0 asm("r8") = variant << 2;
        u32 lane1_init = variant << 4;
        register u32 lane1 asm("r12") = lane1_init;
        register u32 lane2 asm("r9") = variant << 6;
        register u32 lane3 asm("r5") = variant << 8;

        do {
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
            temp |= lane3;
            temp <<= 6;
            packed |= temp;
            *out++ = packed;
            source += 1;
            next = count + 1;
            next <<= 24;
            count = next >> 24;
        } while (count <= 15U);
    }
    return 1;

failed:
    return 0;
}
