#include "m2c_prelude.h"

#define NULL ((void *)0)

M2C_UNK func_08092E0C(s32);
M2C_UNK func_08093AE8(void *, s32);
M2C_UNK func_08093B54(void);
M2C_UNK func_0809534C(void);
M2C_UNK func_08096308(s32, s32);
s32 func_0809669C(void);
M2C_UNK func_08098BB4(u32);
u8 func_080B2EF0(void);
M2C_UNK func_080B484C(void);
M2C_UNK func_080BAB3C(void);
M2C_UNK func_080BAF2C(u8, u8, u8, u32, u32, s32, s32);
M2C_UNK func_080BB940(void);
u8 func_080C05A8(s32, s32);
u8 func_080C2518(void);
M2C_UNK func_080E5880(void *, void *);
void *func_080E669C(void);
M2C_UNK func_080E66B8(void);
s32 func_080E8C90(u32, u32, u8, s32, void *);
s32 func_080E9D88(u32, u32);
u32 func_080ECD5C(s32);
s16 func_080ECD98(s32, s32);
M2C_UNK func_080ED038(void *, void *, s32);
M2C_UNK func_080ED17C(s32);

extern u8 D_02034B4C[];
asm(".set D_case27_selected_offset, 0xA084");
extern u8 D_case27_selected_offset[];
asm(".set D_0203EBD0, D_02034B4C + 41092");
extern u8 D_0203EBD0[];
extern u8 D_020218E4[];
extern u8 D_020218E8[];
extern void *D_02032EBC[2][6];

