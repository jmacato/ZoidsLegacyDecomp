#include "m2c_prelude.h"

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E74(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08092EA0(s32);                         /* extern */
M2C_UNK func_08094174();                            /* extern */
void *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
void *func_08094484_4(M2C_UNK, M2C_UNK, s32, s32);   /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_0809538C(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096F3C();                            /* extern */
M2C_UNK func_08099F80();                            /* extern */
M2C_UNK func_08099FEC();                            /* extern */
M2C_UNK func_0809A00C();                            /* extern */
M2C_UNK func_0809A048();                            /* extern */
M2C_UNK func_0809B46C(s32);                         /* extern */
M2C_UNK func_0809B6DC(s32);                         /* extern */
s32 func_0809B8C4();                                /* extern */
M2C_UNK func_0809CC94(s32);                         /* extern */
M2C_UNK func_0809E204(u16, s32, s32, s32);          /* extern */
M2C_UNK func_0809FCB0();                            /* extern */
M2C_UNK func_0809FD3C(s32, M2C_UNK);                /* extern */
M2C_UNK func_080E6684();                            /* extern */
M2C_UNK func_080EB888();                            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;
extern volatile s16 D_03000052;
extern volatile u16 D_0300004C;
extern volatile s32 D_03000054[];
extern volatile s32 D_02021690;
extern volatile s8 D_020216F4;

struct StateHead {
    u16 mode;
    u16 pad;
    s32 value4;
    s32 value8;
};
extern struct StateHead D_0202ECF4;

void sub_0809BB74(void) {
    volatile s32 sp14;
    void *volatile sp18;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r1;
    s32 var_r7;
    u32 var_r4;
    u32 var_r4_2;
    u32 var_r4_3;
    u8 temp_r0;
    u8 temp_r0_2;
    s32 temp_r4_2;
    register s32 zero_r8 asm("r8");
    register volatile u16 *keys_r9 asm("r9");
    void *temp_r2;
    void *temp_r2_2;
    register void *temp_r6 asm("r6");
    void *var_sl;

    func_080E6684();
    if (*(u8 *)0x02021698 != 0) {
        goto block_3;
    }
    func_0809B6DC(0);
    D_0300004E = 0x3F40;
    D_03000050 = 0x10;
    func_080EB888();
    var_r7 = 0;
    goto block_4;
block_3:
    func_0809B6DC(1);
    func_08092E74(1);
    func_08096308(1, 0x10);
    var_r7 = 0x2000;
block_4:
    func_08092D8C(7, 0x0809BAB1);
    var_r1 = 0;
    if (*(u8 *)0x0202169C != 1) {
        goto block_8;
    }
    if (*(u8 *)0x0202169D != 1) {
        goto block_8;
    }
    if (*(u8 *)0x0202169E != 1) {
        goto block_8;
    }
    var_r1 = 1;
block_8:
    sp14 = var_r1;
    if (*(s32 *)0x02021690 == 1) {
        goto block_10;
    }
    goto loop_112;
block_10:
    {
        register s32 zero_birth_r3 asm("r3");
        register volatile u16 *keys_birth_r0 asm("r0");

        zero_birth_r3 = 0;
        asm volatile("" : "+r"(zero_birth_r3));
        zero_r8 = zero_birth_r3;
        keys_birth_r0 = (volatile u16 *)0x0300000E;
        keys_r9 = keys_birth_r0;
    }
loop_11:
    if (var_r7 != 0xF00) {
        goto block_13;
    }
    goto block_50;
block_13:
    if (var_r7 > 0xF00) {
        goto block_21;
    }
    if (var_r7 == 0x100) {
        goto block_33;
    }
    if (var_r7 > 0x100) {
        goto block_18;
    }
    if (var_r7 == 0) {
        goto block_32;
    }
    goto block_108;
block_18:
    if (var_r7 != 0x200) {
        goto block_20;
    }
    goto block_44;
block_20:
    goto block_108;
block_21:
    if (var_r7 != 0x1000) {
        goto block_23;
    }
    goto block_53;
block_23:
    if (var_r7 > 0x1000) {
        goto block_27;
    }
    if (var_r7 != 0xF10) {
        goto block_26;
    }
    goto block_51;
block_26:
    goto block_108;
block_27:
    if (var_r7 != 0x2000) {
        goto block_29;
    }
    goto block_63;
block_29:
    if (var_r7 != 0x2010) {
        goto block_31;
    }
    goto block_65;
block_31:
    goto block_108;
block_32:
    {
        register u8 stack_value_r2 asm("r2");
        register u8 *state_r0 asm("r0") = (u8 *)0x020216AC;

        asm volatile("mov r2, sp\n\tldrb %0, [r2, #20]"
            : "=r"(stack_value_r2) : "m"(sp14));
        *state_r0 = stack_value_r2;
    }
    var_r7 = 0x100;
    goto block_108;
block_33:
    {
        register s32 *out_args asm("sp");
        register s32 stack_r0 asm("r0");
        register s32 stack_zero_r3 asm("r3");

        stack_r0 = -0xD0;
        out_args[0] = stack_r0;
        stack_zero_r3 = zero_r8;
        out_args[1] = stack_zero_r3;
        out_args[2] = stack_zero_r3;
        stack_r0 = 0x80148;
        out_args[3] = stack_r0;
        out_args[4] = stack_zero_r3;
        var_sl = func_08094484_4(0x080F6608, 0x080F662C, 1, 0x78);
    }
    {
        register s32 callback_r0 asm("r0") = 2;

        func_08092D8C(callback_r0, 0x0809B4FD);
    }
    D_0300004C |= var_r7;
    D_0300004E = 0x3FC1;
    var_r4 = 0;
    {
    register volatile u16 *fade_initial_keys_r3 asm("r3") = keys_r9;

    if (!(0xB & *fade_initial_keys_r3)) {
        register u16 fade_zero_r6 asm("r6") = 0;
        register volatile s16 *fade_r5 asm("r5") = &D_03000052;
        do {
            M2C_FIELD(var_sl, u16 *, 6) = (u16) (M2C_FIELD(var_sl, u16 *, 6) + 1);
            if (var_r4 > 0x1FU) {
                goto block_37;
            }
            *fade_r5 = (s16) (0x10 - (var_r4 >> 1));
            goto block_38;
block_37:
            *fade_r5 = (s16) fade_zero_r6;
block_38:
            func_080ED17C(1);
            var_r4 += 1;
            if (var_r4 > 0x100U) {
                goto block_43;
            }
        } while (!({
            register volatile u16 *fade_loop_keys_r2 asm("r2") = keys_r9;
            0xB & *fade_loop_keys_r2;
        }));
    }
    }
    if (var_r4 > 0x100U) {
        goto block_43;
    }
    {
        register volatile u16 *zero_dst_r0 asm("r0") =
            (volatile u16 *)0x0300004E;

        asm volatile(
            "mov r3, %1\n\t"
            "strh r3, [%0]"
            :
            : "l"(zero_dst_r0), "h"(zero_r8)
            : "r3", "memory");
    }
    {
        register volatile s32 *camera_r1 asm("r1");
        register s32 camera_value_r0 asm("r0");

        camera_r1 = D_03000054;
        camera_value_r0 = 0x7000;
        camera_r1[1] = camera_value_r0;
    }
    func_08094554(var_sl);
    func_08094554(sp18);
    var_r7 = 0xF00;
    goto block_108;
block_43:
    var_r7 = 0x200;
    goto block_108;
block_44:
    func_08094554(var_sl);
    func_08094554(sp18);
    *(u16 *)0x0300004E = 0x3F90;
    {
        register s32 *out_args asm("sp");
        register s32 stack_r0 asm("r0");
        register s32 stack_zero_r3 asm("r3");

        stack_r0 = 0x30;
        out_args[0] = stack_r0;
        stack_zero_r3 = zero_r8;
        out_args[1] = stack_zero_r3;
        out_args[2] = stack_zero_r3;
        stack_r0 = 0x48;
        out_args[3] = stack_r0;
        out_args[4] = stack_zero_r3;
        sp18 = func_08094484_4(0x080F6608, 0x080F662C, 2, 0x78);
    }
    func_08092E84(0x56);
    var_r4_2 = 0;
    {
    register volatile u16 *fade2_initial_keys_r2 asm("r2") = keys_r9;

    if (!(0xB & *fade2_initial_keys_r2)) {
        register volatile s16 *fade2_r5 asm("r5") = &D_03000052;
        do {
            *fade2_r5 = 0x10 - (var_r4_2 >> 1);
            func_080ED17C(1);
            var_r4_2 += 1;
            if (var_r4_2 > 0x20U) {
                goto block_48;
            }
        } while (!({
            register volatile u16 *fade2_loop_keys_r3 asm("r3") = keys_r9;
            0xB & *fade2_loop_keys_r3;
        }));
    }
    }
block_48:
    {
        register volatile u16 *zero_dst_r0 asm("r0") =
            (volatile u16 *)0x0300004E;

        asm volatile(
            "mov r1, %1\n\t"
            "strh r1, [%0]"
            :
            : "l"(zero_dst_r0), "h"(zero_r8)
            : "r1", "memory");
    }
    var_r7 = 0xF10;
    goto block_108;
block_50:
    {
        register s32 *out_args asm("sp");
        register s32 stack_r0 asm("r0");
        register s32 stack_zero_r2 asm("r2");
        register s32 stack_48_r3 asm("r3");

        stack_r0 = 0x30;
        out_args[0] = stack_r0;
        stack_zero_r2 = zero_r8;
        out_args[1] = stack_zero_r2;
        out_args[2] = stack_zero_r2;
        stack_48_r3 = 0x48;
        out_args[3] = stack_48_r3;
        out_args[4] = stack_zero_r2;
        sp18 = func_08094484_4(0x080F6608, 0x080F662C, 2, 0x78);
    }
block_51:
    func_08092E0C(2);
    {
        register s32 *out_args asm("sp");
        register s32 stack_r0 asm("r0");
        register s32 stack_zero_r1 asm("r1");

        stack_r0 = 0x7C;
        out_args[0] = stack_r0;
        stack_r0 = 0x338;
        out_args[1] = stack_r0;
        stack_r0 = 0xC;
        out_args[2] = stack_r0;
        stack_r0 = 0x48;
        out_args[3] = stack_r0;
        stack_zero_r1 = zero_r8;
        asm volatile("" : "+r"(stack_zero_r1));
        out_args[4] = stack_zero_r1;
        *(void **)0x020216A0 = func_08094484_4(0x08102C68, 0x08102C74, 0, 0x78);
    }
    {
        register s32 *out_args asm("sp");
        register s32 stack_r0 asm("r0");
        register s32 stack_48_r2 asm("r2");

        stack_r0 = 0x98;
        out_args[0] = stack_r0;
        stack_r0 = 0x341;
        out_args[1] = stack_r0;
        stack_r0 = 0xD;
        out_args[2] = stack_r0;
        stack_48_r2 = 0x48;
        out_args[3] = stack_48_r2;
        asm volatile(
            "mov r3, %0\n\t"
            "str r3, [sp, #16]"
            :
            : "h"(zero_r8)
            : "r3", "memory");
        func_08094484_4(0x08102ED0, 0x08102EDC, 0, 0x78);
    }
    func_0809538C(1, 0xF0, 0x10, 1, 0xF0, 0x90A0, 0x3030, 0x31);
    var_r0 = 1;
    goto block_107;
block_53:
    var_r4_3 = 0;
loop_54:
    func_080ED17C(1);
    var_r4_3 += 1;
    if (var_r4_3 == 0x258) {
        goto block_56;
    }
    if (!(8 & *keys_r9)) {
        goto loop_54;
    }
block_56:
    if (var_r4_3 > 0x257U) {
        goto block_58;
    }
    func_08094554(*(void **)0x020216A0);
    func_08092E84(0x3D);
    var_r7 = 0x2000;
    goto block_108;
block_58:
    func_08096308(2, 0x10);
    goto loop_60;
block_59:
    func_080ED17C(1);
loop_60:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_59;
    }
    func_0809FCB0();
    {
        register s32 transition_r0 asm("r0") = 0;

        func_0809FD3C(transition_r0, 0x08091D5D);
    }
    {
        register s32 callback_r0 asm("r0") = 3;

        func_08092D8C(callback_r0, 0x080A67E5);
    }
    func_080ED17C(1);
    {
        register s32 callback_r0 asm("r0") = 8;

        func_08092D8C(callback_r0, 0x0809B51D);
    }
    goto block_108;
block_63:
    func_0809B46C(sp14);
    var_r7 = 0x2010;
    goto block_108;
block_65:
    func_08096F3C();
loop_66:
    func_080ED17C(1);
    if (!(0x40 & *(u16 *)0x03006034)) {
        goto block_69;
    }
    temp_r0 = *(u8 *)0x020216AC;
    if (temp_r0 == 0) {
        goto block_69;
    }
    *(u8 *)0x020216AC = (u8) (temp_r0 - 1);
    func_08092E84(0x40);
block_69:
    if (!(0x80 & *(u16 *)0x03006034)) {
        goto block_72;
    }
    temp_r0_2 = *(u8 *)0x020216AC;
    if ((u32) temp_r0_2 > 1U) {
        goto block_72;
    }
    *(u8 *)0x020216AC = (u8) (temp_r0_2 + 1);
    func_08092E84(0x40);
block_72:
    temp_r6 = (void *)0x020216A8;
    M2C_FIELD(*(void **)temp_r6, s16 *, 6) = (s16) ((*(u8 *)0x020216AC * 0x10) + 0x58);
    {
        register volatile u16 *menu_event_keys_r2 asm("r2") = keys_r9;

        if (!(3 & *menu_event_keys_r2)) {
            goto loop_66;
        }
    }
    func_08092E84(0x3E);
    {
        register volatile u16 *menu_confirm_keys_r3 asm("r3") = keys_r9;

        temp_r4 = 1 & *menu_confirm_keys_r3;
    }
    if (temp_r4 != 0) {
        goto block_75;
    }
    goto block_106;
block_75:
    temp_r4_2 = *(u8 *)0x020216AC;
    if (temp_r4_2 == 1) {
        goto block_92;
    }
    if ((s32) temp_r4_2 > 1) {
        goto block_79;
    }
    if (temp_r4_2 == 0) {
        goto block_82;
    }
    goto block_108;
block_79:
    if (temp_r4_2 != 2) {
        goto block_81;
    }
    goto block_103;
block_81:
    goto block_108;
block_82:
    func_08092E84(0x3E);
    func_08096308(2, 0x10);
    goto loop_84;
block_83:
    func_080ED17C(1);
loop_84:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_83;
    }
    if (*(u8 *)0x0202169C != 1) {
        goto block_90;
    }
    if (*(u8 *)0x0202169D != 1) {
        goto block_90;
    }
    if (*(u8 *)0x0202169E != 1) {
        goto block_90;
    }
    if ((func_0809B8C4() << 0x18) != 0) {
        goto block_90;
    }
    func_0809B6DC(1);
    var_r7 = 0x2000;
    var_r0_2 = 1;
    goto block_104;
block_90:
    func_08099F80();
    func_08099FEC();
    func_0809A00C();
    func_0809A048();
    func_08092E74(3);
    func_0809CC94(0);
    func_08092EA0(3);
    {
        register volatile s8 *zero_dst_r0 asm("r0") =
            (volatile s8 *)0x0203055C;

        asm volatile(
            "mov r1, %1\n\t"
            "strb r1, [%0]"
            :
            : "l"(zero_dst_r0), "h"(zero_r8)
            : "r1", "memory");
    }
    goto block_97;
block_92:
    {
        register s32 readiness_r2 asm("r2") = sp14;

        if (readiness_r2 == 0) {
            goto block_99;
        }
    }
    func_08092E84(0x3E);
    func_08096308(2, 0x10);
    goto loop_95;
block_94:
    func_080ED17C(1);
loop_95:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_94;
    }
    func_08094174();
    func_0809E204(D_0202ECF4.mode, D_0202ECF4.value4,
        D_0202ECF4.value8, 1);
    {
        register volatile s8 *zero_dst_r0 asm("r0") =
            (volatile s8 *)0x0203055C;

        asm volatile(
            "mov r3, %1\n\t"
            "strb r3, [%0]"
            :
            : "l"(zero_dst_r0), "h"(zero_r8)
            : "r3", "memory");
    }
