#include "m2c_prelude.h"
#define NULL ((void *)0)

M2C_UNK func_08092E84(s32);                         /* extern */
void *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08096F3C();                            /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, u32);     /* extern */
M2C_UNK func_08098248(s32, s32, s32);               /* extern */
M2C_UNK func_0809844C(s16, s32, s32, s32, s32, s32, u32); /* extern */
M2C_UNK func_0809844C_wide(s32, s32, s32, s32, s32, s32, u32)
    asm("func_0809844C");
M2C_UNK func_080984C4(u32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080984C4_4(u32, s32, s32, s32)
    asm("func_080984C4");
M2C_UNK func_080986B4(s32);                         /* extern */
M2C_UNK func_08098BB4(s32);                         /* extern */
M2C_UNK func_0809A9C8(u8, s32, u8, M2C_UNK, s32, s32); /* extern */
s32 func_0809F818(s32);                             /* extern */
s32 func_080E5354();                                /* extern */
M2C_UNK func_080E5880(void *, void *);              /* extern */
s32 func_080E5CE4(u16, s32);                        /* extern */
s32 func_080E5DC4(u8);                              /* extern */
s32 func_080E5E0C(u8, s32);                         /* extern */
M2C_UNK func_080E5E64(u32);                         /* extern */
M2C_UNK func_080E5FA8(s32, u8);                     /* extern */
M2C_UNK func_080E6020(u8);                          /* extern */
M2C_UNK func_080E6020_wide(s32) asm("func_080E6020");
M2C_UNK func_080E6090(s32);                         /* extern */
M2C_UNK func_080E6F6C(u8);                          /* extern */
M2C_UNK func_080E6F6C_wide(s32) asm("func_080E6F6C");
s32 func_080E705C(void *, s32);                     /* extern */
M2C_UNK func_080E7664(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_080E7664_wide(s32, s32, M2C_UNK)
    asm("func_080E7664");
s32 func_080E79F4();                                /* extern */
s32 func_080E7B64(u8);                              /* extern */
M2C_UNK func_080EB888();                            /* extern */
s32 func_080ECD5C(s32);                             /* extern */
u16 func_080ECD98(s32, s16);                        /* extern */
u16 func_080ECD98_wide(s32, s32) asm("func_080ECD98");
s32 func_080ECF78(void *, s32);                     /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080C7B40();                            /* static */
extern s32 D_087EE170[];

void sub_080C7190(u8 arg0) {
    u8 sp14[6];
    union {
        u8 bytes[12];
        struct {
            u8 pad[4];
            u16 halfwords[24];
        } h;
    } scratch;
    u8 sp50[6];
    u32 sp58;
    u32 sp5C;
    s32 sp60;
    s32 sp64;
    u8 *sp68;
    s32 sp6C;
    u32 sp70;
    u8 *sp74;
    u8 *sp78;
    register volatile u8 **physical_stack asm("sp");
#define sp7C physical_stack[31]
    s32 temp_r0_10;
    s32 temp_r0_12;
    s32 temp_r0_23;
    s32 temp_r0_3;
    s32 temp_r0_6;
    register s32 temp_r0_7 asm("r0");
    s32 temp_r2_2;
    s32 temp_r3_4;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_4;
    s32 temp_r4_6;
    s32 temp_r5_2;
    register s32 temp_r6_3 asm("r6");
    s32 var_r5_5;
    u16 temp_r4_5;
    u32 temp_r0_11;
    u32 temp_r0_24;
    u32 temp_r0_2;
    u32 temp_r0_4;
    u32 temp_r0_9;
    u32 temp_r1_10;
    u32 temp_r2_3;
    u32 var_r0;
    u32 var_sl;
    u8 *temp_r0_26;
    u8 *temp_r1_7;
    register u8 *temp_r3_2 asm("r3");
    register u8 *var_r3 asm("r3");
    register u32 temp_r0 asm("r9");
    u8 temp_r0_13;
    u8 temp_r0_14;
    u8 temp_r0_16;
    u8 temp_r0_17;
    u8 temp_r0_19;
    u8 temp_r0_20;
    u8 temp_r0_22;
    u8 temp_r0_25;
    u8 temp_r0_28;
    u8 temp_r0_29;
    u8 temp_r0_30;
    u8 temp_r0_31;
    u8 temp_r0_5;
    u8 temp_r0_8;
    u8 temp_r1;
    u8 temp_r1_2;
    u8 temp_r1_3;
    u8 temp_r1_4;
    u8 temp_r1_5;
    u32 temp_r1_6;
    u8 temp_r1_8;
    u8 temp_r1_9;
    u8 temp_r2;
    u8 temp_r3_3;
    u8 temp_r4_3;
    register u32 temp_r5 asm("r5");
    u8 temp_r5_3;
    u8 var_r4;
    u8 var_r4_2;
    u8 var_r4_3;
    u8 var_r5;
    u8 var_r5_2;
    u8 var_r5_3;
    u8 var_r7;
    u8 var_r7_2;
    u8 var_r7_4;
    register u32 var_r8 asm("r8");
    register u32 var_r8_10 asm("r8");
    register u32 var_r8_11 asm("r8");
    register u32 var_r8_3 asm("r8");
    register u32 var_r8_5 asm("r8");
    register u32 var_r8_6 asm("r8");
    register u32 var_r8_7 asm("r8");
    register u32 var_r8_8 asm("r8");
    register u32 var_r8_9 asm("r8");
    register u32 var_sl_2;
    u32 menu_row;
    u32 menu_frame_anchor;
    register u32 menu_one_r5 asm("r5");
    u8 *temp_r0_15;
    u8 *temp_r0_18;
    u8 *temp_r0_21;
    u8 *temp_r3;
    u8 *temp_r3_5;
    register u8 *temp_r4_7 asm("r4");
    register u8 *reward_record asm("r4");
    u8 *temp_r6;
    u8 *temp_r6_2;
    register u8 *temp_r7 asm("r7");
    register u8 *temp_r7_2 asm("r7");
    register u8 *temp_r7_3 asm("r7");
    u8 *temp_r7_4;
    u8 *var_r5_7;
    u8 *var_r5_8;
    register u8 *var_r7_3 asm("r7");
    register u32 reward_table_seed asm("r0");
    register u32 reward_successor asm("r8");
    register u32 result_buffer_seed asm("r3");
    register u32 var_r8_2 asm("r8");
    register u32 owner_map_offset asm("r1");
    register u8 *owner_map_ptr asm("r0");
    register u8 *active_base asm("r2");
    register u32 active_offset asm("r3");
    register u8 *active_sum asm("r0");
    register u8 *active_ptr asm("r1");
    u8 active_value;
    register u8 *roster_base asm("r1");
    register u8 *battle_base asm("r4");
    register u32 battle_offset asm("r2");
    register u8 *battle_sum asm("r1");
    register u8 *battle2_base asm("r2");
    register u32 battle2_offset asm("r4");
    register u8 *battle2_sum asm("r1");
    register u8 *scan_base asm("r2");
    register u8 *scan_map_base asm("r0");
    register u32 scan_map_offset asm("r1");
    register u8 *scan_selected asm("r1");
    register u32 scan_selected_offset asm("r3");
    register u8 *scan_selected_sum asm("r0");
    register u32 scan_first_value asm("r0");
    register u8 *scan2_base asm("r2");
    register u8 *scan2_map_base asm("r3");
    register u32 scan2_map_offset asm("r4");
    register u8 *scan2_selected asm("r1");
    register u8 *scan2_selected_base asm("r4");
    register u8 *scan2_selected_sum asm("r0");
    register u8 *mode_base asm("r4");
    register u32 mode_offset asm("r1");
    register u8 *mode_ptr asm("r5");
    u32 mode_index;
    register u32 mode_table_offset asm("r3");
    register u8 *mode_table asm("r1");
    register u8 *mode2_root asm("r1");
    register u32 mode2_offset asm("r2");
    register u8 *mode2_ptr asm("r4");
    register u8 *mode2_table_root asm("r4");
    register u32 mode2_table_offset asm("r5");
    register u8 *mode2_table asm("r2");
    register u8 *mode2_count_ptr asm("r0");
    register u8 *catalog_base asm("r5");
    register u8 *catalog_coord_base asm("r2");
    register u32 catalog_row_seed asm("r1");
    register u32 catalog_row100 asm("r3");
    register u32 catalog_address asm("r0");
    u32 catalog_page_seed;
    register u32 catalog_page2000 asm("r2");
    register u32 catalog_outer_seed asm("r1");
    register s32 stat_left asm("r0");
    register s32 stat_right asm("r1");
    register u32 stat_left_offset asm("r2");
    register u32 stat_right_offset asm("r3");
    register u8 *state13_root asm("r0");
    register u32 state13_offset asm("r2");
    register u8 *state13_control asm("r2");
    register u8 *state13_catalog_seed asm("r4");
    register u8 *state13_catalog_base asm("ip");
    register u32 state13_page_seed asm("r1");
    register u32 state13_work asm("r0");
    register u32 var_r8_4 asm("r8");
    register u8 *header_mode_base asm("r1");
    register u32 header_mode_offset asm("r2");
    register u8 *header_mode_ptr asm("r0");
    register u8 *header_value_base asm("r3");
    register u32 header_value_offset asm("r4");
    register u8 *header_value_ptr asm("r0");
    register u8 *header_value15_base asm("r1");
    register u32 header_value15_offset asm("r2");
    register u8 *header_value15_ptr asm("r0");
    register u8 *header_mode2_base asm("r4");
    register u32 header_mode2_offset asm("r5");
    register u8 *header_mode2_ptr asm("r0");
    register u32 header_value2_offset asm("r1");
    register u8 *header_value2_ptr asm("r0");
    register u8 *header_value14_base asm("r2");
    register u32 header_value14_offset asm("r3");
    register u8 *header_value14_ptr asm("r0");
    register u32 header_half asm("r5");
    register u8 *initial_roster_base asm("r2");
    register u32 initial_active asm("r0");
    register u32 tail_seed asm("r0");
    register u8 *tail_base asm("r2");
    register u32 tail_offset asm("r1");
    register u32 tail_record_offset asm("r0");
    register u32 tail_status_offset asm("r5");
    register u32 tail_status asm("r1");
    register u32 tail_data_offset asm("r0");
    register u8 *tail_data_base asm("r1");
    register u32 tail2_seed asm("r4");
    register u8 *tail2_base asm("r4");
    register u32 tail2_index asm("r5");
    register u32 tail2_record asm("r0");
    register u32 tail2_offset asm("r1");

    temp_r0 = arg0;
    header_mode_base = (u8 *)0x02034B4C;
    header_mode_offset = 0x27BE;
    asm volatile("" : "+r"(header_mode_base), "+r"(header_mode_offset));
    header_mode_ptr = header_mode_base + header_mode_offset;
    if (*header_mode_ptr == 0xF) {
        goto block_2;
    }
    header_value_base = header_mode_base;
    header_value_offset = 0xA070;
    asm volatile("" : "+r"(header_value_base), "+r"(header_value_offset));
    header_value_ptr = header_value_base + header_value_offset;
    var_sl = *(u32 *)header_value_ptr;
    asm volatile("mov %0, sl" : "=r"(header_half));
    header_half >>= 1;
    sp58 = header_half;
    asm volatile("" : : "m"(sp58));
    goto block_3;
block_2:
    header_value15_base = (u8 *)0x02034B4C;
    header_value15_offset = 0xA070;
    asm volatile("" : "+r"(header_value15_base), "+r"(header_value15_offset));
    header_value15_ptr = header_value15_base + header_value15_offset;
    temp_r0_2 = *(u32 *)header_value15_ptr;
    asm volatile(
        "lsl r3, %1, #1\n\t"
        "mov %0, r3"
        : "=r"(var_sl)
        : "r"(temp_r0_2)
        : "r3", "cc");
    sp58 = temp_r0_2;
block_3:
    header_mode2_base = (u8 *)0x02034B4C;
    header_mode2_offset = 0x27BE;
    asm volatile("" : "+r"(header_mode2_base), "+r"(header_mode2_offset));
    header_mode2_ptr = header_mode2_base + header_mode2_offset;
    if (*header_mode2_ptr == 0xE) {
        goto block_6;
    }
    header_value2_offset = 0xA074;
    asm volatile("" : "+r"(header_value2_offset));
    header_value2_ptr = header_mode2_base + header_value2_offset;
    var_r0 = *(u32 *)header_value2_ptr;
    goto block_7;
block_6:
    header_value14_base = (u8 *)0x02034B4C;
    header_value14_offset = 0xA074;
    asm volatile("" : "+r"(header_value14_base), "+r"(header_value14_offset));
    header_value14_ptr = header_value14_base + header_value14_offset;
    var_r0 = *(u32 *)header_value14_ptr * 2;
block_7:
    sp5C = var_r0;
    {
        register u32 initial_mode_r4 asm("r4") = temp_r0;

        asm volatile("" : "+r"(initial_mode_r4));
        if (initial_mode_r4 != 1) {
            goto block_15;
        }
    }
    {
        register u32 initial_count_r5 asm("r5") = 0;

        asm volatile("" : "+r"(initial_count_r5));
        sp6C = initial_count_r5;
    }
    {
        register u32 initial_index_r0 asm("r0") = 1;

        asm volatile("" : "+r"(initial_index_r0));
        var_r8 = initial_index_r0;
    }
    initial_roster_base = (u8 *)0x02027378;
    asm volatile("" : "+r"(initial_roster_base));
loop_9:
    {
        register u32 initial_index_view_r1 asm("r1") = var_r8;
        register u32 initial_offset_r0 asm("r0");

        asm volatile("" : "+r"(initial_index_view_r1));
        initial_offset_r0 = initial_index_view_r1 << 6;
        asm volatile("" : "+r"(initial_offset_r0));
        asm volatile("add %0, %1, %2"
                     : "=r"(temp_r7)
                     : "r"(initial_offset_r0), "r"(initial_roster_base)
                     : "cc");
    }
    asm volatile("ldrb %0, [%1]" : "=r"(initial_active) : "r"(temp_r7));
    if (initial_active == 0) {
        goto block_14;
    }
    {
        register u32 initial_flags asm("r1");

        asm volatile("ldrh %0, [%1, #2]"
                     : "=r"(initial_flags)
                     : "r"(temp_r7)
                     : "memory");
        if (4 & initial_flags) {
            goto block_14;
        }
    }
    {
        register u32 initial_value_r0 asm("r0") =
            M2C_FIELD(temp_r7, u32 *, 4);
        register u32 initial_gain_r3 asm("r3") = sp58;

        asm volatile("" : "+r"(initial_value_r0), "+r"(initial_gain_r3));
        temp_r0_4 = initial_value_r0 + initial_gain_r3;
    }
    M2C_FIELD(temp_r7, u32 *, 4) = temp_r0_4;
    if (temp_r0_4 <= 0x05F5E0FFU) {
        goto block_13;
    }
    M2C_FIELD(temp_r7, u32 *, 4) = 0x05F5E0FFU;
block_13:
    sp6C = (s32) (u8) (sp6C + 1);
block_14:
    temp_r0_5 = var_r8 + 1;
    var_r8 = temp_r0_5;
    if ((u32) temp_r0_5 <= 0x34U) {
        goto loop_9;
    }
block_15:
    {
        register u32 scan_zero_r4 asm("r4") = 0;

        asm volatile("" : "+r"(scan_zero_r4));
        var_r8_2 = scan_zero_r4;
    }
loop_16:
    temp_r5 = 0x02034B4C;
    owner_map_offset = 0x2700;
    asm volatile("" : "+r"(temp_r5), "+r"(owner_map_offset));
    owner_map_ptr = (u8 *)(temp_r5 + owner_map_offset);
    owner_map_ptr += var_r8_2;
    temp_r5 = *owner_map_ptr;
    active_base = (u8 *)0x020218E4;
    active_offset = 0x690C;
    asm volatile("" : "+r"(active_base), "+r"(active_offset));
    active_sum = active_base + active_offset;
    active_ptr = (u8 *)(temp_r5 + (u32)active_sum);
    active_value = *active_ptr;
    {
        register u32 scan_successor_r4 asm("r4") = var_r8_2 + 1;

        asm volatile("" : "+r"(scan_successor_r4));
        sp70 = scan_successor_r4;
    }
    asm volatile("" : "+r"(var_r8_2));
    if (active_value != 0) {
        goto block_18;
    }
    goto block_73;
block_18:
    temp_r2 = *active_ptr;
    temp_r0_6 = (temp_r2 << 3) - temp_r2;
    temp_r0_6 <<= 4;
    roster_base = (u8 *)0x020218E4;
    asm volatile("" : "+r"(roster_base));
    roster_base += 4;
    asm volatile("add %0, %1, %2"
                 : "=r"(temp_r6)
                 : "r"(temp_r0_6), "r"(roster_base)
                 : "cc");
    {
        register u32 scan_index_r1 asm("r1") = var_r8_2;

        asm volatile("" : "+r"(scan_index_r1));
        temp_r0_7 =
            (((s32)(((s32)scan_index_r1 * 4) + var_r8_2) * 8)
             - scan_index_r1) * 0x10;
    }
    {
        register u8 *record_base asm("r4") = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(record_base));
        asm volatile("add %0, %1, %2"
                     : "=r"(var_r3)
                     : "r"(temp_r0_7), "r"(record_base)
                     : "cc");
    }
    temp_r0_8 = M2C_FIELD(temp_r5, u8 *, 0x0203EE68);
    if (temp_r2 == temp_r0_8) {
        goto block_20;
    }
    goto block_44;
block_20:
    {
        register u32 record_flags_r1 asm("r1") =
            M2C_FIELD(var_r3, u16 *, 4);
        register u32 flag_r2 asm("r2") = 8;
        register u32 test_r0 asm("r0") = 8;
        asm volatile("" : "+r"(record_flags_r1), "+r"(flag_r2),
                     "+r"(test_r0));
        if (!(test_r0 & record_flags_r1)) {
            goto block_23;
        }
        M2C_FIELD(temp_r6, u16 *, 4) =
            (u16) (M2C_FIELD(temp_r6, u16 *, 4) | flag_r2);
    }
    {
        register u32 call_arg_r0 asm("r0") = temp_r5;
        asm volatile("" : "+r"(call_arg_r0));
        sp7C = var_r3;
        func_080E6020_wide(call_arg_r0);
    }
    goto block_29;
block_23:
    if (temp_r0 != 1) {
        goto block_30;
    }
    temp_r0_9 = M2C_FIELD(temp_r6, u8 *, 2) << 6;
    battle_base = (u8 *)0x020218E4;
    battle_offset = 0x5A94;
    asm volatile("" : "+r"(battle_base), "+r"(battle_offset));
    battle_sum = battle_base + battle_offset;
    temp_r7_2 = (u8 *)(temp_r0_9 + (u32)battle_sum);
    {
        register u32 active_value_r1 asm("r1") =
            M2C_FIELD(temp_r6, u16 *, 0x10);
        register s32 active_signed_r0 asm("r0");

        asm volatile("" : "+r"(active_value_r1));
        asm volatile(".syntax unified\n\t"
                     "movs r4, #16\n\t"
                     "ldrsh r0, [%1, r4]\n\t"
                     ".syntax divided"
                     : "=r"(active_signed_r0)
                     : "r"(temp_r6)
                     : "r4", "cc");
        if (active_signed_r0 > 0xC7) {
            goto block_26;
        }
        active_signed_r0 = active_value_r1 + 1;
        asm volatile("" : "+r"(active_signed_r0));
        M2C_FIELD(temp_r6, u16 *, 0x10) =
            (u16) active_signed_r0;
    }
block_26:
    temp_r0_9 = M2C_FIELD(temp_r7_2, u32 *, 4) + var_sl;
    M2C_FIELD(temp_r7_2, u32 *, 4) = temp_r0_9;
    if (temp_r0_9 <= 0x05F5E0FFU) {
        goto block_28;
    }
    M2C_FIELD(temp_r7_2, u32 *, 4) = 0x05F5E0FFU;
block_28:
    {
        register void *call_arg0_r0 asm("r0") = temp_r6;
        register void *call_arg1_r1 asm("r1") = temp_r7_2;
        asm volatile("" : "+r"(call_arg0_r0), "+r"(call_arg1_r1));
        sp7C = var_r3;
        func_080E5880(call_arg0_r0, call_arg1_r1);
    }
block_29:
    var_r3 = sp7C;
block_30:
    if (*temp_r6 == *var_r3) {
        goto block_34;
    }
    sp7C = var_r3;
    temp_r4 = func_080E5354();
    var_r3 = sp7C;
    temp_r0_10 = func_080E5354(*var_r3);
    temp_r4 <<= 0x18;
    temp_r0_10 <<= 0x18;
    var_r3 = sp7C;
    if (temp_r4 != temp_r0_10) {
        goto block_38;
    }
    temp_r1 = *var_r3;
    if (*temp_r6 == temp_r1) {
        goto block_34;
    }
    *temp_r6 = temp_r1;
    {
        register u32 call_arg1_r1 asm("r1") =
            M2C_FIELD(temp_r6, u8 *, 2) << 6;
        register u8 *call_arg0_r0 asm("r0") = (u8 *)0x02027378;
        asm volatile("" : "+r"(call_arg1_r1), "+r"(call_arg0_r0));
        call_arg1_r1 += (u32)call_arg0_r0;
        call_arg0_r0 = temp_r6;
        asm volatile("" : "+r"(call_arg0_r0), "+r"(call_arg1_r1));
        sp7C = var_r3;
        func_080E5880(call_arg0_r0, (void *)call_arg1_r1);
    }
    var_r3 = sp7C;
block_34:
    {
        register u32 record_value_r4 asm("r4") =
            M2C_FIELD(var_r3, u16 *, 6);
        register u32 slot_r2 asm("r2") = 6;
        register s32 record_signed_r1 asm("r1");
        register u32 active_offset_r3 asm("r3");
        register s32 active_signed_r0 asm("r0");

        asm volatile("" : "+r"(record_value_r4));
        asm volatile("" : "+r"(slot_r2));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(record_signed_r1)
                     : "r"(var_r3), "r"(slot_r2)
                     : "memory");
        asm volatile("" : "+r"(record_signed_r1));
        slot_r2 = M2C_FIELD(temp_r6, u16 *, 0x3A);
        asm volatile("" : "+r"(slot_r2));
        asm volatile("" : "=r"(active_offset_r3));
        active_signed_r0 = M2C_FIELD(temp_r6, s16 *, 0x3A);
        asm volatile("" : "+r"(active_signed_r0));
        if (record_signed_r1 > active_signed_r0) {
            goto block_37;
        }
        M2C_FIELD(temp_r6, u16 *, 6) = record_value_r4;
        {
            register u32 next_r4 asm("r4") = var_r8_2;
            asm volatile("" : "+r"(next_r4));
            next_r4 += 1;
            sp70 = next_r4;
        }
        goto block_73;
block_37:
        M2C_FIELD(temp_r6, u16 *, 6) = slot_r2;
        {
            register u32 next_r5 asm("r5") = var_r8_2;
            asm volatile("" : "+r"(next_r5));
            next_r5 += 1;
            sp70 = next_r5;
        }
        goto block_73;
    }
block_38:
    {
    register u32 scan_counter_r7 asm("r7") = 0;
    asm volatile("" : "+r"(scan_counter_r7));
    scan_map_base = (u8 *)0x02034B4C;
    scan_map_offset = 0x2700;
    asm volatile("" : "+r"(scan_map_base), "+r"(scan_map_offset));
    scan_base = scan_map_base + scan_map_offset;
    {
        register u32 selected_address_r3 asm("r3") = 0x02037252;
        register u8 *selected_ptr_r1 asm("r1");
        register u32 first_value_r0 asm("r0");
        register u32 selected_value_r1 asm("r1");
        asm volatile("" : "+r"(selected_address_r3));
        selected_ptr_r1 = temp_r5 + selected_address_r3;
        asm volatile("" : "+r"(selected_ptr_r1));
        first_value_r0 = *scan_base;
        asm volatile("" : "+r"(first_value_r0));
        {
            register u32 next_r4 asm("r4") = var_r8_2;
            asm volatile("" : "+r"(next_r4));
            next_r4 += 1;
            sp70 = next_r4;
        }
        selected_value_r1 = *selected_ptr_r1;
        asm volatile("" : "+r"(selected_value_r1));
        if (first_value_r0 == selected_value_r1) {
            goto block_42;
        }
    }
    asm volatile("");
    scan_selected = (u8 *)0x02034B4C;
    scan_selected_offset = 0x2706;
    asm volatile("" : "+r"(scan_selected), "+r"(scan_selected_offset));
    scan_selected_sum = scan_selected + scan_selected_offset;
    scan_selected = (u8 *)((u32)temp_r5 + (u32)scan_selected_sum);
loop_40:
    {
        register u32 next_r0 asm("r0") = scan_counter_r7 + 1;
        asm volatile("" : "+r"(next_r0));
        next_r0 <<= 0x18;
        scan_counter_r7 = next_r0 >> 0x18;
        asm volatile("" : "+r"(scan_counter_r7));
    }
    if (scan_counter_r7 > 5U) {
        goto block_42;
    }
    {
        register u32 scan_work_r0 asm("r0");
        register u32 scan_selected_value_r4 asm("r4");

        asm volatile("add %0, %1, %2"
                     : "=r"(scan_work_r0)
                     : "r"(scan_counter_r7), "r"(scan_base)
                     : "cc");
        scan_work_r0 = *(u8 *)scan_work_r0;
        asm volatile("" : "+r"(scan_work_r0));
        scan_selected_value_r4 = *scan_selected;
        asm volatile("" : "+r"(scan_selected_value_r4));
        if (scan_work_r0 != scan_selected_value_r4) {
            goto loop_40;
        }
    }
block_42:
    {
        register s32 work_r0 asm("r0");
        register u8 *record_base_r5 asm("r5");
        register u8 *record_r3 asm("r3");
        register s32 work_r1 asm("r1");
        register u32 slot_r2 asm("r2");
        register u32 slot_r4 asm("r4");
        asm volatile(
            "lsl %0, %1, #2\n\t"
            "add %0, %0, %1\n\t"
            "lsl %0, %0, #3\n\t"
            "sub %0, %0, %1\n\t"
            "lsl %0, %0, #4"
            : "=&r"(work_r0)
            : "r"(scan_counter_r7));
        record_base_r5 = (u8 *)0x02034B4C;
        asm volatile("" : "+r"(record_base_r5));
        record_r3 = (u8 *)(work_r0 + (u32)record_base_r5);
        asm volatile("" : "+r"(record_r3));
        work_r0 = 0x3A;
        asm volatile("" : "+r"(work_r0));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(work_r1)
                     : "r"(temp_r6), "r"(work_r0));
        slot_r2 = 6;
        asm volatile("" : "+r"(slot_r2));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(work_r0)
                     : "r"(record_r3), "r"(slot_r2));
        work_r0 *= work_r1;
        slot_r4 = 0x3A;
        asm volatile("" : "+r"(slot_r4));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(work_r1)
                     : "r"(record_r3), "r"(slot_r4));
        M2C_FIELD(temp_r6, u16 *, 6) =
            func_080ECD98_wide(work_r0, work_r1);
    }
    goto block_73;
    }
