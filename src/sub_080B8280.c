#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32);
asm(".set func_08094484_4, func_08094484");
extern s32 func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_08094554(s32);
M2C_UNK func_0809534C();
M2C_UNK func_0809538C(s32, s32, M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_080972C8();
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);
M2C_UNK func_08098248(s32, s32, s32);
M2C_UNK func_0809844C(s32, s32, s32, s32, s32, s32, s32);
M2C_UNK func_080986B4(s32);
M2C_UNK func_08098BB4(M2C_UNK);
M2C_UNK func_0809A52C(u8, u8, s32, s32, s32);
M2C_UNK func_080AC214(s32, s32);
M2C_UNK func_080AC6B8(s32);
M2C_UNK func_080AC87C(void *, s32);
M2C_UNK func_080ACA8C(s32, s32, s32);
M2C_UNK func_080ACBA0(s32);
M2C_UNK func_080ACBDC(s32, s32);
s32 func_080B0354(s32, s32);
M2C_UNK func_080B61C8(s32, s32, u8);
u8 func_080B80CC(u8, s32);
M2C_UNK func_080E5A18(u8, s32);
M2C_UNK func_080E5B44(void *, u8, s32);
M2C_UNK func_080E5E38(u8, s32);
M2C_UNK func_080E5E90(u32);
M2C_UNK func_080E5EFC(s32, u8, u32);
s32 func_080E7B64(u8);
s32 func_080ECD98(s32, s32);
M2C_UNK func_080ED17C(s32);
extern u8 D_020218E4[];
extern u8 D_0203237A[];

