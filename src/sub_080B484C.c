#include "m2c_prelude.h"
#define NULL ((void *)0)

M2C_UNK func_08092E84(s32);
M2C_UNK func_08094330();
void *func_08094374();
void *func_08094484();
M2C_UNK func_08094554(void *);
M2C_UNK func_08094564(s32 *, u8);
M2C_UNK func_08095254(s32, M2C_UNK, s32, s32);
M2C_UNK func_08096308(s32, s32);
s32 func_0809669C();
M2C_UNK func_08096F3C();
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
M2C_UNK func_080971AC(s32);
M2C_UNK func_080972C8();
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);
M2C_UNK func_08098834(s32);
M2C_UNK func_08098BB4(M2C_UNK);
M2C_UNK func_0809A4CC(u8, u8, u16, void *);
M2C_UNK func_0809AA64(M2C_UNK, s32, s32, s32);
M2C_UNK func_0809AB44(s32, s32, M2C_UNK, s32, s32);
M2C_UNK func_080ACA8C(s32, s32, s32);
M2C_UNK func_080ACB5C(s32);
M2C_UNK func_080B43B4(s32, u8);
M2C_UNK func_080B44A0(s32, s32);
M2C_UNK func_080B460C();
M2C_UNK func_080B4684(u8, s32);
s32 func_080E9D88(s32, u8);
M2C_UNK func_080ECD2C(s16 *, M2C_UNK, M2C_UNK);
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);
u8 func_080ECF78(u32, s32);
M2C_UNK func_080ED17C(s32);




extern s32 *D_02032E8C[2][6];
extern s32 *D_02032EBC[2][6];

asm(".set func_08094484_4, func_08094484");
extern void *func_08094484_4(s32, s32, s32, s32);
asm(".set func_080981F0_4, func_080981F0");
extern M2C_UNK func_080981F0_4(s32, s32, s32, s32);

