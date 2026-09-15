#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
void *func_08094374(M2C_UNK, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_08096F3C();                            /* extern */
M2C_UNK func_0809AA64(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_080BB224(s32, u8, s32, s32);           /* extern */
s32 func_080E9D88(u8, u8);                          /* extern */
s32 func_080ECE30(s32, s32);                        /* extern */
s32 func_080ECF00(u8, s32);                         /* extern */
u8 func_080ECF78(u32, s32);                         /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

#define CARRY_R0(value) ({ register s32 v asm("r0") = (value); asm volatile("" : "+r"(v)); v; })
#define CARRY_R1(value) ({ register s32 v asm("r1") = (value); asm volatile("" : "+r"(v)); v; })
#define CARRY_R2(value) ({ register s32 v asm("r2") = (value); asm volatile("" : "+r"(v)); v; })
#define CARRY_R3(value) ({ register s32 v asm("r3") = (value); asm volatile("" : "+r"(v)); v; })

u8 sub_080C05A8(s32 arg0, s32 arg1) {
    volatile s32 sp14;
    s16 temp_r6_4;
    s32 var_r1;
    s16 var_r5_4;
    s32 temp_r4_4;
    s32 var_r0;
    s32 var_r0_2;
    u16 temp_r1;
    u16 temp_r1_3;
    u16 temp_r1_4;
    u16 temp_r1_5;
    u16 temp_r1_6;
    u8 temp_r0;
    u8 temp_r1_2;
    u8 temp_r4;
    u8 temp_r4_10;
    u8 temp_r4_2;
    u8 temp_r4_3;
    u8 temp_r4_6;
    u8 temp_r4_7;
    u8 temp_r4_8;
    u8 temp_r4_9;
    u8 temp_r5;
    u8 temp_r6;
    u8 temp_r9;
    u16 var_r5;
    u8 var_r7;
    void *temp_r0_2;
    void *temp_sl;

    temp_r0 = arg0;
    temp_r6 = arg1;
    func_0809AA64(0x087AC9D8, 0, 0x360, 0xD);
    temp_sl = func_08094374(0x087AC9E0, 0, 0, 0, 0, 0x360, 0xD, 0x60, 0);
    var_r5 = temp_r6;
    while ((func_080E9D88(temp_r0, temp_r4 = var_r5) << 0x18) == 0) {
        var_r5 = func_080ECE30((s16) var_r5 + 1, 6);
        if ((s16) var_r5 == temp_r6) {
            asm volatile(
                ".syntax unified\n\t"
                "movs r0, #255\n\t"
                "b .Lsub_080C05A8_return\n\t"
                ".syntax divided"
                : : : "r0");
        }
    }
    var_r7 = temp_r4;
    func_080BB224(2, temp_r0, 0, 0);
    func_08096F3C();
loop_6:
        temp_r9 = var_r7;
        asm volatile("" :: "r"(temp_r9));
        {
        register u16 keys asm("r1") = *(u16 *)0x03006034;
        if (((0x40 & keys) && (temp_r0 == 0)) || ((0x80 & keys) && (temp_r0 != 0))) {
            temp_r1_2 = func_080ECF78((u32) var_r7, 3);
            if (temp_r1_2 != 0) {
                register s32 var_r5_2 asm("r5");
                register s32 temp_r6_2 asm("r6");
                register s32 var_r2 asm("r2");
                asm volatile(
                    ".syntax unified\n\t"
                    "subs r0, %1, #1\n\t"
                    "lsls r0, r0, #16\n\t"
                    "lsrs %0, r0, #16\n\t"
                    ".syntax divided"
                    : "=r"(var_r5_2) : "r"(var_r7) : "r0");
                var_r2 = var_r7 - temp_r1_2;
                while ((s32) ({
                    asm volatile(
                        ".syntax unified\n\t"
                        "lsls r0, %1, #16\n\t"
                        "asrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(temp_r6_2) : "r"(var_r5_2) : "r0");
                    temp_r6_2;
                }) >= var_r2) {
                    temp_r4_2 = (u8) var_r5_2;
                    asm volatile("" :: "r"(var_r5_2));
                    if ((s32) ({
                        register s32 valid asm("r0") = temp_r0;
                        register s32 item asm("r1") = temp_r4_2;
                        asm volatile(
                            ".syntax unified\n\t"
                            "str %2, [sp, #20]\n\t"
                            "bl func_080E9D88\n\t"
                            ".syntax divided"
                            : "+r"(valid), "+r"(item), "+r"(var_r2)
                            : : "r3", "lr", "cc", "memory");
                        valid <<= 0x18;
                        var_r2 = sp14;
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
                        : "=r"(var_r5_2) : "r"(temp_r6_2) : "r0");
                }
                if (var_r7 == temp_r9) {
                    register s32 count asm("r0");
                    register u16 var_r5_3 asm("r5");
                    register s32 temp_r6_3 asm("r6");
                    register s32 var_r2_2 asm("r2");
                    register s32 base asm("r0") = 0;
                    if ((u32) var_r7 <= 2U) {
                        base = 3;
                    }
                    asm volatile("" : "+r"(base));
                    var_r0 = base;
                    count = func_080ECF78((u32) var_r7, 3);
                    {
                        register s32 neg1 asm("r2") = 0xFFFF;
                        asm volatile(
                            ".syntax unified\n\t"
                            "adds r0, %1, %2\n\t"
                            "adds r0, %3, r0\n\t"
                            "lsls r0, r0, #16\n\t"
                            "lsrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(var_r5_3), "+r"(count)
                            : "r"(neg1), "r"(var_r0));
                    }
                    var_r2_2 = var_r0;
                    while ((s32) ({
                        asm volatile(
                            ".syntax unified\n\t"
                            "lsls r0, %1, #16\n\t"
                            "asrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(temp_r6_3) : "r"(var_r5_3) : "r0");
                        temp_r6_3;
                    }) >= var_r2_2) {
                        temp_r4_3 = (u8) var_r5_3;
                        asm volatile("" :: "r"(var_r5_3));
                        if ((s32) ({
                            register s32 valid asm("r0") = temp_r0;
                            register s32 item asm("r1") = temp_r4_3;
                            asm volatile(
                                ".syntax unified\n\t"
                                "str %2, [sp, #20]\n\t"
                                "bl func_080E9D88\n\t"
                                ".syntax divided"
                                : "+r"(valid), "+r"(item), "+r"(var_r2_2)
                                : : "r3", "lr", "cc", "memory");
                            valid <<= 0x18;
                            var_r2_2 = sp14;
                            valid;
                        }) != 0) {
                            var_r7 = temp_r4_3;
                            func_08092E84(0x40);
                            break;
                        }
                        asm volatile(
                            ".syntax unified\n\t"
                            "subs r0, %1, #1\n\t"
                            "lsls r0, r0, #16\n\t"
                            "lsrs %0, r0, #16\n\t"
                            ".syntax divided"
                            : "=r"(var_r5_3) : "r"(temp_r6_3) : "r0");
                    }
                }
            }
        }
        }
        {
        register u16 keys asm("r1") = *(u16 *)0x03006034;
        if ((((0x40 & keys) && (CARRY_R3(temp_r0) != 0)) || ((0x80 & keys) && (CARRY_R0(temp_r0) == 0))) && ((u32) func_080ECF78((u32) var_r7, 3) <= 1U)) {
            register s32 temp_r4_5 asm("r4");
            var_r5_4 = var_r7 + 1;
            asm volatile("" :: "r"(var_r5_4));
            temp_r4_4 = var_r7 + 3;
            temp_r4_5 = temp_r4_4 - func_080ECE30(temp_r4_4, 3);
            asm volatile(
                ".syntax unified\n\t"
                "lsls %0, %0, #16\n\t"
                "asrs %0, %0, #16\n\t"
                ".syntax divided"
                : "+r"(temp_r4_5));
            while ((s32) (temp_r6_4 = var_r5_4) < (s32) temp_r4_5) {
                temp_r5 = (u8) var_r5_4;
                if ((func_080E9D88(temp_r0, temp_r5) << 0x18) != 0) {
                    var_r7 = temp_r5;
                    func_08092E84(0x40);
                    break;
                }
                var_r5_4 = (s16) (u16) (temp_r6_4 + 1);
            }
            if (var_r7 == temp_r9) {
                register s32 count asm("r0");
                register s32 var_r5_5 asm("r5");
                register s32 temp_r6_5 asm("r6");
                register s32 var_r2_3 asm("r2");
                register s32 base asm("r0") = 0;
                if ((u32) var_r7 <= 2U) {
                    base = 3;
                }
                asm volatile("" : "+r"(base));
                var_r0_2 = base;
                count = func_080ECF78((u32) var_r7, 3);
                asm volatile(
                    ".syntax unified\n\t"
                    "adds %1, %1, #1\n\t"
                    "adds %0, %2, %1\n\t"
                    ".syntax divided"
                    : "=r"(var_r5_5), "+r"(count) : "r"(var_r0_2));
                var_r2_3 = var_r0_2 + 3;
                while ((s32) ({
                    asm volatile(
                        ".syntax unified\n\t"
                        "lsls r0, %1, #16\n\t"
                        "asrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(temp_r6_5) : "r"(var_r5_5) : "r0");
                    temp_r6_5;
                }) < var_r2_3) {
                    temp_r4_6 = (u8) var_r5_5;
                    asm volatile("" :: "r"(var_r5_5));
                    if ((s32) ({
                        register s32 valid asm("r0") = temp_r0;
                        register s32 item asm("r1") = temp_r4_6;
                        asm volatile(
                            ".syntax unified\n\t"
                            "str %2, [sp, #20]\n\t"
                            "bl func_080E9D88\n\t"
                            ".syntax divided"
                            : "+r"(valid), "+r"(item), "+r"(var_r2_3)
                            : : "r3", "lr", "cc", "memory");
                            valid <<= 0x18;
                        var_r2_3 = sp14;
                        valid;
                    }) != 0) {
                        var_r7 = temp_r4_6;
                        func_08092E84(0x40);
                        break;
                    }
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds r0, %1, #1\n\t"
                        "lsls r0, r0, #16\n\t"
                        "lsrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(var_r5_5) : "r"(temp_r6_5) : "r0");
                }
            }
        }
        }
        {
        register u16 keys asm("r1") = *(u16 *)0x03006034;
        if ((((0x20 & keys) && (CARRY_R2(temp_r0) == 0)) || ((0x10 & keys) && (CARRY_R3(temp_r0) != 0))) && ((func_080ECF00(var_r7, 3) << 0x18) != 0)) {
            temp_r4_7 = var_r7 - 3;
            if ((func_080E9D88(temp_r0, temp_r4_7) << 0x18) != 0) {
                var_r7 = temp_r4_7;
                func_08092E84(0x40);
            } else {
                register s32 var_r5_6 asm("r5");
                register s32 temp_r6_6 asm("r6");
                var_r5_6 = 0;
                while ((s32) ({
                    asm volatile(
                        ".syntax unified\n\t"
                        "lsls r0, %1, #16\n\t"
                        "asrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(temp_r6_6) : "r"(var_r5_6) : "r0");
                    temp_r6_6;
                }) <= 2) {
                    temp_r4_8 = (u8) var_r5_6;
                    asm volatile("" :: "r"(var_r5_6));
                    if ((func_080E9D88(temp_r0, temp_r4_8) << 0x18) != 0) {
                        var_r7 = temp_r4_8;
                        func_08092E84(0x40);
                        break;
                    }
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds r0, %1, #1\n\t"
                        "lsls r0, r0, #16\n\t"
                        "lsrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(var_r5_6) : "r"(temp_r6_6) : "r0");
                }
            }
        }
        }
        {
        register u16 keys asm("r1") = *(u16 *)0x03006034;
        if ((((0x20 & keys) && (CARRY_R0(temp_r0) != 0)) || ((0x10 & keys) && (CARRY_R1(temp_r0) == 0))) && ((func_080ECF00(var_r7, 3) << 0x18) == 0)) {
            temp_r4_9 = var_r7 + 3;
            if ((func_080E9D88(temp_r0, temp_r4_9) << 0x18) != 0) {
                var_r7 = temp_r4_9;
                func_08092E84(0x40);
            } else {
                register s32 var_r5_7 asm("r5");
                register s32 temp_r6_7 asm("r6");
                var_r5_7 = 3;
                while ((s32) ({
                    asm volatile(
                        ".syntax unified\n\t"
                        "lsls r0, %1, #16\n\t"
                        "asrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(temp_r6_7) : "r"(var_r5_7) : "r0");
                    temp_r6_7;
                }) <= 5) {
                    temp_r4_10 = (u8) var_r5_7;
                    asm volatile("" :: "r"(var_r5_7));
                    if ((func_080E9D88(temp_r0, temp_r4_10) << 0x18) != 0) {
                        var_r7 = temp_r4_10;
                        func_08092E84(0x40);
                        break;
                    }
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds r0, %1, #1\n\t"
                        "lsls r0, r0, #16\n\t"
                        "lsrs %0, r0, #16\n\t"
                        ".syntax divided"
                        : "=r"(var_r5_7) : "r"(temp_r6_7) : "r0");
                }
            }
        }
        }
        {
        register u16 keys asm("r1") = *(u16 *)0x0300000E;
        if (1 & keys) {
            func_08092E84(0x3E);
        } else if (2 & keys) {
            var_r7 = 0xFF;
            func_08092E84(0x3F);
        } else {
            register u32 table asm("r2") = 0x02032E8C;
            register u32 slot asm("r1") = (u32) var_r7 << 2;
            register u32 side asm("r3") = temp_r0;
            register u32 offset asm("r0") = side << 1;
            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(slot));
            asm volatile("" : "+r"(side));
            asm volatile("" : "+r"(offset));
            offset += temp_r0;
            offset <<= 3;
            slot += offset;
            slot += table;
            M2C_FIELD(temp_sl, u16 *, 4) = (u16) M2C_FIELD(M2C_FIELD(slot, void **, 0), u16 *, 4);
            asm volatile("" ::: "memory");
            temp_r0_2 = M2C_FIELD(slot, void **, 0);
            asm volatile(
                ".syntax unified\n\t"
                "movs r3, #12\n\t"
                "ldrsh %0, [%1, r3]\n\t"
                ".syntax divided"
                : "=l"(var_r1) : "l"(temp_r0_2) : "r3");
            if ((s32) var_r1 < 0) {
                var_r1 += 7;
            }
            M2C_FIELD(temp_sl, s16 *, 6) = (s16) (M2C_FIELD(temp_r0_2, u16 *, 6) - (var_r1 >> 3));
            func_080ED17C(1);
            goto loop_6;
        }
        }
    func_08094554(temp_sl);
    {
        register u8 result asm("r0") = var_r7;
        asm volatile(".Lsub_080C05A8_return:" : : "r"(result));
        return result;
    }
}
