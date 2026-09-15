#include "m2c_prelude.h"
void sub_080ACBDC(s32 arg0, s32 arg1) {
    volatile u32 count;
    u8 index;
    register u16 start_input asm("r0");
    register s32 position asm("r0");
    u8 record_index;
    s32 record_offset;
    u8 *record;
    s32 **second_table;
    register s32 set_mask asm("r5");
    register s32 start asm("r9");
    register s32 **first_table asm("r12");
    register u8 *record_base asm("r10");
    register s32 clear_mask asm("r8");

    arg0 <<= 24;
    count = (u32)arg0 >> 24;
    arg1 <<= 16;
    start_input = (u32)arg1 >> 16;
    index = 0;
    if (index < count) {
        start = (s16)start_input;
        {
            register s32 **first_input asm("r2");

            first_input = (s32 **)0x02032A88;
            asm volatile("" : "+r"(first_input));
            first_table = first_input;
        }
        set_mask = 0x20000;
        {
            register s32 **second_input asm("r7");

            second_input = (s32 **)0x02032AA8;
            second_table = second_input;
        }
        {
            register u8 *record_input asm("r6");

            record_input = (u8 *)0x020218E8;
            asm volatile("" : "+r"(record_input));
            record_base = record_input;
        }
        {
            register s32 clear_input asm("r0");

            clear_input = 0xFFFDFFFF;
            clear_mask = clear_input;
        }
        do {
            register s32 start_view asm("r1");

            start_view = start;
            position = start_view + index;
            if (position >= 0 && position < ({
                register u8 *bound_ptr asm("r2");
                register s32 bound asm("r2");

                bound_ptr = (u8 *)0x02032272;
                bound = *bound_ptr;
                bound;
            })) {
                record_index = ({
                    register u8 *lookup asm("r6");
                    register u8 *lookup_address asm("r0");

                    lookup = (u8 *)0x020321A4;
                    lookup_address = (u8 *)position;
                    asm volatile("" : "+r"(lookup_address));
                    lookup_address += (s32)lookup;
                    *lookup_address;
                });
                record_offset = record_index * 0x70;
                {
                    register u8 *base_view asm("r1");

                    base_view = record_base;
                    asm volatile("" : "+r"(base_view));
                    record = (u8 *)(record_offset + (s32)base_view);
                }
                {
                    register u16 flags asm("r1");

                    flags = *(u16 *)(record + 4);
                    asm volatile("" : "+r"(flags));
                    if (flags & 4) {
                        s32 *slot;
                        register s32 **slot_address asm("r0");
                        s32 value;
                        s32 offset;
                        register s32 **table_view asm("r6");

                        offset = index << 2;
                        table_view = first_table;
                        slot_address = (s32 **)(offset + (s32)table_view);
                        slot = *slot_address;
                        value = *slot;
                        value &= clear_mask;
                        *slot = value;
                    } else {
                        s32 *slot;
                        s32 value;

                        slot = first_table[index];
                        value = *slot;
                        value |= set_mask;
                        *slot = value;
                    }
                }
                {
                    register u16 flags asm("r1");

                    flags = *(u16 *)(record + 4);
                    asm volatile("" : "+r"(flags));
                    if (flags & 1) {
                        s32 *slot;
                        s32 value;

                        slot = second_table[index];
                        value = *slot;
                        value &= clear_mask;
                        *slot = value;
                    } else {
                        s32 *slot;
                        s32 value;

                        slot = second_table[index];
                        value = *slot;
                        value |= set_mask;
                        *slot = value;
                    }
                }
            } else {
                s32 *first_slot;
                s32 *second_slot;

                first_slot = first_table[index];
                *first_slot |= set_mask;
                second_slot = second_table[index];
                *second_slot |= set_mask;
            }
            index++;
        } while (index < count);
    }
}
