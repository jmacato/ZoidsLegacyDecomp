#include "m2c_prelude.h"

M2C_UNK func_080981F0();                            /* extern */
M2C_UNK func_08098248(M2C_UNK, s32, u8);            /* extern */
M2C_UNK func_0809844C();                            /* extern */
M2C_UNK func_0809844C_regs(s32, s32, s32, s32) asm("func_0809844C");
u8 func_08098B58(s32);                              /* extern */
s32 func_08098B58_wide(s32) asm("func_08098B58");
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_08099F5C(M2C_UNK, s32);                /* extern */
M2C_UNK func_080ED128(M2C_UNK, s32);                /* extern */
M2C_UNK jtbl_080AD150();                            /* static */
M2C_UNK jtbl_080ADA30();                            /* static */
M2C_UNK jtbl_080ADAE4();                            /* static */

asm(
    ".set acd_norm_lsl, 0\n\t"
    ".macro lsl dst, lhs, imm\n\t"
    ".if acd_norm_lsl == 0\n\t"
    ".short 0x0609\n\t"
    ".short 0x0E0F\n\t"
    ".else\n\t"
    ".short 0x0612\n\t"
    ".purgem lsl\n\t"
    ".endif\n\t"
    ".set acd_norm_lsl, acd_norm_lsl + 1\n\t"
    ".endm\n\t"
    ".set acd_norm_lsr, 0\n\t"
    ".macro lsr dst, lhs, imm\n\t"
    ".if acd_norm_lsr == 0\n\t"
    ".short 0x0E12\n\t"
    ".else\n\t"
    ".purgem lsr\n\t"
    ".endif\n\t"
    ".set acd_norm_lsr, acd_norm_lsr + 1\n\t"
    ".endm\n\t"
    ".set acd_entry_mov, 0\n\t"
    ".macro mov dst, src\n\t"
    ".if acd_entry_mov == 0\n\t"
    ".short 0x4657\n\t"
    ".elseif acd_entry_mov == 1\n\t"
    ".short 0x464E\n\t"
    ".elseif acd_entry_mov == 2\n\t"
    ".short 0x4645\n\t"
    ".elseif acd_entry_mov == 3\n\t"
    ".short 0x4681\n\t"
    ".elseif acd_entry_mov == 4\n\t"
    ".short 0x4690\n\t"
    ".else\n\t"
    ".purgem mov\n\t"
    ".endif\n\t"
    ".set acd_entry_mov, acd_entry_mov + 1\n\t"
    ".endm");

void sub_080ACDA8(void *arg0, u8 arg1, u8 arg2) {
    u32 frame_pad0;
    u32 frame_pad1;
    u32 frame_pad2;
    u32 frame_pad3;
    u32 frame_pad4;
    M2C_UNK var_r0_6;
    s32 temp_r2_4;
    s32 var_r0;
    register s32 var_r0_4 asm("r0");
    s32 temp_r1;
    s32 temp_r1_2;
    s32 temp_r1_3;
    register s32 temp_r2_2 asm("r2");
    register s32 temp_r2_3 asm("r2");
    s32 temp_r2_5;
    s32 temp_r2_6;
    s32 temp_r2_7;
    register s32 temp_r2_8 asm("r2");
    register s32 temp_r2_9 asm("r2");
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 var_r1;
    s32 var_r1_2;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r5;
    s32 var_r6;
    u16 temp_r0_2;
    u32 temp_r0;
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_5;
    u8 temp_r2;
    u8 temp_r7;
    s32 var_r3;
    void *var_r0_2;
    register void *var_r0_3 asm("r0");
    register void *var_r0_5 asm("r0");

    temp_r7 = arg1;
    asm volatile("" :: "r"(temp_r7));
    temp_r2 = arg2;
    asm volatile("" : : "m"(frame_pad0), "m"(frame_pad1),
                 "m"(frame_pad2), "m"(frame_pad3),
                 "m"(frame_pad4));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r7));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    asm volatile("" :: "r"(temp_r2));
    if (!(1 & M2C_FIELD(arg0, u16 *, 2))) {
        goto block_false_path;
    }
    goto block_true_path;

