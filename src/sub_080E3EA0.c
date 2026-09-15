#include "m2c_prelude.h"

s32 *func_08094484();                               /* extern */
M2C_UNK func_08094554(s32 *);                       /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
void *func_0809716C(s32);                           /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_080E2F70(s32);                         /* extern */
M2C_UNK func_080E364C(s32);                         /* extern */
M2C_UNK func_080E39C8();                            /* extern */
M2C_UNK func_080E3CE0();                            /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080E3EA0(void) {
    volatile s32 outgoing0;
    volatile s32 outgoing1;
    volatile s32 outgoing2;
    volatile s32 outgoing3;
    volatile s32 outgoing4;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    M2C_UNK var_r0_2;
    register s32 *var_r8 asm("r8");
    s32 temp_r1;
    s32 var_r0;
    s32 *failure_store;
    s32 var_r5;
    register u32 scan2_index asm("r4");
    u8 *scan2_table;
    u32 scan2_column;
    u32 scan2_row;
    u32 scan2_count;
    s32 temp_r0;
    u8 temp_r0_2;
    register u32 temp_r2 asm("r2");
    u8 temp_r3;
    u8 temp_r3_2;
    u8 var_r4;
    u8 var_sl;
    void *temp_r0_3;
    void *temp_r0_5;

    asm volatile("" : "=m"(outgoing0), "=m"(outgoing1), "=m"(outgoing2),
                 "=m"(outgoing3), "=m"(outgoing4), "=m"(sp14),
                 "=m"(sp18), "=m"(sp1C), "=m"(sp20));
    func_080ECD34(0x081046A8, 0x06015840);
    var_r5 = 0;
    *(u8 *)0x02032E70 = 0;
    if (*(s32 *)0x02021690 == 0xF) {
        goto loop_2;
    }
    goto loop_125;
loop_2:
    if (var_r5 != 0x1110) {
        goto block_4;
    }
    goto block_77;
block_4:
    if (var_r5 > 0x1110) {
        goto block_20;
    }
    if (var_r5 != 0x1000) {
        goto block_7;
    }
    goto block_53;
block_7:
    if (var_r5 > 0x1000) {
        goto block_11;
    }
    if (var_r5 == 0) {
        goto block_38;
    }
    if (var_r5 == 0x10) {
        goto block_39;
    }
    goto block_121;
block_11:
    if (var_r5 != 0x1020) {
        goto block_13;
    }
    goto block_55;
block_13:
    if (var_r5 > 0x1020) {
        goto block_17;
    }
    if (var_r5 != 0x1010) {
        goto block_16;
    }
    goto block_54;
block_16:
    goto block_121;
block_17:
    if (var_r5 != 0x1100) {
        goto block_19;
    }
    goto block_67;
block_19:
    goto block_121;
block_20:
    if (var_r5 != 0x2010) {
        goto block_22;
    }
    goto block_96;
block_22:
    if (var_r5 > 0x2010) {
        goto block_29;
    }
    if (var_r5 != 0x1200) {
        goto block_25;
    }
    goto block_87;
block_25:
    if (var_r5 != 0x2000) {
        goto block_27;
    }
    goto block_94;
block_27:
    goto block_121;
block_29:
    if (var_r5 != 0x2200) {
        goto block_31;
    }
    goto block_110;
block_31:
    if (var_r5 > 0x2200) {
        goto block_35;
    }
    if (var_r5 != 0x2100) {
        goto block_34;
    }
    goto block_101;
block_34:
    goto block_121;
block_35:
    if (var_r5 != 0x3000) {
        goto block_37;
    }
    goto block_117;
block_37:
    goto block_121;
block_38:
    func_080E3CE0();
    var_r5 = 0x10;
    goto block_121;
block_39:
    {
    register s32 outgoing_r0 asm("r0");
    asm volatile(
        "mov %0, #152\n\t"
        "str %0, [sp, #0]"
        : "=r"(outgoing_r0) : : "memory");
    outgoing_r0 = 0x343;
    asm volatile(
        "str %0, [sp, #4]\n\t"
        "mov %0, #15\n\t"
        "str %0, [sp, #8]\n\t"
        "mov %0, #8\n\t"
        "str %0, [sp, #12]\n\t"
        "mov %0, #0\n\t"
        "str %0, [sp, #16]"
        : "+r"(outgoing_r0) : : "r1", "r2", "memory");
    }
    var_r8 = func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8);
    func_08098BB4(0x080061FC);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_50;
    }
    {
        register u8 *destination asm("r1") = (u8 *)0x02032E70;
        register u8 *source asm("r2") = (u8 *)0x0200A880;
        register u32 selected asm("r0");

        asm volatile("" : "+r"(destination), "+r"(source));
        selected = *source;
        *destination = selected;
    }
    func_08094554(var_r8);
    {
        register s32 zero_guard_r0 asm("r0");
        register s32 zero_guard_r1 asm("r1");
        register s32 zero_guard_r2 asm("r2");

        asm volatile("" : "=&r"(zero_guard_r0), "=&r"(zero_guard_r1),
                          "=&r"(zero_guard_r2));
        var_sl = 0;
        asm volatile("" : : "r"(zero_guard_r0), "r"(zero_guard_r1),
                            "r"(zero_guard_r2));
    }
    {
        register u8 *source asm("r6") = (u8 *)0x0200A880;

        asm volatile("" : "+r"(source));
        temp_r0 = *source;
    }
    if (temp_r0 != 1) {
        goto block_42;
    }
    goto block_116;
