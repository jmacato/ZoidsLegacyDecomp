#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);
M2C_UNK func_08094330(void);
s32 *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32);
asm(".set func_08094484_4, func_08094484");
extern s32 *func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_08094554(s32 *);
M2C_UNK func_08096308(s32, s32);
s32 func_0809669C(void);
M2C_UNK func_08096F3C(void);
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
M2C_UNK func_080972C8(void);
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);
M2C_UNK func_0809844C(u32, s32, s32, s32, s32, s32, s32);
asm(".set func_0809844C_4, func_0809844C");
extern M2C_UNK func_0809844C_4(u32, s32, s32, s32);
asm(
    ".macro B7390_PRICE_ADD_AND_FIX_AMOUNT dst, lhs, rhs\n"
    "add \\dst, \\lhs, \\rhs\n"
    ".set b7390_amount_ldr_count, 0\n"
    ".macro ldr args:vararg\n"
    ".if b7390_amount_ldr_count == 0\n"
    ".short 0x4A0B\n"
    ".elseif b7390_amount_ldr_count == 1\n"
    ".short 0x6810\n"
    ".elseif b7390_amount_ldr_count == 2\n"
    ".short 0x6809\n"
    ".else\n"
    ".short 0x4909\n"
    ".purgem ldr\n"
    ".endif\n"
    ".set b7390_amount_ldr_count, b7390_amount_ldr_count + 1\n"
    ".endm\n"
    ".macro add args:vararg\n"
    ".short 0x1870\n"
    ".purgem add\n"
    ".endm\n"
    ".endm\n");
asm(
    ".macro B7390_INIT_LIST_AND_FIX_SLOT dst\n"
    "mov \\dst, #0\n"
    ".set b7390_list_ldr_count, 0\n"
    ".macro ldr args:vararg\n"
    ".if b7390_list_ldr_count == 0\n"
    ".short 0x480D\n"
    ".elseif b7390_list_ldr_count == 1\n"
    ".short 0x4D0C\n"
    ".else\n"
    ".short 0x480C\n"
    ".purgem ldr\n"
    ".endif\n"
    ".set b7390_list_ldr_count, b7390_list_ldr_count + 1\n"
    ".endm\n"
    ".macro add args:vararg\n"
    ".short 0x1820\n"
    ".purgem add\n"
    ".endm\n"
    ".endm\n");
M2C_UNK func_080986B4(s32);
M2C_UNK func_08098834(s32);
M2C_UNK func_080988C8(s32, s32);
M2C_UNK func_08098BB4(s32);
M2C_UNK func_0809AB44(s32, s32, s32, s32, s32);
M2C_UNK func_080ACDA8(s32, s32, s32);
M2C_UNK func_080B65A4(void);
u32 func_080B684C(u32, s32);
M2C_UNK func_080B7210(u8);
M2C_UNK func_080E5CE4(u8, u8);
M2C_UNK func_080E5D38(u8, u8);
M2C_UNK func_080E5E64(s32);
M2C_UNK func_080E5E90(s32);
M2C_UNK func_080ECD34(s32, s32);
s32 func_080ECF00(u32, s32);
M2C_UNK func_080ED17C(s32);

struct FrameB7390 {
    s32 amount;
    u32 index;
    s32 *dialog;
    s32 *modal;
};

#define sp18 frame.amount
#define sp1C frame.index
#define sp20 frame.dialog
#define sp24 frame.modal

