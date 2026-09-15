#include "m2c_prelude.h"

#define NULL ((void *)0)
#define ARG6_FOUR_R2() ({ \
    register s32 value asm("r2") = 4; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define ARG5_FOUR_R3() ({ \
    register s32 value asm("r3") = 4; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define ARG5_FOUR_R2() ({ \
    register s32 value asm("r2") = 4; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define ARG6_EIGHT_R1() ({ \
    register s32 value asm("r1") = 8; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define ARG7_EIGHT_R2() ({ \
    register s32 value asm("r2") = 8; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define ARG7_EIGHT_R1() ({ \
    register s32 value asm("r1") = 8; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define ARG7_TEN_R3() ({ \
    register s32 value asm("r3") = 0xA; \
    asm volatile("" : : "r"(value)); \
    value; \
})
#define ARG6_TEN_R3() ({ \
    register s32 value asm("r3") = 0xA; \
    asm volatile("" : : "r"(value)); \
    value; \
})
#define ARG5_152_R0() ({ \
    register s32 value asm("r0") = 0x98; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define FRESH_THIRTEEN_R1() ({ \
    register s32 value asm("r1"); \
    asm volatile("mov %0, #13" : "=r"(value)); \
    value; \
})
#define FRESH_THIRTEEN_R2() ({ \
    register s32 value asm("r2"); \
    asm volatile("mov %0, #13" : "=r"(value)); \
    value; \
})
#define FRESH_ZERO_R2() ({ \
    register s32 value asm("r2"); \
    asm volatile("mov %0, #0" : "=r"(value)); \
    value; \
})
#define ARG9_ZERO_R1() ({ \
    register s32 value asm("r1") = 0; \
    asm volatile("" : "+r"(value)); \
    value; \
})
#define EMIT_THIRTEEN_R1() ({ \
    asm volatile("mov r1, #13" : : : "r1"); \
    13; \
})
#define EMIT_THIRTEEN_R3() ({ \
    asm volatile("B2108_STORE_THIRTEEN_R3" : : : "r3", "memory"); \
    13; \
})
extern u8 D_020218E4[];
extern u8 D_02027378[];
extern u8 D_020321A4[];
extern u8 D_02032273[];
#define D_087EDD54_reload ((s32 *)0x087EDD54)

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
extern s32 func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(); /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s16, s32);     /* extern */
asm(".set func_080981F0_4, func_080981F0");
extern M2C_UNK func_080981F0_4(s32, s32, s32, s32);
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C(); /* extern */
u8 func_08098B58();                              /* extern */
asm(".set func_08098B58_raw, func_08098B58");
extern s32 func_08098B58_raw();
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A52C(u8, u8, s32, s32, s32);       /* extern */
M2C_UNK func_0809A9C8(u8, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080AC214(s32, s32);                    /* extern */
M2C_UNK func_080AC3B8(s32, s32, u8);                /* extern */
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACBA0(s32);                         /* extern */
M2C_UNK func_080ACBDC(s32, s32);                    /* extern */
M2C_UNK func_080ACCC4(s32, s32);                    /* extern */
M2C_UNK func_080B61C8(s32, s32, s32);               /* extern */
M2C_UNK func_080B63C4();                            /* extern */
M2C_UNK func_080E5880(M2C_UNK *, void *);           /* extern */
M2C_UNK func_080E6020(u8);                          /* extern */
M2C_UNK func_080E6FA0(u8, u8);                      /* extern */
s32 func_080E74F0(void *, s32, u8);                 /* extern */
s32 func_080E7B64(u8);                              /* extern */
s16 func_080ECD98(s16, s32);                        /* extern */
M2C_UNK func_080ED038(M2C_UNK *, void *, s32);      /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

asm(
    ".macro B2108_DROP_NEXT_BRANCH\n"
    ".macro b target\n"
    ".purgem b\n"
    ".purgem bl\n"
    ".endm\n"
    ".macro bl target\n"
    ".purgem b\n"
    ".purgem bl\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_FORCE_SHORT_NEXT_BRANCH\n"
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
    ".macro B2108_STORE_THIRTEEN_R3\n"
    "mov r3, #13\n"
    "str r3, [sp, #8]\n"
    ".macro str args:vararg\n"
    ".purgem str\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_PATCH_ARG_ONE\n"
    ".set B2108_ARG_MOV_COUNT, 0\n"
    ".set B2108_ARG_STR_COUNT, 0\n"
    ".macro mov dst, src\n"
    ".if B2108_ARG_MOV_COUNT == 0\n"
    ".short 0x2413\n"
    ".else\n"
    ".short 0x2201\n"
    ".purgem mov\n"
    ".endif\n"
    ".set B2108_ARG_MOV_COUNT, B2108_ARG_MOV_COUNT + 1\n"
    ".endm\n"
    ".macro str src, addr:vararg\n"
    ".if B2108_ARG_STR_COUNT == 0\n"
    ".short 0x9600\n"
    ".elseif B2108_ARG_STR_COUNT == 1\n"
    ".short 0x9401\n"
    ".else\n"
    ".short 0x9202\n"
    ".purgem str\n"
    ".endif\n"
    ".set B2108_ARG_STR_COUNT, B2108_ARG_STR_COUNT + 1\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_PATCH_ARG_ELEVEN\n"
    ".set B2108_ARG_STR_COUNT, 0\n"
    ".macro mov dst, src\n"
    ".short 0x230B\n"
    ".purgem mov\n"
    ".endm\n"
    ".macro str src, addr:vararg\n"
    ".if B2108_ARG_STR_COUNT == 0\n"
    ".short 0x9600\n"
    ".elseif B2108_ARG_STR_COUNT == 1\n"
    ".short 0x9401\n"
    ".else\n"
    ".short 0x9302\n"
    ".purgem str\n"
    ".endif\n"
    ".set B2108_ARG_STR_COUNT, B2108_ARG_STR_COUNT + 1\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_PATCH_FIRST_TABLE\n"
    ".macro ldr dst, src:vararg\n"
    ".purgem ldr\n"
    "ldr r1, .L160+4\n"
    ".endm\n"
    ".macro add dst, left, right\n"
    ".purgem add\n"
    "add r0, r0, r1\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_PATCH_SECOND_TABLE\n"
    ".macro add dst, left, right\n"
    ".purgem add\n"
    "ldr r1, .L160+4\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_PATCH_BLOCK65_INDEX\n"
    ".set B2108_BLOCK65_LDR_COUNT, 0\n"
    ".macro ldr dst, src:vararg\n"
    ".if B2108_BLOCK65_LDR_COUNT == 0\n"
    ".short 0x4834\n"
    ".else\n"
    ".short 0x9A25\n"
    ".purgem ldr\n"
    ".endif\n"
    ".set B2108_BLOCK65_LDR_COUNT, B2108_BLOCK65_LDR_COUNT + 1\n"
    ".endm\n"
    ".macro add dst, left, right\n"
    ".purgem add\n"
    "add r0, r2, r0\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_PATCH_BLOCK85_ENTRY\n"
    ".macro mov dst, src\n"
    ".purgem mov\n"
    "mov r3, sl\n"
    ".endm\n"
    ".macro ldrb dst, src:vararg\n"
    ".purgem ldrb\n"
    "ldrb r0, [r3, #0]\n"
    ".endm\n"
    ".endm\n"
    ".macro B2108_HOME_CALL addend, home, arg7\n"
    "mov r0, sp\n"
    "add r0, #\\addend\n"
    "str r0, [sp, #\\home]\n"
    "mov r1, #0\n"
    "ldrsh r0, [r0, r1]\n"
    "str r6, [sp, #0]\n"
    "mov r2, #4\n"
    "str r2, [sp, #4]\n"
    "mov r3, #\\arg7\n"
    "str r3, [sp, #8]\n"
    "mov r1, #4\n"
    "mov r2, #0\n"
    "mov r3, #10\n"
    "bl func_0809844C\n"
    ".endm\n"
    ".macro B2108_HOME_PAIR addend1, home1, arg1, addend2, home2, arg2\n"
    "B2108_HOME_CALL \\addend1, \\home1, \\arg1\n"
    "B2108_HOME_CALL \\addend2, \\home2, \\arg2\n"
    ".endm\n"
    ".macro B2108_HOME_LOCAL_PAIR addend, home, homearg, offset, localarg\n"
    "B2108_HOME_CALL \\addend, \\home, \\homearg\n"
    "B2108_LOCAL_CALL \\offset, \\localarg\n"
    ".endm\n"
    ".macro B2108_LOCAL_CALL offset, arg7\n"
    "add r0, sp, #20\n"
    "mov r1, #\\offset\n"
    "ldrsh r0, [r0, r1]\n"
    "str r6, [sp, #0]\n"
    "mov r2, #4\n"
    "str r2, [sp, #4]\n"
    "mov r3, #\\arg7\n"
    "str r3, [sp, #8]\n"
    "mov r1, #4\n"
    "mov r2, #0\n"
    "mov r3, #10\n"
    "bl func_0809844C\n"
    ".endm\n"
    ".macro B2108_HOME_TEN_CALL addend, home\n"
    "mov r0, sp\n"
    "add r0, #\\addend\n"
    "str r0, [sp, #\\home]\n"
    "mov r1, #0\n"
    "ldrsh r0, [r0, r1]\n"
    "str r6, [sp, #0]\n"
    "mov r2, #4\n"
    "str r2, [sp, #4]\n"
    "mov r3, #10\n"
    "str r3, [sp, #8]\n"
    "mov r1, #4\n"
    "mov r2, #0\n"
    "bl func_0809844C\n"
    ".endm\n"
    ".macro B2108_SL_CALLS\n"
    "mov r1, sl\n"
    "mov r2, #52\n"
    "ldrsh r0, [r1, r2]\n"
    "str r6, [sp, #0]\n"
    "mov r3, #10\n"
    "str r3, [sp, #4]\n"
    "mov r1, #1\n"
    "str r1, [sp, #8]\n"
    "mov r1, #3\n"
    "mov r2, #0\n"
    "bl func_0809844C\n"
    "mov r2, sl\n"
    "mov r3, #54\n"
    "ldrsh r0, [r2, r3]\n"
    "str r6, [sp, #0]\n"
    "mov r1, #10\n"
    "str r1, [sp, #4]\n"
    "mov r2, #6\n"
    "str r2, [sp, #8]\n"
    "mov r1, #3\n"
    "mov r2, #0\n"
    "mov r3, #10\n"
    "bl func_0809844C\n"
    "mov r3, sl\n"
    "mov r1, #60\n"
    "ldrsh r0, [r3, r1]\n"
    "str r6, [sp, #0]\n"
    "mov r2, #10\n"
    "str r2, [sp, #4]\n"
    "mov r3, #11\n"
    "str r3, [sp, #8]\n"
    "mov r1, #3\n"
    "mov r2, #0\n"
    "mov r3, #10\n"
    "bl func_0809844C\n"
    "mov r1, sl\n"
    "mov r2, #56\n"
    "ldrsh r0, [r1, r2]\n"
    "str r6, [sp, #0]\n"
    "mov r3, #10\n"
    "str r3, [sp, #4]\n"
    "mov r1, #13\n"
    "str r1, [sp, #8]\n"
    "mov r1, #3\n"
    "mov r2, #0\n"
    "bl func_0809844C\n"
    ".endm\n"
    ".macro B2108_ALL_HOME_CALLS\n"
    "B2108_HOME_CALL 84, 160, 3\n"
    "B2108_HOME_CALL 86, 164, 5\n"
    "B2108_HOME_CALL 88, 168, 6\n"
    "B2108_LOCAL_CALL 10, 7\n"
    "B2108_HOME_CALL 90, 172, 9\n"
    "B2108_HOME_TEN_CALL 92, 176\n"
    "B2108_LOCAL_CALL 60, 11\n"
    "B2108_HOME_CALL 94, 180, 13\n"
    "B2108_SL_CALLS\n"
    ".endm\n"
    ".macro B2108_BLOCK85_CALLS\n"
    "mov r2, sl\n"
    "ldrb r0, [r2, #0]\n"
    "bl func_080E7B64\n"
    "bl func_08098B58\n"
    "mov r3, sl\n"
    "ldrb r1, [r3, #1]\n"
    "lsl r0, r1, #3\n"
    "sub r0, r0, r1\n"
    "lsl r0, r0, #4\n"
    "ldr r1, .L176+4\n"
    "add r0, r0, r1\n"
    "ldrb r0, [r0, #4]\n"
    "lsl r0, r0, #2\n"
    "ldr r2, .L176+8\n"
    "add r0, r0, r2\n"
    "ldr r0, [r0, #0]\n"
    "mov r1, #2\n"
    "str r1, [sp, #0]\n"
    "mov r1, #1\n"
    "mov r2, #9\n"
    "mov r3, #0\n"
    "bl func_080981F0\n"
    "mov r3, sl\n"
    "ldrb r1, [r3, #1]\n"
    "lsl r0, r1, #3\n"
    "sub r0, r0, r1\n"
    "lsl r0, r0, #4\n"
    "ldr r1, .L176+4\n"
    "add r0, r0, r1\n"
    "ldrb r0, [r0, #4]\n"
    "lsl r0, r0, #2\n"
    "ldr r2, .L176+8\n"
    "add r0, r0, r2\n"
    "ldr r0, [r0, #0]\n"
    "bl func_08098B58\n"
    ".endm\n");

s32 sub_080B2108(void) {
    u8 sp14[112];
    s32 sp84;
    s32 sp88;
    s32 sp8C;
    void *sp90;
    void *sp94;
    s32 sp98;
    s32 sp9C;
    s16 *spA0;
    s16 *spA4;
    s16 *spA8;
    s16 *spAC;
    s16 *spB0;
    s16 *spB4;
    M2C_UNK var_r0;
    M2C_UNK var_r0_3;
    s32 temp_r4;
    u32 var_r4_2;
    s32 temp_r0;
    s32 temp_r0_3;
    s32 temp_r0_7;
    s32 var_r1;
    s32 var_r5;
    s32 var_r7;
    register s32 var_r7_2 asm("r7");
    u16 temp_r1;
    u16 temp_r1_2;
    u32 temp_r0_4;
    u32 temp_r5;
    u32 var_r4;
    u32 var_r4_scan;
    u8 temp_r0_2;
    u8 temp_r0_5;
    u8 temp_r0_6;
    u8 temp_r0_8;
    u8 temp_r0_9;
    u8 temp_r6;
    u8 temp_r6_2;
    u8 var_r0_2;
    u8 var_r5_2;
    void *temp_r1_3;
    void *temp_r1_4;
    void *var_r2;
    void *var_r9;
    void *var_sl;
    u8 *roster_base;
    register u8 *first_scan_base asm("r6");
    u8 *unit_base;
    u8 *entity_base;
    u8 *map_base;
    u8 *record_base;
    register u8 *saved_value_ptr asm("r8");
    u32 map_offset;
    register u32 zero_r3 asm("r3");
    register u32 zero_r4 asm("r4");

    sp84 = 0;
    var_r7 = 0;
loop_1:
    {
        register s32 dispatch_2005_r1 asm("r1") = 0x2005;
        asm volatile("" : : "r"(dispatch_2005_r1));
        if (var_r7 != dispatch_2005_r1) {
            goto block_3;
        }
        goto block_63;
block_3:
        if (var_r7 > dispatch_2005_r1) {
            goto block_21;
        }
    }
    if (var_r7 != 0x1010) {
        goto block_6;
    }
    goto block_41;
block_6:
    if (var_r7 > 0x1010) {
        goto block_11;
    }
    if (var_r7 == 0) {
        goto block_37;
    }
    if (var_r7 == 0x1000) {
        goto block_38;
    }
    goto block_147;
block_11:
    var_r1 = 0x1030;
    if (var_r7 != 0x1030) {
        goto block_13;
    }
    goto block_58;
block_13:
    if (var_r7 > 0x1030) {
        goto block_18;
    }
    if (var_r7 != 0x1020) {
        goto block_16;
    }
    goto block_57;
block_16:
    goto block_147;
block_18:
    if (var_r7 != 0x2000) {
        goto block_20;
    }
    goto block_61;
block_20:
    goto block_147;
block_21:
    var_r1 = 0x2030;
    if (var_r7 != 0x2030) {
        goto block_23;
    }
    goto block_85;
block_23:
    if (var_r7 > 0x2030) {
        goto block_30;
    }
    if (var_r7 != 0x2010) {
        goto block_26;
    }
    goto block_65;
block_26:
    if (var_r7 != 0x2020) {
        goto block_28;
    }
    goto block_81;
block_28:
    goto block_147;
block_30:
    {
        register s32 dispatch_4000_r2 asm("r2") = 0x4000;
        asm volatile("" : : "r"(dispatch_4000_r2));
        if (var_r7 == dispatch_4000_r2) {
            goto block_108;
        }
        if (var_r7 > dispatch_4000_r2) {
            goto block_35;
        }
    }
    if (var_r7 != 0x3000) {
        goto block_34;
    }
    goto block_90;
block_34:
    goto block_147;
block_35:
    if (var_r7 == 0x5000) {
        goto block_110;
    }
    goto block_147;
block_37:
    func_08098BB4(0x080021A6);
    func_080B61C8(0, 0, 0);
    func_080AC214(3, 8);
    sp98 = ({
        register s32 zero_r3_local asm("r3");
        asm volatile("mov %0, #0" : "=r"(zero_r3_local));
        zero_r3_local;
    });
    sp90 = ({
        register void *zero_r0_local asm("r0");
        asm volatile("mov %0, #0" : "=r"(zero_r0_local));
        zero_r0_local;
    });
    func_080ACA8C(7, 1, 1);
    var_r7 = 0x1000;
    goto block_147;
block_38:
    {
        register s32 gfx_a asm("r0");
        register s32 gfx_b asm("r1");

        asm volatile(
            "mov r0, #72\n\t"
            "str r0, [sp, #0]\n\t"
            "mov r1, #0\n\t"
            "str r1, [sp, #4]\n\t"
            "str r1, [sp, #8]\n\t"
            "mov r2, #8\n\t"
            "str r2, [sp, #12]\n\t"
            "str r1, [sp, #16]"
            : : : "r0", "r1", "r2", "memory");
        gfx_a = 0x0821024C;
        gfx_b = 0x08210258;
        asm volatile("" : "+r"(gfx_a), "+r"(gfx_b));
        sp88 = func_08094484_4(gfx_a, gfx_b, 0, 0xB8);
    }
    {
        register s32 gfx_a asm("r0");
        register s32 gfx_b asm("r1");
        register s32 stack_r0 asm("r0");

        asm volatile(
            "mov r0, #152\n\t"
            "str r0, [sp, #0]"
            : : : "r0", "memory");
        stack_r0 = 0x343;
        asm volatile("" : "+r"(stack_r0));
        asm volatile(
            "str %0, [sp, #4]\n\t"
            "mov %0, #15\n\t"
            "str %0, [sp, #8]\n\t"
            "mov r3, #8\n\t"
            "str r3, [sp, #12]\n\t"
            "mov %0, #0\n\t"
            "str %0, [sp, #16]"
            : "+r"(stack_r0) : : "r3", "memory");
        gfx_a = 0x08105A20;
        gfx_b = 0x08105A2C;
        asm volatile("" : "+r"(gfx_a), "+r"(gfx_b));
        sp8C = func_08094484_4(gfx_a, gfx_b, 0, 0xD8);
    }
block_39:
    asm volatile(".L_B2108_block39:");
    var_r7 = 0x1010;
    goto block_147;
block_41:
    {
    register s32 record_base_r1 asm("r1");

    temp_r0 = D_020321A4[(u32)sp90] * 0x70;
    record_base_r1 = 0x020218E8;
    asm volatile("" : "+r"(record_base_r1));
    temp_r0 += record_base_r1;
    var_r9 = (void *)temp_r0;
    asm volatile("" : "+r"(var_r9) : "r"(temp_r0));
    func_0809A52C(M2C_FIELD((void *)temp_r0, u8 *, 0),
        M2C_FIELD(var_r9, u8 *, 1), 0, 0, 0x02002880);
    }
    if (*(u8 *)0x0203055C == 1) {
        goto block_46;
    }
    temp_r4 = M2C_FIELD(var_r9, s16 *, 6);
    var_r5 = 0;
    if ((s32) M2C_FIELD(var_r9, s16 *, 6) >=
        (s32) func_080ECD98(M2C_FIELD(var_r9, s16 *, 0x3A), 0xA)) {
        goto block_44;
    }
    var_r5 = 1;
block_44:
    func_0809844C(temp_r4, 4, var_r5, 0xA, 4, 3, ARG7_EIGHT_R1());
    goto block_47;
block_46:
    asm volatile(
        "mov r2, r9\n\t"
        "mov r3, #58\n\t"
        "ldrsh r0, [r2, r3]\n\t"
        "mov r1, #4\n\t"
        "str r1, [sp, #0]\n\t"
        "mov r1, #3\n\t"
        "str r1, [sp, #4]\n\t"
        "mov r2, #8\n\t"
        "str r2, [sp, #8]\n\t"
        "mov r1, #4\n\t"
        "mov r2, #0\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C(M2C_FIELD(var_r9, s16 *, 0x3A), 4, 0, 0xA,
        4, 3, ARG7_EIGHT_R2());
    asm volatile(".endif");
block_47:
    asm volatile(
        "mov r3, r9\n\t"
        "mov r1, #58\n\t"
        "ldrsh r0, [r3, r1]\n\t"
        "mov r2, #4\n\t"
        "str r2, [sp, #0]\n\t"
        "mov r3, #8\n\t"
        "str r3, [sp, #4]\n\t"
        "str r3, [sp, #8]\n\t"
        "mov r1, #4\n\t"
        "mov r2, #0\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C(M2C_FIELD(var_r9, s16 *, 0x3A), 4, 0, 0xA,
        ARG5_FOUR_R2(), 8, 8);
    asm volatile(".endif");
    asm volatile(
        "mov r1, r9\n\t"
        "mov r2, #62\n\t"
        "ldrsh r0, [r1, r2]\n\t"
        "mov r3, #4\n\t"
        "str r3, [sp, #0]\n\t"
        "mov r1, #8\n\t"
        "str r1, [sp, #4]\n\t"
        "mov r5, #9\n\t"
        "str r5, [sp, #8]\n\t"
        "mov r1, #4\n\t"
        "mov r2, #0\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C(M2C_FIELD(var_r9, s16 *, 0x3E), 4, 0, 0xA,
        ARG5_FOUR_R3(), ARG6_EIGHT_R1(), 9);
    asm volatile(".endif");
    func_0809844C((s16) M2C_FIELD(var_r9, u8 *, 0x39), 2, 0, 0xA,
        ARG5_FOUR_R2(), 0xA, 0xA);
    {
        s32 item_address;
        s32 item_addend;

        {
            register u8 *first_record_r3 asm("r3") = var_r9;
            asm volatile("" : "+r"(first_record_r3));
            item_address = first_record_r3[2] << 6;
        }
        {
            register s32 first_item_base_r1 asm("r1") = (s32)D_020218E4;
            asm volatile("" : "+r"(first_item_base_r1));
            item_address += first_item_base_r1;
        }
        item_addend = 0x5A94;
        item_address += item_addend;
        func_080981F0(func_080E7B64(*(u8 *)item_address), 0, 4, 3, 0xC);
        {
            register u8 *second_record_r2 asm("r2") = var_r9;
            asm volatile("" : "+r"(second_record_r2));
            item_address = second_record_r2[2] << 6;
        }
        {
            register s32 second_item_base_r3 asm("r3") = (s32)D_020218E4;
            asm volatile("" : "+r"(second_item_base_r3));
            item_address += second_item_base_r3;
        }
        item_address += item_addend;
        func_080E7B64(*(u8 *)item_address);
    }
    temp_r6 = func_08098B58();
    var_r4 = 0;
    temp_r5 = 9 - temp_r6;
    if (var_r4 >= temp_r5) {
        goto block_49;
    }
loop_48:
    {
        register s32 call_r3 asm("r3") = (s16)(temp_r6 + 3 + var_r4);

        asm volatile("" : "+r"(call_r3));
        asm volatile(
            "mov r0, #12\n\t"
            "str r0, [sp, #0]"
            : : "r"(call_r3) : "r0", "memory");
        func_080981F0_4(0x081061C4, 0, 4, call_r3);
    }
    var_r4 += 1;
    if (var_r4 < temp_r5) {
        goto loop_48;
    }
block_49:
    func_080ACBDC(7, sp98);
    func_08098BB4(0x080021FE);
    sp90 = (void *) *(u8 *)0x0200A880;
    sp98 = (s32) *(u8 *)0x0200A881;
    temp_r0_2 = *(u8 *)0x0200A882;
    if (temp_r0_2 == 1) {
        goto block_53;
    }
    if (temp_r0_2 == 2) {
        goto block_56;
    }
    goto block_147;
block_53:
    {
        register u16 *owner_r0 asm("r0");
        register u32 mask_r2 asm("r2");
        register u32 mask_r0 asm("r0");

        owner_r0 = var_r9;
        asm volatile("" : "+r"(owner_r0));
        temp_r1 = owner_r0[2];
        mask_r2 = 0xFFFE;
        asm volatile("" : "+r"(mask_r2));
        mask_r0 = mask_r2;
        asm volatile("" : "+r"(mask_r0));
        temp_r1 &= mask_r0;
    }
    zero_r4 = 0;
    {
        register u16 *store_owner_r3 asm("r3") = var_r9;
        asm volatile("" : "+r"(store_owner_r3));
        store_owner_r3[2] = temp_r1;
    }
    if (2 & temp_r1) {
        goto block_55;
    }
    var_r7 = 0x1020;
    goto block_147;
block_55:
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(zero_r4) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x10E0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x2060;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    var_r0 = 0x0800223F;
    goto block_78;
block_56:
    var_r7 = 0x5000;
    goto block_147;
block_57:
    var_r0_2 = M2C_FIELD(var_r9, u8 *, 2);
    var_r7 = 0x2000;
    goto block_82;
block_58:
    func_08098BB4(0x080024F3);
    func_080981F0(({
        asm volatile("B2108_PATCH_FIRST_TABLE");
        M2C_FIELD((M2C_FIELD(var_r9, u8 *, 0) * 4), s32 *, 0x087EDD54);
    }), 2, 9, 0, FRESH_ZERO_R2());
    {
        register u8 *lookup_owner_r3 asm("r3") = var_r9;
        u32 lookup_offset;
        register s32 *lookup_table asm("r1");

        asm volatile("B2108_PATCH_SECOND_TABLE" : "+r"(lookup_owner_r3));
        lookup_offset = lookup_owner_r3[0] * 4;
        lookup_table = D_087EDD54_reload;
        asm volatile("" : "+r"(lookup_table));
        lookup_offset += (u32)lookup_table;
        func_08098B58(*(s32 *)lookup_offset);
    }
    {
        s32 item_address;
        s32 item_addend;

        {
            register u8 *first_record_r2 asm("r2") = var_r9;
            asm volatile("" : "+r"(first_record_r2));
            item_address = first_record_r2[2] << 6;
        }
        {
            register s32 first_item_base_r3 asm("r3") = (s32)D_020218E4;
            asm volatile("" : "+r"(first_item_base_r3));
            item_address += first_item_base_r3;
        }
        item_addend = 0x5A94;
        item_address += item_addend;
        func_080981F0(func_080E7B64(*(u8 *)item_address), 1, 9, 0, 2);
        {
            register u8 *second_record_r1 asm("r1") = var_r9;
            asm volatile("" : "+r"(second_record_r1));
            item_address = second_record_r1[2] << 6;
        }
        {
            register s32 second_item_base_r2 asm("r2") = (s32)D_020218E4;
            asm volatile("" : "+r"(second_item_base_r2));
            item_address += second_item_base_r2;
        }
        item_address += item_addend;
        func_080E7B64(*(u8 *)item_address);
    }
    func_08098B58();
    zero_r3 = 0;
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(zero_r3) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x20D0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x850;
        asm volatile("" : "+r"(msg_r2));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(zero_r3)
            : : "lr", "cc", "memory");
    }
    func_08098BB4(0x0800254C);
    func_0809534C();
    temp_r0_2 = *(u8 *)0x0200A882;
    var_r7 = 0x1010;
    if (temp_r0_2 != 1) {
        goto block_147;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_147;
    }
    var_r7 = 0x2000;
    goto block_147;
