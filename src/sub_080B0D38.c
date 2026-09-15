#include "m2c_prelude.h"
#define NULL ((void *)0)

struct Record24 {
    s32 words[6];
};

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094374();                                /* extern */
s32 func_08094484(s32, M2C_UNK, s32, s32, s32, s32, s32, s32, u32); /* extern */
M2C_UNK func_08094554();                            /* extern */
M2C_UNK func_08095114(s32);                         /* extern */
void *func_0809716C(s32);                           /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, u32);     /* extern */
M2C_UNK func_0809844C(s16, s32, s32, s32, s32, u32, u32); /* extern */
M2C_UNK func_0809844C_wide(s32, s32, s32, s32, s32, u32, u32)
    asm("func_0809844C");
M2C_UNK func_0809844C_stack4(s32, s32, s32, s32)
    asm("func_0809844C");
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_080988C8(s32, M2C_UNK32);              /* extern */
M2C_UNK func_080989EC(s32, void *, s32);            /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_08099F5C(M2C_UNK, s32);                /* extern */
s32 func_0809A35C(u8, u8, s32, s32, s32, s32);      /* extern */
M2C_UNK func_0809AA64(s32, u32, u16, u32);          /* extern */
M2C_UNK func_080AC214(s32, s32);                    /* extern */
M2C_UNK func_080AC468(s32, u8, u8);                 /* extern */
M2C_UNK func_080AC468_wide(s32, s32, u8)
    asm("func_080AC468");
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACBA0(s32);                         /* extern */
M2C_UNK func_080ACBDC(s32, s32);                    /* extern */
M2C_UNK func_080ACDA8(void *, s32, s32);            /* extern */
M2C_UNK func_080B61C8(s32, s32, s32);               /* extern */
M2C_UNK func_080B65A4();                            /* extern */
M2C_UNK func_080B6768(void *);                      /* extern */
u8 func_080E5320(void *, u8);                       /* extern */
M2C_UNK func_080E5880(void *, s32);                 /* extern */
M2C_UNK func_080E596C(s16, s16, void *);            /* extern */
M2C_UNK func_080E596C_wide(s32, s32, void *)
    asm("func_080E596C");
M2C_UNK func_080E59A0(void *, void *);              /* extern */
M2C_UNK func_080E5EFC(u32, s32, s32);               /* extern */
void *func_080E669C();                              /* extern */
M2C_UNK func_080E66B8();                            /* extern */
M2C_UNK func_080E6994(void *, s32, s32, u16, void *); /* extern */
s32 func_080E7B64(u8);                              /* extern */
M2C_UNK func_080ED038(s32, M2C_UNK, s32);           /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080B1284();                            /* static */
M2C_UNK jtbl_080B1C34();                            /* static */

void sub_080B0D38(void) {
    register s32 *sp asm("sp");
    u32 *sp18;
    u32 *sp1C;
    s32 sp20;
    s32 sp24;
    void *sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    u32 sp38;
    u32 sp3C;
    void *sp40;
    void *sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s16 *var_r7;
    register u16 *status_slot_203 asm("r4");
    register u8 *status_address_203 asm("r1");
    register u16 *status_slot_213 asm("r4");
    s16 temp_r1;
    s16 temp_r1_5;
    s16 temp_r1_9;
    s16 temp_r2_2;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;
    s16 var_r3_3;
    s32 *temp_r2_3;
    s32 *temp_r2_5;
    s32 *var_r1_2;
    s32 temp_r0;
    s32 temp_r0_15;
    s32 temp_r0_21;
    s32 temp_r0_7;
    s32 temp_r1_11;
    s32 temp_r1_6;
    s32 temp_r2;
    s32 temp_r2_4;
    register s32 temp_r2_8 asm("r2");
    s32 temp_r2_9;
    register s32 temp_r3 asm("r3");
    s32 temp_r5_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 var_r1;
    s32 var_r1_3;
    s32 var_r2;
    s32 var_r2_2;
    register s32 var_r2_3 asm("r2");
    s32 var_r2_4;
    register s32 var_r4 asm("r4");
    s32 var_sl;
    register u32 temp_r0_10 asm("r0");
    register u32 temp_r0_11 asm("r0");
    register u32 temp_r0_12 asm("r0");
    u16 temp_r0_18;
    u16 temp_r0_25;
    u16 temp_r0_26;
    u16 temp_r0_29;
    u16 temp_r0_4;
    u16 temp_r0_6;
    u16 temp_r1_10;
    u16 temp_r2_7;
    u16 temp_r5_3;
    u16 var_r0_2;
    u16 var_r3;
    u16 var_r6;
    u32 temp_r0_16;
    u32 var_r0;
    u32 var_r0_5;
    u32 var_r0_6;
    u32 var_r5_2;
    u32 var_r5_6;
    u8 temp_r0_14;
    u8 temp_r0_19;
    u8 temp_r0_20;
    u8 temp_r0_22;
    u8 temp_r0_23;
    u8 temp_r0_27;
    u8 temp_r0_28;
    register u32 temp_r0_2 asm("r0");
    u8 temp_r0_31;
    u8 temp_r1_3;
    u8 temp_r1_4;
    u8 var_r5;
    u8 var_r5_3;
    u8 var_r5_4;
    u8 var_r5_5;
    u8 var_r5_7;
    void *temp_r0_13;
    void *temp_r0_17;
    void *temp_r0_24;
    void *temp_r0_30;
    void *temp_r0_3;
    void *temp_r0_5;
    void *temp_r0_8;
    void *temp_r0_9;
    void *temp_r1_2;
    void *temp_r1_7;
    void *temp_r1_8;
    void *temp_r2_6;
    s32 subroutine_arg0;
    register void *var_r9 asm("r9");

    sp44 = func_080E669C();
    var_sl = 0;
loop_1:
    {
        register s32 state_2000 asm("r1") = 0x2000;

        if (var_sl == state_2000) {
            goto state_2000_handler;
        }
        if (var_sl > state_2000) {
            goto above_2000;
        }
    }
    {
        register s32 low_state asm("r2") = var_sl;

        if (low_state == 0x20) {
            goto state_20_handler;
        }
        if (low_state > 0x20) {
            goto above_20;
        }
        if (low_state == 0) {
            goto state_0_handler;
        }
        if (low_state == 0x10) {
            goto state_10_handler;
        }
        goto block_287;
    }
above_20:
    {
        register s32 low_state asm("r3") = var_sl;

        asm volatile("" : "+r"(low_state));
        if (low_state == 0x30) {
            goto state_30_handler;
        }
        if (var_sl == 0x1000) {
            goto state_1000_handler;
        }
        goto block_287;
    }
above_2000:
    {
        register s32 state_3010 asm("r0") = 0x3010;

        if (var_sl == state_3010) {
            goto state_3010_handler;
        }
        if (var_sl > state_3010) {
            goto above_3010;
        }
        if (var_sl == 0x2010) {
            goto state_2010_handler;
        }
        if (var_sl == 0x3000) {
            goto state_3000_handler;
        }
        goto block_287;
    }
above_3010:
    if (var_sl == 0x3020) {
        goto state_3020_handler;
    }
    if (var_sl == 0x4000) {
        goto state_4000_handler;
    }
    goto block_287;

state_0_handler:
        asm volatile(
            "mov r4, #0\n\t"
            "str r4, [sp, #44]\n\t"
            "mov r5, #0\n\t"
            "str r5, [sp, #40]\n\t"
            "mov r7, #16\n\t"
            "mov sl, r7");
        goto block_287;
state_10_handler:
        func_08098BB4(0x08002C13);
        func_080B61C8(0, 0, 0);
        func_080AC214(3, 0x18);
        func_080ACA8C(7, 1, 1);
        goto block_43;
state_20_handler:
        func_08098BB4(0x08002E9B);
        sp48 = func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8, 0x98, 0x343, 0xF, 8, 0U);
        asm volatile(
            "mov r1, #48\n\t"
            "mov sl, r1");
        goto block_287;
