#include "m2c_prelude.h"

s32 func_080E7C18(s32, u8, u8, u8, s32, s32, s32);
s16 func_080E813C(s32, u8, u8, u8, s32, s32, s32);
s32 func_080E9D88(u8, u8);

extern u8 D_02037314[];
extern u8 D_087B2524[];
extern u8 D_off_FFFFD838[];
extern u8 D_off_000027C8[];

s32 sub_080E83A4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    u8 *sp1C;
    void *sp20;
    s32 products[2];
    s32 temp_r0_2;
    register s32 temp_r2_2 asm("r2");
    s32 temp_r7;
    s32 temp_r0_3;
    u8 temp_r0;
    u8 temp_r1;
    u8 temp_r2;
    u8 temp_r3;
    u8 temp_r4;
    u8 temp_r5;
    u8 var_r6;
    void *temp_r0_4;
    void *temp_r6;
    register s32 base asm("r2");
    s32 addr;
    s32 offset;
    s32 ret;
    s32 part1;
    s32 part2;

    temp_r0 = arg0;
    sp10 = (s32)temp_r0;
    asm volatile("" : "+rm"(sp10));
    spC = (s32)temp_r0;
    asm volatile("" : "+r"(spC));
    temp_r1 = arg1;
    {
        register s32 copy_r0 asm("r0");
        copy_r0 = (s32)temp_r1;
        asm volatile("" : "+r"(copy_r0));
        sp14 = copy_r0;
    }
    asm volatile("" :: "r"(temp_r1));
    temp_r2 = arg2;
    {
        register s32 copy_r1 asm("r1");
        copy_r1 = (s32)temp_r2;
        asm volatile("" : "+r"(copy_r1));
        sp18 = copy_r1;
    }
    temp_r3 = arg3;
    var_r6 = (u8)arg4;
    temp_r4 = (u8)arg5;
    temp_r5 = (u8)arg6;
    temp_r2_2 = temp_r2 * 0xA8C;
    products[0] = temp_r2_2;
    temp_r0_2 = temp_r3 * 0x384;
    products[1] = temp_r0_2;
    {
        register s32 first_base_r3 asm("r3");
        register s32 combined_addr asm("r1");
        first_base_r3 = (s32)D_02037314;
        addr = temp_r0_2 + first_base_r3;
        combined_addr = temp_r2_2 + addr;
        addr = combined_addr;
        asm volatile("" :: "r"(temp_r0_2));
        asm volatile("" :: "r"(first_base_r3));
        offset = 0x94 * var_r6;
        offset += 0xC;
        addr += offset;
        sp1C = (u8 *)addr;
    }
    {
        register s32 row_offset_r1 asm("r1");
        register u8 *row_base_r7 asm("r7");
        row_offset_r1 = (temp_r4 * 0x48) + 4;
        row_base_r7 = sp1C;
        asm volatile("" : "+r"(row_offset_r1), "+r"(row_base_r7));
        row_offset_r1 = (s32)row_base_r7 + row_offset_r1;
        temp_r6 = (void *)(row_offset_r1 + (temp_r5 * 0xC));
    }
    if ((func_080E9D88(temp_r4, temp_r5) << 0x18) == 0) {
        goto return_zero;
    }
    part1 = temp_r4 * 0x1380;
    part2 = temp_r5 * 0x270;
    {
        s32 base_addr_r3;
        register s32 base_off_r7 asm("r7");
        base_addr_r3 = (s32)D_02037314;
        asm volatile("" : "+r"(base_addr_r3));
        base_off_r7 = (s32)D_off_FFFFD838;
        asm volatile("" : "+r"(base_off_r7));
        asm volatile("" : "=&r"(base) : "r"(base_addr_r3), "r"(base_off_r7));
        base = base_addr_r3 + base_off_r7;
    }
    sp20 = part1 + (part2 + base);
    {
        register s32 state_a_r1 asm("r1");
        register s32 state_b_r3 asm("r3");
        register s32 state_addr_r0 asm("r0");
        register s32 state_off_r7 asm("r7");
        asm volatile("" : "=r"(state_a_r1) : "0"(products[1]));
        asm volatile("" :: "r"(products[0]));
        state_b_r3 = products[0];
        asm volatile("" : "+r"(state_b_r3));
        state_addr_r0 = state_a_r1 + state_b_r3;
        state_addr_r0 += base;
        state_off_r7 = (s32)D_off_000027C8;
        state_addr_r0 += state_off_r7;
        temp_r7 = 1 & *(u16 *)state_addr_r0;
        asm volatile("" :: "rm"(products[1]));
    }
    if (temp_r7 == 0) {
        M2C_FIELD(temp_r6, s16 *, 4) = func_080E813C(sp10, temp_r1, temp_r2, temp_r3, (s32)temp_r4, (s32)temp_r5, temp_r7);
        M2C_FIELD(temp_r6, s16 *, 8) = func_080E813C(sp10, temp_r1, temp_r2, temp_r3, (s32)temp_r4, (s32)temp_r5, 1);
        M2C_FIELD(temp_r6, u16 *, 2) = func_080E7C18(sp10, temp_r1, temp_r2, temp_r3, (s32)temp_r4, (s32)temp_r5, temp_r7);
        temp_r0_3 = func_080E7C18(sp10, temp_r1, temp_r2, temp_r3, (s32)temp_r4, (s32)temp_r5, 1);
        M2C_FIELD(temp_r6, u16 *, 6) = temp_r0_3;
        if ((s32)(temp_r0_3 << 0x10) < 0) {
            M2C_FIELD(temp_r6, u16 *, 6) = (u16)temp_r7;
        }
        {
            s32 cmp_left;
            s32 cmp_right;
            register s32 reserve_r3 asm("r3");
            register s32 reserve_r4 asm("r4");
            register s32 reserve_r5 asm("r5");
            register void *cmp_base_r2 asm("r2");
            cmp_base_r2 = sp20;
            cmp_left = (s32)M2C_FIELD(cmp_base_r2, s16 *, 6);
            asm volatile("" : "=r"(reserve_r3), "=r"(reserve_r4), "=r"(reserve_r5));
            cmp_right = (s32)M2C_FIELD(temp_r6, s16 *, 4);
            asm volatile("" :: "r"(reserve_r3), "r"(reserve_r4), "r"(reserve_r5));
            asm volatile("" :: "r"(cmp_base_r2));
            if (cmp_left < cmp_right) {
                M2C_FIELD(temp_r6, u16 *, 0) = (u16)(M2C_FIELD(temp_r6, u16 *, 0) | 2);
            }
        }
    } else {
        s32 table_index;
        s32 table_term;
        u16 table_value2;
        u16 table_value4;
        s32 table_zero;
        table_index = sp18 * 4;
        table_term = sp14 * 0x270;
        table_index += table_term;
        table_term = spC * 0x1380;
        table_index += table_term;
        table_index += base;
        temp_r0_4 = (M2C_FIELD(table_index, u16 *, 0x52) * 0x18) + (s32)D_087B2524;
        table_value2 = M2C_FIELD(temp_r0_4, u16 *, 0xA);
        table_zero = 0;
        M2C_FIELD(temp_r6, u16 *, 2) = table_value2;
        table_value4 = M2C_FIELD(temp_r0_4, u16 *, 0xC);
        M2C_FIELD(temp_r6, u16 *, 4) = table_value4;
        M2C_FIELD(temp_r6, u16 *, 8) = table_zero;
        M2C_FIELD(temp_r6, u16 *, 6) = table_zero;
    }
    {
        s32 old_flags;
        register s32 final_flags_r1 asm("r1");
        old_flags = M2C_FIELD(temp_r6, u16 *, 0);
        final_flags_r1 = 1;
        final_flags_r1 |= old_flags;
        M2C_FIELD(temp_r6, u16 *, 0) = (u16)final_flags_r1;
    }
    *sp1C += 1;
    ret = 1;
    goto done;

return_zero:
    ret = 0;
done:
    return ret;
}