block_61:
    func_08094554(sp88);
    func_08094554(sp8C);
    func_08098BB4(0x080022CE);
    func_080B63C4();
    {
        register s32 item_base asm("r2");
        register u8 *item_owner_r1 asm("r1") = var_r9;
        register s32 item_addend_r3 asm("r3");
        s32 item_address;

        asm volatile("" : "+r"(item_owner_r1));
        item_address = item_owner_r1[2] << 6;
        item_base = (s32)D_020218E4;
        asm volatile("" : "+r"(item_base));
        item_address += item_base;
        item_addend_r3 = 0x5A94;
        asm volatile("" : "+r"(item_addend_r3));
        item_address += item_addend_r3;
        func_080AC3B8(6, 1, *(u8 *)item_address);
    }
    sp9C = ({
        register s32 state_zero_r0 asm("r0") = 0;
        asm volatile("" : "+r"(state_zero_r0));
        state_zero_r0;
    });
    sp94 = ({
        register void *selection_zero_r1 asm("r1") = NULL;
        asm volatile("" : "+r"(selection_zero_r1));
        selection_zero_r1;
    });
block_62:
    asm volatile(".L_B2108_block62:");
    var_r7 = 0x2005;
    goto block_147;
block_63:
    {
        register s32 gfx_a asm("r0");
        register s32 gfx_b asm("r1");
        register s32 gfx_zero asm("r2");

        asm volatile(
            "mov r0, #16\n\t"
            "str r0, [sp, #0]\n\t"
            "mov %0, #0\n\t"
            "str %0, [sp, #4]\n\t"
            "str %0, [sp, #8]\n\t"
            "mov r3, #8\n\t"
            "str r3, [sp, #12]\n\t"
            "str %0, [sp, #16]"
            : "=r"(gfx_zero) : : "r0", "r3", "memory");
        gfx_a = 0x08359850;
        gfx_b = 0x0835985C;
        asm volatile("" : "+r"(gfx_a), "+r"(gfx_b));
        sp88 = func_08094484_4(gfx_a, gfx_b, gfx_zero, 0x9C);
    }
    asm volatile(
        "mov r0, #152\n\t"
        "str r0, [sp, #0]\n\t"
        "mov r0, #212\n\t"
        "lsl r0, r0, #2\n\t"
        "str r0, [sp, #4]\n\t"
        "mov r0, #15\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r0, #8\n\t"
        "str r0, [sp, #12]\n\t"
        "mov r1, #0\n\t"
        "str r1, [sp, #16]"
        : : : "r0", "r1", "memory");
    sp8C = func_08094484_4(0x08105AFC, 0x08105B08, 0, 0xC8);
    asm volatile(".if 0");
    func_08094484(0, 0, 0, 0, 0, 0, 0, 0, 0);
    asm volatile(".endif");
    var_r7 = 0x2010;
    goto block_147;