state_30_handler: {
        register u8 *record_base_30 asm("r5");
        register u32 record_offset_30 asm("r0");
        register s32 zero_30 asm("r6");

        {
            register u8 *selection_base asm("r0") =
                (u8 *)0x020321A4;
            register u32 selection_offset asm("r2") = (u32)sp28;

            asm volatile("" : "+r"(selection_base));
            asm volatile("add %0, %1, %0"
                         : "+r"(selection_base) : "r"(selection_offset));
            temp_r0_27 = *selection_base;
        }
        sp24 = (s32) temp_r0_27;
        record_offset_30 = temp_r0_27 << 3;
        {
            register u32 r1_birth_guard asm("r1");
            register u32 r2_birth_guard asm("r2");

            asm volatile("" : "=r"(r1_birth_guard),
                              "=r"(r2_birth_guard));
            record_offset_30 -= sp24;
            asm volatile("" : : "r"(r1_birth_guard),
                              "r"(r2_birth_guard));
        }
        record_offset_30 <<= 4;
        record_base_30 = (u8 *)0x020218E8;
        asm volatile("" : "+r"(record_base_30),
            "+r"(record_offset_30));
        var_r9 = record_offset_30 + record_base_30;
        func_080986B4(4);
        {
            register s32 r4_value asm("r4");
            register s32 r7_value asm("r7");
            register s32 four asm("r8");

            func_080981F0(0x081064C0, 0, 4, 0, ({
                zero_30 = 0;
                asm volatile("" : "+r"(zero_30));
                zero_30;
            }));
            func_080981F0(0x081064C8, 0, 4, 0, ({
                r4_value = 2;
                asm volatile("" : "+r"(r4_value));
                r4_value;
            }));
            func_080981F0(0x081064D0, 0, 4, 0, ({
                register s32 outgoing_four asm("r1");

                r7_value = 4;
                asm volatile("" : "+r"(r7_value));
                asm volatile("mov %0, %1"
                    : "=r"(four)
                    : "r"(r7_value));
                asm volatile("mov %0, %1"
                    : "=r"(outgoing_four)
                    : "r"(four));
                outgoing_four;
            }));
            func_080981F0(0x081064D8, 0, 4, 0, ({
                r7_value = 6;
                asm volatile("" : "+r"(r7_value));
                r7_value;
            }));
            r4_value = 0x087EE170;
            asm volatile("" : "+r"(r4_value));
            func_080981F0(M2C_FIELD((M2C_FIELD(var_r9, u16 *, 0x52) * 4), s32 *, r4_value), 0, 4, 2, zero_30);
            func_080981F0(
                M2C_FIELD(
                    (M2C_FIELD(var_r9, u16 *, 0x56) * 4),
                    s32 *, r4_value),
                0, 4, 2, ({
                    register u32 row_two asm("r2") = 2;

                    asm volatile("" : "+r"(row_two));
                    row_two;
                }));
            func_080981F0(
                M2C_FIELD(
                    (M2C_FIELD(var_r9, u16 *, 0x5A) * 4),
                    s32 *, r4_value),
                0, 4, 2, ({
                    register s32 outgoing_four asm("r3");

                    asm volatile("mov %0, r8"
                                 : "=r"(outgoing_four)
                                 : "r"(four));
                    outgoing_four;
                }));
            func_080981F0(M2C_FIELD((M2C_FIELD(var_r9, u16 *, 0x5E) * 4), s32 *, r4_value), 0, 4, 2, r7_value);
        }
        func_080986B4(5);
        {
            register u8 *record_view_30 asm("r4") = var_r9;
            register u32 object_offset asm("r0");
            register u32 field_offset asm("r7");

            object_offset = M2C_FIELD(record_view_30, u8 *, 2);
            asm volatile("" : "+r"(object_offset));
            object_offset <<= 6;
            record_base_30 += object_offset;
            field_offset = 0x5A90;
            asm volatile("" : "+r"(field_offset));
            record_base_30 += field_offset;
            func_080981F0(func_080E7B64(*record_base_30),
                0, 5, 0, zero_30);
            func_080ACBDC(7, sp2C);
            func_08098BB4(0x08002C57);
            sp28 = (void *) *(u8 *)0x0200A880;
            sp2C = (s32) *(u8 *)0x0200A881;
            temp_r0_28 = *(u8 *)0x0200A882;
            if (temp_r0_28 == 1) {
                register u32 flags_value asm("r1");
                register u32 flags_result asm("r0");

                flags_value = M2C_FIELD(record_view_30, u16 *, 4);
                flags_result = 0xFFFE;
                flags_result &= flags_value;
                M2C_FIELD(record_view_30, u16 *, 4) = flags_result;
                flags_value = 2;
                flags_result &= flags_value;
                temp_r0_29 = flags_result;
                if (!temp_r0_29 || (0xFE & M2C_FIELD(record_view_30, u8 *, 3))) {
                    func_080ACBDC(7, sp2C);
                    func_08094554(sp48);
                    func_080B6768(var_r9);
                    temp_r0_31 = *(u8 *)0x02032472;
                    {
                        register s32 state_2000 asm("r2");

                        asm volatile(
                            "mov %0, #128\n\t"
                            "lsl %0, %0, #6"
                            : "=r"(state_2000));
                        var_sl = state_2000;
                    }
                    if (temp_r0_31 != 0) {
                        register s32 state_1000 asm("r3");

                        asm volatile(
                            "mov %0, #128\n\t"
                            "lsl %0, %0, #5"
                            : "=r"(state_1000));
                        var_sl = state_1000;
                    }
                } else {
                    goto block_41;
                }
                goto block_287;
            } else {
                if (temp_r0_28 == 2) {
                    func_08098BB4(0x08002C5B);
                    func_080ACBA0(7);
                    func_08094554(sp48);
                } else {
                    goto block_287;
                }
                goto function_exit;
            }
        }
}
state_1000_handler:
        temp_r0 = func_08094484(0x08105AFC, 0x08105B08, 0, 0x68, 0x50, 0x350, 0xF, 8, 0U);
        sp48 = temp_r0;
        func_08098BB4(0x08002CF0);
        func_08094554(temp_r0);
        if (*(u8 *)0x0200A882 == 1) {
            if (*(u8 *)0x0200A880 == 0) {
                {
                    register u8 *record_view_1000 asm("r4") = var_r9;

                    if (!(2 & M2C_FIELD(record_view_1000, u16 *, 4))) {
                        var_sl = ({
                            register s32 next_state asm("r5");

                            asm volatile(
                                "mov %0, #128\n\t"
                                "lsl %0, %0, #6"
                                : "=r"(next_state));
                            next_state;
                        });
                    } else {
block_41:
                        func_08092E84(0x58);
                        func_08098BB4(0x08002C64);
                    }
                }
            } else {
                var_sl = ({
                    register s32 next_state asm("r7") = 0x4000;

                    asm volatile("" : "+r"(next_state));
                    next_state;
                });
                asm volatile("" : : "i"(0x1078));
            }
        } else {
block_43:
            var_sl = ({
                register s32 next_state asm("r0") = 0x20;

                asm volatile("" : "+r"(next_state));
                next_state;
            });
            asm volatile("" : : "i"(0x43));
        }
        goto block_287;
state_2000_handler: {
        register s32 line_output asm("r4");
        register u32 line_index asm("r5");
        s32 row_table;

        func_08098BB4(0x08002DD0);
        func_08098BB4(0x08002ECD);
        line_index = 0;
        line_output = 0x02030564;
        row_table = 0x087EE170;
        do {
            func_080ED038(line_output, 0x081064E0, 3);
            {
                register s32 first_offset asm("r2") = line_index * 4;
                register u32 first_value asm("r1");
                register u32 first_flag asm("r0");

                first_value =
                    M2C_FIELD((var_r9 + first_offset), u16 *, 0x50);
                first_flag = 1;
                first_flag &= first_value;
                temp_r2 = first_offset;
                if (first_flag) {
                func_08099F5C(line_output, 0x081064E4);
                } else {
                    func_08099F5C(line_output, 0x081061C4);
                }
            }
            {
                register u8 *record_base asm("r2") = var_r9;

                if (2 & M2C_FIELD((record_base + temp_r2), u16 *, 0x50)) {
                    func_08099F5C(0x02030564, 0x0810637C);
                } else {
                    func_08099F5C(0x02030564, 0x081061C4);
                }
            }
            func_08099F5C(line_output, 0x081064E8);
            func_08099F5C(line_output, M2C_FIELD((M2C_FIELD((var_r9 + temp_r2), u16 *, 0x52) * 4), s32 *, row_table));
            func_080988C8(8, line_output);
            {
                register u32 next_index asm("r0") = line_index + 1;

                next_index <<= 24;
                line_index = next_index >> 24;
            }
        } while (line_index <= 3U);
        var_r4 = 0x2010;
        goto block_286;
    }
state_2010_handler:
        temp_r0_21 = func_08094484(0x08105AFC, 0x08105B08, 0, 0x68, 0x50, 0x350, 0xF, 8, 0U);
        sp48 = temp_r0_21;
        func_08098BB4(0x08002DE8);
        func_08094554(temp_r0_21);
        temp_r0_22 = *(u8 *)0x0200A882;
        if (temp_r0_22 == 1) {
            sp30 = (s32) *(u8 *)0x0200A880;
            func_080ACBA0(7);
            var_sl = ({
                register s32 next_state asm("r5");

                asm volatile(
                    "mov %0, #192\n\t"
                    "lsl %0, %0, #6"
                    : "=r"(next_state));
                next_state;
            });
            asm volatile("" : : "i"(0x119A));
        } else if (temp_r0_22 == 2) {
            func_08098BB4(0x08002DEC);
            var_sl = ({
                register s32 next_state asm("r7");

                asm volatile("mov %0, #32"
                             : "=r"(next_state));
                next_state;
            });
            asm volatile("" : : "i"(0x11C6));
        }
        goto block_287;
