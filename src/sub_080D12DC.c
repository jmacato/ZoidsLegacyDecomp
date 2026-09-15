#include "m2c_prelude.h"

s16 func_08092A90(s32);                             /* extern */
s32 func_08092ADC(s32);                             /* extern */
s32 func_080D0AE4();                                /* extern */
M2C_UNK func_080D12A0(s32, s32);                    /* extern */
M2C_UNK jtbl_080D1310();                            /* static */
extern u8 D_0203055C[];
extern u8 D_02033FD0[];
extern void *D_02033F40[];
extern s32 D_02034034;
extern s32 D_02034038;
extern s32 D_0203403C;

asm(
    ".macro D12DC_ARM_CASE4\n"
    ".macro ldr args:vararg\n"
    ".short 0x480A\n"
    ".purgem ldr\n"
    ".endm\n"
    ".macro ldrb args:vararg\n"
    ".short 0x7801\n"
    ".purgem ldrb\n"
    ".endm\n"
    ".macro add args:vararg\n"
    ".short 0x1C04\n"
    ".purgem add\n"
    ".endm\n"
    ".set d12dc_case4_cmp_count, 0\n"
    ".macro cmp args:vararg\n"
    ".if d12dc_case4_cmp_count == 0\n"
    ".short 0x2901\n"
    ".elseif d12dc_case4_cmp_count == 1\n"
    ".short 0x2802\n"
    ".elseif d12dc_case4_cmp_count == 2\n"
    ".short 0x2800\n"
    ".elseif d12dc_case4_cmp_count == 3\n"
    ".short 0x2900\n"
    ".elseif d12dc_case4_cmp_count == 4\n"
    ".short 0x2900\n"
    ".elseif d12dc_case4_cmp_count == 5\n"
    ".short 0x2903\n"
    ".elseif d12dc_case4_cmp_count == 6\n"
    ".short 0x2802\n"
    ".elseif d12dc_case4_cmp_count == 7\n"
    ".short 0x2800\n"
    ".else\n"
    ".short 0x2904\n"
    ".if d12dc_case4_cmp_count == 9\n"
    ".purgem cmp\n"
    ".endif\n"
    ".endif\n"
    ".set d12dc_case4_cmp_count, d12dc_case4_cmp_count + 1\n"
    ".endm\n"
    ".endm\n");

struct CameraOutput {
    s32 x;
    s32 pad4[3];
    s32 y;
};