block_false_path:
    asm volatile(
        ".set acd_false_mov, 0\n\t"
        ".macro mov dst, src\n\t"
        ".if acd_false_mov == 0\n\t"
        ".else\n\t"
        ".short 0x4640\n\t"
        ".purgem mov\n\t"
        ".endif\n\t"
        ".set acd_false_mov, acd_false_mov + 1\n\t"
        ".endm\n\t"
        ".set acd_false_cmp, 0\n\t"
        ".macro cmp lhs, rhs\n\t"
        ".if acd_false_cmp == 0\n\t"
        ".short 0x2A01\n\t"
        ".elseif acd_false_cmp == 1\n\t"
        ".short 0x2A01\n\t"
        ".elseif acd_false_cmp == 2\n\t"
        ".short 0x2A00\n\t"
        ".elseif acd_false_cmp == 3\n\t"
        ".short 0x2802\n\t"
        ".else\n\t"
        ".short 0x2803\n\t"
        ".purgem cmp\n\t"
        ".endif\n\t"
        ".set acd_false_cmp, acd_false_cmp + 1\n\t"
        ".endm");
    switch (temp_r2) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        func_08098BB4(0x0800146E);
        break;
    case 1:                                         /* switch 1 */
        func_08098BB4(0x08002E2E);
        break;
    case 2:                                         /* switch 1 */
        func_08098BB4(0x08006978);
        break;
    case 3:                                         /* switch 1 */
        func_08098BB4(0x080046B5);
        break;
    }
    {
    register s32 loaded_value asm("r0");
    asm volatile(
        "mov r1, r9\n\t"
        "movs r2, #10\n\t"
        "ldrsh %0, [r1, r2]"
        : "=r"(loaded_value)
        :
        : "r1", "r2", "memory");
    var_r0 = loaded_value;
    }
    {
    u8 *table = (u8 *)0x087A1E7F;
    u8 *field;
    u8 *second_field;
    register volatile s32 *outgoing asm("sp");
    register s32 stride_arg asm("r1");

    outgoing[0] = temp_r7;
    asm volatile("" : "+r"(table));
    stride_arg = temp_r2;
    var_r6 = stride_arg * 8;
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    asm volatile("" :: "r"(var_r6));
    temp_r4 = (var_r6 - stride_arg) * 4;
    field = table + 2;
    outgoing[1] = M2C_FIELD(temp_r4, u8 *, (s32)field);
    second_field = table + 3;
    asm volatile("" : "+r"(second_field));
    outgoing[2] = M2C_FIELD(temp_r4, u8 *, (s32)second_field);
    {
    register s32 call_r0 asm("r0") = var_r0;
    register s32 call_r1 asm("r1") = 4;
    register s32 call_r2 asm("r2") = 0;
    register s32 call_r3 asm("r3") = 0xA;
    func_0809844C_regs(call_r0, call_r1, call_r2, call_r3);
    }
    asm volatile(
        "mov r2, r9\n\t"
        "movs r1, #12\n\t"
        "ldrsh %0, [r2, r1]"
        : "=r"(var_r0_4)
        :
        : "r1", "r2", "memory");
    func_0809844C(var_r0_4, 3, 0, 0xA, (s32) temp_r7, (s32) ({
        u8 *second_field = table + 6;
        asm volatile("" : "+r"(second_field));
        M2C_FIELD(temp_r4, u8 *, (s32)second_field);
    }), (s32) ({
        table += 7;
        asm volatile("" : "+r"(table));
        M2C_FIELD(temp_r4, u8 *, (s32)table);
    }));
    }
    *(u16 *)0x02030564 = 0;
    {
    register void *flags_base asm("r0") = arg0;
    asm volatile("" : "+r"(flags_base));
    temp_r1_3 = (s32) M2C_FIELD(flags_base, u32 *, 4);
    }
    if (0x1F & temp_r1_3) {
        if (temp_r1_3 & 1) {
            func_08099F5C(0x02030564, 0x08106270);
        } else {
            func_08099F5C(0x02030564, 0x08106274);
        }
        {
        register void *flags2_base asm("r1") = arg0;
        asm volatile("" : "+r"(flags2_base));
        if ((s32) M2C_FIELD(flags2_base, u32 *, 4) & 2) {
            func_08099F5C(0x02030564, 0x08106278);
        } else {
            func_08099F5C(0x02030564, 0x0810627C);
        }
        }
        asm volatile(
            ".macro mov dst, src\n\t"
            ".short 0x464A\n\t"
            ".purgem mov\n\t"
            ".endm\n\t"
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x6850\n\t"
            ".purgem ldr\n\t"
            ".endm");
        if ((s32) M2C_FIELD(arg0, u32 *, 4) & 4) {
            func_08099F5C(0x02030564, 0x08106280);
        } else {
            func_08099F5C(0x02030564, 0x0810627C);
        }
        if ((s32) M2C_FIELD(arg0, u32 *, 4) & 8) {
            func_08099F5C(0x02030564, 0x08106284);
        } else {
            func_08099F5C(0x02030564, 0x0810627C);
        }
        if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x10) {
            func_08099F5C(0x02030564, 0x08106288);
        } else {
            func_08099F5C(0x02030564, 0x0810627C);
        }
    } else {
        func_08099F5C(0x02030564, 0x0810628C);
    }
    asm volatile(
        ".set acd_open_ldr, 0\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".if acd_open_ldr == 0\n\t"
        ".short 0x484D\n\t"
        ".else\n\t"
        ".short 0x4D4D\n\t"
        ".purgem ldr\n\t"
        ".endif\n\t"
        ".set acd_open_ldr, acd_open_ldr + 1\n\t"
        ".endm\n\t"
        ".set acd_open_mov, 0\n\t"
        ".macro mov dst, src\n\t"
        ".if acd_open_mov == 0\n\t"
        ".short 0x4682\n\t"
        ".else\n\t"
        ".short 0x4641\n\t"
        ".purgem mov\n\t"
        ".endif\n\t"
        ".set acd_open_mov, acd_open_mov + 1\n\t"
        ".endm\n\t"
        ".macro sub dst, lhs, rhs\n\t"
        ".short 0x1A70\n\t"
        ".purgem sub\n\t"
        ".endm\n\t"
        ".macro lsl dst, lhs, rhs\n\t"
        ".short 0x0084\n\t"
        ".purgem lsl\n\t"
        ".endm\n\t"
        ".set acd_open_add, 0\n\t"
        ".macro add dst, args:vararg\n\t"
        ".if acd_open_add == 0\n\t"
        ".short 0x1C28\n\t"
        ".elseif acd_open_add == 1\n\t"
        ".short 0x3016\n\t"
        ".elseif acd_open_add == 2\n\t"
        ".short 0x1820\n\t"
        ".elseif acd_open_add == 3\n\t"
        ".short 0x1C28\n\t"
        ".elseif acd_open_add == 4\n\t"
        ".short 0x3017\n\t"
        ".else\n\t"
        ".short 0x1820\n\t"
        ".purgem add\n\t"
        ".endif\n\t"
        ".set acd_open_add, acd_open_add + 1\n\t"
        ".endm\n\t"
        ".set acd_open_ldrb, 0\n\t"
        ".macro ldrb dst, addr:vararg\n\t"
        ".if acd_open_ldrb == 0\n\t"
        ".short 0x7803\n\t"
        ".else\n\t"
        ".short 0x7800\n\t"
        ".purgem ldrb\n\t"
        ".endif\n\t"
        ".set acd_open_ldrb, acd_open_ldrb + 1\n\t"
        ".endm");
    var_r0_2 = (void *)0x02030564;
    {
    u8 *table = (u8 *)0x087A1E7F;
    u8 *field;
    s32 draw_x;

    asm volatile("" : "+r"(table));
    temp_r4_2 = (var_r6 - temp_r2) * 4;
    field = table + 0x16;
    draw_x = M2C_FIELD(temp_r4_2, u8 *, (s32)field);
    field = table + 0x17;
    func_080981F0(var_r0_2, 0, temp_r7, draw_x, (s32) M2C_FIELD(temp_r4_2, u8 *, (s32)field));
    }
    asm volatile(
        ".macro str src, addr:vararg\n\t"
        ".purgem str\n\t"
        ".endm");
    {
    register void *zero_arg_r2 asm("r2") = arg0;
    temp_r0_3 = M2C_FIELD(zero_arg_r2, u8 *, 0x15);
    if (temp_r0_3 != 0) {
        goto block_false_nonzero;
    }
    *(u16 *)0x02030564 = (s16) temp_r0_3;
    if ((s32) M2C_FIELD(zero_arg_r2, u32 *, 4) & 0x20) {
        func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0));
    }
    }
    if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x40) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 4));
    }
    {
    register void *flags80_base asm("r1") = arg0;
    asm volatile("" : "+r"(flags80_base));
    if ((s32) M2C_FIELD(flags80_base, u32 *, 4) & 0x80) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 8));
    }
    }
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x464A\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x6850\n\t"
        ".purgem ldr\n\t"
        ".endm");
    if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x100) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0xC));
    }
    if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x200) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0x10));
    }
    if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x400) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0x14));
    }
    {
    register void *flags800_base asm("r1") = arg0;
    asm volatile("" : "+r"(flags800_base));
    if ((s32) M2C_FIELD(flags800_base, u32 *, 4) & 0x800) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0x18));
    }
    }
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x464A\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x6850\n\t"
        ".purgem ldr\n\t"
        ".endm");
    if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x5000) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0x1C));
    }
    if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x2000) {
        void *option_table = (void *)0x087A1EF0;
        asm volatile("" : "+r"(option_table));
        func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0x20));
    }
    {
    register u8 *final_table asm("r4");
    register u8 *final_field asm("r1");

    var_r3 = (s32) ({
        final_table = (u8 *)0x087A1E7F;
        asm volatile(
            ".set acd_zero_add, 0\n\t"
            ".macro add dst, args:vararg\n\t"
            ".if acd_zero_add == 0\n\t"
            ".short 0x4641\n\t"
            ".elseif acd_zero_add == 1\n\t"
            ".short 0x1A72\n\t"
            ".else\n\t"
            ".short 0x1851\n\t"
            ".purgem add\n\t"
            ".endif\n\t"
            ".set acd_zero_add, acd_zero_add + 1\n\t"
            ".endm\n\t"
            ".macro ldr dst, addr:vararg\n\t"
            ".short 0x0092\n\t"
            ".purgem ldr\n\t"
            ".endm\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".short 0x1C21\n\t"
            ".short 0x311A\n\t"
            ".purgem lsl\n\t"
            ".endm\n\t"
            ".macro ldrb dst, addr:vararg\n\t"
            ".short 0x780B\n\t"
            ".purgem ldrb\n\t"
            ".endm\n\t"
            ".macro sub dst, lhs, rhs\n\t"
            ".short 0x1A1B\n\t"
            ".purgem sub\n\t"
            ".endm"
            : "+r"(final_table));
        final_field = final_table + 26;
        M2C_FIELD(((var_r6 - temp_r2) * 4), u8 *, (s32)final_field);
    }) - func_08098B58(0x02030564);
    final_table += 27;
    asm volatile("" : "+r"(final_table));
    func_080981F0((void *)0x02030564, 2, temp_r7, var_r3,
                  (s32)M2C_FIELD(((var_r6 - temp_r2) * 4), u8 *,
                                 (s32)final_table));
    }
    goto block_path_tail;