state_3000_handler:
        func_08098BB4(0x08002DEF);
        {
        register u32 zero_3000 asm("r6");
        register u32 flags_3000 asm("r5");
        {
            register u8 *record_view_3000 asm("r1") = var_r9;

            *(s32 *)0x02033F3C = func_0809A35C(
                record_view_3000[0], record_view_3000[1], 3, 1, ({
                    zero_3000 = 0;
                    asm volatile("" : "+r"(zero_3000));
                    zero_3000;
                }), 0x02002880);
        }
        {
            register s16 *line_3000 asm("r4") = (s16 *)0x02030564;
            register u32 header_3000 asm("r0") = 0x101;

            asm volatile("" : "+r"(header_3000));
            line_3000[0] = header_3000;
            line_3000[1] = zero_3000;
            func_08099F5C((s32)line_3000, 0x081064EC);
            flags_3000 = 1;
            asm volatile("" : "+r"(flags_3000));
            line_3000[14] = flags_3000;
            line_3000[15] = zero_3000;
            func_080988C8(0, line_3000);
        }
        {
            register s32 mode asm("r3");
            register u8 *record asm("r4");
            register u8 *address asm("r0");

            asm volatile("ldr %0, [sp, #48]"
                         : "=r"(mode)
                         : "g"(sp30)
                         : "memory");
            temp_r2_8 = mode << 2;
            asm volatile("mov %0, r9"
                         : "=r"(record));
            asm volatile("add %0, %1, %2"
                         : "=r"(address)
                         : "r"(record), "r"(temp_r2_8)
                         : "cc");
            temp_r1_10 = M2C_FIELD(address, u16 *, 0x50);
        }
        flags_3000 &= temp_r1_10;
        {
        register u32 second_flag_3000 asm("r0") = 2;

        asm volatile("" : "+r"(second_flag_3000));
        second_flag_3000 &= temp_r1_10;
        sp54 = temp_r2_8;
        if (second_flag_3000) {
            second_flag_3000 = 2;
            asm volatile("" : "+r"(second_flag_3000));
            flags_3000 |= second_flag_3000;
        }
        }
        if (({
            register s32 mode asm("r7");

            asm volatile("ldr %0, [sp, #48]"
                         : "=r"(mode)
                         : "g"(sp30)
                         : "memory");
            mode;
        }) != 0) {
            goto mode_nonzero;
        }
        var_r0_3 = 4;
        goto block_67;
mode_nonzero:
        if (({
            register s32 mode asm("r0");

            asm volatile("ldr %0, [sp, #48]"
                         : "=r"(mode)
                         : "g"(sp30)
                         : "memory");
            mode;
        }) != 1) {
            goto mode_not_one;
        }
        flags_3000 |= 0xC;
        asm volatile("");
        goto mode_done;
mode_not_one:
        if (({
            register s32 mode asm("r1");

            asm volatile("ldr %0, [sp, #48]"
                         : "=r"(mode)
                         : "g"(sp30)
                         : "memory");
            mode;
        }) == 2) {
            var_r0_3 = 8;
block_67:
            asm volatile("" : "+r"(var_r0_3));
            {
                register u32 narrowed asm("r0");

                asm volatile("orr %0, %1"
                             : "+r"(flags_3000)
                             : "r"(var_r0_3)
                             : "cc");
                narrowed = flags_3000 << 24;
                flags_3000 = narrowed >> 24;
            }
        }
mode_done:
        temp_r0_23 = M2C_FIELD(var_r9, u8 *, 0x38);
        switch (temp_r0_23) {                       /* switch 3 */
        case 0:                                     /* switch 3 */
            break;
        case 1:                                     /* switch 3 */
            var_r0_4 = 0x10;
            goto block_75;
        case 2:                                     /* switch 3 */
            var_r0_4 = 0x20;
            goto block_75;
        case 3:                                     /* switch 3 */
            flags_3000 |= 0x30;
            break;
        case 4:                                     /* switch 3 */
            var_r0_4 = 0x40;
block_75:
            asm volatile("" : "+r"(var_r0_4));
            {
                register u32 narrowed asm("r0");

                asm volatile("orr %0, %1"
                             : "+r"(flags_3000)
                             : "r"(var_r0_4)
                             : "cc");
                narrowed = flags_3000 << 24;
                flags_3000 = narrowed >> 24;
            }
            break;
        }
        if (0x40 & M2C_FIELD(var_r9, u8 *, 0x36)) {
            register u32 narrowed asm("r0");

            flags_3000 |= 0x80;
            narrowed = flags_3000 << 24;
            flags_3000 = narrowed >> 24;
        }
        func_080B65A4();
        {
            register u8 *record asm("r3") = var_r9;

            asm volatile("" : "+r"(record));
            func_080AC468_wide(
                0, flags_3000, M2C_FIELD(record, u8 *, 0));
        }
        }
        {
            register u32 build_index asm("r5");
            register s32 build_offset asm("r6");

            build_index = 0;
build_loop:
            {
                register u32 offset4 asm("r1");
                register u16 *slot asm("r2");
                register u32 slot_minus_one asm("r0");

                offset4 = build_index << 2;
                {
                    register u8 *record asm("r4");
                    register u8 *address asm("r0");

                    record = var_r9;
                    asm volatile("" : "+r"(record));
                    address = record + offset4;
                    slot = (u16 *)(address + 0x52);
                }
                slot_minus_one = *slot;
                slot_minus_one -= 1;
                slot_minus_one <<= 16;
                slot_minus_one >>= 16;
                build_offset = offset4;
                if (slot_minus_one <= 0x63U) {
                    register u8 *image_table asm("r3");
                    register u32 value asm("r0");
                    register u32 doubled asm("r1");
                    register u32 shifted asm("r0");
                    register u32 y_value asm("r4");
                    register u32 index_shift asm("r4");
                    register u32 saved_shift asm("r8");
                    register s32 x_value asm("r3");
                    register u8 *coordinate_table asm("r2");
                    register u32 kind_keep asm("ip");
                    register u8 *sprite_base asm("sl");

                    image_table = (u8 *)0x087ABC6C;
                    asm volatile("" : "+r"(image_table));
                    value = *slot;
                    doubled = value << 1;
                    if (build_index != 0) {
                        shifted = (doubled + 1) << 24;
                    } else {
                        shifted = value << 25;
                    }
                    func_0809AA64(image_table, shifted >> 24,
                                  (index_shift = build_index << 23) >> 16,
                                  build_index);
                    {
                        register u8 *base_seed asm("r7");

                        base_seed = (u8 *)0x087AC2BC;
                        asm volatile("" : "+r"(base_seed));
                        sprite_base = base_seed;
                    }
                    {
                        register u8 *record asm("r1");
                        register u8 *address asm("r0");
                        register u32 value2 asm("r0");
                        register u32 doubled2 asm("r1");
                        register u32 shifted2 asm("r0");

                        record = var_r9;
                        asm volatile("" : "+r"(record));
                        address = record + build_offset;
                        address += 0x52;
                        value2 = *(u16 *)address;
                        doubled2 = value2 << 1;
                        saved_shift = index_shift;
                        if (build_index != 0) {
                            shifted2 = (doubled2 + 1) << 16;
                        } else {
                            shifted2 = value2 << 17;
                        }
                        y_value = shifted2 >> 16;
                    }
                    {
                        register u8 *record asm("r3");
                        register u32 kind asm("r1");
                        register u32 kind_offset asm("r0");

                        coordinate_table = (u8 *)0x087EC38C;
                        asm volatile("" : "+r"(coordinate_table));
                        record = var_r9;
                        kind = *record;
                        kind_offset = kind << 5;
                        kind_offset = build_offset + kind_offset;
                        kind_offset += (u32)coordinate_table;
                        x_value = *(s16 *)kind_offset;
                        kind_keep = kind;
                    }
                    if (build_index == 2) {
                        register u8 *adjust_table asm("r0");
                        register u8 *record asm("r1");
                        register u32 adjustment_index asm("r1");
                        register s32 adjustment asm("r0");

                        adjust_table = (u8 *)0x087AC90C;
                        asm volatile("" : "+r"(adjust_table));
                        record = var_r9;
                        adjustment_index = *(u16 *)(record + 0x5A);
                        adjustment_index <<= 1;
                        adjustment_index += (u32)adjust_table;
                        adjustment = *(s16 *)adjustment_index;
                        x_value = (s16)(x_value - adjustment);
                    }
                    {
                        register s32 result asm("r0");
                        register s32 *output asm("r1");

                        result = func_08094374(
                            sprite_base,
                            y_value,
                            0,
                            x_value,
                            ({
                                register s32 sum asm("r0");
                                register u8 *table asm("r1");
                                register s32 coordinate asm("r0");

                                sum = (s32)kind_keep << 5;
                                asm volatile("add %0, %1, %0"
                                             : "+r"(sum)
                                             : "r"(build_offset)
                                             : "cc");
                                table = coordinate_table + 2;
                                asm volatile("" : "+r"(table));
                                sum += (s32)table;
                                coordinate = *(s16 *)sum;
                                coordinate;
                            }),
                            ({
                                register u32 value asm("r7");
                                register u32 narrowed asm("r0");

                                value = saved_shift;
                                narrowed = value >> 16;
                                narrowed;
                            }),
                            build_index,
                            ({
                                register u8 *table asm("r2");
                                register u8 *record asm("r0");
                                register u32 kind asm("r1");
                                register u32 address asm("r0");
                                register u32 entry asm("r0");
                                register u32 flags asm("r1");
                                register u32 selected asm("r0");

                                table = (u8 *)0x087ED68C;
                                asm volatile("" : "+r"(table));
                                record = var_r9;
                                kind = *record;
                                address = kind << 1;
                                address += kind;
                                address = build_index + address;
                                address += (u32)table;
                                entry = *(u8 *)address;
                                flags = entry << 6;
                                flags |= 0x1208;
                                if (build_index == ({
                                        register u32 mode asm("r2");

                                        asm volatile(
                                            "ldr %0, [sp, #48]"
                                            : "=r"(mode)
                                            : "g"(sp30)
                                            : "memory");
                                        mode;
                                    })) {
                                    selected = 0x200400;
                                } else {
                                    selected = 0x400;
                                }
                                selected |= flags;
                                selected;
                            }),
                            0);
                        output = sp;
                        asm volatile("" : "+r"(output));
                        output = (s32 *)((u8 *)output + build_offset);
                        output = (s32 *)((u8 *)output + 0x14);
                        asm volatile("" : "+r"(output));
                        *output = result;
                    }
                } else {
                    register s32 *output asm("r1");
                    register s32 zero asm("r0");

                    output = sp;
                    asm volatile("" : "+r"(output));
                    output = (s32 *)((u8 *)output + build_offset);
                    output = (s32 *)((u8 *)output + 0x14);
                    asm volatile("" : "+r"(output));
                    zero = 0;
                    *output = zero;
                }
            }
            {
                register u32 next asm("r0");

                next = build_index + 1;
                next <<= 24;
                build_index = next >> 24;
            }
            if (build_index <= 2U) {
                goto build_loop;
            }
        }
        sp34 = 0xFFFF;
        sp3C = 0;
        asm volatile(
            "mov r5, #0\n\t"
            "str r5, [sp, #56]\n\t"
            "str r5, [sp, #32]");
        {
            register volatile u16 *display asm("r1") =
                (volatile u16 *)0x04000008;
            register u32 value asm("r7") = 0x18D;
            register u32 store_value asm("r0");

            asm volatile("" : "+r"(display), "+r"(value));
            store_value = value;
            *display = store_value;
        }
        {
            register volatile u16 *display_shadow asm("r2") =
                (volatile u16 *)0x0300004C;
            register u32 r5_birth_guard asm("r5");

            asm volatile("" : "+r"(display_shadow));
            asm volatile("" : "=r"(r5_birth_guard));
            *display_shadow |= 0x100;
            asm volatile("" : : "r"(r5_birth_guard));
        }
        asm volatile("" : : : "r2");
        {
            register s32 *display_base asm("r2") = (s32 *)0x03000054;
            register s16 *coordinate_base asm("r1") =
                (s16 *)0x087EC38C;
            register u8 *record asm("r4") = var_r9;
            register s32 address asm("r0");
            register s32 stack_offset asm("r5");
            register u32 zero asm("r7");

            asm volatile("" : "+r"(coordinate_base));
            address = *record;
            address <<= 5;
            asm volatile("ldr %0, [sp, #84]"
                         : "=r"(stack_offset)
                         : "g"(sp54)
                         : "memory");
            asm volatile("add %0, %1, %0"
                         : "+r"(address)
                         : "r"(stack_offset)
                         : "cc");
            address += (u32)coordinate_base;
            zero = 0;
            asm volatile("ldrsh %0, [%0, %1]"
                         : "+r"(address)
                         : "r"(zero));
            address -= 0x4C;
            address <<= 8;
            display_base[0] = address;
            {
                register u32 r4_birth_guard asm("r4");
                register u32 r5_birth_guard asm("r5");
                register u32 r7_birth_guard asm("r7");

                asm volatile("" : "=r"(r4_birth_guard),
                                  "=r"(r5_birth_guard),
                                  "=r"(r7_birth_guard));
                display_base[1] = sp38;
                asm volatile("" : : "r"(r4_birth_guard),
                                  "r"(r5_birth_guard),
                                  "r"(r7_birth_guard));
            }
        }
        if (sp30 == 2) {
            {
                register volatile u16 *control_a asm("r1") =
                    (volatile u16 *)0x0300004E;
                register u32 value_a asm("r2") = 0x3741;
                register u32 store_value asm("r0");

                asm volatile("" : "+r"(control_a), "+r"(value_a));
                store_value = value_a;
                *control_a = store_value;
            }
            {
                register volatile u16 *control_b asm("r1") =
                    (volatile u16 *)0x03000050;
                register u32 value_b asm("r3") = 0x808;
                register u32 store_value asm("r0");

                asm volatile("" : "+r"(value_b));
                store_value = value_b;
                *control_b = store_value;
            }
        }
        {
            register s32 palette_3010 asm("r8");
            register s32 palette_low_3010 asm("r4");
            s32 source_a_3010;
            register s32 source_b_3010 asm("sl");

            sp48 = func_08094484(0x08105AFC, 0x08105B08, 0, 0xC8, 0x98, 0x350, ({
                palette_low_3010 = 0xF;
                asm volatile("" : "+r"(palette_low_3010));
                palette_3010 = palette_low_3010;
                asm volatile("" : "+r"(palette_3010));
                palette_low_3010;
            }), 8, ({
                register u32 selector asm("r5");

                asm volatile("ldr %0, [sp, #56]"
                             : "=r"(selector)
                             : "g"(sp38)
                             : "memory");
                selector;
            }));
            source_a_3010 = 0x081058DC;
            {
                register u32 r2_birth_guard asm("r2");
                register u32 r3_birth_guard asm("r3");
                register u32 r5_birth_guard asm("r5");

                asm volatile("" : "=r"(r2_birth_guard),
                                  "=r"(r3_birth_guard),
                                  "=r"(r5_birth_guard));
                source_b_3010 = 0x08105918;
                asm volatile("" : : "r"(r2_birth_guard),
                                  "r"(r3_birth_guard),
                                  "r"(r5_birth_guard));
            }
            sp4C = func_08094484(source_a_3010, source_b_3010, 0,
                0x10, 0x78, 0x2F8, palette_low_3010, 0x48, ({
                    register u32 selector asm("r1");

                    asm volatile("ldr %0, [sp, #56]"
                                 : "=r"(selector)
                                 : "g"(sp38)
                                 : "memory");
                    selector;
                }));
            sp50 = func_08094484(source_a_3010, source_b_3010, 4,
                0x68, 0x78, 0x2F8, ({
                    register s32 palette asm("r2");

                    asm volatile("mov %0, r8"
                                 : "=r"(palette)
                                 : "r"(palette_3010));
                    palette;
                }), 0x48, ({
                    register u32 selector asm("r3");

                    asm volatile("ldr %0, [sp, #56]"
                                 : "=r"(selector)
                                 : "g"(sp38)
                                 : "memory");
                    selector;
                }));
        }
        var_r4 = 0x3010;
        goto block_286;
