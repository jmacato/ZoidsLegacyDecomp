#include "m2c_prelude.h"

#define SECOND_REG(value)                                                \
    ({                                                                  \
        register s32 second_reg asm("r1");                               \
        asm volatile("" : "=r"(second_reg) : "r"(value));                \
        second_reg;                                                      \
    })
#define CALL_BE65C_STAGED(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)       \
    do {                                                                \
        register volatile s32 *be65c_outgoing asm("sp");                 \
        be65c_outgoing[0] = (a4);                                       \
        be65c_outgoing[1] = (a5);                                       \
        be65c_outgoing[2] = (a6);                                       \
        be65c_outgoing[3] = (a7);                                       \
        be65c_outgoing[4] = (a8);                                       \
        be65c_outgoing[5] = (a9);                                       \
        {                                                               \
            register s32 be65c_arg0 asm("r0") = (a0);                    \
            register s32 be65c_arg1 asm("r1") = (a1);                    \
            register s32 be65c_arg2 asm("r2") = (a2);                    \
            register s32 be65c_arg3 asm("r3") = (a3);                    \
            func_080BE65C(be65c_arg0, be65c_arg1,                        \
                          be65c_arg2, be65c_arg3);                        \
        }                                                               \
    } while (0)
#define CALL_BE9D8_STAGED(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)       \
    do {                                                                \
        register volatile s32 *be9d8_outgoing asm("sp");                 \
        be9d8_outgoing[0] = (a4);                                       \
        be9d8_outgoing[1] = (a5);                                       \
        be9d8_outgoing[2] = (a6);                                       \
        be9d8_outgoing[3] = (a7);                                       \
        be9d8_outgoing[4] = (a8);                                       \
        be9d8_outgoing[5] = (a9);                                       \
        {                                                               \
            register s32 be9d8_arg0 asm("r0") = (a0);                    \
            register s32 be9d8_arg1 asm("r1") = (a1);                    \
            register s32 be9d8_arg2 asm("r2") = (a2);                    \
            register s32 be9d8_arg3 asm("r3") = (a3);                    \
            func_080BE9D8(be9d8_arg0, be9d8_arg1,                        \
                          be9d8_arg2, be9d8_arg3);                        \
        }                                                               \
    } while (0)