void sub_080B484C(void) {
    s16 sp18;
    void *sp1C;
    void *sp20;
    void *sp24;
    u32 sp28;
    s32 sp2C;
    u32 sp30;
    s32 sp34;
    s32 sp38;
    u32 sp3C;
    u8 *sp40;
    s32 *temp_r0_15;
    s32 *temp_r0_19;
    s32 *temp_r1_17;
    s32 *temp_r1_18;
    s32 *temp_r1_19;
    s32 *temp_r1_25;
    s32 *temp_r1_26;
    s32 *temp_r1_5;
    s32 *temp_r1_7;
    s32 *temp_r1_9;
    s32 *temp_r2;
    s32 *temp_r2_11;
    s32 *temp_r2_3;
    s32 *temp_r2_8;
    s32 *temp_r2_9;
    register s32 *var_r1 asm("r1");
    s32 temp_r0;
    s32 temp_r0_12;
    s32 temp_r0_16;
    s32 temp_r0_5;
    s32 temp_r1_12;
    s32 temp_r1_14;
    s32 temp_r1_15;
    s32 temp_r1_24;
    register s32 temp_r1_2 asm("r5");
    s32 temp_r1_3;
    s32 temp_r1_4;
    s32 temp_r1_6;
    register s32 temp_r2_7 asm("r2");
    register s32 *block81_state_ptr asm("r1");
    s32 temp_r6_2;
    s32 var_r0;
    s32 var_r0_2;
    register s32 var_r0_3 asm("r0");
    s32 var_r2_2;
    s32 var_r2_3;
    s32 var_r5;
    u16 temp_r1_13;
    u16 temp_r2_2;
    register u32 var_r9 asm("r9");
    register volatile u16 *nav_keys asm("r4");
    s32 temp_r0_17;
    u8 temp_r0_10;
    u8 temp_r0_11;
    u8 temp_r0_13;
    u8 temp_r0_14;
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_7;
    u8 temp_r0_8;
    u8 temp_r0_9;
    u8 temp_r1;
    u8 temp_r1_10;
    u8 temp_r1_11;
    u8 temp_r1_20;
    u8 temp_r1_21;
    u8 temp_r1_22;
    u8 temp_r1_23;
    u8 temp_r1_8;
    u8 temp_r2_10;
    u8 temp_r2_4;
    u8 temp_r2_5;
    u8 temp_r2_6;
    u8 block63_kind;
    u8 var_r0_4;
    u8 var_r1_2;
    u8 var_r2;
    u8 var_r3;
    u8 var_r3_2;
    u8 var_r4;
    u8 var_r4_10;
    u8 var_r4_3;
    u8 var_r4_4;
    u8 var_r4_5;
    u8 var_r4_6;
    u8 var_r4_9;
    void *temp_r0_18;
    void *temp_r0_2;
    void *temp_r0_6;
    register void *temp_r6 asm("r6");
    void *var_r4_7;
    void *var_r4_8;

    register u8 *slot_base asm("r8");
    u8 *order_base;
    register u8 *loop1_slot_base asm("r6");
    register u8 *counter_ptr asm("r5");
    register u8 *loop1_order_base asm("r7");
    register u8 *unit_base asm("r7");
    s32 coord_hi;
    register s32 coord_lo asm("r10");
    s32 sprite_a;
    register s32 sprite_b asm("r8");
    register s32 sprite_c asm("r7");
    register s32 sprite_d asm("r1");

    order_base = (u8 *)0x020321A4;
    *(u16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_0809AB44(2, 0, 0x1EF, 4, 4);
    func_080ECD34(0x081046A8, 0x06015840);
    func_08094330();
    func_08096308(0xF, 0x10);
    {
        register s16 *palette_slot_r1 asm("r1") = &sp18;
        register s32 palette_pool_r2 asm("r2") = 0xE3C0;
        register s32 palette_value_r0 asm("r0");

        asm volatile("" : "+r"(palette_slot_r1), "+r"(palette_pool_r2));
        palette_value_r0 = palette_pool_r2;
        asm volatile("" : "+r"(palette_value_r0));
        *palette_slot_r1 = (s16) palette_value_r0;
    }
    func_080ECD2C(&sp18, 0x06001800, 0x01000400);
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2380\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x009B\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1C19\n\t"
        ".endm");
    *(u16 *)0x0300004C |= 0x200;
    asm volatile(".purgem mov\n\t.purgem lsl\n\t.purgem add");
    asm volatile(
        ".set b48_io_ldr_fix, 0\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".if b48_io_ldr_fix == 0\n\t"
        ".short 0x492A\n\t"
        ".else\n\t"
        ".short 0x4E2A\n\t"
        ".purgem ldr\n\t"
        ".endif\n\t"
        ".set b48_io_ldr_fix, b48_io_ldr_fix + 1\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1C30\n\t"
        ".endm");
    *(s16 *)0x0400000A = 0x305;
    asm volatile(".purgem ldr\n\t.purgem add");
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
    {
        register u8 *counter_seed asm("r0") = (u8 *)0x02032272;

        *counter_seed = 0;
        var_r4 = 0;
        loop1_order_base = order_base;
        counter_ptr = counter_seed;
        loop1_slot_base = (u8 *)0x0203EBD0;
    }
loop_1:
    if ((func_080E9D88(0, var_r4) << 0x18) == 0) {
        goto block_3;
    }
    (*(u8 *)((*counter_ptr) + (s32)loop1_order_base)) = var_r4;
    *counter_ptr += 1;
    (*(u8 *)((var_r4) + (s32)loop1_slot_base)) = var_r4;
    goto block_4;
block_3:
    (*(u8 *)((var_r4) + (s32)loop1_slot_base)) = 0xFFU;
block_4:
    var_r4 += 1;
    if ((u32) var_r4 <= 5U) {
        goto loop_1;
    }
    func_0809AA64(0x087AC9D8, 0, 0x1C0, 0xC);
    var_r4 = 0;
    {
    register u8 *loop6_unit_seed asm("r7") = (u8 *)0x02034B4C;
    register u8 *loop6_unit_base asm("r9");

    loop6_unit_base = loop6_unit_seed;
    {
        register s32 coord_seed_r0 asm("r0") = 0x087A1F4C;

        asm volatile("" : "+r"(coord_seed_r0));
        coord_lo = coord_seed_r0;
    }
loop_6:
    {
        register s32 loop6_slot_seed asm("r0") = 0xA084;
        s32 loop6_slot_base;

        loop6_slot_seed += (s32)loop6_unit_base;
        loop6_slot_base = loop6_slot_seed;
        {
            register u8 *slot_ptr_r0 asm("r0") = var_r4 + loop6_slot_base;

            asm volatile("" : "+r"(slot_ptr_r0));
            sp40 = slot_ptr_r0;
            temp_r1 = *slot_ptr_r0;
        }
    }
    temp_r0 = temp_r1 * 0x270;
    temp_r6 = temp_r0 + (s32)loop6_unit_base;
    asm volatile(".include \"src/sub_080B484C_fix_loop6_dma.inc\""
        : "+r"(temp_r0));
    if (temp_r1 == 0xFF) {
        goto block_8;
    }
    {
        register s32 loop6_dma_offset_r5 asm("r5") = (s32) var_r4 << 22;

        func_0809A4CC(M2C_FIELD(temp_r6, u8 *, 0), M2C_FIELD(temp_r6, u8 *, 1), (u16) (loop6_dma_offset_r5 >> 16), (void *)(u32)var_r4);
    }
block_8:
    {
        register s32 gfx_a_r2 asm("r2") = 0x0821024C;
        register s32 gfx_b_r3 asm("r3") = 0x08210258;

        asm volatile("" : "+r"(gfx_a_r2), "+r"(gfx_b_r3));
        sprite_a = gfx_a_r2;
        sprite_b = gfx_b_r3;
    }
    {
        register s32 loop6_coord_index asm("r1") = (s32)var_r4 * 4;

        asm volatile("" : "+r"(loop6_coord_index));
        asm volatile(
            ".set b6_add_fix, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if b6_add_fix == 1\n\t"
            ".short 0x19C8\n\t"
            ".elseif b6_add_fix == 2\n\t"
            ".short 0x19C8\n\t"
            ".purgem add\n\t"
            ".endif\n\t"
            ".set b6_add_fix, b6_add_fix + 1\n\t"
            ".endm\n\t"
            ".set b6_mov_fix, 0\n\t"
            ".macro mov dst, args:vararg\n\t"
            ".if b6_mov_fix == 0\n\t"
            ".short 0x4657\n\t"
            ".elseif b6_mov_fix == 1\n\t"
            ".short 0x2700\n\t"
            ".else\n\t"
            ".short 0x2700\n\t"
            ".purgem mov\n\t"
            ".endif\n\t"
            ".set b6_mov_fix, b6_mov_fix + 1\n\t"
            ".endm\n\t"
            ".set b6_ldrsh_fix, 0\n\t"
            ".macro ldrsh dst, addr:vararg\n\t"
            ".if b6_ldrsh_fix == 0\n\t"
            ".short 0x5FC3\n\t"
            ".else\n\t"
            ".short 0x5FC0\n\t"
            ".purgem ldrsh\n\t"
            ".endif\n\t"
            ".set b6_ldrsh_fix, b6_ldrsh_fix + 1\n\t"
            ".endm\n\t"
            ".set b6_ldr_fix, 0\n\t"
            ".macro ldr dst, addr:vararg\n\t"
            ".if b6_ldr_fix == 0\n\t"
            ".short 0x4F0D\n\t"
            ".else\n\t"
            ".short 0x9D10\n\t"
            ".purgem ldr\n\t"
            ".endif\n\t"
            ".set b6_ldr_fix, b6_ldr_fix + 1\n\t"
            ".endm\n\t"
        ".macro lsr dst, lhs, rhs\n\t"
        ".short 0x0C28\n\t"
            ".purgem lsr\n\t"
            ".endm\n\t"
            ".macro ldrb dst, addr:vararg\n\t"
            ".short 0x7828\n\t"
            ".short 0x1C0D\n\t"
            ".purgem ldrb\n\t"
            ".endm");
        temp_r1_2 = loop6_coord_index;
    }
    temp_r0_2 = func_08094484(sprite_a, sprite_b, 0U, M2C_FIELD(temp_r1_2, s16 *, (s32)coord_lo), (s32) M2C_FIELD(temp_r1_2, s16 *, 0x087A1F4E), (u16) ((s32) var_r4 << 6), (void *)(u32)var_r4, (*sp40 == 0xFF) ? 0x20348 : 0x348, 0);
    {
        register void **loop6_state1_base asm("r1") = (void **)0x02032E8C;

        asm volatile("" : "+r"(loop6_state1_base));
        M2C_FIELD(temp_r1_2, void **, (s32)loop6_state1_base) = temp_r0_2;
    }
    M2C_FIELD(temp_r0_2, s16 *, 0xC) = 0xA0;
    sprite_c = 0x08105D14;
    sprite_d = 0x08105D50;
    asm volatile("" : "+r"(sprite_c), "+r"(sprite_d));
    {
        register s32 loop6_slot_check asm("r0") = 0xA084;

        loop6_slot_check += (s32)loop6_unit_base;
        loop6_slot_check = var_r4 + loop6_slot_check;
        if (*(u8 *)loop6_slot_check == 0xFF) {
            goto block_14;
        }
    }
    {
        register u8 *loop6_kind_ptr asm("r0") = temp_r6;

        loop6_kind_ptr += 0x38;
        var_r2 = *loop6_kind_ptr;
    }
    goto block_15;
block_14:
    var_r2 = 0;
block_15:
    asm volatile(
        ".include \"src/sub_080B484C_fix_block15_state2.inc\"\n\t"
        ".set b15_pad0, 0\n\t"
        ".set b15_pad1, 0\n\t"
        ".set b15_pad2, 0\n\t"
        ".set b15_pad3, 0\n\t"
        ".set b15_pad4, 0\n\t"
        ".set b15_pad5, 0\n\t"
        ".set b15_pad6, 0");
    M2C_FIELD(temp_r1_2, void **, 0x02032EBC) = func_08094484(sprite_c, sprite_d, var_r2, (s16) ((u16) M2C_FIELD(temp_r1_2, u16 *, (s32)coord_lo) + 4), (s32) (s16) ((u16) M2C_FIELD(temp_r1_2, u16 *, 0x087A1F4E) - 8), 0x385, 0xF, ((*(u8 *)({
        register s32 loop6_final_slot_seed asm("r0") = 0xA084;
        s32 loop6_final_slot;

        loop6_final_slot_seed += (s32)loop6_unit_base;
        loop6_final_slot = var_r4 + loop6_final_slot_seed;
        loop6_final_slot;
    })) == 0xFF) ? 0x20248 : 0x248, 0);
    asm volatile(".purgem mov\n\t.purgem add");
    var_r4 += 1;
    if ((u32) var_r4 > 5U) {
        goto block_20;
    }
    goto loop_6;
    }
block_20:
    func_080B460C();
    *(s32 *)0x02032B90 = 0;
    {
        register u8 *block20_unit_base asm("r3") = (u8 *)0x02034B4C;
        register s32 block20_slot_offset asm("r7") = 0xA084;
        register u8 *block20_slot_ptr asm("r1");
        register s32 block26_choice_r2 asm("r2");

        asm volatile("" : "+r"(block20_unit_base), "+r"(block20_slot_offset));
        block20_slot_ptr = block20_unit_base + block20_slot_offset;
        asm volatile("" : "+r"(block20_slot_ptr));
        temp_r0_3 = *block20_slot_ptr;
        if (temp_r0_3 == 0xFF) {
            goto block_23;
        }
        func_080B4684(temp_r0_3, 0);
        goto block_27;
    block_23:
        {
            register s32 block23_slot_offset asm("r0") = 0xA085;
            register u8 *block23_slot_ptr asm("r1");

            asm volatile("" : "+r"(block20_unit_base), "+r"(block23_slot_offset));
            block23_slot_ptr = block20_unit_base + block23_slot_offset;
            asm volatile("" : "+r"(block23_slot_ptr));
            asm volatile(
                ".macro ldrb dst, addr:vararg\n\t"
                ".short 0x7808\n\t"
                ".endm\n\t"
                ".set b23_lsl_fix, 0\n\t"
                ".macro lsl dst, lhs, rhs\n\t"
                ".if b23_lsl_fix == 0\n\t"
                ".short 0x0081\n\t"
                ".elseif b23_lsl_fix == 1\n\t"
                ".short 0x00C9\n\t"
                ".else\n\t"
                ".short 0x0109\n\t"
                ".endif\n\t"
                ".set b23_lsl_fix, b23_lsl_fix + 1\n\t"
                ".endm\n\t"
                ".set b23_add_fix, 0\n\t"
                ".macro add dst, args:vararg\n\t"
                ".if b23_add_fix == 0\n\t"
                ".short 0x1809\n\t"
                ".elseif b23_add_fix == 1\n\t"
                ".short 0x18C9\n\t"
                ".else\n\t"
                ".short 0x3138\n\t"
                ".endif\n\t"
                ".set b23_add_fix, b23_add_fix + 1\n\t"
                ".endm\n\t"
                ".macro sub dst, lhs, rhs\n\t"
                ".short 0x1A09\n\t"
                ".endm\n\t"
                ".macro cmp lhs, rhs\n\t"
                ".short 0x28FF\n\t"
                ".purgem cmp\n\t"
                ".endm");
            temp_r0_4 = *block23_slot_ptr;
        }
    block26_choice_r2 = 2;
    if (temp_r0_4 == 0xFF) {
        goto block_26;
    }
    if (M2C_FIELD(((temp_r0_4 * 0x270) + (s32)block20_unit_base), u8 *, 0x38) != 4) {
        goto block_26;
    }
    block26_choice_r2 = 1;
    asm volatile(".purgem ldrb\n\t.purgem lsl\n\t.purgem add\n\t.purgem sub");
block_26:
    func_080B4684(0xFFU, block26_choice_r2);
    }
block_27:
    func_080972C8();
    func_080ACA8C(6, 1, 1);
    func_080ACB5C(6);
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x21FF\n\t"
        ".endm\n\t"
        ".macro str src, addr:vararg\n\t"
        ".short 0x910B\n\t"
        ".endm");
    sp2C = 0xFF;
    asm volatile(".purgem mov\n\t.purgem str");
    sp34 = (s32) *(u8 *)0x020321A4;
    {
        register u32 block27_index_zero asm("r2") = 0;

        asm volatile("" : "+r"(block27_index_zero));
        var_r9 = block27_index_zero;
    }
    {
        register u8 *block27_state_ptr asm("r0") = (u8 *)0x0200A881;
        register u8 block27_state_zero asm("r3") = 0;

        *block27_state_ptr = block27_state_zero;
    }
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2500\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".set b28_cmp_fix, 0\n\t"
        ".macro cmp lhs, rhs\n\t"
        ".if b28_cmp_fix == 0\n\t"
        ".short 0x2D10\n\t"
        ".elseif b28_cmp_fix == 1\n\t"
        ".short 0x2D10\n\t"
        ".else\n\t"
        ".short 0x2D00\n\t"
        ".purgem cmp\n\t"
        ".endif\n\t"
        ".set b28_cmp_fix, b28_cmp_fix + 1\n\t"
        ".endm");
    var_r5 = 0;
loop_28:
    if (var_r5 != 0x10) {
        goto block_30;
    }
    goto block_41;
block_30:
    if (var_r5 > 0x10) {
        goto block_34;
    }
    if (var_r5 == 0) {
        goto block_36;
    }
    goto block_190;
block_34:
    asm volatile(
        ".macro cmp lhs, rhs\n\t"
        ".short 0x4285\n\t"
        ".purgem cmp\n\t"
        ".endm");
    if (var_r5 == 0x1000) {
        goto block_161;
    }
    goto block_190;