block_44:
    if (temp_r0_8 != 0) {
        goto block_46;
    }
    goto block_73;
block_46:
    if (8 & M2C_FIELD(var_r3, u16 *, 4)) {
        goto block_50;
    }
    if (temp_r0 != 1) {
        goto block_50;
    }
    {
        register u32 battle_index_r0 asm("r0") =
            M2C_FIELD(temp_r6, u8 *, 2) << 6;
        asm volatile("" : "+r"(battle_index_r0));
        battle2_base = (u8 *)0x020218E4;
        battle2_offset = 0x5A94;
        asm volatile("" : "+r"(battle2_base), "+r"(battle2_offset));
        battle2_sum = battle2_base + battle2_offset;
        temp_r7_3 = (u8 *)(battle_index_r0 + (u32)battle2_sum);
    }
    temp_r0_11 = M2C_FIELD(temp_r7_3, u32 *, 4) + var_sl;
    M2C_FIELD(temp_r7_3, u32 *, 4) = temp_r0_11;
    if (temp_r0_11 <= 0x05F5E0FFU) {
        goto block_50;
    }
    M2C_FIELD(temp_r7_3, u32 *, 4) = 0x05F5E0FFU;
block_50:
    {
        register u32 record_offset_r0 asm("r0") =
            M2C_FIELD(temp_r5, u8 *, 0x0203EE68) * 0x70;
        asm volatile("" : "+r"(record_offset_r0));
        temp_r7_3 = (u8 *)0x020218E8;
        asm volatile("" : "+r"(temp_r7_3));
        temp_r6_2 = (u8 *)(record_offset_r0 + (u32)temp_r7_3);
    }
    if (*temp_r6_2 == *var_r3) {
        goto block_54;
    }
    sp7C = var_r3;
    temp_r4_2 = func_080E5354();
    var_r3 = sp7C;
    temp_r0_10 = func_080E5354(*var_r3);
    temp_r4_2 <<= 0x18;
    temp_r0_10 <<= 0x18;
    var_r3 = sp7C;
    if (temp_r4_2 != temp_r0_10) {
        goto block_58;
    }
    temp_r1_2 = M2C_FIELD(var_r3, u8 *, 0);
    if (*temp_r6_2 == temp_r1_2) {
        goto block_54;
    }
    *temp_r6_2 = temp_r1_2;
    {
        register u32 call_arg1_r1 asm("r1") =
            M2C_FIELD(temp_r6_2, u8 *, 2) << 6;
        register u32 call_offset_r4 asm("r4") = 0x5A90;
        register u8 *call_arg0_r0 asm("r0");
        asm volatile("" : "+r"(call_arg1_r1), "+r"(call_offset_r4));
        call_arg0_r0 = temp_r7_3 + call_offset_r4;
        asm volatile("" : "+r"(call_arg0_r0));
        call_arg1_r1 += (u32)call_arg0_r0;
        call_arg0_r0 = temp_r6_2;
        asm volatile("" : "+r"(call_arg0_r0), "+r"(call_arg1_r1));
        sp7C = var_r3;
        func_080E5880(call_arg0_r0, (void *)call_arg1_r1);
    }
    var_r3 = sp7C;