block_42:
    if ((s32) temp_r0 > 1) {
        goto block_47;
    }
    if (temp_r0 != 0) {
        goto block_45;
    }
    goto block_93;
block_45:
    goto block_121;
block_47:
    if (temp_r0 == 2) {
        goto block_49;
    }
    goto block_121;
block_49:
    var_r5 = 0x3000;
    goto block_121;
block_50:
    func_08096308(0x10, 0);
    if (*(u8 *)0x02032E5C != 0) {
        goto block_52;
    }
    *(s32 *)0x02021690 = 2;
    goto block_121;
block_52:
    *(s32 *)0x02021690 = 4;
    goto block_121;
block_53:
    func_08098BB4(0x08006206);
    M2C_FIELD(func_0809716C(2), u8 *, 0x16) = var_sl;
    var_r5 = 0x1010;
    goto block_121;
block_54:
    asm volatile(
        "mov r0, #128\n\t"
        "str r0, [sp, #0]\n\t"
        "mov r0, #212\n\t"
        "lsl r0, r0, #2\n\t"
        "str r0, [sp, #4]\n\t"
        "mov r0, #15\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r0, #8\n\t"
        "str r0, [sp, #12]\n\t"
        "mov r0, #0\n\t"
        "str r0, [sp, #16]"
        : : : "r0", "r1", "r2", "memory");
    var_r8 = func_08094484(0x08105AFC, 0x08105B08, 0, 0x70);
    var_r5 = 0x1020;
    goto block_121;
block_55:
    func_08098BB4(0x0800625E);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_66;
    }
    temp_r2 = 0x0200A880;
    temp_r2 = *(u8 *)temp_r2;
    var_sl = temp_r2;
    {
        register s32 zero_r3 asm("r3") = 0;
        register s32 zero_r6 asm("r6");

        asm volatile("" : "+r"(zero_r3));
        sp18 = zero_r3;
        zero_r6 = 0;
        sp14 = zero_r6;
    }
    asm volatile("" : "+m"(sp14), "+m"(sp18));
    if ((u32) temp_r2 > 2U) {
        goto block_58;
    }
    func_08094554(var_r8);
    var_r5 = 0x1100;
    goto block_121;
