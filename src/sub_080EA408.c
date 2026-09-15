#include "m2c_prelude.h"

M2C_UNK func_080BE65C(u8, u8, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080BE9D8(u8, u8, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
u8 func_080BF464(u8, u8, s32);                      /* extern */
M2C_UNK func_080C02B4(u8, u8);                      /* extern */
s32 func_080E522C(s32, s32);                        /* extern */
s32 func_080E7AE0(u8, u8, s32);                     /* extern */
M2C_UNK func_080E8B08(u8, u8);                      /* extern */
s32 func_080E9D88(u8, u8);                          /* extern */

asm(
    ".macro EA408_NEG_STAGE3\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r8, r1\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_NEG_STAGE2\n"
    ".macro neg dst, src\n"
    ".purgem neg\n"
    "neg r1, r1\n"
    "EA408_NEG_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_PATCH_NEG_R1\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r1, #1\n"
    "EA408_NEG_STAGE2\n"
    ".endm\n"
    ".endm\n");

asm(
    ".macro EA408_SEL_STAGE9\n"
    ".macro lsl dst, lhs, rhs\n"
    ".purgem lsl\n"
    "lsl r4, r0, #24\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_SEL_STAGE8\n"
    ".macro eor dst, args:vararg\n"
    ".purgem eor\n"
    "eor r0, r1\n"
    "EA408_SEL_STAGE9\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_SEL_STAGE7\n"
    ".macro add dst, args:vararg\n"
    ".purgem add\n"
    "add r0, r6, #0\n"
    "EA408_SEL_STAGE8\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_SEL_STAGE6\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r1, #1\n"
    "EA408_SEL_STAGE7\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_SEL_STAGE5\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r9, r3\n"
    "EA408_SEL_STAGE6\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_SEL_STAGE4\n"
    ".macro lsl dst, lhs, rhs\n"
    ".purgem lsl\n"
    "lsl r3, r6, #2\n"
    "EA408_SEL_STAGE5\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_SEL_STAGE3\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r5, #0\n"
    "EA408_SEL_STAGE4\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_SEL_STAGE2\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r8, r2\n"
    "EA408_SEL_STAGE3\n"
    ".endm\n"
    ".endm\n"
    ".macro EA408_PATCH_SELECTION_INIT\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r2, #0\n"
    "EA408_SEL_STAGE2\n"
    ".endm\n"
    ".endm\n");

void sub_080EA408(s32 arg0, s32 arg1) {
    u8 choices[6];
    void *sp20;
    s16 temp_r1_5;
    s32 temp_r1_6;
    u8 temp_r0;
    u8 temp_r5;
    u8 temp_r6;
    u8 temp_r7;
    u8 var_r5;
    u8 var_r5_2;
    u8 var_r8;
    u32 opposite_shifted;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r1;
    void *temp_r4_2;

    arg0 <<= 24;
    temp_r6 = (u32)arg0 >> 24;
    arg1 <<= 24;
    temp_r7 = (u32)arg1 >> 24;
    {
        u32 row_offset;
        u32 col_offset;
        register u8 *base asm("r2");

        row_offset = temp_r6 * 0x1380;
        col_offset = temp_r7 * 0x270;
        asm volatile("ldr %0, .LEA408_BASE_POOL" : "=r"(base));
        col_offset += (u32)base;
        temp_r1 = row_offset + col_offset;
    }
    sp20 = temp_r1 + 0xB0;
    asm volatile("" : : "m"(sp20));
    if (func_080BF464(temp_r6, temp_r7, 0x17) == 0xFF) {
        goto block_2;
    }
    goto block_34;
block_2:
    asm volatile("EA408_PATCH_NEG_R1");
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 0x17, 0, 0, 0);
    if ((func_080E7AE0(temp_r6, temp_r7, 6) << 0x10) == 0) {
        goto block_4;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 0x1D, 0, 0, 0);
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 0x23, 0, 0, 0);
block_4:
    if ((func_080E7AE0(temp_r6, temp_r7, 7) << 0x10) == 0) {
        goto block_6;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 2, 0x64, 0, 0);
block_6:
    if ((func_080E7AE0(temp_r6, temp_r7, 8) << 0x10) == 0) {
        goto block_8;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 2, 0xC8, 0, 0);
block_8:
    if ((func_080E7AE0(temp_r6, temp_r7, 9) << 0x10) == 0) {
        goto block_10;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 2, 0x12C, 0, 0);
block_10:
    if ((func_080E7AE0(temp_r6, temp_r7, 0xA) << 0x10) == 0) {
        goto block_12;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 1, 0x32, 0, 0);
block_12:
    if ((func_080E7AE0(temp_r6, temp_r7, 0xB) << 0x10) == 0) {
        goto block_14;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 1, 0x64, 0, 0);
block_14:
    if ((func_080E7AE0(temp_r6, temp_r7, 0xD) << 0x10) == 0) {
        goto block_16;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 5, 0xA, 0, 0);
block_16:
    if ((func_080E7AE0(temp_r6, temp_r7, 0xE) << 0x10) == 0) {
        goto block_18;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 5, 0x14, 0, 0);
block_18:
    if ((func_080E7AE0(temp_r6, temp_r7, 0xF) << 0x10) == 0) {
        goto block_20;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 5, 0x1E, 0, 0);
block_20:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x10) << 0x10) == 0) {
        goto block_22;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 6, 1, 0, 0);
