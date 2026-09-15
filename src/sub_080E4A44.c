#include "m2c_prelude.h"

M2C_UNK func_08092E74(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08092EA0(s32);                         /* extern */
s32 func_080940C0();                                /* extern */
s32 func_080940D4();                                /* extern */
s32 func_080940E8();                                /* extern */
s32 func_080940FC();                                /* extern */
s32 func_08094484();                                /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_080981F0();                            /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_08098514();                            /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_080BE600();                            /* extern */
M2C_UNK func_080E4518();                            /* extern */
M2C_UNK func_080E47EC();                            /* extern */
M2C_UNK func_080E4948();                            /* extern */
M2C_UNK func_080E5DC4(u8);                          /* extern */
M2C_UNK func_080E5E0C(u8, s32);                     /* extern */
M2C_UNK func_080E5EBC(u8);                          /* extern */
M2C_UNK func_080EB888();                            /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_080ED038(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
asm(".set D_02032E78_e4a44, 0x02032E78");
extern u8 D_02032E78_e4a44;

void func_080E4A44(void) {
    volatile s32 outgoing_reserve0;
    volatile s32 outgoing_reserve1;
    volatile s32 outgoing_reserve2;
    volatile s32 outgoing_reserve3;
    volatile s32 outgoing_reserve4;
    register s32 var_sl asm("r10");
    register u16 *state asm("r9");
    register u8 *copy_base asm("r8");
    s32 temp_r1;
    register u16 var_r0 asm("r0");
    s32 temp_r0_2;
    u8 temp_r1_2;
    u8 temp_r1_3;
    u8 var_r2;
    u8 var_r2_2;
    u8 var_r6_4;
    u8 var_r6_5;
    u8 var_r7;
    u8 var_r7_2;
    s32 temp_r0;
    s32 temp_r0_3;
    register u8 *temp_r4 asm("r4");
    u8 var_r6;
    u8 var_r6_2;
    u8 var_r6_3;
    u8 var_r6_6;
    u8 var_r6_7;

    asm volatile("" : "=m"(outgoing_reserve0), "=m"(outgoing_reserve1),
                 "=m"(outgoing_reserve2), "=m"(outgoing_reserve3),
                 "=m"(outgoing_reserve4));
    func_080ECD34(0x081046A8, 0x06015840);
    if (*(s32 *)0x02021690 == 0x10) {
        goto block_2;
    }
    goto loop_100;
block_2:
    state = (u16 *)0x02032E76;
loop_3:
    {
    register u16 *dispatch_state asm("r6") = state;
    register s32 state_1000 asm("r7");

    asm volatile("" : "+r"(dispatch_state));
    temp_r1 = *dispatch_state;
    state_1000 = 0x80;
    asm volatile("" : "+r"(state_1000));
    state_1000 <<= 5;
    if (temp_r1 != state_1000) {
        goto block_5;
    }
    goto block_35;
block_5:
    if ((s32) temp_r1 > state_1000) {
        goto block_13;
    }
    }
    if (temp_r1 == 0x10) {
        goto block_27;
    }
    if ((s32) temp_r1 > 0x10) {
        goto block_11;
    }
    if (temp_r1 == 0) {
        goto block_25;
    }
    goto block_95;
block_11:
    if (temp_r1 == 0x20) {
        goto block_29;
    }
    goto block_95;
block_13:
    if (temp_r1 != 0x1020) {
        goto block_15;
    }
    goto block_37;
block_15:
    if ((s32) temp_r1 > 0x1020) {
        goto block_20;
    }
    if (temp_r1 != 0x1010) {
        goto block_18;
    }
    goto block_36;
block_18:
    goto block_95;
block_20:
    if (temp_r1 != 0x2000) {
        goto block_22;
    }
    goto block_49;
block_22:
    if (temp_r1 != 0x3000) {
        goto block_24;
    }
    goto block_87;
block_24:
    goto block_95;
block_25:
    func_080E47EC();
    func_080ED038(0x0202186C, 0x020217F4, 0x78);
    func_080ED038(0x020282EC, 0x020218E4, 0x6A08);
    func_08092E74(3);
    goto block_48;
block_27:
    {
    register s32 outgoing_r0 asm("r0");
    asm volatile(
        "mov %0, #152\n\t"
        "str %0, [sp, #0]"
        : "=r"(outgoing_r0) : : "memory");
    outgoing_r0 = 0x343;
    asm volatile(
        "str %0, [sp, #4]\n\t"
        "mov %0, #15\n\t"
        "str %0, [sp, #8]\n\t"
        "mov %0, #8\n\t"
        "str %0, [sp, #12]\n\t"
        "mov r6, #0\n\t"
        "str r6, [sp, #16]"
        : "+r"(outgoing_r0) : : "r1", "r2", "r6", "memory");
    }
    var_sl = func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8);
    asm volatile("mov %0, #32" : "=r"(var_r0));
    goto block_94;
block_29:
    func_08098BB4(0x080175B7);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_34;
    }
    {
    register u8 *enabled asm("r0") = (u8 *)0x02032E79;
    register u8 *selection asm("r1") = (u8 *)0x0200A880;
    asm volatile("" : "+r"(enabled), "+r"(selection));
    temp_r1_2 = *selection;
    if (M2C_FIELD(temp_r1_2, u8 *, (s32) enabled) == 0) {
        goto block_33;
    }
    *(u8 *)0x02032E74 = temp_r1_2;
    {
    u8 *weapon_index = &D_02032E78_e4a44;
    s32 zero = 0;
    asm volatile("" : : "r"(weapon_index));
    *weapon_index = zero;
    }
    func_08094554(var_sl);
    {
        register s32 next_state asm("r7") = 0x80;
        register u16 *state_r6 asm("r6") = state;

        asm volatile("" : "+r"(next_state));
        next_state <<= 5;
        asm volatile("mov %0, %1"
                     : "=r"(state_r6)
                     : "r"(state), "r"(next_state));
        *state_r6 = next_state;
    }
    goto block_95;
    }
block_33:
    func_08098BB4(0x0801760D);
    goto block_95;
block_34:
    func_08096308(0x10, 0);
    *(s32 *)0x02021690 = 2;
    goto block_95;
block_35:
    func_080E4948();
    goto block_85;
block_36:
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
        "mov r7, #0\n\t"
        "str r7, [sp, #16]"
        : : : "r0", "r1", "r2", "r7", "memory");
    var_sl = func_08094484(0x08105AFC, 0x08105B08, 0, 0x38);
    *state = 0x1020;
    goto block_95;