block_58: {
    register u8 *table_seed asm("r2");
    register u8 *table asm("r9");
    register u32 row_seed asm("r1") = var_sl;
    register u32 row asm("r6");
    register u32 count asm("r0");
    register u32 count_hold asm("r7");
    register u32 item asm("ip");

    var_r4 = 1;
    table_seed = (u8 *)0x087A3A64;
    row_seed *= 0xB0;
    count = *(u8 *)(row_seed + (u32)table_seed);
    if ((u32)var_r4 > count) {
        goto block_64;
    }
    table = table_seed;
    item = 0;
    row = row_seed;
    count_hold = count;
loop_60:
    {
        register u32 item_copy asm("r3") = item;
        register u32 address asm("r0");
        register u32 value asm("r3");
        register u32 word_address asm("r2");
        register u32 work0 asm("r0");
        register u32 bit asm("r1");

        asm volatile("" : "+r"(item_copy));
        address = var_r4 + item_copy;
        address += row;
        address += (u32)table;
        value = *(u8 *)address;
        word_address = value >> 5;
        word_address <<= 2;
        work0 = 0x020217B4;
        word_address += work0;
        work0 = 0x1F;
        value &= work0;
        bit = 1;
        bit <<= value;
        work0 = *(u32 *)word_address;
        work0 &= bit;
        if (work0 != 0) {
            goto block_62;
        }
    }
    var_r4 = (u8)(var_r4 + 1);
    if ((u32)var_r4 <= count_hold) {
        goto loop_60;
    }
block_62:
    {
        register u32 item_copy asm("r1") = item;
        register u32 address asm("r0");

        asm volatile("" : "+r"(item_copy));
        address = item_copy + row;
        address += (u32)table;
        count = *(u8 *)address;
    }
    if ((u32)var_r4 > count) {
        goto block_64;
    }
    goto block_83;
    }
block_64:
    {
        register s32 *failure_load asm("r2") = var_r8;
        register s32 flags asm("r0") = *failure_load;
        register s32 mask asm("r1") = 0x20000;

        flags |= mask;
        var_r0 = flags;
        failure_store = failure_load;
    }
    asm volatile("");
    goto block_85;
block_66:
    var_r0_2 = 0x08006262;
    goto block_100;
block_67:
    {
        register s32 selection_dispatch asm("r6");

        asm volatile("" : "=r"(selection_dispatch) : "0"((s32)var_sl));
        if (selection_dispatch == 1) {
            goto block_74;
        }
        if (selection_dispatch > 1) {
            goto block_71;
        }
        if (selection_dispatch == 0) {
            goto block_73;
        }
    }
    goto block_76;
block_71:
    {
        register s32 selection_two asm("r0");

        asm volatile("" : "=r"(selection_two) : "0"((s32)var_sl));
        if (selection_two == 2) {
            goto block_75;
        }
    }
    goto block_76;
block_73:
    func_08098BB4(0x08006265);
    {
        register s32 width asm("r1") = 0xB0;

        asm volatile("str %1, %0" : "=m"(sp1C) : "r"(width));
    }
    {
        register s32 height asm("r2") = 0x90;

        asm volatile("str %1, %0" : "=m"(sp20) : "r"(height));
    }
    asm volatile("" : "+m"(sp1C), "+m"(sp20));
    goto block_76;
block_74:
    func_08098BB4(0x08006413);
    {
        register s32 width asm("r3") = 0xB0;

        asm volatile("str %1, %0" : "=m"(sp1C) : "r"(width));
    }
    {
        register s32 height asm("r6") = 0x90;

        asm volatile("str %1, %0" : "=m"(sp20) : "r"(height));
    }
    asm volatile("" : "+m"(sp1C), "+m"(sp20));
    goto block_76;
block_75:
    func_08098BB4(0x080065CF);
    sp1C = 0xA8;
    {
        register s32 height asm("r1") = 0x50;

        asm volatile("str %1, %0" : "=m"(sp20) : "r"(height));
    }
block_76: {
    register s32 arg_r3 asm("r3");
    register s32 stack_r0 asm("r0");
    register s32 gfx_r0 asm("r0");
    register s32 gfx_r1 asm("r1");

    {
        register s32 raw_r2 asm("r2") = sp1C;

        arg_r3 = (s16)raw_r2;
        asm volatile("" : : "r"(raw_r2));
    }
    {
        register s32 raw_r6 asm("r6") = sp20;

        stack_r0 = (s16)raw_r6;
    }
    asm volatile("str r0, [sp, #0]" : "+r"(stack_r0) : "r"(arg_r3) : "memory");
    stack_r0 = 0x350;
    asm volatile("str r0, [sp, #4]" : "+r"(stack_r0) : : "memory");
    stack_r0 = 0xF;
    asm volatile("str r0, [sp, #8]" : "+r"(stack_r0) : : "memory");
    stack_r0 = 8;
    asm volatile("str r0, [sp, #12]" : "+r"(stack_r0) : : "memory");
    stack_r0 = 0;
    asm volatile("str r0, [sp, #16]" : "+r"(stack_r0) : : "memory");
    gfx_r0 = 0x08105AFC;
    gfx_r1 = 0x08105B08;
    asm volatile("" : "+r"(gfx_r0), "+r"(gfx_r1));
    var_r8 = func_08094484(gfx_r0, gfx_r1, 0, arg_r3);
    }
    temp_r0_3 = func_0809716C(3);
    {
        register u8 *stack_r1 asm("r1");
        asm volatile("mov %0, sp" : "=r"(stack_r1) : "m"(sp14));
        M2C_FIELD(temp_r0_3, u8 *, 0x14) = stack_r1[20];
    }
    {
        register u32 stack_r2 asm("r2");
        asm volatile("mov %0, sp" : "=r"(stack_r2) : "m"(sp18));
        stack_r2 = *(u8 *)(stack_r2 + 24);
        M2C_FIELD(temp_r0_3, u8 *, 0x16) = stack_r2;
    }
    var_r5 = 0x1110;
    goto block_121;
