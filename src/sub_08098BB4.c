#include "m2c_prelude.h"

struct Map98BB4 {
    u32 flags;
    s16 x;
    s16 y;
    u16 width;
    u16 height;
    s16 offset_x;
    s16 offset_y;
    u16 cursor;
    u8 unk12;
    u8 slot;
    u8 top;
    u8 prior_top;
    u8 selected;
    u8 prior_selected;
    u8 style;
    u8 unk19;
    u8 unk1A;
    u8 repeat;
    u16 keys;
    u16 tiles[1];
};

struct WindowRecord98BB4 {
    s32 flags;
    u16 field4;
    u16 field6;
    u16 field8;
    u16 fieldA;
    u16 fieldC;
    u16 fieldE;
    u8 field10;
    u8 field11;
    u16 field12;
    u16 field14;
    u16 field16;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    s32 field28;
    s32 field2C;
    s32 field30;
    s32 field34;
};

extern u8 *D_0200A888;
extern struct WindowRecord98BB4 *D_0200A88C;
extern struct WindowRecord98BB4 *D_0200A890[4];
extern struct Map98BB4 D_0200A8A0;
extern u8 D_0200A880;
extern u8 D_0200A881;
extern u8 D_0200A882;
extern u16 D_0200A884;
extern volatile u8 D_0200E6C4[];
extern volatile u8 D_0200DE90[];
extern u8 D_0200E6CE[];
extern u32 D_02021664;
extern u16 D_02021668;
extern u16 D_0202166A;
extern u16 D_0202166C;
extern s32 D_02021670;
extern volatile u16 D_0300000C;
extern volatile u16 D_0300000E;
extern volatile u8 D_03000075;

