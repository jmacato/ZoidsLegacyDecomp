#include "m2c_prelude.h"

s32 func_080BE65C(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
void func_080BE9D8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
void func_080C02B4(u8, u8);                            /* extern */
void func_080E77FC();                                  /* extern */
s16 func_080ECD98(s32, s32);                         /* extern */
void jtbl_080BEF5C();                                  /* static */
extern u8 D_02034B4C[];

#define DIRECT_SP_ARG() ((s8)({ \
    register s32 direct_sp asm("r3") = sp18; \
    asm volatile("" : "+r"(direct_sp)); \
    direct_sp; \
}))

#define CALL_SP_R0() ((s8)({ \
    register s32 call_sp asm("r0") = sp18; \
    asm volatile("" : "+r"(call_sp)); \
    call_sp; \
}))

#define DUAL_SP_VALUE() ({ \
    register s32 dual_sp asm("r2") = sp18; \
    register s32 dual_value asm("r4") = (s8)dual_sp; \
    asm volatile("" : "+r"(dual_sp), "+r"(dual_value)); \
    dual_value; \
})

#define CASE17_SP_VALUE() ({ \
    register s32 case_sp asm("r0") = sp18; \
    register s32 case_value asm("r4") = (s8)case_sp; \
    asm volatile("" : "+r"(case_sp), "+r"(case_value)); \
    case_value; \
})

#define DUAL_SP_R3_VALUE() ({ \
    register s32 dual_sp asm("r3") = sp18; \
    register s32 dual_value asm("r4") = (s8)dual_sp; \
    asm volatile("" : "+r"(dual_sp), "+r"(dual_value)); \
    dual_value; \
})

#define FORMAT_ARG(code) ({ \
    register s32 format_const asm("r1") = (code); \
    register s32 format_value asm("r0") = temp_r0; \
    asm volatile("" : "+r"(format_const), "+r"(format_value)); \
    format_value | format_const; \
})

#define FORMAT_JOIN_ARG(code) ({ \
    register s32 format_const asm("r1") = (code); \
    asm volatile("" : "+r"(format_const)); \
    temp_r0 | format_const; \
})

#define CMD_A_R1() ({ \
    register s32 field_value asm("r0"); \
    asm volatile("mov r1, #10\n\tldrsh r0, [r6, r1]" \
                 : "=r"(field_value) : "r"(cmd) : "r1", "cc"); \
    field_value; \
})

#define CMD_E_R2() ({ \
    register s32 field_value asm("r0"); \
    asm volatile("mov r2, #14\n\tldrsh r0, [r6, r2]" \
                 : "=r"(field_value) : "r"(cmd) : "r2", "cc"); \
    field_value; \
})

#define CMD_10_R1() ({ \
    register s32 field_value asm("r0"); \
    asm volatile("mov r1, #16\n\tldrsh r0, [r6, r1]" \
                 : "=r"(field_value) : "r"(cmd) : "r1", "cc"); \
    field_value; \
})



typedef struct Command {
    u8 pad00[2];
    u16 unk2;
    u32 unk4;
    u8 pad08[2];
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} Command;

typedef struct BattleRecord {
    u8 pad00[4];
    u16 unk4;
    u16 unk6;
    u16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    u8 pad12[0x18];
    u16 unk2A;
    u16 unk2C;
    u16 unk2E;
    u16 unk30;
    u16 unk32;
    u8 pad34[6];
    s16 unk3A;
    u8 pad3C[2];
    s16 unk3E;
    u8 pad40[0x61];
    u8 unkA1;
    u8 padA2[0xE];
    u8 unkB0;
    u8 padB1[0x27];
    u8 unkD8;
} BattleRecord;