block_65:
    asm volatile("B2108_PATCH_BLOCK65_INDEX");
    temp_r0_3 = D_02032273[(u32)sp94] << 6;
    {
        register s32 call_r0 asm("r0");
        register s32 call_r1 asm("r1");
        register s32 call_r2 asm("r2");
        register s32 call_r3 asm("r3");

        call_r0 = (s32)D_02027378 + temp_r0_3;
        var_sl = (void *)call_r0;
        asm volatile(
            "ldrb %0, [%0, #0]\n\t"
            "mov %1, #0\n\t"
            "str %1, [sp, #0]"
            : "+r"(call_r0), "=r"(call_r3) : "r"(var_sl) : "memory");
        call_r1 = 0x02002880;
        asm volatile("" : "+r"(call_r1));
        asm volatile("str %0, [sp, #4]" : "+r"(call_r1) : : "memory");
        call_r1 = 0;
        asm volatile("" : "+r"(call_r1));
        call_r2 = 0;
        asm volatile("" : "+r"(call_r2));
        asm volatile("bl func_0809A9C8"
            : "+r"(call_r0), "+r"(call_r1), "+r"(call_r2), "+r"(call_r3)
            : : "lr", "cc", "memory");
    }
    func_0809844C((s16) M2C_FIELD(var_sl, u8 *, 0x30), 2, 0, 0xA, 7, 0xB, 8);
    {
        register u32 second_bound_r0 asm("r0");
        register u32 second_result_r6 asm("r6");

        {
            register u8 *lookup_owner_r2 asm("r2") = var_sl;
            s32 lookup_address;
            register s32 lookup_base asm("r3");
            register s32 *lookup_table_r1 asm("r1");
            u32 table_offset;

            asm volatile("" : "+r"(lookup_owner_r2));
            lookup_address = lookup_owner_r2[1] * 0x70;
            lookup_base = (s32)D_020218E4;
            asm volatile("" : "+r"(lookup_base));
            lookup_address += lookup_base;
            table_offset = *(u8 *)(lookup_address + 4) * 4;
            lookup_table_r1 = D_087EDD54_reload;
            asm volatile("" : "+r"(lookup_table_r1));
            table_offset += (u32)lookup_table_r1;
            second_bound_r0 = func_08098B58_raw(*(s32 *)table_offset);
        }
        asm volatile(
            "lsl %0, %0, #24\n\t"
            "lsr %1, %0, #24"
            : "+r"(second_bound_r0), "=r"(second_result_r6));
        var_r4_2 = 0;
        second_bound_r0 = 0xD;
        asm volatile("sub %0, %0, %1"
            : "+r"(second_bound_r0) : "r"(second_result_r6) : "cc");
        if ((u32) var_r4_2 >= second_bound_r0) {
            goto block_68;
        }
        temp_r5 = second_bound_r0;
        asm volatile("" : "+r"(temp_r5));
        temp_r6 = 0xC;
        asm volatile("" : "+r"(temp_r6));
loop_67:
        {
            register s32 call_r3 asm("r3") = (s16)var_r4_2;

            asm volatile("" : "+r"(call_r3));
            asm volatile("str %0, [sp, #0]"
                : : "r"(temp_r6), "r"(call_r3) : "memory");
            func_080981F0_4(0x081061C4, 0, 7, call_r3);
        }
        var_r4_2 += 1;
        if ((u32) var_r4_2 < temp_r5) {
            goto loop_67;
        }
    }