void sub_080B7390(void)
{
    struct FrameB7390 frame;
    s32 var_r0;
    s32 var_r0_3;
    s32 temp_r4;
    s32 temp_r4_2;
    register s32 var_r0_2 asm("r0");
    register s32 *modal_store asm("r2");
    s32 var_r5;
    register s32 *temp_r8 asm("r8");
    register s32 *temp_r8_2 asm("r8");
    register u32 temp_r1 asm("r1");
    register u32 temp_r1_3 asm("r1");
    u32 temp_r1_2;
    u8 temp_r0;
    u8 temp_r0_2;
    register u32 temp_r0_3 asm("r0");
    u8 var_r4;
    u32 var_r4_2;
    u32 var_r4_4;
    u8 var_r6;
    register u32 var_sl asm("sl");
    u32 var_r4_3;

    *(u16 *)0x0300004C = 0x1140;
    func_08096FBC(0, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_080ECD34(0x081046A8, 0x06015840);
    func_0809AB44(2, 3, 0, 0, 1);
    func_08098BB4(0x08004626);
    if (*(s32 *)0x02021690 != 6) {
        goto block_3;
    }
    func_080981F0(0x0810657C, 0, 0, 0, 0);
    goto block_4;
block_3:
    func_080981F0(0x08106598, 0, 0, 1, 0);
block_4:
    {
        register s32 money_base asm("r8") = 0x020218E4;
        register s32 money_offset asm("r7") = 0x6A04;
        asm volatile("" : "+r"(money_base), "+r"(money_offset));
        money_offset += money_base;
        {
            register u32 current_money asm("r0") = *(volatile u32 *)money_offset;
            func_0809844C(current_money, 7, 0, 2, 1, 1, 0);
        }
    }
    func_08094330();
    sp24 = func_08094484(0x08105724, 0x08105758, 0, 0xA0, 0x6C, 0x2EA, 0xF, 0x20, 0);
    func_08096308(0xF, 0);
    var_r5 = 0;
    if ((u32)(*(s32 *)0x02021690 - 6) > 1U) {
        goto loop_146;
    }
loop_5:
    {
    register s32 state_1130 asm("r1") = 0x1130;
    if (var_r5 != state_1130) {
        goto block_7;
    }
    goto block_98;
block_7:
    if (var_r5 > state_1130) {
        goto block_28;
    }
    }
    if (var_r5 != 0x1100) {
        goto block_10;
    }
    goto block_77;
block_10:
    if (var_r5 > 0x1100) {
        goto block_19;
    }
    if (var_r5 != 0x1000) {
        goto block_13;
    }
    goto block_60;
block_13:
    if (var_r5 > 0x1000) {
        goto block_16;
    }
    if (var_r5 == 0) {
        goto block_50;
    }
    goto block_143;
block_16:
    if (var_r5 != 0x1010) {
        goto block_18;
    }
    goto block_65;
block_18:
    goto block_143;
block_19:
    if (var_r5 != 0x1110) {
        goto block_21;
    }
    goto block_85;
block_21:
    if (var_r5 > 0x1110) {
        goto block_25;
    }
    if (var_r5 != 0x1105) {
        goto block_24;
    }
    goto block_84;
block_24:
    goto block_143;
block_25:
    if (var_r5 != 0x1120) {
        goto block_27;
    }
    goto block_93;
block_27:
    goto block_143;
block_28:
    if (var_r5 != 0x2100) {
        goto block_30;
    }
    goto block_118;
block_30:
    if (var_r5 > 0x2100) {
        goto block_41;
    }
    {
    register s32 state_2010 asm("r4") = 0x2010;
    if (var_r5 != state_2010) {
        goto block_33;
    }
    goto block_102;
block_33:
    if (var_r5 > state_2010) {
        goto block_38;
    }
    if (var_r5 != 0x2000) {
        goto block_36;
    }
    goto block_101;
    }
block_36:
    goto block_143;
block_38:
    if (var_r5 != 0x2020) {
        goto block_40;
    }
    goto block_106;
block_40:
    goto block_143;
block_41:
    if (var_r5 != 0x2120) {
        goto block_43;
    }
    goto block_131;
block_43:
    if (var_r5 > 0x2120) {
        goto block_47;
    }
    if (var_r5 != 0x2110) {
        goto block_46;
    }
    goto block_119;
block_46:
    goto block_143;
block_47:
    if (var_r5 != 0x2130) {
        goto block_49;
    }
    goto block_136;
block_49:
    goto block_143;
block_50:
    func_08098BB4(0x08004786);
    func_08098BB4(0x0800465D);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_58;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_54;
    }
    var_r5 = 0x1000;
    goto block_143;
block_54:
    func_080B65A4();
    if (*(u8 *)0x02032379 != 0) {
        goto block_57;
    }
    func_08098BB4(0x08004896);
    goto block_143;
block_57:
    var_r5 = 0x2000;
    asm volatile(
        ".macro b target\n\t"
        ".purgem b\n\t"
        ".purgem bl\n\t"
        "b \\target\n\t"
        ".endm\n\t"
        ".macro bl target\n\t"
        ".purgem b\n\t"
        ".purgem bl\n\t"
        "b \\target\n\t"
        ".endm");
    goto block_143;
block_58:
    *(s32 *)0x02021690 = 3;
    func_08096308(0x10, 0);
    asm volatile(
        ".macro b target\n\t"
        ".purgem b\n\t"
        "b \\target\n\t"
        ".short 0x0000\n\t"
        ".endm");
    goto block_143;
block_60:
    func_08098BB4(0x08004661);
    var_r4 = 0;
    {
    register u8 *order_base asm("r1") = (u8 *)0x087A21B0;
    register u8 *page_ptr asm("r2") = (u8 *)0x02032B98;
    if (*(u16 *)(order_base + (*page_ptr * 0x10)) == 0) {
        goto block_64;
    }
    {
    register s32 *message_table asm("r7") = (s32 *)0x087EE170;
    register u8 *loop_order_base asm("r6") = order_base;
    register u8 *loop_page_ptr asm("r5") = page_ptr;
loop_62:
    {
        register u32 entry_offset asm("r1") = var_r4;
        register u32 page_offset asm("r0") = *loop_page_ptr;
        entry_offset <<= 1;
        page_offset *= 0x10;
        entry_offset += page_offset;
        entry_offset += (u32)loop_order_base;
        func_080988C8(4, message_table[*(u16 *)entry_offset]);
    }
    var_r4 += 1;
    if ((u32)var_r4 > 7U) {
        goto block_64;
    }
    {
        register u32 check_offset asm("r0") = var_r4 * 2;
        register u32 check_page asm("r1") = *loop_page_ptr;
        check_page *= 0x10;
        check_offset += check_page;
        check_offset += (u32)loop_order_base;
        if (*(u16 *)check_offset != 0) {
            goto loop_62;
        }
    }
    }
    }
block_64:
    {
        register u8 *order_base asm("r1") = (u8 *)0x087A21B0;
        asm volatile("" : "+r"(order_base));
        var_r6 = order_base[*(u8 *)0x02032B98 * 0x10];
    }
    var_r5 = 0x1010;
    goto block_143;
block_65:
    func_08098BB4(0x080047A0);
    asm volatile(
        "mov r0, #152\n\t"
        "str r0, [sp, #0]"
        : : : "r0", "r1", "memory");
    {
        register s32 kind asm("r0") = 0x38F;
        register s32 zero asm("r2");
        asm volatile(
            "str %0, [sp, #4]\n\t"
            "mov %0, #15\n\t"
            "str %0, [sp, #8]\n\t"
            "mov %0, #8\n\t"
            "str %0, [sp, #12]\n\t"
            "mov %1, #0\n\t"
            "str %1, [sp, #16]"
            : "+r"(kind), "=r"(zero) : : "r1", "memory");
        temp_r8 = func_08094484_4(
            ({ register s32 arg asm("r0") = 0x08105DA4;
               arg; }),
            ({ register s32 arg asm("r1") = 0x08105DB0;
               arg; }),
            zero, 0xA0);
    }
    {
    s32 six = 6;
    register s32 eight asm("r9");
    register s32 eight_seed asm("r0") = 8;
    asm volatile("" : "+r"(eight_seed));
    eight = eight_seed;
loop_66:
    func_080986B4(5);
    func_080ACDA8((var_r6 * 0x18) + 0x087B2524, 5, 3);
    temp_r4 = var_r6 * 4;
    func_0809844C(
        ({
            register u32 price_base asm("r1") = 0x087A2390;
            register u32 price_value asm("r0");
            asm volatile(
                "add %0, %2, %1\n\t"
                "ldr %0, [%0]"
                : "=&r"(price_value), "+r"(price_base)
                : "r"(temp_r4) : "memory");
            price_value;
        }),
        6, 0, 2, 5, six, eight);
    func_0809844C((u32)M2C_FIELD(var_r6, u8 *, 0x02028218), 2, 0, 2, six, 0xA,
        ({ register s32 stack_zero asm("r2") = 0; stack_zero; }));
    func_08098BB4(0x080046AA);
    if (*(u8 *)0x0200A882 != 0) {
        goto block_69;
    }
    {
        register u16 *keys_ptr asm("r0") = (u16 *)0x0200A884;
        register u32 keys asm("r1");
        register u32 mask asm("r0");
        keys = *keys_ptr;
        mask = eight;
        if (mask & keys) {
            goto block_69;
        }
    }
    {
        register u32 input_offset asm("r1") = *(u8 *)0x0200A880;
        input_offset <<= 1;
        {
            register u32 page_offset asm("r0") = *(u8 *)0x02032B98;
            page_offset <<= 4;
            input_offset += page_offset;
        }
        {
            register u32 order_base asm("r0") = 0x087A21B0;
            asm volatile("add %0, %0, %1"
                         : "+r"(input_offset)
                         : "r"(order_base));
        }
        var_r6 = *(u8 *)input_offset;
    }
    goto loop_66;
    }
block_69:
    func_08094554(temp_r8);
    temp_r0 = *(u8 *)0x0200A882;
    if (temp_r0 != 1) {
        goto block_74;
    }
    {
        register u32 price_address asm("r0");
        register u32 price_base asm("r1") = 0x087A2390;
        register u32 *money_ptr asm("r2");
        register u32 money asm("r1");
        register u32 price asm("r0");
        asm volatile("add %0, %1, %2"
                     : "=r"(price_address)
                     : "r"(temp_r4), "r"(price_base));
        money_ptr = (u32 *)0x020282E8;
        money = *money_ptr;
        price = *(u32 *)price_address;
        if (money < price) {
            goto block_73;
        }
    }
    var_r5 = 0x1100;
    goto block_143;
block_73:
    func_08098BB4(0x0800481A);
    goto block_143;
block_74:
    if (temp_r0 != 2) {
        goto block_76;
    }
    {
        register s32 message asm("r0") = 0x080046AE;
        asm volatile("" : "+r"(message));
        var_r0 = message;
    }
    goto block_138;
block_76:
    {
        register s32 *modal_load asm("r1") = sp24;
        register s32 modal_mask asm("r1");
        var_r0_2 = *modal_load;
        modal_mask = 0x20000;
        var_r0_2 |= modal_mask;
        modal_store = sp24;
    }
    goto block_117;
block_77:
    temp_r4_2 = var_r6 * 4;
    {
        register u32 price_base asm("r0") = 0x087A2390;
        register u32 *price_ptr asm("r1");
        register u32 *money_ptr asm("r2");
        register u32 money asm("r0");
        register s32 price asm("r1");
        asm volatile("B7390_PRICE_ADD_AND_FIX_AMOUNT %0, %1, %2"
                     : "=r"(price_ptr)
                     : "r"(temp_r4_2), "r"(price_base));
        money_ptr = (u32 *)0x020282E8;
        money = *money_ptr;
        price = *price_ptr;
        sp18 = func_080ECF00(money, price);
    }
    {
    register u32 temp_r2 asm("r2") = M2C_FIELD(var_r6, u8 *, 0x02028218);
    register s32 amount_for_sum asm("r1") = *(volatile s32 *)&sp18;
    register s32 amount_sum asm("r0");
    amount_sum = temp_r2 + amount_for_sum;
    if (amount_sum <= 0x63) {
        goto block_79;
    }
    sp18 = 0x63 - temp_r2;
    }
block_79:
    {
    register s32 amount_check asm("r2") = sp18;
    if (amount_check != 0) {
        goto block_82;
    }
    }
    var_r5 = 0x1105;
    goto block_143;
block_82:
    asm volatile(
        ".set b7390_seed1_mov_count, 0\n\t"
        ".macro mov args:vararg\n\t"
        ".if b7390_seed1_mov_count == 0\n\t"
        ".short 0x2001\n\t"
        ".else\n\t"
        ".purgem mov\n\t"
        "mov sl, r0\n\t"
        ".endif\n\t"
        ".set b7390_seed1_mov_count, b7390_seed1_mov_count + 1\n\t"
        ".endm\n\t"
        ".set b7390_message_ldr_count, 0\n\t"
        ".macro ldr args:vararg\n\t"
        ".short 0x480F\n\t"
        ".if b7390_message_ldr_count == 1\n\t"
        ".purgem ldr\n\t"
        ".endif\n\t"
        ".set b7390_message_ldr_count, b7390_message_ldr_count + 1\n\t"
        ".endm\n\t"
        ".macro add args:vararg\n\t"
        ".short 0x1820\n\t"
        ".purgem add\n\t"
        ".endm");
    var_sl = 1;
    func_08098BB4(0x0800473F);
    func_080981F0(M2C_FIELD(temp_r4_2, s32 *, 0x087EE170), 1, 7, 0, 0);
    asm volatile(
        "mov r0, #80\n\t"
        "str r0, [sp, #0]"
        : : : "r0", "r1", "memory");
    {
        register s32 kind asm("r0") = 0x2CF;
        register s32 zero asm("r2");
        asm volatile(
            "str %0, [sp, #4]\n\t"
            "mov %0, #15\n\t"
            "str %0, [sp, #8]\n\t"
            "mov %0, #8\n\t"
            "str %0, [sp, #12]\n\t"
            "mov %1, #0\n\t"
            "str %1, [sp, #16]"
            : "+r"(kind), "=r"(zero) : : "r1", "memory");
        sp20 = func_08094484_4(
            ({ register s32 arg asm("r0") = 0x0810548C;
               arg; }),
            ({ register s32 arg asm("r1") = 0x08105498;
               arg; }),
            zero, 0x80);
    }
    var_r5 = 0x1110;
    goto block_143;
block_84:
    var_r0_3 = 0x080048C6;
    goto block_99;
block_85:
    var_r4_2 = 0;
    func_08098BB4(0x080047D6);
    func_08096F3C();
    {
    register s32 seven asm("r5") = 7;
    register u32 price_base asm("r1") = 0x087A2390;
    register u32 *price_ptr asm("r7");
    asm volatile(
        "lsl r0, %1, #2\n\t"
        "add %0, r0, %2"
        : "=r"(price_ptr)
        : "r"(var_r6), "r"(price_base)
        : "r0");
loop_86:
    {
        register u32 call_quantity asm("r0");
        register s32 call_amount asm("r1");
        asm volatile(
            "mov %0, %2\n\t"
            "ldr %1, [sp, #24]"
            : "=r"(call_quantity), "=r"(call_amount)
            : "r"(var_sl));
        var_sl = func_080B684C(call_quantity, call_amount);
    }
    if (var_sl == var_r4_2) {
        goto block_88;
    }
    func_0809844C(var_sl, 2, 0, 2, seven, 0x10, 0);
    {
        register s32 call_value asm("r0");
        register s32 product asm("r1");
        asm volatile(
            "ldr %0, [%3]\n\t"
            "mov %1, %2\n\t"
            "mul %1, %0\n\t"
            "add %0, %1, #0"
            : "=&r"(call_value), "=&r"(product)
            : "r"(var_sl), "r"(price_ptr)
            : "cc", "memory");
        func_0809844C(call_value, 7, 0, 2, seven, 0xA, 2);
    }
    func_080972C8();
    var_r4_2 = var_sl;
block_88:
    func_080ED17C(1);
    temp_r1 = *(u16 *)0x0300000E;
    if (!(3 & temp_r1)) {
        goto loop_86;
    }
    if (!(1 & temp_r1)) {
        goto block_91;
    }
    func_08092E84(0x3E);
    var_r5 = 0x1120;
    goto block_143;
block_91:
    func_08098BB4(0x08004767);
    func_08094554(sp20);
    func_08092E84(0x3F);
    var_r5 = 0x1010;
    goto block_143;
    }
block_93:
    func_08098BB4(0x080047EE);
    func_08098BB4(0x0800476A);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_96;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_96;
    }
    var_r5 = 0x1130;
    goto block_143;
