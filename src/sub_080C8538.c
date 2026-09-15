#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
void *func_08094374(M2C_UNK, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_08096F3C();                            /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098248(M2C_UNK, s32, s32);           /* extern */
M2C_UNK func_0809844C(s16, s32, u32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809844C_wide(s32, s32, u32, s32, s32, s32, s32)
    asm("func_0809844C");
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809AA64(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_080BB224(s32, u8, u8, s32);            /* extern */
u8 func_080BF464(u8, u8, s32);                      /* extern */
M2C_UNK func_080E5880(M2C_UNK, void *);             /* extern */
s32 func_080E9924(u8, u8);                          /* extern */
s32 func_080E9D88(u8, u8);                          /* extern */
s16 func_080ECD98(s16, s32);                        /* extern */
s32 func_080ECE30(s16, s32);                        /* extern */
s32 func_080ECE30_wide(s32, s32) asm("func_080ECE30");
s32 func_080ECF00(u8, s32);                         /* extern */
u8 func_080ECF78(u32, s32);                         /* extern */
M2C_UNK func_080ED038(M2C_UNK, void *, s32);        /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

asm(
    ".macro C8538_PATCH_FINAL_REFERENCE\n"
    ".macro ldr dst, src:vararg\n"
    ".purgem ldr\n"
    "ldr r2, \\src\n"
    ".endm\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r4, #0\n"
    ".endm\n"
    ".macro ldrsh dst, src:vararg\n"
    ".purgem ldrsh\n"
    "ldrsh r1, [r2, r4]\n"
    ".endm\n"
    ".endm\n");

asm(
    ".macro C8538_PATCH_STACK_ARG reg\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov \\reg, \\src\n"
    ".endm\n"
    ".macro str src, addr:vararg\n"
    ".purgem str\n"
    "str \\reg, \\addr\n"
    ".endm\n"
    ".endm\n");

asm(
    ".macro C8538_PATCH_FIRST_NAME_CALL\n"
    ".set C8538_NAME_MOV_COUNT, 0\n"
    ".macro mov dst, src\n"
    ".if C8538_NAME_MOV_COUNT == 0\n"
    ".syntax unified\n"
    "movs r3, #0\n"
    ".syntax divided\n"
    ".elseif C8538_NAME_MOV_COUNT == 1\n"
    ".syntax unified\n"
    "movs r1, #0\n"
    ".syntax divided\n"
    ".elseif C8538_NAME_MOV_COUNT == 2\n"
    ".syntax unified\n"
    "movs r2, #3\n"
    ".syntax divided\n"
    ".else\n"
    ".purgem mov\n"
    ".endif\n"
    ".set C8538_NAME_MOV_COUNT, C8538_NAME_MOV_COUNT + 1\n"
    ".endm\n"
    ".macro str src, addr:vararg\n"
    ".purgem str\n"
    "str r3, \\addr\n"
    ".endm\n"
    ".endm\n"
    ".macro C8538_INSERT_R3_BEFORE_BL\n"
    ".macro bl target\n"
    ".purgem bl\n"
    "mov r3, #0\n"
    "bl \\target\n"
    ".endm\n"
    ".endm\n");

asm(
    ".macro C8538_DELAY_FINAL_POINTER\n"
    ".macro ldr dst, src:vararg\n"
    ".purgem ldr\n"
    ".endm\n"
    ".macro strh src, addr:vararg\n"
    ".purgem strh\n"
    "ldr r1, [sp, #20]\n"
    "strh r0, [r1, #6]\n"
    ".endm\n"
    ".endm\n");

asm(
    ".macro C8538_OPEN_INSTALL_MOV4\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r3, \\src\n"
    ".endm\n"
    ".endm\n"
    ".macro C8538_OPEN_INSTALL_MOV3\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov \\dst, \\src\n"
    "C8538_OPEN_INSTALL_MOV4\n"
    ".endm\n"
    ".endm\n"
    ".macro C8538_OPEN_INSTALL_MOV2\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov \\dst, \\src\n"
    "C8538_OPEN_INSTALL_MOV3\n"
    ".endm\n"
    ".endm\n"
    ".macro C8538_OPEN_INSTALL_CMP4\n"
    ".macro cmp lhs, rhs\n"
    ".purgem cmp\n"
    "cmp r3, \\rhs\n"
    ".endm\n"
    ".endm\n"
    ".macro C8538_OPEN_INSTALL_CMP3\n"
    ".macro cmp lhs, rhs\n"
    ".purgem cmp\n"
    "cmp \\lhs, \\rhs\n"
    "C8538_OPEN_INSTALL_CMP4\n"
    ".endm\n"
    ".endm\n"
    ".macro C8538_OPEN_INSTALL_CMP2\n"
    ".macro cmp lhs, rhs\n"
    ".purgem cmp\n"
    "cmp \\lhs, \\rhs\n"
    "C8538_OPEN_INSTALL_CMP3\n"
    ".endm\n"
    ".endm\n"
    ".macro C8538_PATCH_OPENING_R3\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov \\dst, \\src\n"
    "C8538_OPEN_INSTALL_MOV2\n"
    ".endm\n"
    ".macro cmp lhs, rhs\n"
    ".purgem cmp\n"
    "cmp \\lhs, \\rhs\n"
    "C8538_OPEN_INSTALL_CMP2\n"
    ".endm\n"
    ".endm\n");

#define STORE_SKIP_SLOT4() ({ \
    asm volatile( \
        ".syntax unified\n\t" \
        "lsls r2, r7, #2\n\t" \
        "str r2, [sp, #40]\n\t" \
        ".syntax divided" \
        : : : "r2", "memory"); \
    1; \
})
#define VIEW_R2(value_expr) ({ \
    register s32 view asm("r2") = (value_expr); \
    asm volatile("" : "+r"(view)); \
    view; \
})
#define VIEW_R3(value_expr) ({ \
    register s32 view asm("r3") = (value_expr); \
    asm volatile("" : "+r"(view)); \
    view; \
})
#define VIEW_R4(value_expr) ({ \
    register s32 view asm("r4") = (value_expr); \
    asm volatile("" : "+r"(view)); \
    view; \
})
#define LOAD_RECORD_4A(record_expr) ({ \
    register void *base_r0 asm("r0") = (record_expr); \
    register s32 value_r3 asm("r3"); \
    asm volatile( \
        ".syntax unified\n\t" \
        "adds r0, #74\n\t" \
        "movs r2, #0\n\t" \
        "ldrsh r3, [r0, r2]\n\t" \
        ".syntax divided" \
        : "+r"(base_r0), "=r"(value_r3) \
        : : "r2", "cc", "memory"); \
    value_r3; \
})
#define CALL_STAT_ROW(value_expr, relation_expr, row_imm) do { \
    register s32 call_value_r3 asm("r3") = (value_expr); \
    register u32 call_relation_r2 asm("r2") = (relation_expr); \
    asm volatile( \
        ".syntax unified\n\t" \
        "movs r0, #2\n\t" \
        "str r0, [sp, #0]\n\t" \
        "movs r1, #4\n\t" \
        "str r1, [sp, #4]\n\t" \
        "movs r0, #" #row_imm "\n\t" \
        "str r0, [sp, #8]\n\t" \
        "adds r0, %0, #0\n\t" \
        "@ relation %1\n\t" \
        "movs r3, #10\n\t" \
        "bl func_0809844C\n\t" \
        ".syntax divided" \
        : "+r"(call_value_r3), "+r"(call_relation_r2) \
        : : "r0", "r1", "lr", "cc", "memory"); \
} while (0)