state_3010_handler:
        {
            register s32 selector_raw asm("r0");
            register s32 selector_signed asm("r2");
            register s32 selector_neg_one asm("r1");
            u32 selector_home;

            asm volatile(""
                         : "=r"(selector_home)
                         : "0"(sp34)
                         : "r0", "r1", "r2", "r3", "r4");
            selector_raw = selector_home << 0x10;
            selector_signed = selector_raw >> 0x10;
            selector_neg_one = -1;
            asm volatile("" : : "r"(selector_signed),
                                  "r"(selector_neg_one));
            sp58 = selector_raw;
            if (selector_signed != selector_neg_one) {
                register u8 *selector_table asm("r0") =
                    (u8 *)0x020322B2;

                asm volatile("add %0, %1, %0"
                    : "+r"(selector_table)
                    : "r"(selector_signed));
                temp_r0_2 = *selector_table;
                sp38 = (u32) temp_r0_2;
                {
                    register u32 selector_copy asm("r7");
                    register u8 *record_table asm("r1");

                    temp_r0_2 *= 2;
                    asm volatile("ldr %0, [sp, #56]"
                                 : "=r"(selector_copy)
                                 : "g"(sp38)
                                 : "memory");
                    temp_r0_2 += selector_copy;
                    temp_r0_2 *= 8;
                    record_table = (u8 *)0x087B2524;
                    asm volatile("" : "+r"(record_table));
                    asm volatile("add %0, %0, %1"
                        : "+r"(temp_r0_2)
                        : "r"(record_table));
                    sp40 = (void *)temp_r0_2;
                }
            } else {
                register u32 r7_birth_guard asm("r7");

                asm volatile("" : "=r"(r7_birth_guard));
                temp_r0_2 = 0;
                sp38 = temp_r0_2;
                asm volatile("" : : "r"(r7_birth_guard));
            }
        }
        {
        register u32 selected_mode asm("r1");
        u32 previous_mode;
        s32 active_sp20;

        asm volatile(""
                     : "=r"(selected_mode)
                     : "0"(sp38)
                     : "r0", "r2", "r3", "r4", "r5", "r7");
        asm volatile(""
                     : "=r"(previous_mode)
                     : "0"(sp3C)
                     : "r0", "r1", "r3", "r4", "r5", "r7");
        if (selected_mode != previous_mode) {
            active_sp20 = sp20;
            asm volatile("" : "+r"(active_sp20)
                            : "r"(selected_mode));
            if (active_sp20 != 0) {
                func_08094554();
                {
                    register s32 cleared_sp20 asm("r0");

                    asm volatile("mov %0, #0"
                                 : "=r"(cleared_sp20));
                    sp20 = cleared_sp20;
                }
                func_080ED17C(1);
            }
            {
            register u32 r0_cleanup_guard asm("r0");
            register u32 r1_cleanup_guard asm("r1");
            register u32 r2_cleanup_guard asm("r2");
            register u32 *cleanup_flags asm("r2");
            register s32 cleanup_mode asm("r3");

            asm volatile("" : "=r"(r0_cleanup_guard),
                              "=r"(r1_cleanup_guard),
                              "=r"(r2_cleanup_guard));
            cleanup_mode = sp30;
            asm volatile("" : "+r"(cleanup_mode)
                            : "r"(r0_cleanup_guard),
                              "r"(r2_cleanup_guard));
            if (cleanup_mode == 1) {
                cleanup_flags = sp1C;
                asm volatile("" : "+r"(cleanup_flags)
                                : "r"(r1_cleanup_guard));
                if (cleanup_flags != NULL) {
                    register u32 cleanup_value asm("r0");

                    cleanup_value = *cleanup_flags;
                    r1_cleanup_guard = 0xFFDFFFFF;
                    asm volatile("" : "+r"(r1_cleanup_guard),
                                          "+r"(cleanup_value));
                    cleanup_value &= r1_cleanup_guard;
                    *cleanup_flags = cleanup_value;
                }
            }
            {
            register s32 next_cleanup_mode asm("r4") = sp30;

            asm volatile("" : "+r"(next_cleanup_mode)
                            : "r"(r1_cleanup_guard),
                              "r"(cleanup_flags),
                              "r"(cleanup_mode));
            if (next_cleanup_mode == 2) {
                register s32 *flags asm("r2");
                register u32 value asm("r0");

                asm volatile("ldr %0, [sp, #24]"
                             : "=r"(flags)
                             : "g"(sp18)
                             : "memory");
                if (flags != NULL) {
                    value = *flags;
                    value &= 0xFFDFFFFF;
                    *flags = value;
                }
            }
            }
            }
        }
        }
        {
        register u32 active_selector asm("r5");

        asm volatile("ldr %0, [sp, #56]"
                     : "=r"(active_selector)
                     : "g"(sp38)
                     : "memory");
        if (active_selector != 0) {
            register s32 doubled_index_3010 asm("r8");
            register u8 *selector_table asm("r0");
            register s32 selector_reload asm("r7");
            register s32 selector_index asm("r1");
            register u32 selector_value asm("r0");

            selector_table = (u8 *)0x02032AC8;
            asm volatile("" : "+r"(selector_table));
            asm volatile(
                "ldr %0, [sp, #88]\n\t"
                "asr %1, %0, #16"
                : "=r"(selector_reload), "=r"(selector_index));
            asm volatile("add %0, %0, %1"
                         : "+r"(selector_index)
                         : "r"(selector_table)
                         : "cc");
            selector_value = *(u8 *)selector_index;
            sp54 = sp30 * 4;
            doubled_index_3010 = active_selector * 2;
            if (selector_value != 0) {

            } else {
                if ((sp38 <= 0x64U) && (sp38 != sp3C)) {
                    register u8 *image_table_3010 asm("r3");
                    register u8 *sprite_base_3010 asm("r6");

                    image_table_3010 = (u8 *)0x087ABC6C;
                    asm volatile("" : "+r"(image_table_3010));
                    if (sp30 != 0) {
                        var_r0 = (doubled_index_3010 + 1) << 0x18;
                    } else {
                        var_r0 = sp38 << 0x19;
                    }
                    func_0809AA64((s32)image_table_3010, var_r0 >> 0x18, 0x180U, 3U);
                    sprite_base_3010 = (u8 *)0x087AC2BC;
                    asm volatile("" : "+r"(sprite_base_3010));
                    if (sp30 != 0) {
                        register s32 incremented_index asm("r0") =
                            doubled_index_3010 + 1;

                        asm volatile("" : "+r"(incremented_index));
                        var_r5_2 = incremented_index;
                    } else {
                        asm volatile("" : "+g"(sp38));
                        var_r5_2 = sp38 * 2;
                    }
                    {
                        register u8 *coordinate_table_seed_3010 asm("r3") =
                            (u8 *)0x087EC38C;
                        register s32 row_index_seed_3010 asm("r1") = sp30;
                        register s32 row_offset_3010 asm("r2");
                        register u32 kind_keep_3010 asm("ip");
                        register s32 coordinate_3010 asm("r4");
                        register u8 *record_3010 asm("r4");
                        register s32 var_r3_2 asm("r3");
                        register u8 *coordinate_table_keep_3010 asm("r2");

                        asm volatile("" :
                            "+r"(coordinate_table_seed_3010));
                        asm volatile("" : "+r"(row_index_seed_3010));
                        row_offset_3010 = row_index_seed_3010 * 4;
                        asm volatile("mov %0, r9"
                                     : "=r"(record_3010));
                        temp_r1_3 = *record_3010;
                        coordinate_3010 = *(s16 *)(row_offset_3010
                            + (temp_r1_3 << 5)
                            + (s32)coordinate_table_seed_3010);
                        kind_keep_3010 = temp_r1_3;
                        sp54 = row_offset_3010;
                        coordinate_table_keep_3010 =
                            coordinate_table_seed_3010;
                        asm volatile("" :
                            "+r"(coordinate_table_keep_3010));
                        if (sp30 == 2) {
                            s32 adjustment_3010;
                            register s32 adjusted_3010 asm("r0");

                            adjustment_3010 =
                                M2C_FIELD(doubled_index_3010, s16 *,
                                    0x087AC90C);
                            adjusted_3010 =
                                coordinate_3010 - adjustment_3010;
                            adjusted_3010 <<= 16;
                            var_r3_2 = adjusted_3010 >> 16;
                        } else {
                            var_r3_2 = coordinate_3010;
                        }
                        sp20 = func_08094374(
                            sprite_base_3010,
                            var_r5_2,
                            0,
                            var_r3_2,
                            ({
                                register s32 coordinate_sum_3010 asm("r0");
                                register u8 *coordinate_table_arg_3010
                                    asm("r1");
                                register s32 coordinate_arg_3010 asm("r0");

                                coordinate_sum_3010 =
                                    sp54 + (kind_keep_3010 << 5);
                                coordinate_table_arg_3010 =
                                    coordinate_table_keep_3010 + 2;
                                asm volatile("" :
                                    "+r"(coordinate_table_arg_3010));
                                coordinate_sum_3010 +=
                                    (s32)coordinate_table_arg_3010;
                                coordinate_arg_3010 =
                                    *(s16 *)coordinate_sum_3010;
                                coordinate_arg_3010;
                            }),
                            0x180,
                            3,
                            ({
                                register u8 *flags_table_3010 asm("r2") =
                                    (u8 *)0x087ED68C;
                                register u8 *record_3010 asm("r4") = var_r9;
                                register u32 kind_3010 asm("r1");
                                register u32 address_3010 asm("r0");
                                register u32 flags_3010 asm("r0");
                                register s32 mode_3010 asm("r7");

                                asm volatile("" :
                                    "+r"(flags_table_3010));
                                kind_3010 = *record_3010;
                                address_3010 = kind_3010 << 1;
                                address_3010 += kind_3010;
                                asm volatile("ldr %0, [sp, #48]"
                                             : "=r"(mode_3010)
                                             : "g"(sp30)
                                             : "memory");
                                asm volatile("add %0, %1, %0"
                                             : "+r"(address_3010)
                                             : "r"(mode_3010)
                                             : "cc");
                                address_3010 +=
                                    (u32)flags_table_3010;
                                flags_3010 = *(u8 *)address_3010;
                                flags_3010 <<= 6;
                                flags_3010 |= 0x1208;
                                flags_3010;
                            }),
                            0);
                    }
                }
                {
                    register u8 *record asm("r0") = sp40;

                    asm volatile("" : "+r"(record));
                    if ((3 & M2C_FIELD(record, u8 *, 0x14)) == 3) {
                        register s32 *effect asm("r2") = sp1C;

                        asm volatile("" : "+r"(effect));
                        if (effect != NULL) {
                            *effect |= 0x200000;
                        }
                    }
                }
                {
                register u32 r0_birth_guard asm("r0");
                register u32 r2_birth_guard asm("r2");
                s32 effect_mode;

                asm volatile("" : "=r"(r0_birth_guard),
                                  "=r"(r2_birth_guard));
                effect_mode = sp30;
                asm volatile("" : "+r"(effect_mode)
                                : "r"(r0_birth_guard),
                                  "r"(r2_birth_guard));
                if (effect_mode == 2) {
                    register u32 *effect_slot asm("r3") = sp18;

                    asm volatile("" : "+r"(effect_slot));
                    if (effect_slot != NULL) {
                        register u8 *catalog asm("r2") =
                            (u8 *)0x087B2524;
                        register u32 item asm("r1");
                        register u32 item_address asm("r0");
                        register u32 flags asm("r1");

                        asm volatile("" : "+r"(catalog));
                        item = M2C_FIELD(var_r9, u16 *, 0x56);
                        asm volatile("" : "+r"(item));
                        item_address = item << 1;
                        item_address += item;
                        item_address <<= 3;
                        item_address += (u32)catalog;
                        flags = *(u8 *)(item_address + 0x14);
                        asm volatile("" : "+r"(flags));
                        if ((3 & flags) == 3) {
                            *effect_slot |= 0x200000;
                        }
                    }
                }
                }
            }
            {
                register u8 *stack_slot_addr asm("r0");

                stack_slot_addr = (u8 *) sp + sp54;
                stack_slot_addr += 0x14;
                asm volatile("" : "+r"(stack_slot_addr));
                temp_r2_5 = *(s32 **) stack_slot_addr;
            }
            if (temp_r2_5 != NULL) {
                *temp_r2_5 |= 0x20000;
            }
            func_080986B4(2);
            {
                register s16 *stat_source asm("r1");
                register u8 *record_source asm("r2");
                register u32 field_offset asm("r3");
                register s32 compare_zero asm("r5");
                register s32 stat_limit asm("r0");

                stat_source = (s16 *)((u8 *)var_r9 + 0x4C);
                record_source = var_r9;
                var_r6 = *(u16 *)(record_source + 0xE);
                field_offset = 0xE;
                asm volatile("ldrsh %0, [%1, %2]"
                             : "=r"(temp_r4_2)
                             : "r"(record_source), "r"(field_offset));
                compare_zero = 0;
                asm volatile("ldrsh %0, [%1, %2]"
                             : "=r"(stat_limit)
                             : "r"(stat_source), "r"(compare_zero));
                var_r2_3 = 1;
                var_r7 = stat_source;
                if (temp_r4_2 <= stat_limit) {
                    var_r2_3 = 0;
                }
            }
            func_0809844C_wide(
                temp_r4_2, 4, var_r2_3, 0xA, 2, 0U, 0U);
            {
                register u8 *selector_table asm("r1") =
                    (u8 *)0x02032AC8;
                register s32 selector_reload asm("r2");
                register s32 selector_index asm("r0");

                asm volatile("" : "+r"(selector_table));
                selector_reload = sp58;
                asm volatile(
                    "asr %0, %1, #16"
                    : "=r"(selector_index)
                    : "r"(selector_reload));
                asm volatile("add %0, %0, %1"
                             : "+r"(selector_index)
                             : "r"(selector_table)
                             : "cc");
                temp_r1_4 = *(u8 *)selector_index;
            }
            if (temp_r1_4 == 0) {
                u32 stat_delta;

                func_080981F0(
                    0x08106508, 0, 2, 4, (u32) temp_r1_4);
                {
                    register u8 *record_base asm("r0") =
                        (u8 *)(sp54 + (u32)var_r9);
                    register u8 *field_address asm("r1");
                    register u32 field_value asm("r0");

                    asm volatile("mov %0, %1"
                                 : "=r"(field_address)
                                 : "r"(record_base));
                    field_address += 0x52;
                    field_value = *(u16 *)field_address;
                    temp_r0_10 = field_value;
                }
                if (temp_r0_10 != 0) {
                    register u8 *catalog asm("r2") =
                        (u8 *)0x087B2524;
                    register u32 item asm("r1");
                    register u32 item_address asm("r0");
                    register u32 adjustment asm("r1");
                    u32 record_stat;

                    asm volatile("" : "+r"(catalog));
                    item = temp_r0_10;
                    asm volatile("" : "+r"(item));
                    item_address = item << 1;
                    item_address += item;
                    item_address <<= 3;
                    item_address += (u32)catalog;
                    adjustment = *(u16 *)(item_address + 0x12);
                    record_stat = M2C_FIELD(sp40, u16 *, 0x12);
                    asm volatile("" : "+r"(adjustment),
                                      "+r"(record_stat)
                                 : "r"(catalog));
                    stat_delta = record_stat - adjustment;
                } else {
                    stat_delta = M2C_FIELD(sp40, u16 *, 0x12);
                }
                var_r6 = temp_r4_2 + stat_delta;
                if ((3 & M2C_FIELD(sp40, u8 *, 0x14)) == 3) {
                    {
                        register u8 *field_address asm("r1");

                        asm volatile("mov %0, %1"
                                     : "=r"(field_address)
                                     : "r"(var_r9));
                        field_address += 0x5A;
                        temp_r0_11 = *(u16 *)field_address;
                    }
                    if (temp_r0_11 != 0) {
                        register u8 *catalog asm("r2") =
                            (u8 *)0x087B2524;
                        register u32 item asm("r1");
                        register u32 item_address asm("r0");
                        register s32 adjustment asm("r1");

                        asm volatile("" : "+r"(catalog));
                        item = temp_r0_11;
                        asm volatile("" : "+r"(item));
                        item_address = item << 1;
                        item_address += item;
                        item_address <<= 3;
                        item_address += (u32)catalog;
                        adjustment = *(u16 *)(item_address + 0x12);
                        asm volatile("" : "+r"(adjustment));
                        {
                            register s32 signed_value asm("r0") =
                                (s16)var_r6;

                            asm volatile("" : "+r"(signed_value));
                            signed_value -= adjustment;
                            var_r6 = signed_value;
                        }
                    }
                }
                if (sp30 == 2) {
                    {
                        register u8 *field_address asm("r1");

                        asm volatile("mov %0, %1"
                                     : "=r"(field_address)
                                     : "r"(var_r9));
                        field_address += 0x56;
                        temp_r0_12 = *(u16 *)field_address;
                    }
                    if (temp_r0_12 != 0) {
                        register u8 *catalog asm("r2") =
                            (u8 *)0x087B2524;
                        register u32 item asm("r1");
                        register u32 item_offset asm("r0");
                        register u32 flags asm("r1");

                        asm volatile("" : "+r"(catalog));
                        item = temp_r0_12;
                        asm volatile("" : "+r"(item));
                        item_offset = item << 1;
                        item_offset += item;
                        item_offset <<= 3;
                        asm volatile(
                            ".syntax unified\n\t"
                            "adds %0, %1, %0\n\t"
                            ".syntax divided"
                            : "+l"(catalog)
                            : "l"(item_offset));
                        flags = M2C_FIELD(catalog, u8 *, 0x14);
                        asm volatile("" : "+r"(flags));
                        if ((3 & flags) == 3) {
                            register s32 adjustment asm("r1") =
                                M2C_FIELD(catalog, u16 *, 0x12);

                            asm volatile("" : "+r"(adjustment));
                            {
                                register s32 signed_value asm("r0") =
                                    (s16)var_r6;

                                asm volatile("" : "+r"(signed_value));
                                signed_value -= adjustment;
                                var_r6 = signed_value;
                            }
                        }
                    }
                }
        {
            register u32 narrow asm("r0") = var_r6 << 16;
            register s32 signed_value asm("r1") =
                (s32)narrow >> 16;
            register u32 zero_then_flag asm("r2") = 0;
            register s32 threshold asm("r0");

            asm volatile(
                "ldrsh %0, [%1, %2]"
                : "=r"(threshold)
                : "r"(var_r7), "r"(zero_then_flag));
            zero_then_flag = 1;
            if (signed_value <= threshold) {
                zero_then_flag = 0;
            }
            func_0809844C_wide(signed_value, 4, zero_then_flag,
                0xA, 2, 5U, 0U);
        }
            }
            func_080981F0(0x081061A4, 0, 2, 9, 0U);
            func_0809844C_wide(({
                register s32 value asm("r0");
                register s32 zero asm("r3");

                asm volatile(
                    "mov %1, #0\n\t"
                    "ldrsh %0, [%2, %1]"
                    : "=r"(value), "=r"(zero)
                    : "r"(var_r7));
                value;
            }), 3, 0, 0xA, 2, 0xAU, 0U);
            {
                register u8 *catalog asm("r2") = (u8 *)0x087B2524;
                register struct Record24 *copy_source asm("r1");
                register struct Record24 *copy_dest asm("r0");

                asm volatile("" : "+r"(catalog));
                temp_r1_6 = (sp38 + doubled_index_3010) << 3;
                copy_dest = (struct Record24 *)sp44;
                temp_r1_6 += (u32)catalog;
                copy_source = (struct Record24 *)temp_r1_6;
                asm volatile(
                    "ldmia %0!, {r2, r4, r5}\n\t"
                    "stmia %1!, {r2, r4, r5}\n\t"
                    "ldmia %0!, {r3, r4, r5}\n\t"
                    "stmia %1!, {r3, r4, r5}"
                    : "+r"(copy_source), "+r"(copy_dest)
                    :
                    : "r2", "r3", "r4", "r5", "memory");
            }
            {
                register void *copy_check asm("r0");

                asm volatile("ldr %0, [sp, #68]"
                             : "=r"(copy_check)
                             : "g"(sp44)
                             : "memory");
                if (1 & M2C_FIELD(copy_check, u16 *, 2)) {
                    goto block_171;
                }
            }
            {
                register s32 call_value asm("r0");
                register s32 call_limit asm("r1");
                register void *call_record asm("r2");

                asm volatile(
                    "lsl %0, %3, #16\n\t"
                    "asr %0, %0, #16\n\t"
                    "mov %2, #0\n\t"
                    "ldrsh %1, [%4, %2]\n\t"
                    "ldr %2, [sp, #68]"
                    : "=r"(call_value), "=r"(call_limit),
                      "=r"(call_record)
                    : "r"(var_r6), "r"(var_r7)
                    : "cc");
                func_080E596C_wide(
                    call_value, call_limit, call_record);
            }
            {
                register u8 *record_view asm("r3") = var_r9;

                asm volatile("" : "+r"(record_view));
                var_r1 = M2C_FIELD(record_view, u8 *, 2);
                var_r1 <<= 6;
                {
                    register u32 r2_birth_guard asm("r2");
                    register u32 r3_birth_guard asm("r3");
                    register u32 r4_birth_guard asm("r4");
                    register u32 r5_birth_guard asm("r5");

                    asm volatile("" : "=r"(r2_birth_guard),
                                      "=r"(r3_birth_guard),
                                      "=r"(r4_birth_guard),
                                      "=r"(r5_birth_guard));
                    var_r1 += 0x02027378;
                    asm volatile("" : : "r"(r2_birth_guard),
                                      "r"(r3_birth_guard),
                                      "r"(r4_birth_guard),
                                      "r"(r5_birth_guard));
                }
            }
            var_r3 = M2C_FIELD((sp54 + var_r9), u16 *, 0x52);
            goto block_170;
        } else {
            register s32 retained_call_two asm("r8");

            {
                register s32 stack_index asm("r5") = sp30;
                register s32 stack_offset asm("r1");
                register u8 *stack_slot_addr asm("r0");
                register s32 *stack_slot asm("r2");

                asm volatile("" : "=m"(subroutine_arg0));
                stack_offset = stack_index << 2;
                asm volatile("mov %0, sp" : "=r"(stack_slot_addr));
                stack_slot_addr += stack_offset;
                stack_slot_addr += 0x14;
                asm volatile("" : "+r"(stack_slot_addr));
                stack_slot = *(s32 **) stack_slot_addr;
                sp54 = stack_offset;
                if (stack_slot != NULL) {
                    *stack_slot &= 0xFFFDFFFF;
                }
            }
            func_080986B4(2);
            {
                register s16 *stat_source asm("r1");
                register s32 compare_zero asm("r2");
                register s32 stat_limit asm("r0");

                stat_source = (s16 *)((u8 *)var_r9 + 0x4C);
                asm volatile(
                    "mov r7, r9\n\t"
                    "ldrh %0, [r7, #14]\n\t"
                    "mov r0, #14\n\t"
                    "ldrsh %1, [r7, r0]"
                    : "=r"(var_r6), "=r"(temp_r5)
                    :
                    : "r0", "r7");
                compare_zero = 0;
                asm volatile("ldrsh %0, [%1, %2]"
                             : "=r"(stat_limit)
                             : "r"(stat_source), "r"(compare_zero));
                var_r2 = 1;
                var_r7 = stat_source;
                if ((s32)temp_r5 <= stat_limit) {
                    var_r2 = 0;
                }
                asm volatile("" : : "r"(temp_r5), "r"(temp_r5) : "r4");
            }
            asm volatile(
                "mov r3, #2\n\t"
                "mov %0, r3\n\t"
                "str r3, [sp, #0]\n\t"
                "ldr r4, [sp, #56]\n\t"
                "str r4, [sp, #4]\n\t"
                "str r4, [sp, #8]"
                : "=r"(retained_call_two)
                : "g"(sp38)
                : "r3", "r4", "memory");
            func_0809844C_stack4(temp_r5, 4, var_r2, 0xA);
            temp_r0_3 = sp54 + var_r9;
            if (M2C_FIELD(temp_r0_3, u16 *, 0x52) != 0) {
                func_080981F0(0x08106508, 0, 2, 4, sp38);
                {
                    register u8 *catalog asm("r2") =
                        (u8 *)0x087B2524;
                    register u32 adjusted asm("r0");

                    asm volatile("" : "+r"(catalog));
                    adjusted = temp_r5 -
                        M2C_FIELD(((M2C_FIELD(temp_r0_3, u16 *, 0x52)
                            * 0x18) + catalog), u16 *, 0x12);
                    adjusted <<= 16;
                    var_r6 = adjusted >> 16;
                {
                    register s32 signed_value asm("r1") =
                        (s32)adjusted >> 16;
                    register u32 zero_then_flag asm("r2") = 0;
                    register s32 threshold asm("r0");

                    asm volatile(
                        "ldrsh %0, [%1, %2]"
                        : "=r"(threshold)
                        : "r"(var_r7), "r"(zero_then_flag));
                    zero_then_flag = 1;
                    if (signed_value <= threshold) {
                        zero_then_flag = 0;
                    }
                    func_0809844C_wide(signed_value, 4,
                        zero_then_flag, 0xA,
                        retained_call_two, 5U, sp38);
                }
                }
            }
            func_080981F0(0x081061A4, 0, 2, 9, 0U);
            func_0809844C(*var_r7, 3, 0, 0xA, 2, 0xAU, 0U);
            {
                register u32 record_offset asm("r0") = sp54;
                register u8 *record_field asm("r4");

                asm volatile("" : "+r"(record_offset));
                asm volatile("add %0, r9" : "+r"(record_offset));
                record_field = (u8 *)record_offset;
                record_field += 0x52;
                temp_r0_6 = *(u16 *)record_field;
            if (temp_r0_6 == 0) {
                goto no_record_message;
            }
            {
                register u8 *catalog asm("r2") = (u8 *)0x087B2524;
                register u32 item asm("r1");
                register u32 item_offset asm("r0");
                register struct Record24 *copy_source asm("r0");
                register struct Record24 *copy_dest asm("r1");

                asm volatile("" : "+r"(catalog));
                asm volatile("mov %0, %1"
                             : "=r"(item)
                             : "r"(temp_r0_6));
                item_offset = item << 1;
                item_offset += item;
                item_offset <<= 3;
                copy_dest = (struct Record24 *)sp44;
                asm volatile("add %0, %0, %1"
                             : "+r"(item_offset)
                             : "r"(catalog));
                copy_source = (struct Record24 *)item_offset;
                *copy_dest = *copy_source;
            }
            if (1 & M2C_FIELD(sp44, u16 *, 2)) {
                goto block_171;
            }
            asm volatile("" : : : "r7");
            {
                register void *call_record asm("r0");
                register void *call_sp44 asm("r1");

                asm volatile(
                    "mov %0, %2\n\t"
                    "ldr %1, [sp, #68]"
                    : "=r"(call_record), "=r"(call_sp44)
                    : "r"(var_r9));
                func_080E59A0(call_record, call_sp44);
            }
            {
                register u8 *record_view asm("r2") = var_r9;
                register u32 r3_birth_guard asm("r3");
                register u32 r5_birth_guard asm("r5");

                asm volatile("" : "+r"(record_view),
                                  "=r"(r3_birth_guard),
                                  "=r"(r5_birth_guard));
                var_r1 = M2C_FIELD(record_view, u8 *, 2);
                var_r1 <<= 6;
                var_r1 += 0x02027378;
                asm volatile("" : : "r"(record_view),
                                  "r"(r3_birth_guard),
                                  "r"(r5_birth_guard));
            }
            var_r3 = *(u16 *)record_field;
            goto block_170;
            }
        }
        }