block_36:
    if (sp2C != 0xFF) {
        goto block_38;
    }
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x464F\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x00B9\n\t"
        ".purgem lsl\n\t"
        ".endm");
    temp_r1_3 = var_r9 * 4;
    {
        register s32 block36_value_r0 asm("r0");
        register s32 block36_arg3 asm("r3");
        register s32 block36_state_r5 asm("r5");

        asm volatile("" : "+r"(block36_state_r5));
        asm volatile(
            ".macro add dst, lhs, rhs\n\t"
            ".short 0x1888\n\t"
            ".purgem add\n\t"
            ".endm\n\t"
            ".macro ldrsh dst, addr:vararg\n\t"
            ".short 0x5F83\n\t"
            ".purgem ldrsh\n\t"
            ".endm");
        block36_arg3 = M2C_FIELD(temp_r1_3, s16 *, 0x087A1F4C);
        asm volatile(
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x4F0D\n\t"
            ".purgem ldr\n\t"
            ".endm\n\t"
            ".macro add dst, lhs, rhs\n\t"
            ".short 0x19C9\n\t"
            ".purgem add\n\t"
            ".endm\n\t"
            ".macro ldrsh dst, addr:vararg\n\t"
            ".short 0x5E88\n\t"
            ".purgem ldrsh\n\t"
            ".endm");
        block36_value_r0 = (s32) M2C_FIELD(temp_r1_3, s16 *, 0x087A1F4E);
        asm volatile(
            "str r0, [sp, #0]\n\t"
            "mov r0, #224\n\t"
            "lsl r0, r0, #1\n\t"
            "str r0, [sp, #4]\n\t"
            "mov r0, #12\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #96\n\t"
            "str r0, [sp, #12]\n\t"
            "str r5, [sp, #16]"
            : "+r"(block36_value_r0)
            : : "r1", "r2", "memory");
        block36_value_r0 = 0x087AC9E0;
        asm volatile("" : "+r"(block36_value_r0));
        sp20 = func_08094374(block36_value_r0, 0, 0, block36_arg3);
    }
    {
        s32 block36_offset = 0xFFEC;

        M2C_FIELD(sp20, u16 *, 0xA) = block36_offset;
    }
    {
        register void *block36_sp24_zero asm("r5") = NULL;

        asm volatile("" : "+r"(block36_sp24_zero));
        sp24 = block36_sp24_zero;
    }
    goto block_39;
block_38:
    temp_r0_5 = sp2C * 0x270;
    {
        register u8 *block38_unit_base asm("r7") = (u8 *)0x02034B4C;

        asm volatile("" : "+r"(block38_unit_base));
        sp1C = temp_r0_5 + (s32)block38_unit_base;
    }
    {
        register s32 block38_arg5_r4 asm("r4");

    {
        register s32 block38_call0 asm("r0") = *(u8 *)sp1C;
        register s32 block38_call1 asm("r1") = M2C_FIELD(sp1C, u8 *, 1);

        asm volatile(
            ".syntax unified\n\t"
            "movs %2, #192\n\t"
            "lsls %2, %2, #1\n\t"
            "adds r2, %2, #0\n\t"
            "movs r3, #6\n\t"
            "bl func_0809A4CC\n\t"
            ".syntax divided"
            : "+r"(block38_call0), "+r"(block38_call1), "=&r"(block38_arg5_r4)
            : : "r2", "r3", "lr", "cc", "memory");
        sp20 = (void *)block38_call0;
    }
    {
        register s32 block38_gfx_a asm("r0");
        register s32 block38_gfx_b asm("r1");
        register s32 block38_state_r5 asm("r5");

        asm volatile("" : "+r"(block38_state_r5));
        asm volatile(
            "str %1, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #6\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #164\n\t"
            "lsl r0, r0, #1\n\t"
            "str r0, [sp, #12]\n\t"
            "str %1, [sp, #16]"
            : : "r"(block38_arg5_r4), "r"(block38_state_r5)
            : "r0", "r1", "r2", "memory");
        block38_gfx_a = 0x0821024C;
        block38_gfx_b = 0x08210258;
        asm volatile("" : "+r"(block38_gfx_a), "+r"(block38_gfx_b));
        sp20 = func_08094484(block38_gfx_a, block38_gfx_b, 0U, 0);
    }
    }
    {
        u16 sprite_offset = 0xFFF8;

        M2C_FIELD(sp20, u16 *, 0xA) = sprite_offset;
        M2C_FIELD(sp20, u16 *, 8) = sprite_offset;
    }
    {
        register s32 block38b_gfx_a asm("r0");
        register s32 block38b_gfx_b asm("r1");
        register s32 block38b_arg4_r5 asm("r5");
        register u32 block38b_kind_r2 asm("r2") = M2C_FIELD(sp1C, u8 *, 0x38);
        register s32 block38b_stack_r0 asm("r0");

        asm volatile("" : "+r"(block38b_arg4_r5));
        asm volatile("str %0, [sp, #0]"
                     : : "r"(block38b_arg4_r5) : "r0", "memory");
        block38b_stack_r0 = 0x385;
        asm volatile(
            "str %0, [sp, #4]\n\t"
            "mov %0, #15\n\t"
            "str %0, [sp, #8]\n\t"
            "mov %0, #72\n\t"
            "str %0, [sp, #12]\n\t"
            "str %1, [sp, #16]"
            : "+r"(block38b_stack_r0)
            : "r"(block38b_arg4_r5)
            : "memory");
        block38b_gfx_a = 0x08105D14;
        block38b_gfx_b = 0x08105D50;
        asm volatile("" : "+r"(block38b_gfx_a), "+r"(block38b_gfx_b));
        sp24 = func_08094484(block38b_gfx_a, block38b_gfx_b, block38b_kind_r2, 0);
    }
    {
        u16 sprite_offset = 0xFFFC;
        register u16 *block38_sp24_owner asm("r5") = (u16 *)sp24;

        asm volatile("" : "+r"(block38_sp24_owner));
        block38_sp24_owner[4] = sprite_offset;
        sprite_offset -= 12;
        block38_sp24_owner[5] = sprite_offset;
    }
    {
        register s32 block38_sp20_value asm("r0");
        register s16 *block38_sp20_owner asm("r6");

        block38_sp20_value = 0xA0;
        asm volatile("" : "+r"(block38_sp20_value));
        block38_sp20_owner = (s16 *)sp20;
        asm volatile("" : "+r"(block38_sp20_owner)
            : "r"(block38_sp20_value));
        block38_sp20_owner[6] = (s16)block38_sp20_value;
    }
    {
        register u16 *block38_flag_owner asm("r7") = (u16 *)sp1C;
        register u32 block38_flags asm("r0");
        register u32 block38_mask_seed asm("r2");
        register u32 block38_mask asm("r1");

        asm volatile("ldrh %0, [%1, #4]"
            : "=r"(block38_flags)
            : "r"(block38_flag_owner)
            : "memory");
        block38_mask_seed = 0xFFFB;
        asm volatile("mov %0, %1"
            : "=r"(block38_mask)
            : "r"(block38_mask_seed));
        block38_flags &= block38_mask;
        asm volatile("strh %0, [%1, #4]"
            :
            : "r"(block38_flags), "r"(block38_flag_owner)
            : "memory");
    }
    {
        register u8 *block38_slot_base asm("r1") = (u8 *)0x0203EBD0;

        (*(u8 *)((var_r9) + (s32)block38_slot_base)) = 0xFFU;
    }
    {
        register s32 **block38_state1_base asm("r0") =
            (s32 **)D_02032E8C;
        register u32 block38_state_index asm("r1");
        register u32 block38_r3 asm("r3") = var_r9;
        u32 block38_state1_value;

        asm volatile("" : "+r"(block38_state1_base));
        asm volatile("lsl %0, %1, #2"
            : "=r"(block38_state_index)
            : "r"(block38_r3));
        temp_r2 = *(s32 **)(block38_state_index +
            (s32)block38_state1_base);
        block38_state1_value = *temp_r2;
        block38_r3 = 0x80;
        block38_r3 <<= 10;
        asm volatile("" : "+r"(block38_r3));
        block38_state1_value |= block38_r3;
        *temp_r2 = block38_state1_value;
        {
            register s32 **block38_state2_base asm("r0") =
                (s32 **)D_02032EBC;

            asm volatile("" : "+r"(block38_state2_base));
            block38_state_index += (u32)block38_state2_base;
            temp_r1_5 = *(s32 **)block38_state_index;
        }
        *temp_r1_5 |= block38_r3;
    }
    {
        register s8 *block38_state_ptr asm("r0") = (s8 *)0x02028200;

        block38_state_ptr += var_r9;
        {
            register s8 block38_state_zero asm("r5") = 0;

            *block38_state_ptr = block38_state_zero;
        }
    }
    func_080B460C();
    func_080972C8();
block_39:
    sp28 = 0xFF;
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2510\n\t"
        ".endm");
    var_r5 = 0x10;
    asm volatile(".purgem mov");
    goto block_190;
block_41:
    func_08096F3C();
loop_42:
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x9F0A\n\t"
        ".purgem ldr\n\t"
        ".endm\n\t"
        ".macro cmp lhs, rhs\n\t"
        ".short 0x45B9\n\t"
        ".purgem cmp\n\t"
        ".endm");
    if (var_r9 != sp28) {
        goto block_44;
    }
    asm volatile(".purgem ldr\n\t.purgem cmp");
    goto block_81;
block_44:
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x4648\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x0081\n\t"
        ".purgem lsl\n\t"
        ".endm");
    temp_r1_6 = var_r9 * 4;
    asm volatile(".purgem mov\n\t.purgem lsl");
    asm volatile(
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1888\n\t"
        ".purgem add\n\t"
        ".endm");
    temp_r2_7 = M2C_FIELD(temp_r1_6, u16 *, 0x087A1F4C);
    asm volatile(".purgem add");
    M2C_FIELD(sp20, u16 *, 4) = temp_r2_7;
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x4D0E\n\t"
        ".purgem ldr\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1948\n\t"
        ".purgem add\n\t"
        ".endm");
    M2C_FIELD(sp20, u16 *, 6) = (u16) M2C_FIELD(temp_r1_6, u16 *, 0x087A1F4E);
    asm volatile(".purgem ldr\n\t.purgem add");
    {
        register s32 block44_saved_r8 asm("r8");
        asm volatile("mov %0, r1" : "=r"(block44_saved_r8));
    }
    {
        register void *block44_sp24 asm("r6") = sp24;
    if (block44_sp24 == NULL) {
        goto block_46;
    }
        M2C_FIELD(block44_sp24, u16 *, 4) = temp_r2_7;
        M2C_FIELD(block44_sp24, u16 *, 6) = (u16) M2C_FIELD(sp20, u16 *, 6);
    }
