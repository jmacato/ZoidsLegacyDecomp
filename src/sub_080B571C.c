#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094098();                                /* extern */
s32 func_080940AC();                                /* extern */
s32 func_080940C0();                                /* extern */
s32 func_080940D4();                                /* extern */
s32 func_080940E8();                                /* extern */
s32 func_080940FC();                                /* extern */
M2C_UNK func_08094330();                            /* extern */
s32 *func_08094484(M2C_UNK, M2C_UNK, u8, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
s32 *func_08094484_4(M2C_UNK, M2C_UNK, s32, s32);   /* extern */
M2C_UNK func_08094554(s32 *);                       /* extern */
M2C_UNK func_08094564(s32 *, u8);                   /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, M2C_UNK, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_0809538C_4, func_0809538C");
M2C_UNK func_0809538C_4(s32, M2C_UNK, s32, s32);    /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
void *func_0809716C(s32);                           /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_0809844C(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809AB44(s32, s32, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_080AC0C8();                            /* extern */
M2C_UNK func_080ADD38();                            /* extern */
s32 func_080AF924();                                /* extern */
M2C_UNK func_080B0980();                            /* extern */
M2C_UNK func_080B0D38();                            /* extern */
u8 func_080B2108();                                 /* extern */
M2C_UNK func_080B35D4(s32);                         /* extern */
M2C_UNK func_080B56CC();                            /* extern */
M2C_UNK func_080B654C();                            /* extern */
M2C_UNK func_080C0AFC();                            /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
asm(".set D_02021699_b571c, 0x02021699");
asm(".set D_0202169A_b571c, 0x0202169A");
asm(".set D_0202169B_b571c, 0x0202169B");
asm(".set D_0202169C_b571c, 0x0202169C");
asm(".set D_0202169D_b571c, 0x0202169D");
asm(".set D_0202169E_b571c, 0x0202169E");
extern u8 D_02021699_b571c;
extern u8 D_0202169A_b571c;
extern u8 D_0202169B_b571c;
extern u8 D_0202169C_b571c;
extern u8 D_0202169D_b571c;
extern u8 D_0202169E_b571c;
extern u8 D_0202ECF4[];

asm(
    ".set B571C_MOV_COUNT, 0\n"
    ".macro B571C_INSTALL_MOV\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".set B571C_MOV_COUNT, B571C_MOV_COUNT + 1\n"
    ".if B571C_MOV_COUNT == 19\n"
    ".short 0x2600\n"
    ".elseif B571C_MOV_COUNT == 51\n"
    ".short 0x2401\n"
    ".elseif B571C_MOV_COUNT == 53\n"
    ".short 0x2201\n"
    ".elseif B571C_MOV_COUNT == 54\n"
    ".short 0x2501\n"
    ".else\n"
    "mov \\args\n"
    ".endif\n"
    ".if B571C_MOV_COUNT < 54\n"
    "B571C_INSTALL_MOV\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_MOV\n"
    ".set B571C_STR_COUNT, 0\n"
    ".macro B571C_INSTALL_STR\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    ".set B571C_STR_COUNT, B571C_STR_COUNT + 1\n"
    ".if B571C_STR_COUNT == 8\n"
    ".short 0x9606\n"
    ".else\n"
    "str \\args\n"
    ".endif\n"
    ".if B571C_STR_COUNT < 8\n"
    "B571C_INSTALL_STR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_STR\n"
    ".set B571C_ADD_COUNT, 0\n"
    ".macro B571C_INSTALL_ADD\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    ".set B571C_ADD_COUNT, B571C_ADD_COUNT + 1\n"
    ".if B571C_ADD_COUNT == 3\n"
    ".short 0x1888\n"
    ".elseif B571C_ADD_COUNT == 6\n"
    ".short 0x1C20\n"
    ".elseif B571C_ADD_COUNT == 7\n"
    ".short 0x1C60\n"
    ".elseif B571C_ADD_COUNT == 9\n"
    ".short 0x18C1\n"
    ".elseif B571C_ADD_COUNT == 13\n"
    ".short 0x1C28\n"
    ".elseif B571C_ADD_COUNT == 14\n"
    ".short 0x1C50\n"
    ".else\n"
    "add \\args\n"
    ".endif\n"
    ".if B571C_ADD_COUNT < 14\n"
    "B571C_INSTALL_ADD\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_ADD\n"
    ".set B571C_LDR_COUNT, 0\n"
    ".macro B571C_INSTALL_LDR\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    ".set B571C_LDR_COUNT, B571C_LDR_COUNT + 1\n"
    ".if B571C_LDR_COUNT == 14\n"
    ".short 0x6800\n"
    ".elseif B571C_LDR_COUNT == 27\n"
    ".short 0x4B1C\n"
    ".else\n"
    "ldr \\args\n"
    ".endif\n"
    ".if B571C_LDR_COUNT < 27\n"
    "B571C_INSTALL_LDR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_LDR\n"
    ".set B571C_LSR_COUNT, 0\n"
    ".macro B571C_INSTALL_LSR\n"
    ".macro lsr args:vararg\n"
    ".purgem lsr\n"
    ".set B571C_LSR_COUNT, B571C_LSR_COUNT + 1\n"
    ".if B571C_LSR_COUNT == 1\n"
    ".short 0x0E04\n"
    ".elseif B571C_LSR_COUNT == 2\n"
    ".short 0x0E02\n"
    ".else\n"
    "lsr \\args\n"
    ".endif\n"
    ".if B571C_LSR_COUNT < 2\n"
    "B571C_INSTALL_LSR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_LSR\n"
    ".set B571C_CMP_COUNT, 0\n"
    ".macro B571C_INSTALL_CMP\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    ".set B571C_CMP_COUNT, B571C_CMP_COUNT + 1\n"
    ".if B571C_CMP_COUNT == 19\n"
    ".short 0x2CCE\n"
    ".elseif B571C_CMP_COUNT == 23\n"
    ".short 0x2800\n"
    ".elseif B571C_CMP_COUNT == 24\n"
    ".short 0x2A34\n"
    ".elseif B571C_CMP_COUNT == 25\n"
    ".short 0x2CCE\n"
    ".elseif B571C_CMP_COUNT == 26\n"
    ".short 0x2A34\n"
    ".else\n"
    "cmp \\args\n"
    ".endif\n"
    ".if B571C_CMP_COUNT < 26\n"
    "B571C_INSTALL_CMP\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_CMP\n"
    ".set B571C_LSL_COUNT, 0\n"
    ".macro B571C_INSTALL_LSL\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    ".set B571C_LSL_COUNT, B571C_LSL_COUNT + 1\n"
    ".if B571C_LSL_COUNT == 15\n"
    ".short 0x00E0\n"
    ".elseif B571C_LSL_COUNT == 17\n"
    ".short 0x0190\n"
    ".else\n"
    "lsl \\args\n"
    ".endif\n"
    ".if B571C_LSL_COUNT < 17\n"
    "B571C_INSTALL_LSL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_LSL\n"
    ".set B571C_SUB_COUNT, 0\n"
    ".macro B571C_INSTALL_SUB\n"
    ".macro sub args:vararg\n"
    ".purgem sub\n"
    ".set B571C_SUB_COUNT, B571C_SUB_COUNT + 1\n"
    ".if B571C_SUB_COUNT == 1\n"
    ".short 0x1B00\n"
    ".else\n"
    "sub \\args\n"
    ".endif\n"
    ".if B571C_SUB_COUNT < 1\n"
    "B571C_INSTALL_SUB\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_SUB\n"
    ".set B571C_AND_COUNT, 0\n"
    ".macro B571C_INSTALL_AND\n"
    ".macro and args:vararg\n"
    ".purgem and\n"
    ".set B571C_AND_COUNT, B571C_AND_COUNT + 1\n"
    ".if B571C_AND_COUNT == 2\n"
    ".short 0x4008\n"
    ".else\n"
    "and \\args\n"
    ".endif\n"
    ".if B571C_AND_COUNT < 2\n"
    "B571C_INSTALL_AND\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "B571C_INSTALL_AND\n");

void sub_080B571C(void) {
    s32 sp18;
    s32 *var_r7;
    register s32 *var_r8 asm("r8");
    register s32 *var_r9 asm("r9");
    register s32 *var_sl asm("sl");
    s32 temp_r0;
    s32 temp_r0_2;
    register s32 window_flags asm("r6");
    register s32 initial_record_offset asm("r2");
    register s32 *initial_record_base asm("r1");
    register s32 var_r0 asm("r0");
    register s32 var_r4 asm("r4");
    s32 *var_r5;
    s32 *var_r6;
    u16 var_r1;
    u8 temp_r1_3;
    register s32 temp_r2 asm("r2");
    u8 var_r2;
    u8 var_r4_2;
    u8 var_r4_3;
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r2_2;
    void *temp_r3;
    u8 *first_record;
    u32 first_active;
    s32 slot_base;
    s32 slot_mask;
    s32 slot_address;
    s32 slot_offset;
    s32 state_100;
    register s32 rebuild_height asm("r5");
    register s32 rebuild_flags asm("r6");
    register s32 third_window_eight asm("r2");
    register u8 *menu_input_base asm("r0");
    register u8 *menu_input_address asm("r3");
    register s32 menu_input_value asm("r1");

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    *(s16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_080ECD34(0x08104258, 0x0600AB80);
    func_080ECD34(0x081046A8, 0x06015840);
    func_0809AB44(2, 0, 0x1EF, 4, 4);
    func_08094330();
    func_08096308(0xF, 0x10);
    sp18 = 0;
    var_r4 = 0;
    if (*(s32 *)0x02021690 == 4) {
        goto loop_2;
    }
    goto loop_124;
loop_2:
    if (var_r4 != 0x3000) {
        goto block_4;
    }
    goto block_81;
block_4:
    if (var_r4 > 0x3000) {
        goto block_17;
    }
    state_100 = 0x100;
    asm volatile("" : "+r"(state_100));
    if (var_r4 != state_100) {
        goto block_7;
    }
    goto block_59;
block_7:
    if (var_r4 > state_100) {
        goto block_12;
    }
    if (var_r4 == 0) {
        goto block_34;
    }
    if (var_r4 != 0x10) {
        goto block_11;
    }
    goto block_54;
block_11:
    goto block_119;
block_12:
    if (var_r4 != 0x1000) {
        goto block_14;
    }
    goto block_73;
block_14:
    if (var_r4 != 0x2000) {
        goto block_16;
    }
    goto block_76;
block_16:
    goto block_119;
block_17:
    if (var_r4 != 0x6000) {
        goto block_19;
    }
    goto block_85;
block_19:
    if (var_r4 > 0x6000) {
        goto block_25;
    }
    if (var_r4 != 0x4000) {
        goto block_22;
    }
    goto block_82;
block_22:
    if (var_r4 != 0x5000) {
        goto block_24;
    }
    goto block_83;
block_24:
    goto block_119;
block_25:
    if (var_r4 != 0x8000) {
        goto block_27;
    }
    goto block_89;
block_27:
    if (var_r4 > 0x8000) {
        goto block_31;
    }
    if (var_r4 != 0x7000) {
        goto block_30;
    }
    goto block_87;
block_30:
    goto block_119;
block_31:
    if (var_r4 != 0x9000) {
        goto block_33;
    }
    goto block_92;
block_33:
    goto block_119;
block_34:
    func_08098BB4(0x08000E6E);
    M2C_FIELD(func_0809716C(0), u8 *, 0x16) = *(u8 *)0x02032A84;
    initial_record_base = (s32 *)0x020218E4;
    initial_record_offset = 0x6A04;
    asm volatile("" : "+r"(initial_record_base), "+r"(initial_record_offset));
    func_0809844C(*(s32 *)((u8 *)initial_record_base + initial_record_offset), 7, 0, 2, 2, 1, var_r4);
    func_080AC0C8();
    {
        register s32 *out_args asm("sp");

        out_args[0] = 0x8C;
        out_args[1] = 0x2EA;
        window_flags = 0xF;
        out_args[2] = window_flags;
        out_args[3] = 0x20;
        out_args[4] = var_r4;
        var_r9 = func_08094484_4(0x08105724, 0x08105758, 0, 0xA0);
    }
    {
        register s32 *out_args asm("sp");
        register s32 call_r2 asm("r2");
        register s32 second_window_eight asm("r1");
        register u8 *second_window_base asm("r0") = (u8 *)0x020218E4;

        asm volatile("" : "+r"(second_window_base));
        call_r2 = *second_window_base;

        out_args[0] = 0x68;
        out_args[1] = 0x336;
        out_args[2] = window_flags;
        second_window_eight = 8;
        asm volatile("" : "+r"(second_window_eight));
        out_args[3] = second_window_eight;
        out_args[4] = var_r4;
        var_r7 = func_08094484_4(0x081059D4, 0x081059EC, call_r2, 0xB8);
    }
    {
        register s32 *out_args asm("sp");

        out_args[0] = 0x98;
        out_args[1] = 0x343;
        out_args[2] = window_flags;
        third_window_eight = 8;
        asm volatile("" : "+r"(third_window_eight));
        out_args[3] = third_window_eight;
        out_args[4] = var_r4;
    var_r8 = func_08094484_4(0x08105A20, 0x08105A2C, 0, 0xD8);
    }
    var_r4_2 = 1;
    asm volatile("" : "+r"(var_r4_2));
    first_record = (u8 *)0x020218E4;
    asm volatile("" : "+r"(first_record));
    first_record += 0x70;
    first_active = *(volatile u8 *)(first_record + 4);
    if (first_active == 0) {
        goto loop_37;
    }
    var_r1 = M2C_FIELD(first_record, u16 *, 8);
    temp_r0 = var_r4_2;
    goto block_40;
loop_37:
    var_r4_2 += 1;
    if ((u32) var_r4_2 > 0xCEU) {
        goto block_41;
    }
    temp_r1 = (var_r4_2 * 0x70) + 0x020218E4;
    if (M2C_FIELD(temp_r1, u8 *, 4) == 0) {
        goto loop_37;
    }
    var_r1 = M2C_FIELD(temp_r1, u16 *, 8);
    temp_r0 = 1;
block_40:
    if (!(temp_r0 & var_r1)) {
        goto loop_37;
    }
block_41:
    var_r2 = 1;
    slot_base = 0x020218E4;
    slot_mask = 1;
loop_42:
    slot_address = (var_r2 << 6) + slot_base;
    slot_offset = 0x5A94;
    if (*(u8 *)(slot_address + slot_offset) == 0) {
        goto block_44;
    }
    slot_offset += 2;
    var_r1 = *(u16 *)(slot_address + slot_offset);
    {
        register s32 slot_test asm("r0") = slot_mask;
        asm volatile("" : "+r"(slot_test));
        if (slot_test & var_r1) {
            goto block_45;
        }
    }
block_44:
    var_r2 += 1;
    if ((u32) var_r2 <= 0x34U) {
        goto loop_42;
    }
block_45:
    if ((u32) var_r4_2 <= 0xCEU) {
        goto block_47;
    }
    if ((u32) var_r2 > 0x34U) {
        goto block_48;
    }
block_47:
    {
        register s32 *out_args asm("sp");

        out_args[0] = 0xC;
        out_args[1] = 0x2C4;
        out_args[2] = 0xF;
        out_args[3] = 0x200108;
        out_args[4] = 0;
        var_sl = func_08094484_4(0x081053EC, 0x081053F8, 0, 0x30);
    }
block_48:
    temp_r0 = *(u8 *)0x02032A85;
    var_r4 = 0x100;
    if (temp_r0 == 1) {
        goto block_50;
    }
    goto block_119;
block_50:
    {
        register s32 saved_ready asm("r1") = sp18;
        asm volatile("" : "+r"(saved_ready));
        if (saved_ready == 0) {
            goto block_52;
        }
    }
    goto block_119;
block_52:
    var_r4 = 0x10;
    goto block_119;
block_54:
    func_080972C8();
    goto loop_56;
block_55:
    func_080ED17C(1);
loop_56:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_55;
    }
    {
        register s32 *handle asm("r2") = var_r9;
        *handle |= 0x20000;
    }
    *var_r7 |= 0x20000;
    {
        register s32 *handle asm("r6") = var_r8;
        *handle |= 0x20000;
    }
    {
        register s32 *handle asm("r2") = var_sl;
        *handle |= 0x20000;
    }
    func_080B56CC();
    {
        register s32 *handle asm("r6") = var_r9;
        *handle &= 0xFFFDFFFF;
    }
    *var_r7 &= 0xFFFDFFFF;
    {
        register s32 *handle asm("r2") = var_r8;
        *handle &= 0xFFFDFFFF;
    }
    {
        register s32 *handle asm("r6") = var_sl;
        *handle &= 0xFFFDFFFF;
    }
    sp18 = 1;
    goto block_118;
block_59:
    func_08098BB4(0x08000F02);
    temp_r2 = *(u8 *)0x0200A882;
    if (temp_r2 == 1) {
        goto block_66;
    }
    if ((s32) temp_r2 > 1) {
        goto block_63;
    }
    if (temp_r2 == 0) {
        goto block_65;
    }
    goto block_119;
block_63:
    if (temp_r2 == 2) {
        goto block_72;
    }
    goto block_119;
block_65:
    {
        register u8 *toggle_read asm("r1") = (u8 *)0x020218E4;
        register u8 *toggle_write asm("r2");
        register s32 toggle_value asm("r0");

        asm volatile("" : "+r"(toggle_read));
        toggle_value = *toggle_read ^ 1;
        asm volatile("" : "+r"(toggle_value));
        toggle_write = (u8 *)0x020218E4;
        asm volatile("" : "+r"(toggle_write));
        *toggle_write = (u8)toggle_value;
        func_08094564(var_r7, *toggle_write);
    }
    func_080AC0C8();
    goto block_119;
block_66:
    menu_input_base = (u8 *)0x0200A880;
    menu_input_value = *menu_input_base;
    menu_input_address = menu_input_base;
    asm volatile("" : "+r"(menu_input_address), "+r"(menu_input_value));
    if (menu_input_value != 8) {
        goto block_71;
    }
    if (*(u8 *)0x02030664 != 0) {
        goto block_69;
    }
    temp_r2 &= D_0202ECF4[0x21];
    if (temp_r2 == 0) {
        goto block_71;
    }
block_69:
    func_08098BB4(0x08003519);
    goto block_119;
block_71:
    {
        register u8 *selected_dest asm("r1") = (u8 *)0x02032A84;
        register s32 selected_value asm("r0");

        asm volatile("" : "+r"(selected_dest));
        selected_value = *menu_input_address;
        asm volatile("" : "+r"(selected_value));
        *selected_dest = (u8)selected_value;
    }
    {
        register s32 next_state asm("r0");
        next_state = *menu_input_address;
        next_state += 1;
        var_r4 = (u16)(next_state << 0xC);
    }
    goto block_119;
block_72:
    *(s32 *)0x02021690 = 3;
    func_08096308(0x10, 0x10);
    goto block_119;
block_73:
    func_08094554(var_r9);
    func_08094554(var_r7);
    func_08094554(var_r8);
    func_08094554(var_sl);
    func_08098BB4(0x08000F06);
    func_080ADD38();
block_74:
    var_r4 = 0;
    goto block_119;
block_76:
    func_080B654C();
    if (*(u8 *)0x020322B1 == 0) {
        goto block_79;
    }
    func_08094554(var_r9);
    func_08094554(var_r7);
    func_08094554(var_r8);
    func_08094554(var_sl);
    func_08098BB4(0x08000F06);
    if ((func_080AF924() << 0x18) == 0) {
        goto block_74;
    }
    *(s32 *)0x02021690 = 3;
    goto block_90;
block_79:
    func_08098BB4(0x08001CF6);
    var_r4 = state_100;
    goto block_119;
block_81:
    func_08094554(var_r9);
    func_08094554(var_r7);
    func_08094554(var_r8);
    func_08094554(var_sl);
    func_08098BB4(0x08000F06);
    func_080B0980();
    goto block_74;
block_82:
    func_08094554(var_r9);
    func_08094554(var_r7);
    func_08094554(var_r8);
    func_08094554(var_sl);
    func_08098BB4(0x08000F06);
    func_080B0D38();
    goto block_74;
block_83:
    func_08094554(var_r9);
    func_08094554(var_r7);
    func_08094554(var_r8);
    func_08094554(var_sl);
    func_08098BB4(0x08000F06);
    if (func_080B2108() != 2) {
        goto block_74;
    }
    func_080972C8();
    func_080ED17C(1);
    func_080B35D4(0);
    asm volatile("");
    goto block_74;
block_85:
    func_08094554(var_r9);
    func_08094554(var_r7);
    func_08094554(var_r8);
    func_08094554(var_sl);
    func_08098BB4(0x08000F06);
    func_080B35D4(0);
    goto block_74;
block_87:
    func_08094554(var_r9);
    func_08094554(var_r7);
    func_08094554(var_r8);
    func_08094554(var_sl);
    {
        register s32 *out_args asm("sp");
        register s32 first_eight asm("r0");
        register s32 second_eight asm("r1");

        rebuild_height = 0x98;
        out_args[0] = rebuild_height;
        out_args[1] = 0x38F;
        rebuild_flags = 0xF;
        out_args[2] = rebuild_flags;
        first_eight = 8;
        asm volatile("" : "+r"(first_eight));
        out_args[3] = first_eight;
        var_r4 = 0;
        out_args[4] = var_r4;
        var_r7 = func_08094484_4(0x08105DA4, 0x08105DB0, 0, 0x88);

        out_args[0] = rebuild_height;
        out_args[1] = 0x343;
        out_args[2] = rebuild_flags;
        second_eight = 8;
        asm volatile("" : "+r"(second_eight));
        out_args[3] = second_eight;
        out_args[4] = var_r4;
        var_r8 = func_08094484_4(0x08105A20, 0x08105A2C, 0, 0xD8);
    }
    func_08098BB4(0x08000F06);
    func_080C0AFC();
    func_08094554(var_r7);
    func_08094554(var_r8);
    goto block_119;
block_89:
    {
        register s32 *mode_address asm("r0") = (s32 *)0x02021690;
        register s32 mode_value asm("r2") = 0xF;
        asm volatile("" : "+r"(mode_address), "+r"(mode_value));
        *mode_address = mode_value;
    }
    *(s8 *)0x02032E5C = 1;
block_90:
    func_08096308(0x10, 0);
    goto block_119;
block_92:
    func_08098BB4(0x080033A6);
    if (*(u8 *)0x0200A882 == 1) {
        goto block_94;
    }
    goto block_118;
block_94:
    temp_r1_3 = *(u8 *)0x0200A880;
    if (temp_r1_3 == 0) {
        goto block_96;
    }
    goto block_118;
block_96:
    if (*(u8 *)0x0202169C != 1) {
        goto block_100;
    }
    if (*(u8 *)0x0202169D != 1) {
        goto block_100;
    }
    if (*(u8 *)0x0202169E != 1) {
        goto block_100;
    }
    {
        register s32 *out_args asm("sp");
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        out_args[0] = temp_r1_3;
        out_args[1] = temp_r1_3;
        out_args[2] = 0x2F;
        out_args[3] = 0x3F;
        call_r0 = 1;
        asm volatile("" : "+r"(call_r0));
        call_r1 = 0x70D8;
        call_r2 = 0x2080;
        call_r3 = 0;
        asm volatile("" : "+r"(call_r1), "+r"(call_r2), "+r"(call_r3));
        func_0809538C_4(call_r0, call_r1, call_r2, call_r3);
    }
    func_08098BB4(0x080033CC);
    func_0809534C();
    func_080972C8();
    func_080ED17C(1);
block_100:
    if (*(u8 *)0x0200A882 == 1) {
        goto block_102;
    }
    goto block_118;
block_102:
    if (*(u8 *)0x0200A880 == 0) {
        goto block_104;
    }
    goto block_118;
block_104:
    func_08098BB4(0x0800341E);
    var_r4_3 = 0;
    var_r5 = (s32 *)0x087A1B98;
    var_r6 = var_r5 + 1;
loop_105:
    temp_r0 = var_r4_3 * 0x48;
    temp_r2_2 = temp_r0 + 0x020325A0;
    temp_r0_2 = var_r4_3 * 0x14;
    temp_r3 = temp_r0_2 + 0x0202ED2C;
    M2C_FIELD(temp_r0_2, s32 *, 0x0202ED2C) = (s32) M2C_FIELD(temp_r0, s32 *, 0x020325A0);
    M2C_FIELD(temp_r3, u8 *, 4) = (u8) M2C_FIELD(temp_r2_2, u8 *, 4);
    M2C_FIELD(temp_r3, u8 *, 5) = (u8) M2C_FIELD(temp_r2_2, u8 *, 5);
    M2C_FIELD(temp_r3, u16 *, 6) = (u16) M2C_FIELD(temp_r2_2, u16 *, 6);
    if (M2C_FIELD(temp_r2_2, u16 *, 6) == 4) {
        goto block_108;
    }
    M2C_FIELD(temp_r3, s32 *, 8) = (s32) M2C_FIELD(temp_r2_2, s32 *, 8);
    var_r0 = M2C_FIELD(temp_r2_2, s32 *, 0xC);
    goto block_109;
block_108:
    M2C_FIELD(temp_r3, s32 *, 8) = (s32) (M2C_FIELD(temp_r2_2, s32 *, 8) - (var_r5[M2C_FIELD(temp_r2_2, u8 *, 0x1A) * 2] * 0x10));
    {
        register s32 second_delta asm("r1");
        second_delta = var_r6[M2C_FIELD(temp_r2_2, u8 *, 0x1A) * 2];
        second_delta *= 0x10;
        asm volatile("" : "+r"(second_delta));
        var_r0 = M2C_FIELD(temp_r2_2, s32 *, 0xC);
        var_r0 -= second_delta;
    }
block_109:
    M2C_FIELD(temp_r3, s32 *, 0xC) = var_r0;
    M2C_FIELD(temp_r3, u8 *, 0x10) = (u8) M2C_FIELD(temp_r2_2, u8 *, 0x1A);
    var_r4_3 += 1;
    if ((u32) var_r4_3 <= 0xDU) {
        goto loop_105;
    }
    if ((func_08094098() << 0x18) == 0) {
        goto block_117;
    }
    if ((func_080940AC() << 0x18) == 0) {
        goto block_117;
    }
    if ((func_080940C0() << 0x18) == 0) {
        goto block_117;
    }
    if ((func_080940D4() << 0x18) == 0) {
        goto block_117;
    }
    if ((func_080940E8() << 0x18) == 0) {
        goto block_117;
    }
    if ((func_080940FC() << 0x18) == 0) {
        goto block_117;
    }
    func_08092E84(0x35);
    func_08098BB4(0x0800343E);
    func_08098BB4(0x08003441);
    {
        u8 *status99 = &D_02021699_b571c;
        u8 *status9A = &D_0202169A_b571c;
        u8 *status9B = &D_0202169B_b571c;
        u8 *status9C = &D_0202169C_b571c;
        u8 *status9D = &D_0202169D_b571c;
        u8 *status9E = &D_0202169E_b571c;

        *status9E = 1U;
        *status9D = 1U;
        *status9C = 1U;
        *status9B = 1U;
        *status9A = 1U;
        *status99 = 1U;
    }
    goto block_118;
block_117:
    func_08092E84(0x58);
    func_08098BB4(0x0800343E);
    func_08098BB4(0x08003482);
block_118:
    var_r4 = 0x100;
block_119:
    if (*(s32 *)0x02021690 != 4) {
        goto block_121;
    }
    goto loop_2;
block_121:
    goto loop_124;
block_123:
    func_080ED17C(1);
loop_124:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_123;
    }
    return;
}