block_170:
        {
            register u32 r0_call_guard asm("r0");
            register u32 r2_call_guard asm("r2");
            register u32 r5_call_guard asm("r5");
            void *call_sp44;

            asm volatile("" : "=r"(r0_call_guard),
                              "=r"(r2_call_guard),
                              "=r"(r5_call_guard));
            call_sp44 = sp44;
            asm volatile("" : "+r"(call_sp44)
                            : "r"(r0_call_guard),
                              "r"(r2_call_guard),
                              "r"(r5_call_guard));
            func_080E6994(var_r9, var_r1, 0, var_r3, call_sp44);
        }
block_171:
        func_080ACDA8(sp44, 1, 1);
        goto record_update_done;
no_record_message:
        func_08098BB4(0x08002E8B);
record_update_done:
        sp3C = sp38;
        func_08098BB4(0x08002E90);
        sp34 = (s32) (u16) (*(u8 *)0x0200A880 - 1);
        temp_r0_14 = *(u8 *)0x0200A882;
        if (temp_r0_14 == 0) {
            goto action_0;
        }
        if (temp_r0_14 != 1) {
            goto action_default;
        }
action_1:
            temp_r1_9 = (s16) sp34;
            if (temp_r1_9 == -1) {
                if (M2C_FIELD((sp54 + var_r9), u16 *, 0x52) == 0) {
                    goto block_287;
                }
                goto block_185;
            }
            {
                register u32 r2_birth_guard asm("r2");
                register u32 r3_birth_guard asm("r3");
                register u32 r5_birth_guard asm("r5");
                u8 action_state;

                asm volatile("" : "=r"(r2_birth_guard),
                                  "=r"(r3_birth_guard),
                                  "=r"(r5_birth_guard));
                action_state =
                    M2C_FIELD(temp_r1_9, u8 *, 0x02032AC8);
                asm volatile("" : : "r"(r2_birth_guard),
                                  "r"(r3_birth_guard),
                                  "r"(r5_birth_guard));
                if (action_state != 0) {
                    goto action_switch5;
                }
            }