block_22:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x11) << 0x10) == 0) {
        goto block_24;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 6, 2, 0, 0);
block_24:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x13) << 0x10) == 0) {
        goto block_26;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 0xD, 0x1F4, 0, 0);
block_26:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x14) << 0x10) == 0) {
        goto block_28;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 7, 0x1F4, 0, 0);
block_28:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x18) << 0x10) == 0) {
        goto block_31;
    }
    if (func_080BF464(temp_r6, temp_r7, 0x1C) != 0xFF) {
        goto block_31;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 0x1C, 1, 0, 0);
block_31:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x19) << 0x10) == 0) {
        goto block_34;
    }
    if (func_080BF464(temp_r6, temp_r7, 0x1C) != 0xFF) {
        goto block_34;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 0x1C, 2, 0, 0);
block_34:
    if ((func_080E7AE0(temp_r6, temp_r7, 1) << 0x10) == 0) {
        goto block_36;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0x20, 0, 1, 0x1D, 0, 0, 0);
block_36:
    if ((func_080E7AE0(temp_r6, temp_r7, 2) << 0x10) == 0) {
        goto block_38;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0x20, 0, 1, 0x1E, 0, 0, 0);
block_38:
    {
        register s32 result asm("r0") = func_080E7AE0(temp_r6, temp_r7, 3);

        asm volatile(
            "b 1f\n\t"
            ".align 2, 0\n\t"
            ".LEA408_BASE_POOL:\n\t"
            ".word 0x02034B4C\n\t"
            "1:"
            : "+r"(result));
        if ((result << 0x10) == 0) {
            goto block_42;
        }
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0x20, 0, 1, 0x1F, 0, 0, 0);
block_42:
    if ((func_080E7AE0(temp_r6, temp_r7, 4) << 0x10) == 0) {
        goto block_44;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0x20, 0, 1, 0x20, 0, 0, 0);
block_44:
    if ((func_080E7AE0(temp_r6, temp_r7, 5) << 0x10) == 0) {
        goto block_46;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0x20, 0, 1, 0x21, 0, 0, 0);
block_46:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x12) << 0x10) == 0) {
        goto block_50;
    }
    temp_r0 = func_080BF464(temp_r6, temp_r7, 0x15);
    if (temp_r0 != 0xFF) {
        goto block_49;
    }
    func_080BE65C(temp_r6, temp_r7, -1, 0, 0, 1, 0x15, 0x64, 0, 0);
    goto block_50;
block_49:
    {
        u8 *base = (u8 *)0x02034B4C;
        u32 address;

        asm volatile("" : "+r"(base));
        address = temp_r0 * 0xC;
        address += temp_r7 * 0x270;
        address += temp_r6 * 0x1380;
        address += (u32)base;
        address += 0xEA;
        *(u16 *)address = (u16)(*(u16 *)address + 0x64);
    }