block_54:
    {
        register u32 record_value_r4 asm("r4") =
            M2C_FIELD(var_r3, u16 *, 6);
        register u32 slot_r5 asm("r5") = 6;
        register s32 record_signed_r1 asm("r1");
        register u32 active_value_r2 asm("r2");
        register s32 active_signed_r0 asm("r0");

        asm volatile("" : "+r"(record_value_r4));
        asm volatile("" : "+r"(slot_r5));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(record_signed_r1)
                     : "r"(var_r3), "r"(slot_r5));
        active_value_r2 = M2C_FIELD(temp_r6_2, u16 *, 0x3A);
        asm volatile("" : "+r"(active_value_r2));
        asm volatile("" : "=r"(slot_r5));
        active_signed_r0 = M2C_FIELD(temp_r6_2, s16 *, 0x3A);
        asm volatile("" : "+r"(active_signed_r0));
        if (record_signed_r1 > active_signed_r0) {
            goto block_57;
        }
        M2C_FIELD(temp_r6_2, u16 *, 6) = record_value_r4;
        {
            register u32 next_r0 asm("r0") = var_r8_2;
            asm volatile("" : "+r"(next_r0));
            next_r0 += 1;
            sp70 = next_r0;
        }
        goto block_63;
block_57:
        M2C_FIELD(temp_r6_2, u16 *, 6) = active_value_r2;
        {
            register u32 next_r1 asm("r1") = var_r8_2;
            asm volatile("" : "+r"(next_r1));
            next_r1 += 1;
            sp70 = next_r1;
        }
        goto block_63;
    }
block_58:
    var_r7_2 = 0;
    scan2_map_base = (u8 *)0x02034B4C;
    scan2_map_offset = 0x2700;
    asm volatile("" : "+r"(scan2_map_base), "+r"(scan2_map_offset));
    scan2_base = scan2_map_base + scan2_map_offset;
    {
        register u8 *selected_ptr_r1 asm("r1");
        register u32 first_value_r0 asm("r0") = 0x02037252;
        register u32 selected_value_r1 asm("r1");
        asm volatile("" : "+r"(first_value_r0));
        selected_ptr_r1 = temp_r5 + first_value_r0;
        asm volatile("" : "+r"(selected_ptr_r1));
        first_value_r0 = *scan2_base;
        asm volatile("" : "+r"(first_value_r0));
        {
            register u32 next_r3 asm("r3") = var_r8_2;
            asm volatile("" : "+r"(next_r3));
            next_r3 += 1;
            sp70 = next_r3;
        }
        selected_value_r1 = *selected_ptr_r1;
        asm volatile("" : "+r"(selected_value_r1));
        if (first_value_r0 == selected_value_r1) {
            goto block_62;
        }
    }
    asm volatile("");
    scan2_selected_base = (u8 *)0x02034B4C;
    scan2_selected = (u8 *)0x2706;
    asm volatile("" : "+r"(scan2_selected_base), "+r"(scan2_selected));
    scan2_selected_sum = scan2_selected_base + (u32)scan2_selected;
    scan2_selected = (u8 *)((u32)temp_r5 + (u32)scan2_selected_sum);
loop_60:
    var_r7_2 += 1;
    if ((u32) var_r7_2 > 5U) {
        goto block_62;
    }
    if (*(u8 *)(var_r7_2 - (0U - (u32)scan2_base)) !=
            *scan2_selected) {
        goto loop_60;
    }
block_62:
    {
        register s32 work_r0 asm("r0") = var_r7_2 * 0x270;
        register u8 *work_r4 asm("r4") = (u8 *)0x02034B4C;
        register u32 slot_r5 asm("r5");
        register s32 work_r1 asm("r1");
        register u32 slot_r2 asm("r2");
        asm volatile("" : "+r"(work_r0), "+r"(work_r4));
        temp_r3_2 = (u8 *)(work_r0 + (u32)work_r4);
        asm volatile("" : "+r"(temp_r3_2));
        slot_r5 = 0x3A;
        asm volatile("" : "+r"(slot_r5));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(work_r1)
                     : "r"(temp_r6_2), "r"(slot_r5));
        slot_r2 = 6;
        asm volatile("" : "+r"(slot_r2));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(work_r0)
                     : "r"(temp_r3_2), "r"(slot_r2));
        work_r0 *= work_r1;
        work_r4 = (u8 *)0x3A;
        asm volatile("" : "+r"(work_r4));
        asm volatile("ldrsh %0, [%1, %2]"
                     : "=r"(work_r1)
                     : "r"(temp_r3_2), "r"(work_r4));
        sp7C = temp_r3_2;
        M2C_FIELD(temp_r6_2, u16 *, 6) =
            func_080ECD98_wide(work_r0, work_r1);
    }
    var_r3 = sp7C;
block_63:
    {
        register u32 record_flags_r1 asm("r1") =
            M2C_FIELD(var_r3, u16 *, 4);
        register u32 flag_r2 asm("r2") = 8;
        register u32 test_r0 asm("r0") = 8;
        asm volatile("" : "+r"(record_flags_r1), "+r"(flag_r2),
                     "+r"(test_r0));
        if (!(test_r0 & record_flags_r1)) {
            goto block_65;
        }
        M2C_FIELD(temp_r6_2, u16 *, 4) =
            (u16)(M2C_FIELD(temp_r6_2, u16 *, 4) | flag_r2);
    }
    goto block_73;
block_65:
    if (temp_r0 != 1) {
        goto block_73;
    }
    if ((s32) (s16) M2C_FIELD(temp_r6_2, u16 *, 0x10) > 0xC7) {
        goto block_68;
    }
    M2C_FIELD(temp_r6_2, u16 *, 0x10) = (u16) (M2C_FIELD(temp_r6_2, u16 *, 0x10) + 1);
block_68:
    temp_r0_13 = M2C_FIELD(temp_r6_2, u8 *, 2);
    if (temp_r0_13 == 0) {
        goto block_71;
    }
    {
        register u32 reward_offset_r0 asm("r0") = temp_r0_13 << 6;
        register u8 *reward_base_r1 asm("r1");
        asm volatile("" : "+r"(reward_offset_r0));
        reward_base_r1 = (u8 *)0x02027378;
        asm volatile("" : "+r"(reward_base_r1));
        var_r7_3 = (u8 *)(reward_offset_r0 + (u32)reward_base_r1);
    }
    goto block_72;
block_71:
    var_r7_3 = NULL;
