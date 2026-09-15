#include "m2c_prelude.h"

M2C_UNK jtbl_080C10C4();                            /* static */

s32 sub_080C1070(s32 arg0, s32 arg1) {
    register s32 default_result asm("r0") = arg0;
    u8 subroutine_arg0[6];
    volatile s32 sp8;
    u8 * volatile spC;
    volatile s32 sp10;
    register s32 temp_r0_3 asm("r10");
    s32 temp_r1_3;
    s32 temp_r1_5;
    s32 temp_r1_6;
    register s32 temp_r2_2 asm("r2");
    s32 case0_index;
    register u32 case0_pre_arg asm("r1");
    register u32 case0_pre_index asm("r0");
    register u32 stride asm("r9");
    register u32 initial_stride_seed asm("r5");
    register u32 initial_stride asm("r2");
    register u32 case0_table asm("r10");
    register u32 case0_units asm("r4");
    register u32 case0_loop_arg asm("r3");
    register u32 case0_unit_offset asm("r0");
    register u8 *case0_unit_address asm("r1");
    register u32 case0_stride asm("r4");
    register u32 case0_arg asm("r5");
    register u32 case0_records asm("r2");
    register u32 case0_scan_table asm("r5");
    register u32 case0_value asm("r2");
    register u32 case2_initial_table asm("r5");
    register u32 case2_outer3 asm("r9");
    register u32 case2_units asm("r2");
    register u32 case2_outer_address asm("r0");
    register u8 *case2_unit_address asm("r1");
    register u32 case2_stride asm("r4");
    register u32 case2_records asm("r2");
    register u32 case2_table asm("r5");
    register u32 case2_value asm("r2");
    register u8 *case2_tail_address asm("r0");
    register u8 *case2_spc_reload asm("r5");
    u8 *temp_r1_4;
    u8 *temp_r1_7;
    u8 *temp_r1_9;
    register u32 temp_r1 asm("r8");
    u8 temp_r1_2;
    u8 temp_r1_8;
    u8 case0_unit;
    u8 case2_unit;
    u32 counter_update;
    register u32 temp_r2 asm("r12");
    u8 var_r3_2;
    u8 var_r3_3;
    u8 var_r3_4;
    u8 var_r3_5;
    u8 var_r3;
    register u32 clear_zero asm("r2");
    register u32 var_r6 asm("r6");
    u32 var_r7;

    temp_r2 = (u8) arg0;
    temp_r1 = (u8) arg1;
    var_r3 = 0;
    var_r7 = 0x087A2854;
    clear_zero = 0;
    do {
        *(subroutine_arg0 + var_r3) = clear_zero;
        var_r3 += 1;
    } while ((u32) var_r3 <= 5U);
    initial_stride_seed = temp_r2;
    initial_stride = initial_stride_seed * 8;
    temp_r1_2 = M2C_FIELD((initial_stride - initial_stride_seed), u8 *, var_r7);
    asm volatile("" : "+r"(initial_stride_seed) : "r"(temp_r1_2));
    asm volatile("mov %0, %1"
        : "=r"(stride)
        : "r"(initial_stride));
    switch ((u32) temp_r1_2) {                      /* irregular */
    case 0:
        var_r6 = 0;
        asm volatile("mov %0, r9" : "=r"(initial_stride));
        case0_pre_arg = temp_r2;
        asm volatile(
            "sub %0, r2, r1\n"
            "add %0, #1"
            : "=r"(case0_pre_index)
            : "r"(initial_stride), "r"(case0_pre_arg));
        if (M2C_FIELD(case0_pre_index, u8 *, var_r7) != 0) {
            case0_table = var_r7;
loop_7:
            case0_loop_arg = temp_r1;
            asm volatile("" : "+r"(case0_loop_arg));
            case0_unit_offset = var_r6 + case0_loop_arg;
            case0_units = 0x020281F0;
            asm volatile("" : "+r"(case0_units));
            case0_unit_address = (u8 *)(case0_unit_offset + case0_units);
            if (*case0_unit_address != 0) {
                var_r3_2 = 0;
                case0_stride = initial_stride;
                case0_arg = temp_r2;
                case0_index = (case0_stride - case0_arg) + 1;
                if (M2C_FIELD(case0_index, u8 *, case0_table) != 0) {
                    case0_records = 0x020218E4;
                    asm volatile("" :: "r"(case0_records));
                    case0_unit = *case0_unit_address;
                    case0_scan_table = 0x087A2854;
                    case0_value = M2C_FIELD((case0_unit * 0x70), u8 *, case0_records + 4);
loop_10:
                    temp_r1_3 = (case0_stride - temp_r2) + 1;
                    asm volatile("" : "+r"(case0_stride) : "r"(temp_r1_3));
                    if (case0_value == M2C_FIELD((var_r3_2 + temp_r1_3), u8 *, case0_scan_table)) {
                        temp_r1_4 = subroutine_arg0 + var_r3_2;
                        if (*temp_r1_4 == 0) {
                            goto case0_store;
                        }
block_12:
                        return 0U;
                    }
                    var_r3_2 += 1;
                    if (((u32) var_r3_2 > 5U) || (M2C_FIELD((var_r3_2 + temp_r1_3), u8 *, case0_scan_table) == 0)) {
                        goto block_16;
                    }
                    goto loop_10;
                }
block_16:
                if (var_r3_2 != 6) {
                    register u32 case0_post_stride asm("r4");
                    register u32 case0_post_arg asm("r5");
                    register u32 case0_post_index asm("r1");
                    asm volatile(
                        "mov %0, r9\n"
                        "mov %1, ip\n"
                        "sub r0, %0, %1\n"
                        "add %2, r0, #1"
                        : "=r"(case0_post_stride), "=r"(case0_post_arg),
                          "=r"(case0_post_index));
                    temp_r1_5 = case0_post_index;
                    if (M2C_FIELD((var_r3_2 + temp_r1_5), u8 *, var_r7) != 0) {
                        goto case0_increment;
                    }
                    goto block_12;
case0_store:
                    *temp_r1_4 = 1;
                    goto block_16;
case0_increment:
                    asm volatile(
                        "add %0, %1, #1\n"
                        "lsl %0, %0, #24\n"
                        "lsr %1, %0, #24"
                        : "=&r"(counter_update), "+r"(var_r6));
                    if ((u32) var_r6 <= 2U) {
                        asm volatile("mov %0, r9" : "=r"(initial_stride));
                        if (M2C_FIELD((var_r6 + temp_r1_5), u8 *, var_r7) != 0) {
                            goto loop_7;
                        }
                        goto block_27;
                    }
                    goto block_27;
                }
                goto block_12;
            }
            goto block_12;
        }
        goto block_27;
    case 1: {
        register u8 *case1_records asm("r5");
        register u8 *case1_units asm("r4");
        register u32 case1_units_offset asm("r0");
        register u8 *case1_table asm("r3");
        register s32 case1_row asm("r2");
        register u32 case1_counter3 asm("r0");
        register u32 case1_unit asm("r0");
        register u32 case1_record_unit asm("r1");
        var_r7 = 0;
        case1_records = (u8 *)0x020218E4;
        case1_units_offset = 0x690C;
        asm volatile("" : "+r"(case1_units_offset));
        case1_units = case1_records + case1_units_offset;
        case1_table = (u8 *)0x087A2854;
        asm volatile(
            "mov r1, r9\n"
            "mov %0, ip\n"
            "sub r0, r1, %0\n"
            "add %0, r0, #1"
            : "=r"(case1_row)
            :
            : "r0", "r1");
loop_24:
        asm volatile(
            "lsl %0, r7, #1\n"
            "add %0, %0, r7"
            : "=r"(case1_counter3));
        asm volatile(
            "add %0, r8\n"
            "add r1, %0, r4\n"
            "ldrb %0, [r1]"
            : "=r"(case1_unit)
            : "0"(case1_counter3), "r"(case1_units)
            : "r1");
        if (case1_unit == 0) {
            goto case1_next;
        }
        asm volatile("add %0, %1, #0"
            : "=r"(case1_record_unit)
            : "r"(case1_unit));
        if (case1_records[(case1_record_unit * 0x70) + 4] ==
                *(u8 *)((var_r7 + case1_row) + (u32)case1_table)) {
case1_next:
            var_r7 = (u8) (var_r7 + 1);
            if ((u32) var_r7 > 1U) {
                goto block_27;
            }
            goto loop_24;
        }
        goto block_12;
    }
block_27:
        {
            register s32 success_result asm("r0");
            asm volatile("mov %0, #1" : "=r"(success_result));
            return success_result;
        }
    case 2:
        var_r7 = 0;
        sp8 = stride;
        temp_r0_3 = (stride - temp_r2) + 1;
        case2_initial_table = 0x087A2854;
        case2_initial_table += temp_r0_3;
        spC = (u8 *) case2_initial_table;
loop_30:
        var_r6 = 0;
        asm volatile(
            "lsl r0, r7, #1\n"
            "add r0, r0, r7\n"
            "mov %0, r0"
            : "=r"(case2_outer3));
loop_31:
        asm volatile(
            "mov r1, r9\n"
            "add %0, r6, r1\n"
            "add %0, r8"
            : "=r"(case2_outer_address)
            : "r"(case2_outer3), "r"(temp_r1), "r"(var_r6)
            : "r1");
        case2_units = 0x020281F0;
        asm volatile("add %0, %1, r2"
            : "=r"(case2_unit_address)
            : "r"(case2_outer_address), "r"(case2_units));
        if (*case2_unit_address != 0) {
            var_r3_3 = 0;
            case2_stride = sp8;
            case2_spc_reload = spC;
            if (*case2_spc_reload != 0) {
                case2_records = 0x020218E4;
                case2_table = 0x087A2854;
                asm volatile("" :: "r"(case2_table));
                case2_unit = *case2_unit_address;
                case2_value = M2C_FIELD((case2_unit * 0x70), u8 *, case2_records + 4);
loop_34:
                temp_r1_6 = (case2_stride - temp_r2) + 1;
                asm volatile("" : "+r"(case2_stride) : "r"(temp_r1_6));
                if (case2_value == M2C_FIELD((var_r3_3 + temp_r1_6), u8 *, case2_table)) {
                    temp_r1_7 = subroutine_arg0 + var_r3_3;
                    if (*temp_r1_7 == 0) {
                        goto case2_store;
                    }
                    goto block_12;
                }
                var_r3_3 += 1;
                if ((u32) var_r3_3 > 5U) {
                    goto block_39;
                }
                case2_tail_address = (u8 *)(var_r3_3 + temp_r1_6);
                asm volatile("add %0, %0, r5"
                    : "+r"(case2_tail_address));
                if (*case2_tail_address == 0) {
                    goto block_39;
                }
                goto loop_34;
            }
block_39:
            if (var_r3_3 == 6) {
                goto block_12;
            }
            if (M2C_FIELD((var_r3_3 + temp_r0_3), u8 *, 0x087A2854) != 0) {
                goto case2_increment;
            }
            goto block_12;
case2_store:
            *temp_r1_7 = 1;
            goto block_39;
case2_increment:
            asm volatile(
                "add %0, %1, #1\n"
                "lsl %0, %0, #24\n"
                "lsr %1, %0, #24"
                : "=&r"(counter_update), "+r"(var_r6));
            if ((u32) var_r6 > 1U) {
                var_r7 = (u8) (var_r7 + 1);
                if ((u32) var_r7 <= 1U) {
                    goto loop_30;
                }
                goto block_27;
            }
            goto loop_31;
        }
        goto block_12;
    case 3: {
        register u32 case3_initial_record_address asm("r0");
        register u32 case3_initial_table_address asm("r1");
        register u8 *case3_initial_records asm("r0");
        register u32 case3_initial_units_offset asm("r1");
        register u8 *case3_initial_unit_address asm("r2");
        register u8 *case3_records asm("r5");
        register u8 *case3_units asm("r9");
        register u8 *case3_table asm("r4");
        register u32 case3_record_value asm("r1");
        register u32 case3_table_value asm("r0");
        register u32 case3_unit_table asm("r0");
        if ((u32) temp_r1 <= 2U) {
            goto block_12;
        }
        case3_initial_records = (u8 *)0x020218E4;
        case3_initial_units_offset = 0x690D;
        case3_initial_unit_address = case3_initial_records + case3_initial_units_offset;
        temp_r1_8 = *case3_initial_unit_address;
        asm volatile("add %0, %1, #0"
            : "=r"(case3_records)
            : "r"(case3_initial_records));
        if (temp_r1_8 == 0) {
            goto block_12;
        }
        case3_initial_record_address = temp_r1_8 * 0x70;
        asm volatile("add %0, %0, %1"
            : "+r"(case3_initial_record_address)
            : "r"(case3_records));
        temp_r2_2 = stride - temp_r2;
        asm volatile(
            "add %0, r7, #1\n"
            "add %0, r2, %0"
            : "=r"(case3_initial_table_address));
        if (M2C_FIELD(case3_initial_record_address, u8 *, 4) != M2C_FIELD(case3_initial_table_address, u8 *, 0)) {
            goto block_12;
        }
        var_r6 = temp_r1;
        case3_units = case3_records + 0x690C;
        case3_table = (u8 *) var_r7;
        temp_r2_2 += 1;
loop_55:
        if (*(u8 *)((u32)var_r6 + (u32)case3_units) != 0) {
            var_r3_4 = 1;
            case3_unit_table = 0x020281F0;
            asm volatile("" : "+r"(case3_unit_table));
            case3_record_value = case3_records[(M2C_FIELD(var_r6, u8 *, case3_unit_table) * 0x70) + 4];
loop_57:
            case3_table_value = *(u8 *)((var_r3_4 + temp_r2_2) + (u32)case3_table);
            if (case3_record_value != case3_table_value) {
                var_r3_4 += 1;
                if ((u32) var_r3_4 <= 4U) {
                    goto loop_57;
                }
            } else {
                goto case3_store;
            }
case3_postscan:
            if (var_r3_4 != 5) {
                goto block_66;
            }
            if (var_r6 != temp_r1) {
                goto block_66;
            }
            goto block_12;
case3_store:
            *(subroutine_arg0 + var_r3_4) = 1;
            goto case3_postscan;
        }
        if (var_r6 == temp_r1) {
            goto block_12;
        }
block_66:
        asm volatile(
            "sub %0, %1, #1\n"
            "lsl %0, %0, #24\n"
            "lsr %1, %0, #24"
            : "=&r"(counter_update), "+r"(var_r6));
        if ((u32) var_r6 <= 2U) {
            if ((M2C_FIELD(subroutine_arg0, u8 *, 1) != 0) && (M2C_FIELD(subroutine_arg0, u8 *, 2) != 0)) {
                goto block_27;
            }
            if (M2C_FIELD(subroutine_arg0, u8 *, 3) != 0) {
                goto block_27;
            }
            if (M2C_FIELD(subroutine_arg0, u8 *, 4) == 0) {
                goto block_12;
            }
            goto block_27;
        }
        goto loop_55;
    }
    case 4: {
        register u32 case4_records asm("r2");
        register u32 case4_units_offset asm("r5");
        register u32 case4_sp_outer asm("r5");
        register u32 case4_units_base asm("r1");
        register u32 case4_unit_address asm("r0");
        register u32 case4_record_address asm("r0");
        register u32 case4_value asm("r2");
        register s32 case4_index asm("r1");
        register u32 case4_outer3 asm("r4");
        u8 case4_unit;
        var_r7 = 0;
        case0_table = 0x087A2854;
loop_76:
        var_r6 = 0;
        asm volatile(
            "lsl r0, r7, #1\n"
            "add %0, r0, r7"
            : "=r"(case4_outer3)
            :
            : "r0");
        sp10 = case4_outer3;
loop_77:
        if (M2C_FIELD((var_r6 + case4_outer3 + temp_r1), u8 *, 0x020281F0) == 0) {
            goto block_12;
        }
        var_r3_5 = 0;
        case4_records = 0x020218E4;
        asm volatile("" :: "r"(case4_records));
        case4_sp_outer = sp10;
        case4_unit_address = var_r6 + case4_sp_outer;
        case4_unit_address += temp_r1;
        case4_units_offset = 0x690C;
        case4_units_base = case4_records + case4_units_offset;
        case4_unit_address += case4_units_base;
        case4_unit = M2C_FIELD(case4_unit_address, u8 *, 0);
        case4_record_address = case4_unit * 0x70;
        asm volatile("add %0, %0, %1"
            : "+r"(case4_record_address)
            : "r"(case4_records));
        asm volatile(
            "mov r2, r9\n"
            "mov r5, ip\n"
            "sub %0, r2, r5\n"
            "add %0, #1"
            : "=r"(case4_index));
        case4_value = M2C_FIELD(case4_record_address, u8 *, 4);
loop_80:
        if (case4_value == M2C_FIELD((var_r3_5 + case4_index), u8 *, case0_table)) {
            temp_r1_9 = subroutine_arg0 + var_r3_5;
            if (*temp_r1_9 == 0) {
                goto case4_store;
            }
            goto block_12;
        }
        var_r3_5 += 1;
        if ((u32) var_r3_5 > 5U) {
block_85:
            if (var_r3_5 != 6) {
                goto case4_increment;
            }
            goto block_12;
case4_store:
            *temp_r1_9 = 1;
            goto block_85;
case4_increment:
            asm volatile(
                "add %0, %1, #1\n"
                "lsl %0, %0, #24\n"
                "lsr %1, %0, #24"
                : "=&r"(counter_update), "+r"(var_r6));
            if ((u32) var_r6 > 2U) {
                var_r7 = (u8) (var_r7 + 1);
                if ((u32) var_r7 > 1U) {
                    return 1U;
                }
                goto loop_76;
            }
            goto loop_77;
        }
        goto loop_80;
    }
    default:
        return default_result;
    }
}