block_96:
    func_08098BB4(0x08004783);
    var_r5 = 0x1110;
    goto block_143;
block_98:
    func_080E5E90(var_sl * M2C_FIELD((var_r6 * 4), s32 *, 0x087A2390));
    func_080E5CE4(var_r6, var_sl);
    {
        register u32 *money_ptr asm("r1") = (u32 *)0x020282E8;
        register u32 money_value asm("r0");
        register s32 zero asm("r2");
        asm volatile(
            "ldr %0, [%1]\n\t"
            "mov %1, #1\n\t"
            "str %1, [sp, #0]\n\t"
            "str %1, [sp, #4]\n\t"
            "mov %2, #0\n\t"
            "str %2, [sp, #8]"
            : "=r"(money_value), "+r"(money_ptr), "=r"(zero)
            : : "memory");
        func_0809844C_4(money_value, 7, zero, 2);
    }
    {
        register u8 *amount_base asm("r1") = (u8 *)0x02028218;
        register u32 amount_value asm("r0");
        register s32 zero asm("r2");
        asm volatile(
            "add %0, %3, %1\n\t"
            "ldrb %0, [%0]\n\t"
            "mov %1, #6\n\t"
            "str %1, [sp, #0]\n\t"
            "mov %1, #10\n\t"
            "str %1, [sp, #4]\n\t"
            "mov %2, #0\n\t"
            "str %2, [sp, #8]"
            : "=r"(amount_value), "+r"(amount_base), "=r"(zero)
            : "r"(var_r6) : "memory");
        func_0809844C_4(amount_value, 2, zero, 2);
    }
    func_08098BB4(0x08004783);
    func_08098BB4(0x08004767);
    func_08094554(sp20);
    var_r0_3 = 0x08004804;