block_72:
    func_080E5880(temp_r6_2, var_r7_3);
block_73:
    temp_r0_14 = (u8) sp70;
    var_r8_2 = temp_r0_14;
    if ((u32) temp_r0_14 > 5U) {
        goto block_75;
    }
    goto loop_16;
block_75:
    func_080986B4(0);
    {
        register s32 initial_mode_r4 asm("r4") = temp_r0;

        asm volatile("" : "+r"(initial_mode_r4));
        if (initial_mode_r4 == 1) {
            goto block_81;
        }
        if (initial_mode_r4 > 1) {
            goto block_79;
        }
        if (initial_mode_r4 == 0) {
            goto block_225;
        }
    }
    return;
block_79:
    {
        register s32 final_mode_r5 asm("r5") = temp_r0;

        asm volatile("" : "+r"(final_mode_r5));
        if (final_mode_r5 == 2) {
            goto block_235;
        }
    }
    return;
block_81:
    func_08098BB4(0x08003C22);
    func_080E5E64(sp5C);
    func_080986B4(0);
    func_08098248(0x081075C0, 0, 0);
    {
    register s32 block81_zero_r4 asm("r4") = 0;
    register volatile s32 *block81_outgoing asm("sp");

    block81_outgoing[0] = block81_zero_r4;
    func_080984C4_4(var_sl, 7, 2, 0);
    func_08098BB4(0x08003B04);
    if (sp6C == 0) {
        goto block_83;
    }
    func_080986B4(0);
    func_08098248(0x081075EC, 0, 0);
    block81_outgoing[0] = block81_zero_r4;
    func_080984C4_4(sp58, 7, 2, 0);
    func_08098BB4(0x08003B04);
block_83:
    func_080986B4(0);
    func_08098248(0x0810760C, 0, 0);
    block81_outgoing[0] = block81_zero_r4;
    func_080984C4_4(sp5C, 7, 2, 0);
    }
    func_08098BB4(0x08003B12);
    mode_base = (u8 *)0x02034B4C;
    mode_offset = 0x27BE;
    asm volatile("" : "+r"(mode_base), "+r"(mode_offset));
    mode_ptr = mode_base + mode_offset;
    if ((u32) (u8) (*mode_ptr - 9) <= 1U) {
        goto block_86;
    }
    if (((u32) (func_080ECD5C(*(s32 *)0x03000010) * 0xA) >> 0xF) == 0) {
        goto block_86;
    }
    goto block_100;
block_86:
    if (*mode_ptr != 0xA) {
        goto block_88;
    }
    mode_index = (u32) (func_080ECD5C(*(u32 *)0x03000010) *
        mode_base[0x27C0]) >> 0xF;
    mode_table_offset = 0x27C1;
    asm volatile("" : "+r"(mode_table_offset));
    mode_table = mode_base + mode_table_offset;
    mode_index += (u32)mode_table;
    var_r4 = *(u8 *)mode_index;
    goto block_97;
block_88:
    var_r4_2 = 0;
    var_r8_3 = 0;
    catalog_base = (u8 *)0x087B9454;
    catalog_coord_base = (u8 *)0x0203055C;
    asm volatile("" : "+r"(catalog_base), "+r"(catalog_coord_base));
    catalog_row_seed = catalog_coord_base[4];
    asm volatile("" : "+r"(catalog_row_seed));
    catalog_row100 = catalog_row_seed;
    catalog_address = 0x64;
    catalog_row100 *= catalog_address;
    catalog_page_seed = catalog_coord_base[3];
    catalog_address = catalog_page_seed << 5;
    catalog_address -= catalog_page_seed;
    catalog_address <<= 2;
    catalog_address += catalog_page_seed;
    catalog_page2000 = catalog_address << 4;
loop_89:
    catalog_outer_seed = var_r8_3;
    catalog_address = catalog_outer_seed << 4;
    catalog_address += catalog_row100;
    catalog_address += catalog_page2000;
    catalog_address += (u32)catalog_base;
    temp_r0_15 = (u8 *)catalog_address;
    temp_r1_3 = M2C_FIELD(temp_r0_15, u8 *, 4);
    if (temp_r1_3 == 0) {
        goto block_92;
    }
    if (M2C_FIELD(temp_r0_15, u8 *, 7) != 0) {
        goto block_92;
    }
    sp14[var_r4_2] = temp_r1_3;
    var_r4_2 += 1;
block_92:
    temp_r0_16 = var_r8_3 + 1;
    var_r8_3 = temp_r0_16;
    if ((u32) temp_r0_16 <= 5U) {
        goto loop_89;
    }
    if (var_r4_2 == 0) {
        goto block_96;
    }
    var_r4 = sp14[(u32) (func_080ECD5C(*(u32 *)0x03000010) * var_r4_2) >> 0xF];
    goto block_97;
block_96:
    var_r4 = 0;
block_97:
    if (var_r4 == 0) {
        goto block_100;
    }
    func_080986B4(0);
    func_08098BB4(0x08003B46);
    {
        register s32 *message_table_r1 asm("r1") =
            (s32 *)0x087EDD54;
        register u32 message_address_r0 asm("r0");

        asm volatile("" : "+r"(message_table_r1));
        message_address_r0 = var_r4 << 2;
        message_address_r0 += (u32)message_table_r1;
        message_address_r0 = *(u32 *)message_address_r0;
        func_08098248(message_address_r0, 2, 0);
    }
    func_08098BB4(0x08003B9C);
    if ((func_080E5DC4(var_r4) << 0x18) != 0) {
        goto block_100;
    }
    func_080986B4(0);
    func_08098BB4(0x08003B68);
block_100:
    mode2_root = (u8 *)0x02034B4C;
    mode2_offset = 0x27BE;
    asm volatile("" : "+r"(mode2_root), "+r"(mode2_offset));
    mode2_ptr = mode2_root + mode2_offset;
    if ((u32) (u8) (*mode2_ptr - 0xB) <= 1U) {
        goto block_103;
    }
    if (((u32) (func_080ECD5C(*(u32 *)0x03000010) * 6) >> 0xF) == 0) {
        goto block_103;
    }
    goto block_125;
block_103:
    if (*mode2_ptr != 0xC) {
        goto block_107;
    }
    {
        register u32 mode2_zero_r3 asm("r3") = 0;

        asm volatile("" : "+r"(mode2_zero_r3));
        var_r8_4 = mode2_zero_r3;
    }
    mode2_table_root = (u8 *)0x02034B4C;
    mode2_table_offset = 0x27C1;
    asm volatile("" : "+r"(mode2_table_root), "+r"(mode2_table_offset));
    mode2_table = mode2_table_root + mode2_table_offset;
loop_105:
    sp14[var_r8_4] =
        *(u8 *)((u32)var_r8_4 + (u32)mode2_table);
    temp_r0_17 = (u8) (var_r8_4 + 1);
    var_r8_4 = temp_r0_17;
    if ((u32) temp_r0_17 <= 5U) {
        goto loop_105;
    }
    asm volatile("" : "=r"(mode2_table_root));
    mode2_table_root = (u8 *)0x02034B4C;
    asm volatile("" : "+r"(mode2_table_root));
    mode2_table_offset = 0x27C0;
    mode2_count_ptr = mode2_table_root + mode2_table_offset;
    var_r4_3 = *mode2_count_ptr;
    goto block_112;
block_107:
    var_r4_3 = 0;
    var_r8_5 = 0;
    catalog_base = (u8 *)0x087B9454;
    catalog_coord_base = (u8 *)0x0203055C;
    asm volatile("" : "+r"(catalog_base), "+r"(catalog_coord_base));
    catalog_row_seed = catalog_coord_base[4];
    asm volatile("" : "+r"(catalog_row_seed));
    catalog_row100 = catalog_row_seed;
    catalog_address = 0x64;
    catalog_row100 *= catalog_address;
    catalog_page_seed = catalog_coord_base[3];
    catalog_address = catalog_page_seed << 5;
    catalog_address -= catalog_page_seed;
    catalog_address <<= 2;
    catalog_address += catalog_page_seed;
    catalog_page2000 = catalog_address << 4;
loop_108:
    catalog_outer_seed = var_r8_5;
    catalog_address = catalog_outer_seed << 4;
    catalog_address += catalog_row100;
    catalog_address += catalog_page2000;
    catalog_address += (u32)catalog_base;
    temp_r0_18 = (u8 *)catalog_address;
    temp_r1_4 = M2C_FIELD(temp_r0_18, u8 *, 4);
    if (temp_r1_4 == 0) {
        goto block_111;
    }
    if (M2C_FIELD(temp_r0_18, u8 *, 7) != 0) {
        goto block_111;
    }
    sp14[var_r4_3] = temp_r1_4;
    var_r4_3 += 1;
block_111:
    temp_r0_19 = var_r8_5 + 1;
    var_r8_5 = temp_r0_19;
    if ((u32) temp_r0_19 <= 5U) {
        goto loop_108;
    }
block_112:
    var_r5 = 0;
    if (var_r4_3 == 0) {
        goto block_122;
    }
    {
    register u8 *reward_table_r7 asm("r7") = (u8 *)0x087B1E05;
    register u8 *scratch_base_r6 asm("r6");
    register u32 chosen_r3 asm("r3");
    asm volatile("" : "+r"(reward_table_r7));
    asm volatile("add %0, sp, #28" : "=r"(scratch_base_r6));
loop_114:
    {
        register u32 selected_r0 asm("r0") =
            func_080ECD5C(*(u32 *)0x03000010);
        selected_r0 *= var_r4_3;
        selected_r0 >>= 0xF;
        selected_r0 <<= 0x18;
        chosen_r3 = selected_r0 >> 0x18;
        asm volatile("" : "+r"(chosen_r3));
    }
    temp_r1_5 = sp14[chosen_r3];
    var_r8_6 = 0;
    temp_r2_2 = temp_r1_5 * 0xC;
loop_115:
    {
        register u32 reward_address_r0 asm("r0") =
            var_r8_6 + temp_r2_2;

        asm volatile("add %0, %0, %1"
                     : "+r"(reward_address_r0)
                     : "r"(reward_table_r7)
                     : "cc");
        temp_r1_5 = *(u8 *)reward_address_r0;
    }
    if (temp_r1_5 == 0) {
        goto block_117;
    }
    scratch_base_r6[var_r5] = temp_r1_5;
    var_r5 += 1;
block_117:
    temp_r0_20 = var_r8_6 + 1;
    var_r8_6 = temp_r0_20;
    if ((u32) temp_r0_20 <= 1U) {
        goto loop_115;
    }
    if (var_r5 != 0) {
        goto block_123;
    }
    var_r8_7 = chosen_r3;
    asm volatile("" : "+r"(var_r8_7));
    chosen_r3 = var_r4_3 - 1;
    asm volatile("" : "+r"(chosen_r3));
    {
    register s32 bound_r4 asm("r4") = chosen_r3;
    asm volatile("" : "+r"(bound_r4));
    if ((s32) var_r8_7 >= bound_r4) {
        goto block_121;
    }
loop_120:
    {
        register u8 *dest_r2 asm("r2");
        register u32 next_r1 asm("r1");
        register u8 *source_r0 asm("r0");
        register u32 value_r0 asm("r0");
        asm volatile("mov %0, sp" : "=r"(dest_r2));
        dest_r2 += var_r8_7;
        dest_r2 += 0x14;
        asm volatile("" : "+r"(dest_r2));
        next_r1 = var_r8_7 + 1;
        asm volatile("" : "+r"(next_r1));
        asm volatile("mov %0, sp" : "=r"(source_r0));
        source_r0 += next_r1;
        source_r0 += 0x14;
        asm volatile("" : "+r"(source_r0));
        value_r0 = *source_r0;
        asm volatile("" : "+r"(value_r0));
        *dest_r2 = value_r0;
        next_r1 <<= 0x18;
        next_r1 >>= 0x18;
        var_r8_7 = next_r1;
        asm volatile("" : "+r"(var_r8_7));
    }
    if ((s32) var_r8_7 < (s32)chosen_r3) {
        goto loop_120;
    }
block_121:
    {
        register u32 normalized_bound_r0 asm("r0") = bound_r4 << 24;

        asm volatile("" : "+r"(normalized_bound_r0));
        var_r4_3 = normalized_bound_r0 >> 24;
    }
    }
    if (var_r4_3 != 0) {
        goto loop_114;
    }
    }
