#include "m2c_prelude.h"

extern u8 D_020218E4[];
extern u8 D_02032273[];
extern u8 D_020322A7;
extern u8 D_02027378[];

void sub_080B63C4(void)
{
    register s16 i asm("r6");
    register u8 *countp asm("r2");
    register u8 *count_init asm("r1");
    register u8 *catalog asm("r3");
    register u8 *output asm("r4");
    register u8 *catalog_plus asm("r5");
    register u32 next asm("r0");

    count_init = &D_020322A7;
    *count_init = 0;
    i = 0;
    catalog = D_020218E4;
    catalog_plus = catalog + 0x690C;
    output = D_02032273;
    countp = count_init;
    do {
        register s32 signed_i asm("r0");
        register u8 *entry asm("r1");
        register u32 index asm("r0");

        signed_i = (s16)i;
        entry = (u8 *)((u32)signed_i + (u32)catalog_plus);
        index = *entry;
        if (index != 0) {
            register u32 index_copy asm("r1") = index;
            u8 value;

            asm volatile("" : "+r"(index_copy));
            value = catalog[index_copy * 0x70 + 6];
            if (value != 0) {
                *(u8 *)((u32)*countp + (u32)output) = value;
                *countp += 1;
            }
        }
        next = ((u32)i << 16) + 0x10000;
        i = (u16)(next >> 16);
    } while ((s32)next >> 16 <= 5);

    {
        register u32 prefix_count asm("r8");
        register s16 outer asm("r6");
        register u8 *output asm("r10");
        register u8 *countp asm("r9");
        register s32 prefix_store asm("r3");
        register u32 prefix_shift asm("r5");
        volatile s32 prefix;

        prefix_count = D_020322A7;
        outer = 1;
        prefix_store = prefix_count;
        prefix = prefix_store;
        {
            register u8 *output_seed asm("r0");

            output_seed = D_02032273;
            asm volatile("" : "+r"(output_seed));
            output = output_seed;
        }
        {
            register u8 *count_seed asm("r1");

            count_seed = &D_020322A7;
            asm volatile("" : "+r"(count_seed));
            countp = count_seed;
        }
        do {
            register u32 outer_shift asm("r0");
            register s32 outer_value asm("r2");
            register u32 address asm("r1");
            register u32 addend asm("r3");
            u32 active;
            register u32 retained_outer asm("r12");

            outer_shift = (u16)outer << 16;
            outer_value = (s32)outer_shift >> 16;
            address = outer_value << 6;
            addend = (u32)D_020218E4;
            address += addend;
            addend = 0x5A94;
            address += addend;
            asm volatile("ldrb %0, [%0]" : "+r"(address));
            active = address;
            retained_outer = outer_shift;
            {
                register u32 prefix_seed asm("r0");

                prefix_seed = prefix_count;
                prefix_shift = prefix_seed << 16;
            }
            if (active != 0) {
                register s32 inner asm("r4");
                register u32 inner_next asm("r0");
                register s32 prefix_check asm("r1");

                inner = 0;
                prefix_check = prefix;
                if (inner >= prefix_check)
                    goto duplicate_done;
                {
                    {
                        register u8 *first_output asm("r3");

                        first_output = output;
                        if (first_output[0] == outer_value)
                            goto duplicate_done;
                    }
                    {
                        register s32 prefix_limit asm("r3");
                        register u8 *scan_base asm("r7");
                        register s32 wanted asm("r1");

                        asm volatile("asr %0, %1, #16"
                                     : "=r"(prefix_limit)
                                     : "r"(prefix_shift));
                        scan_base = D_02032273;
                        wanted = outer_value;
                        do {
                            register u32 inner_delta asm("r2");

                            inner_delta = 0x10000;
                            inner_next = ((u32)inner << 16) + inner_delta;
                            inner = (u16)(inner_next >> 16);
                            inner_next = (s32)inner_next >> 16;
                            if ((s32)inner_next >= prefix_limit)
                                break;
                        } while (*(u8 *)((u32)inner_next + (u32)scan_base) != wanted);
                    }
                }
duplicate_done:
                {
                    register s32 final_inner asm("r0");
                    register s32 final_prefix asm("r1");

                    final_inner = (u32)inner << 16;
                    final_inner >>= 16;
                    asm volatile("asr %0, %1, #16"
                                 : "=r"(final_prefix)
                                 : "r"(prefix_shift));
                    if (final_inner == final_prefix) {
                        register u8 *count_view asm("r3");

                        count_view = countp;
                        output[*count_view] = (u8)outer;
                        *count_view += 1;
                    }
                }
            }
            next = 0x10000;
            next += retained_outer;
            outer = (u16)(next >> 16);
        } while ((s32)next >> 16 <= 0x34);

        {
            register u16 pos asm("r6");
            register u8 *key_base asm("r9");
            register s32 prefix_signed asm("r2");
            register s32 prefix_bound asm("r8");
            register u32 pos_shift asm("r1");
            register u32 count_carrier asm("r3");

            prefix_signed = (s32)prefix_shift >> 16;
            pos_shift = 0x10000;
            asm volatile("" : "+r"(pos_shift));
            next = prefix_shift + pos_shift;
            pos = (u16)(next >> 16);
            pos_shift = (u32)pos << 16;
            count_carrier = (u32)&D_020322A7;
            count_carrier = *(u8 *)count_carrier;
            if ((s32)pos < (s32)count_carrier) {
                register u8 *key_seed asm("r3");

                {
                    register u8 *output_seed asm("r0");

                    output_seed = D_02032273;
                    asm volatile("" : "+r"(output_seed));
                    output = output_seed;
                }
                key_seed = D_02027378;
                key_base = key_seed;
                prefix_bound = prefix_signed;
                do {
                    u32 value;
                    register u16 prev asm("r4");
                    register u8 *value_key asm("r5");
                    register u32 key_offset asm("r0");
                    register u8 *key_view asm("r3");
                    register u32 retained_pos asm("r12");
                    register s32 signed_pos asm("r1");
                    register u8 *selected_view asm("r2");
                    register u32 current_address asm("r0");
                    register s32 prev_test asm("r0");

                    signed_pos = (s32)pos_shift >> 16;
                    selected_view = output;
                    current_address = (u32)signed_pos + (u32)selected_view;
                    value = *(u8 *)current_address;
                    key_offset = value * 0x40;
                    key_view = key_base;
                    value_key = (u8 *)((u32)key_offset + (u32)key_view);
                    signed_pos -= 1;
                    signed_pos = (u32)signed_pos << 16;
                    prev = (u16)((u32)signed_pos >> 16);
                    signed_pos = (u32)prev << 16;
                    prev_test = (s32)signed_pos >> 16;
                    retained_pos = (u32)pos << 16;
                    if (prev_test < prefix_bound)
                        goto insert_current;
                    {
                        register u8 *inner_output asm("r6");

                        inner_output = D_02032273;
sort_compare:
                        {
                            register s32 signed_previous asm("r2");
                            register u32 earlier_address asm("r0");
                            register u8 earlier asm("r3");
                            register u32 current_value asm("r1");
                            register u32 earlier_value asm("r0");

                            signed_previous = (s32)signed_pos >> 16;
                            earlier_address = (u32)signed_previous + (u32)inner_output;
                            earlier = *(u8 *)earlier_address;
                            earlier_address = (u32)earlier << 6;
                            earlier_address += (u32)key_base;
                            current_value = value_key[0];
                            earlier_value = *(u8 *)earlier_address;
                            if (current_value >= earlier_value)
                                goto insert_current;
                            {
                                register u32 shift_address asm("r0");
                                register u8 *shift_base asm("r1");

                                shift_address = (u32)signed_previous + 1;
                                shift_base = D_02032273;
                                shift_address += (u32)shift_base;
                                *(u8 *)shift_address = earlier;
                            }
                            {
                                register s32 decremented asm("r0");

                                decremented = signed_previous - 1;
                                decremented = (u32)decremented << 16;
                                prev = (u16)((u32)decremented >> 16);
                            }
                            signed_pos = (u32)prev << 16;
                            prev_test = (s32)signed_pos >> 16;
                            if (prev_test >= prefix_bound)
                                goto sort_compare;
                        }
                    }
insert_current:
                    {
                        register s32 final_index asm("r0");

                        final_index = (s16)prev;
                        final_index += 1;
                        final_index += (u32)output;
                        *(u8 *)final_index = value;
                    }
                    next = retained_pos + 0x10000;
                    pos = (u16)(next >> 16);
                    pos_shift = (u32)pos << 16;
                } while ((s32)pos_shift >> 16 < (s32)D_020322A7);
            }
        }
    }
}