block_46:
    {
        register u8 *neighbor_unit_base asm("r5");

        {
            register s32 block46_sp2c_r7 asm("r7") = sp2C;
            if (block46_sp2c_r7 != 0xFF) {
            goto block_63;
            }
        }
        neighbor_unit_base = (u8 *)0x02034B4C;
        {
        register s32 block46_slot_offset asm("r0") = 0xA084;
        register s32 block46_slot_base asm("r4");
        register u32 block46_slot_index asm("r2");
        register u8 *block46_slot_ptr asm("r1");

        asm volatile("" : "+r"(block46_slot_offset));
        block46_slot_base = (s32)neighbor_unit_base + block46_slot_offset;
        asm volatile("" : "+r"(block46_slot_base));
        block46_slot_index = var_r9;
        asm volatile("" : "+r"(block46_slot_index));
        block46_slot_ptr = (u8 *)(block46_slot_index + block46_slot_base);
        temp_r0_7 = *block46_slot_ptr;
        }
        if (temp_r0_7 == 0xFF) {
            goto block_50;
        }
        func_080B4684(temp_r0_7, 0);
        goto block_62;
block_50:
    {
    register s32 block61_choice asm("r2");

    asm volatile("movs r3, #3\n\t"
                 ".include \"src/sub_080B484C_fix_block50_result.inc\""
                 :
                 :
                 : "r3", "memory");
    temp_r0_8 = func_080ECF78(var_r9, 3);
    if (temp_r0_8 == 1) {
        goto block_54;
    }
    {
        register s32 block50_first_mask_r6 asm("r6") = 0x80;
        register s32 block50_first_mask_r0 asm("r0");
        register s32 block50_first_value_r7 asm("r7");

        block50_first_mask_r6 <<= 3;
        asm volatile("mov %0, %1"
            : "=r"(block50_first_mask_r0)
            : "r"(block50_first_mask_r6));
        asm volatile("ldr %0, [sp, #56]"
            : "=r"(block50_first_value_r7)
            : "g"(sp38)
            : "memory");
        block50_first_value_r7 |= block50_first_mask_r0;
        sp38 = block50_first_value_r7;
    }
    {
        register s32 block50_slot_base asm("r4");
        register u32 block50_slot_index asm("r2") = (u8) ((var_r9 - temp_r0_8) + 1);
        register u8 *block50_slot_ptr asm("r1");

        asm volatile("" : "+r"(block50_slot_index));
        block50_slot_ptr = (u8 *)(block50_slot_index + block50_slot_base);
        temp_r0_9 = *block50_slot_ptr;
    }
    if (temp_r0_9 == 0xFF) {
        goto block_59;
    }
    {
        register s32 block50_record_offset asm("r1");

        block50_record_offset = temp_r0_9 * 0x270;
        if (M2C_FIELD((block50_record_offset + (s32)neighbor_unit_base), u8 *, 0x38) != 4) {
            goto block_59;
        }
    }
    {
        register s32 block50_mask_r3 asm("r3") = 0xE0;
        register s32 block50_mask_r0 asm("r0");
        register s32 block50_value_r7 asm("r7");
        register s32 block50_value_r5 asm("r5");

        block50_mask_r3 <<= 2;
        asm volatile("" : "+r"(block50_mask_r3));
        block50_mask_r0 = block50_mask_r3;
        asm volatile("" : "+r"(block50_mask_r0));
        block50_value_r5 = block50_value_r7;
        asm volatile("" : "+r"(block50_value_r5));
        block50_value_r5 |= block50_mask_r0;
        sp38 = block50_value_r5;
    }
    block61_choice = 1;
    goto block_61;
block_54:
    {
        register s32 nb_lo asm("r0") = var_r9 - 1;
        register s32 block54_slot_base asm("r4");
        register u8 *block54_slot_ptr asm("r1");

        asm volatile("" : "+r"(nb_lo));
        block54_slot_ptr = (u8 *)(nb_lo + block54_slot_base);
        temp_r0_10 = *block54_slot_ptr;
    }
    if (temp_r0_10 == 0xFF) {
        goto block_56;
    }
    {
        register s32 block54_record_offset asm("r1");

        block54_record_offset = temp_r0_10 * 0x270;
        if (M2C_FIELD((block54_record_offset + (s32)neighbor_unit_base), u8 *, 0x38) != 0) {
            goto block_58;
        }
    }
block_56:
    {
        register s32 nb_hi asm("r0") = var_r9 + 1;
        register s32 block56_slot_base asm("r4");
        register u8 *block56_slot_ptr asm("r1");

        asm volatile("" : "+r"(nb_hi));
        block56_slot_ptr = (u8 *)((nb_hi) + block56_slot_base);
        temp_r0_11 = *block56_slot_ptr;
    }
    if (temp_r0_11 == 0xFF) {
        goto block_60;
    }
    {
        register s32 block56_record_offset asm("r1");

        block56_record_offset = temp_r0_11 * 0x270;
        if (M2C_FIELD((block56_record_offset + (s32)neighbor_unit_base), u8 *, 0x38) == 0) {
            goto block_60;
        }
    }
block_58:
    {
        register s32 block58_mask_r6 asm("r6") = 0x80;
        register s32 block58_mask_r0 asm("r0");
        register s32 block58_value_r7 asm("r7");
        register s32 block58_narrow_r0 asm("r0");

        block58_mask_r6 <<= 3;
        asm volatile("" : "+r"(block58_mask_r6));
        block58_mask_r0 = block58_mask_r6;
        asm volatile("" : "+r"(block58_mask_r0));
        block58_value_r7 = sp38;
        asm volatile("" : "+r"(block58_value_r7));
        block58_value_r7 |= block58_mask_r0;
        block58_narrow_r0 = block58_value_r7 << 16;
        sp38 = (u32) block58_narrow_r0 >> 16;
    }
block_59:
    block61_choice = 2;
    goto block_61;
block_60:
    block61_choice = 0;
block_61:
    func_080B4684(0xFFU, block61_choice);
    }
    }
block_62:
    func_080972C8();
    goto block_81;
block_63:
    {
        register u8 *block63_kind_ptr asm("r10");
        register u8 *block69_unit_base asm("r5");
        register s32 block69_slot_offset asm("r6");
        register u8 *block69_slot_base asm("r4");
        register u32 block69_index asm("r7");
        register u8 *block73_unit_base asm("r3");
        register u8 *block73_slot_base asm("r7");

        var_r4_3 = 0;
        {
            register u8 *block63_kind_seed asm("r0") = (u8 *)sp1C;

            block63_kind_seed += 0x38;
            asm volatile("" : "+r"(block63_kind_seed));
            block63_kind_ptr = block63_kind_seed;
            asm volatile("" : "+r"(block63_kind_ptr));
    }
    {
        register s32 block64_table_base asm("r7") = 0x087EDD54;
        register u8 *block64_unit_base asm("r6") = (u8 *)0x02034B4C;

loop_64:
    temp_r0_12 = var_r4_3 * 4;
    if (!(*M2C_FIELD(temp_r0_12, s32 **, 0x02032E8C) & 0x200000)) {
        goto block_66;
    }
    {
        register u8 *block64_slot_base asm("r3") = (u8 *)0x0203EBD0;

        func_080981F0((*(s32 *)((((*(u8 *)((((*(u8 *)((var_r4_3) + (s32)block64_slot_base)) * 0x270)) + (s32)block64_unit_base)) * 4)) + block64_table_base)), 0, 3, 0, var_r4_3 * 2);
    }
    temp_r2_3 = M2C_FIELD(temp_r0_12, s32 **, 0x02032E8C);
    {
        register s32 block64_state_value asm("r1") = *temp_r2_3;
        register s32 block64_state_mask asm("r0") = 0xFFDFFFFF;

        *temp_r2_3 = block64_state_value & block64_state_mask;
    }
block_66:
    var_r4_3 += 1;
    if ((u32) var_r4_3 <= 5U) {
        goto loop_64;
    }
    }
    func_080972C8();
    block69_unit_base = (u8 *)0x02034B4C;
    block69_slot_offset = 0xA084;
    block69_slot_base = block69_unit_base + block69_slot_offset;
    asm volatile(".include \"src/sub_080B484C_fix_block69_state.inc\""
        : "+r"(block69_slot_base));
    block69_index = var_r9;
    if (*(u8 *)((block69_index) + (s32)block69_slot_base) == 0xFF) {
        goto block_69;
    }
    temp_r1_7 = M2C_FIELD(temp_r1_6, s32 **, 0x02032E8C);
    *temp_r1_7 |= 0x200000;
block_69:
    {
        register u8 *block69_kind_ptr asm("r3") = block63_kind_ptr;

        block63_kind = *block69_kind_ptr;
    }
    if (block63_kind != 4) {
        goto block_76;
    }
    {
        register u32 block69_prev_index asm("r0") = var_r9;

        asm volatile("" : "+r"(block69_prev_index));
        block69_prev_index -= 1;
        temp_r2_4 = (u8)block69_prev_index;
    }
    {
        register u8 *block69_prev_slot_ptr asm("r0");

        block69_prev_slot_ptr = (u8 *)((temp_r2_4) + (s32)block69_slot_base);
        temp_r1_8 = *block69_prev_slot_ptr;
    }
    if (temp_r1_8 == 0xFF) {
        goto block_73;
    }
    if (M2C_FIELD(((temp_r1_8 * 0x270) + (s32)block69_unit_base), u8 *, 0x38) == 0) {
        goto block_73;
    }
    {
        register s32 *block69_prev_state_base asm("r5");
        s32 block69_prev_state_offset;

        block69_prev_state_offset = temp_r2_4 * 4;
        asm volatile(".short 0x4D14"
            : "=r"(block69_prev_state_base));
        temp_r1_9 = M2C_FIELD(block69_prev_state_offset, s32 **,
            (s32)block69_prev_state_base);
    }
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2680\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x03B6\n\t"
        ".endm\n\t"
        ".macro orr dst, lhs, rhs\n\t"
        ".short 0x4330\n\t"
        ".endm");
    *temp_r1_9 |= 0x200000;
    asm volatile(".purgem mov\n\t.purgem lsl\n\t.purgem orr");