block_122:
    if (var_r5 == 0) {
        goto block_125;
    }
block_123:
    temp_r4_3 = scratch.bytes[(u32) (func_080ECD5C(*(u32 *)0x03000010) * var_r5) >> 0xF];
    func_080986B4(0);
    func_08098248(0x0810761C, 0, 0);
    {
        register s32 *message_table_r1 asm("r1") =
            (s32 *)0x087EEE60;
        register u32 message_address_r0 asm("r0");

        asm volatile("" : "+r"(message_table_r1));
        message_address_r0 = temp_r4_3 << 2;
        message_address_r0 += (u32)message_table_r1;
        message_address_r0 = *(u32 *)message_address_r0;
        func_08098248(message_address_r0, 2, 0);
    }
    func_08098BB4(0x08003B9C);
    if ((func_080E5E0C(temp_r4_3, 1) << 0x18) != 0) {
        goto block_125;
    }
    func_080986B4(0);
    func_08098BB4(0x08003BE4);
block_125:
    state13_root = (u8 *)0x02034B4C;
    state13_offset = 0x27BE;
    asm volatile("" : "+r"(state13_root), "+r"(state13_offset));
    state13_root += state13_offset;
    if (*state13_root != 0xD) {
        goto block_137;
    }
    var_r7_4 = 0;
    {
        register u32 state13_outer_zero asm("r3") = 0;

        asm volatile("" : "+r"(state13_outer_zero));
        var_r8_8 = state13_outer_zero;
    }
    state13_catalog_seed = (u8 *)0x087B9454;
    asm volatile("" : "+r"(state13_catalog_seed));
    state13_catalog_base = state13_catalog_seed;
    state13_control = (u8 *)0x0203055C;
    {
        register u32 catalog_row_r1 asm("r1");
        register u32 catalog_hundred_r0 asm("r0");
        register u32 catalog_product_r5 asm("r5");

        catalog_row_r1 = state13_control[4];
        asm volatile("" : "+r"(catalog_row_r1));
        catalog_hundred_r0 = 100;
        catalog_product_r5 = catalog_row_r1;
        catalog_product_r5 *= catalog_hundred_r0;
        temp_r5_2 = catalog_product_r5;
        asm volatile("" : "+r"(catalog_product_r5));
    }
    state13_page_seed = state13_control[3];
    {
        register u32 catalog_plus8_r0 asm("r0") = 8;

        asm volatile("" : "+r"(catalog_plus8_r0));
        catalog_plus8_r0 += (u32)state13_catalog_base;
        var_sl = catalog_plus8_r0;
    }
    state13_work = state13_page_seed << 5;
    state13_work -= state13_page_seed;
    state13_work <<= 2;
    state13_work += state13_page_seed;
    temp_r6_3 = state13_work << 4;
loop_127:
    var_r5_2 = 0;
    {
        register u32 state13_outer_r1 asm("r1") = var_r8_8;

        asm volatile("" : "+r"(state13_outer_r1));
        temp_r4_4 = state13_outer_r1 << 4;
    }
    asm volatile("" : : "r"(temp_r4_4));
    temp_r3_5 = temp_r4_4 + temp_r5_2 + temp_r6_3 +
        (u32)state13_catalog_base;
    asm volatile("" : : "r"(temp_r3_5));
loop_128:
    if (M2C_FIELD(temp_r3_5, u8 *, 4) == 0) {
        goto block_132;
    }
    if (M2C_FIELD(temp_r3_5, u8 *, 7) != 0) {
        goto block_132;
    }
    temp_r0_21 = var_r5_2 + temp_r4_4 + temp_r5_2 + temp_r6_3;
    if (M2C_FIELD(temp_r0_21, u8 *, var_sl) == 0) {
        goto block_132;
    }
    {
        register u16 *scratch_store_r1 asm("r1");
        register u32 scratch_offset_r0 asm("r0");

        asm volatile("add %0, sp, #32" : "=r"(scratch_store_r1));
        scratch_offset_r0 = var_r7_4 << 1;
        scratch_store_r1 =
            (u16 *)((u8 *)scratch_store_r1 + scratch_offset_r0);
        scratch_offset_r0 = M2C_FIELD(temp_r0_21, u8 *, var_sl);
        *scratch_store_r1 = scratch_offset_r0;
    }
    var_r7_4 += 1;
block_132:
    var_r5_2 += 1;
    if ((u32) var_r5_2 <= 3U) {
        goto loop_128;
    }
    asm volatile("" : "+r"(var_r8_8));
    temp_r0_22 = var_r8_8 + 1;
    var_r8_8 = temp_r0_22;
    if ((u32) temp_r0_22 <= 5U) {
        goto loop_127;
    }
    if (var_r7_4 == 0) {
        goto block_137;
    }
    {
        register u16 *scratch_load_r4 asm("r4");
        register u32 scratch_index_r0 asm("r0");

        asm volatile("add %0, sp, #32" : "=r"(scratch_load_r4));
        scratch_index_r0 = func_080ECD5C(*(u32 *)0x03000010);
        scratch_index_r0 *= var_r7_4;
        scratch_index_r0 >>= 0xF;
        scratch_index_r0 <<= 1;
        scratch_load_r4 =
            (u16 *)((u8 *)scratch_load_r4 + scratch_index_r0);
        temp_r4_5 = *scratch_load_r4;
    }
    func_080986B4(0);
    func_08098248(0x08107638, 0, 0);
    func_08098248(D_087EE170[temp_r4_5], 2, 0);
    func_08098BB4(0x08003B9C);
    if ((func_080E5CE4(temp_r4_5, 1) << 0x18) != 0) {
        goto block_137;
    }
    func_080986B4(0);
    func_08098BB4(0x08003BA6);
block_137:
    {
        register u32 reward_zero_r2 asm("r2") = 0;
        register u32 reward_one_r3 asm("r3");

        sp60 = reward_zero_r2;
        asm volatile("mov %0, #1" : "=r"(reward_one_r3));
        var_r8_9 = reward_one_r3;
    }
loop_138:
    {
    register u32 outer_index asm("r4") = var_r8_9;
    register u32 record_offset asm("r0");
    register u8 *record_base asm("r1");
    register u8 *record asm("r7");
    register u32 active asm("r0");

    record_offset = outer_index << 6;
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x494B\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x1847\n\t"
        ".endm");
    record_base = (u8 *)0x02027378;
    record = (u8 *)(record_offset + (u32)record_base);
    asm volatile(".purgem ldr\n\t.purgem add");
    asm volatile("ldrb %0, [%1]" : "=r"(active) : "r"(record));
    outer_index += 1;
    sp70 = outer_index;
    temp_r7_4 = record;
    if (active == 0) {
        goto block_220;
    }
    {
    register u32 table_value asm("r2") = 0x087B77C8;
    register u8 *status_ptr asm("r1") = record;
    register u32 table_index asm("r0");

    asm volatile("" : "+r"(table_value));
    status_ptr += 0x30;
    table_index = *status_ptr;
    table_index <<= 2;
    table_index += table_value;
    table_value = *(u32 *)table_index;
    sp74 = status_ptr;
    if (table_value == 0) {
        goto block_220;
    }
    if ((u32) M2C_FIELD(record, u32 *, 4) < table_value) {
        goto block_220;
    }
    }
    }
loop_141:
    if (sp60 != 0) {
        goto block_143;
    }
    func_08098BB4(0x08003DE6);
    func_08094484(0x08359850, 0x0835985C, 0, 0x18, 0x28, 0x3C2, 0xE, 8,
        sp60);
    sp60 = 1;
    func_080EB888();
block_143:
    *(s8 *)0x02032EF8 = 0x34;
    func_08092E84(0x34);
    func_08098BB4(0x08003DF9);
    func_080986B4(0);
    func_08098248(func_080E7B64(*temp_r7_4), 2, 0);
    func_08098BB4(0x08003B1C);
    func_080984C4(*sp74 + 1, 2, 1, 0, 0);
    func_08098BB4(0x08003B3E);
    func_0809A9C8(*temp_r7_4, 2, 0U, 0x3C2, 0xE, 0x02002880);
    {
    register u8 *status_ptr_r0 asm("r0") = temp_r7_4;
    register u32 status_value_r1 asm("r1");

    status_ptr_r0 += 0x32;
    status_value_r1 = *status_ptr_r0;
    sp78 = status_ptr_r0;
    if (status_value_r1 <= 4U) {
        goto block_154;
    }
    }
    M2C_FIELD(temp_r7_4, u16 *, 0x2C) = 0U;
    M2C_FIELD(temp_r7_4, u16 *, 0x2E) = 0U;
    M2C_FIELD(temp_r7_4, u16 *, 0x2A) = 0U;
    M2C_FIELD(temp_r7_4, u16 *, 0x28) = 0U;
    M2C_FIELD(temp_r7_4, u16 *, 0x26) = 0U;
    if (*sp78 != 6) {
        goto block_154;
    }
    {
    register u32 reward_counter_r5 asm("r5") = 0;

    asm volatile("" : "+r"(reward_counter_r5));
loop_146:
    temp_r0_24 = (u32) (func_080ECD5C(*(u32 *)0x03000010) * 5) >> 0xF;
    if (temp_r0_24 > 4U) {
        goto block_153;
    }
    switch (temp_r0_24) {                           /* jump table: jtbl_080C7B40 */
case 0:
    M2C_FIELD(temp_r7_4, u16 *, 0x26) = (u16) (M2C_FIELD(temp_r7_4, u16 *, 0x26) + 1);
    goto block_153;
case 1:
    M2C_FIELD(temp_r7_4, u16 *, 0x28) = (u16) (M2C_FIELD(temp_r7_4, u16 *, 0x28) + 1);
    goto block_153;
case 2:
    M2C_FIELD(temp_r7_4, u16 *, 0x2A) = (u16) (M2C_FIELD(temp_r7_4, u16 *, 0x2A) + 1);
    goto block_153;
case 3:
    M2C_FIELD(temp_r7_4, u16 *, 0x2E) = (u16) (M2C_FIELD(temp_r7_4, u16 *, 0x2E) + 1);
    goto block_153;
case 4:
    M2C_FIELD(temp_r7_4, u16 *, 0x2C) = (u16) (M2C_FIELD(temp_r7_4, u16 *, 0x2C) + 1);
    }
block_153:
    {
        register u32 reward_next_r0 asm("r0") = reward_counter_r5 + 1;

        asm volatile("" : "+r"(reward_next_r0));
        reward_next_r0 <<= 24;
        reward_counter_r5 = reward_next_r0 >> 24;
    }
    if (reward_counter_r5 <= 9U) {
        goto loop_146;
    }
    }
