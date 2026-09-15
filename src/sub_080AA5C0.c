#include "m2c_prelude.h"
void *func_08094374(M2C_UNK, u8, u8, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094374_4, func_08094374");
void *func_08094374_4(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_08094564(void *, u16);                 /* extern */
u16 func_080A9A54(void *);                          /* extern */
M2C_UNK func_080A9AFC(void *);                      /* extern */
M2C_UNK func_080AA550(s32);                         /* extern */
u16 func_080ECD24(s16, s16);                        /* extern */
u16 func_080ECD3C(s32);                             /* extern */
extern s32 D_087A1B98[][2];
M2C_UNK jtbl_080AA660();                            /* static */
M2C_UNK jtbl_080AA894();                            /* static */

void sub_080AA5C0(u32 arg0, void *arg1_in) {
    register void *arg1 asm("r6") = arg1_in;
    s32 sp14;
    s32 *var_r1;
    register s32 temp_r0_12 asm("r0");
    s32 temp_r0_14;
    s32 temp_r0_15;
    s32 temp_r0_16;
    s32 temp_r0_21;
    volatile s32 outgoing0;
    volatile s32 outgoing1;
    volatile s32 outgoing2;
    volatile s32 outgoing3;
    volatile s32 outgoing4;
    register u32 command_base asm("r9");
    register s32 *counter_base asm("r0");
    register s32 temp_r1 asm("sl");
    s32 temp_r1_3;
    register s32 temp_r2 asm("r8");
    s32 var_r0;
    s32 var_r0_10;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    u16 temp_r0;
    u16 temp_r0_10;
    register s32 temp_r0_11 asm("r0");
    u16 temp_r0_17;
    u16 temp_r0_18;
    register u32 temp_r0_19 asm("r0");
    u16 temp_r0_2;
    u16 temp_r0_8;
    u16 temp_r0_9;
    u16 temp_r1_5;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r0_5;
    u32 temp_r0_6;
    u32 temp_r0_7;
    s32 temp_r1_2;
    u32 temp_r2_3;
    u32 temp_r3;
    register u32 temp_r3_2 asm("r3");
    register u32 var_r0_8 asm("r0");
    u8 *var_r7;
    register u8 *scan_base asm("r3");
    register u8 *direction_base asm("r2");
    register u8 *direction_address asm("r0");
    register u16 *command_arg_ptr asm("r5");
    register u32 sprite_delta asm("r0");
    register u8 *status_base asm("r1");
    register s32 status_offset asm("r4");
    register u8 *status_address asm("r0");
    register u8 *case_command_base asm("r4");
    register u8 *case_command_address asm("r0");
    u8 scan_type;
    s32 temp_r0_13;
    u8 temp_r4_5;
    u8 var_r0_4;
    u8 var_r1_2;
    void *temp_r0_20;
    void *temp_r2_2;
    void *temp_r2_4;
    void *temp_r4;
    void *temp_r4_2;
    void *temp_r4_3;
    register void *temp_r4_4 asm("r4");
    void *temp_r5;
    void *temp_r5_2;
    void *temp_r5_3;
    void *temp_r5_4;
    void *temp_r5_5;
    void *temp_r5_6;

    asm volatile("" : "=m"(outgoing0), "=m"(outgoing1), "=m"(outgoing2),
                 "=m"(outgoing3), "=m"(outgoing4));
    arg0 <<= 24;
    arg0 >>= 24;
    sp14 = (s32)arg0;
    if (M2C_FIELD(arg1, s32 *, 0) & 2) {
        register s32 zero asm("r4") = 0;

        M2C_FIELD(arg1, u8 *, 0x18) = (u8)zero;
        temp_r5 = M2C_FIELD(arg1, void **, 0x20);
        func_08094564(temp_r5, func_080A9A54(arg1));
        M2C_FIELD(arg1, s32 *, 0x14) = zero;
        M2C_FIELD(arg1, s32 *, 0x10) = zero;
        return;
    }
    counter_base = (s32 *)0x02031468;
    temp_r1 = sp14 * 4;
    temp_r2 = sp14 << 8;
    goto loop_48;
block_counter:
    if (M2C_FIELD(arg1, u8 *, 0x18) != 4) {
        var_r0 = temp_r3 - 1;
        goto block_5;
    }
    goto block_9;
block_5:
    *var_r1 = var_r0;
block_6:
    if (M2C_FIELD(arg1, u8 *, 0x18) != 4) {
        if (M2C_FIELD(temp_r1, u32 *, 0x02031468) != 0) {
            goto block_11;
        }
        goto block_37;
    }
block_9:
    if (M2C_FIELD(M2C_FIELD(arg1, void **, 0x20), s32 *, 0) & 4) {
        goto block_37;
    }
block_11:
    temp_r0_3 = M2C_FIELD(temp_r2, u16 *, 0x02030668) - 0x38;
    switch (temp_r0_3) {                            /* switch 1; irregular */
    case 0:                                         /* switch 1 */
    case 8:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        break;
    case 1:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x10) = D_087A1B98[M2C_FIELD(arg1, u8 *, 0x1A)][0] / 2;
        M2C_FIELD(arg1, s32 *, 0x14) = D_087A1B98[M2C_FIELD(arg1, u8 *, 0x1A)][1] / 2;
        break;
    case 2:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x10) = D_087A1B98[M2C_FIELD(arg1, u8 *, 0x1A)][0];
        M2C_FIELD(arg1, s32 *, 0x14) = D_087A1B98[M2C_FIELD(arg1, u8 *, 0x1A)][1];
        break;
    case 3:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x10) = D_087A1B98[M2C_FIELD(arg1, u8 *, 0x1A)][0] * 2;
        M2C_FIELD(arg1, s32 *, 0x14) = D_087A1B98[M2C_FIELD(arg1, u8 *, 0x1A)][1] * 2;
        break;
    case 4:                                         /* switch 1 */
    case 5:                                         /* switch 1 */
    case 6:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        temp_r2_3 = M2C_FIELD(arg1, u32 *, 0x38) + M2C_FIELD(arg1, s32 *, 0x28);
        M2C_FIELD(arg1, u32 *, 0x38) = temp_r2_3;
        M2C_FIELD(arg1, u32 *, 0x3C) = (u32) (M2C_FIELD(arg1, u32 *, 0x3C) + M2C_FIELD(arg1, s32 *, 0x2C));
        temp_r3_2 = M2C_FIELD(arg1, u32 *, 0x40);
        if (temp_r2_3 >= temp_r3_2) {
            register s32 direction asm("r2") = M2C_FIELD(arg1, s32 *, 0x30);
            register s32 positive asm("r5") = 0x100;
            register s32 negative asm("r4") = 0xFFFFFF00;
            register u32 threshold asm("r1") = temp_r3_2;

            do {
                if (direction == 0) {
                    var_r0_2 = M2C_FIELD(arg1, s32 *, 0x10) + positive;
                } else {
                    var_r0_2 = M2C_FIELD(arg1, s32 *, 0x10) + negative;
                }
                M2C_FIELD(arg1, s32 *, 0x10) = var_r0_2;
                temp_r0_6 = M2C_FIELD(arg1, u32 *, 0x38) - threshold;
                M2C_FIELD(arg1, u32 *, 0x38) = temp_r0_6;
            } while (temp_r0_6 >= threshold);
        }
        if ((u32) M2C_FIELD(arg1, u32 *, 0x3C) >= temp_r3_2) {
            register s32 direction asm("r2") = M2C_FIELD(arg1, s32 *, 0x34);
            register s32 positive asm("r5") = 0x100;
            register s32 negative asm("r4") = 0xFFFFFF00;
            register u32 threshold asm("r1") = temp_r3_2;

            do {
                if (direction == 0) {
                    var_r0_3 = M2C_FIELD(arg1, s32 *, 0x14) + positive;
                } else {
                    var_r0_3 = M2C_FIELD(arg1, s32 *, 0x14) + negative;
                }
                M2C_FIELD(arg1, s32 *, 0x14) = var_r0_3;
                temp_r0_7 = M2C_FIELD(arg1, u32 *, 0x3C) - threshold;
                M2C_FIELD(arg1, u32 *, 0x3C) = temp_r0_7;
            } while (temp_r0_7 >= threshold);
        }
        break;
    case 7:                                         /* switch 1 */
        temp_r2_4 = M2C_FIELD(arg1, void **, 0x20);
        sprite_delta = (u32)(M2C_FIELD(temp_r1, u32 *, 0x02031468) - 1) >> 1;
        sprite_delta -= 3;
        asm volatile("" : "+r"(sprite_delta));
        M2C_FIELD(temp_r2_4, u16 *, 0xA) = (u16)(M2C_FIELD(temp_r2_4, u16 *, 0xA) - sprite_delta);
        break;
    }
    goto block_46;