block_68:
    {
        register u8 *lookup_owner_r2 asm("r2") = var_sl;
        register u8 *lookup_base_r3 asm("r3");
        register s32 *lookup_table_r1 asm("r1");
        u32 lookup_address;
        u32 table_offset;

        asm volatile("" : "+r"(lookup_owner_r2));
        lookup_address = lookup_owner_r2[1] * 0x70;
        lookup_base_r3 = D_020218E4;
        asm volatile("" : "+r"(lookup_base_r3));
        lookup_address += (u32)lookup_base_r3;
        table_offset = *(u8 *)(lookup_address + 4) * 4;
        lookup_table_r1 = D_087EDD54_reload;
        asm volatile("" : "+r"(lookup_table_r1));
        table_offset += (u32)lookup_table_r1;
        func_080981F0(*(s32 *)table_offset, 0, 7, var_r4_2, 0xC);
    }
    func_080ACCC4(7, sp9C);
    func_08098BB4(0x08002318);
    sp94 = (void *) *(u8 *)0x0200A880;
    sp9C = (s32) *(u8 *)0x0200A881;
    temp_r0_5 = *(u8 *)0x0200A882;
    if (temp_r0_5 == 1) {
        goto block_71;
    }
    if (temp_r0_5 == 2) {
        goto block_80;
    }
    goto block_147;
