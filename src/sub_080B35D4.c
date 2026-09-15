#include "m2c_prelude.h"
#define NULL ((void *)0)
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
void *func_08094374(M2C_UNK, s32, s32, s16, s32, s32, s32, s32, s32); /* extern */
void *func_08094484(s32, M2C_UNK, u8, s16, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_08094564(s32 *, u8);                   /* extern */
M2C_UNK func_08095254(s32, M2C_UNK, s32, s32);      /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096F3C();                            /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080971AC(s32);                         /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098834(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A4CC(u8, u8, u16, void *);         /* extern */
M2C_UNK func_0809AA64(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_0809AB44(s32, s32, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_080AC214(s32, s32);                    /* extern */
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACB5C(s32);                         /* extern */
M2C_UNK func_080ACBA0(s32);                         /* extern */
M2C_UNK func_080ACBDC(s32, u8);                     /* extern */
M2C_UNK func_080B339C();                            /* extern */
M2C_UNK func_080B3410(void *, s32);                 /* extern */
M2C_UNK func_080B61C8(s32, s32, s32);               /* extern */
M2C_UNK func_080E5FA8(u32, s32);                    /* extern */
M2C_UNK func_080E6020(u8);                          /* extern */
M2C_UNK func_080ECD2C(s16 *, M2C_UNK, M2C_UNK);     /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
u8 func_080ECF78(u32, s32);                         /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

asm(".set func_080981F0_4, func_080981F0");
extern M2C_UNK func_080981F0_4(s32, s32, s32, s32);
asm(".set func_08094484_4, func_08094484");
extern void *func_08094484_4(s32, s32, s32, s32);
asm(".set func_08094374_4, func_08094374");
extern void *func_08094374_4(s32, s32, s32, s32);
asm(".set func_080E6020_s32, func_080E6020");
extern M2C_UNK func_080E6020_s32(s32);

void sub_080B35D4(u8 arg0) {
    register s32 block41_coord_base asm("sl");
    register s32 block44_state_offset asm("r8");
    register s32 block50_value_r7 asm("r7");
    register s32 *block81_state_ptr asm("r1");
    register volatile u16 *nav_keys asm("r4");
    register u8 *block146_record_base asm("r4");
    s16 sp18;
    s32 sp1C;
    void *sp20;
    void *sp24;
    void *sp28;
    u32 sp2C;
    s32 sp30;
    u32 sp34;
    s32 sp38;
    s32 sp3C;
    u8 *sp40;
    u8 *sp44;
    s32 *temp_r0_17;
    s32 *temp_r0_21;
    s32 *temp_r1_15;
    s32 *temp_r1_16;
    s32 *temp_r1_17;
    s32 *temp_r1_23;
    s32 *temp_r1_24;
    s32 *temp_r1_4;
    s32 *temp_r1_6;
    s32 *temp_r1_8;
    s32 *temp_r2_10;
    s32 *temp_r2_12;
    s32 *temp_r2_2;
    s32 *temp_r2_4;
    s32 *temp_r2_9;
    s32 *var_r1;
    s32 temp_r0_13;
    s32 temp_r0_16;
    s32 temp_r0_18;
    s32 temp_r0_2;
    s32 temp_r0_6;
    s32 temp_r1_11;
    s32 temp_r1_13;
    s32 temp_r1_14;
    s32 temp_r1_22;
    register s32 temp_r1_2 asm("r4");
    s32 temp_r1_3;
    s32 temp_r1_5;
    s32 temp_r2;
    s32 temp_r2_8;
    register s32 temp_r4 asm("r4");
    s32 temp_r4_2;
    s32 temp_r6_2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r2_2;
    s32 var_r2_3;
    register s32 var_r5_2 asm("r5");
    u16 temp_r1_12;
    u16 temp_r1_18;
    u16 temp_r2_3;
    register u32 var_r9 asm("r9");
    u8 temp_r0;
    u8 temp_r0_10;
    u8 temp_r0_11;
    u8 temp_r0_12;
    u8 temp_r0_14;
    u8 temp_r0_15;
    s32 temp_r0_20;
    u8 temp_r0_4;
    u8 temp_r0_5;
    u8 temp_r0_8;
    u8 temp_r0_9;
    u8 temp_r1;
    u8 temp_r1_10;
    u8 temp_r1_19;
    u8 temp_r1_20;
    u8 temp_r1_21;
    u8 temp_r1_7;
    u8 temp_r1_9;
    u8 temp_r2_11;
    u8 temp_r2_5;
    u8 temp_r2_6;
    u8 temp_r2_7;
    u8 var_r0_4;
    u8 var_r2;
    u8 var_r5_10;
    u8 var_r5_3;
    u8 var_r5_4;
    u8 var_r5_5;
    u8 var_r5_6;
    u8 var_r5_7;
    u8 var_r5_8;
    u8 var_r5_9;
    void *temp_r0_19;
    void *temp_r0_3;
    void *temp_r0_7;
    void *temp_r6;
    u8 var_r5;

    temp_r0 = arg0;
    sp1C = (s32) temp_r0;
    if (temp_r0 == 0) {
        goto block_2;
    }
    *(u16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_0809AB44(2, 0, 0x1EF, 4, 4);
    func_080ECD34(0x081046A8, 0x06015840);
    func_08094330();
    func_08096308(0xF, 0x10);
block_2:
    {
        register s16 *palette_slot_r1 asm("r1") = &sp18;
        register s32 palette_pool_r3 asm("r3") = 0xE3C0;
        register s32 palette_value_r0 asm("r0");

        asm volatile("" : "+r"(palette_slot_r1), "+r"(palette_pool_r3));
        palette_value_r0 = palette_pool_r3;
        asm volatile("" : "+r"(palette_value_r0));
        *palette_slot_r1 = (s16)palette_value_r0;
    }
    func_080ECD2C(&sp18, 0x06001800, 0x01000400);
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2480\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x00A4\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1C21\n\t"
        ".endm");
    *(u16 *)0x0300004C = (u16) (*(u16 *)0x0300004C | 0x200);
    asm volatile(".purgem mov\n\t.purgem lsl\n\t.purgem add");
    *(s16 *)0x0400000A = 0x305;
    {
        s32 *state = (s32 *)0x03000054;

        state[3] = 0;
        state[2] = 0;
    }
    func_08095254(0x087A1F64, 0x06001922, 5, 2);
    func_08095254(0x087A1F64, 0x06001A62, 5, 2);
    func_08095254(0x087A1F64, 0x06001BA2, 5, 2);
    func_08095254(0x087A1F64, 0x06001930, 5, 2);
    func_08095254(0x087A1F64, 0x06001A70, 5, 2);
    func_08095254(0x087A1F64, 0x06001BB0, 5, 2);
    func_08098BB4(0x08002800);
    func_080B61C8(0, 0, 0);
    func_0809AA64(0x087AC9D8, 0, 0x1C0, 0xC);
    {
    register u8 *loop3_unit_base asm("r9");
    register s32 loop3_coord_base asm("sl");
    s32 loop3_gfx_a;
    register s32 loop3_gfx_b_r8 asm("r8");
    register s32 loop3_gfx_c_r7 asm("r7");
    register s32 loop3_gfx_d_r1 asm("r1");

    var_r5 = 0;
    {
        register u8 *loop3_unit_seed_r7 asm("r7") = (u8 *)0x020218E4;

        loop3_unit_base = loop3_unit_seed_r7;
    }
    {
        register s32 loop3_coord_seed_r0 asm("r0") = 0x087A1F4C;

        asm volatile("" : "+r"(loop3_coord_seed_r0));
        loop3_coord_base = loop3_coord_seed_r0;
    }
loop_3:
    {
        register s32 loop3_slot_seed_r0 asm("r0") = 0x690C;

        loop3_slot_seed_r0 += (s32)loop3_unit_base;
        sp44 = (u8 *)(var_r5 + loop3_slot_seed_r0);
    }
    temp_r1 = *sp44;
    temp_r0_2 = temp_r1 * 0x70;
    temp_r6 = temp_r0_2 + 0x020218E8;
    asm volatile(".include \"src/sub_080B35D4_fix_loop3_dma.inc\"");
    if (temp_r1 == 0) {
        goto block_5;
    }
    {
        register s32 loop3_dma_offset_r4 asm("r4") = (s32)var_r5 << 22;

        func_0809A4CC(M2C_FIELD(temp_r0_2, u8 *, 0x020218E8),
            M2C_FIELD(temp_r6, u8 *, 1),
            (u16)(loop3_dma_offset_r4 >> 16), (void *)(u32)var_r5);
    }
block_5:
    {
        register s32 loop3_gfx_a_r2 asm("r2") = 0x0821024C;
        register s32 loop3_gfx_b_r3 asm("r3") = 0x08210258;

        asm volatile("" : "+r"(loop3_gfx_a_r2), "+r"(loop3_gfx_b_r3));
        loop3_gfx_a = loop3_gfx_a_r2;
        loop3_gfx_b_r8 = loop3_gfx_b_r3;
    }
    {
        register s32 loop3_coord_index asm("r1") = (s32)var_r5 * 4;

        asm volatile("" : "+r"(loop3_coord_index));
        asm volatile(".include \"src/sub_080B35D4_fix_loop3_coords.inc\"");
        temp_r1_2 = loop3_coord_index;
    }
    temp_r0_3 = func_08094484(loop3_gfx_a, loop3_gfx_b_r8, 0U,
        M2C_FIELD(temp_r1_2, s16 *, loop3_coord_base),
        M2C_FIELD(temp_r1_2, s16 *, 0x087A1F4E),
        (u16)((s32)var_r5 << 6), (s32)var_r5,
        (*sp44 == 0) ? 0x20348 : 0x348, 0);
    {
        register void **loop3_state1_base asm("r1") = (void **)0x02032E8C;

        asm volatile("" : "+r"(loop3_state1_base));
        M2C_FIELD(temp_r1_2, void **, (s32)loop3_state1_base) = temp_r0_3;
    }
    M2C_FIELD(temp_r0_3, s16 *, 0xC) = 0xA0;
    loop3_gfx_c_r7 = 0x08105D14;
    loop3_gfx_d_r1 = 0x08105D50;
    asm volatile("" : "+r"(loop3_gfx_c_r7), "+r"(loop3_gfx_d_r1));
    {
        register s32 loop3_slot_check asm("r0") = 0x690C;

        loop3_slot_check += (s32)loop3_unit_base;
        loop3_slot_check = var_r5 + loop3_slot_check;
        if (*(u8 *)loop3_slot_check == 0) {
            goto block_11;
        }
    }
    {
        register u8 *loop3_kind_ptr asm("r0") = temp_r6;

        loop3_kind_ptr += 0x38;
        var_r2 = *loop3_kind_ptr;
    }
    goto block_12;
block_11:
    var_r2 = 0;
block_12:
block_15:
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x4656\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".set loop3_state2_add_fix, 0\n\t"
        ".macro add dst, args:vararg\n\t"
        ".if loop3_state2_add_fix == 0\n\t"
        ".short 0x19A0\n\t"
        ".elseif loop3_state2_add_fix == 1\n\t"
        ".short 0x3004\n\t"
        ".elseif loop3_state2_add_fix == 2\n\t"
        ".short 0x19A0\n\t"
        ".elseif loop3_state2_add_fix == 3\n\t"
        ".short 0x4448\n\t"
        ".elseif loop3_state2_add_fix == 4\n\t"
        ".short 0x1828\n\t"
        ".elseif loop3_state2_add_fix == 5\n\t"
        ".short 0x1C38\n\t"
        ".else\n\t"
        ".short 0x1861\n\t"
        ".purgem add\n\t"
        ".endif\n\t"
        ".set loop3_state2_add_fix, loop3_state2_add_fix + 1\n\t"
        ".endm\n\t"
        ".set loop3_state2_str_fix, 0\n\t"
        ".macro str src, addr:vararg\n\t"
        ".if loop3_state2_str_fix == 0\n\t"
        ".short 0x9000\n\t"
        ".elseif loop3_state2_str_fix == 1\n\t"
        ".short 0x9001\n\t"
        ".elseif loop3_state2_str_fix == 2\n\t"
        ".short 0x9002\n\t"
        ".elseif loop3_state2_str_fix == 3\n\t"
        ".short 0x9003\n\t"
        ".elseif loop3_state2_str_fix == 4\n\t"
        ".short 0x9604\n\t"
        ".else\n\t"
        ".short 0x6008\n\t"
        ".purgem str\n\t"
        ".endif\n\t"
        ".set loop3_state2_str_fix, loop3_state2_str_fix + 1\n\t"
        ".endm");
    M2C_FIELD(temp_r1_2, void **, 0x02032EBC) = func_08094484(
        loop3_gfx_c_r7, loop3_gfx_d_r1, var_r2,
        (s16)((u16)M2C_FIELD(temp_r1_2, s16 *, loop3_coord_base) + 4),
        (s16)((u16)M2C_FIELD(temp_r1_2, s16 *, 0x087A1F4E) - 8),
        0x385, 0xF,
        ((*(u8 *)({
            register s32 loop3_final_slot_seed asm("r0") = 0x690C;
            s32 loop3_final_slot;

            loop3_final_slot_seed += (s32)loop3_unit_base;
            loop3_final_slot = var_r5 + loop3_final_slot_seed;
            loop3_final_slot;
        })) == 0) ? 0x20248 : 0x248,
        0);
    var_r5 = (u8)(var_r5 + 1);
    if ((u32) var_r5 > 5U) {
        goto block_17;
    }
    goto loop_3;
    }
block_17:
    func_080B339C();
    *(s32 *)0x02032B90 = 0;
    {
        register u8 *block17_unit_base asm("r3") = (u8 *)0x020218E4;
        register s32 block17_slot_offset asm("r7") = 0x690C;
        register u8 *block17_slot_ptr asm("r1");
        register s32 block24_choice asm("r2");

        asm volatile("" : "+r"(block17_unit_base), "+r"(block17_slot_offset));
        block17_slot_ptr = block17_unit_base + block17_slot_offset;
        asm volatile(
            ".macro ldrb dst, addr:vararg\n\t"
            ".short 0x7808\n\t"
            ".endm\n\t"
            ".macro cmp lhs, rhs\n\t"
            ".short 0x2800\n\t"
            ".endm\n\t"
            ".set b17_lsl_fix, 0\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".if b17_lsl_fix == 0\n\t"
            ".short 0x1C01\n\t"
            ".short 0x00C8\n\t"
            ".else\n\t"
            ".short 0x0100\n\t"
            ".endif\n\t"
            ".set b17_lsl_fix, b17_lsl_fix + 1\n\t"
            ".endm\n\t"
            ".set b17_add_fix, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if b17_add_fix == 0\n\t"
            ".short 0x1D19\n\t"
            ".else\n\t"
            ".short 0x1840\n\t"
            ".endif\n\t"
            ".set b17_add_fix, b17_add_fix + 1\n\t"
            ".endm"
            : "+r"(block17_slot_ptr));
        temp_r0_4 = *block17_slot_ptr;
        if (temp_r0_4 == 0) {
            goto block_21;
        }
        func_080B3410((temp_r0_4 * 0x70) + (s32)block17_unit_base + 4, 0);
        asm volatile(
            ".purgem ldrb\n\t"
            ".purgem cmp\n\t"
            ".purgem lsl\n\t"
            ".purgem add");
        goto block_25;
block_20:
    func_08092E84(0x3F);
    goto block_181;
block_21:
        {
            register s32 block21_slot_offset asm("r0") = 0x690D;
            register u8 *block21_slot_ptr asm("r1");

            asm volatile("" : "+r"(block17_unit_base), "+r"(block21_slot_offset));
            block21_slot_ptr = block17_unit_base + block21_slot_offset;
            asm volatile("" : "+r"(block21_slot_ptr));
            asm volatile(".include \"src/sub_080B35D4_fix_block21_kind.inc\"");
            temp_r0_5 = *block21_slot_ptr;
        }
    block24_choice = 2;
    if (temp_r0_5 == 0) {
        goto block_24;
    }
    if (M2C_FIELD(((temp_r0_5 * 0x70) + (s32)block17_unit_base), u8 *, 0x3C) != 4) {
        goto block_24;
    }
    block24_choice = 1;
block_24:
    func_080B3410(NULL, block24_choice);
    }
block_25:
    func_080972C8();
    func_080ACA8C(6, 1, 1);
    func_080ACB5C(6);
    asm volatile(
        ".set block25_zero_mov_fix, 0\n\t"
        ".macro mov dst, args:vararg\n\t"
        ".if block25_zero_mov_fix == 0\n\t"
        ".short 0x2100\n\t"
        ".else\n\t"
        ".short 0x4689\n\t"
        ".purgem mov\n\t"
        ".endif\n\t"
        ".set block25_zero_mov_fix, block25_zero_mov_fix + 1\n\t"
        ".endm\n\t"
        ".set block25_zero_str_fix, 0\n\t"
        ".macro str src, addr:vararg\n\t"
        ".if block25_zero_str_fix == 0\n\t"
        ".short 0x910C\n\t"
        ".else\n\t"
        ".short 0x900E\n\t"
        ".purgem str\n\t"
        ".endif\n\t"
        ".set block25_zero_str_fix, block25_zero_str_fix + 1\n\t"
        ".endm");
    sp30 = 0;
    sp38 = (s32) *(u8 *)0x020321A4;
    var_r9 = 0;
    asm volatile(
        ".set b25_ldr_fix, 0\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".if b25_ldr_fix == 0\n\t"
        ".short 0x4808\n\t"
        ".else\n\t"
        ".short 0x9B0C\n\t"
        ".purgem ldr\n\t"
        ".endif\n\t"
        ".set b25_ldr_fix, b25_ldr_fix + 1\n\t"
        ".endm\n\t"
        ".set b25_cmp_fix, 0\n\t"
        ".macro cmp lhs, rhs\n\t"
        ".if b25_cmp_fix == 0\n\t"
        ".short 0x2D10\n\t"
        ".elseif b25_cmp_fix == 1\n\t"
        ".short 0x2D10\n\t"
        ".elseif b25_cmp_fix == 2\n\t"
        ".short 0x2D00\n\t"
        ".elseif b25_cmp_fix == 3\n\t"
        ".short 0x4285\n\t"
        ".else\n\t"
        ".short 0x2B00\n\t"
        ".purgem cmp\n\t"
        ".endif\n\t"
        ".set b25_cmp_fix, b25_cmp_fix + 1\n\t"
        ".endm\n\t"
        ".set b25_bl_fix, 0\n\t"
        ".macro bl target:vararg\n\t"
        ".if b25_bl_fix == 0\n\t"
        ".short 0xF000\n\t"
        ".short 0xFCDB\n\t"
        ".elseif b25_bl_fix == 1\n\t"
        ".short 0xE3AC\n\t"
        ".elseif b25_bl_fix == 2\n\t"
        ".short 0xF000\n\t"
        ".short 0xFCCD\n\t"
        ".purgem bl\n\t"
        ".endif\n\t"
        ".set b25_bl_fix, b25_bl_fix + 1\n\t"
        ".endm\n\t"
        ".macro strb src, addr:vararg\n\t"
        ".short 0x2200\n\t"
        ".short 0x7002\n\t"
        ".endm");
    *(u8 *)0x0200A881 = 0;
    asm volatile(".purgem strb");
    var_r5_2 = 0;
loop_26:
    if (var_r5_2 != 0x10) {
        goto block_28;
    }
    goto block_41;
block_28:
    if (var_r5_2 > 0x10) {
        goto block_32;
    }
    if (var_r5_2 == 0) {
        goto block_35;
    }
    goto block_180;
block_32:
    if (var_r5_2 != 0x1000) {
        goto block_34;
    }
    goto block_146;
block_34:
    goto block_180;
block_35:
    if (sp30 != 0) {
        goto block_38;
    }
    asm volatile(
        ".set b35_mov_fix, 0\n\t"
        ".macro mov dst, args:vararg\n\t"
        ".if b35_mov_fix == 0\n\t"
        ".short 0x490F\n\t"
        ".short 0x464C\n\t"
        ".short 0x00A2\n\t"
        ".short 0x1850\n\t"
        ".short 0x2600\n\t"
        ".short 0x5F83\n\t"
        ".short 0x3102\n\t"
        ".short 0x1852\n\t"
        ".short 0x2700\n\t"
        ".short 0x5FD0\n\t"
        ".endif\n\t"
        ".set b35_mov_fix, b35_mov_fix + 1\n\t"
        ".endm\n\t"
        ".macro lsl dst, args:vararg\n\t"
        ".endm\n\t"
        ".macro ldr dst, args:vararg\n\t"
        ".endm\n\t"
        ".macro add dst, args:vararg\n\t"
        ".endm\n\t"
        ".macro ldrsh dst, args:vararg\n\t"
        ".endm"
        : "+r"(var_r9));
    temp_r2 = var_r9 * 4;
    {
        s16 *block35_coord_ptr;
        register s32 block35_value_r0 asm("r0");
        register s32 block35_arg3 asm("r3");

        block35_coord_ptr = (s16 *)(temp_r2 + 0x087A1F4C);
        block35_arg3 = block35_coord_ptr[0];
        block35_value_r0 = block35_coord_ptr[1];
        asm volatile(
            ".purgem mov\n\t"
            ".purgem lsl\n\t"
            ".purgem ldr\n\t"
            ".purgem add\n\t"
            ".purgem ldrsh\n\t"
            "str r0, [sp, #0]\n\t"
            "mov r0, #224\n\t"
            "lsl r0, r0, #1\n\t"
            "str r0, [sp, #4]\n\t"
            "mov r0, #12\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #96\n\t"
            "str r0, [sp, #12]\n\t"
            "str r5, [sp, #16]"
            : "+r"(block35_value_r0)
            : "r"(var_r5_2)
            : "r1", "r2", "memory");
        block35_value_r0 = 0x087AC9E0;
        asm volatile(".include \"src/sub_080B35D4_fix_block35_store.inc\""
            : "+r"(block35_value_r0));
        sp24 = func_08094374_4(block35_value_r0, 0, 0, block35_arg3);
    }
    {
        s32 block35_offset = 0xFFEC;

        M2C_FIELD(sp24, u16 *, 0xA) = block35_offset;
    }
    sp28 = NULL;
    goto block_39;
block_38:
    temp_r0_6 = sp30 * 0x70;
    temp_r0_7 = temp_r0_6 + 0x020218E8;
    sp20 = temp_r0_7;
    {
        register s32 block38_arg5_r4 asm("r4");
        register s32 block38_call0 asm("r0") = M2C_FIELD(sp20, u8 *, 0);
        register s32 block38_call1 asm("r1");

        asm volatile(
            "ldr r4, [sp, #32]\n\t"
            "ldrb r1, [r4, #1]"
            : "=r"(block38_call1)
            :
            : "r4", "memory");
        asm volatile(
            ".syntax unified\n\t"
            "movs %2, #192\n\t"
            "lsls %2, %2, #1\n\t"
            "adds r2, %2, #0\n\t"
            "movs r3, #6\n\t"
            "bl func_0809A4CC\n\t"
            ".syntax divided"
            : "+r"(block38_call0), "+r"(block38_call1), "=&r"(block38_arg5_r4)
            :
            : "r2", "r3", "lr", "cc", "memory");
        {
            register s32 block38_gfx_a asm("r0");
            register s32 block38_gfx_b asm("r1");

            asm volatile(
                "str r5, [sp, #0]\n\t"
                "str r4, [sp, #4]\n\t"
                "mov r0, #6\n\t"
                "str r0, [sp, #8]\n\t"
                "mov r0, #164\n\t"
                "lsl r0, r0, #1\n\t"
                "str r0, [sp, #12]\n\t"
                "str r5, [sp, #16]"
                :
                : "r"(block38_arg5_r4), "r"(var_r5_2)
                : "r0", "r1", "r2", "memory");
            block38_gfx_a = 0x0821024C;
            block38_gfx_b = 0x08210258;
            asm volatile("" : "+r"(block38_gfx_a), "+r"(block38_gfx_b));
            sp24 = func_08094484_4(block38_gfx_a, block38_gfx_b, 0, 0);
        }
    }
    {
        s32 sprite_offset = 0xFFF8;

        asm volatile(
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x9E09\n\t"
            ".endm\n\t"
            ".set b38_strh_fix, 0\n\t"
            ".macro strh src, addr:vararg\n\t"
            ".if b38_strh_fix == 0\n\t"
            ".short 0x8170\n\t"
            ".else\n\t"
            ".short 0x8130\n\t"
            ".endif\n\t"
            ".set b38_strh_fix, b38_strh_fix + 1\n\t"
            ".endm"
            : "+r"(sprite_offset));
        M2C_FIELD(sp24, u16 *, 0xA) = sprite_offset;
        M2C_FIELD(sp24, u16 *, 8) = sprite_offset;
        asm volatile(".purgem ldr\n\t.purgem strh");
    }
    {
        register s32 block38b_gfx_a asm("r0");
        register s32 block38b_gfx_b asm("r1");
        register u32 block38b_kind_r2 asm("r2");
        register s32 block38b_stack_r0 asm("r0");

        asm volatile(
            "ldr r0, [sp, #32]\n\t"
            "add r0, #56\n\t"
            "ldrb r2, [r0]"
            : "=r"(block38b_kind_r2)
            :
            : "r0", "memory");
        asm volatile("str r5, [sp, #0]" : : "r"(var_r5_2) : "r0", "memory");
        block38b_stack_r0 = 0x385;
        asm volatile(
            "str r0, [sp, #4]\n\t"
            "mov r0, #15\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #72\n\t"
            "str r0, [sp, #12]\n\t"
            "str r5, [sp, #16]"
            : "+r"(block38b_stack_r0)
            : "r"(var_r5_2)
            : "memory");
        block38b_gfx_a = 0x08105D14;
        block38b_gfx_b = 0x08105D50;
        asm volatile(".include \"src/sub_080B35D4_fix_block38b_offsets.inc\""
            : "+r"(block38b_gfx_a), "+r"(block38b_gfx_b));
        sp28 = func_08094484_4(block38b_gfx_a, block38b_gfx_b, block38b_kind_r2, 0);
    }
    {
        u16 sprite_offset = 0xFFFC;

        M2C_FIELD(sp28, u16 *, 8) = sprite_offset;
        sprite_offset -= 12;
        M2C_FIELD(sp28, u16 *, 0xA) = sprite_offset;
    }
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".purgem ldr\n\t"
        ".endm");
    M2C_FIELD(sp24, s16 *, 0xC) = 0xA0;
    func_080E6020_s32(var_r9);
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x4814\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x464A\n\t"
        ".purgem lsl\n\t"
        ".endm\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x0091\n\t"
        ".purgem ldr\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1808\n\t"
        ".purgem add\n\t"
        ".endm");
    temp_r1_3 = var_r9 * 4;
    temp_r2_2 = M2C_FIELD(temp_r1_3, s32 **, 0x02032E8C);
    *temp_r2_2 |= 0x20000;
    {
        register s32 **block38_state2_base asm("r0") = (s32 **)0x02032EBC;

        asm volatile("" : "+r"(block38_state2_base));
        temp_r1_4 = M2C_FIELD(temp_r1_3, s32 **, (s32)block38_state2_base);
    }
    *temp_r1_4 |= 0x20000;
    func_080B339C();
    func_080972C8();
block_39:
    sp2C = 0xFF;
    var_r5_2 = 0x10;
    goto block_180;
block_41:
    func_08096F3C();
    {
        register s32 block41_coord_seed_r4 asm("r4") = 0x087A1F4C;

        asm volatile(".include \"src/sub_080B35D4_fix_block41_head.inc\""
            : "+r"(block41_coord_seed_r4));
        block41_coord_base = block41_coord_seed_r4;
    }
loop_42:
    if (var_r9 != sp2C) {
        goto block_44;
    }
    goto block_81;
block_44:
    temp_r1_5 = var_r9 * 4;
    temp_r2_3 = M2C_FIELD(temp_r1_5, u16 *, block41_coord_base);
    asm volatile(".include \"src/sub_080B35D4_fix_block44_sp24.inc\""
        : "+r"(temp_r1_5));
    M2C_FIELD(sp24, u16 *, 4) = temp_r2_3;
    M2C_FIELD(sp24, u16 *, 6) = (u16) M2C_FIELD(temp_r1_5, u16 *, 0x087A1F4E);
    asm volatile(".purgem ldr\n\t.purgem strh\n\t.purgem add");
    block44_state_offset = temp_r1_5;
    asm volatile(".include \"src/sub_080B35D4_fix_block44_sp28.inc\""
        : "+r"(block44_state_offset));
    if (sp28 == NULL) {
        goto block_46;
    }
    M2C_FIELD(sp28, u16 *, 4) = temp_r2_3;
    M2C_FIELD(sp28, u16 *, 6) = (u16) M2C_FIELD(sp24, u16 *, 6);
    asm volatile(
        ".purgem ldr\n\t"
        ".purgem cmp\n\t"
        ".purgem strh\n\t"
        ".include \"src/sub_080B35D4_fix_block46_guard.inc\"");
block_46:
    {
        register u8 *neighbor_unit_base asm("r5");
        register s32 block46_slot_base asm("r4");

    if (sp30 != 0) {
        goto block_63;
    }
    neighbor_unit_base = (u8 *)0x020218E4;
    {
        register s32 block46_slot_offset asm("r0") = 0x690C;
        register u32 block46_slot_index asm("r2");
        register u8 *block46_slot_ptr asm("r1");

        asm volatile("" : "+r"(block46_slot_offset));
        block46_slot_base = (s32)neighbor_unit_base + block46_slot_offset;
        asm volatile("" : "+r"(block46_slot_base));
        block46_slot_index = var_r9;
        asm volatile("" : "+r"(block46_slot_index));
        block46_slot_ptr = (u8 *)(block46_slot_index + block46_slot_base);
        asm volatile(".include \"src/sub_080B35D4_fix_block46_call.inc\""
            : "+r"(block46_slot_ptr));
        temp_r0_8 = *block46_slot_ptr;
    }
    if (temp_r0_8 == 0) {
        goto block_50;
    }
    func_080B3410((temp_r0_8 * 0x70) + (s32)neighbor_unit_base + 4, 0);
    asm volatile(
        ".purgem ldrb");
    goto block_62;
block_50:
    sp3C = 3;
    temp_r0_9 = func_080ECF78(var_r9, 3);
    if (temp_r0_9 == 1) {
        goto block_54;
    }
    {
        register s32 block50_first_mask_r6 asm("r6") = 0x80;
        register s32 block50_first_mask_r0 asm("r0");

        block50_first_mask_r6 <<= 3;
        asm volatile("" : "+r"(block50_first_mask_r6));
        block50_first_mask_r0 = block50_first_mask_r6;
        asm volatile("" : "+r"(block50_first_mask_r0));
        block50_value_r7 = sp3C;
        asm volatile("" : "+r"(block50_value_r7));
        block50_value_r7 |= block50_first_mask_r0;
        sp3C = block50_value_r7;
    }
    {
        register u32 block50_slot_index asm("r2") = (u8) ((var_r9 - temp_r0_9) + 1);
        register u8 *block50_slot_ptr asm("r1");

        asm volatile("" : "+r"(block50_slot_index));
        block50_slot_ptr = (u8 *)(block50_slot_index + block46_slot_base);
        temp_r0_10 = *block50_slot_ptr;
    }
    if (temp_r0_10 == 0) {
        goto block_59;
    }
    {
        register s32 block50_record_offset asm("r1");

        block50_record_offset = temp_r0_10 * 0x70;
        if (M2C_FIELD((block50_record_offset + (s32)neighbor_unit_base), u8 *, 0x3C) != 4) {
            goto block_59;
        }
    }
    {
        register s32 block50_mask_r3 asm("r3") = 0xE0;
        register s32 block50_mask_r0 asm("r0");
        register s32 block50_value_r4 asm("r4");

        block50_mask_r3 <<= 2;
        asm volatile("" : "+r"(block50_mask_r3));
        block50_mask_r0 = block50_mask_r3;
        asm volatile("" : "+r"(block50_mask_r0));
        block50_value_r4 = block50_value_r7;
        asm volatile("" : "+r"(block50_value_r4));
        block50_value_r4 |= block50_mask_r0;
        sp3C = block50_value_r4;
    }
    var_r2_3 = 1;
    goto block_61;
block_54:
    {
        register s32 block54_slot_index asm("r0") = var_r9 - 1;
        register u8 *block54_slot_ptr asm("r1");

        asm volatile("" : "+r"(block54_slot_index));
        block54_slot_ptr = (u8 *)(block54_slot_index + block46_slot_base);
        temp_r0_11 = *block54_slot_ptr;
    }
    if (temp_r0_11 == 0) {
        goto block_56;
    }
    {
        register s32 block54_record_offset asm("r1");

        block54_record_offset = temp_r0_11 * 0x70;
        if (M2C_FIELD((block54_record_offset + (s32)neighbor_unit_base), u8 *, 0x3C) != 0) {
            goto block_58;
        }
    }
block_56:
    {
        register s32 block56_slot_index asm("r0") = var_r9 + 1;
        register u8 *block56_slot_ptr asm("r1");

        asm volatile("" : "+r"(block56_slot_index));
        block56_slot_ptr = (u8 *)(block56_slot_index + block46_slot_base);
        temp_r0_12 = *block56_slot_ptr;
    }
    if (temp_r0_12 == 0) {
        goto block_60;
    }
    {
        register s32 block56_record_offset asm("r1");

        block56_record_offset = temp_r0_12 * 0x70;
        if (M2C_FIELD((block56_record_offset + (s32)neighbor_unit_base), u8 *, 0x3C) == 0) {
            goto block_60;
        }
    }
block_58:
    sp3C = (s32) (u16) (sp3C | 0x400);
block_59:
    var_r2_3 = 2;
    goto block_61;
block_60:
    var_r2_3 = 0;
block_61:
    func_080B3410(NULL, var_r2_3);
block_62:
    func_080972C8();
    goto block_81;
    }
block_63:
    {
        register u8 *block69_unit_base asm("r5");
        register s32 block69_slot_offset asm("r6");
        register u8 *block69_slot_base asm("r4");
        register u32 block69_index asm("r7");
        register u8 *block73_unit_base asm("r3");
        register u8 *block73_slot_base asm("r7");

    asm volatile(".include \"src/sub_080B35D4_fix_block64_loop.inc\""
        : "=r"(var_r5_3));
    sp40 = sp20 + 0x38;
    {
        register s32 block64_table_base asm("r7") = 0x087EDD54;
        register u8 *block64_unit_base asm("r6") = (u8 *)0x020218E4;

loop_64:
    temp_r0_13 = var_r5_3 * 4;
    if (!(*M2C_FIELD(temp_r0_13, s32 **, 0x02032E8C) & 0x200000)) {
        goto block_66;
    }
    {
        register u8 *block64_slot_base asm("r3") = (u8 *)0x020281F0;

        func_080981F0(M2C_FIELD((M2C_FIELD(((M2C_FIELD(var_r5_3, u8 *, (s32)block64_slot_base) * 0x70) + (s32)block64_unit_base), u8 *, 4) * 4), s32 *, block64_table_base), 0, 3, 0, var_r5_3 * 2);
    }
    temp_r2_4 = M2C_FIELD(temp_r0_13, s32 **, 0x02032E8C);
    {
        register s32 block64_state_value asm("r1") = *temp_r2_4;
        register s32 block64_state_mask asm("r0") = 0xFFDFFFFF;

        *temp_r2_4 = block64_state_value & block64_state_mask;
    }
block_66:
    var_r5_3 += 1;
    if ((u32) var_r5_3 <= 5U) {
        goto loop_64;
    }
    }
    func_080972C8();
    block69_unit_base = (u8 *)0x020218E4;
    block69_slot_offset = 0x690C;
    block69_slot_base = block69_unit_base + block69_slot_offset;
    asm volatile("" : "+r"(block69_slot_base));
    block69_index = var_r9;
    if (*(u8 *)((s32)block69_index + (s32)block69_slot_base) == 0) {
        goto block_69;
    }
    {
        register s32 *block69_state_ptr_r1 asm("r1");

        asm volatile(
            ".short 0x4821\n\t"
            "add r0, %1\n\t"
            "ldr r1, [r0]"
            : "=r"(block69_state_ptr_r1)
            : "r"(block44_state_offset)
            : "r0", "memory");
        temp_r1_6 = block69_state_ptr_r1;
    }
    asm volatile(
        ".short 0x6808\n\t"
        ".short 0x2280\n\t"
        ".short 0x0392\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".endm\n\t"
        ".macro orr dst, lhs, rhs\n\t"
        ".short 0x4310\n\t"
        ".endm");
    *temp_r1_6 |= 0x200000;
    asm volatile(".include \"src/sub_080B35D4_fix_block69_guard.inc\"\n\t.code 16");
block_69:
    temp_r0_14 = *sp40;
    if (temp_r0_14 != 4) {
        goto block_76;
    }
    {
        register u32 block69_prev_index asm("r0") = var_r9;

        asm volatile(".include \"src/sub_080B35D4_fix_block69_prev_state.inc\""
            : "+r"(block69_prev_index));
        block69_prev_index -= 1;
        temp_r2_5 = (u8)block69_prev_index;
    }
    {
        register u8 *block69_prev_slot_ptr asm("r0");

        block69_prev_slot_ptr = (u8 *)((s32)temp_r2_5 + (s32)block69_slot_base);
        temp_r1_7 = *block69_prev_slot_ptr;
    }
    if (temp_r1_7 == 0) {
        goto block_73;
    }
    if (M2C_FIELD(((temp_r1_7 * 0x70) + (s32)block69_unit_base), u8 *, 0x3C) == 0) {
        goto block_73;
    }
    temp_r1_8 = M2C_FIELD((temp_r2_5 * 4), s32 **, 0x02032E8C);
    asm volatile(
        ".short 0x6808\n\t"
        ".short 0x2680\n\t"
        ".short 0x03B6\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".endm\n\t"
        ".macro orr dst, lhs, rhs\n\t"
        ".short 0x4330\n\t"
        ".endm");
    *temp_r1_8 |= 0x200000;
    asm volatile(".include \"src/sub_080B35D4_fix_block73_state.inc\"\n\t.code 16");
block_73:
    temp_r2_6 = var_r9 + 1;
    block73_unit_base = (u8 *)0x020218E4;
    block73_slot_base = (u8 *)0x020281F0;
    temp_r1_9 = *(u8 *)((s32)temp_r2_6 + (s32)block73_slot_base);
    if (temp_r1_9 == 0) {
        goto block_81;
    }
    if (M2C_FIELD(((temp_r1_9 * 0x70) + (s32)block73_unit_base), u8 *, 0x3C) == 0) {
        goto block_81;
    }
    var_r1 = M2C_FIELD((temp_r2_6 * 4), s32 **, 0x02032E8C);
    var_r0_3 = *var_r1 | 0x200000;
    goto block_80;
block_76:
    if (temp_r0_14 == 0) {
        goto block_81;
    }
    temp_r2_7 = (var_r9 - func_080ECF78(var_r9, 3)) + 1;
    {
        register u8 *block76_slot_ptr asm("r0");

        block76_slot_ptr = (u8 *)((s32)temp_r2_7 + (s32)block69_slot_base);
        temp_r1_10 = *block76_slot_ptr;
    }
    if (temp_r1_10 == 0) {
        goto block_81;
    }
    if (M2C_FIELD(((temp_r1_10 * 0x70) + (s32)block69_unit_base), u8 *, 0x3C) != 4) {
        goto block_81;
    }
    asm volatile(
        ".set b76_ldr_fix, 0\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".if b76_ldr_fix == 0\n\t"
        ".short 0x4C17\n\t"
        ".elseif b76_ldr_fix == 1\n\t"
        ".short 0x6801\n\t"
        ".endif\n\t"
        ".set b76_ldr_fix, b76_ldr_fix + 1\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1900\n\t"
        ".endm\n\t"
        ".macro orr dst, lhs, rhs\n\t"
        ".short 0x4330\n\t"
        ".endm\n\t"
        ".macro str src, addr:vararg\n\t"
        ".short 0x6008\n\t"
        ".endm");
    var_r1 = M2C_FIELD((temp_r2_7 * 4), s32 **, 0x02032E8C);
    asm volatile(
        ".short 0x6808\n\t"
        ".short 0x2680\n\t"
        ".short 0x03B6");
    var_r0_3 = *var_r1 | 0x200000;
block_80:
    *var_r1 = var_r0_3;
    asm volatile(
        ".include \"src/sub_080B35D4_fix_block81_guard.inc\"\n\t"
        ".code 16\n\t"
        ".code 16\n\t"
        ".code 16");
    }
block_81:
    block81_state_ptr = (s32 *)0x03000078;
    temp_r2_8 = *block81_state_ptr;
    if (!(0x3F & temp_r2_8)) {
        goto block_84;
    }
    if (sp2C == var_r9) {
        goto block_89;
    }
    if (temp_r2_8 & 0x20) {
        goto block_89;
    }
block_84:
    var_r5_4 = 0;
    {
        register s32 **block84_state_base asm("r4") = (s32 **)0x02032E8C;

loop_85:
    if (!(*block84_state_base[var_r5_4] & 0x200000)) {
        goto block_87;
    }
    {
        register s32 block84_call_r0 asm("r0") = var_r5_4 * 2;

        asm volatile("str r0, [sp, #0]" : "+r"(block84_call_r0) : : "memory");
        block84_call_r0 = 0x08106238;
        asm volatile("" : "+r"(block84_call_r0));
        func_080981F0_4(block84_call_r0, 0, 3, 0);
    }
block_87:
    var_r5_4 += 1;
    if ((u32) var_r5_4 <= 5U) {
        goto loop_85;
    }
    func_080972C8();
    }
    goto block_97;
block_89:
    temp_r1_11 = *block81_state_ptr;
    if ((0x3F & temp_r1_11) == 0x20) {
        goto block_92;
    }
    if (sp2C == var_r9) {
        goto block_97;
    }
    if (!(temp_r1_11 & 0x20)) {
        goto block_97;
    }
block_92:
    asm volatile(".include \"src/sub_080B35D4_fix_block92_mask.inc\""
        : "=r"(var_r5_5));
    {
        register s32 block92_table_base asm("r6") = 0x087EDD54;
        register u8 *block92_unit_base asm("r4") = (u8 *)0x020218E4;

loop_93:
    if (!(*M2C_FIELD((var_r5_5 * 4), s32 **, 0x02032E8C) & 0x200000)) {
        goto block_95;
    }
    {
        register u8 *block92_slot_base asm("r1") = (u8 *)0x020281F0;

        func_080981F0(M2C_FIELD((M2C_FIELD(((M2C_FIELD(var_r5_5, u8 *, (s32)block92_slot_base) * 0x70) + (s32)block92_unit_base), u8 *, 4) * 4), s32 *, block92_table_base), 0, 3, 0, var_r5_5 * 2);
    }
block_95:
    var_r5_5 += 1;
    if ((u32) var_r5_5 <= 5U) {
        goto loop_93;
    }
    func_080972C8();
    }
block_97:
    sp2C = var_r9;
    func_080ED17C(1);
    if (!(0x40 & *(u16 *)0x03006034)) {
        goto block_103;
    }
    if (sp30 == 0) {
        goto block_100;
    }
    if (M2C_FIELD(sp20, u8 *, 0x38) == 4) {
        goto block_103;
    }
block_100:
    if ((func_080ECF78(var_r9, 3) << 0x18) == 0) {
        goto block_103;
    }
    var_r0_4 = var_r9 - 1;
    goto block_114;
block_103:
    {
        register volatile u16 *nav_key_seed asm("r0") = (volatile u16 *)0x03006034;
        u32 nav_80;

        nav_80 = 0x80 & *nav_key_seed;
        nav_keys = nav_key_seed;
        if (!nav_80) {
            goto block_108;
        }
    }
    if (sp30 == 0) {
        goto block_106;
    }
    if (M2C_FIELD(sp20, u8 *, 0x38) == 4) {
        goto block_108;
    }
block_106:
    if ((u32) func_080ECF78(var_r9, 3) > 1U) {
        goto block_108;
    }
    var_r0_4 = var_r9 + 1;
    goto block_114;
block_108:
    if (!(0x20 & *nav_keys)) {
        goto block_111;
    }
    asm volatile(".include \"src/sub_080B35D4_fix_nav_indices.inc\"");
    if (var_r9 <= 2U) {
        goto block_111;
    }
    var_r0_4 = var_r9 - 3;
    goto block_114;
block_111:
    if (!(0x10 & *nav_keys)) {
        goto block_115;
    }
    if (var_r9 > 2U) {
        goto block_115;
    }
    var_r0_4 = var_r9 + 3;
block_114:
    var_r9 = (u32) var_r0_4;
    func_08092E84(0x40);
    goto loop_42;
block_115:
    temp_r1_12 = *(u16 *)0x0300000E;
    if (1 & temp_r1_12) {
        goto block_117;
    }
    goto block_129;
block_117:
    if (sp30 != 0) {
        goto block_124;
    }
    {
        register u8 *block117_slot_base asm("r1") = (u8 *)0x020281F0;

        asm volatile("" : "+r"(block117_slot_base));
        temp_r0_15 = *(u8 *)((s32)var_r9 + (s32)block117_slot_base);
    }
    if (temp_r0_15 == 0) {
        goto block_121;
    }
    {
        register u32 block117_selected asm("r1");

        asm volatile(".include \"src/sub_080B35D4_fix_block117_to_coord.inc\""
            : "=r"(block117_selected)
            : "r"(temp_r0_15));
        sp30 = (s32)block117_selected;
    }
    func_08094554(sp24);
    func_08092E84(0x3E);
    func_080ED17C(1);
    var_r5_2 = 0;
    goto block_122;
block_121:
    func_08098834(4);
    func_080AC214(4, sp3C);
    func_08094554(sp24);
    {
        register s32 block121_arg_r3 asm("r3");
        register s32 block121_stack_r0 asm("r0");
        register s32 block121_gfx_a asm("r0");
        register s32 block121_gfx_b asm("r1");

        temp_r1_13 = var_r9 * 4;
        block121_arg_r3 = (s16)(M2C_FIELD(temp_r1_13, u16 *, block41_coord_base) - 4);
        block121_stack_r0 = (s32)(s16)(M2C_FIELD(temp_r1_13, u16 *, 0x087A1F4E) - 0x28);
        asm volatile(".include \"src/sub_080B35D4_fix_block121_tail.inc\""
            : "+r"(block121_stack_r0) : : "memory");
        block121_stack_r0 = 0x2DF;
        asm volatile("str r0, [sp, #4]" : "+r"(block121_stack_r0) : : "memory");
        block121_stack_r0 = 0xF;
        asm volatile("str r0, [sp, #8]" : "+r"(block121_stack_r0) : : "memory");
        block121_stack_r0 = 0x60;
        asm volatile("str r0, [sp, #12]" : "+r"(block121_stack_r0) : : "memory");
        {
            register s32 block121_last_r6 asm("r6");

            asm volatile("ldr %0, [sp, #48]"
                : "=r"(block121_last_r6)
                :
                : "memory");
            asm volatile("str r6, [sp, #16]"
                : "+r"(block121_last_r6)
                :
                : "memory");
        }
        block121_gfx_a = 0x0810557C;
        block121_gfx_b = 0x081055B0;
        asm volatile("" : "+r"(block121_gfx_a), "+r"(block121_gfx_b));
        sp24 = func_08094484_4(block121_gfx_a, block121_gfx_b, 0, block121_arg_r3);
    }
    func_08092E84(0x3E);
    var_r5_2 = 0x1000;
block_122:
    sp34 = var_r9;
    goto block_180;
block_124:
    func_08092E84(0x4E);
    asm volatile(".include \"src/sub_080B35D4_fix_block124_loop.inc\""
        : "=r"(var_r5_6));
    temp_r0_16 = var_r9 * 4;
    block44_state_offset = temp_r0_16;
    sp40 = sp20 + 0x38;
    {
        register u32 block124_event_seed asm("r2") = var_r9;

        asm volatile("" : "+r"(block124_event_seed));
        block124_event_seed <<= 22;
        block41_coord_base = block124_event_seed;
    }
    block50_value_r7 = 0x80;
    block50_value_r7 <<= 10;
    asm volatile("" : "+r"(block50_value_r7));
loop_125:
    temp_r6_2 = var_r5_6 * 4;
    temp_r2_9 = M2C_FIELD(temp_r6_2, s32 **, 0x02032E8C);
    temp_r1_14 = *temp_r2_9;
    {
        register u32 block124_flags_test asm("r0");
        register u32 block124_flags_mask asm("r3");

        asm volatile(
            "mov %0, %2\n\t"
            "mov %1, #128\n\t"
            "lsl %1, %1, #14"
            : "=r"(block124_flags_test), "=r"(block124_flags_mask)
            : "r"(temp_r1_14));
        if (!(block124_flags_test & block124_flags_mask)) {
            goto block_127;
        }
    }
    *temp_r2_9 = temp_r1_14 & 0xFFDFFFFF;
    func_080E6020(var_r5_6);
    temp_r1_15 = M2C_FIELD(temp_r6_2, s32 **, 0x02032E8C);
    *temp_r1_15 |= block50_value_r7;
    temp_r1_16 = M2C_FIELD(temp_r6_2, s32 **, 0x02032EBC);
    *temp_r1_16 |= block50_value_r7;
block_127:
    var_r5_6 += 1;
    if ((u32) var_r5_6 <= 5U) {
        goto loop_125;
    }
    func_080ED17C(1);
    func_080E5FA8(var_r9, sp30);
    func_0809A4CC(M2C_FIELD(sp20, u8 *, 0), M2C_FIELD(sp20, u8 *, 1), (u16) (block41_coord_base >> 16), (void *) var_r9);
    {
        register s32 **block124_state_base asm("r0") = (s32 **)0x02032E8C;

        asm volatile(".short 0x480E" : "=r"(block124_state_base));
        temp_r1_17 = M2C_FIELD(block44_state_offset, s32 **, (s32)block124_state_base);
    }
    *temp_r1_17 &= 0xFFFDFFFF;
    temp_r0_17 = M2C_FIELD(block44_state_offset, s32 **, 0x02032EBC);
    *temp_r0_17 &= 0xFFFDFFFF;
    func_08094564(temp_r0_17, *sp40);
    sp30 = 0;
    func_08094554(sp24);
    func_08094554(sp28);
    func_080B339C();
    func_080972C8();
    asm volatile("" : : "g"(sp30));
    goto block_179;
block_129:
    if (2 & temp_r1_12) {
        goto block_131;
    }
    goto loop_42;
block_131:
    if (sp30 != 0) {
        goto block_140;
    }
    asm volatile(".include \"src/sub_080B35D4_fix_block131_scan.inc\""
        : "=r"(var_r5_7));
    {
        register u8 *block131_slot_seed asm("r2") = (u8 *)0x020281F0;

        if (*block131_slot_seed != 0) {
            goto block_136;
        }
        {
            register u8 *block134_slot_base asm("r1") = block131_slot_seed;
loop_134:
    var_r5_7 += 1;
    if ((u32) var_r5_7 > 5U) {
        goto block_138;
    }
    if (M2C_FIELD(var_r5_7, u8 *, (s32)block134_slot_base) == 0) {
        goto loop_134;
    }
        }
block_136:
    if ((u32) var_r5_7 > 5U) {
        goto block_138;
    }
    goto block_20;
    }
block_138:
    func_08092E84(0x58);
    func_08098BB4(0x080028CF);
    goto loop_42;
block_140:
    asm volatile(".include \"src/sub_080B35D4_fix_block140_loop.inc\""
        : "=r"(var_r5_8));
    {
        register s32 block140_table_base asm("r7") = 0x087EDD54;
        register u8 *block140_unit_base asm("r6") = (u8 *)0x020218E4;

loop_141:
    temp_r0_18 = var_r5_8 * 4;
    if (!(*M2C_FIELD(temp_r0_18, s32 **, 0x02032E8C) & 0x200000)) {
        goto block_143;
    }
    {
        register u8 *block140_slot_base asm("r2") = (u8 *)0x020281F0;

        func_080981F0(M2C_FIELD((M2C_FIELD(((M2C_FIELD(var_r5_8, u8 *, (s32)block140_slot_base) * 0x70) + (s32)block140_unit_base), u8 *, 4) * 4), s32 *, block140_table_base), 0, 3, 0, var_r5_8 * 2);
    }
    temp_r2_10 = M2C_FIELD(temp_r0_18, s32 **, 0x02032E8C);
    {
        register s32 block140_state_value asm("r1") = *temp_r2_10;
        register s32 block140_state_mask asm("r0") = 0xFFDFFFFF;

        *temp_r2_10 = block140_state_value & block140_state_mask;
    }
block_143:
    var_r5_8 += 1;
    if ((u32) var_r5_8 <= 5U) {
        goto loop_141;
    }
    }
    func_080972C8();
    func_08092E84(0x3F);
    sp30 = 0;
    func_08094554(sp24);
    func_08094554(sp28);
    goto block_179;
block_146:
    temp_r0_19 = sp38 * 0x70;
    block146_record_base = (u8 *)0x020218E8;
    sp20 = temp_r0_19 + (s32)block146_record_base;
    func_080B3410(sp20, 0);
    func_080ACBDC(6, *(u8 *)0x0200A881);
    func_08098BB4(0x08002850);
    {
        register u8 *block146_order_base asm("r1") = (u8 *)0x020321A4;
        u32 block146_order_index;

        asm volatile("" : "+r"(block146_order_base));
        block146_order_index = *(u8 *)0x0200A880;
        block146_order_index += (u32)block146_order_base;
        sp38 = (s32)*(u8 *)block146_order_index;
    }
    temp_r0_20 = *(u8 *)0x0200A882;
    if (temp_r0_20 == 1) {
        goto block_153;
    }
    if ((s32) temp_r0_20 > 1) {
        goto block_149;
    }
    goto block_180;
block_149:
    if (temp_r0_20 != 2) {
        goto block_151;
    }
    goto block_178;
block_151:
    goto block_180;
block_153:
    {
        register u16 *block153_flag_owner asm("r6") = (u16 *)sp20;
        register u32 block153_flags asm("r0");
        register u32 block153_mask_seed asm("r7");
        register u32 block153_mask asm("r1");

        asm volatile("ldrh %0, [%1, #4]"
            : "=r"(block153_flags)
            : "r"(block153_flag_owner)
            : "memory");
        block153_mask_seed = 0xFFFE;
        asm volatile("mov %0, %1"
            : "=r"(block153_mask)
            : "r"(block153_mask_seed));
        asm volatile(
            ".macro and dst, lhs, rhs\n\t"
            ".short 0x4001\n\t"
            ".endm\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".endm\n\t"
            ".macro lsr dst, lhs, rhs\n\t"
            ".endm\n\t"
            ".macro strh src, addr:vararg\n\t"
            ".short 0x80B1\n\t"
            ".endm");
        block153_flags &= block153_mask;
        temp_r1_18 = block153_flags;
        asm volatile("strh %0, [%1, #4]"
            :
            : "r"(block153_flags), "r"(block153_flag_owner)
            : "memory");
        asm volatile(
            ".purgem and\n\t"
            ".purgem lsl\n\t"
            ".purgem lsr\n\t"
            ".purgem strh");
        if (M2C_FIELD(block153_flag_owner, u8 *, 2) != 0) {
            goto block_155;
        }
    }
    func_08092E84(0x58);
    func_08098BB4(0x0800285D);
    goto block_180;
block_155:
    if (!(8 & temp_r1_18)) {
        goto block_158;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08002926);
    goto block_180;
block_158:
    {
        register u8 *block158_kind_seed asm("r0") = (u8 *)sp20;

        block158_kind_seed += 0x38;
        asm volatile("" : "+r"(block158_kind_seed));
        temp_r1_19 = *block158_kind_seed;
        sp40 = block158_kind_seed;
    }
    if (temp_r1_19 != 4) {
        goto block_167;
    }
    if (func_080ECF78(sp34, 3) == 1) {
        goto block_162;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08002A14);
    goto block_180;
block_162:
    {
        register u8 *block162_unit_base asm("r3") = block146_record_base - 4;

        {
            register s32 block162_slot_lo asm("r0") = sp34;
            register u8 *block162_slot_base_lo asm("r1");

            asm volatile("" : "+r"(block162_slot_lo));
            block162_slot_lo -= 1;
            block162_slot_base_lo = (u8 *)0x020281F0;
            asm volatile("" : "+r"(block162_slot_base_lo));
            temp_r1_20 = *(u8 *)((s32)block162_slot_lo + (s32)block162_slot_base_lo);
        }
        {
            register s32 block162_slot_hi asm("r0") = sp34;
            register u8 *block162_slot_base_hi asm("r2");

            asm volatile("" : "+r"(block162_slot_hi));
            block162_slot_hi += 1;
            block162_slot_base_hi = (u8 *)0x020281F0;
            asm volatile("" : "+r"(block162_slot_base_hi));
            temp_r2_11 = *(u8 *)((s32)block162_slot_hi + (s32)block162_slot_base_hi);
        }
    if (temp_r1_20 == 0) {
        goto block_164;
    }
    if (M2C_FIELD(((temp_r1_20 * 0x70) + (s32)block162_unit_base), u8 *, 0x3C) != 0) {
        goto block_166;
    }
block_164:
    if (temp_r2_11 == 0) {
        goto block_171;
    }
    if (M2C_FIELD(((temp_r2_11 * 0x70) + (s32)block162_unit_base), u8 *, 0x3C) == 0) {
        goto block_171;
    }
block_166:
    func_08092E84(0x58);
    func_08098BB4(0x08002A9E);
    goto block_180;
    }
block_167:
    if (temp_r1_19 == 0) {
        goto block_171;
    }
    block146_record_base -= 4;
    {
        register s32 block167_index asm("r0");
        u8 block167_distance = func_080ECF78(sp34, 3);
        register s32 block167_selected_r3 asm("r3");
        register u8 *block167_slot_base asm("r6");

        asm volatile(".include \"src/sub_080B35D4_fix_block167_index.inc\"");
        block167_selected_r3 = sp34;
        block167_index = block167_selected_r3 - block167_distance;
        block167_index += 1;
        asm volatile("" : "+r"(block167_index));
        block167_slot_base = (u8 *)0x020281F0;
        asm volatile("" : "+r"(block167_slot_base));
        temp_r1_21 = *(u8 *)((s32)block167_index + (s32)block167_slot_base);
    }
    if (temp_r1_21 == 0) {
        goto block_171;
    }
    if (M2C_FIELD(((temp_r1_21 * 0x70) + (s32)block146_record_base), u8 *, 0x3C) != 4) {
        goto block_171;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08002B4E);
    goto block_180;
block_171:
    {
        register u32 block171_event_r6 asm("r6");
        register u32 block171_flags_r1 asm("r1");
        u32 block171_flag_mask;

    func_08092E84(0x4E);
    asm volatile(
        "ldr r7, [sp, #32]\n\t"
        "ldrh r1, [r7, #4]"
        : "=r"(block171_flags_r1)
        :
        : "r7", "cc", "memory");
    block171_flag_mask = 4;
    block171_flag_mask &= block171_flags_r1;
    {
        register u32 block171_selected_r1 asm("r1") = sp34;

        block171_event_r6 = block171_selected_r1 << 22;
        temp_r4 = block171_selected_r1 * 4;
    }
    if (!block171_flag_mask) {
        goto block_177;
    }
    var_r5_9 = 0;
    {
        register u8 *block171_first_slot_base asm("r2") = (u8 *)0x020281F0;
        register u8 *block171_scan_slot_base asm("r1");
        u8 block171_first_slot;

        asm volatile(".include \"src/sub_080B35D4_fix_block171_scan.inc\""
            : "+r"(block171_first_slot_base));
        block171_first_slot = *block171_first_slot_base;
        if (block171_first_slot == sp38) {
            goto block_176;
        }
        asm volatile("mov %0, %1"
            : "=r"(block171_scan_slot_base)
            : "r"(block171_first_slot_base));
loop_174:
        var_r5_9 += 1;
        if ((u32) var_r5_9 > 5U) {
            goto block_176;
        }
        if (*(u8 *)((s32)var_r5_9 + (s32)block171_scan_slot_base) != sp38) {
            goto loop_174;
        }
    }
block_176:
    func_080E6020(var_r5_9);
    {
        register s32 **block176_state_base asm("r0") = (s32 **)0x02032E8C;

        asm volatile(".include \"src/sub_080B35D4_fix_block176_to177.inc\""
            : "+r"(block176_state_base));
        temp_r1_22 = var_r5_9 * 4;
        temp_r2_12 = M2C_FIELD(temp_r1_22, s32 **, (s32)block176_state_base);
    }
    *temp_r2_12 |= 0x20000;
    temp_r1_23 = M2C_FIELD(temp_r1_22, s32 **, 0x02032EBC);
    *temp_r1_23 |= 0x20000;
block_177:
    func_080E5FA8(sp34, sp38);
    func_0809A4CC(M2C_FIELD(sp20, u8 *, 0), M2C_FIELD(sp20, u8 *, 1), (u16) (block171_event_r6 >> 16), (void *) sp34);
    temp_r1_24 = M2C_FIELD(temp_r4, s32 **, 0x02032E8C);
    *temp_r1_24 &= 0xFFFDFFFF;
    temp_r0_21 = M2C_FIELD(temp_r4, s32 **, 0x02032EBC);
    *temp_r0_21 &= 0xFFFDFFFF;
    func_08094564(temp_r0_21, *sp40);
    func_08094554(sp24);
    func_080ACB5C(6);
    func_080B339C();
    func_080972C8();
    goto block_179;
    }
block_178:
    func_080971AC(3);
    func_080972C8();
    func_08094554(sp24);
    func_080ACB5C(6);
block_179:
    var_r5_2 = 0;
block_180:
    {
        register s32 tail_guard_r3 asm("r3") = 0;

        asm volatile(".include \"src/sub_080B35D4_fix_block181_guard.inc\""
            : "+r"(tail_guard_r3));
        if (tail_guard_r3 != 0) {
            goto block_181;
        }
    }
    goto loop_26;
block_181:
    if (sp1C != 0) {
        goto block_188;
    }
    func_08095254(0x087A1F78, 0x06000922, 5, 2);
    func_08095254(0x087A1F78, 0x06000A62, 5, 2);
    func_08095254(0x087A1F78, 0x06000BA2, 5, 2);
    func_08095254(0x087A1F78, 0x06000930, 5, 2);
    func_08095254(0x087A1F78, 0x06000A70, 5, 2);
    func_08095254(0x087A1F78, 0x06000BB0, 5, 2);
    func_08094554(sp24);
    func_080ACBA0(6);
    if (*(void **)0x02032B90 == 0) {
        goto block_184;
    }
    func_08094554(*(void **)0x02032B90);
block_184:
    var_r5_10 = 0;
loop_185:
    {
        register void **block185_state_base asm("r6") = (void **)0x02032E8C;

        asm volatile(".include \"src/sub_080B35D4_fix_block185_tail.inc\""
            : "+r"(block185_state_base));
        temp_r4_2 = var_r5_10 * 4;
        func_08094554(M2C_FIELD(temp_r4_2, void **, (s32)block185_state_base));
    }
    func_08094554(M2C_FIELD(temp_r4_2, void **, 0x02032EBC));
    var_r5_10 += 1;
    if ((u32) var_r5_10 <= 5U) {
        goto loop_185;
    }
    func_08098BB4(0x08002854);
    *(u16 *)0x0300004C = (u16) (0xFCFF & *(u16 *)0x0300004C);
    return;
block_188:
    func_08096308(0x10, 0x10);
    goto loop_190;
block_189:
    func_080ED17C(1);
loop_190:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_189;
    }
    return;
}