block_99:
    func_08098BB4(var_r0_3);
    var_r5 = 0x1010;
    goto block_143;
block_101:
    func_08098BB4(0x08004661);
    sp1C = 0;
    goto block_142;
block_102:
    asm volatile("B7390_INIT_LIST_AND_FIX_SLOT %0" : "=r"(var_r4_3));
    if (var_r4_3 >= (u32)*(u8 *)0x02032379) {
        goto block_105;
    }
    {
    register s32 *message_table asm("r5") = (s32 *)0x087EE170;
loop_104:
    func_080988C8(4, message_table[M2C_FIELD(var_r4_3, u8 *, 0x020322B2)]);
    var_r4_3 = (u8)(var_r4_3 + 1);
    if (var_r4_3 < (u32)*(u8 *)0x02032379) {
        goto loop_104;
    }
    }
block_105:
    {
        register u8 *slot_base asm("r0") = (u8 *)0x020322B2;
        register u32 selected_index asm("r1") = sp1C;
        asm volatile("add %0, %1, %0"
                     : "+r"(slot_base) : "r"(selected_index));
        var_r6 = *slot_base;
    }
    var_r5 = 0x2020;
    goto block_143;
block_106:
    func_08098BB4(0x08004844);
    asm volatile(
        "mov r0, #152\n\t"
        "str r0, [sp, #0]"
        : : : "r0", "r1", "memory");
    {
        register s32 kind asm("r0") = 0x38F;
        register s32 zero asm("r2");
        asm volatile(
            "str %0, [sp, #4]\n\t"
            "mov %0, #15\n\t"
            "str %0, [sp, #8]\n\t"
            "mov %0, #8\n\t"
            "str %0, [sp, #12]\n\t"
            "mov %1, #0\n\t"
            "str %1, [sp, #16]"
            : "+r"(kind), "=r"(zero) : : "r1", "memory");
        temp_r8_2 = func_08094484_4(
            ({ register s32 arg asm("r0") = 0x08105DA4;
               arg; }),
            ({ register s32 arg asm("r1") = 0x08105DB0;
               arg; }),
            zero, 0xA0);
    }
    {
    register s32 six_2 asm("r4") = 6;
    register s32 eight_2 asm("r7") = 8;
loop_107:
    asm volatile(
        ".set b7390_display_add_count, 0\n\t"
        ".macro add args:vararg\n\t"
        ".if b7390_display_add_count == 0\n\t"
        ".short 0x1980\n\t"
        ".else\n\t"
        ".short 0x1840\n\t"
        ".purgem add\n\t"
        ".endif\n\t"
        ".set b7390_display_add_count, b7390_display_add_count + 1\n\t"
        ".endm\n\t"
        ".macro ldr args:vararg\n\t"
        ".short 0x491E\n\t"
        ".purgem ldr\n\t"
        ".endm");
    func_080986B4(5);
    func_080ACDA8((var_r6 * 0x18) + 0x087B2524, 5, 3);
    func_0809844C((u32)M2C_FIELD((var_r6 * 4), u32 *, 0x087A2390) >> 1, 6, 0, 2, 5, six_2, eight_2);
    func_0809844C((u32)M2C_FIELD(var_r6, u8 *, 0x02028218), 2, 0, 2, six_2, 0xA, 0);
    func_08098BB4(0x080046AA);
    if (*(u8 *)0x0200A882 != 0) {
        goto block_111;
    }
    {
        register u16 *keys_ptr asm("r0") = (u16 *)0x0200A884;
        register u32 keys asm("r1");
        register u32 mask asm("r0");
        keys = *keys_ptr;
        mask = eight_2;
        if (mask & keys) {
            goto block_111;
        }
    }
    {
        register u8 *slot_base asm("r1") = (u8 *)0x020322B2;
        register u32 slot_address asm("r0");
        asm volatile("" : "+r"(slot_base));
        slot_address = *(u8 *)0x0200A880;
        asm volatile("add %0, %0, %1"
                     : "+r"(slot_address) : "r"(slot_base));
        var_r6 = *(u8 *)slot_address;
    }
    goto loop_107;
    }
