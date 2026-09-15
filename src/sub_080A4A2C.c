#include "m2c_prelude.h"

M2C_UNK func_08092E74(u8);                          /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08092EA0(u8);                          /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554();                            /* extern */
M2C_UNK func_08095208(s32, s32, s32);               /* extern */
M2C_UNK func_080981F0(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_0809844C(u8, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809844C_4(s32, s32, s32, s32) asm("func_0809844C");
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A9C8(u16, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080A016C(s32, s32, s32);               /* extern */

s32 sub_080A4A2C(s32 arg0, s32 *arg1) {
    volatile s32 sp14;
    volatile s32 sp18;
    u8 * volatile sp1C;
    register s32 temp_r4 asm("r4");
    s16 temp_r7;
    register s32 var_r6 asm("r6");
    s32 var_r1;
    s32 var_r2_2;
    register s32 var_r8 asm("r8");
    register s32 call_arg asm("r0");
    u16 temp_r0_2;
    register u32 var_r2 asm("r2");
    register u32 var_r5_2 asm("r5");
    u32 var_r5_3;
    u32 var_r5_4;
    u8 *temp_r4_2;
    u8 *var_r4_3;
    u8 temp_r0;
    u8 temp_r0_3;
    u32 var_r4;
    register u32 var_r5 asm("r5");
    void *var_r2_3;

    register s32 *argp asm("sl");
    asm volatile("mov %0, %2" : "=r"(argp), "+r"(arg0) : "r"(arg1));
    arg0 <<= 24;
    arg0 = (u32)arg0 >> 24;
    sp14 = arg0;
    *(s8 *)0x02030664 = 1;
    {
    register u8 *state asm("r1") = (u8 *)0x020280EC;
    asm volatile("" : "+r"(state));
    if (*state == 0) {
        goto no_state;
    }
    }
    {
        func_08092EA0(*(u8 *)0x02030667);
        func_08092E84(0x35);
        if (*(s32 *)0x02031744 != 0) {
            func_08094554();
            *(s32 *)0x02031744 = 0;
        }
        if ((*(s32 *)0x02021690 != 0xA) || (*(u8 *)0x02031748 != 0)) {
            register u8 *menu_state asm("r4") = (u8 *)0x02030666;
            asm volatile("" : "+r"(menu_state));
            temp_r0 = *menu_state;
            if (temp_r0 != 0) {
                goto block_check_one;
            }
            goto block_12;
block_palette_copy:
            {
            register s32 *palette_table asm("r1") = (s32 *)0x087A1C08;
            register s32 selected asm("r3") = sp18;
            register s32 palette asm("r0");
            register u32 palette_offset asm("r0");
            asm volatile("" : "+r"(palette_table));
            asm volatile("" : "+r"(selected));
            palette_offset = (u32)selected << 2;
            asm volatile("" : "+r"(palette_offset));
            asm volatile(".syntax unified\n\tadds %0, %0, %1\n\t.syntax divided"
                         : "+r"(palette_offset) : "r"(palette_table) : "cc");
            palette = *(s32 *)palette_offset;
            func_08095208(palette,
                           (M2C_FIELD(var_r2_3, u8 *, 5) << 5) + 0x05000200,
                           0x20);
            }
            goto block_palette_done;
block_check_one:
            if (temp_r0 == 1) {
                func_08098BB4(0x080177F5);
block_12:
                func_08098BB4(0x080177ED);
                *menu_state = 2;
            }
        }
        var_r2 = 0;
        var_r5 = 0;
        {
        register u8 *list_base asm("r3") = (u8 *)0x020280EC;
        asm volatile("" : "+r"(list_base));
        list_base += 2;
        sp1C = list_base;
        }
        {
        register u8 *flags asm("r8") = (u8 *)0x020324B0;
        register u16 *table asm("r9") =
            ({ register u16 *table_seed asm("r1") = (u16 *)0x087AF5F8;
               asm volatile("" : "+r"(table_seed));
               table_seed; });
        register u8 *category_ptr asm("r3") = (u8 *)0x020280EC;
        u32 category = *category_ptr;
        register u8 *gfx_base asm("ip") = (u8 *)0x02002880;
        register u8 *list asm("r6") = sp1C;
        register s32 *stats_arg asm("r1") = argp;
        register u8 *stats asm("r3") = (u8 *)*stats_arg;
        asm volatile("" : "+r"(flags), "+r"(table), "+r"(category));
        asm volatile("" : "+r"(gfx_base), "+r"(list), "+r"(stats));
        do {
            register u8 *list_element asm("r1") = list + var_r5;
            register u8 *stat_element asm("r0");
            register u32 stat_value asm("r0");
            register u32 list_value asm("r1");
            register u32 combined asm("r0");
            register u32 clipped asm("r4");
            asm volatile("" : "+r"(list_element));
            asm volatile(".syntax unified\n\tadds %0, %1, %2\n\t.syntax divided"
                         : "=r"(stat_element) : "r"(var_r5), "r"(stats) : "cc");
            stat_value = stat_element[1];
            list_value = *list_element;
            asm volatile("" : "+r"(stat_value), "+r"(list_value));
            combined = stat_value + list_value;
            asm volatile(".syntax unified\n\tlsls %0, %0, #24\n\tlsrs %1, %0, #24\n\t.syntax divided"
                         : "+r"(combined), "=r"(clipped) : : "cc");
            var_r4 = clipped;
            if ((u32) var_r4 > 0x63U) {
                var_r4 = 0x63;
            }
            if ((u32) var_r4 > var_r2) {
                var_r2 = (u32) var_r4;
                {
                register u32 selected asm("r0");
                selected = var_r5 << 24;
                selected >>= 24;
                sp18 = (s32)selected;
                }
            }
            var_r5 += 1;
        } while ((u32) var_r5 <= 3U);
        {
        register u8 *flag_ptr asm("r2") = flags;
        asm volatile("" : "+r"(flag_ptr));
        if (4 & *flag_ptr) {
            *(s8 *)0x020314A4 = 0xF;
        }
        }
        temp_r0_2 = table[category];
        var_r2_2 = 0;
        if (temp_r0_2 == 0x4B) {
            var_r2_2 = sp18;
        }
        func_0809A9C8(temp_r0_2, 0, var_r2_2, 0x3C2, 0xE,
                      ({ register s32 gfx_arg asm("r3") = (s32)gfx_base;
                         asm volatile("" : "+r"(gfx_arg));
                         gfx_arg; }));
        }
        *(s32 *)0x02031744 = func_08094484(0x08359850, 0x0835985C, 0, 0x18, 0x18, 0x3C2, 0xE, 8, 0);
        func_08098BB4(0x08017A0B);
        var_r5_2 = 0;
        asm volatile("" : "+r"(var_r5_2));
loop_24:
        {
        register s32 one asm("r0") = 1;
        asm volatile("" : "+r"(one));
        var_r8 = one;
        asm volatile("" : "+r"(var_r8));
        }
        {
        register s32 selected asm("r1") = sp18;
        asm volatile("" : "+r"(selected));
        if (var_r5_2 != selected) {
            register s32 zero asm("r2") = 0;
            asm volatile("" : "+r"(zero));
            var_r8 = zero;
            asm volatile("" : "+r"(var_r8));
        }
        }
        switch (var_r5_2) {
        case 0: goto case_0;
        case 1: goto case_1;
        case 2: goto case_2;
        case 3: goto case_3;
        default:
            var_r6 = var_r5_2 + 1;
            goto cases_done;
        }
case_0:
        temp_r4 = var_r5_2 + 1;
        {
        register s32 stack_arg asm("r0") = (s32)(s16)temp_r4;
        asm volatile("" : "+r"(stack_arg));
        asm volatile("str %0, [sp]" : : "r"(stack_arg) : "memory");
        func_080981F0(0x08103D20, var_r8, 5, 0);
        }
        var_r6 = temp_r4;
        goto cases_done;
case_1:
        {
        register s32 stack_arg asm("r0") = 2;
        asm volatile("" : "+r"(stack_arg));
        asm volatile("str %0, [sp]" : : "r"(stack_arg) : "memory");
        func_080981F0(0x08103D30, var_r8, 5, 0);
        }
        var_r6 = 2;
        goto cases_done;
case_2:
        {
        register s32 stack_arg asm("r0") = 3;
        asm volatile("" : "+r"(stack_arg));
        asm volatile("str %0, [sp]" : : "r"(stack_arg) : "memory");
        func_080981F0(0x08103D40, var_r8, 5, 0);
        }
        var_r6 = 3;
        goto cases_done;
case_3:
        {
        register s32 stack_arg asm("r0") = 4;
        asm volatile("" : "+r"(stack_arg));
        asm volatile("str %0, [sp]" : : "r"(stack_arg) : "memory");
        func_080981F0(0x08103D50, var_r8, 5, 0);
        }
        var_r6 = 4;
cases_done:
        {
        register u8 *list_base asm("r3") = sp1C;
        asm volatile("" : "+r"(list_base));
        temp_r4_2 = &list_base[var_r5_2];
        }
        temp_r7 = var_r6;
        temp_r0_3 = *temp_r4_2;
        {
        register s32 five_seed asm("r1") = 5;
        register s32 five_value asm("r9") = five_seed;
        register u8 *second_stats asm("r0");
        func_0809844C(temp_r0_3, 2, var_r8, 0xA, five_seed, 7, (s32) temp_r7);
        asm volatile("mov r2, %1\n\tldr %0, [r2]\n\t.syntax unified\n\tadds %0, %2, %0\n\t.syntax divided"
                     : "=r"(second_stats) : "r"(argp), "r"(var_r5_2) : "r2", "cc");
        temp_r0_3 = second_stats[1];
        asm volatile("mov r3, %0\n\tstr r3, [sp]\n\tmovs r1, #10\n\tstr r1, [sp, #4]\n\tstr %1, [sp, #8]"
                     : : "r"(five_value), "r"((s32)temp_r7) : "r1", "r3", "memory");
        func_0809844C_4(temp_r0_3, 2, var_r8, 0xA);
        {
        register s32 *arg_carrier asm("r1") = argp;
        register u8 *stat_ptr asm("r0");
        register u32 stat_value asm("r0");
        register u32 list_and_clipped asm("r4") = (u32)temp_r4_2;
        asm volatile("" : "+r"(arg_carrier));
        stat_ptr = (u8 *)*arg_carrier;
        asm volatile(".syntax unified\n\tadds %0, %1, %0\n\t.syntax divided"
                     : "+r"(stat_ptr) : "r"(var_r5_2) : "cc");
        stat_value = stat_ptr[1];
        asm volatile("ldrb %0, [%0]\n\t.syntax unified\n\tadds %1, %1, %0\n\tlsls %1, %1, #24\n\tlsrs %0, %1, #24\n\tcmp %0, #99\n\tbls 0f\n\tmovs %0, #99\n0:\n\t.syntax divided"
                     : "+r"(list_and_clipped), "+r"(stat_value) : : "cc");
        asm volatile("mov r2, %0\n\tstr r2, [sp]\n\tmovs r0, #14\n\tstr r0, [sp, #4]\n\tstr %1, [sp, #8]"
                     : : "r"(five_value), "r"((s32)temp_r7) : "r0", "r2", "memory");
        func_0809844C_4(list_and_clipped, 2, var_r8, 0xA);
        }
        }
        var_r5_2 = (u32) var_r6;
        if (var_r5_2 <= 3U) {
            goto loop_24;
        }
        *(s32 *)0x0200A888 = 0x08103D60;
        func_08098BB4(0x080177D5);
        func_08098BB4(0x08017A2D);
        func_08094554(*(s32 *)0x02031744);
        *(s32 *)0x02031744 = 0;
        *(u8 *)0x020314A4 = 0x5F;
        func_08098BB4(0x08017A37);
        func_08092EA0(0x35U);
        func_08092E74(*(u8 *)0x02030667);
        if ((*(u8 *)0x0200A882 == 1) && (*(u8 *)0x0200A880 == 0)) {
            register u32 update_index asm("r5");
            register u8 *update_ptr asm("r4");
            register u32 maximum asm("r1");
            update_index = 0;
            asm volatile("" : "+r"(update_index));
            maximum = 99;
            asm volatile("" : "+r"(maximum));
            update_ptr = sp1C;
            asm volatile("" : "+r"(update_ptr));
            do {
                register s32 *arg_carrier asm("r3") = argp;
                register u8 *stats asm("r0");
                register u32 value asm("r0");
                register u32 old_value asm("r2");
                asm volatile("" : "+r"(arg_carrier));
                stats = (u8 *)*arg_carrier;
                asm volatile(".syntax unified\n\tadds %0, %1, %0\n\t.syntax divided"
                             : "+r"(stats) : "r"(update_index) : "cc");
                value = stats[1];
                old_value = *update_ptr;
                value += old_value;
                *update_ptr = value;
                value <<= 24;
                value >>= 24;
                if (value > 0x63U) {
                    *update_ptr = maximum;
                }
                update_ptr += 1;
                update_index += 1;
            } while (update_index <= 3U);
            {
            register u8 *state asm("r3") = (u8 *)0x020280EC;
            register u32 current asm("r0");
            register s32 selected asm("r1");
            asm volatile("" : "+r"(state));
            current = state[1];
            selected = sp18;
            asm volatile("" : "+r"(current), "+r"(selected));
            if (current != selected) {
                register u32 scan_index asm("r5") = 0;
                asm volatile("" : "+r"(scan_index));
                var_r2_3 = (void *)0x020325A0;
loop_47:
                if (M2C_FIELD(var_r2_3, u8 *, 4) == 0x4B) {
                    goto block_palette_copy;
                } else {
                    var_r2_3 += 0x48;
                    scan_index += 1;
                    if (scan_index <= 0xDU) {
                        goto loop_47;
                    }
                }
            }
            }
block_palette_done:
            {
            register u32 selected asm("r3");
            register u8 *state asm("r2");
            asm volatile("mov r2, sp\n\tldrb %0, [r2, #24]"
                         : "=r"(selected) : : "r2");
            state = (u8 *)0x020280EC;
            asm volatile("" : "+r"(state));
            state[1] = selected;
            }
            call_arg = sp14;
            asm volatile("" : "+r"(call_arg));
            var_r1 = 0x7F;
        } else {
            call_arg = sp14;
            asm volatile("" : "+r"(call_arg));
            var_r1 = 0x80;
        }
    }
    goto finish;
no_state:
    var_r1 = -1;
    call_arg = sp14;
    asm volatile("" : "+r"(call_arg));
finish:
    func_080A016C(call_arg, var_r1, 0);
    return 0;
}
