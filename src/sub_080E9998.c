#include "m2c_prelude.h"

s32 func_080BE488(s32, s32, s32);                   /* extern */
u8 func_080BF464(u8, u8, s32);                      /* extern */
s32 func_080E74F0(s32, s32, s32);                   /* extern */
s32 func_080E7AE0(s32, s32, s32);                   /* extern */
u32 func_080ECD5C(s32);                             /* extern */
extern u8 D_02034B4C[];
extern u8 D_000027BE[];

void sub_080E9998(void) {
    volatile u32 sp0;
    u8 *sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 var_r0_2;
    s32 var_r2;
    s32 temp_r1;
    register s32 temp_r5 asm("r5");
    register s32 var_r0 asm("r0");
    register u32 or_value_r1 asm("r1");
    u32 temp_r0;
    u8 *temp_r4;
    u8 temp_r0_2;
    register u32 var_r8 asm("r8");
    register u32 var_sl asm("sl");
    register void *temp_r2 asm("r9");
    register u8 *temp_r6 asm("r6");
    register u8 *type_ptr_r1 asm("r1");

    sp0 = 0;
    asm volatile("" : "=m"(sp4), "=m"(sp8), "=m"(spC), "=m"(sp10),
        "=m"(sp14), "=m"(sp18), "=m"(sp1C), "=m"(sp20));
    {
        register u8 *base_r0 asm("r0") = D_02034B4C;
        register u32 offset_r2 asm("r2") = 0xA1AF;
        register u8 *limit_r1 asm("r1");
        register u32 outer_r3 asm("r3");
        register u32 limit_r4 asm("r4");

        limit_r1 = base_r0 + offset_r2;
        outer_r3 = sp0;
        limit_r4 = *limit_r1;
        asm volatile("" : "+r"(limit_r4));
        if (outer_r3 >= limit_r4) {
            return;
        }
    }
loop_2:
    {
        register u32 zero_r5 asm("r5") = 0;
        asm volatile("" : "+r"(zero_r5));
        var_sl = zero_r5;
    }
    {
        register u32 outer_r6 asm("r6") = sp0;
        sp1C = outer_r6 * 8;
    }
    sp14 = sp0 * 2;
    {
        register u32 outer_r1 asm("r1") = sp0;
        spC = outer_r1 + 1;
    }
    {
        register u32 address_r2 asm("r2") = sp0;
        register u32 base_r3 asm("r3") = 0x0203ECFC;
        address_r2 += base_r3;
        sp4 = (u8 *)address_r2;
    }
loop_3:
    {
        register u32 zero_r4 asm("r4") = 0;
        asm volatile("" : "+r"(zero_r4));
        var_r8 = zero_r4;
    }
    {
        register u32 inner_r5 asm("r5") = var_sl;
        asm volatile("" : "+r"(inner_r5));
        sp20 = inner_r5 * 8;
    }
    {
        register u32 inner_r6 asm("r6") = var_sl;
        asm volatile("" : "+r"(inner_r6));
        sp18 = inner_r6 * 2;
    }
    sp10 = var_sl + 1;
    {
        register u32 inner_r1 asm("r1") = var_sl;
        register u32 stride_r0 asm("r0");

        stride_r0 = inner_r1 << 2;
        stride_r0 += var_sl;
        stride_r0 <<= 3;
        stride_r0 -= inner_r1;
        stride_r0 <<= 7;
        sp8 = stride_r0;
    }
loop_4:
    {
        register u8 *row_r2 asm("r2") = sp4;
        register u32 row_r1 asm("r1");

        row_r1 = *row_r2;
        temp_r5 = row_r1 * 0xA8C;
    }
    {
        register s32 phase_r3 asm("r3");
        s32 phase_r7;
        register u32 address_r2 asm("r2");
        register u32 work_r0 asm("r0");
        register u32 work_r1 asm("r1");
        register u8 *output_r4 asm("r4");

        {
            register u32 outer_r4 asm("r4");

            phase_r3 = sp1C;
            outer_r4 = sp0;
            work_r0 = phase_r3 - outer_r4;
            work_r0 <<= 5;
            work_r0 += outer_r4;
            phase_r3 = work_r0 << 2;
            temp_r6 = D_02034B4C;
            work_r0 = 0x27C8;
            address_r2 = (u32)temp_r6 + work_r0;
            address_r2 = phase_r3 + address_r2;
            address_r2 = temp_r5 + address_r2;

            work_r1 = 0xA1B3;
            work_r0 = (u32)temp_r6 + work_r1;
            work_r0 = outer_r4 - (0U - work_r0);
            work_r1 = *(u8 *)work_r0;
        }
        work_r0 = 0x94;
        phase_r7 = work_r1;
        phase_r7 *= work_r0;
        work_r0 = phase_r7;
        work_r0 += 0xC;
        address_r2 += work_r0;

        work_r0 = sp20 + var_sl;
        work_r0 <<= 3;
        work_r0 += 4;
        address_r2 += work_r0;
        output_r4 = (u8 *)var_r8;
        asm volatile("" : "+r"(output_r4));
        work_r0 = (u32)output_r4 << 1;
        work_r0 += var_r8;
        work_r0 <<= 2;
        address_r2 += work_r0;
        temp_r2 = (void *)address_r2;

        temp_r6 = (u8 *)sp14;
        work_r0 = sp0;
        address_r2 = (u32)temp_r6 + work_r0;
        address_r2 <<= 2;
        work_r0 = sp18 + var_sl;
        work_r0 <<= 1;
        output_r4 = D_02034B4C;
        temp_r6 = (u8 *)0xA1B6;
        work_r1 = (u32)output_r4 + (u32)temp_r6;
        work_r0 += work_r1;
        address_r2 += work_r0;
        work_r0 = var_r8;
        output_r4 = (u8 *)(address_r2 + work_r0);
        temp_r4 = output_r4;

        work_r0 = phase_r3 + temp_r5;
        work_r1 = (u32)D_02034B4C;
        temp_r6 = (u8 *)(work_r0 + work_r1);
        if (M2C_FIELD(temp_r6, u8 *, 0x27D2) == 0) {
            goto block_zero;
        }
        work_r0 = phase_r7 + phase_r3;
        work_r0 += temp_r5;
        work_r0 += work_r1;
        if (M2C_FIELD(work_r0, u8 *, 0x27D4) == 0) {
            goto block_zero;
        }
    }
    {
        register u32 one_r3 asm("r3");

        {
            register u8 *flags_r5 asm("r5") = temp_r2;
            register u32 flags_r1 asm("r1");

            flags_r1 = *(u16 *)flags_r5;
            one_r3 = 1;
            if (!(1 & flags_r1)) {
                goto block_zero;
            }
        }
        if (1 & ({
                register u32 flag_r1 asm("r1") = 0x27C8;
                register u32 flag_address_r0 asm("r0");

                asm volatile("" : "+r"(flag_r1));
                flag_address_r0 = (u32)temp_r6 + flag_r1;
                flag_r1 = *(u16 *)flag_address_r0;
                flag_r1;
            })) {
            goto block_set3;
        }
        {
        register u8 *base_r2 asm("r2") = D_02034B4C;
        register u32 type_offset_r5 asm("r5") = 0x27BE;
        register u32 type_value_r0 asm("r0");

        asm volatile("" : "+r"(base_r2), "+r"(type_offset_r5));
        type_value_r0 = (u32)base_r2 + type_offset_r5;
        type_value_r0 += var_sl;
        type_value_r0 = *(u8 *)type_value_r0;
        if ((type_value_r0 == 0x21) && (({
                register u32 index_r6 asm("r6") = var_r8;
                register u32 address_r0 asm("r0");
                register u32 row_r1 asm("r1");

                address_r0 = index_r6 << 2;
                address_r0 += var_r8;
                address_r0 <<= 3;
                address_r0 -= index_r6;
                address_r0 <<= 4;
                row_r1 = sp8;
                address_r0 += row_r1;
                address_r0 += (u32)base_r2;
                address_r0 += 0x70;
                address_r0 = *(u8 *)address_r0;
                address_r0;
            }) != 1)) {
            *temp_r4 = one_r3;
            goto block_random;
        }
        }
    }
    temp_r0 = func_080ECD5C(*(s32 *)0x03000010) * 0x64;
    temp_r0 *= 2;
    temp_r6 = (u8 *) (temp_r0 >> 0x10);
    temp_r1 = (s32) temp_r0 >> 0x10;
    if (temp_r1 == 0) {
        goto block_set1;
    }
    if (temp_r1 > (s32) ({
            register u8 *entry_r2 asm("r2") = temp_r2;
            register u32 offset_r3 asm("r3");
            register s32 value_r0 asm("r0");
            asm volatile(
                "mov %1, #2\n\t"
                "ldrsh %0, [%2, %1]"
                : "=r"(value_r0), "=r"(offset_r3)
                : "r"(entry_r2));
            value_r0;
        })) {
        goto block_set1;
    }
    if (((func_080E7AE0(var_sl, var_r8, 0x15) << 0x10) != 0) &&
        ((s32) ({
            register u32 index_r1 asm("r1") = var_r8;
            register u32 address_r0 asm("r0");
            register u32 row_r2 asm("r2");
            register u8 *base_r3 asm("r3");

            address_r0 = index_r1 << 2;
            address_r0 += var_r8;
            address_r0 <<= 3;
            address_r0 -= index_r1;
            address_r0 <<= 4;
            row_r2 = sp8;
            address_r0 += row_r2;
            base_r3 = D_02034B4C;
            address_r0 += (u32)base_r3;
            index_r1 = 8;
            *(s16 *)(address_r0 + index_r1);
        }) > 1) && ((func_080ECD5C(*(s32 *)0x03000010) >> 0xE) == 0)) {
        goto block_set2;
    }
    {
        register u8 *base_r2 asm("r2") = D_02034B4C;
        {
            register u32 type_offset_r3 asm("r3") = 0x27BE;
            register u8 *type_base_r0 asm("r0");
            register u32 type_index_r5 asm("r5");
            type_base_r0 = base_r2 + type_offset_r3;
            type_index_r5 = var_sl;
            asm volatile("add %0, %1, %2"
                : "=r"(type_ptr_r1)
                : "r"(type_index_r5), "r"(type_base_r0));
            if ((*type_ptr_r1 == 0x20) &&
                (({
                    register u32 address_r0 asm("r0") = 0x94;
                    register u32 index_r3 asm("r3") = var_sl;
                    register u32 offset_r5 asm("r5");

                    index_r3 *= address_r0;
                    address_r0 = index_r3;
                    address_r0 += (u32)base_r2;
                    offset_r5 = 0xA084;
                    asm volatile("" : "+r"(offset_r5));
                    address_r0 += offset_r5;
                    address_r0 = *(u8 *)address_r0;
                    address_r0;
                }) == var_r8)) {
                goto block_set5;
            }
        }
        {
            register s32 compare_r1 asm("r1");
            register u32 offset_r3 asm("r3");
            register s32 entry_value_r0 asm("r0");

            compare_r1 = (u32)temp_r6 << 16;
            compare_r1 >>= 15;
            temp_r6 = (u8 *)temp_r2;
            asm volatile(
                "mov %1, #6\n\t"
                "ldrsh %0, [%2, %1]"
                : "=r"(entry_value_r0), "=r"(offset_r3)
                : "r"(temp_r6));
            if (compare_r1 > entry_value_r0) {
                *temp_r4 = 3;
                {
                    register u32 index_r5 asm("r5") = var_r8;
                    register u32 address_r0 asm("r0");
                    register u32 row_r6 asm("r6");
                    register u32 offset_r1 asm("r1");
                    register s32 field_r2 asm("r2");

                    address_r0 = index_r5 << 2;
                    address_r0 += var_r8;
                    address_r0 <<= 3;
                    address_r0 -= index_r5;
                    address_r0 <<= 4;
                    row_r6 = sp8;
                    address_r0 += row_r6;
                    address_r0 += (u32)base_r2;
                    asm volatile(
                        "mov %1, #60\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(field_r2), "=r"(offset_r1)
                        : "r"(address_r0));
                    var_r2 = field_r2;
                }
                {
                    register u8 *entry_r3 asm("r3") = temp_r2;
                    register u32 offset_r5 asm("r5");
                    register s32 field_r0 asm("r0");

                    asm volatile(
                        "mov %1, #4\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(field_r0), "=r"(offset_r5)
                        : "r"(entry_r3));
                    var_r0_2 = field_r0;
                }
            } else {
                *temp_r4 = 4;
                {
                    register u32 address_r0 asm("r0");
                    register s32 field_r2 asm("r2");

                    temp_r6 = (u8 *)var_r8;
                    address_r0 = (u32)temp_r6 << 2;
                    address_r0 += var_r8;
                    address_r0 <<= 3;
                    address_r0 -= (u32)temp_r6;
                    address_r0 <<= 4;
                    compare_r1 = sp8;
                    address_r0 += compare_r1;
                    address_r0 += (u32)base_r2;
                    asm volatile(
                        "mov %1, #60\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(field_r2), "=r"(offset_r3)
                        : "r"(address_r0));
                    var_r2 = field_r2;
                }
                {
                    register u8 *entry_r5 asm("r5") = temp_r2;
                    register s32 field_r0 asm("r0");

                    asm volatile(
                        "mov %1, #8\n\t"
                        "ldrsh %0, [%2, %1]"
                        : "=r"(field_r0), "=r"(temp_r6)
                        : "r"(entry_r5));
                    var_r0_2 = field_r0;
                }
            }
        }
        if (func_080BE488(var_sl, var_r8, var_r2 - var_r0_2) != 0) {
            register u32 value_r1 asm("r1") = *temp_r4;
            register u32 mask_r0 asm("r0") = 0x40;

            value_r1 |= mask_r0;
            *temp_r4 = value_r1;
        }
    }
    if (((func_080E74F0(({
            register u32 call_address_r0 asm("r0");
            register u8 *call_base_r1 asm("r1") = D_02034B4C;
            register u32 call_offset_r2 asm("r2") =
                (s32)D_000027BE - 0x12;

            call_address_r0 = (u32)call_base_r1 + call_offset_r2;
            call_address_r0 = *(s32 *)call_address_r0;
            call_address_r0;
        }), 0x14, ({
            register u32 call_address_r1 asm("r1");

            {
                register u32 phase_r3 asm("r3") = sp1C;
                register u32 outer_r5 asm("r5") = sp0;

                call_address_r1 = phase_r3 - outer_r5;
                call_address_r1 <<= 5;
                call_address_r1 += outer_r5;
                call_address_r1 <<= 2;
            }
            {
                register u8 *row_r6 asm("r6") = sp4;
                register u32 row_r3 asm("r3") = *row_r6;
                register u32 stride_r2 asm("r2") = 0xA8C;

                stride_r2 *= row_r3;
                call_address_r1 += stride_r2;
            }
            {
                register u32 table_r2 asm("r2") = 0x02037318;
                register s32 call_value_r2 asm("r2");

                asm volatile("" : "+r"(table_r2));
                call_address_r1 += table_r2;
                call_value_r2 = *(s32 *)call_address_r1;
                call_value_r2;
            }
        })) << 0x10) != 0) &&
        ((s32) ((u32) (func_080ECD5C(*(s32 *)0x03000010) * 0xA) >> 0xF) <= 2)) {
        register u32 value_r1 asm("r1") = *temp_r4;
        register u32 mask_r0 asm("r0") = 0x80;

        value_r1 |= mask_r0;
        *temp_r4 = value_r1;
    }
    if ((({
            register u32 call_base_r1 asm("r1") = (u32)D_02034B4C;
            register u32 first_offset_r3 asm("r3") =
                (s32)D_000027BE - 0x1A;
            register u32 first_value_r0 asm("r0");
            register u32 second_offset_r5 asm("r5");

            first_value_r0 = call_base_r1 + first_offset_r3;
            first_value_r0 = *(u8 *)first_value_r0;
            second_offset_r5 = (s32)D_000027BE - 0x19;
            asm volatile("" : "+r"(second_offset_r5));
            call_base_r1 += second_offset_r5;
            call_base_r1 = *(u8 *)call_base_r1;
            func_080BF464(first_value_r0, call_base_r1, 0x1F);
        }) != 0xFF) && ({
            register u32 flag_address_r0 asm("r0");

            {
                register u32 phase_r6 asm("r6") = sp1C;
                register u32 outer_r1 asm("r1") = sp0;

                flag_address_r0 = phase_r6 - outer_r1;
                flag_address_r0 <<= 5;
                flag_address_r0 += outer_r1;
                flag_address_r0 <<= 2;
            }
            {
                register u8 *row_r3 asm("r3") = sp4;
                register u32 row_r2 asm("r2") = *row_r3;
                register u32 stride_r1 asm("r1") = 0xA8C;

                stride_r1 *= row_r2;
                flag_address_r0 += stride_r1;
            }
            {
                register u32 table_r5 asm("r5") = 0x02037318;
                register u32 flag_r1 asm("r1");
                register u32 mask_r0 asm("r0");

                asm volatile("" : "+r"(table_r5));
                flag_address_r0 += table_r5;
                flag_r1 = *(u32 *)flag_address_r0;
                mask_r0 = 0x10;
                flag_r1 &= mask_r0;
                flag_r1;
            }
        }) && ((func_080ECD5C(*(s32 *)0x03000010) >> 0xE) != 0)) {
        or_value_r1 = *temp_r4;
        var_r0 = 0x20;
        goto block_or;
    }
    goto block_random;

block_set5:
    *temp_r4 = 5;
    *type_ptr_r1 = 0U;
    goto block_random;
block_set2:
    *temp_r4 = 2;
    goto block_random;
block_set1:
    *temp_r4 = 1;
    goto block_random;
block_set3:
    *temp_r4 = 3;
    if (func_080BE488(var_sl, var_r8, 0) != 0) {
        or_value_r1 = *temp_r4;
        var_r0 = 0x40;
        goto block_or;
    }
    goto block_random;
block_or:
    or_value_r1 |= var_r0;
    *temp_r4 = or_value_r1;
block_random:
    *temp_r4 |= ((u32) (func_080ECD5C(*(s32 *)0x03000010) * 3) >> 0xF) * 8;
    goto block_increment;
block_zero:
    *temp_r4 = 0;
block_increment:
    temp_r0_2 = var_r8 + 1;
    var_r8 = temp_r0_2;
    if ((u32) temp_r0_2 <= 5U) {
        goto loop_4;
    }
    {
        register u32 successor_r6 asm("r6") = sp10;
        register u32 narrow_r0 asm("r0");

        narrow_r0 = successor_r6 << 24;
        narrow_r0 >>= 24;
        var_sl = narrow_r0;
        if (narrow_r0 <= 1U) {
            goto loop_3;
        }
    }
    {
        register u32 successor_r1 asm("r1") = spC;
        register u32 narrow_r0 asm("r0");
        register u32 limit_r2 asm("r2");

        narrow_r0 = successor_r1 << 24;
        narrow_r0 >>= 24;
        sp0 = narrow_r0;
        limit_r2 = 0x0203ECFB;
        limit_r2 = *(u8 *)limit_r2;
        if (narrow_r0 < limit_r2) {
            goto loop_2;
        }
    }
}