block_111:
    func_08094554(temp_r8_2);
    temp_r0_2 = *(u8 *)0x0200A882;
    if (temp_r0_2 != 1) {
        goto block_114;
    }
    sp1C = *(u8 *)0x0200A880;
    var_r5 = 0x2100;
    goto block_143;
block_114:
    if (temp_r0_2 != 2) {
        goto block_116;
    }
    var_r0 = 0x080046AE;
    goto block_138;
block_116:
    modal_store = sp24;
    var_r0_2 = *modal_store;
    {
        register s32 modal_mask asm("r1") = 0x20000;
        var_r0_2 |= modal_mask;
    }
block_117:
    *modal_store = var_r0_2;
    func_080B7210(var_r6);
    {
        register s32 *modal_load asm("r1") = sp24;
        register s32 flags asm("r0");
        register s32 mask asm("r1");
        register s32 *clear_store asm("r2");
        flags = *modal_load;
        mask = 0xFFFDFFFF;
        flags &= mask;
        clear_store = sp24;
        *clear_store = flags;
    }
    goto block_143;
block_118:
    func_08098BB4(0x0800473F);
    {
        register s32 *message_base asm("r1") = (s32 *)0x087EE170;
        asm volatile("" : "+r"(message_base));
        func_080981F0(message_base[var_r6], 1, 7, 0, 0);
    }
    asm volatile(
        ".set b7390_seed2_mov_count, 0\n\t"
        ".macro mov args:vararg\n\t"
        ".if b7390_seed2_mov_count == 0\n\t"
        ".short 0x2201\n\t"
        ".else\n\t"
        ".purgem mov\n\t"
        "mov sl, r2\n\t"
        ".endif\n\t"
        ".set b7390_seed2_mov_count, b7390_seed2_mov_count + 1\n\t"
        ".endm");
    {
        register u32 one asm("r2") = 1;
        var_sl = one;
    }
    {
        register u8 *amount_base asm("r1") = (u8 *)0x02028218;
        register u32 amount_addr asm("r0");
        asm volatile("" : "+r"(amount_base));
        amount_addr = var_r6 + (u32)amount_base;
        sp18 = *(u8 *)amount_addr;
    }
    asm volatile(
        "mov r0, #80\n\t"
        "str r0, [sp, #0]"
        : : : "r0", "r1", "memory");
    {
        register s32 kind asm("r0") = 0x2CF;
        register s32 zero asm("r2");
        asm volatile(
            "str %0, [sp, #4]\n\t"
            "mov %0, #15\n\t"
            "str %0, [sp, #8]\n\t"
            "mov %0, #8\n\t"
            "str %0, [sp, #12]\n\t"
            "mov %1, #0\n\t"
            "str %1, [sp, #16]"
            : "+r"(kind), "=r"(zero) : : "r1", "memory");
        sp20 = func_08094484_4(
            ({ register s32 arg asm("r0") = 0x0810548C;
               asm volatile("" : "+r"(arg)); arg; }),
            ({ register s32 arg asm("r1") = 0x08105498;
               asm volatile("" : "+r"(arg)); arg; }),
            zero, 0x80);
    }
    var_r5 = 0x2110;
    goto block_143;