block_77:
    func_08098BB4(0x0800661B);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_86;
    }
    sp14 = (s32) *(u8 *)0x0200A881;
    {
        register s32 selected asm("r3") = 0x0200A880;

        selected = *(u8 *)selected;
        sp18 = selected;
    }
    {
        register u8 *table_seed asm("r3");
        register u32 work_r0 asm("r0");
        register u32 column_load asm("r6");
        register u32 column_setup asm("r2");
        register u32 row_setup asm("r1");

        scan2_index = 1;
        table_seed = (u8 *)0x087A3A64;
        asm volatile("" : "+r"(table_seed));
        work_r0 = 0xB;
        asm volatile("ldr %0, [sp, #24]"
                     : "=r"(column_load) : "m"(sp18));
        column_setup = column_load;
        column_setup *= work_r0;
        work_r0 = 0xB0;
        row_setup = var_sl;
        row_setup *= work_r0;
        work_r0 = column_setup + row_setup;
        work_r0 += (u32)table_seed;
        work_r0 = *(u8 *)work_r0;
        if (scan2_index > work_r0) {
            goto block_84;
        }
        scan2_table = table_seed;
        scan2_column = column_setup;
        scan2_row = row_setup;
        scan2_count = work_r0;
    }
loop_80:
    {
        register u32 address asm("r0") = scan2_index + scan2_column;
        register u32 value asm("r3");
        register u32 word_address asm("r2");
        register u32 work0 asm("r0");
        register u32 bit asm("r1");

        address += scan2_row;
        address += (u32)scan2_table;
        value = *(u8 *)address;
        word_address = value >> 5;
        word_address <<= 2;
        work0 = 0x020217B4;
        asm volatile("add %0, %0, %1"
            : "+l"(word_address)
            : "l"(work0)
            : "cc");
        work0 = 0x1F;
        value &= work0;
        bit = 1;
        bit <<= value;
        work0 = *(u32 *)word_address;
        work0 &= bit;
        if (work0 != 0) {
            goto block_82;
        }
    }
    {
        register u32 index_next asm("r0") = scan2_index + 1;

        scan2_index = (u8)index_next;
    }
    if (scan2_index <= scan2_count) {
        goto loop_80;
    }
block_82:
    {
        register u32 address asm("r0") = scan2_column + scan2_row;

        address += (u32)scan2_table;
        if (scan2_index > *(u8 *)address) {
            goto block_84;
        }
    }
block_83:
    var_r5 = 0x1200;
    goto block_121;
block_84:
    {
        register s32 *failure_load asm("r1") = var_r8;
        register s32 flags asm("r0") = *failure_load;
        register s32 mask asm("r1") = 0x20000;

        flags |= mask;
        var_r0 = flags;
        failure_store = var_r8;
    }
block_85:
    *failure_store = var_r0;
    func_08098BB4(0x08006622);
    {
        register s32 *clear_pointer asm("r3") = var_r8;
        register s32 flags asm("r0") = *clear_pointer;
        register s32 mask asm("r1") = 0xFFFDFFFF;

        flags &= mask;
        *clear_pointer = flags;
    }
    goto block_121;
block_86:
    func_08098BB4(0x0800661F);
    func_08094554(var_r8);
    var_r5 = 0x1010;
    goto block_121;
block_87:
    func_08096308(0x10, 0);
    goto loop_89;
block_88:
    func_080ED17C(1);
