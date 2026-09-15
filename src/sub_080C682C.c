#include "m2c_prelude.h"

s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
s32 func_08094484_4(M2C_UNK, M2C_UNK, s32, s32);       /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A9C8(s32, s32, s32, s32, s32, s32); /* extern */
s32 func_080E9D88(u8, u32);                         /* extern */
M2C_UNK jtbl_080C6858();                            /* static */
asm(".set sub_080C682C_state, 0x0203055C");
extern u8 sub_080C682C_state[];

u8 sub_080C682C(void) {
    s16 temp_r0_3;
    s32 case3_half;
    s32 case3_health;
    s16 temp_r0_5;
    s32 case4_half;
    s32 case4_health;
    s16 temp_r0_7;
    s32 case5_half;
    s32 case5_health;
    register s32 temp_r8 asm("r8");
    s32 temp_r8_2;
    s32 temp_r8_3;
    s32 temp_r8_4;
    register u8 *case5_state_tail asm("r1");
    register u8 *case5_record_base asm("r2");
    register u8 *case5_record asm("r1");
    register u8 *case5_health_address asm("r2");
    register u8 *case5_max_address asm("r0");
    register s32 case5_scene_x asm("r6");
    register s32 case5_scene_y asm("r4");
    register void *case5_scene_buffer asm("r7");
    register s32 *case5_out_args asm("sp");
    register u8 *case0_record_base asm("r3");
    register u8 *case3_record asm("r1");
    register u32 case3_record_offset asm("r0");
    register u8 *case3_health_address asm("r2");
    register u8 *case3_max_address asm("r0");
    register u8 *case4_health_address asm("r2");
    register u8 *case4_max_address asm("r0");
    register u8 *case4_record_base asm("r3");
    register u8 *case9_record_base asm("r2");
    register u8 *case7_tail_base asm("r1");
    register u32 case7_score_offset asm("r3");
    register u8 *case6_score_base2 asm("r0");
    register u32 case6_score_offset2 asm("r2");
    register u8 *case6_score_base4 asm("r0");
    register u32 case6_score_offset4 asm("r1");
    register u8 *case6_score_base8 asm("r0");
    register u32 case6_score_offset8 asm("r4");
    register u8 *case6_outer_base asm("r4");
    register u8 *case6_inner_base asm("r6");
    register u8 *case7_outer_base asm("r4");
    register u8 *case7_inner_base asm("r6");
    u32 temp_r0;
    u32 var_r4;
    u32 var_r4_2;
    u32 var_r4_3;
    u32 var_r5_6;
    u32 var_r5_7;
    u8 temp_r0_10;
    u8 temp_r0_2;
    u8 temp_r0_4;
    u8 temp_r0_6;
    u8 temp_r0_8;
    u8 temp_r0_9;
    u8 temp_r3;
    u8 temp_r3_2;
    u8 temp_r3_3;
    u8 var_r5;
    register u8 *state asm("r2");
    register u8 *state_load asm("r1");
    u8 var_r6;
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r1_3;
    void *temp_r1_4;
    void *temp_r1_5;
    void *temp_r1_6;

    state_load = (u8 *) 0x0203055C;
    temp_r0 = M2C_FIELD(state_load, u8 *, 5) - 1;
    state = state_load;
    switch (temp_r0) {
    case 0:
        var_r5 = 0;
        case0_record_base = (u8 *)0x02034B4C;
        do {
            temp_r1 = (void *)((var_r5 * 0x270) - (0U - (u32)case0_record_base));
            if (((u32) (u8) (M2C_FIELD(temp_r1, u8 *, 0x13F0) - 0x36) <= 1U) && ((s32) M2C_FIELD(temp_r1, s16 *, 0x1386) < (s32) M2C_FIELD(temp_r1, s16 *, 0x13BA))) {
                goto block_88;
            }
            var_r5 += 1;
        } while ((u32) var_r5 <= 5U);
        goto block_94;
    case 3:
        var_r5 = 0;
        case0_record_base = (u8 *)0x02034B4C;
loop_10:
        case3_record_offset = var_r5 * 0x270;
        case3_record = (u8 *)(case3_record_offset - (0U - (u32)case0_record_base));
        temp_r0_2 = M2C_FIELD(case3_record, u8 *, 0x13F0);
        if ((temp_r0_2 == 0x34) || (temp_r0_2 == 0x5E)) {
            case3_health_address = case3_record + 0x1386;
            case3_max_address = case3_record + 0x13BA;
            temp_r0_3 = *(s16 *)case3_max_address;
            case3_half = temp_r0_3 + ((u32) temp_r0_3 >> 0x1F);
            case3_health = *(s16 *)case3_health_address;
            case3_half >>= 1;
            if (case3_health < case3_half) {
                goto block_88;
            }
        }
        var_r5 += 1;
        asm volatile(
            ".macro bls target\n\t"
            ".purgem bls\n\t"
            "bls .L14\n\t"
            ".endm\n\t"
            ".macro b target\n\t"
            ".purgem b\n\t"
            ".endm");
        if ((u32) var_r5 > 5U) {
            goto block_94;
        }
        goto loop_10;
    case 4:
        var_r5 = 0;
        case4_record_base = (u8 *)0x02034B4C;
        do {
            temp_r1_3 = (void *)((var_r5 * 0x270) - (0U - (u32)case4_record_base));
            temp_r0_4 = M2C_FIELD(temp_r1_3, u8 *, 0x13F0);
            if ((temp_r0_4 == 0x34) || (temp_r0_4 == 0x5E)) {
                case4_health_address = temp_r1_3 + 0x1386;
                case4_max_address = temp_r1_3 + 0x13BA;
                temp_r0_5 = *(s16 *)case4_max_address;
                case4_half = temp_r0_5 + ((u32) temp_r0_5 >> 0x1F);
                case4_health = *(s16 *)case4_health_address;
                case4_half >>= 1;
                if (case4_health < case4_half) {
                    goto case4_scene;
                }
            }
            var_r5 += 1;
        } while ((u32) var_r5 <= 5U);
        goto block_94;
    case 5:
        if (M2C_FIELD(state, u8 *, 6) != 0) {

        } else {
            var_r5 = 0;
            case5_record_base = (u8 *)0x02034B4C;
            case5_scene_x = 0x3C2;
            case5_scene_y = 0xD;
            case5_scene_buffer = (void *)0x02002880;
loop_27:
            {
                register u32 case5_record_offset asm("r0");

                case5_record_offset = var_r5 * 0x270;
                case5_record = (u8 *)(case5_record_offset - (0U - (u32)case5_record_base));
            }
            temp_r0_6 = M2C_FIELD(case5_record, u8 *, 0x13F0);
            if ((temp_r0_6 != 0x34) && (temp_r0_6 != 0x5E)) {
                goto case5_retry;
            } else {
                case5_health_address = case5_record + 0x1386;
                case5_max_address = case5_record + 0x13BA;
                temp_r0_7 = *(s16 *)case5_max_address;
                case5_half = temp_r0_7 + ((u32) temp_r0_7 >> 0x1F);
                case5_health = *(s16 *)case5_health_address;
                case5_half >>= 1;
                if (case5_health >= case5_half) {

                } else {
                    case5_out_args[0] = 0x68;
                    case5_out_args[1] = case5_scene_x;
                    case5_out_args[2] = case5_scene_y;
                    case5_out_args[3] = 8;
                    case5_out_args[4] = 0;
                    temp_r8 = func_08094484_4(0x08359850, 0x0835985C, 0, 8);
                    func_08098BB4(0x08017BD3);
                    func_0809A9C8(0x46, 0, 0, case5_scene_x, case5_scene_y, case5_scene_buffer);
                    func_08098BB4(0x08017BEC);
                    func_0809A9C8(9, 6, 0, case5_scene_x, case5_scene_y, case5_scene_buffer);
                    func_08098BB4(0x08018021);
                    func_0809A9C8(3, 1, 0, case5_scene_x, case5_scene_y, case5_scene_buffer);
                    func_08098BB4(0x0801805A);
                    func_0809A9C8(0x34, 2, 0, case5_scene_x, case5_scene_y, case5_scene_buffer);
                    func_08098BB4(0x08018093);
                    func_0809A9C8(0x34, 3, 0, case5_scene_x, case5_scene_y, case5_scene_buffer);
                    func_08098BB4(0x08018121);
                    func_0809A9C8(1, 3, 0, case5_scene_x, case5_scene_y, case5_scene_buffer);
                    func_08098BB4(0x08018184);
                    func_0809A9C8(0x34, 3, 0, case5_scene_x, case5_scene_y, case5_scene_buffer);
                    func_08098BB4(0x080181E6);
                    func_08094554(temp_r8);
                    func_08098BB4(0x08017BE6);
                    case5_state_tail = (u8 *)0x0203055C;
                    M2C_FIELD(case5_state_tail, u8 *, 6) = (u8) (M2C_FIELD(case5_state_tail, u8 *, 6) + 1);
                }
            }
        }
        goto block_94;
case5_retry:
        var_r5 += 1;
        if ((u32) var_r5 <= 5U) {
            goto loop_27;
        }
        goto block_94;
    case 6:
        var_r5_6 = 0;
        case6_outer_base = (u8 *)0x02034B4C;
loop_38:
        if (((func_080E9D88(0U, var_r5_6) << 0x18) == 0) || ((temp_r0_8 = M2C_FIELD(((var_r5_6 * 0x270) + case6_outer_base), u8 *, 0x70), (temp_r0_8 != 0x1E)) && (temp_r0_8 != 0x5F))) {
            var_r5_6 = (u32) (u8) (var_r5_6 + 1);
            if (var_r5_6 <= 5U) {
                goto loop_38;
            }
        }
        var_r4_2 = 0;
        case6_inner_base = (u8 *)0x02034B4C;
        while ((var_r4_2 <= 5U) && (((func_080E9D88(1U, var_r4_2) << 0x18) == 0) || (M2C_FIELD(((var_r4_2 * 0x270) + case6_inner_base), u8 *, 0x13F0) != 0x22))) {
            var_r4_2 = (u32) (u8) (var_r4_2 + 1);
        }
        if (var_r5_6 > 5U) {

        } else if (var_r4_2 > 5U) {

        } else {
            temp_r3 = 2 & sub_080C682C_state[6];
            if (temp_r3 != 0) {

            } else if (({
                case6_score_base2 = (u8 *)0x02034B4C;
                case6_score_offset2 = 0xA078;
                asm volatile(".include \"src/sub_080C682C_fix_score2.inc\""
                    : "+r"(case6_score_base2), "+r"(case6_score_offset2));
                *(s16 *)(case6_score_base2 + case6_score_offset2);
            }) == 0) {

            } else {
                temp_r8_2 = func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, (s32) temp_r3);
                func_08098BB4(0x08017BD3);
                func_0809A9C8(0x22, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08018ED2);
                func_0809A9C8(0x21, 6, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08018F1E);
                func_0809A9C8(0x31, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08018F89);
                func_0809A9C8(0x31, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08018FFC);
                func_0809A9C8(0x21, 7, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019052);
                func_0809A9C8(0x31, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080190B0);
                func_0809A9C8(0x21, 7, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080190FA);
                func_0809A9C8(0x20, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019119);
                func_0809A9C8(0x31, 7, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801913A);
                func_0809A9C8(0x21, 4, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019177);
                func_08094554(temp_r8_2);
                func_08098BB4(0x08017BE6);
                {
                    register u32 case6_old_flags2 asm("r1") = sub_080C682C_state[6];
                    register u32 case6_new_flags2 asm("r0") = 2;

                    case6_new_flags2 |= case6_old_flags2;
                    sub_080C682C_state[6] = (u8)case6_new_flags2;
                }
            }
            temp_r3_2 = 4 & sub_080C682C_state[6];
            if (temp_r3_2 != 0) {

            } else if ((s32) ({
                case6_score_base4 = (u8 *)0x02034B4C;
                case6_score_offset4 = 0xA078;
                asm volatile(".include \"src/sub_080C682C_fix_score4.inc\""
                    : "+r"(case6_score_base4), "+r"(case6_score_offset4));
                *(s16 *)(case6_score_base4 + case6_score_offset4);
            }) <= 0xC7) {

            } else {
                temp_r8_3 = func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, (s32) temp_r3_2);
                func_08098BB4(0x08017BD3);
                func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801919E);
                func_0809A9C8(0x22, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080191F8);
                func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801925B);
                func_0809A9C8(0x22, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080192F5);
                func_0809A9C8(0x1E, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080193A6);
                func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080193DB);
                func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019480);
                func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080194D0);
                func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801954D);
                func_0809A9C8(0x22, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019617);
                func_0809A9C8(0x22, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801963A);
                func_0809A9C8(0x22, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801969D);
                func_0809A9C8(0x1E, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801972B);
                func_0809A9C8(0x1E, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019756);
                func_08094554(temp_r8_3);
                func_08098BB4(0x08017BE6);
                sub_080C682C_state[6] = (u8) (4 | sub_080C682C_state[6]);
            }
            temp_r3_3 = 8 & sub_080C682C_state[6];
            if (temp_r3_3 != 0) {

            } else if ((s32) ({
                case6_score_base8 = (u8 *)0x02034B4C;
                case6_score_offset8 = 0xA07A;
                asm volatile("" : "+r"(case6_score_base8), "+r"(case6_score_offset8));
                *(s16 *)(case6_score_base8 + case6_score_offset8);
            }) <= 0xC7) {

            } else {
                temp_r8_4 = func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, (s32) temp_r3_3);
                func_08098BB4(0x08017BD3);
                func_0809A9C8(0x1E, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080197BB);
                func_0809A9C8(0x20, 6, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019815);
                func_0809A9C8(0x21, 6, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x0801986B);
                func_0809A9C8(0x23, 0, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080198A0);
                func_0809A9C8(0x1E, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x080198C3);
                func_0809A9C8(0x22, 3, 0, 0x3C2, 0xD, 0x02002880);
                func_08098BB4(0x08019930);
                func_08094554(temp_r8_4);
                func_08098BB4(0x08017BE6);
                sub_080C682C_state[6] = (u8) (8 | sub_080C682C_state[6]);
            }
        }
        goto block_94;
    case 7:
        var_r5_7 = 0;
        case7_outer_base = (u8 *)0x02034B4C;