block_37:
    func_08098BB4(0x08017663);
    if (*(u8 *)0x0200A882 != 1) {
        goto block_47;
    }
    {
    register u8 *enabled asm("r0") = (u8 *)0x02032E83;
    register u8 *selection asm("r1") = (u8 *)0x0200A880;
    asm volatile("" : "+r"(enabled), "+r"(selection));
    temp_r1_3 = *selection;
    if (M2C_FIELD(temp_r1_3, u8 *, (s32) enabled) == 0) {
        goto block_46;
    }
    *(u8 *)0x02032E78 = temp_r1_3;
    func_080BE600();
    func_080E4518();
    {
    register s32 clear_index asm("r6");
    register u8 *clear_base asm("r2");
    register s32 clear_zero asm("r1");

    clear_index = 0;
    clear_base = (u8 *)0x02028200;
    clear_zero = 0;
loop_40:
    M2C_FIELD(clear_index, u8 *, (s32) clear_base) = clear_zero;
    {
    register s32 next_clear_index asm("r0") = clear_index + 1;
    clear_index = (u8) next_clear_index;
    }
    if ((u32) clear_index <= 5U) {
        goto loop_40;
    }
    }
    func_08096308(0x10, 0);
    goto loop_44;
block_43:
    func_080ED17C(1);
loop_44:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_43;
    }
    *(s8 *)0x02032EF8 = 0x1D;
    func_08092E74(0x1D);
    {
        u8 *output = (u8 *)0x0203055C;
        register s32 zero_r6 asm("r6");
        register s32 zero_r7 asm("r7");
        register s32 *word asm("r0");

        output[0] = 2;
        output[1] = 0x10;
        zero_r6 = 0;
        output[5] = zero_r6;
        word = (s32 *)0x02030558;
        asm volatile("" : "+r"(word));
        zero_r7 = 0;
        *word = zero_r7;
    }
    *(s32 *)0x02021690 = 9;
    goto block_95;
    }
block_46:
    func_08098BB4(0x080176BC);
    goto block_95;
block_47:
    func_08098BB4(0x080176B9);
    func_08094554(var_sl);
block_48:
    {
        register s32 next_state asm("r0") = 0x10;
        register u16 *state_r1 asm("r1");
        asm volatile("" : "+r"(next_state));
        state_r1 = state;
        *state_r1 = next_state;
    }
    goto block_95;
