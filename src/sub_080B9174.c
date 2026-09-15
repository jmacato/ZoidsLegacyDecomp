#include "m2c_prelude.h"
#define NULL ((void *)0)

struct ItemB9174 {
    u8 pad00[9];
    u8 price_factor;
    u8 pad0A[14];
};

extern volatile u8 D_0200A880;

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, s32, M2C_UNK, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(M2C_UNK, s32, s32, s32, s32); /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C(s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080984C4(s16, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A52C(u8, u8, s32, s32, s32);       /* extern */
M2C_UNK func_080AC214(s32, s32);                    /* extern */
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACB5C(s32);                         /* extern */
M2C_UNK func_080ACBA0(s32);                         /* extern */
M2C_UNK func_080ACBDC(s32, s32);                    /* extern */
M2C_UNK func_080B61C8(s32, s32, s32);               /* extern */
u8 func_080B80CC(u8, u8);                           /* extern */
M2C_UNK func_080B8F44(void *, void *);              /* extern */
M2C_UNK func_080B9080(void *, void *);              /* extern */
u8 func_080E523C(u8);                               /* extern */
asm(".set func_080E523C_price, func_080E523C");
asm(".include \"src/sub_080B9174_fix.inc\"");
s32 func_080E523C_price(u8);                        /* extern */
M2C_UNK func_080E5880(void *, void *);              /* extern */
M2C_UNK func_080E59BC(void *, void *, s32, u8, void *); /* extern */
M2C_UNK func_080E5E90(u32);                         /* extern */
void *func_080E669C();                              /* extern */
M2C_UNK func_080E66B8();                            /* extern */
s32 func_080E7B64(u8);                              /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080B9560();                            /* static */

void sub_080B9174(void) {
    void *sp14;
    s32 sp18;
    void *sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    void *sp2C;
    M2C_UNK var_r0_2;
    s32 *temp_r2_4;
    s32 *temp_r2_5;
    s32 temp_r0_12;
    s32 temp_r0_6;
    s32 temp_r0_9;
    s32 temp_r2;
    register s32 item_slot_r9 asm("r9");
    register volatile u32 *money2_r8 asm("r8");
    register volatile u32 *money3_r6 asm("r6");
    s32 temp_r4_2;
    register s32 var_r6 asm("r6");
    u16 temp_r1;
    u16 temp_r1_2;
    u16 temp_r1_4;
    u16 temp_r1_6;
    register s32 state_1200_r5 asm("r5");
    register s32 dialog_zero_r4 asm("r4");
    register u32 var_r5 asm("r5");
    u32 var_r5_2;
    u32 var_r5_3;
    u8 *temp_r0_5;
    u8 *temp_r1_3;
    u8 *temp_r1_5;
    u8 temp_r0;
    u8 temp_r0_10;
    u8 temp_r0_11;
    u8 temp_r0_13;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_7;
    u8 temp_r0_8;
    s32 temp_r3;
    u8 temp_r4;
    u8 temp_r4_4;
    u8 temp_r4_5;
    u8 temp_r4_6;
    u8 temp_r4_7;
    u8 temp_r5;
    u8 temp_r6;
    u8 temp_r6_2;
    u8 temp_r6_3;
    u8 *temp_r2_2;
    u8 *temp_r2_3;
    u8 *temp_r4_3;
    void *var_r0;
    u8 *var_r7;
    register void *var_sl asm("sl");

    sp14 = func_080E669C();
    func_08098BB4(0x080056E9);
    var_r6 = 0;
loop_1:
    if (var_r6 != 0x3020) {
        goto block_3;
    }
    goto block_106;
block_3:
    if (var_r6 > 0x3020) {
        goto block_30;
    }
    if (var_r6 != 0x1100) {
        goto block_6;
    }
    goto block_71;
block_6:
    if (var_r6 > 0x1100) {
        goto block_18;
    }
    if (var_r6 != 0x1000) {
        goto block_9;
    }
    goto block_59;
block_9:
    if (var_r6 > 0x1000) {
        goto block_13;
    }
    if (var_r6 == 0) {
        goto block_52;
    }
    goto block_183;
block_13:
    if (var_r6 != 0x1010) {
        goto block_15;
    }
    goto block_60;
block_15:
    if (var_r6 != 0x1020) {
        goto block_17;
    }
    goto block_62;
block_17:
    goto block_183;
block_18:
    {
    state_1200_r5 = 0x1200;
    asm volatile("" : "+r"(state_1200_r5));
    if (var_r6 != state_1200_r5) {
        goto block_20;
    }
    goto block_84;
block_20:
    if (var_r6 > state_1200_r5) {
        goto block_25;
    }
    {
        register s32 state_1110_r0 asm("r0") = 0x1110;
        asm volatile("" : "+r"(state_1110_r0));
    if (var_r6 != state_1110_r0) {
        goto block_23;
    }
    goto block_74;
    }
block_23:
    goto block_183;
    }
block_25:
    if (var_r6 != 0x3000) {
        goto block_27;
    }
    goto block_102;
block_27:
    if (var_r6 != 0x3010) {
        goto block_29;
    }
    goto block_104;
block_29:
    goto block_183;
block_30:
    if (var_r6 == 0x4100) {
        goto block_147;
    }
    if (var_r6 > 0x4100) {
        goto block_44;
    }
    if (var_r6 != 0x4000) {
        goto block_34;
    }
    goto block_129;
block_34:
    if (var_r6 > 0x4000) {
        goto block_38;
    }
    if (var_r6 != 0x3100) {
        goto block_37;
    }
    goto block_118;
block_37:
    goto block_183;
block_38:
    if (var_r6 != 0x4010) {
        goto block_40;
    }
    goto block_132;
block_40:
    if (var_r6 != 0x4020) {
        goto block_42;
    }
    goto block_134;
block_42:
    goto block_183;
block_44:
    if (var_r6 == 0x5015) {
        goto block_160;
    }
    if (var_r6 > 0x5015) {
        goto block_49;
    }
    if (var_r6 == 0x5000) {
        goto block_157;
    }
    if (var_r6 == 0x5010) {
        goto block_159;
    }
    goto block_183;
block_49:
    if (var_r6 == 0x5100) {
        goto block_171;
    }
    if (var_r6 == 0x5200) {
        goto block_176;
    }
    goto block_183;
block_52:
    func_08098BB4(0x08005B4B);
    func_08098BB4(0x08005791);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_57;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_56;
    }
    var_r6 = 0x1000;
    goto block_183;
block_56:
    {
        register u32 state_r0 asm("r0") = *(u8 *)0x0200A880;

        state_r0 += 2;
        var_r6 = (s32) (u16) (state_r0 << 0xC);
    }
    goto block_183;
block_57:
    func_08098BB4(0x08005795);
    goto block_184;
block_59:
    func_08098BB4(0x08005821);
    func_080B61C8(0, 0, 0);
    func_080AC214(5, 8);
    func_080ACA8C(5, 1, 1);
    sp20 = 0;
    sp1C = NULL;
    var_r6 = 0x1010;
    goto block_183;
block_60:
    func_08098BB4(0x08005B81);
    var_r6 = 0x1020;
    goto block_183;
block_62:
    {
        register s32 entry_offset_r0 asm("r0") = 0x020321A4;
        register s32 selected_r2 asm("r2") = (s32) sp1C;
        register s32 entry_base_r1 asm("r1");

        asm volatile("" : "+r"(entry_offset_r0), "+r"(selected_r2));
        entry_offset_r0 = *(volatile u8 *)(selected_r2 + entry_offset_r0) * 0x70;
        entry_base_r1 = 0x020218E8;
        asm volatile("" : "+r"(entry_base_r1));
        var_r7 = (u8 *)(entry_offset_r0 + entry_base_r1);
    temp_r0 = M2C_FIELD(var_r7, u8 *, 2);
    if (temp_r0 == 0) {
        goto block_65;
    }
        {
            register s32 palette_offset_r0 asm("r0") = temp_r0 << 6;
            register s32 palette_delta_r3 asm("r3") = 0x5A90;
            asm volatile("" : "+r"(palette_delta_r3));
            entry_base_r1 += palette_delta_r3;
            var_r0 = (void *)(palette_offset_r0 + entry_base_r1);
        }
    goto block_66;
    }
block_65:
    var_r0 = NULL;
block_66:
    var_sl = var_r0;
    func_080B8F44(var_r7, var_sl);
    func_080986B4(7);
    {
        register s32 display_addr_r0 asm("r0");
        register s32 display_base_r1 asm("r1") = 0x020218E4;

        asm volatile("" : "+r"(display_base_r1));
        display_addr_r0 = M2C_FIELD(var_r7, u8 *, 2) << 6;
        display_addr_r0 += display_base_r1;
        display_base_r1 = 0x5A94;
        asm volatile("" : "+r"(display_base_r1));
        display_addr_r0 += display_base_r1;
        func_08098248(func_080E7B64(*(u8 *)display_addr_r0), 0, 7);
    }
    func_080ACBDC(5, sp20);
    func_08098BB4(0x08005860);
    sp1C = (void *) *(u8 *)0x0200A880;
    sp20 = (s32) *(u8 *)0x0200A881;
    temp_r0_2 = *(u8 *)0x0200A882;
    if (temp_r0_2 == 0) {
        goto block_183;
    }
    if (temp_r0_2 != 1) {
        goto block_169;
    }
    asm volatile("B9174_FIX_FLAG_AND");
    temp_r1 = 0xFFFE & M2C_FIELD(var_r7, u16 *, 4);
    M2C_FIELD(var_r7, u16 *, 4) = temp_r1;
    if (!(2 & temp_r1)) {
        goto block_70;
    }
    goto block_146;
block_70:
    var_r6 = 0x1100;
    goto block_183;
block_71:
    func_080B9080(var_r7, var_sl);
block_72:
    var_r6 = 0x1110;
    goto block_183;
block_74:
    func_08098BB4(0x08005BB9);
    func_08098BB4(0x08005883);
    temp_r4_2 = *(u8 *)0x0200A882;
    if (temp_r4_2 != 1) {
        goto block_83;
    }
    temp_r0_3 = D_0200A880;
    sp24 = (s32) temp_r0_3;
    temp_r3 = temp_r0_3 + 4;
    asm volatile("B9174_FIX_SELECTION_INDEX_ADD");
    if (M2C_FIELD((var_r7 + (temp_r3 * 4)), u16 *, 0x52) == 0) {
        goto block_82;
    }
    func_080E59BC(var_r7, var_sl, 0, temp_r3, sp14);
    asm volatile("B9174_FIX_SELECTION_MASK_LOAD");
    temp_r4_2 &= M2C_FIELD(sp14, u16 *, 2);
    if (temp_r4_2 != 0) {
        goto block_80;
    }
    asm volatile("B9174_FIX_SELECTION_PRICE_ADDRESS");
    temp_r2 = sp24 + ((u32) (func_080E523C(M2C_FIELD(var_r7, u8 *, 0)) << 0x18) >> 0x16);
    temp_r4_3 = var_r7 + 0x1E;
    if (*(temp_r4_3 + temp_r2) != 5) {
        goto block_79;
    }
    func_08092E84(0x58);
    func_0809538C(1, 0x28C8, 0x2060, 0, temp_r4_2, temp_r4_2, 0x2F, 0x3F);
    var_r0_2 = 0x08005D7F;
    goto block_167;
block_79:
    var_r6 = state_1200_r5;
    goto block_183;
block_80:
    func_08092E84(0x58);
    func_08098BB4(0x08005D11);
    goto block_183;
block_82:
    func_08092E84(0x58);
    func_08098BB4(0x08005D46);
    goto block_183;
block_83:
    func_08098BB4(0x08005887);
    var_r6 = 0x1010;
    goto block_183;
block_84:
    func_08098BB4(0x0800588A);
    {
        register u32 price_field_r2 asm("r2");
        register u32 unit_price_r0 asm("r0");
        s32 price_index_raw = func_080E523C_price(M2C_FIELD(var_r7, u8 *, 0));

        price_field_r2 = M2C_FIELD(var_r7, u8 *, 0x39);
        asm volatile("B9174_FIX_ITEM_LOOKUP" : "+r"(price_field_r2));
        temp_r2 = sp24 + ((u32) (price_index_raw << 0x18) >> 0x16);
        temp_r4_3 = var_r7 + 0x1E;
        unit_price_r0 = (*(temp_r4_3 + temp_r2) + 1) * 0x1F4;
        var_r5 = price_field_r2;
        var_r5 *= unit_price_r0;
    }
    {
        struct ItemB9174 *item_table = (struct ItemB9174 *)0x087B2524;

        asm volatile("" : "+r"(item_table));
        item_slot_r9 = sp24 + 4;
        temp_r0_4 = item_table[M2C_FIELD((var_r7 + (item_slot_r9 * 4)), u16 *, 0x52)].price_factor;
    }
    sp2C = temp_r4_3;
    if ((u32) temp_r0_4 > 7U) {
        goto block_91;
    }
    switch (temp_r0_4) {                            /* jump table: jtbl_080B9560 */
case 0:
case 6:
    goto block_91;
case 1:
case 2:
    var_r5 *= 2;
    goto block_91;
case 3:
    var_r5 *= 3;
    goto block_91;
case 4:
    var_r5 *= 4;
    goto block_91;
case 5:
    var_r5 *= 6;
    goto block_91;
case 7:
    var_r5 *= 0xC;
    goto block_91;
    }
block_91:
    if (var_r5 <= 0x98967FU) {
        goto block_93;
    }
    var_r5 = 0x98967F;
block_93:
    func_0809844C(var_r5, 7, 0, 0, 9, 8, 0);
    func_08098248(0x08106F04, 0, 9);
    func_08098BB4(0x08005A2E);
    asm volatile("B9174_FIX_FIRST_CONFIRM_FLAGS");
    temp_r6 = *(u8 *)0x0200A882;
    if (temp_r6 == 1) {
        goto block_95;
    }
    goto block_72;
block_95:
    asm volatile("" : : : "r0");
    temp_r4_4 = *(u8 *)0x0200A880;
    if (temp_r4_4 == 0) {
        goto block_97;
    }
    goto block_72;
block_97:
    asm volatile("B9174_FIX_FIRST_MONEY");
    {
        register s32 money_base asm("r0") = 0x020218E4;
        register s32 money_offset asm("r1") = 0x6A04;

        asm volatile("" : "+r"(money_base), "+r"(money_offset));
        money2_r8 = (volatile u32 *)(money_base + money_offset);
    }
    if (*money2_r8 < var_r5) {
        goto block_100;
    }
    func_080972C8();
    func_080ED17C(1);
    func_08098BB4(0x08005A33);
    {
        register s32 *message_table_r1 asm("r1") = (s32 *)0x087EE170;

        asm volatile("B9174_FIX_FIRST_MESSAGE_ADD" : "+r"(message_table_r1));
        func_08098248(message_table_r1[M2C_FIELD((var_r7 + (item_slot_r9 * 4)), u16 *, 0x52)], 1, 9);
    }
    func_08098BB4(0x08005A3B);
    func_080E5E90(var_r5);
    asm volatile("B9174_FIX_FIRST_MONEY_CALL");
    func_0809844C(*money2_r8, 7, 0, 2, (s32) temp_r6, (s32) temp_r6, (s32) temp_r4_4);
    temp_r0_5 = sp2C + (sp24 + ((u32) (func_080E523C(M2C_FIELD(var_r7, u8 *, 0)) << 0x18) >> 0x16));
    *temp_r0_5 += 1;
    func_080E5880(var_r7, var_sl);
    func_080B8F44(var_r7, var_sl);
    goto block_72;
block_100:
    func_08092E84(0x58);
    func_08098BB4(0x08005180);
    goto block_72;
block_102:
    func_08098BB4(0x08005ACE);
    func_080B61C8(0, 0, 0);
    func_080AC214(5, 8);
    func_080ACA8C(5, 1, 1);
    asm volatile("B9174_FIX_ZERO_PAIR");
    sp20 = 0;
    sp1C = NULL;
block_103:
    var_r6 = 0x3010;
    goto block_183;
block_104:
    func_08098BB4(0x08005C69);
    var_r6 = 0x3020;
    asm volatile(
        ".macro bl target\n\t"
        "b \\target\n\t"
        ".purgem bl\n\t"
        ".endm");
    goto block_183;
block_106:
    {
        register s32 entry_offset_r0 asm("r0") = 0x020321A4;

        {
            register s32 selected_r1 asm("r1") = (s32) sp1C;
            asm volatile("" : "+r"(entry_offset_r0), "+r"(selected_r1));
            entry_offset_r0 = *(volatile u8 *)(selected_r1 + entry_offset_r0) * 0x70;
        }
        {
            register s32 entry_base_r1 asm("r1") = 0x020218E8;

            asm volatile("" : "+r"(entry_base_r1));
            var_r7 = (u8 *)(entry_offset_r0 + entry_base_r1);
            temp_r0_7 = M2C_FIELD(var_r7, u8 *, 2);
            if (temp_r0_7 == 0) {
                goto block_108;
            }
            {
                register s32 palette_offset_r0 asm("r0") = temp_r0_7 << 6;
                register s32 palette_delta_r2 asm("r2") = 0x5A90;

                asm volatile("" : "+r"(palette_delta_r2));
                entry_base_r1 += palette_delta_r2;
                var_sl = (void *)(palette_offset_r0 + entry_base_r1);
            }
            goto block_109;
        }
    }
block_108:
    asm volatile("B9174_FIX_NULL_SL");
    var_sl = NULL;
block_109:
    func_080986B4(6);
    func_080981F0(0x08106F08, 0, 6, 0, 0);
    func_080984C4(M2C_FIELD(var_r7, s16 *, 0x40), 4, 0, 0xA, 6);
    temp_r0_8 = func_080E523C(M2C_FIELD(var_r7, u8 *, 0));
    temp_r2_2 = var_r7 + 0x12;
    func_0809844C(*(temp_r0_8 + temp_r2_2), 1, 0, 0xA, 6, 9, 0);
    func_08098248(0x08106F10, 0, 6);
    func_080986B4(7);
    {
        register s32 display_addr_r0 asm("r0");
        register s32 display_delta_r1 asm("r1") = 0x020218E4;
        register s32 display_base_r3 asm("r3");

        asm volatile("" : "+r"(display_delta_r1));
        display_addr_r0 = M2C_FIELD(var_r7, u8 *, 2) << 6;
        display_addr_r0 += display_delta_r1;
        display_base_r3 = 0x5A94;
        asm volatile("" : "+r"(display_base_r3));
        display_addr_r0 += display_base_r3;
        func_08098248(func_080E7B64(*(u8 *)display_addr_r0), 0, 7);
    }
    func_080ACBDC(5, sp20);
    func_08098BB4(0x08005860);
    sp1C = (void *) *(u8 *)0x0200A880;
    sp20 = (s32) *(u8 *)0x0200A881;
    temp_r0_8 = *(u8 *)0x0200A882;
    if (temp_r0_8 != 0) {
        goto block_111;
    }
    goto block_183;
block_111:
    if (temp_r0_8 == 1) {
        goto block_113;
    }
    goto block_169;
block_113:
    asm volatile("B9174_FIX_FLAG_AND");
    temp_r1_2 = 0xFFFE & M2C_FIELD(var_r7, u16 *, 4);
    M2C_FIELD(var_r7, u16 *, 4) = temp_r1_2;
    if (!(2 & temp_r1_2)) {
        goto block_115;
    }
    goto block_146;
block_115:
    if (*(func_080E523C(M2C_FIELD(var_r7, u8 *, 0)) + temp_r2_2) != 2) {
        goto block_117;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08005E00);
    goto block_183;
block_117:
    var_r6 = 0x3100;
    goto block_183;
block_118:
    func_08098BB4(0x0800591E);
    {
        register u32 price_field_r2 asm("r2") = M2C_FIELD(var_r7, u8 *, 0x39);
        register s32 unit_price_r0 asm("r0");

        asm volatile("B9174_FIX_SECOND_PRICE_SCALE" : "+r"(price_field_r2));
        unit_price_r0 = M2C_FIELD((var_r7 + 0x39), s16 *, 7);
        unit_price_r0 *= 0x3E8;
        var_r5_2 = price_field_r2;
        var_r5_2 *= unit_price_r0;
    }
    if (var_r5_2 <= 0x98967FU) {
        goto block_120;
    }
    var_r5_2 = 0x98967F;
block_120:
    func_0809844C(var_r5_2, 7, 0, 0, 9, 8, 0);
    func_08098248(0x08106F04, 0, 9);
    func_08098BB4(0x08005A2E);
    temp_r4_5 = *(u8 *)0x0200A882;
    if (temp_r4_5 == 1) {
        goto block_122;
    }
    goto block_103;
block_122:
    asm volatile("" : : : "r0");
    temp_r6_2 = *(u8 *)0x0200A880;
    if (temp_r6_2 == 0) {
        goto block_124;
    }
    goto block_103;
block_124:
    {
        register s32 money_base asm("r0") = 0x020218E4;
        register s32 money_offset asm("r1") = 0x6A04;

        asm volatile("B9174_FIX_LATER_MONEY" : "+r"(money_base), "+r"(money_offset));
        money2_r8 = (volatile u32 *)(money_base + money_offset);
    }
    if (*money2_r8 < var_r5_2) {
        goto block_127;
    }
    func_080972C8();
    func_080ED17C(1);
    func_08098BB4(0x08005A33);
    {
        register s32 *message_table_r1 asm("r1") = (s32 *)0x087EDD54;

        asm volatile("B9174_FIX_SECOND_MESSAGE_MONEY_CALL" : "+r"(message_table_r1));
        func_08098248(message_table_r1[M2C_FIELD(var_r7, u8 *, 0)], 1, 9);
    }
    func_08098BB4(0x08005A70);
    func_080E5E90(var_r5_2);
    func_0809844C(*money2_r8, 7, 0, 2, (s32) temp_r4_5, (s32) temp_r4_5, (s32) temp_r6_2);
    temp_r0_8 = func_080E523C(M2C_FIELD(var_r7, u8 *, 0));
    temp_r1_3 = var_r7;
    temp_r1_3 += 0x12;
    temp_r1_3 += temp_r0_8;
    *temp_r1_3 += 1;
    func_080E5880(var_r7, var_sl);
    goto block_103;
block_127:
    func_08092E84(0x58);
    func_08098BB4(0x08005180);
    goto block_103;
block_129:
    func_08098BB4(0x08005ACE);
    func_080B61C8(0, 0, 0);
    func_080AC214(5, 8);
    func_080ACA8C(5, 1, 1);
    asm volatile("B9174_FIX_ZERO_SP20");
    sp20 = 0;
    sp1C = NULL;
block_130:
    var_r6 = 0x4010;
    goto block_183;
block_132:
    func_08098BB4(0x08005C9F);
    var_r6 = 0x4020;
    goto block_183;
block_134:
    {
        register s32 entry_offset_r0 asm("r0") = 0x020321A4;

        {
            register s32 selected_r1 asm("r1") = (s32) sp1C;
            asm volatile("" : "+r"(entry_offset_r0), "+r"(selected_r1));
            entry_offset_r0 = *(volatile u8 *)(selected_r1 + entry_offset_r0) * 0x70;
        }
        {
            register s32 entry_base_r1 asm("r1") = 0x020218E8;

            asm volatile("" : "+r"(entry_base_r1));
            var_r7 = (u8 *)(entry_offset_r0 + entry_base_r1);
            temp_r0_10 = M2C_FIELD(var_r7, u8 *, 2);
            if (temp_r0_10 == 0) {
                goto block_136;
            }
            {
                register s32 palette_offset_r0 asm("r0") = temp_r0_10 << 6;
                register s32 palette_delta_r2 asm("r2") = 0x5A90;

                asm volatile("" : "+r"(palette_delta_r2));
                entry_base_r1 += palette_delta_r2;
                var_sl = (void *)(palette_offset_r0 + entry_base_r1);
            }
            goto block_137;
        }
    }
block_136:
    asm volatile("B9174_FIX_NULL_SL");
    var_sl = NULL;
block_137:
    func_080986B4(6);
    func_080981F0(0x08106F14, 0, 6, 0, 0);
    asm volatile("B9174_FIX_S16_FIELD_LOAD");
    func_080984C4(M2C_FIELD(var_r7, s16 *, 0x46), 4, 0, 0xA, 6);
    temp_r0_11 = func_080E523C(M2C_FIELD(var_r7, u8 *, 0));
    asm volatile("B9174_FIX_THIRD_ITEM_POINTER");
    temp_r2_3 = var_r7 + 0x18;
    func_0809844C(*(temp_r0_11 + temp_r2_3), 1, 0, 0xA, 6, 9, 0);
    func_08098248(0x08106ED8, 0, 6);
    func_080986B4(7);
    {
        register s32 display_addr_r0 asm("r0");
        register s32 display_delta_r1 asm("r1") = 0x020218E4;
        register s32 display_base_r3 asm("r3");

        asm volatile("" : "+r"(display_delta_r1));
        display_addr_r0 = M2C_FIELD(var_r7, u8 *, 2) << 6;
        display_addr_r0 += display_delta_r1;
        display_base_r3 = 0x5A94;
        asm volatile("" : "+r"(display_base_r3));
        display_addr_r0 += display_base_r3;
        func_08098248(func_080E7B64(*(u8 *)display_addr_r0), 0, 7);
    }
    func_080ACBDC(5, sp20);
    func_08098BB4(0x08005860);
    sp1C = (void *) *(u8 *)0x0200A880;
    sp20 = (s32) *(u8 *)0x0200A881;
    temp_r0_11 = *(u8 *)0x0200A882;
    if (temp_r0_11 != 0) {
        goto block_139;
    }
    goto block_183;
block_139:
    if (temp_r0_11 == 1) {
        goto block_141;
    }
    goto block_169;
block_141:
    asm volatile("B9174_FIX_FLAG_AND");
    temp_r1_4 = 0xFFFE & M2C_FIELD(var_r7, u16 *, 4);
    M2C_FIELD(var_r7, u16 *, 4) = temp_r1_4;
    if (2 & temp_r1_4) {
        goto block_146;
    }
    if (*(func_080E523C(M2C_FIELD(var_r7, u8 *, 0)) + temp_r2_3) != 5) {
        goto block_145;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08005E4A);
    goto block_183;
block_145:
    var_r6 = 0x4100;
    goto block_183;
block_146:
    func_08092E84(0x58);
    func_08098BB4(0x08005798);
    goto block_183;
block_147:
    func_08098BB4(0x0800598F);
    {
        register u32 price_field_r2 asm("r2") = M2C_FIELD(var_r7, u8 *, 0x39);
        register s32 unit_price_r0 asm("r0");

        asm volatile("B9174_FIX_THIRD_PRICE_SCALE" : "+r"(price_field_r2));
        unit_price_r0 = M2C_FIELD((var_r7 + 0x39), s16 *, 0xD);
        unit_price_r0 *= 0xA;
        var_r5_3 = price_field_r2;
        var_r5_3 *= unit_price_r0;
    }
    if (var_r5_3 <= 0x98967FU) {
        goto block_149;
    }
    var_r5_3 = 0x98967F;
block_149:
    func_0809844C(var_r5_3, 7, 0, 0, 9, 8, 0);
    func_08098248(0x08106F04, 0, 9);
    func_08098BB4(0x08005A2E);
    temp_r4_6 = *(u8 *)0x0200A882;
    if (temp_r4_6 == 1) {
        goto block_151;
    }
    goto block_130;
block_151:
    asm volatile("" : : : "r0");
    temp_r6_3 = *(u8 *)0x0200A880;
    if (temp_r6_3 == 0) {
        goto block_153;
    }
    goto block_130;
block_153:
    {
        register s32 money_base asm("r0") = 0x020218E4;
        register s32 money_offset asm("r1") = 0x6A04;

        asm volatile("B9174_FIX_LATER_MONEY" : "+r"(money_base), "+r"(money_offset));
        money2_r8 = (volatile u32 *)(money_base + money_offset);
    }
    if (*money2_r8 < var_r5_3) {
        goto block_155;
    }
    func_080972C8();
    func_080ED17C(1);
    func_08098BB4(0x08005A33);
    {
        register s32 *message_table_r1 asm("r1") = (s32 *)0x087EDD54;

        asm volatile("B9174_FIX_THIRD_MESSAGE_MONEY_CALL" : "+r"(message_table_r1));
        func_08098248(message_table_r1[M2C_FIELD(var_r7, u8 *, 0)], 1, 9);
    }
    func_08098BB4(0x08005A9B);
    func_080E5E90(var_r5_3);
    func_0809844C(*money2_r8, 7, 0, 2, (s32) temp_r4_6, (s32) temp_r4_6, (s32) temp_r6_3);
    temp_r0_11 = func_080E523C(M2C_FIELD(var_r7, u8 *, 0));
    temp_r1_5 = var_r7;
    temp_r1_5 += 0x18;
    temp_r1_5 += temp_r0_11;
    *temp_r1_5 += 1;
    func_080E5880(var_r7, var_sl);
    goto block_130;
block_155:
    func_08092E84(0x58);
    func_08098BB4(0x08005180);
    goto block_130;
block_157:
    func_08098BB4(0x08005B0C);
    func_080B61C8(0, 0, 0);
    func_080AC214(5, 8);
    func_080ACA8C(5, 1, 1);
    sp18 = func_08094484(0x0821024C, 0x08210258, 0, 0xB8, 0x48, 0, 0, 8, 0);
    asm volatile("B9174_FIX_ZERO_SP20");
    sp20 = 0;
    sp1C = NULL;
    goto block_182;
block_159:
    func_08098BB4(0x08005CD5);
    var_r6 = 0x5015;
block_160:
    {
        register s32 entry_offset_r0 asm("r0") = 0x020321A4;
        register s32 entry_base_r4 asm("r4");

        {
            register s32 selected_r1 asm("r1") = (s32) sp1C;
            asm volatile("" : "+r"(entry_offset_r0), "+r"(selected_r1));
            entry_offset_r0 = *(volatile u8 *)(selected_r1 + entry_offset_r0) * 0x70;
        }
        entry_base_r4 = 0x020218E8;
        asm volatile("" : "+r"(entry_base_r4));
        var_r7 = (u8 *)(entry_offset_r0 + entry_base_r4);
        func_0809A52C(M2C_FIELD(var_r7, u8 *, 0), M2C_FIELD(var_r7, u8 *, 1), 0, 0, 0x02002880);
        func_080986B4(7);
        {
            register s32 display_offset_r0 asm("r0") = M2C_FIELD(var_r7, u8 *, 2) << 6;
            register s32 display_delta_r2 asm("r2");

            entry_base_r4 += display_offset_r0;
            display_delta_r2 = 0x5A90;
            asm volatile("" : "+r"(display_delta_r2));
            entry_base_r4 += display_delta_r2;
            func_08098248(func_080E7B64(*(u8 *)entry_base_r4), 0, 7);
        }
    }
    func_080ACBDC(5, sp20);
    func_08098BB4(0x08005860);
    sp1C = (void *) *(u8 *)0x0200A880;
    sp20 = (s32) *(u8 *)0x0200A881;
    temp_r0_13 = *(u8 *)0x0200A882;
    if (temp_r0_13 != 0) {
        goto block_162;
    }
    goto block_183;
block_162:
    if (temp_r0_13 != 1) {
        goto block_168;
    }
    asm volatile("B9174_FIX_FLAG_AND");
    temp_r1_6 = 0xFFFE & M2C_FIELD(var_r7, u16 *, 4);
    dialog_zero_r4 = 0;
    asm volatile("" : "+r"(dialog_zero_r4));
    M2C_FIELD(var_r7, u16 *, 4) = temp_r1_6;
    if (2 & temp_r1_6) {
        goto block_166;
    }
    func_08094554(sp18);
    var_r6 = 0x5100;
    goto block_183;
block_166:
    func_08092E84(0x58);
    func_0809538C(1, 0x10E0, 0x2060, 0, dialog_zero_r4, dialog_zero_r4, 0x2F, 0x3F);
    var_r0_2 = 0x08005798;
block_167:
    func_08098BB4(var_r0_2);
    func_0809534C();
    goto block_183;
block_168:
    func_08094554(sp18);
block_169:
    func_080ACBA0(5);
    func_08098BB4(0x08005864);
    var_r6 = 0;
    goto block_183;
block_171:
    func_080ACB5C(5);
    temp_r2_4 = *(s32 **)0x02032B94;
    *temp_r2_4 |= 0x20000;
    sp28 = (s32) func_080B80CC(M2C_FIELD(var_r7, u8 *, 0), M2C_FIELD(var_r7, u8 *, 1));
    func_080ACBDC(5, sp20);
    sp18 = func_08094484(0x0821024C, 0x08210258, 0, 0xB8, 0x48, 0, 0, 8, 0);
    func_0809A52C(M2C_FIELD(var_r7, u8 *, 0), M2C_FIELD(var_r7, u8 *, 1), 0, 0, 0x02002880);
    temp_r2_5 = *(s32 **)0x02032B94;
    *temp_r2_5 &= 0xFFFDFFFF;
    if (!(1 & *(u16 *)0x0300000E)) {
        goto block_175;
    }
    asm volatile("B9174_FIX_FINAL_SELECTION_COMPARE");
    if (sp28 == M2C_FIELD(var_r7, u8 *, 1)) {
        goto block_175;
    }
    func_08092E84(0x3E);
    var_r6 = 0x5200;
    goto block_183;
block_175:
    func_08092E84(0x3F);
    goto block_182;
block_176:
    func_0809538C(1, 0x80D0, 0x1868, 0, 0, 0, 0x2F, 0x3F);
    func_08098BB4(0x080059EC);
    asm volatile("B9174_FIX_FIXED_PRICE_500");
    func_0809844C(0x1F4U, 7, 0, 0, 9, 8, 0);
    func_08098248(0x08106F04, 0, 9);
    func_08098BB4(0x08005A2E);
    func_0809534C();
    temp_r4_7 = *(u8 *)0x0200A882;
    if (temp_r4_7 != 1) {
        goto block_182;
    }
    asm volatile("" : : : "r0");
    temp_r5 = *(u8 *)0x0200A880;
    if (temp_r5 != 0) {
        goto block_182;
    }
    {
        register s32 money_base asm("r0") = 0x020218E4;
        register s32 money_offset asm("r2") = 0x6A04;

        asm volatile("" : "+r"(money_base), "+r"(money_offset));
        money3_r6 = (volatile u32 *)(money_base + money_offset);
    }
    if (*money3_r6 <= 0x1F3U) {
        goto block_181;
    }
    func_080E5E90(0x1F4U);
    {
        register u32 current_money_r0 asm("r0") = *money3_r6;
        asm volatile("" : "+r"(current_money_r0));
        func_0809844C(current_money_r0, 7, 0, 2, (s32) temp_r4_7, (s32) temp_r4_7, (s32) temp_r5);
    }
    asm volatile("B9174_FIX_FINAL_SELECTION_STORE");
    M2C_FIELD(var_r7, u8 *, 1) = (u8) sp28;
    goto block_182;
block_181:
    func_08092E84(0x58);
    func_08098BB4(0x08005180);
block_182:
    var_r6 = 0x5010;
block_183:
    {
        register s32 tail_guard_r0 asm("r0") = 0;

        asm volatile("" : "+r"(tail_guard_r0));
        if (tail_guard_r0 != 0) {
            goto block_184;
        }
    }
    goto loop_1;
block_184:
    func_080E66B8();
    return;
}