block_71:
    {
        register u16 *owner_r2 asm("r2") = var_sl;
        register u32 mask_r3 asm("r3");
        register u32 mask_r0 asm("r0");

        asm volatile("" : "+r"(owner_r2));
        temp_r1_2 = owner_r2[1];
        mask_r3 = 0xFFFE;
        asm volatile("" : "+r"(mask_r3));
        mask_r0 = mask_r3;
        asm volatile("" : "+r"(mask_r0));
        temp_r1_2 &= mask_r0;
        zero_r4 = 0;
        owner_r2[1] = temp_r1_2;
    }
    if (({
        register u8 *selected_table_r0 asm("r0") = D_02032273;
        register u32 selected_index_r2 asm("r2") = (u32)sp94;

        asm volatile("" : "+r"(selected_table_r0));
        asm volatile("" : "+r"(selected_index_r2));
        asm volatile("add %0, %1, %0"
            : "+r"(selected_table_r0) : "r"(selected_index_r2));
        asm volatile("ldrb %0, [%0, #0]"
            : "+r"(selected_table_r0) : : "memory");
        (u32)selected_table_r0;
    }) == ({
        register u8 *compare_owner_r3 asm("r3") = var_r9;
        asm volatile("" : "+r"(compare_owner_r3));
        compare_owner_r3[2];
    })) {
        goto block_77;
    }
    if (2 & temp_r1_2) {
        goto block_75;
    }
    {
        register s32 state_2020_r7 asm("r7") = 0x2020;

        asm volatile("" : "+r"(state_2020_r7));
        asm volatile(
            "b .L_B2108_block147\n\t"
            ".short 0\n\t"
            "B2108_DROP_NEXT_BRANCH"
            : : "r"(state_2020_r7));
    }
    goto block_147;