block_154:
    func_0809844C(M2C_FIELD(temp_r7_4, s16 *, 0x34), 3, 0, 0xA, 1, 4, 0U);
    func_0809844C(M2C_FIELD(temp_r7_4, s16 *, 0x36), 3, 0, 0xA, 1, 4, 1U);
    func_0809844C(M2C_FIELD(temp_r7_4, s16 *, 0x3C), 3, 0, 0xA, 1, 4, 2U);
    func_0809844C(M2C_FIELD(temp_r7_4, s16 *, 0x38), 3, 0, 0xA, 1, 4, 3U);
    func_0809844C(M2C_FIELD(temp_r7_4, s16 *, 0x3A), 3, 0, 0xA, 1, 4, 4U);
    func_0809844C((s16) M2C_FIELD(temp_r7_4, u16 *, 0x26), 3, 0, 0xA, 1, 8, 0U);
    func_0809844C((s16) M2C_FIELD(temp_r7_4, u16 *, 0x28), 3, 0, 0xA, 1, 8, 1U);
    func_0809844C((s16) M2C_FIELD(temp_r7_4, u16 *, 0x2E), 3, 0, 0xA, 1, 8, 2U);
    func_0809844C((s16) M2C_FIELD(temp_r7_4, u16 *, 0x2A), 3, 0, 0xA, 1, 8, 3U);
    func_0809844C((s16) M2C_FIELD(temp_r7_4, u16 *, 0x2C), 3, 0, 0xA, 1, 8, 4U);
    stat_left_offset = 0x34;
    stat_right_offset = 0x26;
    stat_left = *(s16 *)(temp_r7_4 + stat_left_offset);
    stat_right = *(s16 *)(temp_r7_4 + stat_right_offset);
    stat_left += stat_right;
    func_0809844C_wide(stat_left, 3, 0, 0xA, 1, 0xC, 0U);
    stat_left_offset = 0x36;
    stat_right_offset = 0x28;
    stat_left = *(s16 *)(temp_r7_4 + stat_left_offset);
    stat_right = *(s16 *)(temp_r7_4 + stat_right_offset);
    stat_left += stat_right;
    func_0809844C_wide(stat_left, 3, 0, 0xA, 1, 0xC, 1U);
    stat_left_offset = 0x3C;
    stat_right_offset = 0x2E;
    stat_left = *(s16 *)(temp_r7_4 + stat_left_offset);
    stat_right = *(s16 *)(temp_r7_4 + stat_right_offset);
    stat_left += stat_right;
    func_0809844C_wide(stat_left, 3, 0, 0xA, 1, 0xC, 2U);
    stat_left_offset = 0x38;
    stat_right_offset = 0x2A;
    stat_left = *(s16 *)(temp_r7_4 + stat_left_offset);
    stat_right = *(s16 *)(temp_r7_4 + stat_right_offset);
    stat_left += stat_right;
    func_0809844C_wide(stat_left, 3, 0, 0xA, 1, 0xC, 3U);
    stat_left_offset = 0x3A;
    stat_right_offset = 0x2C;
    stat_left = *(s16 *)(temp_r7_4 + stat_left_offset);
    stat_right = *(s16 *)(temp_r7_4 + stat_right_offset);
    stat_left += stat_right;
    func_0809844C_wide(stat_left, 3, 0, 0xA, 1, 0xC, 4U);
    func_080972C8();
    {
        register volatile u16 *keys asm("r4") =
            (volatile u16 *)0x0300000E;
        register u32 mask asm("r5") = 3;
        register u32 key_value_r1 asm("r1");
        register u32 key_test_r0 asm("r0");

        do {
            func_080ED17C(1);
            asm volatile("ldrh %0, [%1]"
                         : "=r"(key_value_r1)
                         : "r"(keys)
                         : "memory");
            key_test_r0 = mask;
            asm volatile("" : "+r"(key_test_r0));
        } while (!(key_test_r0 & key_value_r1));
    }
    func_08092E84(0x41);
    if (*sp78 == 5) {
        goto block_158;
    }
    goto block_182;
block_158:
    func_08098BB4(0x08003E61);
    {
        register u32 menu_selection_zero_r4 asm("r4") = 0;

        asm volatile("" : "+r"(menu_selection_zero_r4));
        var_sl_2 = menu_selection_zero_r4;
    }
    {
    register u32 clear_index asm("r5") = 0;
    register u8 *clear_base asm("r2");
    register u32 clear_zero asm("r1");
    register u8 *clear_address asm("r0");
    temp_r6_3 = (s32) sp50;
    clear_base = (u8 *) temp_r6_3;
    asm volatile("" : "+r"(clear_base));
    clear_zero = 0;
loop_159:
    clear_address = clear_base + clear_index;
    *clear_address = (u8)clear_zero;
    {
        register u32 clear_successor asm("r0") = clear_index + 1;

        clear_successor <<= 24;
        clear_index = clear_successor >> 24;
    }
    if (clear_index <= 5U) {
        goto loop_159;
    }
    }
    {
        register u32 menu_remaining_r5 asm("r5") = 0xA;

        asm volatile("" : "+r"(menu_remaining_r5));
        sp64 = menu_remaining_r5;
    }
    var_r5_5 = 1;
    sp68 = func_08094484(0x080ED830, 0x080ED864, 0, 0x98,
        (s32) ((var_sl_2 << 19) + ({
            register u32 menu_y_base_r4 asm("r4") = 0xA0;

            menu_y_base_r4 <<= 14;
            asm volatile("" : "+r"(menu_y_base_r4));
            menu_y_base_r4;
        })) >> 16,
        0x3EE, 0xF, 0x20,
        ({ register s32 zero asm("r2") = 0; zero; }));
    asm volatile("" : "=g"(menu_frame_anchor));
    func_08096F3C();
    asm volatile("" : "+r"(var_r5_5));
    temp_r0 = var_r5_5;
    var_r8_9 = (u32) temp_r6_3;
loop_161:
    menu_row = var_sl_2 << 3;
    asm volatile("" : "+r"(menu_row));
    asm volatile(
        ".macro bne target\n\t"
        ".short 0xD06B\n\t"
        ".endm\n\t"
        ".macro b target\n\t"
        ".endm");
    if (var_r5_5 == 0) {
        goto block_165;
    }
    asm volatile(".purgem bne\n\t.purgem b");
    var_r5_5 = 0;
loop_163:
    func_0809844C((s16) ((u8 *) temp_r6_3)[var_r5_5], 3, 0, 0xA, temp_r0, 8, var_r5_5);
    var_r5_5 = (u32) (u8) (var_r5_5 + 1);
    if ((u32) var_r5_5 <= 4U) {
        goto loop_163;
    }
    {
        register u32 stat_offset asm("r2") = 0x34;
        register s32 stat_value asm("r0");
        register u32 menu_value asm("r3");
        register u32 one_view asm("r5");
        register u32 zero_view asm("r2");

        stat_value = *(s16 *)(temp_r7_4 + stat_offset);
        menu_value = var_r8_9;
        asm volatile("" : "+r"(menu_value));
        menu_value = *(u8 *)menu_value;
        asm volatile("" : "+r"(menu_value));
        stat_value += menu_value;
        one_view = temp_r0;
        asm volatile("" : "+r"(one_view));
        func_0809844C_wide(stat_value, 3, zero_view, 0xA, one_view,
            ({
                register u32 twelve asm("r1") = 0xC;
                asm volatile("" : "+r"(twelve));
                twelve;
            }),
            ({
                zero_view = 0;
                asm volatile("" : "+r"(zero_view));
                zero_view;
            }));
    }
    {
        register s32 stat_value asm("r0");
        register u32 stat_offset asm("r3") = 0x36;
        register u8 *menu_view asm("r5");
        register u32 one_r1 asm("r1");

        stat_value = *(s16 *)(temp_r7_4 + stat_offset);
        menu_view = (u8 *) var_r8_9;
        asm volatile("" : "+r"(menu_view));
        stat_value += menu_view[1];
        one_r1 = temp_r0;
        asm volatile("" : "+r"(one_r1));
        func_0809844C_wide(stat_value, 3, 0, 0xA, one_r1,
            ({
                register u32 twelve asm("r2") = 0xC;
                asm volatile("" : "+r"(twelve));
                twelve;
            }), one_r1);
        {
            register s32 stat_value asm("r0");
        register u32 stat_offset asm("r3") = 0x3C;
        register u32 menu_value asm("r1");

        asm volatile(
            ".macro mov dst, src\n\t"
            ".short 0x233C\n\t"
            ".endm\n\t"
            ".macro ldrsh dst, addr:vararg\n\t"
            ".short 0x5EF8\n\t"
            ".endm");
        stat_value = *(s16 *)(temp_r7_4 + stat_offset);
        asm volatile(".purgem mov\n\t.purgem ldrsh");
            menu_value = menu_view[2];
            asm volatile("" : "+r"(menu_value));
            stat_value += menu_value;
            menu_one_r5 = temp_r0;
            asm volatile("" : "+r"(menu_one_r5));
            func_0809844C_wide(stat_value, 3, 0, 0xA, menu_one_r5,
                ({
                    register u32 twelve asm("r1") = 0xC;
                    asm volatile("" : "+r"(twelve));
                    twelve;
                }), 2U);
        }
    }
    {
        register s32 stat_value asm("r0");
        register u32 stat_offset asm("r2") = 0x38;
        register u8 *menu_view asm("r3");
        register u32 menu_value asm("r1");
        register u32 three_r1 asm("r1");

        stat_value = *(s16 *)(temp_r7_4 + stat_offset);
        menu_view = (u8 *)var_r8_9;
        asm volatile("" : "+r"(menu_view));
        menu_value = menu_view[3];
        asm volatile("" : "+r"(menu_value));
        stat_value += menu_value;
        func_0809844C_wide(stat_value, three_r1, 0, 0xA, menu_one_r5,
            ({
                register u32 twelve asm("r5") = 0xC;
                asm volatile("" : "+r"(twelve));
                twelve;
            }),
            ({
                three_r1 = 3;
                asm volatile("" : "+r"(three_r1));
                three_r1;
            }));
    }
    {
        register s32 stat_value asm("r0");
        register u32 stat_offset asm("r2") = 0x3A;
        register u32 menu_value asm("r3");

        asm volatile(
            ".macro mov dst, src\n\t"
            ".short 0x223A\n\t"
            ".endm\n\t"
            ".macro ldrsh dst, addr:vararg\n\t"
            ".short 0x5EB8\n\t"
            ".endm");
        stat_value = *(s16 *)(temp_r7_4 + stat_offset);
        asm volatile(".purgem mov\n\t.purgem ldrsh");
        menu_value = var_r8_9;
        asm volatile("" : "+r"(menu_value));
        menu_value = *(u8 *)(menu_value + 4);
        asm volatile("" : "+r"(menu_value));
        stat_value += menu_value;
        func_0809844C_wide(stat_value, 3, 0, 0xA, temp_r0,
            ({
                register u32 twelve asm("r1") = 0xC;
                asm volatile("" : "+r"(twelve));
                twelve;
            }), 4U);
    }
    asm volatile(".syntax unified\n\t"
                 "movs r2, #3\n\t"
                 "str r2, [sp]\n\t"
                 "movs r0, #9\n\t"
                 "str r0, [sp, #4]\n\t"
                 "movs r3, #0\n\t"
                 "str r3, [sp, #8]\n\t"
                 "ldr r0, [sp, #100]\n\t"
                 "movs r1, #2\n\t"
                 "movs r2, #0\n\t"
                 "movs r3, #10\n\t"
                 "bl func_0809844C\n\t"
                 ".syntax divided"
                 :
                 :
                 : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
    func_080972C8();
    var_r5_5 = 0;
block_165:
    asm volatile("" : : "g"(menu_frame_anchor));
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x9C1A\n\t"
        ".endm\n\t"
        ".macro strh src, addr:vararg\n\t"
        ".short 0x80E0\n\t"
        ".endm");
    M2C_FIELD(sp68, s16 *, 6) = (s16) (menu_row + 0x28);
    asm volatile(".purgem ldr\n\t.purgem strh");
    func_080ED17C(1);
    if (!(0x40 & *(u16 *)0x03006034)) {
        goto block_168;
    }
    {
        u32 selection = var_sl_2;

        asm volatile("" : "+r"(selection));
        if (selection == 0) {
            goto block_168;
        }
        selection = (u8)(selection - 1);
        var_sl_2 = selection;
    }
    func_08092E84(0x40);
block_168:
    if (!(0x80 & *(u16 *)0x03006034)) {
        goto block_171;
    }
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x4651\n\t"
        ".endm\n\t"
        ".macro cmp lhs, rhs\n\t"
        ".short 0x2903\n\t"
        ".endm");
    if ((u32) var_sl_2 > 3U) {
        goto block_171;
    }
    asm volatile(".purgem mov\n\t.purgem cmp");
    var_sl_2 = (u8)(var_sl_2 + 1);
    func_08092E84(0x40);
block_171:
    if (!(0x20 & *(u16 *)0x03006034)) {
        goto block_174;
    }
    asm volatile(
        ".macro mov dst, src\n\t"
        ".short 0x4652\n\t"
        ".endm\n\t"
        ".macro add dst, lhs, rhs\n\t"
        ".short 0x18B1\n\t"
        ".endm");
    temp_r1_7 = &((u8 *) temp_r6_3)[var_sl_2];
    asm volatile(".purgem mov\n\t.purgem add");
    temp_r0_25 = *temp_r1_7;
    if (temp_r0_25 == 0) {
        goto block_174;
    }
    *temp_r1_7 = temp_r0_25 - 1;
    sp64 = (s32) (u8) (sp64 + 1);
    var_r5_5 = 1;
    func_08092E84(0x40);