block_185:
                if (({
                        register u32 selector asm("r2");

                        asm volatile("ldr %0, [sp, #56]"
                                     : "=r"(selector)
                                     : "g"(sp38)
                                     : "memory");
                        selector;
                    }) != 0) {
                    if ((3 & M2C_FIELD(({
                            register u8 *record asm("r3");

                            asm volatile("ldr %0, [sp, #64]"
                                         : "=r"(record)
                                         : "g"(sp40)
                                         : "memory");
                            record;
                        }), u8 *, 0x14)) == 3) {
                        func_08098BB4(0x0800332A);
                        if (*(u8 *)0x0200A882 == 2) {
                            goto block_287;
                        } else if (*(u8 *)0x0200A880 == 1) {
                            goto block_287;
                        } else {
                            goto block_191;
                        }
                    } else {
block_191:
                        if ((s32) (s16) var_r6 > (s32) ({
                                register u32 index_r2_guard asm("r2");
                                register u32 index_guard asm("r3");
                                s32 threshold;

                                asm volatile("" : "=r"(index_r2_guard),
                                                  "=r"(index_guard));
                                threshold = *var_r7;
                                asm volatile("" : : "r"(index_r2_guard),
                                                  "r"(index_guard));
                                threshold;
                            })) {
                            func_08098BB4(0x08003244);
                            if (*(u8 *)0x0200A882 == 2) {
                            goto block_287;
                            } else if (*(u8 *)0x0200A880 == 1) {
                            goto block_287;
                            } else {
                                goto block_196;
                            }
                        } else {
                            goto block_196;
                        }
                    }
                } else {
block_196:
                    temp_r0_17 = sp54 + var_r9;
                    temp_r0_18 = M2C_FIELD(temp_r0_17, u16 *, 0x52);
                    if ((temp_r0_18 != 0) && (temp_r0_18 != sp38) && (({
                            register u32 status_base asm("r0") = 0x020218E4;
                            register u32 status_offset asm("r7") = 0x6934;

                            asm volatile("" : "+r"(status_base),
                                "+r"(status_offset));
                            status_base += status_offset;
                            asm volatile("" : : : "memory");
                            status_base +=
                                M2C_FIELD(temp_r0_17, u16 *, 0x52);
                            *(u8 *)status_base;
                        }) == 0x63)) {
                        func_08098BB4(0x080031A8);
                        {
                            register s32 *message_table asm("r1") =
                                (s32 *)0x087EE170;

                            asm volatile("" : "+r"(message_table));
                            func_080981F0(
                                message_table[
                                    M2C_FIELD(
                                        temp_r0_17, u16 *, 0x52)],
                                2, 3, 0, 0U);
                        }
                        func_08098BB4(0x0800323E);
                        if (*(u8 *)0x0200A882 == 2) {
                            goto block_287;
                        } else if (*(u8 *)0x0200A880 == 1) {
                            goto block_287;
                        } else {
                            goto block_203;
                        }
                    } else {
block_203:
                        if (((3 & M2C_FIELD(({
                                register u8 *record asm("r2");

                                asm volatile("ldr %0, [sp, #64]"
                                             : "=r"(record)
                                             : "g"(sp40)
                                             : "memory");
                                record;
                            }), u8 *, 0x14)) == 3) && ({
                                register u16 *status_slot asm("r0") =
                                    (u16 *)((u8 *)var_r9 + 0x5A);
                                register u16 status_value asm("r1") =
                                    *status_slot;

                                asm volatile(
                                    ".syntax unified\n\t"
                                    "adds %0, %1, #0\n\t"
                                    ".syntax divided"
                                    : "=l"(status_slot_203)
                                    : "l"(status_slot));
                                status_value != 0;
                            })) {
                            {
                                register u8 *status_base asm("r0") =
                                    (u8 *)0x020218E4;
                                register u32 status_offset asm("r3") =
                                    0x6934;
                                register u32 status_index asm("r5");

                                asm volatile("" : "+r"(status_base));
                                asm volatile("" : "+r"(status_offset));
                                status_base += status_offset;
                                status_index = *status_slot_203;
                                asm volatile("" : "+r"(status_index));
                                status_address_203 =
                                    status_base + status_index;
                                temp_r0_19 = *status_address_203;
                            }
                            if (temp_r0_19 == 0x63) {
                                func_08098BB4(0x080031A8);
                                {
                                    register s32 *message_table asm("r1") =
                                        (s32 *)0x087EE170;

                                    asm volatile("" :
                                        "+r"(message_table));
                                    func_080981F0(
                                        message_table[*status_slot_203],
                                        2, 3, 0, 0U);
                                }
                                func_08098BB4(0x0800323E);
                                if (*(u8 *)0x0200A882 == 2) {
                            goto block_287;
                                } else if (*(u8 *)0x0200A880 == 1) {
                            goto block_287;
                                } else {
                                    goto block_212;
                                }
                            } else {
                                *status_address_203 =
                                    (u8) (temp_r0_19 + 1);
block_212:
                                *status_slot_203 = 0U;
                                goto block_213;
                            }
                        } else {
block_213:
                            if ((sp30 == 2) && ({
                                    register u16 *status_slot asm("r0") =
                                        (u16 *)((u8 *)var_r9 + 0x56);
                                    register u16 status_value asm("r1") =
                                        *status_slot;

                                    asm volatile(
                                        ".syntax unified\n\t"
                                        "adds %0, %1, #0\n\t"
                                        ".syntax divided"
                                        : "=l"(status_slot_213)
                                        : "l"(status_slot));
                                    status_value != 0;
                                }) && ((3 & ({
                                    register u8 *catalog asm("r1") =
                                        (u8 *)0x087B2524;

                                    asm volatile("" : "+r"(catalog));
                                    temp_r2_7 = *status_slot_213;
                                    M2C_FIELD(
                                        ((temp_r2_7 * 0x18) + catalog),
                                        u8 *, 0x14);
                                })) == 3)) {
                                register u8 *status_base asm("r0") =
                                    (u8 *)0x020218E4;
                                register u32 status_work asm("r1") =
                                    0x6934;

                                asm volatile("" : "+r"(status_base));
                                asm volatile("" : "+r"(status_work));
                                status_base += status_work;
                                asm volatile("add r1, r2, r0"
                                             : "=r"(status_work)
                                             : "r"(temp_r2_7),
                                               "r"(status_base));
                                temp_r0_20 = *(u8 *)status_work;
                                if (temp_r0_20 == 0x63) {
                                    func_08098BB4(0x080031A8);
                                    {
                                        register s32 *message_table
                                            asm("r1") =
                                                (s32 *)0x087EE170;

                                        asm volatile("" :
                                            "+r"(message_table));
                                        func_080981F0(
                                            message_table[
                                                *status_slot_213],
                                            2, 3, 0, 0U);
                                    }
                                    func_08098BB4(0x0800323E);
                                    if (*(u8 *)0x0200A882 == 2) {
                            goto block_287;
                                    } else if (*(u8 *)0x0200A880 == 1) {
                            goto block_287;
                                    } else {
                                        goto block_223;
                                    }
                                } else {
                                    *(u8 *)status_work =
                                        (u8) (temp_r0_20 + 1);
block_223:
                                    *status_slot_213 = 0U;
                                    goto block_224;
                                }
                            } else {
block_224:
                                func_08092E84(0x4F);
                                {
                                    register u8 *stack_slot_addr asm("r0");

                                    stack_slot_addr = (u8 *)sp + sp54;
                                    stack_slot_addr += 0x14;
                                    asm volatile("" : "+r"(stack_slot_addr));
                                    if (*(s32 *)stack_slot_addr != 0) {
                                        func_08094554();
                                    }
                                }
                                func_080ED17C(1);
                                {
                                    register u32 cleanup_index asm("r5") = 0;

                                    do {
                                        u32 cleanup_mode;

                                        asm volatile(""
                                                     : "=r"(cleanup_mode)
                                                     : "0"(sp30)
                                                     : "r0", "r1");
                                        if (cleanup_index != cleanup_mode) {
                                            register u8 *stack_slot_addr
                                                asm("r0");

                                            stack_slot_addr = (u8 *)sp
                                                + (cleanup_index * 4);
                                            stack_slot_addr += 0x14;
                                            asm volatile("" :
                                                "+r"(stack_slot_addr));
                                            if (*(s32 *)stack_slot_addr != 0) {
                                                func_08094554();
                                            }
                                        }
                                        {
                                            register u32 next_index asm("r0") =
                                                cleanup_index + 1;

                                            next_index <<= 24;
                                            cleanup_index = next_index >> 24;
                                        }
                                    } while (cleanup_index <= 2U);
                                    }
                                func_080E5EFC(sp38, sp24, sp30);
                                goto action_default;
action_switch5:
                func_08092E84(0x58);
                temp_r0_16 = M2C_FIELD(temp_r1_9, u8 *, 0x02032AC8) - 1;
                switch (temp_r0_16) {               /* switch 5; irregular */
                case 0:                             /* switch 5 */
                    if (!(1 & ({
                            register u32 case0_flags asm("r1");

                            asm volatile("ldrh %0, [%1, #2]"
                                         : "=r"(case0_flags)
                                         : "r"(sp40)
                                         : "r0", "r2", "memory");
                            case0_flags;
                        }))) {
                        func_08098BB4(0x08002EFB);
                    } else {
                        func_08098BB4(0x08002F64);
                    }
                    break;
                case 1:                             /* switch 5 */
                    func_08098BB4(0x08002FCD);
                    if ((3 & ({
                            register u32 case1_flags asm("r1");

                            asm volatile("ldrb %0, [%1, #20]"
                                         : "=r"(case1_flags)
                                         : "r"(sp40)
                                         : "r0", "r2", "r3", "memory");
                            case1_flags;
                        })) == 1) {
                        func_080981F0(0x0810650C, 1, 3, 5, 6U);
                    }
                    if ((3 & M2C_FIELD(sp40, u8 *, 0x14)) == 2) {
                        func_080981F0(0x08106510, 1, 3, 4, 6U);
                    }
                    if ((3 & M2C_FIELD(sp40, u8 *, 0x14)) == 3) {
                        func_080981F0(0x08106518, 1, 3, 5, 6U);
                    }
                    break;
                case 2:                             /* switch 5 */
                    func_08098BB4(0x08003053);
                    break;
                case 3:                             /* switch 5 */
                    func_08098BB4(0x080030A5);
                    {
                        register s32 *message_table asm("r1") =
                            (s32 *)0x087F2DEC;

                        asm volatile("" : "+r"(message_table));
                        func_080981F0(
                            message_table[M2C_FIELD(sp40, u8 *, 0x15)],
                            1, 3, 0, 8U);
                    }
                    break;
                case 4:                             /* switch 5 */
                    func_08098BB4(0x08003127);
                    break;
                }
                func_08098BB4(0x080031A2);
                goto block_287;
action_default:
                                {
                                    register u32 cleanup_index asm("r5") = 0;

                                    do {
                                        register u8 *stack_slot_addr
                                            asm("r0");

                                        stack_slot_addr = (u8 *)sp
                                            + (cleanup_index * 4);
                                        stack_slot_addr += 0x14;
                                        asm volatile("" :
                                            "+r"(stack_slot_addr));
                                        if (*(s32 *)stack_slot_addr != 0) {
                                            func_08094554();
                                        }
                                        {
                                            register u32 next_index asm("r0") =
                                                cleanup_index + 1;

                                            next_index <<= 24;
                                            cleanup_index =
                                                next_index >> 24;
                                        }
                                    } while (cleanup_index <= 3U);
                                }
                                func_08095114(*(s32 *)0x02033F3C);
                                func_08094554(sp48);
                                func_08094554(sp4C);
                                func_08094554(sp50);
                                func_08098BB4(0x08002E94);
                                *(u16 *)0x0300004C &= 0xFEFF;
                                *(s16 *)0x0300004E = 0;
                                var_sl = 0x3020;
                            }
                        }
                    }
                }
            goto block_287;