block_73:
    temp_r2_5 = var_r9 + 1;
    block73_unit_base = (u8 *)0x02034B4C;
    block73_slot_base = (u8 *)0x0203EBD0;
    temp_r1_10 = (*(u8 *)((temp_r2_5) + (s32)block73_slot_base));
    if (temp_r1_10 == 0xFF) {
        goto block_81;
    }
    if (M2C_FIELD(((temp_r1_10 * 0x270) + (s32)block73_unit_base), u8 *, 0x38) == 0) {
        goto block_81;
    }
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x4905\n\t"
        ".purgem ldr\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1840\n\t"
        ".purgem add\n\t"
        ".endm");
    asm volatile("" ::: "memory");
    var_r1 = M2C_FIELD((temp_r2_5 * 4), s32 **, 0x02032E8C);
    var_r0_3 = *var_r1 | 0x200000;
    asm volatile("" : : "r"(var_r1));
    goto block_80;
block_76:
    if (block63_kind == 0) {
        goto block_81;
    }
    asm volatile(
        ".set b76_mov_fix, 0\n\t"
        ".macro mov dst, args:vararg\n\t"
        ".if b76_mov_fix == 0\n\t"
        ".short 0x4648\n\t"
        ".elseif b76_mov_fix == 1\n\t"
        ".short 0x2103\n\t"
        ".else\n\t"
        ".short 0x464B\n\t"
        ".purgem mov\n\t"
        ".endif\n\t"
        ".set b76_mov_fix, b76_mov_fix + 1\n\t"
        ".endm\n\t"
        ".macro sub dst, lhs, rhs\n\t"
        ".short 0x1A18\n\t"
        ".purgem sub\n\t"
        ".endm");
    temp_r2_6 = (var_r9 - func_080ECF78(var_r9, 3)) + 1;
    {
        register u8 *block76_slot_ptr asm("r0");

        block76_slot_ptr = (u8 *)((temp_r2_6) + (s32)block69_slot_base);
        temp_r1_11 = *block76_slot_ptr;
    }
    if (temp_r1_11 == 0xFF) {
        goto block_81;
    }
    if (M2C_FIELD(((temp_r1_11 * 0x270) + (s32)block69_unit_base), u8 *, 0x38) != 4) {
        goto block_81;
    }
    {
        register s32 block76_state_offset asm("r0");

        block76_state_offset = temp_r2_6;
        block76_state_offset <<= 2;
        asm volatile("" : "+r"(block76_state_offset));
        {
            register s32 *block76_state_base asm("r5");
            asm volatile(
                ".macro mov dst, src\n\t"
                ".short 0x4D17\n\t"
                ".purgem mov\n\t"
                ".endm");
            block76_state_base = (s32 *)0x02032E8C;

            asm volatile("" : "+r"(block76_state_base) : : "memory");
            var_r1 = M2C_FIELD(block76_state_offset, s32 **,
                (s32)block76_state_base);
        }
    }
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2680\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x03B6\n\t"
        ".endm\n\t"
        ".macro orr dst, lhs, rhs\n\t"
        ".short 0x4330\n\t"
        ".endm");
    var_r0_3 = *var_r1 | 0x200000;
    asm volatile(
        ".include \"src/sub_080B484C_fix_block81_pool.inc\"\n\t"
        ".set b81_pad0, 0\n\t"
        ".set b81_pad1, 0");
block_80:
    *var_r1 = var_r0_3;
    }
block_81:
    block81_state_ptr = (s32 *)0x02032E8C;
    temp_r2_7 = *block81_state_ptr;
    if (!(0x3F & temp_r2_7)) {
        goto block_84;
    }
    {
        register u32 block81_prev_r7 asm("r7") = sp28;

        asm volatile("" : "+r"(block81_prev_r7));
        if (block81_prev_r7 == var_r9) {
            goto block_89;
        }
    }
    temp_r2_7 &= 0x20;
    if (temp_r2_7) {
        goto block_89;
    }
block_84:
    var_r4_4 = 0;
    {
        register s32 **block84_state_base asm("r5") = (s32 **)0x03000078;
loop_85:
    if (!(*block84_state_base[var_r4_4] & 0x200000)) {
        goto block_87;
    }
    {
        register s32 block84_call_r0 asm("r0");

        block84_call_r0 = var_r4_4 * 2;
        asm volatile("str r0, [sp, #0]" : "+r"(block84_call_r0) : : "memory");
        block84_call_r0 = 0x08106238;
        asm volatile("" : "+r"(block84_call_r0));
        func_080981F0_4(block84_call_r0, 0, 3, 0);
    }
block_87:
    var_r4_4 += 1;
    if ((u32) var_r4_4 <= 5U) {
        goto loop_85;
    }
    func_080972C8();
    }
    goto block_97;
block_89:
    temp_r1_12 = *block81_state_ptr;
    if ((0x3F & temp_r1_12) == 0x20) {
        goto block_92;
    }
    {
        register u32 block89_prev_r2 asm("r2") = sp28;

        asm volatile("" : "+r"(block89_prev_r2));
        if (block89_prev_r2 == var_r9) {
            goto block_97;
        }
    }
    if (!(temp_r1_12 & 0x20)) {
        goto block_97;
    }
block_92:
    var_r4_5 = 0;
    {
        register s32 block92_table_base asm("r6") = 0x087EDD54;
        register u8 *block92_unit_base asm("r5") = (u8 *)0x02034B4C;

loop_93:
    {
        s32 block92_flags;
        register u32 block92_mask asm("r7");

        block92_flags = *M2C_FIELD((var_r4_5 * 4), s32 **, 0x02032E8C);
        block92_mask = 0x200000;
        asm volatile("" : "+r"(block92_mask) : "r"(block92_flags));
        if (!(block92_flags & block92_mask)) {
        goto block_95;
        }
    }
    {
        register u8 *block92_slot_base asm("r1") = (u8 *)0x0203EBD0;
        register u8 *block92_slot_addr asm("r0");

        asm volatile("" : "+r"(block92_slot_base));
        block92_slot_addr = (u8 *)((s32)var_r4_5 + (s32)block92_slot_base);
        func_080981F0(*(s32 *)(((s32)*(u8 *)(((s32)*block92_slot_addr * 0x270) + (s32)block92_unit_base) * 4) + block92_table_base), 0, 3, 0, var_r4_5 * 2);
    }
block_95:
    var_r4_5 += 1;
    if ((u32) var_r4_5 <= 5U) {
        goto loop_93;
    }
    func_080972C8();
    }
block_97:
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x464A\n\t"
        ".endm\n\t"
        ".macro str src, addr:vararg\n\t"
        ".short 0x920A\n\t"
        ".endm");
    sp28 = var_r9;
    asm volatile(".purgem mov\n\t.purgem str");
    func_080ED17C(1);
    if (!(0x40 & *(u16 *)0x03006034)) {
        goto block_103;
    }
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x9B0B\n\t"
        ".endm\n\t"
        ".macro cmp lhs, rhs\n\t"
        ".short 0x2BFF\n\t"
        ".endm");
    if (sp2C == 0xFF) {
        goto block_100;
    }
    asm volatile(".purgem ldr\n\t.purgem cmp");
    if (M2C_FIELD(sp1C, u8 *, 0x38) == 4) {
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
    {
        register u32 block106_state_r5 asm("r5") = sp2C;

        asm volatile("" : "+r"(block106_state_r5));
        if (block106_state_r5 == 0xFF) {
            goto block_106;
        }
    }
    if (M2C_FIELD(sp1C, u8 *, 0x38) == 4) {
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
    {
        register u32 block108_index_r6 asm("r6") = var_r9;

        asm volatile("" : "+r"(block108_index_r6));
        if (block108_index_r6 <= 2U) {
        goto block_111;
    }
    }
    var_r0_4 = var_r9 - 3;
    goto block_114;
block_111:
    if (!(0x10 & *nav_keys)) {
        goto block_115;
    }
    {
        register u32 block111_index_r7 asm("r7") = var_r9;

        asm volatile("" : "+r"(block111_index_r7));
        if (block111_index_r7 > 2U) {
        goto block_115;
    }
    }
    var_r0_4 = var_r9 + 3;
block_114:
    var_r9 = (u32) var_r0_4;
    func_08092E84(0x40);
    goto loop_42;
block_115:
    temp_r1_13 = *(u16 *)0x0300000E;
    if (1 & temp_r1_13) {
        goto block_117;
    }
    goto block_129;
block_117:
    {
        register s32 block117_state_r0 asm("r0") = sp2C;

        asm volatile("" : "+r"(block117_state_r0));
        if (block117_state_r0 != 0xFF) {
        goto block_123;
    }
    }
    {
        register u8 *block117_slot_base asm("r1") = (u8 *)0x0203EBD0;

        asm volatile("" : "+r"(block117_slot_base));
        temp_r0_14 = (*(u8 *)((var_r9) + (s32)block117_slot_base));
    }
    if (temp_r0_14 == 0xFF) {
        goto block_120;
    }
    {
        register u32 block117_selected asm("r1");

        asm volatile("mov %0, %1"
            : "=r"(block117_selected)
            : "r"(temp_r0_14));
        sp2C = (s32)block117_selected;
    }
    func_08094554(sp20);
    func_08092E84(0x3E);
    func_080ED17C(1);
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2500\n\t"
        ".endm");
    var_r5 = 0;
    asm volatile(".purgem mov");
    goto block_121;
block_120:
    {
        register s32 block120_arg_r3 asm("r3");
        register s32 block120_stack_r0 asm("r0");
        register s32 block120_gfx_a asm("r0");
        register s32 block120_gfx_b asm("r1");

    func_08098834(4);
    func_080B44A0(4, sp38);
    func_08094554(sp20);
    temp_r1_14 = var_r9 * 4;
    block120_arg_r3 = (s16) (M2C_FIELD(temp_r1_14, u16 *, 0x087A1F4C) - 4);
    temp_r1_2 = 0x087A1F4E;
    block120_stack_r0 = (s32) (s16) (M2C_FIELD(temp_r1_14, u16 *, temp_r1_2) - 0x28);
    asm volatile("str r0, [sp, #0]" : "+r"(block120_stack_r0) : : "memory");
    block120_stack_r0 = 0x2DF;
    asm volatile("str r0, [sp, #4]" : "+r"(block120_stack_r0) : : "memory");
    block120_stack_r0 = 0xF;
    asm volatile("str r0, [sp, #8]" : "+r"(block120_stack_r0) : : "memory");
    block120_stack_r0 = 0x60;
    asm volatile("str r0, [sp, #12]" : "+r"(block120_stack_r0) : : "memory");
    block120_stack_r0 = 0;
    asm volatile("str r0, [sp, #16]" : "+r"(block120_stack_r0) : : "memory");
    block120_gfx_a = 0x0810557C;
    block120_gfx_b = 0x081055B0;
    asm volatile("" : "+r"(block120_gfx_a), "+r"(block120_gfx_b));
    sp20 = func_08094484_4(block120_gfx_a, block120_gfx_b, 0, block120_arg_r3);
    }
    func_08092E84(0x3E);
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2580\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x016D\n\t"
        ".endm");
    var_r5 = 0x1000;
    asm volatile(".purgem mov\n\t.purgem lsl");
