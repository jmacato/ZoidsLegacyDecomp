#include "m2c_prelude.h"

#define NULL ((void *)0)

struct ByteAt26 {
    u8 pad[0x1A];
    u8 value;
};

M2C_UNK jtbl_080E60D0();                            /* static */
M2C_UNK jtbl_080E6170();                            /* static */

s32 sub_080E60B0(s32 arg0) {
    register s32 first asm("r0") = arg0;
    register u32 temp_r0 asm("r0");
    u32 temp_r1;
    u8 temp_r1_2;
    register u32 temp_r4 asm("r4");
    u8 var_r2;
    u8 var_r2_2;
    u8 var_r2_3;
    u8 var_r2_4;
    void *var_r2_5;
    void *var_r3;
    void *var_r3_10;
    void *var_r3_11;
    void *var_r3_12;
    void *var_r3_2;
    void *var_r3_3;
    void *var_r3_4;
    void *var_r3_5;
    void *var_r3_6;
    void *var_r3_7;
    void *var_r3_8;
    void *var_r3_9;
    register u8 *case9_base asm("r8");
    register s32 case9_slots asm("r2");
    register u32 case9_entity asm("r0");

    asm volatile(
        "lsl %0, %0, #24\n\t"
        "lsr %1, %0, #24"
        : "+r"(first), "=r"(temp_r4)
        :
        : "cc");
    temp_r0 = temp_r4 - 1;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
    case 1:                                         /* switch 1 */
    case 2:                                         /* switch 1 */
    case 3:                                         /* switch 1 */
    case 22: {                                      /* switch 1 */
        register u8 *shared_base asm("r8");
        register s32 shared_slots asm("r4");

        var_r2 = 0;
        {
            register u32 shared_index_seed asm("r3") = 0;

            asm volatile("" : "+r"(shared_index_seed));
            var_r3 = (void *)shared_index_seed;
        }
        temp_r1 = temp_r4 - 1;
        shared_base = (u8 *)0x020218E4;
        shared_slots = 0x690C;
        asm volatile("" : "+r"(shared_base), "+r"(shared_slots));
        shared_slots += (s32)shared_base;
        do {
            if (*(u8 *)((u32)var_r3 + (u32)shared_slots) != 0) {
                var_r2 += 1;
            }
            var_r3 = (void *) (u8) (var_r3 + 1);
        } while ((u32) var_r3 <= 5U);
        switch (temp_r1) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            if ((u32) var_r2 <= 1U) {
                goto block_117;
            }
block_13:
            return 0;
        case 1:                                     /* switch 2 */
            if ((u32) var_r2 <= 2U) {
                goto block_117;
            }
            goto block_13;
        case 2:                                     /* switch 2 */
            if ((u32) var_r2 <= 3U) {
                goto block_117;
            }
            goto block_13;
        case 3:                                     /* switch 2 */
            if ((u32) var_r2 <= 4U) {
                goto block_117;
            }
            goto block_13;
        case 22:                                    /* switch 2 */
            if (var_r2 == 2) {
                goto block_117;
            }
            goto block_13;
        default:                                    /* switch 2 */
            goto block_117;
        }
        break;
    }
    case 4: {                                       /* switch 1 */
        register u8 *case4_base asm("r8");
        register u8 *case4_base_seed asm("r1");
        register s32 case4_slots asm("r2");
        register u32 case4_entity asm("r0");

        var_r3_2 = NULL;
        case4_base_seed = (u8 *)0x020218E4;
        asm volatile("mov %0, %1"
                     : "=r"(case4_base)
                     : "r"(case4_base_seed));
        case4_slots = 0x690C;
        asm volatile("" : "+r"(case4_base), "+r"(case4_slots));
        case4_slots += (s32)case4_base;
        do {
            asm volatile(
                "add r1, %1, %2\n\t"
                "ldrb %0, [r1]"
                : "=r"(case4_entity)
                : "r"(var_r3_2), "r"(case4_slots)
                : "r1", "cc", "memory");
            if ((case4_entity != 0) && (case4_base[(case4_entity * 0x70) + 0x3C] != 0)) {
                goto block_13;
            }
            var_r3_2 = (void *) (u8) (var_r3_2 + 1);
        } while ((u32) var_r3_2 <= 5U);
        goto block_117;
    }
    case 5: {                                       /* switch 1 */
        register u8 *case5_base asm("r8");
        register s32 case5_slots asm("r2");
        register u32 case5_entity asm("r0");

        var_r3_3 = NULL;
        case5_base = (u8 *)0x020218E4;
        case5_slots = 0x690C;
        asm volatile("" : "+r"(case5_base), "+r"(case5_slots));
        case5_slots += (s32)case5_base;
        do {
            asm volatile(
                "add r1, %1, %2\n\t"
                "ldrb %0, [r1]"
                : "=r"(case5_entity)
                : "r"(var_r3_3), "r"(case5_slots)
                : "r1", "cc", "memory");
            if ((case5_entity != 0) && ((u32)case5_base[(case5_entity * 0x70) + 0x3C] > 1U)) {
                goto block_13;
            }
            var_r3_3 = (void *) (u8) (var_r3_3 + 1);
        } while ((u32) var_r3_3 <= 5U);
        goto block_117;
    }
    case 6: {                                       /* switch 1 */
        register u8 *case6_base asm("r8");
        register u8 *case6_base_seed asm("r1");
        register s32 case6_slots asm("r2");
        register u32 case6_entity asm("r0");

        var_r3_4 = NULL;
        case6_base_seed = (u8 *)0x020218E4;
        asm volatile("mov %0, %1"
                     : "=r"(case6_base)
                     : "r"(case6_base_seed));
        case6_slots = 0x690C;
        asm volatile("" : "+r"(case6_base), "+r"(case6_slots));
        case6_slots += (s32)case6_base;
        do {
            asm volatile(
                "add r1, %1, %2\n\t"
                "ldrb %0, [r1]"
                : "=r"(case6_entity)
                : "r"(var_r3_4), "r"(case6_slots)
                : "r1", "cc", "memory");
            if ((case6_entity != 0) && (case6_base[(case6_entity * 0x70) + 0x3C] != 1)) {
                goto block_13;
            }
            var_r3_4 = (void *) (u8) (var_r3_4 + 1);
        } while ((u32) var_r3_4 <= 5U);
        goto block_117;
    }
    case 7: {                                       /* switch 1 */
        register u8 *case7_base asm("r8");
        register s32 case7_slots asm("r2");
        register u32 case7_entity asm("r0");

        var_r3_5 = NULL;
        case7_base = (u8 *)0x020218E4;
        case7_slots = 0x690C;
        asm volatile("" : "+r"(case7_base), "+r"(case7_slots));
        case7_slots += (s32)case7_base;
        do {
            asm volatile(
                "add r1, %1, %2\n\t"
                "ldrb %0, [r1]"
                : "=r"(case7_entity)
                : "r"(var_r3_5), "r"(case7_slots)
                : "r1", "cc", "memory");
            if ((case7_entity != 0) && ((u32)case7_base[(case7_entity * 0x70) + 0x3C] > 2U)) {
                goto block_13;
            }
            var_r3_5 = (void *) (u8) (var_r3_5 + 1);
        } while ((u32) var_r3_5 <= 5U);
        goto block_117;
    }
    case 8: {                                       /* switch 1 */
        register u8 *case8_base asm("r8");
        register u8 *case8_base_seed asm("r1");
        register s32 case8_slots asm("r2");
        register u32 case8_entity asm("r0");

        var_r3_6 = NULL;
        case8_base_seed = (u8 *)0x020218E4;
        asm volatile("mov %0, %1"
                     : "=r"(case8_base)
                     : "r"(case8_base_seed));
        case8_slots = 0x690C;
        asm volatile("" : "+r"(case8_base), "+r"(case8_slots));
        case8_slots += (s32)case8_base;
loop_50:
        asm volatile(
            "add r1, %1, %2\n\t"
            "ldrb %0, [r1]"
            : "=r"(case8_entity)
            : "r"(var_r3_6), "r"(case8_slots)
            : "r1", "cc", "memory");
        if ((case8_entity == 0) || ((u32)case8_base[(case8_entity * 0x70) + 0x3C] <= 1U)) {
            var_r3_6 = (void *) (u8) (var_r3_6 + 1);
            if ((u32) var_r3_6 > 5U) {

            } else {
                goto loop_50;
            }
        }
        goto block_59;
    }
    case 9:                                         /* switch 1 */
        var_r3_6 = NULL;
        case9_base = (u8 *)0x020218E4;
        case9_slots = 0x690C;
        asm volatile("" : "+r"(case9_base), "+r"(case9_slots));
        case9_slots += (s32)case9_base;
