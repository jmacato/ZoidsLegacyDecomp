#include "m2c_prelude.h"

u8 func_080BF464(u8, u8, s32);
s32 func_080E6664(s32);

void sub_080CA238(void) {
    register u32 index asm("r8");
    u8 *record;
    register u32 next_index asm("r6");
    register s32 reserve_r4 asm("r4");
    register s32 reserve_r5 asm("r5");
    register u32 slot asm("r2");

#define SET_NEXT() \
    asm volatile("mov r6, r8\n\tadd r6, #1" : "=r"(next_index) : "r"(index))

    asm volatile("" : "=r"(reserve_r4), "=r"(reserve_r5) : : "r7");
    *(u8 *)0x0203EFA8 = 0;
    index = 0;

loop:
    {
    register u32 stride asm("r0") = 0xA8C;
    register u32 record_offset asm("r2") = index;

    asm volatile("" : "+r"(stride), "+r"(record_offset));
    asm volatile("mul r2, r0" : "+r"(record_offset) : "r"(stride) : "cc");
    {
    register u32 selector_base asm("r1") = 0x02034B4C;
    register u32 selector_offset asm("r3") = 0xA1AF;
    register u32 selector_address asm("r0");
    register u32 selector asm("r1");
    register u32 page_offset asm("r0");
    register u8 *record_base asm("r4");
    register u32 record_base_offset asm("r5");
    register u8 *page_base asm("r1");
    register u8 *count_base asm("r1");
    register u8 *count_ptr asm("r0");
    register u32 halfword asm("r1");
    register u32 bit asm("r0");
    register u8 *filter_base asm("r5");
    asm volatile("" : "+r"(selector_base), "+r"(selector_offset));
    selector_address = selector_base + selector_offset;
    selector = *(u8 *)selector_address;
    page_offset = selector << 3;
    page_offset -= selector;
    page_offset <<= 5;
    page_offset += selector;
    page_offset <<= 2;
    record_base = (u8 *)0x02034B4C;
    record_base_offset = 0x27C8;
    asm volatile("" : "+r"(record_base), "+r"(record_base_offset));
    page_base = record_base + record_base_offset;
    page_offset += (u32)page_base;
    record = (u8 *)(record_offset + page_offset);

    count_base = (u8 *)0x0203EFA9;
    count_ptr = (u8 *)0x0203EFA8;
    asm volatile(
        "ldrb r0, [r0]\n\t"
        "add r0, r0, r1\n\t"
        "mov r1, #0\n\t"
        "strb r1, [r0]"
        : "+r"(count_ptr), "+r"(count_base) : : "cc", "memory");
    halfword = *(u16 *)record;
    bit = 1;
    bit &= halfword;
    filter_base = record_base;

    if (bit == 0) {
        {
        register u8 *other asm("r2");
        if (filter_base[0x27BE] == 0x10) {
            goto type_10;
        }
        other = (u8 *)0x0203730B;
        asm volatile("" : "+r"(other));
        if (*other != 0x10) {
            goto after_type_10;
        }
type_10:
        {
            register u32 masked asm("r1") = *(u32 *)(record + 4);
            register u32 mask asm("r0") = 0x10;
            masked &= mask;
            SET_NEXT();
            if (masked != 0) {
                goto next;
            }
        }
after_type_10:
        ;
        }
        {
        register u8 *other asm("r4");
        register u32 filter_offset asm("r3") = 0x27BE;
        register u32 filter_value asm("r0");
        asm volatile("" : "+r"(filter_offset));
        filter_value = (u32)filter_base + filter_offset;
        filter_value = *(u8 *)filter_value;
        if (filter_value == 0x11) {
            goto type_11;
        }
        other = (u8 *)0x0203730B;
        asm volatile("" : "+r"(other));
        if (*other != 0x11) {
            goto after_type_11;
        }
type_11:
        {
            register u32 masked asm("r1") = *(u32 *)(record + 4);
            register u32 mask asm("r0") = 0x10;
            masked &= mask;
            SET_NEXT();
            if (masked == 0) {
                goto next;
            }
        }
after_type_11:
        ;
        }
        {
        register u8 *other asm("r2");
        register u32 filter_offset asm("r1") = 0x27BE;
        register u32 filter_value asm("r0");
        asm volatile("" : "+r"(filter_offset));
        filter_value = (u32)filter_base + filter_offset;
        filter_value = *(u8 *)filter_value;
        if (filter_value == 0x17) {
            goto type_17;
        }
        other = (u8 *)0x0203730B;
        asm volatile("" : "+r"(other));
        if (*other != 0x17) {
            goto after_type_17;
        }
type_17:
        {
            register u32 masked asm("r1") = *(u32 *)(record + 4);
            register u32 mask asm("r0") = 0xC;
            masked &= mask;
            SET_NEXT();
            if (masked != 0) {
                goto next;
            }
        }
after_type_17:
        asm volatile("" : "+r"(filter_base));
        }
        if ((func_080E6664(0x12) << 24) != 0) {
            register u32 masked asm("r1") = *(u32 *)(record + 4);
            register u32 mask asm("r0") = 0x10;
            masked &= mask;
            SET_NEXT();
            if (masked == 0) {
                goto next;
            }
        }
        if ((func_080E6664(0x13) << 24) != 0) {
            register u32 masked asm("r1") = *(u32 *)(record + 4);
            register u32 mask asm("r0") = 0x10;
            masked &= mask;
            SET_NEXT();
            if (masked != 0) {
                goto next;
            }
        }
    } else {
        if ((func_080E6664(0x14) << 24) != 0) {
            register u32 type asm("r0") = record[4];
            type -= 0x10;
            SET_NEXT();
            if (type <= 2) {
                goto next;
            }
        }
        if ((func_080E6664(0x16) << 24) != 0) {
            register u32 type asm("r0") = record[4];
            SET_NEXT();
            if (type == 0x15) {
                goto next;
            }
        }
    }
    }
    }

    if ((func_080E6664(0x11) << 24) != 0) {
        register u32 compare_index asm("r3");
        SET_NEXT();
        compare_index = index;
        asm volatile("" : "+r"(compare_index));
        if (compare_index <= 3) {
            goto next;
        }
    }

    {
    register u32 halfword asm("r1") = *(u16 *)record;
    register u32 masked asm("r0") = 1;
    masked &= halfword;
    SET_NEXT();
    if (masked == 0) {
        goto collect;
    }
    }

    {
    u32 flags = *(u32 *)(record + 4);
    u8 type = *(u8 *)(record + 4);
    if (type == 0x14) {
        register u8 *base asm("r4") = (u8 *)0x02034B4C;
        register u32 offset asm("r5") = 0x27A4;
        register u32 arg0 asm("r0");
        asm volatile("" : "+r"(base), "+r"(offset));
        arg0 = (u32)base + offset;
        arg0 = *(u8 *)arg0;
        {
        register u8 *arg1_ptr asm("r2") = (u8 *)0x020372F1;
        register u32 arg1 asm("r1");
        register u32 mode asm("r2");
        asm volatile("" : "+r"(arg1_ptr));
        arg1 = *arg1_ptr;
        mode = 0x15;
        if (func_080BF464(arg0, arg1, mode) != 0xFF) {
            goto next;
        }
        }
        goto collect;
    }
    if (type == 0x15) {
        register u8 *base asm("r3") = (u8 *)0x02034B4C;
        register u32 offset asm("r4") = 0x27A4;
        register u32 arg0 asm("r0");
        asm volatile("" : "+r"(base), "+r"(offset));
        arg0 = (u32)base + offset;
        arg0 = *(u8 *)arg0;
        {
        register u8 *arg1_ptr asm("r5") = (u8 *)0x020372F1;
        register u32 arg1 asm("r1");
        asm volatile("" : "+r"(arg1_ptr));
        arg1 = *arg1_ptr;
        if (func_080BF464(arg0, arg1, 0x1C) != 0xFF) {
            goto next;
        }
        }
        goto collect;
    }

    if (flags & 0x40000000) {
        register u8 *search_base asm("r5");
        register u8 *retained_base asm("r9");
        register u32 member_offset asm("sl");
        register u32 member_pointer_offset asm("r1");
        register u32 member_value asm("r1");
        register u32 team_offset asm("r3");
        register u32 team_pointer_offset asm("r3");
        register u32 team_value asm("r1");
        register u32 team_work asm("r0");
        asm volatile("mov r2, #0" : "=r"(slot));
        search_base = (u8 *)0x02034B4C;
        retained_base = search_base;
        member_pointer_offset = 0x27A5;
        asm volatile("" : "+r"(member_pointer_offset));
        team_work = (u32)search_base + member_pointer_offset;
        member_value = *(u8 *)team_work;
        team_work = (member_value << 2) + member_value;
        team_work <<= 3;
        team_work -= member_value;
        member_offset = team_work << 4;
        team_pointer_offset = 0x27A4;
        asm volatile("" : "+r"(team_pointer_offset));
        team_work = (u32)search_base + team_pointer_offset;
        team_value = *(u8 *)team_work;
        team_work = (team_value << 2) + team_value;
        team_work <<= 3;
        team_work -= team_value;
        team_offset = team_work << 7;
search_flagged:
        {
            register u32 entry_offset asm("r0") = slot * 0xC;
            register u32 address asm("r1");
            register u8 *base_copy asm("r4");
            entry_offset += member_offset;
            address = entry_offset + team_offset;
            base_copy = retained_base;
            {
                register u8 *entry asm("r0") = (u8 *)((u32)address - (0 - (u32)base_copy));
                if (*(u16 *)(entry + 0xE8) != 0) {
                    register u8 *flag_address asm("r0") = search_base;
                    register u32 flag_value asm("r0");
                    flag_address += 0xE4;
                    flag_address = (u8 *)((u32)address - (0 - (u32)flag_address));
                    flag_value = *(u32 *)flag_address;
                    {
                    register u32 high_mask asm("r1") = 0x40000000;
                    register u32 masked_flag asm("r0") = flag_value;
                    asm volatile("" : "+r"(high_mask), "+r"(masked_flag));
                    masked_flag &= high_mask;
                    if (masked_flag != 0) {
                        goto search_done;
                    }
                    }
                }
            }
        }
        {
            register u32 next_slot asm("r0") = slot + 1;
            next_slot <<= 24;
            slot = next_slot >> 24;
        }
        if (slot <= 0x1F) {
            goto search_flagged;
        }
    } else {
        register u8 *search_base asm("r4");
        register u32 member_offset asm("r9");
        register u32 member_pointer_offset asm("r5");
        register u32 member_value asm("r1");
        register u32 team_offset asm("r3");
        register u32 team_value asm("r1");
        register u32 team_work asm("r0");
        asm volatile("mov r2, #0" : "=r"(slot));
        search_base = (u8 *)0x02034B4C;
        member_pointer_offset = 0x27A5;
        asm volatile("" : "+r"(member_pointer_offset));
        team_work = (u32)search_base + member_pointer_offset;
        member_value = *(u8 *)team_work;
        team_work = (member_value << 2) + member_value;
        team_work <<= 3;
        team_work -= member_value;
        member_offset = team_work << 4;
        team_value = search_base[0x27A4];
        team_work = (team_value << 2) + team_value;
        team_work <<= 3;
        team_work -= team_value;
        team_offset = team_work << 7;
search_index:
        {
            register u32 entry_offset asm("r0") = slot * 0xC;
            register u16 value asm("r1");
            entry_offset += member_offset;
            entry_offset += team_offset;
            entry_offset += (u32)search_base;
            value = *(u16 *)(entry_offset + 0xE8);
            if (value != 0) {
                register u32 mask asm("r5") = 0xF00;
                register u32 extracted asm("r0") = mask;
                asm volatile("" : "+r"(mask));
                extracted = mask;
                extracted &= value;
                extracted >>= 8;
                if (extracted == index) {
                    goto search_done;
                }
            }
        }
        {
            register u32 next_slot asm("r0") = slot + 1;
            next_slot <<= 24;
            slot = next_slot >> 24;
        }
        if (slot <= 0x1F) {
            goto search_index;
        }
    }

search_done:
    if (slot <= 0x1F) {
        goto next;
    }
    }

collect:
    {
    register u32 has_parts asm("r0") = record[0xA];
    register u8 *out_source asm("r1");
    register u8 *out_count_ptr asm("ip");
    register u8 *counts_source asm("r2");
    register u8 *counts_base asm("r9");
    out_source = (u8 *)0x0203EFA8;
    asm volatile("" : "+r"(out_source));
    out_count_ptr = out_source;
    asm volatile("" : "+r"(out_count_ptr));
    counts_source = (u8 *)0x0203EFA9;
    asm volatile("" : "+r"(counts_source));
    counts_base = counts_source;
    asm volatile("" : "+r"(counts_base));
    if (has_parts != 0) {
        register u32 part asm("r3") = 0;
        register u8 *slots_source asm("r4") = (u8 *)0x0203EF78;
        register u8 *slots_base asm("sl");
        register u8 *counts_copy asm("r5");
        register u8 *out_count_copy asm("r4");
        asm volatile("" : "+r"(slots_source));
        slots_base = slots_source;
        asm volatile("" : "+r"(slots_base));
        counts_copy = counts_base;
        out_count_copy = out_count_ptr;
        do {
            register u32 part_offset asm("r0") = part;
            part_offset *= 0x94;
            part_offset = (u32)record - (0 - part_offset);
            if (*(u8 *)(part_offset + 0xC) != 0) {
                register u32 out asm("r1") = *out_count_copy;
                register u8 *count_ptr asm("r2") = (u8 *)((u32)out - (0 - (u32)counts_copy));
                register u32 slot_offset asm("r0") = out * 6;
                register u32 count asm("r2");
                asm volatile("" : "+r"(slot_offset));
                count = *count_ptr;
                slot_offset += count;
                slot_offset += (u32)slots_base;
                *(u8 *)slot_offset = part;
                out = *out_count_copy;
                out = (u32)out - (0 - (u32)counts_copy);
                {
                    register u32 next_count asm("r0") = *(u8 *)out;
                    next_count++;
                    *(u8 *)out = next_count;
                }
            }
            {
                register u32 next_part asm("r0") = part + 1;
                next_part <<= 24;
                part = next_part >> 24;
            }
        } while (part <= 5);
    }

    {
        register u8 *out_count_copy asm("r5") = out_count_ptr;
        register u32 out asm("r1") = *out_count_copy;
        register u8 *counts_copy asm("r2") = counts_base;
        register u8 *count_ptr asm("r0") = (u8 *)((u32)out - (0 - (u32)counts_copy));
        if (*count_ptr != 0) {
            count_ptr = (u8 *)0x0203EF70;
            asm volatile("" : "+r"(count_ptr));
            count_ptr = (u8 *)((u32)out - (0 - (u32)count_ptr));
            {
                register u32 out_index asm("r3") = index;
                *count_ptr = out_index;
            }
            {
                register u32 next_out asm("r0") = *out_count_copy;
                next_out++;
                *out_count_copy = next_out;
            }
        }
    }
    }

next:
    {
    register u32 normalized_index asm("r0") = next_index;
    normalized_index <<= 24;
    normalized_index >>= 24;
    index = normalized_index;
    if (normalized_index <= 7) {
        goto loop;
    }
    }
    asm volatile("" : : : "r9", "sl");
#undef SET_NEXT
}
