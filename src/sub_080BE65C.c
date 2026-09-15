#include "m2c_prelude.h"

M2C_UNK func_080BE9D8(s32, s32, s8, s32, s32, s32, s32, s32, s32, s32); /* extern */
u8 func_080BF464(u8, s32, u16);                     /* extern */
M2C_UNK jtbl_080BE7FC();                            /* static */


s32 sub_080BE65C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    register s32 hold8 asm("r8") = arg8;
    register s32 hold9 asm("r9") = arg9;
    register s32 hold0 asm("sl");
    volatile s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_r1;
    s32 temp_r1_2;
    s32 temp_r2;
    s32 temp_r2_2;
    s32 temp_r2_3;
    s32 col_sum;
    s32 temp_r4_2;
    s8 temp_r2_4;
    u16 temp_r1_3;
    u16 temp_r3;
    u32 temp_r3_3;
    u16 temp_r7;
    s32 var_r0;
    u16 var_r6;
    u32 temp_r0_2;
    u8 temp_r3_2;
    u8 var_r5;
    register u8 *base_tail asm("ip");
    u8 *status;
    void *temp_r1_4;
    void *temp_r4;
    void *var_r4;
    void *loop_address;

    hold0 = (u8) arg0;
    sp18 = (s32) (u8) arg1;
    sp1C = (s32) (u8) arg2;
    temp_r3 = (u16) arg3;
    sp20 = (s32) temp_r3;
    sp24 = (s32) (u8) arg5;
    temp_r7 = (u16) arg6;
    var_r6 = (u16) arg7;
    {
        register s32 normalized8 asm("r0") = hold8;
        asm volatile("" : "+r"(normalized8));
        sp28 = (s32) (u16) normalized8;
    }
    {
        register s32 normalized9 asm("r1") = hold9;
        asm volatile("" : "+r"(normalized9));
        sp2C = (s32) (u16) normalized9;
    }
    if (!(1 & temp_r3)) {
        register s32 zero_arg4 asm("r2") = 0;
        asm volatile("" : "+r"(zero_arg4));
        arg4 = zero_arg4;
    }
    if ((((u32) (u16) (temp_r7 - 0x15) <= 7U) || (temp_r7 == 0x23)) && (func_080BF464(hold0, sp18, temp_r7) != 0xFF)) {
        goto block_36;
    }
    {
    register s32 product_col asm("r3") = hold0;
    register s32 special_row asm("r4");
    asm volatile("" : "+r"(product_col));
    product_col *= 4;
    sp30 = product_col;
    special_row = sp18;
    asm volatile("" : "+r"(special_row));
    special_row *= 4;
    sp34 = special_row;
    asm volatile("" : : : "r5");
    status = (u8 *)0x0203055C;
    if (temp_r7 == 0x14) {
        temp_r3_2 = func_080BF464(hold0, sp18, 0x14U);
        if (temp_r3_2 != 0xFF) {
            register s32 special_a asm("r1");
            register s32 special_b asm("r0");
            special_a = (((sp30 + hold0) * 8) - hold0) << 7;
            asm volatile("" : "+r"(special_a));
            {
                register s32 special_input asm("r2") = sp18;
                asm volatile("" : "+r"(special_input));
                special_b = (((special_row + special_input) * 8) - special_input) * 0x10;
            }
            asm volatile("" : "+r"(special_b));
            {
                register u8 *special_base asm("r2") = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(special_base));
                special_b += (s32)special_base;
                asm volatile("" : "+r"(special_b));
                special_a += special_b;
                asm volatile("" : "+r"(special_a));
            }
            {
                register s32 special_offset asm("r0");
                register void *special_record asm("r4");
                special_offset = ((s32)temp_r3_2) << 1;
                asm volatile("" : "+r"(special_offset));
                special_offset += temp_r3_2;
                asm volatile("" : "+r"(special_offset));
                special_offset <<= 2;
                special_offset += 0xE4;
                special_record = special_a + special_offset;
                asm volatile("" : "+r"(special_record));
                temp_r4 = special_record;
            }
            {
                register s32 reserve_r2 asm("r2");
                asm volatile("" : "=r"(reserve_r2));
                if ((s32)M2C_FIELD(temp_r4, s16 *, 6) >= (s32)(s16)var_r6) {
                    goto block_36;
                }
                asm volatile("" : : "r"(reserve_r2));
            }
            M2C_FIELD(temp_r4, s16 *, 4) = 0;
            goto block_11;
        }
block_11:
        if ((0x800 & arg4) && (status[2] == 0xB)) {
            var_r6 *= 2;
        }
        goto block_14;
    }
    }