void sub_080C8538(s32 arg0, s32 arg1) {
    volatile struct {
        void *sp14;
        s32 sp18;
        void *sp1C;
        s32 sp20;
        s32 sp24;
        s32 sp28;
    } stack;
    volatile s32 spill;
    s16 temp_r0_4;
    s16 temp_r1_11;
    s16 temp_r1_13;
    s16 temp_r1_15;
    s16 temp_r1_17;
    s16 temp_r1_19;
    s16 temp_r1_21;
    s16 temp_r1_23;
    s16 temp_r1_7;
    s16 temp_r1_9;
    s32 temp_r3;
    s32 temp_r3_10;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 temp_r3_8;
    s32 temp_r3_9;
    register s32 temp_r4_14 asm("r4");
    s16 temp_r4_3;
    s16 temp_r4_4;
    s16 temp_r6;
    s16 temp_r6_2;
    s16 temp_r6_3;
    s16 temp_r6_4;
    s16 temp_r6_5;
    s16 temp_r6_6;
    s32 var_r1;
    s16 var_r2;
    s16 var_r5_4;
    s16 var_r5_5;
    s16 var_r5_8;
    s32 temp_r0_3;
    s32 temp_r1_10;
    s32 temp_r1_12;
    s32 temp_r1_14;
    s32 temp_r1_16;
    s32 temp_r1_18;
    s32 temp_r1_20;
    s32 temp_r1_22;
    s32 temp_r1_24;
    s32 temp_r1_6;
    s32 temp_r1_8;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r2_2;
    s32 var_r2_3;
    s32 var_r8;
    u16 temp_r1;
    u16 temp_r1_3;
    u16 temp_r1_4;
    u16 temp_r1_5;
    u16 temp_r6_7;
    u16 var_r5;
    u16 var_r5_2;
    s16 var_r5_3;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 var_r2_10;
    u32 var_r2_11;
    u32 var_r2_12;
    u32 var_r2_13;
    u32 var_r2_4;
    u32 var_r2_5;
    u32 var_r2_6;
    u32 var_r2_7;
    u32 var_r2_8;
    u32 var_r2_9;
    register u32 var_r5_9 asm("r5");
    u8 temp_r1_2;
    u8 temp_r4;
    u8 temp_r4_10;
    u8 temp_r4_11;
    u8 temp_r4_12;
    u8 temp_r4_13;
    u8 temp_r4_2;
    u8 temp_r4_5;
    u8 temp_r4_6;
    u8 temp_r4_7;
    u8 temp_r4_8;
    u8 temp_r4_9;
    u8 temp_r5;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 scan_side_1;
    u8 scan_side_2;
    u16 var_r5_6;
    u16 var_r5_7;
    u8 var_r7;
    u8 var_r9;
    register u32 var_sl asm("sl");
    void *temp_r0_5;
    void *temp_r0_6;
    register void *temp_r2 asm("r8");

    var_r9 = arg0;
    var_r7 = arg1;
    func_0809AA64(0x087AC9D8, 0, 0x360, 0xD);
    stack.sp14 = func_08094374(0x087AC9E0, 0, 0, 0, 0, 0x360, 0xD, 0x60, 0);
    stack.sp18 = (s32) (u8) (var_r7 + 1);
    func_080BB224(5, var_r9, var_r7, 1);
    {
        u8 *control = (u8 *)0x030033C4;
        M2C_FIELD(control, s32 *, 0x14) = 0xB4;
        M2C_FIELD(control, s32 *, 0x18) = 0x58;
    }
    func_08098BB4(0x08003F08);
    func_08096F3C();
    stack.sp1C = (void *)0x02033EC4;
    do {
        {
        register u16 keys_r1 asm("r1") = *(u16 *)0x03006034;
        asm volatile("C8538_PATCH_OPENING_R3");
        if (((0x40 & keys_r1) && (VIEW_R2(var_r9) == 0)) ||
            ((0x80 & keys_r1) && (var_r9 != 0))) {
            temp_r1_2 = func_080ECF78((u32) var_r7, 3);
            if (temp_r1_2 != 0) {
                register s32 loop_index asm("r5");
                register s32 loop_signed asm("r6");
                register s32 loop_bound asm("r2");
                {
                    register s32 count_r1 asm("r1") = temp_r1_2;
                    asm volatile(
                        ".syntax unified\n\t"
                        "subs r0, %3, #1\n\t"
                        "subs %2, %3, %2\n\t"
                        "lsls r0, r0, #16\n\t"
                        "lsrs %0, r0, #16\n\t"
                        "lsls %2, %2, #16\n\t"
                        "asrs %1, %2, #16\n\t"
                        ".syntax divided"
                        : "=r"(loop_index), "=r"(loop_bound), "+r"(count_r1)
                        : "r"(var_r7) : "r0");
                }
                while ((s32) ({
                    asm volatile(
                        ".syntax unified\n\t"
                        "lsls r0, %1, #16\n\t"
                        "asrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(loop_signed) : "r"(loop_index) : "r0");
                    loop_signed;
                }) >= loop_bound) {
                    temp_r4 = (u8) loop_index;
                    asm volatile("" :: "r"(loop_index));
                    if ((s32) ({
                        register s32 valid asm("r0") = var_r9;
                        register s32 item_arg asm("r1") = temp_r4;
                        asm volatile(
                            ".syntax unified\n\t"
                            "str %2, [sp, #44]\n\t"
                            "bl func_080E9D88\n\t"
                            ".syntax divided"
                            : "+r"(valid), "+r"(item_arg), "+r"(loop_bound)
                            : : "r3", "lr", "cc", "memory");
                        valid <<= 0x18;
                        loop_bound = spill;
                        valid;
                    }) != 0) {
                        var_r7 = temp_r4;
                        func_08092E84(0x40);
                        break;
                    }
                    asm volatile(
                        ".syntax unified\n\t"
                        "subs r0, %1, #1\n\t"
                        "lsls r0, r0, #16\n\t"
                        "lsrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(loop_index) : "r"(loop_signed) : "r0");
                }
                if (var_r7 == VIEW_R4(stack.sp18)) {
                    register s32 count_r0 asm("r0");
                    register u16 fallback_index asm("r5");
                    register s32 fallback_signed asm("r6");
                    register s32 fallback_bound asm("r2");
                    register s32 fallback_base asm("r0") = 0;
                    if ((u32) var_r7 <= 2U) {
                        fallback_base = 3;
                    }
                    var_r0 = fallback_base;
                    count_r0 = func_080ECF78((u32) var_r7, 3);
                    {
                        register s32 neg1 asm("r1") = 0xFFFF;
                        asm volatile(
                            ".syntax unified\n\t"
                            "adds r0, %1, %2\n\t"
                            "adds r0, %3, r0\n\t"
                            "lsls r0, r0, #16\n\t"
                            "lsrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(fallback_index), "+r"(count_r0)
                            : "r"(neg1), "r"(var_r0));
                    }
                    fallback_bound = var_r0;
                    while ((s32) ({
                        asm volatile(
                            ".syntax unified\n\t"
                            "lsls r0, %1, #16\n\t"
                            "asrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(fallback_signed) : "r"(fallback_index) : "r0");
                        fallback_signed;
                    }) >= fallback_bound) {
                        temp_r4_2 = (u8) fallback_index;
                        asm volatile("" :: "r"(fallback_index));
                        if ((s32) ({
                            register s32 valid asm("r0") = var_r9;
                            register s32 item_arg asm("r1") = temp_r4_2;
                            asm volatile(
                                ".syntax unified\n\t"
                                "str %2, [sp, #44]\n\t"
                                "bl func_080E9D88\n\t"
                                ".syntax divided"
                                : "+r"(valid), "+r"(item_arg), "+r"(fallback_bound)
                                : : "r3", "lr", "cc", "memory");
                            valid <<= 0x18;
                            fallback_bound = spill;
                            valid;
                        }) != 0) {
                            var_r7 = temp_r4_2;
                            func_08092E84(0x40);
                            break;
                        }
                        asm volatile(
                            ".syntax unified\n\t"
                            "subs r0, %1, #1\n\t"
                            "lsls r0, r0, #16\n\t"
                            "lsrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(fallback_index) : "r"(fallback_signed) : "r0");
                    }
                }
            }
        }
        }
        {
        register u16 keys_r1 asm("r1") = *(u16 *)0x03006034;
        if ((((0x40 & keys_r1) && (var_r9 != 0)) || ((0x80 & keys_r1) && (var_r9 == 0))) && ((u32) func_080ECF78((u32) var_r7, 3) <= 1U)) {
            register s32 upper_bound asm("r4");
            asm volatile(
                ".syntax unified\n\t"
                "adds r0, %1, #1\n\t"
                "lsls r0, r0, #16\n\t"
                "lsrs %0, r0, #16\n\t"
                ".syntax divided"
                : "=r"(var_r5_3) : "r"(var_r7) : "r0");
            upper_bound = var_r7 + 3;
            asm volatile(
                ".syntax unified\n\t"
                "lsls %0, %0, #16\n\t"
                "asrs %0, %0, #16\n\t"
                ".syntax divided"
                : "+r"(upper_bound));
            upper_bound -= func_080ECE30_wide(upper_bound, 3);
            asm volatile(
                ".syntax unified\n\t"
                "lsls %0, %0, #16\n\t"
                "asrs %0, %0, #16\n\t"
                ".syntax divided"
                : "+r"(upper_bound));
            while ((s32) (temp_r6_3 = var_r5_3) < upper_bound) {
                temp_r5 = (u8) var_r5_3;
                if ((func_080E9D88(var_r9, temp_r5) << 0x18) != 0) {
                    var_r7 = temp_r5;
                    func_08092E84(0x40);
                    break;
                }
                var_r5_3 = (s16) (u16) (temp_r6_3 + 1);
            }
            if (var_r7 == VIEW_R4(stack.sp18)) {
                register s32 count_r0 asm("r0");
                register s32 fallback_index asm("r5");
                register s32 fallback_signed asm("r6");
                register s32 fallback_bound asm("r2");
                register s32 fallback_base asm("r0") = 0;
                if ((u32) var_r7 <= 2U) {
                    fallback_base = 3;
                }
                var_r0_2 = fallback_base;
                count_r0 = func_080ECF78((u32) var_r7, 3);
                asm volatile(
                    ".syntax unified\n\t"
                    "adds %1, %1, #1\n\t"
                    "adds %0, %2, %1\n\t"
                    ".syntax divided"
                    : "=r"(fallback_index), "+r"(count_r0) : "r"(var_r0_2));
                fallback_bound = var_r0_2 + 3;
                while ((s32) ({
                    asm volatile(
                        ".syntax unified\n\t"
                        "lsls r0, %1, #16\n\t"
                        "asrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(fallback_signed) : "r"(fallback_index) : "r0");
                    fallback_signed;
                }) < fallback_bound) {
                    temp_r4_5 = (u8) fallback_index;
                    asm volatile("" :: "r"(fallback_index));
                    if ((s32) ({
                        register s32 valid asm("r0") = var_r9;
                        register s32 item_arg asm("r1") = temp_r4_5;
                        asm volatile(
                            ".syntax unified\n\t"
                            "str %2, [sp, #44]\n\t"
                            "bl func_080E9D88\n\t"
                            ".syntax divided"
                            : "+r"(valid), "+r"(item_arg), "+r"(fallback_bound)
                            : : "r3", "lr", "cc", "memory");
                        valid <<= 0x18;
                        fallback_bound = spill;
                        valid;
                    }) != 0) {
                        var_r7 = temp_r4_5;
                        func_08092E84(0x40);
                        break;
                    }
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds r0, %1, #1\n\t"
                        "lsls r0, r0, #16\n\t"
                        "lsrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(fallback_index) : "r"(fallback_signed) : "r0");
                }
            }
        }
        }
        {
        register u16 keys_r1 asm("r1") = *(u16 *)0x03006034;
        register s32 reload_guard_r4 asm("r4");
        asm volatile("" : "=r"(reload_guard_r4));
        if (!(0x20 & keys_r1) || (var_r9 != 0)) {
            if (!(0x10 & keys_r1)) {

            } else if (var_r9 == 0) {

            } else {
                goto block_44;
            }
        } else {
block_44:
            asm volatile("" : : "r"(reload_guard_r4));
            var_r8 = 0;
            if ((func_080ECF00(var_r7, 3) << 0x18) != 0) {
                temp_r4_6 = var_r7 - 3;
                if ((func_080E9D88(var_r9, temp_r4_6) << 0x18) != 0) {
                    var_r7 = temp_r4_6;
                    func_08092E84(0x40);
                    var_r8 = 1;
                } else {
                    register s32 loop_index asm("r5") = 0;
                    register s32 loop_signed asm("r6");
                    while ((s32) ({
                        asm volatile(
                            ".syntax unified\n\t"
                            "lsls r0, %1, #16\n\t"
                            "asrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(loop_signed) : "r"(loop_index) : "r0");
                        loop_signed;
                    }) <= 2) {
                        temp_r4_7 = (u8) loop_index;
                        asm volatile("" :: "r"(loop_index));
                        if ((func_080E9D88(var_r9, temp_r4_7) << 0x18) != 0) {
                            var_r7 = temp_r4_7;
                            func_08092E84(0x40);
                            var_r8 = 1;
                            break;
                        }
                        asm volatile(
                            ".syntax unified\n\t"
                            "adds r0, %1, #1\n\t"
                            "lsls r0, r0, #16\n\t"
                            "lsrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(loop_index) : "r"(loop_signed) : "r0");
                    }
                    if (loop_signed == 3) {
                        var_r7 -= 3;
                    }
                }
            }
            if (((func_080ECF00(var_r7, 3) << 0x18) == 0) && (var_r8 == 0)) {
                asm volatile(
                    ".syntax unified\n\t"
                    "movs r1, #1\n\t"
                    "mov r0, r9\n\t"
                    "eors r0, r1\n\t"
                    "lsls r0, r0, #24\n\t"
                    "lsrs %0, r0, #24\n\t"
                    ".syntax divided"
                    : "=r"(temp_r4_8) : : "r0", "r1");
                temp_r5_2 = 2 - var_r7;
                if ((func_080E9D88(temp_r4_8, temp_r5_2) << 0x18) != 0) {
                    var_r9 = temp_r4_8;
                    var_r7 = temp_r5_2;
                    asm volatile("" ::: "memory");
                    goto block_66;
                }
                goto first_scan_start;
first_scan_found:
                var_r9 = scan_side_1;
                var_r7 = temp_r4_9;
                func_08092E84(0x40);
                goto first_scan_done;
first_scan_start:
                var_r5_6 = 0;
                scan_side_1 = temp_r4_8;
                do {
                    temp_r4_9 = var_r5_6;
                    if ((func_080E9D88(scan_side_1, temp_r4_9) << 0x18) != 0) {
                        goto first_scan_found;
                    }
                    temp_r0 = (var_r5_6 << 0x10) + 0x10000;
                    var_r5_6 = (u16) (temp_r0 >> 0x10);
                } while ((s32) ((s32) temp_r0 >> 0x10) <= 2);
first_scan_done:
                if (var_r5_6 == 3) {
                    temp_r4_10 = var_r9 ^ 1;
                    temp_r5_3 = 5 - var_r7;
                    if ((func_080E9D88(temp_r4_10, temp_r5_3) << 0x18) != 0) {
                        var_r9 = temp_r4_10;
                        var_r7 = temp_r5_3;
                        goto block_66;
                    }
                    goto second_scan_start;
second_scan_found:
                    var_r9 = scan_side_2;
                    var_r7 = temp_r4_11;
block_66:
                    func_08092E84(0x40);
                    goto second_scan_done;
second_scan_start:
                    var_r5_7 = 3;
                    scan_side_2 = temp_r4_10;
loop_68:
                    temp_r4_11 = var_r5_7;
                    if ((func_080E9D88(scan_side_2, temp_r4_11) << 0x18) == 0) {
                        temp_r0_2 = (var_r5_7 << 0x10) + 0x10000;
                        var_r5_7 = (u16) (temp_r0_2 >> 0x10);
                        if ((s32) ((s32) temp_r0_2 >> 0x10) <= 5) {
                            goto loop_68;
                        }
                    } else {
                        goto second_scan_found;
                    }
second_scan_done:
                    ;
                }
        }
        }
        }
        asm volatile(
            ".syntax unified\n\t"
            "mov r3, r9\n\t"
            "lsls r3, r3, #1\n\t"
            "str r3, [sp, #32]\n\t"
            ".syntax divided"
            : : : "r3", "memory");
        if (var_sl == var_r9) {
        register u16 keys_r1 asm("r1") = *(u16 *)0x03006034;
        register s32 reload_guard_r3 asm("r3");
        asm volatile("" : "=r"(reload_guard_r3));
        if (((0x20 & keys_r1) && (var_sl != 0)) || ((0x10 & keys_r1) && (var_sl == 0))) {
            asm volatile("" : : "r"(reload_guard_r3));
            temp_r0_3 = func_080ECF00(var_r7, 3) << 0x18;
            asm volatile(
                ".syntax unified\n\t"
                "mov r1, r9\n\t"
                "lsls r1, r1, #1\n\t"
                "str r1, [sp, #32]\n\t"
                ".syntax divided"
                : : : "r1", "memory");
            if (temp_r0_3 == 0) {
                temp_r4_12 = var_r7 + 3;
                if ((func_080E9D88(var_r9, temp_r4_12) << 0x18) != 0) {
                    var_r7 = temp_r4_12;
                    func_08092E84(0x40);
                } else {
                    register s32 loop_index asm("r5") = 3;
                    register s32 loop_signed asm("r6");
                    while ((s32) ({
                        asm volatile(
                            ".syntax unified\n\t"
                            "lsls r0, %1, #16\n\t"
                            "asrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(loop_signed) : "r"(loop_index) : "r0");
                        loop_signed;
                    }) <= 5) {
                        temp_r4_13 = (u8) loop_index;
                        asm volatile("" :: "r"(loop_index));
                        if ((func_080E9D88(var_r9, temp_r4_13) << 0x18) != 0) {
                            var_r7 = temp_r4_13;
                            func_08092E84(0x40);
                            break;
                        }
                        asm volatile(
                            ".syntax unified\n\t"
                            "adds r0, %1, #1\n\t"
                            "lsls r0, r0, #16\n\t"
                            "lsrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(loop_index) : "r"(loop_signed) : "r0");
                    }
                }
            }
        }
        }
        if ((var_r9 == var_sl) && STORE_SKIP_SLOT4() &&
            (var_r7 == VIEW_R3(stack.sp18))) {

        } else {
            register u32 work_r4 asm("r4") = var_r9;
            register u32 side4_r5 asm("r5") = work_r4 << 2;
            register u32 address_r2 asm("r2");
            register u32 slot_address_r0 asm("r0");
            register u32 base_r1 asm("r1") = 0x02034B4C;
            register void *initial_record_r2 asm("r2");
            address_r2 = side4_r5 + work_r4;
            address_r2 = ((address_r2 << 3) - work_r4) << 7;
            work_r4 = var_r7 << 2;
            slot_address_r0 = work_r4 + var_r7;
            slot_address_r0 = ((slot_address_r0 << 3) - var_r7) << 4;
            slot_address_r0 += base_r1;
            address_r2 += slot_address_r0;
            temp_r2 = (void *) address_r2;
            {
                register u32 reference_seed_r0 asm("r0") = 0x02033EC4;
                var_sl = reference_seed_r0;
                func_080ED038(reference_seed_r0, temp_r2, 0x70);
            }
            func_080E5880(var_sl, temp_r2 + 0x70);
            {
                register u32 flags_r1 asm("r1");
                asm volatile(
                    ".syntax unified\n\t"
                    "mov %1, r8\n\t"
                    "ldrh %0, [%1, #4]\n\t"
                    ".syntax divided"
                    : "=r"(flags_r1), "=r"(initial_record_r2));
                temp_r6_7 = 0x40 & flags_r1;
            }
            stack.sp24 = side4_r5;
            stack.sp28 = work_r4;
            if (temp_r6_7 == 0) {
                {
                    temp_r4_14 = M2C_FIELD(initial_record_r2, s16 *, 6);
                    var_r5_9 = 0;
                    temp_r0_4 = func_080ECD98(M2C_FIELD(initial_record_r2, s16 *, 0x3A), 0xA);
                }
                {
                    register void *record_r2 asm("r2") = temp_r2;
                    if ((s32) M2C_FIELD(record_r2, s16 *, 6) < (s32) temp_r0_4) {
                        var_r5_9 = 1;
                    }
                }
                func_0809844C_wide(temp_r4_14, 4, var_r5_9, 0xA, 2, 4, (s32) temp_r6_7);
                {
                    register void *record_r2 asm("r2") = temp_r2;
                    temp_r3 = M2C_FIELD(record_r2, s16 *, 0x3A);
                }
                temp_r1_6 = temp_r3;
                asm volatile("" : "+r"(temp_r1_6));
                {
                    register void *reference_r2 asm("r2") = (void *) var_sl;
                    temp_r0_4 = M2C_FIELD(reference_r2, s16 *, 0x3A);
                }
                if ((s32) temp_r1_6 <= (s32) temp_r0_4) {
                    temp_r1_6 ^= temp_r0_4;
                    var_r2_4 = (u32) ((0 - temp_r1_6) | temp_r1_6) >> 0x1F;
                } else {
                    var_r2_4 = 2;
                }
                func_0809844C_wide(temp_r3, 4, var_r2_4, 0xA, 2, 9, 0);
                {
                    register void *record_r2 asm("r2") = temp_r2;
                    func_0809844C(M2C_FIELD(record_r2, s16 *, 8), 4, 0U, 0xA, 2, 4, 1);
                }
                {
                    register void *record_r2 asm("r2") = temp_r2;
                    temp_r3_2 = M2C_FIELD(record_r2, s16 *, 0x3E);
                }
                {
                    register s32 current_r0 asm("r0") = temp_r3_2;
                    {
                        register void *reference_r2 asm("r2") = stack.sp1C;
                        register s32 offset_r4 asm("r4") = 0x3E;
                        temp_r1_7 = M2C_FIELD(reference_r2, s16 *, offset_r4);
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_7) {
                        temp_r1_8 = temp_r1_7 ^ current_r0;
                        var_r2_5 = (u32) ((0 - temp_r1_8) | temp_r1_8) >> 0x1F;
                    } else {
                        var_r2_5 = 2;
                    }
                }
                func_0809844C_wide(temp_r3_2, 4, var_r2_5, 0xA, 2, 9, 1);
                temp_r3_3 = M2C_FIELD(temp_r2, s16 *, 0x40);
                {
                    register s32 current_r0 asm("r0") = temp_r3_3;
                    {
                        register s16 *reference_r4 asm("r4") = (s16 *)0x02033F04;
                        temp_r1_9 = *reference_r4;
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_9) {
                        temp_r1_10 = temp_r1_9 ^ current_r0;
                        var_r2_6 = (u32) ((0 - temp_r1_10) | temp_r1_10) >> 0x1F;
                    } else {
                        var_r2_6 = 2;
                    }
                }
                func_0809844C_wide(temp_r3_3, 4, var_r2_6, 0xA, 2, 4, 2);
                temp_r3_4 = M2C_FIELD(temp_r2, s16 *, 0x42);
                {
                    register s32 current_r0 asm("r0") = temp_r3_4;
                    {
                        register s16 *reference_r4 asm("r4") = (s16 *)0x02033F06;
                        temp_r1_11 = *reference_r4;
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_11) {
                        temp_r1_12 = temp_r1_11 ^ current_r0;
                        var_r2_7 = (u32) ((0 - temp_r1_12) | temp_r1_12) >> 0x1F;
                    } else {
                        var_r2_7 = 2;
                    }
                }
                func_0809844C_wide(temp_r3_4, 4, var_r2_7, 0xA, 2, 4, 4);
                temp_r3_5 = M2C_FIELD(temp_r2, s16 *, 0x44);
                {
                    register s32 current_r0 asm("r0") = temp_r3_5;
                    {
                        register s16 *reference_r4 asm("r4") = (s16 *)0x02033F08;
                        temp_r1_13 = *reference_r4;
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_13) {
                        temp_r1_14 = temp_r1_13 ^ current_r0;
                        var_r2_8 = (u32) ((0 - temp_r1_14) | temp_r1_14) >> 0x1F;
                    } else {
                        var_r2_8 = 2;
                    }
                }
                func_0809844C_wide(temp_r3_5, 4, var_r2_8, 0xA, 2, 4, 5);
                {
                    register void *record_r1 asm("r1") = temp_r2;
                    temp_r3_6 = M2C_FIELD(record_r1, s16 *, 0xA);
                }
                {
                    register s32 current_r0 asm("r0") = temp_r3_6;
                    {
                        register void *reference_r2 asm("r2") = stack.sp1C;
                        temp_r1_15 = M2C_FIELD(reference_r2, s16 *, 0xA);
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_15) {
                        temp_r1_16 = temp_r1_15 ^ current_r0;
                        var_r2_9 = (u32) ((0 - temp_r1_16) | temp_r1_16) >> 0x1F;
                    } else {
                        var_r2_9 = 2;
                    }
                }
                func_0809844C_wide(temp_r3_6, 4, var_r2_9, 0xA, 2, 4, 6);
                temp_r3_7 = M2C_FIELD(temp_r2, s16 *, 0x46);
                {
                    register s32 current_r0 asm("r0") = temp_r3_7;
                    {
                        register s16 *reference_r2 asm("r2") = (s16 *)0x02033F0A;
                        temp_r1_17 = *reference_r2;
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_17) {
                        temp_r1_18 = temp_r1_17 ^ current_r0;
                        var_r2_10 = (u32) ((0 - temp_r1_18) | temp_r1_18) >> 0x1F;
                    } else {
                        var_r2_10 = 2;
                    }
                }
                func_0809844C_wide(temp_r3_7, 4, var_r2_10, 0xA, 2, 4, 8);
                temp_r3_8 = M2C_FIELD(temp_r2, s16 *, 0x48);
                {
                    register s32 current_r0 asm("r0") = temp_r3_8;
                    {
                        register s16 *reference_r2 asm("r2") = (s16 *)0x02033F0C;
                        temp_r1_19 = *reference_r2;
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_19) {
                        temp_r1_20 = temp_r1_19 ^ current_r0;
                        var_r2_11 = (u32) ((0 - temp_r1_20) | temp_r1_20) >> 0x1F;
                    } else {
                        var_r2_11 = 2;
                    }
                }
                func_0809844C_wide(temp_r3_8, 4, var_r2_11, 0xA, 2, 4, 9);
                {
                    register void *record_r2 asm("r2") = temp_r2;
                    temp_r3_9 = M2C_FIELD(record_r2, s16 *, 0x3C);
                }
                {
                    register s32 current_r0 asm("r0") = temp_r3_9;
                    {
                        register void *reference_r2 asm("r2") = stack.sp1C;
                        register s32 offset_r4 asm("r4") = 0x3C;
                        temp_r1_21 = M2C_FIELD(reference_r2, s16 *, offset_r4);
                    }
                    if ((s32) current_r0 <= (s32) temp_r1_21) {
                        temp_r1_22 = temp_r1_21 ^ current_r0;
                        var_r2_12 = (u32) ((0 - temp_r1_22) | temp_r1_22) >> 0x1F;
                    } else {
                        var_r2_12 = 2;
                    }
                }
                CALL_STAT_ROW(temp_r3_9, var_r2_12, 0xA);
                temp_r3_10 = LOAD_RECORD_4A(temp_r2);
                {
                    register s32 current_r0 asm("r0") = temp_r3_10;
                    asm volatile("C8538_PATCH_FINAL_REFERENCE");
                    temp_r1_23 = *(s16 *)0x02033F0E;
                    if ((s32) current_r0 <= (s32) temp_r1_23) {
                        temp_r1_24 = temp_r1_23 ^ current_r0;
                        var_r2_13 = (u32) ((0 - temp_r1_24) | temp_r1_24) >> 0x1F;
                    } else {
                        var_r2_13 = 2;
                    }
                }
                CALL_STAT_ROW(temp_r3_10, var_r2_13, 0xC);
            } else {
                asm volatile("C8538_PATCH_STACK_ARG r2");
                func_080981F0(0x08107658, 0, 2, 4, 0);
                asm volatile("C8538_PATCH_STACK_ARG r3");
                func_080981F0(0x08107658, 0, 2, 9, 0);
                func_080981F0(0x08107658, 0, 2, 4, 1);
                func_080981F0(0x08107658, 0, 2, 9, 1);
                asm volatile("C8538_PATCH_STACK_ARG r4");
                func_080981F0(0x08107658, 0, 2, 4, 2);
                asm volatile("C8538_PATCH_STACK_ARG r0");
                func_080981F0(0x08107658, 0, 2, 4, 4);
                func_080981F0(0x08107658, 0, 2, 4, 5);
                func_080981F0(0x08107658, 0, 2, 4, 6);
                func_080981F0(0x08107658, 0, 2, 4, 8);
                func_080981F0(0x08107658, 0, 2, 4, 9);
                func_080981F0(0x08107658, 0, 2, 4, 0xA);
                func_080981F0(0x08107658, 0, 2, 4, 0xC);
            }
            if (func_080BF464(var_r9, var_r7, 0x19) != 0xFF) {
                func_080981F0(0x08107660, 0, 2, 0, 0xE);
                func_08098248(0x08107664, 1, 2);
            } else {
                func_080981F0(0x0810766C, 0, 2, 0, 0xE);
            }
            if (func_080BF464(var_r9, var_r7, 0x18) != 0xFF) {
                func_080981F0(0x08107660, 0, 2, 0, 0xF);
                func_08098248(0x08107674, 1, 2);
            } else {
                func_080981F0(0x08107680, 0, 2, 0, 0xF);
            }
            if (func_080BF464(var_r9, var_r7, 0x1C) != 0xFF) {
                func_080981F0(0x08107660, 0, 2, 0, 0x10);
                func_08098248(0x0810768C, 2, 2);
            } else {
                func_080981F0(0x0810766C, 0, 2, 0, 0x10);
            }
            if (func_080BF464(var_r9, var_r7, 0x15) != 0xFF) {
                func_080981F0(0x08107660, 0, 2, 0, 0x11);
                func_08098248(0x08107694, 2, 2);
            } else {
                func_080981F0(0x081076A0, 0, 2, 0, 0x11);
            }
            func_080986B4(3);
            {
                register s32 *names_r1 asm("r1") = (s32 *)0x087EDD54;
                register void *record_r2 asm("r2") = temp_r2;
                asm volatile("" : "+r"(record_r2));
                asm volatile("C8538_PATCH_FIRST_NAME_CALL");
                func_080981F0(names_r1[M2C_FIELD(record_r2, u8 *, 0)], 0, 3, 0, 0);
            }
            func_080986B4(4);
            {
                register u8 *base_r2 asm("r2") = (u8 *)0x02034B4C;
                register u32 slot4_r4 asm("r4") = stack.sp28;
                register u32 address_r1 asm("r1");
                register u32 side_offset_r0 asm("r0");
                register u32 side_r3 asm("r3");
                address_r1 = slot4_r4 + var_r7;
                address_r1 = ((address_r1 << 3) - var_r7) << 4;
                side_offset_r0 = stack.sp24;
                side_offset_r0 += var_r9;
                side_offset_r0 <<= 3;
                side_r3 = var_r9;
                asm volatile("" : "+r"(side_r3));
                side_offset_r0 = (side_offset_r0 - side_r3) << 7;
                address_r1 += side_offset_r0;
                address_r1 += (u32) base_r2;
                address_r1 += 0x70;
                address_r1 = M2C_FIELD(address_r1, u8 *, 0);
                {
                    register s32 name_result_r0 asm("r0");
                    name_result_r0 = func_080E9924(var_r9, address_r1);
                    asm volatile("C8538_PATCH_STACK_ARG r4\n\tC8538_INSERT_R3_BEFORE_BL"
                        : "+r"(name_result_r0));
                    func_080981F0(name_result_r0, 0, 4, 0, 0);
                }
            }
            func_080972C8();
        }
        func_080BB224(5, var_r9, var_r7, 0);
        {
            register u8 *entry asm("r0");
            register u8 *table asm("r1") = (u8 *)0x02032E8C;
            register u32 slot_offset asm("r2");
            asm volatile("" : "+r"(table));
            entry = (u8 *) stack.sp20;
            entry += var_r9;
            entry = (u8 *) ((u32) entry << 3);
            slot_offset = stack.sp28;
            entry = (u8 *)(slot_offset - (0 - (u32) entry));
            entry += (u32) table;
            {
                register u16 selected_value asm("r1");
                register void *window_ptr asm("r3");
                selected_value = M2C_FIELD(M2C_FIELD(entry, void **, 0), u16 *, 4);
                window_ptr = stack.sp14;
                M2C_FIELD(window_ptr, u16 *, 4) = selected_value;
            }
            entry = M2C_FIELD(entry, void **, 0);
            var_r1 = M2C_FIELD(entry, s16 *, 0xC);
            if ((s32) var_r1 < 0) {
                var_r1 += 7;
            }
            asm volatile("C8538_DELAY_FINAL_POINTER");
            M2C_FIELD(stack.sp14, s16 *, 6) =
                (s16) (M2C_FIELD(entry, u16 *, 6) - (var_r1 >> 3));
        }
        func_080ED17C(1);
        var_sl = var_r9;
        stack.sp18 = (s32) var_r7;
    } while (!(3 & *(u16 *)0x0300000E));
    func_08092E84(0x3F);
    func_08094554(stack.sp14);
    func_08098BB4(0x08003F84);
    {
        u8 *control = (u8 *)0x030033C4;
        M2C_FIELD(control, s32 *, 0x14) = 0x78;
        M2C_FIELD(control, s32 *, 0x18) = 0x78;
    }
}