M2C_UNK func_0809A4CC(u8, u8, u16, u8);             /* extern */
M2C_UNK func_080BAF2C(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080BAF2C_regs(s32, s32, s32, s32) asm("func_080BAF2C");
M2C_UNK func_080BB224(s32, s32, s32, s32);          /* extern */
s32 func_080BB654();                                /* extern */
M2C_UNK func_080BE560(s32, u8);                     /* extern */
M2C_UNK func_080BE5A8(s32, u8);                     /* extern */
M2C_UNK func_080BE65C();                            /* extern */
M2C_UNK func_080BE9D8();                            /* extern */
M2C_UNK func_080C007C(u8, s32, u8, s16);            /* extern */
M2C_UNK func_080C007C_word(s32, s32, s32, s32) asm("func_080C007C");
M2C_UNK func_080C00B0(s32, u8);                     /* extern */
M2C_UNK func_080C02B4(s32, u8);                     /* extern */
M2C_UNK func_080C02B4_word(s32, s32) asm("func_080C02B4");
M2C_UNK func_080C030C(s32);                         /* extern */
M2C_UNK func_080C04DC(s32, u8);                     /* extern */
M2C_UNK func_080C04DC_word(s32, s32) asm("func_080C04DC");
M2C_UNK func_080C052C(s32, u8);                     /* extern */
s32 func_080C0C54(s32, s32, u8);                    /* extern */
s32 func_080C0C54_word(s32, s32, s32) asm("func_080C0C54");
M2C_UNK func_080C2DB0();                            /* extern */
M2C_UNK func_080C3440(s32, u8, u8);                 /* extern */
M2C_UNK func_080C3440_word(s32, s32, s32) asm("func_080C3440");
M2C_UNK func_080C34A4(s32, u8, s32);                /* extern */
M2C_UNK func_080C34A4_word(s32, s32, s32) asm("func_080C34A4");
M2C_UNK func_080C9F00(s32, s32);                    /* extern */
s32 func_080CA140();                                /* extern */
M2C_UNK func_080E8B08(s32, u8);                     /* extern */
M2C_UNK func_080E8B08_word(s32, s32) asm("func_080E8B08");
M2C_UNK func_080E90AC(s32, u8);                     /* extern */
s32 func_080E9D88(u32, u32);                        /* extern */
u16 func_080ECD98(s32, s16);                        /* extern */
u16 func_080ECD98_word(s32, s32) asm("func_080ECD98");
u8 func_080ECF78(u8, u8);                           /* extern */
u8 func_080ECF78_word(s32, s32) asm("func_080ECF78");
M2C_UNK func_080ED038(void *, void *, s32);         /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080C3674();                            /* static */

void sub_080C35C4(u8 arg0) {
    volatile s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp2C;
    s32 sp30;
    s32 frame_home34;
    s32 frame_home38;
    s32 frame_home3C;
    s32 frame_home40;
    s32 frame_home44;
    s32 frame_home48;
    s32 frame_home4C;
    s32 frame_home50;
    s32 frame_home54;
    s32 frame_home58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    register volatile s32 *physical_stack asm("sp");
#define sp6C physical_stack[27]
#define sp28 physical_stack[10]
#define sp34 physical_stack[13]
#define sp38 physical_stack[14]
#define sp3C physical_stack[15]
#define sp40 physical_stack[16]
#define sp44 physical_stack[17]
#define sp48 physical_stack[18]
#define sp4C physical_stack[19]
#define sp50 physical_stack[20]
#define sp54 physical_stack[21]
#define sp58 physical_stack[22]
    s32 sp70;
    s32 sp74;
    s32 sp78;
    s32 sp7C;
    s16 temp_r0_2;
    s16 temp_r0_31;
    s32 temp_r0_4;
    register s32 temp_r1_2 asm("r1");
    register s32 case12_effect asm("r5");
    register s32 case12_arg1 asm("r1");
    register s32 case12_neg asm("r2");
    register s32 case0_zero asm("r4");
    u16 case0_max;
    s32 case0_offset;
    register s32 case4_row2 asm("r4");
    register s32 case4_record_offset asm("r0");
    register u8 *case4_scan_base asm("r5");
    register s32 case4_r6_guard asm("r6");
    register s32 case4_zero asm("r5");
    s32 case29_side_sum;
    s32 case29_list_offset;
    s32 case29_copy_list_offset;
    u8 *case29_copy_dest;
    s32 case33_list_offset;
    s32 case33_first_list_offset;
    s32 temp_r0_40;
    register s32 temp_r0_53 asm("r0");
    s32 temp_r0_55;
    s32 temp_r0_57;
    s32 temp_r0_62;
    register s32 temp_r0_64 asm("r0");
    s32 temp_r0_73;
    s32 temp_r0_79;
    s32 temp_r1_10;
    register s32 temp_r1_11 asm("r1");
    s32 temp_r1_13;
    s32 temp_r1_16;
    register s32 temp_r1_17 asm("r1");
    register s32 temp_r1_18 asm("r1");
    s32 temp_r1_3;
    s32 temp_r1_5;
    s32 temp_r1_8;
    register s32 temp_r2_10 asm("r2");
    register s32 temp_r2_11 asm("r2");
    register s32 temp_r2_12 asm("r2");
    register s32 temp_r2_13 asm("r2");
    register s32 temp_r2_6 asm("r2");
    register s32 temp_r2_7 asm("r2");
    register s32 temp_r2_8 asm("r2");
    register s32 temp_r2_9 asm("r2");
    register s32 temp_r3_2 asm("r3");
    register s32 temp_r3_3 asm("r3");
    register s32 temp_r4_21 asm("r4");
    register s32 temp_r4_22 asm("r4");
    register s32 temp_r4_2 asm("r4");
    register s32 temp_r4_5 asm("r4");
    register s32 temp_r4_6 asm("r4");
    register s32 case29_second_index4 asm("r5");
    register s32 temp_r4_8 asm("r4");
    register s32 temp_r4_9 asm("r4");
    register s32 temp_r6_5 asm("r6");
    s32 temp_ret;
    register s32 var_r0 asm("r0");
    register s32 *final_state asm("r1");
    register s32 var_r0_3 asm("r0");
    register s32 case3031_neg asm("r2");
    register s32 case3031_zero asm("r3");
    register u8 *var_r3 asm("r3");
    register s32 var_r3_2 asm("r3");
    register u32 case41_copy asm("r6");
    s32 var_r7_13;
    register s32 var_r8 asm("r8");
    register s32 var_r8_10 asm("r8");
    register s32 var_r8_14 asm("r8");
    register s32 var_r8_15 asm("r8");
    register s32 var_r8_16 asm("r8");
    register s32 var_r8_17 asm("r8");
    register s32 var_r8_18 asm("r8");
    register s32 var_r8_19 asm("r8");
    register s32 var_r8_29 asm("r8");
    register s32 var_r8_32 asm("r8");
    s32 temp_r0_10;
    register u16 temp_r0_11 asm("r0");
    register s32 temp_r0_3 asm("r0");
    u16 temp_r0_7;
    register u16 temp_r9 asm("r9");
    register u16 temp_r9_2 asm("r9");
    register u16 temp_r9_4 asm("r9");
    register u16 temp_r9_5 asm("r9");
    register u16 temp_r9_6 asm("r9");
    register u16 temp_r9_7 asm("r9");
    register u16 temp_r9_8 asm("r9");
    register u16 temp_r9_9 asm("r9");
    register u16 var_r9 asm("r9");
    register u16 var_r9_2 asm("r9");
    register u16 var_r9_3 asm("r9");
    register u32 var_r9_4 asm("r9");
    register u8 *case29_players asm("r9");
    register u8 *case29_slots asm("r6");
    register u8 *case33_slots asm("r9");
    register u8 *case33_lists asm("r8");
    register s32 *case33_first_dest asm("r2");
    u32 temp_r1;
    register u8 *var_r0_4 asm("r0");
    u8 *var_r0_5;
    register u8 *var_r1_3 asm("r1");
    u8 temp_r0;
    u8 temp_r0_12;
    u8 temp_r0_13;
    u8 temp_r0_14;
    u8 temp_r0_15;
    u8 temp_r0_16;
    u8 temp_r0_17;
    u8 temp_r0_18;
    u8 temp_r0_19;
    u8 temp_r0_20;
    u8 temp_r0_21;
    u8 temp_r0_22;
    u8 temp_r0_23;
    u8 temp_r0_24;
    u8 temp_r0_25;
    u8 temp_r0_26;
    u8 temp_r0_27;
    u8 temp_r0_28;
    u8 temp_r0_29;
    u8 temp_r0_33;
    register u32 temp_r0_34 asm("r9");
    u8 temp_r0_35;
    u8 temp_r0_36;
    u8 temp_r0_37;
    u8 temp_r0_38;
    u8 temp_r0_39;
    register u32 temp_r0_41 asm("r9");
    u8 temp_r0_42;
    u8 temp_r0_43;
    u8 temp_r0_44;
    u8 temp_r0_45;
    u8 temp_r0_46;
    u8 temp_r0_47;
    u8 temp_r0_48;
    u8 temp_r0_49;
    u8 temp_r0_50;
    u8 temp_r0_51;
    u8 temp_r0_52;
    u8 temp_r0_54;
    u8 temp_r0_5;
    u8 temp_r0_61;
    u8 temp_r0_68;
    u8 temp_r0_6;
    u8 temp_r0_75;
    u8 temp_r0_76;
    u8 temp_r0_77;
    u8 temp_r0_78;
    u8 temp_r0_80;
    u8 temp_r0_8;
    register u32 temp_r4_10 asm("r4");
    register u32 temp_r4_23 asm("r4");
    register u32 temp_r5_2 asm("r5");
    u32 temp_r6_2;
    u8 temp_r6_3;
    u8 temp_r6_4;
    u8 temp_r6_6;
    u8 temp_r6_7;
    u32 temp_r6_8;
    u8 temp_r7;
    u8 var_r1;
    u8 var_r1_2;
    register s32 var_r4 asm("r4");
    u8 var_r6_2;
    u8 var_r6_3;
    register u32 var_r7 asm("r7");
    u8 var_r7_11;
    u8 var_r7_12;
    u8 var_r7_14;
    u8 var_r7_15;
    register u32 var_r7_16 asm("r7");
    u8 var_r7_17;
    u8 var_r7_18;
    u8 var_r7_19;
    u32 var_r7_20;
    register u32 var_r7_21 asm("r7");
    u8 var_r7_2;
    u8 var_r7_3;
    u8 var_r7_4;
    u8 var_r7_5;
    u8 var_r7_6;
    u8 var_r7_7;
    u8 var_r7_8;
    u8 var_r7_9;
    register u32 var_r8_11 asm("r8");
    register u32 var_r8_12 asm("r8");
    register u32 var_r8_13 asm("r8");
    register u32 var_r8_20 asm("r8");
    register u32 var_r8_21 asm("r8");
    register u32 var_r8_23 asm("r8");
    register u32 var_r8_24 asm("r8");
    register u32 var_r8_25 asm("r8");
    register u32 var_r8_26 asm("r8");
    register u32 var_r8_27 asm("r8");
    register u32 var_r8_28 asm("r8");
    register u32 var_r8_2 asm("r8");
    register u32 var_r8_30 asm("r8");
    register u32 var_r8_31 asm("r8");
    register u32 var_r8_33 asm("r8");
    register u32 var_r8_34 asm("r8");
    register u32 var_r8_35 asm("r8");
    register u32 var_r8_36 asm("r8");
    register u32 var_r8_37 asm("r8");
    register u32 var_r8_38 asm("r8");
    register s32 var_r8_39 asm("r8");
    register u32 var_r8_3 asm("r8");
    register s32 var_r8_40 asm("r8");
    register u32 var_r8_41 asm("r8");
    register u32 var_r8_4 asm("r8");
    register u32 var_r8_5 asm("r8");
    register u32 var_r8_6 asm("r8");
    register u32 var_r8_7 asm("r8");
    register u32 var_r8_8 asm("r8");
    register u32 var_r8_9 asm("r8");
    register s32 var_sl asm("sl");
    register u32 var_sl_2 asm("sl");
    register u32 var_sl_3 asm("sl");
    register void *temp_r0_30 asm("r0");
    void *temp_r0_32;
    void *temp_r0_56;
    void *temp_r0_58;
    void *temp_r0_59;
    void *temp_r0_60;
    void *temp_r0_63;
    void *temp_r0_65;
    void *temp_r0_66;
    void *temp_r0_67;
    void *temp_r0_69;
    void *temp_r0_70;
    void *temp_r0_71;
    void *temp_r0_72;
    void *temp_r0_74;
    void *temp_r0_9;
    void *temp_r1_12;
    void *temp_r1_14;
    register void *temp_r1_15 asm("r1");
    void *temp_r1_19;
    void *temp_r1_20;
    void *temp_r1_21;
    void *temp_r1_22;
    register void *temp_r1_23 asm("r1");
    void *temp_r1_4;
    s32 temp_r1_6;
    register s32 temp_r1_7 asm("r1");
    register void *temp_r1_9 asm("r1");
    register void *temp_r2 asm("r2");
    register void *temp_r2_2 asm("r2");
    register void *temp_r2_3 asm("r2");
    register void *temp_r2_4 asm("r2");
    register void *temp_r2_5 asm("r2");
    register void *temp_r3 asm("r3");
    register void *temp_r4 asm("r4");
    register void *temp_r4_11 asm("r4");
    register void *temp_r4_12 asm("r4");
    register void *temp_r4_13 asm("r4");
    register void *temp_r4_14 asm("r4");
    register void *temp_r4_15 asm("r4");
    register void *temp_r4_16 asm("r4");
    register void *temp_r4_17 asm("r4");
    register void *temp_r4_18 asm("r4");
    register void *temp_r4_19 asm("r4");
    register void *temp_r4_20 asm("r4");
    register void *temp_r4_24 asm("r4");
    register void *temp_r4_3 asm("r4");
    register void *temp_r4_4 asm("r4");
    register void *temp_r4_7 asm("r4");
    register void *temp_r5 asm("r5");
    register void *temp_r5_10 asm("r5");
    register void *temp_r5_3 asm("r5");
    register void *temp_r5_4 asm("r5");
    register void *temp_r5_5 asm("r5");
    register void *temp_r5_6 asm("r5");
    register void *temp_r5_7 asm("r5");
    register void *temp_r5_8 asm("r5");
    register void *temp_r5_9 asm("r5");
    register u8 *case29_lists asm("r5");
    register s32 *case29_first_dest asm("r2");
    register u8 *case29_wait_records asm("r5");
    register u8 *case29_wait_flags asm("r4");
    register s32 **case29_wait_record0 asm("r6");
    u8 *var_r7_10;
    register u8 *var_r8_22 asm("r8");
    volatile u8 frame_padding[36];

    asm volatile("" : "=m"(frame_home34), "=m"(frame_home38),
                  "=m"(frame_home3C), "=m"(frame_home40),
                  "=m"(frame_home44), "=m"(frame_home48),
                  "=m"(frame_home4C), "=m"(frame_home50),
                  "=m"(frame_home54), "=m"(frame_home58));
    sp18 = (s32) arg0;
    var_r8 = 0;
    {
        register s32 opening_sp6c asm("r1") = sp18;
        opening_sp6c *= 4;
        sp6C = opening_sp6c;
    }
    {
    register volatile s32 *opening_stack asm("sp");
    register u32 opening_successor asm("r2");
    register u32 opening_outer asm("r3");
    register u32 opening_triple asm("r0");
    register u32 opening_row asm("r4");
    register u32 opening_slots asm("r5") = 0x02032EBC;
    register u32 opening_slot_address asm("r0");
loop_1:
    var_r7_13 = 0;
    opening_successor = var_r8;
    opening_successor += 1;
    opening_stack[24] = opening_successor;
    opening_outer = var_r8;
    asm volatile("" : "+r"(opening_outer));
    opening_triple = opening_outer * 2;
    opening_triple += var_r8;
    opening_row = opening_triple * 8;
loop_2:
    if ((func_080E9D88(var_r8, var_r7_13) << 0x18) == 0) {
        goto block_4;
    }
    opening_slot_address = var_r7_13 * 4;
    opening_slot_address += opening_row;
    opening_slot_address += opening_slots;
    *(s32 *)(*(u32 *)opening_slot_address + 0x2C) = 0x20000;
block_4:
    {
        register u32 opening_next asm("r0");
        opening_next = var_r7_13 + 1;
        opening_next <<= 24;
        var_r7_13 = opening_next >> 24;
    }
    if ((u32)var_r7_13 <= 5U) {
        goto loop_2;
    }
    {
        register u32 opening_outer_reload asm("r4") = opening_stack[24];
        register u32 opening_outer_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(opening_outer_normalized)
            : "r"(opening_outer_reload));
        var_r8 = opening_outer_normalized;
        if (opening_outer_normalized <= 1U) {
            goto loop_1;
        }
    }
    }
    func_080BB224(2, sp18, 0, 0);
    goto loop_9;
block_8:
    func_080ED17C(1);
loop_9:
    if ((func_080BB654() << 0x18) == 0) {
        goto block_8;
    }
    {
        register u32 opening_exit_base asm("r0") = 0x02034B4C;
        register s32 opening_exit_state asm("r5");
        register u8 *opening_exit_address asm("r1");
        register u32 opening_exit_offset asm("r2");

        asm volatile("" : "+r"(opening_exit_base));
        opening_exit_state = sp6C;
        opening_exit_address =
            (u8 *)(opening_exit_state + opening_exit_base);
        opening_exit_offset = 0xA07D;
        opening_exit_address += opening_exit_offset;
        {
            register u32 opening_exit_value asm("r1") =
                *opening_exit_address;
            opening_exit_value -= 1;
            asm volatile("" : "+r"(opening_exit_value));
            temp_r1 = opening_exit_value;
        }
    }
    if (temp_r1 > 0x32U) {
        goto block_373;
    }
    switch (temp_r1) {                              /* jump table: jtbl_080C3674 */
case 0:
    {
        register s32 case0_state_seed asm("r3") = 0;
        asm volatile("" : "+r"(case0_state_seed));
        var_r8_2 = case0_state_seed;
    }
loop_13:
    if ((func_080E9D88(sp18, var_r8_2) << 0x18) == 0) {
        goto block_17;
    }
    {
        register s32 case0_row_base asm("r4") = sp6C;
        register s32 case0_side asm("r5") = sp18;
        asm volatile("" : "+r"(case0_row_base), "+r"(case0_side));
        temp_r2 =
            (void *)((((case0_row_base + case0_side) * 8)
                      - case0_side) << 7);
    }
    asm volatile(
        "mov r7, r8\n\t"
        "lsl %0, r7, #2\n\t"
        "add %0, r8\n\t"
        "lsl %0, %0, #3\n\t"
        "sub %0, %0, r7\n\t"
        "lsl %0, %0, #4"
        : "=l"(case0_offset)
        :
        : "cc");
    {
        register u32 case0_record_base asm("r1") = 0x02034B4C;
        asm volatile("" : "+r"(case0_record_base));
        case0_offset += case0_record_base;
    }
    temp_r2 += case0_offset;
    {
        register s32 case0_sum asm("r0");
        asm volatile(
            "mov r1, #58\n\t"
            "ldrsh %0, [%1, r1]\n\t"
            "lsr r1, %0, #31\n\t"
            "add %0, %0, r1\n\t"
            "asr %0, %0, #1\n\t"
            "ldrh r3, [%1, #6]\n\t"
            "add %0, %0, r3"
            : "=r"(case0_sum)
            : "l"(temp_r2)
            : "cc");
        temp_r0_3 = case0_sum;
    }
    case0_zero = 0;
    M2C_FIELD(temp_r2, u16 *, 6) = temp_r0_3;
    temp_r0_3 = (s16) temp_r0_3;
    case0_max = M2C_FIELD(temp_r2, u16 *, 0x3A);
    if (temp_r0_3 <= (s32) M2C_FIELD(temp_r2, s16 *, 0x3A)) {
        goto block_16;
    }
    M2C_FIELD(temp_r2, u16 *, 6) = case0_max;
block_16:
    {
        register volatile s32 *case0_outgoing asm("sp");
        case0_outgoing[0] = case0_zero;
        case0_outgoing[1] = case0_zero;
        case0_outgoing[2] = 1;
        {
            register s32 case0_half_value asm("r0");
            register s32 case0_field_offset asm("r7");
            asm volatile(
                "movs %1, #58\n\t"
                "ldrsh %0, [%2, %1]"
                : "=r"(case0_half_value), "=r"(case0_field_offset)
                : "r"(temp_r2)
                : "memory");
            case0_outgoing[3] =
                (s32)(case0_half_value +
                      ((u32)case0_half_value >> 0x1F)) >> 1;
        }
        case0_outgoing[4] = case0_zero;
        case0_outgoing[5] = case0_zero;
    }
    {
        register s32 case0_arg0 asm("r0") = sp18;
        register s32 case0_arg1 asm("r1") = var_r8_2;
        register s32 case0_arg2 asm("r2") = -1;
        register s32 case0_arg3 asm("r3") = 0;
        asm volatile("" : "+r"(case0_arg0), "+r"(case0_arg1),
                     "+r"(case0_arg2), "+r"(case0_arg3));
        func_080BE9D8(case0_arg0, case0_arg1, case0_arg2, case0_arg3);
    }
block_17:
    temp_r0_5 = var_r8_2 + 1;
    var_r8_2 = temp_r0_5;
    if ((u32) temp_r0_5 <= 5U) {
        goto loop_13;
    }
    return;
case 1: {
    register s32 case1_zero asm("r4");
    register s32 case1_base asm("r3");
    register s32 case1_unit asm("r5");
    {
        register s32 case1_initial_zero asm("r0") = 0;
        var_r8_3 = case1_initial_zero;
    }
    case1_zero = 0;
loop_21:
    if ((func_080E9D88(sp18, var_r8_3) << 0x18) == 0) {
        goto block_23;
    }
    func_080C02B4_word(sp18, var_r8_3);
    {
        register volatile s32 *case1_outgoing asm("sp");
        case1_outgoing[0] = case1_zero;
        case1_outgoing[1] = case1_zero;
        case1_outgoing[2] = 0x1A;
        case1_outgoing[3] = case1_zero;
        case1_outgoing[4] = 1;
        case1_outgoing[5] = case1_zero;
        {
            register s32 case1_arg0 asm("r0") = sp18;
            register s32 case1_arg1 asm("r1") = var_r8_3;
            register s32 case1_arg2 asm("r2") = -1;
            register s32 case1_arg3 asm("r3") = 0;
            func_080BE65C(case1_arg0, case1_arg1,
                          case1_arg2, case1_arg3);
        }
    }
block_23:
    temp_r0_6 = var_r8_3 + 1;
    var_r8_3 = temp_r0_6;
    if ((u32) temp_r0_6 <= 5U) {
        goto loop_21;
    }
    {
        register s32 case1_row_base asm("r1") = sp6C;
        register s32 case1_row_side asm("r3") = sp18;
        register s32 case1_row asm("r2");
        asm volatile("" : "+r"(case1_row_base),
                     "+r"(case1_row_side));
        asm volatile("add %0, %1, %2"
                     : "=r"(case1_row)
                     : "r"(case1_row_base), "r"(case1_row_side)
                     : "cc");
        case1_row *= 8;
        case1_row -= case1_row_side;
        temp_r2_2 = case1_row << 7;
    }
    case1_base = 0x02034B4C;
    {
        register u32 case1_scale asm("r0") = 0x94;
        case1_zero = sp18;
        case1_unit = case1_zero;
        case1_unit *= case1_scale;
    }
    case1_unit += case1_base;
    {
        register u32 case1_field asm("r7") = 0xA084;
        case1_unit += case1_field;
    }
    {
        register s32 case1_effect asm("r3");
        register u32 case1_current asm("r0");
        register volatile s32 *case12_outgoing asm("sp");

        temp_r2_2 += (M2C_FIELD(case1_unit, u8 *, 0) * 0x270) + case1_base;
        case1_effect = M2C_FIELD(temp_r2_2, u16 *, 0x3E);
        case1_current = M2C_FIELD(temp_r2_2, u16 *, 8);
        asm volatile("" : "+r"(case1_effect), "+r"(case1_current));
        case1_effect -= case1_current;
        case1_effect = (s16)case1_effect;
        asm volatile("add %0, %1, %0"
                     : "+r"(case1_current)
                     : "r"(case1_effect)
                     : "cc");
        case1_zero = 0;
        M2C_FIELD(temp_r2_2, u16 *, 8) = (u16)case1_current;
        var_r1 = M2C_FIELD(case1_unit, u8 *, 0);
        case12_arg1 = var_r1;
        case12_neg = -1;
        case12_outgoing[0] = case1_zero;
        case12_outgoing[1] = case1_zero;
        case12_outgoing[2] = 4;
        case12_outgoing[3] = case1_effect;
        case12_outgoing[4] = case1_zero;
        case12_outgoing[5] = case1_zero;
    }
    goto block_33;
}
case 2: {
    u8 *case2_base;
    register u32 case2_cap asm("r4");
    register u8 *case2_unit asm("r6");
    register s32 case2_field asm("r7");
    s32 case2_post_base;
    register s32 case2_row asm("r5");
    register s32 case2_post_side asm("r5");
    register s32 case2_zero asm("r3");
    {
        register s32 case2_initial_scale asm("r0") = 0x94;
        register s32 case2_initial_player asm("r1");
        register s32 case2_initial_base asm("r2");
        register s32 case2_initial_field asm("r3");

        case2_initial_player = sp18;
        var_r4 = case2_initial_player;
        var_r4 *= case2_initial_scale;
        case2_initial_base = 0x02034B4C;
        asm volatile("" : "+r"(case2_initial_base));
        var_r4 += case2_initial_base;
        case2_initial_field = 0xA084;
        asm volatile("" : "+r"(case2_initial_field));
        var_r4 += case2_initial_field;
    }
    func_080C02B4(sp18, *(u8 *)var_r4);
    func_080BE65C(sp18, *(u8 *)var_r4, -1, 0,
                  0, 0, 0x1A, 0, 1, 0);
    var_r4 = 0;
    var_r8_4 = var_r4;
    case2_base = (u8 *)0x02034B4C;
    {
        register s32 case2_row_side asm("r7");
        register s32 case2_row_work asm("r0");
        case2_row = sp6C;
        case2_row_side = sp18;
        asm volatile("add %0, %1, %2"
                     : "=r"(case2_row_work)
                     : "r"(case2_row), "r"(case2_row_side)
                     : "cc");
        case2_row_work *= 8;
        case2_row_work -= case2_row_side;
        case2_row = case2_row_work << 7;
    }
loop_27:
    if ((func_080E9D88(sp18, var_r8_4) << 0x18) == 0) {
        goto block_29;
    }
    {
        register u32 case2_delta asm("r0");
        register s32 case2_accumulator asm("r1");
        asm volatile(
            "mov r1, r8\n\t"
            "lsl %0, r1, #2\n\t"
            "add %0, r8\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, r1\n\t"
            "lsl %0, %0, #4"
            : "=r"(case2_delta)
            :
            : "cc");
        case2_delta += case2_row;
        case2_delta -= 0U - (u32)case2_base;
        case2_delta += 0x40;
        case2_accumulator = (s16)var_r4;
        case2_delta = *(u16 *)case2_delta;
        case2_accumulator += case2_delta;
        var_r4 = (u16)case2_accumulator;
    }
block_29:
    temp_r0_8 = var_r8_4 + 1;
    var_r8_4 = temp_r0_8;
    if ((u32) temp_r0_8 <= 5U) {
        goto loop_27;
    }
    {
        register s32 case2_row_base asm("r3") = sp6C;
        register s32 case2_post_row asm("r2");
        case2_post_side = sp18;
        asm volatile("" : "+r"(case2_row_base),
                     "+r"(case2_post_side));
        asm volatile("add %0, %1, %2"
                     : "=r"(case2_post_row)
                     : "r"(case2_row_base), "r"(case2_post_side)
                     : "cc");
        case2_post_row *= 8;
        case2_post_row -= case2_post_side;
        temp_r2_3 = case2_post_row << 7;
    }
    case2_post_base = 0x02034B4C;
    {
        register s32 case2_unit_base asm("r0") =
            (0x94 * case2_post_side) + case2_post_base;
        case2_field = 0xA084;
        asm volatile("add %0, %1, %2"
                     : "=r"(case2_unit)
                     : "r"(case2_unit_base), "r"(case2_field)
                     : "cc");
    }
    temp_r2_3 += (*case2_unit * 0x270) + case2_post_base;
    temp_r0_10 = M2C_FIELD(temp_r2_3, u16 *, 8);
    {
        register s32 case2_effect_shift asm("r1") = var_r4 << 16;
        asm volatile("" : "+r"(case2_effect_shift));
        case12_effect = case2_effect_shift >> 16;
    }
    asm volatile("add %0, %1, %0"
                 : "+r"(temp_r0_10)
                 : "r"(case12_effect)
                 : "cc");
    case2_zero = 0;
    M2C_FIELD(temp_r2_3, u16 *, 8) = temp_r0_10;
    {
        register s32 case2_current_signed asm("r0") = (s16)temp_r0_10;
        register u8 *case2_compare_base asm("r2") = (u8 *)temp_r2_3;
        register s32 case2_signed_cap asm("r1");

        case2_cap = M2C_FIELD(temp_r2_3, u16 *, 0x3E);
        asm volatile("" : "+r"(case2_cap)
                     : "r"(case2_current_signed));
        asm volatile(
            ".syntax unified\n\t"
            "movs %1, #62\n\t"
            "ldrsh %0, [%2, %1]\n\t"
            ".syntax divided"
            : "=l"(case2_signed_cap), "=l"(case2_field)
            : "l"(case2_compare_base));
        if (case2_current_signed <= case2_signed_cap) {
            goto block_32;
        }
    }
    M2C_FIELD(temp_r2_3, u16 *, 8) = (u16)case2_cap;
block_32:
    var_r1 = *case2_unit;
    case12_arg1 = var_r1;
    case12_neg = -1;
    {
        register volatile s32 *case12_outgoing asm("sp");
        case12_outgoing[0] = case2_zero;
        case12_outgoing[1] = case2_zero;
        case12_outgoing[2] = 4;
        case12_outgoing[3] = case12_effect;
        case12_outgoing[4] = case2_zero;
        case12_outgoing[5] = case2_zero;
    }
block_33:
    func_080BE9D8(sp18, case12_arg1, case12_neg, 0);
    return;
}
case 3: {
    void *case3_base2;
    register s32 case3_offset asm("r0");
    s32 case3_row1;
    s32 case3_row2;
    register s32 case3_zero asm("r4");
    {
        register s32 case3_initial_zero asm("r0") = 0;
        asm volatile("" : "+r"(case3_initial_zero));
        var_r8_5 = case3_initial_zero;
    }
    {
        register s32 case3_row1_base asm("r1") = sp6C;
        register s32 case3_row1_side asm("r2") = sp18;
        register s32 case3_row1_work asm("r0");
        asm volatile("" : "+r"(case3_row1_base), "+r"(case3_row1_side));
        asm volatile("add %0, %1, %2"
                     : "=r"(case3_row1_work)
                     : "r"(case3_row1_base), "r"(case3_row1_side)
                     : "cc");
        case3_row1_work *= 8;
        case3_row1_work -= case3_row1_side;
        case3_row1 = case3_row1_work << 7;
    }
    case3_zero = 0;
loop_36:
    if ((func_080E9D88(sp18, var_r8_5) << 0x18) == 0) {
        goto block_38;
    }
    {
        register s32 case3_index_view asm("r3");
        register void *case3_record_base asm("r1");

        asm volatile(
            "mov %1, r8\n\t"
            "lsl %0, %1, #2\n\t"
            "add %0, r8\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4"
            : "=r"(case3_offset), "=r"(case3_index_view)
            : "r"(var_r8_5)
            : "cc");
        case3_record_base = (void *)0x02034B4C;
        asm volatile(
            "add %0, %0, %2\n\t"
            "add %1, %3, %0"
            : "+r"(case3_offset), "=r"(temp_r2_4)
            : "r"(case3_record_base), "r"(case3_row1)
            : "cc");
    }
    temp_r1_2 = M2C_FIELD(temp_r2_4, u16 *, 0x3A);
    temp_r0_11 = M2C_FIELD(temp_r2_4, u16 *, 6);
    temp_r1_2 = (s16)(temp_r1_2 - temp_r0_11);
    M2C_FIELD(temp_r2_4, u16 *, 6) = (u16) (temp_r1_2 + temp_r0_11);
    {
        register volatile s32 *case3_outgoing asm("sp");
        case3_outgoing[0] = case3_zero;
        case3_outgoing[1] = case3_zero;
        case3_outgoing[2] = 1;
        case3_outgoing[3] = (s32) temp_r1_2;
        case3_outgoing[4] = case3_zero;
        case3_outgoing[5] = case3_zero;
        {
            register s32 case3_arg0 asm("r0") = sp18;
            register s32 case3_arg1 asm("r1") = var_r8_5;
            register s32 case3_arg2 asm("r2") = -1;
            register s32 case3_arg3 asm("r3") = 0;
            asm volatile("" : "+r"(case3_arg0), "+r"(case3_arg1),
                         "+r"(case3_arg2), "+r"(case3_arg3));
            func_080BE9D8(case3_arg0, case3_arg1, case3_arg2, case3_arg3);
        }
    }
block_38:
    temp_r0_12 = var_r8_5 + 1;
    var_r8_5 = temp_r0_12;
    if ((u32) temp_r0_12 <= 5U) {
        goto loop_36;
    }
    {
        register s32 case3_second_state_seed asm("r4") = 0;
        asm volatile("" : "+r"(case3_second_state_seed));
        var_r8_6 = case3_second_state_seed;
    }
    case3_base2 = (void *)0x02034B4C;
    {
        register s32 case3_row2_base asm("r7") = sp6C;
        register s32 case3_row2_side asm("r1") = sp18;
        asm volatile("" : "+r"(case3_row2_base), "+r"(case3_row2_side));
        case3_row2 =
            (((case3_row2_base + case3_row2_side) * 8)
             - case3_row2_side) << 7;
    }
loop_40:
    if ((func_080E9D88(sp18, var_r8_6) << 0x18) == 0) {
        goto block_42;
    }
    {
        register void *case3_second_record asm("r0");
        register u32 case3_second_index_view asm("r2");
        asm volatile(
            "mov %1, r8\n\t"
            "lsl %0, %1, #2\n\t"
            "add %0, r8\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "add %0, %0, r4\n\t"
            "add %0, %0, r5"
            : "=r"(case3_second_record),
              "=r"(case3_second_index_view)
            : "r"(var_r8_6), "r"(case3_row2),
              "r"(case3_base2)
            : "cc");
        if (M2C_FIELD(case3_second_record, u8 *, 0x70) == 1) {
            goto block_43;
        }
    }
block_42:
    temp_r0_13 = var_r8_6 + 1;
    var_r8_6 = temp_r0_13;
    if ((u32) temp_r0_13 <= 5U) {
        goto loop_40;
    }
block_43:
    func_080C02B4_word(sp18, var_r8_6);
    {
        register s32 case3_final_neg asm("r2") = -1;
        register s32 case3_final_zero asm("r1");

        case3_final_zero = 0;
        func_080BE65C(sp18, var_r8_6, case3_final_neg, 0,
                      case3_final_zero, case3_final_zero, 0x1A,
                      case3_final_zero, 1, case3_final_zero);
    }
    return;
}
case 4:
    {
        register s32 case4_state_seed asm("r3") = 0;
        asm volatile("" : "+r"(case4_state_seed));
        var_r8_7 = case4_state_seed;
    }
    case4_scan_base = (u8 *)0x02034B4C;
    {
        register s32 case4_scan_row asm("r4");
        register u8 *case4_scan_record asm("r0");

        asm volatile(
            "ldr r4, [sp, #108]\n\t"
            "ldr r7, [sp, #24]\n\t"
            "add r0, r4, r7\n\t"
            "lsl r0, r0, #3\n\t"
            "sub r0, r0, r7\n\t"
            "lsl %0, r0, #7"
            : "=&r"(case4_scan_row)
            :
            : "cc");
loop_45:
    if ((func_080E9D88(sp18, var_r8_7) << 0x18) == 0) {
        goto block_47;
    }
    asm volatile(
        "mov r1, r8\n\t"
        "lsl %0, r1, #2\n\t"
        "add %0, r8\n\t"
        "lsl %0, %0, #3\n\t"
        "sub %0, %0, r1\n\t"
        "lsl %0, %0, #4\n\t"
        "add %0, %0, %1\n\t"
        "add %0, %0, %2"
        : "=&r"(case4_scan_record)
        : "r"(case4_scan_row), "r"(case4_scan_base)
        : "cc");
    if (M2C_FIELD(case4_scan_record, u8 *, 0x70) == 1) {
        goto block_48;
    }
block_47:
    temp_r0_14 = var_r8_7 + 1;
    var_r8_7 = temp_r0_14;
    if ((u32) temp_r0_14 <= 5U) {
        goto loop_45;
    }
block_48:
    }
    func_080C9F00(sp18, 1);
    {
        register s32 case4_store_base asm("r2") = 0x02034B4C;
        register s32 case4_store_index asm("r3") = var_r8_7;
        register u8 *case4_store_record asm("r1");
        register s32 case4_store_row_base asm("r4");
        register s32 case4_store_side asm("r5");
        register s32 case4_store_row asm("r0");
        asm volatile("" : "+r"(case4_store_base), "+r"(case4_store_index));
        case4_store_record = (u8 *)(case4_store_index * 4);
        asm volatile("add %0, r8"
                     : "+l"(case4_store_record));
        case4_store_record =
            (u8 *)((((u32)case4_store_record * 8) - case4_store_index) * 16);
        case4_store_row_base = sp6C;
        case4_store_side = sp18;
        asm volatile("" : "+r"(case4_store_row_base), "+r"(case4_store_side));
        case4_store_row = case4_store_row_base + case4_store_side;
        case4_store_row = (case4_store_row * 8) - case4_store_side;
        case4_store_row <<= 7;
        case4_store_record += case4_store_row;
        case4_store_record += case4_store_base;
        M2C_FIELD(case4_store_record, s16 *, 6) = 0;
    }
    func_080C04DC_word(sp18, var_r8_7);
    goto loop_51;
block_50:
    func_080ED17C(1);
loop_51:
    temp_ret = func_080CA140();
    if (temp_ret == 0) {
        goto block_50;
    }
    asm volatile("" : "=r"(case4_r6_guard));
    var_r7_2 = 0;
    case4_zero = 0;
    {
        asm volatile(
            "ldr r1, [sp, #108]\n\t"
            "ldr r2, [sp, #24]\n\t"
            "add r0, r1, r2\n\t"
            "lsl r0, r0, #3\n\t"
            "sub r0, r0, r2\n\t"
            "lsl r4, r0, #7"
            : "=r"(case4_row2)
            :
            : "r0", "r1", "r2", "cc", "memory");
    }
loop_53:
    if (var_r7_2 == var_r8_7) {
        goto block_57;
    }
    asm volatile(
        "lsl r0, %1, #2\n\t"
        "add r0, r0, %1\n\t"
        "lsl r0, r0, #3\n\t"
        "sub r0, r0, %1\n\t"
        "lsl r0, r0, #4"
        : "=r"(case4_record_offset)
        : "r"(var_r7_2)
        : "cc");
    {
        register u32 case4_record_base asm("r1") = 0x02034B4C;
        asm volatile(
            "add r0, r0, r1\n\t"
            "add r2, r4, r0"
            : "+r"(case4_record_offset), "=r"(temp_r2_5)
            : "r"(case4_record_base), "r"(case4_row2)
            : "cc");
    }
    if (M2C_FIELD(temp_r2_5, u8 *, 0) == 0) {
        goto block_57;
    }
    if (!(8 & M2C_FIELD(temp_r2_5, u16 *, 4))) {
        goto block_57;
    }
    func_080C052C(sp18, var_r7_2);
    func_080C00B0(sp18, var_r7_2);
    CALL_BE9D8_STAGED(sp18, var_r7_2, -1, 0,
                      case4_zero, case4_zero, 0x24,
                      case4_zero, case4_zero, case4_zero);
block_57:
    var_r7_2 += 1;
    if ((u32) var_r7_2 <= 5U) {
        goto loop_53;
    }
    asm volatile("" :: "r"(case4_r6_guard));
    {
        register s32 case4_inner_state_seed asm("r3") = 0;
        asm volatile("" : "+r"(case4_inner_state_seed));
        var_r8_8 = case4_inner_state_seed;
    }
    {
        s32 case4_one = 1;
        temp_r4_2 = sp18;
        temp_r4_2 ^= case4_one;
    }
    {
        u32 case4_data_base = 0x02034B4C;
        u32 case4_ptr_base = 0x02032E8C;
loop_59:
        if ((func_080E9D88(temp_r4_2, var_r8_8) << 0x18) == 0) {
            goto block_61;
        }
        {
            register u32 case4_index asm("r7") = var_r8_8;
            register u32 case4_index4 asm("r3");
            register u32 case4_arg0 asm("r0");
            register u32 case4_arg1 asm("r1");

            asm volatile("lsl %0, %1, #2"
                         : "=r"(case4_index4)
                         : "r"(case4_index));
            temp_r1_4 = (((case4_index4 + case4_index) * 8) - case4_index) * 16;
            temp_r1_4 += temp_r4_2 * 0x1380;
            case4_arg0 = M2C_FIELD(temp_r1_4, u8 *, case4_data_base);
            case4_arg1 = M2C_FIELD((temp_r1_4 + case4_data_base), u8 *, 1);
            asm volatile("" : : "r"(case4_arg0), "r"(case4_arg1));
            {
                register u32 case4_player24 asm("r2") = temp_r4_2 * 0x18;
                case4_index4 += case4_player24;
                case4_index4 += case4_ptr_base;
                temp_r3 = *(void **)case4_index4;
            }
            func_0809A4CC(case4_arg0, case4_arg1, M2C_FIELD(temp_r3, u16 *, 0xE), M2C_FIELD(temp_r3, u8 *, 0x10));
        }
block_61:
        temp_r0_15 = var_r8_8 + 1;
        var_r8_8 = temp_r0_15;
        if ((u32) temp_r0_15 <= 5U) {
            goto loop_59;
        }
        return;
    }
case 5: {
    s32 case5_neg;
    s32 case5_zero;
    s32 case5_one;
    {
        register s32 case5_state_seed asm("r0") = 0;
        asm volatile("" : "+r"(case5_state_seed));
        var_r8_9 = case5_state_seed;
    }
    case5_neg = -1;
    case5_zero = 0;
    case5_one = 1;
    asm volatile("" : "+r"(case5_neg), "+r"(case5_zero), "+r"(case5_one));
loop_64:
    if ((func_080E9D88(sp18, var_r8_9) << 0x18) == 0) {
        goto block_66;
    }
    func_080BE65C(sp18, var_r8_9, case5_neg, 0,
                  case5_zero, case5_zero, 0x12,
                  case5_zero, case5_one, case5_zero);
    func_080BE65C(sp18, var_r8_9, case5_neg, 0,
                  case5_zero, case5_zero, 0x13,
                  case5_zero, case5_one, case5_zero);
    func_080E8B08_word(sp18, var_r8_9);
block_66:
    temp_r0_16 = var_r8_9 + 1;
    var_r8_9 = temp_r0_16;
    if ((u32) temp_r0_16 <= 5U) {
        goto loop_64;
    }
    return;
}
case 6: {
    register volatile s32 *case6_stack asm("sp");
    s32 case6_zero;
    {
        register s32 case6_state_seed asm("r1") = 0;
        asm volatile("" : "+r"(case6_state_seed));
        var_r8_10 = case6_state_seed;
    }
    case6_zero = 0;
    asm volatile("" : "+r"(case6_zero));
loop_69:
    {
        register s32 case6_guard_r5 asm("r5");
        register s32 case6_guard_r6 asm("r6");
        asm volatile("" : "=r"(case6_guard_r5), "=r"(case6_guard_r6));
        var_r7_3 = 0;
        asm volatile("" :: "r"(case6_guard_r5), "r"(case6_guard_r6));
    }
    {
        register u32 case6_successor asm("r2") = var_r8_10;

        case6_successor += 1;
        case6_stack[24] = case6_successor;
    }
loop_70:
    if ((func_080E9D88(var_r8_10, var_r7_3) << 0x18) == 0) {
        goto block_72;
    }
    CALL_BE65C_STAGED(var_r8_10, var_r7_3, -1, 0,
                      case6_zero, case6_zero, 0x13,
                      case6_zero, 1, case6_zero);
    func_080E8B08(var_r8_10, var_r7_3);
block_72:
    var_r7_3 += 1;
    if ((u32) var_r7_3 <= 5U) {
        goto loop_70;
    }
    {
        register u32 case6_reload asm("r3") = case6_stack[24];
        register u32 case6_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case6_normalized)
            : "r"(case6_reload));
        var_r8_10 = case6_normalized;
        if (case6_normalized <= 1U) {
            goto loop_69;
        }
    }
    return;
}
case 7: {
    s32 case7_zero;
    s32 case7_second_zero;
    {
        register s32 case7_state_seed asm("r4") = 3;
        asm volatile("" : "+r"(case7_state_seed));
        var_r8_11 = case7_state_seed;
    }
    case7_zero = 0;
loop_76:
    if ((func_080E9D88(sp18, var_r8_11) << 0x18) == 0) {
        goto block_78;
    }
    func_080C02B4_word(sp18, var_r8_11);
    CALL_BE65C_STAGED(sp18, var_r8_11, -1, 0,
                      case7_zero, case7_zero, 0x1A,
                      case7_zero, 1, case7_zero);
block_78:
    temp_r0_18 = var_r8_11 + 1;
    var_r8_11 = temp_r0_18;
    if ((u32) temp_r0_18 <= 5U) {
        goto loop_76;
    }
    {
        register s32 case7_second_state_seed asm("r5") = 0;
        asm volatile("" : "+r"(case7_second_state_seed));
        var_r8_12 = case7_second_state_seed;
    }
    case7_second_zero = 0;
loop_80:
    if ((func_080E9D88(sp18, var_r8_12) << 0x18) == 0) {
        goto block_82;
    }
    CALL_BE65C_STAGED(sp18, var_r8_12, -1, 0,
                      case7_second_zero, case7_second_zero, 0x12,
                      case7_second_zero, 1, case7_second_zero);
block_82:
    temp_r0_19 = var_r8_12 + 1;
    var_r8_12 = temp_r0_19;
    if ((u32) temp_r0_19 <= 2U) {
        goto loop_80;
    }
    return;
}
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 48: {
    s32 case8_zero;
    {
        register u32 case8_base asm("r7") = 0x02034B4C;
        register u32 case8_carrier asm("r1") = 0x27BE;
        register u8 *case8_dest asm("r0");
        register s32 case8_dest_index asm("r2");
        register s32 case8_source_index asm("r3");
        register u32 case8_source_offset asm("r4");

        asm volatile("" : "+r"(case8_base), "+r"(case8_carrier));
        case8_dest = (u8 *)(case8_base + case8_carrier);
        case8_dest_index = sp18;
        case8_dest = (u8 *)(
            (u32)case8_dest_index - (0U - (u32)case8_dest));
        case8_source_index = sp6C;
        case8_carrier = case8_source_index + case8_base;
        case8_source_offset = 0xA07D;
        asm volatile("" : "+r"(case8_source_offset));
        case8_carrier += case8_source_offset;
        *case8_dest = *(u8 *)case8_carrier;
    }
    {
        register s32 case8_state_seed asm("r5") = 0;
        asm volatile("" : "+r"(case8_state_seed));
        var_r8_13 = case8_state_seed;
    }
    case8_zero = 0;
loop_85:
    CALL_BE9D8_STAGED(sp18, var_r8_13, -1, 0,
                      case8_zero, case8_zero, 0x24,
                      case8_zero, case8_zero, case8_zero);
    temp_r0_20 = var_r8_13 + 1;
    var_r8_13 = temp_r0_20;
    if ((u32) temp_r0_20 <= 5U) {
        goto loop_85;
    }
    return;
}
case 15:
case 16:
case 22: {
    register volatile s32 *case15_stack asm("sp");
    register s32 case15_next asm("r0");
    s32 case15_zero;
    {
        register u32 case15_base asm("r7") = 0x02034B4C;
        register u32 case15_carrier asm("r1") = 0x27BE;
        register u8 *case15_dest asm("r0");
        register s32 case15_dest_index asm("r2");
        register s32 case15_source_index asm("r3");
        register u32 case15_source_offset asm("r4");

        asm volatile("" : "+r"(case15_base), "+r"(case15_carrier));
        case15_dest = (u8 *)(case15_base + case15_carrier);
        case15_dest_index = sp18;
        case15_dest = (u8 *)(
            (u32)case15_dest_index - (0U - (u32)case15_dest));
        case15_source_index = sp6C;
        case15_carrier = case15_source_index + case15_base;
        case15_source_offset = 0xA07D;
        asm volatile("" : "+r"(case15_source_offset));
        case15_carrier += case15_source_offset;
        *case15_dest = *(u8 *)case15_carrier;
    }
    {
        register s32 case15_state_zero asm("r5") = 0;
        asm volatile("" : "+r"(case15_state_zero));
        var_r8_14 = case15_state_zero;
    }
    case15_zero = 0;
loop_89:
    {
        register s32 case15_guard_r5 asm("r5");
        register s32 case15_guard_r6 asm("r6");
        asm volatile("" : "=r"(case15_guard_r5), "=r"(case15_guard_r6));
        var_r7_4 = 0;
        asm volatile("" :: "r"(case15_guard_r5), "r"(case15_guard_r6));
    }
    case15_stack[24] = var_r8_14 + 1;
loop_90:
    CALL_BE9D8_STAGED(var_r8_14, var_r7_4, -1, 0,
                      case15_zero, case15_zero, 0x26,
                      case15_zero, case15_zero, case15_zero);
    var_r7_4 += 1;
    if ((u32) var_r7_4 <= 5U) {
        goto loop_90;
    }
    {
        register s32 case15_reload asm("r1");
        case15_reload = case15_stack[24];
        case15_next = (u8) case15_reload;
    }
    var_r8_14 = case15_next;
    if ((u32) case15_next <= 1U) {
        goto loop_89;
    }
    return;
}
case 17: {
    register volatile s32 *case17_stack asm("sp");
    register u8 *case17_base asm("r6");
    register s32 case17_row asm("r5");
    s32 case17_zero;
    {
        register s32 case17_state_seed asm("r2") = 0;
        asm volatile("" : "+r"(case17_state_seed));
        var_r8_15 = case17_state_seed;
    }
    case17_base = (u8 *)0x02034B4C;
    case17_zero = 0;
    asm volatile("" : "+r"(case17_zero));
loop_95:
    var_r7_5 = 0;
    {
        register s32 case17_next asm("r3") = var_r8_15;
        case17_next += 1;
        case17_stack[24] = case17_next;
    }
    asm volatile(
        "mov %0, %1\n\t"
        "lsl r0, %0, #2\n\t"
        "add r0, r8\n\t"
        "lsl r0, r0, #3\n\t"
        "sub r0, r0, %0\n\t"
        "lsl %0, r0, #7"
        : "=&r"(case17_row)
        : "r"(var_r8_15)
        : "r0", "cc");
loop_96:
    if ((func_080E9D88(var_r8_15, var_r7_5) << 0x18) == 0) {
        goto block_99;
    }
    {
        register u8 *case17_record asm("r0");

        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "add %0, %0, %2\n\t"
            "add %0, %0, %3"
            : "=&r"(case17_record)
            : "r"(var_r7_5), "r"(case17_row), "r"(case17_base)
            : "cc");
        if (!(0x40 & M2C_FIELD(case17_record, u8 *, 0x36))) {
            goto block_99;
        }
    }
    func_080C02B4(var_r8_15, var_r7_5);
    CALL_BE65C_STAGED(var_r8_15, var_r7_5, -1, 0,
                      case17_zero, case17_zero, 0x1A,
                      case17_zero, 1, case17_zero);