loop_89:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_88;
    }
    {
        register s32 address asm("r0");
        register s32 row asm("r6");
        register s32 column asm("r1");
        register s32 item asm("r2");

        address = 0xB0;
        asm volatile("" : "+r"(address));
        asm volatile(
            "mov %0, %2\n\t"
            "mul %0, %1\n\t"
            "add %1, %0, #0"
            : "=&l"(row), "+l"(address)
            : "r"((s32)var_sl)
            : "cc");
        column = 0xB;
        asm volatile("" : "+r"(column));
        item = sp18;
        column *= item;
        {
            register s32 table asm("r2") = 0x087A3A64;

            asm volatile("" : "+r"(table));
            column += table;
        }
        address += column;
        func_080E2F70(address);
    }
    func_080E3CE0();
    {
        register u32 selection_limit asm("r3");

        asm volatile("" : "=r"(selection_limit) : "0"((u32)var_sl));
        if (selection_limit > 2U) {
            goto block_93;
        }
    }
    func_08098BB4(0x08006206);
    {
        void *child = func_0809716C(2);
        register s32 selected_store asm("r6") = var_sl;

        M2C_FIELD(child, u8 *, 0x16) = selected_store;
    }
    var_r5 = 0x1100;
    goto block_121;
block_93:
    var_r5 = 0x1000;
    goto block_121;
block_94:
    func_08098BB4(0x080066D6);
    {
        void *child = func_0809716C(2);
        register s32 selected_store asm("r1") = var_sl;

        M2C_FIELD(child, u8 *, 0x16) = selected_store;
    }
    var_r5 = 0x2010;
    goto block_121;
block_96:
    asm volatile(
        "mov r0, #144\n\t"
        "str r0, [sp, #0]\n\t"
        "mov r0, #212\n\t"
        "lsl r0, r0, #2\n\t"
        "str r0, [sp, #4]\n\t"
        "mov r0, #15\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r0, #8\n\t"
        "str r0, [sp, #12]\n\t"
        "mov r0, #0\n\t"
        "str r0, [sp, #16]"
        : : : "r0", "r1", "r2", "memory");
    var_r8 = func_08094484(0x08105AFC, 0x08105B08, 0, 0xB8);
    func_08098BB4(0x0800679F);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_99;
    }
    {
        register u32 selected asm("r2") = 0x0200A880;

        selected = *(u8 *)selected;
        var_sl = selected;
    }
    {
        register s32 zero_r3 asm("r3") = 0;
        register s32 zero_r6 asm("r6");

        asm volatile("" : "+r"(zero_r3));
        sp18 = zero_r3;
        zero_r6 = 0;
        sp14 = zero_r6;
    }
    asm volatile("" : "+m"(sp14), "+m"(sp18));
    if ((u32) (u8) (var_sl - 1) > 1U) {
        goto block_108;
    }
    func_08094554(var_r8);
    var_r5 = 0x2100;
    goto block_121;
block_99:
    var_r0_2 = 0x080067A3;
block_100:
    func_08098BB4(var_r0_2);
    func_08094554(var_r8);
    var_r5 = 0x10;
    goto block_121;
block_101:
    {
        register s32 selection_case asm("r0");

        asm volatile("" : "=r"(selection_case) : "0"((s32)var_sl));
        if (selection_case == 1) {
            goto block_104;
        }
        if (selection_case == 2) {
            goto block_105;
        }
    }
    goto block_106;
block_104:
    func_08098BB4(0x080067A6);
    {
        register s32 width asm("r1") = 0xB0;

        asm volatile("str %1, %0" : "=m"(sp1C) : "r"(width));
    }
    {
        register s32 height asm("r2") = 0x60;

        asm volatile("str %1, %0" : "=m"(sp20) : "r"(height));
    }
    asm volatile("" : "+m"(sp1C), "+m"(sp20));
    goto block_106;
block_105:
    func_08098BB4(0x080067F5);
    {
        register s32 width asm("r3") = 0xB8;

        asm volatile("str %1, %0" : "=m"(sp1C) : "r"(width));
    }
    {
        register s32 height asm("r6") = 0x60;

        asm volatile("str %1, %0" : "=m"(sp20) : "r"(height));
    }