block_14:
    {
    register u8 *base_seed asm("r3") = (u8 *)0x02034B4C;
    asm volatile("" : "+r"(base_seed));
    {
        register s32 row_product asm("r1") = sp34;
        register s32 row_input asm("r2") = sp18;
        register s32 row_sum asm("r0");
        asm volatile("" : "+r"(row_product));
        asm volatile("" : "+r"(row_input));
        row_sum = row_product + row_input;
        asm volatile("" : "+r"(row_sum));
        row_sum *= 8;
        row_input = row_sum - row_input;
        asm volatile("" : "+r"(row_input));
        temp_r2 = row_input;
    }
    temp_r1 = temp_r2 * 0x10;
    col_sum = (sp30 + hold0) * 8;
    asm volatile("" : : "l"(hold0) : "r2");
    temp_r4_2 = col_sum - hold0;
    temp_r2_2 = temp_r4_2 << 7;
    {
        register s32 initial_address asm("r0") = temp_r1 + temp_r2_2;
        asm volatile("" : "+r"(initial_address));
        initial_address += (s32)base_seed;
        asm volatile("" : "+r"(initial_address));
        var_r5 = M2C_FIELD(initial_address, u8 *, 0x266);
    }
    {
        register s32 record_row asm("r1") = temp_r1;
        register s32 record_col asm("r2") = temp_r2_2;
        register s32 record_offset asm("r0");
        asm volatile("" : "+r"(record_row));
        asm volatile("" : "+r"(record_col));
        record_row += (s32)base_seed;
        asm volatile("" : "+r"(record_row));
        record_col += record_row;
        asm volatile("" : "+r"(record_col));
        record_offset = (var_r5 * 0xC) + 0xE4;
        asm volatile("" : "+r"(record_offset));
        var_r4 = record_col + record_offset;
    }
    temp_r3_3 = M2C_FIELD(var_r4, u16 *, 4);
    base_tail = base_seed;
    }
    if (temp_r3_3 != 0) {
        asm volatile("mov r3, r8" : : "h"(temp_r4_2) : "r3");
loop_16:
        if ((u32) var_r5 <= 0x1FU) {
            var_r5 += 1;
        } else {
            var_r5 = 0;
        }
        asm volatile("mov r0, r9\n\tlsl %0, r0, #4"
                     : "=l"(temp_r1_2)
                     : "h"(temp_r2)
                     : "r0", "cc");
        asm volatile("lsl %0, r3, #7"
                     : "=l"(temp_r2_3)
                     : "h"(temp_r4_2)
                     : "r3", "cc");
        loop_address = temp_r1_2 + temp_r2_3;
        {
            register u8 *loop_base asm("r4") = (u8 *)0x02034B4C;
            asm volatile("" : "+r"(loop_base));
            loop_address += (s32)loop_base;
        }
        {
            register s32 loop_field asm("r4") = 0x266;
            asm volatile("" : "+r"(loop_field));
            loop_address += loop_field;
        }
        if (var_r5 == M2C_FIELD(loop_address, u16 *, 0)) {
            goto block_36;
        }
        asm volatile("" : : "b"(base_tail) : "r0", "r3");
        var_r4 = (void *)(temp_r2_3 + (temp_r1_2 + (s32)base_tail) +
            ({
                register s32 loop_offset asm("r1") = (var_r5 * 0xC) + 0xE4;
                asm volatile("" : "+r"(loop_offset));
                loop_offset;
            }));
        if (M2C_FIELD(var_r4, u16 *, 4) == 0) {
            goto block_23;
        }
        goto loop_16;
    }