void sub_080BEE04(Command *cmd, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    volatile s32 sp18;
    s32 temp_r0;
    s32 temp_r1_2;
    s32 temp_r1_3;
    s32 temp_r7;
    register s32 var_r1 asm("r1");
    register s32 second_arg4 asm("r0");
    register s32 second_zero asm("r5");
    u16 second_flags;
    s32 temp_r4_2;
    s32 var_r4;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r7_2;
    u32 temp_r0_2;
    u8 temp_r1;
    u8 temp_r2;
    u8 temp_r4;
    BattleRecord *temp_r5;

    temp_r1 = (u8)arg1;
    temp_r2 = (u8)arg2;
    sp18 = (u8)arg3;
    temp_r4 = (u8) arg4;
    temp_r0 = ((s32) ((0 - temp_r4) | temp_r4) >> 0x1F) & 0x1000;
    {
        register s32 row_value asm("r1") = temp_r1 * 0x1380;
        register s32 col_value asm("r0") = temp_r2 * 0x270;
        register u8 *record_base asm("r2");
        asm volatile("" : "+r"(row_value), "+r"(col_value));
        record_base = D_02034B4C;
        asm volatile("" : "+r"(record_base));
        col_value += (s32)record_base;
        temp_r5 = (BattleRecord *)(row_value + col_value);
    }
    temp_r7 = 1 & cmd->unk2;
    if (temp_r7 == 0) {
        if (cmd->unk4 & 0x400) {
            register s32 neg_one asm("r4") = -1;
            asm volatile("" : "+r"(neg_one));
            func_080BE65C(temp_r1, temp_r2, neg_one, 0U,
                         temp_r7, temp_r7, 9,
                         (s32)({
                             s16 result;
                             asm volatile("" ::: "memory");
                             result = func_080ECD98(0 - cmd->unkA, 0xA);
                             result;
                         }),
                         temp_r7, temp_r7);
        }
        if (cmd->unk4 & 0x800) {
            func_080BE65C(temp_r1, temp_r2, -1, 0x18U, temp_r7, temp_r7, 0x18, temp_r7, temp_r7, temp_r7);
        }
        temp_r1_2 = cmd->unk4;
        if (((temp_r1_2 & 0x1000) || ((temp_r1_2 & 0x4000) && !(0x40 & temp_r5->unk4))) && ((func_080BE65C(temp_r1, temp_r2, -1, 0x18U, temp_r7, temp_r7, 0x19, temp_r7, temp_r7, temp_r7) << 0x18) != 0)) {
            func_080C02B4(temp_r1, temp_r2);
        }
        if (!(cmd->unk4 & 0x2000)) {
            return;
        }
        func_080BE65C(temp_r1, temp_r2, -1, 0x18U, 0, 0, 0x1B, 0, 0, 0);
        return;
    }
    temp_r0_2 = (u8) cmd->unk4 - 1;
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(9), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 1:
        var_r4 = DUAL_SP_VALUE();
        func_080BE65C(temp_r1, temp_r2, var_r4, cmd->unk2, cmd->unk4, (second_zero = 0), FORMAT_ARG(9), CMD_A_R1(), CMD_E_R2(), CMD_10_R1());
        second_flags = cmd->unk2;
        second_arg4 = cmd->unk4;
        asm volatile("str %0, [sp]\n\tstr %1, [sp, #4]"
                     : : "r"(second_arg4), "r"(second_zero) : "memory");
        var_r1 = 0xA;
        goto block_50;
    case 2:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(7), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 3:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(8), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 4:
        var_r4 = DUAL_SP_VALUE();
        func_080BE65C(temp_r1, temp_r2, var_r4, cmd->unk2, cmd->unk4, (second_zero = 0), FORMAT_ARG(7), CMD_A_R1(), CMD_E_R2(), CMD_10_R1());
        second_flags = cmd->unk2;
        second_arg4 = cmd->unk4;
        asm volatile("str %0, [sp]\n\tstr %1, [sp, #4]"
                     : : "r"(second_arg4), "r"(second_zero) : "memory");
        var_r1 = 8;
        goto block_50;
    case 5:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(0xB), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 6:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(0x10), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 7:
        var_r4 = DUAL_SP_VALUE();
        func_080BE65C(temp_r1, temp_r2, var_r4, cmd->unk2, cmd->unk4, (second_zero = 0), FORMAT_ARG(0xB), CMD_A_R1(), CMD_E_R2(), CMD_10_R1());
        second_flags = cmd->unk2;
        second_arg4 = cmd->unk4;
        asm volatile("str %0, [sp]\n\tstr %1, [sp, #4]"
                     : : "r"(second_arg4), "r"(second_zero) : "memory");
        var_r1 = 0x10;
        goto block_50;
    case 8:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(0x10),
                     (s32)(s16)(0 - (u16)cmd->unkA),
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 9:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(6), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 10:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(0xE), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 11:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(0x11), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 12:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(2), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 13:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(5), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 14:
        var_r4 = DUAL_SP_VALUE();
        func_080BE65C(temp_r1, temp_r2, var_r4, cmd->unk2, cmd->unk4, (second_zero = 0), FORMAT_ARG(2), CMD_A_R1(), CMD_E_R2(), CMD_10_R1());
        second_flags = cmd->unk2;
        second_arg4 = cmd->unk4;
        asm volatile("str %0, [sp]\n\tstr %1, [sp, #4]"
                     : : "r"(second_arg4), "r"(second_zero) : "memory");
        var_r1 = 5;
        goto block_50;
    case 15: {
        register s32 case15_flag asm("r4");
        asm volatile("ldrh r1, [r6, #2]\n\t"
                     "mov r0, #2\n\t"
                     "and r0, r0, r1\n\t"
                     "lsl r0, r0, #16\n\t"
                     "lsr r4, r0, #16"
                     : "=r"(case15_flag) : "r"(cmd) : "r0", "r1", "cc");
        if (case15_flag == 0) {
            register u32 add_value asm("r0") = (u16)cmd->unkA;
            register u32 current_value asm("r3") = temp_r5->unk6;
            asm volatile("" : "+r"(add_value), "+r"(current_value));
            temp_r0_3 = add_value + current_value;
            temp_r5->unk6 = temp_r0_3;
            if ((s32) (s16) temp_r0_3 > (s32) (s16) temp_r5->unk3A) {
                temp_r5->unk6 = (u16) temp_r5->unk3A;
            }
            func_080BE9D8(temp_r1, temp_r2, CALL_SP_R0(), cmd->unk2,
                          cmd->unk4, case15_flag, FORMAT_JOIN_ARG(1),
                          (s32)cmd->unkA, (s32)cmd->unkE,
                          (s32)cmd->unk10);
        } else {
            func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                         cmd->unk4, 0, FORMAT_ARG(1), (s32)cmd->unkA,
                         (s32)cmd->unkE, (s32)cmd->unk10);
        }
        break;
    }
    case 16: {
        register s32 case16_flag asm("r4");
        asm volatile("ldrh r1, [r6, #2]\n\t"
                     "mov r0, #2\n\t"
                     "and r0, r0, r1\n\t"
                     "lsl r0, r0, #16\n\t"
                     "lsr r4, r0, #16"
                     : "=r"(case16_flag) : "r"(cmd) : "r0", "r1", "cc");
        if (case16_flag != 0) {
            goto case16_false;
        }
        {
            register u32 add_value asm("r0") = (u16)cmd->unkA;
            register u32 current_value asm("r2") = temp_r5->unk8;
            asm volatile("" : "+r"(add_value), "+r"(current_value));
            temp_r0_4 = add_value + current_value;
        }
        temp_r5->unk8 = temp_r0_4;
        if ((s32) (s16) temp_r0_4 > (s32) (s16) temp_r5->unk3E) {
            temp_r5->unk8 = (u16) temp_r5->unk3E;
        }
        func_080BE9D8(temp_r1, temp_r2, CALL_SP_R0(), cmd->unk2,
                      cmd->unk4, case16_flag, FORMAT_JOIN_ARG(4),
                      (s32)cmd->unkA, (s32)cmd->unkE,
                      (s32)cmd->unk10);
        break;
    }