block_99:
    var_r7_5 += 1;
    if ((u32) var_r7_5 <= 5U) {
        goto loop_96;
    }
    {
        register u32 case17_reload asm("r7") = case17_stack[24];
        register u32 case17_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case17_normalized)
            : "r"(case17_reload));
        var_r8_15 = case17_normalized;
        if (case17_normalized <= 1U) {
            goto loop_95;
        }
    }
    return;
}
case 18: {
    register volatile s32 *case18_stack asm("sp");
    register s32 case18_outer_next asm("r0");
    register u8 *case18_base asm("r6");
    register s32 case18_row asm("r5");
    s32 case18_zero;
    {
        register s32 case18_outer_zero asm("r0") = 0;
        asm volatile("" : "+r"(case18_outer_zero));
        var_r8_16 = case18_outer_zero;
    }
    case18_base = (u8 *)0x02034B4C;
    case18_zero = 0;
    asm volatile("" : "+r"(case18_zero));
loop_103:
    var_r7_6 = 0;
    asm volatile(
        "mov r1, r8\n\t"
        "add r1, #1\n\t"
        "str r1, [sp, #96]"
        :
        : "r"(var_r8_16)
        : "memory");
    asm volatile(
        "mov r2, %1\n\t"
        "lsl r0, r2, #2\n\t"
        "add r0, r8\n\t"
        "lsl r0, r0, #3\n\t"
        "sub r0, r0, r2\n\t"
        "lsl %0, r0, #7"
        : "=&r"(case18_row)
        : "r"(var_r8_16)
        : "cc");
loop_104:
    if ((func_080E9D88(var_r8_16, var_r7_6) << 0x18) == 0) {
        goto block_107;
    }
    {
        register u8 *case18_record asm("r0");

        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "add %0, %0, %2\n\t"
            "add %0, %0, %3"
            : "=&r"(case18_record)
            : "r"(var_r7_6), "r"(case18_row), "r"(case18_base)
            : "cc");
        if (!(0x80 & M2C_FIELD(case18_record, u8 *, 0x36))) {
            goto block_107;
        }
    }
    func_080C02B4(var_r8_16, var_r7_6);
    CALL_BE65C_STAGED(var_r8_16, var_r7_6, -1, 0,
                      case18_zero, case18_zero, 0x1A,
                      case18_zero, 1, case18_zero);
block_107:
    var_r7_6 += 1;
    if ((u32) var_r7_6 <= 5U) {
        goto loop_104;
    }
    {
        register s32 case18_reload asm("r3");
        case18_reload = case18_stack[24];
        case18_outer_next = (u8) case18_reload;
    }
    var_r8_16 = case18_outer_next;
    if ((u32) case18_outer_next <= 1U) {
        goto loop_103;
    }
    return;
}
case 19: {
    register volatile s32 *case19_stack asm("sp");
    register u8 *case19_base asm("r6");
    register s32 case19_row asm("r5");
    register s32 case19_outer_next asm("r0");
    s32 case19_zero = 0;
    asm volatile("" : "+r"(case19_zero));
    var_r8_17 = case19_zero;
    case19_base = (u8 *)0x02034B4C;
loop_111:
    var_r7_7 = 0;
    case19_row = var_r8_17 + 1;
    case19_stack[24] = case19_row;
    asm volatile(
        "mov r1, %1\n\t"
        "lsl r0, r1, #2\n\t"
        "add r0, r8\n\t"
        "lsl r0, r0, #3\n\t"
        "sub r0, r0, r1\n\t"
        "lsl %0, r0, #7"
        : "=&r"(case19_row)
        : "r"(var_r8_17)
        : "cc");
loop_112:
    if ((func_080E9D88(var_r8_17, var_r7_7) << 0x18) == 0) {
        goto block_115;
    }
    {
        register u8 *case19_record asm("r0");

        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "add %0, %0, %2\n\t"
            "add %0, %0, %3"
            : "=&r"(case19_record)
            : "r"(var_r7_7), "r"(case19_row), "r"(case19_base)
            : "cc");
        if (M2C_FIELD(case19_record, u8 *, 0x38) == 0) {
            goto block_115;
        }
    }
    func_080C02B4(var_r8_17, var_r7_7);
    CALL_BE65C_STAGED(var_r8_17, var_r7_7, -1, 0,
                      case19_zero, case19_zero, 0x1A,
                      case19_zero, 1, case19_zero);
block_115:
    var_r7_7 += 1;
    if ((u32) var_r7_7 <= 5U) {
        goto loop_112;
    }
    {
        register s32 case19_reload asm("r2");
        case19_reload = case19_stack[24];
        case19_outer_next = (u8) case19_reload;
    }
    var_r8_17 = case19_outer_next;
    if ((u32) case19_outer_next <= 1U) {
        goto loop_111;
    }
    return;
}
case 20: {
    register volatile s32 *case20_stack asm("sp");
    register u8 *case20_base asm("r6");
    register s32 case20_row asm("r5");
    register s32 case20_outer_next asm("r0");
    s32 case20_zero;
    {
        register s32 case20_state_seed asm("r3") = 0;
        asm volatile("" : "+r"(case20_state_seed));
        var_r8_18 = case20_state_seed;
    }
    case20_base = (u8 *)0x02034B4C;
    case20_zero = 0;
    asm volatile("" : "+r"(case20_zero));
loop_120:
    var_r7_8 = 0;
    case20_row = var_r8_18 + 1;
    case20_stack[24] = case20_row;
    asm volatile(
        "mov r1, %1\n\t"
        "lsl r0, r1, #2\n\t"
        "add r0, r8\n\t"
        "lsl r0, r0, #3\n\t"
        "sub r0, r0, r1\n\t"
        "lsl %0, r0, #7"
        : "=&r"(case20_row)
        : "r"(var_r8_18)
        : "cc");
loop_121:
    if ((func_080E9D88(var_r8_18, var_r7_8) << 0x18) == 0) {
        goto block_124;
    }
    {
        register u8 *case20_record asm("r0");

        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "add %0, %0, %2\n\t"
            "add %0, %0, %3"
            : "=&r"(case20_record)
            : "r"(var_r7_8), "r"(case20_row), "r"(case20_base)
            : "cc");
        if (M2C_FIELD(case20_record, u8 *, 0x38) == 4) {
            goto block_124;
        }
    }
    func_080C02B4(var_r8_18, var_r7_8);
    CALL_BE65C_STAGED(var_r8_18, var_r7_8, -1, 0,
                      case20_zero, case20_zero, 0x1A,
                      case20_zero, 1, case20_zero);
block_124:
    var_r7_8 += 1;
    if ((u32) var_r7_8 <= 5U) {
        goto loop_121;
    }
    {
        register s32 case20_reload asm("r2");
        case20_reload = case20_stack[24];
        case20_outer_next = (u8) case20_reload;
    }
    var_r8_18 = case20_outer_next;
    if ((u32) case20_outer_next <= 1U) {
        goto loop_120;
    }
    return;
}
case 21: {
    register volatile s32 *case21_stack asm("sp");
    register u8 *case21_base asm("r9");
    register u8 *case21_selection asm("r5");
    register s32 case21_stride asm("r6");
    register s32 case21_offset asm("r0");
    register s32 case21_outer_next asm("r0");
    s32 case21_zero;
    {
        register s32 case21_state_seed asm("r3") = 0;
        asm volatile("" : "+r"(case21_state_seed));
        var_r8_19 = case21_state_seed;
    }
    {
        register u8 *case21_base_seed asm("r4") = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(case21_base_seed));
        case21_base = case21_base_seed;
    }
    case21_zero = 0;
    asm volatile("" : "+r"(case21_zero));
    case21_stride = 0x94;
loop_128:
    var_r7_9 = 0;
    case21_selection = (u8 *)(var_r8_19 + 1);
    case21_stack[24] = (s32) case21_selection;
    case21_offset = var_r8_19 * case21_stride;
    case21_offset += (s32) case21_base;
    {
        register u32 case21_adjust asm("r1") = 0xA084;
        case21_selection = (u8 *)case21_offset + case21_adjust;
    }
loop_129:
    if ((func_080E9D88(var_r8_19, var_r7_9) << 0x18) == 0) {
        goto block_133;
    }
    {
        register s32 case21_player asm("r2") = sp18;
        if (var_r8_19 != case21_player) {
            goto block_132;
        }
    }
    {
        register u32 case21_selected_player asm("r3");

        asm volatile(
            "ldrb %0, [%1, #0]"
            : "=r"(case21_selected_player)
            : "r"(case21_selection)
            : "memory");
        if (var_r7_9 == case21_selected_player) {
            goto block_133;
        }
    }
block_132:
    func_080C02B4(var_r8_19, var_r7_9);
    CALL_BE65C_STAGED(var_r8_19, var_r7_9, -1, 0,
                      case21_zero, case21_zero, 0x1A,
                      case21_zero, 1, case21_zero);
block_133:
    var_r7_9 += 1;
    if ((u32) var_r7_9 <= 5U) {
        goto loop_129;
    }
    case21_selection = (u8 *) case21_stack[24];
    case21_outer_next = (u8)(s32) case21_selection;
    var_r8_19 = case21_outer_next;
    if ((u32) case21_outer_next <= 1U) {
        goto loop_128;
    }
    return;
}
case 23: {
    register s32 case23_base asm("r7") = 0x02034B4C;
    register s32 case23_work asm("r0") = 0x27A5;
    register u8 *case23_state asm("r1");
    register s32 case23_zero asm("r4");
    asm volatile("" : "+r"(case23_base), "+r"(case23_work));
    case23_state = (u8 *)(case23_base + case23_work);
    case23_work = 6;
    *case23_state = (u8)case23_work;
    {
        register s32 case23_state_seed asm("r1") = 0;
        asm volatile("" : "+r"(case23_state_seed));
        var_r8_20 = case23_state_seed;
    }
    case23_zero = 0;
loop_137:
    if ((func_080E9D88(sp18, var_r8_20) << 0x18) == 0) {
        goto block_139;
    }
    func_080C02B4_word(sp18, var_r8_20);
    CALL_BE65C_STAGED(sp18, var_r8_20, -1, 0,
                      case23_zero, case23_zero, 0x1A,
                      case23_zero, 1, case23_zero);
block_139:
    temp_r0_27 = var_r8_20 + 1;
    var_r8_20 = temp_r0_27;
    if ((u32) temp_r0_27 <= 5U) {
        goto loop_137;
    }
    final_state = (s32 *)0x02030558;
    asm volatile("" : "+r"(final_state));
    var_r0 = 0x1300;
    goto block_372;
}
case 24: {
    register s32 case24_base asm("r2") = 0x02034B4C;
    register s32 case24_offset asm("r3") = 0x27A5;
    register u8 *case24_state asm("r1");
    register s32 case24_value asm("r0");
    asm volatile("" : "+r"(case24_base), "+r"(case24_offset));
    case24_state = (u8 *)(case24_base + case24_offset);
    case24_value = 6;
    *case24_state = (u8)case24_value;
    final_state = (s32 *)0x02030558;
    asm volatile("" : "+r"(final_state));
    var_r0 = 0x1300;
    goto block_372;
}
case 25: {
    register s32 case25_zero asm("r5");
    register u8 *case25_state asm("r1");
    register s32 case25_work asm("r0");
    register s32 case25_side asm("r7");
    temp_r4_3 = (void *)0x02034B4C;
    case25_zero = 0x27A5;
    asm volatile("" : "+r"(temp_r4_3), "+r"(case25_zero));
    case25_state = temp_r4_3 + case25_zero;
    case25_zero = 0;
    *case25_state = 6U;
    case25_work = 0x94;
    case25_side = sp18;
    asm volatile("" : "+r"(case25_work), "+r"(case25_side));
    temp_r4_3 = (void *)case25_side;
    temp_r4_3 = (void *)((u32)temp_r4_3 * case25_work);
    case25_work = 0x02034B4C;
    asm volatile("" : "+r"(case25_work));
    temp_r4_3 += case25_work;
    case25_state = (u8 *)0xA084;
    asm volatile("" : "+r"(case25_state));
    temp_r4_3 += (s32)case25_state;
    func_080C02B4(case25_side, M2C_FIELD(temp_r4_3, u8 *, 0));
    func_080BE65C(sp18, M2C_FIELD(temp_r4_3, u8 *, 0), -1, 0,
                  case25_zero, case25_zero, 0x1A,
                  case25_zero, 1, case25_zero);
    final_state = (s32 *)0x02030558;
    asm volatile("" : "+r"(final_state));
    var_r0 = 0x1300;
    goto block_372;
}
case 26: {
    register s32 case26_zero asm("r4");
    {
        register s32 case26_init asm("r2") = 0;
        asm volatile("" : "+r"(case26_init));
        var_r8_21 = case26_init;
    }
    case26_zero = 0;
loop_144:
    if ((func_080E9D88(sp18, var_r8_21) << 0x18) == 0) {
        goto block_146;
    }
    func_080C02B4_word(sp18, var_r8_21);
    {
        register volatile s32 *case26_outgoing asm("sp");
        case26_outgoing[0] = case26_zero;
        case26_outgoing[1] = case26_zero;
        case26_outgoing[2] = 0x1A;
        case26_outgoing[3] = case26_zero;
        case26_outgoing[4] = 1;
        case26_outgoing[5] = case26_zero;
        {
            register s32 case26_arg0 asm("r0") = sp18;
            register s32 case26_arg1 asm("r1") = var_r8_21;
            register s32 case26_arg2 asm("r2") = -1;
            register s32 case26_arg3 asm("r3") = 0;
            func_080BE65C(case26_arg0, case26_arg1,
                          case26_arg2, case26_arg3);
        }
    }
block_146:
    temp_r0_28 = var_r8_21 + 1;
    var_r8_21 = temp_r0_28;
    if ((u32) temp_r0_28 <= 5U) {
        goto loop_144;
    }
    return;
}
case 27: {
    u32 case27_count;
    register u32 case27_scan asm("r8");
    register u8 *case27_list asm("r4");
    register u8 *case27_flags asm("r2");
    register u8 *case27_store_base asm("r1");
    register u32 case27_r6_reserve asm("r6");

    {
        register s32 case27_player asm("r3") = sp18;
        if (case27_player == 0) {
            goto block_373;
        }
    }
    asm volatile("" : "=&r"(case27_r6_reserve));
    case27_count = 0;
    {
        register u32 case27_zero asm("r4") = 0;
        asm volatile("mov %0, %1"
                     : "=r"(case27_scan)
                     : "l"(case27_zero));
    }
    case27_list = (u8 *)0x02033EBA;
    case27_flags = (u8 *)0x02037300;
    asm volatile("" : "+r"(case27_list), "+r"(case27_flags));
    case27_store_base = case27_list;
loop_150:
    {
        register u32 case27_index asm("r5");
        asm volatile("mov %0, r8" : "=l"(case27_index));
        if (*(u8 *)(
                case27_index - (0U - (u32)case27_flags)) != 0) {
            register u32 case27_count_next asm("r0");
            *(u8 *)(
                case27_count - (0U - (u32)case27_store_base)) =
                (u8)case27_index;
            case27_count_next = case27_count + 1;
            case27_count = (u8)case27_count_next;
        }
    }
block_152:
    {
        register u32 case27_scan_next asm("r0");
        case27_scan_next = case27_scan + 1;
        case27_scan = (u8)case27_scan_next;
    }
    if (case27_scan <= 9U) {
        goto loop_150;
    }
    {
        register u32 case27_player_offset asm("r0") = 0x94;
        {
            register u32 case27_player asm("r1") = sp18;
            case27_player_offset *= case27_player;
        }
        {
            register u32 case27_record_base asm("r2") = 0x02034B4C;
            asm volatile("" : "+r"(case27_record_base));
            case27_player_offset += case27_record_base;
        }
        {
            register u32 case27_state_offset asm("r3") = 0xA084;
            asm volatile("" : "+r"(case27_state_offset));
            case27_player_offset += case27_state_offset;
        }
        case27_player_offset =
            func_080ECF78(*(u8 *)case27_player_offset, case27_count);
        case27_player_offset = (u8)case27_player_offset;
        case27_player_offset += (u32)case27_list;
        case27_list = (u8 *)0x02034B4C;
        {
            register u32 case27_dest_offset asm("r5") = 0x27B4;
            register u8 *case27_dest asm("r1");
            asm volatile("" : "+r"(case27_list),
                         "+r"(case27_dest_offset));
            case27_dest =
                (u8 *)((u32)case27_list + case27_dest_offset);
            case27_player_offset = *(u8 *)case27_player_offset;
            case27_dest += case27_player_offset;
            *case27_dest = 0;
        }
    }
    asm volatile("" : : "r"(case27_r6_reserve));
    return;
}
case 28: {
    register u8 *case28_second_flag asm("r6");
    register u8 *case28_second_addr asm("r0");
    register u8 *case28_wait_flag asm("r5");
    register void *case28_copy_source asm("r6");
    {
        register u32 case28_state_work asm("r0") = 0x94;
        register s32 case28_player asm("r7") = sp18;
        register u32 case28_record_base asm("r1");
        register u32 case28_state_offset asm("r2");
        case28_state_work *= case28_player;
        case28_record_base = 0x02034B4C;
        asm volatile("" : "+r"(case28_record_base));
        case28_state_work += case28_record_base;
        case28_state_offset = 0xA084;
        asm volatile("" : "+r"(case28_state_offset));
        case28_state_work += case28_state_offset;
        temp_r7 = *(u8 *)case28_state_work;
    }
    {
        register u32 case28_wait_base asm("r1");
        register s32 case28_player asm("r3");
        register s32 case28_player_twice asm("r2");
        case28_wait_base = 0x02032EEC;
        asm volatile("" : "+r"(case28_wait_base));
        case28_player = sp18;
        case28_player_twice = case28_player << 1;
        temp_r0_30 = (void *)(case28_player_twice + case28_player);
        temp_r0_30 = (void *)((u32)temp_r0_30 << 1);
        temp_r0_30 = (void *)(temp_r7 + (u32)temp_r0_30);
        temp_r0_30 = (void *)((u32)temp_r0_30 + case28_wait_base);
        case28_wait_base = 2;
        *(u8 *)temp_r0_30 = (u8)case28_wait_base;
        var_sl = case28_player_twice;
        case28_wait_flag = temp_r0_30;
    }
loop_156:
    func_080ED17C(1);
    if (*case28_wait_flag != 0) {
        goto loop_156;
    }
    {
        register u32 case28_record_base asm("r2") = 0x02034B4C;
        register u32 case28_record_offset asm("r1");
        register u32 case28_row asm("r0");
        case28_record_offset = temp_r7 * 0x270;
        temp_r4_4 = (void *)sp6C;
        temp_r5 = (void *)sp18;
        case28_row =
            ((((u32)temp_r4_4 + (u32)temp_r5) * 8)
             - (u32)temp_r5) << 7;
        case28_record_offset += case28_row;
        temp_r4_4 =
            (void *)(case28_record_offset + case28_record_base);
        {
            register u32 case28_player_offset asm("r0") = 0x94;
            case28_player_offset *= (u32)temp_r5;
            temp_r5 = (void *)(
                case28_player_offset + case28_record_base);
        }
    }
    {
        register u32 case28_copy_offset asm("r0") = 0xA0A8;
        asm volatile("" : "+r"(case28_copy_offset));
        case28_copy_source =
            (void *)((u32)temp_r5 + case28_copy_offset);
        func_080ED038(temp_r4_4, case28_copy_source, 0x70);
    }
    func_080BE560(sp18, temp_r7);
    func_080E90AC(sp18, temp_r7);
    func_080E8B08(sp18, temp_r7);
    {
        register s32 case28_half asm("r0");
        asm volatile(
            "mov r1, #62\n\t"
            "ldsh r0, [r4, r1]\n\t"
            "lsr r1, r0, #31\n\t"
            "add r0, r0, r1\n\t"
            "asr r0, r0, #1"
            : "=r"(case28_half)
            : "r"(temp_r4_4)
            : "r1", "cc", "memory");
        M2C_FIELD(temp_r4_4, s16 *, 8) = (s16)case28_half;
    }
    if (*(u8 *)0x0203055C != 1) {
        goto block_159;
    }
    M2C_FIELD(temp_r4_4, u16 *, 6) = (u16) M2C_FIELD(temp_r4_4, u16 *, 0x3A);
block_159:
    M2C_FIELD(temp_r4_4, u16 *, 4) = (u16) (M2C_FIELD(temp_r4_4, u16 *, 4) | 4);
    {
        register volatile s32 *case28_call_stack asm("sp");
        register s32 case28_first_arg asm("r3");
        register s32 case28_second_arg asm("r1");
        register s32 case28_third_arg asm("r2");
        register s32 case28_direction_player asm("r5");
        register s32 case28_direction asm("r0");
        case28_first_arg = *(u8 *)case28_copy_source;
        {
            register u32 case28_second_offset asm("r2") = 0xA0A9;
            register u8 *case28_second_value asm("r0");
            asm volatile("" : "+r"(case28_second_offset));
            case28_second_value =
                (u8 *)((u32)temp_r5 + case28_second_offset);
            case28_second_arg = *case28_second_value;
        }
        {
            register u32 case28_third_offset asm("r4") = 0xA0E0;
            register u8 *case28_third_value asm("r0");
            asm volatile("" : "+r"(case28_third_offset));
            case28_third_value =
                (u8 *)((u32)temp_r5 + case28_third_offset);
            case28_third_arg = *case28_third_value;
        }
        case28_call_stack[0] = temp_r7;
        case28_direction_player = sp18;
        case28_direction =
            case28_direction_player == 0 ? 0x10000 : 0xFFFF0000;
        case28_call_stack[1] = case28_direction;
        case28_direction = 0;
        case28_call_stack[2] = case28_direction;
        {
            register s32 case28_first_call_arg asm("r0") =
                case28_first_arg;
            register s32 case28_player_call_arg asm("r3") = sp18;
            func_080BAF2C_regs(
                case28_first_call_arg, case28_second_arg,
                case28_third_arg, case28_player_call_arg);
        }
    }
    {
        register u32 case28_second_base asm("r1") = 0x02032EEC;
        asm volatile("" : "+r"(case28_second_base));
        case28_second_addr = (u8 *)sp18;
        case28_second_addr =
            (u8 *)((u32)case28_second_addr + var_sl);
        case28_second_addr =
            (u8 *)((u32)case28_second_addr << 1);
        case28_second_addr =
            (u8 *)(temp_r7 + (u32)case28_second_addr);
        case28_second_addr =
            (u8 *)((u32)case28_second_addr + case28_second_base);
        case28_second_base = 1;
        *case28_second_addr = (u8)case28_second_base;
    }
    case28_second_flag = case28_second_addr;
loop_164:
    func_080ED17C(1);
    temp_r5_2 = *case28_second_flag;
    if (temp_r5_2 != 0) {
        goto loop_164;
    }
    func_080C02B4(sp18, temp_r7);
    func_080BE65C(sp18, temp_r7, -1, 0, (s32) temp_r5_2, (s32) temp_r5_2, 0x1A, (s32) temp_r5_2, 1, (s32) temp_r5_2);
    return;
}
case 29: {
    register volatile s32 *case29_stack asm("sp");
    register u32 case29_r7 asm("r7");
    register u8 *case29_wait_flag0 asm("r7");
    register s32 temp_r6 asm("r6");
    register s32 var_r6 asm("r6");
    s32 *case29_second_dest;
    s32 case29_player;
    register s32 case29_scan_offset asm("r3");
    register u32 case29_zero asm("r4");
    register u8 *case29_first_count asm("r1");
    func_080BB224(2, sp18, 0, 0);
    {
        register s32 case29_side_twice asm("r7") = sp18;
        case29_side_twice <<= 1;
        var_sl = case29_side_twice;
    }
    goto loop_168;
block_167:
    func_080ED17C(1);
loop_168:
    if ((func_080BB654() << 0x18) == 0) {
        goto block_167;
    }
    {
        register s32 case29_state_seed asm("r0") = 0;
        asm volatile("" : "+r"(case29_state_seed));
        var_r8_23 = case29_state_seed;
    }
    {
        register u8 *case29_base asm("r1") = (u8 *)0x02034B4C;
        register s32 case29_players_offset asm("r2") = 0x2713;
        asm volatile("" : "+r"(case29_base),
                     "+r"(case29_players_offset));
        case29_players = case29_base + case29_players_offset;
    }
    {
        register u8 *case29_base asm("r3") = (u8 *)0x02034B4C;
        register s32 case29_slots_offset asm("r4") = 0x2714;
        asm volatile("" : "+r"(case29_base),
                     "+r"(case29_slots_offset));
        case29_slots = case29_base + case29_slots_offset;
    }
    case29_lists = (u8 *)0x02032FCA;
loop_170:
    {
        register u8 *case29_copy_dest_r0 asm("r0") =
            (u8 *)0x02032FE4;
        register s32 case29_copy_row asm("r1");
        register s32 case29_source_row asm("r2");
        register s32 case29_source_base asm("r3");
        asm volatile("" : "+r"(case29_copy_dest_r0));
        case29_r7 = var_r8_23;
        temp_r4_5 = case29_r7 << 2;
        case29_copy_row = temp_r4_5 + case29_r7;
        case29_copy_row <<= 3;
        case29_copy_row -= case29_r7;
        case29_copy_row <<= 4;
        case29_copy_dest_r0 =
            (u8 *)(case29_copy_row + (u32)case29_copy_dest_r0);
        case29_source_base = sp6C;
        case29_player = sp18;
        case29_source_row = case29_source_base + case29_player;
        case29_source_row <<= 3;
        case29_source_row -= case29_player;
        case29_source_row <<= 7;
        case29_copy_row += case29_source_row;
        case29_source_row = 0x02034B4C;
        case29_copy_row += case29_source_row;
        func_080ED038(
            case29_copy_dest_r0, (void *)case29_copy_row, 0x270);
    }
    case29_first_dest = (s32 *)0x02033E84;
    asm volatile("" : "+r"(case29_first_dest));
    case29_first_dest =
        (s32 *)((u32)temp_r4_5 + (u32)case29_first_dest);
    {
        register s32 case29_first_src_base asm("r0") = 0x02032E8C;
        temp_r1_6 = case29_player;
        asm volatile("" : "+r"(temp_r1_6));
        temp_r1_6 += var_sl;
        temp_r1_6 <<= 3;
        asm volatile("add %0, %1, %0"
                     : "+r"(temp_r1_6)
                     : "r"(temp_r4_5));
        *case29_first_dest =
            *(s32 *)(temp_r1_6 + case29_first_src_base);
    }
    {
        register s32 case29_record_b_dest_base asm("r0") = 0x02033E9C;
        temp_r4_5 += case29_record_b_dest_base;
    }
    {
        register s32 case29_record_b_src_base asm("r0") = 0x02032EBC;
        asm volatile("" : "+r"(case29_record_b_src_base));
        temp_r1_6 += case29_record_b_src_base;
    }
    *(s32 *)temp_r4_5 = *(s32 *)temp_r1_6;
    case29_first_count = (u8 *)0x02032FDC + var_r8_23;
    *case29_first_count = 0U;
    var_r7_11 = 0;
    case29_scan_offset = var_r8_23;
    {
        register s32 case29_scan_twice asm("r0") =
            case29_scan_offset << 1;
        asm volatile("add %0, %1, %0"
                     : "+r"(case29_scan_offset)
                     : "r"(case29_scan_twice));
    }
loop_171:
    temp_r2_6 = var_r7_11 * 2;
    {
        register u32 case29_player_value asm("r0");
        register s32 case29_side_view asm("r4");
        asm volatile(
            "mov %1, %3\n\t"
            "add %0, %2, %1\n\t"
            "ldrb %0, [%0]\n\t"
            "ldr %1, [sp, #24]"
            : "=&r"(case29_player_value), "=&r"(case29_side_view)
            : "r"(temp_r2_6), "r"(case29_players)
            : "memory");
        if (case29_player_value != (u32)case29_side_view) {
            goto block_174;
        }
    }
    {
        register u32 case29_slot_value asm("r0");
        asm volatile(
            "add %0, %1, %2\n\t"
            "ldrb %0, [%0]"
            : "=&r"(case29_slot_value)
            : "r"(temp_r2_6), "r"(case29_slots)
            : "memory");
        if (case29_slot_value != var_r8_23) {
            goto block_174;
        }
    }
    *(u8 *)(
        (*case29_first_count + case29_scan_offset)
        - (0U - (u32)case29_lists)) = var_r7_11;
    *case29_first_count = (u8)(*case29_first_count + 1);
block_174:
    var_r7_11 += 1;
    if ((u32) var_r7_11 <= 0x23U) {
        goto loop_171;
    }
    case29_player = sp18;
    if (case29_player != 0) {
        goto block_177;
    }
    {
        register u8 *case29_state_dest asm("r0") =
            (u8 *)0x02033EB4 + var_r8_23;
        register u8 *case29_state_source asm("r1");
        register u32 case29_state_base asm("r2") = 0x02034B4C;
        register u32 case29_state_offset asm("r3") = 0x9C;
        asm volatile("" : "+r"(case29_state_dest),
                     "+r"(case29_state_base),
                     "+r"(case29_state_offset));
        case29_state_offset <<= 6;
        case29_state_source =
            (u8 *)(case29_state_base + case29_state_offset + var_r8_23);
        *case29_state_dest = *case29_state_source;
    }
block_177:
    asm volatile("" : "+r"(var_r8_23));
    temp_r0_33 = var_r8_23 + 1;
    var_r8_23 = temp_r0_33;
    if ((u32) temp_r0_33 <= 5U) {
        goto loop_170;
    }
    asm volatile("movs %0, #0" : "=r"(case29_zero));
    var_r8_24 = case29_zero;
    {
        register s32 case29_row_base asm("r5") = sp6C;
        register s32 case29_row_side asm("r7") = sp18;
        register s32 case29_row asm("r0");
        register s32 case29_side_row asm("r1");
        case29_row = case29_row_base + case29_row_side;
        case29_row <<= 3;
        case29_row -= case29_row_side;
        case29_row <<= 7;
        case29_stack[8] = case29_row;
        case29_row = case29_row_side;
        asm volatile("" : "+r"(case29_row));
        case29_row += var_sl;
        case29_side_row = case29_row << 3;
        case29_stack[9] = case29_side_row;
        case29_row <<= 1;
        case29_stack[10] = case29_row;
    }
loop_179:
    {
        register u32 case29_base asm("r3");
        register u32 case29_unit_addr asm("r0") = 0x94;
        register u32 case29_unit_side asm("r2") = sp18;
        register u32 case29_field asm("r4");
        register u32 case29_unit_base asm("r1");
        register u32 case29_index asm("r7");
        register u32 case29_copy_dest_r0 asm("r0");
        register u32 case29_copy_source_r1 asm("r1");
        register u32 case29_copy_base_r2 asm("r2");
        case29_unit_addr *= case29_unit_side;
        case29_unit_addr += var_r8_24;
        case29_base = 0x02034B4C;
        case29_field = 0xA084;
        asm volatile("" : "+r"(case29_base), "+r"(case29_field));
        case29_unit_base = case29_base + case29_field;
        case29_unit_addr += case29_unit_base;
        case29_unit_addr = *(u8 *)case29_unit_addr;
        temp_r0_34 = case29_unit_addr;
        case29_index = var_r8_24;
        case29_second_index4 = case29_index << 2;
        case29_copy_dest_r0 = case29_second_index4 + case29_index;
        case29_copy_dest_r0 <<= 3;
        case29_copy_dest_r0 -= case29_index;
        case29_copy_dest_r0 <<= 4;
        case29_copy_dest_r0 += case29_stack[8];
        case29_copy_dest_r0 += case29_base;
        case29_copy_base_r2 = 0x02032FE4;
        asm volatile("" : "+r"(case29_copy_base_r2));
        case29_base = temp_r0_34;
        temp_r4_6 = case29_base << 2;
        case29_copy_source_r1 = temp_r4_6 + case29_base;
        case29_copy_source_r1 <<= 3;
        case29_copy_source_r1 -= case29_base;
        case29_copy_source_r1 <<= 4;
        case29_copy_source_r1 += case29_copy_base_r2;
        func_080ED038((void *)case29_copy_dest_r0,
                      (void *)case29_copy_source_r1, 0x270);
    }
    {
        register s32 case29_second_dest_base asm("r2") = 0x02032E8C;
        register s32 case29_second_row asm("r7") = case29_stack[9];
        asm volatile("" : "+r"(case29_second_dest_base));
        temp_r1_7 = case29_second_index4 + case29_second_row;
        case29_second_dest =
            (s32 *)(temp_r1_7 + case29_second_dest_base);
        {
            register u32 case29_record_a asm("r0") = 0x02033E84;
            asm volatile("" : "+r"(case29_record_a));
            case29_record_a = temp_r4_6 + case29_record_a;
            *case29_second_dest = *(s32 *)case29_record_a;
        }
    }
    {
        register u32 case29_record_b_dest asm("r0") = 0x02032EBC;
        temp_r1_7 += case29_record_b_dest;
    }
    {
        register u32 case29_record_b_src asm("r0") = 0x02033E9C;
        temp_r4_6 += case29_record_b_src;
    }
    *(s32 *)temp_r1_7 = *(s32 *)temp_r4_6;
    case29_r7 = (u32) *(s32 **)case29_second_dest;
    temp_r6 = *(s32 *)case29_r7 & ~0xC0;
    if (sp18 != 0) {
        goto block_181;
    }
    {
        register s32 case29_mask_delta asm("r4") = 3;
        case29_mask_delta -= func_080ECF78_word(var_r8_24, 3U);
        case29_mask_delta <<= 6;
        var_r6 = temp_r6 | case29_mask_delta;
    }
    goto block_182;
block_181:
    var_r6 = temp_r6 | (((u32) (func_080ECF78_word(var_r8_24, 3U) << 0x18) >> 0x12) + 0x40);
block_182:
    *(s32 *)case29_r7 = var_r6;
    case29_r7 = 0;
    {
        register u8 *case29_count_ptr asm("r0") =
            (u8 *)0x02032FDC + temp_r0_34;
        case29_stack[24] = var_r8_24 + 1;
        if (case29_r7 >= (u32) *case29_count_ptr) {
            goto block_185;
        }
    }
    var_r6 = 0x02032FCA;
    {
        register u32 case29_copy_unit_r2 asm("r2") = temp_r0_34;
        register u32 case29_copy_twice_r0 asm("r0");
        case29_copy_twice_r0 = case29_copy_unit_r2 << 1;
        asm volatile("" : "+r"(case29_copy_twice_r0));
        temp_r4_6 = case29_copy_twice_r0 + case29_copy_unit_r2;
    }
    {
        register u32 case29_copy_record_base_r1 asm("r1") = 0x02034B4C;
        register u32 case29_copy_outer_r3 asm("r3") = var_r8_24;
        register u32 case29_copy_record_r0 asm("r0");
        asm volatile("" : "+r"(case29_copy_record_base_r1),
                     "+r"(case29_copy_outer_r3));
        case29_copy_record_r0 =
            case29_second_index4 + case29_copy_outer_r3;
        case29_copy_record_r0 <<= 3;
        case29_copy_record_r0 -= case29_copy_outer_r3;
        case29_copy_record_r0 <<= 4;
        case29_second_index4 = case29_stack[8];
        case29_copy_record_r0 += case29_second_index4;
        case29_second_index4 =
            case29_copy_record_r0 + case29_copy_record_base_r1;
    }
    asm volatile("" : : "g"(sp20));
loop_184:
    {
        register s32 case29_record_value asm("r0") =
            M2C_FIELD((case29_r7 + temp_r4_6), u8 *, var_r6);
        register s32 case29_record_arg asm("r3");
        register s32 case29_record_side asm("r1");
        register s32 case29_record_outer asm("r2");
        asm volatile(
            "mov r1, #10\n\t"
            "ldsh r3, [r5, r1]"
            : "=r"(case29_record_arg)
            : "r"(case29_second_index4)
            : "r1", "cc", "memory");
        case29_record_side = sp18;
        case29_record_outer = var_r8_24;
        func_080C007C_word(
            case29_record_value, case29_record_side,
            case29_record_outer, case29_record_arg);
    }
    case29_r7 = (u8)(case29_r7 + 1);
    if (case29_r7 < (u32) M2C_FIELD(temp_r0_34, u8 *, 0x02032FDC)) {
        goto loop_184;
    }
block_185:
    {
        register s32 case29_guard_r0 asm("r0");
        register s32 case29_guard_r1 asm("r1");
        s32 case29_side_guard;
        asm volatile("" :
                     "=r"(case29_guard_r0), "=r"(case29_guard_r1));
        case29_side_guard = sp18;
        asm volatile("" :
                     : "r"(case29_guard_r0), "r"(case29_guard_r1),
                       "r"(case29_side_guard));
        if (case29_side_guard != 0) {
            goto block_187;
        }
    }
    M2C_FIELD(var_r8_24, u8 *, 0x0203724C) = (u8) M2C_FIELD(temp_r0_34, u8 *, 0x02033EB4);
block_187:
    if ((func_080E9D88(sp18, var_r8_24) << 0x18) == 0) {
        goto block_189;
    }
    {
        register u32 case29_flag_base asm("r0") = 0x02032EEC;
        register u32 case29_flag_addr asm("r1") = case29_stack[10];
        asm volatile("" : "+r"(case29_flag_base));
        case29_flag_addr += var_r8_24;
        case29_flag_addr += case29_flag_base;
        case29_flag_base = 1;
        *(u8 *)case29_flag_addr = (u8)case29_flag_base;
    }
block_189:
    {
        register u32 case29_exit_reload asm("r3") = case29_stack[24];
        register u32 case29_exit_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case29_exit_normalized)
            : "r"(case29_exit_reload));
        var_r8_24 = case29_exit_normalized;
        if (case29_exit_normalized > 5U) {
            goto block_191;
        }
    }
    goto loop_179;