loop_56:
        asm volatile(
            "add r1, %1, %2\n\t"
            "ldrb %0, [r1]"
            : "=r"(case9_entity)
            : "r"(var_r3_6), "r"(case9_slots)
            : "r1", "cc", "memory");
        if ((case9_entity == 0) || ((u32)case9_base[(case9_entity * 0x70) + 0x3C] <= 2U)) {
            var_r3_6 = (void *) (u8) (var_r3_6 + 1);
            if ((u32) var_r3_6 <= 5U) {
                goto loop_56;
            }
        }
block_59:
        if (var_r3_6 != (void *)6) {
            goto block_117;
        }
        goto block_13;
    case 10: {                                      /* switch 1 */
        register u8 *case10_base asm("r8");
        register u8 *case10_base_seed asm("r1");
        register s32 case10_slots asm("r2");
        register u32 case10_mask asm("r4");
        register u32 case10_entity asm("r0");
        register u32 case10_copy asm("r1");

        var_r3_7 = NULL;
        case10_base_seed = (u8 *)0x020218E4;
        asm volatile("mov %0, %1"
                     : "=r"(case10_base)
                     : "r"(case10_base_seed));
        case10_slots = 0x690C;
        asm volatile("" : "+r"(case10_base), "+r"(case10_slots));
        case10_slots += (s32)case10_base;
        case10_mask = 0x40;
        do {
            asm volatile(
                "add r1, %1, %2\n\t"
                "ldrb %0, [r1]"
                : "=r"(case10_entity)
                : "r"(var_r3_7), "r"(case10_slots)
                : "r1", "cc", "memory");
            if (case10_entity != 0) {
                case10_copy = case10_entity;
                case10_entity = case10_copy << 3;
                case10_entity -= case10_copy;
                case10_entity <<= 4;
                case10_entity += (u32)case10_base;
                case10_entity += 0x3A;
                case10_copy = *(u8 *)case10_entity;
                case10_entity = case10_mask;
                case10_entity &= case10_copy;
                if (case10_entity != 0) {
                    goto block_13;
                }
            }
            var_r3_7 = (void *) (u8) (var_r3_7 + 1);
        } while ((u32) var_r3_7 <= 5U);
        goto block_117;
    }
    case 11: {                                      /* switch 1 */
        register u8 *case11_base asm("r8");
        register s32 case11_slots asm("r2");
        register u32 case11_mask asm("r4");
        register u32 case11_entity asm("r0");
        register u32 case11_copy asm("r1");

        var_r3_8 = NULL;
        case11_base = (u8 *)0x020218E4;
        case11_slots = 0x690C;
        asm volatile("" : "+r"(case11_base), "+r"(case11_slots));
        case11_slots += (s32)case11_base;
        case11_mask = 0x40;
        do {
            asm volatile(
                "add r1, %1, %2\n\t"
                "ldrb %0, [r1]"
                : "=r"(case11_entity)
                : "r"(var_r3_8), "r"(case11_slots)
                : "r1", "cc", "memory");
            if (case11_entity != 0) {
                case11_copy = case11_entity;
                case11_entity = case11_copy << 3;
                case11_entity -= case11_copy;
                case11_entity <<= 4;
                case11_entity += (u32)case11_base;
                case11_entity += 0x3A;
                case11_copy = *(u8 *)case11_entity;
                case11_entity = case11_mask;
                case11_entity &= case11_copy;
                if (case11_entity == 0) {
                    goto block_13;
                }
            }
            var_r3_8 = (void *) (u8) (var_r3_8 + 1);
        } while ((u32) var_r3_8 <= 5U);
        goto block_117;
    }
    case 12: {                                      /* switch 1 */
        register u8 *case12_base asm("r8");
        register u8 *case12_base_seed asm("r1");
        register s32 case12_offset asm("r0");
        register u8 *case12_slots asm("ip");
        register struct ByteAt26 *case12_table asm("r7");
        register u32 case12_entity asm("r0");
        register u32 case12_value asm("r1");

        var_r3_9 = NULL;
        case12_base_seed = (u8 *)0x020218E4;
        asm volatile("mov %0, %1"
                     : "=r"(case12_base)
                     : "r"(case12_base_seed));
        case12_offset = 0x690C;
        asm volatile("" : "+r"(case12_base), "+r"(case12_offset));
        case12_slots = (u8 *)((s32)case12_base + case12_offset);
        case12_table = (struct ByteAt26 *)0x087A5810;
        do {
            asm volatile(
                "mov r0, %1\n\t"
                "add r1, %2, r0\n\t"
                "ldrb %0, [r1]"
                : "=&r"(case12_entity)
                : "r"(case12_slots), "r"(var_r3_9)
                : "r1", "cc", "memory");
            if (case12_entity != 0) {
            register u8 *case12_inner_table asm("r6");

            var_r2_2 = 0;
            case12_value = case12_entity << 3;
            case12_value -= case12_entity;
            case12_value <<= 4;
            case12_value += (u32)case12_base;
            case12_entity = *(u8 *)(case12_value + 4);
            case12_inner_table = (u8 *)0x087A5810;
            asm volatile("" : "+r"(case12_inner_table));
            asm volatile("ldrb %0, [%1, #26]"
                         : "=r"(case12_value)
                         : "r"(case12_table)
                         : "memory");
            if (case12_entity != case12_value) {
                register u8 *case12_inner_base asm("r5");
                register s32 case12_inner_offset asm("r1");
                register u8 *case12_inner_slot asm("r4");

                case12_inner_base = (u8 *)0x020218E4;
                case12_inner_offset = 0x690C;
                asm volatile("" : "+r"(case12_inner_base), "+r"(case12_inner_offset));
                asm volatile(
                    "add r0, %1, %2\n\t"
                    "add %0, %3, r0"
                    : "=r"(case12_inner_slot)
                    : "r"(case12_inner_base), "r"(case12_inner_offset), "r"(var_r3_9)
                    : "r0", "cc");
                case12_inner_table += 0x1A;
loop_78:
                var_r2_2 += 1;
                if ((u32) var_r2_2 <= 0x19U) {
                    if (case12_inner_base[(*case12_inner_slot * 0x70) + 4] != *(u8 *)((u32)var_r2_2 + (u32)case12_inner_table)) {
                        goto loop_78;
                    }
                }
            }
            if (var_r2_2 == 0x1A) {
                goto block_13;
            }
            }
            var_r3_9 = (void *) (u8) (var_r3_9 + 1);
        } while ((u32) var_r3_9 <= 5U);
        goto block_117;
    }
    case 13: {                                      /* switch 1 */
        register u8 *case13_base asm("r8");
        register s32 case13_offset asm("r1");
        register u8 *case13_slots asm("ip");
        register u8 *case13_table asm("r7");
        register u32 case13_entity asm("r0");
        register u32 case13_value asm("r1");

        var_r3_10 = NULL;
        case13_base = (u8 *)0x020218E4;
        case13_offset = 0x690C;
        asm volatile("" : "+r"(case13_base), "+r"(case13_offset));
        case13_slots = (u8 *)((s32)case13_base + case13_offset);
        case13_table = (u8 *)0x087A58AC;
        do {
            asm volatile(
                "mov r0, %1\n\t"
                "add r1, %2, r0\n\t"
                "ldrb %0, [r1]"
                : "=&r"(case13_entity)
                : "r"(case13_slots), "r"(var_r3_10)
                : "r1", "cc", "memory");
            if (case13_entity != 0) {
            register u8 *case13_inner_table asm("r6");

            var_r2_3 = 0;
            case13_value = case13_entity << 3;
            case13_value -= case13_entity;
            case13_value <<= 4;
            case13_value += (u32)case13_base;
            case13_entity = *(u8 *)(case13_value + 4);
            case13_inner_table = (u8 *)0x087A5810;
            asm volatile("" : "+r"(case13_inner_table));
            asm volatile("ldrb %0, [%1, #0]"
                         : "=r"(case13_value)
                         : "r"(case13_table)
                         : "memory");
            if (case13_entity != case13_value) {
                register u8 *case13_inner_base asm("r5");
                register s32 case13_inner_offset asm("r1");
                register u8 *case13_inner_slot asm("r4");

                case13_inner_base = (u8 *)0x020218E4;
                case13_inner_offset = 0x690C;
                asm volatile("" : "+r"(case13_inner_base), "+r"(case13_inner_offset));
                asm volatile(
                    "add r0, %1, %2\n\t"
                    "add %0, %3, r0"
                    : "=r"(case13_inner_slot)
                    : "r"(case13_inner_base), "r"(case13_inner_offset), "r"(var_r3_10)
                    : "r0", "cc");
                case13_inner_table += 0x9C;
loop_89:
                var_r2_3 += 1;
                if ((u32) var_r2_3 <= 0x19U) {
                    if (case13_inner_base[(*case13_inner_slot * 0x70) + 4] != *(u8 *)((u32)var_r2_3 + (u32)case13_inner_table)) {
                        goto loop_89;
                    }
                }
            }
            if (var_r2_3 == 0x1A) {
                goto block_13;
            }
            }
            var_r3_10 = (void *) (u8) (var_r3_10 + 1);
        } while ((u32) var_r3_10 <= 5U);
        goto block_117;
    }
    case 14: {                                      /* switch 1 */
        register u8 *case14_base asm("r8");
        register u8 *case14_base_seed asm("r0");
        register s32 case14_offset asm("r1");
        register u8 *case14_slots asm("ip");
        register u8 *case14_table asm("r7");
        register u32 case14_entity asm("r0");
        register u32 case14_value asm("r1");

        var_r3_11 = NULL;
        case14_base_seed = (u8 *)0x020218E4;
        asm volatile("mov %0, %1"
                     : "=r"(case14_base)
                     : "r"(case14_base_seed));
        case14_offset = 0x690C;
        asm volatile("" : "+r"(case14_base), "+r"(case14_offset));
        case14_slots = (u8 *)((s32)case14_base + case14_offset);
        case14_table = (u8 *)0x087A58C6;
        do {
            asm volatile(
                "mov r0, %1\n\t"
                "add r1, %2, r0\n\t"
                "ldrb %0, [r1]"
                : "=&r"(case14_entity)
                : "r"(case14_slots), "r"(var_r3_11)
                : "r1", "cc", "memory");
            if (case14_entity != 0) {
            register u8 *case14_inner_table asm("r6");

            var_r2_4 = 0;
            case14_value = case14_entity << 3;
            case14_value -= case14_entity;
            case14_value <<= 4;
            case14_value += (u32)case14_base;
            case14_entity = *(u8 *)(case14_value + 4);
            case14_inner_table = (u8 *)0x087A5810;
            asm volatile("" : "+r"(case14_inner_table));
            asm volatile("ldrb %0, [%1, #0]"
                         : "=r"(case14_value)
                         : "r"(case14_table)
                         : "memory");
            if (case14_entity != case14_value) {
                register u8 *case14_inner_base asm("r5");
                register s32 case14_inner_offset asm("r1");
                register u8 *case14_inner_slot asm("r4");

                case14_inner_base = (u8 *)0x020218E4;
                case14_inner_offset = 0x690C;
                asm volatile("" : "+r"(case14_inner_base), "+r"(case14_inner_offset));
                asm volatile(
                    "add r0, %1, %2\n\t"
                    "add %0, %3, r0"
                    : "=r"(case14_inner_slot)
                    : "r"(case14_inner_base), "r"(case14_inner_offset), "r"(var_r3_11)
                    : "r0", "cc");
                case14_inner_table += 0xB6;
loop_100:
                var_r2_4 += 1;
                if ((u32) var_r2_4 <= 0x19U) {
                    if (case14_inner_base[(*case14_inner_slot * 0x70) + 4] != *(u8 *)((u32)var_r2_4 + (u32)case14_inner_table)) {
                        goto loop_100;
                    }
                }
            }
            if (var_r2_4 == 0x1A) {
                goto block_13;
            }
            }
            var_r3_11 = (void *) (u8) (var_r3_11 + 1);
        } while ((u32) var_r3_11 <= 5U);
        goto block_117;
    }
    case 15: {                                      /* switch 1 */
        register u8 *case15_base asm("r8");
        register u8 *case15_base_seed asm("r0");
        register s32 case15_offset asm("r1");
        register u8 *case15_slots asm("ip");
        u8 *case15_record_base;

        var_r3_12 = NULL;
        case15_base_seed = (u8 *)0x020218E4;
        asm volatile("mov %0, %1"
                     : "=r"(case15_base)
                     : "r"(case15_base_seed));
        case15_offset = 0x690C;
        asm volatile("" : "+r"(case15_base), "+r"(case15_offset));
        case15_slots = (u8 *)((s32)case15_base + case15_offset);
        case15_record_base = case15_base;
loop_108:
        {
        register u8 *case15_slots_low asm("r1") = case15_slots;
        register u8 *case15_slot asm("r0");

        asm volatile("add %0, %1, %2"
                     : "=r"(case15_slot)
                     : "r"(var_r3_12), "r"(case15_slots_low)
                     : "cc");
        if (*case15_slot != 0) {
            register u8 *case15_table asm("r6");
            register u8 *case15_table_a asm("r5");
            register u8 *case15_table_c asm("r4");
            register u8 *case15_lookup asm("r0");
            register u8 *case15_map asm("r0");
            register u32 case15_map_entity asm("r1");

            var_r2_5 = NULL;
            case15_table = (u8 *)0x087A5810;
            asm volatile("" : "+r"(case15_table));
            case15_map = (u8 *)0x020281F0;
            asm volatile(
                "add %1, %2, %1\n\t"
                "ldrb %0, [%1]"
                : "=r"(case15_map_entity), "+r"(case15_map)
                : "r"(var_r3_12)
                : "cc", "memory");
            temp_r1_2 = case15_record_base[(case15_map_entity * 0x70) + 4];
            case15_table_a = case15_table;
            case15_table_c = case15_table;
            case15_table_c += 0xB6;
loop_110:
            case15_lookup = case15_table_a;
            case15_lookup += 0x1A;
            asm volatile("add %0, %1, %0"
                         : "+r"(case15_lookup)
                         : "r"(var_r2_5)
                         : "cc");
            if (temp_r1_2 != *case15_lookup) {
                case15_lookup = case15_table;
                case15_lookup += 0x9C;
                asm volatile("add %0, %1, %0"
                             : "+r"(case15_lookup)
                             : "r"(var_r2_5)
                             : "cc");
                if (temp_r1_2 != *case15_lookup) {
                    asm volatile("add %0, %1, %2"
                                 : "=r"(case15_lookup)
                                 : "r"(var_r2_5), "r"(case15_table_c)
                                 : "cc");
                    if (temp_r1_2 != *case15_lookup) {
                        var_r2_5 = (void *) (u8) (var_r2_5 + 1);
                        if ((u32) var_r2_5 <= 0x19U) {
                            goto loop_110;
                        }
                    }
                }
            }
            if (var_r2_5 == (void *)0x1A) {
                goto block_13;
            }
            goto block_116;
        }
        }
block_116:
        var_r3_12 = (void *) (u8) (var_r3_12 + 1);
        if ((u32) var_r3_12 > 5U) {
            goto block_117;
        }
        goto loop_108;
    }
    }
block_117:
    return 1;
}