void sub_080D12DC(void) {
    s32 var_r0_3;
    s32 var_r0_4;
    s32 *var_r2_2;
    register s32 temp_r1 asm("r1");
    s32 temp_r1_10;
    s32 temp_r1_11;
    s32 temp_r1_2;
    s32 temp_r1_3;
    s32 temp_r1_4;
    register s32 temp_r1_5 asm("r1");
    register s32 temp_r1_6 asm("r1");
    s32 temp_r1_8;
    s32 temp_r1_9;
    register s32 temp_r2 asm("r2");
    s32 temp_r2_2;
    register s32 temp_r3 asm("r3");
    register s32 temp_r3_2 asm("r3");
    register s32 temp_r3_5 asm("r3");
    register s32 temp_r4 asm("r4");
    register s32 temp_r4_2 asm("r4");
    s32 temp_r4_4;
    s32 *case1_position;
    register s32 *case1_velocity asm("r6");
    s32 *case2_position;
    s32 *case2_velocity;
    register volatile s32 *case3_position asm("r6");
    register s32 *case3_init asm("r0");
    register s32 *case3_velocity asm("r5");
    u8 *case4_counter;
    u8 *case79_counter;
    u8 *case7_init;
    u32 case7_count;
    s32 *case7_position;
    volatile u8 *case8_counter;
    void *case8_object;
    s32 *case9_position;
    register u8 *case1011_counter asm("r3");
    register u32 case1011_state asm("r2");
    register s32 *case1011_position asm("r0");
    register s32 case1011_current asm("r1");
    s32 *case12_position;
    s32 *tail_position_x;
    s32 *tail_velocity_x;
    s32 *tail_velocity_y;
    s32 tail_sum;
    s32 tail_limit;
    s32 tail_offset;
    s32 tail_position_y_value;
    register s32 var_r0 asm("r0");
    s32 var_r0_2;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    register s32 var_r0_8 asm("r0");
    s32 var_r0_9;
    s32 var_r2;
    register s32 var_r3 asm("r3");
    register s32 var_r4 asm("r4");
    s32 var_r6;
    u32 temp_r0;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r1_7;
    u8 temp_r3_3;
    u8 temp_r4_3;
    u8 *state_base;
    void *var_r1;
    void *var_r1_2;

    temp_r0_2 = D_0203055C[2];
    var_r6 = 0x200;
    if (temp_r0_2 == 0xD) {
        goto block_2;
    }
    var_r6 = 0x80;
block_2:
    {
    u8 *state_init = (u8 *)0x02034030;
    temp_r0 = *state_init - 1;
    state_base = state_init;
    }
    if (temp_r0 <= 0xFU) {
        goto block_4;
    }
    goto block_122;
block_4:
    switch (temp_r0) {                              /* jump table: jtbl_080D1310 */
case 14:
    var_r6 += 0x200;
case 0:
    D_0203403C = var_r6;
    *(s32 *)0x02034040 = 0 - var_r6;
    goto block_122;
case 15:
    var_r6 += 0x200;
case 1:
    D_0203403C = var_r6;
    *(s32 *)0x02034040 = (s32) (0 - var_r6);
    case1_position = &D_02034034;
    temp_r2 = 0x1000;
    temp_r1_11 = -0x1000;
    asm volatile("" : "+r"(temp_r1_11));
    temp_r1 = *case1_position;
    if (temp_r1 >= temp_r1_11) {
        goto block_11;
    }
    var_r0 = temp_r1 + 0x800;
    *case1_position = var_r0;
    D_02034038 += 0x800;
    goto block_122;
block_11:
    case1_velocity = &D_02034038;
    temp_r3 = temp_r2 - temp_r1;
    var_r0 = temp_r3;
    asm volatile("" : "+r"(var_r0));
    if (temp_r3 >= 0) {
        goto block_13;
    }
    var_r0 = temp_r3 + 3;
block_13:
    temp_r4 = var_r0 >> 2;
    *case1_velocity = (s32) (*case1_velocity + temp_r4);
    temp_r1_2 = temp_r1 + temp_r4;
    *case1_position = temp_r1_2;
    if (temp_r1_2 > temp_r2 - 0x80) {
        goto block_15;
    }
    goto block_122;
block_15:
    *case1_position = temp_r2;
    if (*state_base != 2) {
        goto block_17;
    }
    goto block_117;
block_17:
    var_r0_2 = 0xF;
    goto block_118;
case 2:
    temp_r2 = 0x1000;
    case2_velocity = &D_02034038;
    case2_position = &D_02034034;
    temp_r1_3 = *case2_position;
    temp_r2 = temp_r2 - temp_r1_3;
    *case2_velocity = (s32) (*case2_velocity + temp_r2);
    *case2_position = (s32) (temp_r1_3 + temp_r2);
    goto block_117;
case 3:
    temp_r1_4 = *(s32 *)0x0203404C;
    if (temp_r1_4 > 0x7F) {
        goto block_22;
    }
    var_r2 = 0x1000 - ((0x90 - temp_r1_4) << 8);
    goto block_23;
block_22:
    var_r2 = 0x1000;
block_23:
    case3_velocity = &D_02034038;
    case3_init = &D_02034034;
    temp_r4_2 = *case3_init;
    temp_r1_5 = var_r2 - temp_r4_2;
    var_r3 = temp_r1_5;
    asm volatile("" : "+r"(var_r3));
    case3_position = case3_init;
    asm volatile("" : "+r"(case3_position));
    if (temp_r1_5 >= 0) {
        goto block_25;
    }
    var_r3 = temp_r1_5 + 7;
block_25:
    temp_r3_2 = var_r3 >> 3;
    *case3_velocity = (s32) (*case3_velocity + temp_r3_2);
    var_r0 = temp_r4_2 + temp_r3_2;
    *case3_position = var_r0;
    temp_r1_6 = *case3_position;
    if (temp_r1_6 < var_r2) {
        goto block_29;
    }
    if (temp_r1_6 < (s32) (var_r2 + 0x80)) {
        goto block_31;
    }
    if (temp_r1_6 <= var_r2) {
        goto block_29;
    }
    goto block_122;
block_29:
    if (temp_r1_6 > (s32) (var_r2 - 0x80)) {
        goto block_31;
    }
    goto block_122;
block_31:
    D_02034034 = var_r2;
    goto block_117;
case 4:
    asm volatile("D12DC_ARM_CASE4");
    case4_counter = (u8 *)0x02034054;
    temp_r1_7 = *case4_counter;
    if ((u32) temp_r1_7 > 1U) {
        goto block_45;
    }
    if ((u32) D_02033FD0[3] > 2U) {
        goto block_43;
    }
    if (D_02033FD0[1] != 0) {
        goto block_39;
    }
    if (temp_r1_7 != 0) {
        goto block_38;
    }
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1 = case4_table[D_02033FD0[3]];
    }
    var_r0_3 = M2C_FIELD(var_r1, u16 *, 4) + 4;
    goto block_42;
block_38:
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1 = case4_table[D_02033FD0[3]];
    }
    var_r0_3 = M2C_FIELD(var_r1, u16 *, 4) + 2;
    goto block_42;