block_75:
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(zero_r4) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x18D8;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x2060;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    var_r0 = 0x08002345;
    goto block_78;
block_77:
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(zero_r4) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x28C8;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x1868;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    var_r0 = 0x08002768;
block_78:
    func_08098BB4(var_r0);
    func_0809534C();
    asm volatile(
        "b .L_B2108_block147\n\t"
        ".short 0\n\t"
        "B2108_DROP_NEXT_BRANCH");
    goto block_147;
block_80:
    func_08094554(sp88);
    func_08094554(sp8C);
    func_08098BB4(0x08002313);
    var_r7 = 0x1000;
    asm volatile("B2108_FORCE_SHORT_NEXT_BRANCH");
    goto block_147;
block_81:
    var_r0_2 = ({
        register u8 *state_owner_r2 asm("r2") = var_sl;

        asm volatile("" : "+r"(state_owner_r2));
        state_owner_r2[1];
    });
    var_r7 = 0x3000;
block_82:
    if (var_r0_2 != 0) {
        goto block_84;
    }
    goto block_147;
block_84:
    var_r7 = var_r1;
    goto block_147;
block_85:
    func_08098BB4(0x080024F3);
    func_080981F0(func_080E7B64(({
        asm volatile("B2108_PATCH_BLOCK85_ENTRY");
        M2C_FIELD(var_sl, u8 *, 0);
    })), 2, 9, 0, 0);
    asm volatile("B2108_BLOCK85_CALLS"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_080E7B64(M2C_FIELD(var_sl, u8 *, 0));
    {
        s32 lookup_address = M2C_FIELD(var_sl, u8 *, 1) * 0x70;
        s32 lookup_base = (s32)D_020218E4;
        u32 lookup_offset;
        register s32 *lookup_table asm("r2");

        asm volatile("" : "+r"(lookup_base));
        lookup_address += lookup_base;
        lookup_offset = *(u8 *)(lookup_address + 4) * 4;
        lookup_table = (s32 *)0x087EDD54;
        asm volatile("" : "+r"(lookup_table));
        lookup_offset += (u32)lookup_table;
        func_080981F0(*(s32 *)lookup_offset, 1, 9, 0, 2);
    }
    {
        s32 lookup_address = M2C_FIELD(var_sl, u8 *, 1) * 0x70;
        s32 lookup_base = (s32)D_020218E4;
        u32 lookup_offset;
        register s32 *lookup_table asm("r2");

        asm volatile("" : "+r"(lookup_base));
        lookup_address += lookup_base;
        lookup_offset = *(u8 *)(lookup_address + 4) * 4;
        lookup_table = (s32 *)0x087EDD54;
        asm volatile("" : "+r"(lookup_table));
        lookup_offset += (u32)lookup_table;
        func_08098B58(*(s32 *)lookup_offset);
    }
    asm volatile(".endif");
    zero_r3 = 0;
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");

        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : : "r"(zero_r3) : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x20D0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x850;
        asm volatile("" : "+r"(msg_r2));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(zero_r3)
            : : "lr", "cc", "memory");
    }
    func_08098BB4(0x0800254C);
    func_0809534C();
    temp_r0_5 = *(u8 *)0x0200A882;
    var_r7 = 0x2010;
    if (temp_r0_5 == 1) {
        goto block_87;
    }
    goto block_147;
block_87:
    if (*(u8 *)0x0200A880 == 0) {
        goto block_89;
    }
    goto block_147;
block_89:
    var_r7 = 0x3000;
    goto block_147;
block_90:
    func_08094554(sp88);
    func_08094554(sp8C);
    func_080ACBA0(7);
    asm volatile(
        "ldr r0, .L_B2108_pool102\n\t"
        "bl func_08098BB4"
        : : : "r0", "lr", "cc", "memory");
    func_080ED038(&sp14, var_r9, 0x70);
    func_080E5880(&sp14, NULL);
    asm volatile(
        "add r0, sp, #20\n\t"
        "mov r1, #58\n\t"
        "ldrsh r0, [r0, r1]\n\t"
        "mov r6, #8\n\t"
        "str r6, [sp, #0]\n\t"
        "mov r2, #4\n\t"
        "str r2, [sp, #4]\n\t"
        "mov r3, #1\n\t"
        "str r3, [sp, #8]\n\t"
        "mov r1, #4\n\t"
        "mov r2, #0\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x3A), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 1);
    asm volatile(".endif");
    asm volatile(
        "add r0, sp, #20\n\t"
        "mov r1, #62\n\t"
        "ldrsh r0, [r0, r1]\n\t"
        "str r6, [sp, #0]\n\t"
        "mov r2, #4\n\t"
        "str r2, [sp, #4]\n\t"
        "mov r3, #2\n\t"
        "str r3, [sp, #8]\n\t"
        "mov r1, #4\n\t"
        "mov r2, #0\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x3E), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 2);
    asm volatile(".endif");
    asm volatile("B2108_ALL_HOME_CALLS"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    asm volatile(".if 0");
    spA0 = (s16 *)((u8 *)&sp14 + 0x40);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x40), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 3);
    spA4 = (s16 *)((u8 *)&sp14 + 0x42);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x42), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 5);
    spA8 = (s16 *)((u8 *)&sp14 + 0x44);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x44), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 6);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0xA), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 7);
    spAC = (s16 *)((u8 *)&sp14 + 0x46);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x46), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 9);
    spB0 = (s16 *)((u8 *)&sp14 + 0x48);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x48), 4, 0, 0xA, 8, ARG6_FOUR_R2(), ARG7_TEN_R3());
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x3C), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 0xB);
    spB4 = (s16 *)((u8 *)&sp14 + 0x4A);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x4A), 4, 0, 0xA, 8, ARG6_FOUR_R2(), 0xD);
    func_0809844C(M2C_FIELD(var_sl, s16 *, 0x34), 3, 0, 0xA, 8, ARG6_TEN_R3(), 1);
    func_0809844C(M2C_FIELD(var_sl, s16 *, 0x36), 3, 0, 0xA, 8, 0xA, 6);
    func_0809844C(M2C_FIELD(var_sl, s16 *, 0x3C), 3, 0, 0xA, 8, 0xA, 0xB);
    func_0809844C(M2C_FIELD(var_sl, s16 *, 0x38), 3, 0, 0xA, 8, 0xA, EMIT_THIRTEEN_R1());
    asm volatile(".endif");
    var_r5_2 = M2C_FIELD(var_sl, u8 *, 0x30);
    if ((func_080E74F0(var_sl, 3, M2C_FIELD(&sp14, u8 *, 0)) << 0x10) == 0) {
        goto block_92;
    }
    var_r5_2 += 5;
block_92:
    if ((func_080E74F0(var_sl, 4, M2C_FIELD(&sp14, u8 *, 0)) << 0x10) == 0) {
        goto block_94;
    }
    var_r5_2 += 0xA;
block_94:
    if ((func_080E74F0(var_sl, 5, M2C_FIELD(&sp14, u8 *, 0)) << 0x10) == 0) {
        goto block_96;
    }
    var_r5_2 += 0x14;
block_96:
    if ((u32) var_r5_2 <= 0x63U) {
        goto block_98;
    }
    var_r5_2 = 0x63;
