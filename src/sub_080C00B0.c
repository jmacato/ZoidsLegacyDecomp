#include "m2c_prelude.h"

extern u8 D_02034B4C[];

#define LIST_COUNT (*(u8 *)0x0203725D)

extern u8 func_080BF464(u32, u32, s32);
extern void func_080C007C(s32, s32, s32, s32);

void sub_080C00B0(u32 group, u32 slot)
{
    register u32 group_byte asm("r8");
    register u32 occurrence asm("r5");
    register u32 slot4 asm("r3");
    register u32 group4 asm("r2");
    register u32 score asm("r1");
    register u32 pass asm("r0");
    u32 frame[4];

    group_byte = (u8)group;
    frame[0] = (u8)slot;
    occurrence = (u8)func_080BF464(group_byte, frame[0], 28);
    if (occurrence == 0xFF) {
        register u32 group_copy asm("r4");
        register u32 slot_copy asm("r1");

        frame[1] = 1;
        slot_copy = frame[0];
        slot4 = slot_copy << 2;
        group_copy = group_byte;
        asm("" : "+r"(group_copy));
        group4 = group_copy << 2;
    } else {
        register u8 *record_base asm("r4");
        register u32 offset asm("r1");
        register u32 slot_value asm("r5");
        register u32 group_copy asm("r7");
        u32 slot_offset;
        u32 group_offset;

        record_base = D_02034B4C;
        offset = occurrence * 12;
        slot_value = frame[0];
        slot4 = slot_value << 2;
        slot_offset = ((slot4 + slot_value) * 8 - slot_value) << 4;
        offset += slot_offset;
        group_copy = group_byte;
        group4 = group_copy << 2;
        group_offset = ((group4 + group_copy) * 8 - group_copy) << 7;
        offset += group_offset;
        offset += (u32)record_base;
        frame[1] = (u8)(*(u8 *)(offset + 0xEA) + 1);
    }
    {
        register u32 slot_value asm("r0");
        register u32 address asm("r1");
        register u32 group_copy asm("r3");
        register u32 group_offset asm("r0");
        register u8 *record_base asm("r4");

        slot_value = frame[0];
        address = ((slot4 + slot_value) * 8 - slot_value) << 4;
        group_copy = group_byte;
        group_offset = ((group4 + group_copy) * 8 - group_copy) << 7;
        address += group_offset;
        record_base = D_02034B4C;
        address += (u32)record_base;
        score = *(u16 *)(address + 10);
    }
    pass = 0;
    goto pass_test;

pass_loop:
    {
        register u32 index asm("r5");
        register s32 score_shifted asm("r9");
        register u8 *base asm("r6");
        register u8 *mode_ptr asm("sl");
        register u8 *first_base asm("ip");
        register u32 write_index asm("r0");
        u8 *second_base;

        index = 0;
        score_shifted = score << 16;
        frame[3] = pass + 1;
        second_base = (u8 *)0x0203725D;
        second_base = (u8 *)(u32)*second_base;
        if (index >= (u32)second_base)
            goto found;

        base = D_02034B4C;
        {
            register u32 mode_offset asm("r0");
            register u32 mode0 asm("r1");
            register u32 first_offset asm("r2");
            register u32 second_offset asm("r3");

            mode_offset = 0x270F;
            mode_ptr = base + mode_offset;
            mode0 = *mode_ptr;
            frame[2] = mode0;
            first_offset = 0x2713;
            asm("" : "+r"(first_offset));
            first_offset += (u32)base;
            first_base = (u8 *)first_offset;
            second_offset = 0x2714;
            asm("" : "+r"(second_offset));
            second_base = (u8 *)((u32)base - (0 - second_offset));
        }

scan:
        {
            u32 offset = index << 1;
            register u32 old_score asm("r4");
            register u32 score_offset asm("r4");
            register u8 *score_address asm("r0");

            score_offset = 0x275C;
            asm("" : "+r"(score_offset));
            score_address = base + score_offset;
            score_address = (u8 *)(offset - (0 - (u32)score_address));
            old_score = *(u16 *)score_address;

            if (frame[2] == 0) {
                register u32 first asm("r3");

                first = *(u8 *)(offset - (0 - (u32)first_base));

                if (first != 0xFF ||
                    *(u8 *)(offset - (0 - (u32)second_base)) != 0xFF) {
                    register s32 current asm("r2");
                    register s32 old_signed asm("r0");

                    current = score_shifted >> 16;
                    old_signed = (s16)old_score;
                    if (current > old_signed)
                        goto found;
                    if (current == old_signed &&
                        group_byte == base[0x2712] && first != group_byte)
                        goto found;
                }
            }
            {
                register u8 *mode_copy asm("r3");

                mode_copy = mode_ptr;
                if (*mode_copy == 1) {
                    register u32 first asm("r3");

                    first = *(u8 *)(offset - (0 - (u32)first_base));

                    if (first != 0xFF ||
                        *(u8 *)(offset - (0 - (u32)second_base)) != 0xFF) {
                        register s32 current asm("r2");
                        register s32 old_signed asm("r0");

                        current = score_shifted >> 16;
                        old_signed = (s16)old_score;
                        if (current < old_signed)
                            goto found;
                        if (current == old_signed) {
                            register u8 *tie_base asm("r2");
                            register u32 tie_offset asm("r4");
                            register u32 tie_value asm("r0");
                            register u8 *tie_address asm("r0");

                            tie_base = D_02034B4C;
                            tie_offset = 0x2712;
                            asm("" : "+r"(tie_offset));
                            tie_address = (u8 *)((u32)tie_base -
                                (0 - tie_offset));
                            tie_value = *tie_address;
                            if (group_byte != tie_value && first == tie_value)
                                goto found;
                        }
                    }
                }
            }
            {
                register u8 *mode_copy asm("r2");

                mode_copy = mode_ptr;
                if (*mode_copy == 2) {
                    register u8 *first_copy asm("r3");
                    register u8 *first_address asm("r0");
                    register u32 first asm("r0");

                    first_copy = first_base;
                    asm("" : "+r"(first_copy));
                    first_address = (u8 *)(offset + (u32)first_copy);
                    first = *first_address;

                    if (first == 0xFF &&
                        *(u8 *)(offset - (0 - (u32)second_base)) == 0xFF)
                        goto found;
                }
            }
        }
        {
            register u32 next_index asm("r0");

            next_index = index + 1;
            index = (u8)next_index;
        }
        {
            register u32 next_count asm("r4");

            next_count = 0x0203725D;
            next_count = *(u8 *)next_count;
            if (index < next_count)
                goto scan;
        }

found:
        asm("" : "+r"(index));
        {
            register u8 *found_base asm("r7");
            register u32 found_mode_offset asm("r0");
            register u8 *found_mode asm("r1");
            register u8 *count_address asm("r2");
            register u32 shift_count asm("r0");

            found_base = D_02034B4C;
            found_mode_offset = 0x270F;
            asm("" : "+r"(found_mode_offset));
            found_mode = (u8 *)((u32)found_base -
                (0 - found_mode_offset));
            if (*found_mode != 2) {
                count_address = (u8 *)0x0203725D;
                shift_count = *count_address;
                write_index = shift_count;
                if (shift_count <= index)
                    goto write_entry;
                {
                    register u8 *shift_first asm("ip");
                    register u8 *shift_second asm("sl");
                    register u8 *shift_scores asm("r6");
                    register u8 *first_seed asm("r3");
                    register u8 *second_seed asm("r4");
                    u32 cursor;

                    first_seed = found_mode + 4;
                    asm("" : "+r"(first_seed));
                    shift_first = first_seed;
                    second_seed = found_mode + 5;
                    asm("" : "+r"(second_seed));
                    shift_second = second_seed;
                    shift_scores = found_mode;
                    shift_scores += 0x4D;
                    cursor = shift_count;
shift:
                    {
                        register u32 destination asm("r2");
                        register u32 previous asm("r4");
                        register u32 source asm("r1");

                        destination = cursor << 1;
                        {
                            register u8 *first_copy asm("r7");
                            register u8 *destination_address asm("r3");
                            register u8 *source_address asm("r0");

                            first_copy = shift_first;
                            destination_address = (u8 *)(destination +
                                (u32)first_copy);
                            asm("" : "+r"(destination_address));
                            previous = cursor - 1;
                            source = previous << 1;
                            source_address = (u8 *)(source -
                                (0 - (u32)first_copy));
                            *destination_address = *source_address;
                        }
                        {
                            register u8 *second_copy asm("r0");
                            register u8 *destination_address asm("r3");

                            second_copy = shift_second;
                            destination_address = (u8 *)(destination -
                                (0 - (u32)second_copy));
                            second_copy = (u8 *)(source -
                                (0 - (u32)second_copy));
                            *destination_address = *second_copy;
                        }
                        destination += (u32)shift_scores;
                        source += (u32)shift_scores;
                        *(u16 *)destination = *(u16 *)source;
                        cursor = (u8)previous;
                    }
                    if (cursor > index)
                        goto shift;
                    write_index = cursor;
                    goto write_entry;
                }
            }
            write_index = index;
        }

write_entry:
        asm("" : "+r"(score_shifted));
        {
            register s32 current asm("r4");
            register u32 call_group asm("r1");
            register u32 call_slot asm("r2");
            register u32 sign_copy asm("r3");
            register u32 sign asm("r0");

            current = score_shifted >> 16;
            call_group = group_byte;
            asm("" : "+r"(call_group));
            call_slot = frame[0];
            func_080C007C(write_index, call_group, call_slot, current);
            {
                register u8 *count_ptr asm("r2");
                register u32 count asm("r0");

                count_ptr = (u8 *)0x0203725D;
                count = *count_ptr;
                count++;
                *count_ptr = count;
            }
            sign_copy = score_shifted;
            asm("" : "+r"(sign_copy));
            sign = sign_copy >> 31;
            current += sign;
            current = (u32)current << 15;
            score = (u32)current >> 16;
        }
        {
            register u32 next_pass asm("r4");

            next_pass = frame[3];
            pass = (u8)next_pass;
        }
    }

pass_test:
    {
        register u32 pass_limit asm("r5");

        pass_limit = frame[1];
        if (pass < pass_limit)
            goto pass_loop;
    }
}
