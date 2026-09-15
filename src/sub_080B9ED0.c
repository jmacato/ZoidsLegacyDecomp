#include "m2c_prelude.h"
#define NULL ((void *)0)

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
extern s32 func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, s32, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
asm(".set func_0809538C_4, func_0809538C");
M2C_UNK func_0809538C_4(s32, s32, s32, s32);        /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C(s16, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_0809844C_wide, func_0809844C");
M2C_UNK func_0809844C_wide(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080984C4(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098834(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A52C(u8, u8, s32, s32, s32);       /* extern */
M2C_UNK func_080AC214(s32, M2C_UNK);                /* extern */
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACBA0(s32);                         /* extern */
M2C_UNK func_080ACBDC(s32, u32);                    /* extern */
M2C_UNK func_080B61C8(s32, s32, s32);               /* extern */
M2C_UNK func_080E5C34(u8);                          /* extern */
M2C_UNK func_080E5E64(s32);                         /* extern */
M2C_UNK func_080E5EFC(s32, u8, u8);                 /* extern */
s32 func_080E67F0(u8);                              /* extern */
s32 func_080E7B64(u8);                              /* extern */
s16 func_080ECD98(s16, s32);                        /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080B9ED0(void) {
    u16 items[4];
    u8 counts[4];
    volatile u32 selected;
    volatile u32 sp24;
    volatile s32 sp28;
    M2C_UNK var_r0;
    s32 temp_r7;
    s32 temp_r0;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 aggregation_offset;
    u16 aggregation_field_value;
    register u32 aggregation_next_r2 asm("r2");
    s32 temp_r5;
    volatile s32 var_r2;
    s32 var_r6;
    u16 temp_r1;
    u16 temp_r4;
    register u32 var_r9 asm("r9");
    u8 temp_r0_2;
    s32 var_r0_2;
    u8 var_r3;
    u8 var_r5;
    u8 var_r5_2;
    u8 var_r5_3;
    u8 *counts_base;
    register u8 *selected_slot asm("r6");
    register u8 *selected_slot_view asm("r4");
    register u32 selected_copy asm("r4");
    register u32 scroll_copy asm("r1");
    void *temp_r1_2;
    register s32 record_base asm("sl");
    register void *var_r8 asm("r8");

    var_r6 = 0;
loop_1:
    if (var_r6 != 0x110) {
        goto block_3;
    }
    goto block_46;
block_3:
    if (var_r6 > 0x110) {
        goto block_12;
    }
    if (var_r6 == 0x10) {
        goto block_24;
    }
    if (var_r6 > 0x10) {
        goto block_8;
    }
    if (var_r6 == 0) {
        goto block_23;
    }
    goto block_96;
block_8:
    if (var_r6 == 0x20) {
        goto block_26;
    }
    if (var_r6 != 0x100) {
        goto block_11;
    }
    goto block_45;
block_11:
    goto block_96;
block_12:
    if (var_r6 != 0x210) {
        goto block_14;
    }
    goto block_66;
block_14:
    if (var_r6 > 0x210) {
        goto block_18;
    }
    if (var_r6 != 0x200) {
        goto block_17;
    }
    goto block_52;
block_17:
    goto block_96;
block_18:
    if (var_r6 != 0x220) {
        goto block_20;
    }
    goto block_72;
block_20:
    if (var_r6 != 0x300) {
        goto block_22;
    }
    goto block_82;
block_22:
    goto block_96;
block_23:
    func_08098BB4(0x08005E9C);
    func_080B61C8(0, 0, 0);
    func_080ACA8C(7, 1, 1);
    asm volatile(
        "mov r0, #72\n\t"
        "str r0, [sp, #0]\n\t"
        "str r6, [sp, #4]\n\t"
        "str r6, [sp, #8]\n\t"
        "mov r0, #8\n\t"
        "str r0, [sp, #12]\n\t"
        "str r6, [sp, #16]"
        : : "r"(var_r6) : "r0", "r1", "memory");
    sp28 = func_08094484_4(
        ({ register s32 arg asm("r0") = 0x0821024C;
           asm volatile("" : "+r"(arg)); arg; }),
        ({ register s32 arg asm("r1") = 0x08210258;
           asm volatile("" : "+r"(arg)); arg; }),
        0, 0xB8);
    asm volatile(".if 0");
    func_08094484(0, 0, 0, 0, 0, 0, 0, 0, 0);
    asm volatile(".endif");
    {
        register s32 scroll_zero_r1 asm("r1") = 0;

        asm volatile("" : "+r"(scroll_zero_r1));
        sp24 = scroll_zero_r1;
    }
    {
        register s32 selected_zero_r2 asm("r2") = 0;

        asm volatile("" : "+r"(selected_zero_r2));
        selected = selected_zero_r2;
    }
    var_r6 = 0x10;
    goto block_96;
block_24:
    {
        register s32 block24_arg0_r0 asm("r0") = 4;
        register s32 block24_arg1_r1 asm("r1") = 0x82C;

        asm volatile("" : "+r"(block24_arg0_r0));
        asm volatile("" : "+r"(block24_arg1_r1));
        func_080AC214(block24_arg0_r0, block24_arg1_r1);
    }
    goto block_95;
block_26:
    {
        register s32 entry_address_r0 asm("r0") = 0x020321A4;
        register s32 selected_r3 asm("r3") = (s32) selected;
        register s32 entry_base_r4 asm("r4");

        asm volatile("" : "+r"(entry_address_r0), "+r"(selected_r3));
        entry_address_r0 =
            *(volatile u8 *)(selected_r3 + entry_address_r0) * 0x70;
        entry_base_r4 = 0x020218E8;
        asm volatile("" : "+r"(entry_base_r4));
        record_base = entry_base_r4;
        asm volatile("" : "+r"(record_base));
        entry_address_r0 += record_base;
        var_r8 = (void *)entry_address_r0;
        asm volatile("" : : "r"(var_r8), "r"(var_r8));
        {
        register u8 entry_value_r0 asm("r0") =
            M2C_FIELD(entry_address_r0, u8 *, 0);
        register u8 *entry_record_r2 asm("r2") = var_r8;

        asm volatile("" : : "r"(entry_value_r0));
        asm volatile("" : "+r"(entry_record_r2));
        func_0809A52C(entry_value_r0, M2C_FIELD(entry_record_r2, u8 *, 1),
            0, 0, 0x02002880);
        }
    }
    {
    register s32 compare_result_r0 asm("r0");
    register s32 current_stat_r1 asm("r1");
    register s32 compare_flag_r2 asm("r2");

    asm volatile(
        ".syntax unified\n\t"
        "mov r3, %5\n\t"
        "movs r4, #6\n\t"
        "ldrsh %0, [r3, r4]\n\t"
        "movs %3, #0\n\t"
        "movs %2, #58\n\t"
        "ldrsh %1, [r3, %2]\n\t"
        "movs %2, #10\n\t"
        "str %3, [sp, #44]\n\t"
        "bl func_080ECD98\n\t"
        "mov r3, %5\n\t"
        "movs r4, #6\n\t"
        "ldrsh %2, [r3, r4]\n\t"
        "lsls %1, %1, #16\n\t"
        "asrs %1, %1, #16\n\t"
        "ldr %3, [sp, #44]\n\t"
        ".syntax divided"
        : "=&l"(temp_r7), "=&r"(compare_result_r0),
          "=&r"(current_stat_r1), "=&r"(compare_flag_r2), "=m"(var_r2)
        : "r"(var_r8)
        : "r3", "r4", "lr", "cc", "memory");
    if (current_stat_r1 >= compare_result_r0) {
        goto block_28;
    }
    compare_flag_r2 = 1;
block_28:
    func_0809844C_wide(temp_r7, 4, compare_flag_r2, 0xA, 5, 3, 8);
    }
    {
        register u8 *field3a_record_r1 asm("r1") = var_r8;
        register u32 field3a_offset_r2 asm("r2") = 0x3A;
        register s32 field3a_value_r0 asm("r0");

        asm volatile("ldrsh %0, [%1, %2]"
            : "=l"(field3a_value_r0)
            : "l"(field3a_record_r1), "l"(field3a_offset_r2)
            : "memory");
        func_0809844C_wide(field3a_value_r0, 4, 0, 0xA, 5, 8, 8);
    }
    {
        register u8 *field3e_record_r3 asm("r3") = var_r8;
        register u32 field3e_offset_r1 asm("r1") = 0x3E;
        register s32 field3e_value_r0 asm("r0");

        asm volatile("ldrsh %0, [%1, %2]"
            : "=l"(field3e_value_r0)
            : "l"(field3e_record_r3), "l"(field3e_offset_r1)
            : "memory");
        func_0809844C_wide(field3e_value_r0, 4, 0, 0xA, 5, 8, 9);
    }
    func_080986B4(6);
    asm volatile(
        "mov r2, #4\n\t"
        "neg r2, r2\n\t"
        "add sl, r2"
        : "+r"(record_base)
        :
        : "r2", "cc");
    asm volatile("" : "+r"(record_base));
    {
        register u8 *display_record_r3 asm("r3") = var_r8;
        register s32 display_addr_r0 asm("r0");

        asm volatile("" : "+r"(display_record_r3));
        display_addr_r0 = M2C_FIELD(display_record_r3, u8 *, 2) << 6;
        display_addr_r0 += record_base;
        temp_r7 = 0x5A94;
        asm volatile("" : "+r"(temp_r7));
        display_addr_r0 += temp_r7;
        func_08098248(func_080E7B64(*(u8 *)display_addr_r0), 0, 6);
    }
    {
        register s32 dialog_arg0_r0 asm("r0") = 7;

        asm volatile("" : "+r"(dialog_arg0_r0));
        func_080ACBDC(dialog_arg0_r0, sp24);
    }
    func_08098BB4(0x08005F21);
    selected = *(volatile u8 *)0x0200A880;
    sp24 = (u32) *(u8 *)0x0200A881;
    temp_r0_2 = *(volatile u8 *)0x0200A882;
    if (temp_r0_2 != 0) {
        goto block_30;
    }
    goto block_96;
block_30:
    if (temp_r0_2 == 1) {
        goto block_32;
    }
    goto block_43;
block_32:
    {
    register s32 block32_zero_r5 asm("r5");
    {
        register u16 *flag_record_r4 asm("r4") = var_r8;
        register u32 flag_mask_r2 asm("r2");
        register u32 flag_mask_r0 asm("r0");

        asm volatile("" : "+r"(flag_record_r4));
        temp_r1 = flag_record_r4[2];
        flag_mask_r2 = 0xFFFE;
        asm volatile("" : "+r"(flag_mask_r2));
        flag_mask_r0 = flag_mask_r2;
        asm volatile("" : "+r"(flag_mask_r0));
        temp_r1 &= flag_mask_r0;
        block32_zero_r5 = 0;
        flag_record_r4[2] = temp_r1;
    }
    temp_r4 = 4 & temp_r1;
    if (temp_r4 == 0) {
        goto block_35;
    }
    func_08092E84(0x58);
    {
        register s32 *out_args asm("sp");
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        out_args[0] = block32_zero_r5;
        out_args[1] = block32_zero_r5;
        {
            register s32 stack47_r3 asm("r3") = 0x2F;

            asm volatile("" : "+r"(stack47_r3));
            out_args[2] = stack47_r3;
        }
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        call_r1 = 0x28C8;
        call_r2 = 0x2858;
        call_r3 = 0;
        asm volatile("" : "+r"(call_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, call_r1, call_r2, call_r3);
    }
    var_r0 = 0x0800607D;
    goto block_40;
    }
block_35:
    temp_r5 = 0x12 & temp_r1;
    if (temp_r5 == 0) {
        goto block_38;
    }
    func_08092E84(0x58);
    {
        register s32 *out_args asm("sp");
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        out_args[0] = temp_r4;
        out_args[1] = temp_r4;
        {
            register s32 stack47_r4 asm("r4") = 0x2F;

            asm volatile("" : "+r"(stack47_r4));
            out_args[2] = stack47_r4;
        }
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        call_r1 = 0x38B8;
        call_r2 = 0x2858;
        call_r3 = 0;
        asm volatile("" : "+r"(call_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, call_r1, call_r2, call_r3);
    }
    var_r0 = 0x080060D5;
    goto block_40;
block_38:
    {
    register u8 *kind_record_r1 asm("r1") = var_r8;

    asm volatile("" : "+r"(kind_record_r1));
    if (*(u8 *)((M2C_FIELD(kind_record_r1, u8 *, 2) << 6) +
            record_base + temp_r7) != 1) {
        goto block_42;
    }
    func_08092E84(0x58);
    {
        register s32 *out_args asm("sp");
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        out_args[0] = temp_r5;
        out_args[1] = temp_r5;
        {
            register s32 stack47_r2 asm("r2") = 0x2F;

            asm volatile("" : "+r"(stack47_r2));
            out_args[2] = stack47_r2;
        }
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        call_r1 = 0x38B8;
        call_r2 = 0x2060;
        call_r3 = 0;
        asm volatile("" : "+r"(call_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, call_r1, call_r2, call_r3);
    }
    func_08098BB4(0x0800611D);
    func_080981F0(func_080E7B64(1U), 1, 7, 6, temp_r5);
    var_r0 = 0x0800612F;
    }
block_40:
    func_08098BB4(var_r0);
    func_0809534C();
    goto block_96;
block_42:
    var_r6 = 0x100;
    goto block_96;
block_43:
    func_08094554(sp28);
    func_080ACBA0(7);
    func_08098BB4(0x08005F25);
    return;
block_45:
    {
        register u8 *state_record_r3 asm("r3") = var_r8;

        asm volatile("" : "+r"(state_record_r3));
        var_r0_2 = M2C_FIELD(state_record_r3, u8 *, 2);
    }
    var_r6 = 0x200;
    goto block_63;
block_46:
    {
        register s32 state_r4 asm("r4") = 0;
    {
        register s32 *out_args asm("sp");
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        asm volatile("" : "+r"(state_r4));
        out_args[0] = state_r4;
        out_args[1] = state_r4;
        out_args[2] = 0x2F;
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        call_r1 = 0x30C0;
        call_r2 = 0x1048;
        call_r3 = 0;
        asm volatile("" : "+r"(call_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, call_r1, call_r2, call_r3);
    }
    func_08098BB4(0x08005F2C);
    {
        register s32 *lookup_table_r1 asm("r1") = (s32 *)0x087EDD54;
        register u8 *lookup_record_r2 asm("r2") = var_r8;

        asm volatile("" : "+r"(lookup_table_r1));
        asm volatile("" : "+r"(lookup_record_r2));
        func_080981F0(lookup_table_r1[M2C_FIELD(lookup_record_r2, u8 *, 0)],
            0, 7, 0, state_r4);
    }
    {
        register s32 display_addr_r0 asm("r0");
        register s32 display_base_r1 asm("r1") = 0x020218E4;
        register u8 *kind_record_r3 asm("r3") = var_r8;

        asm volatile("" : "+r"(display_base_r1));
        asm volatile("" : "+r"(kind_record_r3));
        display_addr_r0 = M2C_FIELD(kind_record_r3, u8 *, 2) << 6;
        display_addr_r0 += display_base_r1;
        state_r4 = 0x5A94;
        asm volatile("" : "+r"(state_r4));
        display_addr_r0 += state_r4;
        func_080981F0(func_080E7B64(*(u8 *)display_addr_r0), 0, 7, 0, 2);
    }
    }
    func_08098BB4(0x08005F5A);
    func_080972C8();
    func_0809534C();
    func_080ED17C(1);
    temp_r0_2 = *(volatile u8 *)0x0200A882;
    var_r6 = 0x20;
    if (temp_r0_2 == 1) {
        goto block_48;
    }
    goto block_96;
block_48:
    if (*(u8 *)0x0200A880 == 0) {
        goto block_50;
    }
    goto block_96;
block_50:
    var_r6 = 0x200;
    goto block_96;
block_52:
    var_r9 = 0;
    var_r5 = 0;
    counts_base = counts;
loop_53:
    aggregation_offset = var_r5 * 4;
    temp_r1_2 = var_r8 + aggregation_offset + 0x52;
    aggregation_field_value = *(u16 *)temp_r1_2;
    temp_r0_3 = aggregation_offset;
    asm volatile(""
        : "+&r"(temp_r0_3)
        : "r"(aggregation_offset), "r"(aggregation_field_value));
    aggregation_next_r2 = var_r5 + 1;
    asm volatile("" : "+r"(aggregation_next_r2));
    if (aggregation_field_value == 0) {
        goto block_61;
    }
    var_r3 = 0;
    if ((u32) var_r3 >= var_r9) {
        goto block_59;
    }
    {
    register void *aggregation_inner_field asm("r1");

    asm volatile("mov %0, %1"
        : "=&l"(aggregation_inner_field)
        : "l"(temp_r1_2));
loop_56:
    asm volatile("" :: "r"(var_r5));
    if (items[var_r3] != *(u16 *)aggregation_inner_field) {
        goto block_58;
    }
    counts_base[var_r3] += 1;
    goto block_59;
block_58:
    var_r3 += 1;
    if ((u32) var_r3 < var_r9) {
        goto loop_56;
    }
    }
block_59:
    if (var_r3 != var_r9) {
        goto block_61;
    }
    items[var_r9] = (u16) M2C_FIELD((var_r8 + temp_r0_3), u16 *, 0x52);
    counts_base[var_r9] = 1;
    var_r9 = (u32) (u8) (var_r9 + 1);
block_61:
    var_r5 = aggregation_next_r2;
    asm volatile("" :: "r"(aggregation_next_r2));
    if ((u32) var_r5 <= 3U) {
        goto loop_53;
    }
    var_r6 = 0x300;
    var_r0_2 = var_r9;
block_63:
    if (var_r0_2 != 0) {
        goto block_65;
    }
    goto block_96;
block_65:
    var_r6 -= 0xF0;
    goto block_96;
block_66:
    {
        register s32 *out_args asm("sp");
        register s32 zero_r1 asm("r1") = 0;
        register s32 call_r0 asm("r0");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        asm volatile("" : "+r"(zero_r1));
        out_args[0] = zero_r1;
        out_args[1] = zero_r1;
        {
            register s32 stack47_r2 asm("r2") = 0x2F;

            asm volatile("" : "+r"(stack47_r2));
            out_args[2] = stack47_r2;
        }
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        zero_r1 = 0x18D8;
        call_r2 = 0x1048;
        call_r3 = 0;
        asm volatile("" : "+r"(zero_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, zero_r1, call_r2, call_r3);
    }
    func_08098BB4(0x08005F5F);
    func_080972C8();
    func_0809534C();
    func_080ED17C(1);
    temp_r0_2 = *(volatile u8 *)0x0200A882;
    var_r6 = 0x20;
    if (temp_r0_2 == 1) {
        goto block_68;
    }
    goto block_96;
block_68:
    if (*(volatile u8 *)0x0200A880 == 0) {
        goto block_70;
    }
    goto block_96;
block_70:
    var_r6 = 0x220;
    goto block_96;
block_72:
    var_r5_2 = 0;
    if ((u32) var_r5_2 >= var_r9) {
        goto block_78;
    }
    {
    u16 *validation_item;
    register u8 *inventory_base_r7 asm("r7") = (u8 *)0x02028218;
    register s32 validation_zero_r6 asm("r6") = 0;

    asm volatile("" : "+r"(inventory_base_r7), "+r"(validation_zero_r6));
loop_74:
    validation_item = &items[var_r5_2];
    asm volatile("" :: "r"(validation_item));
    if ((s32) (*(u8 *)((u32)*validation_item -
            (0U - (u32)inventory_base_r7)) + counts[var_r5_2]) <= 0x63) {
        goto block_77;
    }
    {
        register s32 *out_args asm("sp");
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        out_args[0] = validation_zero_r6;
        out_args[1] = validation_zero_r6;
        {
            register s32 stack47_r3 asm("r3") = 0x2F;

            asm volatile("" : "+r"(stack47_r3));
            out_args[2] = stack47_r3;
        }
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        call_r1 = 0x18D8;
        call_r2 = 0x1048;
        call_r3 = 0;
        asm volatile("" : "+r"(call_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, call_r1, call_r2, call_r3);
    }
    func_08098BB4(0x0800551A);
    {
        register s32 *validation_table_r1 asm("r1") = (s32 *)0x087EE170;

        asm volatile("" : "+r"(validation_table_r1));
        func_080981F0(validation_table_r1[*validation_item],
            0, 9, 0, validation_zero_r6);
    }
    func_08098BB4(0x08005575);
    func_080972C8();
    func_0809534C();
    func_080ED17C(1);
    if (*(volatile u8 *)0x0200A882 == 2) {
        goto block_78;
    }
    if (*(volatile u8 *)0x0200A880 != 0) {
        goto block_78;
    }
block_77:
    var_r5_2 += 1;
    if ((u32) var_r5_2 < var_r9) {
        goto loop_74;
    }
    }
block_78:
    var_r6 = 0x300;
    if ((u32) var_r5_2 < var_r9) {
        goto block_80;
    }
    goto block_96;
block_80:
    goto block_95;
block_82:
    {
        register s32 state300_zero_r4 asm("r4") = 0;
    {
        register s32 *out_args asm("sp");
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        asm volatile("" : "+r"(state300_zero_r4));
        out_args[0] = state300_zero_r4;
        out_args[1] = state300_zero_r4;
        out_args[2] = 0x2F;
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        call_r1 = 0x28C8;
        call_r2 = 0x1048;
        call_r3 = 0;
        asm volatile("" : "+r"(call_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, call_r1, call_r2, call_r3);
    }
    func_08098BB4(0x08006054);
    {
        register s32 *lookup_table_r1 asm("r1") = (s32 *)0x087EDD54;
        register u8 *lookup_record_r2 asm("r2") = var_r8;

        asm volatile("" : "+r"(lookup_table_r1));
        asm volatile("" : "+r"(lookup_record_r2));
        func_080981F0(lookup_table_r1[M2C_FIELD(lookup_record_r2, u8 *, 0)],
            0, 7, 0, state300_zero_r4);
    }
    }
    func_08098248(0x08106F18, 0, 7);
    {
        register u8 *selected_base_r0 asm("r0") = (u8 *)0x020321A4;
        register u32 selected_index_r3 asm("r3") = selected;

        asm volatile("" : "+r"(selected_base_r0));
        asm volatile("" : "+r"(selected_index_r3));
        asm volatile("add %0, %2, %1"
                     : "=r"(selected_slot)
                     : "r"(selected_base_r0), "r"(selected_index_r3));
    }
    temp_r0_4 = func_080E67F0(*selected_slot);
    func_080984C4(temp_r0_4, 7, 0, 0, 7);
    func_08098248(0x08106F04, 0, 7);
    func_08098BB4(0x08006078);
    func_080972C8();
    func_0809534C();
    func_080ED17C(1);
    if (*(volatile u8 *)0x0200A882 != 1) {
        goto block_95;
    }
    if (*(volatile u8 *)0x0200A880 != 0) {
        goto block_95;
    }
    func_080E5E64(temp_r0_4);
    var_r5_3 = 0;
    selected_slot_view = selected_slot;
    asm volatile("" : "+r"(selected_slot_view));
loop_85:
    if (M2C_FIELD(((var_r5_3 * 4) + var_r8), u16 *, 0x52) == 0) {
        goto block_87;
    }
    func_080E5EFC(0, *selected_slot_view, var_r5_3);
block_87:
    var_r5_3 += 1;
    if ((u32) var_r5_3 <= 3U) {
        goto loop_85;
    }
    {
        register u8 *final_selected_base_r0 asm("r0") = (u8 *)0x020321A4;

        asm volatile("" : "+r"(final_selected_base_r0));
        selected_copy = selected;
        asm volatile("" : "+r"(selected_copy));
        final_selected_base_r0 = (u8 *)(selected_copy -
            (0U - (u32)final_selected_base_r0));
        func_080E5C34(*final_selected_base_r0);
    }
    func_080B61C8(0, 0, 0);
    if (*(u8 *)0x02032272 != selected_copy) {
        goto block_90;
    }
    {
        register u32 selected_next_r0 asm("r0") = selected_copy;

        asm volatile("" : "+r"(selected_next_r0));
        selected_next_r0 = (u8) (selected_next_r0 - 1);
        selected = selected_next_r0;
    }
block_90:
    {
        register u32 selected_compare_r0 asm("r0") = selected;

        asm volatile("" : "+r"(selected_compare_r0));
        scroll_copy = sp24;
        asm volatile("" : "+r"(scroll_copy));
        if (selected_compare_r0 >= scroll_copy) {
            goto block_94;
        }
    }
    if (scroll_copy <= 6U) {
        goto block_93;
    }
    {
        register u32 scroll_next_r0 asm("r0") = scroll_copy;

        asm volatile("" : "+r"(scroll_next_r0));
        scroll_next_r0 = (u8) (scroll_next_r0 - 7);
        sp24 = scroll_next_r0;
        asm volatile("" : : "m"(sp24));
    }
    goto block_94;
block_93:
    {
        register u32 scroll_zero_r2 asm("r2") = 0;

        asm volatile("" : "+r"(scroll_zero_r2));
        sp24 = scroll_zero_r2;
    }
block_94:
    func_08098834(4);
    var_r6 = 0x10;
    goto block_96;
block_95:
    var_r6 = 0x20;
block_96:
    {
        register s32 tail_guard_r3 asm("r3") = 0;

        asm volatile("" : "+r"(tail_guard_r3));
        if (tail_guard_r3 != 0) {
            goto block_98;
        }
    }
    goto loop_1;
block_98:
    return;
}