block_191:
    case29_wait_records = (u8 *)0x02032E8C;
    {
        register s32 case29_wait_index asm("r0") = sp18 + var_sl;
        case29_wait_flags = (u8 *)0x02032EEC;
        {
            register s32 case29_wait_flag_offset asm("r1") =
                case29_wait_index * 2;
            case29_wait_flag0 = (u8 *)(
                (u32)case29_wait_flag_offset
                - (0U - (u32)case29_wait_flags));
        }
        case29_wait_record0 = (s32 **)(
            (u32)(case29_wait_index * 8)
            - (0U - (u32)case29_wait_records));
    }
loop_192:
    func_080ED17C(1);
    {
        register u32 case29_wait_zero asm("r0") = 0;
        asm volatile("" : "+r"(case29_wait_zero));
        var_r8_25 = case29_wait_zero;
    }
    if (*case29_wait_record0 == 0) {
        goto loop_194;
    }
    {
        register u32 case29_wait_flag_value asm("r0");
        asm volatile("ldrb %0, [%1, #0]"
                     : "=r"(case29_wait_flag_value)
                     : "r"(case29_wait_flag0)
                     : "memory");
        if (case29_wait_flag_value != 0) {
            goto block_197;
        }
    }
loop_194:
    {
        register u32 case29_wait_next asm("r0") = var_r8_25 + 1;
        register s32 case29_wait_row asm("r2");
        case29_wait_next <<= 24;
        case29_wait_next >>= 24;
        var_r8_25 = case29_wait_next;
        if (case29_wait_next > 5U) {
            goto block_373;
        }
        case29_wait_next *= 4;
        {
            register s32 case29_wait_row8 asm("r1");
            case29_wait_row = sp18;
            case29_wait_row += var_sl;
            case29_wait_row8 = case29_wait_row * 8;
            case29_wait_next += case29_wait_row8;
        }
        case29_wait_next += (u32)case29_wait_records;
        if (*(s32 *)case29_wait_next == 0) {
            goto loop_194;
        }
        {
            register u32 case29_wait_flag_address asm("r0") =
                case29_wait_row * 2;
            case29_wait_flag_address += var_r8_25;
            case29_wait_flag_address += (u32)case29_wait_flags;
            if (*(u8 *)case29_wait_flag_address == 0) {
                goto loop_194;
            }
        }
    }
block_197:
    {
        register u32 case29_wait_check asm("r1") = var_r8_25;

        asm volatile("" : "+r"(case29_wait_check));
        if (case29_wait_check <= 5U) {
            goto loop_192;
        }
    }
    return;
}
case 30: {
    register u32 case30_state asm("r3");
    register u32 case30_player asm("r4");
    register u32 case30_row asm("r2");

    case30_state = sp6C;
    case30_player = sp18;
    case30_row = ((case30_state + case30_player) * 8 - case30_player) << 7;
    {
        register u32 case30_unit_addr asm("r0") = case30_player * 0x94;
        register u32 case30_base asm("r5") = 0x02034B4C;
        register u32 case30_unit asm("r1");

        case30_unit_addr += case30_base;
        {
            register u32 case30_field asm("r7") = 0xA084;
            case30_unit_addr += case30_field;
        }
        case30_unit = *(u8 *)case30_unit_addr;
        case30_row += (case30_unit * 0x270) + case30_base;
    }
    {
        register u32 case30_outer_zero asm("r0") = 0;
        asm volatile("" : "+r"(case30_outer_zero));
        var_r8_26 = case30_outer_zero;
    }
    {
        register u32 case30_zero asm("r1") = 0;
loop_201:
        {
            register u32 case30_index asm("r3") = var_r8_26;
            register u32 case30_addr asm("r0") = case30_index * 4;
            asm volatile("" : "+r"(case30_index));
            case30_addr = case30_row + case30_addr;
            M2C_FIELD(case30_addr, s16 *, 0x52) = case30_zero;
        }
    }
    temp_r0_37 = var_r8_26 + 1;
    var_r8_26 = temp_r0_37;
    if ((u32) temp_r0_37 <= 3U) {
        goto loop_201;
    }
    {
        register u32 case30_scale asm("r0") = 0x94;
        register u32 case30_player2 asm("r5") = sp18;
        register u32 case30_record asm("r4") = case30_player2;

        case30_record *= case30_scale;
        {
            register u32 case30_base2 asm("r7") = 0x02034B4C;
            register u32 case30_field2 asm("r0");

            case30_record += case30_base2;
            case30_field2 = 0xA084;
            asm volatile("" : "+r"(case30_field2));
            case30_record += case30_field2;
        }
        func_080BE5A8(case30_player2, *(u8 *)case30_record);
        func_080E90AC(sp18, *(u8 *)case30_record);
        func_080E8B08(sp18, *(u8 *)case30_record);
        var_r1_2 = *(u8 *)case30_record;
    }
    case3031_neg = -1;
    case3031_zero = 0;
    {
        register volatile s32 *case3031_outgoing asm("sp");
        case3031_outgoing[0] = case3031_zero;
        case3031_outgoing[1] = case3031_zero;
    }
    var_r0_3 = 0x25;
    goto block_205;
}
case 31: {
    register u32 case31_base asm("r2");
    register u32 case31_offset asm("r3");
    register u32 case31_player asm("r4");
    register u32 case31_state asm("r5");
    register u32 case31_dst asm("r1");
    register u32 case31_src asm("r0");

    case31_base = 0x02034B4C;
    case31_offset = 0x27BE;
    asm volatile("" : "+r"(case31_offset));
    case31_dst = case31_base + case31_offset;
    case31_player = sp18;
    case31_dst = case31_player + case31_dst;
    case31_state = sp6C;
    case31_src = case31_state + case31_base;
    {
        register u32 case31_field asm("r7") = 0xA07D;
        case31_src += case31_field;
    }
    {
        register u32 case31_value asm("r0") = *(u8 *)case31_src;
        case3031_zero = 0;
        *(u8 *)case31_dst = case31_value;
    }
    {
        register u32 case31_record asm("r0") = 0x94;
        register u32 case31_record_field asm("r1");

        case31_record *= case31_player;
        case31_record += case31_base;
        case31_record_field = 0xA084;
        case31_record += case31_record_field;
        var_r1_2 = *(u8 *)case31_record;
    }
    case3031_neg = -1;
    {
        register volatile s32 *case3031_outgoing asm("sp");
        case3031_outgoing[0] = case3031_zero;
        case3031_outgoing[1] = case3031_zero;
    }
    var_r0_3 = 0x24;
    goto block_205;
}
block_205:
    {
        register volatile s32 *case3031_outgoing asm("sp");
        case3031_outgoing[2] = var_r0_3;
        case3031_outgoing[3] = case3031_zero;
        case3031_outgoing[4] = case3031_zero;
        case3031_outgoing[5] = case3031_zero;
    }
    func_080BE9D8(sp18, var_r1_2, case3031_neg, case3031_zero);
    return;