action_0:
            {
            register volatile u16 *input_state asm("r2") =
                (volatile u16 *)0x0200A884;

            asm volatile("" : "+r"(input_state));
            if (0x200 & *input_state) {
                register s32 *camera asm("r4") =
                    (s32 *)0x03000054;
                register s32 camera_value asm("r3") = *camera;
                register s32 camera_limit asm("r0") = 0x87FF;

                if (camera_value <= camera_limit) {
                    register s32 camera_step asm("r5") = 0x800;
                    register s32 camera_next asm("r0") =
                        camera_value + camera_step;

                    *camera = camera_next;
                }
            }
            if (!(0x100 & *input_state)) {

            } else {
                temp_r0_15 = M2C_FIELD((void *)0x03000054, s32 *, 0);
                if (temp_r0_15 <= 0) {

                } else {
                    M2C_FIELD((void *)0x03000054, s32 *, 0) = (s32) (temp_r0_15 + 0xFFFFF800);
                }
            }
            }
        goto block_287;
state_3020_handler:
        {
        register s32 *message_table asm("r4");

        func_08098BB4(0x08002C13);
        temp_r0_30 = func_0809716C(3);
        {
        register u32 zero_3020 asm("r7") = 0;

        asm volatile("" : "+r"(zero_3020));
        M2C_FIELD(temp_r0_30, u8 *, 0x15) = (u8) sp2C;
        M2C_FIELD(temp_r0_30, u8 *, 0x14) = (u8) sp2C;
        M2C_FIELD(temp_r0_30, u8 *, 0x16) = (u8) sp28;
        func_080B61C8(0, 0, 0);
        func_080AC214(3, 0x18);
        func_080ACA8C(7, 1, 1);
        func_080981F0(0x081064C0, 0, 4, 0, zero_3020);
        func_080981F0(0x081064C8, 0, 4, 0, 2U);
        func_080981F0(0x081064D0, 0, 4, 0, 4U);
        func_080981F0(0x081064D8, 0, 4, 0, 6U);
        message_table = (s32 *)0x087EE170;
        asm volatile("" : "+r"(message_table));
        func_080981F0(message_table[M2C_FIELD(var_r9, u16 *, 0x52)], 0, 4, 2, zero_3020);
        func_080981F0(message_table[M2C_FIELD(var_r9, u16 *, 0x56)], 0, 4, 2, 2U);
        func_080981F0(message_table[M2C_FIELD(var_r9, u16 *, 0x5A)], 0, 4, 2, 4U);
        func_080981F0(message_table[M2C_FIELD(var_r9, u16 *, 0x5E)], 0, 4, 2, 6U);
        {
            register u32 type_base asm("r1") = 0x020218E4;
            register u8 *type_entry asm("r2") = var_r9;
            register u32 type_address asm("r0");
            register u32 type_addend asm("r3");

            asm volatile("" : "+r"(type_base));
            type_address = type_entry[2] << 6;
            type_address += type_base;
            type_addend = 0x5A94;
            asm volatile("" : "+r"(type_addend));
            type_address += type_addend;
            func_080981F0(func_080E7B64(*(u8 *)type_address),
                0, 5, 0, zero_3020);
        }
        }
        func_080ACBDC(7, sp2C);
        func_08098BB4(0x08002DD0);
        func_08098BB4(0x08002ECD);
        {
            register s32 line_output asm("r7");
            register u32 row_index_3020 asm("r5");

            row_index_3020 = 0;
            line_output = 0x02030564;
            do {
                func_080ED038(line_output, 0x081064E0, 3);
                {
                    register s32 first_offset_3020 asm("r2") =
                        row_index_3020 * 4;
                    register u32 first_value_3020 asm("r1");
                    register u32 first_address_3020 asm("r0");
                    register u32 first_flag_3020 asm("r0");

                    asm volatile("mov %0, r9"
                                 : "=r"(first_value_3020));
                    first_address_3020 =
                        first_value_3020 + first_offset_3020;
                    first_address_3020 += 0x50;
                    first_value_3020 = *(u16 *)first_address_3020;
                    first_flag_3020 = 1;
                    first_flag_3020 &= first_value_3020;
                    temp_r2_9 = first_offset_3020;
                    if (first_flag_3020) {
                    func_08099F5C(line_output, 0x081064E4);
                    } else {
                        func_08099F5C(line_output, 0x081061C4);
                    }
                }
                {
                    register u8 *record_base asm("r2") = var_r9;
                    register u32 second_address_3020 asm("r0");
                    register u32 second_value_3020 asm("r1");
                    register u32 second_flag_3020 asm("r0");

                    asm volatile("mov %0, r9"
                                 : "=r"(record_base));
                    second_address_3020 =
                        (u32)record_base + temp_r2_9;
                    second_address_3020 += 0x50;
                    second_value_3020 = *(u16 *)second_address_3020;
                    second_flag_3020 = 2;
                    second_flag_3020 &= second_value_3020;
                    if (second_flag_3020) {
                        func_08099F5C(0x02030564, 0x0810637C);
                    } else {
                        func_08099F5C(0x02030564, 0x081061C4);
                    }
                }
                func_08099F5C(line_output, 0x081064E8);
                {
                    register u8 *message_record_3020 asm("r3");
                    register u32 message_address_3020 asm("r0");

                    asm volatile("mov %0, r9"
                                 : "=r"(message_record_3020));
                    message_address_3020 =
                        (u32)message_record_3020 + temp_r2_9;
                    message_address_3020 += 0x52;
                    message_address_3020 =
                        *(u16 *)message_address_3020;
                    func_08099F5C(line_output,
                        message_table[message_address_3020]);
                }
                func_080988C8(8, line_output);
                {
                    register u32 next_index_3020 asm("r0") =
                        row_index_3020 + 1;

                    next_index_3020 <<= 24;
                    row_index_3020 = next_index_3020 >> 24;
                }
            } while (row_index_3020 <= 3U);
        }
        }
        {
            register u8 *state_output asm("r0");
            register u32 state_value asm("r4");

            state_output = func_0809716C(8);
            asm volatile(
                "add %0, sp, #48\n\t"
                "ldrb %0, [%0, #0]"
                : "=r"(state_value)
                : "g"(sp30)
                : "memory");
            M2C_FIELD(state_output, u8 *, 0x16) = state_value;
        }
        var_sl = ({
            register s32 next_state_3020 asm("r5") = 0x2010;

            asm volatile("" : "+r"(next_state_3020));
            next_state_3020;
        });
        asm volatile("" : : "i"(0x1FCE));
        goto block_287;