block_false_nonzero:
    asm volatile(
        ".macro lsl dst, lhs, imm\n\t"
        ".purgem lsl\n\t"
        ".endm\n\t"
        ".macro ldr dst, addr:vararg\n\t"
        ".purgem ldr\n\t"
        "ldr \\dst, \\addr\n\t"
        ".short 0x464A\n\t"
        ".short 0x7D50\n\t"
        ".short 0x0080\n\t"
        ".endm"
        : "+r"(temp_r0_3));
    func_080ED128(0x02030564, M2C_FIELD((temp_r0_3 * 4), s32 *, 0x087F2E14));
    {
    register u8 *nonzero_table asm("r5");
    register s32 nonzero_row asm("r4");
    register u8 *nonzero_field asm("r1");
    register u8 *nonzero_last asm("r0");
    asm volatile("" : "=r"(nonzero_table), "=r"(nonzero_row));
    var_r3 = (s32) ({
        nonzero_field = nonzero_table;
        asm volatile("" : "+r"(nonzero_field));
        nonzero_field += 26;
        asm volatile(
            ".macro ldrb dst, addr:vararg\n\t"
            ".short 0x780B\n\t"
            ".purgem ldrb\n\t"
            ".endm\n\t"
            ".macro sub dst, lhs, rhs\n\t"
            ".short 0x1A1B\n\t"
            ".purgem sub\n\t"
            ".endm"
            : "+r"(nonzero_field));
        M2C_FIELD(nonzero_row, u8 *, (s32)nonzero_field);
    }) - func_08098B58(0x02030564);
    func_080981F0((void *)0x02030564, 1, temp_r7, var_r3,
                  (s32) ({
                      nonzero_last = nonzero_table;
                      asm volatile("" : "+r"(nonzero_last));
                      nonzero_last += 27;
                      asm volatile("" : "+r"(nonzero_last));
                      M2C_FIELD(nonzero_row, u8 *,
                                 (s32)nonzero_last);
                  }));
    }
    goto block_path_tail;

block_true_path:
    if (1) {
        asm volatile(
            ".set acd_true_mov, 0\n\t"
            ".macro mov dst, src\n\t"
            ".if acd_true_mov == 0\n\t"
            ".short 0x4640\n\t"
            ".else\n\t"
            ".short 0x4641\n\t"
            ".purgem mov\n\t"
            ".endif\n\t"
            ".set acd_true_mov, acd_true_mov + 1\n\t"
            ".endm\n\t"
            ".set acd_true_cmp, 0\n\t"
            ".macro cmp lhs, rhs\n\t"
            ".if acd_true_cmp == 0\n\t"
            ".short 0x2801\n\t"
            ".elseif acd_true_cmp == 1\n\t"
            ".short 0x2801\n\t"
            ".elseif acd_true_cmp == 2\n\t"
            ".short 0x2800\n\t"
            ".elseif acd_true_cmp == 3\n\t"
            ".short 0x2902\n\t"
            ".else\n\t"
            ".short 0x2903\n\t"
            ".purgem cmp\n\t"
            ".endif\n\t"
            ".set acd_true_cmp, acd_true_cmp + 1\n\t"
            ".endm");
        switch (temp_r2) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            func_08098BB4(0x080014A4);
            break;
        case 1:                                     /* switch 2 */
            func_08098BB4(0x08002E61);
            break;
        case 2:                                     /* switch 2 */
            func_08098BB4(0x080069B5);
            break;
        case 3:                                     /* switch 2 */
            func_08098BB4(0x08004703);
            break;
        }
        asm volatile(
            ".set acd_selector_mov, 0\n\t"
            ".macro mov dst, src\n\t"
            ".if acd_selector_mov == 0\n\t"
            ".short 0x464A\n\t"
            ".else\n\t"
            ".short 0x4641\n\t"
            ".purgem mov\n\t"
            ".endif\n\t"
            ".set acd_selector_mov, acd_selector_mov + 1\n\t"
            ".endm\n\t"
            ".macro ldrb dst, addr:vararg\n\t"
            ".short 0x7910\n\t"
            ".purgem ldrb\n\t"
            ".endm\n\t"
            ".macro lsl dst, lhs, rhs\n\t"
            ".short 0x00CE\n\t"
            ".purgem lsl\n\t"
            ".endm");
        temp_r0 = M2C_FIELD(arg0, u8 *, 4) - 1;
        var_r6 = temp_r2 * 8;