block_97:
    *(s32 *)0x02021690 = 3;
    goto block_108;
block_99:
    func_08092E84(0x58);
    temp_r2 = *(void **)temp_r6;
    M2C_FIELD(temp_r2, s32 *, 0) = (s32) (M2C_FIELD(temp_r2, s32 *, 0) | 0x20000);
    {
        register s32 *out_args asm("sp");
        register s32 stack_r0 asm("r0");

        stack_r0 = 0x40;
        out_args[0] = stack_r0;
        stack_r0 = 0x37D;
        out_args[1] = stack_r0;
        stack_r0 = 0xE;
        out_args[2] = stack_r0;
        stack_r0 = 0x10;
        out_args[3] = stack_r0;
        stack_r0 = sp14;
        out_args[4] = stack_r0;
        temp_r6 = func_08094484_4(0x08103770, 0x08103794, 2, 0x38);
    }
    {
        register volatile u16 *wait_keys_r4 asm("r4") =
            (volatile u16 *)0x0300000E;
        register u32 wait_mask_r5 asm("r5") = 3;
        register u32 wait_value_r1 asm("r1");
        register u32 wait_test_r0 asm("r0");

        do {
            func_080ED17C(1);
            wait_value_r1 = *wait_keys_r4;
            wait_test_r0 = wait_mask_r5;
            asm volatile("" : "+r"(wait_test_r0));
            wait_test_r0 &= wait_value_r1;
        } while (wait_test_r0 == 0);
    }
    func_08092E84(0x41);
    temp_r2_2 = *(void **)0x020216A8;
    M2C_FIELD(temp_r2_2, s32 *, 0) = (s32) (M2C_FIELD(temp_r2_2, s32 *, 0) & 0xFFFDFFFF);
    func_08094554(temp_r6);
    goto block_108;