block_39:
    if (temp_r1_7 != 0) {
        goto block_41;
    }
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1 = case4_table[D_02033FD0[3]];
    }
    var_r0_3 = M2C_FIELD(var_r1, u16 *, 4) - 4;
    goto block_42;
block_41:
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1 = case4_table[D_02033FD0[3]];
    }
    var_r0_3 = M2C_FIELD(var_r1, u16 *, 4) - 2;
block_42:
    M2C_FIELD(var_r1, s16 *, 4) = var_r0_3;
block_43:
    D_0203403C = var_r6;
    goto block_57;
block_45:
    if ((u32) temp_r1_7 <= 3U) {
        goto block_56;
    }
    if ((u32) D_02033FD0[3] > 2U) {
        goto block_56;
    }
    if (D_02033FD0[1] != 0) {
        goto block_52;
    }
    if (temp_r1_7 != 4) {
        goto block_51;
    }
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1_2 = case4_table[D_02033FD0[3]];
    }
    var_r0_4 = M2C_FIELD(var_r1_2, u16 *, 4) - 4;
    goto block_55;
block_51:
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1_2 = case4_table[D_02033FD0[3]];
    }
    var_r0_4 = M2C_FIELD(var_r1_2, u16 *, 4) - 2;
    goto block_55;
block_52:
    if (temp_r1_7 != 4) {
        goto block_54;
    }
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1_2 = case4_table[D_02033FD0[3]];
    }
    var_r0_4 = M2C_FIELD(var_r1_2, u16 *, 4) + 4;
    goto block_55;
block_54:
    {
    register void **case4_table asm("r1") = D_02033F40;
    asm volatile("" : "+r"(case4_table));
    var_r1_2 = case4_table[D_02033FD0[3]];
    }
    var_r0_4 = M2C_FIELD(var_r1_2, u16 *, 4) + 2;
block_55:
    M2C_FIELD(var_r1_2, s16 *, 4) = var_r0_4;
block_56:
    D_0203403C = (s32) (((*case4_counter - 6) << 9) + var_r6);
block_57:
    if (++*case4_counter == 6) {
        goto block_59;
    }
    goto block_122;
block_59:
    goto block_117;
case 5:
    temp_r4_3 = *(u8 *)0x02034054;
    if ((u32) temp_r4_3 <= 0x10U) {
        goto block_63;
    }
    goto block_117;
block_63:
    {
    register s32 *case5_dest asm("r2") = (s32 *)0x02034044;
    register s32 *case5_table asm("r1") = (s32 *)0x087A2A24;
    asm volatile("" : "+r"(case5_dest));
    asm volatile("" : "+r"(case5_table));
    *case5_dest = case5_table[*(volatile u8 *)0x02034054 >> 1];
    }
    *(u8 *)0x02034054 = (u8) (temp_r4_3 + 1);
    goto block_122;
case 6:
    if ((func_080D0AE4() << 0x18) != 0) {
        goto block_66;
    }
    goto block_122;
block_66:
    if (*(u8 *)0x02033F36 != 0) {
        goto block_70;
    }
    if ((s32) M2C_FIELD((void *)0x03000054, s32 *, 0) > 0x10000) {
        goto block_71;
    }
    goto block_72;