case16_false:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, FORMAT_ARG(4), (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 17:
        temp_r7_2 = (u16)(2 & cmd->unk2);
        if (temp_r7_2 == 0) {
            {
                register u32 add_value asm("r0") = (u16)cmd->unkA;
                register u32 current_value asm("r2") = temp_r5->unk6;
                asm volatile("" : "+r"(add_value), "+r"(current_value));
                temp_r0_5 = add_value + current_value;
            }
            temp_r5->unk6 = temp_r0_5;
            if ((s32) (s16) temp_r0_5 > (s32) (s16) temp_r5->unk3A) {
                temp_r5->unk6 = (u16) temp_r5->unk3A;
            }
            temp_r0_6 = (u16)cmd->unkC + temp_r5->unk8;
            temp_r5->unk8 = temp_r0_6;
            if ((s32) (s16) temp_r0_6 > (s32) (s16) temp_r5->unk3E) {
                temp_r5->unk8 = (u16) temp_r5->unk3E;
            }
            temp_r4_2 = CASE17_SP_VALUE();
            func_080BE9D8(temp_r1, temp_r2, temp_r4_2, cmd->unk2, cmd->unk4, (s32) temp_r7_2, FORMAT_ARG(1), (s32) cmd->unkA, (s32) cmd->unkE, (s32) cmd->unk10);
            func_080BE9D8(temp_r1, temp_r2, temp_r4_2, cmd->unk2, cmd->unk4, (s32) temp_r7_2, FORMAT_ARG(4), (s32) (s16) cmd->unkC, (s32) cmd->unkE, (s32) cmd->unk10);
            goto block_after_50;
        } else {
            var_r4 = DUAL_SP_R3_VALUE();
            func_080BE65C(temp_r1, temp_r2, var_r4, cmd->unk2, cmd->unk4, (second_zero = 0), FORMAT_ARG(1), (s32) cmd->unkA, (s32) cmd->unkE, (s32) cmd->unk10);
            second_flags = cmd->unk2;
            second_arg4 = cmd->unk4;
            asm volatile("str %0, [sp]\n\tstr %1, [sp, #4]"
                         : : "r"(second_arg4), "r"(second_zero) : "memory");
            var_r1 = 4;
            goto block_50;
        }
        func_080BE65C(temp_r1, temp_r2, var_r4, second_flags,
                     second_arg4, second_zero, (s32)({
                         block_50:
                         temp_r0 | var_r1;
                     }),
                     (s32)(s16)cmd->unkC, (s32)cmd->unkE,
                     (s32)cmd->unk10);
        asm volatile("");
block_after_50:
        break;
    case 18:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, 0x14, (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 19:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, 0x15, (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 20:
        func_080BE65C(temp_r1, temp_r2, DIRECT_SP_ARG(), cmd->unk2,
                     cmd->unk4, 0, 0x1C, (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
        break;
    case 21: {
        register u8 *state_ptr asm("r2") = (u8 *)temp_r5 + 0xA1;
        asm volatile("" : "+r"(state_ptr));
        if (*state_ptr == 0) {
            register u32 state_value asm("r1") = 6;
            register u8 *setup_ptr asm("r0");
            register u8 *source_ptr asm("r2");
            asm volatile("" : "+r"(state_value));
            *state_ptr = (u8)state_value;
            setup_ptr = (u8 *)temp_r5 + 0xB0;
            source_ptr = (u8 *)0x087B77BC;
            asm volatile("" : "+r"(setup_ptr), "+r"(source_ptr));
            *setup_ptr = (u8)state_value;
            {
                register u32 source_byte asm("r3") = source_ptr[0];
                register u8 *byte_dest asm("r1") = (u8 *)temp_r5 + 0xD8;
                asm volatile("" : "+r"(source_byte), "+r"(byte_dest));
                *byte_dest = (u8)source_byte;
            }
            *(u16 *)(setup_ptr + 0x2A) = *(u16 *)(source_ptr + 2);
            *(u16 *)(setup_ptr + 0x2C) = *(u16 *)(source_ptr + 4);
            *(u16 *)(setup_ptr + 0x2E) = *(u16 *)(source_ptr + 6);
            *(u16 *)(setup_ptr + 0x30) = *(u16 *)(source_ptr + 8);
            *(u16 *)(setup_ptr + 0x32) = *(u16 *)(source_ptr + 10);
            func_080E77FC();
        }
        break;
    }
    }
    temp_r1_3 = cmd->unk4;
    if (0x1000 & temp_r1_3) {
        register s32 final_sp18 asm("r3") = sp18;
        asm volatile("" : "+r"(final_sp18));
        func_080BE65C(temp_r1, temp_r2, (s8)final_sp18, cmd->unk2,
                     temp_r1_3, 0, temp_r0 | 0x16, (s32)cmd->unkA,
                     (s32)cmd->unkE, (s32)cmd->unk10);
    }
}