s32 sub_080C25DC(u8 arg0)
{
    u8 scratch[36];
    u32 id;
    u32 id_offset;
    u8 *selected_ptr;
    u8 *case27_link_ptr;
    u8 *unit;
    u8 *case27_selected_unit;
    u8 *record;
    u8 *cleanup_slots;
    u8 *cleanup_slot;
    u8 *command;
    register void *battle asm("r4");
    void *effect;
    register u32 side asm("r6");
    register u32 slot asm("r5");
    register u8 *case28_base asm("r7");
    register u32 case28_side_offset asm("r4");
    register u32 case28_side_next asm("r8");
    u32 case28_slot_next;
    register u32 case28_unit_address asm("r2");
    register u32 case27_unit_slot asm("r2");
    register u32 chosen0 asm("r7");
    register u32 chosen1 asm("r7");
    register u32 shared_store_address asm("r0");
    register u32 shared_store_offset asm("r1");
    register u32 shared_store_value asm("r7");
    u32 message0;
    u32 message1;
    u8 picked;
    register u32 case25_value asm("r7");
    register u32 case25_address asm("r1");
    u8 case27_result;
    register u32 case27_initial_index asm("r4");
    u8 case27_record_index;
    u32 case27_side;
    u32 case27_slot;
    register u32 case27_zero asm("r9");
    register u32 case27_side_next asm("r8");
    register u32 case27_side_offset asm("sl");
    u8 index;
    register u32 remaining asm("r4");
    u32 case34_remaining_next;
    u8 count;
    s16 total;
    s16 maximum;
    s32 case47_count;
    u32 case47_count_saved;
    register u32 case47_count_observed asm("r2");
    s16 case47_total;
    s16 case47_maximum;
    register u32 case47_slot asm("r6");
    u8 case47_member;
    u16 *case47_result_ptr;
    register u32 case47_slot_next asm("r8");
    u32 case47_slot_narrowed;
    u32 random;
    register u32 case34_random asm("r1");
    register u32 case34_id_offset asm("r7");
    register u32 case34_chosen asm("r5");
    register u8 *case34_table asm("r9");
    register u32 case34_output_next asm("r8");
    u8 cleanup_state;

    id = arg0;
    command = D_02034B4C;
    command += id * 4;
    if (command[0xA07C] != 1)
        goto success;

    switch (command[0xA07D] - 2) {
    case 0:
        message0 = 0x08019ACF;
select_case0:
        func_08098BB4(message0);
        chosen0 = func_080C05A8(0, 0);
        if (chosen0 != 0xFF)
            goto store_case0;
        goto failure;

    case 1:
        message1 = 0x08019B0A;
select_case1:
        func_08098BB4(message1);
        chosen1 = func_080C05A8(0, 0);
        if (chosen1 != 0xFF)
            goto store_case1;
        goto failure;

    case 20:
        message0 = 0x08019B45;
        goto select_case0;

    case 24:
    case 42:
        message1 = 0x08019B7C;
        goto select_case1;

    case 25:
        case25_value = func_080C2518();
        if (case25_value == 0)
            goto failure;
        index = 0;
        if (D_02034B4C[0x27B4] == 0x1B) {
            D_02034B4C[0x27B4] = case25_value;
            goto success;
        }
case25_loop:
        index = (u8)(index + 1);
        if (index > 9)
            goto success;
        case25_address = 0x27B4;
        asm volatile(
            "add r0, %1, %0\n\t"
            "add %0, %2, r0"
            : "+r"(case25_address)
            : "r"(D_02034B4C), "r"(index)
            : "r0");
        if (*(u8 *)case25_address != 0x1B)
            goto case25_loop;
        *(u8 *)case25_address = case25_value;
        goto success;

    case 26:
        {
            u32 case26_random;
            u32 case26_offset;
            u8 *case26_row;

            case26_random = func_080ECD5C(*(s32 *)0x03000010);
            case26_row = D_02034B4C;
            case26_offset = 0x94;
            case26_offset *= id;
            case26_offset += (u32)case26_row;
            case26_row = (u8 *)case26_offset;
            case26_random >>= 7;
            case26_row[0xA084] = (u8)case26_random;
            goto success;
        }

    case 27:
        id_offset = id * 0x94;
        {
            register u32 case27_selected_base asm("r3");
            register u32 case27_selected_address asm("r0");
            register u32 case27_selected_offset asm("r5");

            case27_selected_base = (u32)D_02034B4C;
            asm volatile(
                "add %0, %1, %2"
                : "=r"(case27_selected_address)
                : "r"(id_offset), "r"(case27_selected_base));
            case27_selected_offset = (u32)D_case27_selected_offset;
            asm volatile(
                "add %0, %1, %0"
                : "+r"(case27_selected_offset)
                : "r"(case27_selected_address));
            selected_ptr = (u8 *)case27_selected_offset;
        }
case27_select:
        func_08098BB4(0x08019BBB);
        chosen0 = func_080C05A8(0, 0);
        if (chosen0 == 0xFF)
            goto failure;
        {
            register u8 *case27_selected_store asm("r0");

            case27_selected_store = selected_ptr;
            asm volatile("" : "+r"(case27_selected_store));
            *case27_selected_store = chosen0;
        }
        func_08096308(2, 8);
        while ((func_0809669C() << 24) == 0) {
            func_080ED17C(1);
        }
        func_08092E0C(7);
        func_08093B54();
        *(u8 *)0x03000074 = 0;
        func_0809534C();
        *(u8 *)0x03000075 = 1;
        *(u8 *)0x0300603D = 1;
        case27_result = func_080B2EF0();
        asm volatile("" ::
                     "r"(case27_result), "r"(case27_result),
                     "r"(case27_result), "r"(case27_result),
                     "r"(case27_result), "r"(case27_result));
        asm volatile("" ::
                     "r"(case27_result), "r"(case27_result),
                     "r"(case27_result), "r"(case27_result),
                     "r"(case27_result));
        func_080BB940();
        case27_side = 0;
        asm volatile(
            "mov %0, %1"
            : "=r"(case27_zero)
            : "r"(case27_side));
        do {
            case27_slot = 0;
            asm volatile(
                "add r1, %2, #1\n\t"
                "mov %0, r1\n\t"
                "lsl r0, %2, #2\n\t"
                "add r0, r0, %2\n\t"
                "lsl r0, r0, #3\n\t"
                "sub r0, r0, %2\n\t"
                "lsl r0, r0, #7\n\t"
                "mov %1, r0"
                : "=r"(case27_side_next),
                  "=r"(case27_side_offset)
                : "r"(case27_side)
                : "r0", "r1");
            do {
                if ((func_080E9D88(case27_side, case27_slot) << 24) != 0) {
                    u32 case27_object_offset;
                    register u32 case27_loop_unit_address asm("r2");
                    register u32 case27_loop_unit_base asm("r3");

                    case27_object_offset = case27_slot << 2;
                    case27_loop_unit_address =
                        case27_object_offset + case27_slot;
                    case27_loop_unit_address <<= 3;
                    case27_loop_unit_address -= case27_slot;
                    case27_loop_unit_address <<= 4;
                    case27_loop_unit_address += case27_side_offset;
                    case27_loop_unit_base = (u32)D_02034B4C;
                    case27_loop_unit_address += case27_loop_unit_base;
                    unit = (u8 *)case27_loop_unit_address;
                    func_080BAF2C(unit[0], unit[1], unit[0x38],
                                  case27_side, case27_slot,
                                  case27_zero, case27_zero);
                    asm volatile("" : "+r"(case27_side));
                    case27_object_offset += case27_side * 0x18;
                    case27_object_offset += (u32)D_02032EBC;
                    *(u32 *)((u8 *)*(void **)case27_object_offset +
                             0x2C) = case27_zero;
                }
                case27_slot = (u8)(case27_slot + 1);
            } while (case27_slot <= 5);
            case27_side = (u8)case27_side_next;
        } while (case27_side <= 1);
        func_080BAB3C();
        func_08093AE8((void *)0x0202F094, 1);
        {
            register u8 *case27_flag asm("r0");
            register u32 case27_flag_value asm("r1");
            register u32 case27_flag_bit asm("r2");

            case27_flag = (u8 *)0x03000074;
            case27_flag_value = *case27_flag;
            case27_flag_bit = 1;
            case27_flag_value |= case27_flag_bit;
            *case27_flag = (u8)case27_flag_value;
        }
        func_08098BB4(0x080036D3);
        func_08096308(1, 8);
        if (case27_result == 0xFF)
            goto case27_select;

        {
            register u8 *copy_id_base asm("r4");
            u32 case27_unit_id_offset;
            u32 case27_unit_slot_offset;

            {
                register u8 *case27_pre_call_base asm("r3") = D_02034B4C;

                asm volatile(
                    "add %0, %1, %2"
                    : "=r"(copy_id_base)
                    : "r"(id_offset), "r"(case27_pre_call_base));
            func_080ED038(copy_id_base + 0xA0A8,
                          ({
                              case27_slot = (u32)D_020218E4;
                              (u8 *)case27_slot +
                                  case27_result * 0x70 + 4;
                          }),
                          ({
                              register u32 case27_copy_size asm("r2") = 0x70;
                              asm volatile("str r3, [sp, #64]"
                                           : "+r"(case27_copy_size)
                                           :
                                           : "memory");
                              case27_copy_size;
                          }));
            }
            case27_unit_id_offset = id * 0x1380;
            {
                register u32 case27_selected_offset asm("r0") = 0xA084;

                asm volatile(
                    "add %0, %0, %1"
                    : "+r"(copy_id_base)
                    : "r"(case27_selected_offset));
                case27_unit_slot = *copy_id_base;
            }
            case27_unit_slot_offset = case27_unit_slot * 0x270;
            {
                register u8 *case27_data_base asm("r3");

                asm volatile("ldr %0, [sp, #64]"
                             : "=r"(case27_data_base)
                             :
                             : "memory");
                asm volatile(
                    "add %0, %0, %1"
                    : "+r"(case27_unit_slot_offset)
                    : "r"(case27_data_base));
                case27_selected_unit = (u8 *)case27_unit_id_offset +
                                       case27_unit_slot_offset;
        asm volatile(
            "mov r1, #156\n\t"
            "lsl r1, r1, #6\n\t"
            "add r0, %2, r1\n\t"
            "add %1, %1, r0\n\t"
            "ldrb %0, [%1]"
            : "=r"(case27_initial_index),
              "+r"(case27_unit_slot)
            : "r"(case27_data_base)
            : "r0", "r1");
        {
            register u32 case27_link_offset asm("r2") = 0x2706;

            asm volatile(
                "add r0, %1, %2\n\t"
                "add %0, %3, r0"
                : "=r"(case27_link_ptr)
                : "r"(case27_data_base),
                  "r"(case27_link_offset),
                  "r"(case27_initial_index)
                : "r0");
        }
        if (*case27_link_ptr == 0xFF) {
            u32 case27_record_address;
            u32 case27_record_offset;

            case27_record_address = (u32)case27_data_base + 0xA31C;
            asm volatile(""
                         : "+&r"(case27_record_address)
                         : "r"(case27_data_base));
            asm volatile(
                "add %0, %1, %0"
                : "+r"(case27_record_address)
                : "r"(case27_initial_index));
            case27_record_index = *(u8 *)case27_record_address;
            case27_record_offset = case27_record_index * 0x70;
            asm volatile(
                "add r1, %2, #4\n\t"
                "add %0, %1, r1"
                : "=r"(record)
                : "r"(case27_record_offset),
                  "r"((u8 *)case27_slot)
                : "r1");
            if (record[0] != case27_selected_unit[0])
                record[0] = case27_selected_unit[0];
            if (*(s16 *)(case27_selected_unit + 6) <=
                *(s16 *)(record + 0x3A))
                *(u16 *)(record + 6) =
                    *(u16 *)(case27_selected_unit + 6);
            else
                *(u16 *)(record + 6) = *(u16 *)(record + 0x3A);
            if (*(s16 *)(record + 0x10) <= 0xC7)
                *(u16 *)(record + 0x10) = *(u16 *)(record + 0x10) + 1;
            if (record[2] != 0) {
                u32 case27_effect_offset;

                case27_effect_offset = record[2] << 6;
                effect = (void *)0x02027378;
                asm volatile(
                    "add %0, %1, %0"
                    : "+r"(effect)
                    : "r"(case27_effect_offset));
            } else
                effect = NULL;
            func_080E5880(record, effect);
        } else {
            register u8 *case27_index_table asm("r9");
            register u32 case27_scan_address asm("r0");
            u32 case27_table_address;

            case27_slot = *case27_link_ptr;
            index = 0;
            case27_index_table = case27_data_base + 0xA31C;
            do {
                case27_scan_address =
                    (u32)case27_data_base + 0x2706;
                case27_scan_address = index + case27_scan_address;
                if (*(u8 *)case27_scan_address == case27_slot) {
                    u8 *case27_else_record_base;
                    u32 case27_else_record_offset;

                    case27_else_record_offset =
                        *(u8 *)((u32)index +
                                (u32)case27_index_table) * 0x70;
                    case27_else_record_base = D_020218E8;
                    record = case27_else_record_base +
                             case27_else_record_offset;
                    {
                        register s32 scaled_value asm("sl");
                        register s32 unit_field asm("ip");

                        scaled_value = *(s16 *)(record + 0x3A);
                        unit_field = *(s16 *)(case27_selected_unit + 6);
                        scaled_value = unit_field * scaled_value;
                        unit_field = *(s16 *)(case27_selected_unit + 0x3A);
                        *(u16 *)(record + 6) =
                            func_080ECD98(scaled_value, unit_field);
                    }
                    {
                        register u32 record_level asm("sl");

                        record_level = *(u16 *)(record + 0x10);
                        asm volatile("" : "+r"(record_level) : : "memory");
                        if (*(s16 *)(record + 0x10) <= 0xC7)
                            *(u16 *)(record + 0x10) = record_level + 1;
                    }
                    if (record[2] != 0) {
                        u32 case27_effect_offset;
                        register u32 case27_effect_base asm("r2");

                        case27_effect_offset = record[2] << 6;
                        case27_effect_base =
                            (u32)case27_else_record_base;
                        case27_effect_base += 0x5A90;
                        effect = (u8 *)(case27_effect_offset +
                                        case27_effect_base);
                    } else
                        effect = NULL;
                    func_080E5880(record, effect);
                    case27_scan_address =
                        (u32)case27_data_base + 0x2706;
                    case27_scan_address = index + case27_scan_address;
                    *(u8 *)case27_scan_address = 0xFF;
                    asm volatile(
                        "mov r0, %1\n\t"
                        "add %0, %2, r0"
                        : "=r"(case27_table_address)
                        : "r"(case27_index_table),
                          "r"(index)
                        : "r0");
                    *(u8 *)case27_table_address = 0;
                    }
                    index = (u8)(index + 1);
                } while (index <= 5);
        }
            }
        }
        {
            register u32 shared_store_base asm("r2");
            register u32 shared_store_term asm("r3");
            register u32 shared_store_selected asm("r5");

            shared_store_base = (u32)D_02034B4C;
            shared_store_term = 0x2700;
            shared_store_offset = shared_store_base + shared_store_term;
            shared_store_selected = *selected_ptr;
            shared_store_offset += shared_store_selected;
            shared_store_term = 0xA31C;
            shared_store_address = shared_store_base + shared_store_term;
            shared_store_offset = *(u8 *)shared_store_offset;
            shared_store_value = case27_result;
            goto shared_store_tail;
        }

    case 28:
        func_08096308(2, 8);
        while ((func_0809669C() << 24) == 0) {
            func_080ED17C(1);
        }
        func_08092E0C(7);
        func_08093B54();
        *(u8 *)0x03000074 = 0;
        func_0809534C();
        *(u8 *)0x03000075 = 1;
        *(u8 *)0x0300603D = 1;
        func_080B484C();
        func_080BB940();
        side = 0;
        case28_base = D_02034B4C;
        do {
            slot = 0;
            case28_side_next = side + 1;
            asm volatile(
                "lsl r0, %1, #2\n\t"
                "add r0, r0, %1\n\t"
                "lsl r0, r0, #3\n\t"
                "sub r0, r0, %1\n\t"
                "lsl %0, r0, #7"
                : "=r"(case28_side_offset)
                : "r"(side)
                : "r0");
            do {
                if ((func_080E9D88(side, slot) << 24) != 0) {
                    case28_unit_address = slot * 0x270;
                    case28_unit_address += case28_side_offset;
                    asm volatile("add %0, %1"
                                 : "+r"(case28_unit_address)
                                 : "r"(case28_base));
                    func_080BAF2C(((u8 *)case28_unit_address)[0],
                                  ((u8 *)case28_unit_address)[1],
                                  ((u8 *)case28_unit_address)[0x38],
                                  side, slot, 0, 0);
                }
                case28_slot_next = slot + 1;
                asm volatile(
                    "lsl %1, %1, #24\n\t"
                    "lsr %0, %1, #24"
                    : "=r"(slot), "+r"(case28_slot_next));
            } while (slot <= 5);
            asm volatile(
                "mov r1, %1\n\t"
                "lsl r0, r1, #24\n\t"
                "lsr %0, r0, #24"
                : "=r"(side)
                : "r"(case28_side_next)
                : "r0", "r1");
        } while (side <= 1);
        func_08093AE8((void *)0x0202F094, 1);
        *(u8 *)0x03000074 |= 1;
        func_08098BB4(0x080036D3);
        func_08096308(1, 8);
        goto success;

    case 29:
        func_08098BB4(0x08019BF0);
        chosen1 = func_080C05A8(0, 0);
        if (chosen1 != 0xFF)
            goto store_case1;
        goto failure;
store_case1:
        {
            register u32 store1_address asm("r0");
            register u32 store1_id asm("r2");
            register u8 *store1_base asm("r1");
            register u32 store1_tail asm("r3");

            store1_base = D_02034B4C;
            store1_address = 0x94;
            store1_id = id;
            asm volatile(
                "mul %0, %1\n\t"
                "add %0, %0, %2"
                : "+r"(store1_address)
                : "r"(store1_id), "r"(store1_base));
            store1_tail = 0xA084;
            asm volatile("add %0, %1"
                         : "+r"(store1_address)
                         : "r"(store1_tail));
            *(u8 *)store1_address = chosen1;
            goto success;
        }

    case 30:
        func_08098BB4(0x08019C2F);
        chosen0 = func_080C05A8(0, 0);
        if (chosen0 != 0xFF)
            goto store_case0;
        goto failure;
store_case0:
        {
            register u32 store0_id asm("r5");

            shared_store_offset = (u32)D_02034B4C;
            shared_store_address = 0x94;
            store0_id = id;
            asm volatile(
                "mul %0, %1\n\t"
                "add %0, %0, %2"
                : "+r"(shared_store_address)
                : "r"(store0_id), "r"(shared_store_offset));
            shared_store_offset = 0xA084;
            shared_store_value = chosen0;
            goto shared_store_tail;
        }

shared_store_tail:
        shared_store_address += shared_store_offset;
        *(u8 *)shared_store_address = shared_store_value;
        goto success;

    case 32:
        {
            register u32 case32_outer asm("r6");
            u8 case32_inner;
            u32 case32_id_offset;
            register u32 case32_second_seed asm("r2");
            register u32 case32_second_offset asm("r9");
            register u32 case32_row_offset asm("r4");
            register u32 case32_outer_next asm("r8");
            u32 case32_outer_narrowed;
            u8 *case32_table;

            case32_outer = 0;
            case32_id_offset = id * 0x94;
            case32_table = D_0203EBD0;
            case32_second_seed = case32_id_offset + 3;
            case32_second_offset = case32_second_seed;
            asm volatile("" : "+r"(case32_second_seed));
            do {
                case32_inner = 0;
                asm volatile(
                    "add r0, %1, #1\n\t"
                    "mov %0, r0"
                    : "=r"(case32_outer_next)
                    : "r"(case32_outer)
                    : "r0");
                asm volatile(
                    "lsl r0, %1, #1\n\t"
                    "add r0, r0, %1\n\t"
                    "lsl %0, r0, #1"
                    : "=r"(case32_row_offset)
                    : "r"(case32_outer)
                    : "r0");
                do {
                    random = func_080ECD5C(*(s32 *)0x03000010) >> 14;
                    if (random == 0) {
                        u32 case32_zero_entry_offset;
                        u32 case32_zero_first_address;
                        u32 case32_zero_second_address;

                        case32_zero_entry_offset =
                            case32_row_offset + case32_inner;
                        case32_zero_first_address = case32_zero_entry_offset;
                        case32_zero_first_address += case32_id_offset;
                        case32_zero_first_address += (u32)case32_table;
                        *(u8 *)case32_zero_first_address = case32_inner;
                        case32_zero_second_address = case32_zero_entry_offset;
                        asm volatile("add %0, r9"
                                     : "+r"(case32_zero_second_address)
                                     : "r"(case32_second_offset));
                        case32_zero_second_address += (u32)case32_table;
                        *(u8 *)case32_zero_second_address = case32_inner + 3;
                    } else {
                        u32 case32_nonzero_entry_offset;
                        u32 case32_nonzero_first_address;
                        u32 case32_nonzero_second_address;

                        case32_nonzero_entry_offset =
                            case32_row_offset + case32_inner;
                        case32_nonzero_first_address =
                            case32_nonzero_entry_offset;
                        case32_nonzero_first_address += case32_id_offset;
                        case32_nonzero_first_address += (u32)case32_table;
                        *(u8 *)case32_nonzero_first_address = case32_inner + 3;
                        case32_nonzero_second_address =
                            case32_nonzero_entry_offset;
                        asm volatile("add %0, r9"
                                     : "+r"(case32_nonzero_second_address)
                                     : "r"(case32_second_offset));
                        case32_nonzero_second_address += (u32)case32_table;
                        *(u8 *)case32_nonzero_second_address = case32_inner;
                    }
                    case32_inner = (u8)(case32_inner + 1);
                } while (case32_inner <= 2);
                case32_outer_narrowed = case32_outer_next << 24;
                case32_outer = case32_outer_narrowed >> 24;
                asm volatile("" : : "r"(case32_outer_narrowed));
            } while (case32_outer <= 1);
        }
        goto success;

    case 34:
        index = 0;
        do {
            scratch[index] = index;
            index = (u8)(index + 1);
        } while (index <= 0x23);
        remaining = 0x24;
        index = 0;
        case34_id_offset = id * 0x94;
        case34_table = D_0203EBD0;
        do {
            u8 *case34_output;

            case34_random = func_080ECD5C(*(s32 *)0x03000010);
            case34_random = (case34_random * remaining) >> 15;
            case34_random = (u8)case34_random;
            case34_output = (u8 *)(index + case34_id_offset);
            asm volatile("add %0, %1"
                         : "+r"(case34_output)
                         : "r"(case34_table));
            *case34_output = scratch[case34_random];
            case34_remaining_next = remaining - 1;
            asm volatile(
                "lsl %1, %1, #24\n\t"
                "lsr %0, %1, #24"
                : "=r"(remaining), "+r"(case34_remaining_next));
            case34_chosen = (u8)case34_random;
            case34_output_next = index + 1;
            while (case34_chosen < remaining) {
                asm volatile(
                    "mov r2, sp\n\t"
                    "add r2, r2, %0\n\t"
                    "add r2, #12\n\t"
                    "add r1, %0, #1\n\t"
                    "mov r0, sp\n\t"
                    "add r0, r0, r1\n\t"
                    "add r0, #12\n\t"
                    "ldrb r0, [r0]\n\t"
                    "strb r0, [r2]\n\t"
                    "lsl r1, r1, #24\n\t"
                    "lsr %0, r1, #24"
                    : "+r"(case34_chosen)
                    :
                    : "r0", "r1", "r2", "memory");
            }
            index = (u8)case34_output_next;
        } while (index <= 0x23);
        goto success;

failure:
        return 0;

    case 47:
        battle = func_080E669C();
        case47_count = 0;
        case47_total = 0;
        case47_slot = 0;
        do {
            if ((func_080E9D88(id, case47_slot) << 24) != 0) {
                case47_maximum = 0;
                case47_member = 0;
                case47_count++;
                case47_count_saved = case47_count;
                do {
                    if (((func_080E8C90(id, case47_slot, case47_member, 0,
                                        battle) << 16) != 0) &&
                        ((*(u16 *)((u8 *)battle + 2) & 1) == 0) &&
                        (case47_maximum <
                         ({
                             register s32 case47_battle_max asm("r1");
                             asm volatile(
                                 "mov r2, #10\n\t"
                                 "ldrsh %0, [%1, r2]"
                                 : "=r"(case47_battle_max)
                                 : "r"(battle)
                                 : "r2");
                             case47_battle_max;
                         }))) {
                        case47_maximum = *(u16 *)((u8 *)battle + 0xA);
                    }
                    case47_member = (u8)(case47_member + 1);
                } while (case47_member <= 7);
                asm volatile(
                    "mov r3, %0\n\t"
                    "lsl r0, r3, #16\n\t"
                    "asr r0, r0, #16\n\t"
                    "lsl r1, %1, #16\n\t"
                    "asr r1, r1, #16\n\t"
                    "add r0, r0, r1\n\t"
                    "lsl r0, r0, #16\n\t"
                    "lsr r0, r0, #16\n\t"
                    "mov %0, r0"
                    : "+r"(case47_total)
                    : "r"(case47_maximum)
                    : "r0", "r1", "r3");
                asm volatile(
                    "mov r5, %1\n\t"
                    "lsl r0, r5, #24\n\t"
                    "lsr %0, r0, #24"
                    : "=r"(case47_count_observed)
                    : "r"(case47_count_saved)
                    : "r0", "r5");
                case47_count = case47_count_observed;
            }
            case47_slot_next = case47_slot + 1;
            case47_slot_narrowed = case47_slot_next << 24;
            case47_slot = case47_slot_narrowed >> 24;
            asm volatile("" : : "r"(case47_slot_narrowed));
        } while (case47_slot <= 5);
        {
            register u32 case47_result_address asm("r4");
            register u32 case47_result_factor asm("r0");
            register u32 case47_result_id asm("r3");

            case47_result_factor = 0x94;
            case47_result_id = id;
            asm volatile(
                "mov %0, %1\n\t"
                "mul %0, %2"
                : "=&r"(case47_result_address)
                : "r"(case47_result_id), "r"(case47_result_factor));
            case47_result_factor = 0x0203EBD0;
            asm volatile("add %0, %1"
                         : "+r"(case47_result_address)
                         : "r"(case47_result_factor));
            case47_result_ptr = (u16 *)case47_result_address;
        }
        *case47_result_ptr = func_080ECD98(
            ({
                register s32 case47_total_argument asm("r0");

                asm volatile(
                    "mov r5, %1\n\t"
                    "lsl %0, r5, #16\n\t"
                    "asr %0, %0, #16"
                    : "=r"(case47_total_argument)
                    : "r"(case47_total)
                    : "r5");
                case47_total_argument;
            }),
            case47_count);
        func_080E66B8();
        goto success;

    default:
        goto success;
    }

success:
    shared_store_address = id;
    asm volatile("" : "+r"(shared_store_address));
    if (shared_store_address == 0) {
        register u32 cleanup_state_offset asm("r2");
        u8 *cleanup_base;
        register u32 cleanup_state_address asm("r0");
        register s32 cleanup_scratch1 asm("r1");
        register s32 cleanup_scratch2 asm("r2");

        index = 0;
        cleanup_base = D_02034B4C;
        asm volatile("" : "=&r"(cleanup_state_address),
                       "=&r"(cleanup_scratch1),
                       "=&r"(cleanup_scratch2)
                     : "r"(cleanup_base));
        cleanup_scratch1 = 0x27B4;
        asm volatile(
            "add %0, %1, %2"
            : "=r"(record)
            : "r"(cleanup_base), "r"(cleanup_scratch1));
        cleanup_state_offset = 0xA07D;
        asm volatile("add %0, %1, %2"
                     : "=&r"(cleanup_state_address)
                     : "r"(cleanup_base), "r"(cleanup_state_offset));
        cleanup_state = *(u8 *)cleanup_state_address;
        do {
            u32 cleanup_address;

            cleanup_address = index;
            cleanup_address += (u32)record;
            cleanup_slot = (u8 *)cleanup_address;
            if (*cleanup_slot == cleanup_state) {
                *cleanup_slot = 0;
                break;
            }
            index = (u8)(index + 1);
        } while (index <= 9);
    }
    return 1;
}
