#include "m2c_prelude.h"

M2C_UNK func_0809534C();
void func_080966B4(s32, s32, s32);
s32 func_080ECD30(s32, s32);
s16 func_080ECD98(s32, u8);
extern volatile s16 D_0300004E;
extern volatile s16 D_03000052;
extern u16 D_03005EEA[];
extern u16 D_03005EEE[];
extern u8 D_03005F71;
extern u8 D_03005F72;

struct Frame96774 {
    s16 *output;
    void *next_input;
    u8 add4;
    u8 pad9[3];
    u8 add8;
    u8 padD[3];
    s16 *next_output;
};

void sub_08096774(s32 arg3) {
    volatile struct Frame96774 frame;
    s32 temp_r0_2;
    s32 temp_r2_4;
    s32 temp_r2_6;
    s32 var_r0_10;
    s32 var_r0_11;
    s32 var_r4;
    s32 var_r4_2;
    register s8 *var_r1 asm("r1");
    register s8 *var_r1_2 asm("r1");
    register u32 var_r3_2 asm("r3");
    register volatile u8 *dispatch_state_r7 asm("r7");
    register volatile u8 *case12_progress_r7 asm("r7");
    register volatile u8 *case12_limit_r8 asm("r8");
    register u32 case12_one_r6 asm("r6");
    register u32 case12_zero_r5 asm("r5");
    register u32 case12_successor_ip asm("ip");
    register volatile u8 *case13_progress_r7 asm("r7");
    register u32 case13_zero_r6 asm("r6");
    register u32 case13_one_r5 asm("r5");
    register u32 case13_successor_ip asm("ip");
    u32 temp_r0;
    u32 temp_r0_6;
    u32 var_r3_3;
    u32 var_r3_4;
    u8 temp_r1;
    u8 temp_r1_2;
    register u32 temp_r2_3 asm("r2");
    register u32 temp_r2_5 asm("r2");
    register u32 var_r3 asm("r3");
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;

    (void)arg3;
    temp_r1 = *(u8 *)0x03005F70;
    if (temp_r1 != 0) {
        goto block_2;
    }
    return;
block_2:
    if (!(0x80 & temp_r1)) {
        goto block_14;
    }
    temp_r0 = 0x3F;
    temp_r0 &= temp_r1;
    temp_r0 -= 1;
    if (temp_r0 > 0xFU) {
        goto block_14;
    }
    switch (temp_r0) {
case 0:
case 2:
case 4:
case 6:
case 8:
case 9:
case 12:
case 14:
    {
        register u32 result_r1 asm("r1");

        result_r1 = 0x10 - func_080ECD30(
            *(u8 *)0x03005F72 * 0x10, *(u8 *)0x03005F71);
        asm volatile(
            "lsl %1, %1, #24\n\t"
            "lsr %0, %1, #24"
            : "=r"(var_r3), "+r"(result_r1)
            :
            : "cc");
    }
    if (!(0x80 & *(u8 *)0x03005F70)) {
        goto block_14;
    }
    if (var_r3 != 0) {
        goto block_11;
    }
    goto block_13;
case 1:
case 3:
case 5:
case 7:
case 10:
case 11:
case 13:
case 15:
    {
        register u32 result_r0 asm("r0");

        result_r0 = func_080ECD30(
            *(u8 *)0x03005F72 * 0x10, *(u8 *)0x03005F71);
        asm volatile(
            "lsl %1, %1, #24\n\t"
            "lsr %0, %1, #24"
            : "=r"(var_r3), "+r"(result_r0)
            :
            : "cc");
    }
    if (!(0x80 & *(u8 *)0x03005F70)) {
        goto block_14;
    }
    if (var_r3 == 0) {
        goto block_13;
    }
block_11:
    {
        register u32 result_r0 asm("r0") = var_r3 - 1;

        asm volatile(
            "lsl %1, %1, #24\n\t"
            "lsr %0, %1, #24"
            : "=r"(var_r3), "+r"(result_r0)
            :
            : "cc");
    }
    {
        register u32 packed_r0 asm("r0");
        register volatile s16 *destination_r2 asm("r2") =
            (volatile s16 *)0x03005F78;

        asm volatile(
            "lsl %0, %2, #4\n\t"
            "orr %0, %2\n\t"
            "lsl r1, %2, #8\n\t"
            "orr %0, r1\n\t"
            "lsl r1, %2, #12\n\t"
            "orr %0, r1\n\t"
            "strh %0, [%1]"
            : "=&r"(packed_r0)
            : "r"(destination_r2), "r"(var_r3)
            : "r1", "cc", "memory");
    }
    goto block_14;
block_13:
    *(s16 *)0x03005F78 = (s16)var_r3;
    }
block_14:
    temp_r1_2 = *(u8 *)0x03005F70;
    if (0x40 & temp_r1_2) {
        goto block_26;
    }
    temp_r0_2 = 0x3F & temp_r1_2;
    if (temp_r0_2 == 2) {
        goto block_25;
    }
    if (temp_r0_2 > 2) {
        goto block_20;
    }
    if (temp_r0_2 == 1) {
        goto block_23;
    }
    goto block_48;
block_20:
    if (temp_r0_2 == 3) {
        goto block_23;
    }
    if (temp_r0_2 == 4) {
        goto block_25;
    }
    goto block_48;
block_23:
    {
        register volatile s16 *destination_r4 asm("r4") =
            (volatile s16 *)0x03000052;
        *destination_r4 = 0x10 - func_080ECD30(
            *(u8 *)0x03005F72 * 0x10, *(u8 *)0x03005F71);
    }
    goto block_48;
block_25:
    {
        register volatile s16 *destination_r4 asm("r4") =
            (volatile s16 *)0x03000052;
        *destination_r4 = (s16)func_080ECD30(
            *(u8 *)0x03005F72 * 0x10, *(u8 *)0x03005F71);
    }
    goto block_48;
block_26:
    {
        register u8 *record_r2 asm("r2");
        register volatile u8 *limit_r9 asm("r9");
        register u32 base0_sl asm("sl");
        register u32 channel0_phase_r8 asm("r8");
        register u32 channel0_value_r4 asm("r4");
        register u32 channel1_phase_r6 asm("r6");
        u32 channel1_value_r7;
        register u32 successor_ip asm("ip");

        record_r2 = (u8 *)0x02000F40;
        frame.output = (s16 *)0x02000B40;
        var_r3_2 = 0;
        {
            register volatile u8 *limit_birth_r1 asm("r1") =
                (volatile u8 *)0x03005F71;
            register volatile u8 *limit_birth_r8 asm("r8");

            asm volatile("" : "+r"(limit_birth_r1));
            limit_birth_r8 = limit_birth_r1;
            asm volatile("" : "+r"(limit_birth_r8));
            limit_r9 = limit_birth_r8;
        }
loop_27:
        {
            register u32 phase0_r0 asm("r0") = record_r2[2];
            register u32 base0_r4 asm("r4") = record_r2[0];
            register u8 *next_input_r5 asm("r5");
            register u32 limit_value_r3 asm("r3");

            asm volatile("" : "+r"(base0_r4));
            base0_sl = base0_r4;
            asm volatile(
                "ldrb r1, [%0, #4]\n\t"
                "mov r5, sp\n\t"
                "strb r1, [r5, #8]\n\t"
                "ldrb r4, [%0, #8]\n\t"
                "strb r4, [r5, #12]"
                :
                : "l"(record_r2)
                : "r1", "r4", "r5", "memory");
            next_input_r5 = record_r2;
            next_input_r5 += 0xC;
            frame.next_input = next_input_r5;
            frame.next_output = frame.output + 1;
            successor_ip = var_r3_2 + 1;
            asm volatile(
                "mov %0, %1\n\t"
                "ldrb %0, [%0]"
                : "=&r"(limit_value_r3)
                : "r"(limit_r9)
                : "memory");
            if (phase0_r0 < limit_value_r3) {
                goto block_33;
            }
        }
        {
            register u32 direction0_r4 asm("r4") = record_r2[1];
            register volatile u8 *inner_limit_r3 asm("r3") =
                (volatile u8 *)0x03005F71;
            register s32 temp_r0_3 asm("r0");

loop_29:
            if (direction0_r4 != 0) {
                goto block_31;
            }
            var_r0 = record_r2[3] + 1;
            goto block_32;
block_31:
            var_r0 = record_r2[3] - 1;
block_32:
            record_r2[3] = var_r0;
            asm volatile(
                "ldrb %0, [%1, #2]\n\t"
                "ldrb r1, [%2]\n\t"
                "sub %0, %0, r1"
                : "=r"(temp_r0_3)
                : "r"(record_r2), "r"(inner_limit_r3)
                : "r1", "cc", "memory");
            record_r2[2] = temp_r0_3;
            temp_r0_3 = (u8)temp_r0_3;
            {
                register u32 compare_limit_r5 asm("r5");

                asm volatile("ldrb %0, [%1]"
                             : "=r"(compare_limit_r5)
                             : "r"(inner_limit_r3)
                             : "memory");
                if ((u32)temp_r0_3 >= compare_limit_r5) {
                    goto loop_29;
                }
            }
        }
block_33:
        {
            register u32 phase1_r0 asm("r0") = record_r2[6];
            register u32 limit_value_r3 asm("r3");

            channel0_phase_r8 = record_r2[2];
            channel0_value_r4 = record_r2[3];
            asm volatile(
                "mov %0, %1\n\t"
                "ldrb %0, [%0]"
                : "=&r"(limit_value_r3)
                : "r"(limit_r9)
                : "memory");
            if (phase1_r0 < limit_value_r3) {
                goto block_40;
            }
        }
        {
            register u32 direction1_r5 asm("r5") = record_r2[5];
            register volatile u8 *inner_limit_r3 asm("r3") =
                (volatile u8 *)0x03005F71;
            register s32 temp_r0_4 asm("r0");

loop_35:
            if (direction1_r5 != 0) {
                goto block_38;
            }
            var_r0_2 = record_r2[7] + 1;
            goto block_39;
block_38:
            var_r0_2 = record_r2[7] - 1;
block_39:
            record_r2[7] = var_r0_2;
            asm volatile(
                "ldrb %0, [%1, #6]\n\t"
                "ldrb r1, [%2]\n\t"
                "sub %0, %0, r1"
                : "=r"(temp_r0_4)
                : "r"(record_r2), "r"(inner_limit_r3)
                : "r1", "cc", "memory");
            record_r2[6] = temp_r0_4;
            temp_r0_4 = (u8)temp_r0_4;
            if ((u32)temp_r0_4 >= (u32)*inner_limit_r3) {
                goto loop_35;
            }
        }
block_40:
        {
            register u32 phase2_r0 asm("r0") = record_r2[0xA];
            register u32 limit_value_r3 asm("r3");

            channel1_phase_r6 = record_r2[6];
            channel1_value_r7 = record_r2[7];
            asm volatile(
                "mov %0, %1\n\t"
                "ldrb %0, [%0]"
                : "=&r"(limit_value_r3)
                : "r"(limit_r9)
                : "memory");
            if (phase2_r0 < limit_value_r3) {
                goto block_46;
            }
        }
        {
            register u32 direction2_r5 asm("r5") = record_r2[9];
            register volatile u8 *inner_limit_r3 asm("r3") =
                (volatile u8 *)0x03005F71;
            register s32 temp_r0_5 asm("r0");

loop_42:
            if (direction2_r5 != 0) {
                goto block_44;
            }
            var_r0_3 = record_r2[0xB] + 1;
            goto block_45;
block_44:
            var_r0_3 = record_r2[0xB] - 1;
block_45:
            record_r2[0xB] = var_r0_3;
            asm volatile(
                "ldrb %0, [%1, #10]\n\t"
                "ldrb r1, [%2]\n\t"
                "sub %0, %0, r1"
                : "=r"(temp_r0_5)
                : "r"(record_r2), "r"(inner_limit_r3)
                : "r1", "cc", "memory");
            record_r2[0xA] = temp_r0_5;
            temp_r0_5 = (u8)temp_r0_5;
            if ((u32)temp_r0_5 >= (u32)*inner_limit_r3) {
                goto loop_42;
            }
        }
block_46:
        asm volatile(
            "mov r0, %3\n\t"
            "add r0, %4\n\t"
            "strb r0, [%0, #2]\n\t"
            "mov r3, sp\n\t"
            "ldrb r3, [r3, #8]\n\t"
            "add r0, %5, r3\n\t"
            "strb r0, [%0, #6]\n\t"
            "mov r5, sp\n\t"
            "ldrb r5, [r5, #12]\n\t"
            "ldrb r1, [%0, #10]\n\t"
            "add r0, r5, r1\n\t"
            "strb r0, [%0, #10]\n\t"
            "lsl r0, %2, #5\n\t"
            "orr %1, r0\n\t"
            "ldrb r0, [%0, #11]\n\t"
            "lsl r0, r0, #10\n\t"
            "orr %1, r0\n\t"
            "ldr r2, [sp, #0]\n\t"
            "strh %1, [r2]\n\t"
            "ldr %0, [sp, #4]\n\t"
            "ldr r3, [sp, #16]\n\t"
            "str r3, [sp, #0]"
            : "+r"(record_r2), "+r"(channel0_value_r4),
              "+r"(channel1_value_r7)
            : "r"(channel0_phase_r8), "r"(base0_sl),
              "r"(channel1_phase_r6)
            : "r0", "r1", "r3", "r5", "cc", "memory");
        {
            register u32 next_index_r3 asm("r3");

            asm volatile(
                "mov r4, %1\n\t"
                "lsl r0, r4, #16\n\t"
                "lsr %0, r0, #16"
                : "=l"(next_index_r3)
                : "h"(successor_ip)
                : "r0", "r4", "cc");
            var_r3_2 = next_index_r3;
        }
        if ((u32)var_r3_2 > 0x1FFU) {
            goto block_48;
        }
        goto loop_27;
    }
block_48:
    {
        register volatile u8 *dispatch_state_seed_r2 asm("r2") =
            (volatile u8 *)0x03005F70;
        temp_r0_6 = (0x3F & *dispatch_state_seed_r2) - 5;
        dispatch_state_r7 = dispatch_state_seed_r2;
    }
    if (temp_r0_6 <= 0xDU) {
        goto block_50;
    }
    return;
block_50:
    switch (temp_r0_6) {
case 0:
case 1:
    *(s8 *)0x03005EF2 = *(u8 *)0x03005F72 * 2;
    if (*(u8 *)0x03005F72 == D_03005F71) {
        goto block_54;
    }
    return;
block_54:
    {
        register u32 dispatch_byte_r1 asm("r1");
        asm volatile("ldrb %0, [%1]"
                     : "=r"(dispatch_byte_r1)
                     : "r"(dispatch_state_r7)
                     : "memory");
        if ((0x3F & dispatch_byte_r1) == 6) {
            goto block_56;
        }
    }
    goto block_74;
block_56:
    D_03000052 = 0x10;
    D_0300004E = 0xFF;
    asm volatile("");
    goto block_74;
case 2:
case 3:
    {
    register u16 *square_a_r3 asm("r3");
    register u16 *square_b_r2 asm("r2");
    register u8 *progress_r4 asm("r4");
    register u32 square_store_r0 asm("r0");

    square_a_r3 = D_03005EEA;
    square_b_r2 = D_03005EEE;
    progress_r4 = &D_03005F72;
    square_store_r0 = *progress_r4;
    asm volatile(
        "mov r5, %0\n\t"
        "mul r5, %0\n\t"
        "mov %0, r5"
        : "+r"(square_store_r0)
        :
        : "r5", "cc");
    square_b_r2[1] = square_store_r0;
    {
        register u32 mask_r5 asm("r5") = 0xFFFF;
        register u32 mask_r1 asm("r1");

        asm volatile("" : "+r"(mask_r5));
        mask_r1 = mask_r5;
        square_store_r0 &= mask_r1;
        square_b_r2[0] = square_store_r0;
        square_store_r0 &= mask_r1;
        square_a_r3[1] = square_store_r0;
        square_store_r0 &= mask_r1;
        square_a_r3[0] = square_store_r0;
    }
    if (*progress_r4 == *(u8 *)0x03005F71) {
        goto block_59;
    }
    return;
    }
block_59:
    {
        register u32 dispatch_byte_r1 asm("r1");
        asm volatile("ldrb %0, [%1]"
                     : "=r"(dispatch_byte_r1)
                     : "r"(dispatch_state_r7)
                     : "memory");
        if ((0x3F & dispatch_byte_r1) != 8) {
            goto block_74;
        }
    }
    D_03000052 = 0x10;
    D_0300004E = 0xFF;
    asm volatile("");
    goto block_74;
case 4:
case 5:
case 6:
case 7:
    {
        register volatile s16 *destination_r6 asm("r6") =
            (volatile s16 *)0x03005EF4;

        *destination_r6 = func_080ECD98(
            *(u8 *)0x03005F72 * 0x140, *(u8 *)0x03005F71);
    }
    if (*(u8 *)0x03005F72 == *(u8 *)0x03005F71) {
        goto block_63;
    }
    return;
block_63:
    {
        register u32 dispatch_byte_r1 asm("r1");
        asm volatile("ldrb %0, [%1]"
                     : "=r"(dispatch_byte_r1)
                     : "r"(dispatch_state_r7)
                     : "memory");
        if ((u32)(u8)((0x3F & dispatch_byte_r1) - 0xB) > 1U) {
            goto block_74;
        }
    }
    D_03000052 = 0x10;
    D_0300004E = 0xFF;
    asm volatile("");
    goto block_74;
case 8:
    {
    register s32 work_r1 asm("r1");
    register u8 *progress_r5 asm("r5");
    register s32 progress_r2 asm("r2");
    register s32 complement_r3 asm("r3");
    register s32 product_r0 asm("r0");
    register s32 x_result_r4 asm("r4");

    work_r1 = *(s16 *)0x03005F74 - 0x78;
    progress_r5 = &D_03005F72;
    progress_r2 = *progress_r5;
    {
        register s32 complement_seed_r0 asm("r0") = 0x20;
        asm volatile("" : "+r"(complement_seed_r0));
        complement_r3 = complement_seed_r0 - progress_r2;
    }
    product_r0 = work_r1;
    product_r0 *= complement_r3;
    if (product_r0 < 0) {
        product_r0 += 0x1F;
    }
    product_r0 >>= 5;
    product_r0 += 0x78;
    x_result_r4 = (s16)product_r0;

    product_r0 = *(s16 *)0x03005F76 - 0x50;
    product_r0 *= complement_r3;
    if (product_r0 < 0) {
        product_r0 += 0x1F;
    }
    product_r0 >>= 5;
    product_r0 += 0x50;
    work_r1 = (s16)product_r0;

    product_r0 = (progress_r2 << 4) - progress_r2;
    product_r0 <<= 3;
    if (product_r0 < 0) {
        product_r0 += 0x1F;
    }
    progress_r2 = product_r0 >> 5;
    func_080966B4(x_result_r4, work_r1, progress_r2);
    if (*progress_r5 == *(u8 *)0x03005F71) {
        goto block_74;
    }
    return;
    }
block_74:
    func_0809534C();
    return;
case 9:
    {
    register u8 *progress_r5 asm("r5");
    register s32 progress_r2 asm("r2");
    register s32 product_r0 asm("r0");
    register s32 x_result_r4 asm("r4");
    register s32 y_result_r3 asm("r3");
    register s32 complement_r1 asm("r1");

    product_r0 = *(s16 *)0x03005F74 - 0x78;
    progress_r5 = &D_03005F72;
    progress_r2 = *progress_r5;
    product_r0 *= progress_r2;
    if (product_r0 < 0) {
        product_r0 += 0x1F;
    }
    product_r0 >>= 5;
    product_r0 += 0x78;
    x_result_r4 = (s16)product_r0;

    product_r0 = (s32)(s16 *)0x03005F76;
    asm volatile(
        "mov r3, #0\n\t"
        "ldrsh %0, [%0, r3]"
        : "+r"(product_r0)
        :
        : "r3", "memory");
    product_r0 -= 0x50;
    product_r0 *= progress_r2;
    if (product_r0 < 0) {
        product_r0 += 0x1F;
    }
    product_r0 >>= 5;
    product_r0 += 0x50;
    y_result_r3 = (s16)product_r0;

    complement_r1 = 0x20 - progress_r2;
    product_r0 = (complement_r1 << 4) - complement_r1;
    product_r0 <<= 3;
    if (product_r0 < 0) {
        product_r0 += 0x1F;
    }
    progress_r2 = product_r0 >> 5;
    func_080966B4(x_result_r4, y_result_r3, progress_r2);
    if (*progress_r5 == *(u8 *)0x03005F71) {
        goto block_83;
    }
    return;
    }
block_83:
    D_03000052 = 0x10;
    goto block_89;
case 10:
case 11:
    *(s8 *)0x03005EF6 = *(u8 *)0x03005F72 * 4;
    if (*(u8 *)0x03005F72 == D_03005F71) {
        goto block_87;
    }
    return;
block_87:
    {
        register u32 dispatch_byte_r0 asm("r0");
        register u32 completion_r3 asm("r3");

        asm volatile("ldrb %0, [%1]"
                     : "=r"(dispatch_byte_r0)
                     : "r"(dispatch_state_r7)
                     : "memory");
        completion_r3 = 0x3F;
        completion_r3 &= dispatch_byte_r0;
        if (completion_r3 != 0x10) {
            goto block_74;
        }
        D_03000052 = completion_r3;
    }
block_89:
    D_0300004E = 0xFF;
    goto block_74;
case 12:
    {
        register u32 toggle_r0 asm("r0") = (u32)(u8 *)0x03005F7A;
        register u32 toggle_r1 asm("r1");

        asm volatile(
            "ldrb %1, [%0]\n\t"
            "mov %0, #1\n\t"
            "eor %0, %1"
            : "+r"(toggle_r0), "=r"(toggle_r1)
            :
            : "cc", "memory");
        var_r1 = (s8 *)((toggle_r0 * 0xA0) + 0x02002740);
    }
    var_r3_3 = 0;
    case12_progress_r7 = &D_03005F72;
    {
        register volatile u8 *limit_seed_r4 asm("r4") =
            (volatile u8 *)0x03005F71;
        asm volatile("" : "+r"(limit_seed_r4));
        case12_limit_r8 = limit_seed_r4;
    }
    case12_one_r6 = 1;
    case12_zero_r5 = 0;
loop_91:
    var_r4 = 0;
    {
        register u32 successor_r0 asm("r0") = var_r3_3 + 1;
        asm volatile("" : "+r"(successor_r0));
        case12_successor_ip = successor_r0;
    }
loop_92:
    asm volatile("ldrb %0, [%1]"
                 : "=r"(temp_r2_3)
                 : "r"(case12_progress_r7)
                 : "memory");
    if ((u32)temp_r2_3 < var_r3_3) {
        goto block_99;
    }
    if ((s32)temp_r2_3 >= (s32)(var_r3_3 + 8)) {
        goto block_97;
    }
    temp_r2_4 = temp_r2_3 - var_r3_3;
    var_r0_10 = temp_r2_4;
    if (temp_r2_4 >= 0) {
        goto block_96;
    }
    var_r0_10 = temp_r2_4 + 7;
block_96:
    if ((s32)(temp_r2_4 - ((var_r0_10 >> 3) * 8)) <= var_r4) {
        goto block_99;
    }
block_97:
    *var_r1 = case12_one_r6;
    goto block_100;
block_99:
    *var_r1 = case12_zero_r5;
block_100:
    var_r1 += 1;
    var_r4 = (s32)(u16)(var_r4 + 1);
    if ((u32)var_r4 <= 7U) {
        goto loop_92;
    }
    {
        register u32 successor_r2 asm("r2") = case12_successor_ip;
        var_r3_3 = (u16)successor_r2;
    }
    if (var_r3_3 <= 0x13U) {
        goto loop_91;
    }
    {
        register u32 progress_r0 asm("r0");
        register u32 limit_r3 asm("r3");

        asm volatile(
            "ldrb %0, [%2]\n\t"
            "mov %1, %3\n\t"
            "ldrb %1, [%1]"
            : "=l"(progress_r0), "=l"(limit_r3)
            : "l"(case12_progress_r7), "h"(case12_limit_r8)
            : "memory");
        if (progress_r0 != limit_r3) {
            goto block_119;
        }
    }
    goto block_106;
case 13:
    {
        register volatile u8 *progress_seed_r0 asm("r0") = &D_03005F72;
        register volatile u8 *limit_r2 asm("r2") =
            (volatile u8 *)0x03005F71;
        register u32 progress_value_r1 asm("r1") = *progress_seed_r0;

        case13_progress_r7 = progress_seed_r0;
        asm volatile("ldrb %0, [%0]"
                     : "+r"(limit_r2)
                     :
                     : "memory");
        if (progress_value_r1 != (u32)limit_r2) {
            goto block_108;
        }
    }
    D_03000052 = 0x10;
    D_0300004E = 0xFF;
block_106:
    *(s8 *)0x03005F7B = 2;
    return;
block_108:
    {
        register u32 toggle_r0 asm("r0") = (u32)(u8 *)0x03005F7A;
        register u32 toggle_r1 asm("r1");

        asm volatile(
            "ldrb %1, [%0]\n\t"
            "mov %0, #1\n\t"
            "eor %0, %1"
            : "+r"(toggle_r0), "=r"(toggle_r1)
            :
            : "cc", "memory");
        var_r1_2 = (s8 *)((toggle_r0 * 0xA0) + 0x02002740);
    }
    var_r3_4 = 0;
    case13_zero_r6 = 0;
    case13_one_r5 = 1;
loop_109:
    var_r4_2 = 0;
    {
        register u32 successor_r0 asm("r0") = var_r3_4 + 1;
        asm volatile("" : "+r"(successor_r0));
        case13_successor_ip = successor_r0;
    }
loop_110:
    asm volatile("ldrb %0, [%1]"
                 : "=r"(temp_r2_5)
                 : "r"(case13_progress_r7)
                 : "memory");
    if ((u32)temp_r2_5 < var_r3_4) {
        goto block_116;
    }
    if ((s32)temp_r2_5 >= (s32)(var_r3_4 + 8)) {
        goto block_115;
    }
    temp_r2_6 = temp_r2_5 - var_r3_4;
    var_r0_11 = temp_r2_6;
    if (temp_r2_6 >= 0) {
        goto block_114;
    }
    var_r0_11 = temp_r2_6 + 7;
block_114:
    if ((s32)(temp_r2_6 - ((var_r0_11 >> 3) * 8)) <= var_r4_2) {
        goto block_116;
    }
block_115:
    *var_r1_2 = case13_zero_r6;
    goto block_117;
block_116:
    *var_r1_2 = case13_one_r5;
block_117:
    var_r1_2 += 1;
    var_r4_2 = (s32)(u16)(var_r4_2 + 1);
    if ((u32)var_r4_2 <= 7U) {
        goto loop_110;
    }
    {
        register u32 successor_r2 asm("r2") = case13_successor_ip;
        var_r3_4 = (u16)successor_r2;
    }
    if (var_r3_4 <= 0x13U) {
        goto loop_109;
    }
block_119:
    return;
    }
}