block_119:
    var_r4_4 = 0;
    func_08098BB4(0x0800487E);
    func_08096F3C();
    {
    register u32 *price_table asm("r5") = (u32 *)0x087A2390;
    asm volatile("" : "+r"(price_table));
loop_120:
    {
        register u32 call_quantity asm("r0");
        register s32 call_amount asm("r1");
        asm volatile(
            "mov %0, %2\n\t"
            "ldr %1, [sp, #24]"
            : "=r"(call_quantity), "=r"(call_amount)
            : "r"(var_sl));
        var_sl = func_080B684C(call_quantity, call_amount);
    }
    if (var_sl == var_r4_4) {
        goto block_126;
    }
    func_0809844C((u32)var_sl, 2, 0, 2, 7, 0x10, 0);
    temp_r1_2 = var_sl * (price_table[var_r6] >> 1);
    if (temp_r1_2 <= 0x98967FU) {
        goto block_124;
    }
    func_0809844C(0x98967FU, 7, 0, 2, 7, 0xA, 2);
    goto block_125;
block_124:
    func_0809844C(temp_r1_2, 7, 0, 2, 7, 0xA, 2);
block_125:
    func_080972C8();
    var_r4_4 = var_sl;
block_126:
    func_080ED17C(1);
    temp_r1_3 = *(u16 *)0x0300000E;
    if (!(3 & temp_r1_3)) {
        goto loop_120;
    }
    if (!(1 & temp_r1_3)) {
        goto block_129;
    }
    func_08092E84(0x3E);
    var_r5 = 0x2120;
    goto block_143;
block_129:
    func_08098BB4(0x08004767);
    func_08094554(sp20);
    func_08092E84(0x3F);
    var_r5 = 0x2020;
    goto block_143;
    }