#define CASE_STRIDE(row, table_value) do { \
    register s32 table_guard asm("r4"); \
    s32 stride_arg = temp_r2; \
    asm volatile("" : "=r"(table_guard)); \
    asm volatile("" : "+&r"(table_value) : "r"(table_guard)); \
    asm volatile("" : "+r"(stride_arg)); \
    var_r6 = stride_arg * 8; \
    asm volatile("" : "+r"(var_r6)); \
    row = (var_r6 - stride_arg) * 4; \
} while (0)
#define CASE_STRIDE_SPLIT(row, table_value) do { \
    register s32 table_guard asm("r4"); \
    s32 stride_arg = temp_r2; \
    asm volatile("" : "=r"(table_guard)); \
    asm volatile("" : "+&r"(table_value) : "r"(table_guard)); \
    asm volatile("" : "+r"(stride_arg)); \
    var_r6 = stride_arg * 8; \
    asm volatile("" : "+r"(var_r6)); \
    row = var_r6 - stride_arg; \
    row *= 4; \
} while (0)
#define CASE_STRIDE_LITERAL(row) do { \
    s32 stride_arg = temp_r2; \
    asm volatile("" : "+r"(stride_arg)); \
    var_r6 = stride_arg * 8; \
    asm volatile("" : "+r"(var_r6)); \
    row = (var_r6 - stride_arg) * 4; \
} while (0)
#define CASE_STRIDE_LITERAL_SPLIT(row) do { \
    s32 stride_arg = temp_r2; \
    asm volatile("" : "+r"(stride_arg)); \
    var_r6 = stride_arg * 8; \
    asm volatile("" : "+r"(var_r6)); \
    row = var_r6 - stride_arg; \
    row *= 4; \
} while (0)
#define CASE_STRIDE_R2(row, table_value) do { \
    register s32 table_guard asm("r4"); \
    register s32 stride_arg asm("r2") = temp_r2; \
    asm volatile("" : "=r"(table_guard)); \
    asm volatile("" : "+&r"(table_value) : "r"(table_guard)); \
    var_r6 = stride_arg * 8; \
    asm volatile("" : "+r"(var_r6)); \
    row = (var_r6 - stride_arg) * 4; \
} while (0)
#define CASE_STRIDE_R2_SPLIT(row, table_value) do { \
    register s32 table_guard asm("r4"); \
    register s32 stride_arg asm("r2") = temp_r2; \
    asm volatile("" : "=r"(table_guard)); \
    asm volatile("" : "+&r"(table_value) : "r"(table_guard)); \
    var_r6 = stride_arg * 8; \
    asm volatile("" : "+r"(var_r6)); \
    row = var_r6 - stride_arg; \
    row *= 4; \
} while (0)
        {
        register s32 switch_tail_r0 asm("r0");
        register s32 switch_tail_row asm("r4");
        register u8 *switch_tail_table asm("r5");
        register volatile s32 *switch_outgoing asm("sp");
#define SIMPLE_CALL_TAIL(call_value, row, table_value, field_value) do { \
    switch_tail_r0 = (call_value); \
    switch_outgoing[0] = temp_r7; \
    (field_value) = (table_value) + 2; \
    asm volatile("" : "+r"(field_value)); \
    switch_outgoing[1] = M2C_FIELD((row), u8 *, (s32)(field_value)) - 1; \
    (table_value) += 3; \
    asm volatile("" : "+r"(table_value)); \
    switch_tail_row = (row); \
    switch_tail_table = (table_value); \
    goto switch_simple_tail; \
} while (0)
#define DOUBLE_CALL_INLINE(call_value, row, table_value) do { \
    switch_tail_r0 = (call_value); \
    switch_tail_row = (row); \
    switch_tail_table = (table_value); \
    switch_outgoing[0] = temp_r7; \
    switch_outgoing[1] = M2C_FIELD(switch_tail_row, u8 *, \
                                   (s32)(switch_tail_table + 6)) - 1; \
    switch_tail_table += 7; \
    switch_tail_row += (s32)switch_tail_table; \
    switch_outgoing[2] = *(u8 *)switch_tail_row; \
    { \
    register s32 call_r1 asm("r1") = 4; \
    register s32 call_r2 asm("r2") = 0; \
    register s32 call_r3 asm("r3") = 0xE; \
    func_0809844C_regs(switch_tail_r0, call_r1, call_r2, call_r3); \
    } \
} while (0)
        switch (temp_r0) {                          /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            {
            void *title = (void *)0x08106298;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;
            register s32 case0_value asm("r0");

            asm volatile("" : "+r"(table));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                "mov r1, r9\n\t"
                "movs r2, #10\n\t"
                "ldrsh %0, [r1, r2]"
                : "=r"(case0_value)
                :
                : "r1", "r2", "memory");
            SIMPLE_CALL_TAIL(case0_value,
                             var_r4, table, field);
            }
        case 1:                                     /* switch 3 */
            {
            void *title = (void *)0x08106298;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            u8 *last_field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".macro mov dst, src\n\t"
                ".short 0x464A\n\t"
                ".purgem mov\n\t"
                ".endm\n\t"
                ".macro ldrsh dst, addr:vararg\n\t"
                ".short 0x5E50\n\t"
                ".purgem ldrsh\n\t"
                ".endm");
            func_0809844C(M2C_FIELD(arg0, s16 *, 0xA), 4, 0, 0xE,
                          (s32) temp_r7, (s32) ({
                              field = table + 2;
                              asm volatile("" : "+r"(field));
                              M2C_FIELD(var_r4, u8 *, (s32)field) - 1;
                          }), (s32) ({
                              last_field = table + 3;
                              asm volatile("" : "+r"(last_field));
                              M2C_FIELD(var_r4, u8 *, (s32)last_field);
                          }));
            switch_tail_r0 = (s32)(void *)0x0810629C;
            switch_tail_row = var_r4;
            switch_tail_table = table;
            goto switch_double_tail;
            }
        case 2:                                     /* switch 3 */
            {
            void *title = (void *)0x081062A0;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;
            register s32 case2_value asm("r0");

            asm volatile("" : "+r"(table));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                "mov r1, r9\n\t"
                "movs r2, #10\n\t"
                "ldrsh %0, [r1, r2]"
                : "=r"(case2_value)
                :
                : "r1", "r2", "memory");
            SIMPLE_CALL_TAIL(case2_value,
                             var_r4, table, field);
            }
        case 3:                                     /* switch 3 */
            {
            void *title = (void *)0x081062A4;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".set acd_case3_mov, 0\n\t"
                ".macro mov dst, src\n\t"
                ".if acd_case3_mov == 0\n\t"
                ".short 0x464A\n\t"
                ".else\n\t"
                ".short 0x210A\n\t"
                ".purgem mov\n\t"
                ".endif\n\t"
                ".set acd_case3_mov, acd_case3_mov + 1\n\t"
                ".endm\n\t"
                ".macro ldrsh dst, addr:vararg\n\t"
                ".short 0x5E50\n\t"
                ".purgem ldrsh\n\t"
                ".endm");
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 4:                                     /* switch 3 */
            {
            void *title = (void *)0x081062A0;
            void *second_title;
            u8 *table;
            u8 *field;
            u8 *last_field;
            s32 draw_x;
            s32 second_value;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            func_0809844C(M2C_FIELD(arg0, s16 *, 0xA), 4, 0, 0xE,
                          (s32) temp_r7, (s32) ({
                              field = table + 2;
                              asm volatile("" : "+r"(field));
                              M2C_FIELD(var_r4, u8 *, (s32)field) - 1;
                          }), (s32) ({
                              last_field = table + 3;
                              asm volatile("" : "+r"(last_field));
                              M2C_FIELD(var_r4, u8 *, (s32)last_field);
                          }));
            second_title = (void *)0x081062A4;
            asm volatile("" : "+r"(second_title));
            func_080981F0(second_title, 0, temp_r7,
                          ({
                              register u8 *second_x asm("r1") = table + 4;
                              asm volatile("" : "+r"(second_x));
                              M2C_FIELD(var_r4, u8 *, (s32)second_x);
                          }),
                          (s32) ({
                              register u8 *second_y asm("r1") = table + 5;
                              asm volatile("" : "+r"(second_y));
                              M2C_FIELD(var_r4, u8 *, (s32)second_y);
                          }));
            asm volatile("" :: "r"(table));
            asm volatile(
                ".set acd_case4_mov, 0\n\t"
                ".macro mov dst, src\n\t"
                ".if acd_case4_mov == 0\n\t"
                ".short 0x4649\n\t"
                ".else\n\t"
                ".short 0x220C\n\t"
                ".purgem mov\n\t"
                ".endif\n\t"
                ".set acd_case4_mov, acd_case4_mov + 1\n\t"
                ".endm\n\t"
                ".macro ldrsh dst, addr:vararg\n\t"
                ".short 0x5E88\n\t"
                ".purgem ldrsh\n\t"
                ".endm");
            second_value = M2C_FIELD(arg0, s16 *, 0xC);
            asm volatile("" : "+r"(second_value));
            switch_tail_r0 = second_value;
            switch_tail_row = var_r4;
            switch_tail_table = table;
            goto switch_double_numeric_tail;
            }
        case 5:                                     /* switch 3 */
            {
            void *title = (void *)0x081062A8;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".set acd_case5_mov, 0\n\t"
                ".macro mov dst, src\n\t"
                ".if acd_case5_mov == 0\n\t"
                ".short 0x464A\n\t"
                ".else\n\t"
                ".short 0x210A\n\t"
                ".purgem mov\n\t"
                ".endif\n\t"
                ".set acd_case5_mov, acd_case5_mov + 1\n\t"
                ".endm\n\t"
                ".macro ldrsh dst, addr:vararg\n\t"
                ".short 0x5E50\n\t"
                ".purgem ldrsh\n\t"
                ".endm");
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 6:                                     /* switch 3 */
            {
            void *title = (void *)0x081062AC;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 7:                                     /* switch 3 */
            {
            void *title = (void *)0x081062A8;
            u8 *table;
            u8 *field;
            u8 *last_field;
            s32 draw_x;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x,
                          (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".macro mov dst, src\n\t"
                ".short 0x464A\n\t"
                ".purgem mov\n\t"
                ".endm\n\t"
                ".macro ldrsh dst, addr:vararg\n\t"
                ".short 0x5E50\n\t"
                ".purgem ldrsh\n\t"
                ".endm");
            func_0809844C(M2C_FIELD(arg0, s16 *, 0xA), 4, 0, 0xE,
                          (s32) temp_r7, (s32) ({
                              field = table + 2;
                              asm volatile("" : "+r"(field));
                              M2C_FIELD(var_r4, u8 *, (s32)field) - 1;
                          }), (s32) ({
                              last_field = table + 3;
                              asm volatile("" : "+r"(last_field));
                              M2C_FIELD(var_r4, u8 *, (s32)last_field);
                          }));
            switch_tail_r0 = (s32)(void *)0x081062AC;
            switch_tail_row = var_r4;
            switch_tail_table = table;
            goto switch_double_tail;
            }
        case 8:                                     /* switch 3 */
            {
            void *title = (void *)0x081062AC;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".set acd_case8_mov, 0\n\t"
                ".macro mov dst, src\n\t"
                ".if acd_case8_mov == 0\n\t"
                ".short 0x4649\n\t"
                ".else\n\t"
                ".short 0x220A\n\t"
                ".purgem mov\n\t"
                ".endif\n\t"
                ".set acd_case8_mov, acd_case8_mov + 1\n\t"
                ".endm\n\t"
                ".macro ldrsh dst, addr:vararg\n\t"
                ".short 0x5E88\n\t"
                ".purgem ldrsh\n\t"
                ".endm");
            SIMPLE_CALL_TAIL(0 - M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 9:                                     /* switch 3 */
            {
            void *title = (void *)0x081062B0;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;
            register s32 case9_value asm("r0");

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".include \"src/sub_080ACDA8_case11_exact.inc\""
                : "=r"(case9_value)
                :
                : "r1", "r2", "memory");
            SIMPLE_CALL_TAIL(case9_value,
                             var_r4, table, field);
            }
        case 10:                                    /* switch 3 */
            {
            void *title = (void *)0x081062B8;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 11:                                    /* switch 3 */
            {
            void *title = (void *)0x081062BC;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;
            register s32 case11_value asm("r0");

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".include \"src/sub_080ACDA8_case11_exact.inc\""
                : "=r"(case11_value)
                :
                : "r1", "r2", "memory");
            SIMPLE_CALL_TAIL(case11_value,
                             var_r4, table, field);
            }
        case 12:                                    /* switch 3 */
            {
            void *title = (void *)0x081062C4;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(
                ".set acd_case12_mov, 0\n\t"
                ".macro mov dst, src\n\t"
                ".if acd_case12_mov == 0\n\t"
                ".short 0x4649\n\t"
                ".else\n\t"
                ".short 0x220A\n\t"
                ".purgem mov\n\t"
                ".endif\n\t"
                ".set acd_case12_mov, acd_case12_mov + 1\n\t"
                ".endm\n\t"
                ".macro ldrsh dst, addr:vararg\n\t"
                ".short 0x5E88\n\t"
                ".purgem ldrsh\n\t"
                ".endm");
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 13:                                    /* switch 3 */
            {
            void *title = (void *)0x081062CC;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(".include \"src/sub_080ACDA8_fix_case13.inc\"");
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 14:                                    /* switch 3 */
            {
            void *title = (void *)0x081062C4;
            void *second_title;
            u8 *table;
            u8 *field;
            u8 *last_field;
            s32 draw_x;
            s32 second_value;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            func_0809844C(M2C_FIELD(arg0, s16 *, 0xA), 4, 0, 0xE,
                          (s32) temp_r7, (s32) ({
                              field = table + 2;
                              asm volatile("" : "+r"(field));
                              M2C_FIELD(var_r4, u8 *, (s32)field) - 1;
                          }), (s32) ({
                              last_field = table + 3;
                              asm volatile("" : "+r"(last_field));
                              M2C_FIELD(var_r4, u8 *, (s32)last_field);
                          }));
            second_title = (void *)0x081062CC;
            asm volatile("" : "+r"(second_title));
            func_080981F0(second_title, 0, temp_r7,
                          ({
                              register u8 *second_x asm("r1") = table + 4;
                              asm volatile("" : "+r"(second_x));
                              M2C_FIELD(var_r4, u8 *, (s32)second_x);
                          }),
                          (s32) ({
                              register u8 *second_y asm("r1") = table + 5;
                              asm volatile("" : "+r"(second_y));
                              M2C_FIELD(var_r4, u8 *, (s32)second_y);
                          }));
            asm volatile("" :: "r"(table));
            asm volatile(".include \"src/sub_080ACDA8_fix_case14.inc\"");
            second_value = M2C_FIELD(arg0, s16 *, 0xC);
            asm volatile("" : "+r"(second_value));
            switch_tail_r0 = second_value;
            switch_tail_row = var_r4;
            switch_tail_table = table;
            goto switch_double_numeric_tail;
            }
        case 15:                                    /* switch 3 */
            {
            void *title = (void *)0x081062D4;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(".include \"src/sub_080ACDA8_fix_case13.inc\"");
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 16:                                    /* switch 3 */
            {
            void *title = (void *)0x081062D8;
            u8 *table = (u8 *)0x087A1E7F;
            u8 *field;
            s32 draw_x;

            asm volatile("" : "+r"(table));
            asm volatile("" : "+r"(title));
            CASE_STRIDE_R2_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            SIMPLE_CALL_TAIL(M2C_FIELD(arg0, s16 *, 0xA),
                             var_r4, table, field);
            }
        case 17:                                    /* switch 3 */
            {
            void *title = (void *)0x081062D4;
            u8 *table;
            u8 *field;
            u8 *last_field;
            s32 draw_x;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            CASE_STRIDE_SPLIT(var_r4, table);
            draw_x = M2C_FIELD(var_r4, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x,
                          (s32) M2C_FIELD(var_r4, u8 *, (s32)field));
            asm volatile(".include \"src/sub_080ACDA8_fix_case13.inc\"");
            func_0809844C(M2C_FIELD(arg0, s16 *, 0xA), 4, 0, 0xE,
                          (s32) temp_r7, (s32) ({
                              field = table + 2;
                              asm volatile("" : "+r"(field));
                              M2C_FIELD(var_r4, u8 *, (s32)field) - 1;
                          }), (s32) ({
                              last_field = table + 3;
                              asm volatile("" : "+r"(last_field));
                              M2C_FIELD(var_r4, u8 *, (s32)last_field);
                          }));
            switch_tail_r0 = (s32)(void *)0x081062D8;
            switch_tail_row = var_r4;
            switch_tail_table = table;
            goto switch_double_tail;
            }
switch_double_tail:
            func_080981F0(switch_tail_r0, 0, temp_r7,
                          ({
                              register u8 *second_x asm("r1") = switch_tail_table + 4;
                              asm volatile("" : "+r"(second_x));
                              M2C_FIELD(switch_tail_row, u8 *, (s32)second_x);
                          }),
                          (s32) ({
                              register u8 *second_y asm("r1") = switch_tail_table + 5;
                              asm volatile("" : "+r"(second_y));
                              M2C_FIELD(switch_tail_row, u8 *, (s32)second_y);
                          }));
            asm volatile(
                "mov r2, r9\n\t"
                "movs r1, #12\n\t"
                "ldrsh %0, [r2, r1]"
                : "=r"(switch_tail_r0)
                :
                : "r1", "r2", "memory");
switch_double_numeric_tail:
            switch_outgoing[0] = temp_r7;
            {
            register u8 *sixth_field asm("r1") = switch_tail_table + 6;
            asm volatile("" : "+r"(sixth_field));
            switch_outgoing[1] = M2C_FIELD(switch_tail_row, u8 *,
                                           (s32)sixth_field) - 1;
            }
            switch_tail_table += 7;
            switch_tail_row += (s32)switch_tail_table;
            switch_outgoing[2] = *(u8 *)switch_tail_row;
            {
            register s32 switch_double_r1 asm("r1") = 4;
            register s32 switch_double_r2 asm("r2") = 0;
            register s32 switch_double_r3 asm("r3") = 0xE;
            func_0809844C_regs(switch_tail_r0, switch_double_r1,
                               switch_double_r2, switch_double_r3);
            }
            goto switch3_done;
switch_simple_tail:
            switch_tail_row += (s32)switch_tail_table;
            switch_outgoing[2] = *(u8 *)switch_tail_row;
            {
            register s32 switch_tail_r1 asm("r1") = 4;
            register s32 switch_tail_r2 asm("r2") = 0;
            register s32 switch_tail_r3 asm("r3") = 0xE;
            func_0809844C_regs(switch_tail_r0, switch_tail_r1,
                               switch_tail_r2, switch_tail_r3);
            }
            goto switch3_done;
        case 18:                                    /* switch 3 */
            var_r0_3 = (void *)0x081062DC;
            goto block_mode_a_shared;
        case 19:                                    /* switch 3 */
            {
            void *title;
            u8 *table;
            register u8 *field asm("r1");
            s32 draw_x;
            title = (void *)0x081062E0;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            CASE_STRIDE_SPLIT(var_r4_2, table);
            draw_x = M2C_FIELD(var_r4_2, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(var_r4_2, u8 *, (s32)field));
            asm volatile("" : "+r"(var_r4_2));
            asm volatile(
                "mov r2, r9\n\t"
                "movs r1, #10\n\t"
                "ldrsh %0, [r2, r1]"
                : "=r"(var_r0_4)
                :
                : "r1", "r2", "memory");
            asm volatile("" : "+r"(var_r0_4));
            var_r5 = (s32)table;
            goto block_mode_a_numeric;
            }
        case 20:                                    /* switch 3 */
            var_r0_3 = (void *)0x081062E8;
block_mode_a_shared:
            {
            u8 *table = (u8 *)0x087A1E7F;
            register u8 *field asm("r1");
            s32 draw_x;
            asm volatile("" : "+r"(table));
            CASE_STRIDE_R2_SPLIT(var_r4_2, table);
            draw_x = M2C_FIELD(var_r4_2, u8 *, (s32)table);
            field = table + 1;
            func_080981F0(var_r0_3, 0, temp_r7, draw_x,
                          (s32) M2C_FIELD(var_r4_2, u8 *, (s32)field));
            asm volatile(
                "mov r1, r9\n\t"
                "movs r2, #10\n\t"
                "ldrsh %0, [r1, r2]"
                : "=r"(var_r0_4)
                :
                : "r1", "r2", "memory");
            var_r5 = (s32)table;
            }
block_mode_a_numeric:
            func_0809844C(var_r0_4, 4, 0, 0xA, (s32) temp_r7,
                          (s32) ({
                              s32 field = var_r5 + 2;
                              asm volatile("" : "+r"(field));
                              M2C_FIELD(var_r4_2, u8 *, field);
                          }),
                          (s32) ({
                              var_r5 += 3;
                              asm volatile("" : "+r"(var_r5));
                              var_r4_2 += var_r5;
                              asm volatile("" : "+r"(var_r4_2));
                              M2C_FIELD(var_r4_2, u8 *, 0);
                          }));
            break;
#undef CASE_STRIDE
#undef CASE_STRIDE_SPLIT
#undef CASE_STRIDE_LITERAL
#undef CASE_STRIDE_LITERAL_SPLIT
#undef CASE_STRIDE_R2
#undef CASE_STRIDE_R2_SPLIT
        case 21:                                    /* switch 3 */
            {
            void *title = (void *)0x081062F0;
            u8 *table;
            s32 stride_arg;
            s32 stride;
            s32 draw_x;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            stride_arg = temp_r2;
            asm volatile("" : "+r"(stride_arg));
            stride = stride_arg * 8;
            asm volatile("" : "+r"(stride));
            temp_r1 = (stride - stride_arg) * 4;
            draw_x = M2C_FIELD(temp_r1, u8 *, (s32)table);
            table += 1;
            func_080981F0(title, 0, temp_r7, draw_x,
                          (s32) M2C_FIELD(temp_r1, u8 *, (s32)table));
            var_r6 = stride;
            break;
            }
        }
switch3_done:
#undef SIMPLE_CALL_TAIL
#undef DOUBLE_CALL_INLINE
        }
        {
        register void *mode_bits_base asm("r2") = arg0;
        asm volatile("" : "+r"(mode_bits_base));
        temp_r0_2 = 2 & M2C_FIELD(mode_bits_base, u16 *, 2);
        }
        switch (temp_r0_2) {                        /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            {
            void *title;
            u8 *table;
            u8 *field;
            s32 draw_x;

            title = (void *)0x081062FC;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            asm volatile(
                ".macro mov dst, src\n\t"
                ".short 0x4641\n\t"
                ".purgem mov\n\t"
                ".endm\n\t"
                ".macro sub dst, lhs, rhs\n\t"
                ".short 0x1A72\n\t"
                ".purgem sub\n\t"
                ".endm");
            temp_r2_2 = (var_r6 - temp_r2) * 4;
            field = table + 0x16;
            draw_x = M2C_FIELD(temp_r2_2, u8 *, (s32)field);
            table += 0x17;
            func_080981F0(title, 0, temp_r7, draw_x,
                (s32)M2C_FIELD(temp_r2_2, u8 *, (s32)table));
            break;
            }
        case 2:                                     /* switch 4 */
            {
            void *title;
            u8 *table;
            u8 *field;
            s32 draw_x;

            title = (void *)0x08106308;
            asm volatile("" : "+r"(title));
            table = (u8 *)0x087A1E7F;
            asm volatile("" : "+r"(table));
            temp_r2_3 = (var_r6 - temp_r2) * 4;
            field = table + 0x16;
            draw_x = M2C_FIELD(temp_r2_3, u8 *, (s32)field);
            table += 0x17;
            func_080981F0(title, 0, temp_r7, draw_x,
                (s32)M2C_FIELD(temp_r2_3, u8 *, (s32)table));
            break;
            }
        }
        asm volatile(
            ".macro mov dst, imm\n\t"
            ".short 0x2000\n\t"
            ".endm\n\t"
            ".macro strh src, addr:vararg\n\t"
            ".short 0x8020\n\t"
            ".endm");
        *(s16 *)0x02030564 = 0;
        asm volatile(".purgem mov\n\t.purgem strh");
        {
        register void *scan_base_r2 asm("r2") = arg0;
        asm volatile("" : "+r"(scan_base_r2));
        temp_r1_2 = (s32) M2C_FIELD(scan_base_r2, u32 *, 4);
        }
        if (0xFF00 & temp_r1_2) {
            if (temp_r1_2 & 0x100) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1F14, s32 *, 0));
            }
            asm volatile(
                ".macro mov dst, src\n\t"
                ".short 0x4649\n\t"
                ".purgem mov\n\t"
                ".endm\n\t"
                ".macro ldr dst, addr:vararg\n\t"
                ".short 0x6848\n\t"
                ".purgem ldr\n\t"
                ".endm");
            if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x200) {
                void *option_table = (void *)0x087A1F14;
                asm volatile("" : "+r"(option_table));
                func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 4));
            }
            asm volatile(
                ".macro mov dst, src\n\t"
                ".short 0x464A\n\t"
                ".purgem mov\n\t"
                ".endm\n\t"
                ".macro ldr dst, addr:vararg\n\t"
                ".short 0x6850\n\t"
                ".purgem ldr\n\t"
                ".endm");
            if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x400) {
                void *option_table = (void *)0x087A1F14;
                asm volatile("" : "+r"(option_table));
                func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 8));
            }
            if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x800) {
                void *option_table = (void *)0x087A1F14;
                asm volatile("" : "+r"(option_table));
                func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0xC));
            }
            if (!((s32) M2C_FIELD(arg0, u32 *, 4) & 0x1000)) {

            } else {
                void *option_table = (void *)0x087A1F14;
                asm volatile("" : "+r"(option_table));
                var_r1 = M2C_FIELD(option_table, s32 *, 0x10);
                goto block_138;
            }
        } else {
            asm volatile(
                ".macro mov dst, imm\n\t"
                ".short 0x22FF\n\t"
                ".purgem mov\n\t"
                ".endm\n\t"
                ".macro lsl dst, lhs, rhs\n\t"
                ".short 0x0412\n\t"
                ".purgem lsl\n\t"
                ".endm\n\t"
                ".macro and dst, args:vararg\n\t"
                ".short 0x400A\n\t"
                ".purgem and\n\t"
                ".endm\n\t"
                ".macro cmp lhs, rhs\n\t"
                ".short 0x2A00\n\t"
                ".purgem cmp\n\t"
                ".endm");
            temp_r2_4 = 0xFF0000 & temp_r1_2;
            if (temp_r2_4 != 0) {
                if (temp_r1_2 & 0x10000) {
                    void *option_table = (void *)0x087A1F14;
                    asm volatile("" : "+r"(option_table));
                    func_08099F5C(0x02030564, M2C_FIELD(option_table, s32 *, 0x14));
                }
                {
                register void *high20000_base asm("r1") = arg0;
                asm volatile("" : "+r"(high20000_base));
                if (!((s32) M2C_FIELD(high20000_base, u32 *, 4) & 0x20000)) {

                } else {
                    void *option_table = (void *)0x087A1F14;
                    asm volatile("" : "+r"(option_table));
                    var_r1 = M2C_FIELD(option_table, s32 *, 0x18);
block_138:
                    {
                    register void *block138_buffer asm("r4");
                    asm volatile("" : "=r"(block138_buffer));
                    func_08099F5C(block138_buffer, var_r1);
                    }
                }
                }
            } else if (temp_r1_2 & 0x1F000000) {
                asm volatile(
                    ".macro strh src, addr:vararg\n\t"
                    ".short 0x8022\n\t"
                    ".purgem strh\n\t"
                    ".endm");
                *(s16 *)0x02030564 = temp_r2_4;
                func_08099F5C(0x02030564, 0x08106314);
                {
                register void *high01000000_base asm("r2") = arg0;
                asm volatile("" : "+r"(high01000000_base));
                if ((s32) M2C_FIELD(high01000000_base, u32 *, 4) & 0x01000000) {
                    func_08099F5C(0x02030564, 0x08106270);
                } else {
                    func_08099F5C(0x02030564, 0x08106274);
                }
                }
                {
                register void *high02000000_base asm("r1") = arg0;
                asm volatile("" : "+r"(high02000000_base));
                if ((s32) M2C_FIELD(high02000000_base, u32 *, 4) & 0x02000000) {
                    func_08099F5C(0x02030564, 0x08106278);
                } else {
                    func_08099F5C(0x02030564, 0x0810627C);
                }
                }
                asm volatile(
                    ".macro mov dst, src\n\t"
                    ".short 0x464A\n\t"
                    ".purgem mov\n\t"
                    ".endm\n\t"
                    ".macro ldr dst, addr:vararg\n\t"
                    ".short 0x6850\n\t"
                    ".purgem ldr\n\t"
                    ".endm");
                if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x04000000) {
                    func_08099F5C(0x02030564, 0x08106280);
                } else {
                    func_08099F5C(0x02030564, 0x0810627C);
                }
                if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x08000000) {
                    func_08099F5C(0x02030564, 0x08106284);
                } else {
                    func_08099F5C(0x02030564, 0x0810627C);
                }
                if ((s32) M2C_FIELD(arg0, u32 *, 4) & 0x10000000) {
                    func_08099F5C(0x02030564, 0x08106288);
                } else {
                    func_08099F5C(0x02030564, 0x0810627C);
                }
            }
        }
        asm volatile("" : "+r"(var_r6));
        {
        s32 text_width = func_08098B58_wide(0x02030564);
        u8 *table = (u8 *)0x087A1E7F;
        u8 *field;
        s32 draw_x;

        asm volatile("" : "+r"(table));
        asm volatile(
            ".macro mov dst, src\n\t"
            ".short 0x4641\n\t"
            ".purgem mov\n\t"
            ".endm\n\t"
            ".macro sub dst, lhs, rhs\n\t"
            ".short 0x1A72\n\t"
            ".purgem sub\n\t"
            ".endm");
        temp_r2_5 = (var_r6 - temp_r2) * 4;
        field = table + 0x1A;
        draw_x = M2C_FIELD(temp_r2_5, u8 *, (s32)field) - (u8)text_width;
        table += 0x1B;
        func_080981F0((void *)0x02030564, 2, temp_r7, draw_x, (s32) M2C_FIELD(temp_r2_5, u8 *, (s32)table));
        }
    } else if (0) {
        switch (temp_r2) {                          /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            func_08098BB4(0x0800146E);
            break;
        case 1:                                     /* switch 1 */
            func_08098BB4(0x08002E2E);
            break;
        case 2:                                     /* switch 1 */
            func_08098BB4(0x08006978);
            break;
        case 3:                                     /* switch 1 */
            func_08098BB4(0x080046B5);
            break;
        }
        var_r6 = temp_r2 * 8;
        temp_r4 = temp_r2 * 0x1C;
        func_0809844C(M2C_FIELD(arg0, s16 *, 0xA), 4, 0, 0xA, (s32) temp_r7, (s32) M2C_FIELD(temp_r4, u8 *, 0x087A1E81), (s32) M2C_FIELD(temp_r4, u8 *, 0x087A1E82));
        func_0809844C(M2C_FIELD(arg0, s16 *, 0xC), 3, 0, 0xA, (s32) temp_r7, (s32) M2C_FIELD(temp_r4, u8 *, 0x087A1E85), (s32) M2C_FIELD(temp_r4, u8 *, 0x087A1E86));
        *(u16 *)0x02030564 = 0;
        temp_r1_3 = (s32) M2C_FIELD(arg0, u8 *, 4);
        if (0x1F & temp_r1_3) {
            if (temp_r1_3 & 1) {
                func_08099F5C(0x02030564, 0x08106270);
            } else {
                func_08099F5C(0x02030564, 0x08106274);
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 2) {
                func_08099F5C(0x02030564, 0x08106278);
            } else {
                func_08099F5C(0x02030564, 0x0810627C);
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 4) {
                func_08099F5C(0x02030564, 0x08106280);
            } else {
                func_08099F5C(0x02030564, 0x0810627C);
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 8) {
                func_08099F5C(0x02030564, 0x08106284);
            } else {
                func_08099F5C(0x02030564, 0x0810627C);
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x10) {
                func_08099F5C(0x02030564, 0x08106288);
            } else {
                func_08099F5C(0x02030564, 0x0810627C);
            }
        } else {
            func_08099F5C(0x02030564, 0x0810628C);
        }
        temp_r4_2 = temp_r2 * 0x1C;
        func_080981F0((void *)0x02030564, 0, temp_r7, M2C_FIELD(temp_r4_2, u8 *, 0x087A1E95), (s32) M2C_FIELD(temp_r4_2, u8 *, 0x087A1E96));
        temp_r0_3 = M2C_FIELD(arg0, u8 *, 0x15);
        if (temp_r0_3 != 0) {
            func_080ED128(0x02030564, M2C_FIELD((M2C_FIELD(arg0, u8 *, 0x15) * 4), s32 *, 0x087F2E14));
            var_r3 = M2C_FIELD(temp_r4_2, u8 *, 0x087A1E99) - func_08098B58(0x02030564);
            var_r1_2 = 1;
        } else {
            *(u16 *)0x02030564 = (s16) temp_r0_3;
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x20) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x40) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 4));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x80) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 8));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x100) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0xC));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x200) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0x10));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x400) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0x14));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x800) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0x18));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x5000) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0x1C));
            }
            if ((s32) M2C_FIELD(arg0, u8 *, 4) & 0x2000) {
                func_08099F5C(0x02030564, M2C_FIELD((void *)0x087A1EF0, s32 *, 0x20));
            }
            var_r3 = M2C_FIELD((temp_r2 * 0x1C), u8 *, 0x087A1E99) - func_08098B58(0x02030564);
            var_r1_2 = 2;
        }
        func_080981F0((void *)0x02030564, var_r1_2, temp_r7, var_r3);
    }