block_70:
    if ((s32) M2C_FIELD((void *)0x03000054, s32 *, 0) >= -0x10000) {
        goto block_72;
    }
block_71:
    D_0203403C = 0x800;
    func_080D12A0(0, 0);
    goto block_74;
block_72:
    temp_r1_8 = D_0203403C;
    if (temp_r1_8 > 0xFFF) {
        goto block_74;
    }
    D_0203403C = (s32) (temp_r1_8 + 0x20);
block_74:
    temp_r1_9 = *(s32 *)0x02034040;
    if (temp_r1_9 > -0x800) {
        goto block_76;
    }
    goto block_122;
block_76:
    *(s32 *)0x02034040 = (s32) (temp_r1_9 - 0x40);
    goto block_122;
case 7:
    case7_init = (u8 *)0x02034054;
    asm volatile(
        "ldrb %0, [%2]\n\t"
        "mov %1, %0"
        : "=l"(temp_r3_3), "=l"(case7_count)
        : "l"(case7_init));
    case79_counter = case7_init;
    if (case7_count > 0x10U) {
        goto block_79;
    }
    var_r2_2 = (s32 *)0x02034044;
    {
    register s32 *case7_table asm("r1") = (s32 *)0x087A2A24;
    asm volatile("" : "+r"(case7_table));
    var_r0_5 = case7_table[*(volatile u8 *)case79_counter >> 1];
    }
    asm volatile("" : : "r"(temp_r3_3));
    goto block_97;
block_79:
    if (case7_count != 0x11) {
        goto block_81;
    }
    case7_position = &D_0203403C;
    var_r0_6 = var_r6 + 0xFFFFF800;
    goto block_82;
block_81:
    case7_position = &D_0203403C;
    var_r0_6 = *case7_position + 0x80;
block_82:
    *case7_position = var_r0_6;
    ++*case79_counter;
    var_r0_7 = D_0203403C;
block_83:
    if (var_r0_7 == var_r6) {
        goto block_85;
    }
    goto block_122;
block_85:
    goto block_117;
case 8:
    case8_counter = (u8 *)0x02034054;
    if ((u32) *case8_counter <= 0x10U) {
        goto block_89;
    }
    goto block_117;
block_89:
    case8_object = *(void **)0x02033F4C;
    {
    register s32 *case8_table asm("r1") = (s32 *)0x087A2A24;
    asm volatile("" : "+r"(case8_table));
    M2C_FIELD(case8_object, s16 *, 8) =
        (s16) (case8_table[*case8_counter >> 1] / 0x100);
    }
    ++*case8_counter;
    goto block_122;
case 9:
    case79_counter = (u8 *)0x02034054;
    asm volatile(
        "ldrb r3, [%1]\n\t"
        "mov %0, r3"
        : "=l"(var_r0_8)
        : "l"(case79_counter)
        : "r3");
    asm volatile("" : "+r"(var_r0_8));
    if ((u32) var_r0_8 > 0x3BU) {
        goto block_99;
    }
    var_r2_2 = &D_0203403C;
    if (*var_r2_2 >= (s32) (var_r6 + 0x400)) {
        goto block_95;
    }
    *var_r2_2 += 0x80;
block_95:
    var_r2_2 = (s32 *)0x02034040;
    if (*var_r2_2 <= (s32) ((0 - var_r6) + 0xFFFFFC00)) {
        goto block_98;
    }
    var_r0_5 = *var_r2_2 - 0x20;
block_97:
    *var_r2_2 = var_r0_5;
block_98:
    asm volatile("add %0, r3, #1"
                 : "=l"(var_r0)
                 :
                 : "r3");
    *case79_counter = (u8) var_r0;
    goto block_122;
block_99:
    if ((u32) var_r0_8 > 0x7BU) {
        goto block_103;
    }
    case9_position = &D_0203403C;
    var_r0_9 = func_08092A90((*(volatile u8 *)case79_counter - 0x3C) * 2) * 0x4B;
    if (var_r0_9 >= 0) {
        goto block_102;
    }
    var_r0_9 += 0x3F;
block_102:
    var_r0_9 >>= 6;
    var_r0_9 += 0xFFFFFC00;
    *case9_position = (s32) (var_r6 - var_r0_9);
    ++*case79_counter;
    goto block_122;