block_49:
    func_080EB888();
    {
    register s32 copy_index asm("r6");

    {
    register u8 *copy_dst asm("r3");
    register u8 *copy_src asm("r2");

    copy_index = 0;
    copy_dst = (u8 *)0x020217F4;
    copy_src = (u8 *)0x0202186C;
loop_50:
    M2C_FIELD(copy_index, u8 *, (s32) copy_dst) =
        M2C_FIELD(copy_index, u8 *, (s32) copy_src);
    {
    register s32 next_copy_index asm("r0") = copy_index + 1;
    copy_index = (u8) next_copy_index;
    }
    if ((u32) copy_index <= 9U) {
        goto loop_50;
    }
    }
    {
    register u8 *copy_dst asm("r5");
    register u8 *copy_src asm("r4");
    register u8 *copy_tail_dst asm("r12");
    register u8 *copy_tail_seed asm("r0");
    register s32 inner_index asm("r2");
    register s32 row_offset asm("r3");

    copy_index = 0;
    copy_base = (u8 *)0x0202ECF4;
    copy_dst = (u8 *)0x02028200;
    copy_src = (u8 *)0x0202EC08;
    asm volatile("" : "+r"(copy_dst), "+r"(copy_src));
    copy_tail_seed = copy_dst + 6;
    asm volatile("" : "+r"(copy_tail_seed));
    copy_tail_dst = copy_tail_seed;
loop_52:
    {
    register u8 *indexed_dst asm("r0");
    register u8 *indexed_src asm("r1");
    asm volatile(
        "add %0, %2, %3\n\t"
        "add %1, %2, %4"
        : "=&r"(indexed_dst), "=&r"(indexed_src)
        : "r"(copy_index), "r"(copy_dst), "r"(copy_src));
    *indexed_dst = *indexed_src;
    }
    inner_index = 0;
    {
    register s32 doubled_index asm("r0") = copy_index * 2;
    asm volatile("" : "+r"(doubled_index));
    row_offset = doubled_index + copy_index;
    }
loop_53:
    temp_r0 = inner_index + row_offset;
    M2C_FIELD(temp_r0, u8 *, (s32) copy_tail_dst) =
        *(u8 *)(0x0202EC0E + temp_r0);
    {
    register s32 next_inner_index asm("r0") = inner_index + 1;
    inner_index = (u8) next_inner_index;
    }
    if ((u32) inner_index <= 2U) {
        goto loop_53;
    }
    asm volatile("" : "+r"(copy_index));
    {
    register s32 next_copy_index asm("r0") = copy_index + 1;
    copy_index = (u8) next_copy_index;
    }
    if ((u32) copy_index <= 5U) {
        goto loop_52;
    }
    }
    }
    {
    register u8 *weapon_ptr asm("r4") = (u8 *)0x02032E78;
    register u8 *zoid_ptr asm("r5") = (u8 *)0x02032E74;
    register s32 selected asm("r0");
    register s32 selected_byte asm("r1");
    register s32 count_index asm("r6");
    asm volatile("" : "+r"(weapon_ptr), "+r"(zoid_ptr));
    selected_byte = *zoid_ptr;
    selected = selected_byte * 5;
    selected_byte = *weapon_ptr;
    selected += selected_byte;
    {
    register u8 *flag_base asm("r1") = (u8 *)0x198;
    flag_base += (s32) copy_base;
    M2C_FIELD(selected, u8 *, (s32) flag_base) = 1;
    }
    func_080E47EC();
    func_080E4948();
    var_r7 = 0;
    count_index = 0;
    {
    register s32 weapon_offset asm("r2");
    register s32 zoid_offset asm("r1");
    register s32 zoid_scaled asm("r0");
    register u8 *count_table asm("r3");
    register s32 count_address asm("r0");

    {
    register s32 weapon_value asm("r0") = *weapon_ptr;
    asm volatile("" : "+r"(weapon_value));
    weapon_offset = weapon_value << 7;
    }
    zoid_offset = *zoid_ptr;
    zoid_scaled = zoid_offset * 5;
    zoid_offset = zoid_scaled << 7;
    count_table = (u8 *)0x087A3F64;
    asm volatile("" : "+r"(count_table));
loop_56:
    count_address = count_index * 2;
    count_address += weapon_offset;
    count_address += zoid_offset;
    count_address += (s32) count_table;
    if (*(u8 *)count_address == 0) {
        goto block_58;
    }
    var_r7 += 1;
block_58:
    {
    register s32 next_count_index asm("r0") = count_index + 1;
    count_index = (u8) next_count_index;
    }
    if ((u32) count_index <= 4U) {
        goto loop_56;
    }
    }
    if (var_r7 != 0) {
        goto block_61;
    }
    goto block_84;
block_61:
    {
    register s32 draw_y asm("r2");

    asm volatile(
        "mov %0, #6\n\t"
        "sub %0, %1\n\t"
        "lsl %0, %0, #24\n\t"
        "lsr %0, %0, #24\n\t"
        "lsl r0, %1, #25\n\t"
        "mov r6, #128\n\t"
        "lsl r6, r6, #18\n\t"
        "add r0, r0, r6\n\t"
        "lsr r0, r0, #24\n\t"
        "str r0, [sp, #0]\n\t"
        "mov %1, #0\n\t"
        "str %1, [sp, #4]"
        : "=&r"(draw_y), "+r"(var_r7)
        :
        : "r0", "r6", "memory");
    func_08098514(3, 0, draw_y, 0x1E);
    }
    {
    register s32 item_table asm("r2");

    var_r6_5 = 0;
loop_62:
    {
    register u8 *selection_ptr asm("r0") = (u8 *)0x02032E74;
    register s32 selection asm("r0");

    asm volatile("" : "+r"(selection_ptr));
    selection = *selection_ptr;
    item_table = selection * 0x280;
    }
    {
    register u8 *selection_ptr asm("r0") = (u8 *)0x02032E78;
    register s32 selection asm("r0");
    register u8 *table_base asm("r1");

    asm volatile("" : "+r"(selection_ptr));
    selection = *selection_ptr;
    selection <<= 7;
    asm volatile("" : "+r"(selection));
    table_base = (u8 *)0x087A3EF0;
    asm volatile("" : "+r"(table_base));
    selection += (s32) table_base;
    item_table += selection;
    }
    {
    register s32 item_offset asm("r0") = var_r6_5 * 2;

    item_offset += 0x74;
    temp_r4 = (u8 *)(item_table + item_offset);
    }
    temp_r0_2 = temp_r4[0];
    if (temp_r0_2 == 2) {
        goto block_71;
    }
    if ((s32) temp_r0_2 > 2) {
        goto block_67;
    }
    if (temp_r0_2 == 1) {
        goto block_69;
    }
    goto block_75;
block_67:
    if (temp_r0_2 == 3) {
        goto block_73;
    }
    goto block_75;
block_69:
    {
        register s32 outgoing_r0 asm("r0") = var_r7 * 2;
        asm volatile("str %0, [sp, #0]" : "+r"(outgoing_r0) : : "memory");
    }
    func_080981F0(0x081093AC, 0, 3, 0);
    {
    register s32 *message_table asm("r1") = (s32 *)0x087EF130;
    asm volatile("" : "+r"(message_table));
    func_08098248(message_table[temp_r4[1]], 2, 3);
    }
    func_08098248(0x081093C8, 0, 3);
    func_080E5EBC(temp_r4[1]);
    goto block_74;
block_71:
    {
        register s32 outgoing_r0 asm("r0") = var_r7 * 2;
        asm volatile("str %0, [sp, #0]" : "+r"(outgoing_r0) : : "memory");
    }
    func_080981F0(0x081093CC, 0, 3, 0);
    {
    register s32 *message_table asm("r1") = (s32 *)0x087EEE60;
    asm volatile("" : "+r"(message_table));
    func_08098248(message_table[temp_r4[1]], 2, 3);
    }
    func_08098248(0x081093DC, 0, 3);
    func_080E5E0C(temp_r4[1], 1);
    goto block_74;
block_73:
    {
        register s32 outgoing_r0 asm("r0") = var_r7 * 2;
        asm volatile("str %0, [sp, #0]" : "+r"(outgoing_r0) : : "memory");
    }
    func_080981F0(0x081093CC, 0, 3, 0);
    {
    register s32 *message_table asm("r1") = (s32 *)0x087EDD54;
    asm volatile("" : "+r"(message_table));
    func_08098248(message_table[temp_r4[1]], 2, 3);
    }
    func_08098248(0x081093EC, 0, 3);
    func_080E5DC4(temp_r4[1]);
block_74:
    var_r7 += 1;
block_75:
    var_r6_5 += 1;
    if ((u32) var_r6_5 > 4U) {
        goto block_77;
    }
    goto loop_62;
    }
block_77:
    asm volatile("" : : "r"(zoid_ptr));
    }
    if ((func_080940C0() << 0x18) == 0) {
        goto block_83;
    }
    if ((func_080940D4() << 0x18) == 0) {
        goto block_83;
    }
    if ((func_080940E8() << 0x18) == 0) {
        goto block_83;
    }
    if ((func_080940FC() << 0x18) == 0) {
        goto block_83;
    }
    {
        u8 *flag_b = (u8 *)0x0202169B;
        u8 *flag_c = (u8 *)0x0202169C;
        u8 *flag_d = (u8 *)0x0202169D;
        u8 *flag_e = (u8 *)0x0202169E;
        s32 one = 1;

        *flag_e = one;
        *flag_d = one;
        *flag_c = one;
        *flag_b = one;
    }
    func_08092E84(0x35);
    func_08098BB4(0x0801770A);
    func_08092EA0(0x35);
    goto block_84;