block_174:
    if (!(0x10 & *(u16 *)0x03006034)) {
        goto block_177;
    }
    {
        register u32 remaining_r3 asm("r3") = sp64;
        register u32 selection_r4 asm("r4");
        register u32 next_r0 asm("r0");
        register u8 *address_r0 asm("r0");
        register u32 value_r1 asm("r1");

        asm volatile("" : "+r"(remaining_r3));
        if (remaining_r3 == 0) {
            goto block_177;
        }
        selection_r4 = var_sl_2;
        asm volatile("" : "+r"(selection_r4));
        address_r0 = &((u8 *) temp_r6_3)[selection_r4];
        asm volatile("" : "+r"(address_r0));
        value_r1 = *address_r0;
        value_r1 += 1;
        *address_r0 = value_r1;
        next_r0 = remaining_r3;
        asm volatile("" : "+r"(next_r0));
        next_r0 = (u8)(next_r0 - 1);
        sp64 = next_r0;
    }
    var_r5_5 = 1;
    func_08092E84(0x40);
block_177:
    asm volatile(
        ".macro ldrh dst, addr:vararg\n\t"
        ".short 0x8801, 0x4648\n\t"
        ".macro mov dst2, src2\n\t"
        ".purgem ldrh\n\t"
        ".purgem mov\n\t"
        ".endm\n\t"
        ".endm");
    if (temp_r0 & *(u16 *)0x0300000E) {
        goto block_179;
    }
    goto loop_161;
block_179:
    asm volatile(
        ".macro ldr dst, addr:vararg\n\t"
        ".short 0x9819, 0x2800\n\t"
        ".macro cmp lhs, rhs\n\t"
        ".purgem ldr\n\t"
        ".purgem cmp\n\t"
        ".endm\n\t"
        ".endm");
    if (sp64 == 0) {
        goto block_181;
    }
    func_08092E84(0x58);
    func_0809538C(1, 0, 0, 1, 0x48A8, 0x2858, 0x2B3B, 0x3E);
    func_08098BB4(0x08001C22);
    func_0809534C();
    {
        register s32 transition_zero_r1 asm("r1") = 0;

        asm volatile("" : "+r"(transition_zero_r1));
        func_0809538C(1, transition_zero_r1, 0, 0,
            transition_zero_r1, transition_zero_r1, 0x3B, 0x3E);
    }
    func_080972C8();
    goto loop_161;
block_181:
    M2C_FIELD(temp_r7_4, u16 *, 0x26) = (u16) ((u8 *) temp_r6_3)[0];
    M2C_FIELD(temp_r7_4, u16 *, 0x28) = (u16) ((u8 *) temp_r6_3)[1];
    M2C_FIELD(temp_r7_4, u16 *, 0x2E) = (u16) ((u8 *) temp_r6_3)[2];
    M2C_FIELD(temp_r7_4, u16 *, 0x2A) = (u16) ((u8 *) temp_r6_3)[3];
    M2C_FIELD(temp_r7_4, u16 *, 0x2C) = (u16) ((u8 *) temp_r6_3)[4];
    func_08098BB4(0x08003E90);
    func_08094554(sp68);
    func_08092E84(0x3E);
block_182:
    {
        register u8 *status_r2 asm("r2") = sp74;
        register u32 updated_r0 asm("r0") = *status_r2;

        updated_r0 += 1;
        *status_r2 = updated_r0;
    }
    {
        register u32 updated_r0 asm("r0") =
            M2C_FIELD(temp_r7_4, u16 *, 0x26);
        register u32 current_r3 asm("r3") =
            M2C_FIELD(temp_r7_4, u16 *, 0x34);

        updated_r0 += current_r3;
        M2C_FIELD(temp_r7_4, u16 *, 0x34) = updated_r0;
    }
    {
        register u32 updated_r0 asm("r0") =
            M2C_FIELD(temp_r7_4, u16 *, 0x28);
        register u32 current_r4 asm("r4") =
            M2C_FIELD(temp_r7_4, u16 *, 0x36);

        updated_r0 += current_r4;
        M2C_FIELD(temp_r7_4, u16 *, 0x36) = updated_r0;
    }
    {
        register u32 updated_r0 asm("r0") =
            M2C_FIELD(temp_r7_4, u16 *, 0x2E);
        register u32 current_r5 asm("r5") =
            M2C_FIELD(temp_r7_4, u16 *, 0x3C);

        updated_r0 += current_r5;
        M2C_FIELD(temp_r7_4, u16 *, 0x3C) = updated_r0;
    }
    {
        register u32 updated_r0 asm("r0") =
            M2C_FIELD(temp_r7_4, u16 *, 0x2A);
        register u32 current_r1 asm("r1") =
            M2C_FIELD(temp_r7_4, u16 *, 0x38);

        updated_r0 += current_r1;
        M2C_FIELD(temp_r7_4, u16 *, 0x38) = updated_r0;
    }
    {
        register u32 updated_r0 asm("r0") =
            M2C_FIELD(temp_r7_4, u16 *, 0x2C);
        register u32 current_r2 asm("r2") =
            M2C_FIELD(temp_r7_4, u16 *, 0x3A);

        updated_r0 += current_r2;
        M2C_FIELD(temp_r7_4, u16 *, 0x3A) = updated_r0;
    }
    if ((func_080E705C(temp_r7_4, 0) << 0x18) == 0) {
        goto block_194;
    }
    func_08098BB4(0x08003E93);
    var_r5_7 = NULL;
    if ((u32) var_r5_7 >= (u32) *(u8 *)0x02032E20) {
        goto block_191;
    }
    result_buffer_seed = 0x02030564;
    temp_r0 = result_buffer_seed;
loop_185:
    {
        register u32 result_successor_r4 asm("r4") =
            (u32)var_r5_7 + 1;

        asm volatile("" : "+r"(result_successor_r4));
        reward_successor = result_successor_r4;
    }
    if (var_r5_7 == NULL) {
        goto block_190;
    }
    if ((func_080ECF78(var_r5_7, 3) << 0x18) != 0) {
        goto block_190;
    }
    func_080972C8();
    {
    register volatile u16 *result_keys asm("r4") =
        (volatile u16 *)0x0300000E;
    register u32 result_key_mask asm("r6") = 3;
loop_188:
    func_080ED17C(1);
    {
    register u32 result_key_value_r1 asm("r1");
    register u32 result_key_test_r0 asm("r0");

    asm volatile("ldrh %0, [%1]"
                 : "=r"(result_key_value_r1)
                 : "r"(result_keys)
                 : "memory");
    asm volatile("add %0, %1, #0"
                 : "=r"(result_key_test_r0)
                 : "r"(result_key_mask));
    if (!(result_key_test_r0 & result_key_value_r1)) {
        goto loop_188;
    }
    }
    }
    func_08092E84(0x41);
    func_080986B4(1);
block_190:
    {
        register u32 result_first_r0 asm("r0") = 0x02032E21;
        register u32 result_second_r1 asm("r1");

        asm volatile("add %0, %1, %0"
                     : "+r"(result_first_r0)
                     : "r"(var_r5_7));
        result_first_r0 = *(u8 *)result_first_r0;
        result_second_r1 = 0x02032E2B;
        asm volatile(".short 0x1869"
                     : "+r"(result_second_r1)
                     : "r"(var_r5_7));
        result_second_r1 = *(u8 *)result_second_r1;
        func_080E7664_wide(
            result_first_r0, result_second_r1, temp_r0);
    }
    func_080981F0(temp_r0, 0, 1, 0, (u32) (func_080ECF78(var_r5_7, 3) << 0x18) >> 0x17);
    {
        register u32 result_successor_r5 asm("r5") = reward_successor;
        register u32 result_successor_r0 asm("r0");

        asm volatile("" : "+r"(result_successor_r5));
        result_successor_r0 = result_successor_r5 << 24;
        var_r5_7 = (void *)(result_successor_r0 >> 24);
    }
    if ((u32) var_r5_7 < (u32) *(u8 *)0x02032E20) {
        goto loop_185;
    }
block_191:
    func_080972C8();
    {
    register volatile u16 *summary_keys asm("r4") =
        (volatile u16 *)0x0300000E;
    register u32 summary_key_mask asm("r5") = 3;
loop_192:
    func_080ED17C(1);
    {
    register u32 summary_key_value_r1 asm("r1");
    register u32 summary_key_test_r0 asm("r0");

    asm volatile("ldrh %0, [%1]"
                 : "=r"(summary_key_value_r1)
                 : "r"(summary_keys)
                 : "memory");
    asm volatile("add %0, %1, #0"
                 : "=r"(summary_key_test_r0)
                 : "r"(summary_key_mask));
    if (!(summary_key_test_r0 & summary_key_value_r1)) {
        goto loop_192;
    }
    }
    }
    func_08092E84(0x41);
block_194:
    {
    register u32 reward_kind_r0 asm("r0") =
        M2C_FIELD(temp_r7_4, u8 *, 1);
    register u32 reward_kind_r1 asm("r1");

    if (reward_kind_r0 == 0) {
        goto block_196;
    }
    asm volatile(".include \"src/sub_080C7190_fix8090.inc\""
                 : "=r"(reward_kind_r1)
                 : "r"(reward_kind_r0));
    func_080E5880((reward_kind_r1 * 0x70) + 0x020218E8, temp_r7_4);
    }
block_196:
    temp_r0_28 = *temp_r7_4;
    if (temp_r0_28 == 1) {
        goto block_198;
    }
    goto block_218;
block_198:
    if (M2C_FIELD(temp_r7_4, u8 *, 0x31) != 0) {
        goto block_200;
    }
    goto block_218;
block_200:
    reward_record = (u8 *)0x020218E4;
    asm volatile("" : "+r"(reward_record));
    if ((u32) *(u8 *)0x02028114 <= 0x62U) {
        goto block_202;
    }
    goto block_218;
