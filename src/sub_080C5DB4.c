#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_0809A4CC(u8, u8, u16, u8);             /* extern */
M2C_UNK func_080BAB3C();                            /* extern */
M2C_UNK func_080BB224(s32, s32, s32, s32);          /* extern */
struct VecC5DB4 {
    s32 x;
    s32 y;
    s32 z;
};
M2C_UNK func_080BB424(struct VecC5DB4 *, s32 *, s32); /* extern */
s32 func_080BB654();                                /* extern */
M2C_UNK func_080C04DC(s32, u8);                     /* extern */
M2C_UNK func_080C9F00(s32, s32);                    /* extern */
M2C_UNK func_080CA0AC(s32, s32, u8, s32);           /* extern */
s32 func_080CA140();                                /* extern */
s32 func_080E9D88(u32, u32);                        /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080C60E0();                            /* static */
M2C_UNK jtbl_080C6380();                            /* static */
extern u8 D_02034B4C[];
extern s32 D_087A2790[];
extern s32 D_087A2798[];

static inline u8 *switch_entry_address(u8 *base, u32 index) {
    u32 address;

    address = index * 0xC;
    asm volatile("add %0, %1, %0" : "+r"(address) : "r"(base));
    return (u8 *)address;
}

static inline u32 add_address_accumulator(u32 address, u32 addend) {
    asm volatile("add %0, %0, %1" : "+r"(address) : "r"(addend));
    return address;
}