void func_08092E84(s32);
struct WindowRecord98BB4 *func_08094484(
    s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_08094554(struct WindowRecord98BB4 *);
void func_08094564(struct WindowRecord98BB4 *, s16);
struct Map98BB4 *func_0809716C(u8);
void func_080971AC(u8);
void func_080972C8(void);
void func_08097980(u16);
u8 *func_08097DA8(struct Map98BB4 *, u8 *);
void func_08098514(s32, s32, s32, s32, s32, s32);
void func_080986B4(u8);
void func_08098754(u8);
void func_0809885C(struct Map98BB4 *);
void func_080ED17C(s32);

M2C_UNK jtbl_08098BDC();                            /* static */

void sub_08098BB4(u8 *arg0) {
    u8 * volatile sp14;
    volatile u32 sp18;
    volatile s32 sp1C;
    u8 * volatile sp20;
    volatile s32 sp24;
    volatile s32 sp28;
    s32 temp_r0_11;
    s32 temp_r0_13;
    s32 temp_r0_22;
    register s32 temp_r2_12 asm("r2");
    register s32 temp_r2_13 asm("r2");
    s32 temp_r2_14;
    register s32 temp_r2_15 asm("r2");
    s32 temp_r2_8;
    s32 temp_r2_9;
    s32 temp_r4_3;
    s32 temp_r4_4;
    s32 temp_r5_2;
    s32 temp_r6_2;
    s32 page_down_selected;
    s32 map_offset;
    register u16 *event_mask_base asm("r2");
    register u32 event_mask_value asm("r1");
    register s32 var_r0_3 asm("r0");
    s32 var_r1_3;
    s32 var_r1_4;
    s32 var_r1_5;
    s32 var_r5_10;
    s32 var_r5_2;
    s32 var_r5_3;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r5_6;
    s32 var_r5_7;
    s32 var_r5_8;
    s32 var_r5_9;
    register s32 var_r8_3 asm("r8");
    register s32 var_r8_4 asm("r8");
    register s32 var_r8_6 asm("r8");
    register s32 var_r8_7 asm("r8");
    register s32 var_r8_8 asm("r8");
    struct Map98BB4 *temp_r0_24;
    struct Map98BB4 *temp_r0_2;
    struct Map98BB4 *temp_r0_7;
    struct Map98BB4 *temp_r0_8;
    struct Map98BB4 *map_entry;
    register u16 *temp_r4_7 asm("r4");
    u16 *var_r4;
    u16 *var_r4_2;
    register u16 *var_sl_attr asm("r10");
    register u32 *var_ip_tiles asm("r12");
    register u32 *var_r6_tiles asm("r6");
    u16 temp_r1_11;
    u16 temp_r1_13;
    register u32 temp_r2_17 asm("r2");
    register u32 temp_r2_18 asm("r2");
    register u32 temp_r3_4 asm("r3");
    register u32 temp_r3_5 asm("r3");
    u16 temp_r4;
    u16 temp_r5;
    u32 var_r0_7;
    u32 temp_r0_10;
    u32 temp_r0_12;
    u32 temp_r0_14;
    u32 temp_r0_15;
    u32 temp_r0_16;
    u32 temp_r0_17;
    u32 temp_r0_20;
    u32 temp_r0_21;
    u32 temp_r0_23;
    u32 temp_r0_26;
    u32 temp_r1_10;
    u32 temp_r1_12;
    u32 temp_r1_14;
    register u32 temp_r1_18 asm("r1");
    u32 temp_r1_7;
    u32 temp_r1_8;
    register u32 var_r8_5 asm("r8");
    register u32 var_r9 asm("r9");
    register u32 var_r9_2 asm("r9");
    register u32 var_r9_3 asm("r9");
    u8 *temp_r1_15;
    u8 *temp_r1_3;
    u8 *temp_r1_6;
    u8 *temp_r8;
    u8 *var_r1;
    register u8 *var_r1_2 asm("r1");
    u8 *var_r5;
    u8 *var_r8;
    u8 temp_r0;
    s32 temp_r0_18;
    s32 temp_r0_19;
    s32 temp_r0_25;
    u8 temp_r0_3;
    u8 temp_r0_4;
    register s32 temp_r0_5 asm("r0");
    register s32 temp_r0_6 asm("r0");
    u8 temp_r0_9;
    u8 temp_r1;
    u8 temp_r1_16;
    register u32 temp_r1_17 asm("r3");
    u8 temp_r1_2;
    register s32 temp_r1_4 asm("r1");
    register s32 temp_r1_5 asm("r1");
    u8 temp_r1_9;
    u8 temp_r2;
    u8 temp_r2_10;
    u8 temp_r2_11;
    u8 temp_r2_16;
    u8 temp_r2_2;
    u8 temp_r2_3;
    u8 temp_r2_4;
    u8 temp_r2_5;
    u8 temp_r2_6;
    u8 temp_r2_7;
    u8 temp_r3;
    register s32 temp_r3_2 asm("r3");
    u8 temp_r3_3;
    u8 temp_r4_2;
    u8 temp_r4_5;
    u8 temp_r4_6;
    u8 temp_r6;
    u8 var_ip;
    u8 var_r0;
    register s32 var_r0_2 asm("r0");
    u8 var_r0_4;
    s32 var_r0_5;
    u8 var_r0_6;
    s32 var_r1_6;
    s32 var_r3;

    sp14 = arg0;
loop_1:
    {
        register u8 *opcode_stream_r1 asm("r1") = sp14;

        temp_r0 = M2C_FIELD(opcode_stream_r1, u8 *, 0);
    }
    if ((u32) temp_r0 > 0xDU) {
        goto block_289;
    }
    switch (temp_r0) {                              /* jump table: jtbl_08098BDC */
case 0:
    return;
case 1:
    {
        u8 *case1_head;
        u8 *case1_mid;

        func_08098514(
            ({
                case1_head = sp14;
                (s32) case1_head[1];
            }),
            (s32) case1_head[2],
            (s32) case1_head[3],
            ({
                case1_mid = sp14;
                (s32) case1_mid[4];
            }),
            (s32) case1_mid[5],
            ({
                var_r5 = sp14;
                var_r5[6] * 0x10;
            }));
        var_r5 += 7;
        goto block_288;
    }
case 2:
    {
        register u8 *stream_r6 asm("r6") = sp14;

        func_080986B4(M2C_FIELD(stream_r6, u8 *, 1));
        stream_r6 += 2;
        sp14 = stream_r6;
        goto block_289;
    }
case 3:
    {
        register u8 *stream_r1 asm("r1") = sp14;

        func_08098754(M2C_FIELD(stream_r1, u8 *, 1));
        {
            register u8 *next_r2 asm("r2") = sp14;

            next_r2 += 2;
            sp14 = next_r2;
        }
        goto block_289;
    }
case 4:
    func_080972C8();
    func_080ED17C(1);
    {
        register u8 *next_r3 asm("r3") = sp14;

        next_r3 += 1;
        sp14 = next_r3;
    }
    goto block_289;
case 5:
case 6:
    {
    register u8 *parser_stream_r4 asm("r4") = sp14;

    temp_r0_2 = func_0809716C(M2C_FIELD(parser_stream_r4, u8 *, 1));
    temp_r0_2->cursor = 0;
    if (M2C_FIELD(parser_stream_r4, u8 *, 0) != 5) {
        goto block_9;
    }
    var_r8 = parser_stream_r4 + 2;
    goto block_10;
block_9:
    var_r8 = D_0200A888;
block_10:
    if (!(temp_r0_2->flags & 0x80)) {
        goto block_12;
    }
    goto loop_41;
block_12:
    var_r8 = func_08097DA8(temp_r0_2, var_r8);
    goto block_44;
loop_13:
    temp_r3 = M2C_FIELD(var_r8, u8 *, 0);
    if ((u32) temp_r3 <= 0x1FU) {
        goto block_15;
    }
    goto block_34;
block_15:
    temp_r3_2 = M2C_FIELD(var_r8, volatile u8 *, 0);
    if (temp_r3_2 == 2) {
        goto block_26;
    }
    if ((s32) temp_r3_2 > 2) {
        goto block_19;
    }
    if (temp_r3_2 == 1) {
        goto block_24;
    }
    goto block_32;
block_19:
    if (temp_r3_2 != 3) {
        goto block_21;
    }
    goto block_27;
block_21:
    if (temp_r3_2 != 0xA) {
        goto block_23;
    }
    goto block_28;
block_23:
    goto block_32;
block_24:
    {
        register s32 case1_first_slot_r2 asm("r2") = temp_r0_2->slot;
        register s32 case1_first_destination_r0 asm("r0");
        register s32 case1_first_row_stride_r5 asm("r5");
        register u8 *case1_first_index_entry_r1 asm("r1");

        {
            register u8 *case1_first_index_base_r4 asm("r4") = D_0200E6C4;

            case1_first_index_entry_r1 = (u8 *)(
                case1_first_slot_r2 + (s32)case1_first_index_base_r4);
        }
        case1_first_row_stride_r5 = 0xD2;
        case1_first_destination_r0 = case1_first_slot_r2;
        case1_first_destination_r0 *= case1_first_row_stride_r5;
        case1_first_destination_r0 += *case1_first_index_entry_r1;
        {
            register u8 *case1_first_lookup_r6 asm("r6") = D_0200DE90;

            case1_first_destination_r0 += (s32) case1_first_lookup_r6;
        }
        case1_first_destination_r0 = *(u8 *) case1_first_destination_r0 * 0x25;
        case1_first_destination_r0 += var_ip;
        {
            register s32 case1_first_grid_stride_r4 asm("r4") = 0x1E5A;
            register s32 case1_first_grid_offset_r1 asm("r1") = case1_first_slot_r2;

            case1_first_grid_offset_r1 *= case1_first_grid_stride_r4;
            case1_first_destination_r0 += case1_first_grid_offset_r1;
        }
        {
            register u8 *case1_first_output_r5 asm("r5") = D_0200E6CE;

            case1_first_destination_r0 += (s32) case1_first_output_r5;
        }
        *(u8 *) case1_first_destination_r0 = temp_r3_2;
    }
    {
        register s32 case1_step_r6 asm("r6") = 1;

        asm volatile("" : "+r"(case1_step_r6));
        var_r8 += case1_step_r6;
    }
    {
        register s32 case1_second_slot_r2 asm("r2") = temp_r0_2->slot;
        register s32 case1_second_destination_r0 asm("r0");
        register s32 case1_second_row_stride_r3 asm("r3");
        register u8 *case1_second_index_entry_r1 asm("r1");

        {
            register u8 *case1_second_index_base_r0 asm("r0") = D_0200E6C4;

            case1_second_index_entry_r1 = (u8 *)(
                case1_second_slot_r2 + (s32)case1_second_index_base_r0);
        }
        case1_second_row_stride_r3 = 0xD2;
        case1_second_destination_r0 = case1_second_slot_r2;
        case1_second_destination_r0 *= case1_second_row_stride_r3;
        case1_second_destination_r0 += *case1_second_index_entry_r1;
        {
            register u8 *case1_second_lookup_r4 asm("r4") = D_0200DE90;

            case1_second_destination_r0 += (s32) case1_second_lookup_r4;
        }
        case1_second_destination_r0 = *(u8 *) case1_second_destination_r0 * 0x25;
        case1_second_destination_r0 += var_ip;
        {
            register s32 case1_second_grid_stride_r5 asm("r5") = 0x1E5A;
            register s32 case1_second_grid_offset_r1 asm("r1") = case1_second_slot_r2;

            case1_second_grid_offset_r1 *= case1_second_grid_stride_r5;
            case1_second_destination_r0 += case1_second_grid_offset_r1;
        }
        {
            register u8 *case1_second_output_r6 asm("r6") = D_0200E6CE;

            case1_second_destination_r0 += (s32) case1_second_output_r6;
        }
        {
            register u8 *case1_second_stream_r2 asm("r2") = var_r8;

            asm volatile("" : "+r"(case1_second_stream_r2));
            *(u8 *) case1_second_destination_r0 = *case1_second_stream_r2;
            asm volatile("");
        }
    }
    goto block_32;
block_26:
    {
        register s32 case2_first_slot_r2 asm("r2") = temp_r0_2->slot;
        register s32 case2_first_destination_r0 asm("r0");
        register s32 case2_first_row_stride_r5 asm("r5");
        register u8 *case2_first_index_entry_r1 asm("r1");

        {
            register u8 *case2_first_index_base_r4 asm("r4") = D_0200E6C4;

            case2_first_index_entry_r1 = (u8 *)(
                case2_first_slot_r2 + (s32)case2_first_index_base_r4);
        }
        case2_first_row_stride_r5 = 0xD2;
        case2_first_destination_r0 = case2_first_slot_r2;
        case2_first_destination_r0 *= case2_first_row_stride_r5;
        case2_first_destination_r0 += *case2_first_index_entry_r1;
        {
            register u8 *case2_first_lookup_r6 asm("r6") = D_0200DE90;

            case2_first_destination_r0 += (s32) case2_first_lookup_r6;
        }
        case2_first_destination_r0 = *(u8 *) case2_first_destination_r0 * 0x25;
        case2_first_destination_r0 += var_ip;
        {
            register s32 case2_first_grid_stride_r4 asm("r4") = 0x1E5A;
            register s32 case2_first_grid_offset_r1 asm("r1") = case2_first_slot_r2;

            case2_first_grid_offset_r1 *= case2_first_grid_stride_r4;
            case2_first_destination_r0 += case2_first_grid_offset_r1;
        }
        {
            register u8 *case2_first_output_r5 asm("r5") = D_0200E6CE;

            case2_first_destination_r0 += (s32) case2_first_output_r5;
        }
        *(u8 *) case2_first_destination_r0 = temp_r3_2;
    }
    {
        register s32 case2_first_step_r6 asm("r6") = 1;

        asm volatile("" : "+r"(case2_first_step_r6));
        var_r8 += case2_first_step_r6;
    }
    {
        register s32 case2_second_slot_r2 asm("r2") = temp_r0_2->slot;
        register s32 case2_second_destination_r0 asm("r0");
        register s32 case2_second_row_stride_r3 asm("r3");
        register u8 *case2_second_index_entry_r1 asm("r1");

        {
            register u8 *case2_second_index_base_r0 asm("r0") = D_0200E6C4;

            case2_second_index_entry_r1 = (u8 *)(
                case2_second_slot_r2 + (s32)case2_second_index_base_r0);
        }
        case2_second_row_stride_r3 = 0xD2;
        case2_second_destination_r0 = case2_second_slot_r2;
        case2_second_destination_r0 *= case2_second_row_stride_r3;
        case2_second_destination_r0 += *case2_second_index_entry_r1;
        {
            register u8 *case2_second_lookup_r4 asm("r4") = D_0200DE90;

            case2_second_destination_r0 += (s32) case2_second_lookup_r4;
        }
        case2_second_destination_r0 = *(u8 *) case2_second_destination_r0 * 0x25;
        case2_second_destination_r0 += var_ip;
        {
            register s32 case2_second_grid_stride_r5 asm("r5") = 0x1E5A;
            register s32 case2_second_grid_offset_r1 asm("r1") = case2_second_slot_r2;

            case2_second_grid_offset_r1 *= case2_second_grid_stride_r5;
            case2_second_destination_r0 += case2_second_grid_offset_r1;
        }
        {
            register u8 *case2_second_output_r6 asm("r6") = D_0200E6CE;

            case2_second_destination_r0 += (s32) case2_second_output_r6;
        }
        {
            register u8 *case2_second_stream_r2 asm("r2") = var_r8;

            *(u8 *) case2_second_destination_r0 = *case2_second_stream_r2;
        }
    }
    {
        register s32 case2_second_step_r3 asm("r3") = 1;

        asm volatile("" : "+r"(case2_second_step_r3));
        var_r8 += case2_second_step_r3;
    }
    {
        register s32 case2_third_slot_r2 asm("r2") = temp_r0_2->slot;
        register s32 case2_third_destination_r0 asm("r0");
        register s32 case2_third_row_stride_r5 asm("r5");
        register u8 *case2_third_index_entry_r1 asm("r1");

        {
            register u8 *case2_third_index_base_r4 asm("r4") = D_0200E6C4;

            case2_third_index_entry_r1 = (u8 *)(
                case2_third_slot_r2 + (s32)case2_third_index_base_r4);
        }
        case2_third_row_stride_r5 = 0xD2;
        case2_third_destination_r0 = case2_third_slot_r2;
        case2_third_destination_r0 *= case2_third_row_stride_r5;
        case2_third_destination_r0 += *case2_third_index_entry_r1;
        {
            register u8 *case2_third_lookup_r6 asm("r6") = D_0200DE90;

            case2_third_destination_r0 += (s32) case2_third_lookup_r6;
        }
        case2_third_destination_r0 = *(u8 *) case2_third_destination_r0 * 0x25;
        case2_third_destination_r0 += var_ip;
        {
            register s32 case2_third_grid_stride_r3 asm("r3") = 0x1E5A;
            register s32 case2_third_grid_offset_r1 asm("r1") = case2_third_slot_r2;

            case2_third_grid_offset_r1 *= case2_third_grid_stride_r3;
            case2_third_destination_r0 += case2_third_grid_offset_r1;
        }
        {
            register u8 *case2_third_output_r4 asm("r4") = D_0200E6CE;

            case2_third_destination_r0 += (s32) case2_third_output_r4;
        }
        {
            register u8 *case2_third_stream_r5 asm("r5") = var_r8;

            *(u8 *) case2_third_destination_r0 = *case2_third_stream_r5;
        }
    }
    goto block_32;
block_27:
    temp_r2_6 = temp_r0_2->slot;
    {
        register s32 case3_slot_r2 asm("r2") = temp_r2_6;
        register s32 case3_destination_r0 asm("r0");
        register s32 case3_row_stride_r4 asm("r4");
        register u8 *case3_index_entry_r1 asm("r1");

        {
            register u8 *case3_index_base_r6 asm("r6") = D_0200E6C4;

            case3_index_entry_r1 = (u8 *)(
                case3_slot_r2 + (s32)case3_index_base_r6);
        }
        case3_row_stride_r4 = 0xD2;
        case3_destination_r0 = case3_slot_r2;
        case3_destination_r0 *= case3_row_stride_r4;
        case3_destination_r0 += *case3_index_entry_r1;
        {
            register u8 *case3_lookup_r5 asm("r5") = D_0200DE90;

            case3_destination_r0 += (s32) case3_lookup_r5;
        }
        case3_destination_r0 = *(u8 *) case3_destination_r0 * 0x25;
        case3_destination_r0 += var_ip;
        {
            register s32 case3_grid_stride_r6 asm("r6") = 0x1E5A;
            register s32 case3_grid_offset_r1 asm("r1") = case3_slot_r2;

            case3_grid_offset_r1 *= case3_grid_stride_r6;
            case3_destination_r0 += case3_grid_offset_r1;
        }
        {
            register u8 *case3_output_r1 asm("r1") = D_0200E6CE;

            case3_destination_r0 += (s32) case3_output_r1;
        }
        *(u8 *) case3_destination_r0 = temp_r3_2;
    }
    goto block_32;
block_28:
    {
        register volatile u8 *opcode10_lookup_r3 asm("r3") = D_0200DE90;
        register volatile u8 *opcode10_index_r4 asm("r4") = D_0200E6C4;
        register s32 opcode10_slot_r2 asm("r2") = temp_r0_2->slot;
        register volatile u8 *opcode10_entry_r1 asm("r1") =
            (volatile u8 *)(
                opcode10_slot_r2 + (s32)opcode10_index_r4);
        register s32 opcode10_row_stride_r5 asm("r5") = 0xD2;
        register s32 opcode10_destination_r0 asm("r0") = opcode10_slot_r2;
        register s32 opcode10_grid_stride_r6 asm("r6");
        register s32 opcode10_grid_offset_r1 asm("r1");

        opcode10_destination_r0 *= opcode10_row_stride_r5;
        {
            register s32 opcode10_entry_value_r1 asm("r1") =
                *opcode10_entry_r1;

            asm volatile("add %0, %0, %1"
                         : "+r"(opcode10_destination_r0)
                         : "r"(opcode10_entry_value_r1));
        }
        opcode10_destination_r0 += (s32)opcode10_lookup_r3;
        opcode10_destination_r0 =
            *(volatile u8 *)opcode10_destination_r0 * 0x25;
        opcode10_destination_r0 += var_ip;
        opcode10_grid_stride_r6 = 0x1E5A;
        opcode10_grid_offset_r1 = opcode10_slot_r2;
        opcode10_grid_offset_r1 *= opcode10_grid_stride_r6;
        opcode10_destination_r0 += opcode10_grid_offset_r1;
        {
            register u8 *opcode10_output_r1 asm("r1") = D_0200E6CE;

            opcode10_destination_r0 += (s32)opcode10_output_r1;
        }
        {
            register s32 opcode10_zero_r1 asm("r1") = 0;

            *(u8 *)opcode10_destination_r0 = opcode10_zero_r1;
        }
        {
            register u32 opcode10_count_r2 asm("r2") = var_ip;

            asm volatile("" : "+r"(opcode10_count_r2));
            if (opcode10_count_r2 > 0x24U) {
                goto block_30;
            }
        }
        {
            register s32 opcode10_branch_slot_r1 asm("r1") = temp_r0_2->slot;
            register s32 opcode10_table_value_r0 asm("r0");
            register s32 opcode10_bank_r2 asm("r2");
            register s32 opcode10_update_r1 asm("r1");

            asm volatile(
                "add %0, %1, %2\n\t"
                "ldrb %0, [%0]"
                : "=&r"(opcode10_table_value_r0)
                : "r"(opcode10_branch_slot_r1),
                  "r"(opcode10_index_r4));
            opcode10_bank_r2 = opcode10_branch_slot_r1;
            opcode10_bank_r2 *= opcode10_row_stride_r5;
            opcode10_update_r1 = opcode10_bank_r2 + 1;
            opcode10_update_r1 =
                opcode10_table_value_r0 + opcode10_update_r1;
            opcode10_update_r1 += (s32)opcode10_lookup_r3;
            opcode10_table_value_r0 += opcode10_bank_r2;
            opcode10_table_value_r0 += (s32)opcode10_lookup_r3;
            opcode10_table_value_r0 =
                *(volatile u8 *)opcode10_table_value_r0;
            opcode10_table_value_r0 += 1;
            *(u8 *)opcode10_update_r1 = opcode10_table_value_r0;
        }
        goto block_31;
block_30:
        {
            register s32 opcode10_branch_slot_r1 asm("r1") = temp_r0_2->slot;
            register s32 opcode10_table_value_r0 asm("r0");
            register s32 opcode10_bank_r2 asm("r2");
            register s32 opcode10_update_r1 asm("r1");

            asm volatile(
                "add %0, %1, %2\n\t"
                "ldrb %0, [%0]"
                : "=&r"(opcode10_table_value_r0)
                : "r"(opcode10_branch_slot_r1),
                  "r"(opcode10_index_r4));
            opcode10_bank_r2 = opcode10_branch_slot_r1;
            opcode10_bank_r2 *= opcode10_row_stride_r5;
            opcode10_update_r1 = opcode10_bank_r2 + 1;
            opcode10_update_r1 =
                opcode10_table_value_r0 + opcode10_update_r1;
            opcode10_update_r1 += (s32)opcode10_lookup_r3;
            opcode10_table_value_r0 += opcode10_bank_r2;
            opcode10_table_value_r0 += (s32)opcode10_lookup_r3;
            opcode10_table_value_r0 =
                *(volatile u8 *)opcode10_table_value_r0;
            opcode10_table_value_r0 += 2;
            *(u8 *)opcode10_update_r1 = opcode10_table_value_r0;
        }
block_31:
        ;
    }
    func_0809885C(temp_r0_2);
    {
        register u32 print_advance_slot_r1 asm("r1") = temp_r0_2->slot;
        register u8 *print_advance_base_r3 asm("r3") = D_0200E6C4;
        register u32 print_advance_value_r0 asm("r0");

        print_advance_slot_r1 += (u32)print_advance_base_r3;
        print_advance_value_r0 = *(u8 *)print_advance_slot_r1;
        print_advance_value_r0 += 1;
        *(u8 *)print_advance_slot_r1 = print_advance_value_r0;
    }
    {
        register u32 opcode10_reset_zero_r4 asm("r4") = 0;

        asm volatile("mov %0, %1"
                     : "=r"(var_ip)
                     : "r"(opcode10_reset_zero_r4));
    }
block_32:
    {
        register s32 print_stream_step_r5 asm("r5") = 1;

        asm volatile("" : "+r"(print_stream_step_r5));
        var_r8 += print_stream_step_r5;
    }
    goto loop_42;
block_34:
    {
    volatile u8 *print_index_base;
    register volatile u8 *print_index_entry asm("r1");
    volatile u8 *print_lookup;
    register u8 *print_output asm("r10");
    register s32 print_row_stride asm("r9");
    register s32 print_grid_stride asm("r5");
    register s32 print_bank asm("r0");
    register s32 print_glyph asm("r0");
    s32 print_destination;
    s32 print_grid_offset;

    print_output =
        ({
            register u8 *print_output_seed_r6 asm("r6") = D_0200E6CE;

            asm volatile("" : "+r"(print_output_seed_r6));
            print_output_seed_r6;
        });
    print_lookup = D_0200DE90;
    print_index_base = D_0200E6C4;
    temp_r2_10 = temp_r0_2->slot;
    print_index_entry = print_index_base + temp_r2_10;
    {
        register s32 print_row_stride_seed_r0 asm("r0") = 0xD2;

        print_row_stride = print_row_stride_seed_r0;
    }
    print_bank = temp_r2_10 * print_row_stride;
    {
        register s32 print_index_value_r1 asm("r1") = *print_index_entry;

        asm volatile("add %0, %0, %1"
                     : "+r"(print_bank)
                     : "r"(print_index_value_r1));
        print_glyph = print_bank;
    }
    print_destination = print_lookup[print_glyph] * 0x25;
    print_destination += var_ip;
    print_grid_stride = 0x1E5A;
    print_grid_offset = temp_r2_10 * print_grid_stride;
    print_destination += print_grid_offset;
    print_destination += (s32)print_output;
    *(u8 *)print_destination = temp_r3;
    var_ip += 1;
    {
        register s32 print_next_step_r1 asm("r1") = 1;

        var_r8 += print_next_step_r1;
    }
    {
        register u8 *print_next_stream_r2 asm("r2") = var_r8;

        asm volatile("" : "+r"(print_next_stream_r2));
        temp_r3_3 = *print_next_stream_r2;
    }
    if (temp_r3_3 == 0) {
        goto block_36;
    }
    goto loop_13;
block_36:
    temp_r2_11 = temp_r0_2->slot;
    print_index_entry = print_index_base + temp_r2_11;
    print_bank = temp_r2_11 * print_row_stride;
    {
        register s32 print_index_value_r1 asm("r1") = *print_index_entry;

        asm volatile("add %0, %0, %1"
                     : "+r"(print_bank)
                     : "r"(print_index_value_r1));
        print_glyph = print_bank;
    }
    print_destination = print_lookup[print_glyph] * 0x25;
    print_destination += var_ip;
    print_grid_offset = temp_r2_11 * print_grid_stride;
    asm volatile("" : : "r"(temp_r2_11));
    print_destination += print_grid_offset;
    print_destination += (s32)print_output;
    *(u8 *)print_destination = temp_r3_3;
    {
        register u32 print_count_r3 asm("r3") = var_ip;

        asm volatile("" : "+r"(print_count_r3));
        if (print_count_r3 > 0x24U) {
            goto block_39;
        }
    }
    temp_r1_4 = temp_r0_2->slot;
    temp_r0_5 = D_0200E6C4[temp_r1_4];
    temp_r2_12 = print_row_stride * temp_r1_4;
    asm volatile(
        ".byte 0x51, 0x1C\n\t"
        ".byte 0x41, 0x18"
        : "=r"(var_r1_2)
        : "r"(temp_r0_5),
          "r"(temp_r2_12));
    var_r1_2 += (s32)print_lookup;
    var_r0_2 = D_0200DE90[temp_r0_5 + temp_r2_12] + 1;
    goto block_40;
block_39:
    temp_r1_5 = temp_r0_2->slot;
    temp_r0_6 = D_0200E6C4[temp_r1_5];
    temp_r2_13 = print_row_stride * temp_r1_5;
    asm volatile(
        ".byte 0x51, 0x1C\n\t"
        ".byte 0x41, 0x18"
        : "=r"(var_r1_2)
        : "r"(temp_r0_6),
          "r"(temp_r2_13));
    var_r1_2 += (s32)print_lookup;
    var_r0_2 = D_0200DE90[temp_r0_6 + temp_r2_13] + 2;
block_40:
    *var_r1_2 = var_r0_2;
    }
    func_0809885C(temp_r0_2);
    {
        register s32 print_slot_r1 asm("r1") = temp_r0_2->slot;
        register u8 *print_index_base_r4 asm("r4") = D_0200E6C4;
        register u32 print_index_value_r0 asm("r0");

        asm volatile("" : "+r"(print_slot_r1),
                          "+r"(print_index_base_r4));
        print_slot_r1 += (s32)print_index_base_r4;
        print_index_value_r0 = *(u8 *)print_slot_r1;
        print_index_value_r0 += 1;
        *(u8 *)print_slot_r1 = print_index_value_r0;
    }
loop_41:
    {
        register u32 print_reset_zero_r5 asm("r5") = 0;

        asm volatile("mov %0, %1"
                     : "=r"(var_ip)
                     : "r"(print_reset_zero_r5));
    }
loop_42:
    {
        register u8 *print_stream_check_r6 asm("r6") = var_r8;

        asm volatile("" : "+r"(print_stream_check_r6));
        if (*print_stream_check_r6 == 0) {
            goto block_44;
        }
    }
    goto loop_13;
block_44:
    if (!(temp_r0_2->flags & 0x20)) {
        goto block_48;
    }
    D_0200A890[1] = func_08094484(
        0x080ED620,
        0x080ED648,
        1U,
        ({
            register s32 popup_x_r3 asm("r3") = temp_r0_2->offset_x;
            register u32 popup_base_x_r5 asm("r5");

            popup_x_r3 += 1;
            popup_base_x_r5 = (u16)temp_r0_2->x;
            popup_x_r3 += popup_base_x_r5;
            (s16)(popup_x_r3 * 8);
        }),
        ({
            s32 popup_y = temp_r0_2->offset_y;
            u32 popup_base_y;

            popup_y += 1;
            popup_base_y = (u16)temp_r0_2->y;
            popup_y += popup_base_y;
            popup_y <<= 0x13;
            popup_y += 0x80000;
            popup_y >>= 0x10;
            popup_y;
        }),
        (u16) (s32) (u16) (D_0202166A + 2),
        (u16) (s32) D_0202166C,
        0x20,
        0);
    func_080972C8();
    {
    register volatile u16 *parser_keys_r4 asm("r4") = &D_0300000E;
    register u32 parser_key_mask_r5 asm("r5") = 3;
loop_46:
    func_080ED17C(1);
    {
        register u32 parser_test_r0 asm("r0");
        register u32 parser_keys_r1 asm("r1");

        parser_keys_r1 = *parser_keys_r4;
        parser_test_r0 = parser_key_mask_r5;
        asm volatile("" : "+r"(parser_test_r0));
        parser_test_r0 &= parser_keys_r1;
        if (!parser_test_r0) {
            goto loop_46;
        }
    }
    }
    func_08094554(D_0200A890[1]);
    func_08092E84(0x41);
block_48:
    {
        register u8 *case8_init_stream_r1 asm("r1") = sp14;

        func_080971AC(M2C_FIELD(case8_init_stream_r1, u8 *, 1));
    }
    var_r8 += 1;
    {
        register u8 *print_opcode_stream_r2 asm("r2") = sp14;

        if (M2C_FIELD(print_opcode_stream_r2, u8 *, 0) != 5) {
            goto block_50;
        }
    }
    goto block_66;
block_50:
    {
        register u8 *print_next_command_r4 asm("r4") = sp14;

        print_next_command_r4 += 2;
        sp14 = print_next_command_r4;
    }
    goto block_289;
    }
case 9:
    {
        register u8 *case9_stream_r5 asm("r5") = sp14;

        temp_r0_7 =
            func_0809716C(M2C_FIELD(case9_stream_r5, u8 *, 1));
    }
    var_r4 = &temp_r0_7->tiles[1];
    var_r5_2 = 1;
    {
    register s32 case9_bound_r0 asm("r0") = temp_r0_7->width - 1;

    {
        register u8 *case9_data_stream_r6 asm("r6") = sp14;

        case9_data_stream_r6 += 2;
        var_r8 = case9_data_stream_r6;
    }
    if (var_r5_2 >= case9_bound_r0) {
        goto block_58;
    }
    }
    var_r6_tiles = &D_02021664;
loop_54:
    {
        register u32 case9_tile_r1 asm("r1") = *var_r4;
        register u32 case9_mask_r2 asm("r2") = 0x3FF;
        register u32 case9_mask_copy_r0 asm("r0");

        asm volatile("" : "+r"(case9_mask_r2));
        case9_mask_copy_r0 = case9_mask_r2;
        asm volatile("" : "+r"(case9_mask_copy_r0));
        case9_tile_r1 &= case9_mask_copy_r0;
        temp_r1_7 = case9_tile_r1;
    }
    if (temp_r1_7 < *var_r6_tiles) {
        goto block_56;
    }
    if (temp_r1_7 < *var_r6_tiles + 0x40) {
        goto block_57;
    }
block_56:
    func_08097980((u16) (temp_r1_7 - D_02021670));
block_57:
    *var_r4 = (*var_r6_tiles + 6) | D_02021668;
    var_r4 += 1;
    var_r5_2 += 1;
    if (var_r5_2 < (s32) (temp_r0_7->width - 1)) {
        goto loop_54;
    }
block_58:
    temp_r4 = (u16) temp_r0_7->offset_x;
    temp_r5 = (u16) temp_r0_7->offset_y;
    temp_r6 = temp_r0_7->unk12;
    temp_r0_7->offset_x = 0;
    temp_r0_7->offset_y = -1;
    temp_r0_7->unk12 = 0;
    func_08097DA8(temp_r0_7, (u8 *)0x080ED944);
    var_r8 = func_08097DA8(temp_r0_7, var_r8);
    temp_r0_7->flags |= 2;
    {
        register u8 *case9_next_command_r3 asm("r3") = var_r8;

        case9_next_command_r3 += 1;
        sp14 = case9_next_command_r3;
    }
    temp_r0_7->offset_x = (s16) temp_r4;
    temp_r0_7->offset_y = (s16) temp_r5;
    temp_r0_7->unk12 = temp_r6;
    goto block_289;
case 10:
    {
    register s32 case10_counter_r5 asm("r5");

    {
        register u8 *case10_stream_r4 asm("r4") = sp14;

        temp_r0_8 =
            func_0809716C(M2C_FIELD(case10_stream_r4, u8 *, 1));
    }
    var_r4_2 = &temp_r0_8->tiles[1];
    case10_counter_r5 = 1;
    {
    register s32 case10_bound_r0 asm("r0") = temp_r0_8->width - 1;

    {
        register u8 *case10_data_stream_r6 asm("r6") = sp14;

        case10_data_stream_r6 += 2;
        var_r8 = case10_data_stream_r6;
    }
    if (case10_counter_r5 >= case10_bound_r0) {
        goto block_66;
    }
    }
    var_r6_tiles = &D_02021664;
loop_62:
    {
        register u32 case10_tile_r1 asm("r1") = *var_r4_2;
        register u32 case10_mask_r2 asm("r2") = 0x3FF;
        register u32 case10_mask_copy_r0 asm("r0");

        asm volatile("" : "+r"(case10_mask_r2));
        case10_mask_copy_r0 = case10_mask_r2;
        asm volatile("" : "+r"(case10_mask_copy_r0));
        case10_tile_r1 &= case10_mask_copy_r0;
        temp_r1_8 = case10_tile_r1;
    }
    if (temp_r1_8 < *var_r6_tiles) {
        goto block_64;
    }
    if (temp_r1_8 < *var_r6_tiles + 0x40) {
        goto block_65;
    }
block_64:
    func_08097980((u16) (temp_r1_8 - D_02021670));
block_65:
    *var_r4_2 = (*var_r6_tiles + 6) | D_02021668;
    var_r4_2 += 1;
    case10_counter_r5 += 1;
    if (case10_counter_r5 < (s32) (temp_r0_8->width - 1)) {
        goto loop_62;
    }
block_66:
    {
        register u8 *case10_next_command_r3 asm("r3") = var_r8;

        sp14 = case10_next_command_r3;
    }
    goto block_289;
    }
case 7:
    {
        register u8 *case7_stream_r4 asm("r4") = sp14;

        func_080971AC(case7_stream_r4[1]);
        map_entry = &D_0200A8A0;
#define D_0200A8A0 (*map_entry)
        if (0x1E & case7_stream_r4[2]) {
            goto block_70;
        }
    }
    map_entry->prior_selected = 0xFF;
block_70:
    if (map_entry->prior_selected == 0xFF) {
        goto block_72;
    }
    goto block_73;
block_72:
    {
        register u16 *case7_palette_low_r5 asm("r5");
        register u16 *case7_tile_low_r6 asm("r6");
        register u16 *case7_palette_long_sl asm("r10");
        register u16 *case7_tile_long_r9 asm("r9");

        D_0200A88C = func_08094484(
            0x080ED8F8,
            0x080ED92C,
            0U,
            (s16) ((u16) D_0200A8A0.x * 8),
            (s16) ((((u16) D_0200A8A0.y + 1) * 8) + ((D_0200A8A0.selected - D_0200A8A0.top) * 0x10)),
            ({
                case7_palette_low_r5 = &D_0202166A;
                case7_palette_long_sl = case7_palette_low_r5;
                (u16)(*case7_palette_low_r5 + 0xE);
            }),
            ({
                case7_tile_low_r6 = &D_0202166C;
                case7_tile_long_r9 = case7_tile_low_r6;
                *case7_tile_low_r6;
            }),
            0x20,
            0);
        M2C_FIELD(D_0200A890, struct WindowRecord98BB4 **, 0) = func_08094484(0x080ED578, 0x080ED5A0, 0U, (s16) ((((u16) D_0200A8A0.x + D_0200A8A0.width) - 1) * 8), (s16) (((u16) D_0200A8A0.y + 1) * 8), (u16) (s32)*case7_palette_low_r5, (u16) (s32)*case7_tile_low_r6, 0x20030, ({
            register u32 case7_zero_arg_r4 asm("r4");

            asm volatile("mov %0, r8" : "=r"(case7_zero_arg_r4));
            case7_zero_arg_r4;
        }));
        D_0200A890[1] = func_08094484(0x080ED620, 0x080ED648, 0U, (s16) ((((u16) D_0200A8A0.x + D_0200A8A0.width) - 1) * 8), (s16) ((((u16) D_0200A8A0.y + D_0200A8A0.height) - 2) * 8), (u16) (s32) (u16) (*({
            register u16 *case7_palette_view_r4 asm("r4") =
                case7_palette_long_sl;

            case7_palette_view_r4;
        }) + 2), (u16) (s32)*({
            register u16 *case7_tile_view_r4 asm("r4") =
                case7_tile_long_r9;

            case7_tile_view_r4;
        }), 0x20030, 0);
        D_0200A890[2] = func_08094484(0x080ED6C8, 0x080ED6F0, 0U, (s16) (((u16) D_0200A8A0.x + 1) * 8), (s16) ((((u16) D_0200A8A0.y + D_0200A8A0.height) - 1) * 8), (u16) (s32) (u16) (*({
            register u16 *case7_palette_view_r4 asm("r4") =
                case7_palette_long_sl;

            case7_palette_view_r4;
        }) + 4), (u16) (s32)*({
            register u16 *case7_tile_view_r4 asm("r4") =
                case7_tile_long_r9;

            case7_tile_view_r4;
        }), 0x20030, 0);
        D_0200A890[3] = func_08094484(0x080ED770, 0x080ED798, 0U, (s16) ((((u16) D_0200A8A0.x + D_0200A8A0.width) - 2) * 8), (s16) ((((u16) D_0200A8A0.y + D_0200A8A0.height) - 1) * 8), (u16) (s32) (u16) (*({
            register u16 *case7_palette_view_r4 asm("r4") =
                case7_palette_long_sl;

            case7_palette_view_r4;
        }) + 6), (u16) (s32)*({
            register u16 *case7_tile_view_r4 asm("r4") =
                case7_tile_long_r9;

            case7_tile_view_r4;
        }), 0x20030, ({
            register u32 case7_zero_arg_r6 asm("r6");

            asm volatile("mov %0, r8" : "=r"(case7_zero_arg_r6));
            case7_zero_arg_r6;
        }));
    }
    D_0200A880 = D_0200A8A0.selected;
    D_0200A881 = D_0200A8A0.top;
block_73:
    {
        register u8 *case7_count_base_r0 asm("r0") = D_0200E6C4;
        register s32 case7_count_r1 asm("r1") = D_0200A8A0.slot;

        case7_count_r1 += (s32)case7_count_base_r0;
        case7_count_r1 = *(u8 *)case7_count_r1;
        temp_r1_9 = case7_count_r1;
    }
    if ((u32) D_0200A8A0.selected < (u32) temp_r1_9) {
        goto block_79;
    }
    {
    register s32 clamp_selected_r0 asm("r0");
    register s32 clamp_zero_r3 asm("r3");
    register s32 clamp_top_r1 asm("r1");
    register s32 clamp_top_r2 asm("r2");

    clamp_selected_r0 = temp_r1_9 - 1;
    clamp_zero_r3 = 0;
    D_0200A8A0.selected = clamp_selected_r0;
    clamp_top_r1 = D_0200A8A0.top;
    if ((u32)clamp_top_r1 <= (u32) (u8) clamp_selected_r0) {
        goto block_83;
    }
    clamp_top_r2 = clamp_top_r1;
    temp_r0_10 = D_0200A8A0.height - 2;
    temp_r0_11 = (s32) (temp_r0_10 + (temp_r0_10 >> 0x1F)) >> 1;
    if (clamp_top_r2 < temp_r0_11) {
        goto block_78;
    }
    {
        register s32 clamp_new_top_r0 asm("r0") = temp_r0_11;

        asm volatile("sub %0, %1, %0"
                     : "+r"(clamp_new_top_r0)
                     : "r"(clamp_top_r2));
        D_0200A8A0.top = clamp_new_top_r0;
    }
    goto block_83;
block_78:
    D_0200A8A0.top = clamp_zero_r3;
    asm volatile("" : : "r"(clamp_zero_r3));
    goto block_83;
    }
block_79:
    temp_r2_14 = D_0200A8A0.selected - D_0200A8A0.top;
    if (temp_r2_14 < 0) {
        goto block_81;
    }
    temp_r0_12 = D_0200A8A0.height - 2;
    if (temp_r2_14 < (s32) ((s32) (temp_r0_12 + (temp_r0_12 >> 0x1F)) >> 1)) {
        goto block_82;
    }
block_81:
    D_0200A8A0.top = D_0200A8A0.selected;
    goto block_83;
block_82:
    {
        register s32 clamp_prior_top_r0 asm("r0") =
            D_0200A8A0.prior_top;

        asm volatile("" : "+r"(clamp_prior_top_r0));
        if (D_0200A8A0.top == clamp_prior_top_r0) {
            goto block_84;
        }
    }
block_83:
    D_0200A8A0.flags |= 2;
    D_0200A8A0.prior_selected = 0xFF;
    goto block_85;
block_84:
    func_080972C8();
block_85:
    sp18 = 0;
    D_0200A882 = 0;
loop_86:
    if (D_0200A8A0.flags & 2) {
        goto block_88;
    }
    goto block_153;
block_88:
    {
        u32 selected_now = D_0200A8A0.selected;
        register u32 prior_selected_r3 asm("r3") =
            D_0200A8A0.prior_selected;

        asm volatile("" : "+r"(prior_selected_r3));
        if (selected_now != prior_selected_r3) {
            goto block_90;
        }
    }
    goto block_150;
block_90:
    {
        register struct WindowRecord98BB4 **selection_record_ptr_r0
            asm("r0") = &D_0200A88C;
        register struct WindowRecord98BB4 *selection_record_r3 asm("r3");

        selection_record_r3 = *selection_record_ptr_r0;
        asm volatile(
            "ldrh r1, [r7, #6]\n\t"
            "add r1, #1\n\t"
            "lsl r1, #3\n\t"
            "ldrb r0, [r7, #22]\n\t"
            "ldrb r2, [r7, #20]\n\t"
            "sub r0, r2\n\t"
            "lsl r0, #4\n\t"
            "add r1, r0\n\t"
            "strh r1, [r3, #6]"
            : "+r"(selection_record_r3)
            : "r"(map_entry)
            : "r0", "r1", "r2", "cc", "memory");
    }
    temp_r2_15 = D_0200A8A0.top - D_0200A8A0.prior_top;
    temp_r1_10 = D_0200A8A0.height - 2;
    temp_r0_13 = (s32) (temp_r1_10 + (temp_r1_10 >> 0x1F)) >> 1;
    asm volatile("" :: "r"(temp_r1_10));
    asm volatile("" :: "r"(temp_r1_10));
    asm volatile("" :: "r"(temp_r1_10));
    asm volatile("" :: "r"(temp_r1_10));
    if (temp_r2_15 > temp_r0_13) {
        goto block_92;
    }
    temp_r6_2 = D_0200A8A0.prior_top - D_0200A8A0.top;
    if (temp_r6_2 <= temp_r0_13) {
        goto block_102;
    }
block_92:
    func_080986B4(D_0200A8A0.slot);
    {
        register u32 scroll_zero_r4 asm("r4") = 0;

        asm volatile("" : "+r"(scroll_zero_r4));
        var_r9 = scroll_zero_r4;
    }
    temp_r0_14 = D_0200A8A0.height - 2;
    if (var_r9 < (u32) ((s32) (temp_r0_14 + (temp_r0_14 >> 0x1F)) >> 1)) {
        goto block_94;
    }
    goto block_150;
block_94:
{
    register volatile u8 *scroll_index_r1 asm("r1") = D_0200E6C4;
    register s32 scroll_slot_r0 asm("r0") = D_0200A8A0.slot;
    register s32 scroll_slot_r4 asm("r4");
    register s32 scroll_row_r2 asm("r2");
    register volatile u8 *scroll_lookup_r5 asm("r5");

    asm volatile("add %0, %1, %0"
                 : "+r"(scroll_index_r1)
                 : "r"(scroll_slot_r0));
    scroll_slot_r4 = scroll_slot_r0;
    scroll_row_r2 = D_0200A8A0.top;
    asm volatile("ldrb %0, [%0]"
                 : "+r"(scroll_index_r1)
                 :
                 : "memory");
    if ((u32)scroll_row_r2 < (u32)scroll_index_r1) {
        goto block_96;
    }
    goto block_150;
block_96:
    scroll_lookup_r5 = D_0200DE90;
loop_97:
    {
        register s32 scroll_grid_stride_r0 asm("r0") = 0x1E5A;
        register s32 scroll_grid_offset_r1 asm("r1") = scroll_slot_r4;
        register s32 scroll_row_stride_r0 asm("r0");
        register s32 scroll_destination_r0 asm("r0");

        scroll_grid_offset_r1 *= scroll_grid_stride_r0;
        scroll_row_r2 += var_r9;
        scroll_row_stride_r0 = 0xD2;
        scroll_row_stride_r0 *= scroll_slot_r4;
        scroll_row_r2 += scroll_row_stride_r0;
        scroll_row_r2 += (s32)scroll_lookup_r5;
        scroll_row_r2 = *(volatile u8 *)scroll_row_r2;
        scroll_destination_r0 = scroll_row_r2 * 0x25;
        {
            register u8 *scroll_output_r2 asm("r2") = D_0200E6CE;

            scroll_destination_r0 += (s32)scroll_output_r2;
        }
        scroll_grid_offset_r1 += scroll_destination_r0;
        func_08097DA8(&D_0200A8A0, (void *)scroll_grid_offset_r1);
    }
    D_0200A8A0.offset_x = 0;
    D_0200A8A0.offset_y = (u16) D_0200A8A0.offset_y + 2;
    {
        register u32 scroll_step_r6 asm("r6") = 1;

        asm volatile("" : "+r"(scroll_step_r6));
        var_r9 += scroll_step_r6;
    }
    temp_r0_15 = D_0200A8A0.height - 2;
    if (var_r9 < (u32) ((s32) (temp_r0_15 + (temp_r0_15 >> 0x1F)) >> 1)) {
        goto block_99;
    }
    goto block_150;
block_99:
    {
        register s32 scroll_count_r0 asm("r0") = var_r9;
        register s32 scroll_compare_r3 asm("r3");

        scroll_row_r2 = D_0200A8A0.top;
        scroll_compare_r3 = scroll_row_r2 + scroll_count_r0;
        scroll_index_r1 = D_0200E6C4;
        scroll_slot_r0 = D_0200A8A0.slot;
        asm volatile("add %0, %1, %0"
                     : "+r"(scroll_index_r1)
                     : "r"(scroll_slot_r0));
        scroll_slot_r4 = scroll_slot_r0;
        asm volatile("ldrb %0, [%0]"
                     : "+r"(scroll_index_r1)
                     :
                     : "memory");
        if ((u32)scroll_compare_r3 < (u32)scroll_index_r1) {
            goto loop_97;
        }
    }
    goto block_150;
}
block_102:
    if ((u32) D_0200A8A0.top > (u32) D_0200A8A0.prior_top) {
        goto block_104;
    }
    goto block_127;
block_104:
    {
        register s32 cleanup_seed_r1 asm("r1") = 1;

        var_r8_3 = cleanup_seed_r1;
    }
    {
        register s32 cleanup_row_count_seed_r3 asm("r3") = 0;

        asm volatile("" : "+r"(cleanup_row_count_seed_r3));
        var_r9_2 = cleanup_row_count_seed_r3;
    }
    {
        register s32 cleanup_row_bound_r0 asm("r0");

        asm volatile("lsl %0, %1, #1"
                     : "=r"(cleanup_row_bound_r0)
                     : "r"(temp_r2_15));
        if (var_r9_2 >= (u32)cleanup_row_bound_r0) {
            goto block_111;
        }
    }
    {
    register s32 cleanup_column_r5 asm("r5");
    register s32 cleanup_next_row_r4 asm("r4");
    register s32 cleanup_next_r8_sl asm("r10");

loop_105:
    cleanup_column_r5 = 1;
    temp_r1_11 = D_0200A8A0.width;
    {
        register s32 cleanup_bound_r0 asm("r0") = temp_r1_11 - 1;

        cleanup_next_row_r4 = var_r9_2 + 1;
        {
            register s32 cleanup_step_r6 asm("r6") = 1;

            asm volatile("" : "+r"(cleanup_step_r6));
            cleanup_step_r6 += var_r8_3;
            cleanup_next_r8_sl = cleanup_step_r6;
        }
        if (cleanup_column_r5 >= cleanup_bound_r0) {
            goto block_110;
        }
    }
loop_106:
    {
        register u32 cleanup_tile_r1 asm("r1");
        register u32 cleanup_mask_r2 asm("r2");
        register u32 cleanup_mask_copy_r0 asm("r0");

        {
            register s32 cleanup_tile_index_r1 asm("r1");
            register s32 cleanup_tile_address_r0 asm("r0");

            {
                register s32 cleanup_row_product_r0 asm("r0") = var_r8_3;

                asm volatile("mul %0, %1"
                             : "+r"(cleanup_row_product_r0)
                             : "r"(temp_r1_11)
                             : "cc");
                cleanup_tile_index_r1 = cleanup_row_product_r0;
                asm volatile("" : "+r"(cleanup_tile_index_r1));
            }
            cleanup_tile_index_r1 =
                cleanup_column_r5 + cleanup_tile_index_r1;
            cleanup_tile_index_r1 <<= 1;
            cleanup_tile_address_r0 = (s32)map_entry;
            cleanup_tile_address_r0 += 0x1E;
            cleanup_tile_address_r0 += cleanup_tile_index_r1;
            cleanup_tile_r1 = *(u16 *)cleanup_tile_address_r0;
        }
        cleanup_mask_r2 = 0x3FF;
        asm volatile("" : "+r"(cleanup_mask_r2));
        cleanup_mask_copy_r0 = cleanup_mask_r2;
        asm volatile("" : "+r"(cleanup_mask_copy_r0));
        cleanup_tile_r1 &= cleanup_mask_copy_r0;
        temp_r1_12 = cleanup_tile_r1;
    }
    if (temp_r1_12 < (u32) D_02021664) {
        goto block_108;
    }
    if (temp_r1_12 < (u32) (D_02021664 + 0x40)) {
        goto block_109;
    }
block_108:
    func_08097980((u16) (temp_r1_12 - D_02021670));
block_109:
    cleanup_column_r5 += 1;
    temp_r1_11 = D_0200A8A0.width;
    if (cleanup_column_r5 < (s32) (temp_r1_11 - 1)) {
        goto loop_106;
    }
block_110:
    var_r8_3 = cleanup_next_r8_sl;
    var_r9_2 = cleanup_next_row_r4;
    if (var_r9_2 < (u32) ((D_0200A8A0.top - D_0200A8A0.prior_top) * 2)) {
        goto loop_105;
    }
block_111:
    }
    {
        register s32 first_row_seed_r3 asm("r3") = 1;

        asm volatile("" : "+r"(first_row_seed_r3));
        var_r8_4 = first_row_seed_r3;
    }
    goto loop_116;
block_112:
{
    register s32 copy_column_r5 asm("r5") = 1;
    register s32 copy_width_r3 asm("r3") = D_0200A8A0.width;
    register s32 copy_bound_r0 asm("r0") = copy_width_r3 - 1;
    register s32 copy_next_sl asm("r10");
    register u16 *copy_tiles_r4 asm("r4");

    {
        register s32 copy_next_seed_r4 asm("r4") = 1;

        asm volatile("" : "+r"(copy_next_seed_r4));
        copy_next_sl = copy_next_seed_r4;
        copy_next_sl += var_r8_4;
    }
    if (copy_column_r5 >= copy_bound_r0) {
        goto block_115;
    }
    copy_tiles_r4 = D_0200A8A0.tiles;
loop_114:
    *(u16 *)({
        register s32 copy_destination_r2 asm("r2") = var_r8_4;

        copy_destination_r2 *= copy_width_r3;
        copy_destination_r2 =
            copy_column_r5 + copy_destination_r2;
        copy_destination_r2 <<= 1;
        copy_destination_r2 =
            (s32)copy_tiles_r4 + copy_destination_r2;
        copy_destination_r2;
    }) =
        *(u16 *)({
            register s32 copy_source_r0 asm("r0") = D_0200A8A0.top;
            register s32 copy_prior_r1 asm("r1") = D_0200A8A0.prior_top;

            copy_source_r0 -= copy_prior_r1;
            copy_source_r0 <<= 1;
            copy_source_r0 += var_r8_4;
            copy_source_r0 *= copy_width_r3;
            copy_source_r0 = copy_column_r5 + copy_source_r0;
            copy_source_r0 <<= 1;
            copy_source_r0 =
                (s32)copy_tiles_r4 + copy_source_r0;
            copy_source_r0;
        });
    copy_column_r5 += 1;
    copy_width_r3 = D_0200A8A0.width;
    copy_bound_r0 = copy_width_r3 - 1;
    if (copy_column_r5 < copy_bound_r0) {
        goto loop_114;
    }
block_115:
    var_r8_4 = copy_next_sl;
}
loop_116:
    {
        register s32 copy_height_r0 asm("r0") = D_0200A8A0.height;
        register s32 copy_difference_r1 asm("r1") = D_0200A8A0.top;
        register s32 copy_prior_r2 asm("r2") = D_0200A8A0.prior_top;

        copy_difference_r1 -= copy_prior_r2;
        copy_difference_r1 <<= 1;
        copy_difference_r1 += 1;
        copy_difference_r1 = copy_height_r0 - copy_difference_r1;
        if (var_r8_4 < copy_difference_r1) {
            goto block_112;
        }
        copy_height_r0 -= 1;
        if (var_r8_4 < copy_height_r0) {
            goto loop_119;
        }
    }
    goto block_150;
loop_119:
{
    register s32 first_column_r5 asm("r5");
    register s32 first_next_r6 asm("r6");
    register s32 first_sign_r9 asm("r9");
    register s32 first_width_r1 asm("r1");
    register s32 first_bound_r0 asm("r0");
    register u16 *first_tiles_r3 asm("r3");

    first_column_r5 = 1;
    first_width_r1 = D_0200A8A0.width;
    first_bound_r0 = first_width_r1 - 1;
    first_next_r6 = var_r8_4 - 1;
    first_sign_r9 = var_r8_4 >> 0x1F;
    {
        register s32 first_second_next_r3 asm("r3") = var_r8_4;

        first_second_next_r3 += 2;
        sp24 = first_second_next_r3;
    }
    if (first_column_r5 >= first_bound_r0) {
        goto block_122;
    }
    first_tiles_r3 = D_0200A8A0.tiles;
    {
        register s32 first_adjacent_row_r4 asm("r4") = var_r8_4;

        first_adjacent_row_r4 += 1;
        sp28 = first_adjacent_row_r4;
    }
    var_ip_tiles = &D_02021664;
    var_sl_attr = &D_02021668;
loop_121:
    *(u16 *)({
        register s32 first_product_r4 asm("r4") = var_r8_4;
        register s32 first_destination_r1 asm("r1");

        asm volatile("mul %0, %1"
                     : "+r"(first_product_r4)
                     : "r"(first_width_r1)
                     : "cc");
        first_destination_r1 = first_product_r4;
        asm volatile("" : "+r"(first_destination_r1));
        first_destination_r1 =
            first_column_r5 + first_destination_r1;
        first_destination_r1 <<= 1;
        first_destination_r1 =
            (s32)first_tiles_r3 + first_destination_r1;
        first_destination_r1;
    }) =
        (temp_r2_17 =
             (*var_ip_tiles + 1) |
             *({
                 register u16 *first_attr_r4 asm("r4") = var_sl_attr;

                 first_attr_r4;
             }));
    *(u16 *)({
        register s32 first_second_width_r0 asm("r0") =
            D_0200A8A0.width;
        register s32 first_second_row_r1 asm("r1") = sp28;

        first_second_width_r0 *= first_second_row_r1;
        asm volatile("add %0, %1, %0"
                     : "+r"(first_second_width_r0)
                     : "r"(first_column_r5), "r"(temp_r2_17));
        first_second_width_r0 <<= 1;
        asm volatile("add %0, %1, %0"
                     : "+r"(first_second_width_r0)
                     : "r"(first_tiles_r3), "r"(temp_r2_17));
        first_second_width_r0;
    }) =
        temp_r2_17;
    first_column_r5 += 1;
    first_width_r1 = D_0200A8A0.width;
    first_bound_r0 = first_width_r1 - 1;
    if (first_column_r5 < first_bound_r0) {
        goto loop_121;
    }
block_122:
    D_0200A8A0.offset_x = 0;
    D_0200A8A0.offset_y = first_next_r6;
    {
        register s32 first_average_value_r2 asm("r2") = var_r8_4;
        register s32 first_average_sign_r3 asm("r3") = first_sign_r9;
        register s32 first_average_r0 asm("r0");
        register s32 first_top_r5 asm("r5");
        register s32 first_item_r4 asm("r4");
        register s32 first_slot_r3 asm("r3");
        register u8 *first_index_base_r6 asm("r6");

        asm volatile(
            "sub %0, %1, %2\n\t"
            "asr %0, %0, #1"
            : "=r"(first_average_r0)
            : "r"(first_average_value_r2),
              "r"(first_average_sign_r3)
            : "cc");
        first_top_r5 = D_0200A8A0.top;
        first_item_r4 = first_average_r0 + first_top_r5;
        first_slot_r3 = D_0200A8A0.slot;
        first_index_base_r6 = D_0200E6C4;
        {
            register s32 first_limit_address_r0 asm("r0") =
                first_slot_r3 + (s32)first_index_base_r6;

            if (first_item_r4 >= *(u8 *)first_limit_address_r0) {
                goto block_124;
            }
        }
        {
            register s32 first_grid_offset_r1 asm("r1") = first_slot_r3;
            register s32 first_grid_stride_r0 asm("r0") = 0x1E5A;
            register s32 first_row_address_r0 asm("r0");

            first_grid_offset_r1 *= first_grid_stride_r0;
            {
                register u8 *first_lookup_r2 asm("r2") = D_0200DE90;

                first_row_address_r0 = 0xD2;
                first_row_address_r0 *= first_slot_r3;
                first_row_address_r0 =
                    first_item_r4 + first_row_address_r0;
                first_row_address_r0 += (s32) first_lookup_r2;
            }
            first_row_address_r0 = *(u8 *) first_row_address_r0 * 0x25;
            {
                register u8 *first_output_r2 asm("r2") = D_0200E6CE;

                first_row_address_r0 += (s32) first_output_r2;
            }
            first_grid_offset_r1 += first_row_address_r0;
            func_08097DA8(&D_0200A8A0, (void *) first_grid_offset_r1);
        }
    }
block_124:
    {
        register s32 first_resume_r0 asm("r0") = sp24;

        var_r8_4 = first_resume_r0;
    }
    if (var_r8_4 < (s32) (D_0200A8A0.height - 1)) {
        goto loop_119;
    }
    goto block_150;
}
block_127:
    if ((u32) D_0200A8A0.top < (u32) D_0200A8A0.prior_top) {
        goto block_129;
    }
    goto block_150;
block_129:
    var_r8_5 = temp_r1_10;
    {
        register u32 mirror_zero_r1 asm("r1") = 0;

        asm volatile("" : "+r"(mirror_zero_r1));
        var_r9_3 = mirror_zero_r1;
    }
    if (var_r9_3 >= (u32) (temp_r6_2 * 2)) {
        goto block_136;
    }
    {
    register s32 mirror_column_r5 asm("r5");

loop_130:
    mirror_column_r5 = 1;
    temp_r1_13 = D_0200A8A0.width;
    if (mirror_column_r5 >= (s32) (temp_r1_13 - 1)) {
        goto block_135;
    }
loop_131:
    {
        register u32 mirror_tile_r1 asm("r1");
        register u32 mirror_mask_r3 asm("r3");
        register u32 mirror_mask_copy_r0 asm("r0");

        {
            register s32 mirror_tile_index_r1 asm("r1");
            register s32 mirror_tile_address_r0 asm("r0");
            register s32 mirror_row_product_r2 asm("r2") = var_r8_5;

            asm volatile("mul %0, %1"
                         : "+r"(mirror_row_product_r2)
                         : "r"(temp_r1_13)
                         : "cc");
            mirror_tile_index_r1 = mirror_row_product_r2;
            asm volatile("" : "+r"(mirror_tile_index_r1));
            mirror_tile_index_r1 =
                mirror_column_r5 + mirror_tile_index_r1;
            mirror_tile_index_r1 <<= 1;
            mirror_tile_address_r0 = (s32)map_entry;
            mirror_tile_address_r0 += 0x1E;
            mirror_tile_address_r0 += mirror_tile_index_r1;
            mirror_tile_r1 = *(u16 *)mirror_tile_address_r0;
        }
        mirror_mask_r3 = 0x3FF;
        asm volatile("" : "+r"(mirror_mask_r3));
        mirror_mask_copy_r0 = mirror_mask_r3;
        asm volatile("" : "+r"(mirror_mask_copy_r0));
        mirror_tile_r1 &= mirror_mask_copy_r0;
        temp_r1_14 = mirror_tile_r1;
    }
    if (temp_r1_14 < (u32) D_02021664) {
        goto block_133;
    }
    if (temp_r1_14 < (u32) (D_02021664 + 0x40)) {
        goto block_134;
    }
block_133:
    func_08097980((u16) (temp_r1_14 - D_02021670));
block_134:
    mirror_column_r5 += 1;
    temp_r1_13 = D_0200A8A0.width;
    if (mirror_column_r5 < (s32) (temp_r1_13 - 1)) {
        goto loop_131;
    }
block_135:
    var_r8_5 -= 1;
    var_r9_3 += 1;
    if (var_r9_3 < (u32) ((D_0200A8A0.prior_top - D_0200A8A0.top) * 2)) {
        goto loop_130;
    }
block_136:
    }
    var_r8_6 = D_0200A8A0.height - 2;
    goto loop_142;
block_138:
{
    register s32 mirror_copy_column_r5 asm("r5") = 1;
    register s32 mirror_copy_width_r3 asm("r3") = D_0200A8A0.width;
    register s32 mirror_copy_bound_r0 asm("r0") =
        mirror_copy_width_r3 - 1;
    register u16 *mirror_copy_tiles_r4 asm("r4");

    if (mirror_copy_column_r5 >= mirror_copy_bound_r0) {
        goto block_141;
    }
    mirror_copy_tiles_r4 = D_0200A8A0.tiles;
    do {
        register s32 mirror_copy_destination_r2 asm("r2") = var_r8_6;
        register s32 mirror_copy_source_r0 asm("r0");
        register s32 mirror_copy_row_r6 asm("r6");

        mirror_copy_destination_r2 *= mirror_copy_width_r3;
        mirror_copy_destination_r2 =
            mirror_copy_column_r5 + mirror_copy_destination_r2;
        mirror_copy_destination_r2 <<= 1;
        mirror_copy_destination_r2 =
            (s32)mirror_copy_tiles_r4 + mirror_copy_destination_r2;
        mirror_copy_source_r0 = D_0200A8A0.prior_top;
        mirror_copy_source_r0 -= D_0200A8A0.top;
        mirror_copy_source_r0 <<= 1;
        mirror_copy_row_r6 = var_r8_6;
        asm volatile("" : "+r"(mirror_copy_row_r6));
        mirror_copy_source_r0 =
            mirror_copy_row_r6 - mirror_copy_source_r0;
        mirror_copy_source_r0 *= mirror_copy_width_r3;
        mirror_copy_source_r0 =
            mirror_copy_column_r5 + mirror_copy_source_r0;
        mirror_copy_source_r0 <<= 1;
        mirror_copy_source_r0 =
            (s32)mirror_copy_tiles_r4 + mirror_copy_source_r0;
        *(u16 *)mirror_copy_destination_r2 =
            *(u16 *)mirror_copy_source_r0;
        mirror_copy_column_r5 += 1;
        mirror_copy_width_r3 = D_0200A8A0.width;
        mirror_copy_bound_r0 = mirror_copy_width_r3 - 1;
    } while (mirror_copy_column_r5 < mirror_copy_bound_r0);
block_141:
    ;
}
    var_r8_6 -= 1;
loop_142:
    {
        s32 mirror_limit =
            (s32) ((D_0200A8A0.prior_top - D_0200A8A0.top) * 2);

        if (var_r8_6 > mirror_limit) {
            goto block_138;
        }
        var_r8_7 = var_r8_6 - 1;
        asm volatile("" :: "r"(mirror_limit));
    }
    {
        register s32 mirror_exit_r2 asm("r2") = var_r8_7;

        asm volatile("" : "+r"(mirror_exit_r2));
        if (mirror_exit_r2 <= 0) {
            goto block_150;
        }
    }
loop_144:
{
    register s32 mirror_column_r5 asm("r5");
    register s32 mirror_next_r6 asm("r6");
    register s32 mirror_sign_r9 asm("r9");
    register s32 mirror_width_r1 asm("r1");
    register s32 mirror_bound_r0 asm("r0");
    register u16 *mirror_tiles_r3 asm("r3");

    mirror_column_r5 = 1;
    mirror_width_r1 = D_0200A8A0.width;
    mirror_bound_r0 = mirror_width_r1 - 1;
    mirror_next_r6 = var_r8_7 - 1;
    {
        register s32 mirror_sign_seed_r3 asm("r3") = var_r8_7;

        asm volatile("" : "+r"(mirror_sign_seed_r3));
        mirror_sign_seed_r3 >>= 0x1F;
        mirror_sign_r9 = mirror_sign_seed_r3;
    }
    {
        register s32 mirror_previous_row_r4 asm("r4") = var_r8_7;

        mirror_previous_row_r4 -= 2;
        sp1C = mirror_previous_row_r4;
    }
    if (mirror_column_r5 >= mirror_bound_r0) {
        goto block_147;
    }
    mirror_tiles_r3 = D_0200A8A0.tiles;
    sp28 = var_r8_7 + 1;
    {
    register u32 *mirror_tiles_ip asm("r12") =
        ({
            register u32 *mirror_tiles_seed_r2 asm("r2") =
                &D_02021664;

            asm volatile("" : "+r"(mirror_tiles_seed_r2));
            mirror_tiles_seed_r2;
        });
    register u16 *mirror_attr_sl asm("r10") =
        ({
            register u16 *mirror_attr_seed_r4 asm("r4") =
                &D_02021668;

            asm volatile("" : "+r"(mirror_attr_seed_r4));
            mirror_attr_seed_r4;
        });

loop_146:
    *(u16 *)({
        register s32 mirror_fill_product_r0 asm("r0") = var_r8_7;
        register s32 mirror_fill_destination_r1 asm("r1");

        asm volatile("mul %0, %1"
                     : "+r"(mirror_fill_product_r0)
                     : "r"(mirror_width_r1)
                     : "cc");
        mirror_fill_destination_r1 = mirror_fill_product_r0;
        asm volatile("" : "+r"(mirror_fill_destination_r1));
        mirror_fill_destination_r1 =
            mirror_column_r5 + mirror_fill_destination_r1;
        mirror_fill_destination_r1 <<= 1;
        mirror_fill_destination_r1 =
            (s32)mirror_tiles_r3 + mirror_fill_destination_r1;
        mirror_fill_destination_r1;
    }) =
        (temp_r2_18 =
             (*({
                  register u32 *mirror_tiles_r4 asm("r4") =
                      mirror_tiles_ip;

                  mirror_tiles_r4;
              }) +
              1) |
             *({
                 register u16 *mirror_attr_r4 asm("r4") =
                     mirror_attr_sl;

                 mirror_attr_r4;
             }));
    *(u16 *)({
        register s32 mirror_second_width_r0 asm("r0") =
            D_0200A8A0.width;
        register s32 mirror_second_row_r1 asm("r1") = sp28;

        mirror_second_width_r0 *= mirror_second_row_r1;
        asm volatile("add %0, %1, %0"
                     : "+r"(mirror_second_width_r0)
                     : "r"(mirror_column_r5), "r"(temp_r2_18));
        mirror_second_width_r0 <<= 1;
        asm volatile("add %0, %1, %0"
                     : "+r"(mirror_second_width_r0)
                     : "r"(mirror_tiles_r3), "r"(temp_r2_18));
        mirror_second_width_r0;
    }) =
        temp_r2_18;
    mirror_column_r5 += 1;
    mirror_width_r1 = D_0200A8A0.width;
    mirror_bound_r0 = mirror_width_r1 - 1;
    if (mirror_column_r5 < mirror_bound_r0) {
        goto loop_146;
    }
    }
block_147:
    D_0200A8A0.offset_x = 0;
    D_0200A8A0.offset_y = mirror_next_r6;
    {
        register s32 mirror_average_value_r2 asm("r2") = var_r8_7;
        register s32 mirror_average_sign_r3 asm("r3") = mirror_sign_r9;
        register s32 mirror_average_r0 asm("r0");
        register s32 mirror_top_r5 asm("r5");
        register s32 mirror_item_r4 asm("r4");
        register s32 mirror_slot_r3 asm("r3");
        register u8 *mirror_index_base_r6 asm("r6");

        asm volatile(
            "sub %0, %1, %2\n\t"
            "asr %0, %0, #1"
            : "=r"(mirror_average_r0)
            : "r"(mirror_average_value_r2),
              "r"(mirror_average_sign_r3)
            : "cc");
        mirror_top_r5 = D_0200A8A0.top;
        mirror_item_r4 = mirror_average_r0 + mirror_top_r5;
        mirror_slot_r3 = D_0200A8A0.slot;
        mirror_index_base_r6 = D_0200E6C4;
        {
            register s32 mirror_limit_address_r0 asm("r0") =
                mirror_slot_r3 + (s32)mirror_index_base_r6;

            if (mirror_item_r4 >= *(u8 *)mirror_limit_address_r0) {
                goto block_149;
            }
        }
        {
        register s32 mirror_grid_offset_r1 asm("r1") = mirror_slot_r3;
        register s32 mirror_grid_stride_r0 asm("r0") = 0x1E5A;
        register s32 mirror_row_address_r0 asm("r0");

        mirror_grid_offset_r1 *= mirror_grid_stride_r0;
        {
            register u8 *mirror_lookup_r2 asm("r2") = D_0200DE90;

            mirror_row_address_r0 = 0xD2;
            mirror_row_address_r0 *= mirror_slot_r3;
            mirror_row_address_r0 =
                mirror_item_r4 + mirror_row_address_r0;
            mirror_row_address_r0 += (s32)mirror_lookup_r2;
        }
        mirror_row_address_r0 = *(u8 *)mirror_row_address_r0 * 0x25;
        {
            register u8 *mirror_output_r2 asm("r2") = D_0200E6CE;

            mirror_row_address_r0 += (s32)mirror_output_r2;
        }
        mirror_grid_offset_r1 += mirror_row_address_r0;
        func_08097DA8(&D_0200A8A0, (void *) mirror_grid_offset_r1);
        }
    }
block_149:
    {
        register s32 mirror_resume_r0 asm("r0") = sp1C;

        var_r8_7 = mirror_resume_r0;
        if (mirror_resume_r0 > 0) {
            goto loop_144;
        }
    }
}
block_150:
    D_0200A880 = D_0200A8A0.selected;
    D_0200A881 = D_0200A8A0.top;
    asm volatile("" : : : "memory");
    D_0200A8A0.prior_selected = D_0200A8A0.selected;
    D_0200A8A0.prior_top = D_0200A8A0.top;
    if (({
            register s32 return_state_r1 asm("r1") = sp18;

            return_state_r1;
        }) == 0) {
        goto block_152;
    }
    asm volatile(
        ".short (0xE000 | (((.Lsub_08098BB4_return - . - 4) >> 1) & 0x7FF))");
block_152:
    func_080972C8();
block_153:
{
    register struct WindowRecord98BB4 **arrow_table_r5 asm("r5");

    if (D_0200A8A0.top == 0) {
        goto block_155;
    }
    {
        register struct WindowRecord98BB4 **clear_table_r2 asm("r2") =
            D_0200A890;
        register struct WindowRecord98BB4 *clear_record_r0 asm("r0") =
            *clear_table_r2;
        register u32 clear_flags_r1 asm("r1") = clear_record_r0->flags;
        register u32 clear_mask_r2 asm("r2") = 0xFFFDFFFF;

        clear_flags_r1 &= clear_mask_r2;
        clear_record_r0->flags = clear_flags_r1;
    }
    arrow_table_r5 = D_0200A890;
    goto block_156;
block_155:
    {
        register struct WindowRecord98BB4 **set_table_r3 asm("r3") =
            D_0200A890;
        register struct WindowRecord98BB4 *set_record_r0 asm("r0") =
            *set_table_r3;
        register u32 set_flags_r1 asm("r1") = set_record_r0->flags;
        register u32 set_mask_r2 asm("r2") = 0x20000;

        set_flags_r1 |= set_mask_r2;
        set_record_r0->flags = set_flags_r1;
        arrow_table_r5 = set_table_r3;
    }
block_156:
    {
    register struct WindowRecord98BB4 *upper_record_r0 asm("r0");
    register u32 upper_flags_r1 asm("r1");

    {
    register s32 upper_arrow_top_r4 asm("r4") = D_0200A8A0.top;
    register volatile u8 *upper_arrow_index_r3 asm("r3") = D_0200E6C4;
    register s32 upper_arrow_slot_r0 asm("r0") = D_0200A8A0.slot;
    register volatile u8 *upper_arrow_entry_r0 asm("r0");
    register s32 upper_arrow_count_r2 asm("r2");

    upper_arrow_entry_r0 = (volatile u8 *)upper_arrow_slot_r0;
    asm volatile("add %0, %0, %1"
                 : "+r"(upper_arrow_entry_r0)
                 : "r"(upper_arrow_index_r3));
    upper_arrow_count_r2 = *upper_arrow_entry_r0;
    asm volatile("" : "+r"(upper_arrow_count_r2));
    temp_r0_16 = D_0200A8A0.height - 2;
    if (upper_arrow_top_r4 >=
        upper_arrow_count_r2 -
            ((s32) (temp_r0_16 + (temp_r0_16 >> 0x1F)) >> 1)) {
        goto block_158;
    }
    }
    upper_record_r0 = arrow_table_r5[1];
    upper_flags_r1 = upper_record_r0->flags;
    {
        register u32 upper_clear_mask_r2 asm("r2") = 0xFFFDFFFF;

        upper_flags_r1 &= upper_clear_mask_r2;
    }
    goto block_159;
block_158:
    upper_record_r0 = arrow_table_r5[1];
    upper_flags_r1 = upper_record_r0->flags;
    {
        register u32 upper_set_mask_r2 asm("r2") = 0x20000;

        upper_flags_r1 |= upper_set_mask_r2;
    }
block_159:
    upper_record_r0->flags = upper_flags_r1;
    }
    if (D_0200A8A0.top == 0) {
        goto block_161;
    }
    {
    register struct WindowRecord98BB4 *middle_record_r0 asm("r0");
    register u32 middle_flags_r1 asm("r1");

    middle_record_r0 = arrow_table_r5[2];
    middle_flags_r1 = middle_record_r0->flags;
    {
        register u32 middle_clear_mask_r2 asm("r2") = 0xFFFDFFFF;

        middle_flags_r1 &= middle_clear_mask_r2;
    }
    goto block_162;
block_161:
    middle_record_r0 = arrow_table_r5[2];
    middle_flags_r1 = middle_record_r0->flags;
    {
        register u32 middle_set_mask_r2 asm("r2") = 0x20000;

        middle_flags_r1 |= middle_set_mask_r2;
    }
block_162:
    middle_record_r0->flags = middle_flags_r1;
    }
    {
    register struct WindowRecord98BB4 *lower_record_r0 asm("r0");
    register u32 lower_flags_r1 asm("r1");

    {
    register s32 lower_arrow_top_r3 asm("r3") = D_0200A8A0.top;
    register s32 lower_arrow_slot_r0 asm("r0") = D_0200A8A0.slot;
    register volatile u8 *lower_arrow_index_r4 asm("r4") = D_0200E6C4;
    register volatile u8 *lower_arrow_entry_r0 asm("r0");
    register s32 lower_arrow_count_r2 asm("r2");

    lower_arrow_entry_r0 = (volatile u8 *)lower_arrow_slot_r0;
    asm volatile("add %0, %0, %1"
                 : "+r"(lower_arrow_entry_r0)
                 : "r"(lower_arrow_index_r4));
    lower_arrow_count_r2 = *lower_arrow_entry_r0;
    asm volatile("" : "+r"(lower_arrow_count_r2));
    temp_r0_17 = D_0200A8A0.height - 2;
    if (lower_arrow_top_r3 >=
        lower_arrow_count_r2 -
            ((s32) (temp_r0_17 + (temp_r0_17 >> 0x1F)) >> 1)) {
        goto block_164;
    }
    }
    lower_record_r0 = arrow_table_r5[3];
    lower_flags_r1 = lower_record_r0->flags;
    {
        register u32 lower_clear_mask_r2 asm("r2") = 0xFFFDFFFF;

        lower_flags_r1 &= lower_clear_mask_r2;
    }
    goto block_165;
block_164:
    lower_record_r0 = arrow_table_r5[3];
    lower_flags_r1 = lower_record_r0->flags;
    {
        register u32 lower_set_mask_r2 asm("r2") = 0x20000;

        lower_flags_r1 |= lower_set_mask_r2;
    }
block_165:
    lower_record_r0->flags = lower_flags_r1;
    }
}
    func_080ED17C(1);
    {
        register u8 *repeat_stream_r5 asm("r5") = sp14;

        sp18 = (u32) (0 - (u8) (2 & M2C_FIELD(repeat_stream_r5, u8 *, 2))) >> 0x1F;
    }
    {
    register volatile u16 *repeat_state_r5 asm("r5");
    register u16 *repeat_keys_r2 asm("r2") = &D_0300000C;
    register u32 repeat_keys_r1 asm("r1") = *repeat_keys_r2;
    register u32 saved_keys_r6 asm("r6") = D_0200A8A0.keys;

    asm volatile("" : "+r"(saved_keys_r6));
    if (repeat_keys_r1 != saved_keys_r6) {
        goto block_170;
    }
    temp_r0_18 = D_03000075 + D_0200A8A0.repeat;
    D_0200A8A0.repeat = temp_r0_18;
    if ((u32) (u8) temp_r0_18 <= 7U) {
        goto block_169;
    }
    {
        register u32 repeated_keys_r0 asm("r0") = *repeat_keys_r2;

        repeat_keys_r2 = &D_0200A884;
        *repeat_keys_r2 = repeated_keys_r0;
        D_0200A8A0.repeat = 0;
        repeat_state_r5 = repeat_keys_r2;
    }
    goto block_171;
block_169:
    {
        register u16 *repeat_low_state_r3 asm("r3") = &D_0200A884;

        *repeat_low_state_r3 = 0;
        repeat_state_r5 = repeat_low_state_r3;
    }
    goto block_171;
block_170:
    {
        register u32 repeat_changed_zero_r0 asm("r0") = 0;
        register u16 *repeat_changed_input_r1 asm("r1");
        register u16 *repeat_changed_state_r4 asm("r4");

        D_0200A8A0.keys = repeat_keys_r1;
        repeat_changed_input_r1 = &D_0300000E;
        repeat_keys_r1 = *repeat_changed_input_r1;
        repeat_changed_state_r4 = &D_0200A884;
        *repeat_changed_state_r4 = repeat_keys_r1;
        D_0200A8A0.repeat = repeat_changed_zero_r0;
        repeat_state_r5 = repeat_changed_state_r4;
    }
block_171:
    {
    register u32 repeat_event_r1 asm("r1") = *repeat_state_r5;
    register u32 repeat_mask_r4 asm("r4");
    register u32 repeat_masked_r0 asm("r0");

    repeat_mask_r4 = 0x40;
    repeat_masked_r0 = repeat_mask_r4 & repeat_event_r1;
    repeat_masked_r0 <<= 16;
    asm volatile("lsr %0, %1, #16"
                 : "=r"(temp_r3_4)
                 : "r"(repeat_masked_r0));
    if (temp_r3_4 == 0) {
        goto block_180;
    }
    if (D_0200A8A0.selected == 0) {
        goto block_177;
    }
    temp_r0_19 = D_0200A8A0.selected - 1;
    D_0200A8A0.selected = temp_r0_19;
    if ((u32) (u8) temp_r0_19 >= (u32) D_0200A8A0.top) {
        goto block_175;
    }
    D_0200A8A0.top -= 1;
    {
        register struct WindowRecord98BB4 **up_scroll_table_r5 asm("r5") =
            D_0200A890;

        func_08094564(*up_scroll_table_r5, 1);
    }
block_175:
    D_0200A8A0.flags |= 2;
    func_08092E84(0x40);
    goto block_179;
block_177:
    {
        register u8 *upper_limit_stream_r6 asm("r6") = sp14;

        u32 upper_limit_stream_r6_test;
        register u32 upper_limit_stream_r6_byte asm("r1");

        upper_limit_stream_r6_byte = M2C_FIELD(upper_limit_stream_r6, u8 *, 2);
        upper_limit_stream_r6_test = repeat_mask_r4;
        asm volatile("" : "+r"(upper_limit_stream_r6_test), "+r"(repeat_mask_r4));
        upper_limit_stream_r6_test &= upper_limit_stream_r6_byte;
        if (!upper_limit_stream_r6_test) {
            goto block_179;
        }
    }
    D_0200A8A0.selected = D_0200E6C4[D_0200A8A0.slot] - 1;
    D_0200A8A0.flags |= 2;
    func_08092E84(0x40);
block_179:
    {
        register u32 nav_clear_r0 asm("r0") = (u32)&D_0200A884;
        register u32 nav_clear_r1 asm("r1");

        nav_clear_r1 = *(u16 *)nav_clear_r0;
        nav_clear_r0 = 0x40;
        nav_clear_r0 &= nav_clear_r1;
        nav_clear_r1 = (u32)&D_0200A884;
        *(u16 *)nav_clear_r1 = nav_clear_r0;
    }
    asm volatile("");
    goto block_226;
block_180:
    if (!(0x80 & repeat_event_r1)) {
        goto block_189;
    }
    if ((s32) D_0200A8A0.selected >= (s32) (D_0200E6C4[D_0200A8A0.slot] - 1)) {
        goto block_186;
    }
    D_0200A8A0.selected += 1;
    {
    register s32 down_selected_r2 asm("r2") = D_0200A8A0.selected;
    register s32 down_top_r3 asm("r3") = D_0200A8A0.top;

    temp_r0_20 = D_0200A8A0.height - 2;
    if (down_selected_r2 <
        down_top_r3 +
            ((s32) (temp_r0_20 + (temp_r0_20 >> 0x1F)) >> 1)) {
        goto block_184;
    }
    }
    D_0200A8A0.top += 1;
    {
        register struct WindowRecord98BB4 **down_scroll_table_r2 asm("r2") =
            D_0200A890;

        func_08094564(down_scroll_table_r2[1], 1);
    }
block_184:
    D_0200A8A0.flags |= 2;
    func_08092E84(0x40);
    goto block_188;
block_186:
    {
        register u8 *lower_limit_stream_r5 asm("r5") = sp14;

        u32 lower_limit_stream_r5_test;
        register u32 lower_limit_stream_r5_byte asm("r1");

        lower_limit_stream_r5_byte = M2C_FIELD(lower_limit_stream_r5, u8 *, 2);
        lower_limit_stream_r5_test = repeat_mask_r4;
        asm volatile("" : "+r"(lower_limit_stream_r5_test), "+r"(repeat_mask_r4));
        lower_limit_stream_r5_test &= lower_limit_stream_r5_byte;
        if (!lower_limit_stream_r5_test) {
            goto block_188;
        }
    }
    D_0200A8A0.selected = (u8) temp_r3_4;
    D_0200A8A0.flags |= 2;
    func_08092E84(0x40);
block_188:
    {
        register u16 *down_event_base_r6 asm("r6") = &D_0200A884;
        register u32 down_event_value_r1 asm("r1") = *down_event_base_r6;
        register u32 down_event_mask_r0 asm("r0") = 0x80;

        asm volatile("" : "+r"(down_event_base_r6),
                              "+r"(down_event_value_r1),
                              "+r"(down_event_mask_r0));
        down_event_mask_r0 &= down_event_value_r1;
        *down_event_base_r6 = down_event_mask_r0;
    }
    goto block_226;
block_189:
    if (!(0x20 & repeat_event_r1)) {
        goto block_198;
    }
    if (D_0200A8A0.selected == 0) {
        goto block_196;
    }
    {
    register s32 page_up_top_r2 asm("r2") = D_0200A8A0.top;

    temp_r0_21 = D_0200A8A0.height - 2;
    temp_r0_22 = (s32) (temp_r0_21 + (temp_r0_21 >> 0x1F)) >> 1;
    if (page_up_top_r2 < temp_r0_22) {
        goto block_193;
    }
    var_r1_6 = page_up_top_r2 - temp_r0_22;
    goto block_194;
block_193:
    {
        register s32 page_up_zero_r1 asm("r1");

        asm volatile("movs %0, #0" : "=r"(page_up_zero_r1));
        var_r1_6 = page_up_zero_r1;
    }
block_194:
    D_0200A8A0.top = var_r1_6;
    if ((u8)var_r1_6 == D_0200A8A0.prior_top) {
        goto block_196;
    }
    }
    D_0200A8A0.selected -= D_0200A8A0.prior_top - var_r1_6;
    {
        register struct WindowRecord98BB4 **page_up_table_r1 asm("r1") =
            D_0200A890;

        func_08094564(page_up_table_r1[2], 1);
    }
    D_0200A8A0.flags |= 2;
    func_08092E84(0x40);
block_196:
    event_mask_base = &D_0200A884;
    event_mask_value = *event_mask_base;
    var_r0_3 = 0x20;
    goto block_216;
block_198:
    if (!(0x10 & repeat_event_r1)) {
        goto block_210;
    }
    {
        register s32 page_selected_r6 asm("r6") = D_0200A8A0.selected;
        register u32 page_entry_base_r0 asm("r0") = (u32)D_0200E6C4;
        register u32 page_entry_r1 asm("r1") = D_0200A8A0.slot;
        register volatile u8 *page_entry_r8 asm("r8");
        register s32 page_count_r4 asm("r4");
        register s32 page_top_r3 asm("r3");
        register s32 page_top_compare_r2 asm("r2");
        register s32 page_half_r5 asm("r5");
        register u32 page_height_r0 asm("r0");
        register u32 page_height_sign_r1 asm("r1");

        page_entry_r1 += page_entry_base_r0;
        page_entry_r8 = (volatile u8 *)page_entry_r1;
        page_count_r4 = *(volatile u8 *)page_entry_r1;
        asm volatile("" : "+r"(page_selected_r6),
                          "+r"(page_entry_r8),
                          "+r"(page_count_r4));
        if (page_selected_r6 >= page_count_r4 - 1) {
            goto block_209;
        }
        page_top_r3 = *(volatile u8 *)&D_0200A8A0.top;
        page_top_compare_r2 = *(volatile u8 *)&D_0200A8A0.top;
        page_height_r0 = D_0200A8A0.height;
        page_height_r0 -= 2;
        page_height_sign_r1 = page_height_r0 >> 0x1F;
        page_height_r0 += page_height_sign_r1;
        page_half_r5 = (s32)page_height_r0 >> 1;
        asm volatile("" : "+r"(page_top_r3),
                          "+r"(page_top_compare_r2),
                          "+r"(page_half_r5),
                          "+r"(page_height_r0),
                          "+r"(page_height_sign_r1));
        {
            register s32 page_limit_r0 asm("r0");

            asm volatile("sub %0, %1, %2"
                         : "=r"(page_limit_r0)
                         : "r"(page_count_r4),
                           "r"(page_half_r5));
            if (page_top_compare_r2 >= page_limit_r0) {
                goto block_202;
            }
        }
        page_top_r3 += page_half_r5;
block_202:
        D_0200A8A0.top = page_top_r3;
        {
            register s32 page_new_top_r4 asm("r4");
            register s32 page_new_top_scratch_r0 asm("r0");

            asm volatile(
                "lsl %1, %2, #24\n\t"
                "lsr %0, %1, #24"
                : "=r"(page_new_top_r4),
                  "=&r"(page_new_top_scratch_r0)
                : "r"(page_top_r3));
            {
            register s32 page_prior_top_r3 asm("r3") =
                D_0200A8A0.prior_top;
            register s32 page_selected_r2 asm("r2");
            register volatile u8 *page_entry_r0 asm("r0");
            register s32 page_count_r1 asm("r1");
            register s32 page_result_r0 asm("r0");

            asm volatile("" : "+r"(page_new_top_r4),
                              "+r"(page_prior_top_r3));
            if (page_new_top_r4 == page_prior_top_r3) {
                goto block_209;
            }
            page_selected_r2 = page_selected_r6;
            page_entry_r0 = page_entry_r8;
            page_count_r1 = *page_entry_r0;
            asm volatile("" : "+r"(page_selected_r2),
                              "+r"(page_entry_r0),
                              "+r"(page_count_r1),
                              "+r"(page_half_r5));
            if (page_selected_r2 >= page_count_r1 - page_half_r5) {
                goto block_205;
            }
            page_result_r0 = page_selected_r2 + page_half_r5;
            goto block_208;
block_205:
            if (page_prior_top_r3 != page_new_top_r4) {
                goto block_207;
            }
            page_result_r0 = page_selected_r6;
            goto block_208;
block_207:
            page_result_r0 = page_count_r1 - 1;
block_208:
            D_0200A8A0.selected = page_result_r0;
            }
        }
    }
    {
        register struct WindowRecord98BB4 **page_down_table_r1 asm("r1") =
            D_0200A890;

        func_08094564(page_down_table_r1[3], 1);
    }
    D_0200A8A0.flags |= 2;
    func_08092E84(0x40);
block_209:
    event_mask_base = &D_0200A884;
    event_mask_value = *event_mask_base;
    var_r0_3 = 0x10;
    goto block_216;
block_210:
    {
        register u8 *action_options_stream_r3 asm("r3") = sp14;
        register u32 action_options_raw_r1 asm("r1");

        action_options_raw_r1 =
            M2C_FIELD(action_options_stream_r3, u8 *, 2);
        {
            u32 action_options_gate = 0x20 & action_options_raw_r1;

            temp_r1_17 = action_options_raw_r1;
            if (action_options_gate) {
                goto block_213;
            }
        }
    }
    {
        register u32 action1_keys_r1 asm("r1") = D_0300000E;
        register u32 action1_state_r2 asm("r2");

        action1_state_r2 = 1;
        if (!(1 & action1_keys_r1)) {
            goto block_213;
        }
        D_0200A882 = action1_state_r2;
        {
            register u8 *action1_next_r6 asm("r6") = sp14;

            action1_next_r6 += 3;
            sp14 = action1_next_r6;
        }
        func_08092E84(0x3E);
        *repeat_state_r5 &= 1;
    }
    goto block_226;
block_213:
    if (!(1 & temp_r1_17)) {
        goto block_217;
    }
    {
        register u32 action2_keys_r1 asm("r1") = D_0300000E;
        register u32 action2_state_r2 asm("r2") = 2;
        register u32 action2_mask_r4 asm("r4") = 2;

        asm volatile("" : "+r"(action2_keys_r1),
                              "+r"(action2_state_r2),
                              "+r"(action2_mask_r4));
        if (!(action2_mask_r4 & action2_keys_r1)) {
            goto block_217;
        }
        D_0200A882 = action2_state_r2;
        sp14 += 3;
        func_08092E84(0x3F);
        event_mask_base = &D_0200A884;
        event_mask_value = *event_mask_base;
        var_r0_3 = action2_mask_r4;
    }
block_216:
    var_r0_3 &= event_mask_value;
    *event_mask_base = var_r0_3;
    goto block_226;
block_217:
    {
    register u32 close_options_r2 asm("r2") = temp_r1_17;

    if (!(4 & close_options_r2)) {
        goto block_219;
    }
    {
        register u32 close_event_r0 asm("r0") = *repeat_state_r5;
        register u32 close_mask_200_r4 asm("r4") = 0x200;
        register u32 close_mask_copy_r1 asm("r1") = close_mask_200_r4;

        asm volatile("" : "+r"(close_event_r0),
                          "+r"(close_mask_200_r4),
                          "+r"(close_mask_copy_r1));
        if (close_event_r0 & close_mask_copy_r1) {
            goto block_223;
        }
    }
block_219:
    if (!(8 & close_options_r2)) {
        goto block_221;
    }
    {
        register u32 close_event_r0 asm("r0") = *repeat_state_r5;
        register u32 close_mask_100_r6 asm("r6") = 0x100;
        register u32 close_mask_copy_r1 asm("r1") = close_mask_100_r6;

        asm volatile("" : "+r"(close_event_r0),
                          "+r"(close_mask_100_r6),
                          "+r"(close_mask_copy_r1));
        if (close_event_r0 & close_mask_copy_r1) {
            goto block_223;
        }
    }
    }
block_221:
    if (!(0x10 & temp_r1_17)) {
        goto block_225;
    }
    if (!(8 & *repeat_state_r5)) {
        goto block_225;
    }
block_223:
    func_08094554(D_0200A88C);
    {
        register struct WindowRecord98BB4 **close_base_r1 asm("r1") =
            D_0200A890;

        func_08094554(close_base_r1[0]);
    }
    {
        register struct WindowRecord98BB4 **close_base_r2 asm("r2") =
            D_0200A890;

        func_08094554(close_base_r2[1]);
    }
    {
        register struct WindowRecord98BB4 **close_base_r3 asm("r3") =
            D_0200A890;

        func_08094554(close_base_r3[2]);
    }
    {
        register struct WindowRecord98BB4 **close_base_r4 asm("r4") =
            D_0200A890;

        func_08094554(close_base_r4[3]);
    }
    D_0200A8A0.prior_selected = 0xFF;
    {
        register u16 *close_tail_base_r5 asm("r5") = &D_0200A884;
        register u32 close_tail_value_r0 asm("r0") = *close_tail_base_r5;
        register u32 close_tail_mask_r6 asm("r6") = 0x308;
        register u32 close_tail_mask_copy_r1 asm("r1") = close_tail_mask_r6;

        asm volatile("" : "+r"(close_tail_base_r5),
                          "+r"(close_tail_value_r0),
                          "+r"(close_tail_mask_r6),
                          "+r"(close_tail_mask_copy_r1));
        close_tail_value_r0 &= close_tail_mask_copy_r1;
        *close_tail_base_r5 = close_tail_value_r0;
    }
    return;
    }
    }
block_225:
    sp18 = 0;
block_226:
    if (D_0200A882 == 0) {
        goto loop_86;
    }
    func_08094554(D_0200A88C);
    func_08094554(M2C_FIELD(D_0200A890, struct WindowRecord98BB4 **, 0));
    func_08094554(D_0200A890[1]);
    func_08094554(D_0200A890[2]);
    func_08094554(D_0200A890[3]);
    D_0200A8A0.prior_selected = 0xFF;
    goto block_289;
#undef D_0200A8A0
case 8:
    {
    struct Map98BB4 *case8_map;
    register u32 case8_zero_r4 asm("r4");
    register u32 case8_map_guard_r5 asm("r5");
    register u32 case8_map_guard_r6 asm("r6");

    {
        register u8 *case8_init_stream_r1 asm("r1") = sp14;

        func_080971AC(M2C_FIELD(case8_init_stream_r1, u8 *, 1));
    }
    case8_map = &D_0200A8A0;
    asm volatile("" : "=&r"(case8_map_guard_r5),
                      "=&r"(case8_map_guard_r6),
                      "+r"(case8_map));
    D_0200A88C = func_08094484(0x080ED8F8, 0x080ED92C, 0U,
        (s16) (({
            register s32 case8_x_r3 asm("r3") = (u16) case8_map->x;
            register s32 case8_half_width_r2 asm("r2");

            case8_x_r3 -= 2;
            case8_half_width_r2 = (u16) case8_map->width;
            case8_half_width_r2 >>= 1;
            case8_x_r3 += case8_half_width_r2;
            case8_x_r3;
        }) * 8),
        ({
            register s32 case8_y_r4 asm("r4") = (u16)case8_map->y;
            register s32 case8_y_term_r2 asm("r2") =
                (u16)case8_map->height;

            case8_y_r4 += case8_y_term_r2;
            case8_y_r4 -= 5;
            case8_y_r4 <<= 3;
            case8_y_term_r2 = case8_map->selected;
            case8_y_term_r2 <<= 4;
            case8_y_r4 += case8_y_term_r2;
            case8_y_r4 <<= 16;
            case8_y_r4 >>= 16;
            case8_y_r4;
        }), (u16) (s32) (u16) (D_0202166A + 0xE), (u16) (s32) D_0202166C, 0x20, ({
            case8_zero_r4 = 0;
            case8_zero_r4;
        }));
    func_080972C8();
    D_0200A882 = case8_zero_r4;
    {
    register u8 *case8_state_r4 asm("r4") = &D_0200A882;
loop_229:
    D_0200A88C->field6 = ((((u16) case8_map->y + case8_map->height) - 5) * 8) + (case8_map->selected * 0x10);
    func_080ED17C(1);
    {
    register volatile u16 *case8_keys_address_r0 asm("r0") = &D_0300000E;
    register u32 case8_keys_r1 asm("r1") = *case8_keys_address_r0;

    asm volatile("" : "+r"(case8_keys_address_r0),
                      "+r"(case8_keys_r1));
    if (!(0x40 & case8_keys_r1)) {
        goto block_233;
    }
    if (case8_map->selected == 0) {
        goto block_242;
    }
    var_r0_5 = case8_map->selected - 1;
    goto block_236;
block_233:
    if (!(0x80 & case8_keys_r1)) {
        goto block_237;
    }
    if (case8_map->selected != 0) {
        goto block_242;
    }
    var_r0_5 = case8_map->selected + 1;
block_236:
    case8_map->selected = var_r0_5;
    func_08092E84(0x40);
    goto block_242;
block_237:
    {
        register u32 case8_accept_value_r2 asm("r2");
        register u32 case8_accept_test_r0 asm("r0");

        asm volatile(
            "movs %0, #1\n"
            "movs %1, #1\n"
            "and %1, %1, %2"
            : "=r"(case8_accept_value_r2),
              "=r"(case8_accept_test_r0)
            : "r"(case8_keys_r1));
        if (!case8_accept_test_r0) {
            goto block_240;
        }
        *case8_state_r4 = case8_accept_value_r2;
    }
    D_0200A880 = case8_map->selected;
    {
        register u8 *case8_accept_next_r2 asm("r2") = sp14;

        case8_accept_next_r2 += 2;
        sp14 = case8_accept_next_r2;
    }
    func_08092E84(0x3E);
    goto block_242;
block_240:
    {
        register u32 case8_cancel_value_r2 asm("r2");
        register u32 case8_cancel_test_r0 asm("r0");

        asm volatile(
            "movs %0, #2\n"
            "movs %1, #2\n"
            "and %1, %1, %2"
            : "=r"(case8_cancel_value_r2),
              "=r"(case8_cancel_test_r0)
            : "r"(case8_keys_r1));
        if (!case8_cancel_test_r0) {
            goto block_242;
        }
        *case8_state_r4 = case8_cancel_value_r2;
    }
    {
        register u8 *case8_cancel_next_r3 asm("r3") = sp14;

        case8_cancel_next_r3 += 2;
        sp14 = case8_cancel_next_r3;
    }
    func_08092E84(0x3F);
    }
block_242:
    if (*case8_state_r4 == 0) {
        goto loop_229;
    }
    func_08094554(D_0200A88C);
    }
    goto block_289;
    }
case 11:
    {
    register u8 *case11_stream_r4 asm("r4") = sp14;
    register u32 case11_guard_r2 asm("r2");
    register u32 case11_guard_r3 asm("r3");
    register u32 case11_guard_r5 asm("r5");
    register u32 case11_guard_r6 asm("r6");

    temp_r0_24 = func_0809716C(M2C_FIELD(case11_stream_r4, u8 *, 1));
    asm volatile("" : "=&r"(case11_guard_r2),
                      "=&r"(case11_guard_r3),
                      "=&r"(case11_guard_r5),
                      "=&r"(case11_guard_r6),
                      "+r"(temp_r0_24));
    temp_r0_24->style = M2C_FIELD(case11_stream_r4, u8 *, 2);
    temp_r0_25 = M2C_FIELD(case11_stream_r4, u8 *, 2);
    if (temp_r0_25 == 1) {
        goto block_253;
    }
    if ((s32) temp_r0_25 > 1) {
        goto block_248;
    }
    if (temp_r0_25 == 0) {
        goto block_251;
    }
    goto block_255;
block_248:
    if (temp_r0_25 == 2) {
        goto block_252;
    }
    if (temp_r0_25 == 3) {
        goto block_253;
    }
    goto block_255;
block_251:
    temp_r0_24->unk19 = 0;
    var_r0_6 = 5;
    asm volatile("");
    goto block_254;
block_252:
    temp_r0_24->unk19 = 0;
    var_r0_6 = 5;
    goto block_254;
block_253:
    temp_r0_24->unk19 = 4;
    var_r0_6 = 6;
block_254:
    temp_r0_24->unk1A = var_r0_6;
block_255:
    temp_r0_24->flags |= 0xA;
    var_r5 = sp14;
    var_r5 += 3;
    goto block_288;
    }
case 12:
    {
    register u8 *case12_next_r6 asm("r6") = sp14 + 1;
    register volatile u16 *case12_keys_r4 asm("r4") = &D_0300000E;
    register u32 case12_mask_r5 asm("r5") = 3;

loop_257:
    func_080ED17C(1);
    {
        register u32 case12_keys_r1 asm("r1") = *case12_keys_r4;

        asm volatile("" : "+r"(case12_keys_r1));
        if (!(case12_mask_r5 & case12_keys_r1)) {
            goto loop_257;
        }
    }
    func_08092E84(0x41);
    func_080ED17C(1);
    sp14 = case12_next_r6;
    goto block_289;
    }
case 13:
    {
    register u8 *case13_stream_r6 asm("r6") = sp14;
    register u16 *case13_attr_r9 asm("r9");
    register struct Map98BB4 *case13_map_r7 asm("r7");
    register u8 *case13_command_r3 asm("r3");
    register s32 case13_x_r1 asm("r1");
    register s32 case13_y_r2 asm("r2");
    register s32 case13_product_r0 asm("r0");
    register u32 case13_tile_base_r2 asm("r2");
    register s32 case13_next_r8_sl asm("r10");

    case13_map_r7 = func_0809716C(M2C_FIELD(case13_stream_r6, u8 *, 1));
    {
        register s32 case13_seed_r0 asm("r0") = -1;

        asm volatile("" : "+r"(case13_seed_r0));
        var_r8_8 = case13_seed_r0;
    }
    sp20 = case13_stream_r6 + 4;
    var_r6_tiles = &D_02021664;
    {
        register u16 *case13_attr_seed_r1 asm("r1") = &D_02021668;

        asm volatile("" : "+r"(case13_attr_seed_r1));
        case13_attr_r9 = case13_attr_seed_r1;
    }
loop_260:
    var_r5_10 = -1;
    case13_next_r8_sl = var_r8_8 + 1;
loop_261:
    case13_command_r3 = sp14;
    case13_x_r1 = M2C_FIELD(case13_command_r3, u8 *, 2);
    case13_x_r1 += var_r5_10;
    case13_y_r2 = M2C_FIELD(case13_command_r3, u8 *, 3);
    case13_y_r2 += var_r8_8;
    asm volatile("ldrh %0, [%1, #8]"
                 : "=r"(case13_product_r0)
                 : "r"(case13_map_r7));
    case13_product_r0 *= case13_y_r2;
    case13_x_r1 += case13_product_r0;
    case13_x_r1 <<= 1;
    case13_x_r1 += 0x1E;
    asm volatile("add %0, %1, %2"
                 : "=r"(temp_r4_7)
                 : "r"(case13_map_r7), "r"(case13_x_r1));
    asm volatile("ldrh %0, [%1, #0]"
                 : "=r"(temp_r3_5)
                 : "r"(temp_r4_7)
                 : "memory");
    {
        register u32 case13_mask_r1 asm("r1") = 0x3FF;
        register u32 case13_mask_copy_r0 asm("r0");

        asm volatile("" : "+r"(case13_mask_r1));
        case13_mask_copy_r0 = case13_mask_r1;
        asm volatile("" : "+r"(case13_mask_copy_r0));
        case13_mask_r1 = case13_mask_copy_r0;
        temp_r1_18 = case13_mask_r1 & temp_r3_5;
    }
    case13_tile_base_r2 = *var_r6_tiles;
    temp_r0_26 = case13_tile_base_r2 + 2;
    if (temp_r1_18 < temp_r0_26) {
        goto block_263;
    }
    if (temp_r1_18 <= (u32) (temp_r0_26 + 7)) {
        goto block_282;
    }
block_263:
    if (temp_r1_18 < case13_tile_base_r2) {
        goto block_265;
    }
    {
        register u32 case13_tile_upper_r0 asm("r0");

        asm volatile("add %0, %1, #0"
                     : "=r"(case13_tile_upper_r0)
                     : "r"(case13_tile_base_r2));
        case13_tile_upper_r0 += 0x40;
        if (temp_r1_18 < case13_tile_upper_r0) {
            goto block_266;
        }
    }
block_265:
    func_08097980((u16) (temp_r1_18 - D_02021670));
block_266:
    if (var_r5_10 != -1) {
        goto block_272;
    }
    if (var_r8_8 != var_r5_10) {
        goto block_269;
    }
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x18;
        register u16 *case13_attr_address_r2 asm("r2") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r2)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_269:
    {
        register s32 case13_first_compare_r3 asm("r3") = var_r8_8;

        asm volatile("" : "+r"(case13_first_compare_r3));
        if (case13_first_compare_r3 > 5) {
            goto block_271;
        }
    }
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x1E;
        register u16 *case13_attr_address_r2 asm("r2") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r2)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_271:
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x1A;
        register u16 *case13_attr_address_r3 asm("r3") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r3)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_272:
    if (var_r5_10 > 5) {
        goto block_277;
    }
    if (var_r8_8 != -1) {
        goto block_275;
    }
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x1C;
        register u16 *case13_attr_address_r2 asm("r2") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r2)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_275:
    {
        register s32 case13_second_compare_r3 asm("r3") = var_r8_8;

        asm volatile("" : "+r"(case13_second_compare_r3));
        if (case13_second_compare_r3 != 6) {
            goto block_284;
        }
    }
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x1D;
        register u16 *case13_attr_address_r2 asm("r2") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r2)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_277:
    if (var_r8_8 != -1) {
        goto block_279;
    }
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x19;
        register u16 *case13_attr_address_r3 asm("r3") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r3)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_279:
    if (var_r8_8 > 5) {
        goto block_281;
    }
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x1F;
        register u16 *case13_attr_address_r2 asm("r2") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r2)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_281:
    {
        register u32 case13_result_r0 asm("r0") = *var_r6_tiles + 0x1B;
        register u16 *case13_attr_address_r3 asm("r3") = case13_attr_r9;
        register u32 case13_attr_value_r1 asm("r1");

        asm volatile("ldrh %0, [%1, #0]"
                     : "=r"(case13_attr_value_r1)
                     : "r"(case13_attr_address_r3)
                     : "memory");
        case13_result_r0 |= case13_attr_value_r1;
        var_r0_7 = case13_result_r0;
    }
    goto block_283;