state_4000_handler:
        sp48 = func_08094484(0x08105AFC, 0x08105B08, 0, 0x60, 0x60, 0x350, 0xF, 8, 0U);
        func_08098BB4(0x0800338A);
        {
        register u32 list_index asm("r5");
        register s32 *row_table asm("r4");

        list_index = 0;
        if (list_index < (u32)*(u8 *)0x02032472) {
            row_table = (s32 *)0x087EDD54;
            do {
                u32 selected;
                register u32 next_index asm("r0");
                register u8 *selection_addr asm("r0") =
                    (u8 *)0x0203246C;

                asm volatile("add %0, %1, %0"
                             : "+r"(selection_addr)
                             : "r"(list_index)
                             : "cc");
                asm volatile("" : : "i"(0x2018));
                selected = func_080E5320(var_r9, *selection_addr);
                selected <<= 24;
                selected >>= 22;
                asm volatile("add %0, %0, %1"
                             : "+r"(selected)
                             : "r"(row_table)
                             : "cc");
                func_080988C8(8, *(s32 *)selected);
                next_index = list_index + 1;
                next_index <<= 24;
                list_index = next_index >> 24;
            } while (list_index < (u32)*(u8 *)0x02032472);
        }
        }
        func_08098BB4(0x080033A0);
        func_08094554(sp48);
        if (*(u8 *)0x0200A882 == 1) {
            {
                register u32 selection_value asm("r0");
                register u8 *selection_state asm("r7");
                register u8 *selection_rows asm("r1") =
                    (u8 *)0x0203246C;
                register u32 selection_index asm("r0");

                asm volatile("" : "+r"(selection_rows));
                selection_index = *(u8 *)0x0200A880;
                asm volatile("add %0, %0, %1"
                             : "+r"(selection_index)
                             : "r"(selection_rows)
                             : "cc");
                func_080E5320(var_r9, *(u8 *)selection_index);
                selection_state = var_r9;
                asm volatile(
                    "strb %0, [%1, #0]\n\t"
                    "ldrb %0, [%1, #2]"
                    : "=r"(selection_value)
                    : "r"(selection_state)
                    : "memory");
                if (selection_value != 0) {
                    register u32 selection_type_base asm("r1");

                    selection_value <<= 6;
                    selection_type_base = 0x02027378;
                    asm volatile("" : "+r"(selection_type_base)
                                 : "r"(selection_value));
                    selection_type_base =
                        selection_value + selection_type_base;
                    var_r1_3 = selection_type_base;
                } else {
                    var_r1_3 = 0;
                }
            }
            func_080E5880(var_r9, var_r1_3);
            func_080ED038(0x02030564, 0x081061C4, 3);
            {
                register s32 *row_table asm("r1") =
                    (s32 *)0x087EDD54;
                register u8 *record asm("r2");

                asm volatile("" : "+r"(row_table));
                asm volatile("mov %0, r9"
                             : "=r"(record));
                func_08099F5C(
                    0x02030564,
                    row_table[M2C_FIELD(record, u8 *, 0)]);
            }
            func_080989EC(3, sp28, 0x02030564);
            var_sl = ({
                register s32 next_state_4000_success asm("r3");

                asm volatile("mov %0, #32"
                             : "=r"(next_state_4000_success));
                next_state_4000_success;
            });
            asm volatile("" : : "i"(0x20D0));
        } else {
            var_r4 = 0x20;
            goto block_286;
        }
        goto block_287;
block_286:
        var_sl = var_r4;
block_287:
        {
            register s32 completion asm("r5") = 0;

            asm volatile("" : "+r"(completion));
            if (completion == 0) {
                goto loop_1;
            }
        }
function_exit:
    func_080E66B8();
}