void sub_080C5DB4(u8 arg0) {
    struct VecC5DB4 vec;
    s32 tail[2];
    s32 sp14;
    s32 var_r3;
    s32 var_r3_2;
    s32 temp_r0_2;
    s32 temp_r1;
    s32 temp_r4_3;
    s32 temp_r6;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r6;
    s32 var_sl_4;
    register s32 var_sl_5 asm("sl");
    u8 *temp_r2_2;
    u8 *temp_r2_3;
    register u16 temp_r1_2 asm("r1");
    u16 temp_r4;
    u16 temp_r4_2;
    u32 temp_r0;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 var_r7_2;
    u32 temp_r4_4;
    register u32 var_r5 asm("r5");
    u8 var_r6_2;
    u8 var_r6_3;
    u8 var_r7;
    u8 var_r7_3;
    u8 var_r7_4;
    u8 var_r7_5;
    u8 var_r7_6;
    u8 var_r7_7;
    u8 var_r7_8;
    u8 var_r7_9;
    s32 temp_r0_5;
    void *temp_r0_6;
    void *temp_r1_3;
    void *temp_r2;
    void *temp_r3;
    void *temp_r3_2;

    sp14 = (s32) arg0;
    {
        register u8 *initial_side_address asm("r0");
        register u32 initial_side_offset asm("r1");

        initial_side_address = D_02034B4C;
        initial_side_offset = 0x27A4;
        asm volatile("add %0, %0, %1"
                     : "+r"(initial_side_address)
                     : "r"(initial_side_offset));
        var_r5 = *initial_side_address;
    }
    do {
        s32 side_record_offset;
        u32 side_object_offset;
        u8 *record_base;
        void **object_base;

        {
            register s32 initial_flag_zero asm("r2");

            initial_flag_zero = 0;
            asm volatile("" : "+r"(initial_flag_zero));
            var_sl_5 = initial_flag_zero;
        }
        var_r7 = 0;
        record_base = D_02034B4C;
        side_record_offset = var_r5 * 0x1218;
        object_base = (void **)0x02032EBC;
        side_object_offset = var_r5 * 0x18;
loop_2:
        if (1 & *(u16 *)(add_address_accumulator(
                             add_address_accumulator(var_r7 * 0x304,
                                                     side_record_offset),
                             (u32)record_base) +
                         0x7C28)) {
            *(s32 *)(*(void **)add_address_accumulator(
                           add_address_accumulator(var_r7 * 4,
                                                   side_object_offset),
                           (u32)object_base) +
                       0x2C) = 0x20000;
            var_sl_5 = 1;
        }
        var_r7 += 1;
        if ((u32) var_r7 <= 5U) {
            goto loop_2;
        }
        func_080ED17C(1);
        if (var_sl_5 != 0) {
            if (sp14 != 0) {
                if (sp14 == 1) {
                register s32 *position_table asm("r6");
                register s32 *average_table asm("sl");
                s32 *side_position_base;
                u32 side_position_address;
                register s32 saved_tail_word asm("ip");
                register volatile s32 *tail_words asm("r8");
                register s32 case_side_record_offset asm("r4");
                u32 opposite_index;
                register u8 *case_record_base asm("r9");

                vec.x = 0;
                var_r7 = 0;
                position_table = D_087A2790;
                saved_tail_word = tail[0];
                tail_words = tail;
                case_record_base = D_02034B4C;
                case_side_record_offset = var_r5 * 0x1218;
                average_table = position_table;
                side_position_address = var_r5 * 0x48;
                side_position_address += (u32)position_table;
                side_position_base = (s32 *)side_position_address;
                opposite_index = (var_r5 * 6) + 3;
loop_11:
                if (1 & *(u16 *)(case_record_base +
                                 ((var_r7 * 0x304) + case_side_record_offset) +
                                 0x7C28)) {
                    if (var_r7 > 2U) {
                        if (vec.x != 0) {
                            temp_r0 = vec.x + average_table[opposite_index * 3];
                            vec.x = (s32) (temp_r0 + (temp_r0 >> 0x1F)) >> 1;
                            goto block_20;
                        }
                        goto block_22;
                    } else {
                        if (vec.x == 0) {
                            vec.x = *side_position_base;
                            var_r7 = 2;
                        }
                        goto block_18;
                    }
                } else {
block_18:
                    var_r7 = (u8) (var_r7 + 1);
                    if ((u32) var_r7 <= 5U) {
                        goto loop_11;
                    }
                }
block_20:
                if (var_r5 == 0) {
                    var_r0 = position_table[2];
                    goto block_24;
                }
                goto block_23;
block_22:
                {
                    s32 fallback_index;

                    fallback_index = (var_r5 * 6) + 3;
                    vec.x = position_table[fallback_index * 3];
                }
                goto block_20;
block_23:
                {
                    s32 nonzero_y_index;
                    s32 nonzero_y_offset;
                    u8 *nonzero_y_base;

                    nonzero_y_index = (var_r5 * 6) + 2;
                    nonzero_y_offset = nonzero_y_index * 0xC;
                    nonzero_y_base = (u8 *)position_table;
                    nonzero_y_base += 8;
                    asm volatile(
                        "add %0, %0, %1\n\t"
                        "ldr %1, [%0]"
                        : "+r"(nonzero_y_offset), "+r"(nonzero_y_base)
                        :
                        : "memory");
                    var_r0 = (s32)(u32)nonzero_y_base;
                    asm volatile("" : "+r"(position_table));
                }
block_24:
                vec.y = var_r0;
                {
                    s32 max_side_record_offset;
                    u32 max_position_index_base;
                    s32 *max_position_table;
                    u8 *max_record_base;

                    var_r7 = 0;
                    max_record_base = D_02034B4C;
                    max_side_record_offset = var_r5 * 0x1218;
                    max_position_index_base = var_r5 * 6;
                    max_position_table = D_087A2798;
                    do {
                        u32 max_record_address;

                        max_record_address = (var_r7 * 0x304) +
                                             max_side_record_offset;
                        max_record_address += (u32)max_record_base;
                        if (1 & *(u16 *)(max_record_address + 0x7C28)) {
                            if (vec.y < max_position_table[
                                    (max_position_index_base + var_r7) * 3]) {
                                vec.y = max_position_table[
                                    (max_position_index_base + var_r7) * 3];
                            }
                        }
                        var_r7 += 1;
                    } while ((u32) var_r7 <= 5U);
                }
                vec.z = 0x8000;
                temp_r0_2 = (0xFFFF0000 & saved_tail_word) | 0x20;
                tail[0] = temp_r0_2;
                {
                    volatile s32 *tail_access;

                    tail_access = tail_words;
                    tail_access[1] = (s32) ((u32) tail_access[1] & 0xFFFF0000);
                }
                {
                    u32 tail_low_mask;

                    tail_low_mask = 0xFFFF;
                    tail[0] = (s32) ((u32) tail[0] & tail_low_mask);
                }
                func_080BB424(&vec, (s32 *)tail_words, 0);
                } else if (({
                               register s32 mode_two_check asm("r2");

                               mode_two_check = sp14;
                               asm volatile("" : "+r"(mode_two_check));
                               mode_two_check;
                           }) == 2) {
                    func_080BB224(2, var_r5, 0, 0);
                }
                while ((func_080BB654() << 0x18) == 0) {
                    func_080ED17C(1);
                }
            }
            {
                s32 action_side_offset;

                {
                    register s32 action_flag_zero asm("r3");

                    action_flag_zero = 0;
                    asm volatile("" : "+r"(action_flag_zero));
                    var_sl_5 = action_flag_zero;
                }
                var_r6 = 1;
                var_r7 = 0;
                action_side_offset = var_r5 * 0x1218;
                do {
                    u32 action_record_address;

                    action_record_address = (var_r7 * 0x304) + 0x0203C774;
                    temp_r2 = (void *)(action_side_offset + action_record_address);
                    temp_r1_2 = M2C_FIELD(temp_r2, u16 *, 0);
                    if ((1 & temp_r1_2) && (2 & temp_r1_2)) {
                        if (8 & temp_r1_2) {
                            func_080CA0AC(1, var_r5, var_r7, M2C_FIELD(temp_r2, s16 *, 2));
                            var_r6 = 0;
                        } else if (0x10 & temp_r1_2) {
                            func_080CA0AC(0x25, var_r5, var_r7, M2C_FIELD(temp_r2, s16 *, 2));
                        } else {
                            func_080CA0AC(2, var_r5, var_r7, M2C_FIELD(temp_r2, s16 *, 2));
                        }
                        var_sl_5 = 1;
                    }
                    var_r7 += 1;
                } while ((u32) var_r7 <= 5U);
                if (var_sl_5 != 0) {
                    func_080C9F00(var_r5, 0);
                    if (var_r6 != 0) {
                        func_08092E84(0x58);
                    }
                    while (func_080CA140() == 0) {
                        func_080ED17C(1);
                    }
                }
            }
            var_r7_5 = 0;
loop_50:
            var_sl_5 = 0;
            var_r6_2 = 0;
            asm volatile("" ::
                "r"(var_r6_2), "r"(var_r6_2),
                "r"(var_r6_2), "r"(var_r6_2),
                "r"(var_r6_2), "r"(var_r6_2),
                "r"(var_r6_2), "r"(var_r6_2),
                "r"(var_r6_2), "r"(var_r6_2));
            asm volatile("" ::
                "r"(var_r6_2), "r"(var_r6_2),
                "r"(var_r6_2), "r"(var_r6_2));
loop_51:
            if ((func_080E9D88(var_r5, var_r6_2) << 0x18) == 0) {

            } else {
                register s32 switch2_side_offset asm("r2");
                register u32 switch2_entry_offset asm("r0");
                register u8 *switch2_entry_base asm("r1");

                switch2_side_offset = var_r5 * 0x1218;
                switch2_entry_offset = var_r6_2 * 0x304;
                switch2_entry_base = (u8 *)0x0203C774;
                asm volatile("add %0, %0, %1"
                             : "+r"(switch2_entry_offset)
                             : "r"(switch2_entry_base));
                asm volatile("add %0, %0, %1"
                             : "+r"(switch2_side_offset)
                             : "r"(switch2_entry_offset));
                temp_r2_2 = (u8 *)switch2_side_offset;
                if (!(1 & *(u16 *)temp_r2_2)) {

                } else {
                    temp_r4 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), u16 *, 8);
                    if (temp_r4 == 0) {

                    } else {
                        temp_r0_3 = 0x7F;
                        temp_r0_3 &= temp_r4;
                        temp_r0_3 -= 1;
                        switch (temp_r0_3) {        /* switch 2; irregular */
                        case 0:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 6;
                            goto block_89;
                        case 1:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 7;
                            goto block_89;
                        case 2:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 8;
                            goto block_89;
                        case 3:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 9;
                            goto block_89;
                        case 4:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0xA;
                            goto block_89;
                        case 5:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0xB;
                            goto block_89;
                        case 6:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0xC;
                            goto block_89;
                        case 7:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0xD;
                            goto block_89;
                        case 8:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0xE;
                            goto block_89;
                        case 9:                     /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0xF;
                            goto block_89;
                        case 10:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x10;
                            goto block_89;
                        case 11:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x11;
                            goto block_89;
                        case 12:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x12;
                            goto block_89;
                        case 13:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x13;
                            goto block_89;
                        case 14:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x14;
                            goto block_89;
                        case 15:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x15;
                            goto block_89;
                        case 16:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x16;
                            goto block_89;
                        case 17:                    /* switch 2 */
                            var_r0_3 = 0x17;
                            goto block_93;
                        case 18:                    /* switch 2 */
                            var_r0_3 = 0x18;
                            goto block_93;
                        case 19:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x1B;
                            goto block_89;
                        case 20:                    /* switch 2 */
                            var_r0_3 = 0x1C;
                            goto block_93;
                        case 21:                    /* switch 2 */
                            var_r0_3 = 0x1E;
                            goto block_93;
                        case 22:                    /* switch 2 */
                            var_r0_3 = 0x1F;
                            goto block_93;
                        case 23:                    /* switch 2 */
                            var_r0_3 = 0x20;
                            goto block_93;
                        case 24:                    /* switch 2 */
                            var_r0_3 = 5;
                            goto block_93;
                        case 25:                    /* switch 2 */
                            var_r0_3 = 3;
                            goto block_93;
                        case 26:                    /* switch 2 */
                            var_r0_3 = 0x22;
                            goto block_93;
                        case 27:                    /* switch 2 */
                            var_r3 = M2C_FIELD(switch_entry_address(temp_r2_2, var_r7_5), s16 *, 0xA);
                            var_r0_2 = 0x24;
                            goto block_89;
block_89:
                            func_080CA0AC(var_r0_2, var_r5, var_r6_2, var_r3);
                            goto block_94;
                        case 34:                    /* switch 2 */
                            var_r0_3 = 0x27;
                            goto block_93;
                        case 35:                    /* switch 2 */
                            var_r0_3 = 0x26;
                            goto block_93;
                        case 36:                    /* switch 2 */
                            var_r0_3 = 0x29;
                            goto block_93;
block_93:
                            func_080CA0AC(var_r0_3, var_r5, var_r6_2, 0);
                            goto block_94;
                        case 37:                    /* switch 2 */
                            func_080CA0AC(0x2A, var_r5, var_r6_2, 0);
                            goto block_94;
                        }
                        goto block_94;
block_94:
                        var_sl_5 = 1;
                    }
                }
            }
            var_r6_2 += 1;
            if ((u32) var_r6_2 <= 5U) {
                goto loop_51;
            }
            if (var_sl_5 != 0) {
                func_080C9F00(var_r5, 2);
                while (func_080CA140() == 0) {
                    func_080ED17C(1);
                }
            }
            asm volatile("" : "+r"(var_r7_5));
            var_r7_5 += 1;
            if ((u32) var_r7_5 <= 0x1FU) {
                goto loop_50;
            }
            var_r7_6 = 0;
loop_105:
            var_sl_5 = 0;
            var_r6_3 = 0;
            asm volatile("" ::
                "r"(var_r6_3), "r"(var_r6_3),
                "r"(var_r6_3), "r"(var_r6_3),
                "r"(var_r6_3), "r"(var_r6_3),
                "r"(var_r6_3), "r"(var_r6_3),
                "r"(var_r6_3), "r"(var_r6_3));
            asm volatile("" ::
                "r"(var_r6_3), "r"(var_r6_3),
                "r"(var_r6_3), "r"(var_r6_3));
loop_106:
            if ((func_080E9D88(var_r5, var_r6_3) << 0x18) == 0) {

            } else {
                register s32 switch3_side_offset asm("r2");
                register u32 switch3_entry_offset asm("r0");
                register u8 *switch3_entry_base asm("r1");

                switch3_side_offset = var_r5 * 0x1218;
                switch3_entry_offset = var_r6_3 * 0x304;
                switch3_entry_base = (u8 *)0x0203C774;
                asm volatile("add %0, %0, %1"
                             : "+r"(switch3_entry_offset)
                             : "r"(switch3_entry_base));
                asm volatile("add %0, %0, %1"
                             : "+r"(switch3_side_offset)
                             : "r"(switch3_entry_offset));
                temp_r2_3 = (u8 *)switch3_side_offset;
                if (!(1 & *(u16 *)temp_r2_3)) {

                } else {
                    temp_r4_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), u16 *, 0x188);
                    if (temp_r4_2 == 0) {

                    } else {
                        temp_r0_4 = 0x7F;
                        temp_r0_4 &= temp_r4_2;
                        temp_r0_4 -= 1;
                        switch (temp_r0_4) {        /* switch 3; irregular */
                        case 0:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 6;
                            goto block_136;
                        case 1:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 7;
                            goto block_136;
                        case 2:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 8;
                            goto block_136;
                        case 3:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 9;
                            goto block_136;
                        case 4:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0xA;
                            goto block_136;
                        case 5:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0xB;
                            goto block_136;
                        case 6:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0xC;
                            goto block_136;
                        case 7:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0xD;
                            goto block_136;
                        case 8:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0xE;
                            goto block_136;
                        case 9:                     /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0xF;
                            goto block_136;
                        case 10:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0x10;
                            goto block_136;
                        case 11:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0x11;
                            goto block_136;
                        case 12:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0x12;
                            goto block_136;
                        case 13:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0x13;
                            goto block_136;
                        case 14:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0x14;
                            goto block_136;
                        case 15:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0x15;
                            goto block_136;
                        case 16:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r3_2 = 0 - var_r3_2;
                            var_r0_4 = 0x16;
                            goto block_136;
                        case 17:                    /* switch 3 */
                            var_r0_5 = 0x19;
                            goto block_141;
                        case 18:                    /* switch 3 */
                            var_r0_5 = 0x1A;
                            goto block_141;
                        case 19:                    /* switch 3 */
                            var_r3_2 = M2C_FIELD(switch_entry_address(temp_r2_3, var_r7_6), s16 *, 0x18A);
                            var_r0_4 = 0x1B;
                            goto block_136;
block_136:
                            func_080CA0AC(var_r0_4, var_r5, var_r6_3, var_r3_2);
                            goto block_142;
                        case 20:                    /* switch 3 */
                            var_r0_5 = 0x1D;
                            goto block_141;
                        case 23:                    /* switch 3 */
                            var_r0_5 = 0x21;
                            goto block_141;
                        case 24:                    /* switch 3 */
                            var_r0_5 = 0x28;
                            goto block_141;
                        case 26:                    /* switch 3 */
                            var_r0_5 = 0x23;
                            goto block_141;
block_141:
                            func_080CA0AC(var_r0_5, var_r5, var_r6_3, 0);
                            goto block_142;
                        case 27:                    /* switch 3 */
                            func_080CA0AC(0x2B, var_r5, var_r6_3, 0);
                            goto block_142;
                        case 28:                    /* switch 3 */
                        case 29:                    /* switch 3 */
                        case 30:                    /* switch 3 */
                        case 31:                    /* switch 3 */
                        case 32:                    /* switch 3 */
                        case 33:                    /* switch 3 */
                        case 34:                    /* switch 3 */
                        case 35:                    /* switch 3 */
                        case 36:                    /* switch 3 */
                        case 37:                    /* switch 3 */
                            goto block_142;
                        }
                        goto block_142;
block_142:
                        var_sl_5 = 1;
                    }
                }
            }
            var_r6_3 += 1;
            if ((u32) var_r6_3 <= 5U) {
                goto loop_106;
            }
            if (var_sl_5 != 0) {
                func_080C9F00(var_r5, 2);
                while (func_080CA140() == 0) {
                    func_080ED17C(1);
                }
            }
            asm volatile("" : "+r"(var_r7_6));
            var_r7_6 += 1;
            if ((u32) var_r7_6 <= 0x1FU) {
                goto loop_105;
            }
            {
                register u8 *cleanup_reset_address asm("r1");
                register u32 cleanup_reset_work asm("r0");

                cleanup_reset_address = D_02034B4C;
                cleanup_reset_work = 0x27C0;
                cleanup_reset_address += cleanup_reset_work;
                cleanup_reset_work = 0;
                *cleanup_reset_address = cleanup_reset_work;
                var_sl_5 = cleanup_reset_work;
            }
            var_r7_7 = 0;
            do {
                if ((func_080E9D88(var_r5, var_r7_7) << 0x18) != 0) {
                    u8 *cleanup_record_base;

                    cleanup_record_base = D_02034B4C;
                    temp_r6 = var_r7_7 * 0x270;
                    temp_r4_3 = var_r5 * 0x1380;
                    temp_r0_5 = temp_r6 + temp_r4_3;
                    temp_r0_6 = cleanup_record_base + temp_r0_5;
                    if (({
                            register s32 cleanup_signed_field asm("r0");

                            asm volatile(
                                "mov r2, #6\n\t"
                                "ldrsh %0, [%1, r2]"
                                : "=r"(cleanup_signed_field)
                                : "0"(temp_r0_6)
                                : "r2");
                            cleanup_signed_field;
                        }) == 0) {
                        func_080C04DC(var_r5, var_r7_7);
                        if (var_r5 != 0) {
                            register u8 *cleanup_address_r3 asm("r3");
                            register u32 cleanup_address_r0 asm("r0");

                            cleanup_address_r3 = cleanup_record_base;
                            asm volatile("add %0, %1, %2"
                                         : "=r"(cleanup_address_r0)
                                         : "r"(temp_r6), "r"(cleanup_address_r3));
                            asm volatile("add %0, %1, %2"
                                         : "=r"(cleanup_address_r3)
                                         : "r"(temp_r4_3), "r"(cleanup_address_r0));
                            temp_r3 = cleanup_address_r3;
                            *(s32 *)(cleanup_record_base + 0xA070) += M2C_FIELD(temp_r3, s32 *, 0x268);
                            *(s32 *)(cleanup_record_base + 0xA074) += M2C_FIELD(temp_r3, s32 *, 0x26C);
                            if (!(0x40 & M2C_FIELD(temp_r0_6, u16 *, 4))) {
                                register u8 *cleanup_destination asm("r0");
                                register u32 cleanup_count_carrier asm("r3");
                                register u8 *cleanup_increment_ptr asm("r1");

                                cleanup_destination = cleanup_record_base + 0x27C1;
                                cleanup_count_carrier = 0x0203730C;
                                cleanup_count_carrier = *(u8 *)cleanup_count_carrier;
                                cleanup_destination += cleanup_count_carrier;
                                *cleanup_destination = *(u8 *)temp_r0_6;
                                cleanup_increment_ptr = (u8 *)0x0203730C;
                                *cleanup_increment_ptr = (u8)(*cleanup_increment_ptr + 1);
                            }
                        }
                        {
                            register u8 *cleanup_mode_seed asm("r0");
                            register u8 *cleanup_mode_base asm("r2");
                            register u32 cleanup_mode1 asm("r1");

                            cleanup_mode_seed = D_02034B4C;
                            cleanup_mode_base = (u8 *)0x27BE;
                            asm volatile("add %0, %1, %2"
                                         : "=r"(cleanup_mode1)
                                         : "r"(cleanup_mode_seed),
                                           "r"(cleanup_mode_base));
                            cleanup_mode1 = var_r5 + cleanup_mode1;
                            cleanup_mode1 = *(u8 *)cleanup_mode1;
                            cleanup_mode_base = cleanup_mode_seed;
                            if ((cleanup_mode1 == 0x2E) && ((var_r7_7 == 1) || (var_r7_7 == 3) || (var_r7_7 == 5))) {
                                register u8 *cleanup_mode1_store asm("r0");

                                cleanup_mode1_store = cleanup_mode_base + 0x27BE;
                                asm volatile("add %0, %1, %0"
                                             : "+r"(cleanup_mode1_store)
                                             : "r"(var_r5));
                                *cleanup_mode1_store = 0U;
                            }
                            {
                                register u32 cleanup_mode2 asm("r0");

                                cleanup_mode2 = (u32)cleanup_mode_base + 0x27BE;
                                asm volatile("add %0, %1, %0"
                                             : "+r"(cleanup_mode2)
                                             : "r"(var_r5));
                                cleanup_mode2 = *(u8 *)cleanup_mode2;
                                if ((cleanup_mode2 == 0x2F) && ((var_r7_7 == 0) || (var_r7_7 == 2) || (var_r7_7 == 4))) {
                                    register u8 *cleanup_mode2_store asm("r0");

                                    cleanup_mode2_store = cleanup_mode_base + 0x27BE;
                                    asm volatile("add %0, %1, %0"
                                                 : "+r"(cleanup_mode2_store)
                                                 : "r"(var_r5));
                                    *cleanup_mode2_store = 0U;
                                }
                            }
                            {
                                register u8 *mode3_ptr asm("r1");
                                register u32 mode3_address asm("r0");

                                mode3_ptr = (u8 *)0x27BE;
                                mode3_address =
                                    (u32)cleanup_mode_base + (u32)mode3_ptr;
                                mode3_ptr = (u8 *)(var_r5 + mode3_address);
                                if ((*mode3_ptr == 0x30) && ((var_r7_7 == 1) || (var_r7_7 == 4))) {
                                    *mode3_ptr = 0U;
                                }
                            }
                        }
                        {
                            register s32 cleanup_success_seed asm("r2");

                            asm volatile(
                                "mov %1, #1\n\t"
                                "mov %0, %1"
                                : "=r"(var_sl_5), "=r"(cleanup_success_seed));
                        }
                    }
                }
                var_r7_7 += 1;
            } while ((u32) var_r7_7 <= 5U);
            if (({
                    register s32 cleanup_flag_check asm("r3");

                    cleanup_flag_check = var_sl_5;
                    asm volatile("" : "+r"(cleanup_flag_check));
                    cleanup_flag_check;
                }) != 0) {
                func_080C9F00(var_r5, 1);
                while (func_080CA140() == 0) {
                    func_080ED17C(1);
                }
            }
            {
                u8 *opponent_record_base;
                void **opponent_object_base;
                u8 opponent_a;
                u8 opponent_b;
                u32 opponent_one;

                var_r7 = 0;
                opponent_one = 1;
                temp_r4_4 = var_r5;
                asm volatile("" : "+r"(temp_r4_4));
                temp_r4_4 ^= opponent_one;
                {
                    register u32 opponent_base_guard_r2 asm("r2");
                    register u32 opponent_base_guard_r3 asm("r3");

                    asm volatile("" : "=&r"(opponent_base_guard_r2),
                                          "=&r"(opponent_base_guard_r3));
                    opponent_record_base = D_02034B4C;
                    asm volatile("" : : "r"(opponent_base_guard_r2),
                                          "r"(opponent_base_guard_r3));
                }
                opponent_object_base = (void **)0x02032E8C;
                do {
                    if ((func_080E9D88(temp_r4_4, var_r7) << 0x18) != 0) {
                        s32 opponent_record_offset;
                        u32 opponent_object_address;
                        u32 opponent_object_offset;

                        asm volatile("" : "+r"(temp_r4_4));
                        opponent_record_offset = (var_r7 * 0x270) +
                                                 (temp_r4_4 * 0x1380);
                        temp_r1_3 = opponent_record_base + opponent_record_offset;
                        opponent_a = M2C_FIELD(temp_r1_3, u8 *, 0);
                        opponent_b = M2C_FIELD(temp_r1_3, u8 *, 1);
                        opponent_object_offset = (var_r7 * 4) +
                                                 (temp_r4_4 * 0x18);
                        opponent_object_address = opponent_object_offset;
                        opponent_object_address += (u32)opponent_object_base;
                        temp_r3_2 = *(void **)opponent_object_address;
                        func_0809A4CC(opponent_a,
                                      opponent_b,
                                      M2C_FIELD(temp_r3_2, u16 *, 0xE),
                                      M2C_FIELD(temp_r3_2, u8 *, 0x10));
                    }
                    var_r7 += 1;
                } while ((u32) var_r7 <= 5U);
            }
            {
                s32 final_side_record_offset;
                u32 final_side_object_offset;
                u8 *final_record_base;
                void **final_object_base;

                var_r7 = 0;
                final_record_base = D_02034B4C;
                final_side_record_offset = var_r5 * 0x1218;
                final_object_base = (void **)0x02032EBC;
                final_side_object_offset = var_r5 * 0x18;
                do {
                    if (1 & *(u16 *)(add_address_accumulator(
                                         add_address_accumulator(var_r7 * 0x304,
                                                                 final_side_record_offset),
                                         (u32)final_record_base) +
                                     0x7C28)) {
                        *(s32 *)(*(void **)add_address_accumulator(
                                       add_address_accumulator(var_r7 * 4,
                                                               final_side_object_offset),
                                       (u32)final_object_base) +
                                   0x2C) = 0;
                    }
                    var_r7 += 1;
                } while ((u32) var_r7 <= 5U);
            }
            func_080BAB3C();
        }
        var_r5 ^= 1;
    } while (var_r5 != ({
                 register u8 *final_side_address asm("r0");
                 register u32 final_side_offset asm("r2");

                 final_side_address = D_02034B4C;
                 final_side_offset = 0x27A4;
                 asm volatile("add %0, %0, %1"
                              : "+r"(final_side_address)
                              : "r"(final_side_offset));
                 *final_side_address;
             }));
}