block_103:
    D_02034034 = 0x1000;
    {
    register s32 *case9_final_position asm("r1") = &D_0203403C;
    asm volatile(
        "mov r4, #128\n\t"
        "lsl r4, r4, #3\n\t"
        "add %0, %2, r4"
        : "=l"(var_r0)
        : "l"(case9_final_position), "l"(var_r6)
        : "r4");
    *case9_final_position = var_r0;
    }
    var_r0_2 = 0;
    goto block_118;
case 10:
    case1011_counter = (u8 *)0x02034054;
    case1011_state = *case1011_counter;
    if (case1011_state != 0) {
        goto block_108;
    }
    case1011_position = &D_0203403C;
    case1011_current = *case1011_position;
    var_r4 = 0x800;
    goto block_111;
block_108:
    var_r0_7 = D_0203403C + 0xFFFFFF00;
    D_0203403C = var_r0_7;
    goto block_83;
case 11:
    case1011_counter = (u8 *)0x02034054;
    case1011_state = *case1011_counter;
    if (case1011_state != 0) {
        goto block_112;
    }
    case1011_position = &D_0203403C;
    case1011_current = *case1011_position;
    var_r4 = 0xFFFFFE00;
block_111:
    *case1011_position = (s32) (case1011_current + var_r4);
    var_r0 = case1011_state + 1;
    *case1011_counter = (u8) var_r0;
    goto block_122;
block_112:
    var_r0_7 = D_0203403C + 0x10;
    D_0203403C = var_r0_7;
    goto block_83;
case 12:
    temp_r0_3 = *(u8 *)0x02034054;
    if ((u32) temp_r0_3 > 0x24U) {
        goto block_117;
    }
    case12_position = &D_0203403C;
    temp_r1_10 = temp_r0_3;
    asm volatile("" : "+r"(temp_r1_10));
    *case12_position = (s32) (var_r6 - ((s32) (func_08092ADC(temp_r1_10 * 6) << 0x10) >> 0xD));
    *(u8 *)0x02034054 = (u8) (*(u8 *)0x02034054 + 1);
    goto block_122;
block_117:
    var_r0_2 = 1;
block_118:
    func_080D12A0(var_r0_2, 0);
    goto block_122;
case 13:
    D_0203403C = 0;
    if (D_02034034 > 0xFFF) {
        goto block_121;
    }
    *(s32 *)0x02034040 = 0x800;
    goto block_122;
block_121:
    *(s32 *)0x02034040 = 0;
    func_080D12A0(0, 0);
    }
block_122:
    tail_position_x = &D_02034034;
    tail_velocity_x = &D_0203403C;
    tail_velocity_y = (s32 *)0x02034040;
    tail_sum = *tail_velocity_x;
    temp_r2_2 = *tail_velocity_y;
    tail_sum += temp_r2_2;
    temp_r4_4 = *tail_position_x + tail_sum;
    *tail_position_x = temp_r4_4;
    tail_velocity_y = &D_02034038;
    tail_position_y_value = *tail_velocity_y;
    asm volatile("add %0, %1, %2"
                 : "=&r"(temp_r3_5)
                 : "r"(tail_position_y_value), "r"(temp_r2_2));
    *tail_velocity_y = temp_r3_5;
    if (*(u8 *)0x02033F36 != 0) {
        goto block_125;
    }
    {
    register struct CameraOutput *tail_output asm("r1") = (struct CameraOutput *)0x03000054;
    asm volatile("" : "+r"(tail_output));
    tail_output->x = (s32) (temp_r4_4 + *(s32 *)0x02034044);
    var_r0 = *(s32 *)0x02034048;
    asm volatile("add %0, %1, %0"
                 : "+r"(var_r0)
                 : "r"(temp_r3_5));
    tail_output->y = var_r0;
    }
    return;
block_125:
    {
    register struct CameraOutput *tail_output asm("r2") = (struct CameraOutput *)0x03000054;
    asm volatile("" : "+r"(tail_output));
    tail_offset = *(s32 *)0x02034044;
    tail_limit = 0x1000;
    tail_output->x = (s32) ((tail_limit - tail_offset) - temp_r4_4);
    tail_offset = *(s32 *)0x02034048;
    tail_output->y = (s32) ((tail_limit - tail_offset) - temp_r3_5);
    }
    return;
}