block_282:
    var_r0_7 = temp_r3_5 + 0xE;
block_283:
    *temp_r4_7 = var_r0_7;
block_284:
    var_r5_10 += 1;
    if (var_r5_10 <= 6) {
        goto loop_261;
    }
    var_r8_8 = case13_next_r8_sl;
    {
        register s32 case13_outer_compare_r4 asm("r4") = var_r8_8;

        asm volatile("" : "+r"(case13_outer_compare_r4));
        if (case13_outer_compare_r4 > 6) {
            goto block_287;
        }
    }
    goto loop_260;
block_287:
    {
        register u32 case13_flags_r0 asm("r0");
        register u32 case13_flag_mask_r1 asm("r1");

        asm volatile(
            "ldr %0, [%2, #0]\n"
            "movs %1, #2\n"
            "orr %0, %0, %1\n"
            "str %0, [%2, #0]"
            : "=&r"(case13_flags_r0),
              "=&r"(case13_flag_mask_r1)
            : "r"(case13_map_r7)
            : "memory");
    }
    var_r5 = sp20;
    }
    }
block_288:
    sp14 = var_r5;
block_289:
    {
        register s32 tail_r6 asm("r6") = 0;
        asm volatile("" : "+r"(tail_r6));
        if (tail_r6 == 0) {
            goto loop_1;
        }
    }
    asm volatile(".Lsub_08098BB4_return:");
    return;
}
