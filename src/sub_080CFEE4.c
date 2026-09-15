#include "m2c_prelude.h"

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E74(u8);                          /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
void *func_08094484(s32, s32, s32, s16, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08095114(s32);                         /* extern */
M2C_UNK func_0809538C(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809A1BC(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
s32 func_0809A35C(u8, u8, s32, s32, s32, s32);      /* extern */
M2C_UNK func_080ECD34(M2C_UNK, s32);                /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
extern u8 D_02034B4C[];
asm(".set D_02033FCC, 0x02033FCC");
extern u8 D_02033FCC;
asm(".set D_02033F55, 0x02033F55");
extern u8 D_02033F55;

asm(
    ".set CFEE4_ADD_COUNT, 0\n"
    ".macro CFEE4_INSTALL_ADD\n"
    ".macro add args:vararg\n"
    ".purgem add\n"
    ".set CFEE4_ADD_COUNT, CFEE4_ADD_COUNT + 1\n"
    ".if CFEE4_ADD_COUNT == 1\n"
    ".short 0xB08A\n"
    ".elseif CFEE4_ADD_COUNT == 24\n"
    ".short 0x1880\n"
    ".elseif CFEE4_ADD_COUNT == 25\n"
    ".short 0x18C0\n"
    ".elseif CFEE4_ADD_COUNT == 26\n"
    ".short 0x1840\n"
    ".elseif CFEE4_ADD_COUNT == 27\n"
    ".short 0x1880\n"
    ".elseif CFEE4_ADD_COUNT == 31\n"
    ".short 0x18D0\n"
    ".elseif CFEE4_ADD_COUNT == 35\n"
    ".short 0x3220\n"
    ".elseif CFEE4_ADD_COUNT == 36\n"
    ".short 0x4499\n"
    ".elseif CFEE4_ADD_COUNT == 37\n"
    ".short 0x3060\n"
    ".elseif CFEE4_ADD_COUNT == 41\n"
    ".short 0x448A\n"
    ".elseif CFEE4_ADD_COUNT == 44\n"
    ".short 0x444D\n"
    ".elseif CFEE4_ADD_COUNT == 45\n"
    ".short 0x1940\n"
    ".elseif CFEE4_ADD_COUNT == 47\n"
    ".short 0xB00A\n"
    ".else\n"
    "add \\args\n"
    ".endif\n"
    ".if CFEE4_ADD_COUNT < 47\n"
    "CFEE4_INSTALL_ADD\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_ADD\n");

asm(
    ".set CFEE4_CMP_COUNT, 0\n"
    ".macro CFEE4_INSTALL_CMP\n"
    ".macro cmp args:vararg\n"
    ".purgem cmp\n"
    ".set CFEE4_CMP_COUNT, CFEE4_CMP_COUNT + 1\n"
    ".if CFEE4_CMP_COUNT == 7\n"
    ".short 0x2F20\n"
    ".elseif CFEE4_CMP_COUNT == 8\n"
    ".short 0x2F20\n"
    ".elseif CFEE4_CMP_COUNT == 9\n"
    ".short 0x2F00\n"
    ".elseif CFEE4_CMP_COUNT == 10\n"
    ".short 0x2F10\n"
    ".elseif CFEE4_CMP_COUNT == 11\n"
    ".short 0x2F40\n"
    ".elseif CFEE4_CMP_COUNT == 12\n"
    ".short 0x2F40\n"
    ".elseif CFEE4_CMP_COUNT == 13\n"
    ".short 0x2F30\n"
    ".elseif CFEE4_CMP_COUNT == 14\n"
    ".short 0x2F50\n"
    ".elseif CFEE4_CMP_COUNT == 18\n"
    ".short 0x4281\n"
    ".elseif CFEE4_CMP_COUNT == 19\n"
    ".short 0x4A08\n"
    ".short 0x2800\n"
    ".elseif CFEE4_CMP_COUNT == 37\n"
    ".short 0x280F\n"
    ".elseif CFEE4_CMP_COUNT == 42\n"
    ".short 0x4282\n"
    ".elseif CFEE4_CMP_COUNT == 49\n"
    ".short 0x4A09\n"
    ".short 0x2800\n"
    ".elseif CFEE4_CMP_COUNT == 53\n"
    ".short 0x9909\n"
    ".short 0x2800\n"
    ".elseif CFEE4_CMP_COUNT == 54\n"
    ".short 0x2900\n"
    ".else\n"
    "cmp \\args\n"
    ".endif\n"
    ".if CFEE4_CMP_COUNT < 54\n"
    "CFEE4_INSTALL_CMP\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_CMP\n");

asm(
    ".set CFEE4_MOV_COUNT, 0\n"
    ".macro CFEE4_INSTALL_MOV\n"
    ".macro mov args:vararg\n"
    ".purgem mov\n"
    ".set CFEE4_MOV_COUNT, CFEE4_MOV_COUNT + 1\n"
    ".if CFEE4_MOV_COUNT == 39\n"
    ".short 0x2700\n"
    ".elseif CFEE4_MOV_COUNT == 42\n"
    ".short 0x4641\n"
    ".elseif CFEE4_MOV_COUNT == 43\n"
    ".short 0x2280\n"
    ".elseif CFEE4_MOV_COUNT == 44\n"
    ".short 0x2380\n"
    ".elseif CFEE4_MOV_COUNT == 46\n"
    ".short 0x20A0\n"
    ".elseif CFEE4_MOV_COUNT == 47\n"
    ".short 0x4643\n"
    ".elseif CFEE4_MOV_COUNT == 49\n"
    ".short 0x2710\n"
    ".elseif CFEE4_MOV_COUNT == 50\n"
    ".short 0x4642\n"
    ".elseif CFEE4_MOV_COUNT == 53\n"
    ".short 0x4643\n"
    ".elseif CFEE4_MOV_COUNT == 54\n"
    ".short 0x4641\n"
    ".elseif CFEE4_MOV_COUNT == 55\n"
    ".short 0x2720\n"
    ".elseif CFEE4_MOV_COUNT == 58\n"
    ".short 0x2730\n"
    ".elseif CFEE4_MOV_COUNT == 60\n"
    ".short 0x4641\n"
    ".elseif CFEE4_MOV_COUNT == 64\n"
    ".short 0x4642\n"
    ".elseif CFEE4_MOV_COUNT == 65\n"
    ".short 0x4643\n"
    ".elseif CFEE4_MOV_COUNT == 66\n"
    ".short 0x2740\n"
    ".elseif CFEE4_MOV_COUNT == 68\n"
    ".short 0x4641\n"
    ".elseif CFEE4_MOV_COUNT == 69\n"
    ".short 0x2340\n"
    ".elseif CFEE4_MOV_COUNT == 70\n"
    ".short 0x464A\n"
    ".elseif CFEE4_MOV_COUNT == 71\n"
    ".short 0x4653\n"
    ".elseif CFEE4_MOV_COUNT == 72\n"
    ".short 0x469A\n"
    ".elseif CFEE4_MOV_COUNT == 75\n"
    ".short 0x4641\n"
    ".elseif CFEE4_MOV_COUNT == 78\n"
    ".short 0x2750\n"
    ".elseif CFEE4_MOV_COUNT == 79\n"
    ".short 0x4641\n"
    ".elseif CFEE4_MOV_COUNT == 82\n"
    ".short 0x4643\n"
    ".else\n"
    "mov \\args\n"
    ".endif\n"
    ".if CFEE4_MOV_COUNT < 89\n"
    "CFEE4_INSTALL_MOV\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_MOV\n");

asm(
    ".set CFEE4_LDR_COUNT, 0\n"
    ".macro CFEE4_INSTALL_LDR\n"
    ".macro ldr args:vararg\n"
    ".purgem ldr\n"
    ".set CFEE4_LDR_COUNT, CFEE4_LDR_COUNT + 1\n"
    ".if CFEE4_LDR_COUNT == 26\n"
    ".short 0x4838\n"
    ".elseif CFEE4_LDR_COUNT == 27\n"
    ".short 0x4C39\n"
    ".elseif CFEE4_LDR_COUNT == 45\n"
    ".short 0x490A\n"
    ".elseif CFEE4_LDR_COUNT == 47\n"
    ".short 0x4A09\n"
    ".elseif CFEE4_LDR_COUNT == 48\n"
    ".short 0x6821\n"
    ".elseif CFEE4_LDR_COUNT == 49\n"
    ".short 0x6821\n"
    ".elseif CFEE4_LDR_COUNT == 50\n"
    ".short 0x480A\n"
    ".elseif CFEE4_LDR_COUNT == 57\n"
    ".short 0x4B0B\n"
    ".elseif CFEE4_LDR_COUNT == 67\n"
    ".short 0x9A07\n"
    ".elseif CFEE4_LDR_COUNT == 69\n"
    ".short 0x9808\n"
    ".elseif CFEE4_LDR_COUNT == 73\n"
    ".short 0x9908\n"
    ".elseif CFEE4_LDR_COUNT == 77\n"
    ".short 0x9808\n"
    ".elseif CFEE4_LDR_COUNT == 88\n"
    ".short 0x9D07\n"
    ".elseif CFEE4_LDR_COUNT == 93\n"
    ".short 0x9905\n"
    ".else\n"
    "ldr \\args\n"
    ".endif\n"
    ".if CFEE4_LDR_COUNT < 96\n"
    "CFEE4_INSTALL_LDR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_LDR\n");

asm(
    ".set CFEE4_LDRB_COUNT, 0\n"
    ".macro CFEE4_INSTALL_LDRB\n"
    ".macro ldrb args:vararg\n"
    ".purgem ldrb\n"
    ".set CFEE4_LDRB_COUNT, CFEE4_LDRB_COUNT + 1\n"
    ".if CFEE4_LDRB_COUNT == 8\n"
    ".short 0x7808\n"
    ".elseif CFEE4_LDRB_COUNT == 11\n"
    ".short 0x7818\n"
    ".elseif CFEE4_LDRB_COUNT == 13\n"
    ".short 0x7810\n"
    ".elseif CFEE4_LDRB_COUNT == 15\n"
    ".short 0x7818\n"
    ".elseif CFEE4_LDRB_COUNT == 16\n"
    ".short 0x7808\n"
    ".elseif CFEE4_LDRB_COUNT == 20\n"
    ".short 0x7808\n"
    ".elseif CFEE4_LDRB_COUNT == 22\n"
    ".short 0x7810\n"
    ".elseif CFEE4_LDRB_COUNT == 23\n"
    ".short 0x7818\n"
    ".elseif CFEE4_LDRB_COUNT == 24\n"
    ".short 0x7808\n"
    ".elseif CFEE4_LDRB_COUNT == 27\n"
    ".short 0x7808\n"
    ".elseif CFEE4_LDRB_COUNT == 29\n"
    ".short 0x7808\n"
    ".elseif CFEE4_LDRB_COUNT == 31\n"
    ".short 0x7818\n"
    ".else\n"
    "ldrb \\args\n"
    ".endif\n"
    ".if CFEE4_LDRB_COUNT < 32\n"
    "CFEE4_INSTALL_LDRB\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_LDRB\n");

asm(
    ".set CFEE4_LSL_COUNT, 0\n"
    ".macro CFEE4_INSTALL_LSL\n"
    ".macro lsl args:vararg\n"
    ".purgem lsl\n"
    ".set CFEE4_LSL_COUNT, CFEE4_LSL_COUNT + 1\n"
    ".if CFEE4_LSL_COUNT == 17\n"
    ".short 0x0052\n"
    ".elseif CFEE4_LSL_COUNT == 18\n"
    ".short 0x009B\n"
    ".elseif CFEE4_LSL_COUNT == 19\n"
    ".short 0x0180\n"
    ".elseif CFEE4_LSL_COUNT == 21\n"
    ".short 0x0408\n"
    ".else\n"
    "lsl \\args\n"
    ".endif\n"
    ".if CFEE4_LSL_COUNT < 22\n"
    "CFEE4_INSTALL_LSL\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_LSL\n");

asm(
    ".set CFEE4_SUB_COUNT, 0\n"
    ".macro CFEE4_INSTALL_SUB\n"
    ".macro sub args:vararg\n"
    ".purgem sub\n"
    ".set CFEE4_SUB_COUNT, CFEE4_SUB_COUNT + 1\n"
    ".if CFEE4_SUB_COUNT == 8\n"
    ".short 0x1A80\n"
    ".elseif CFEE4_SUB_COUNT == 9\n"
    ".short 0x1A1B\n"
    ".elseif CFEE4_SUB_COUNT == 10\n"
    ".short 0x1B40\n"
    ".else\n"
    "sub \\args\n"
    ".endif\n"
    ".if CFEE4_SUB_COUNT < 11\n"
    "CFEE4_INSTALL_SUB\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_SUB\n");

asm(
    ".set CFEE4_STR_COUNT, 0\n"
    ".macro CFEE4_INSTALL_STR\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    ".set CFEE4_STR_COUNT, CFEE4_STR_COUNT + 1\n"
    ".if CFEE4_STR_COUNT == 29\n"
    ".short 0x9207\n"
    ".elseif CFEE4_STR_COUNT == 30\n"
    ".short 0x9008\n"
    ".else\n"
    "str \\args\n"
    ".endif\n"
    ".if CFEE4_STR_COUNT < 40\n"
    "CFEE4_INSTALL_STR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_STR\n");

asm(
    ".set CFEE4_LSR_COUNT, 0\n"
    ".macro CFEE4_INSTALL_LSR\n"
    ".macro lsr args:vararg\n"
    ".purgem lsr\n"
    ".set CFEE4_LSR_COUNT, CFEE4_LSR_COUNT + 1\n"
    ".if CFEE4_LSR_COUNT == 3\n"
    ".short 0x0C00\n"
    ".else\n"
    "lsr \\args\n"
    ".endif\n"
    ".if CFEE4_LSR_COUNT < 3\n"
    "CFEE4_INSTALL_LSR\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_LSR\n");

asm(
    ".set CFEE4_NEG_COUNT, 0\n"
    ".macro CFEE4_INSTALL_NEG\n"
    ".macro neg args:vararg\n"
    ".purgem neg\n"
    ".set CFEE4_NEG_COUNT, CFEE4_NEG_COUNT + 1\n"
    ".if CFEE4_NEG_COUNT == 2\n"
    ".short 0x425B\n"
    ".else\n"
    "neg \\args\n"
    ".endif\n"
    ".if CFEE4_NEG_COUNT < 2\n"
    "CFEE4_INSTALL_NEG\n"
    ".endif\n"
    ".endm\n"
    ".endm\n"
    "CFEE4_INSTALL_NEG\n");

void sub_080CFEE4(void) {
    volatile s32 sp14;
    void *sp18;
    s32 sp1C;
    s32 sp20;
    u8 *sp24;
    s32 var_r0_3;
    s32 temp_r0;
    s32 temp_r5;
    s32 var_r0;
    s32 var_r0_10;
    s32 var_r0_2;
    s32 var_r0_9;
    s32 var_r7;
    register s32 var_r9 asm("r9");
    register s32 var_sl asm("sl");
    u16 *var_r4;
    u16 temp_r0_2;
    register s32 state48_frame asm("r1");
    s32 var_r0_5;
    s32 var_r0_7;
    s32 var_r0_8;
    u16 var_r1_2;
    register u16 vram_mask asm("r3");
    u16 vram_limit;
    register u8 *var_r1_3 asm("r1");
    register u8 *exit_flag asm("r8");
    u8 *exit_setup;
    u8 *state0_side;
    s32 *state0_camera;
    s32 state0_camera_value;
    s32 state0_threshold;
    u8 *state0_exit_check;
    u8 *state16_side;
    u16 state16_frame;
    u8 *state48_side;
    u8 *state64_side;
    s32 *state64_camera;
    register s32 state64_camera_value asm("r1");
    register s32 state64_threshold asm("r0");
    u8 *state64_exit_check;
    s32 *state80_camera;
    register s32 temp_r2 asm("r2");
    u8 temp_r2_2;
    u8 temp_r3;
    void *temp_r1;
    void *temp_r6;
    void *var_r1;
    register s32 constructor_asset asm("r4");
    register s32 constructor_aux asm("r1");
    *(s16 *)0x0300004C = 0x1340;
    M2C_FIELD((void *)0x04000008, s16 *, 0) = 0x4086;
    M2C_FIELD((void *)0x04000008, s16 *, 2) = 0x20B;
    if (D_02034B4C[0x27A4] != 0) {
        goto block_2;
    }
    var_r1 = (void *)0x03000054;
    var_r0 = 0xFFFF6800;
    goto block_3;
block_2:
    var_r1 = (void *)0x03000054;
    var_r0 = 0xA800;
block_3:
    M2C_FIELD(var_r1, s32 *, 0) = var_r0;
    M2C_FIELD(var_r1, s32 *, 4) = 0;
    M2C_FIELD(var_r1, s32 *, 8) = 0;
    M2C_FIELD(var_r1, s32 *, 0xC) = 0xFFFFD000;
    var_r9 = 0;
    sp1C = 0;
    func_08094330();
    temp_r2 = D_02034B4C[0x27A4];
    var_sl = 0x600;
    if (temp_r2 != 0) {
        goto block_5;
    }
    var_sl = 0xEA00;
block_5:
    constructor_asset = 0x083C713C;
    constructor_aux = 0x083C71DC;
    var_r0_2 = var_sl;
    if (var_r0_2 >= 0) {
        goto block_7;
    }
    var_r0_2 += 0xFF;
block_7:
    temp_r0 = var_r0_2 >> 8;
    if (temp_r2 != 0) {
        goto block_10;
    }
    var_r0_3 = temp_r0 + 0x240;
    goto block_11;
block_10:
    var_r0_3 = temp_r0 + 0xFFFFFDC0;
block_11:
    temp_r6 = func_08094484(constructor_asset, constructor_aux, 0, var_r0_3,
                           0x50, 0x180, 3,
                           D_02034B4C[0x27A4] != 0 ? 0x8018 : 0x18, 0);
    sp20 = 0;
    func_080ECD34(0x083C422C, 0x06013000);
    func_0809A1BC(0x083C5338, 0x05000260, 0x02002880);
    func_080ECD34(0x083C71E0, 0x06008000);
    func_080ECD34(0x083C77FC,
                  (s32) (var_r4 = (u16 *)0x06001000));
    var_r1_2 = 0;
    {
        register u32 vram_mask_seed asm("r0") = 0x4000;
        asm volatile("" : "+r"(vram_mask_seed));
        vram_mask = vram_mask_seed;
    }
    vram_limit = 0x3FF;
loop_16:
    *var_r4 |= vram_mask;
    var_r4++;
    var_r1_2 += 1;
    if (var_r1_2 <= vram_limit) {
        goto loop_16;
    }
    *(s16 *)0x05000000 = 0;
    temp_r3 = D_02034B4C[0x27A4];
    temp_r1 = D_02034B4C + (temp_r3 * 0x1380) + (D_02034B4C[0x27A5] * 0x270);
    sp18 = temp_r1;
    *(s32 *)0x02033F3C = func_0809A35C(M2C_FIELD(temp_r1, u8 *, 0), M2C_FIELD(temp_r1, u8 *, 1), 1, 0, (s32) temp_r3, 0x02002880);
    func_0809538C(1, 0xF0, 0x50, 1, 0xF0, 0x50A0, 0, 0x3F);
    *(s8 *)0x02033F54 = 1;
    D_02033F55 = 0;
    *(s16 *)0x0300004E = 0;
    exit_setup = &D_02033FCC;
    *exit_setup = 0;
    func_08092D8C(2, 0x080CFD99);
    func_08092E74(0x16U);
    var_r7 = 0;
    {
        register s32 done_zero asm("r3") = 0;
        asm volatile("" : "+r"(done_zero));
        sp14 = done_zero;
    }
    exit_flag = exit_setup;
loop_18:
    if (var_r7 != 0x20) {
        goto block_20;
    }
    goto block_72;
block_20:
    if (var_r7 > 0x20) {
        goto block_26;
    }
    if (var_r7 == 0) {
        goto block_35;
    }
    if (var_r7 != 0x10) {
        goto block_24;
    }
    goto block_51;
block_24:
    goto block_122;
block_26:
    if (var_r7 != 0x40) {
        goto block_28;
    }
    goto block_92;
block_28:
    if (var_r7 > 0x40) {
        goto block_32;
    }
    if (var_r7 != 0x30) {
        goto block_31;
    }
    goto block_74;
block_31:
    goto block_122;
block_32:
    if (var_r7 != 0x50) {
        goto block_34;
    }
    goto block_114;
block_34:
    goto block_122;
block_35:
    if (*exit_flag == 0) {
        goto block_37;
    }
    goto block_124;
block_37:
    state0_side = (u8 *)0x020372F0;
    state0_camera = (s32 *)0x03000054;
loop_38:
    if (*state0_side != 0) {
        goto block_40;
    }
    state0_camera[0] += 0x100;
    state0_camera[2] += 0x200;
    var_r0_5 = M2C_FIELD(temp_r6, u16 *, 4) - 3;
    goto block_41;
block_40:
    state0_camera[0] -= 0x100;
    state0_camera[2] -= 0x200;
    var_r0_5 = M2C_FIELD(temp_r6, u16 *, 4) + 3;
block_41:
    M2C_FIELD(temp_r6, u16 *, 4) = var_r0_5;
    func_080ED17C(1);
    if (*state0_side != 0) {
        goto block_44;
    }
    state0_camera_value = state0_camera[0];
    state0_threshold = 0x2800;
    goto block_45;
block_44:
    state0_camera_value = state0_camera[0];
    state0_threshold = -0x1800;
block_45:
    state0_exit_check = &D_02033FCC;
    if (state0_camera_value == state0_threshold) {
        goto block_47;
    }
    if (*exit_flag == 0) {
        goto loop_38;
    }
block_47:
    if (*state0_exit_check == 0) {
        goto block_49;
    }
    goto block_124;
block_49:
    M2C_FIELD(temp_r6, s32 *, 0) = (s32) (M2C_FIELD(temp_r6, s32 *, 0) & ~8);
    var_r7 = 0x10;
    goto block_122;
block_51:
    state16_frame = M2C_FIELD(temp_r6, u16 *, 0x14);
    if ((u32) state16_frame > 0xBU) {
        goto block_69;
    }
    if (*exit_flag == 0) {
        goto block_54;
    }
    goto block_124;
block_54:
    state16_side = (u8 *)0x020372F0;
loop_55:
    if (state16_frame != 0) {
        goto block_58;
    }
    M2C_FIELD(temp_r6, u16 *, 6) = (u16) (M2C_FIELD(temp_r6, u16 *, 6) + 2);
    goto block_63;
block_58:
    if ((u32) (u16) (state16_frame - 6) > 2U) {
        goto block_63;
    }
    if (*state16_side != 0) {
        goto block_61;
    }
    var_r0_7 = M2C_FIELD(temp_r6, u16 *, 4) - 1;
    goto block_62;
block_61:
    var_r0_7 = M2C_FIELD(temp_r6, u16 *, 4) + 1;
block_62:
    M2C_FIELD(temp_r6, u16 *, 4) = var_r0_7;
block_63:
    if (M2C_FIELD(temp_r6, u16 *, 0x16) != 0) {
        goto block_67;
    }
    temp_r0_2 = M2C_FIELD(temp_r6, u16 *, 0x14);
    if (temp_r0_2 == 1) {
        goto block_66;
    }
    if (temp_r0_2 != 9) {
        goto block_67;
    }
block_66:
    func_08092E84(0x59);
block_67:
    func_080ED17C(1);
    state16_frame = M2C_FIELD(temp_r6, u16 *, 0x14);
    if ((u32) state16_frame > 0xBU) {
        goto block_69;
    }
    if (*exit_flag == 0) {
        goto loop_55;
    }
block_69:
    if (*exit_flag == 0) {
        goto block_71;
    }
    goto block_124;
block_71:
    var_r7 = 0x20;
    goto block_122;
block_72:
    func_08095114(*(void **)0x02033F3C);
    *(void **)0x02033F3C = (void *)func_0809A35C(
        D_02034B4C[0x270E], M2C_FIELD(sp18, u8 *, 1), 1, 0,
        (s32)D_02034B4C[0x27A4], 0x02002880);
    var_r7 = 0x30;
    goto block_122;
block_74:
    if (M2C_FIELD(temp_r6, s32 *, 0) & 4) {
        goto block_89;
    }
    if (*exit_flag == 0) {
        goto block_77;
    }
    goto block_124;
block_77:
    state48_side = (u8 *)0x020372F0;
loop_78:
    {
        register u32 state48_frame_load asm("r0") =
            M2C_FIELD(temp_r6, u16 *, 0x14);
        asm volatile("" : "+r"(state48_frame_load));
        state48_frame = state48_frame_load;
    }
    if ((u32) state48_frame > 0xEU) {
        goto block_84;
    }
    if (*state48_side != 0) {
        goto block_82;
    }
    var_r0_8 = M2C_FIELD(temp_r6, u16 *, 4) + 1;
    goto block_83;
block_82:
    var_r0_8 = M2C_FIELD(temp_r6, u16 *, 4) - 1;
block_83:
    M2C_FIELD(temp_r6, u16 *, 4) = var_r0_8;
block_84:
    if (M2C_FIELD(temp_r6, u16 *, 0x16) != 0) {
        goto block_87;
    }
    if ((u16) state48_frame != 0xF) {
        goto block_87;
    }
    func_08092E84(0x59);
block_87:
    func_080ED17C(1);
    if (M2C_FIELD(temp_r6, s32 *, 0) & 4) {
        goto block_89;
    }
    if (*exit_flag == 0) {
        goto loop_78;
    }
block_89:
    if (*exit_flag == 0) {
        goto block_91;
    }
    goto block_124;
block_91:
    var_r7 = 0x40;
    goto block_122;
block_92:
    func_08092E84(0x68);
    if (*exit_flag == 0) {
        goto block_94;
    }
    goto block_124;
block_94:
    state64_side = (u8 *)0x020372F0;
    state64_camera = (s32 *)0x03000054;
loop_95:
    if (sp1C > 0xFFF) {
        goto block_97;
    }
    sp1C += 0x20;
block_97:
    if (var_r9 <= -0x800) {
        goto block_99;
    }
    var_r9 -= 0x40;
    sp20 += 0x60;
block_99:
    if (*state64_side != 0) {
        goto block_102;
    }
    state64_camera[0] += sp1C + var_r9;
    state64_camera[2] += var_r9;
    var_sl += sp20;
    goto block_103;
block_102:
    state64_camera[0] -= sp1C + var_r9;
    state64_camera[2] -= var_r9;
    var_sl -= sp20;
block_103:
    var_r0_9 = var_sl;
    if (var_r0_9 >= 0) {
        goto block_105;
    }
    var_r0_9 += 0xFF;
block_105:
    M2C_FIELD(temp_r6, u16 *, 4) = (u16) (var_r0_9 >> 8);
    func_080ED17C(1);
    if (*state64_side != 0) {
        goto block_109;
    }
    state64_camera_value = state64_camera[0];
    state64_threshold = 0xFFFF;
    state64_exit_check = &D_02033FCC;
    if (state64_camera_value > state64_threshold) {
        goto block_111;
    }
    goto block_110;
block_109:
    state64_camera_value = state64_camera[0];
    state64_threshold = -0xF000;
    state64_exit_check = &D_02033FCC;
    if (state64_camera_value <= state64_threshold) {
        goto block_111;
    }
block_110:
    if (*exit_flag == 0) {
        goto loop_95;
    }
block_111:
    temp_r2_2 = *state64_exit_check;
    if (temp_r2_2 != 0) {
        goto block_124;
    }
    {
        register s32 state64_reset_speed asm("r3") = 0x800;
        asm volatile("" : "+r"(state64_reset_speed));
        sp1C = state64_reset_speed;
    }
    *(u8 *)0x02033F54 = 2;
    D_02033F55 = temp_r2_2;
    var_r7 = 0x50;
    goto block_122;
block_114:
    if (*exit_flag != 0) {
        goto block_121;
    }
    var_r1_3 = (u8 *)0x020372F0;
    state80_camera = (s32 *)0x03000054;
    temp_r5 = sp1C + var_r9;
loop_116:
    if (*var_r1_3 != 0) {
        goto block_119;
    }
    state80_camera[0] += temp_r5;
    var_r0_10 = state80_camera[2] + var_r9;
    goto block_120;
block_119:
    state80_camera[0] -= temp_r5;
    var_r0_10 = state80_camera[2] - var_r9;
block_120:
    state80_camera[2] = var_r0_10;
    asm volatile(
        ".macro bl target\n\t"
        ".short 0x9109\n\t"
        ".purgem bl\n\t"
        "bl \\target\n\t"
        ".endm");
    func_080ED17C(1);
    if (*exit_flag == 0) {
        goto loop_116;
    }
block_121:
    sp14 = 1;
block_122:
    if (sp14 != 0) {
        goto block_124;
    }
    goto loop_18;
block_124:
    func_08092E0C(2);
    *(s32 *)0x02021690 = 9;
    *(s8 *)0x02033F35 = 0;
    func_08092E74(*(u8 *)0x02032EF8);
    return;
}
