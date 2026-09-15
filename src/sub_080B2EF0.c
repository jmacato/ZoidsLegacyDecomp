#include "m2c_prelude.h"

#define NULL ((void *)0)
#define ARG7_EIGHT_R1() ({ \
    register s32 value asm("r1") = 8; \
    asm volatile("" : "+r"(value)); \
    value; \
})

extern u8 D_020218E4[];
extern u8 D_0200A881;

M2C_UNK func_08094330();                            /* extern */
M2C_UNK func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_08094484_4, func_08094484");
extern M2C_UNK func_08094484_4(s32, s32, s32, s32);
M2C_UNK func_0809534C();                            /* extern */
M2C_UNK func_0809538C(s32, M2C_UNK, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
asm(".set func_080981F0_4, func_080981F0");
M2C_UNK func_080981F0_4(s32, s32, s32, s32);         /* extern */
M2C_UNK func_0809844C(s16, s32, s32, s32, s32, s32, s32); /* extern */
asm(".set func_0809844C_wide, func_0809844C");
M2C_UNK func_0809844C_wide(s32, s32, s32, s32, s32, s32, s32); /* extern */
u8 func_08098B58();                                 /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A52C(u8, u8, s32, s32, s32);       /* extern */
M2C_UNK func_0809AB44(s32, s32, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_080AC214(s32, s32);                    /* extern */
M2C_UNK func_080ACA8C(s32, s32, s32);               /* extern */
M2C_UNK func_080ACBDC(s32, u8);                     /* extern */
asm(".set func_080ACBDC_wide, func_080ACBDC");
M2C_UNK func_080ACBDC_wide(s32, s32);                /* extern */
M2C_UNK func_080B61C8(s32, s32, s32);               /* extern */
s32 func_080E7B64(u8);                              /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
s16 func_080ECD98(s16, s32);                        /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

s32 sub_080B2EF0(void) {
    volatile s32 sp18;
    s32 temp_r4_254;
    s32 temp_r0_243;
    s32 var_r0_381;
    register s32 var_r5_255 asm("r5");
    register s32 var_r8_49 asm("r8");
    register s32 zero_sl asm("r10");
    u8 temp_r0_368;
    u8 temp_r0_388;
    u8 temp_r0_398;
    s32 temp_r5_115;
    register s32 var_r4_171 asm("r4");
    register s32 var_r5_153 asm("r5");
    u8 temp_r1_121;
    register s32 var_r1_111 asm("r1");
    register s32 var_r4_101 asm("r4");
    u8 var_r5_391;
    register s32 var_r5_89 asm("r5");
    register void *record_selector asm("r6");
    register void *dialog_result asm("r6");
    void *var_r7_9;
    register void *var_r9_0 asm("r9");
    u8 *order_base;
    register u8 *comparison_base asm("r9");
    register u8 *count_ptr asm("r6");
    register u8 *count_seed_r0 asm("r0");
    register u8 *shift_base asm("ip");
    register u8 *entity_base asm("r9");
    register u8 *roster_base asm("r8");
    register u8 *roster_count_ptr asm("r3");
    u8 *roster_order_base;
    u8 *entity_record;
    u8 *search_map_base;
    u8 *search_record;

    *(s16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x35C, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_0809AB44(2, 0, 0x1EF, 4, 4);
    func_080ECD34(0x081046A8, 0x06015840);
    func_08094330();
    {
        register s32 initial_zero_r0 asm("r0") = 0;

        asm volatile("" : "+r"(initial_zero_r0));
        var_r8_49 = initial_zero_r0;
        zero_sl = initial_zero_r0;
    }
loop_1:
    {
        register s32 dispatch_1010_r1 asm("r1") = 0x1010;

        asm volatile("" : : "r"(dispatch_1010_r1));
        if (var_r8_49 != dispatch_1010_r1) {
            goto block_3;
        }
        goto block_37;
block_3:
        if (var_r8_49 > dispatch_1010_r1) {
            goto block_8;
        }
    }
    {
        register s32 zero_test_r2 asm("r2") = var_r8_49;

        asm volatile("" : "+r"(zero_test_r2));
        if (zero_test_r2 == 0) {
            goto block_13;
        }
    }
    if (var_r8_49 != 0x1000) {
        goto block_7;
    }
    goto block_35;
block_7:
    goto block_60;
block_8:
    if (var_r8_49 != 0x1020) {
        goto block_10;
    }
    goto block_47;
block_10:
    if (var_r8_49 != 0x1030) {
        goto block_12;
    }
    goto block_54;
block_12:
    goto block_60;
block_13:
    func_08098BB4(0x080021A6);
    func_080B61C8(0, 4, 0);
    var_r5_89 = 0;
    count_seed_r0 = (u8 *)0x02032272;
    asm volatile("" : "+r"(count_seed_r0));
    if ((u32) var_r8_49 >= (u32) *count_seed_r0) {
        goto block_24;
    }
    order_base = (u8 *)0x020321A4;
    comparison_base = (u8 *)0x0203EE68;
    count_ptr = count_seed_r0;
    asm volatile("" : "+r"(count_ptr));
    shift_base = order_base;
loop_15:
    var_r4_101 = 0;
loop_16:
    {
    register u8 *order_view_r2 asm("r2") = order_base;
    register u8 *order_entry_r0 asm("r0") =
        (u8 *)(var_r5_89 + (s32)order_view_r2);
    register u8 *comparison_view_r2 asm("r2") = comparison_base;
    register u8 *comparison_entry_r1 asm("r1") =
        (u8 *)(var_r4_101 + (s32)comparison_view_r2);

    if (*order_entry_r0 != *comparison_entry_r1) {
        goto block_22;
    }
    }
    var_r1_111 = var_r5_89;
    {
        volatile u8 *inner_count_ptr = count_ptr;
        register s32 inner_limit_r0 asm("r0");

        inner_limit_r0 = *(volatile u8 *)count_ptr - 1;
        asm volatile("" : "+r"(inner_limit_r0));
        temp_r5_115 = var_r1_111 - 1;
        if ((s32) var_r1_111 < inner_limit_r0) {
            u8 *inner_shift_base = shift_base;

            do {
                u8 *shift_destination =
                    (u8 *)(var_r1_111 + (s32)inner_shift_base);

                var_r1_111 += 1;
                *shift_destination =
                    *(u8 *)(var_r1_111 + (s32)inner_shift_base);
                var_r1_111 = (u8)var_r1_111;
            } while ((s32) var_r1_111 < (s32) (*inner_count_ptr - 1));
        }
    }
block_20:
    *count_ptr -= 1;
    {
        register s32 restored_outer_r0 asm("r0") = temp_r5_115;

        restored_outer_r0 <<= 24;
        var_r5_89 = (u32)restored_outer_r0 >> 24;
    }
    goto block_23;
block_22:
    {
        register s32 inner_next_r0 asm("r0") = var_r4_101 + 1;

        inner_next_r0 <<= 24;
        var_r4_101 = (u32)inner_next_r0 >> 24;
    }
    if ((u32) var_r4_101 <= 5U) {
        goto loop_16;
    }
block_23:
    {
        register s32 outer_next_r0 asm("r0") = var_r5_89 + 1;

        outer_next_r0 <<= 24;
        var_r5_89 = (u32)outer_next_r0 >> 24;
    }
    if ((u32) var_r5_89 < (u32) *count_ptr) {
        goto loop_15;
    }
block_24:
    {
    register s32 roster_next_r2 asm("r2");

    var_r5_153 = 1;
    entity_base = (u8 *)0x020218E4;
    roster_base = (u8 *)0x0203EE68;
    roster_count_ptr = (u8 *)0x02032272;
    roster_order_base = (u8 *)0x020321A4;
loop_25:
    entity_record = entity_base + (var_r5_153 * 0x70);
    {
    register u32 roster_flag_r0 asm("r0") =
        4 & *(u16 *)(entity_record + 8);

    roster_next_r2 = var_r5_153 + 1;
    if (!roster_flag_r0) {
        goto block_32;
    }
    }
    var_r4_171 = 0;
    if (var_r5_153 == *roster_base) {
        goto block_30;
    }
    {
        register u8 *inner_roster_base_r1 asm("r1") =
            (u8 *)0x0203EE68;

        asm volatile("" : "+r"(inner_roster_base_r1));
loop_28:
        {
            register s32 roster_inner_next_r0 asm("r0") = var_r4_171 + 1;

            roster_inner_next_r0 <<= 24;
            var_r4_171 = (u32)roster_inner_next_r0 >> 24;
        }
        if ((u32) var_r4_171 > 5U) {
            goto block_30;
        }
        if (var_r5_153 !=
            *(u8 *)(var_r4_171 + (s32)inner_roster_base_r1)) {
            goto loop_28;
        }
    }
block_30:
    if (var_r4_171 != 6) {
        goto block_32;
    }
    *(u8 *)(*roster_count_ptr + (s32)roster_order_base) = var_r5_153;
    *roster_count_ptr = (u8)(*roster_count_ptr + 1);
block_32:
    {
        register s32 roster_outer_next_r0 asm("r0") = roster_next_r2;

        roster_outer_next_r0 <<= 24;
        var_r5_153 = (u32)roster_outer_next_r0 >> 24;
    }
    if ((u32) var_r5_153 <= 0xCEU) {
        goto loop_25;
    }
    }
    func_080AC214(3, 0);
    {
        register void *dialog_zero_r1 asm("r1") = NULL;

        asm volatile("" : "+r"(dialog_zero_r1));
        var_r9_0 = dialog_zero_r1;
    }
    record_selector = NULL;
    func_080ACA8C(7, 1, 1);
    func_08096308(0xF, 0);
    {
        register s32 next_state_r2 asm("r2") = 0x1000;

        asm volatile("" : "+r"(next_state_r2));
        var_r8_49 = next_state_r2;
    }
    goto block_60;
block_35:
    asm volatile(
        "mov r0, #72\n\t"
        "str r0, [sp, #0]\n\t"
        "mov r0, sl\n\t"
        "str r0, [sp, #4]\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r1, #8\n\t"
        "str r1, [sp, #12]\n\t"
        "str r0, [sp, #16]"
        : : "r"(zero_sl) : "r0", "r1", "memory");
    func_08094484_4(
        ({ register s32 arg asm("r0") = 0x0821024C;
           asm volatile("" : "+r"(arg)); arg; }),
        ({ register s32 arg asm("r1") = 0x08210258;
           asm volatile("" : "+r"(arg)); arg; }),
        0, 0xB8);
    asm volatile(".if 0");
    func_08094484(0, 0, 0, 0, 0, 0, 0, 0, 0);
    asm volatile(".endif");
    {
        register s32 next_state_r2 asm("r2") = 0x1010;

        asm volatile("" : "+r"(next_state_r2));
        var_r8_49 = next_state_r2;
    }
    goto block_60;
block_37:
    {
    register u8 *order_entry_r0 asm("r0") = (u8 *)0x020321A4;
    register s32 record_base_r1 asm("r1");

    asm volatile("add %0, %1, %0"
        : "+r"(order_entry_r0) : "r"(record_selector));
    temp_r0_243 = *order_entry_r0 * 0x70;
    record_base_r1 = 0x020218E8;
    asm volatile("" : "+r"(record_base_r1));
    var_r7_9 = (void *)(temp_r0_243 + record_base_r1);
    func_0809A52C(M2C_FIELD(var_r7_9, u8 *, 0), M2C_FIELD(var_r7_9, u8 *, 1), 0, 0, 0x02002880);
    }
    {
    register s32 ten_r6 asm("r6");

    temp_r4_254 = M2C_FIELD(var_r7_9, s16 *, 6);
    var_r5_255 = 0;
    {
    register s32 compare_result_r0 asm("r0");
    register s32 compare_value_r1 asm("r1");

    compare_result_r0 = M2C_FIELD(var_r7_9, s16 *, 0x3A);
    ten_r6 = 0xA;
    asm volatile("" : "+r"(ten_r6));
    compare_value_r1 = 0xA;
    asm volatile("bl func_080ECD98"
        : "+r"(compare_result_r0), "+r"(compare_value_r1)
        : "r"(ten_r6), "r"(var_r7_9)
        : "r2", "r3", "ip", "lr", "cc", "memory");
    compare_value_r1 = temp_r4_254;
    asm volatile("" : "+r"(compare_value_r1));
    if (compare_value_r1 >= (s16) compare_result_r0) {
        goto block_39;
    }
    }
    var_r5_255 = 1;
block_39:
    asm volatile(
        "mov r0, #4\n\t"
        "str r0, [sp, #0]\n\t"
        "mov r0, #3\n\t"
        "str r0, [sp, #4]\n\t"
        "mov r1, #8\n\t"
        "str r1, [sp, #8]\n\t"
        ".syntax unified\n\t"
        "adds r0, %0, #0\n\t"
        ".syntax divided\n\t"
        "mov r1, #4\n\t"
        ".syntax unified\n\t"
        "adds r2, %1, #0\n\t"
        ".syntax divided\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : "r"(temp_r4_254), "r"(var_r5_255), "r"(ten_r6)
        : "r0", "r1", "r2", "r3", "ip", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C_wide(temp_r4_254, 4, var_r5_255, 0xA, 4, 3,
        ARG7_EIGHT_R1());
    asm volatile(".endif");
    asm volatile(
        "mov r2, #58\n\t"
        "ldrsh r0, [%0, r2]\n\t"
        "mov r1, #4\n\t"
        "str r1, [sp, #0]\n\t"
        "mov r2, #8\n\t"
        "str r2, [sp, #4]\n\t"
        "str r2, [sp, #8]\n\t"
        "mov r2, #0\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : "r"(var_r7_9)
        : "r0", "r1", "r2", "r3", "ip", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C(M2C_FIELD(var_r7_9, s16 *, 0x3A), 4, 0, 0xA, 4, 8, 8);
    asm volatile(".endif");
    asm volatile(
        "mov r1, #62\n\t"
        "ldrsh r0, [%0, r1]\n\t"
        "mov r2, #4\n\t"
        "str r2, [sp, #0]\n\t"
        "mov r1, #8\n\t"
        "str r1, [sp, #4]\n\t"
        "mov r2, #9\n\t"
        "str r2, [sp, #8]\n\t"
        "mov r1, #4\n\t"
        "mov r2, #0\n\t"
        "mov r3, #10\n\t"
        "bl func_0809844C"
        : : "r"(var_r7_9)
        : "r0", "r1", "r2", "r3", "ip", "lr", "cc", "memory");
    asm volatile(".if 0");
    func_0809844C(M2C_FIELD(var_r7_9, s16 *, 0x3E), 4, 0, 0xA, 4, 8, 9);
    asm volatile(".endif");
    func_0809844C((s16) M2C_FIELD(var_r7_9, u8 *, 0x39), 2, 0, 0xA, 4, ten_r6, ten_r6);
    }
    {
    register s32 first_item_base asm("r2");
    s32 first_item_address = M2C_FIELD(var_r7_9, u8 *, 2) << 6;
    s32 item_offset;
    register s32 second_item_base asm("r1");
    s32 second_item_address;

    first_item_base = (s32)D_020218E4;
    asm volatile("" : "+r"(first_item_base));
    first_item_address += first_item_base;
    item_offset = 0x5A94;
    first_item_address += item_offset;
    func_080981F0(func_080E7B64(*(u8 *)first_item_address), 0, 4, 3, 0xC);
    second_item_address = M2C_FIELD(var_r7_9, u8 *, 2) << 6;
    second_item_base = (s32)D_020218E4;
    asm volatile("" : "+r"(second_item_base));
    second_item_address += second_item_base;
    second_item_address += item_offset;
    func_080E7B64(*(u8 *)second_item_address);
    }
    {
    register u32 result_r0 asm("r0") = func_08098B58();
    register u32 width_r4 asm("r4");
    register s32 index_r5 asm("r5");
    register s32 remaining_r0 asm("r0");

    result_r0 <<= 24;
    width_r4 = result_r0 >> 24;
    index_r5 = 0;
    asm volatile("" : "+r"(index_r5));
    {
    register s32 nine_r2 asm("r2") = 9;

    asm volatile("" : "+r"(nine_r2));
    remaining_r0 = nine_r2 - width_r4;
    }
    if (index_r5 < remaining_r0) {
        register s32 bound_r6 asm("r6") = remaining_r0;

        do {
            register s32 call_r3 asm("r3");
            register s32 index_next_r0 asm("r0");

            asm volatile(
                "add %0, %1, #3\n\t"
                "add %0, %0, %2"
                : "=&r"(call_r3)
                : "r"(width_r4), "r"(index_r5));
            func_080981F0(0x081061C4, 0, 4, call_r3, 0xC);
            index_next_r0 = index_r5 + 1;
            asm volatile("" : "+r"(index_next_r0));
            index_r5 = (u8)index_next_r0;
        } while (index_r5 < bound_r6);
    }
    }
block_42:
    func_080ACBDC_wide(7, (s32)var_r9_0);
    func_08098BB4(0x080021FE);
    dialog_result = (void *) *(u8 *)0x0200A880;
    var_r9_0 = (void *)D_0200A881;
    temp_r0_368 = *(u8 *)0x0200A882;
    if (temp_r0_368 == 1) {
        goto block_45;
    }
    if (temp_r0_368 == 2) {
        goto block_46;
    }
    goto block_60;
block_45:
    {
        register u32 flag_value_r0 asm("r0");
        register u32 mask_seed_r2 asm("r2");
        register u32 mask_r1 asm("r1");

        flag_value_r0 = M2C_FIELD(var_r7_9, u16 *, 4);
        mask_seed_r2 = 0xFFFE;
        asm volatile("" : "+r"(mask_seed_r2));
        mask_r1 = mask_seed_r2;
        asm volatile("" : "+r"(mask_r1));
        flag_value_r0 &= mask_r1;
        M2C_FIELD(var_r7_9, u16 *, 4) = (u16)flag_value_r0;
    }
    var_r0_381 = 0x1020;
    goto block_59;
block_46:
    {
        register s32 cancel_value_r1 asm("r1") = 0xFF;

        asm volatile("" : "+r"(cancel_value_r1));
        sp18 = cancel_value_r1;
    }
    goto block_62;
block_47:
    {
    register u8 *search_entity_base_r3 asm("r3");
    register u32 search_map_offset_r2 asm("r2");
    register u8 *search_map_base_r4 asm("r4");
    register u32 wanted_r0 asm("r0");
    register u32 wanted_r2 asm("r2");
    register s32 search_index_r5 asm("r5");
    register s32 index_next_r0 asm("r0");
    register u32 entry_r0 asm("r0");
    register u8 *entry_address_r1 asm("r1");
    register u32 entry_r1 asm("r1");

    wanted_r0 = M2C_FIELD(var_r7_9, u8 *, 2);
    asm volatile("" : "+r"(wanted_r0));
    if (wanted_r0 == 0) {
        goto block_56;
    }
    search_index_r5 = 0;
    search_entity_base_r3 = D_020218E4;
    asm volatile("" : "+r"(search_entity_base_r3));
    search_map_offset_r2 = 0x690C;
    asm volatile("" : "+r"(search_map_offset_r2));
    search_map_base_r4 = search_entity_base_r3 + search_map_offset_r2;
    wanted_r2 = wanted_r0;
    asm volatile("" : "+r"(wanted_r2));
loop_49:
    entry_address_r1 =
        (u8 *)(search_index_r5 + (s32)search_map_base_r4);
    entry_r0 = *entry_address_r1;
    if (entry_r0 == 0) {
        goto block_51;
    }
    entry_r1 = entry_r0;
    asm volatile("" : "+r"(entry_r1));
    if (wanted_r2 == search_entity_base_r3[(entry_r1 * 0x70) + 6]) {
        goto block_52;
    }
block_51:
    index_next_r0 = search_index_r5 + 1;
    asm volatile("" : "+r"(index_next_r0));
    search_index_r5 = (u8)index_next_r0;
    if ((u32)search_index_r5 <= 5U) {
        goto loop_49;
    }
block_52:
    if (search_index_r5 != 6) {
        goto block_56;
    }
    var_r0_381 = 0x1030;
    goto block_59;
    }
block_54:
    func_08098BB4(0x080024F3);
    {
    register s32 *message_table_r4 asm("r4") = (s32 *)0x087EDD54;
    register s32 message_call_r0 asm("r0");

    asm volatile("" : "+r"(message_table_r4));
    message_call_r0 = message_table_r4[M2C_FIELD(var_r7_9, u8 *, 0)];
    asm volatile(
        "mov r1, sl\n\t"
        "str r1, [sp, #0]"
        : "+r"(message_call_r0) : "r"(zero_sl) : "r1", "memory");
    func_080981F0_4(message_call_r0, 2, 9, 0);
    func_08098B58(message_table_r4[M2C_FIELD(var_r7_9, u8 *, 0)]);
    }
    {
    register s32 first_message_item_base asm("r2");
    s32 first_message_item_address = M2C_FIELD(var_r7_9, u8 *, 2) << 6;
    s32 message_item_offset;
    register s32 second_message_item_base asm("r1");
    s32 second_message_item_address;

    first_message_item_base = (s32)D_020218E4;
    asm volatile("" : "+r"(first_message_item_base));
    first_message_item_address += first_message_item_base;
    message_item_offset = 0x5A94;
    first_message_item_address += message_item_offset;
    func_080981F0(func_080E7B64(*(u8 *)first_message_item_address), 1, 9, 0, 2);
    second_message_item_address = M2C_FIELD(var_r7_9, u8 *, 2) << 6;
    second_message_item_base = (s32)D_020218E4;
    asm volatile("" : "+r"(second_message_item_base));
    second_message_item_address += second_message_item_base;
    second_message_item_address += message_item_offset;
    func_080E7B64(*(u8 *)second_message_item_address);
    }
    func_08098B58();
    {
    register s32 message_r0 asm("r0");
    register s32 message_r1 asm("r1");
    register s32 message_r2 asm("r2");
    register s32 message_r3 asm("r3");

    message_r2 = zero_sl;
    asm volatile(
        "str %0, [sp, #0]\n\t"
        "str %0, [sp, #4]\n\t"
        "mov r0, #47\n\t"
        "str r0, [sp, #8]\n\t"
        "mov r0, #63\n\t"
        "str r0, [sp, #12]"
        : "+r"(message_r2) : : "r0", "memory");
    message_r0 = 1;
    message_r1 = 0x20D0;
    message_r2 = 0x850;
    message_r3 = 0;
    asm volatile("bl func_0809538C"
        : "+r"(message_r0), "+r"(message_r1), "+r"(message_r2), "+r"(message_r3)
        : : "lr", "cc", "memory");
    }
    func_08098BB4(0x0800254C);
    func_0809534C();
    if (*(u8 *)0x0200A882 != 1) {
        goto block_58;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto block_58;
    }
block_56:
    {
        register u8 *selected_order_r0 asm("r0") = (u8 *)0x020321A4;

        asm volatile("add %0, %1, %0"
            : "+r"(selected_order_r0) : "r"(dialog_result));
        sp18 = *selected_order_r0;
    }
    goto block_62;
block_58:
    var_r0_381 = 0x1010;
block_59:
    var_r8_49 = var_r0_381;
block_60:
    {
    register s32 tail_guard_r1 asm("r1") = 0;

    asm volatile("" : "+r"(tail_guard_r1));
    if (tail_guard_r1 != 0) {
        goto block_62;
    }
    }
    goto loop_1;
block_62:
    func_08096308(0x10, 0);
    goto loop_65;
block_64:
    func_080ED17C(1);
loop_65:
    if ((func_0809669C() << 0x18) == 0) {
        goto block_64;
    }
    return sp18;
}