block_23:
    temp_r0_2 = 0x38 & sp20;
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        M2C_FIELD(var_r4, u16 *, 4) = temp_r7;
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        if (2 & sp20) {
            var_r0 = 0;
        } else {
            M2C_FIELD(var_r4, u16 *, 8) = (u16) sp28;
            goto block_39;
        }
        goto block_38;
    case 8:
        M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r7 | 0x2000);
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        M2C_FIELD(var_r4, u16 *, 8) = (u16) sp28;
        goto block_39;
    case 16:
        M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r7 | 0x4000);
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        M2C_FIELD(var_r4, u16 *, 8) = (u16) sp2C;
        goto block_39;
    case 24: {
        register u32 case24_bits asm("r3");
        register s32 case24_addr asm("r0") = sp34 + (hold0 * 0x18);
        register s32 case24_offset asm("r1");
        asm volatile("" : "+r"(case24_addr));
        case24_offset = 0xA1DC;
        asm volatile("" : "+r"(case24_offset));
        case24_offset += (s32)base_tail;
        asm volatile("" : "+r"(case24_offset));
        case24_addr += case24_offset;
        asm volatile("" : "+r"(case24_addr));
        case24_bits = M2C_FIELD(case24_addr, s32 *, 0) & (1 << var_r5);
        asm volatile("" : "+r"(case24_bits));
        if (case24_bits != 0) {
            goto block_36;
        }
        M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r7 | 0x6000);
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        M2C_FIELD(var_r4, u16 *, 8) = case24_bits;
        goto block_39;
    }
    case 32: {
        register u32 case32_copy asm("r0");
        {
            register u32 case32_mask asm("r1") = 0x8000;
            asm volatile("" : "+r"(case32_mask));
            case32_copy = case32_mask;
            asm volatile("" : "+r"(case32_copy));
        }
        {
            register u32 case32_zero asm("r2") = 0;
            register u32 case32_result asm("r1") = temp_r7;
            asm volatile("" : "+r"(case32_zero));
            asm volatile("" : "+r"(case32_result));
            case32_result |= case32_copy;
            M2C_FIELD(var_r4, u16 *, 4) = (u16)case32_result;
            M2C_FIELD(var_r4, u16 *, 6) = var_r6;
            M2C_FIELD(var_r4, u16 *, 8) = case32_zero;
        }
        goto block_39;
    }
block_36:
        return 0;
    case 40: {
        {
            register u32 case40_mask asm("r2") = 0xA000;
            register u32 case40_copy asm("r0");
            register u32 case40_result asm("r1");
            asm volatile("" : "+r"(case40_mask));
            case40_copy = case40_mask;
            asm volatile("" : "+r"(case40_copy));
            case40_result = temp_r7;
            asm volatile("" : "+r"(case40_result));
            case40_result |= case40_copy;
            M2C_FIELD(var_r4, u16 *, 4) = (u16)case40_result;
            M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        }
        {
            register s32 case40_input asm("r3") = sp2C;
            register s32 case40_signed asm("r0");
            asm volatile("" : "+r"(case40_input));
            case40_signed = (s16)case40_input;
            asm volatile("" : "+r"(case40_signed));
            case40_signed = -case40_signed;
            var_r0 = case40_signed;
        }
    }
block_38:
        M2C_FIELD(var_r4, u16 *, 8) = var_r0;
        goto block_39;
    default:
block_39:
        temp_r2_4 = (s8) sp1C;
        temp_r1_3 = ((0xF & temp_r2_4) << 8) | M2C_FIELD(var_r4, u16 *, 4);
        M2C_FIELD(var_r4, u16 *, 4) = temp_r1_3;
        if (sp24 != 0) {
            M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r1_3 | 0x80);
        }
        M2C_FIELD(var_r4, s32 *, 0) = arg4;
        func_080BE9D8(hold0, sp18, temp_r2_4, sp20, arg4, sp24, (s32) temp_r7, (s32) (s16) var_r6, (s32) (s16) sp28,
            ({
                register s32 call_arg9 asm("r4") = sp2C;
                register s32 call_arg9_signed asm("r0");
                asm volatile("" : "+r"(call_arg9));
                call_arg9_signed = (s16)call_arg9;
                asm volatile("" : "+r"(call_arg9_signed));
                call_arg9_signed;
            }));
        {
            register u8 *final_base asm("r2");
            register s32 final_row asm("r1");
            register s32 final_col asm("r0");
            register s32 final_field asm("r4");

            final_base = (u8 *)0x02034B4C;
            asm volatile("" : "+r"(final_base));
            {
                register s32 final_sp34 asm("r7") = sp34;
                register s32 final_sp18 asm("r0") = sp18;
                asm volatile("" : "+r"(final_sp34));
                asm volatile("" : "+r"(final_sp18));
                final_row = (((final_sp34 + final_sp18) * 8) - final_sp18) * 0x10;
            }
            asm volatile("" : "+r"(final_row));
            {
                register s32 final_sp30 asm("r0");
                register s32 final_sub asm("r3");
                asm volatile("" : "=r"(final_sp30) : "0"(sp30));
                final_col = final_sp30 + hold0;
                final_col *= 8;
                final_sub = hold0;
                asm volatile("" : "+r"(final_sub));
                final_col -= final_sub;
                final_col <<= 7;
            }
            asm volatile("" : "+r"(final_col));
            final_row += final_col;
            asm volatile("" : "+r"(final_row));
            final_row += (s32) final_base;
            asm volatile("" : "+r"(final_row));
            final_field = 0x266;
            asm volatile("" : "+r"(final_field));
            temp_r1_4 = (void *)(final_row + final_field);
            M2C_FIELD(temp_r1_4, u16 *, 0) = (u16) (M2C_FIELD(temp_r1_4, u16 *, 0) + 1);
        }
        return 1;
    }
}
