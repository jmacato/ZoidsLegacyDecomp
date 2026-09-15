#include "m2c_prelude.h"

M2C_UNK func_0809258C();                            /* extern */
M2C_UNK func_080925A4(M2C_UNK *);                   /* extern */
M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, u32); /* extern */
asm(".set func_08094484_4, func_08094484");
extern s32 func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08095114(s32);                         /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_08098BB4(s32);                         /* extern */
s32 func_0809A1F8(u8, s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_0809A5B4(u8, u8, s32, s32, s32);       /* extern */
M2C_UNK func_0809AA64(s32, u32, u16, u32);          /* extern */
M2C_UNK func_080D0AF0(M2C_UNK);                     /* extern */
M2C_UNK func_080D12A0(s32, s32);                    /* extern */
s32 func_080D22B4(M2C_UNK, u32, s32, s16, s32, s32, u32, s32, s32, s32); /* extern */
M2C_UNK func_080E2DCC(s32, s32);                    /* extern */
M2C_UNK func_080E2EA4();                            /* extern */
M2C_UNK func_080E2F30();                            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
extern u16 D_0300004E;
extern u16 D_03000050;
extern u16 D_03000052;

struct SaveBlock { s32 words[4]; };
struct SelectionRow { u8 flags; u8 pad1; u8 value; u8 pad3[0x35]; };
struct StackPair { s32 value; s32 pad; };

void sub_080E2F70(u8 *arg0) {
    struct SaveBlock sp18;
    s32 sp28[3];
    u8 *volatile sp34;
    volatile u32 sp38;
    s32 sp3C;
    s32 sp40;
    u8 *sp44;
    struct StackPair sp48;
    s32 sp4C;
    s32 var_r0_6;
    s32 var_r3;
    s32 var_r3_2;
    register s32 *temp_r4_2 asm("r4");
    s32 *var_r1;
    s32 *var_r1_2;
    register s32 temp_r1 asm("r1");
    s32 temp_r1_2;
    s32 temp_r1_4;
    s32 temp_r1_5;
    s32 temp_r2_4;
    register s32 temp_r2_8 asm("r2");
    s32 temp_r4;
    s32 var_r0_3;
    s32 var_r0_9;
    u16 temp_r0_3;
    u16 temp_r0_4;
    u16 temp_r0_6;
    u16 temp_r0_7;
    u16 temp_r1_3;
    u32 var_r0;
    u32 var_r0_2;
    u32 var_r0_7;
    u32 var_r0_8;
    u32 var_r4;
    u32 var_r5;
    register u32 var_r5_2 asm("r5");
    u32 var_r5_4;
    u8 temp_r0;
    register u32 initial_entry_bits asm("r2");
    u8 temp_r2_2;
    u8 temp_r2_5;
    u8 temp_r2_6;
    u8 temp_r3;
    u8 temp_r3_2;
    u8 temp_r3_3;
    u8 temp_r3_4;
    u8 temp_r3_5;
    u8 temp_r7;
    u8 temp_r7_2;
    u8 var_r0_10;
    u8 var_r0_4;
    u8 var_r5_3;
    register void *temp_r0_2 asm("r9");
    register void *temp_r0_5 asm("r9");
    void *temp_r2_3;
    void *temp_r2_7;
    void *var_r0_11;
    void *var_r0_5;
    s32 *display_state;
    struct SelectionRow *graphics;
    u8 *state;
    u8 graphics_flags;
    register s32 initial_count asm("r3");
    register s32 *initial_flags_base asm("r4");
    register s32 *initial_loop_flags_base asm("r6");
    register u32 initial_bit_limit asm("r4");
    register u32 initial_one_mask asm("r5");
    register s32 *initial_flags_word asm("r1");
    register u32 initial_first_mask asm("r0");
    register u32 initial_loop_r0 asm("r0");
    register u8 *initial_loop_selected_base asm("r2");
    register u32 initial_loop_entry_bits asm("r2");
    register u32 initial_loop_mask asm("r1");
    register u8 *initial_selected_base asm("r3");
    register u32 initial_selected_index asm("r4");
    register u8 *initial_selected_address asm("r0");
    register u16 *state_halfword asm("r1");
    s32 *flags_base;
    s32 flags_index;
    u32 flags_mask;
    u32 bit_limit;
    u32 one_mask;
    register u32 initial_index asm("r4");
    s32 sprite_offset;
    s32 sprite_offset_2;
    register s32 constructor_offset asm("r6");
    s32 constructor_offset_2;
    register u8 *sprite_base asm("sl");
    u8 *scan_data;
    u8 *animation_table;
    u8 *animation_table_2;
    register u8 *coordinate_table asm("r0");
    register u8 *coordinate_table_2 asm("r0");
    register s32 coordinate_sum_first asm("r1");
    register s32 coordinate_sum_second asm("r1");
    register u8 *coordinate_table_keep asm("ip");
    register u32 constructor_y asm("r4");
    register u32 constructor_y_2 asm("r4");
    register u32 first_record_offset asm("r0");
    register u32 first_record_base asm("r1");
    u32 shifted_index_source;
    register u32 saved_shift asm("r8");
    u32 shifted_index_source_2;
    register u32 saved_shift_2 asm("r8");
    register u32 constructor_record_offset_2 asm("r0");
    register u32 constructor_stride_source_2 asm("r2");
    register u32 constructor_base_2 asm("r1");
    u32 constructor_stride_keep_2;
    u32 doubled_x;
    u32 doubled_y;
    u32 doubled_x_2;
    u32 doubled_y_2;
    u32 constructor_range;
    u32 constructor_range_2;

    sp34 = arg0;
    sp18 = *(struct SaveBlock *)0x08109334;
    *(u16 *)0x0300004C = 0x1D40;
    M2C_FIELD((void *)0x04000008, s16 *, 0) = 0x4086;
    M2C_FIELD((void *)0x04000008, s16 *, 4) = 0x28B;
    display_state = (s32 *)0x03000054;
    display_state[5] = 0;
    display_state[1] = 0;
    func_08096FBC(3, 3, 0, 0x1C0, 0x1C0, 3, 0xE, 0, 0x3E6, 0xF);
    func_08094330();
    func_08094484(0x08105DF4, 0x08105E00, 0, 0xA0, 0x98, 0x399, 0xF, 0x408, 0U);
    func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8, 0x98, 0x343, 0xF, 0x408, 0U);
    func_08092D8C(2, 0x080E2F4D);
    func_08098BB4(0x080066B1);
    func_08096308(0xF, 0);
    initial_index = 1;
    sp38 = initial_index;
    scan_data = sp34;
    initial_count = scan_data[0];
    sp44 = (u8 *)sp28;
    if (initial_index <= (u32)initial_count) {
        initial_flags_base = (s32 *)0x020217B4;
        initial_entry_bits = scan_data[1];
        initial_flags_word = (s32 *)
            (((initial_entry_bits >> 5) * 4) + (s32)initial_flags_base);
        initial_entry_bits &= 0x1F;
        initial_first_mask = sp38;
        initial_first_mask <<= initial_entry_bits;
        if (!(*initial_flags_word & initial_first_mask)) {
            initial_loop_flags_base = initial_flags_base;
            initial_bit_limit = 0x1F;
            initial_one_mask = 1;
            do {
                initial_loop_r0 = sp38 + 1;
                initial_loop_r0 = (u8)initial_loop_r0;
                sp38 = initial_loop_r0;
                if (initial_loop_r0 > (u32) initial_count) {
                    break;
                }
                initial_loop_selected_base = sp34;
                asm volatile("add %0, %1, %0"
                    : "+r"(initial_loop_r0)
                    : "r"(initial_loop_selected_base));
                initial_loop_entry_bits = *(u8 *)initial_loop_r0;
                initial_loop_r0 = ((initial_loop_entry_bits >> 5) * 4) +
                    (u32)initial_loop_flags_base;
                initial_loop_entry_bits &= initial_bit_limit;
                initial_loop_mask = initial_one_mask;
                initial_loop_mask <<= initial_loop_entry_bits;
            } while (!(*(s32 *)initial_loop_r0 & initial_loop_mask));
        }
    }
    initial_selected_base = sp34;
    initial_selected_index = sp38;
    initial_selected_address = initial_selected_base + initial_selected_index;
    temp_r7 = *initial_selected_address;
    *(s32 *)0x02033F3C = func_0809A1F8(temp_r7, 0, 1, 0, 0, 0x02002880);
    first_record_offset = temp_r7 * 0x38;
    first_record_base = 0x087AFCC4;
    asm volatile("" : "+r"(first_record_base));
    temp_r0_2 = (void *)(first_record_offset + first_record_base);
    var_r5 = 0;
    do {
    register void *first_record_view asm("r0");
    temp_r1 = var_r5 * 4;
    first_record_view = temp_r0_2;
    asm volatile("" : "+r"(first_record_view));
    temp_r2_3 = first_record_view + temp_r1;
    constructor_range = (u16)(M2C_FIELD(temp_r2_3, u16 *, 0x1A) - 1);
    constructor_offset = temp_r1;
    if (constructor_range <= 0x63U) {
        goto block_8;
    }
    goto block_17;
block_8:
    animation_table = (u8 *)0x087ABC6C;
    temp_r0_3 = M2C_FIELD(temp_r2_3, u16 *, 0x1A);
    doubled_x = temp_r0_3 << 1;
    if (var_r5 == 0) {
        goto block_10;
    }
    var_r0 = (doubled_x + 1) << 0x18;
    goto block_11;
block_10:
    var_r0 = temp_r0_3 << 0x19;
block_11:
    func_0809AA64(animation_table, var_r0 >> 0x18,
        (shifted_index_source = var_r5 << 0x17) >> 0x10, var_r5);
    {
    register u8 *sprite_base_source asm("r1");
    register void *first_y_record_view asm("r2");
    register void *first_y_record_address asm("r0");
    sprite_base_source = (u8 *)0x087AC2BC;
    asm volatile("" : "+r"(sprite_base_source));
    sprite_base = sprite_base_source;
    first_y_record_view = temp_r0_2;
    asm volatile("add %0, %1, %2"
        : "=r"(first_y_record_address)
        : "r"(first_y_record_view), "r"(constructor_offset));
    temp_r0_4 = M2C_FIELD(first_y_record_address, u16 *, 0x1A);
    }
    doubled_y = temp_r0_4 << 1;
    saved_shift = shifted_index_source;
    if (var_r5 == 0) {
        goto block_13;
    }
    var_r0_2 = (doubled_y + 1) << 0x10;
    goto block_14;
block_13:
    var_r0_2 = temp_r0_4 << 0x11;
block_14:
    constructor_y = var_r0_2 >> 0x10;
    coordinate_table = (u8 *)0x087EC38C;
    temp_r2_4 = temp_r7 << 5;
    coordinate_sum_first = constructor_offset + temp_r2_4;
    {
    register u8 *coordinate_address_first asm("r3");
    asm volatile("add %0, %1, %2"
        : "=r"(coordinate_address_first)
        : "r"(coordinate_sum_first), "r"(coordinate_table));
    var_r3 = *(s16 *)coordinate_address_first;
    }
    coordinate_table_keep = coordinate_table;
    if (var_r5 != 2) {
        goto block_16;
    }
    {
    register u32 sprite_offset_io asm("r0");

    sprite_offset_io = 0x087AC90C;
    asm volatile(
        "mov r1, %1\n\t"
        "ldrh r1, [r1, #34]\n\t"
        "lsl r1, r1, #1\n\t"
        "str r1, [sp, #76]\n\t"
        "add r0, r1, r0\n\t"
        "mov r1, #0\n\t"
        "ldrsh r0, [r0, r1]"
        : "+r"(sprite_offset_io) : "r"(temp_r0_2) : "r1");
    sprite_offset = (s32)sprite_offset_io;
    }
    var_r3 = (s16) (var_r3 - sprite_offset);
block_16:
    var_r0_3 = func_080D22B4(sprite_base, constructor_y, 0, var_r3, ({
        register s32 coordinate_sum asm("r0");
        register u8 *coordinate_arg_base asm("r1");
        register s32 coordinate_value asm("r0");
        coordinate_sum = constructor_offset + temp_r2_4;
        coordinate_arg_base = coordinate_table_keep + 2;
        coordinate_sum += (s32)coordinate_arg_base;
        coordinate_value = *(s16 *)coordinate_sum;
        coordinate_value;
    }), saved_shift >> 0x10, var_r5, ({
        register u8 *flags_table asm("r1");
        register u32 flags_index_value asm("r0");
        register u32 flags_value asm("r0");
        register u32 constructor_flags asm("r0");
        flags_table = (u8 *)0x087ED68C;
        flags_index_value = temp_r7 << 1;
        flags_index_value += temp_r7;
        asm volatile("add %0, %1, %0"
            : "+r"(flags_index_value) : "r"(var_r5));
        flags_index_value += (u32)flags_table;
        flags_value = *(u8 *)flags_index_value;
        constructor_flags = flags_value << 6;
        constructor_flags |= 0x1218;
        constructor_flags;
    }), 0, 0);
    var_r1 = (s32 *)(sp44 + constructor_offset);
    goto block_18;
block_17:
    var_r1 = (s32 *)(sp44 + constructor_offset);
    var_r0_3 = 0;
block_18:
    *var_r1 = var_r0_3;
    var_r5 = (u32) (u8) (var_r5 + 1);
    } while (var_r5 <= 2U);
    {
    register struct SelectionRow *graphics_base asm("r2");
    register u32 graphics_stride asm("r1");
    register u32 graphics_stride_keep asm("sl");
    register s32 graphics_flags_first asm("r3");
    register u32 graphics_low_first asm("r3");
    register s32 graphics_high asm("r0");
    register u32 graphics_row_offset asm("r0");
    struct SelectionRow *graphics_row;
    register u32 state_r0 asm("r0");
    register u8 *state_r1 asm("r1");

    graphics_base = (struct SelectionRow *)0x087AFCC4;
    graphics_stride = temp_r7 << 3;
    graphics_row_offset = (graphics_stride - temp_r7) << 3;
    asm volatile("add %0, %0, %1"
        : "+r"(graphics_row_offset) : "r"(graphics_base));
    graphics_row = (struct SelectionRow *)graphics_row_offset;
    graphics_flags_first = graphics_row->flags;
    graphics_high = graphics_flags_first & 0x80;
    graphics_stride_keep = graphics_stride;
    if (graphics_high != 0) {
        state_r1 = (u8 *)0x0203055C;
        state_r0 = 0xB;
        goto first_nonzero_state;
    }
    graphics_low_first = (u8)(graphics_flags_first & 0x40);
    if (graphics_low_first != 0) {
        state_r1 = (u8 *)0x0203055C;
        state_r0 = 0xD;
first_nonzero_state:
        state_r1[2] = state_r0;
        state_r0 = (u32)state_r1;
        goto first_state_ready;
    }
    state_r0 = 0x0203055C;
    ((u8 *)state_r0)[2] = graphics_low_first;
first_state_ready:
    func_0809A5B4(((u8 *)state_r0)[2],
        ({
            register u32 graphics_final_address asm("r1");

            graphics_final_address = (graphics_stride_keep - temp_r7) << 3;
            asm volatile("add %0, %0, %1"
                : "+r"(graphics_final_address)
                : "r"(graphics_base));
            ((struct SelectionRow *)graphics_final_address)->value;
        }), 2, 2, 1);
    }
    *(s8 *)0x02033F36 = 0;
    func_080D0AF0(0xFFFFFF00);
    func_080D12A0(2, 0);
    {
    register s32 *first_kind_table asm("r0");

    first_kind_table = (s32 *)0x087F26C8;
    temp_r4 = temp_r7 * 4;
    asm volatile("add %0, %1, %0"
        : "+r"(first_kind_table) : "r"(temp_r4));
    func_08098BB4(*first_kind_table);
    }
    {
    register s32 *second_kind_table asm("r0");

    second_kind_table = (s32 *)0x087A3660;
    asm volatile("" : "+r"(second_kind_table));
    temp_r4 += (s32)second_kind_table;
    func_080E2DCC(2, *(s32 *)temp_r4);
    }
    func_080972C8();
    sp3C = 0;
    var_r4 = 0;
loop_28:
    if (var_r4 == 0) {
        goto block_30;
    }
    goto block_54;
block_30:
    {
    register u32 input_value asm("r0");
    register u32 input_mask_source asm("r2");
    register u32 input_mask asm("r1");

    input_value = *(u16 *)0x0300000C;
    input_mask_source = 0x80;
    input_mask_source <<= 1;
    asm volatile("" : "+r"(input_mask_source));
    input_mask = input_mask_source;
    asm volatile("" : "+r"(input_mask));
    if (!(input_value & input_mask)) {
        goto block_35;
    }
    }
    {
    register s32 dialog_state_first asm("r3");
    dialog_state_first = sp3C;
    asm volatile("" : "+r"(dialog_state_first));
    if (dialog_state_first != 0) {
        goto block_33;
    }
    }
    goto block_91;
block_33:
    {
    register u16 *display_control asm("r0");
    register u32 display_value asm("r1");
    register u32 clear_mask_source asm("r3");
    register u32 clear_mask asm("r2");

    display_control = (u16 *)0x0300004C;
    display_value = *display_control;
    clear_mask_source = 0xF7FF;
    asm volatile("" : "+r"(clear_mask_source));
    clear_mask = clear_mask_source;
    asm volatile("" : "+r"(clear_mask));
    display_value &= clear_mask;
    *display_control = display_value;
    }
    func_080925A4(&sp18);
    {
    register s32 dialog_state_zero asm("r0");
    dialog_state_zero = 0;
    asm volatile("" : "+r"(dialog_state_zero));
    sp3C = dialog_state_zero;
    }
    func_08094554(sp40);
    goto block_91;
block_35:
    {
    register s32 dialog_state_second asm("r1");
    dialog_state_second = sp3C;
    if (dialog_state_second != 0) {
        goto block_37;
    }
    }
    *(u16 *)0x0300004C = (u16) (*(u16 *)0x0300004C | 0x800);
    func_0809258C();
    sp3C = 1;
    asm volatile(
        "mov r0, #120\n\t"
        "str r0, [sp, #0]\n\t"
        "mov r0, #232\n\t"
        "lsl r0, r0, #2\n\t"
        "str r0, [sp, #4]\n\t"
        "mov r0, #15\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r0, #129\n\t"
        "lsl r0, r0, #3\n\t"
        "str r0, [sp, #12]\n\t"
        "str %0, [sp, #16]"
        : : "r"(var_r4) : "r0", "memory");
    sp40 = func_08094484_4(0x08105E58, 0x08105E64, 0, 0x38);
block_37:
    temp_r1_3 = *(u16 *)0x0300000E;
    if (!(0x20 & temp_r1_3)) {
        goto block_44;
    }
    {
    register s32 *decrement_flags_base asm("r6");
    register u32 decrement_bit_limit asm("r3");
    register u32 decrement_one_mask asm("r4");

    var_r5_2 = sp38;
    decrement_flags_base = (s32 *)0x020217B4;
    decrement_bit_limit = 0x1F;
    decrement_one_mask = 1;
    asm volatile(
        "1:\n\t"
        "sub r0, %0, #1\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24\n\t"
        "cmp %0, #0\n\t"
        "bne 2f\n\t"
        "ldr r1, [sp, #52]\n\t"
        "ldrb %0, [r1, #0]\n\t"
        "2:\n\t"
        "ldr r2, [sp, #52]\n\t"
        "add r0, r2, %0\n\t"
        "ldrb r2, [r0, #0]\n\t"
        "lsr r0, r2, #5\n\t"
        "lsl r0, r0, #2\n\t"
        "add r0, r0, %1\n\t"
        "and r2, %2\n\t"
        "mov r1, %3\n\t"
        "lsl r1, r1, r2\n\t"
        "ldr r0, [r0, #0]\n\t"
        "and r0, r0, r1\n\t"
        "cmp r0, #0\n\t"
        "beq 1b"
        : "+r"(var_r5_2)
        : "r"(decrement_flags_base), "r"(decrement_bit_limit),
          "r"(decrement_one_mask)
        : "r0", "r1", "r2", "cc", "memory");
    }
    goto block_49;
block_44:
    if (!(0x10 & temp_r1_3)) {
        goto block_51;
    }
    {
    register u8 *increment_count_pointer asm("r4");
    register u32 increment_count asm("r3");
    register s32 *increment_flags_base asm("r7");
    register u32 increment_bit_limit asm("r4");
    register u32 increment_one_mask asm("r6");

    var_r5_2 = sp38;
    increment_count_pointer = sp34;
    increment_count = *increment_count_pointer;
    increment_flags_base = (s32 *)0x020217B4;
    increment_bit_limit = 0x1F;
    increment_one_mask = 1;
    asm volatile(
        "1:\n\t"
        "add r0, %0, #1\n\t"
        "lsl r0, r0, #24\n\t"
        "lsr %0, r0, #24\n\t"
        "cmp %0, %1\n\t"
        "bls 2f\n\t"
        "mov %0, #1\n\t"
        "2:\n\t"
        "ldr r1, [sp, #52]\n\t"
        "add r0, r1, %0\n\t"
        "ldrb r2, [r0, #0]\n\t"
        "lsr r0, r2, #5\n\t"
        "lsl r0, r0, #2\n\t"
        "add r0, r0, %2\n\t"
        "and r2, %3\n\t"
        "mov r1, %4\n\t"
        "lsl r1, r1, r2\n\t"
        "ldr r0, [r0, #0]\n\t"
        "and r0, r0, r1\n\t"
        "cmp r0, #0\n\t"
        "beq 1b"
        : "+r"(var_r5_2)
        : "r"(increment_count), "r"(increment_flags_base),
          "r"(increment_bit_limit), "r"(increment_one_mask)
        : "r0", "r1", "r2", "cc", "memory");
    }
block_49:
    sp38 = var_r5_2;
    func_08092E84(0x40);
    var_r4 = 1;
    goto block_91;
block_51:
    {
    register u32 exit_input_test asm("r0");
    exit_input_test = 2;
    asm volatile("and %0, %1"
        : "+r"(exit_input_test) : "r"(temp_r1_3));
    if (!exit_input_test) {
        goto block_53;
    }
    }
    func_08092E84(0x3F);
    func_08096308(0x10, 0);
    goto loop_93;
block_53:
    func_080E2EA4();
    goto block_91;
block_54:
    if (var_r4 > 8U) {
        goto block_57;
    }
    D_0300004E = 0xDD5;
    D_03000050 = 0x10;
    state_halfword = &D_03000052;
    var_r0_6 = var_r4 * 2;
    goto block_88;
block_57:
    if (var_r4 == 9) {
        goto block_59;
    }
    goto block_86;
block_59:
    {
    register u8 *second_selected_base asm("r3");
    register u32 second_selected_index asm("r4");
    register u8 *second_selected_address asm("r0");
    second_selected_base = sp34;
    second_selected_index = sp38;
    second_selected_address = second_selected_base + second_selected_index;
    temp_r7_2 = *second_selected_address;
    }
    func_08095114(*(s32 *)0x02033F3C);
    var_r5_3 = 0;
loop_60:
    asm volatile(
        "lsl r0, %1, #2\n\t"
        "ldr r1, [sp, #68]\n\t"
        "add %0, r1, r0"
        : "=&r"(temp_r4_2)
        : "r"(var_r5_3)
        : "r0", "r1");
    if (*temp_r4_2 == 0) {
        goto block_62;
    }
    func_08094554(*temp_r4_2);
    *temp_r4_2 = 0;
block_62:
    var_r5_3 += 1;
    if ((u32) var_r5_3 <= 2U) {
        goto loop_60;
    }
    *(s32 *)0x02033F3C = func_0809A1F8(temp_r7_2, 0, 1, 0, 0, 0x02002880);
    asm volatile(
        "lsl %1, %2, #3\n\t"
        "sub %0, %1, %2\n\t"
        "lsl %0, %0, #3"
        : "=&r"(constructor_record_offset_2),
          "=&r"(constructor_stride_source_2)
        : "r"(temp_r7_2));
    constructor_base_2 = 0x087AFCC4;
    asm volatile("" : "+r"(constructor_base_2));
    temp_r0_5 = (void *)(constructor_record_offset_2 + constructor_base_2);
    var_r5_4 = 0;
    constructor_stride_keep_2 = constructor_stride_source_2;
    {
    register u32 sp48_source_2 asm("r2");
    asm volatile(
        "lsl %0, %1, #2"
        : "=r"(sp48_source_2)
        : "r"(temp_r7_2));
    sp48.value = sp48_source_2;
    }
    do {
    temp_r1_4 = var_r5_4 * 4;
    temp_r2_7 = temp_r0_5 + temp_r1_4;
    constructor_range_2 = (u16)(M2C_FIELD(temp_r2_7, u16 *, 0x1A) - 1);
    constructor_offset_2 = temp_r1_4;
    if (constructor_range_2 > 0x63U) {
        goto block_75;
    }
    animation_table_2 = (u8 *)0x087ABC6C;
    temp_r0_6 = M2C_FIELD(temp_r2_7, u16 *, 0x1A);
    doubled_x_2 = temp_r0_6 << 1;
    if (var_r5_4 == 0) {
        goto block_68;
    }
    var_r0_7 = (doubled_x_2 + 1) << 0x18;
    goto block_69;
block_68:
    var_r0_7 = temp_r0_6 << 0x19;
block_69:
    func_0809AA64(animation_table_2, var_r0_7 >> 0x18,
        (shifted_index_source_2 = var_r5_4 << 0x17) >> 0x10, var_r5_4);
    temp_r0_7 = M2C_FIELD((temp_r0_5 + constructor_offset_2), u16 *, 0x1A);
    doubled_y_2 = temp_r0_7 << 1;
    saved_shift_2 = shifted_index_source_2;
    if (var_r5_4 == 0) {
        goto block_71;
    }
    var_r0_8 = (doubled_y_2 + 1) << 0x10;
    goto block_72;
block_71:
    var_r0_8 = temp_r0_7 << 0x11;
block_72:
    constructor_y_2 = var_r0_8 >> 0x10;
    coordinate_table_2 = (u8 *)0x087EC38C;
    temp_r2_8 = temp_r7_2 << 5;
    coordinate_sum_second = constructor_offset_2 + temp_r2_8;
    {
    register u8 *coordinate_address_second asm("r3");
    asm volatile("add %0, %1, %2"
        : "=r"(coordinate_address_second)
        : "r"(coordinate_sum_second), "r"(coordinate_table_2));
    var_r3_2 = *(s16 *)coordinate_address_second;
    }
    coordinate_table_keep = coordinate_table_2;
    if (var_r5_4 != 2) {
        goto block_74;
    }
    {
    register u32 sprite_offset_io_2 asm("r0");

    sprite_offset_io_2 = 0x087AC90C;
    asm volatile(
        "mov r1, %1\n\t"
        "ldrh r1, [r1, #34]\n\t"
        "lsl r1, r1, #1\n\t"
        "str r1, [sp, #76]\n\t"
        "add r0, r1, r0\n\t"
        "mov r1, #0\n\t"
        "ldrsh r0, [r0, r1]"
        : "+r"(sprite_offset_io_2) : "r"(temp_r0_5) : "r1");
    sprite_offset_2 = (s32)sprite_offset_io_2;
    }
    var_r3_2 = (s16) (var_r3_2 - sprite_offset_2);
block_74:
    var_r0_9 = func_080D22B4(0x087AC2BC, constructor_y_2, 0, var_r3_2, ({
        register s32 coordinate_sum asm("r0");
        register u8 *coordinate_arg_base asm("r1");
        register s32 coordinate_value asm("r0");
        coordinate_sum = constructor_offset_2 + temp_r2_8;
        coordinate_arg_base = coordinate_table_keep + 2;
        coordinate_sum += (s32)coordinate_arg_base;
        coordinate_value = *(s16 *)coordinate_sum;
        coordinate_value;
    }), saved_shift_2 >> 0x10, var_r5_4, ({
        register u8 *flags_table asm("r1");
        register u32 flags_index_value asm("r0");
        register u32 flags_value asm("r0");
        register u32 constructor_flags asm("r0");
        flags_table = (u8 *)0x087ED68C;
        flags_index_value = temp_r7_2 << 1;
        flags_index_value += temp_r7_2;
        asm volatile("add %0, %1, %0"
            : "+r"(flags_index_value) : "r"(var_r5_4));
        flags_index_value += (u32)flags_table;
        flags_value = *(u8 *)flags_index_value;
        constructor_flags = flags_value << 6;
        constructor_flags |= 0x1218;
        constructor_flags;
    }), 0, 0);
    *(s32 *)(sp44 + constructor_offset_2) = var_r0_9;
    goto block_76;
block_75:
    *(s32 *)(sp44 + constructor_offset_2) = 0;
block_76:
    var_r5_4 = (u32) (u8) (var_r5_4 + 1);
    } while (var_r5_4 <= 2U);
    {
    register struct SelectionRow *graphics_base_source_2 asm("r0");
    register struct SelectionRow *graphics_base_keep_2 asm("r2");
    register s32 graphics_flags_2 asm("r3");
    register u32 graphics_low_2 asm("r3");
    register s32 graphics_high_2 asm("r1");
    register u32 graphics_stride_first_2 asm("r4");
    register u32 graphics_difference_first_2 asm("r1");
    register u32 graphics_stride_second_2 asm("r3");
    register u32 graphics_difference_second_2 asm("r1");
    register u8 graphics_state_value_2 asm("r0");
    struct SelectionRow *graphics_row_2;
    register u32 state_r0_2 asm("r0");
    register u8 *state_r1_2 asm("r1");

    graphics_base_source_2 = (struct SelectionRow *)0x087AFCC4;
    graphics_stride_first_2 = constructor_stride_keep_2;
    graphics_difference_first_2 = graphics_stride_first_2 - temp_r7_2;
    graphics_difference_first_2 <<= 3;
    asm volatile("add %0, %0, %1"
        : "+r"(graphics_difference_first_2)
        : "r"(graphics_base_source_2));
    graphics_row_2 = (struct SelectionRow *)
        graphics_difference_first_2;
    graphics_flags_2 = graphics_row_2->flags;
    graphics_high_2 = graphics_flags_2 & 0x80;
    graphics_base_keep_2 = graphics_base_source_2;
    if (graphics_high_2 != 0) {
        state_r1_2 = (u8 *)0x0203055C;
        state_r0_2 = 0xB;
        goto second_nonzero_state;
    }
    graphics_low_2 = (u8)(graphics_flags_2 & 0x40);
    if (graphics_low_2 != 0) {
        state_r1_2 = (u8 *)0x0203055C;
        state_r0_2 = 0xD;
second_nonzero_state:
        state_r1_2[2] = state_r0_2;
        state_r0_2 = (u32)state_r1_2;
        goto second_state_ready;
    }
    state_r0_2 = 0x0203055C;
    ((u8 *)state_r0_2)[2] = graphics_low_2;
second_state_ready:
    graphics_state_value_2 = ((u8 *)state_r0_2)[2];
    graphics_stride_second_2 = constructor_stride_keep_2;
    graphics_difference_second_2 = graphics_stride_second_2 - temp_r7_2;
    graphics_difference_second_2 <<= 3;
    asm volatile("add %0, %0, %1"
        : "+r"(graphics_difference_second_2)
        : "r"(graphics_base_keep_2));
    func_0809A5B4(graphics_state_value_2,
        ((struct SelectionRow *)graphics_difference_second_2)->value,
        2, 2, 1);
    }
    func_080D0AF0(0xFFFFFF00);
    func_080D12A0(2, 0);
    func_08098BB4(0x080066C7);
    func_080E2F30();
    {
    register s32 *second_first_kind_table asm("r0");
    register s32 sp48_keep asm("r4");

    second_first_kind_table = (s32 *)0x087F26C8;
    sp48_keep = sp48.value;
    asm volatile("add %0, %1, %0"
        : "+r"(second_first_kind_table) : "r"(sp48_keep));
    func_08098BB4(*second_first_kind_table);
    {
    register s32 *second_second_kind_table asm("r0");
    register s32 second_second_kind_value asm("r1");

    second_second_kind_table = (s32 *)0x087A3660;
    asm volatile(
        "add %0, %2, %0\n\t"
        "ldr %1, [%0]"
        : "+r"(second_second_kind_table),
          "=r"(second_second_kind_value)
        : "r"(sp48_keep)
        : "memory");
    func_080E2DCC(2, second_second_kind_value);
    }
    }
    func_080972C8();
    var_r4 = 0xA;
    goto block_91;
block_86:
    if (var_r4 > 0x11U) {
        goto block_90;
    }
    D_0300004E = 0xDD5;
    state_halfword = &D_03000052;
    var_r0_6 = (0x11 - var_r4) * 2;
block_88:
    *state_halfword = var_r0_6;
    var_r4 = (u32) (u8) (var_r4 + 1);
    goto block_91;
block_90:
    var_r4 = 0;
block_91:
    func_080ED17C(1);
    goto loop_28;
block_92:
    func_080ED17C(1);
loop_93:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_92;
    }
    func_08092E0C(2);
    func_080E2F30();
    return;
}