block_37:
    status_base = (u8 *)0x02030668;
    status_offset = temp_r2;
    status_address = (u8 *)((u32)status_offset - (0U - (u32)status_base));
    temp_r0_2 = *(u16 *)status_address;
    if (temp_r0_2 == 0x40) {
        if (M2C_FIELD(arg1, u8 *, 4) == 0x36) {
            status_address = status_base + 2;
            status_address += temp_r2;
            if (*(u16 *)status_address == 1) {
                M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0xFFFFF800);
                func_08094554(M2C_FIELD(arg1, void **, 0x20));
                func_080A9AFC(arg1);
                temp_r4_2 = M2C_FIELD(arg1, void **, 0x20);
                func_08094564(temp_r4_2, func_080A9A54(arg1));
            }
        }
        {
            register u8 *status_counter_address asm("r0") = (u8 *)0x02031468;
            register u32 status_counter_value asm("r1");

            status_counter_address += temp_r1;
            status_counter_value = 0;
            *(u32 *)status_counter_address = status_counter_value;
        }
    } else if (temp_r0_2 != 0x38) {
        register s32 zero asm("r4") = 0;

        M2C_FIELD(arg1, u8 *, 0x18) = (u8)zero;
        temp_r5_3 = M2C_FIELD(arg1, void **, 0x20);
        func_08094564(temp_r5_3, func_080A9A54(arg1));
        M2C_FIELD(arg1, s32 *, 0x14) = zero;
        M2C_FIELD(arg1, s32 *, 0x10) = zero;
    }
    func_080AA550(sp14);
    M2C_FIELD(arg1, u8 *, 0x19) = (u8) M2C_FIELD(arg1, u8 *, 0x18);
