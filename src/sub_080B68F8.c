#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096F3C();                            /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08096FBC_4, func_08096FBC");
M2C_UNK func_08096FBC_4(s32, s32, s32, s32);        /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C(u32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080984C4(u32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098834(s32);                         /* extern */
M2C_UNK func_080988C8(s32, s32);                    /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809AB44(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080B654C();                            /* extern */
u32 func_080B684C(u32, u8);                         /* extern */
M2C_UNK func_080E5D6C(u8, u8);                      /* extern */
M2C_UNK func_080E5D98(u8, u8);                      /* extern */
M2C_UNK func_080E5E64(s32);                         /* extern */
M2C_UNK func_080E5E90(s32);                         /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
u8 func_080ECF00(u32, s32);                         /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

asm(
    ".macro B68F8_FORCE_SHORT_NEXT_BRANCH\n"
    ".macro b target\n"
    ".purgem b\n"
    ".purgem bl\n"
    "b \\target\n"
    ".endm\n"
    ".macro bl target\n"
    ".purgem b\n"
    ".purgem bl\n"
    "b \\target\n"
    ".endm\n"
    ".endm\n"
    ".set B68F8_ADD_COUNT, 0\n"
    ".macro B68F8_INSTALL_ADD\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    ".set B68F8_ADD_COUNT, B68F8_ADD_COUNT + 1\n"
    ".if B68F8_ADD_COUNT == 16\n"
    ".short 0x1838\n"
    ".elseif B68F8_ADD_COUNT == 19\n"
    ".short 0x1861\n"
    ".elseif B68F8_ADD_COUNT == 20\n"
    ".short 0x1838\n"
    ".elseif B68F8_ADD_COUNT == 22\n"
    ".short 0x1820\n"
    ".elseif B68F8_ADD_COUNT == 24\n"
    ".short 0x1C08\n"
    ".elseif B68F8_ADD_COUNT == 26\n"
    ".short 0x1C10\n"
    ".elseif B68F8_ADD_COUNT == 28\n"
    ".short 0x1838\n"
    ".elseif B68F8_ADD_COUNT == 29\n"
    ".short 0x1820\n"
    ".elseif B68F8_ADD_COUNT == 34\n"
    ".short 0x1824\n"
    ".elseif B68F8_ADD_COUNT == 35\n"
    ".short 0x1838\n"
    ".elseif B68F8_ADD_COUNT == 38\n"
    ".short 0x1838\n"
    ".elseif B68F8_ADD_COUNT == 40\n"
    ".short 0x1C10\n"
    ".elseif B68F8_ADD_COUNT == 42\n"
    ".short 0x1C08\n"
    ".elseif B68F8_ADD_COUNT == 44\n"
    ".short 0x1838\n"
    ".else\n"
    "add \\args\n"
    ".endif\n"
    ".if B68F8_ADD_COUNT < 44\n"
    "B68F8_INSTALL_ADD\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_ADD\n"
    ".set B68F8_AND_COUNT, 0\n"
    ".macro B68F8_INSTALL_AND\n"
    ".macro and args:vararg\n"
    ".purgem and\n"
    ".set B68F8_AND_COUNT, B68F8_AND_COUNT + 1\n"
    ".if B68F8_AND_COUNT == 2\n"
    ".short 0x4008\n"
    ".elseif B68F8_AND_COUNT == 4\n"
    ".short 0x4008\n"
    ".else\n"
    "and \\args\n"
    ".endif\n"
    ".if B68F8_AND_COUNT < 4\n"
    "B68F8_INSTALL_AND\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_AND\n"
    ".set B68F8_CMP_COUNT, 0\n"
    ".macro B68F8_INSTALL_CMP\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    ".set B68F8_CMP_COUNT, B68F8_CMP_COUNT + 1\n"
    ".if B68F8_CMP_COUNT == 37\n"
    ".short 0x2800\n"
    ".elseif B68F8_CMP_COUNT == 46\n"
    ".short 0x2800\n"
    ".else\n"
    "cmp \\args\n"
    ".endif\n"
    ".if B68F8_CMP_COUNT < 46\n"
    "B68F8_INSTALL_CMP\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_CMP\n"
    ".set B68F8_LDR_COUNT, 0\n"
    ".macro B68F8_INSTALL_LDR\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    ".set B68F8_LDR_COUNT, B68F8_LDR_COUNT + 1\n"
    ".if B68F8_LDR_COUNT == 6\n"
    ".short 0x4923\n"
    ".elseif B68F8_LDR_COUNT == 7\n"
    ".short 0x6808\n"
    ".elseif B68F8_LDR_COUNT == 43\n"
    ".short 0x4815\n"
    ".elseif B68F8_LDR_COUNT == 48\n"
    ".short 0x4A03\n"
    ".elseif B68F8_LDR_COUNT == 49\n"
    ".short 0x6811\n"
    ".elseif B68F8_LDR_COUNT == 57\n"
    ".short 0x4809\n"
    ".elseif B68F8_LDR_COUNT == 60\n"
    ".short 0x480F\n"
    ".elseif B68F8_LDR_COUNT == 83\n"
    ".short 0x4915\n"
    ".elseif B68F8_LDR_COUNT == 84\n"
    ".short 0x6808\n"
    ".elseif B68F8_LDR_COUNT == 85\n"
    ".short 0x4810\n"
    ".elseif B68F8_LDR_COUNT == 94\n"
    ".short 0x480C\n"
    ".elseif B68F8_LDR_COUNT == 104\n"
    ".short 0x4818\n"
    ".elseif B68F8_LDR_COUNT == 107\n"
    ".short 0x4812\n"
    ".elseif B68F8_LDR_COUNT == 117\n"
    ".short 0x480D\n"
    ".elseif B68F8_LDR_COUNT == 139\n"
    ".short 0x491A\n"
    ".elseif B68F8_LDR_COUNT == 140\n"
    ".short 0x6808\n"
    ".elseif B68F8_LDR_COUNT == 141\n"
    ".short 0x4815\n"
    ".else\n"
    "ldr \\args\n"
    ".endif\n"
    ".if B68F8_LDR_COUNT < 141\n"
    "B68F8_INSTALL_LDR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_LDR\n"
    ".set B68F8_LSL_COUNT, 0\n"
    ".macro B68F8_INSTALL_LSL\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    ".set B68F8_LSL_COUNT, B68F8_LSL_COUNT + 1\n"
    ".if B68F8_LSL_COUNT == 25\n"
    ".short 0x0601\n"
    ".elseif B68F8_LSL_COUNT == 33\n"
    ".short 0x0611\n"
    ".else\n"
    "lsl \\args\n"
    ".endif\n"
    ".if B68F8_LSL_COUNT < 33\n"
    "B68F8_INSTALL_LSL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_LSL\n"
    ".set B68F8_MOV_COUNT, 0\n"
    ".macro B68F8_INSTALL_MOV\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".set B68F8_MOV_COUNT, B68F8_MOV_COUNT + 1\n"
    ".if B68F8_MOV_COUNT == 53\n"
    ".short 0x4651\n"
    ".elseif B68F8_MOV_COUNT == 65\n"
    ".short 0x4651\n"
    ".elseif B68F8_MOV_COUNT == 72\n"
    ".short 0x4652\n"
    ".elseif B68F8_MOV_COUNT == 81\n"
    ".short 0x4650\n"
    ".elseif B68F8_MOV_COUNT == 86\n"
    ".short 0x4641\n"
    ".elseif B68F8_MOV_COUNT == 99\n"
    ".short 0x4642\n"
    ".elseif B68F8_MOV_COUNT == 100\n"
    ".short 0x4640\n"
    ".elseif B68F8_MOV_COUNT == 102\n"
    ".short 0x4652\n"
    ".elseif B68F8_MOV_COUNT == 145\n"
    ".short 0x4650\n"
    ".elseif B68F8_MOV_COUNT == 154\n"
    ".short 0x4651\n"
    ".elseif B68F8_MOV_COUNT == 159\n"
    ".short 0x4642\n"
    ".elseif B68F8_MOV_COUNT == 171\n"
    ".short 0x4641\n"
    ".elseif B68F8_MOV_COUNT == 172\n"
    ".short 0x4642\n"
    ".elseif B68F8_MOV_COUNT == 174\n"
    ".short 0x4652\n"
    ".else\n"
    "mov \\args\n"
    ".endif\n"
    ".if B68F8_MOV_COUNT < 174\n"
    "B68F8_INSTALL_MOV\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_MOV\n"
    ".set B68F8_MUL_COUNT, 0\n"
    ".macro B68F8_INSTALL_MUL\n"
    ".macro mul args:vararg\n"
    ".purgem mul\n"
    ".set B68F8_MUL_COUNT, B68F8_MUL_COUNT + 1\n"
    ".if B68F8_MUL_COUNT == 1\n"
    ".short 0x4341\n"
    ".elseif B68F8_MUL_COUNT == 2\n"
    ".short 0x4342\n"
    ".elseif B68F8_MUL_COUNT == 3\n"
    ".short 0x4342\n"
    ".elseif B68F8_MUL_COUNT == 4\n"
    ".short 0x4341\n"
    ".else\n"
    "mul \\args\n"
    ".endif\n"
    ".if B68F8_MUL_COUNT < 4\n"
    "B68F8_INSTALL_MUL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_MUL\n"
    ".set B68F8_STR_COUNT, 0\n"
    ".macro B68F8_INSTALL_STR\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    ".set B68F8_STR_COUNT, B68F8_STR_COUNT + 1\n"
    ".if B68F8_STR_COUNT == 21\n"
    ".short 0x9102\n"
    ".elseif B68F8_STR_COUNT == 22\n"
    ".short 0x9100\n"
    ".elseif B68F8_STR_COUNT == 27\n"
    ".short 0x9204\n"
    ".elseif B68F8_STR_COUNT == 31\n"
    ".short 0x9002\n"
    ".elseif B68F8_STR_COUNT == 37\n"
    ".short 0x9202\n"
    ".elseif B68F8_STR_COUNT == 53\n"
    ".short 0x9004\n"
    ".elseif B68F8_STR_COUNT == 57\n"
    ".short 0x9102\n"
    ".elseif B68F8_STR_COUNT == 63\n"
    ".short 0x9202\n"
    ".else\n"
    "str \\args\n"
    ".endif\n"
    ".if B68F8_STR_COUNT < 63\n"
    "B68F8_INSTALL_STR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B68F8_INSTALL_STR\n");

void sub_080B68F8(void) {
    register u32 var_sl asm("sl");
    s32 frame_pad;
    u8 sp18;
    s32 sp1C;
    M2C_UNK var_r0;
    M2C_UNK var_r0_2;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    register s32 var_r5 asm("r5");
    u16 temp_r1;
    u16 temp_r1_2;
    u8 temp_r0;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r2;
    u8 var_r4;
    u32 displayed_quantity;
    u8 var_r7;
    u32 var_r8;
    u8 var_r9;
    u8 var_r4_3;

    asm volatile("" : "=m"(frame_pad));
    *(s16 *)0x0300004C = 0x1140;
    {
        register s32 setup_x asm("r3") = 0x3C0;
        register s32 *out_args asm("sp");

        out_args[0] = setup_x;
        var_r5 = 0;
        out_args[1] = var_r5;
        out_args[2] = 0xE;
        out_args[3] = var_r5;
        out_args[4] = 0x3E6;
        out_args[5] = 0xF;
        func_08096FBC_4(0, 1, 0, setup_x);
    }
    func_080ECD34(0x081046A8, 0x06015840);
    func_0809AB44(2, 3, 0, 0, 1);
    func_08098BB4(0x080043D7);
    func_0809844C(*(u32 *)0x020282E8, 7, 0, 2, 1, 1, var_r5);
    func_08094330();
    func_08094484(0x08105724, 0x08105758, 0, 0xA0, 0x6C, 0x2EA, 0xF, 0x20, var_r5);
    func_08096308(0xF, 0);
    if (*(s32 *)0x02021690 == 5) {
        var_sl = var_r5;
        do {
            {
                register s32 state_1130 asm("r2") = 0x1130;

                if (var_r5 != state_1130) {
                    goto dispatch_7;
                }
                goto state_1130;
dispatch_7:
                if (var_r5 > state_1130) {
                    goto dispatch_28;
                }
            }
            if (var_r5 != 0x1100) {
                goto dispatch_10;
            }
            goto state_1100;
dispatch_10:
            if (var_r5 > 0x1100) {
                goto dispatch_19;
            }
            if (var_r5 != 0x1000) {
                goto dispatch_13;
            }
            goto state_1000;
dispatch_13:
            if (var_r5 > 0x1000) {
                goto dispatch_16;
            }
            if (var_r5 == 0) {
                goto state_0;
            }
            goto state_done;
dispatch_16:
            if (var_r5 == 0x1010) {
                goto state_1010;
            }
            goto state_done;
dispatch_19:
            if (var_r5 != 0x1110) {
                goto dispatch_21;
            }
            goto state_1110;
dispatch_21:
            if (var_r5 > 0x1110) {
                goto dispatch_25;
            }
            if (var_r5 == 0x1105) {
                goto state_1105;
            }
            goto state_done;
dispatch_25:
            if (var_r5 == 0x1120) {
                goto state_1120;
            }
            asm volatile("B68F8_FORCE_SHORT_NEXT_BRANCH");
            goto state_done;
dispatch_28:
            if (var_r5 != 0x2100) {
                goto dispatch_30;
            }
            goto state_2100;
dispatch_30:
            if (var_r5 > 0x2100) {
                goto dispatch_41;
            }
            {
                register s32 state_2010 asm("r4") = 0x2010;

                if (var_r5 != state_2010) {
                    goto dispatch_33;
                }
                goto state_2010;
dispatch_33:
                if (var_r5 > state_2010) {
                    goto dispatch_38;
                }
            }
            if (var_r5 == 0x2000) {
                goto state_2000;
            }
            goto state_done;
dispatch_38:
            if (var_r5 == 0x2020) {
                goto state_2020;
            }
            goto state_done;
dispatch_41:
            if (var_r5 != 0x2120) {
                goto dispatch_43;
            }
            goto state_2120;
dispatch_43:
            if (var_r5 > 0x2120) {
                goto dispatch_47;
            }
            if (var_r5 == 0x2110) {
                goto state_2110;
            }
            goto state_done;
dispatch_47:
            if (var_r5 == 0x2130) {
                goto state_2130;
            }
            goto state_done;
            if (0) {
            switch (var_r5) {
            case 0x0:
state_0:
                func_08098BB4(0x080044C0);
                func_08098BB4(0x08004423);
                if (*(u8 *)0x0200A882 == 1) {
                    if (*(u8 *)0x0200A880 == 0) {
                        var_r5 = 0x1000;
                    } else {
                        func_080B654C();
                        if (*(u8 *)0x020322B1 == 0) {
                            func_08098BB4(0x080045C6);
                        } else {
                            var_r5 = 0x2000;
                        }
                    }
                } else {
                    *(s32 *)0x02021690 = 3;
                    func_08096308(0x10, 0);
                }
                break;
            case 0x1000:
state_1000:
                func_08098BB4(0x08004427);
                var_r4 = 0;
                {
                    register u8 *order_base asm("r1") = (u8 *)0x087A1F98;
                    register u8 *page_ptr asm("r2") = (u8 *)0x02032B98;

                    if (*(u16 *)(order_base + (*page_ptr * 0x10)) != 0) {
                        register s32 *message_table asm("r7") = (s32 *)0x087EEE10;
                        register u8 *loop_order_base asm("r6") = order_base;
                        register u8 *loop_page_ptr asm("r5") = page_ptr;

loop_60:
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
                        if ((u32)var_r4 <= 7U) {
                            register u32 check_offset asm("r0") = var_r4 * 2;
                            register u32 check_page asm("r1") = *loop_page_ptr;

                            check_page *= 0x10;
                            check_offset += check_page;
                            check_offset += (u32)loop_order_base;
                            if (*(u16 *)check_offset != 0) {
                                goto loop_60;
                            }
                        }
                    }
                }
                {
                    register u8 *order_base asm("r1") = (u8 *)0x087A1F98;

                    asm volatile("" : "+r"(order_base));
                    var_r7 = order_base[*(u8 *)0x02032B98 * 0x10];
                }
                var_r5 = 0x1010;
                break;
            case 0x1010:
state_1010:
                {
                func_08098BB4(0x080044DA);
                {
                register u8 *order_base asm("r6") = (u8 *)0x087A1F98;
loop_64:
                func_080986B4(5);
                {
                    register s32 *name_base asm("r0") = (s32 *)0x087EEE38;

                    asm volatile("" : "+r"(name_base));
                temp_r4_2 = var_r7 * 4;
                func_08098248(*(s32 *)(temp_r4_2 + (u32)name_base), 0, 5);
                }
                func_080981F0(0x08106568, 0, 5, 0, 8);
                func_080984C4(M2C_FIELD(temp_r4_2, u32 *, 0x087A2188), 6, 0, 2, 5);
                func_08098248(0x08106578, 0, 5);
                func_0809844C((u32) M2C_FIELD(var_r7, u8 *, 0x020217F4), 2, 0, 2, 6, 0xA, var_sl);
                func_08098BB4(0x0800446E);
                temp_r0 = *(u8 *)0x0200A882;
                if (temp_r0 == 0) {
                    register u32 input_offset asm("r1") = *(u8 *)0x0200A880;

                    input_offset <<= 1;
                    {
                        register u32 page_offset asm("r0") = *(u8 *)0x02032B98;

                        page_offset <<= 4;
                        input_offset += page_offset;
                    }
                    input_offset += (u32)order_base;
                    var_r7 = *(u8 *)input_offset;
                    goto loop_64;
                }
                }
                }
                if (temp_r0 == 1) {
                    if ((u32) *(u32 *)0x020282E8 >= (u32) M2C_FIELD(temp_r4_2, u32 *, 0x087A2188)) {
                        var_r5 = 0x1100;
                    } else {
                        func_08098BB4(0x08004560);
                    }
                } else {
                    var_r0_2 = 0x08004472;
                    asm volatile("" : "+r"(var_r0_2));
                    goto block_123;
                }
                break;
            case 0x1100:
state_1100:
                {
                    register u32 price_address asm("r1") = 0x087A2188;
                    register u32 *money_ptr asm("r2");
                    register u32 money asm("r0");

                    asm volatile("" : "+r"(price_address));
                    temp_r4 = var_r7 * 4;
                    price_address += temp_r4;
                    money_ptr = (u32 *)0x020282E8;
                    money = *money_ptr;
                    price_address = *(u32 *)price_address;
                    asm volatile("" : "=r"(var_r9) : "0"(func_080ECF00(money, price_address)));
                }
                temp_r2 = M2C_FIELD(var_r7, u8 *, 0x020217F4);
                if ((s32) (temp_r2 + var_r9) > 0x63) {
                    asm volatile("" : "=r"(var_r9) : "0"(0x63 - temp_r2));
                }
                if (var_r9 == 0) {
                    var_r5 = 0x1105;
                } else {
                    var_r8 = 1;
                    func_08098BB4(0x08004479);
                    func_080981F0(M2C_FIELD(temp_r4, s32 *, 0x087EEE10), 1, 7, 0, var_sl);
                    sp1C = func_08094484(0x0810548C, 0x08105498, 0, 0x80, 0x50, 0x2CF, 0xF, 8, var_sl);
                    var_r5 = 0x1110;
                }
                break;
            case 0x1105:
state_1105:
                var_r0 = 0x080045EE;
                goto block_92;
            case 0x1110:
state_1110:
                displayed_quantity = 0;
                func_08098BB4(0x08004510);
                func_08096F3C();
                {
                    register s32 seven asm("r5") = 7;
                    register u32 *price_base asm("r1") = (u32 *)0x087A2188;
                    register u32 *price_ptr asm("r6");

                    asm volatile("" : "+r"(price_base));
                    {
                        register u32 price_offset asm("r0") = var_r7 * 4;

                        price_ptr = (u32 *)(price_offset + (u32)price_base);
                    }
                do {
                    var_r8 = func_080B684C(var_r8, var_r9);
                    if (var_r8 != displayed_quantity) {
                        func_0809844C((u32) var_r8, 2, 0, 2, seven, 0x10, var_sl);
                        func_0809844C(var_r8 * *price_ptr, 7, 0, 2, seven, 0xA, 2);
                        func_080972C8();
                        displayed_quantity = var_r8;
                    }
                    func_080ED17C(1);
                    temp_r1 = *(u16 *)0x0300000E;
                } while (!(3 & temp_r1));
                if (1 & temp_r1) {
                    func_08092E84(0x3E);
                    var_r5 = 0x1120;
                } else {
                    func_08098BB4(0x080044A1);
                    func_08094554(sp1C);
                    func_08092E84(0x3F);
                    var_r5 = 0x1010;
                }
                }
                break;
            case 0x1120:
state_1120:
                func_08098BB4(0x08004528);
                func_08098BB4(0x080044A4);
                if ((*(u8 *)0x0200A882 == 1) && (*(u8 *)0x0200A880 == 0)) {
                    var_r5 = 0x1130;
                } else {
                    func_08098BB4(0x080044BD);
                    var_r5 = 0x1110;
                }
                break;
            case 0x1130:
state_1130:
                {
                    register u32 *price_base asm("r1") = (u32 *)0x087A2188;

                    asm volatile("" : "+r"(price_base));
                    {
                        register u32 price_address asm("r0") = var_r7 * 4;

                        price_address += (u32)price_base;
                        func_080E5E90(var_r8 * *(s32 *)price_address);
                    }
                }
                func_080E5D6C(var_r7, (u8)var_r8);
                func_0809844C(*(u32 *)0x020282E8, 7, 0, 2, 1, 1, var_sl);
                func_0809844C((u32) M2C_FIELD(var_r7, u8 *, 0x020217F4), 2, 0, 2, 6, 0xA, var_sl);
                func_08098BB4(0x080044BD);
                func_08098BB4(0x080044A1);
                func_08094554(sp1C);
                var_r0 = 0x08004544;
block_92:
                func_08098BB4(var_r0);
                var_r5 = 0x1010;
                break;
            case 0x2000:
state_2000:
                func_08098BB4(0x08004427);
                sp18 = 0;
                goto block_127;
            case 0x2010:
state_2010:
                var_r4_3 = 0;
                if ((u32)var_r4_3 < (u32)*(u8 *)0x020322B1) {
                    register s32 *message_table asm("r5") = (s32 *)0x087EEE10;

loop_2010:
                    func_080988C8(4, message_table[M2C_FIELD(var_r4_3, u8 *, 0x020322A8)]);
                    var_r4_3 = (u8)(var_r4_3 + 1);
                    if ((u32)var_r4_3 < (u32)*(u8 *)0x020322B1) {
                        goto loop_2010;
                    }
                }
                {
                    register u8 *slot_base asm("r0") = (u8 *)0x020322A8;
                    register u32 selected_index asm("r1") = sp18;

                    asm volatile("add %0, %1, %0"
                                 : "+r"(slot_base) : "r"(selected_index));
                    var_r7 = *slot_base;
                }
                var_r5 = 0x2020;
                break;
            case 0x2020:
state_2020:
                func_08098BB4(0x08004588);
loop_100:
                func_080986B4(5);
                {
                    register s32 *name_base asm("r0") = (s32 *)0x087EEE38;

                    asm volatile("" : "+r"(name_base));
                temp_r4_3 = var_r7 * 4;
                func_08098248(*(s32 *)(temp_r4_3 + (u32)name_base), 0, 5);
                }
                func_080981F0(0x08106568, 0, 5, 0, 8);
                func_080984C4((u32) M2C_FIELD(temp_r4_3, u32 *, 0x087A2188) >> 1, 6, 0, 2, 5);
                func_08098248(0x08106578, 0, 5);
                func_0809844C((u32) M2C_FIELD(var_r7, u8 *, 0x020217F4), 2, 0, 2, 6, 0xA, var_sl);
                func_08098BB4(0x0800446E);
                temp_r0_2 = *(u8 *)0x0200A882;
                if (temp_r0_2 == 0) {
                    register u8 *slot_base asm("r1") = (u8 *)0x020322A8;
                    register u32 slot_address asm("r0");

                    asm volatile("" : "+r"(slot_base));
                    slot_address = *(u8 *)0x0200A880;
                    asm volatile("add %0, %0, %1"
                                 : "+r"(slot_address) : "r"(slot_base));
                    var_r7 = *(u8 *)slot_address;
                    goto loop_100;
                }
                if (temp_r0_2 == 1) {
                    sp18 = *(u8 *)0x0200A880;
                    var_r5 = 0x2100;
                } else {
                    var_r0_2 = 0x08004472;
                    goto block_123;
                }
                break;
            case 0x2100:
state_2100:
                func_08098BB4(0x08004479);
                {
                    register s32 *message_base asm("r1") = (s32 *)0x087EEE10;

                    asm volatile("" : "+r"(message_base));
                    {
                        register u32 message_offset asm("r0") = var_r7 * 4;

                        func_080981F0(*(s32 *)(message_offset + (u32)message_base), 1, 7, 0, var_sl);
                    }
                }
                var_r8 = 1;
                var_r9 = M2C_FIELD(var_r7, u8 *, 0x020217F4);
                sp1C = func_08094484(0x0810548C, 0x08105498, 0, 0x80, 0x50, 0x2CF, 0xF, 8, var_sl);
                var_r5 = 0x2110;
                break;
            case 0x2110:
state_2110:
                displayed_quantity = 0;
                func_08098BB4(0x080045AE);
                func_08096F3C();
                {
                    register s32 seven asm("r5") = 7;
                    register u32 *price_base asm("r1") = (u32 *)0x087A2188;
                    register u32 *price_ptr asm("r6");

                    asm volatile("" : "+r"(price_base));
                    {
                        register u32 price_offset asm("r0") = var_r7 * 4;

                        price_ptr = (u32 *)(price_offset + (u32)price_base);
                    }
                do {
                    var_r8 = func_080B684C(var_r8, var_r9);
                    if (var_r8 != displayed_quantity) {
                        func_0809844C((u32) var_r8, 2, 0, 2, seven, 0x10, var_sl);
                        func_0809844C(var_r8 * (*price_ptr >> 1), 7, 0, 2, seven, 0xA, 2);
                        func_080972C8();
                        displayed_quantity = var_r8;
                    }
                    func_080ED17C(1);
                    temp_r1_2 = *(u16 *)0x0300000E;
                } while (!(3 & temp_r1_2));
                if (1 & temp_r1_2) {
                    func_08092E84(0x3E);
                    var_r5 = 0x2120;
                } else {
                    func_08098BB4(0x080044A1);
                    func_08094554(sp1C);
                    func_08092E84(0x3F);
                    var_r5 = 0x2020;
                }
                }
                break;
            case 0x2120:
state_2120:
                func_08098BB4(0x08004528);
                func_08098BB4(0x080044A4);
                if ((*(u8 *)0x0200A882 == 1) && (*(u8 *)0x0200A880 == 0)) {
                    var_r5 = 0x2130;
                } else {
                    func_08098BB4(0x080044BD);
                    var_r5 = 0x2110;
                }
                break;
            case 0x2130:
state_2130:
                {
                    register u32 *price_base asm("r1") = (u32 *)0x087A2188;

                    asm volatile("" : "+r"(price_base));
                    {
                        register u32 price_address asm("r0") = var_r7 * 4;

                        price_address += (u32)price_base;
                        func_080E5E64(var_r8 * (*(u32 *)price_address >> 1));
                    }
                }
                func_080E5D98(var_r7, (u8)var_r8);
                func_0809844C(*(u32 *)0x020282E8, 7, 0, 2, 1, 1, var_sl);
                func_0809844C((u32) M2C_FIELD(var_r7, u8 *, 0x020217F4), 2, 0, 2, 6, 0xA, var_sl);
                func_08098BB4(0x080044BD);
                func_08098BB4(0x080044A1);
                func_08094554(sp1C);
                func_08098BB4(0x08004544);
                func_080B654C();
                temp_r0_3 = *(u8 *)0x020322B1;
                if (temp_r0_3 != 0) {
                    goto case2130_nonempty;
                }
                func_08098BB4(0x08004472);
                var_r0_2 = 0x080045C6;
block_123:
                func_08098BB4(var_r0_2);
                var_r5 = 0;
                break;
case2130_nonempty:
                if (temp_r0_3 == sp18) {
                    sp18 = (u8) (sp18 - 1);
                }
                func_08098834(4);
block_127:
                var_r5 = 0x2010;
                break;
            }
            }
state_done:
            ;
        } while (*(s32 *)0x02021690 == 5);
    }
    goto loop_132;
block_132:
    func_080ED17C(1);
loop_132:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_132;
    }
    if (*(u8 *)0x02030664 == 2) {
        *(u8 *)0x02030664 = 1;
        func_080ED17C(1);
    }
}