block_202:
    *(u8 *)0x02032EF8 = 0x34;
    func_08092E84(0x34);
    reward_record += 0x6808;
    func_08098BB4(0x08003EA0);
    func_080986B4(0);
    func_08098248(func_080E7B64(0x4BU), 2, 0);
    func_08098BB4(0x08003B1C);
    func_080984C4(*(u8 *)0x02028114 + 1, 2, 1, 0, 0);
    func_08098BB4(0x08003B3E);
    func_0809A9C8(0x4BU, 0, M2C_FIELD(reward_record, u8 *, 1), 0x3C2, 0xE, 0x02002880);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x2A), 3, 0, 0xA, (s32) temp_r0_28, 4, 0U);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x2C), 3, 0, 0xA, (s32) temp_r0_28, 4, (u32) temp_r0_28);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x2E), 3, 0, 0xA, (s32) temp_r0_28, 4, 2U);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x30), 3, 0, 0xA, (s32) temp_r0_28, 4, 3U);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x32), 3, 0, 0xA, (s32) temp_r0_28, 4, 4U);
    {
    register u8 *reward_stat_base asm("r6") = (u8 *)0x087B7988;
    register u32 reward_stat_last_offset asm("r2");
    register u8 *reward_stat_last asm("r8");
    register u32 reward_update_index asm("r1");
    register u32 reward_update_offset asm("r0");
    register u32 reward_update_current asm("r5");
    register u32 reward_second_base asm("r1");
    register u32 reward_second_current asm("r2");
    register u32 reward_third_index asm("r1");
    register u32 reward_third_base asm("r3");
    register u32 reward_third_current asm("r5");
    register u32 reward_fourth_base asm("r1");
    register u32 reward_fourth_current asm("r2");
    register u32 reward_fifth_index asm("r1");
    register u32 reward_fifth_current asm("r3");
    register u32 reward_display_fifth_index asm("r1");
    register u32 reward_display_fifth_offset asm("r0");
    func_0809844C(M2C_FIELD((M2C_FIELD(reward_record, u8 *, 1) * 0xA), s16 *, (u32)reward_stat_base), 3, 0, 0xA, (s32) temp_r0_28, 8, 0U);
    func_0809844C(M2C_FIELD((M2C_FIELD(reward_record, u8 *, 1) * 0xA), s16 *, 0x087B798A), 3, 0, 0xA, (s32) temp_r0_28, 8, (u32) temp_r0_28);
    func_0809844C(M2C_FIELD((M2C_FIELD(reward_record, u8 *, 1) * 0xA), s16 *, 0x087B798C), 3, 0, 0xA, (s32) temp_r0_28, 8, 2U);
    func_0809844C(M2C_FIELD((M2C_FIELD(reward_record, u8 *, 1) * 0xA), s16 *, 0x087B798E), 3, 0, 0xA, (s32) temp_r0_28, 8, 3U);
    reward_display_fifth_index = M2C_FIELD(reward_record, u8 *, 1);
    reward_display_fifth_offset = reward_display_fifth_index << 2;
    reward_display_fifth_offset += reward_display_fifth_index;
    reward_display_fifth_offset <<= 1;
    reward_stat_last_offset = 8;
    reward_stat_last_offset += (u32)reward_stat_base;
    reward_stat_last = (u8 *)reward_stat_last_offset;
    reward_display_fifth_offset += (u32)reward_stat_last;
    func_0809844C(*(s16 *)reward_display_fifth_offset, 3, 0, 0xA,
        (s32) temp_r0_28, 8, 4U);
    *(u8 *)0x02028114 = (u8) (*(u8 *)0x02028114 + 1);
    reward_update_index = M2C_FIELD(reward_record, u8 *, 1);
    reward_update_offset = reward_update_index << 2;
    reward_update_offset += reward_update_index;
    reward_update_offset <<= 1;
    reward_update_offset += (u32)reward_stat_base;
    reward_update_offset = *(u16 *)reward_update_offset;
    reward_update_current = M2C_FIELD(reward_record, u16 *, 0x2A);
    reward_update_offset += reward_update_current;
    M2C_FIELD(reward_record, u16 *, 0x2A) = (u16)reward_update_offset;
    temp_r1_8 = reward_update_index;
    reward_update_offset = temp_r1_8 << 2;
    reward_update_offset += temp_r1_8;
    reward_update_offset <<= 1;
    reward_second_base = 0x087B798A;
    asm volatile("add %0, %0, %1"
                 : "+r"(reward_update_offset)
                 : "r"(reward_second_base));
    reward_update_offset = *(u16 *)reward_update_offset;
    reward_second_current = M2C_FIELD(reward_record, u16 *, 0x2C);
    reward_update_offset += reward_second_current;
    M2C_FIELD(reward_record, u16 *, 0x2C) = (u16)reward_update_offset;
    reward_third_index = M2C_FIELD(reward_record, u8 *, 1);
    reward_update_offset = reward_third_index << 2;
    reward_update_offset += reward_third_index;
    reward_update_offset <<= 1;
    reward_third_base = 0x087B798C;
    asm volatile("add %0, %0, %1"
                 : "+r"(reward_update_offset)
                 : "r"(reward_third_base));
    reward_update_offset = *(u16 *)reward_update_offset;
    reward_third_current = M2C_FIELD(reward_record, u16 *, 0x2E);
    reward_update_offset += reward_third_current;
    M2C_FIELD(reward_record, u16 *, 0x2E) = (u16)reward_update_offset;
    reward_update_offset = reward_third_index << 2;
    reward_update_offset += reward_third_index;
    reward_update_offset <<= 1;
    reward_fourth_base = 0x087B798E;
    asm volatile("add %0, %0, %1"
                 : "+r"(reward_update_offset)
                 : "r"(reward_fourth_base));
    reward_update_offset = *(u16 *)reward_update_offset;
    reward_fourth_current = M2C_FIELD(reward_record, u16 *, 0x30);
    reward_update_offset += reward_fourth_current;
    M2C_FIELD(reward_record, u16 *, 0x30) = (u16)reward_update_offset;
    reward_fifth_index = M2C_FIELD(reward_record, u8 *, 1);
    reward_update_offset = reward_fifth_index << 2;
    reward_update_offset += reward_fifth_index;
    reward_update_offset <<= 1;
    reward_update_offset += (u32)reward_stat_last;
    reward_update_offset = *(u16 *)reward_update_offset;
    reward_fifth_current = M2C_FIELD(reward_record, u16 *, 0x32);
    reward_update_offset += reward_fifth_current;
    M2C_FIELD(reward_record, u16 *, 0x32) = (u16)reward_update_offset;
    }
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x2A), 3, 0, 0xA, (s32) temp_r0_28, 0xC, 0U);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x2C), 3, 0, 0xA, (s32) temp_r0_28, 0xC, (u32) temp_r0_28);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x2E), 3, 0, 0xA, (s32) temp_r0_28, 0xC, 2U);
    func_0809844C(M2C_FIELD(reward_record, s16 *, 0x30), 3, 0, 0xA, (s32) temp_r0_28, 0xC, 3U);
    {
        register s32 final_reward_value_r0 asm("r0");

        asm volatile(".include \"src/sub_080C7190_fix8310.inc\"\n\t"
                     : "=r"(final_reward_value_r0)
                     : "r"(reward_record));
        func_0809844C_wide(final_reward_value_r0, 3, 0, 0xA,
            (s32) temp_r0_28, 0xC, 4U);
    }
    func_080972C8();
    {
    register volatile u16 *reward_summary_keys asm("r4") =
        (volatile u16 *)0x0300000E;
    register u32 reward_summary_mask asm("r5") = 3;
loop_203:
    func_080ED17C(1);
    {
    register u32 reward_summary_value_r1 asm("r1");
    register u32 reward_summary_test_r0 asm("r0");

    asm volatile("ldrh %0, [%1]"
                 : "=r"(reward_summary_value_r1)
                 : "r"(reward_summary_keys)
                 : "memory");
    asm volatile("add %0, %1, #0"
                 : "=r"(reward_summary_test_r0)
                 : "r"(reward_summary_mask));
    if (!(reward_summary_test_r0 & reward_summary_value_r1)) {
        goto loop_203;
    }
    }
    }
    func_08092E84(0x41);
    if ((func_080E79F4() << 0x18) == 0) {
        goto block_218;
    }
    func_08098BB4(0x08003E93);
    var_r5_8 = NULL;
    if ((u32) var_r5_8 >= (u32) *(u8 *)0x02032E35) {
        goto block_215;
    }
    reward_table_seed = 0x087EF410;
    asm volatile("" : "+r"(reward_table_seed));
    temp_r0 = reward_table_seed;
loop_209:
    {
        register u32 reward_successor_r1 asm("r1") =
            (u32)var_r5_8 + 1;

        asm volatile("" : "+r"(reward_successor_r1));
        reward_successor = reward_successor_r1;
    }
    if (var_r5_8 == NULL) {
        goto block_214;
    }
    if ((func_080ECF78(var_r5_8, 3) << 0x18) != 0) {
        goto block_214;
    }
    func_080972C8();
    {
    register volatile u16 *reward_keys asm("r4") =
        (volatile u16 *)0x0300000E;
    register u32 reward_key_mask asm("r6") = 3;
    register u32 reward_key_value_r1 asm("r1");
    register u32 reward_key_test_r0 asm("r0");
loop_212:
    func_080ED17C(1);
    asm volatile("ldrh %0, [%1]"
                 : "=r"(reward_key_value_r1)
                 : "r"(reward_keys)
                 : "memory");
    reward_key_test_r0 = reward_key_mask;
    asm volatile("" : "+r"(reward_key_test_r0));
    if (!(reward_key_test_r0 & reward_key_value_r1)) {
        goto loop_212;
    }
    }
    func_08092E84(0x41);
    func_080986B4(1);
block_214:
    {
        register u32 reward_index_r0 asm("r0") = 0x02032E36;

        asm volatile("" : "+r"(reward_index_r0));
        reward_index_r0 = (u32)var_r5_8 + reward_index_r0;
        reward_index_r0 = *(u8 *)reward_index_r0;
        temp_r4_6 = *(s32 *)((reward_index_r0 * 4) + temp_r0);
    }
    func_080981F0(temp_r4_6, 0, 1, 0, (u32) (func_080ECF78(var_r5_8, 3) << 0x18) >> 0x17);
    {
        register u32 reward_successor_r2 asm("r2") = reward_successor;
        register u32 reward_successor_r0 asm("r0");

        asm volatile("" : "+r"(reward_successor_r2));
        reward_successor_r0 = reward_successor_r2 << 24;
        var_r5_8 = (void *)(reward_successor_r0 >> 24);
    }
    if ((u32) var_r5_8 < (u32) *(u8 *)0x02032E35) {
        goto loop_209;
    }
block_215:
    func_080972C8();
    {
    register volatile u16 *final_keys asm("r4") =
        (volatile u16 *)0x0300000E;
    register u32 final_key_mask asm("r5") = 3;
    register u32 final_key_value_r1 asm("r1");
    register u32 final_key_test_r0 asm("r0");
loop_216:
    func_080ED17C(1);
    asm volatile("ldrh %0, [%1]"
                 : "=r"(final_key_value_r1)
                 : "r"(final_keys)
                 : "memory");
    final_key_test_r0 = final_key_mask;
    asm volatile("" : "+r"(final_key_test_r0));
    if (!(final_key_test_r0 & final_key_value_r1)) {
        goto loop_216;
    }
    }
    func_08092E84(0x41);
block_218:
    {
    register u32 final_table_value asm("r1") = 0x087B77C8;
    register u8 *final_status_ptr asm("r3") = sp74;
    register u32 final_table_index asm("r0");

    asm volatile("" : "+r"(final_table_value));
    final_table_index = *final_status_ptr;
    final_table_index <<= 2;
    final_table_index += final_table_value;
    final_table_value = *(u32 *)final_table_index;
    temp_r1_10 = final_table_value;
    }
    if (temp_r1_10 == 0) {
        goto block_220;
    }
    if ((u32) M2C_FIELD(temp_r7_4, u32 *, 4) >= temp_r1_10) {
        goto loop_141;
    }
block_220:
    {
        register u32 final_owner_r4 asm("r4") = sp70;
        register u32 final_owner_r0 asm("r0");

        asm volatile("" : "+r"(final_owner_r4));
        final_owner_r0 = final_owner_r4 << 24;
        final_owner_r0 >>= 24;
        var_r8_9 = final_owner_r0;
        if (final_owner_r0 <= 0x34U) {
            goto loop_138;
        }
    }
    return;
block_223:
    tail_status_offset = 0x5A95;
    asm volatile("" : "+r"(tail_status_offset));
    temp_r4_7 += tail_status_offset;
    tail_status = *temp_r4_7;
    tail_data_offset = (tail_status << 3) - tail_status;
    tail_data_offset <<= 4;
    tail_data_base = tail_base + 4;
    tail_data_offset += (u32)tail_data_base;
    func_080E6090(tail_data_offset);
    func_080E5FA8(1, *temp_r4_7);
    goto block_228;
block_225:
    func_08098BB4(0x08003C58);
    tail_seed = 1;
    asm volatile("" : "+r"(tail_seed));
    var_r8_10 = tail_seed;
    tail_base = (u8 *)0x020218E4;
    tail_offset = 0x5A94;
    asm volatile(".include \"src/sub_080C7190_fix84B6.inc\""
                 : "+r"(tail_base), "+r"(tail_offset));
loop_226:
    tail_record_offset = var_r8_10 << 6;
    asm volatile("add %0, %1, %2"
                 : "=r"(temp_r4_7)
                 : "r"(tail_record_offset), "r"(tail_base));
    if (M2C_FIELD(temp_r4_7, u8 *, tail_offset) == 1) {
        goto block_223;
    }
    temp_r0_30 = var_r8_10 + 1;
    var_r8_10 = temp_r0_30;
    if ((u32) temp_r0_30 <= 0x34U) {
        goto loop_226;
    }
block_228:
    if ((func_0809F818(2) << 0x18) != 0) {
        goto block_236;
    }
    tail2_seed = 1;
    asm volatile("" : "+r"(tail2_seed));
    var_r8_11 = tail2_seed;
    tail2_base = (u8 *)0x020218E4;
    asm volatile("" : "+r"(tail2_base));
loop_230:
    tail2_index = var_r8_11;
    asm volatile("" : "+r"(tail2_index));
    tail2_record = tail2_index << 6;
    tail2_record += (u32)tail2_base;
    tail2_offset = 0x5A94;
    asm volatile("" : "+r"(tail2_offset));
    tail2_record += tail2_offset;
    if (*(u8 *)tail2_record != 0x60) {
        goto block_232;
    }
    func_080E6F6C_wide(var_r8_11);
block_232:
    temp_r0_31 = var_r8_11 + 1;
    var_r8_11 = temp_r0_31;
    if ((u32) temp_r0_31 <= 0x34U) {
        goto loop_230;
    }
    return;
block_235:
    func_08092E84(0x53);
    func_08098BB4(0x08003C88);
block_236:
    return;
}