block_121:
    {
        register s32 block120_sp30_r6 asm("r6") = var_r9;

        asm volatile("" : "+r"(block120_sp30_r6));
        sp30 = block120_sp30_r6;
    }
    goto block_190;
block_123:
    {
        register s32 block123_state_offset asm("r8");

    func_08092E84(0x4E);
    var_r4 = 0;
    {
        register s32 block123_state_seed asm("r7") = var_r9;

        block123_state_seed <<= 2;
        block123_state_offset = block123_state_seed;
    }
    {
        register u8 *block123_kind_seed asm("r0") = (u8 *)sp1C;
        register u8 *block123_kind_ptr asm("r10");

        block123_kind_seed += 0x38;
        asm volatile("" : "+r"(block123_kind_seed));
        block123_kind_ptr = block123_kind_seed;
    {
        register u32 block123_event_seed asm("r1") = var_r9;

        asm volatile("" : "+r"(block123_event_seed));
        block123_event_seed <<= 22;
        asm volatile("" : "+r"(block123_event_seed));
        sp3C = block123_event_seed;
    }
    {
        register u8 *block123_unit_seed asm("r2") = (u8 *)0x02034B4C;

        asm volatile("" : "+r"(block123_unit_seed));
        {
        register u8 *block123_unit_base asm("ip") = block123_unit_seed;
        register u32 block123_clear_mask asm("r7") = 0x20000;

            asm volatile("" : "+r"(block123_clear_mask));
loop_124:
    temp_r6_2 = var_r4 * 4;
    asm volatile(".include \"src/sub_080B484C_fix_block124_state.inc\""
        :: "r"(temp_r6_2));
    temp_r2_8 = M2C_FIELD(temp_r6_2, s32 **, 0x02032E8C);
    temp_r1_15 = *temp_r2_8;
    {
        register u32 block124_flags_test asm("r0");
        register u32 block124_flags_mask asm("r3");

        asm volatile(
            "mov %0, %2\n\t"
            "mov %1, #128\n\t"
            "lsl %1, %1, #14"
            : "=r"(block124_flags_test), "=r"(block124_flags_mask)
            : "r"(temp_r1_15));
        if (!(block124_flags_test & block124_flags_mask)) {
            goto block_126;
        }
    }
    *temp_r2_8 = temp_r1_15 & 0xFFDFFFFF;
    {
        register u8 *block123_slot_seed asm("r0") = (u8 *)0x0203EBD0;
        register u8 *block123_slot_ptr asm("r3");

        asm volatile("" : "+r"(block123_slot_seed));
        block123_slot_ptr = (u8 *)((s32)var_r4 + (s32)block123_slot_seed);
        {
            register void *block123_record_r1 asm("r1") =
                ((*block123_slot_ptr) * 0x270) + (s32)block123_unit_base;

            M2C_FIELD(block123_record_r1, u16 *, 4) =
                (u16) (0xFFFB & M2C_FIELD(block123_record_r1, u16 *, 4));
        }
        *block123_slot_ptr = 0xFFU;
    }
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x6829\n\t"
        ".endm");
    temp_r1_17 = M2C_FIELD(temp_r6_2, s32 **, 0x02032E8C);
    asm volatile(".purgem ldr");
    *temp_r1_17 |= block123_clear_mask;
    {
        register u8 *block124_state2_base_r0 asm("r0") = (u8 *)0x02032EBC;

        asm volatile("" : "+r"(block124_state2_base_r0));
        temp_r1_18 = M2C_FIELD(temp_r6_2, s32 **,
            (s32)block124_state2_base_r0);
    }
    *temp_r1_18 |= block123_clear_mask;
    {
        register u8 *block124_state_base_r1 asm("r1") = (u8 *)0x02028200;
        register u8 *block124_state_address_r0 asm("r0");

            asm volatile("" : "+r"(block124_state_base_r1));
            block124_state_address_r0 = (u8 *)((s32)var_r4 +
                (s32)block124_state_base_r1);
            asm volatile("" : "+r"(block124_state_address_r0));
            {
                register s32 block124_state_zero_r2 asm("r2") = 0;

                asm volatile("" : "+r"(block124_state_zero_r2));
                *block124_state_address_r0 = (u8)block124_state_zero_r2;
            }
        }
block_126:
    var_r4 += 1;
    if ((u32) var_r4 <= 5U) {
        goto loop_124;
    }
        }
    }
    func_080ED17C(1);
    {
        register u8 *block123_tail_record_r3 asm("r3") = (u8 *)sp1C;

        asm volatile("" : "+r"(block123_tail_record_r3));
        M2C_FIELD(block123_tail_record_r3, u16 *, 4) =
            (u16) (M2C_FIELD(block123_tail_record_r3, u16 *, 4) | 4);
        asm volatile(
            ".include \"src/sub_080B484C_fix_block123_tail.inc\"\n\t"
            ".set b123_tail_pad0, 0\n\t"
            ".set b123_tail_pad1, 0\n\t"
            ".set b123_tail_pad2, 0\n\t"
            ".set b123_tail_pad3, 0\n\t"
            ".set b123_tail_pad4, 0\n\t"
            ".set b123_tail_pad5, 0\n\t"
            ".set b123_tail_pad6, 0\n\t"
            ".set b123_tail_pad7, 0\n\t"
            ".set b123_tail_pad8, 0\n\t"
            ".set b123_tail_pad9, 0\n\t"
            ".set b123_tail_pad10, 0\n\t"
            ".set b123_tail_pad11, 0\n\t"
            ".set b123_tail_pad12, 0\n\t"
            ".set b123_tail_pad13, 0");
        M2C_FIELD(var_r9, u8 *, 0x0203EBD0) = (u8)sp2C;
        asm volatile(".purgem add\n\t.purgem ldrb\n\t.set b123_tail_pad14, 0");
        {
            register u8 *block123_tail_state_base_r0 asm("r0") = (u8 *)0x02028200;

            asm volatile("" : "+r"(block123_tail_state_base_r0));
            M2C_FIELD(var_r9, s8 *, (s32)block123_tail_state_base_r0) = 0;
        }
        func_0809A4CC(M2C_FIELD(block123_tail_record_r3, u8 *, 0),
            M2C_FIELD(block123_tail_record_r3, u8 *, 1),
            (u16) (sp3C >> 0x10), (void *) var_r9);
    }
    temp_r1_19 = M2C_FIELD(block123_state_offset, s32 **, 0x02032E8C);
    *temp_r1_19 &= 0xFFFDFFFF;
    temp_r0_15 = M2C_FIELD(block123_state_offset, s32 **, 0x02032EBC);
    *temp_r0_15 &= 0xFFFDFFFF;
    {
        register u8 *block123_kind_view_r2 asm("r2") = block123_kind_ptr;

        asm volatile("" : "+r"(block123_kind_view_r2));
        func_08094564(temp_r0_15, *block123_kind_view_r2);
    }
    {
        register s32 block123_tail_sentinel_r3 asm("r3") = 0xFF;

        asm volatile("" : "+r"(block123_tail_sentinel_r3));
        sp2C = block123_tail_sentinel_r3;
    }
    func_08094554(sp20);
    func_08094554(sp24);
    func_080B460C();
    func_080972C8();
    asm volatile("" : : "g"(sp2C));
    goto block_189;
        }
    }
block_129:
    {
        u32 block129_mask = 2;

        block129_mask &= temp_r1_13;
        if (block129_mask) {
            goto block_131;
        }
    }
    goto loop_42;
