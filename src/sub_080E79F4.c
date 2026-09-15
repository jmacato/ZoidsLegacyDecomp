#include "m2c_prelude.h"

s32 func_080E7868(u8, s16);

s32 sub_080E79F4(void)
{
    u8 * volatile saved_count;
    register u8 *count asm("r3");
    register u32 outer asm("r6");
    register u8 *table asm("r9");

    {
        register u8 *initial_count asm("r2") = (u8 *)0x02032E35;
        register u32 zero asm("r1") = 0;

        *initial_count = zero;
        outer = 0;
        table = (u8 *)0x087B9364;
        count = initial_count;
    }
    do {
        u8 inner = 0;
        register u32 outer_scaled asm("r8");
        register u32 next_outer asm("sl");

        {
            register u32 value asm("r1") = outer << 4;
            outer_scaled = value;
        }
        {
            register u32 value asm("r2") = outer + 1;
            next_outer = value;
        }
        do {
            register u32 offset asm("r1");
            register u8 *record asm("r2");
            register s32 key asm("r0");

            {
                register u32 inner_offset asm("r0") = inner << 1;
                register u32 outer_offset asm("r1");
                register u32 scaled asm("r4") = outer_scaled;

                inner_offset += inner;
                inner_offset <<= 1;
                outer_offset = scaled - outer;
                outer_offset <<= 2;
                offset = inner_offset + outer_offset;
            }
            record = (u8 *)(offset + (u32)table);
            key = *(s16 *)record;
            if (key != 0) {
                register s32 key_copy asm("r2") = key;
                register u8 *limit_base asm("r4") = (u8 *)0x020280F2;
                register u8 *limit asm("r0");

                asm volatile("" : "+r"(limit_base));
                limit = limit_base + outer;
                if (key_copy > *limit) {
                    limit_base = (u8 *)0x020280EE;
                    asm volatile("" : "+r"(limit_base));
                    limit = limit_base + outer;
                    if (key_copy <= *limit) {
                        register u8 *id_slot asm("r4");
                        register u8 *value_slot asm("r5");
                        register u8 *id_base asm("r0") = table + 2;
                        register u8 *value_base asm("r2");
                        register u32 id asm("r0");
                        register s32 value asm("r1");
                        register s32 result asm("r0");

                        asm volatile("" : "+r"(id_base));
                        id_slot = (u8 *)(offset + (u32)id_base);
                        id = *id_slot;
                        value_base = (u8 *)0x087B9368;
                        value_slot = (u8 *)(offset + (u32)value_base);
                        value = *(s16 *)value_slot;
                        saved_count = count;
                        result = func_080E7868(id, value);
                        result <<= 24;
                        count = saved_count;
                        if (result != 0) {
                            register u8 *output asm("r0");
                            register u32 scratch asm("r1");

                            scratch = 0x02032E36;
                            asm volatile("" : "+r"(scratch));
                            output = (u8 *)(u32)*count;
                            output += scratch;
                            scratch = *(u16 *)id_slot;
                            *output = scratch;
                            scratch = 0x02032E40;
                            asm volatile("" : "+r"(scratch));
                            output = (u8 *)((u32)*count << 1);
                            output += scratch;
                            scratch = *(u16 *)value_slot;
                            *(u16 *)output = scratch;
                            (*count)++;
                        }
                    }
                }
            }
            {
                register u32 next asm("r0") = inner + 1;
                inner = (u8)next;
            }
        } while (inner <= 9);

        {
            register u8 *dest_base asm("r4") = (u8 *)0x020280F2;
            register u8 *dest asm("r1");
            register u8 *source_base asm("r2");
            register u8 *source asm("r0");
            register u32 copied asm("r0");

            asm volatile("" : "+r"(dest_base));
            dest = dest_base;
            dest += outer;
            asm volatile("" : "+r"(dest));
            source_base = (u8 *)0x020280EE;
            asm volatile("" : "+r"(source_base));
            source = source_base;
            source += outer;
            asm volatile("" : "+r"(source));
            copied = *source;
            *dest = copied;
        }
        {
            register u32 value asm("r4") = next_outer;
            register u32 normalized asm("r0") = value << 24;

            outer = normalized >> 24;
        }
    } while (outer <= 3);

    if (*(u8 *)0x02032E35 != 0) {
        return 1;
    }
    return 0;
}