block_103:
    func_08092E84(0x3E);
    D_02021690 = (s32) temp_r4_2;
    {
        register volatile s8 *zero_dst_r0 asm("r0") = &D_020216F4;

        asm volatile(
            "mov r1, %1\n\t"
            "strb r1, [%0]"
            :
            : "l"(zero_dst_r0), "h"(zero_r8)
            : "r1", "memory");
    }
    var_r0_2 = 2;
block_104:
    func_08096308(var_r0_2, 0x10);
    goto block_108;
block_106:
    func_08094554(*(void **)0x020216A4);
    func_08094554(*(void **)temp_r6);
    {
        register s32 *out_args asm("sp");
        register s32 stack_r0 asm("r0");
        register s32 stack_48_r2 asm("r2");

        stack_r0 = 0x7C;
        out_args[0] = stack_r0;
        stack_r0 = 0x338;
        out_args[1] = stack_r0;
        stack_r0 = 0xC;
        out_args[2] = stack_r0;
        stack_48_r2 = 0x48;
        out_args[3] = stack_48_r2;
        out_args[4] = temp_r4;
        *(void **)0x020216A0 = func_08094484_4(0x08102C68,
            0x08102C74, 0, 0x78);
    }
    asm volatile(".if 0");
    func_08094484(0, 0, 0, 0, 0, 0, 0, 0, 0);
    asm volatile(".endif");
    var_r0 = 0x3F;
block_107:
    func_08092E84(var_r0);
    var_r7 = 0x1000;
block_108:
    if (*(s32 *)0x02021690 != 1) {
        goto block_110;
    }
    goto loop_11;
block_110:
    goto loop_112;
block_111:
    func_080ED17C(1);
loop_112:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_111;
    }
    func_08092E0C(7);
    return;
}