block_131:
    {
        register s32 block131_state asm("r5") = sp2C;

        if (block131_state != 0xFF) {
            goto block_155;
        }
    }
    {
        register void *roster_i_r4 asm("r4") = NULL;

        asm volatile("" : "+r"(roster_i_r4));
        var_r4_7 = roster_i_r4;
    }
    {
        register u8 *block134_count_seed asm("r0") = (u8 *)0x02032272;
        register u8 *block134_count_ptr asm("r10");
        register u32 block134_initial_count asm("r1");

        block134_initial_count = *block134_count_seed;
        block134_count_ptr = block134_count_seed;
    if ((u32) var_r4_7 >= block134_initial_count) {
        goto block_140;
    }
    {
        register u32 block134_first_slot asm("r7") = *(u8 *)0x0203EBD0;
        register u8 *block134_order_base asm("r8") = (u8 *)0x020321A4;
        register u32 block134_count_limit asm("r6") = block134_initial_count;

loop_134:
    var_r3 = 0;
    {
        register u8 *block134_order_base_view asm("r0") = block134_order_base;
        register u8 *block134_order_entry asm("r1") = (u8 *)((s32)var_r4_7 + (s32)block134_order_base_view);
        register u32 block134_ordered asm("r0") = *block134_order_entry;

        if (block134_ordered == block134_first_slot) {
            goto block_138;
        }
    {
        register u8 *block134_order_ptr asm("r2") = block134_order_entry;
        register u8 *block134_slot_base asm("r5") = (u8 *)0x0203EBD0;

loop_136:
    var_r3 += 1;
    if ((u32) var_r3 > 5U) {
        goto block_138;
    }
    if ((*block134_order_ptr) != (*(u8 *)((var_r3) + (s32)block134_slot_base))) {
        goto loop_136;
    }
    }
    }
block_138:
    if (var_r3 == 6) {
        goto block_140;
    }
    var_r4_7 = (void *) (u8) (var_r4_7 + 1);
    if ((u32) var_r4_7 < block134_count_limit) {
        goto loop_134;
    }
    }
block_140:
    {
        register u8 *block134_final_count_ptr asm("r1") = block134_count_ptr;

        if (var_r4_7 != *block134_final_count_ptr) {
            goto block_154;
        }
    }
    }
    {
        register u32 block142_value asm("r3");

        func_08092E84(0x3F);
        asm volatile(".include \"src/sub_080B484C_fix_block142_slot.inc\""
            : "=r"(block142_value));
    {
        register u32 block142_index asm("r4") = 0;
        register u8 *block142_slot_base asm("r10") = (u8 *)0x0203EBD0;
        register u32 block142_next_index asm("r8");

loop_142:
    {
        register u8 *block142_slot_view asm("r5") = block142_slot_base;
        register u32 block142_slot_value asm("r0");

        block142_slot_value = block142_slot_view[block142_index];
        {
            register u32 block142_next_seed asm("r6") = block142_index + 1;

            block142_next_index = block142_next_seed;
        }
        if (block142_slot_value != 0xFF) {
            goto block_152;
        }
    }
    {
        register u8 *block142_count_seed asm("r6") = (u8 *)0x02032272;
        register u32 block142_count asm("r7");
        register u8 *block142_order_seed asm("r0");
        register u8 *block142_order_base asm("ip");
        register u8 *block142_count_ptr asm("r9");
        register u32 block142_next_value asm("r5");

        block142_count = *block142_count_seed;
        sp40 = (u8 *)(u32)block142_count;
        block142_order_seed = (u8 *)0x020321A4;
        block142_order_base = block142_order_seed;
        block142_count_ptr = block142_count_seed;
loop_144:
    var_r1_2 = 0;
    block142_next_value = block142_value + 1;
        if ((u32)var_r1_2 >= (u32)sp40) {
        goto block_151;
    }
    {
        register volatile u8 *block142_initial_order asm("r7") = (volatile u8 *)block142_order_base;
        register u32 block142_initial_value asm("r0");

        asm volatile("" : "+r"(block142_initial_order));
        asm volatile("ldrb %0, [%1]"
            : "=r"(block142_initial_value)
            : "r"(block142_initial_order));
        if (block142_initial_value == block142_value) {
            goto block_149;
        }
    }
    {
        register u32 block142_loop_count asm("r2") = *block142_count_ptr;

        asm volatile("" : "+r"(block142_loop_count));
loop_147:
        var_r1_2 += 1;
        if ((u32)var_r1_2 >= block142_loop_count) {
            goto block_151;
        }
        {
            register u8 *block142_loop_order asm("r7") = block142_order_base;

            asm volatile("" : "+r"(block142_loop_order));
            if (*(u8 *)((s32)var_r1_2 + (s32)block142_loop_order) != block142_value) {
                goto loop_147;
            }
        }
    }
block_149:
    if ((u32)var_r1_2 >= *block142_count_seed) {
        goto block_151;
    }
    {
        register u32 block142_next asm("r0") = block142_value + 1;

        block142_next <<= 24;
        block142_value = block142_next >> 24;
    }
    goto loop_144;
block_151:
    {
        register u8 *block142_slot_write_base asm("r1") = block142_slot_base;
        register u8 *block142_slot_write asm("r0");

        asm volatile("" : "+r"(block142_slot_write_base));
        block142_slot_write = (u8 *)((u32)block142_index +
            (u32)block142_slot_write_base);
        asm volatile("" : "+r"(block142_slot_write));
        *block142_slot_write = block142_value;
    }
    {
        register u32 block142_value_shift asm("r0") = block142_next_value << 24;

        asm volatile("" : "+r"(block142_value_shift));
        block142_value = block142_value_shift >> 24;
    }
    }
block_152:
    {
        register u32 block142_index_seed asm("r2") = block142_next_index;
        register u32 block142_index_shift asm("r0");

        asm volatile("" : "+r"(block142_index_seed));
        block142_index_shift = block142_index_seed << 24;
        asm volatile("" : "+r"(block142_index_shift));
        block142_index = block142_index_shift >> 24;
    }
    if (block142_index <= 5U) {
        goto loop_142;
    }
    goto block_191;
    }
    }
block_154:
    func_08092E84(0x58);
    func_08098BB4(0x0800299D);
    goto loop_42;
block_155:
    var_r4_9 = 0;
    asm volatile(
        ".set b155_ldr_fix, 0\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".if b155_ldr_fix == 0\n\t"
        ".short 0x4F1C\n\t"
        ".elseif b155_ldr_fix == 1\n\t"
        ".short 0x4E1C\n\t"
        ".else\n\t"
        ".short 0x4B1C\n\t"
        ".purgem ldr\n\t"
        ".endif\n\t"
        ".set b155_ldr_fix, b155_ldr_fix + 1\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x18C5\n\t"
        ".purgem add\n\t"
        ".endm");
    {
        register s32 block155_table_base asm("r7") = 0x087EDD54;
        register u8 *block155_unit_base asm("r6") = (u8 *)0x02034B4C;

loop_156:
    {
        register s32 block155_offset asm("r0") = var_r4_9 * 4;
        register s32 *block155_state_base asm("r3") = (s32 *)0x02032E8C;
        register s32 **block155_state_entry asm("r5") = (s32 **)(block155_offset + (s32)block155_state_base);

        if (!(**block155_state_entry & 0x200000)) {
            goto block_158;
        }
        {
            register u8 *block155_slot_base asm("r2") = (u8 *)0x0203EBD0;

            func_080981F0((*(s32 *)((((*(u8 *)((((*(u8 *)((var_r4_9) + (s32)block155_slot_base)) * 0x270)) + (s32)block155_unit_base)) * 4)) + block155_table_base)), 0, 3, 0, var_r4_9 * 2);
        }
        temp_r2_9 = *block155_state_entry;
        {
            register s32 block155_state_value asm("r1") = *temp_r2_9;
            register s32 block155_state_mask asm("r0") = 0xFFDFFFFF;

            *temp_r2_9 = block155_state_value & block155_state_mask;
        }
    }
block_158:
    var_r4_9 += 1;
    if ((u32) var_r4_9 <= 5U) {
        goto loop_156;
    }
    }
    func_080972C8();
    func_08092E84(0x3F);
    sp2C = 0xFF;
    func_08094554(sp20);
    func_08094554(sp24);
    goto block_189;