block_50:
    if ((func_080E7AE0(temp_r6, temp_r7, 0x16) << 0x10) == 0) {
        goto block_56;
    }
    asm volatile("EA408_PATCH_SELECTION_INIT");
    var_r8 = 0;
    var_r5 = 0;
    temp_r0_2 = (void *)(temp_r6 * 4);
    asm volatile("" : : "r"(temp_r0_2));
    opposite_shifted = temp_r6 ^ 1;
    opposite_shifted <<= 24;
loop_52:
    if ((func_080E9D88(opposite_shifted >> 24, var_r5) << 0x18) == 0) {
        goto block_54;
    }
    choices[var_r8] = var_r5;
    var_r8 += 1;
block_54:
    var_r5 += 1;
    if ((u32) var_r5 <= 5U) {
        goto loop_52;
    }
    temp_r5 = temp_r6 ^ 1;
    {
        register u8 *base asm("r0") = (u8 *)0x02034B4C;
        register u32 offset asm("r4");

        asm volatile("" : "+r"(base));
        base += (u32)temp_r0_2;
        offset = 0xA07E;
        asm volatile("" : "+r"(offset));
        asm volatile(
            ".macro add dst, args:vararg\n\t"
            ".purgem add\n\t"
            "add r4, r4, r0\n\t"
            ".endm");
        temp_r0_3 = base + offset;
    }
    {
        register void *saved_selection asm("r9");

        asm volatile(
            "mov %0, %1\n\t"
            "ldrb r0, [%1]\n\t"
            "mov r1, %2\n\t"
            "mul r1, r0\n\t"
            "add r0, r1, #0\n\t"
            "asr r0, r0, #8\n\t"
            "add r0, sp\n\t"
            "add r0, #24\n\t"
            "ldrb r1, [r0]\n\t"
            "mov r2, #1\n\t"
            "neg r2, r2\n\t"
            "mov r3, #0\n\t"
            "str r3, [sp, #0]\n\t"
            "mov %1, #1\n\t"
            "str %1, [sp, #4]\n\t"
            "mov r0, #25\n\t"
            "str r0, [sp, #8]\n\t"
            "str r3, [sp, #12]\n\t"
            "str %1, [sp, #16]\n\t"
            "str r3, [sp, #20]\n\t"
            "add r0, %3, #0\n\t"
            "bl func_080BE65C"
            : "=r"(saved_selection), "+r"(temp_r0_3)
            : "r"(var_r8), "r"(temp_r5)
            : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
        {
            register void *selection_read asm("r2") = saved_selection;

            asm volatile("" : "+r"(selection_read));
            func_080C02B4(temp_r5, choices[(s32) (var_r8 * M2C_FIELD(selection_read, u8 *, 0)) >> 8]);
        }
    }
block_56:
    func_080E8B08(temp_r6, temp_r7);
    asm volatile(
        "mov r4, %0\n\t"
        "mov r5, #58\n\t"
        "ldrsh r1, [r4, r5]\n\t"
        "mov r2, #6\n\t"
        "ldrsh r0, [r4, r2]\n\t"
        "cmp r1, r0\n\t"
        "ble 2f\n\t"
        "add r0, r1, #0\n\t"
        "ldr r4, [sp, #32]\n\t"
        "mov r5, #42\n\t"
        "ldrsh r1, [r4, r5]\n\t"
        "bl func_080E522C\n\t"
        "mov r2, %0\n\t"
        "ldrh r1, [r2, #6]\n\t"
        "lsl r0, r0, #16\n\t"
        "asr r4, r0, #16\n\t"
        "add r1, r4, r1\n\t"
        "mov r3, #0\n\t"
        "strh r1, [r2, #6]\n\t"
        "lsl r1, r1, #16\n\t"
        "asr r1, r1, #16\n\t"
        "ldrh r5, [r2, #58]\n\t"
        "mov r8, r5\n\t"
        "mov r5, #58\n\t"
        "ldrsh r0, [r2, r5]\n\t"
        "cmp r1, r0\n\t"
        "ble 1f\n\t"
        "mov r0, r8\n\t"
        "strh r0, [r2, #6]\n\t"
        "1:\n\t"
        "mov r2, #1\n\t"
        "neg r2, r2\n\t"
        "str r3, [sp, #0]\n\t"
        "mov r0, #1\n\t"
        "str r0, [sp, #4]\n\t"
        "str r0, [sp, #8]\n\t"
        "str r4, [sp, #12]\n\t"
        "str r3, [sp, #16]\n\t"
        "str r3, [sp, #20]\n\t"
        "add r0, r6, #0\n\t"
        "add r1, r7, #0\n\t"
        "mov r3, #0\n\t"
        "bl func_080BE9D8\n\t"
        "2:"
        :
        : "r"(temp_r1)
        : "r0", "r1", "r2", "r3", "r4", "r5", "r8", "lr", "cc", "memory");
    asm volatile(
        "mov r2, %0\n\t"
        "mov r3, #62\n\t"
        "ldrsh r1, [r2, r3]\n\t"
        "mov r4, #8\n\t"
        "ldrsh r0, [r2, r4]\n\t"
        "cmp r1, r0\n\t"
        "ble 1f\n\t"
        "mov r2, #1\n\t"
        "neg r2, r2\n\t"
        "mov r3, #0\n\t"
        "str r3, [sp, #0]\n\t"
        "mov r0, #1\n\t"
        "str r0, [sp, #4]\n\t"
        "mov r0, #4\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r5, %0\n\t"
        "ldrh r0, [r5, #62]\n\t"
        "ldrh r1, [r5, #8]\n\t"
        "sub r0, r0, r1\n\t"
        "lsl r0, r0, #16\n\t"
        "asr r0, r0, #16\n\t"
        "str r0, [sp, #12]\n\t"
        "str r3, [sp, #16]\n\t"
        "str r3, [sp, #20]\n\t"
        "add r0, r6, #0\n\t"
        "add r1, r7, #0\n\t"
        "bl func_080BE9D8\n\t"
        "ldrh r0, [r5, #62]\n\t"
        "strh r0, [r5, #8]\n\t"
        "1:"
        :
        : "r"(temp_r1)
        : "r0", "r1", "r2", "r3", "r4", "r5", "lr", "cc", "memory");
    if ((func_080E7AE0(temp_r6, temp_r7, 0xC) << 0x10) == 0) {
        goto block_69;
    }
    {
        u32 row_offset;

        var_r5_2 = 0;
        row_offset = temp_r6 * 0x1380;
loop_64:
    if (var_r5_2 == temp_r7) {
        goto block_68;
    }
    if ((func_080E9D88(temp_r6, var_r5_2) << 0x18) == 0) {
        goto block_68;
    }
    {
        u32 col_offset;
        u8 *base;
        register s32 max_arg asm("r0");
        register u32 row_carrier asm("r1");
        register s32 field_offset asm("r2");
        register void *aux_base asm("r3");

        col_offset = var_r5_2 * 0x270;
        base = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(base));
        col_offset += (u32)base;
        row_carrier = row_offset;
        asm volatile("" : "+r"(row_carrier));
        temp_r4_2 = (void *)(row_carrier + col_offset);
        asm volatile(
            ".macro mov dst, src\n\t"
            ".purgem mov\n\t"
            "mov r2, \\src\n\t"
            ".endm\n\t"
            ".macro ldrsh dst, addr:vararg\n\t"
            ".purgem ldrsh\n\t"
            "ldrsh r0, [r4, r2]\n\t"
            ".endm");
        field_offset = 0x3A;
        max_arg = *(s16 *)((u8 *)temp_r4_2 + field_offset);
        aux_base = sp20;
        field_offset = 0x2A;
        temp_r1_5 = *(s16 *)((u8 *)aux_base + field_offset);
        temp_r1_6 = M2C_FIELD(temp_r4_2, u16 *, 6) + func_080E522C(max_arg, (s16) ((s32) (temp_r1_5 + ((u32) temp_r1_5 >> 0x1F)) >> 1));
    }
    M2C_FIELD(temp_r4_2, u16 *, 6) = temp_r1_6;
    if ((s32) (s16) temp_r1_6 <= (s32) M2C_FIELD(temp_r4_2, s16 *, 0x3A)) {
        goto block_68;
    }
    M2C_FIELD(temp_r4_2, u16 *, 6) = (u16) M2C_FIELD(temp_r4_2, s16 *, 0x3A);
block_68:
    var_r5_2 += 1;
    if ((u32) var_r5_2 <= 5U) {
        goto loop_64;
    }
    }
block_69:
    return;
}
