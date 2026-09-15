#include "m2c_prelude.h"

s32 func_080E9D88(s32, s32);                        /* extern */
M2C_UNK jtbl_080C0CAC();                            /* static */

s32 sub_080C0C54(s32 arg0, s32 arg1, s32 arg2) {
    register s32 default_result asm("r0") = arg0;
    register u8 initial_zero asm("r2");
    u8 subroutine_arg0[6];
    volatile u32 sp8;
    volatile s32 spC;
    s32 case0_index;
    s32 case1_index;
    s32 case2_index;
    register s32 case3_unbiased_index asm("r0");
    register s32 case3_index asm("r1");
    s32 case4_index;
    s32 temp_r1_3;
    s32 temp_r2;
    s32 temp_r2_2;
    register u32 case1_stride asm("r5");
    register u32 case1_stride_seed asm("r0");
    register u32 case1_zero asm("r4");
    register u32 case2_zero asm("r3");
    register u32 case2_unit_seed asm("r0");
    register u32 case4_seed asm("r5");
    register u32 case0_base asm("r3");
    register u32 case0_table asm("r8");
    register u32 case0_data_base asm("r2");
    register u32 case0_scan_base asm("r4");
    register u32 case0_unit_offset asm("r1");
    register u32 case0_saved asm("r5");
    register u32 case0_arg8 asm("r5");
    register u32 case2_base asm("r2");
    register u32 case2_base_copy asm("r0");
    register u32 case2_scan_arg8 asm("r5");
    register u32 case2_table_address asm("r1");
    register u32 case2_value_address asm("r0");
    register u32 case2_table asm("r12");
    register u32 case3_base asm("r4");
    register u32 case3_work asm("r3");
    register u32 case3_initial_table asm("r1");
    register u32 case3_initial_offset asm("r2");
    register u32 case3_unit_offset asm("r0");
    register u32 case4_data_base asm("r2");
    register u32 case4_unit_offset asm("r1");
    register u32 case4_stride asm("r0");
    u8 *temp_r1_2;
    u8 *temp_r1_4;
    u8 *temp_r1_5;
    u8 temp_r0;
    u8 temp_r0_2;
    u8 temp_r0_3;
    register u32 case0_value asm("r1");
    register u32 case2_value asm("r0");
    register u32 case3_value asm("r2");
    u8 case4_value;
    register u8 temp_r1 asm("r1");
    u8 temp_r3;
    register u32 temp_r4 asm("r4");
    register u32 temp_r4_2 asm("r4");
    register u32 temp_r4_3 asm("r4");
    register u32 temp_r4_4 asm("r4");
    u8 temp_r6;
    u8 var_r3;
    u8 var_r3_2;
    u8 var_r3_3;
    u8 var_r3_4;
    u8 var_r3_5;
    u32 var_r7;
    register u32 var_r8 asm("r8");

    temp_r3 = arg0;
    temp_r6 = arg1;
    sp8 = (u8) arg2;
    var_r3 = 0;
    initial_zero = 0;
    do {
        *(subroutine_arg0 + var_r3) = initial_zero;
        var_r3 += 1;
    } while ((u32) var_r3 <= 5U);
    temp_r1 = M2C_FIELD((temp_r3 * 7), u8 *, 0x087A2854);
    switch ((u32) temp_r1) {                        /* irregular */
    case 0:
        var_r7 = 0;
        case0_index = (temp_r3 * 7) + 1;
        asm volatile("" : "+r"(case0_index));
        case0_base = 0x087A2854;
        asm volatile("" : "+r"(case0_base));
        if (M2C_FIELD(case0_index, volatile u8 *, case0_base) == 0) {
            goto block_30;
        }
        case0_table = case0_base;
loop_8:
        case0_saved = sp8;
        asm volatile("" :: "r"(case0_saved));
        temp_r4 = var_r7 + case0_saved;
        if ((func_080E9D88(temp_r6, (u8) temp_r4) << 0x18) != 0) {
            var_r3_2 = 0;
            case0_arg8 = temp_r3 * 8;
            asm volatile("" : "+r"(case0_arg8));
            case0_index = (case0_arg8 - temp_r3) + 1;
            asm volatile("" : "+r"(case0_index));
            if (M2C_FIELD(case0_index, u8 *, case0_table) != 0) {
                case0_data_base = 0x02034B4C;
                asm volatile("" :: "r"(case0_data_base));
                case0_unit_offset = temp_r4 * 0x270;
                asm volatile("" :: "r"(case0_unit_offset));
                case0_scan_base = 0x087A2854;
                asm volatile("" :: "r"(case0_scan_base));
                case0_unit_offset += temp_r6 * 0x1380;
                case0_value = M2C_FIELD(case0_unit_offset, u8 *, case0_data_base);
loop_11:
                {
                    register s32 case0_unbiased_index asm("r0");
                    register s32 case0_index_rhs asm("r2") = temp_r3;
                    case0_unbiased_index = case0_arg8 - case0_index_rhs;
                    temp_r2 = case0_unbiased_index + 1;
                }
                asm volatile("" :: "r"(temp_r2));
                if (case0_value == M2C_FIELD((var_r3_2 + temp_r2), u8 *, case0_scan_base)) {
                    temp_r1_2 = subroutine_arg0 + var_r3_2;
                    if (*temp_r1_2 == 0) {
                        goto case0_store;
                    }
block_13:
                    return 0U;
                }
                var_r3_2 += 1;
                if (((u32) var_r3_2 > 5U) || (M2C_FIELD((var_r3_2 + temp_r2), u8 *, case0_scan_base) == 0)) {
                    goto block_17;
                }
                goto loop_11;
            }
block_17:
            if (var_r3_2 != 6) {
                temp_r1_3 = (temp_r3 * 7) + 1;
                if (({
                        register u32 case0_postscan_address asm("r0");
                        register u32 case0_postscan_table asm("r2");
                        u32 case0_postscan_value;
                        case0_postscan_address = var_r3_2 + temp_r1_3;
                        case0_postscan_table = 0x087A2854;
                        case0_postscan_address += case0_postscan_table;
                        case0_postscan_value = M2C_FIELD(case0_postscan_address, u8 *, 0);
                        case0_postscan_value;
                    }) != 0) {
                    goto case0_increment;
                }
                goto block_13;
case0_store:
                *temp_r1_2 = 1;
                goto block_17;
case0_increment:
                var_r7 = (u8) (var_r7 + 1);
                if ((u32) var_r7 <= 2U) {
                    if (({
                            register u32 case0_increment_address asm("r0");
                            register u32 case0_increment_table asm("r3");
                            case0_increment_address = var_r7 + temp_r1_3;
                            case0_increment_table = 0x087A2854;
                            case0_increment_address += case0_increment_table;
                            M2C_FIELD(case0_increment_address, u8 *, 0);
                        }) != 0) {
                        goto loop_8;
                    }
                    goto block_30;
                }
                goto block_30;
            }
            goto block_13;
        } else {
            goto block_13;
        }
    case 1:
        case1_zero = 0;
        var_r8 = case1_zero;
        var_r7 = 0x087A2854;
        case1_stride_seed = temp_r6 * 4;
        case1_stride_seed = ((case1_stride_seed + temp_r6) * 8) - temp_r6;
        case1_stride = case1_stride_seed * 0x80;
loop_27:
        temp_r4_2 = ({
            register u32 case1_lane_seed asm("r1");
            register u32 case1_lane_sum asm("r0");
            register u32 case1_saved_arg asm("r2");
            register u32 case1_lane_result asm("r4");
            case1_lane_seed = var_r8;
            case1_lane_sum = case1_lane_seed * 2;
            case1_lane_sum += var_r8;
            case1_saved_arg = sp8;
            case1_lane_result = case1_saved_arg + case1_lane_sum;
            case1_lane_result;
        });
        if (((func_080E9D88(temp_r6, (u8) temp_r4_2) << 0x18) != 0) && (M2C_FIELD(({
                register u32 case1_data_address asm("r0");
                register u32 case1_data_base asm("r3");
                case1_data_address = temp_r4_2 * 0x270;
                asm volatile("add %0, %0, %1"
                    : "+r"(case1_data_address)
                    : "r"(case1_stride));
                case1_data_base = 0x02034B4C;
                asm volatile("add %0, %0, %1"
                    : "+r"(case1_data_address)
                    : "r"(case1_data_base));
                case1_data_address;
            }), u8 *, 0) == M2C_FIELD(((case1_index = ({
                register s32 case1_index_lhs asm("r4");
                register s32 case1_index_rhs asm("r2");
                register s32 case1_index_result asm("r1");
                asm volatile(
                    "mov %0, sl\n"
                    "mov %1, r9\n"
                    "sub %2, %0, %1"
                    : "=r"(case1_index_lhs), "=r"(case1_index_rhs),
                      "=r"(case1_index_result));
                case1_index_result + 1;
            })) + var_r8), u8 *, var_r7))) {
            temp_r0 = var_r8 + 1;
            var_r8 = temp_r0;
            if ((u32) temp_r0 > 1U) {
                goto block_30;
            }
            goto loop_27;
        }
        goto block_13;
block_30:
        {
            register s32 success_result asm("r0");
            asm volatile("mov %0, #1" : "=r"(success_result));
            return success_result;
    }
    case 2:
        asm volatile(
            "mov %0, #0\n"
            "mov %1, %0"
            : "=r"(case2_zero), "=r"(var_r8));
loop_32:
        var_r7 = 0;
        {
            register u32 case2_outer_copy asm("r4");
            asm volatile(
                "mov %0, r8\n"
                "lsl %0, %0, #1"
                : "=r"(case2_outer_copy));
            temp_r4_3 = case2_outer_copy;
            spC = case2_outer_copy;
        }
loop_33:
        temp_r4_3 = ({
            register u32 case2_lane_sum asm("r0") = spC;
            register u32 case2_saved_arg asm("r5");
            register u32 case2_lane_result asm("r4");
            case2_lane_sum += var_r8;
            case2_lane_sum = var_r7 + case2_lane_sum;
            case2_saved_arg = sp8;
            case2_lane_result = case2_saved_arg + case2_lane_sum;
            case2_lane_result;
        });
        if ((func_080E9D88(temp_r6, (u8) temp_r4_3) << 0x18) != 0) {
            var_r3_3 = 0;
            {
                register u32 case2_initial_seed asm("r5");
                register s32 case2_index_rhs asm("r1");
                register s32 case2_index_result asm("r0");
                case2_initial_seed = temp_r3 * 8;
                asm volatile("" : "+r"(case2_initial_seed));
                asm volatile(
                    "mov %0, r9\n"
                    "sub %1, r5, %0"
                    : "=r"(case2_index_rhs), "=r"(case2_index_result));
                case2_index = case2_index_result + 1;
                asm volatile("" :: "r"(case2_initial_seed), "r"(case2_index));
            }
            case2_base = 0x087A2854;
            asm volatile("" : "+r"(case2_base));
            if (M2C_FIELD(case2_index, u8 *, case2_base) != 0) {
                case2_base_copy = case2_base;
                asm volatile("" : "+r"(case2_base_copy));
                case2_table = case2_base_copy;
                case2_unit_seed = temp_r4_3 * 4;
                asm volatile("" : "+r"(case2_unit_seed));
                case2_unit_seed = ((case2_unit_seed + temp_r4_3) * 8) - temp_r4_3;
                temp_r4_3 = case2_unit_seed * 0x10;
                asm volatile("" : "=r"(case2_scan_arg8));
loop_36:
                asm volatile("" : "+r"(temp_r6));
                {
                    register u32 case2_reserve2 asm("r2");
                    asm volatile("" : "=&r"(case2_reserve2));
                    case2_value_address = (temp_r4_3 + (temp_r6 * 0x1380)) + 0x02034B4C;
                    asm volatile("" :: "r"(case2_reserve2));
                }
                temp_r2_2 = (case2_scan_arg8 - temp_r3) + 1;
                asm volatile("" :: "r"(case2_scan_arg8), "r"(temp_r2_2));
                case2_table_address = (var_r3_3 + temp_r2_2) + case2_table;
                asm volatile("" :: "r"(case2_value_address), "r"(case2_table_address));
                case2_value = M2C_FIELD(case2_value_address, volatile u8 *, 0);
                if (case2_value == M2C_FIELD(case2_table_address, u8 *, 0)) {
                    temp_r1_4 = subroutine_arg0 + var_r3_3;
                    if (*temp_r1_4 == 0) {
                        goto case2_store;
                    }
                    goto block_13;
                }
                var_r3_3 += 1;
                if (((u32) var_r3_3 > 5U) || (M2C_FIELD((var_r3_3 + temp_r2_2), u8 *, case2_table) == 0)) {
                    goto block_42;
                }
                goto loop_36;
            }
block_42:
            if (var_r3_3 == 6) {
                goto block_13;
            }
            case2_index = (temp_r3 * 7) + 1;
            asm volatile("" : "+r"(case2_index));
            if (M2C_FIELD((var_r3_3 + case2_index), u8 *, 0x087A2854) != 0) {
                goto case2_increment;
            }
            goto block_13;
case2_store:
            *temp_r1_4 = 1;
            goto block_42;
case2_increment:
            var_r7 = (u8) (var_r7 + 1);
            if ((u32) var_r7 > 1U) {
                temp_r0_2 = var_r8 + 1;
                var_r8 = temp_r0_2;
                if ((u32) temp_r0_2 <= 1U) {
                    goto loop_32;
                }
                goto block_30;
            }
            goto loop_33;
        }
        goto block_13;
    case 3:
        case3_work = sp8;
        asm volatile("" :: "r"(case3_work));
        if (case3_work <= 2U) {
            goto block_13;
        }
        if ((func_080E9D88(temp_r6, 1U) << 0x18) == 0) {
            goto block_13;
        }
        case3_base = 0x02034B4C;
        asm volatile("" : "+r"(case3_base));
        if (M2C_FIELD((({
                register u32 case3_group_seed asm("r3");
                register u32 case3_group_stride asm("r0");
                case3_group_seed = temp_r6 * 4;
                case3_group_stride = case3_group_seed + temp_r6;
                case3_group_stride *= 8;
                case3_group_stride -= temp_r6;
                case3_group_stride *= 128;
                case3_group_stride += case3_base;
                case3_group_stride;
            }) + 0x270), u8 *, 0) != ({
                case3_initial_table = 0x087A2854;
                asm volatile("" : "+r"(case3_initial_table));
                case3_initial_offset = temp_r3 * 7;
                asm volatile("" : "+r"(case3_initial_offset));
                case3_initial_table += 1;
                case3_initial_offset += case3_initial_table;
                M2C_FIELD(case3_initial_offset, u8 *, 0);
            })) {
            goto block_13;
        }
        var_r7 = sp8;
        var_r8 = case3_base;
loop_57:
        if ((func_080E9D88(temp_r6, var_r7) << 0x18) != 0) {
            var_r3_4 = 1;
            case3_unit_offset = var_r7 * 0x270;
            asm volatile("" : "+r"(case3_unit_offset));
            case3_unit_offset += temp_r6 * 0x1380;
            case3_value = M2C_FIELD(case3_unit_offset, u8 *, var_r8);
            case3_unbiased_index = temp_r3 * 7;
            case3_index = case3_unbiased_index + 1;
            asm volatile("" :: "r"(case3_unbiased_index), "r"(case3_index));
loop_59:
            if (case3_value != ({
                register u32 case3_scan_table asm("r4");
                    case3_unbiased_index = var_r3_4 + case3_index;
                    case3_scan_table = 0x087A2854;
                    asm volatile("" : "+r"(case3_scan_table));
                    case3_unbiased_index += case3_scan_table;
                    M2C_FIELD(case3_unbiased_index, u8 *, 0);
                })) {
                var_r3_4 += 1;
                if ((u32) var_r3_4 <= 4U) {
                    goto loop_59;
                }
            } else {
                goto case3_store;
            }
case3_postscan:
            if (var_r3_4 != 5) {
                goto block_68;
            }
            if (var_r7 != sp8) {
                goto block_68;
            }
            goto block_13;
case3_store:
            asm volatile(
                "mov r2, sp\n"
                "add r1, r2, %0\n"
                "mov r0, #1\n"
                "strb r0, [r1]"
                :: "r"(var_r3_4)
                : "memory");
            goto case3_postscan;
        }
        case3_work = sp8;
        asm volatile("" :: "r"(case3_work));
        if (var_r7 == case3_work) {
            goto block_13;
        }
block_68:
        var_r7 = (u32) (u8) (var_r7 - 1);
        if (var_r7 <= 2U) {
            if ((M2C_FIELD(subroutine_arg0, u8 *, 1) != 0) && (M2C_FIELD(subroutine_arg0, u8 *, 2) != 0)) {
                goto block_30;
            }
            if (M2C_FIELD(subroutine_arg0, u8 *, 3) != 0) {
                goto block_30;
            }
            if (M2C_FIELD(subroutine_arg0, u8 *, 4) == 0) {
                goto block_13;
            }
            goto block_30;
        }
        goto loop_57;
    case 4:
        temp_r4_4 = 0;
        asm volatile("" :: "r"(temp_r4_4));
        var_r8 = temp_r4_4;
loop_78:
        var_r7 = 0;
        case4_seed = var_r8;
        asm volatile("" : "+r"(case4_seed));
        case4_seed *= 2;
        spC = case4_seed;
loop_79:
        case4_stride = spC;
        asm volatile("" : "+r"(case4_stride));
        case4_stride += var_r8;
        case4_stride = var_r7 + case4_stride;
        case4_unit_offset = sp8;
        asm volatile("" : "+r"(case4_unit_offset));
        temp_r4_4 = case4_unit_offset + case4_stride;
        if ((func_080E9D88(temp_r6, (u8) temp_r4_4) << 0x18) == 0) {
            goto block_13;
        }
        var_r3_5 = 0;
        case4_seed = temp_r6 * 4;
        asm volatile("" :: "r"(case4_seed));
        case4_data_base = 0x02034B4C;
        asm volatile("" :: "r"(case4_data_base));
        case4_unit_offset = temp_r4_4 * 0x270;
        asm volatile("" :: "r"(case4_unit_offset));
        case4_stride = case4_seed + temp_r6;
        asm volatile("" : "+r"(case4_stride));
        case4_unit_offset += ((case4_stride * 8) - temp_r6) * 0x80;
        case4_value = M2C_FIELD(case4_unit_offset, u8 *, case4_data_base);
loop_82:
        if (case4_value == ({
                register s32 case4_index_lhs asm("r2");
                register s32 case4_index_rhs asm("r4");
                register u32 case4_table_address asm("r0");
                register u32 case4_table_base asm("r5");
                asm volatile(
                    "mov %0, sl\n"
                    "mov %1, r9\n"
                    "sub %2, %0, %1"
                    : "=r"(case4_index_lhs), "=r"(case4_index_rhs),
                      "=r"(case4_table_address));
                case4_table_address += 1;
                case4_table_address = var_r3_5 + case4_table_address;
                case4_table_base = 0x087A2854;
                asm volatile("add %0, %0, %1"
                    : "+r"(case4_table_address)
                    : "r"(case4_table_base));
                M2C_FIELD(case4_table_address, u8 *, 0);
            })) {
            {
                register u8 *case4_slot_address asm("r1");
                asm volatile(
                    "mov r0, sp\n"
                    "add %0, r0, %1"
                    : "=r"(case4_slot_address)
                    : "r"(var_r3_5));
                temp_r1_5 = case4_slot_address;
            }
            if (*temp_r1_5 == 0) {
                goto case4_store;
            }
            goto block_13;
        }
        var_r3_5 += 1;
        if ((u32) var_r3_5 > 5U) {
block_87:
            if (var_r3_5 != 6) {
                goto case4_increment;
            }
            goto block_13;
case4_store:
            *temp_r1_5 = 1;
            goto block_87;
case4_increment:
            var_r7 = (u8) (var_r7 + 1);
            if ((u32) var_r7 > 2U) {
                temp_r0_3 = var_r8 + 1;
                var_r8 = temp_r0_3;
                if ((u32) temp_r0_3 > 1U) {
                    return 1U;
                }
                goto loop_78;
            }
            goto loop_79;
        }
        goto loop_82;
    default:
        return default_result;
    }
}