block_161:
    {
        register u8 *block161_kind_ptr asm("r10");

        {
            register u8 *block161_unit_base asm("r4");

    sp1C = sp34 * 0x270;
    block161_unit_base = (u8 *)0x02034B4C;
    sp1C += (s32)block161_unit_base;
    func_080B4684((u8) sp34, 0);
    func_080B43B4(6, *(u8 *)0x0200A881);
    func_08098BB4(0x08002850);
    {
        register u8 *block161_order_base asm("r1") = order_base;
        u32 block161_order_index;

        asm volatile("" : "+r"(block161_order_base));
        block161_order_index = *(u8 *)0x0200A880;
        block161_order_index += (u32)block161_order_base;
        sp34 = (s32)*(u8 *)block161_order_index;
    }
    temp_r0_17 = *(u8 *)0x0200A882;
    if (temp_r0_17 == 1) {
        goto block_167;
    }
    if ((s32) temp_r0_17 > 1) {
        goto block_164;
    }
    goto block_190;
block_164:
    if (temp_r0_17 != 2) {
        goto block_166;
    }
    goto block_188;
block_166:
    goto block_190;
block_167:
    {
        register u16 *block167_flag_owner asm("r7") = (u16 *)sp1C;
        register u32 block167_flags asm("r0");
        register u32 block167_mask_seed asm("r2");
        register u32 block167_mask asm("r1");
        register u8 *block161_kind_seed asm("r0");

        asm volatile("ldrh %0, [%1, #4]"
            : "=r"(block167_flags)
            : "r"(block167_flag_owner)
            : "memory");
        block167_mask_seed = 0xFFFE;
        asm volatile("mov %0, %1"
            : "=r"(block167_mask)
            : "r"(block167_mask_seed));
        block167_flags &= block167_mask;
        asm volatile("strh %0, [%1, #4]"
            :
            : "r"(block167_flags), "r"(block167_flag_owner)
            : "memory");
        block161_kind_seed = (u8 *)block167_flag_owner;
        block161_kind_seed += 0x38;
        asm volatile("" : "+r"(block161_kind_seed));
        temp_r1_21 = *block161_kind_seed;
        block161_kind_ptr = block161_kind_seed;
        asm volatile("" : "+r"(block161_kind_ptr));
    }
    if (temp_r1_21 != 4) {
        goto block_176;
    }
    if (func_080ECF78(sp30, 3) == 1) {
        goto block_171;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08002A14);
    goto block_190;
block_171:
    {
        register s32 slot_lo asm("r0") = sp30 - 1;

        asm volatile("" : "+r"(slot_lo));
        {
            register u8 *block171_slot_base asm("r3") = (u8 *)0x0203EBD0;

            asm volatile("" : "+r"(block171_slot_base));
            temp_r1_22 = (*(u8 *)((slot_lo) + (s32)block171_slot_base));
            {
                register s32 slot_hi asm("r0") = sp30 + 1;

                asm volatile("" : "+r"(slot_hi));
                temp_r2_10 = (*(u8 *)((slot_hi) + (s32)block171_slot_base));
            }
        }
    }
    if (temp_r1_22 == 0xFF) {
        goto block_173;
    }
    if (M2C_FIELD(((temp_r1_22 * 0x270) + (s32)block161_unit_base), u8 *, 0x38) != 0) {
        goto block_175;
    }
block_173:
    if (temp_r2_10 == 0xFF) {
        goto block_181;
    }
    if (M2C_FIELD(((temp_r2_10 * 0x270) + (s32)block161_unit_base), u8 *, 0x38) == 0) {
        goto block_181;
    }
block_175:
    func_08092E84(0x58);
    func_08098BB4(0x08002A9E);
    goto block_190;
block_176:
    if (temp_r1_21 == 0) {
        goto block_181;
    }
    {
        register s32 block176_index asm("r0");
        u8 block176_distance;

        block176_distance = func_080ECF78(sp30, 3);
        {
            register s32 block176_sp30_r6 asm("r6") = sp30;

            asm volatile("" : "+r"(block176_sp30_r6));
            block176_index = block176_sp30_r6 - block176_distance;
        }
        block176_index += 1;
        {
            register u8 *block176_slot_base asm("r7") = (u8 *)0x0203EBD0;

            asm volatile("" : "+r"(block176_slot_base));
            temp_r1_23 = *(u8 *)((block176_index) + (s32)block176_slot_base);
        }
    }
    if (temp_r1_23 == 0xFF) {
        goto block_181;
    }
    if (M2C_FIELD(((temp_r1_23 * 0x270) + (s32)block161_unit_base), u8 *, 0x38) != 4) {
        goto block_181;
    }
    func_08092E84(0x58);
    func_08098BB4(0x08002B4E);
    goto block_190;
    }
block_181:
    {
        register s32 temp_r5 asm("r5");
        register u32 block181_event_x asm("r6");
        register s32 block181_unit_index asm("r1");
        register u32 block181_flags_r1 asm("r1");
        u32 block181_flag_mask;

    func_08092E84(0x4E);
    asm volatile(
        "ldr r0, [sp, #28]\n\t"
        "ldrh r1, [r0, #4]"
        : "=r"(block181_flags_r1)
        :
        : "r0", "cc", "memory");
    block181_flag_mask = 4;
    block181_flag_mask &= block181_flags_r1;
    {
        register u32 block181_slot asm("r1") = sp30;

        block181_event_x = block181_slot << 0x16;
        temp_r5 = block181_slot * 4;
    }
    if (!block181_flag_mask) {
        goto block_187;
    }
    var_r4_10 = 0;
    {
        register u8 *block181_first_slot_base asm("r2") = (u8 *)0x0203EBD0;
        u8 block181_first_slot;

        block181_first_slot = *block181_first_slot_base;
        {
        register s32 *block181_state1_base asm("r3") = (s32 *)0x02032E8C;
        register s32 *block181_state2_base asm("r8");

        {
            register s32 block181_state2_seed asm("r7") = 0x02032EBC;

            block181_state2_base = (s32 *)block181_state2_seed;
        }

    block181_unit_index = sp34 * 4;
    if (block181_first_slot == sp34) {
        goto block_186;
    }
    {
        register u8 *block181_scan_slot_base asm("r2") = (u8 *)0x0203EBD0;

loop_184:
    var_r4_10 += 1;
    if ((u32) var_r4_10 > 5U) {
        goto block_186;
    }
    {
        register u32 block181_scan_value asm("r0");
        register s32 block181_scan_target asm("r7");

        block181_scan_value = *(u8 *)((var_r4_10) + (s32)block181_scan_slot_base);
        asm volatile("" : "+r"(block181_scan_value));
        block181_scan_target = sp34;
        asm volatile("" : "+r"(block181_scan_target));
        if (block181_scan_value != block181_scan_target) {
            goto loop_184;
        }
    }
    }
block_186:
    {
        register s32 block186_kind asm("r2") = sp34;
        register s32 block186_offset asm("r0") = block181_unit_index + block186_kind;

        block186_offset <<= 3;
        block186_offset -= block186_kind;
        block186_offset <<= 4;
        {
            register u8 *block186_unit_base asm("r7") = (u8 *)0x02034B4C;

        block186_offset += (s32)block186_unit_base;
        temp_r0_18 = (void *)block186_offset;
        }
        {
            register u32 block186_flags asm("r1") = M2C_FIELD(temp_r0_18, u16 *, 4);
            register u32 block186_mask_seed asm("r7") = 0xFFFB;
            register u32 block186_mask asm("r2") = block186_mask_seed;

            asm volatile("" : "+&r"(block186_mask) : "r"(block186_mask_seed));
            M2C_FIELD(temp_r0_18, u16 *, 4) = (u16)(block186_flags & block186_mask);
        }
    }
    {
        register u8 *block186_slot_base asm("r0") = (u8 *)0x0203EBD0;
        register u8 *block186_slot_ptr asm("r1");

        asm volatile("" : "+r"(block186_slot_base));
        block186_slot_ptr = var_r4_10 + (s32)block186_slot_base;
        asm volatile("" : "+r"(block186_slot_ptr));
        *block186_slot_ptr = 0xFFU;
    {
        register s32 block181_state_index asm("r1") = var_r4_10 * 4;

        {
            register s32 *block181_state1_entry asm("r0") = (s32 *)(block181_state_index + (s32)block181_state1_base);

            asm volatile("" : "+r"(block181_state1_entry));
            temp_r2_11 = *(s32 **)block181_state1_entry;
        }
        *temp_r2_11 |= 0x20000;
        temp_r1_25 = *(s32 **)((s32)block181_state2_base + block181_state_index);
        *temp_r1_25 |= 0x20000;
    }
        {
            register u8 *block186_state_base_r1 asm("r1") = (u8 *)0x02028200;

            asm volatile("" : "+r"(block186_state_base_r1));
            block186_slot_base = (u8 *)((s32)var_r4_10 +
                (s32)block186_state_base_r1);
            asm volatile("" : "+r"(block186_slot_base));
            {
                register s32 block186_state_zero_r2 asm("r2") = 0;

                asm volatile("" : "+r"(block186_state_zero_r2));
                *block186_slot_base = (u8)block186_state_zero_r2;
            }
        }
        }
        }
    }
block_187:
    {
        register u8 *block187_unit asm("r3") = (u8 *)sp1C;

        M2C_FIELD(block187_unit, u16 *, 4) = (u16) (M2C_FIELD(block187_unit, u16 *, 4) | 4);
    }
    {
        register u32 block187_slot_index asm("r7") = sp30;
        register u8 *block187_slot_base asm("r1") = (u8 *)0x0203EBD0;
        register u8 *block187_slot_ptr asm("r0");

        asm volatile("" : "+r"(block187_slot_index), "+r"(block187_slot_base));
        block187_slot_ptr = block187_slot_index + (s32)block187_slot_base;
        asm volatile("" : "+r"(block187_slot_ptr));
        asm volatile(
            ".macro add dst, args:vararg\n\t"
            ".short 0xAA0D\n\t"
            ".purgem add\n\t"
            ".endm\n\t"
            ".macro ldrb dst, addr:vararg\n\t"
            ".short 0x7812\n\t"
            ".purgem ldrb\n\t"
            ".endm");
        {
            register u8 block187_slot_value_r2 asm("r2") = (u8)sp34;

            asm volatile("" : "+r"(block187_slot_value_r2));
            *block187_slot_ptr = block187_slot_value_r2;
        }
        {
            register u8 *block187_state_base_r3 asm("r3") = (u8 *)0x02028200;

            asm volatile("" : "+r"(block187_state_base_r3));
            block187_slot_ptr = (u8 *)((s32)block187_slot_index +
                (s32)block187_state_base_r3);
            asm volatile("" : "+r"(block187_slot_ptr));
            block187_slot_index = 0;
            asm volatile("" : "+r"(block187_slot_index));
            *block187_slot_ptr = (u8)block187_slot_index;
        }
    }
    func_0809A4CC(M2C_FIELD(sp1C, u8 *, 0), M2C_FIELD(sp1C, u8 *, 1), (u16) (block181_event_x >> 0x10), (void *) sp30);
    {
        register u8 *block187_state1_base_r0 asm("r0") = (u8 *)0x02032E8C;

        asm volatile("" : "+r"(block187_state1_base_r0));
        temp_r1_26 = M2C_FIELD(temp_r5, s32 **,
            (s32)block187_state1_base_r0);
        *temp_r1_26 &= 0xFFFDFFFF;
        block187_state1_base_r0 = (u8 *)0x02032EBC;
        asm volatile("" : "+r"(block187_state1_base_r0));
        temp_r0_19 = M2C_FIELD(temp_r5, s32 **,
            (s32)block187_state1_base_r0);
        *temp_r0_19 &= 0xFFFDFFFF;
    }
    {
        register u8 *block187_kind_ptr asm("r2") = block161_kind_ptr;
        register u32 block187_kind asm("r1") = *block187_kind_ptr;

        func_08094564(temp_r0_19, block187_kind);
    }
    func_08094554(sp20);
    func_080ACB5C(6);
    func_080B460C();
    func_080972C8();
    goto block_189;
    }
    }
block_188:
    func_080971AC(3);
    func_080972C8();
    func_08094554(sp20);
    func_080ACB5C(6);
block_189:
    asm volatile(
        ".macro mov dst, imm\n\t"
        ".short 0x2500\n\t"
        ".endm");
    var_r5 = 0;
    asm volatile(".purgem mov");
block_190:
    {
        register s32 tail_guard_r3 asm("r3") = 0;

        asm volatile("" : "+r"(tail_guard_r3));
        if (tail_guard_r3 != 0) {
            goto block_191;
        }
    }
    goto loop_28;
block_191:
    func_08096308(0x10, 0x10);
    goto loop_193;
block_192:
    func_080ED17C(1);
loop_193:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_192;
    }
    return;
}
