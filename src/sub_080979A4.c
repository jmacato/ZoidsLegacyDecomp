#include "m2c_prelude.h"

u32 sub_080979A4(u32 requested, u16 *out)
{
    register u32 count asm("r10");
    register u32 word_index asm("r6");
    register u16 *cursor asm("r4");
    register u32 *masks asm("r9");
    register u32 *limit asm("r8");
    register u32 *limit_view asm("r7");
    register u32 *mask_source;
    register u32 *limit_source asm("r1");
    register u32 zero asm("r1");
    register u32 request_value asm("r2");
    register u32 request asm("r12");

    request_value = requested;
    cursor = out;
    asm volatile("" : "+r"(request_value));
    request_value <<= 24;
    request_value >>= 24;
    request = request_value;
    zero = 0;
    count = zero;
    word_index = 0;
    mask_source = (u32 *)0x0200DD90;
    masks = mask_source;
    asm volatile("" : "+r"(mask_source), "+r"(zero) : : "r0", "r2", "r3", "r5", "r8");
    limit_source = (u32 *)0x02021658;
    asm volatile("" : "+r"(limit_source) : : "r7");
    limit = limit_source;
    asm volatile("" : "+r"(limit));
    do {
        register u32 bit_index asm("r5");
        register u32 bits asm("r3");
        register u32 mask_offset asm("r1");

        mask_offset = word_index << 2;
        bits = *(u32 *)((u32)masks + mask_offset);
        bit_index = 0;
        do {
            register u32 available asm("r1") = 1;
            register u32 emitted asm("r1");
            register u32 observed asm("r2");
            register u32 maximum asm("r1");

            if ((available & bits) == 0) {
                emitted = ((u32)word_index << 5) + bit_index;
                *cursor = emitted;
                observed = *cursor;
                limit_view = limit;
                maximum = *limit_view;

                if (observed < maximum) {
                    goto success;
                }
                {
                    register u32 failed asm("r0") = 0;
                    asm volatile("" : "+r"(failed));
                    return failed;
                }
success:
                { register u32 next asm("r1") = count + 1; next <<= 24; count = next >> 24; }
                if (count == request) return 1;
                cursor++;
            }
            bits >>= 1;
            { register u32 next asm("r1") = bit_index + 1; next <<= 24; bit_index = next >> 24; }
        } while (bit_index <= 31);
        { register u32 next asm("r1") = word_index + 1; next <<= 24; word_index = next >> 24; }
    } while (word_index <= 31);
    {
        register u32 terminal asm("r0");
        return terminal;
    }
}