block_98:
    {
        register u32 saved_value_seed_r2 asm("r2") = 0x39;
        register u32 saved_value_r3 asm("r3");
        asm volatile("" : : "r"(saved_value_seed_r2));
        saved_value_seed_r2 += (u32)var_r9;
        saved_value_ptr = (u8 *)saved_value_seed_r2;
        var_r7_2 = 1;
        saved_value_r3 = *(u8 *)saved_value_seed_r2;
        asm volatile("" : : "r"(saved_value_r3));
        if ((u32) var_r5_2 < saved_value_r3) {
            goto block_100;
        }
    }
    var_r7_2 = 2;
block_100:
    func_0809844C((s16) var_r5_2, 2, var_r7_2, 0xA, 8, 0x10, 1);
    func_0809844C((s16) var_r5_2, 2, var_r7_2, 0xA, 8, 0x10, 6);
    func_0809844C((s16) var_r5_2, 2, var_r7_2, 0xA, 8, 0x10, 0xB);
    func_0809844C((s16) var_r5_2, 2, var_r7_2, 0xA, 8, 0x10, EMIT_THIRTEEN_R3());
    func_0809844C((s16) *({
        register u8 *value_ptr_r1 asm("r1") = saved_value_ptr;
        asm volatile("B2108_PATCH_ARG_ONE" : "+r"(value_ptr_r1));
        value_ptr_r1;
    }), 2, 0, 0xA, 8, 0x13, 1);
    func_0809844C((s16) *({
        register u8 *value_ptr_r3 asm("r3") = saved_value_ptr;
        asm volatile("" : "+r"(value_ptr_r3));
        value_ptr_r3;
    }), 2, 0, 0xA, 8, 0x13, 6);
    func_0809844C((s16) *({
        register u8 *value_ptr_r2 asm("r2") = saved_value_ptr;
        asm volatile("B2108_PATCH_ARG_ELEVEN" : "+r"(value_ptr_r2));
        value_ptr_r2;
    }), 2, 0, 0xA, 8, 0x13, 0xB);
    func_0809844C((s16) *({
        register u8 *value_ptr_r1 asm("r1") = saved_value_ptr;
        asm volatile("" : "+r"(value_ptr_r1));
        value_ptr_r1;
    }), 2, 0, 0xA, 8, 0x13, FRESH_THIRTEEN_R2());
    func_080ED038(&sp14, var_r9, 0x70);
    func_080E5880(&sp14, var_sl);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x3A), 4, 0, 0xA, 8, 0x18, 1);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x3E), 4, 0, 0xA, 8, 0x18, 2);
    func_0809844C(*spA0, 4, 0, 0xA, 8, 0x18, 3);
    func_0809844C(*spA4, 4, 0, 0xA, 8, 0x18, 5);
    func_0809844C(*spA8, 4, 0, 0xA, 8, 0x18, 6);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0xA), 4, 0, 0xA, 8, 0x18, 7);
    func_0809844C(*spAC, 4, 0, 0xA, 8, 0x18, 9);
    func_0809844C(*spB0, 4, 0, 0xA, 8, 0x18, 0xA);
    func_0809844C(M2C_FIELD(&sp14, s16 *, 0x3C), 4, 0, 0xA, 8, 0x18, 0xB);
    func_0809844C(*spB4, 4, 0, 0xA, 8, 0x18, FRESH_THIRTEEN_R1());
    asm volatile(
        "bl func_080972C8\n\t"
        "ldr r0, .L_B2108_pool102 + 4\n\t"
        "bl func_08098BB4\n\t"
        "mov r0, #7\n\t"
        "mov r1, #1\n\t"
        "mov r2, #1\n\t"
        "bl func_080ACA8C\n\t"
        "ldr r0, .L_B2108_pool102 + 8\n\t"
        "ldrb r0, [r0, #0]\n\t"
        "cmp r0, #1\n\t"
        "beq 1f\n\t"
        "b .L_B2108_block62\n"
        "1:\n\t"
        "ldr r0, .L_B2108_pool102 + 12\n\t"
        "ldrb r0, [r0, #0]\n\t"
        "b 2f\n\t"
        ".short 0\n\t"
        ".align 2, 0\n"
        ".L_B2108_pool102:\n\t"
        ".word 0x080023CC\n\t"
        ".word 0x080024C5\n\t"
        ".word 0x0200A882\n\t"
        ".word 0x0200A880\n"
        "2:\n\t"
        "cmp r0, #0\n\t"
        "beq 3f\n\t"
        "b .L_B2108_block62\n"
        "3:\n\t"
        "ldr r0, .L_B2108_pool106\n\t"
        "bl func_08098BB4\n\t"
        "mov r7, #128\n\t"
        "lsl r7, r7, #7\n\t"
        "b .L_B2108_block147\n\t"
        ".short 0\n\t"
        ".align 2, 0\n"
        ".L_B2108_pool106:\n\t"
        ".word 0x08002313"
        : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
block_108:
    func_080E6FA0(({
        register u8 *first_table_r0 asm("r0") = D_02032273;
        register u32 first_index_r2 asm("r2");

        asm volatile("" : "+r"(first_table_r0));
        asm volatile("ldr %0, [sp, #148]" : "=r"(first_index_r2)
            : : "memory");
        asm volatile("add %0, %1, %0"
            : "+r"(first_table_r0) : "r"(first_index_r2));
        *first_table_r0;
    }), ({
        register u8 *second_table_r1 asm("r1") = D_020321A4;
        register u32 second_index_r3 asm("r3");

        asm volatile("" : "+r"(second_table_r1));
        asm volatile("ldr %0, [sp, #144]" : "=r"(second_index_r3)
            : : "memory");
        asm volatile("add %0, %1, %0"
            : "+r"(second_table_r1) : "r"(second_index_r3));
        *second_table_r1;
    }));
    var_r7 = 0x1000;
    goto block_147;
block_110:
    var_r4_scan = 1;
    roster_base = D_02027378;
    first_scan_base = roster_base;
    asm volatile("" : "+r"(first_scan_base));
    unit_base = roster_base - 0x5A94;
    var_r2 = roster_base + 0x40;
loop_111:
    var_sl = first_scan_base + (var_r4_scan << 6);
    if (M2C_FIELD(var_r2, u8 *, 0) == 0) {
        goto block_114;
    }
    {
        register u32 unit_index_r0 asm("r0");
        register u32 unit_index_r1 asm("r1");

        unit_index_r0 = M2C_FIELD(var_r2, u8 *, 1);
        if (unit_index_r0 == 0) {
            goto block_114;
        }
        unit_index_r1 = unit_index_r0;
        asm volatile("" : "+r"(unit_index_r1));
        if (!(8 & *(u16 *)(unit_base + (unit_index_r1 * 0x70) + 8))) {
            goto block_115;
        }
    }
block_114:
    var_r2 += 0x40;
    var_r4_scan += 1;
    if (var_r4_scan <= 0x34U) {
        goto loop_111;
    }
block_115:
    if (var_r4_scan != 0x35) {
        goto block_117;
    }
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        msg_r1 = 0;
        asm volatile("" : "+r"(msg_r1));
        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : "+r"(msg_r1) : : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x20D0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x2858;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    var_r0_3 = 0x08002551;
    goto block_124;
block_117:
    var_r4_scan = 1;
    {
        register u8 *initial_unit_r2 asm("r2") = (u8 *)0x40;
        asm volatile("" : : "r"(initial_unit_r2));
        initial_unit_r2 += (u32)roster_base;
        var_sl = initial_unit_r2;
        if (M2C_FIELD(initial_unit_r2, u8 *, 0) != 1) {
            goto loop_119;
        }
        if (M2C_FIELD(initial_unit_r2, u8 *, 1) != 0) {
            goto block_122;
        }
    }
loop_119:
    var_r4_scan += 1;
    if (var_r4_scan > 0x34U) {
        goto block_122;
    }
    temp_r0_7 = var_r4_scan << 6;
    var_sl = roster_base + temp_r0_7;
    if (M2C_FIELD(var_sl, u8 *, 0) != 1) {
        goto loop_119;
    }
    if (M2C_FIELD(var_sl, u8 *, 1) == 0) {
        goto loop_119;
    }
block_122:
    if (var_r4_scan != 0x35) {
        goto block_126;
    }
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        msg_r2 = 0;
        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : "+r"(msg_r2) : : "r0", "memory");
        msg_r0 = 1;
        asm volatile("" : "+r"(msg_r0));
        msg_r1 = 0x20D0;
        asm volatile("" : "+r"(msg_r1));
        msg_r2 = 0x2858;
        asm volatile("" : "+r"(msg_r2));
        msg_r3 = 0;
        asm volatile("" : "+r"(msg_r3));
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    func_08098BB4(0x080025B7);
    func_08098248(func_080E7B64(1U), 1, 9);
    var_r0_3 = 0x080025C9;
