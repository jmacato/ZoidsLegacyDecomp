#include "m2c_prelude.h"
#define NULL ((void *)0)

extern u8 D_020217F4[];
extern u8 D_0200A880;
extern u8 D_0200A882;

M2C_UNK func_08092E84(s32);                         /* extern */
s32 func_080940C0();                                /* extern */
s32 func_080940D4();                                /* extern */
M2C_UNK func_08094330();                            /* extern */
s32 func_08094484();                                /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
u8 *func_0809716C(s32);                             /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0();                            /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C();                             /* extern */
M2C_UNK func_080984C4();                             /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098834(s32);                         /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809AB44(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_0809AC98();                            /* extern */
s32 func_0809AE38();                                /* extern */
M2C_UNK func_0809AEA0();                            /* extern */
M2C_UNK func_0809AEC0(u8 *, s32, s32);              /* extern */
u8 func_0809AEF4();                                 /* extern */
M2C_UNK func_0809B00C(u8 *, s32, s32);              /* extern */
u8 func_0809B040();                                 /* extern */
M2C_UNK func_080AC6B8(s32);                         /* extern */
M2C_UNK func_080AC6FC(s32);                         /* extern */
M2C_UNK func_080AC87C(s32, s32);                    /* extern */
M2C_UNK func_080B65E4(s32);                         /* extern */
M2C_UNK func_080B6728();                            /* extern */
s32 func_080B684C(s32, s32);                        /* extern */
M2C_UNK func_080E5DC4(s32);                         /* extern */
M2C_UNK func_080E5E0C(s32, s32);                    /* extern */
M2C_UNK func_080E5E38(s32, s32);                    /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080E1F40(void) {
    u8 sp18;
    u8 sp19;
    u8 sp1A;
    u8 sp1B;
    u8 sp1C;
    u32 sp20;
    s32 sp24;
    s32 sp28;
    register s32 var_r6 asm("r6");
    s32 temp_r0_5;
    s32 temp_r0_7;
    s32 temp_r0_8;
    s32 temp_r0_9;
    register u32 temp_r1_2 asm("r1");
    register u8 *var_r7 asm("r7");
    u8 temp_r0;
    u8 temp_r0_2;
    s32 temp_r0_3;
    register u32 temp_r0_4 asm("r0");
    u8 temp_r0_6;
    u8 temp_r1;
    u8 temp_r1_3;
    u8 temp_r2;
    u8 temp_r3;
    register u32 temp_r4 asm("r4");
    register u32 temp_r4_10 asm("r4");
    register u32 temp_r4_11 asm("r4");
    register u32 temp_r4_12 asm("r4");
    register u32 temp_r4_13 asm("r4");
    register u32 temp_r4_14 asm("r4");
    register u32 temp_r4_15 asm("r4");
    register u32 temp_r4_2 asm("r4");
    u8 temp_r4_3;
    s32 temp_r4_4;
    register u32 temp_r4_5 asm("r4");
    register u32 temp_r4_6 asm("r4");
    register u32 temp_r4_7 asm("r4");
    register u32 temp_r4_8 asm("r4");
    register u32 temp_r4_9 asm("r4");
    u8 temp_r5;
    register u32 temp_r5_2 asm("r5");
    register u32 temp_r5_3 asm("r5");
    register u32 temp_r5_4 asm("r5");
    register u32 temp_r5_5 asm("r5");
    register u32 temp_r5_6 asm("r5");
    register u32 var_r4 asm("r4");

    *(s16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_080ECD34(0x081046A8, 0x06015840);
    func_0809AB44(2, 3, 0, 0, 1);
    func_08094330();
    func_08096308(0xF, 0x10);
    asm volatile("" : "=m"(sp20), "=m"(sp24), "=m"(sp28));
    {
        register s32 zero_r3 asm("r3") = 0;
        register s32 zero_r5 asm("r5");

        asm volatile("" : "+r"(zero_r3));
        sp28 = zero_r3;
        zero_r5 = 0;
        sp24 = zero_r5;
        sp18 = zero_r3;
    }
    var_r6 = 0;
    if (*(s32 *)0x02021690 != 0xE) {
        goto block_242;
    }
    asm volatile(
        "mov r2, #26\n\t"
        "add r2, sp\n\t"
        "mov sl, r2"
        :
        :
        : "r2", "r8", "r9", "r10");
loop_2:
    {
    register s32 state_4020 asm("r3") = 0x4020;

    if (var_r6 != state_4020) {
        goto block_4;
    }
    goto block_131;
block_4:
    if (var_r6 > state_4020) {
        goto block_33;
    }
    }
    if (var_r6 != 0x3000) {
        goto block_7;
    }
    goto block_83;
block_7:
    if (var_r6 > 0x3000) {
        goto block_20;
    }
    if (var_r6 != 0x10) {
        goto block_10;
    }
    goto block_73;
block_10:
    if (var_r6 > 0x10) {
        goto block_15;
    }
    if (var_r6 != 0) {
        goto block_13;
    }
    goto block_58;
block_13:
    goto block_241;
block_15:
    if (var_r6 != 0x1000) {
        goto block_17;
    }
    goto block_75;
block_17:
    if (var_r6 != 0x2000) {
        goto block_19;
    }
    goto block_78;
block_19:
    goto block_241;
block_20:
    if (var_r6 != 0x3110) {
        goto block_22;
    }
    goto block_101;
block_22:
    if (var_r6 > 0x3110) {
        goto block_28;
    }
    if (var_r6 != 0x3010) {
        goto block_25;
    }
    goto block_89;
block_25:
    if (var_r6 != 0x3100) {
        goto block_27;
    }
    goto block_99;
block_27:
    goto block_241;
block_28:
    if (var_r6 != 0x3200) {
        goto block_30;
    }
    goto block_120;
block_30:
    if (var_r6 != 0x4000) {
        goto block_32;
    }
    goto block_130;
block_32:
    goto block_241;
block_33:
    if (var_r6 != 0x4125) {
        goto block_35;
    }
    goto block_152;
block_35:
    if (var_r6 > 0x4125) {
        goto block_48;
    }
    if (var_r6 != 0x4100) {
        goto block_38;
    }
    goto block_146;
block_38:
    if (var_r6 > 0x4100) {
        goto block_43;
    }
    if (var_r6 != 0x4040) {
        goto block_41;
    }
    goto block_140;
block_41:
    goto block_241;
block_43:
    if (var_r6 != 0x4110) {
        goto block_45;
    }
    goto block_148;
block_45:
    if (var_r6 != 0x4120) {
        goto block_47;
    }
    goto block_150;
block_47:
    goto block_241;
block_48:
    if (var_r6 == 0x5000) {
        goto block_198;
    }
    if (var_r6 > 0x5000) {
        goto block_55;
    }
    if (var_r6 != 0x4130) {
        goto block_52;
    }
    goto block_169;
block_52:
    if (var_r6 != 0x4140) {
        goto block_54;
    }
    goto block_182;
block_54:
    goto block_241;
block_55:
    if (var_r6 == 0x5100) {
        goto block_213;
    }
    if (var_r6 == 0x5200) {
        goto block_224;
    }
    goto block_241;
block_58:
    asm volatile(
        "mov r0, #96\n\t"
        "str r0, [sp, #0]\n\t"
        "mov r0, #212\n\t"
        "lsl r0, r0, #2\n\t"
        "str r0, [sp, #4]\n\t"
        "mov r0, #15\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r0, #8\n\t"
        "str r0, [sp, #12]\n\t"
        "str r6, [sp, #16]"
        : : : "r0", "r1", "r2", "memory");
    var_r6 = func_08094484(0x08105AFC, 0x08105B08, 0, 0xA8);
    func_08098BB4(0x08028BF9);
    goto loop_61;
block_60:
    func_080ED17C(1);
loop_61:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_60;
    }
    func_0809AC98();
    goto loop_64;
block_63:
    func_080ED17C(1);
loop_64:
    if ((func_0809AE38() << 0x18) != 0) {
        goto block_67;
    }
    if (!(2 & *(u16 *)0x0300000E)) {
        goto block_63;
    }
    func_08092E84(0x3F);
    func_0809AEA0();
    func_08094554(var_r6);
    func_08098BB4(0x08028250);
    *(s32 *)0x02021690 = 2;
block_67:
    if (*(s32 *)0x02021690 != 0xE) {
        goto block_242;
    }
    func_0809AEC0(NULL, 0, 0x08109244);
    func_0809B00C(NULL, 0, 0x08109244);
loop_69:
    temp_r4 = func_0809AEF4();
    temp_r5 = func_0809B040();
    func_080ED17C(1);
    if (temp_r4 == 0) {
        goto loop_69;
    }
    if (temp_r5 == 0) {
        goto loop_69;
    }
    func_08098BB4(0x08028C58);
    func_08094554(var_r6);
block_72:
    var_r6 = 0x10;
    goto block_241;
block_73:
    {
        register u32 mode asm("r0") = *(u8 *)0x0300603C;

        var_r6 = 0x2000;
        if (mode == 0) {
            goto block_241;
        }
    }
    var_r6 = 0x1000;
    goto block_241;
block_75:
    func_08098BB4(0x08028C63);
    {
        register u8 *record asm("r1") = func_0809716C(1);

        asm volatile("" : "+r"(record));
        record[0x16] = sp18;
    }
    func_08098BB4(0x08028C99);
    func_08098BB4(0x08028C92);
    sp18 = D_0200A880;
    {
        register u8 *arg0 asm("r0") = &sp18;
        register s32 one asm("r1") = 1;

        func_0809AEC0(arg0, one, 0x08109250);
    }
loop_76:
    temp_r4_2 = func_0809AEF4();
    func_080ED17C(1);
    if (temp_r4_2 == 0) {
        goto loop_76;
    }
    func_08098BB4(0x08028C96);
    {
        register u32 zero asm("r5") = 0;

        asm volatile("" : "+r"(zero));
        sp19 = zero;
    }
    var_r6 = 0x3000;
    goto block_241;
block_78:
    func_08098BB4(0x08028CC1);
    {
        register u8 *arg0 asm("r0") = &sp18;
        register s32 one asm("r1") = 1;

        func_0809B00C(arg0, one, 0x08109250);
    }
loop_79:
    temp_r5_2 = func_0809B040();
    func_080ED17C(1);
    if (temp_r5_2 == 0) {
        goto loop_79;
    }
    {
        register u8 *choice asm("r0") = &sp18;
        register u32 value asm("r2") = *choice;

        if (value == 2) {
            goto block_82;
        }
        {
            register u32 toggle asm("r1") = 1;

            toggle ^= value;
            *choice = toggle;
        }
    }
block_82:
    sp19 = 0U;
    var_r6 = 0x3000;
    goto block_241;
block_83:
    temp_r4_3 = sp18;
    if (temp_r4_3 == 0) {
        goto block_86;
    }
    if (temp_r4_3 == 1) {
        goto block_87;
    }
    goto block_205;
block_86:
    func_08098BB4(0x08028D3A);
    asm volatile("str %0, [sp, #0]" : : "r"(temp_r4_3) : "memory");
    func_080981F0(0x0810925C, 0, 2, 1);
    asm volatile("");
    goto block_205;
block_87:
    func_08098BB4(0x08028D3A);
    {
        register s32 zero asm("r1");

        asm volatile(
            "mov %0, #0\n\t"
            "str %0, [sp, #0]"
            : "=r"(zero)
            :
            : "memory");
        func_080981F0(0x08109268, zero, 2, 1);
    }
    goto block_205;
block_89:
    temp_r4_4 = sp18;
    if (temp_r4_4 == 1) {
        goto block_96;
    }
    if ((s32) temp_r4_4 > 1) {
        goto block_93;
    }
    if (temp_r4_4 == 0) {
        goto block_95;
    }
    goto block_241;
block_93:
    if (temp_r4_4 == 2) {
        goto block_97;
    }
    goto block_241;
block_95:
    var_r6 = 0x3100;
    goto block_241;
block_96:
    var_r6 = 0x3200;
    goto block_241;
block_97:
    func_0809AEA0();
    func_08098BB4(0x08028CFC);
    *(s32 *)0x02021690 = (s32) temp_r4_4;
    goto block_241;
block_99:
    func_08098BB4(0x08028D70);
    func_08098BB4(0x08028D45);
    {
        register u8 *record asm("r1") = func_0809716C(3);

        asm volatile("" : "+r"(record));
        record[0x16] = sp19;
    }
    var_r6 = 0x3110;
    goto block_241;
block_101:
    func_08098BB4(0x08028D69);
    if (D_0200A882 != 1) {
        goto block_115;
    }
    sp19 = D_0200A880;
    temp_r1 = sp19;
    var_r7 = &sp19;
    if (temp_r1 == 0) {
        goto block_106;
    }
    if (temp_r1 == 1) {
        goto block_110;
    }
    goto block_114;
block_106:
    func_080B65E4(0);
    if (*(u8 *)0x02032411 == 0) {
        goto block_108;
    }
    var_r6 = 0x4000;
    goto block_114;
block_108:
    func_08098BB4(0x08028D88);
    goto block_241;
block_110:
    func_080B6728();
    if (*(u8 *)0x0203246B != 0) {
        goto block_113;
    }
    func_08098BB4(0x08028DB7);
    goto block_241;
block_113:
    var_r6 = 0x4100;
block_114:
    func_08098BB4(0x08028D42);
    func_08098BB4(0x08028D6D);
    func_080972C8();
    func_080ED17C(1);
    goto block_116;
block_115:
    sp19 = 3U;
    var_r6 = 0x10;
    func_08098BB4(0x08028D42);
    func_08098BB4(0x08028D6D);
    var_r7 = &sp19;
block_116:
    {
        register u8 *arg0 asm("r0") = var_r7;
        register s32 one asm("r1") = 1;

        func_0809AEC0(arg0, one, 0x08109278);
    }
loop_117:
    temp_r4_5 = func_0809AEF4();
    temp_r4_5 = (u8)temp_r4_5;
    func_080ED17C(1);
    if (temp_r4_5 == 0) {
        goto loop_117;
    }
    goto block_241;
block_120:
    func_08098BB4(0x08028CC1);
    {
        register u8 *arg0 asm("r0") = &sp19;
        register s32 one asm("r1") = 1;

        func_0809B00C(arg0, one, 0x08109278);
    }
    asm volatile(
        "mov %0, sp\n\t"
        "add %0, #25"
        : "=r"(var_r7));
loop_121:
    temp_r5_3 = func_0809B040();
    temp_r5_3 = (u8)temp_r5_3;
    func_080ED17C(1);
    if (temp_r5_3 == 0) {
        goto loop_121;
    }
    {
        register u32 selected asm("r0");

        asm volatile("ldrb %0, [r7]"
                     : "=r"(selected) : "r"(var_r7) : "memory");
        if (selected > 2U) {
            goto block_124;
        }
    }
    goto block_240;
block_124:
    func_08098BB4(0x08028D42);
    {
        register u32 pending asm("r2") = sp24;

        if (pending == 0) {
            goto block_126;
        }
    }
    func_08098BB4(0x08028FA6);
    {
        register u32 zero asm("r3") = 0;

        sp24 = zero;
    }
block_126:
    {
        register u32 pending asm("r5") = sp28;

        if (pending != 0) {
            goto block_128;
        }
    }
    goto block_72;
block_128:
    func_08098BB4(0x0802903F);
    sp28 = 0;
    goto block_72;
block_130:
    func_08098BB4(0x08028DE2);
    func_080AC6B8(1);
    var_r6 = 0x4020;
    goto block_241;
block_131:
    {
    register u8 *record_base asm("r4") = (u8 *)0x0203237A;
    register u32 record asm("r0");
    register u32 work_r1 asm("r1");

    asm volatile(
        "ldr r1, [sp, #32]\n\t"
        "add %0, r1, r4\n\t"
        "ldrb r1, [%0]\n\t"
        "lsl %0, r1, #1\n\t"
        "add %0, %0, r1\n\t"
        "lsl %0, %0, #2"
        : "=r"(record)
        : "r"(record_base)
        : "r1", "memory");
    work_r1 = 0x087B1E04;
    asm volatile(
        "add %0, %0, %1\n\t"
        "mov %1, #2"
        : "+r"(record), "+r"(work_r1));
    func_080AC87C(record, work_r1);
    func_08098BB4(0x08028ED9);
    {
        register u32 selected asm("r0") = D_0200A880;

        sp20 = selected;
    }
    temp_r0 = D_0200A882;
    if (temp_r0 == 1) {
        goto block_135;
    }
    if (temp_r0 == 2) {
        goto block_137;
    }
    goto block_241;
block_135:
    asm volatile(
        "ldr r2, [sp, #32]\n\t"
        "add r0, r2, r4\n\t"
        "ldrb r0, [r0]\n\t"
        "mov r3, sl\n\t"
        "strb r0, [r3]"
        :
        : "r"(record_base)
        : "r0", "r2", "r3", "memory");
    var_r6 = 0x4040;
    goto block_241;
block_137:
    {
        register u8 *arg0 asm("r0");
        register s32 one asm("r1");

        asm volatile(
            "mov r0, #0\n\t"
            "mov r5, sl\n\t"
            "strb r0, [r5]\n\t"
            "mov %0, sl\n\t"
            "mov %1, #1"
            : "=r"(arg0), "=r"(one)
            :
            : "r5", "memory");
        func_0809AEC0(arg0, one, 0x08109284);
    }
loop_138:
    temp_r4_6 = func_0809AEF4();
    temp_r4_6 = (u8)temp_r4_6;
    func_080ED17C(1);
    if (temp_r4_6 == 0) {
        goto loop_138;
    }
    goto block_196;
    }
block_140:
    {
    register u8 *unit_ptr_4040 asm("r8");
    {
        register u8 *arg0 asm("r0") = &sp1A;
        register s32 one asm("r1") = 1;

        func_0809AEC0(arg0, one, 0x08109284);
    }
    asm volatile(
        "mov r1, #26\n\t"
        "add r1, sp\n\t"
        "mov %0, r1"
        : "=r"(unit_ptr_4040) : : "r1");
loop_141:
    temp_r4_7 = func_0809AEF4();
    temp_r4_7 = (u8)temp_r4_7;
    func_080ED17C(1);
    if (temp_r4_7 == 0) {
        goto loop_141;
    }
    func_08098BB4(0x08028F9E);
    asm volatile(
        "mov r2, #0\n\t"
        "str r2, [sp, #0]"
        : : : "r2", "memory");
    func_080981F0(0x08109290, 0, 3, 0);
    {
        register s32 *record asm("r0") = (s32 *)0x087EDD54;
        register s32 zero_r5 asm("r5");

        asm volatile(
            "mov r3, r8\n\t"
            "ldrb r1, [r3]\n\t"
            "lsl r1, r1, #2\n\t"
            "add r1, r1, %0\n\t"
            "ldr %0, [r1]"
            : "+r"(record)
            : "r"(unit_ptr_4040)
            : "r1", "r3", "memory");
        asm volatile(
            "mov %1, #0\n\t"
            "str %1, [sp, #0]"
            : "+r"(record), "=r"(zero_r5) : : "memory");
        func_080981F0(record, 0, 3, 7);
    }
    func_08098248(0x081092B0, 0, 3);
    func_080972C8();
    {
        register volatile u16 *keys asm("r4") = (volatile u16 *)0x0300000E;
        register u32 mask asm("r5") = 3;
        register u32 key_word asm("r1");
        register u32 masked asm("r0");

loop_143:
        func_080ED17C(1);
        key_word = *keys;
        masked = mask;
        asm volatile("" : "+r"(masked));
        masked &= key_word;
        if (masked == 0) {
            goto loop_143;
        }
    }
    func_08092E84(0x41);
    func_08098BB4(0x08028FA6);
    var_r6 = 0x4020;
    goto block_241;
    }
block_146:
    func_08098BB4(0x08028EAB);
    sp20 = NULL;
    var_r6 = 0x4110;
    goto block_241;
block_148:
    func_080AC6FC(1);
    var_r6 = 0x4120;
    goto block_241;
block_150:
    func_08098BB4(0x08028E7F);
    var_r6 = 0x4125;
    goto block_241;
block_152:
    {
    register s32 *record_table asm("r1");
    register u8 *record_base asm("r4");
    register s32 record asm("r0");
    register u8 *choice_ptr asm("r7");

    func_080986B4(2);
    record_table = (s32 *)0x087EEFC8;
    record_base = (u8 *)0x02032412;
    asm volatile(
        "ldr r2, [sp, #32]\n\t"
        "add %0, r2, r4\n\t"
        "ldrb %0, [%0]\n\t"
        "lsl %0, %0, #2\n\t"
        "add %0, %0, r1\n\t"
        "ldr %0, [%0]"
        : "=r"(record)
        : "r"(record_table), "r"(record_base)
        : "r2", "memory");
    func_08098248(record, 0, 2);
    func_08098BB4(0x08028ED9);
    sp20 = D_0200A880;
    temp_r0_2 = D_0200A882;
    if (temp_r0_2 == 1) {
        goto block_155;
    }
    if (temp_r0_2 == 2) {
        goto block_165;
    }
    goto block_241;
block_155:
    {
        register u8 *arg0 asm("r0");
        register s32 one asm("r1");

        asm volatile(
            "ldr r3, [sp, #32]\n\t"
            "add r0, r3, r4\n\t"
            "ldrb r0, [r0]\n\t"
            "mov r5, sl\n\t"
            "strb r0, [r5]\n\t"
            "mov %0, sl\n\t"
            "mov %1, #1"
            : "=r"(arg0), "=r"(one)
            : "r"(record_base)
            : "r3", "r5", "memory");
        func_0809AEC0(arg0, one, 0x081092B8);
    }
    choice_ptr = &sp1B;
loop_156:
    temp_r4_8 = func_0809AEF4();
    temp_r4_8 = (u8)temp_r4_8;
    func_080ED17C(1);
    if (temp_r4_8 == 0) {
        goto loop_156;
    }
    {
        register u8 *arg0 asm("r0") = choice_ptr;
        register s32 one asm("r1") = 1;

        func_0809B00C(arg0, one, 0x081092C4);
    }
loop_158:
    temp_r5_4 = func_0809B040();
    temp_r5_4 = (u8)temp_r5_4;
    func_080ED17C(1);
    if (temp_r5_4 == 0) {
        goto loop_158;
    }
    asm volatile("ldrb %0, [r7]"
                 : "=r"(temp_r4_9) : "r"(choice_ptr) : "memory");
    if (temp_r4_9 != 0) {
        goto block_164;
    }
    func_08098BB4(0x08028F2E);
    sp1C = temp_r4_9;
    {
        register s32 one asm("r1") = 1;

        func_0809AEC0(&sp1C, one, 0x081092D0);
    }
loop_161:
    temp_r4_10 = func_0809AEF4();
    temp_r4_10 = (u8)temp_r4_10;
    func_080ED17C(1);
    if (temp_r4_10 == 0) {
        goto loop_161;
    }
    goto block_241;
block_164:
    var_r6 = 0x4130;
    goto block_241;
block_165:
    {
        register u8 *arg0 asm("r0");
        register s32 one asm("r1");

        asm volatile(
            "mov r1, #0\n\t"
            "mov %0, sl\n\t"
            "strb r1, [%0]\n\t"
            "mov %1, #1"
            : "=r"(arg0), "=r"(one)
            :
            : "memory");
        func_0809AEC0(arg0, one, 0x081092B8);
    }
loop_166:
    temp_r4_11 = func_0809AEF4();
    temp_r4_11 = (u8)temp_r4_11;
    func_080ED17C(1);
    if (temp_r4_11 == 0) {
        goto loop_166;
    }
    goto block_196;
    }
block_169:
    {
    register u8 *sp1b_seed asm("r1");
    register u8 *sp1c_seed asm("r2");
    register u8 *sp1b_ptr asm("r7");
    register u8 *sp1c_ptr asm("r9");
    register u8 *sp1c_low asm("r5");
    register u8 *lookup asm("r0");
    register u32 current asm("r0");
    register u32 limit asm("r3");
    register u32 masked asm("r0");

    func_08098BB4(0x08028EE5);
    {
        register s32 *table asm("r1") = (s32 *)0x087EEE60;
        register s32 child asm("r0");
        register s32 zero_r3 asm("r3");

        asm volatile(
            "mov r2, sl\n\t"
            "ldrb %0, [r2]\n\t"
            "lsl %0, %0, #2\n\t"
            "add %0, %0, r1\n\t"
            "ldr %0, [%0]"
            : "=r"(child)
            : "r"(table)
            : "r2", "memory");

        asm volatile(
            "mov %1, #0\n\t"
            "str %1, [sp, #0]"
            : "+r"(child), "=r"(zero_r3) : : "memory");
        func_080981F0(child, 0, 3, zero_r3);
    }
    sp1c_seed = &sp1C;
    *sp1c_seed = 1;
    var_r4 = 0;
    sp1b_seed = &sp1B;
    lookup = D_020217F4;
    asm volatile(
        "add %0, #10\n\t"
        "mov r5, sl\n\t"
        "ldrb r5, [r5]\n\t"
        "add %0, %0, r5\n\t"
        "ldrb %1, [%0]"
        : "+r"(lookup), "=r"(limit)
        :
        : "r5", "memory");
    current = *sp1b_seed;
    sp1b_ptr = sp1b_seed;
    sp1c_ptr = sp1c_seed;
    if (current <= limit) {
        goto block_171;
    }
    asm volatile("strb %0, [r7]" : : "r"(limit) : "memory");
block_171:
    sp1c_low = sp1c_ptr;
    var_r6 = 3;
loop_172:
    {
        register u32 first asm("r0");
        register u32 second asm("r1");

        asm volatile(
            "ldrb %0, [r5]\n\t"
            "ldrb %1, [r7]"
            : "=r"(first), "=r"(second)
            : "r"(sp1c_low), "r"(sp1b_ptr)
            : "memory");
        temp_r0_3 = func_080B684C(first, second);
    }
    *sp1c_low = temp_r0_3;
    asm volatile(
        "lsl %0, %0, #24\n\t"
        "lsr %0, %0, #24"
        : "+r"(temp_r0_3));
    if (temp_r0_3 == var_r4) {
        goto block_174;
    }
    {
        register u32 draw_arg asm("r0");
        register u32 zero_r2 asm("r2");

        asm volatile(
            "mov r1, r9\n\t"
            "ldrb %0, [r1]\n\t"
            "str r6, [sp, #0]\n\t"
            "mov r1, #11\n\t"
            "str r1, [sp, #4]\n\t"
            "mov %1, #0\n\t"
            "str %1, [sp, #8]"
            : "=r"(draw_arg), "=r"(zero_r2)
            : "r"(sp1c_ptr), "r"(var_r6)
            : "r1", "memory");
        func_0809844C(draw_arg, 2, zero_r2, 2);
    }
    func_080972C8();
    {
        register u8 *previous_ptr asm("r3") = sp1c_ptr;

        var_r4 = *previous_ptr;
    }
block_174:
    func_080ED17C(1);
    temp_r1_2 = *(u16 *)0x0300000E;
    masked = var_r6;
    asm volatile("" : "+r"(masked));
    masked &= temp_r1_2;
    if (masked == 0) {
        goto loop_172;
    }
    temp_r0_4 = 1;
    temp_r0_4 &= temp_r1_2;
    if (temp_r0_4 == 0) {
        goto block_178;
    }
    func_08092E84(0x3E);
    var_r6 = 0x4140;
    goto block_179;
block_178:
    {
        register u8 *cancel_ptr asm("r5") = sp1c_ptr;

        *cancel_ptr = temp_r0_4;
    }
    func_08092E84(0x3F);
    var_r6 = 0x4120;
block_179:
    func_08098BB4(0x08028F2A);
    {
        register u8 *arg0 asm("r0") = sp1c_ptr;
        register s32 arg1 asm("r1") = 1;

        func_0809AEC0(arg0, arg1, 0x081092D0);
    }
loop_180:
    temp_r4_12 = func_0809AEF4();
    temp_r4_12 = (u8)temp_r4_12;
    func_080ED17C(1);
    if (temp_r4_12 == 0) {
        goto loop_180;
    }
    goto block_241;
    }
block_182:
    {
    register u8 *unit_ptr_4140 asm("r5");
    register u8 *choice_ptr_4140 asm("r4");
    register u8 *saved_unit_4140 asm("r8");
    {
        register u32 unit asm("r0");
        register u32 choice asm("r1");

        unit_ptr_4140 = &sp1A;
        asm volatile("ldrb %0, [r5]"
                     : "=r"(unit) : "r"(unit_ptr_4140) : "memory");
        choice_ptr_4140 = &sp1C;
        asm volatile("ldrb %0, [r4]"
                     : "=r"(choice) : "r"(choice_ptr_4140) : "memory");
        func_080E5E38(unit, choice);
    }
    temp_r0_5 = func_080940D4();
    *(s8 *)0x0202169C = temp_r0_5;
    temp_r0_5 <<= 0x18;
    asm volatile("mov %0, r5"
                 : "=r"(saved_unit_4140) : "r"(unit_ptr_4140));
    if (temp_r0_5 == 0) {
        goto block_189;
    }
    func_08098BB4(0x08028F9E);
    asm volatile(
        "mov r0, #0\n\t"
        "str r0, [sp, #0]"
        : : : "r0", "memory");
    func_080981F0(0x081092DC, 0, 3, 0);
    func_080984C4(*choice_ptr_4140, 2, 0, 0, 3);
    func_08098248(0x081092EC, 0, 3);
    {
        register s32 *table asm("r1") = (s32 *)0x087EEE60;
        register s32 record asm("r0");

        asm volatile(
            "ldrb %0, [r5]\n\t"
            "lsl %0, %0, #2\n\t"
            "add %0, %0, r1\n\t"
            "ldr %0, [%0]"
            : "=r"(record)
            : "r"(table), "r"(unit_ptr_4140)
            : "memory");
        func_08098248(record, 0, 3);
    }
    if ((u32) *choice_ptr_4140 <= 1U) {
        goto block_185;
    }
    func_08098248(0x081092F0, 0, 3);
block_185:
    func_080972C8();
    {
        register volatile u16 *keys asm("r4") = (volatile u16 *)0x0300000E;
        register u32 mask asm("r5") = 3;
        register u32 key_word asm("r1");
        register u32 masked asm("r0");

loop_186:
        func_080ED17C(1);
        key_word = *keys;
        masked = mask;
        asm volatile("" : "+r"(masked));
        masked &= key_word;
        if (masked == 0) {
            goto loop_186;
        }
    }
    func_08092E84(0x41);
    func_08098BB4(0x08028FA6);
    goto block_192;
block_189:
    func_08092E84(0x58);
    func_08098BB4(0x08028FF6);
    {
        register volatile u16 *keys asm("r4") = (volatile u16 *)0x0300000E;
        register u32 mask asm("r5") = 3;
        register u32 key_word asm("r1");
        register u32 masked asm("r0");

loop_190:
        func_080ED17C(1);
        key_word = *keys;
        masked = mask;
        asm volatile("" : "+r"(masked));
        masked &= key_word;
        if (masked == 0) {
            goto loop_190;
        }
    }
    func_08098BB4(0x0802903F);
block_192:
    func_08098834(1);
    func_080B6728();
    temp_r4_13 = *(u8 *)0x0203246B;
    if (temp_r4_13 == 0) {
        goto block_194;
    }
    var_r6 = 0x4110;
    goto block_241;
block_194:
    func_08098BB4(0x08028DB7);
    {
        register u8 *arg0 asm("r0");
        register s32 one asm("r1");

        asm volatile(
            "mov r1, r8\n\t"
            "strb r4, [r1]\n\t"
            "mov %0, r8\n\t"
            "mov %1, #1"
            : "=r"(arg0), "=r"(one)
            : "r"(saved_unit_4140), "r"(temp_r4_13)
            : "memory");
        func_0809AEC0(arg0, one, 0x081092B8);
    }
loop_195:
    temp_r4_14 = func_0809AEF4();
    temp_r4_14 = (u8)temp_r4_14;
    func_080ED17C(1);
    if (temp_r4_14 == 0) {
        goto loop_195;
    }
block_196:
    func_08098BB4(0x08028EDD);
    var_r6 = 0x3000;
    goto block_241;
    }
block_198:
    {
    register u8 *selected_ptr asm("r8");

    temp_r1_3 = sp19;
    if (temp_r1_3 == 0) {
        goto block_201;
    }
    if (temp_r1_3 == 1) {
        goto block_202;
    }
    asm volatile(
        "mov r2, #26\n\t"
        "add r2, sp\n\t"
        "mov %0, r2"
        : "=r"(selected_ptr) : : "r2");
    goto loop_203;
block_201:
    {
        register u8 *arg0 asm("r0") = &sp1A;
        register s32 one asm("r1") = 1;

        func_0809B00C(arg0, one, 0x08109284);
    }
    asm volatile(
        "mov r3, #26\n\t"
        "add r3, sp\n\t"
        "mov %0, r3"
        : "=r"(selected_ptr) : : "r3");
    goto loop_203;
block_202:
    {
        register u8 *arg0 asm("r0") = &sp1A;
        register s32 one asm("r1") = 1;

        func_0809B00C(arg0, one, 0x081092B8);
    }
    asm volatile(
        "mov r5, #26\n\t"
        "add r5, sp\n\t"
        "mov %0, r5"
        : "=r"(selected_ptr) : : "r5");
loop_203:
    temp_r5_5 = func_0809B040();
    temp_r5_5 = (u8)temp_r5_5;
    func_080ED17C(1);
    if (temp_r5_5 == 0) {
        goto loop_203;
    }
    {
        register u8 *test_ptr asm("r1") = selected_ptr;
        register u32 selected asm("r0") = *test_ptr;

        if (selected != 0) {
            goto block_206;
        }
    }
block_205:
    var_r6 = 0x3010;
    goto block_241;
block_206:
    temp_r0_6 = sp19;
    if (temp_r0_6 == 0) {
        goto block_209;
    }
    if (temp_r0_6 == 1) {
        goto block_210;
    }
    goto block_211;
block_209:
    var_r6 = 0x5100;
    goto block_211;
block_210:
    {
        register u8 *arg0 asm("r0") = &sp1B;
        register u32 work_r1 asm("r1") = (u32)D_020217F4;

        asm volatile(
            "add %1, #10\n\t"
            "mov r2, r8\n\t"
            "ldrb r2, [r2]\n\t"
            "add %1, %1, r2\n\t"
            "ldrb r2, [%1]\n\t"
            "mov %1, #99\n\t"
            "sub %1, %1, r2\n\t"
            "strb %1, [%0]\n\t"
            "mov %1, #1"
            : "+r"(arg0), "+r"(work_r1)
            : "r"(selected_ptr)
            : "r2", "memory");
        func_0809AEC0(arg0, work_r1, 0x081092C4);
    }
    var_r6 = 0x5200;
block_211:
    func_080972C8();
    goto block_241;
    }
block_213:
    {
    register u8 *unit_ptr_5100 asm("r8");

    {
        register u32 pending asm("r3") = sp28;

        if (pending == 0) {
            goto block_215;
        }
    }
    func_08098BB4(0x0802903F);
    {
        register u32 zero asm("r5") = 0;

        sp28 = zero;
    }
block_215:
    {
        register u32 unit asm("r0");

        asm volatile(
            "mov r1, sl\n\t"
            "ldrb %0, [r1]"
            : "=r"(unit) : : "r1", "memory");
        func_080E5DC4(unit);
    }
    temp_r0_7 = func_080940D4();
    *(s8 *)0x0202169C = temp_r0_7;
    temp_r0_7 <<= 0x18;
    asm volatile(
        "mov r2, #26\n\t"
        "add r2, sp\n\t"
        "mov %0, r2"
        : "=r"(unit_ptr_5100) : : "r2");
    if (temp_r0_7 == 0) {
        goto block_222;
    }
    temp_r0_8 = func_080940C0();
    *(s8 *)0x0202169B = temp_r0_8;
    if ((temp_r0_8 << 0x18) == 0) {
        goto block_222;
    }
    {
        register u32 pending asm("r3") = sp24;

        if (pending != 0) {
            goto block_219;
        }
    }
    func_08098BB4(0x08028F9E);
    {
        register u32 one asm("r5") = 1;

        sp24 = one;
    }
    goto block_220;
block_219:
    func_080986B4(3);
block_220:
    asm volatile(
        "mov r0, #0\n\t"
        "str r0, [sp, #0]"
        : : : "r0", "memory");
    func_080981F0(0x081092F4, 0, 3, 0);
    {
        register s32 *record asm("r0") = (s32 *)0x087EDD54;
        register s32 zero_r3 asm("r3");

        asm volatile(
            "mov r2, r8\n\t"
            "ldrb r1, [r2]\n\t"
            "lsl r1, r1, #2\n\t"
            "add r1, r1, %0\n\t"
            "ldr %0, [r1]"
            : "+r"(record)
            : "r"(unit_ptr_5100)
            : "r1", "r2", "memory");
        asm volatile(
            "mov %1, #0\n\t"
            "str %1, [sp, #0]"
            : "+r"(record), "=r"(zero_r3) : : "memory");
        func_080981F0(record, 0, 3, 0xB);
    }
    func_08098248(0x081092B0, 0, 3);
block_221:
    func_080972C8();
    goto block_240;
block_222:
    func_08092E84(0x58);
    func_08098BB4(0x08028FA9);
    {
        register s32 one asm("r5") = 1;

        sp28 = one;
    }
    goto block_240;
    }
block_224:
    {
    register u8 *choice_ptr_5200 asm("r9");
    register u8 *unit_ptr_5200 asm("r8");

    asm volatile(
        "add r0, sp, #28\n\t"
        "mov %0, r0"
        : "=r"(choice_ptr_5200) : : "r0");
loop_225:
    temp_r4_15 = func_0809AEF4();
    temp_r4_15 = (u8)temp_r4_15;
    func_080ED17C(1);
    if (temp_r4_15 == 0) {
        goto loop_225;
    }
    {
        register u8 *arg0 asm("r0") = choice_ptr_5200;
        register s32 one asm("r1") = 1;

        func_0809B00C(arg0, one, 0x081092D0);
    }
loop_227:
    temp_r5_6 = func_0809B040();
    temp_r5_6 = (u8)temp_r5_6;
    func_080ED17C(1);
    if (temp_r5_6 == 0) {
        goto loop_227;
    }
    {
        register u8 *test_ptr asm("r1") = choice_ptr_5200;
        register u32 selected asm("r0") = *test_ptr;

        if (selected == 0) {
            goto block_240;
        }
    }
    {
        register u32 pending asm("r2") = sp28;

        if (pending == 0) {
            goto block_231;
        }
    }
    func_08098BB4(0x0802903F);
    {
        register u32 zero asm("r3") = 0;

        sp28 = zero;
    }
block_231:
    {
        register u32 first asm("r0");
        register u32 second asm("r1");

        asm volatile(
            "mov r5, sl\n\t"
            "ldrb %0, [r5]\n\t"
            "mov r2, r9\n\t"
            "ldrb %1, [r2]"
            : "=r"(first), "=r"(second)
            : "r"(choice_ptr_5200)
            : "r2", "r5", "memory");
        func_080E5E0C(first, second);
    }
    temp_r0_9 = func_080940D4();
    *(s8 *)0x0202169C = temp_r0_9;
    temp_r0_9 <<= 0x18;
    asm volatile(
        "mov r3, #26\n\t"
        "add r3, sp\n\t"
        "mov %0, r3"
        : "=r"(unit_ptr_5200) : : "r3");
    if (temp_r0_9 == 0) {
        goto block_239;
    }
    {
        register u32 pending asm("r5") = sp24;

        if (pending != 0) {
            goto block_234;
        }
    }
    func_08098BB4(0x08028F9E);
    sp24 = 1;
    goto block_235;
block_234:
    func_080986B4(3);
block_235:
    {
        register s32 zero_r1 asm("r1");

        asm volatile(
            "mov %0, #0\n\t"
            "str %0, [sp, #0]"
            : "=r"(zero_r1) : : "memory");
        func_080981F0(0x0810931C, zero_r1, 3, 0);
    }
    {
        register u32 arg0 asm("r0");

        asm volatile(
            "mov r2, r9\n\t"
            "ldrb %0, [r2]\n\t"
            "mov r1, #3\n\t"
            "str r1, [sp, #0]"
            : "=r"(arg0)
            : "r"(choice_ptr_5200)
            : "r1", "r2", "memory");
        func_080984C4(arg0, 2, 0, 0);
    }
    func_08098248(0x081092EC, 0, 3);
    {
        register s32 *table asm("r1") = (s32 *)0x087EEE60;
        register s32 record asm("r0");

        asm volatile(
            "mov r3, r8\n\t"
            "ldrb %0, [r3]\n\t"
            "lsl %0, %0, #2\n\t"
            "add %0, %0, r1\n\t"
            "ldr %0, [%0]"
            : "=r"(record)
            : "r"(table), "r"(unit_ptr_5200)
            : "r3", "memory");
        func_08098248(record, 0, 3);
    }
    {
        register u8 *choice_view asm("r5") = choice_ptr_5200;
        register u32 selected asm("r0") = *choice_view;

        if (selected > 1U) {
            goto block_237;
        }
    }
    goto block_221;
block_237:
    func_08098248(0x081092F0, 0, 3);
    goto block_221;
block_239:
    func_08092E84(0x58);
    func_08098BB4(0x08028FF6);
    sp28 = 1;
    }
block_240:
    var_r6 = 0x5000;
block_241:
    if (*(s32 *)0x02021690 == 0xE) {
        goto loop_2;
    }
block_242:
    func_08096308(0x10, 0);
    goto loop_245;
block_244:
    func_080ED17C(1);
loop_245:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_244;
    }
    return;
}