block_106: {
    register s32 arg_r3 asm("r3");
    register s32 stack_r0 asm("r0");

    {
        register s32 raw_width asm("r0") = sp1C;

        asm volatile(
            "lsl %0, %1, #16\n\t"
            "asr %0, %0, #16"
            : "=&r"(arg_r3)
            : "r"(raw_width));
    }
    {
        register s32 raw_height asm("r1") = sp20;

        stack_r0 = (s16)raw_height;
    }

    asm volatile("str r0, [sp, #0]" : "+r"(stack_r0) : "r"(arg_r3) : "memory");
    stack_r0 = 0x350;
    asm volatile("str r0, [sp, #4]" : "+r"(stack_r0) : : "memory");
    stack_r0 = 0xF;
    asm volatile("str r0, [sp, #8]" : "+r"(stack_r0) : : "memory");
    stack_r0 = 8;
    asm volatile("str r0, [sp, #12]" : "+r"(stack_r0) : : "memory");
    stack_r0 = 0;
    asm volatile("str r0, [sp, #16]" : "+r"(stack_r0) : : "memory");
    var_r8 = func_08094484(0x08105AFC, 0x08105B08, 0, arg_r3);
    }
    temp_r0_5 = func_0809716C(3);
    {
        register u32 stack_r2 asm("r2");
        asm volatile("mov %0, sp" : "=r"(stack_r2) : "m"(sp14));
        stack_r2 = *(u8 *)(stack_r2 + 20);
        M2C_FIELD(temp_r0_5, u8 *, 0x14) = stack_r2;
    }
    {
        register u32 stack_r3 asm("r3");
        asm volatile("mov %0, sp" : "=r"(stack_r3) : "m"(sp18));
        stack_r3 = *(u8 *)(stack_r3 + 24);
        M2C_FIELD(temp_r0_5, u8 *, 0x16) = stack_r3;
    }
    func_08098BB4(0x0800683E);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_109;
    }
    sp14 = (s32) *(u8 *)0x0200A881;
    {
        register u32 selected asm("r6") = 0x0200A880;

        selected = *(u8 *)selected;
        sp18 = selected;
    }
block_108:
    var_r5 = 0x2200;
    goto block_121;
block_109:
    func_08098BB4(0x08006842);
    func_08094554(var_r8);
    var_r5 = 0x2010;
    goto block_121;
block_110: {
    register s32 selection_minus asm("r6");
    register s32 selection_copy asm("r0");
    register s32 selection8 asm("r4");
    register s32 item_load asm("r1");
    register s32 item2 asm("r5");

    func_08096308(0x10, 0);
    selection_minus = var_sl;
    selection_minus -= 1;
    selection_copy = var_sl;
    asm volatile("" : "+r"(selection_copy));
    selection8 = selection_copy << 3;
    item_load = sp18;
    item2 = item_load << 1;
    goto loop_112;
block_111:
    func_080ED17C(1);
loop_112:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_111;
    }
    {
        register s32 selection_copy2 asm("r2");
        register s32 row asm("r0");
        register s32 item_load2 asm("r3");
        register s32 column asm("r1");
        register s32 table asm("r2");

        selection_copy2 = var_sl;
        asm volatile("" : "+r"(selection_copy2));
        row = selection8 + selection_copy2;
        row <<= 2;
        item_load2 = sp18;
        column = item2 + item_load2;
        column <<= 2;
        table = 0x087A3D24;
        column += table;
        row += column;
        func_080E364C(row);
    }
    func_080E3CE0();
    {
        register u32 selection_test asm("r0");

        selection_test = (u32)selection_minus << 24;
        selection_test >>= 24;
        if (selection_test > 1U) {
            goto block_116;
        }
    }
    func_08098BB4(0x080066D6);
    {
        void *child = func_0809716C(2);
        register s32 selected_store asm("r6") = var_sl;

        M2C_FIELD(child, u8 *, 0x16) = selected_store;
    }
    var_r5 = 0x2100;
    goto block_121;
    }
block_116:
    var_r5 = 0x2000;
    goto block_121;
block_117:
    func_08096308(0x10, 0);
    goto loop_119;
block_118:
    func_080ED17C(1);
loop_119:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_118;
    }
    func_08098BB4(0x08006200);
    func_080E39C8();
    var_r5 = 0;
block_121:
    if (*(s32 *)0x02021690 != 0xF) {
        goto block_123;
    }
    goto loop_2;
block_123:
    goto loop_125;
block_124:
    func_080ED17C(1);
loop_125:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_124;
    }
    return;
}