block_46:
    counter_base = (s32 *)0x02031468;
    if (*(u32 *)((u32)temp_r1 - (0U - (u32)counter_base)) != 0) {
        return;
    }
loop_48:
    var_r1 = (s32 *)((u32)temp_r1 - (0U - (u32)counter_base));
    temp_r3 = (u32)*var_r1;
    if (temp_r3 != 0) {
        goto block_counter;
    }
    if (M2C_FIELD(temp_r2, u16 *, 0x02030668) == 0) {
        goto block_empty;
    }
    if (M2C_FIELD(arg1, u8 *, 0x18) == 4) {
        temp_r2_2 = M2C_FIELD(arg1, void **, 0x20);
        if (M2C_FIELD(temp_r2_2, s32 *, 0x18) == 0x083554B4) {
            *(s16 *)0x0300004E = (s16) temp_r3;
        }
        func_08094554(temp_r2_2);
        if (M2C_FIELD(arg1, void **, 0x24) != 0) {
            func_08094554(M2C_FIELD(arg1, void **, 0x24));
        }
        func_080A9AFC(arg1);
    }
    {
        register u8 *command_seed asm("r0") = (u8 *)0x02030668;
        register s32 command_offset asm("r2") = temp_r2;
        register s32 dispatch asm("r1");

        dispatch = *(u16 *)((u32)command_offset -
                            (0U - (u32)command_seed)) - 0x38;
        asm volatile("" : "+r"(dispatch));
        command_base = (u32)command_seed;
        temp_r1_2 = dispatch;
    }
    switch (temp_r1_2) {                            /* switch 2; irregular */
    case 0:                                         /* switch 2 */
        M2C_FIELD(arg1, u8 *, 0x18) = 0U;
        case_command_base = (u8 *)0x02030668;
        asm volatile("" : "+r"(case_command_base));
        case_command_address = case_command_base + 2;
        case_command_address += temp_r2;
        temp_r0 = *(u16 *)case_command_address;
        M2C_FIELD(arg1, u8 *, 0x1B) = (u8) temp_r0;
        M2C_FIELD(arg1, u8 *, 0x1A) = (u8) temp_r0;
        temp_r5_2 = M2C_FIELD(arg1, void **, 0x20);
        func_08094564(temp_r5_2, func_080A9A54(arg1));
        var_r1 = temp_r1 + 0x02031468;
        case_command_base += 4;
        case_command_base += temp_r2;
        var_r0 = (s32)*(u16 *)case_command_base;
        goto block_5;
    case 1:                                         /* switch 2 */
        M2C_FIELD(arg1, u8 *, 0x18) = 2U;
        case_command_base = (u8 *)0x02030668;
        asm volatile("" : "+r"(case_command_base));
        case_command_address = case_command_base + 2;
        case_command_address += temp_r2;
        temp_r0_8 = *(u16 *)case_command_address;
        M2C_FIELD(arg1, u8 *, 0x1B) = (u8) temp_r0_8;
        M2C_FIELD(arg1, u8 *, 0x1A) = (u8) temp_r0_8;
        temp_r5_4 = M2C_FIELD(arg1, void **, 0x20);
        func_08094564(temp_r5_4, func_080A9A54(arg1));
        var_r1 = temp_r1 + 0x02031468;
        case_command_base += 4;
        case_command_base += temp_r2;
        var_r0 = *(u16 *)case_command_base * 0x10;
        goto block_5;
    case 2:                                         /* switch 2 */
        M2C_FIELD(arg1, u8 *, 0x18) = 2U;
        case_command_base = (u8 *)0x02030668;
        asm volatile("" : "+r"(case_command_base));
        case_command_address = case_command_base + 2;
        case_command_address += temp_r2;
        temp_r0_9 = *(u16 *)case_command_address;
        M2C_FIELD(arg1, u8 *, 0x1B) = (u8) temp_r0_9;
        M2C_FIELD(arg1, u8 *, 0x1A) = (u8) temp_r0_9;
        temp_r5_5 = M2C_FIELD(arg1, void **, 0x20);
        func_08094564(temp_r5_5, func_080A9A54(arg1));
        var_r1 = temp_r1 + 0x02031468;
        case_command_base += 4;
        case_command_base += temp_r2;
        var_r0 = *(u16 *)case_command_base * 8;
        goto block_5;
    case 3:                                         /* switch 2 */
        M2C_FIELD(arg1, u8 *, 0x18) = 3U;
        case_command_base = (u8 *)0x02030668;
        asm volatile("" : "+r"(case_command_base));
        case_command_address = case_command_base + 2;
        case_command_address += temp_r2;
        temp_r0_10 = *(u16 *)case_command_address;
        M2C_FIELD(arg1, u8 *, 0x1B) = (u8) temp_r0_10;
        M2C_FIELD(arg1, u8 *, 0x1A) = (u8) temp_r0_10;
        temp_r5_6 = M2C_FIELD(arg1, void **, 0x20);
        func_08094564(temp_r5_6, func_080A9A54(arg1));
        var_r1 = temp_r1 + 0x02031468;
        case_command_base += 4;
        case_command_base += temp_r2;
        var_r0 = *(u16 *)case_command_base * 4;
        goto block_5;
    case 4:                                         /* switch 2 */
    case 5:                                         /* switch 2 */
    case 6:                                         /* switch 2 */
        temp_r0_11 = *(u16 *)((u32)temp_r2 - (0U - command_base));
        switch (temp_r0_11) {                       /* switch 3; irregular */
        case 0x3C:                                  /* switch 3 */
            M2C_FIELD(arg1, u8 *, 0x18) = 1U;
            break;
        case 0x3D:                                  /* switch 3 */
            M2C_FIELD(arg1, u8 *, 0x18) = 2U;
            break;
        case 0x3E:                                  /* switch 3 */
            M2C_FIELD(arg1, u8 *, 0x18) = 3U;
            break;
        }
        direction_base = (u8 *)0x02030668;
        asm volatile("" : "+r"(direction_base));
        direction_address = direction_base + 2;
        direction_address += temp_r2;
        temp_r1_3 = *(u16 *)direction_address * 8;
        var_r0_5 = M2C_FIELD(arg1, s32 *, 8);
        if (var_r0_5 < 0) {
            var_r0_5 += 0xFF;
        }
        temp_r1_3 -= var_r0_5 >> 8;
        M2C_FIELD(arg1, s32 *, 0x28) = temp_r1_3;
        {
            register u32 y_raw asm("r0");
            register s32 y_component asm("r2");

            direction_address = direction_base + 4;
            direction_address += temp_r2;
            y_raw = *(u16 *)direction_address;
            asm volatile("" : "+r"(y_raw));
            y_component = y_raw * 8;
            var_r0_6 = M2C_FIELD(arg1, s32 *, 0xC);
            if (var_r0_6 < 0) {
                var_r0_6 += 0xFF;
            }
            temp_r0_12 = y_component - (var_r0_6 >> 8);
        }
        M2C_FIELD(arg1, s32 *, 0x2C) = temp_r0_12;
        {
            register u32 raw asm("r0");
            register u32 normalized asm("r1");
            register s32 bias asm("r4");
            register u32 sum asm("r0");
            register s32 quotient asm("r1");
            register s32 remainder asm("r0");
            register s32 sign_zero asm("r1");

            raw = func_080ECD24((s16)(0 - temp_r0_12), (s16)temp_r1_3);
            raw <<= 16;
            normalized = raw >> 16;
            bias = 0x80;
            bias <<= 5;
            sum = normalized + bias;
            asm volatile("" : "+r"(sum));
            quotient = (s32)sum >> 0xD;
            remainder = quotient;
            asm volatile("" : "+r"(remainder));
            remainder >>= 3;
            remainder <<= 3;
            remainder = quotient - remainder;
            temp_r0_13 = remainder;
            sign_zero = 0;
            asm volatile("" : "+r"(sign_zero));
            M2C_FIELD(arg1, u8 *, 0x1B) = temp_r0_13;
            M2C_FIELD(arg1, u8 *, 0x1A) = temp_r0_13;
            temp_r0_14 = M2C_FIELD(arg1, s32 *, 0x28);
            if (temp_r0_14 >= 0) {
                M2C_FIELD(arg1, s32 *, 0x30) = sign_zero;
            } else {
                M2C_FIELD(arg1, s32 *, 0x28) = (s32) (0 - temp_r0_14);
                M2C_FIELD(arg1, s32 *, 0x30) = 1;
            }
        }
        temp_r0_15 = M2C_FIELD(arg1, s32 *, 0x2C);
        if (temp_r0_15 >= 0) {
            var_r0_7 = 0;
        } else {
            M2C_FIELD(arg1, s32 *, 0x2C) = (s32) (0 - temp_r0_15);
            var_r0_7 = 1;
        }
        M2C_FIELD(arg1, s32 *, 0x34) = var_r0_7;
        M2C_FIELD(arg1, u32 *, 0x3C) = 0U;
        M2C_FIELD(arg1, u32 *, 0x38) = 0U;
        temp_r0_16 = M2C_FIELD(arg1, s32 *, 0x28);
        {
            register s32 first_product asm("r4");
            register s32 first_sum asm("r0");
            register s32 second_value asm("r1");
            register s32 second_product asm("r2");
            register s32 second_sum asm("r1");
            register u32 sqrt_shift asm("r2");

            first_product = temp_r0_16;
            first_product *= temp_r0_16;
            asm volatile("" : "+r"(first_product));
            first_sum = first_product;
            asm volatile("" : "+r"(first_sum));
            second_value = M2C_FIELD(arg1, s32 *, 0x2C);
            second_product = second_value;
            second_product *= second_value;
            second_sum = second_product;
            temp_r0_17 = func_080ECD3C(first_sum + second_sum);
            sqrt_shift = (u32)temp_r0_17 << 16;
            temp_r1_5 = sqrt_shift >> 16;
            M2C_FIELD(arg1, u32 *, 0x40) = (u32)temp_r1_5;
            temp_r0_18 = M2C_FIELD(temp_r2, u16 *, 0x02030668);
            if (temp_r0_18 == 0x3C) {
                var_r0_8 = temp_r1_5 * 2;
                goto block_95;
            }
            if (temp_r0_18 == 0x3E) {
                var_r0_8 = sqrt_shift >> 17;
block_95:
                M2C_FIELD(arg1, u32 *, 0x40) = var_r0_8;
            }
        }
        temp_r4_3 = M2C_FIELD(arg1, void **, 0x20);
        func_08094564(temp_r4_3, func_080A9A54(arg1));
        {
            register u8 *case_counter_address asm("r0") = (u8 *)0x02031468;
            register u32 case_counter_value asm("r1");

            case_counter_address += temp_r1;
            case_counter_value = M2C_FIELD(arg1, u32 *, 0x40);
            *(u32 *)case_counter_address = case_counter_value;
            asm volatile("");
        }
        goto block_6;
    case 7:                                         /* switch 2 */
        {
            register u8 *case_counter_address asm("r0") = (u8 *)0x02031468;
            register u32 case_counter_value asm("r1");

            case_counter_address += temp_r1;
            case_counter_value = 0xE;
            *(u32 *)case_counter_address = case_counter_value;
            asm volatile("");
        }
        goto block_6;
    case 8:                                         /* switch 2 */
        var_r1_2 = 0;
        var_r7 = (u8 *)0x087A1C18;
        scan_type = M2C_FIELD(arg1, u8 *, 4);
        scan_base = var_r7;
        goto loop_scan_test;
loop_104:
        var_r1_2 += 1;
        temp_r0_21 = var_r1_2 * 0x24;
        var_r7 = (u8 *)((u32)temp_r0_21 - (0U - (u32)scan_base));
        if (*var_r7 == 0xFF) {
            goto block_46;
        }
loop_scan_test:
        if (*var_r7 != scan_type) {
            goto loop_104;
        }
        {
            register u8 *command_address asm("r0") = (u8 *)command_base;
            register s32 command_offset asm("r4");

            command_address += 2;
            command_offset = temp_r2;
            command_arg_ptr = (u16 *)((u32)command_offset -
                                      (0U - (u32)command_address));
            temp_r0_19 = *command_arg_ptr;
        }
        if ((u32)temp_r0_19 > 7U) {
            goto loop_104;
        }
        temp_r4_4 = var_r7 + ((temp_r0_19 * 4) + 4);
        if (M2C_FIELD(temp_r4_4, u8 *, 0) == 0xFF) {
            goto loop_104;
        }
        {
            register s32 zero_seed asm("r0") = 0;
            command_base = zero_seed;
        }
        M2C_FIELD(arg1, u8 *, 0x18) = 4U;
        func_08094554(M2C_FIELD(arg1, void **, 0x20));
        {
            register void *descriptor_ip asm("ip");
            register u32 call_type asm("r1");
            register u32 call_variant asm("r2");
            register s32 call_x asm("r3");
            register s32 stack_r0 asm("r0");

            {
                register void *descriptor_seed asm("r1") = (void *)0x087ADAF8;
                descriptor_ip = descriptor_seed;
            }
            call_type = M2C_FIELD(temp_r4_4, u8 *, 0);
            call_variant = M2C_FIELD(temp_r4_4, u8 *, 1);
            {
                register s32 call_x_raw asm("r0");

                call_x_raw = M2C_FIELD(arg1, s32 *, 8);
                if (call_x_raw < 0) {
                    call_x_raw += 0xFF;
                }
                call_x_raw <<= 8;
                call_x = call_x_raw >> 0x10;
            }
            var_r0_10 = M2C_FIELD(arg1, s32 *, 0xC);
            if (var_r0_10 < 0) {
                var_r0_10 += 0xFF;
            }
            stack_r0 = (s32)(var_r0_10 << 8) >> 0x10;
            asm volatile("str %0, [sp, #0]" : "+r"(stack_r0) : : "memory");
            stack_r0 = M2C_FIELD(arg1, u8 *, 5) * 0x10;
            asm volatile("str %0, [sp, #4]" : "+r"(stack_r0) : : "memory");
            stack_r0 = M2C_FIELD(arg1, u8 *, 5);
            asm volatile("str %0, [sp, #8]" : "+r"(stack_r0) : : "memory");
            stack_r0 = 0x4410D0;
            asm volatile("str %0, [sp, #12]" : "+r"(stack_r0) : : "memory");
            stack_r0 = command_base;
            asm volatile("str %0, [sp, #16]" : "+r"(stack_r0) : : "memory");
            temp_r0_20 = func_08094374_4((M2C_UNK)descriptor_ip, call_type,
                                         call_variant, call_x);
        }
        M2C_FIELD(arg1, void **, 0x20) = temp_r0_20;
        if (M2C_FIELD(temp_r4_4, u8 *, 3) == 0) {
            M2C_FIELD(temp_r0_20, u16 *, 0xA) = (u16) (M2C_FIELD(temp_r0_20, u16 *, 0xA) - 2);
        }
        temp_r4_5 = M2C_FIELD(temp_r4_4, u8 *, 2);
        if (temp_r4_5 == 0) {
            func_08094554(M2C_FIELD(arg1, void **, 0x24));
            M2C_FIELD(arg1, void **, 0x24) = (void *) temp_r4_5;
        }
        if ((M2C_FIELD(arg1, u8 *, 4) == 0x34) && (*command_arg_ptr == 0)) {
            M2C_FIELD(M2C_FIELD(arg1, void **, 0x20), s32 *, 0x24) = 0x080AA59D;
        }
        M2C_FIELD(temp_r1, u32 *, 0x02031468) = 1U;
        if (*var_r7 == 0xFF) {
            goto block_46;
        }
        goto block_6;
    }
    goto block_6;
block_empty:
    {
        register u32 current_state asm("r0") = M2C_FIELD(arg1, u8 *, 0x18);
        register u32 previous_state asm("r1") = M2C_FIELD(arg1, u8 *, 0x19);

        asm volatile("" : "+r"(previous_state));
        if (current_state != previous_state) {
            temp_r4 = M2C_FIELD(arg1, void **, 0x20);
            func_08094564(temp_r4, func_080A9A54(arg1));
            M2C_FIELD(arg1, u8 *, 0x19) = (u8) M2C_FIELD(arg1, u8 *, 0x18);
        }
    }
    return;
}
