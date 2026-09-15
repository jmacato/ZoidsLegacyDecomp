#include "m2c_prelude.h"

s32 func_080E522C(s32, s32);                        /* extern */
s32 func_080E74F0(void *, s32, s32);                /* extern */
s16 func_080ECD98(s32, u8);                         /* extern */

void sub_080E6994(void *raw0, void *raw1, void *raw2, M2C_UNK arg3, void *raw4) {
    register void *arg0 asm("r8") = raw0;
    register void *arg1 asm("r6") = raw1;
    register void *arg2 asm("r9") = raw2;
    register void *arg4 asm("r5") = raw4;
    register s16 stat asm("r4");
    s32 delta;
    u8 var_r7;

    asm volatile(""
        : "+r"(arg0), "+r"(arg1), "+r"(arg2), "+r"(arg4));

    if (arg1 == 0) {
        return;
    }
    if (1 & M2C_FIELD(arg4, u16 *, 2)) {
        return;
    }
    var_r7 = M2C_FIELD(arg1, u8 *, 0x30);
    if ((func_080E74F0(arg1, 3, M2C_FIELD(arg0, u8 *, 0)) << 0x10) != 0) {
        var_r7 += 5;
    }
    {
        register void *bonus_base asm("r1") = arg0;
        asm volatile("" : "+r"(bonus_base));
        if ((func_080E74F0(arg1, 4, M2C_FIELD(bonus_base, u8 *, 0)) << 0x10) != 0) {
            var_r7 += 0xA;
        }
    }
    {
        register void *bonus_base asm("r3") = arg0;
        asm volatile("" : "+r"(bonus_base));
        if ((func_080E74F0(arg1, 5, M2C_FIELD(bonus_base, u8 *, 0)) << 0x10) != 0) {
            var_r7 += 0x14;
        }
    }
    if (arg2 != 0) {
        var_r7 += M2C_FIELD(arg2, u8 *, 0x28);
    }
    if ((u32) var_r7 > 0x63U) {
        var_r7 = 0x63;
    }
    stat = M2C_FIELD(arg1, u16 *, 0x3A);
#define APPLY_STAT(ID, OP) do {                                             \
        delta = func_080E74F0(arg1, (ID), M2C_FIELD(arg4, s32 *, 4));       \
        asm volatile(                                                       \
            "lsl %0, %0, #16\n"                                           \
            "asr %0, %0, #16\n"                                           \
            OP " %0, %0, %1\n"                                            \
            "lsl %0, %0, #16\n"                                           \
            "lsr %0, %0, #16"                                             \
            : "+r"(stat)                                                   \
            : "r"(delta));                                                 \
    } while (0)
    APPLY_STAT(0x17, "sub");
    APPLY_STAT(0x18, "sub");
    APPLY_STAT(0x21, "add");
    APPLY_STAT(0x19, "sub");
    APPLY_STAT(0x1A, "sub");
    APPLY_STAT(0x1B, "sub");
    APPLY_STAT(0x1C, "sub");
    APPLY_STAT(0x1D, "sub");
    APPLY_STAT(0x1E, "sub");
    APPLY_STAT(0x22, "add");
    APPLY_STAT(0x23, "add");
    APPLY_STAT(0x24, "add");
    APPLY_STAT(0x25, "add");
    APPLY_STAT(0x26, "add");
#undef APPLY_STAT
    delta = func_080E74F0(arg1, 0x27, M2C_FIELD(arg4, s32 *, 4));
    asm volatile(
        "lsl %0, %0, #16\n"
        "asr %0, %0, #16\n"
        "add %0, %0, %1"
        : "+r"(stat)
        : "r"(delta));
    {
        register s32 result asm("r0");
        asm volatile(
            "movs r1, #12\n"
            "ldrsh r0, [r5, r1]\n"
            "lsl %1, %1, #16\n"
            "asr %1, %1, #16\n"
            "add r1, %1, #0\n"
            "bl func_080E522C"
            : "=r"(result), "+r"(stat)
            :
            : "r1", "r2", "r3", "lr", "cc", "memory");
        M2C_FIELD(arg4, s16 *, 0xC) = (u16) M2C_FIELD(arg4, s16 *, 0xC) + result;
    }
    {
        u8 *limit = &M2C_FIELD(arg0, u8 *, 0x39);
        if ((u32) var_r7 < (u32) *limit) {
            M2C_FIELD(arg4, s16 *, 0xC) = func_080ECD98(M2C_FIELD(arg4, s16 *, 0xC) * var_r7, *limit);
        }
    }
    if (arg2 != 0) {
        register s32 result asm("r0");
        asm volatile(
            "movs r1, #10\n"
            "ldrsh r0, [r5, r1]\n"
            "mov r2, r9\n"
            "movs r3, #44\n"
            "ldrsh r1, [r2, r3]\n"
            "bl func_080E522C"
            : "=r"(result)
            :
            : "r1", "r2", "r3", "lr", "cc", "memory");
        M2C_FIELD(arg4, s16 *, 0xA) = (u16) M2C_FIELD(arg4, s16 *, 0xA) + result;
    }
    if (M2C_FIELD(arg4, s16 *, 0x10) != 0) {
        if ((func_080E74F0(arg1, 6, M2C_FIELD(arg4, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(arg4, s16 *, 0x10) = func_080E522C(M2C_FIELD(arg4, s16 *, 0x10), 0x5A);
        }
        if ((func_080E74F0(arg1, 7, M2C_FIELD(arg4, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(arg4, s16 *, 0x10) = func_080E522C(M2C_FIELD(arg4, s16 *, 0x10), 0x46);
        }
        if ((func_080E74F0(arg1, 8, M2C_FIELD(arg4, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(arg4, s16 *, 0x10) = func_080E522C(M2C_FIELD(arg4, s16 *, 0x10), 0x32);
        }
        if ((func_080E74F0(arg1, 9, M2C_FIELD(arg4, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(arg4, s16 *, 0x10) = func_080E522C(M2C_FIELD(arg4, s16 *, 0x10), 0x5A);
        }
        if ((func_080E74F0(arg1, 0xA, M2C_FIELD(arg4, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(arg4, s16 *, 0x10) = func_080E522C(M2C_FIELD(arg4, s16 *, 0x10), 0x46);
        }
        if ((func_080E74F0(arg1, 0xB, M2C_FIELD(arg4, s32 *, 4)) << 0x10) != 0) {
            M2C_FIELD(arg4, s16 *, 0x10) = func_080E522C(M2C_FIELD(arg4, s16 *, 0x10), 0x32);
        }
        if (M2C_FIELD(arg4, s16 *, 0x10) == 0) {
            M2C_FIELD(arg4, s16 *, 0x10) = 1;
        }
    }
    if ((s32) M2C_FIELD(arg4, s16 *, 0xA) > 0x270F) {
        M2C_FIELD(arg4, s16 *, 0xA) = 0x270F;
    }
    {
        u16 cap = M2C_FIELD(arg4, u16 *, 0xE);
        if ((s32) M2C_FIELD(arg4, s16 *, 0xC) > (s32) (s16) cap) {
            M2C_FIELD(arg4, s16 *, 0xC) = cap;
        }
    }
}