loop_68:
        if (((func_080E9D88(0U, var_r5_7) << 0x18) == 0) || ((temp_r0_9 = M2C_FIELD(((var_r5_7 * 0x270) + case7_outer_base), u8 *, 0x70), (temp_r0_9 != 0x1E)) && (temp_r0_9 != 0x5F))) {
            var_r5_7 = (u32) (u8) (var_r5_7 + 1);
            if (var_r5_7 <= 5U) {
                goto loop_68;
            }
        }
        var_r4_3 = 0;
        case7_inner_base = (u8 *)0x02034B4C;
        while ((var_r4_3 <= 5U) && (((func_080E9D88(1U, var_r4_3) << 0x18) == 0) || (M2C_FIELD(((var_r4_3 * 0x270) + case7_inner_base), u8 *, 0x13F0) != 0x3B))) {
            var_r4_3 = (u32) (u8) (var_r4_3 + 1);
        }
        if (var_r5_7 > 5U) {
            goto block_94;
        }
        if (var_r4_3 > 5U) {
            goto block_94;
        }
        case7_tail_base = (u8 *)0x02034B4C;
        case7_score_offset = 0xA078;
        if ((s32) *(s16 *)(case7_tail_base + case7_score_offset) <= 0xC7) {
            case7_tail_base = (u8 *)((var_r5_7 * 0x270) - (0U - (u32)case7_tail_base));
            temp_r1_5 = case7_tail_base;
            if (M2C_FIELD(temp_r1_5, s16 *, 6) != 1) {
                if (M2C_FIELD(temp_r1_5, s16 *, 0x1386) != 1) {
                    goto block_94;
                }
                goto block_88;
            }
        }
        goto block_88;