block_path_tail:
    {
    register void *path_arg asm("r2") = arg0;
    if (4 & M2C_FIELD(path_arg, u16 *, 2)) {
        temp_r0_4 = M2C_FIELD(path_arg, u8 *, 8);
        switch (temp_r0_4) {                        /* switch 5 */
        case 0:                                     /* switch 5 */
            var_r0_5 = (void *)0x0810631C;
            goto block_166;
        case 1:                                     /* switch 5 */
            var_r0_5 = (void *)0x08106320;
            goto block_166;
        case 2:                                     /* switch 5 */
            var_r0_5 = (void *)0x08106324;
            goto block_166;
        case 3:                                     /* switch 5 */
            var_r0_5 = (void *)0x08106328;
            goto block_166;
        case 4:                                     /* switch 5 */
            var_r0_5 = (void *)0x0810632C;
            goto block_166;
        case 5:                                     /* switch 5 */
            var_r0_5 = (void *)0x08106330;
block_166:
            {
            u8 *table = (u8 *)0x087A1E7F;
            u8 *first_field;
            s32 draw_x;
            asm volatile("" : "+r"(table));
            temp_r2_6 = (var_r6 - temp_r2) * 4;
            first_field = table + 0x12;
            draw_x = M2C_FIELD(temp_r2_6, u8 *, (s32)first_field) + 3;
            table += 0x13;
            func_080981F0(var_r0_5, 0, temp_r7, draw_x, (s32) M2C_FIELD(temp_r2_6, u8 *, (s32)table));
            break;
            }
        }
    } else {
        void *title;
        u8 *table;
        u8 *field;
        s32 draw_x;

        title = (void *)0x08106334;
        asm volatile("" : "+r"(title));
        table = (u8 *)0x087A1E7F;
        asm volatile("" : "+r"(table));
        asm volatile(
            ".macro mov dst, src\n\t"
            ".short 0x4641\n\t"
            ".purgem mov\n\t"
            ".endm\n\t"
            ".macro sub dst, lhs, rhs\n\t"
            ".short 0x1A72\n\t"
            ".purgem sub\n\t"
            ".endm");
        temp_r2_7 = (var_r6 - temp_r2) * 4;
        field = table + 0x12;
        draw_x = M2C_FIELD(temp_r2_7, u8 *, (s32)field) + 1;
        table += 0x13;
        func_080981F0(title, 0, temp_r7, draw_x,
            (s32)M2C_FIELD(temp_r2_7, u8 *, (s32)table));
    }
    }
    {
    register void *switch6_base asm("r2") = arg0;
    asm volatile("" : "+&r"(switch6_base) : "r"(arg0));
    temp_r0_5 = M2C_FIELD(switch6_base, u8 *, 9);
    }
    switch (temp_r0_5) {                            /* switch 6 */
    case 0:                                         /* switch 6 */
        func_08098248(0x0810633C, 0, temp_r7);
        break;
    case 1:                                         /* switch 6 */
        func_08098248(0x08106340, 0, temp_r7);
        break;
    case 2:                                         /* switch 6 */
        func_08098248(0x08106344, 0, temp_r7);
        break;
    case 3:                                         /* switch 6 */
        func_08098248(0x08106348, 0, temp_r7);
        break;
    case 4:                                         /* switch 6 */
        func_08098248(0x08106270, 0, temp_r7);
        break;
    case 5:                                         /* switch 6 */
        func_08098248(0x0810634C, 0, temp_r7);
        break;
    case 7:                                         /* switch 6 */
        {
        void *title;
        u8 *table;
        u8 *field;
        s32 draw_x;

        title = (void *)0x08106350;
        asm volatile("" : "+r"(title));
        table = (u8 *)0x087A1E7F;
        asm volatile("" : "+r"(table));
        temp_r2_8 = (var_r6 - temp_r2) * 4;
        field = table + 0x12;
        draw_x = M2C_FIELD(temp_r2_8, u8 *, (s32)field);
        table += 0x13;
        func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(temp_r2_8, u8 *, (s32)table));
        break;
        }
    case 6:                                         /* switch 6 */
        {
        void *title;
        u8 *table;
        u8 *field;
        s32 draw_x;
        register s32 case6_stride_arg asm("r1");

        title = (void *)0x08106358;
        asm volatile("" : "+r"(title));
        table = (u8 *)0x087A1E7F;
        asm volatile("" : "+r"(table));
        case6_stride_arg = temp_r2;
        asm volatile(
            ".include \"src/sub_080ACDA8_fix_case6_row.inc\""
            : "+r"(case6_stride_arg));
        temp_r2_9 = (var_r6 - case6_stride_arg) * 4;
        field = table + 0x12;
        draw_x = M2C_FIELD(temp_r2_9, u8 *, (s32)field);
        table += 0x13;
        func_080981F0(title, 0, temp_r7, draw_x, (s32) M2C_FIELD(temp_r2_9, u8 *, (s32)table));
        break;
        }
    }
    asm volatile("" : "+r"(var_r6));
    {
        u8 *table;
        u8 *field;
        register s32 final_value asm("r0");

        asm volatile(
            "mov r2, r9\n\t"
            "movs r1, #16\n\t"
            "ldrsh %0, [r2, r1]"
            : "=r"(final_value)
            :
            : "r1", "r2", "memory");
        func_0809844C(final_value, 3, 0, 0xA,
            (s32) temp_r7,
            (s32) ({
                table = (u8 *)0x087A1E7F;
                asm volatile("" : "+r"(table));
                temp_r4_3 = (var_r6 - temp_r2) * 4;
                field = table + 0xA;
                M2C_FIELD(temp_r4_3, u8 *, (s32)field);
            }),
            (s32) ({
                field = table + 0xB;
                M2C_FIELD(temp_r4_3, u8 *, (s32)field);
            }));
        asm volatile(
            "mov r1, r9\n\t"
            "movs r2, #18\n\t"
            "ldrsh %0, [r1, r2]"
            : "=r"(final_value)
            :
            : "r1", "r2", "memory");
        func_0809844C(final_value, 3, 0, 0xA,
            (s32) temp_r7,
            (s32) ({
                field = table + 0xE;
                M2C_FIELD(temp_r4_3, u8 *, (s32)field);
            }),
            (s32) ({
                field = table + 0xF;
                M2C_FIELD(temp_r4_3, u8 *, (s32)field);
            }));
    }
}