case 32: {
    register void *case32_base asm("r6");
    s32 case32_zero;
    register s32 case32_row asm("r5");

    {
        register u32 case32_outer_zero asm("r2") = 0;
        asm volatile("" : "+r"(case32_outer_zero));
        var_r8_27 = case32_outer_zero;
    }
    case32_base = (void *)0x02034B4C;
    case32_zero = 0;
    {
        register s32 case32_row_base asm("r3") = sp6C;
        register s32 case32_row_work asm("r0");
        case32_row = sp18;
        asm volatile("" : "+r"(case32_row_base), "+r"(case32_row));
        asm volatile("add %0, %1, %2"
                     : "=r"(case32_row_work)
                     : "r"(case32_row_base), "r"(case32_row)
                     : "cc");
        case32_row_work *= 8;
        case32_row_work -= case32_row;
        case32_row = case32_row_work << 7;
    }
loop_207:
    if ((func_080E9D88(sp18, var_r8_27) << 0x18) == 0) {
        goto block_212;
    }
    {
        register u32 case32_record_flag asm("r0");
        asm volatile(
            "mov r1, %1\n\t"
            "lsl r0, r1, #2\n\t"
            "add r0, %1\n\t"
            "lsl r0, r0, #3\n\t"
            "sub r0, r0, r1\n\t"
            "lsl r0, r0, #4\n\t"
            "add r0, %2\n\t"
            "add r0, %3\n\t"
            "add r0, #112\n\t"
            "ldrb r0, [r0]"
            : "=r"(case32_record_flag)
            : "r"(var_r8_27), "r"(case32_row), "r"(case32_base)
            : "r1", "cc", "memory");
        if (case32_record_flag != 1) {
            goto block_211;
        }
    }
    var_r7 = var_r8_27;
    goto block_212;
block_211:
    CALL_BE9D8_STAGED(sp18, var_r8_27, -1, 0,
                      case32_zero, case32_zero, 0x24,
                      case32_zero, case32_zero, case32_zero);
block_212:
    temp_r0_38 = var_r8_27 + 1;
    var_r8_27 = temp_r0_38;
    if ((u32) temp_r0_38 <= 5U) {
        goto loop_207;
    }
    func_080C02B4_word(sp18, var_r7);
    {
        register volatile s32 *case32_outgoing asm("sp");
        register s32 case32_arg2 asm("r2");
        register s32 case32_outgoing_zero asm("r1");

        case32_arg2 = -1;
        case32_outgoing_zero = 0;
        case32_outgoing[0] = case32_outgoing_zero;
        case32_outgoing[1] = case32_outgoing_zero;
        case32_outgoing[2] = 0x1A;
        case32_outgoing[3] = case32_outgoing_zero;
        case32_outgoing[4] = 1;
        case32_outgoing[5] = case32_outgoing_zero;
        {
            register s32 case32_arg0 asm("r0") = sp18;
            register s32 case32_arg1 asm("r1") = var_r7;
            register s32 case32_arg3 asm("r3") = 0;

            func_080BE65C(case32_arg0, case32_arg1,
                          case32_arg2, case32_arg3);
        }
    }
    {
        register u32 case32_exit_base asm("r0") = 0x02034B4C;
        register u32 case32_exit_dest_offset asm("r2") = 0x27BE;
        register s32 case32_exit_dest_index asm("r3");
        register s32 case32_exit_source_index asm("r4");
        register u32 case32_exit_source_offset asm("r5");

        asm volatile("" : "+r"(case32_exit_base),
                     "+r"(case32_exit_dest_offset));
        var_r1_3 =
            (u8 *)(case32_exit_base + case32_exit_dest_offset);
        case32_exit_dest_index = sp18;
        var_r1_3 = (u8 *)(
            (u32)case32_exit_dest_index - (0U - (u32)var_r1_3));
        case32_exit_source_index = sp6C;
        case32_exit_base =
            (u32)case32_exit_source_index
            - (0U - case32_exit_base);
        case32_exit_source_offset = 0xA07D;
        asm volatile("" : "+r"(case32_exit_source_offset));
        var_r0_4 =
            (u8 *)(case32_exit_base + case32_exit_source_offset);
    }
    goto block_356;
}
case 33:
    {
    register volatile s32 *case33_stack asm("sp");
    u8 *case33_wait_flags;
    u8 *case33_wait_records;
    register u8 *case33_first_base asm("r5");
    register u8 *case33_first_count asm("r1");
    register s32 *case33_wait_record0 asm("r6");
    register u32 case33_side4 asm("r1");
    register u32 case33_successor asm("r2");
    register u32 case33_second_row_base asm("r4");
    {
        register u32 case33_initial_seed asm("r7") = 0;

        asm volatile("" : "+r"(case33_initial_seed));
        var_r8_28 = case33_initial_seed;
    }
loop_215:
    {
        register u32 case33_initial_view asm("r0") = var_r8_28;

        asm volatile("" : "+r"(case33_initial_view));
        if (case33_initial_view != 0) {
            goto block_217;
        }
    }
    {
        register u32 case33_r6_birth asm("r6");
        asm volatile("" : "=r"(case33_r6_birth));
        var_r7_13 = sp18;
        asm volatile("" : : "r"(case33_r6_birth));
    }
    goto block_218;
block_217:
    {
        register u32 case33_r6_birth asm("r6");
        s32 case33_side_one;

        asm volatile("" : "=r"(case33_r6_birth));
        case33_side_one = 1;
        var_r7_13 = sp18;
        var_r7_13 ^= case33_side_one;
        asm volatile("" : : "r"(case33_r6_birth));
    }
block_218:
    func_080BB224(2, var_r7_13, 0, 0);
    case33_side4 = var_r7_13 * 4;
    case33_stack[29] = case33_side4;
    case33_successor = var_r8_28;
    case33_successor += 1;
    case33_stack[24] = case33_successor;
    {
        register s32 case33_row_twice asm("r3") = var_r7_13 * 2;

        physical_stack[28] = case33_row_twice;
        asm volatile("" : "=m"(sp70));
    }
    goto loop_220;
block_219:
    func_080ED17C(1);
loop_220:
    if ((func_080BB654() << 0x18) == 0) {
        goto block_219;
    }
    {
        register u32 case33_outer_zero asm("r4") = 0;
        asm volatile("" : "+r"(case33_outer_zero));
        var_sl = case33_outer_zero;
    }
    {
        register u32 case33_slots_work asm("r0");
        register u32 case33_slots_offset asm("r1");
        case33_first_base = (u8 *)0x02034B4C;
        case33_slots_work = (u32)case33_first_base;
        case33_slots_offset = 0x2714;
        asm volatile("" : "+r"(case33_slots_offset));
        case33_slots_work += case33_slots_offset;
        case33_slots = (u8 *)case33_slots_work;
    }
    {
        register u8 *case33_lists_seed asm("r2") =
            (u8 *)0x02032FCA;
        asm volatile("" : "+r"(case33_lists_seed));
        case33_lists = case33_lists_seed;
    }
loop_222:
    {
        register u32 case33_row_index asm("r3") = var_sl;
        temp_r4_8 = case33_row_index * 4;
        temp_r1_8 =
            (((temp_r4_8 + case33_row_index) * 8)
             - case33_row_index) * 0x10;
    }
    {
        register u32 case33_copy_arg0_base asm("r2") =
            0x02032FE4;
        register void *case33_copy_arg0 asm("r0");
        register void *case33_copy_arg1 asm("r1");
        register s32 case33_first_row_reload asm("r3");
        register s32 case33_first_row_work asm("r2");

        asm volatile("add %0, %1, %2"
                     : "=r"(case33_copy_arg0)
                     : "r"(temp_r1_8),
                       "r"(case33_copy_arg0_base)
                     : "cc");
        asm volatile(
            "ldr %0, [sp, #116]\n\t"
            "add %1, %0, r7\n\t"
            "lsl %1, %1, #3\n\t"
            "sub %1, %1, r7\n\t"
            "lsl %1, %1, #7"
            : "=r"(case33_first_row_reload),
              "=r"(case33_first_row_work)
            : "r"(var_r7_13)
            : "cc", "memory");
        asm volatile(
            "add %0, %1, %2\n\t"
            "add %0, %0, r5"
            : "=r"(case33_copy_arg1)
            : "r"(temp_r1_8),
              "r"(case33_first_row_work),
              "r"(case33_first_base)
            : "cc");
        func_080ED038(
            case33_copy_arg0,
            case33_copy_arg1,
            0x270);
    }
    {
        register s32 case33_first_dest_base asm("r2") = 0x02033E84;

        asm volatile("add %0, %1, %0"
                     : "+r"(case33_first_dest_base)
                     : "r"(temp_r4_8));
        case33_first_dest = (s32 *)case33_first_dest_base;
    }
    {
        register s32 case33_first_src_base asm("r0") = 0x02032E8C;
        register s32 case33_first_src_reload asm("r3");
        asm volatile(
            "ldr %2, [sp, #112]\n\t"
            "add %1, %2, r7\n\t"
            "lsl %1, %1, #3\n\t"
            "add %1, r4, %1\n\t"
            "add %0, %1, %0\n\t"
            "ldr %0, [%0]\n\t"
            "str %0, [%3]"
            : "+r"(case33_first_src_base),
              "=r"(temp_r1_9),
              "=r"(case33_first_src_reload)
            : "r"(case33_first_dest),
              "r"(temp_r4_8),
              "r"(var_r7_13)
            : "cc", "memory");
    }
    {
        register s32 case33_second_dest_base asm("r0") =
            0x02033E9C;
        asm volatile("add %0, %0, %1"
                     : "+r"(temp_r4_8)
                     : "r"(case33_second_dest_base)
                     : "cc");
    }
    {
        register s32 case33_second_src_base asm("r0") =
            0x02032EBC;
        asm volatile(
            "add %0, %0, %1\n\t"
            "ldr %1, [%0]\n\t"
            "str %1, [%2]"
            : "+r"(temp_r1_9), "+r"(case33_second_src_base)
            : "r"(temp_r4_8)
            : "cc", "memory");
    }
    case33_first_count = (u8 *)0x02032FDC + var_sl;
    *case33_first_count = 0U;
    {
        register u32 case33_first_index asm("r6");
        register u32 case33_first_list_seed asm("r4");

        case33_first_index = 0;
        case33_first_list_seed = var_sl;
        asm volatile("" : "+r"(case33_first_list_seed));
        case33_first_list_offset = case33_first_list_seed * 3;
loop_223:
        temp_r2_7 = case33_first_index * 2;
        {
            register u8 *case33_players_base asm("r4") =
                (u8 *)0x0203725F;
            register u8 *case33_player_entry asm("r0");
            asm volatile("add %0, %1, %2"
                         : "=l"(case33_player_entry)
                         : "l"(temp_r2_7), "l"(case33_players_base));
            if (*case33_player_entry != var_r7_13) {
                goto block_226;
            }
        }
        {
            register u8 *case33_slots_copy asm("r4") = case33_slots;
            register u8 *case33_slot_entry asm("r0");
            asm volatile("add %0, %1, %2"
                         : "=l"(case33_slot_entry)
                         : "l"(temp_r2_7), "l"(case33_slots_copy));
            if (*case33_slot_entry != var_sl) {
                goto block_226;
            }
        }
        case33_lists[*case33_first_count + case33_first_list_offset] =
            case33_first_index;
        *case33_first_count = (u8) (*case33_first_count + 1);
block_226:
        {
            register u32 case33_first_successor asm("r0");

            case33_first_successor = case33_first_index + 1;
            case33_first_successor <<= 24;
            case33_first_index = case33_first_successor >> 24;
        }
        if (case33_first_index <= 0x23U) {
            goto loop_223;
        }
    }
    if (var_r7_13 != 0) {
        goto block_229;
    }
    {
        register u8 *case33_side_dest asm("r0");
        register u8 *case33_side_base asm("r2");
        register u32 case33_side_offset asm("r3");
        register u8 *case33_side_source asm("r1");

        case33_side_dest = (u8 *)0x02033EB4;
        case33_side_dest += var_sl;
        case33_side_base = (u8 *)0x02034B4C;
        case33_side_offset = 0x9C;
        asm volatile("" : "+r"(case33_side_offset));
        case33_side_offset <<= 6;
        case33_side_source =
            case33_side_base + case33_side_offset + var_sl;
        *case33_side_dest = *case33_side_source;
    }
block_229:
    asm volatile("" : "+r"(var_sl));
    temp_r0_39 = var_sl + 1;
    var_sl = temp_r0_39;
    if ((u32) temp_r0_39 <= 5U) {
        goto loop_222;
    }
    {
        register u32 case33_second_outer_zero asm("r4") = 0;

        asm volatile("" : "+r"(case33_second_outer_zero));
        var_sl_2 = case33_second_outer_zero;
    }
    {
        register s32 case33_second_row asm("r5") = physical_stack[28];
        register s32 case33_second_row_sum asm("r0");

        asm volatile("add %0, %1, %2"
                     : "=r"(case33_second_row_sum)
                     : "r"(case33_second_row), "r"(var_r7_13));
        temp_r0_40 = case33_second_row_sum;
    }
    physical_stack[11] = temp_r0_40 * 2;
    asm volatile("" : "=m"(sp2C));
    sp34 = temp_r0_40 * 8;
    {
        register s32 case33_scale_factor asm("r0") = 0x94;
        register s32 case33_scale_input asm("r3") = sp18;
        register s32 case33_scale_work asm("r2");

        asm volatile(
            "add %0, %1, #0\n\t"
            "mul %0, %2"
            : "=&l"(case33_scale_work)
            : "l"(case33_scale_input), "l"(case33_scale_factor)
            : "cc");
        physical_stack[12] = case33_scale_work;
    }
loop_231:
    {
        register s32 case33_side_input asm("r4") = sp18;

        if (case33_side_input == 0) {
            goto block_233;
        }
    }
    if (*(u8 *)0x0203055C == 1) {
        goto block_234;
    }
block_233:
    {
        register u32 case33_normal_offset asm("r0");
        register u8 *case33_normal_base asm("r1");

        asm volatile(
            "ldr %0, [sp, #44]\n\t"
            "add %0, sl\n\t"
            "ldr r5, [sp, #48]\n\t"
            "add %0, %0, r5"
            : "=&r"(case33_normal_offset)
            :
            : "cc");
        case33_normal_base = (u8 *)0x0203EBD0;
        asm volatile("add %0, %1, %2"
                     : "=r"(var_r0_5)
                     : "r"(case33_normal_offset),
                       "r"(case33_normal_base)
                     : "cc");
    }
    goto block_235;
block_234:
    {
        register u32 case33_alternate_offset asm("r0");
        register u8 *case33_alternate_base asm("r3");

        asm volatile(
            "mov %0, #1\n\t"
            "add r1, r7, #0\n\t"
            "eor r1, %0\n\t"
            "lsl r1, r1, #24\n\t"
            "lsr r1, r1, #24\n\t"
            "lsl %0, r1, #1\n\t"
            "add %0, %0, r1\n\t"
            "lsl %0, %0, #1\n\t"
            "add %0, sl\n\t"
            "ldr r2, [sp, #48]\n\t"
            "add %0, %0, r2"
            : "=&r"(case33_alternate_offset)
            :
            : "cc");
        case33_alternate_base = (u8 *)0x0203EBD0;
        asm volatile("" : "+r"(case33_alternate_base));
        var_r0_5 = case33_alternate_offset + (u32)case33_alternate_base;
    }
block_235:
    temp_r0_41 = *var_r0_5;
    {
        register u32 case33_index asm("r4") = var_sl_2;
        register u32 case33_copy_dest asm("r0");
        register u32 case33_row_base asm("r1");
        register u32 case33_dest_base asm("r2");
        register u32 case33_copy_source asm("r1");
        register u32 case33_unit_copy asm("r2");
        register s32 case33_copy_size asm("r2");
        temp_r5_3 = (void *)(case33_index << 2);
        case33_copy_dest = (u32)temp_r5_3 + case33_index;
        case33_copy_dest <<= 3;
        case33_copy_dest -= case33_index;
        temp_r3_2 = case33_copy_dest << 4;
        case33_row_base = case33_stack[29];
        case33_copy_dest = case33_row_base + var_r7_13;
        case33_copy_dest <<= 3;
        case33_copy_dest -= var_r7_13;
        case33_copy_dest <<= 7;
        case33_copy_dest = temp_r3_2 + case33_copy_dest;
        case33_dest_base = 0x02034B4C;
        asm volatile("" : "+r"(case33_dest_base));
        case33_copy_dest += case33_dest_base;
        case33_copy_source = temp_r0_41;
        temp_r4_9 = case33_copy_source << 2;
        case33_copy_source = temp_r4_9 + case33_copy_source;
        case33_copy_source <<= 3;
        case33_unit_copy = temp_r0_41;
        case33_copy_source -= case33_unit_copy;
        case33_copy_source <<= 4;
        case33_unit_copy = 0x02032FE4;
        case33_copy_source += case33_unit_copy;
        case33_copy_size = 0x270;
        case33_stack[31] = temp_r3_2;
        func_080ED038((void *)case33_copy_dest,
                      (void *)case33_copy_source, case33_copy_size);
    }
    {
        register s32 case33_second_dest_base asm("r1") = 0x02032E8C;
        register s32 case33_second_row asm("r0") = sp34;
        temp_r5_3 = (void *)((u32)temp_r5_3 + case33_second_row);
        asm volatile("add %0, %1, %0"
                     : "+r"(case33_second_dest_base)
                     : "r"(temp_r5_3));
        {
            register u32 case33_record_a asm("r0") = 0x02033E84;
            asm volatile("" : "+r"(case33_record_a));
            case33_record_a = temp_r4_9 + case33_record_a;
            *(s32 *)case33_second_dest_base = *(s32 *)case33_record_a;
        }
    }
    {
        register u32 case33_record_b_dest asm("r0") = 0x02032EBC;
        temp_r5_3 = (void *)((u32)temp_r5_3 + case33_record_b_dest);
    }
    {
        register u32 case33_record_b_src asm("r0") = 0x02033E9C;
        asm volatile("" : "+r"(case33_record_b_src));
        temp_r4_9 += case33_record_b_src;
    }
    *(s32 *)temp_r5_3 = *(s32 *)temp_r4_9;
    var_r6_3 = 0;
    {
        register u8 *case33_second_count_r0 asm("r0") =
            (u8 *)0x02032FDC + temp_r0_41;
        case33_stack[26] = var_sl_2 + 1;
        asm volatile("ldr r3, [sp, #124]"
                     :
                     :
                     : "r3", "memory");
        if ((u32)var_r6_3 >= (u32)*case33_second_count_r0) {
            goto block_238;
        }
    }
    {
        register u32 case33_second_list_seed asm("r2") = temp_r0_41;

        asm volatile(
            "lsl r0, %0, #1\n\t"
            "add r5, r0, %0"
            :
            : "r"(case33_second_list_seed)
            : "r0", "r5", "cc");
    }
    {
        case33_second_row_base = 0x02034B4C;
        asm volatile(
            "mov %0, %1\n\t"
            "add %1, r3, #0"
            : "=r"(case33_lists), "+r"(case33_second_row_base)
            :
            : "cc");
    }
loop_237:
    {
        register s32 case33_call_arg0 asm("r0");
        register s32 case33_call_arg1 asm("r1");
        register s32 case33_call_arg2 asm("r2");
        register s32 case33_call_arg3 asm("r3");
        asm volatile(
            "add %0, r6, r5"
            : "=r"(case33_call_arg0));
        case33_call_arg1 = 0x02032FCA;
        asm volatile(
            "add %0, %0, %1\n\t"
            "ldrb %0, [%0]\n\t"
            "ldr r2, [sp, #116]\n\t"
            "add r1, r2, r7\n\t"
            "lsl r1, r1, #3\n\t"
            "sub r1, r1, r7\n\t"
            "lsl r1, r1, #7\n\t"
            "add r1, r4, r1\n\t"
            "add r1, r8\n\t"
            "movs r2, #10\n\t"
            "ldrsh %3, [r1, r2]\n\t"
            "add %1, r7, #0\n\t"
            "mov %2, sl"
            : "+r"(case33_call_arg0),
              "+r"(case33_call_arg1),
              "=r"(case33_call_arg2),
              "=r"(case33_call_arg3)
            :
            : "cc", "memory");
        ((void (*)())func_080C007C_word)(
            case33_call_arg0, case33_call_arg1,
            case33_call_arg2, case33_call_arg3);
    }
    var_r6_3 += 1;
    if ((u32) var_r6_3 < (u32) M2C_FIELD(temp_r0_41, u8 *, 0x02032FDC)) {
        goto loop_237;
    }
block_238:
    if (var_r7_13 != 0) {
        goto block_240;
    }
    M2C_FIELD(var_sl_2, u8 *, 0x0203724C) = (u8) M2C_FIELD(temp_r0_41, u8 *, 0x02033EB4);
block_240:
    if ((func_080E9D88(var_r7_13, var_sl_2) << 0x18) == 0) {
        goto block_242;
    }
    {
        register u8 *case33_flag_address asm("r1");

        {
            register u8 *case33_flag_base asm("r0") =
                (u8 *)0x02032EEC;

            case33_flag_address =
                (u8 *)(physical_stack[11] + var_sl_2);
            asm volatile("add %0, %0, %1"
                         : "+r"(case33_flag_address)
                         : "r"(case33_flag_base));
        }
        {
            register u32 case33_flag_value asm("r0") = 1;

            *case33_flag_address = case33_flag_value;
        }
    }
block_242:
    {
        register u32 case33_next_outer_reload asm("r3") =
            case33_stack[26];
        register u32 case33_next_outer_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case33_next_outer_normalized)
            : "r"(case33_next_outer_reload));
        var_sl_2 = case33_next_outer_normalized;
        if (case33_next_outer_normalized > 5U) {
            goto block_244;
        }
    }
    goto loop_231;
block_244:
    case33_wait_records = (u8 *)0x02032E8C;
    {
        register s32 case33_wait_base asm("r4") = physical_stack[28];
        register s32 case33_wait_index asm("r1");
        case33_wait_index = case33_wait_base + var_r7_13;
        case33_wait_flags = (u8 *)0x02032EEC;
        {
            register s32 case33_flag_offset asm("r0") =
                case33_wait_index * 2;
            var_r3 = case33_wait_flags + case33_flag_offset;
        }
        case33_wait_record0 =
            (s32 *)(case33_wait_records + (case33_wait_index * 8));
    }
loop_245:
    {
        register s32 case33_wait_call_arg asm("r0") = 1;

        asm volatile("" : "=m"(sp7C));
        case33_stack[31] = (s32)var_r3;
        func_080ED17C(case33_wait_call_arg);
    }
    {
        register u32 case33_wait_zero asm("r0") = 0;
        asm volatile("" : "+r"(case33_wait_zero));
        var_sl_3 = case33_wait_zero;
    }
    {
        register s32 case33_wait_record_value asm("r0") =
            *case33_wait_record0;

        var_r3 = (u8 *)case33_stack[31];
        if (case33_wait_record_value == 0) {
            goto loop_247;
        }
    }
    if (*var_r3 != 0) {
        goto block_250;
    }
loop_247:
    temp_r0_43 = var_sl_3 + 1;
    var_sl_3 = temp_r0_43;
    if ((u32) temp_r0_43 > 5U) {
        goto block_251;
    }
    {
        register s32 case33_inner_offset asm("r0") = temp_r0_43 * 4;
        register s32 case33_row_work asm("r1") = physical_stack[28];
        temp_r2_8 = case33_row_work + var_r7_13;
        case33_row_work = (s32)temp_r2_8 * 8;
        case33_inner_offset += case33_row_work;
        case33_inner_offset += (s32)case33_wait_records;
        if (*(s32 *)case33_inner_offset == 0) {
            goto loop_247;
        }
    }
    {
        register s32 case33_flag_address asm("r0") =
            (s32)temp_r2_8 * 2;
        case33_flag_address += var_sl_3;
        case33_flag_address += (s32)case33_wait_flags;
        if (*(u8 *)case33_flag_address == 0) {
            goto loop_247;
        }
    }
block_250:
    {
        register u32 case33_wait_check asm("r2") = var_sl_3;
        asm volatile("" : "+r"(case33_wait_check));
        if (case33_wait_check <= 5U) {
            goto loop_245;
        }
    }
block_251:
    {
        register u32 case33_exit_state_reload asm("r3") =
            case33_stack[24];
        register u32 case33_exit_state_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case33_exit_state_normalized)
            : "r"(case33_exit_state_reload));
        var_r8_28 = case33_exit_state_normalized;
        if (case33_exit_state_normalized > 1U) {
            goto block_253;
        }
    }
    goto loop_215;
block_253:
    return;
    }