case4_scene:
        func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, 0);
        func_08098BB4(0x08017BD3);
        func_0809A9C8(0x34, 2, 0, 0x3C2, 0xD, 0x02002880);
        func_08098BB4(0x08018369);
        func_0809A9C8(1, 1, 0, 0x3C2, 0xD, 0x02002880);
        func_08098BB4(0x080183F1);
        func_0809A9C8(3, 1, 0, 0x3C2, 0xD, 0x02002880);
        func_08098BB4(0x08018440);
block_88:
        return 4U;
    case 9:
        var_r5 = 0;
        case9_record_base = (u8 *)0x02034B4C;
loop_90:
        temp_r1_6 = (void *)((var_r5 * 0x270) - (0U - (u32)case9_record_base));
        temp_r0_10 = M2C_FIELD(temp_r1_6, u8 *, 0x13F0);
        if (((temp_r0_10 != 0x34) && (temp_r0_10 != 0x5E)) || (M2C_FIELD(temp_r1_6, s16 *, 0x1386) != 1)) {
            var_r5 += 1;
            if ((u32) var_r5 > 5U) {
                goto block_94;
            }
            goto loop_90;
        }
        goto block_88;
    default:
block_94:
        var_r6 = 0;
        var_r5 = 0;
        do {
            var_r4 = 0;
            while ((var_r4 <= 5U) && ((func_080E9D88(var_r5, var_r4) << 0x18) == 0)) {
                var_r4 = (u32) (u8) (var_r4 + 1);
            }
            if (var_r4 == 6) {
                var_r6 |= 1 << var_r5;
            }
            var_r5 += 1;
        } while ((u32) var_r5 <= 1U);
        return var_r6;
    }
}