block_124:
    func_08098BB4(var_r0_3);
    func_0809534C();
    goto block_39;
block_126:
    var_r4_scan = 0;
    {
    register u8 *first_entity_base_r0 asm("r0");
    register u8 *first_map_base_r3 asm("r3");
    register u8 *first_record_base_r2 asm("r2");
    register u32 first_map_offset_r1 asm("r1");
    register u32 first_entry_r0 asm("r0");
    register u8 *first_work_r1 asm("r1");

    first_entity_base_r0 = D_020218E4;
    asm volatile("" : "+r"(first_entity_base_r0));
    first_map_offset_r1 = 0x690C;
    asm volatile("" : "+r"(first_map_offset_r1));
    first_map_base_r3 = first_entity_base_r0 + first_map_offset_r1;
    first_record_base_r2 = first_entity_base_r0 + 4;
loop_127:
    first_work_r1 = (u8 *)((u32)var_r4_scan + (u32)first_map_base_r3);
    first_entry_r0 = *first_work_r1;
    if (first_entry_r0 == 0) {
        goto block_129;
    }
    first_work_r1 = (u8 *)((first_entry_r0 * 0x70) + (u32)first_record_base_r2);
    var_r9 = first_work_r1;
    if (M2C_FIELD(first_work_r1, u8 *, 2) == 0) {
        goto block_130;
    }
block_129:
    var_r4_scan += 1;
    if (var_r4_scan <= 5U) {
        goto loop_127;
    }
    }
block_130:
    asm volatile(
        "cmp %0, #5\n\t"
        "bhi .L_B2108_block145\n\t"
        ".if 0"
        : : "r"(var_r4_scan) : "cc");
    if (var_r4_scan > 5U) {
        goto block_145;
    }
    asm volatile(".endif");
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        msg_r2 = 0;
        asm volatile("" : "+r"(msg_r2));
        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov r0, #47\n\t"
            "str r0, [sp, #8]\n\t"
            "mov r0, #63\n\t"
            "str r0, [sp, #12]"
            : "+r"(msg_r2) : : "r0", "memory");
        msg_r0 = 1;
        msg_r1 = 0x28C8;
        msg_r2 = 0x850;
        msg_r3 = 0;
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    func_08098BB4(0x0800260E);
    func_0809534C();
    if (*(u8 *)0x0200A882 != 1) {
        goto block_39;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_39;
    }
    var_r4_scan = 0;
    {
    u8 *second_entity_base;
    u8 *second_record_base;
    register u32 second_map_offset_r3 asm("r3");
    register u32 second_entry_r0 asm("r0");
    register u8 *second_work_r1 asm("r1");

    second_entity_base = D_020218E4;
    second_record_base = second_entity_base + 4;
loop_134:
    second_map_offset_r3 = 0x690C;
    asm volatile("" : : "r"(second_map_offset_r3));
    second_entry_r0 = (u32)second_entity_base + second_map_offset_r3;
    second_work_r1 = (u8 *)((u32)var_r4_scan + second_entry_r0);
    second_entry_r0 = *second_work_r1;
    if (second_entry_r0 == 0) {
        goto block_137;
    }
    second_work_r1 = (u8 *)((second_entry_r0 * 0x70) + (u32)second_record_base);
    var_r9 = second_work_r1;
    if (M2C_FIELD(second_work_r1, u8 *, 2) != 0) {
        goto block_137;
    }
    func_080E6020((u8) var_r4_scan);
block_137:
    var_r4_scan += 1;
    if (var_r4_scan <= 5U) {
        goto loop_134;
    }
    }
    var_r4_scan = 0;
    entity_base = D_020218E4;
    map_offset = 0x690C;
    map_base = entity_base + map_offset;
    if (map_base[0] != 0) {
        goto block_141;
    }
loop_139:
    var_r4_scan += 1;
    if (var_r4_scan > 5U) {
        goto block_144;
    }
    if (*(u8 *)((u32)var_r4_scan + (u32)map_base) == 0) {
        goto loop_139;
    }
block_141:
    if (var_r4_scan > 5U) {
        goto block_144;
    }
    sp84 = 1;
    goto block_146;
block_144:
    func_080972C8();
    func_080ED17C(1);
    func_08092E84(0x58);
    {
        register s32 msg_r0 asm("r0");
        register s32 msg_r1 asm("r1");
        register s32 msg_r2 asm("r2");
        register s32 msg_r3 asm("r3");

        msg_r0 = 0;
        asm volatile(
            "str %0, [sp, #0]\n\t"
            "str %0, [sp, #4]\n\t"
            "mov %0, #47\n\t"
            "str %0, [sp, #8]\n\t"
            "mov %0, #63\n\t"
            "str %0, [sp, #12]"
            : "+r"(msg_r0) : : "memory");
        msg_r0 = 1;
        msg_r1 = 0x10E0;
        msg_r2 = 0x1868;
        msg_r3 = 0;
        asm volatile("bl func_0809538C"
            : "+r"(msg_r0), "+r"(msg_r1), "+r"(msg_r2), "+r"(msg_r3)
            : : "lr", "cc", "memory");
    }
    func_08098BB4(0x080026A8);
    func_0809534C();
    {
        register s32 final_state_r1 asm("r1") = 2;

        asm volatile("" : "+r"(final_state_r1));
        asm volatile(
            "str %0, [sp, #132]\n\t"
            "b .L_B2108_block146\n\t"
            "B2108_DROP_NEXT_BRANCH"
            : "+r"(final_state_r1) : : "memory");
    }
    goto block_146;
block_145:
    asm volatile(".L_B2108_block145:");
    sp84 = ({
        register s32 final_state_r2 asm("r2") = 1;

        asm volatile("" : "+r"(final_state_r2));
        final_state_r2;
    });
block_146:
    asm volatile(".L_B2108_block146:");
    func_08094554(sp88);
    func_08094554(sp8C);
    func_080ACBA0(7);
    func_08098BB4(0x080021F7);
block_147:
    asm volatile(".L_B2108_block147:");
    {
        register s32 final_state_r3 asm("r3") = sp84;

        asm volatile("" : "+r"(final_state_r3));
        if (final_state_r3 == 0) {
            goto loop_1;
        }
        return final_state_r3;
    }
}