case 34: {
    register volatile s32 *case34_stack asm("sp");
    register s32 case34_zero asm("r4");
    func_080C030C(1);
    case34_zero = 0;
    var_r8_29 = case34_zero;
loop_256:
    {
        register s32 case34_guard_r5 asm("r5");
        register s32 case34_guard_r6 asm("r6");
        asm volatile("" : "=r"(case34_guard_r5), "=r"(case34_guard_r6));
        var_r7_14 = 0;
        asm volatile("" :: "r"(case34_guard_r5), "r"(case34_guard_r6));
    }
    {
        register s32 case34_successor asm("r5") = var_r8_29;

        case34_successor += 1;
        case34_stack[24] = case34_successor;
    }
loop_257:
    CALL_BE9D8_STAGED(var_r8_29, var_r7_14, -1, 0,
                      case34_zero, case34_zero, 0x24,
                      case34_zero, case34_zero, case34_zero);
    var_r7_14 += 1;
    if ((u32) var_r7_14 <= 5U) {
        goto loop_257;
    }
    {
        register u32 case34_exit_state_reload asm("r7") =
            case34_stack[24];
        register u32 case34_exit_state_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case34_exit_state_normalized)
            : "r"(case34_exit_state_reload));
        var_r8_29 = case34_exit_state_normalized;
        if (case34_exit_state_normalized <= 1U) {
            goto loop_256;
        }
    }
    return;
}
case 35: {
    register volatile s32 *case35_stack asm("sp");
    register s32 case35_zero asm("r4");
    register u32 case35_copy_current asm("r0");
    u8 *case35_old_players;
    u8 *case35_old_slots;
    u8 *case35_new_players;
    u8 *case35_new_slots;
    case35_copy_current = 0;
    var_r8_30 = case35_copy_current;
    case35_old_players = (u8 *)0x02032F82;
    case35_new_players = (u8 *)0x0203725F;
    case35_old_slots = case35_old_players + 1;
    case35_new_slots = case35_new_players + 1;
loop_261:
    temp_r1_11 = var_r8_30 * 2;
    asm volatile("" : : "r"(case35_copy_current));
    *(u8 *)(
        (u32)temp_r1_11 - (0U - (u32)case35_old_players)) =
        *(u8 *)(
            (u32)temp_r1_11 - (0U - (u32)case35_new_players));
    *(u8 *)(
        (u32)temp_r1_11 - (0U - (u32)case35_old_slots)) =
        *(u8 *)(
            (u32)temp_r1_11 - (0U - (u32)case35_new_slots));
    asm volatile(
        "mov r0, r8\n\t"
        "add r0, #1\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24"
        : "=r"(case35_copy_current)
        :
        : "cc");
    var_r8_30 = case35_copy_current;
    if (case35_copy_current <= 0x23U) {
        goto loop_261;
    }
    {
    u8 *case35_players;
    u8 *case35_saved_players;
    u8 *case35_selection;
    u8 *case35_saved_slots;
    u8 *case35_slots;
    s32 case35_side_offset;
    register s32 case35_side_r5 asm("r5");
    {
        register s32 case35_state_seed asm("r3") = 0;
        asm volatile("" : "+r"(case35_state_seed));
        var_r8_31 = case35_state_seed;
    }
    case35_players = (u8 *)0x0203725F;
    case35_saved_players = (u8 *)0x02032F82;
    {
        register s32 case35_scale_r0 asm("r0") = 0x94;
        register s32 case35_side_offset_r4 asm("r4");

        case35_side_r5 = sp18;
        case35_side_offset_r4 = case35_side_r5;
        asm volatile("" : "+r"(case35_scale_r0),
                     "+r"(case35_side_r5),
                     "+r"(case35_side_offset_r4));
        case35_side_offset_r4 *= case35_scale_r0;
        case35_side_offset = case35_side_offset_r4;
    }
    case35_selection = case35_players + 0x7971;
    asm volatile("" : : "r"(case35_side_r5));
    case35_saved_slots = case35_saved_players + 1;
    case35_slots = case35_players + 1;
loop_263:
    {
        register u32 case35_output_index asm("r3") = var_r8_31;
        register u8 *case35_output_player asm("r3");
        register u32 case35_selection_index asm("r0");
        register u8 *case35_selection_address asm("r1");

        asm volatile("" : "+r"(case35_output_index));
        temp_r2_9 = case35_output_index * 2;
        asm volatile("add %0, %1, %2"
                     : "=r"(case35_output_player)
                     : "r"(temp_r2_9), "r"(case35_players));
        case35_selection_index = var_r8_31;
        asm volatile("add %0, %1, %2"
                     : "=r"(case35_selection_address)
                     : "r"(case35_selection_index),
                       "r"(case35_side_offset));
        case35_selection_address += (u32)case35_selection;
        *case35_output_player =
            case35_saved_players[
                (u32)*case35_selection_address * 2];
        asm volatile("add %0, %0, %1"
                     : "+r"(temp_r2_9)
                     : "r"(case35_slots));
        *(u8 *)temp_r2_9 =
            case35_saved_slots[
                (u32)*case35_selection_address * 2];
    }
    temp_r0_47 = var_r8_31 + 1;
    var_r8_31 = temp_r0_47;
    if ((u32) temp_r0_47 <= 0x23U) {
        goto loop_263;
    }
    }
    {
        register u32 case35_state_base asm("r2") = 0x02034B4C;
        register u32 case35_state_offset asm("r3") = 0x270F;
        register u8 *case35_state asm("r1");
        register u32 case35_state_value asm("r0");
        asm volatile("" : "+r"(case35_state_base),
                      "+r"(case35_state_offset));
        case35_state =
            (u8 *)(case35_state_base + case35_state_offset);
        case35_state_value = 2;
        *case35_state = (u8)case35_state_value;
    }
    case35_zero = 0;
    var_r8_32 = case35_zero;
loop_265:
    {
        register s32 case35_guard_r5 asm("r5");
        register s32 case35_guard_r6 asm("r6");
        asm volatile("" : "=r"(case35_guard_r5), "=r"(case35_guard_r6));
        var_r7_15 = 0;
        asm volatile("" :: "r"(case35_guard_r5), "r"(case35_guard_r6));
    }
    {
        register s32 case35_successor asm("r5") = var_r8_32;

        case35_successor += 1;
        case35_stack[24] = case35_successor;
    }
loop_266:
    CALL_BE9D8_STAGED(var_r8_32, var_r7_15, -1, 0,
                      case35_zero, case35_zero, 0x24,
                      case35_zero, case35_zero, case35_zero);
    var_r7_15 += 1;
    if ((u32) var_r7_15 <= 5U) {
        goto loop_266;
    }
    {
        register u32 case35_exit_state_reload asm("r7") =
            case35_stack[24];
        register u32 case35_exit_state_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case35_exit_state_normalized)
            : "r"(case35_exit_state_reload));
        var_r8_32 = case35_exit_state_normalized;
        if (case35_exit_state_normalized <= 1U) {
            goto loop_265;
        }
    }
    return;
}
case 36: {
    u8 *case36_base;
    s32 case36_row;
    {
        register u32 case36_zero asm("r0") = 0;

        asm volatile("" : "+r"(case36_zero));
        var_r8_33 = case36_zero;
    }
    case36_base = (u8 *)0x02034B4C;
    {
        register s32 case36_row_base asm("r1") = sp6C;
        register s32 case36_side asm("r3") = sp18;
        register s32 case36_row_sum asm("r0");

        asm volatile("" : "+r"(case36_row_base), "+r"(case36_side));
        asm volatile("add %0, %1, %2"
                     : "=r"(case36_row_sum)
                     : "r"(case36_row_base), "r"(case36_side));
        case36_row_sum <<= 3;
        case36_row_sum -= case36_side;
        case36_row = case36_row_sum << 7;
    }
loop_271:
    {
        register u32 case36_index_copy asm("r4") = var_r8_33;
        register u32 case36_record_offset asm("r0");

        case36_record_offset = case36_index_copy << 2;
        case36_record_offset += var_r8_33;
        case36_record_offset <<= 3;
        case36_record_offset -= case36_index_copy;
        case36_record_offset <<= 4;
        case36_record_offset += case36_row;
        case36_record_offset += (u32)case36_base;
        temp_r0_49 = M2C_FIELD(case36_record_offset, u8 *, 0x70);
    }
    if (temp_r0_49 == 0xE) {
        goto block_274;
    }
    if (temp_r0_49 == 0x16) {
        goto block_274;
    }
    temp_r0_50 = var_r8_33 + 1;
    var_r8_33 = temp_r0_50;
    if ((u32) temp_r0_50 <= 5U) {
        goto loop_271;
    }
block_274:
    func_080BE65C(sp18, var_r8_33, -1, 0, 0, 1, 2, 0x12C, 0, 0);
    func_080BE65C(sp18, var_r8_33, -1, 0, 0, 1, 5, 0x1E, 0, 0);
    {
        register u32 case36_state_address asm("r0") = 0x02034B4C;
        register u32 case36_state_offset asm("r5") = 0x27A5;
        register u32 case36_state_value asm("r7");

        asm volatile("" : "+r"(case36_state_address),
                     "+r"(case36_state_offset));
        case36_state_address += case36_state_offset;
        case36_state_value = var_r8_33;
        *(u8 *)case36_state_address = case36_state_value;
    }
    final_state = (s32 *)0x02030558;
    var_r0 = 0x1320;
    goto block_372;
}
case 37: {
    register u8 *case37_first_base asm("r3");
    register u8 *case37_base asm("r2");
    {
        register u32 case37_zero asm("r0") = 0;

        asm volatile("" : "+r"(case37_zero));
        var_r8_34 = case37_zero;
    }
    {
        register s32 case37_row_base asm("r1") = sp6C;
        register s32 case37_side asm("r2") = sp18;
        register s32 case37_row_sum asm("r0");

        asm volatile("" : "+r"(case37_row_base), "+r"(case37_side));
        asm volatile("add %0, %1, %2"
                     : "=r"(case37_row_sum)
                     : "r"(case37_row_base), "r"(case37_side));
        case37_row_sum <<= 3;
        case37_row_sum -= case37_side;
        temp_r1_13 = case37_row_sum << 7;
    }
    case37_first_base = (u8 *)0x02034B4C;
    {
        register u8 *case37_first_address asm("r0");

        asm volatile("add %0, %1, %2"
                     : "=r"(case37_first_address)
                     : "r"(temp_r1_13), "r"(case37_first_base));
        if (M2C_FIELD(case37_first_address, u8 *, 0x70) == 1) {
            goto block_280;
        }
    }
    case37_base = case37_first_base;
    asm volatile("" : "+r"(case37_base) : "r"(case37_first_base));
loop_278:
    temp_r0_51 = var_r8_34 + 1;
    var_r8_34 = temp_r0_51;
    if ((u32) temp_r0_51 > 5U) {
        goto block_280;
    }
    {
        register u32 case37_record_offset asm("r0");
        register u32 case37_index_copy asm("r4");

        case37_record_offset = temp_r0_51 << 2;
        case37_record_offset += var_r8_34;
        case37_record_offset <<= 3;
        case37_index_copy = var_r8_34;
        asm volatile("" : "+r"(case37_index_copy));
        case37_record_offset -= case37_index_copy;
        case37_record_offset <<= 4;
        case37_record_offset += temp_r1_13;
        case37_record_offset += (u32)case37_base;
        if (M2C_FIELD(case37_record_offset, u8 *, 0x70) != 1) {
            goto loop_278;
        }
    }
block_280:
    func_080BE65C(sp18, var_r8_34, -1, 0, 0, 1, 2, 0x12C, 0, 0);
    func_080BE65C(sp18, var_r8_34, -1, 0, 0, 1, 5, 0x1E, 0, 0);
    {
        register u32 case37_state_address asm("r0") = 0x02034B4C;
        register u32 case37_state_offset asm("r5") = 0x27A5;
        register u32 case37_state_value asm("r7");

        asm volatile("" : "+r"(case37_state_address),
                     "+r"(case37_state_offset));
        case37_state_address += case37_state_offset;
        case37_state_value = var_r8_34;
        *(u8 *)case37_state_address = case37_state_value;
    }
    final_state = (s32 *)0x02030558;
    asm volatile("" : "+r"(final_state));
    var_r0 = 0x1320;
    goto block_372;
}
case 38: {
    register volatile s32 *case38_stack asm("sp");
    register s32 case38_sum asm("r1");
    u8 case38_inner_next;
    func_080C2DB0();
    {
        register u32 case38_initial_zero asm("r0") = 0;
        asm volatile("" : "+r"(case38_initial_zero));
        var_r8_35 = case38_initial_zero;
    }
loop_283:
    var_r7_16 = 0;
    {
        register s32 case38_successor asm("r1") = var_r8_35;

        case38_successor += 1;
        case38_stack[24] = case38_successor;
    }
loop_284:
    temp_r4_10 = var_r7_16 + 1;
    {
        register u32 case38_outer_view asm("r3") = var_r8_35;
        if ((func_080C0C54(
                0, sp18, (u8)(temp_r4_10 - case38_outer_view))
             << 0x18) == 0) {
            goto block_288;
        }
    }
    asm volatile(
        "lsl r0, %1, #24\n\t"
        "lsr r0, r0, #24\n\t"
        "mov sl, r0\n\t"
        "lsl %0, r0, #2\n\t"
        "add %0, sl\n\t"
        "lsl %0, %0, #3\n\t"
        "sub %0, %0, r0\n\t"
        "lsl %0, %0, #4"
        : "=r"(case38_sum)
        : "r"(temp_r4_10)
        : "r0", "sl", "cc");
    {
        register s32 case38_row_base asm("r4") = sp6C;
        register s32 case38_row_side asm("r5") = sp18;
        register s32 case38_row_work asm("r0");

        asm volatile("" : "+r"(case38_row_base),
                     "+r"(case38_row_side));
        case38_row_work =
            ((case38_row_base + case38_row_side) * 8) - case38_row_side;
        temp_r0_53 = case38_row_work << 7;
    }
    sp38 = temp_r0_53;
    case38_sum += temp_r0_53;
    {
        register void *case38_record_base asm("r0") =
            (void *)0x02034B4C;
        asm volatile(
            "add %0, %1, %2"
            : "=l"(temp_r5_4)
            : "l"(case38_sum), "l"(case38_record_base)
            : "cc");
    }
    {
        register u32 case38_initial_hp asm("r1") =
            M2C_FIELD(temp_r5_4, u16 *, 0x3A);

        case38_stack[7] = case38_initial_hp;
    }
    temp_r9 = M2C_FIELD(temp_r5_4, u16 *, 6);
    asm volatile(
        "mov r0, #1\n\t"
        "mov r3, r8\n\t"
        "sub r0, r0, r3\n\t"
        "lsl r0, r0, #1\n\t"
        "add r0, r7, r0\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24"
        : "=l"(temp_r6_2)
        :
        : "cc");
    if (M2C_FIELD(temp_r5_4, u8 *, 0) == 0x77) {
        goto block_287;
    }
    {
        register s32 case38_row_reload asm("r0");

        temp_r4_11 = temp_r6_2 * 0x270;
        case38_row_reload = sp38;
        temp_r4_11 += case38_row_reload;
        asm volatile(
            "add %0, %0, %1"
            : "+l"(temp_r4_11)
            : "l"((u32)0x02034B4C),
              "l"(case38_row_reload)
            : "cc");
    }
    M2C_FIELD(temp_r5_4, u8 *, 2) = (u8) M2C_FIELD(temp_r4_11, u8 *, 2);
    func_080ED038(temp_r5_4 + 0x70, temp_r4_11 + 0x70, 0x40);
    {
        register void *case38_copy_dest asm("r0");
        register void *case38_copy_source asm("r1");
        register u32 case38_copy_size asm("r2");

        asm volatile(
            "add %0, %4, #0\n\t"
            "add %0, #176\n\t"
            "add %3, #176\n\t"
            "add %1, %3, #0\n\t"
            "movs %2, #52"
            : "=l"(case38_copy_dest),
              "=l"(case38_copy_source),
              "=l"(case38_copy_size),
              "+l"(temp_r4_11)
            : "l"(temp_r5_4)
            : "cc");
        func_080ED038(case38_copy_dest, case38_copy_source,
                      case38_copy_size);
    }
block_287:
    {
        register u32 case38_index_post asm("r6") = temp_r6_2;
        register s32 case38_call_side asm("r0");
        register u32 case38_call_one asm("r1");
        register u32 case38_call_index asm("r2");
        register void *case38_post_base asm("r3");
        asm volatile(
            "ldr %0, [sp, #24]\n\t"
            "mov %1, sl\n\t"
            "add %2, %3, #0"
            : "=l"(case38_call_side),
              "=l"(case38_call_one),
              "=l"(case38_call_index)
            : "l"(case38_index_post)
            : "memory");
        ((void (*)())func_080C3440)(case38_call_side, case38_call_one,
                                    case38_call_index);
        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "ldr r2, [sp, #56]\n\t"
            "add %0, %0, r2"
            : "=r"(temp_r1_15)
            : "r"(case38_index_post)
            : "cc");
        case38_post_base = (void *)0x02034B4C;
        asm volatile(
            "add %0, %0, %1"
            : "+r"(temp_r1_15)
            : "r"(case38_post_base)
            : "cc");
    }
    {
        register u32 case38_hp_reload asm("r4");
        register u32 case38_hp_sum asm("r0");
        register u32 case38_hp_addend asm("r2");
        register void *case38_hp_record asm("r1") = temp_r1_15;

        asm volatile(
            "ldr %0, [sp, #28]\n\t"
            "lsl %1, %0, #16\n\t"
            "asr %1, %1, #16\n\t"
            "ldrh %2, [%3, #58]\n\t"
            "add %1, %1, %2\n\t"
            "lsl %1, %1, #16\n\t"
            "lsr %1, %1, #16\n\t"
            "str %1, [sp, #28]"
            : "=&l"(case38_hp_reload),
              "=&l"(case38_hp_sum),
              "=&l"(case38_hp_addend)
            : "l"(case38_hp_record)
            : "cc", "memory");
    }
    asm volatile(
        "mov r3, %2\n\t"
        "lsl r0, r3, #16\n\t"
        "asr r0, r0, #16\n\t"
        "ldrh r1, [%1, #6]\n\t"
        "add r0, r0, r1\n\t"
        "lsl r0, r0, #16\n\t"
        "lsr r0, r0, #16\n\t"
        "mov %0, r0"
        : "=r"(temp_r9_2)
        : "r"(temp_r1_15), "r"(temp_r9)
        : "cc");
    {
        register s32 case38_final_arg0 asm("r0") = sp18;
        register s32 case38_final_arg1 asm("r1");
        register s32 case38_final_arg2 asm("r2");

        asm volatile("mov %0, sl" : "=r"(case38_final_arg1));
        case38_final_arg2 = 0x83;
        func_080C34A4_word(case38_final_arg0,
                           case38_final_arg1,
                           case38_final_arg2);
    }
    {
        register s32 case38_factor asm("r1");
        register u32 case38_factor_offset asm("r4");
        register u32 case38_total_source asm("r2");
        register s32 case38_product asm("r0");
        register s32 case38_final_hp asm("r3");
        register s32 case38_divisor asm("r1");

        asm volatile(
            ".syntax unified\n\t"
            "movs %1, #58\n\t"
            "ldrsh %0, [%2, %1]\n\t"
            ".syntax divided"
            : "=l"(case38_factor), "=l"(case38_factor_offset)
            : "l"(temp_r5_4));
        asm volatile(
            "mov %0, %1"
            : "=l"(case38_total_source)
            : "r"(temp_r9_2));
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16\n\t"
            "mul %0, %2"
            : "=&l"(case38_product)
            : "l"(case38_total_source), "l"(case38_factor)
            : "cc");
        case38_final_hp = case38_stack[7];
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16"
            : "=l"(case38_divisor)
            : "l"(case38_final_hp));
        M2C_FIELD(temp_r5_4, u16 *, 6) =
            func_080ECD98_word(case38_product, case38_divisor);
    }
block_288:
    case38_inner_next = var_r7_16 + 3;
    var_r7_16 = case38_inner_next;
    if ((u32) var_r7_16 <= 5U) {
        goto loop_284;
    }
    {
        register u32 case38_exit_state_reload asm("r4") =
            case38_stack[24];
        register u32 case38_exit_state_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case38_exit_state_normalized)
            : "r"(case38_exit_state_reload));
        var_r8_35 = case38_exit_state_normalized;
        if (case38_exit_state_normalized > 1U) {
            goto block_291;
        }
    }
    goto loop_283;
block_291:
    goto block_371;
}
case 39: {
    register volatile s32 *case39_stack asm("sp");
    register s32 case39_sum asm("r1");
    register u32 case39_counter asm("r7");
    register u32 case39_one asm("sl");
    func_080C2DB0();
    {
        register u32 case39_zero asm("r5") = 0;

        asm volatile("" : "+r"(case39_zero));
        var_r8_36 = case39_zero;
    }
    {
        register s32 case39_initial_row_base asm("r7") = sp6C;
        register s32 case39_initial_row_side asm("r1") = sp18;
        register s32 case39_initial_row_work asm("r0");

        asm volatile("" : "+r"(case39_initial_row_base),
                     "+r"(case39_initial_row_side));
        case39_initial_row_work =
            ((case39_initial_row_base + case39_initial_row_side) * 8) -
            case39_initial_row_side;
        sp3C = case39_initial_row_work << 7;
    }
loop_293:
    {
        register u32 case39_call_index asm("r2");
        asm volatile(
            "mov %0, #1\n\t"
            "mov r3, r8\n\t"
            "sub %0, %0, r3\n\t"
            "lsl %0, %0, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case39_call_index)
            : "r"(var_r8_36)
            : "r3", "cc");
        temp_r0_55 =
            func_080C0C54_word(1, sp18, case39_call_index) << 0x18;
    }
    {
        register s32 case39_successor asm("r4") = var_r8_36;

        case39_successor += 1;
        asm volatile("str %0, [sp, #96]"
                     :
                     : "r"(case39_successor)
                     : "memory");
    }
    asm volatile("" : "=m"(sp60));
    if (temp_r0_55 != 0) {
        goto block_295;
    }
    goto block_305;
block_295:
    {
        register u32 case39_one_seed asm("r5") = 1;

        asm volatile("" : "+r"(case39_one_seed));
        case39_one = case39_one_seed;
    }
    {
        register s32 case39_row asm("r7") = sp3C;
        register s32 case39_offset asm("r1") = 0x270;
        register void *case39_record asm("r0");
        asm volatile("" : "+r"(case39_row), "+r"(case39_offset));
        case39_record = case39_row + case39_offset;
        {
            register s32 case39_base asm("r2") = 0x02034B4C;
            asm volatile("" : "+r"(case39_record), "+r"(case39_base));
            temp_r0_56 = case39_record + case39_base;
        }
    }
    {
        register u32 case39_initial_hp asm("r3") =
            M2C_FIELD(temp_r0_56, u16 *, 0x3A);
        case39_stack[7] = case39_initial_hp;
    }
    var_r9 = M2C_FIELD(temp_r0_56, u16 *, 6);
    case39_counter = 0;
    {
        register s32 case39_row_base asm("r4") = sp6C;
        register s32 case39_row_side asm("r5") = sp18;
        register s32 case39_row_work asm("r0");
        asm volatile("" : "+r"(case39_row_base), "+r"(case39_row_side));
        case39_row_work =
            ((case39_row_base + case39_row_side) * 8) - case39_row_side;
        sp40 = case39_row_work;
        sp44 = case39_row_work << 7;
    }
loop_296:
    if (case39_counter != 2) {
        goto block_298;
    }
    case39_counter = 3;
block_298:
    temp_r1_16 = case39_counter + 1;
    temp_r6_3 = temp_r1_16 - var_r8_36;
    case39_stack[25] = temp_r1_16;
    {
        register u32 case39_primary_scale asm("r3");
        asm volatile("mov %0, %1\n\tlsl %0, %0, #2"
                     : "=l"(case39_primary_scale)
                     : "r"(case39_one));
        case39_stack[30] = case39_primary_scale;
    }
    asm volatile("" : "+m"(sp78));
    if (temp_r6_3 == case39_one) {
        goto block_303;
    }
    {
        register u32 case39_primary_scale asm("r3");
        register u32 case39_primary_base asm("r1") = 0x02034B4C;
        register void *case39_primary_work asm("r0");
        asm volatile(
            "add %0, %2, #0\n\t"
            "add %0, sl\n\t"
            "lsl %0, %0, #3\n\t"
            "mov %1, sl\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4"
            : "=&l"(case39_primary_work), "=l"(temp_r4_12)
            : "l"(case39_primary_scale)
            : "cc");
        {
            register s32 case39_primary_row_reload asm("r5");

            asm volatile(
                "ldr %0, [sp, #64]\n\t"
                "lsl %1, %0, #7"
                : "=r"(case39_primary_row_reload),
                  "=r"(temp_r2_10)
                :
                : "memory");
        }
        asm volatile(
            "add %0, %0, %2\n\t"
            "add %1, %0, %3"
            : "+l"(case39_primary_work), "+l"(temp_r4_12)
            : "l"(temp_r2_10), "l"(case39_primary_base)
            : "cc");
    }
    if (M2C_FIELD(temp_r4_12, u8 *, 0) == 0x77) {
        goto block_302;
    }
    temp_r0_59 = (temp_r6_3 * 0x270) + temp_r2_10;
    asm volatile("add %0, %1, r1"
                 : "=&l"(temp_r5_5)
                 : "l"(temp_r0_59));
    if (M2C_FIELD(temp_r5_5, u8 *, 0) != 0x77) {
        goto block_302;
    }
    M2C_FIELD(temp_r4_12, u8 *, 2) = (u8) M2C_FIELD(temp_r5_5, u8 *, 2);
    func_080ED038(temp_r4_12 + 0x70, temp_r5_5 + 0x70, 0x40);
    func_080ED038(temp_r4_12 + 0xB0, temp_r5_5 + 0xB0, 0x34);
block_302:
    func_080C3440_word(sp18, case39_one, temp_r6_3);
    temp_r0_60 = (void *)(temp_r6_3 * 0x270);
    asm volatile(
        "ldr r7, [sp, #68]\n\t"
        "add %0, %0, r7"
        : "+l"(temp_r0_60)
        :
        : "memory");
    {
        register u32 case39_post_base asm("r1") = 0x02034B4C;

        asm volatile(
            "add %0, %0, %1"
            : "+l"(temp_r0_60)
            : "l"(case39_post_base)
            : "cc");
    }
    asm volatile(
        "ldr r2, [sp, #28]\n\t"
        "lsl r1, r2, #16\n\t"
        "asr r1, r1, #16\n\t"
        "ldrh r3, [%0, #58]\n\t"
        "add r1, r1, r3\n\t"
        "lsl r1, r1, #16\n\t"
        "lsr r1, r1, #16\n\t"
        "str r1, [sp, #28]"
        :
        : "r"(temp_r0_60)
        : "cc", "memory");
    asm volatile(
        "mov r4, %0\n\t"
        "lsl r1, r4, #16\n\t"
        "asr r1, r1, #16\n\t"
        "ldrh r0, [%1, #6]\n\t"
        "add r1, r1, r0\n\t"
        "lsl r1, r1, #16\n\t"
        "lsr r1, r1, #16\n\t"
        "mov %0, r1"
        : "+r"(var_r9)
        : "r"(temp_r0_60)
        : "cc");
block_303:
    {
        register u32 case39_counter_reload asm("r5");
        register u32 case39_counter_normalized asm("r0");

        asm volatile(
            "ldr %0, [sp, #100]\n\t"
            "lsl %1, %0, #24\n\t"
            "lsr %2, %1, #24"
            : "=r"(case39_counter_reload),
              "=r"(case39_counter_normalized),
              "=r"(case39_counter)
            :
            : "memory");
    }
    if (case39_counter <= 4U) {
        goto loop_296;
    }
    {
        func_080C34A4_word(sp18, case39_one, 0x80);
        asm volatile(
            "ldr %0, [sp, #120]\n\t"
            "add %0, sl\n\t"
            "lsl %0, %0, #3\n\t"
            "mov r7, sl\n\t"
            "sub %0, %0, r7\n\t"
            "lsl %0, %0, #4\n\t"
            "ldr r0, [sp, #60]\n\t"
            "add %0, %0, r0"
            : "=r"(temp_r4_13)
            : "r"(case39_one)
            : "r0", "r7", "cc", "memory");
        {
            register u32 case39_final_base asm("r1") =
                0x02034B4C;

            asm volatile(
                "add %0, %0, %1"
                : "+r"(temp_r4_13)
                : "r"(case39_final_base)
                : "cc");
        }
    }
    {
        register s32 case39_factor asm("r1");
        register u32 case39_factor_offset asm("r2");
        register u32 case39_total_source asm("r3");
        register s32 case39_product asm("r0");
        register s32 case39_final_hp asm("r5");
        register s32 case39_divisor asm("r1");

        asm volatile(
            ".syntax unified\n\t"
            "movs %1, #58\n\t"
            "ldrsh %0, [%2, %1]\n\t"
            ".syntax divided"
            : "=l"(case39_factor), "=l"(case39_factor_offset)
            : "l"(temp_r4_13));
        asm volatile(
            "mov %0, %1"
            : "=l"(case39_total_source)
            : "r"(var_r9));
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16\n\t"
            "mul %0, %2"
            : "=&l"(case39_product)
            : "l"(case39_total_source), "l"(case39_factor)
            : "cc");
        case39_final_hp = case39_stack[7];
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16"
            : "=l"(case39_divisor)
            : "l"(case39_final_hp));
        M2C_FIELD(temp_r4_13, u16 *, 6) =
            func_080ECD98_word(case39_product, case39_divisor);
    }
block_305:
    {
        register u32 case39_exit_state_reload asm("r7");
        register u32 case39_exit_state_normalized asm("r0");

        asm volatile("ldr %0, [sp, #96]"
                     : "=r"(case39_exit_state_reload)
                     :
                     : "memory");
        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case39_exit_state_normalized)
            : "r"(case39_exit_state_reload));
        var_r8_36 = case39_exit_state_normalized;
        if (case39_exit_state_normalized > 1U) {
            goto block_307;
        }
    }
    goto loop_293;