void sub_080B8280(void) {
    u16 sp14[4];
    u8 sp1C[4];
    u8 sp20[4];
    u32 sp24;
    s32 sp28;
    u32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 temp_r7;
    s32 temp_r0_6;
    register s32 aggregation_offset_r0 asm("r0");
    register s32 temp_r0_8 asm("sl");
    register u8 *aggregation_counts_r7 asm("r7");
    register u8 *aggregation_field_ptr_r3 asm("r3");
    register u32 aggregation_r1 asm("r1");
    register u32 aggregation_next_r2 asm("r2");
    u32 availability_address;
    s32 compare_result;
    s32 current_stat;
    s32 var_r0;
    s32 var_r2;
    s32 var_r6;
    s32 threshold_120;
    u16 *var_r3;
    u16 *var_r4_3;
    u16 temp_r1;
    u32 var_r4;
    register u32 var_r5_2 asm("r5");
    register u32 var_r5_3 asm("r5");
    u32 var_r5_4;
    u32 var_r5_5;
    u32 var_r5_6;
    register u32 var_r6_3 asm("r6");
    register u32 zero_r4 asm("r4");
    s32 temp_r0_2;
    s32 temp_r0_3;
    u8 temp_r0_4;
    s32 temp_r0_5;
    u8 temp_r0_7;
    u8 temp_r0_9;
    register u32 temp_r2 asm("r2");
    u8 var_r0_2;
    register u32 var_r5 asm("r5");
    s32 var_r6_2;
    u8 *temp_r0;
    register u8 *option_record_address_r1 asm("r1");
    u8 *var_r8;
    u8 *var_r9;
    register s32 *display_item_table asm("r4");
    register u8 *resource_base asm("r7");
    register u8 *record_option_base asm("r4");
    register u8 *availability_base asm("r3");
    u8 *selected_slot;

    var_r6 = 0;
loop_1:
    asm volatile("" : :
        "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6),
        "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6));
    asm volatile("" : :
        "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6),
        "r"(var_r6), "r"(var_r6), "r"(var_r6), "r"(var_r6));
    if (var_r6 != 0x100) {
        goto block_3;
    }
    goto block_85;
block_3:
    if (var_r6 > 0x100) {
        goto block_11;
    }
    if (var_r6 == 0x10) {
        goto block_23;
    }
    if (var_r6 > 0x10) {
        goto block_8;
    }
    if (var_r6 == 0) {
        goto block_22;
    }
    goto block_145;
block_8:
    if (var_r6 == 0x20) {
        goto block_24;
    }
    if (var_r6 == 0x30) {
        goto block_34;
    }
    goto block_145;
block_11:
    {
        register s32 threshold_seed_r1 asm("r1") = 0x120;

        asm volatile("mov %0, %1"
            : "=r"(threshold_120)
            : "l"(threshold_seed_r1));
    }
    if (var_r6 != threshold_120) {
        goto block_13;
    }
    goto block_99;
block_13:
    if (var_r6 > threshold_120) {
        goto block_17;
    }
    {
        register s32 state_110_r0 asm("r0");

        asm volatile(
            ".syntax unified\n\t"
            "movs %0, #136\n\t"
            "lsls %0, %0, #1\n\t"
            ".syntax divided"
            : "=r"(state_110_r0));
        if (var_r6 != state_110_r0) {
            goto block_16;
        }
        goto block_88;
    }
block_16:
    goto block_145;
block_17:
    if (var_r6 != 0x200) {
        goto block_19;
    }
    goto block_124;
block_19:
    if (var_r6 != 0x300) {
        goto block_21;
    }
    goto block_130;
block_21:
    goto block_145;
block_22:
    func_08098BB4(0x080051A8);
    func_08098BB4(0x080055ED);
    func_080AC6B8(4);
    {
        register u32 initial_selection_r2 asm("r2") = 0;

        asm volatile("" : "+r"(initial_selection_r2));
        sp2C = initial_selection_r2;
    }
    var_r6 = 0x10;
    goto block_145;
block_23:
    func_08098BB4(0x080055ED);
    goto block_144;
block_24:
{
    register u8 *selection_base asm("r4") = D_0203237A;
    register u8 *selected_record_r0 asm("r0");
    register u8 *selected_record_base_r1 asm("r1");

    {
        register u8 *selection_address_r0 asm("r0");

        asm volatile("add %0, %1, %2"
            : "=&l"(selection_address_r0)
            : "l"(sp2C), "l"(selection_base)
            : "r1", "r2");
        selected_record_r0 = (u8 *)(*selection_address_r0 * 0xC);
    }
    asm volatile("" : "+r"(selected_record_r0));
    selected_record_base_r1 = (u8 *)0x087B1E04;
    asm volatile("" : "+r"(selected_record_base_r1));
    selected_record_r0 += (u32)selected_record_base_r1;
    var_r9 = selected_record_r0;
    func_080AC87C(selected_record_r0, 5);
    func_08098BB4(0x08005214);
    sp2C = *(u8 *)0x0200A880;
    temp_r0_2 = *(u8 *)0x0200A882;
    if (temp_r0_2 == 1) {
        goto block_30;
    }
    if ((s32) temp_r0_2 > 1) {
        goto block_27;
    }
    goto block_145;
block_27:
    if (temp_r0_2 == 2) {
        goto block_33;
    }
    goto block_145;
block_30:
    asm volatile("add %0, %1, %2"
        : "=&l"(selected_record_r0)
        : "l"(sp2C), "l"(selection_base));
    if (func_080B0354((*selected_record_r0 * 0x38) + 0x087AFCC4, 1) != 0) {
        goto block_32;
    }
    goto block_145;
block_32:
    var_r6 = 0x30;
    goto block_145;
block_33:
    func_08098BB4(0x08005218);
    return;
}
block_34:
    {
        register s32 loaded_status_r0 asm("r0");
        register s32 status_r1 asm("r1");

        status_r1 = (u32)var_r9;
        asm volatile("" : "+r"(status_r1));
        loaded_status_r0 = M2C_FIELD(status_r1, u8 *, 0);
        asm volatile("" : "+r"(loaded_status_r0));
        status_r1 = loaded_status_r0;
        asm volatile("" : "+r"(status_r1));
        temp_r0_3 = status_r1;
    }
    if (temp_r0_3 != 0) {
        goto block_38;
    }
    if ((u32)D_020218E4[1] <= 0x96U) {
        goto block_38;
    }
    func_08098BB4(0x08005272);
    goto block_144;
block_38:
    var_r6_2 = 0;
    if ((temp_r0_3 << 0x18) == 0) {
        goto block_41;
    }
    func_080B61C8(0, 0, *(volatile u8 *)var_r9);
    if (*(u8 *)0x02032272 != 0) {
        goto block_41;
    }
    sp20[0] = 0;
    var_r6_2 = 1;
block_41:
    var_r5 = 0;
    resource_base = D_020218E4;
    record_option_base = var_r9 + 1;
    availability_base = (u8 *)0x020217FE;
loop_42:
    option_record_address_r1 = record_option_base + var_r5;
    temp_r0_4 = *option_record_address_r1;
    temp_r2 = var_r5 + 1;
    if (temp_r0_4 == 0) {
        goto block_45;
    }
    availability_address = temp_r0_4;
    availability_address += (u32)availability_base;
    if (*(u8 *)availability_address != 0) {
        goto block_45;
    }
    sp20[var_r6_2] = temp_r2;
    var_r6_2 = (u8)(var_r6_2 + 1);
block_45:
    var_r5 = temp_r2;
    if ((u32)var_r5 <= 1U) {
        goto loop_42;
    }
    {
        register u32 money_offset_r4 asm("r4") = 0x6A04;
        register u32 money_address_r0 asm("r0");
        register u32 current_money_r1 asm("r1");
        register u8 *money_record_r5 asm("r5");

        asm volatile(
            ".syntax unified\n\t"
            "adds %0, %1, %2\n\t"
            ".syntax divided"
            : "=l"(money_address_r0)
            : "l"(resource_base), "l"(money_offset_r4));
        current_money_r1 = *(u32 *)money_address_r0;
        asm volatile("" : "+r"(current_money_r1));
        money_record_r5 = var_r9;
        asm volatile("" : "+r"(money_record_r5));
        if (current_money_r1 >=
                (u32)M2C_FIELD(money_record_r5, u32 *, 4)) {
            goto block_48;
        }
    }
    sp20[var_r6_2] = 3;
    var_r6_2 = (u8)(var_r6_2 + 1);
block_48:
    if (var_r6_2 != 0) {
        goto block_50;
    }
    goto block_82;
block_50:
    func_08092E84(0x58);
    if (var_r6_2 == 2) {
        goto block_60;
    }
    if (var_r6_2 > 2) {
        goto block_55;
    }
    if (var_r6_2 == 1) {
        goto block_58;
    }
    goto block_63;
block_55:
    if (var_r6_2 == 3) {
        goto block_61;
    }
    if (var_r6_2 == 4) {
        goto block_62;
    }
    goto block_63;
block_58:
    func_08098BB4(0x0800521D);
    goto block_63;
block_60:
    func_08098BB4(0x08005231);
    goto block_63;
block_61:
    func_08098BB4(0x08005245);
    goto block_63;
block_62:
    func_08098BB4(0x08005259);
block_63:
    var_r5_2 = 0;
    if (var_r5_2 >= (u32)var_r6_2) {
        goto block_81;
    }
    display_item_table = (s32 *)0x087EEE60;
loop_65:
    {
        register u8 *display_stack_address_r0 asm("r0");

        asm volatile(
            "add r0, sp, #32\n\t"
            "add r0, r0, %1"
            : "=r"(display_stack_address_r0)
            : "r"(var_r5_2)
            : "cc");
        temp_r0_5 = *display_stack_address_r0;
    }
    if (temp_r0_5 == 1) {
        goto block_75;
    }
    if ((s32)temp_r0_5 > 1) {
        goto block_70;
    }
    if (temp_r0_5 == 0) {
        goto block_73;
    }
    goto block_80;
block_70:
    if (temp_r0_5 == 2) {
        goto block_76;
    }
    if (temp_r0_5 == 3) {
        goto block_79;
    }
    goto block_80;
block_73:
    var_r0 = 0x08106E54;
    goto block_78;
block_75:
    func_08098248(0x08106E7C, 0, 6);
    var_r0_2 = M2C_FIELD(var_r9, u8 *, 1);
    goto block_77;
block_76:
    func_08098248(0x08106E7C, 0, 6);
    {
        register u8 *option_record_r2 asm("r2") = var_r9;

        asm volatile("" : "+r"(option_record_r2));
        var_r0_2 = option_record_r2[2];
    }
block_77:
    func_08098248(display_item_table[var_r0_2], 0, 6);
    var_r0 = 0x08106E84;
block_78:
    func_08098248(var_r0, 0, 6);
    goto block_80;
block_79:
    func_08098248(0x08106E94, 0, 6);
block_80:
    var_r5_2 += 1;
    if (var_r5_2 < (u32)var_r6_2) {
        goto loop_65;
    }
block_81:
    func_08098BB4(0x0800526D);
    goto block_144;
block_82:
    temp_r0_9 = M2C_FIELD(var_r9, u8 *, 0);
    var_r6 = 0x100;
    if (temp_r0_9 == 0) {
        goto block_84;
    }
    goto block_145;
block_84:
    var_r6 = 0x200;
    goto block_145;
block_85:
{
    register s32 constructor_sp28_zero_r4 asm("r4");
    register s32 constructor_zero_r5 asm("r5");

    func_08098BB4(0x08005409);
    func_080AC214(6, 0x28);
    func_080ACA8C(7, 1, 1);
    constructor_sp28_zero_r4 = 0;
    asm volatile("" : "+r"(constructor_sp28_zero_r4));
    sp28 = constructor_sp28_zero_r4;
    constructor_zero_r5 = 0;
    asm volatile("" : "+r"(constructor_zero_r5));
    sp24 = constructor_zero_r5;
    asm volatile(
        "mov r0, #72\n\t"
        "str r0, [sp, #0]\n\t"
        "str r5, [sp, #4]\n\t"
        "str r5, [sp, #8]\n\t"
        "mov r0, #8\n\t"
        "str r0, [sp, #12]\n\t"
        "str r5, [sp, #16]"
        : : "r"(constructor_zero_r5) : "r0", "r1", "memory");
    sp34 = func_08094484_4(
        ({ register s32 arg asm("r0") = 0x0821024C;
           asm volatile("" : "+r"(arg)); arg; }),
        ({ register s32 arg asm("r1") = 0x08210258;
           asm volatile("" : "+r"(arg)); arg; }),
        0, 0xB8);
    asm volatile(".if 0");
    func_08094484(0, 0, 0, 0, 0, 0, 0, 0, 0);
    asm volatile(".endif");
}
block_86:
    var_r6 = 0x110;
    goto block_145;
block_88:
    {
        register s32 entry_offset_r0 asm("r0") = 0x020321A4;
        register s32 selected_r1 asm("r1") = (s32) sp24;
        register s32 entry_base_r2 asm("r2");

        asm volatile("" : "+r"(entry_offset_r0), "+r"(selected_r1));
        entry_offset_r0 =
            *(volatile u8 *)(selected_r1 + entry_offset_r0) * 0x70;
        entry_base_r2 = 0x020218E8;
        asm volatile("" : "+r"(entry_base_r2));
        entry_offset_r0 += entry_base_r2;
        var_r8 = (u8 *)entry_offset_r0;
        asm volatile("" : : "r"(var_r8), "r"(var_r8));
        {
            register u8 entry_value_r0 asm("r0") =
                M2C_FIELD(entry_offset_r0, u8 *, 0);
            register u8 *entry_record_r3 asm("r3") = var_r8;

            asm volatile("" : : "r"(entry_value_r0));
            asm volatile("" : "+r"(entry_record_r3));
            func_0809A52C(entry_value_r0,
                M2C_FIELD(entry_record_r3, u8 *, 1),
                0, 0, 0x02002880);
        }
    }
    {
    register u8 *stat_record_r4 asm("r4") = var_r8;

    asm volatile(
        ".syntax unified\n\t"
        "movs r5, #6\n\t"
        "ldrsh %0, [%1, r5]\n\t"
        ".syntax divided"
        : "=&l"(temp_r7)
        : "l"(stat_record_r4)
        : "r5", "memory");
    asm volatile("" : : "r"(temp_r7), "r"(temp_r7));
    sp38 = 0;
    var_r2 = 0;
    asm volatile("" : : "r"(var_r2), "r"(var_r2));
    {
        register u32 compare_offset_r1 asm("r1") = 0x3A;
        register s32 compare_arg_r0 asm("r0");

        asm volatile("ldrsh %0, [%1, %2]"
            : "=l"(compare_arg_r0)
            : "l"(stat_record_r4), "l"(compare_offset_r1)
            : "memory");
        compare_result = func_080ECD98(compare_arg_r0, 0xA);
    }
    {
        register u32 current_offset_r3 asm("r3") = 6;
        register s32 current_value_r1 asm("r1");

        asm volatile("ldrsh %0, [%1, %2]"
            : "=l"(current_value_r1)
            : "l"(stat_record_r4), "l"(current_offset_r3)
            : "memory");
        current_stat = current_value_r1;
    }
    if (current_stat >= (s16)compare_result) {
        goto block_90;
    }
    var_r2 = 1;
block_90:
    func_0809844C(temp_r7, 4, var_r2, 0xA, 7, 3, 8);
    }
    {
        register u8 *field3a_record_r1 asm("r1") = var_r8;
        register u32 field3a_offset_r2 asm("r2") = 0x3A;
        register s32 field3a_value_r0 asm("r0");

        asm volatile(
            ".syntax unified\n\t"
            "ldrsh %0, [%1, %2]\n\t"
            ".syntax divided"
            : "=l"(field3a_value_r0)
            : "l"(field3a_record_r1), "l"(field3a_offset_r2)
            : "memory");
        func_0809844C(field3a_value_r0,
            4, 0, 0xA, 7, 8, 8);
    }
    {
        register u8 *field3e_record_r3 asm("r3") = var_r8;
        register u32 field3e_offset_r1 asm("r1") = 0x3E;
        register s32 field3e_value_r0 asm("r0");

        asm volatile(
            ".syntax unified\n\t"
            "ldrsh %0, [%1, %2]\n\t"
            ".syntax divided"
            : "=l"(field3e_value_r0)
            : "l"(field3e_record_r3), "l"(field3e_offset_r1)
            : "memory");
        func_0809844C(field3e_value_r0, 4, 0, 0xA, 7, 8, 9);
    }
    func_080986B4(8);
    {
        register u8 *display_record_r2 asm("r2") = var_r8;
        register s32 display_addr_r0 asm("r0");
        register s32 display_base_r3 asm("r3");

        asm volatile(
            ".syntax unified\n\t"
            "ldrb %0, [%1, #2]\n\t"
            "lsls %0, %0, #6\n\t"
            ".syntax divided"
            : "=l"(display_addr_r0)
            : "l"(display_record_r2)
            : "memory");
        display_base_r3 = 0x020218E8;
        asm volatile("" : "+r"(display_base_r3));
        display_addr_r0 = display_base_r3 + display_addr_r0;
        {
            register s32 display_delta_r4 asm("r4") = 0x5A90;

            asm volatile("" : "+r"(display_delta_r4));
            display_addr_r0 += display_delta_r4;
        }
        func_08098248(func_080E7B64(*(u8 *)display_addr_r0), 0, 8);
    }
    func_080ACBDC(7, sp28);
    func_08098BB4(0x0800547C);
    sp24 = *(u8 *)0x0200A880;
    sp28 = (s32)*(u8 *)0x0200A881;
    temp_r0_7 = *(u8 *)0x0200A882;
    if (temp_r0_7 != 0) {
        goto block_92;
    }
    goto block_145;
block_92:
    if (temp_r0_7 != 1) {
        goto block_97;
    }
    {
        register u16 *flag_owner_r5 asm("r5") = (u16 *)var_r8;
        register u32 mask_r2 asm("r2");
        register u32 mask_r0 asm("r0");

        asm volatile("" : "+r"(flag_owner_r5));
        temp_r1 = flag_owner_r5[2];
        mask_r2 = 0xFFFE;
        asm volatile("" : "+r"(mask_r2));
        mask_r0 = mask_r2;
        asm volatile("" : "+r"(mask_r0));
        temp_r1 &= mask_r0;
        zero_r4 = 0;
        flag_owner_r5[2] = temp_r1;
    }
    if (!(0x12 & temp_r1)) {
        goto block_96;
    }
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(zero_r4) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x30C0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x2060;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    func_08098BB4(0x08005396);
    func_0809534C();
    goto block_145;
block_96:
    var_r6 = threshold_120;
    goto block_145;
block_97:
    func_08094554(sp34);
    func_080ACBA0(7);
    func_08098BB4(0x08005480);
    var_r6 = 0x10;
    goto block_145;
block_99:
    var_r6_3 = 0;
    var_r5_3 = 0;
    aggregation_counts_r7 = sp1C;
    asm volatile("" : "+r"(aggregation_counts_r7));
loop_100:
    aggregation_offset_r0 = var_r5_3 * 4;
    aggregation_field_ptr_r3 = var_r8;
    asm volatile("" : "+r"(aggregation_field_ptr_r3));
    aggregation_r1 = (u32)(aggregation_field_ptr_r3 + aggregation_offset_r0);
    asm volatile("" : "+r"(aggregation_r1));
    aggregation_field_ptr_r3 = (u8 *)aggregation_r1;
    asm volatile("" : "+r"(aggregation_field_ptr_r3));
    aggregation_field_ptr_r3 += 0x52;
    asm volatile("" : "+r"(aggregation_field_ptr_r3));
    aggregation_r1 = *(u16 *)aggregation_field_ptr_r3;
    asm volatile("" : "+r"(aggregation_r1));
    aggregation_next_r2 = var_r5_3 + 1;
    asm volatile("" : "+r"(aggregation_next_r2));
    temp_r0_8 = aggregation_offset_r0;
    asm volatile("" : "+r"(temp_r0_8));
    if (aggregation_r1 == 0) {
        goto block_108;
    }
    var_r4 = 0;
    if (var_r4 >= var_r6_3) {
        goto block_106;
    }
    aggregation_r1 = (u32)aggregation_field_ptr_r3;
    asm volatile("" : "+r"(aggregation_r1));
    var_r3 = sp14;
loop_103:
    if (*var_r3 != *(u16 *)aggregation_r1) {
        goto block_105;
    }
    aggregation_counts_r7[var_r4] += 1;
    goto block_106;
block_105:
    var_r3 += 1;
    var_r4 += 1;
    if (var_r4 < var_r6_3) {
        goto loop_103;
    }
block_106:
    if (var_r4 != var_r6_3) {
        goto block_108;
    }
    sp14[var_r6_3] = M2C_FIELD((var_r8 + temp_r0_8), u16 *, 0x52);
    aggregation_counts_r7[var_r6_3] = 1;
    {
        register u32 aggregation_count_next_r0 asm("r0") = var_r6_3 + 1;

        asm volatile("" : "+r"(aggregation_count_next_r0));
        var_r6_3 = (u8)aggregation_count_next_r0;
    }
block_108:
    var_r5_3 = aggregation_next_r2;
    if (var_r5_3 <= 3U) {
        goto loop_100;
    }
    if (var_r6_3 == 0) {
        goto block_122;
    }
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        asm volatile(
            "mov r0, #0\n\t"
            "str r0, [sp, #0]\n\t"
            "str r0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x10E0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x1048;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    func_08098BB4(0x08005487);
    func_080972C8();
    func_0809534C();
    func_080ED17C(1);
    if (*(u8 *)0x0200A882 == 1) {
        goto block_112;
    }
    goto block_86;
block_112:
    if (*(u8 *)0x0200A880 == 0) {
        goto block_114;
    }
    goto block_86;
block_114:
    var_r5_4 = 0;
    if (var_r5_4 >= var_r6_3) {
        goto block_122;
    }
    {
        register u32 level_base_r0 asm("r0") = 0x02028218;

        asm volatile("mov sl, %0"
                     : "+r"(level_base_r0)
                     :
                     : "sl");
        {
        s32 zero = 0;
        u16 *item_ptr = sp14;

        do {
            register u32 level_sum_r1 asm("r1");

            asm volatile(
                "ldrh r0, [%1]\n\t"
                "add r0, sl\n\t"
                "ldrb r1, [r0]\n\t"
                "add r0, sp, #28\n\t"
                "add r0, r0, %2\n\t"
                "ldrb r0, [r0]\n\t"
                "add r1, r1, r0"
                : "=r"(level_sum_r1)
                : "r"(item_ptr), "r"(var_r5_4)
                : "r0", "cc", "memory");
            if ((s32)level_sum_r1 > 0x63) {
                func_0809538C(1, 0x18D8, 0x1048, 0, zero, zero, 0x2F, 0x3F);
                func_08098BB4(0x0800551A);
                {
                    s32 *message_table_r1 = (s32 *)0x087EE170;
                    register u32 message_r0 asm("r0");

                    asm volatile(
                        "ldrh r0, [%2]\n\t"
                        "lsl r0, r0, #2\n\t"
                        "add r0, r0, %1\n\t"
                        "ldr r0, [r0]"
                        : "=r"(message_r0)
                        : "r"(message_table_r1), "r"(item_ptr)
                        : "cc", "memory");
                    func_080981F0(message_r0, 0, 9, 0, zero);
                }
                func_08098BB4(0x08005575);
                func_080972C8();
                func_0809534C();
                func_080ED17C(1);
                if (*(u8 *)0x0200A882 == 2) {
                    goto block_120;
                }
                if (*(u8 *)0x0200A880 != 0) {
                    goto block_120;
                }
            }
            item_ptr += 1;
            var_r5_4 += 1;
        } while (var_r5_4 < var_r6_3);
        }
    }
block_120:
    if (var_r5_4 >= var_r6_3) {
        goto block_122;
    }
    goto block_86;
block_122:
    func_08094554(sp34);
    func_080ACBA0(7);
    func_08098BB4(0x08005480);
    func_08098BB4(0x080055ED);
    var_r6 = 0x200;
    goto block_145;
block_124:
    {
        register u8 *selection_base_r0 asm("r0") = D_0203237A;
        register u32 selection_r1 asm("r1") = sp2C;

        asm volatile("" : "+r"(selection_base_r0));
        asm volatile("" : "+r"(selection_r1));
        asm volatile("add %0, %1, %0"
                     : "+r"(selection_base_r0)
                     : "r"(selection_r1));
        sp30 = (s32)func_080B80CC(*selection_base_r0, 0);
    }
    if (!(1 & *(u16 *)0x0300000E)) {
        goto block_127;
    }
    func_08098BB4(0x080055ED);
    func_08092E84(0x3E);
    var_r6 = 0x300;
    goto block_145;
block_127:
    {
        register u8 *state_record_r2 asm("r2") = var_r9;

        asm volatile("" : "+r"(state_record_r2));
        temp_r0_9 = state_record_r2[0];
    }
    var_r6 = 0x10;
    if (temp_r0_9 == 0) {
        goto block_129;
    }
    asm volatile("add %0, #240" : "+r"(var_r6));
block_129:
    func_08092E84(0x3F);
    goto block_145;
block_130:
    func_08098BB4(0x0800557A);
    {
        register s32 *message_table_r1 asm("r1") = (s32 *)0x087EDD54;
        register u8 *selection_base_r0 asm("r0") = D_0203237A;
        register u32 selection_r3 asm("r3") = sp2C;

        asm volatile("" : "+r"(message_table_r1));
        asm volatile("" : "+r"(selection_base_r0));
        asm volatile("" : "+r"(selection_r3));
        asm volatile("add %0, %1, %0"
                     : "+r"(selection_base_r0)
                     : "r"(selection_r3));
        func_080981F0(message_table_r1[*selection_base_r0], 0, 6, 0, 2);
    }
    func_08098248(0x08106ED0, 0, 6);
    func_08098BB4(0x080055E8);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_144;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_144;
    }
    var_r5_5 = 0;
    record_option_base = var_r9 + 1;
loop_133:
    option_record_address_r1 = record_option_base + var_r5_5;
    asm volatile("" : "+r"(option_record_address_r1));
    temp_r0_9 = *option_record_address_r1;
    if (temp_r0_9 == 0) {
        goto block_135;
    }
    func_080E5E38(temp_r0_9, 1);
block_135:
    var_r5_5 += 1;
    if (var_r5_5 <= 1U) {
        goto loop_133;
    }
    record_option_base = var_r9;
    asm volatile("" : "+r"(record_option_base));
    func_080E5E90(M2C_FIELD(record_option_base, u32 *, 4));
    if (M2C_FIELD(record_option_base, u8 *, 0) != 0) {
        goto block_138;
    }
    {
        register u8 *selection_base_r0 asm("r0") = D_0203237A;
        register u32 selection_r5 asm("r5") = sp2C;

        asm volatile("" : "+r"(selection_base_r0));
        asm volatile("" : "+r"(selection_r5));
        asm volatile("add %0, %1, %0"
                     : "+r"(selection_base_r0)
                     : "r"(selection_r5));
        func_080E5A18(*selection_base_r0, sp30);
    }
    goto block_143;
block_138:
    var_r5_6 = 0;
    {
        register u8 *selected_base_r0 asm("r0") = (u8 *)0x020321A4;
        register u32 selected_index_r1 asm("r1") = sp24;

        asm volatile("" : "+r"(selected_base_r0));
        asm volatile("" : "+r"(selected_index_r1));
        asm volatile("add %0, %2, %1"
                     : "=r"(selected_slot)
                     : "r"(selected_base_r0), "r"(selected_index_r1));
    }
    var_r4_3 = var_r8 + 0x52;
loop_139:
    if (*var_r4_3 == 0) {
        goto block_141;
    }
    func_080E5EFC(0, *selected_slot, var_r5_6);
block_141:
    var_r4_3 += 2;
    var_r5_6 += 1;
    if (var_r5_6 <= 3U) {
        goto loop_139;
    }
    {
        register u8 *selection_base_r0 asm("r0") = D_0203237A;
        register u32 selection_r2 asm("r2") = sp2C;
        register u32 selected_r1 asm("r1");

        asm volatile("" : "+r"(selection_base_r0));
        asm volatile("" : "+r"(selection_r2));
        asm volatile("add %0, %1, %0"
                     : "+r"(selection_base_r0)
                     : "r"(selection_r2));
        selected_r1 = *selection_base_r0;
        func_080E5B44(var_r8, selected_r1, sp30);
    }
block_143:
    func_08098BB4(0x0800564A);
    func_08098BB4(0x080055ED);
block_144:
    var_r6 = 0x20;
block_145:
    {
        register s32 tail_guard_r3 asm("r3") = 0;

        asm volatile("" : "+r"(tail_guard_r3));
        if (tail_guard_r3 != 0) {
            goto block_147;
        }
    }
    goto loop_1;
block_147:
    return;
}