block_131:
    func_08098BB4(0x080047EE);
    func_08098BB4(0x0800476A);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_134;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_134;
    }
    var_r5 = 0x2130;
    goto block_143;
block_134:
    func_08098BB4(0x08004783);
    var_r5 = 0x2110;
    goto block_143;
block_136:
    func_080E5E64(var_sl * ((u32)M2C_FIELD((var_r6 * 4), u32 *, 0x087A2390) >> 1));
    func_080E5D38(var_r6, var_sl);
    {
        register u32 *money_ptr asm("r1") = (u32 *)0x020282E8;
        register u32 money_value asm("r0");
        register s32 zero asm("r2");
        asm volatile(
            "ldr %0, [%1]\n\t"
            "mov %1, #1\n\t"
            "str %1, [sp, #0]\n\t"
            "str %1, [sp, #4]\n\t"
            "mov %2, #0\n\t"
            "str %2, [sp, #8]"
            : "=r"(money_value), "+r"(money_ptr), "=r"(zero)
            : : "memory");
        func_0809844C_4(money_value, 7, zero, 2);
    }
    {
        register u8 *amount_base asm("r1") = (u8 *)0x02028218;
        register u32 amount_value asm("r0");
        register s32 zero asm("r2");
        asm volatile(
            "add %0, %3, %1\n\t"
            "ldrb %0, [%0]\n\t"
            "mov %1, #6\n\t"
            "str %1, [sp, #0]\n\t"
            "mov %1, #10\n\t"
            "str %1, [sp, #4]\n\t"
            "mov %2, #0\n\t"
            "str %2, [sp, #8]"
            : "=r"(amount_value), "+r"(amount_base), "=r"(zero)
            : "r"(var_r6) : "memory");
        func_0809844C_4(amount_value, 2, zero, 2);
    }
    func_08098BB4(0x08004783);
    func_08098BB4(0x08004767);
    func_08094554(sp20);
    func_08098BB4(0x08004804);
    func_080B65A4();
    temp_r0_3 = *(u8 *)0x02032379;
    if (temp_r0_3 != 0) {
        goto block_139;
    }
    func_08098BB4(0x080046AE);
    var_r0 = 0x08004896;
block_138:
    func_08098BB4(var_r0);
    var_r5 = 0;
    goto block_143;
block_139:
    if (temp_r0_3 != sp1C) {
        goto block_141;
    }
    {
        register u32 previous_index asm("r0") = sp1C;
        asm volatile("sub %0, %0, #1" : "+r"(previous_index));
        sp1C = (u8)previous_index;
    }
block_141:
    func_08098834(4);
block_142:
    var_r5 = 0x2010;
block_143:
    if ((u32)(*(s32 *)0x02021690 - 6) <= 1U) {
        goto loop_5;
    }
    goto loop_146;
block_145:
    func_080ED17C(1);
loop_146:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_145;
    }
    if (*(u8 *)0x02030664 != 2) {
        goto block_149;
    }
    *(u8 *)0x02030664 = 1;
    func_080ED17C(1);
block_149:
    return;
}

#undef sp18
#undef sp1C
#undef sp20
#undef sp24