block_307:
    goto block_371;
}
case 40: {
    register volatile s32 *case40_stack asm("sp");
    register s32 case40_sum asm("r1");
    register u32 case40_counter asm("r7");
    register u32 case40_one asm("sl");
    register s32 case40_row_side asm("r5");
    func_080C2DB0();
    {
        register s32 case40_state_seed asm("r0") = 0;

        asm volatile("" : "+r"(case40_state_seed));
        var_r8_37 = case40_state_seed;
    }
    {
        register s32 case40_row_base asm("r1") = sp6C;
        register s32 case40_row_side asm("r2") = sp18;
        register s32 case40_row asm("r0");
        asm volatile("" : "+r"(case40_row_base), "+r"(case40_row_side));
        case40_row = case40_row_base + case40_row_side;
        case40_row = (case40_row * 8) - case40_row_side;
        case40_row <<= 7;
        sp48 = case40_row;
    }
loop_309:
    {
        register u32 case40_side_delta asm("r2") = 1;
        register u32 case40_outer_view asm("r3");

        case40_outer_view = var_r8_37;
        asm volatile("" : "+r"(case40_outer_view));
        case40_side_delta -= case40_outer_view;
        temp_r0_62 =
            func_080C0C54(2, sp18, (u8)case40_side_delta) << 0x18;
    }
    {
        register s32 case40_successor asm("r4") = var_r8_37;

        case40_successor += 1;
        case40_stack[24] = case40_successor;
    }
    if (temp_r0_62 != 0) {
        goto block_311;
    }
    goto block_321;
block_311:
    {
        register u32 case40_one_seed asm("r5") = 1;

        case40_one = case40_one_seed;
    }
    {
        register s32 case40_initial_row asm("r7") = sp48;
        register s32 case40_initial_offset asm("r1") = 0x270;
        register void *case40_initial_record asm("r0");

        asm volatile("" : "+r"(case40_initial_row),
                     "+r"(case40_initial_offset));
        case40_initial_record = case40_initial_row + case40_initial_offset;
        {
            register u32 case40_initial_base asm("r2") = 0x02034B4C;

            asm volatile("" : "+r"(case40_initial_record),
                         "+r"(case40_initial_base));
            case40_initial_record =
                (void *)((u32)case40_initial_record + case40_initial_base);
        }
        {
            register u32 case40_initial_hp asm("r3") =
                M2C_FIELD(case40_initial_record, u16 *, 0x3A);

            case40_stack[7] = case40_initial_hp;
        }
        var_r9_2 = M2C_FIELD(case40_initial_record, u16 *, 6);
    }
    case40_counter = 0;
    {
        register s32 case40_row_base asm("r4") = sp6C;
        register s32 case40_row_work asm("r0");

        case40_row_side = sp18;
        asm volatile("" : "+r"(case40_row_base),
                     "+r"(case40_row_side));
        case40_row_work =
            ((case40_row_base + case40_row_side) * 8) - case40_row_side;
        sp4C = case40_row_work;
        sp50 = case40_row_work << 7;
    }
loop_312:
    if (case40_counter != 2) {
        goto block_314;
    }
    case40_counter = 3;
block_314:
    temp_r1_17 = case40_counter + 1;
    temp_r6_4 = temp_r1_17 - var_r8_37;
    asm volatile("" : : "r"(case40_row_side));
    case40_stack[25] = temp_r1_17;
    {
        register u32 case40_primary_scale asm("r3");
        asm volatile("mov %0, sl\n\tlsl %0, %0, #2"
                     : "=l"(case40_primary_scale));
        case40_stack[30] = case40_primary_scale;
    }
    if (temp_r6_4 == case40_one) {
        goto block_319;
    }
    {
        register u32 case40_primary_scale asm("r3");
        register u32 case40_primary_base asm("r1") = 0x02034B4C;
        register void *case40_primary_work asm("r0");
        asm volatile(
            "add %0, %2, #0\n\t"
            "add %0, sl\n\t"
            "lsl %0, %0, #3\n\t"
            "mov %1, sl\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4"
            : "=&l"(case40_primary_work), "=l"(temp_r4_14)
            : "l"(case40_primary_scale)
            : "cc");
        {
            register s32 case40_primary_row_reload asm("r5");

            asm volatile(
                "ldr %0, [sp, #76]\n\t"
                "lsl %1, %0, #7"
                : "=r"(case40_primary_row_reload),
                  "=r"(temp_r2_11)
                :
                : "memory");
        }
        asm volatile(
            "add %0, %0, %2\n\t"
            "add %1, %0, %3"
            : "+l"(case40_primary_work), "+l"(temp_r4_14)
            : "l"(temp_r2_11), "l"(case40_primary_base)
            : "cc");
    }
    if (M2C_FIELD(temp_r4_14, u8 *, 0) == 0x7E) {
        goto block_318;
    }
    temp_r0_66 = (temp_r6_4 * 0x270) + temp_r2_11;
    asm volatile("add %0, %1, r1"
                 : "=&l"(temp_r5_6)
                 : "l"(temp_r0_66));
    if (M2C_FIELD(temp_r5_6, u8 *, 0) != 0x7E) {
        goto block_318;
    }
    M2C_FIELD(temp_r4_14, u8 *, 2) = (u8) M2C_FIELD(temp_r5_6, u8 *, 2);
    func_080ED038(temp_r4_14 + 0x70, temp_r5_6 + 0x70, 0x40);
    func_080ED038(temp_r4_14 + 0xB0, temp_r5_6 + 0xB0, 0x34);
block_318:
    {
        register u32 case40_call_player asm("r0") = sp18;
        register u32 case40_call_one asm("r1");
        asm volatile("mov %0, %1"
                     : "=l"(case40_call_one)
                     : "r"(case40_one));
        func_080C3440_word(case40_call_player, case40_call_one, temp_r6_4);
    }
    {
        register void *case40_secondary_record asm("r0");

        case40_secondary_record = (void *)(temp_r6_4 * 0x270);
        {
            register s32 case40_secondary_row asm("r7") = sp50;

            case40_secondary_record =
                (void *)((u32)case40_secondary_record +
                         case40_secondary_row);
        }
        {
            register u32 case40_secondary_base asm("r1") = 0x02034B4C;

            asm volatile("" : "+r"(case40_secondary_base));
            case40_secondary_record =
                (void *)((u32)case40_secondary_record +
                         case40_secondary_base);
        }
        {
            register u32 case40_hp_reload asm("r2") =
                case40_stack[7];
            register u32 case40_other_hp asm("r3");

            case40_sum = (s16)case40_hp_reload;
            case40_other_hp =
                M2C_FIELD(case40_secondary_record, u16 *, 0x3A);
            asm volatile("" : "+r"(case40_other_hp));
            case40_sum += case40_other_hp;
            case40_sum = (u32)case40_sum << 16;
            case40_sum = (u32)case40_sum >> 16;
            case40_stack[7] = case40_sum;
        }
        {
            register u32 case40_total_reload asm("r4");

            asm volatile("mov %0, %1"
                         : "=l"(case40_total_reload)
                         : "r"(var_r9_2));
            case40_sum = (s16)case40_total_reload;
            case40_sum +=
                M2C_FIELD(case40_secondary_record, u16 *, 6);
            case40_sum = (u32)case40_sum << 16;
            case40_sum = (u32)case40_sum >> 16;
            var_r9_2 = case40_sum;
        }
    }
block_319:
    {
        register u32 case40_counter_reload asm("r5") =
            case40_stack[25];
        register u32 case40_counter_shift asm("r0");

        case40_counter_shift = case40_counter_reload << 24;
        case40_counter = case40_counter_shift >> 24;
        if (case40_counter <= 4U) {
            goto loop_312;
        }
    }
    func_080C34A4_word(sp18, case40_one, 0x81);
    {
        register u32 case40_final_work asm("r4") =
            case40_stack[30];
        register s32 case40_factor asm("r1");
        register u32 case40_factor_offset asm("r2");
        register u32 case40_total_source asm("r3");
        register s32 case40_product asm("r0");

        case40_final_work += case40_one;
        case40_final_work <<= 3;
        {
            register u32 case40_final_one asm("r7") =
                case40_one;

            case40_final_work -= case40_final_one;
        }
        case40_final_work <<= 4;
        {
            register u32 case40_final_row asm("r0") = sp48;

            case40_final_work += case40_final_row;
        }
        {
            register u32 case40_final_base asm("r1") = 0x02034B4C;

            asm volatile("" : "+r"(case40_final_base));
            case40_final_work += case40_final_base;
        }
        asm volatile(
            ".syntax unified\n\t"
            "movs %1, #58\n\t"
            "ldrsh %0, [%2, %1]\n\t"
            ".syntax divided"
            : "=l"(case40_factor), "=l"(case40_factor_offset)
            : "l"(case40_final_work));
        asm volatile("mov %0, %1"
                     : "=l"(case40_total_source)
                     : "r"(var_r9_2));
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16\n\t"
            "mul %0, %2"
            : "=&l"(case40_product)
            : "l"(case40_total_source), "l"(case40_factor)
            : "cc");
        {
            register u32 case40_final_hp_reload asm("r5") =
                case40_stack[7];
            register s32 case40_divisor asm("r1");

            case40_divisor = (s16)case40_final_hp_reload;
            M2C_FIELD(case40_final_work, u16 *, 6) =
                func_080ECD98(case40_product, case40_divisor);
        }
    }
block_321:
    {
        register u32 case40_exit_state_reload asm("r7") =
            case40_stack[24];
        register u32 case40_exit_state_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case40_exit_state_normalized)
            : "r"(case40_exit_state_reload));
        var_r8_37 = case40_exit_state_normalized;
        if (case40_exit_state_normalized > 1U) {
            goto block_323;
        }
    }
    goto loop_309;
block_323:
    goto block_371;
}
case 41: {
    register volatile s32 *case41_stack asm("sp");
    register s32 case41_sum asm("r1");
    register s32 case41_row asm("r8");
    func_080C2DB0();
    {
        register u32 case41_one_seed asm("r0") = 1;

        asm volatile("" : "+r"(case41_one_seed));
        var_sl = case41_one_seed;
    }
    {
        register s32 case41_base asm("r3");

        case41_base = 0x02034B4C;
        {
            register s32 case41_row_input asm("r2");
            register s32 case41_arg asm("r4");

            case41_row_input = sp6C;
            case41_arg = sp18;
            temp_r1_18 = case41_row_input + case41_arg;
            temp_r1_18 <<= 3;
            temp_r1_18 -= case41_arg;
        }
        temp_r2_12 = temp_r1_18 << 7;
        {
            register s32 case41_offset asm("r5") = 0x270;
            register void *case41_record asm("r0");

            asm volatile("" : "+r"(case41_offset));
            case41_record = temp_r2_12 + case41_offset;
            temp_r0_69 = case41_record + case41_base;
        }
    }
    sp1C = (s32) M2C_FIELD(temp_r0_69, u16 *, 0x3A);
    case41_stack[7] = sp1C;
    var_r9_3 = M2C_FIELD(temp_r0_69, u16 *, 6);
    var_r7_19 = 0;
    sp54 = temp_r1_18;
    case41_row = temp_r2_12;
loop_326:
    case41_copy = var_r7_19;
    {
        register u32 case41_primary_work asm("r0");
        register u32 case41_primary_base asm("r1");
        register u32 case41_primary_one asm("r2");
        register u32 case41_primary_row asm("r3");
        register u32 case41_secondary_work asm("r0");
        register u8 *case41_secondary_record asm("r5");

        case41_primary_work = var_sl;
        asm volatile("" : "+r"(case41_primary_work));
        case41_primary_work <<= 2;
        case41_stack[30] = case41_primary_work;
        if (var_r7_19 == var_sl) {
            goto block_331;
        }
        case41_primary_base = 0x02034B4C;
        case41_primary_work += var_sl;
        case41_primary_work <<= 3;
        case41_primary_one = var_sl;
        asm volatile("" : "+r"(case41_primary_one));
        case41_primary_work -= case41_primary_one;
        case41_primary_work <<= 4;
        case41_primary_row = sp54;
        temp_r2_13 = case41_primary_row << 7;
        case41_primary_work += temp_r2_13;
        temp_r4_16 = (void *)(case41_primary_work + case41_primary_base);
        if (M2C_FIELD(temp_r4_16, u8 *, 0) == 0x77) {
            goto block_330;
        }
        case41_secondary_work = var_r7_19 << 2;
        case41_secondary_work += var_r7_19;
        case41_secondary_work <<= 3;
        case41_secondary_work -= var_r7_19;
        case41_secondary_work <<= 4;
        case41_secondary_work += temp_r2_13;
        case41_secondary_record =
            (u8 *)(case41_secondary_work + case41_primary_base);
        if (M2C_FIELD(case41_secondary_record, u8 *, 0) != 0x77) {
            goto block_330;
        }
        M2C_FIELD(temp_r4_16, u8 *, 2) =
            (u8) M2C_FIELD(case41_secondary_record, u8 *, 2);
        func_080ED038(temp_r4_16 + 0x70,
                     case41_secondary_record + 0x70, 0x40);
        func_080ED038(temp_r4_16 + 0xB0,
                     case41_secondary_record + 0xB0, 0x34);
    }
block_330:
    func_080C3440_word(sp18, var_sl, case41_copy);
    {
        register u32 case41_post_work asm("r0");
        register u32 case41_post_base asm("r4");
        register s32 case41_hp_reload asm("r5");

        case41_post_work = case41_copy << 2;
        case41_post_work += case41_copy;
        case41_post_work <<= 3;
        case41_post_work -= case41_copy;
        case41_post_work <<= 4;
        case41_post_work += case41_row;
        case41_post_base = 0x02034B4C;
        asm volatile("" : "+r"(case41_post_base));
        case41_post_work += case41_post_base;
        asm volatile(
            "ldr r5, [sp, #28]\n\t"
            "lsl r1, r5, #16\n\t"
            "asr r1, r1, #16\n\t"
            "ldrh r2, [%1, #58]\n\t"
            "add r1, r1, r2\n\t"
            "lsl r1, r1, #16\n\t"
            "lsr r1, r1, #16\n\t"
            "str r1, [sp, #28]\n\t"
            "mov r3, %0\n\t"
            "lsl r1, r3, #16\n\t"
            "asr r1, r1, #16\n\t"
            "ldrh %1, [%1, #6]\n\t"
            "add r1, r1, %1\n\t"
            "lsl r1, r1, #16\n\t"
            "lsr r1, r1, #16\n\t"
            "mov %0, r1"
            : "+r"(var_r9_3), "+r"(case41_post_work)
            :
            : "r1", "r2", "r3", "r5", "cc", "memory");
    }
block_331:
    var_r7_19 += 1;
    if ((u32) var_r7_19 <= 5U) {
        goto loop_326;
    }
    func_080C34A4_word(sp18, var_sl, 0x82);
    {
        register u32 case41_final_work asm("r4");
        register s32 case41_product asm("r0");

        {
            register u32 case41_final_base asm("r1");
            register u32 case41_final_one asm("r5");
            register u32 case41_final_row_saved asm("r7");
            register u32 case41_final_arg asm("r2");
            register u32 case41_final_row_work asm("r0");

            case41_final_base = 0x02034B4C;
            case41_final_work = case41_stack[30];
            case41_final_work += var_sl;
            case41_final_work <<= 3;
            case41_final_one = var_sl;
            asm volatile("" : "+r"(case41_final_one));
            case41_final_work -= case41_final_one;
            case41_final_work <<= 4;
            case41_final_row_saved = sp6C;
            case41_final_arg = sp18;
            case41_final_row_work =
                case41_final_row_saved + case41_final_arg;
            case41_final_row_work <<= 3;
            case41_final_row_work -= case41_final_arg;
            case41_final_row_work <<= 7;
            case41_final_work += case41_final_row_work;
            case41_final_work += case41_final_base;
        }
        {
            register s32 case41_factor asm("r1");
            register u32 case41_factor_offset asm("r3");
            register u32 case41_total_source asm("r5");

            asm volatile(
                ".syntax unified\n\t"
                "movs %1, #58\n\t"
                "ldrsh %0, [%2, %1]\n\t"
                ".syntax divided"
                : "=l"(case41_factor), "=l"(case41_factor_offset)
                : "l"(case41_final_work));
            asm volatile("mov %0, %1"
                         : "=l"(case41_total_source)
                         : "r"(var_r9_3));
            asm volatile(
                "lsl %0, %1, #16\n\t"
                "asr %0, %0, #16\n\t"
                "mul %0, %2"
                : "=&l"(case41_product)
                : "l"(case41_total_source), "l"(case41_factor)
                : "cc");
        }
        {
            register u32 case41_final_hp_reload asm("r7") =
                case41_stack[7];
            register s32 case41_divisor asm("r1");

            asm volatile(
                "lsl %0, %1, #16\n\t"
                "asr %0, %0, #16"
                : "=l"(case41_divisor)
                : "l"(case41_final_hp_reload));
            M2C_FIELD(case41_final_work, u16 *, 6) =
                func_080ECD98_word(case41_product, case41_divisor);
        }
    }
    goto block_371;
}
case 42: {
    u32 case42_index4;
    u32 case42_kind;
    s32 case42_sum;
    register volatile s32 *case42_stack asm("sp");
    register u32 case42_one asm("sl");
    register u32 case42_post_hp_field asm("r5");
    func_080C2DB0();
    {
        register u32 case42_initial_five asm("r0") = 5;

        asm volatile("" : "+r"(case42_initial_five));
        var_r8_38 = case42_initial_five;
    }
    {
        register s32 case42_row_base asm("r1") = sp6C;
        register s32 case42_row_side asm("r2") = sp18;
        register s32 case42_row_work asm("r0");

        case42_row_work = case42_row_base + case42_row_side;
        case42_row_work <<= 3;
        case42_row_work -= case42_row_side;
        temp_r6_5 = case42_row_work << 7;
    }
loop_334:
    temp_r0_73 = func_080C0C54_word(6, 0, var_r8_38) << 0x18;
    temp_r3_3 = var_r8_38 - 1;
    case42_stack[23] = temp_r3_3;
    asm volatile(
        ".macro bne target\n\t"
        "beq 991f\n\t"
        ".endm\n\t"
        ".macro b target\n\t"
        ".endm");
    if (temp_r0_73 == 0) {
        goto block_342;
    }
    asm volatile(".purgem bne\n\t.purgem b");
    {
        register u32 case42_one_seed asm("r4");
        register s32 case42_offset asm("r5");
        register u32 case42_base asm("r7");
        register void *case42_record asm("r0");
        register s32 case42_initial_hp asm("r1");
        register u32 case42_initial_index4 asm("r1");
        register u32 case42_current asm("r2");
        register u32 case42_test_address asm("r0");

        asm volatile("mov %0, #1" : "=r"(case42_one_seed));
        case42_one = case42_one_seed;
        case42_offset = 0x270;
        case42_record = temp_r6_5 + case42_offset;
        case42_base = 0x02034B4C;
        temp_r0_74 = case42_record + case42_base;
        case42_initial_hp = M2C_FIELD(temp_r0_74, u16 *, 0x3A);
        case42_stack[7] = case42_initial_hp;
        var_r9_4 = M2C_FIELD(temp_r0_74, u16 *, 6);
        case42_current = var_r8_38;
        case42_initial_index4 = case42_current << 2;
        case42_test_address = case42_initial_index4 + case42_current;
        case42_test_address <<= 3;
        case42_test_address -= case42_current;
        case42_test_address <<= 4;
        case42_test_address += temp_r6_5;
        case42_test_address += case42_base;
        case42_kind = (u8)(
            M2C_FIELD(case42_test_address, u8 *, 0) - 0x77);
        case42_index4 = case42_initial_index4;
    }
    if (case42_kind > 1U) {
        goto block_341;
    }
    {
    register u32 case42_inner_index asm("r7");
    register u32 case42_inner_normalized asm("r0");

    asm volatile(
        "lsl %0, %2, #24\n\t"
        "lsr %1, %0, #24"
        : "=r"(case42_inner_normalized),
          "=r"(case42_inner_index)
        : "r"(temp_r3_3));

    if (case42_inner_index <= 2U) {
        goto block_341;
    }
    var_r3_2 = 0x02034B4C;
loop_338:
    {
        register u32 case42_address_work asm("r0");

        asm volatile(
            "lsl %0, %2, #2\n\t"
            "add %0, %0, %2\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %2\n\t"
            "lsl %0, %0, #4\n\t"
            "add %0, %0, %3\n\t"
            "add %1, %0, %4"
            : "=&r"(case42_address_work), "=r"(temp_r4_18)
            : "r"(case42_inner_index), "r"(temp_r6_5), "r"(var_r3_2));
    }
    if ((u32) (u8) (M2C_FIELD(temp_r4_18, u8 *, 0) - 0x77) > 1U) {
        goto block_340;
    }
    {
        register s32 case42_call_side asm("r0") = sp18;
        register u32 case42_call_one asm("r1") = case42_one;
        register u32 case42_call_index asm("r2") = case42_inner_index;

        physical_stack[31] = var_r3_2;
        func_080C3440_word(case42_call_side, case42_call_one,
                           case42_call_index);
    }
    {
        asm volatile(
            "ldr r1, [sp, #28]\n\t"
            "lsl r0, r1, #16\n\t"
            "asr r0, r0, #16\n\t"
            "ldrh r2, [%0, #58]\n\t"
            "add r0, r0, r2\n\t"
            "lsl r0, r0, #16\n\t"
            "lsr r0, r0, #16\n\t"
            "str r0, [sp, #28]"
            :
            : "r"(temp_r4_18)
            : "r0", "r1", "r2", "cc", "memory");
    }
    case42_sum = (s16)var_r9_4;
    case42_sum += M2C_FIELD(temp_r4_18, u16 *, 6);
    case42_sum = (u32)case42_sum << 16;
    case42_sum = (u32)case42_sum >> 16;
    var_r9_4 = case42_sum;
    {
        register s32 case42_base_reload asm("r3") = physical_stack[31];

        var_r3_2 = case42_base_reload;
    }
block_340:
    case42_inner_index = (u8)(case42_inner_index - 1);
    if (case42_inner_index > 2U) {
        goto loop_338;
    }
    }
block_341:
    func_080C3440_word(sp18, case42_one, var_r8_38);
    {
        register u32 case42_post_base asm("r3");

        temp_r1_19 =
            (void *)(((((case42_index4 + var_r8_38) * 8)
                        - var_r8_38) * 0x10)
                      + temp_r6_5);
        case42_post_base = 0x02034B4C;
        asm volatile("" : "+r"(case42_post_base));
        temp_r1_19 =
            (void *)((u32)temp_r1_19 + case42_post_base);
    }
    asm volatile(
        "ldr r4, [sp, #28]\n\t"
        "lsl r0, r4, #16\n\t"
        "asr r0, r0, #16\n\t"
        "ldrh %2, [%1, #58]\n\t"
        "add r0, r0, %2\n\t"
        "lsl r0, r0, #16\n\t"
        "lsr r0, r0, #16\n\t"
        "str r0, [sp, #28]\n\t"
        "mov r7, %0\n\t"
        "lsl r0, r7, #16\n\t"
        "asr r0, r0, #16\n\t"
        "ldrh %1, [%1, #6]\n\t"
        "add r0, r0, %1\n\t"
        "lsl r0, r0, #16\n\t"
        "lsr r0, r0, #16\n\t"
        "mov %0, r0"
        : "+r"(var_r9_4), "+r"(temp_r1_19),
          "=r"(case42_post_hp_field)
        :
        : "r0", "r4", "r7", "cc", "memory");
    func_080C34A4_word(sp18, case42_one, 0x84);
    asm volatile(
        "mov r0, sl\n\t"
        "lsl %0, r0, #2\n\t"
        "add %0, sl\n\t"
        "lsl %0, %0, #3\n\t"
        "sub %0, %0, r0\n\t"
        "lsl %0, %0, #4\n\t"
        "add %0, %0, r6"
        : "=r"(temp_r4_19)
        : "r"(case42_one), "r"(temp_r6_5)
        : "r0", "cc");
    {
        register u32 case42_final_base asm("r1") = 0x02034B4C;

        asm volatile(
            "add %0, %0, %1"
            : "+r"(temp_r4_19)
            : "r"(case42_final_base)
            : "cc");
    }
    {
        register s32 case42_factor asm("r1");
        register u32 case42_total_source asm("r3");
        register s32 case42_product asm("r0");
        register s32 case42_final_hp asm("r5");
        register s32 case42_divisor asm("r1");

        asm volatile(
            ".syntax unified\n\t"
            "ldrsh %0, [%3, %4]\n\t"
            ".syntax divided\n\t"
            "mov %1, %5\n\t"
            "lsl %2, %1, #16\n\t"
            "asr %2, %2, #16\n\t"
            "mul %2, %0"
            : "=l"(case42_factor), "=l"(case42_total_source),
              "=&l"(case42_product)
            : "l"(temp_r4_19), "l"((u32)58), "r"(var_r9_4),
              "r"(case42_post_hp_field)
            : "cc");
        case42_final_hp = case42_stack[7];
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16"
            : "=l"(case42_divisor)
            : "l"(case42_final_hp));
        M2C_FIELD(temp_r4_19, u16 *, 6) =
            func_080ECD98_word(case42_product, case42_divisor);
    }
block_342:
    asm volatile("991:");
    {
        register u32 case42_exit_reload asm("r7");
        register u32 case42_exit_normalized asm("r0");

        asm volatile(
            "ldr %0, [sp, #92]\n\t"
            "lsl %1, %0, #24\n\t"
            "lsr %1, %1, #24"
            : "=r"(case42_exit_reload),
              "=r"(case42_exit_normalized)
            :
            : "memory");
        var_r8_38 = case42_exit_normalized;
        if (case42_exit_normalized <= 2U) {
            goto block_344;
        }
    }
    goto loop_334;