block_83:
    func_08092E84(0x35);
    func_08098BB4(0x0801770A);
    func_08092EA0(0x35);
    func_08092E84(0x58);
    func_08098BB4(0x08017732);
block_84:
    func_08092E74(3);
block_85:
    {
        register s32 state_1010 asm("r1") = 0x1010;
        register s32 next_state asm("r0") = state_1010;
        register u16 *state_r6 asm("r6");
        asm volatile("" : "+r"(state_1010), "+r"(next_state));
        state_r6 = state;
        *state_r6 = next_state;
    }
    goto block_95;
block_87:
    {
    register s32 copy_index asm("r6");

    {
    register u8 *copy_dst asm("r3");
    register u8 *copy_src asm("r2");

    copy_index = 0;
    copy_dst = (u8 *)0x020217F4;
    copy_src = (u8 *)0x0202186C;
loop_88:
    M2C_FIELD(copy_index, u8 *, (s32) copy_dst) =
        M2C_FIELD(copy_index, u8 *, (s32) copy_src);
    {
    register s32 next_copy_index asm("r0") = copy_index + 1;
    copy_index = (u8) next_copy_index;
    }
    if ((u32) copy_index <= 9U) {
        goto loop_88;
    }
    }
    {
    register u8 *copy_dst asm("r7");
    register u8 *copy_src asm("r5");
    register u8 *copy_tail_src asm("r12");
    register u8 *copy_tail_seed asm("r1");
    register s32 inner_index asm("r2");
    register s32 next_copy_index asm("r4");
    register s32 row_offset asm("r3");

    copy_index = 0;
    copy_dst = (u8 *)0x02028200;
    copy_src = (u8 *)0x0202EC08;
    asm volatile("" : "+r"(copy_dst), "+r"(copy_src));
    copy_base = copy_dst + 6;
    copy_tail_seed = copy_src + 6;
    asm volatile("" : "+r"(copy_tail_seed));
    copy_tail_src = copy_tail_seed;
loop_90:
    {
    register u8 *indexed_dst asm("r0");
    register u8 *indexed_src asm("r1");
    asm volatile(
        "add %0, %2, %3\n\t"
        "add %1, %2, %4"
        : "=&r"(indexed_dst), "=&r"(indexed_src)
        : "r"(copy_index), "r"(copy_dst), "r"(copy_src));
    *indexed_dst = *indexed_src;
    }
    inner_index = 0;
    next_copy_index = copy_index + 1;
    {
    register s32 doubled_index asm("r0") = copy_index * 2;
    asm volatile("" : "+r"(doubled_index));
    row_offset = doubled_index + copy_index;
    }
loop_91:
    temp_r0_3 = inner_index + row_offset;
    {
    register u8 *copy_tail_dst asm("r6") = copy_base;
    register u8 *copy_tail_address asm("r1");
    asm volatile("add %0, %1, %2"
                 : "=r"(copy_tail_address)
                 : "r"(temp_r0_3), "r"(copy_tail_dst));
    *copy_tail_address = copy_tail_src[temp_r0_3];
    }
    {
    register s32 next_inner_index asm("r0") = inner_index + 1;
    inner_index = (u8) next_inner_index;
    }
    if ((u32) inner_index <= 2U) {
        goto loop_91;
    }
    {
    register s32 normalized_index asm("r0") = next_copy_index << 24;
    asm volatile("" : "+r"(normalized_index));
    copy_index = (u32) normalized_index >> 24;
    }
    if ((u32) copy_index <= 5U) {
        goto loop_90;
    }
    }
    }
    func_080E47EC();
    func_08092E74(3);
    asm volatile(
        "mov %0, #128\n\t"
        "lsl %0, %0, #5"
        : "=r"(var_r0));
block_94:
    asm volatile(
        "mov r7, r9\n\t"
        "strh %0, [r7]"
        : "+r"(var_r0)
        : "r"(state)
        : "r7", "memory");
block_95:
    if (*(s32 *)0x02021690 != 0x10) {
        goto block_97;
    }
    goto loop_3;
block_97:
    goto loop_100;
block_99:
    func_080ED17C(1);
loop_100:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_99;
    }
    return;
}