block_344:
    goto block_371;
}
case 43: {
    register s32 case43_zero asm("r5");
    {
        register s32 case43_base asm("r0") = 0x02034B4C;
        register s32 case43_offset asm("r2") = 0x27A5;
        register u8 *case43_state asm("r1");
        asm volatile("" : "+r"(case43_base), "+r"(case43_offset));
        case43_state = (u8 *)(case43_base + case43_offset);
        case43_zero = 0;
        *case43_state = 7U;
    }
    {
        register s32 case43_work asm("r0") = 0x94;
        register s32 case43_side asm("r3") = sp18;
        register u8 *case43_record asm("r4") = (u8 *)case43_side;
        register s32 case43_base asm("r7");
        asm volatile("" : "+r"(case43_work), "+r"(case43_side),
            "+r"(case43_record));
        case43_record = (u8 *)((u32)case43_record * case43_work);
        case43_base = 0x02034B4C;
        case43_record += case43_base;
        case43_work = 0xA084;
        case43_record += case43_work;
        func_080C02B4(case43_side, *case43_record);
        func_080BE65C(sp18, *case43_record, -1,
        0, case43_zero, case43_zero, 0x1A, case43_zero, 1, case43_zero);
    }
    {
        register u32 *case43_state_slot asm("r1") = (u32 *)0x02030558;
        register u32 case43_state_value asm("r0") = 0x1300;
        *case43_state_slot = case43_state_value;
    }
    return;
}
case 44: {
    register volatile s32 *case44_stack asm("sp");
    register s32 case44_base asm("r7");
    register s32 case44_sum asm("r0");
    func_080C2DB0();
    var_r8_39 = 0;
    case44_base = 0x02034B4C;
loop_348:
    if ((func_080C0C54_word(4, sp18, var_r8_39) << 0x18) == 0) {
        goto block_350;
    }
    temp_r5_8 = var_r8_39 * 0x270;
    {
        register s32 case44_row_base asm("r3") = sp6C;
        register s32 case44_side asm("r0") = sp18;
        asm volatile("" : "+r"(case44_row_base), "+r"(case44_side));
        asm volatile(
            "add %0, %1, %2\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %2\n\t"
            "lsl %0, %0, #7"
            : "=r"(temp_r4_21)
            : "r"(case44_row_base), "r"(case44_side)
            : "cc");
    }
    asm volatile(
        "add %0, %0, %1\n\t"
        "add %0, %0, %2"
        : "+r"(temp_r5_8)
        : "r"(temp_r4_21), "r"(case44_base)
        : "cc");
    {
        register s32 case44_initial_hp asm("r1") =
            M2C_FIELD(temp_r5_8, u16 *, 0x3A);
        register s32 case44_initial_power asm("r2");
        case44_stack[7] = case44_initial_hp;
        case44_initial_power = M2C_FIELD(temp_r5_8, u16 *, 6);
        temp_r9_4 = case44_initial_power;
    }
    {
        register u32 case44_successor asm("r0") = var_r8_39;
        case44_successor += 3;
        asm volatile(
            "lsl %1, %1, #24\n\t"
            "lsr %0, %1, #24"
            : "=l"(temp_r6_6), "+r"(case44_successor));
    }
    func_080C3440_word(sp18, var_r8_39, temp_r6_6);
    temp_r1_20 = (temp_r6_6 * 0x270) + temp_r4_21 + case44_base;
    asm volatile(
        "ldr r3, [sp, #28]\n\t"
        "lsl r0, r3, #16\n\t"
        "asr r0, r0, #16\n\t"
        "ldrh r4, [%0, #58]\n\t"
        "add r0, r0, r4\n\t"
        "lsl r0, r0, #16\n\t"
        "lsr r0, r0, #16\n\t"
        "str r0, [sp, #28]"
        :
        : "r"(temp_r1_20)
        : "cc", "memory");
    case44_sum = (s16)temp_r9_4;
    case44_sum += M2C_FIELD(temp_r1_20, u16 *, 6);
    case44_sum = (u32)case44_sum << 16;
    case44_sum = (u32)case44_sum >> 16;
    temp_r9_5 = case44_sum;
    func_080C34A4_word(sp18, var_r8_39, 0x47);
    {
        register s32 case44_factor asm("r1");
        register u32 case44_factor_offset asm("r3");
        register u32 case44_total_source asm("r4");
        register s32 case44_product asm("r0");
        register s32 case44_final_hp asm("r2");
        register s32 case44_divisor asm("r1");

        asm volatile(
            ".syntax unified\n\t"
            "movs %1, #58\n\t"
            "ldrsh %0, [%2, %1]\n\t"
            ".syntax divided"
            : "=l"(case44_factor), "=l"(case44_factor_offset)
            : "l"(temp_r5_8));
        asm volatile(
            "mov %0, %1"
            : "=l"(case44_total_source)
            : "r"(temp_r9_5));
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16\n\t"
            "mul %0, %2"
            : "=&l"(case44_product)
            : "l"(case44_total_source), "l"(case44_factor)
            : "cc");
        case44_final_hp = case44_stack[7];
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16"
            : "=l"(case44_divisor)
            : "l"(case44_final_hp));
        M2C_FIELD(temp_r5_8, u16 *, 6) =
            func_080ECD98_word(case44_product, case44_divisor);
    }
block_350:
    temp_r0_76 = var_r8_39 + 1;
    var_r8_39 = temp_r0_76;
    if ((u32) temp_r0_76 <= 2U) {
        goto loop_348;
    }
    goto block_371;
}
case 45:
    func_080C02B4(sp18, 3U);
    {
        register volatile s32 *case45_outgoing asm("sp");
        register s32 case45_neg_one asm("r5") = -1;
        register s32 case45_zero asm("r4") = 0;
        register s32 case45_arg6_seed asm("r3");
        register s32 case45_arg6_saved asm("r8");
        register s32 case45_arg6_second asm("r7");
        register s32 case45_one asm("r6");

        case45_outgoing[0] = case45_zero;
        case45_outgoing[1] = case45_zero;
        case45_arg6_seed = 0x1A;
        asm volatile("mov %0, %1"
                     : "=r"(case45_arg6_saved)
                     : "r"(case45_arg6_seed));
        case45_outgoing[2] = case45_arg6_seed;
        case45_outgoing[3] = case45_zero;
        case45_one = 1;
        case45_outgoing[4] = case45_one;
        case45_outgoing[5] = case45_zero;
        {
            register s32 case45_arg0 asm("r0") = sp18;
            register s32 case45_arg1 asm("r1") = 3;
            register s32 case45_arg2 asm("r2") = case45_neg_one;
            register s32 case45_arg3 asm("r3") = 0;
            func_080BE65C(case45_arg0, case45_arg1,
                          case45_arg2, case45_arg3);
        }
        func_080C02B4(sp18, 5U);
        case45_outgoing[0] = case45_zero;
        case45_outgoing[1] = case45_zero;
        asm volatile("mov %0, r8"
                     : "=r"(case45_arg6_second)
                     : "r"(case45_arg6_saved));
        case45_outgoing[2] = case45_arg6_second;
        case45_outgoing[3] = case45_zero;
        case45_outgoing[4] = case45_one;
        case45_outgoing[5] = case45_zero;
        {
            register s32 case45_arg0 asm("r0") = sp18;
            register s32 case45_arg1 asm("r1") = 5;
            register s32 case45_arg2 asm("r2") = case45_neg_one;
            register s32 case45_arg3 asm("r3") = 0;
            func_080BE65C(case45_arg0, case45_arg1,
                          case45_arg2, case45_arg3);
        }
        case45_outgoing[0] = case45_zero;
        case45_outgoing[1] = case45_zero;
        case45_outgoing[2] = 0x24;
        case45_outgoing[3] = case45_zero;
        case45_outgoing[4] = case45_zero;
        case45_outgoing[5] = case45_zero;
        {
            register s32 case45_arg0 asm("r0") = sp18;
            register s32 case45_arg1 asm("r1") = 1;
            register s32 case45_arg2 asm("r2") = case45_neg_one;
            register s32 case45_arg3 asm("r3") = 0;
            func_080BE9D8(case45_arg0, case45_arg1,
                          case45_arg2, case45_arg3);
        }
    }
    {
        register u32 case45_base asm("r0");
        register u32 case45_dest_offset asm("r2");
        register s32 case45_dest_index asm("r3");
        register s32 case45_source_index asm("r4");
        register u32 case45_source_offset asm("r5");

        case45_base = 0x02034B4C;
        case45_dest_offset = 0x27BE;
        asm volatile("" : "+r"(case45_dest_offset));
        var_r1_3 = (u8 *)(case45_base + case45_dest_offset);
        case45_dest_index = sp18;
        var_r1_3 = (u8 *)(
            (u32)case45_dest_index - (0U - (u32)var_r1_3));
        case45_source_index = sp6C;
        case45_base =
            (u32)case45_source_index - (0U - case45_base);
        case45_source_offset = 0xA07D;
        var_r0_4 = (u8 *)(case45_base + case45_source_offset);
    }
    goto block_356;
case 46:
    func_080C02B4(sp18, 0U);
    {
        register volatile s32 *case46_outgoing asm("sp");
        register s32 case46_neg_one asm("r5") = -1;
        register s32 case46_zero asm("r4") = 0;
        register s32 case46_arg6_seed asm("r7");
        register s32 case46_arg6_saved asm("r8");
        register s32 case46_arg6_first asm("r0");
        register s32 case46_arg6_second asm("r1");
        register s32 case46_one asm("r6");

        case46_outgoing[0] = case46_zero;
        case46_outgoing[1] = case46_zero;
        case46_arg6_seed = 0x1A;
        asm volatile("mov %0, %1"
                     : "=r"(case46_arg6_saved)
                     : "r"(case46_arg6_seed));
        asm volatile("mov %0, r8"
                     : "=r"(case46_arg6_first)
                     : "r"(case46_arg6_saved));
        case46_outgoing[2] = case46_arg6_first;
        case46_outgoing[3] = case46_zero;
        case46_one = 1;
        case46_outgoing[4] = case46_one;
        case46_outgoing[5] = case46_zero;
        {
            register s32 case46_arg0 asm("r0") = sp18;
            register s32 case46_arg1 asm("r1") = 0;
            register s32 case46_arg2 asm("r2") = case46_neg_one;
            register s32 case46_arg3 asm("r3") = 0;
            func_080BE65C(case46_arg0, case46_arg1,
                          case46_arg2, case46_arg3);
        }
        func_080C02B4(sp18, 2U);
        case46_outgoing[0] = case46_zero;
        case46_outgoing[1] = case46_zero;
        asm volatile("mov %0, r8"
                     : "=r"(case46_arg6_second)
                     : "r"(case46_arg6_saved));
        case46_outgoing[2] = case46_arg6_second;
        case46_outgoing[3] = case46_zero;
        case46_outgoing[4] = case46_one;
        case46_outgoing[5] = case46_zero;
        {
            register s32 case46_arg0 asm("r0") = sp18;
            register s32 case46_arg1 asm("r1") = 2;
            register s32 case46_arg2 asm("r2") = case46_neg_one;
            register s32 case46_arg3 asm("r3") = 0;
            func_080BE65C(case46_arg0, case46_arg1,
                          case46_arg2, case46_arg3);
        }
        case46_outgoing[0] = case46_zero;
        case46_outgoing[1] = case46_zero;
        case46_outgoing[2] = 0x24;
        case46_outgoing[3] = case46_zero;
        case46_outgoing[4] = case46_zero;
        case46_outgoing[5] = case46_zero;
        {
            register s32 case46_arg0 asm("r0") = sp18;
            register s32 case46_arg1 asm("r1") = 4;
            register s32 case46_arg2 asm("r2") = case46_neg_one;
            register s32 case46_arg3 asm("r3") = 0;
            func_080BE9D8(case46_arg0, case46_arg1,
                          case46_arg2, case46_arg3);
        }
    }
    {
        register u32 case46_base asm("r0");
        register u32 case46_dest_offset asm("r2");
        register s32 case46_dest_index asm("r3");
        register s32 case46_source_index asm("r4");
        register u32 case46_source_offset asm("r5");

        case46_base = 0x02034B4C;
        case46_dest_offset = 0x27BE;
        asm volatile("" : "+r"(case46_dest_offset));
        var_r1_3 = (u8 *)(case46_base + case46_dest_offset);
        case46_dest_index = sp18;
        var_r1_3 = (u8 *)(
            (u32)case46_dest_index - (0U - (u32)var_r1_3));
        case46_source_index = sp6C;
        case46_base =
            (u32)case46_source_index - (0U - case46_base);
        case46_source_offset = 0xA07D;
        asm volatile("" : "+r"(case46_source_offset));
        var_r0_4 = (u8 *)(case46_base + case46_source_offset);
    }
    goto block_356;
case 47:
    func_080C02B4(sp18, 4U);
    func_080BE65C(sp18, 4U, -1, 0, 0, 0, 0x1A, 0, 1, 0);
    func_080BE9D8(sp18, 1U, -1, 0, 0, 0, 0x24, 0, 0, 0);
    {
        register u32 case47_base asm("r0");
        register u32 case47_dest_offset asm("r7");
        register s32 case47_dest_index asm("r2");
        register s32 case47_source_index asm("r3");
        register u32 case47_source_offset asm("r4");

        case47_base = 0x02034B4C;
        case47_dest_offset = 0x27BE;
        var_r1_3 = (u8 *)(case47_base + case47_dest_offset);
        case47_dest_index = sp18;
        var_r1_3 = (u8 *)(
            (u32)case47_dest_index - (0U - (u32)var_r1_3));
        case47_source_index = sp6C;
        case47_base =
            (u32)case47_source_index - (0U - case47_base);
        case47_source_offset = 0xA07D;
        asm volatile("" : "+r"(case47_source_offset));
        var_r0_4 = (u8 *)(case47_base + case47_source_offset);
    }
block_356:
    *var_r1_3 = *var_r0_4;
    return;
case 49: {
    register u8 *case49_base asm("r7");
    s32 case49_offset;
    register s32 case49_zero asm("r5");
    register s32 case49_sum asm("r0");
    register s32 case49_row_side asm("r2");
    register void *case49_second_record asm("r1");
    func_080C2DB0();
    case49_zero = 0;
    var_r8_40 = case49_zero;
    asm volatile("" : "+r"(case49_zero));
    case49_base = (u8 *)0x02034B4C;
loop_358:
    if ((func_080C0C54_word(5, sp18, var_r8_40) << 0x18) == 0) {
        goto block_360;
    }
    asm volatile(
        "mov r0, r8\n\t"
        "lsl %0, r0, #2\n\t"
        "add %0, r8\n\t"
        "lsl %0, %0, #3\n\t"
        "sub %0, %0, r0\n\t"
        "lsl %0, %0, #4"
        : "=l"(case49_offset)
        :
        : "cc");
    {
        register s32 case49_row_base asm("r1") = sp6C;
        register s32 case49_row_work asm("r4");

        case49_row_side = sp18;
        asm volatile("" : "+r"(case49_row_base),
                     "+r"(case49_row_side));
        case49_row_work = case49_row_base + case49_row_side;
        asm volatile("" : "+r"(case49_row_work));
        case49_row_work =
            (case49_row_work * 8) - case49_row_side;
        case49_row_work <<= 7;
        temp_r4_22 = case49_row_work;
    }
    temp_r5_9 = case49_offset + temp_r4_22;
    asm volatile(
        "add %0, %0, %1"
        : "+l"(temp_r5_9)
        : "l"(case49_base)
        : "cc");
    {
        register s32 case49_initial_hp asm("r3");
        asm volatile(
            "ldrh %0, [%1, #58]\n\t"
            "str %0, [sp, #28]"
            : "=r"(case49_initial_hp)
            : "r"(temp_r5_9)
            : "memory");
    }
    asm volatile("" : "=r"(sp1C));
    temp_r9_6 = M2C_FIELD(temp_r5_9, u16 *, 6);
    {
        register u32 case49_successor asm("r0") = var_r8_40;
        case49_successor += 3;
        asm volatile(
            "lsl %1, %1, #24\n\t"
            "lsr %0, %1, #24"
            : "=l"(temp_r6_7), "+r"(case49_successor));
    }
    func_080C3440_word(case49_row_side, var_r8_40, temp_r6_7);
    asm volatile(
        "lsl %0, %1, #2\n\t"
        "add %0, %0, %1\n\t"
        "lsl %0, %0, #3\n\t"
        "sub %0, %0, %1\n\t"
        "lsl %0, %0, #4\n\t"
        "add %0, %0, %2\n\t"
        "add %0, %0, %3"
        : "=&r"(case49_second_record)
        : "r"(temp_r6_7), "r"(temp_r4_22), "r"(case49_base)
        : "cc");
    asm volatile("" : : "r"(sp1C));
    asm volatile(
        "ldr r2, [sp, #28]\n\t"
        "lsl r0, r2, #16\n\t"
        "asr r0, r0, #16\n\t"
        "ldrh r3, [%1, #58]\n\t"
        "add r0, r0, r3\n\t"
        "lsl r0, r0, #16\n\t"
        "lsr r0, r0, #16\n\t"
        "str r0, [sp, #28]\n\t"
        "mov r4, %2\n\t"
        "lsl r0, r4, #16\n\t"
        "asr r0, r0, #16\n\t"
        "ldrh %1, [%1, #6]\n\t"
        "add r0, r0, %1\n\t"
        "lsl r0, r0, #16\n\t"
        "lsr r0, r0, #16\n\t"
        "mov %0, r0"
        : "=r"(temp_r9_7), "+r"(case49_second_record)
        : "0"(temp_r9_6)
        : "r0", "r2", "r3", "r4", "cc", "memory");
    asm volatile("" : "=r"(sp1C));
    func_080C34A4_word(sp18, var_r8_40, 0x76);
    {
        register s32 case49_factor asm("r1");
        register u32 case49_factor_offset asm("r0");
        register u32 case49_total_source asm("r2");
        register s32 case49_product asm("r0");
        register s32 case49_final_hp asm("r3");
        register s32 case49_divisor asm("r1");

        asm volatile(
            ".syntax unified\n\t"
            "movs %1, #58\n\t"
            "ldrsh %0, [%2, %1]\n\t"
            ".syntax divided"
            : "=l"(case49_factor), "=l"(case49_factor_offset)
            : "l"(temp_r5_9));
        asm volatile("mov %0, %1"
                     : "=l"(case49_total_source)
                     : "r"(temp_r9_7));
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16\n\t"
            "mul %0, %2"
            : "=&l"(case49_product)
            : "l"(case49_total_source), "l"(case49_factor)
            : "cc");
        case49_final_hp = physical_stack[7];
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16"
            : "=l"(case49_divisor)
            : "l"(case49_final_hp));
        asm volatile("" : : "r"(sp1C));
        M2C_FIELD(temp_r5_9, u16 *, 6) =
            func_080ECD98_word(case49_product, case49_divisor);
    }
block_360:
    temp_r0_77 = var_r8_40 + 1;
    var_r8_40 = temp_r0_77;
    if ((u32) temp_r0_77 <= 2U) {
        goto loop_358;
    }
    goto block_371;
}
case 50: {
    register volatile s32 *case50_stack asm("sp");
    register s32 case50_sum asm("r1");
    u8 case50_inner_next;
    func_080C2DB0();
    {
        register u32 case50_initial_zero asm("r4") = 0;

        asm volatile("" : "+r"(case50_initial_zero));
        var_r8_41 = case50_initial_zero;
    }
loop_363:
    var_r7_21 = 0;
    {
        register u32 case50_successor asm("r5") = var_r8_41;

        case50_successor += 1;
        case50_stack[24] = case50_successor;
    }
loop_364:
    temp_r4_23 = var_r7_21 + 1;
    {
        register u32 case50_outer_view asm("r0") = var_r8_41;

        if ((func_080C0C54(
                7, sp18, (u8)(temp_r4_23 - case50_outer_view))
             << 0x18) == 0) {
            goto block_368;
        }
    }
    {
        register u32 case50_index_work asm("r0");
        register void *case50_record_offset asm("r1");
        register s32 case50_row_work asm("r0");
        register void *case50_record_base asm("r4");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24\n\t"
            "mov sl, %0"
            : "=r"(case50_index_work)
            : "r"(temp_r4_23));
        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, sl\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4"
            : "=&r"(case50_record_offset)
            : "r"(case50_index_work)
            : "cc");
        asm volatile(
            "ldr r2, [sp, #108]\n\t"
            "ldr r3, [sp, #24]\n\t"
            "add %0, r2, r3\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, r3\n\t"
            "lsl %0, %0, #7"
            : "=l"(case50_row_work)
            :
            : "r2", "r3", "cc", "memory");
        sp58 = case50_row_work;
        asm volatile(
            "add %0, %0, %1"
            : "+r"(case50_record_offset)
            : "r"(case50_row_work)
            : "cc");
        asm volatile(
            "ldr %0, [pc, #220]"
            : "=r"(case50_record_base));
        asm volatile(
            "add %0, %1, %2"
            : "=l"(temp_r5_10)
            : "l"(case50_record_offset), "l"(case50_record_base)
            : "cc");
    }
    {
        register s32 case50_initial_hp asm("r0");
        asm volatile(
            "ldrh %0, [%1, #58]\n\t"
            "str %0, [sp, #28]"
            : "=r"(case50_initial_hp)
            : "r"(temp_r5_10)
            : "memory");
    }
    temp_r9_8 = M2C_FIELD(temp_r5_10, u16 *, 6);
    asm volatile(
        "mov r0, #1\n\t"
        "mov r2, r8\n\t"
        "sub r0, r0, r2\n\t"
        "lsl r0, r0, #1\n\t"
        "add r0, r7, r0\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24"
        : "=l"(temp_r6_8)
        :
        : "cc");
    if (M2C_FIELD(temp_r5_10, u8 *, 0) == 0x7E) {
        goto block_367;
    }
    {
        register void *case50_alternate_base asm("r0");

        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "ldr r3, [sp, #88]\n\t"
            "add %0, %0, r3"
            : "=&r"(temp_r4_24)
            : "r"(temp_r6_8)
            : "cc");
        asm volatile(
            "ldr %0, [pc, #176]"
            : "=r"(case50_alternate_base));
        asm volatile(
            "add %0, %0, %1"
            : "+r"(temp_r4_24)
            : "r"(case50_alternate_base)
            : "cc");
    }
    M2C_FIELD(temp_r5_10, u8 *, 2) = (u8) M2C_FIELD(temp_r4_24, u8 *, 2);
    func_080ED038(temp_r5_10 + 0x70, temp_r4_24 + 0x70, 0x40);
    {
        register void *case50_copy_dest asm("r0");
        register void *case50_copy_source asm("r1");
        register u32 case50_copy_size asm("r2");

        asm volatile(
            "add %0, %4, #0\n\t"
            "add %0, #176\n\t"
            "add %3, #176\n\t"
            "add %1, %3, #0\n\t"
            "movs %2, #52"
            : "=l"(case50_copy_dest),
              "=l"(case50_copy_source),
              "=l"(case50_copy_size),
              "+l"(temp_r4_24)
            : "l"(temp_r5_10)
            : "cc");
        func_080ED038(case50_copy_dest, case50_copy_source,
                      case50_copy_size);
    }
block_367:
    {
        register u32 case50_index_post asm("r6") = temp_r6_8;
        register s32 case50_call_side asm("r0");
        register u32 case50_call_one asm("r1");
        register u32 case50_call_index asm("r2");
        register void *case50_post_base asm("r3");
        asm volatile(
            "ldr %0, [sp, #24]\n\t"
            "mov %1, sl\n\t"
            "add %2, %3, #0"
            : "=l"(case50_call_side),
              "=l"(case50_call_one),
              "=l"(case50_call_index)
            : "l"(case50_index_post)
            : "memory");
        ((void (*)())func_080C3440)(case50_call_side, case50_call_one,
                                    case50_call_index);
        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4\n\t"
            "ldr r2, [sp, #88]\n\t"
            "add %0, %0, r2"
            : "=r"(temp_r1_23)
            : "r"(case50_index_post)
            : "cc");
        asm volatile(
            "ldr %0, [pc, #116]"
            : "=r"(case50_post_base));
        asm volatile(
            "add %0, %0, %1"
            : "+r"(temp_r1_23)
            : "r"(case50_post_base)
            : "cc");
    }
    {
        register u32 case50_hp_reload asm("r4");
        register u32 case50_hp_sum asm("r0");
        register u32 case50_hp_addend asm("r2");
        register void *case50_hp_record asm("r1") = temp_r1_23;

        asm volatile(
            "ldr %0, [sp, #28]\n\t"
            "lsl %1, %0, #16\n\t"
            "asr %1, %1, #16\n\t"
            "ldrh %2, [%3, #58]\n\t"
            "add %1, %1, %2\n\t"
            "lsl %1, %1, #16\n\t"
            "lsr %1, %1, #16\n\t"
            "str %1, [sp, #28]"
            : "=&l"(case50_hp_reload),
              "=&l"(case50_hp_sum),
              "=&l"(case50_hp_addend)
            : "l"(case50_hp_record)
            : "cc", "memory");
    }
    asm volatile(
        "mov r3, %2\n\t"
        "lsl r0, r3, #16\n\t"
        "asr r0, r0, #16\n\t"
        "ldrh r1, [%1, #6]\n\t"
        "add r0, r0, r1\n\t"
        "lsl r0, r0, #16\n\t"
        "lsr r0, r0, #16\n\t"
        "mov %0, r0"
        : "=r"(temp_r9_9)
        : "r"(temp_r1_23), "r"(temp_r9_8)
        : "cc");
    func_080C34A4(sp18, temp_r0_78, 0x97);
    {
        register s32 case50_factor asm("r1");
        register u32 case50_factor_offset asm("r4");
        register u32 case50_total_source asm("r2");
        register s32 case50_product asm("r0");
        register s32 case50_final_hp asm("r3");
        register s32 case50_divisor asm("r1");

        asm volatile(
            ".syntax unified\n\t"
            "movs %1, #58\n\t"
            "ldrsh %0, [%2, %1]\n\t"
            ".syntax divided"
            : "=l"(case50_factor), "=l"(case50_factor_offset)
            : "l"(temp_r5_10));
        asm volatile(
            "mov %0, %1"
            : "=l"(case50_total_source)
            : "r"(temp_r9_9));
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16\n\t"
            "mul %0, %2"
            : "=&l"(case50_product)
            : "l"(case50_total_source), "l"(case50_factor)
            : "cc");
        case50_final_hp = case50_stack[7];
        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16"
            : "=l"(case50_divisor)
            : "l"(case50_final_hp));
        M2C_FIELD(temp_r5_10, u16 *, 6) =
            func_080ECD98_word(case50_product, case50_divisor);
    }
block_368:
    case50_inner_next = var_r7_21 + 3;
    var_r7_21 = case50_inner_next;
    if ((u32) var_r7_21 <= 5U) {
        goto loop_364;
    }
    {
        register u32 case50_exit_reload asm("r4") = case50_stack[24];
        register u32 case50_exit_normalized asm("r0");

        asm volatile(
            "lsl %0, %1, #24\n\t"
            "lsr %0, %0, #24"
            : "=r"(case50_exit_normalized)
            : "r"(case50_exit_reload));
        var_r8_41 = case50_exit_normalized;
        if (case50_exit_normalized > 1U) {
            goto block_371;
        }
    }
    goto loop_363;
}
block_371:
    asm volatile(
        "ldr %0, [pc, #24]"
        : "=r"(final_state));
    var_r0 = 0x1340;
block_372:
    *final_state = var_r0;
block_373:
    return;
    }
}
