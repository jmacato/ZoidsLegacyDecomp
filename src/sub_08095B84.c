#include "m2c_prelude.h"

s16 func_08092A90(s32);                             /* extern */
s16 func_08092ADC(s32);                             /* extern */
extern u8 D_02000000[];

void sub_08095B84(void) {
    volatile s32 sp0;
    volatile s32 sp4;
    register s32 var_ip asm("ip");
    register s32 var_ip_2 asm("ip");
    s32 var_r1;
    s32 var_r1_2;
    register s32 var_r6 asm("r6");
    s32 var_r7;
    register s32 var_r8 asm("r8");
    register s32 var_r9 asm("r9");
    register s32 var_sl asm("sl");
    register s32 var_sl_2 asm("sl");
    u32 temp_r0;
    u32 temp_r1;

    {
        register u32 clear_index asm("r3") = 0;
        register u8 *angle_ptr asm("r8") = (u8 *)0x03005EF2;
        register u8 *screen_base asm("r6") = D_02000000;
        register u8 *page_select asm("r5") = (u8 *)0x03005F12;
        register u32 one asm("r4") = 1;

        do {
            register u32 destination asm("r2");
            register u32 value asm("r0");
            if (clear_index <= 0x4F) {
                register u32 page asm("r0");
                register u32 bank asm("r1");
                destination = clear_index << 3;
                asm volatile("" : "+r"(destination));
                page = *page_select;
                bank = one;
                bank ^= page;
                page = bank << 2;
                page += bank;
                page <<= 8;
                destination += page;
                destination += (u32)screen_base;
                value = 0x78F00000;
            } else {
                register u32 page asm("r0");
                register u32 bank asm("r1");
                destination = clear_index << 3;
                asm volatile("" : "+r"(destination));
                page = *page_select;
                bank = one;
                bank ^= page;
                page = bank << 2;
                page += bank;
                page <<= 8;
                destination += page;
                destination += (u32)screen_base;
                value = 0x00780000;
            }
            *(u32 *)destination = value;
            {
                register u32 next asm("r0") = clear_index + 1;
                next <<= 24;
                clear_index = next >> 24;
            }
        } while (clear_index <= 0x9F);
        asm volatile("" : : "r"(angle_ptr));
    var_r7 = 0;
    var_r6 = 0;
    {
        register u8 *call_ptr asm("r1") = angle_ptr;
        register u32 call_arg asm("r0") = *call_ptr;
        asm volatile("" : "+r"(call_ptr), "+r"(call_arg));
        var_r1 = 0 - (func_08092ADC(call_arg) * 0xA0);
    }
    if (var_r1 < 0) {
        var_r1 += 0xFF;
    }
    var_r9 = var_r1 >> 8;
    {
        register u8 *call_ptr asm("r3") = angle_ptr;
        register u32 call_arg asm("r0") = *call_ptr;
        asm volatile("" : "+r"(call_ptr), "+r"(call_arg));
        var_r1_2 = 0 - (func_08092A90(call_arg) * 0xA0);
    }
    if (var_r1_2 < 0) {
        var_r1_2 += 0xFF;
    }
    var_r8 = var_r1_2 >> 8;
    }
    {
    register s32 sign_test asm("r4") = var_r9;
    asm volatile("" : "+r"(sign_test));
    if (sign_test >= 0) {
        register s32 zero asm("r0") = 0;
        sp0 = zero;
    } else {
        register s32 magnitude asm("r1") = var_r9;
        register s32 one asm("r3");
        magnitude = 0 - magnitude;
        var_r9 = magnitude;
        one = 1;
        sp0 = one;
    }
    }
    {
    register s32 sign_test asm("r4") = var_r8;
    asm volatile("" : "+r"(sign_test));
    if (sign_test >= 0) {
        register s32 zero asm("r0") = 0;
        sp4 = zero;
    } else {
        register s32 magnitude asm("r1") = var_r8;
        register s32 one asm("r3");
        asm volatile("" : "+r"(magnitude));
        magnitude = 0 - magnitude;
        var_r8 = magnitude;
        one = 1;
        sp4 = one;
    }
    }
    if (var_r9 > var_r8) {
        register s32 zero asm("r4") = 0;
        asm volatile("" : "+r"(zero));
        var_ip = zero;
        if (var_ip > var_r9) {
            return;
        }
        {
            register s32 steps asm("r0") = 1;
            asm volatile("" : "+r"(steps));
            steps += var_r9;
            var_sl = steps;
        }
loop_56:
        {
        register u8 *screen_0 asm("r2");
        register u8 *screen_2 asm("r3");
        {
        register u32 row asm("r0") = var_r6 + 0x4F;
        temp_r0 = row;
        if (temp_r0 <= 0x4FU) {
            register s32 clamp asm("r4") = var_r7 + 0x77;
            register u32 row_index asm("r5");
            asm volatile("" : "+r"(clamp));
            row_index = row;
            if (clamp < 0) {
                clamp = 0;
            } else if (clamp > 0xEF) {
                clamp = 0xEF;
            }
            {
                register u8 *page_ptr asm("r1") = (u8 *)0x03005F12;
                register u32 page asm("r0") = *page_ptr;
                register u32 bank asm("r1") = 1;
                register u32 address asm("r0");
                register u32 offset asm("r1");
                register u32 value asm("r1");
                bank ^= page;
                address = bank << 2;
                address += bank;
                address <<= 8;
                offset = row_index << 3;
                address += offset;
                screen_0 = D_02000000;
                address += (u32)screen_0;
                value = (u32)clamp + 1;
                *(u16 *)address = value;
            }
            {
            register s32 clamp2 asm("r4");
            register u32 opposite_row asm("r5");
            register u32 start_x asm("r0") = 0x78;
            clamp2 = start_x - var_r7;
            start_x = 0x50;
            opposite_row = start_x - var_r6;
            if (clamp2 < 0) {
                clamp2 = 0;
            } else if (clamp2 > 0xEF) {
                clamp2 = 0xEF;
            }
            {
                register u8 *page_ptr asm("r3") = (u8 *)0x03005F12;
                register u32 page asm("r0") = *page_ptr;
                register u32 bank asm("r1") = 1;
                register u32 address asm("r0");
                register u32 offset asm("r1");
                register u32 value asm("r1");
                bank ^= page;
                address = bank << 2;
                address += bank;
                address <<= 8;
                offset = opposite_row << 3;
                address += offset;
                address += (u32)screen_0;
                value = (u32)clamp2 << 8;
                screen_0 = (u8 *)0xF0;
                value |= (u32)screen_0;
                *(u16 *)address = value;
            }
            }
        }
        }
        {
        register u32 column asm("r1") = var_r7 + 0x4F;
        temp_r1 = column;
        if (temp_r1 <= 0x4FU) {
            register s32 clamp3 asm("r4");
            register u32 column_index asm("r5");
            register u32 start_y asm("r0") = 0x77;
            asm volatile("" : "+r"(start_y));
            clamp3 = start_y - var_r6;
            asm volatile("" : "+r"(clamp3));
            column_index = column;
            if (clamp3 < 0) {
                clamp3 = 0;
            } else if (clamp3 > 0xEF) {
                clamp3 = 0xEF;
            }
            {
                register u8 *page_ptr asm("r1") = (u8 *)0x03005F12;
                register u32 page asm("r0") = *page_ptr;
                register u32 bank asm("r1") = 1;
                register u32 address asm("r0");
                register u32 offset asm("r1");
                register u32 value asm("r1");
                register u32 high asm("r4");
                register u32 high_copy asm("r2");
                bank ^= page;
                address = bank << 2;
                address += bank;
                address <<= 8;
                offset = column_index << 3;
                address += offset;
                screen_2 = (u8 *)0x02000002;
                address += (u32)screen_2;
                value = (u32)clamp3 + 1;
                high = 0x7800;
                asm volatile("" : "+r"(high));
                high_copy = high;
                asm volatile("" : "+r"(high_copy));
                value |= high_copy;
                *(u16 *)address = value;
            }
            {
            register s32 clamp4 asm("r4") = var_r6;
            register u32 opposite_column asm("r5");
            register u32 start asm("r0");
            clamp4 += 0x78;
            start = 0x50;
            opposite_column = start - var_r7;
            if (clamp4 < 0) {
                clamp4 = 0;
            } else if (clamp4 > 0xEF) {
                clamp4 = 0xEF;
            }
            {
                register u8 *page_ptr asm("r1") = (u8 *)0x03005F12;
                register u32 page asm("r0") = *page_ptr;
                register u32 bank asm("r1") = 1;
                register u32 address asm("r0");
                register u32 offset asm("r1");
                register u32 value asm("r1");
                register u32 low asm("r2");
                bank ^= page;
                address = bank << 2;
                address += bank;
                address <<= 8;
                offset = opposite_column << 3;
                address += offset;
                address += (u32)screen_2;
                value = (u32)clamp4 << 8;
                low = 0x78;
                value |= low;
                *(u16 *)address = value;
            }
            }
        }
        }
        }
        {
        register s32 flag asm("r3") = sp0;
        asm volatile("" : "+r"(flag));
        if (flag == 0) {
            var_r7 += 1;
        } else {
            var_r7 -= 1;
        }
        }
        var_ip += var_r8;
        if (var_ip >= var_r9) {
            register s32 flag asm("r4") = sp4;
            asm volatile("" : "+r"(flag));
            if (flag == 0) {
                var_r6 += 1;
            } else {
                var_r6 -= 1;
            }
            {
                register s32 acc asm("r0") = var_ip;
                register s32 major asm("r1") = var_r9;
                asm volatile("" : "+r"(acc), "+r"(major));
                asm volatile(".syntax unified\n\tsubs %0, %0, %1\n\t.syntax divided"
                             : "+r"(acc) : "r"(major) : "cc");
                var_ip = acc;
            }
        }
        {
        register s32 decrement asm("r3") = 1;
        register s32 test asm("r4");
        asm volatile("" : "+r"(decrement));
        asm volatile(".syntax unified\n\tnegs %0, %0\n\tadd %1, %0\n\t.syntax divided"
                     : "+r"(decrement), "+r"(var_sl) : : "cc");
        test = var_sl;
        asm volatile("" : "+r"(test));
        if (test != 0) {
            goto loop_56;
        }
        }
        return;
    }
    {
    register s32 zero asm("r0") = 0;
    register s32 major_test asm("r1");
    asm volatile("" : "+r"(zero));
    var_ip_2 = zero;
    asm volatile("" : "+r"(var_ip_2));
    major_test = var_r8;
    asm volatile("" : "+r"(major_test));
    if (major_test < 0) {
        return;
    }
    }
    {
    register s32 steps asm("r3") = 1;
    asm volatile("" : "+r"(steps));
    steps += var_r8;
    var_sl_2 = steps;
    }
loop_21:
    {
    register u8 *screen_0_first asm("r3");
    register u8 *screen_0_second asm("r2");
    {
    register u32 row asm("r0") = var_r6 + 0x4F;
    if (row <= 0x4FU) {
        register s32 clamp asm("r4") = var_r7 + 0x77;
        register u32 row_index asm("r5") = row;
        asm volatile("" : "+r"(clamp), "+r"(row_index));
        if (clamp < 0) {
            clamp = 0;
        } else if (clamp > 0xEF) {
            clamp = 0xEF;
        }
        {
        register u8 *page_ptr asm("r1") = (u8 *)0x03005F12;
        register u32 page asm("r0") = *page_ptr;
        register u32 bank asm("r1") = 1;
        register u32 address asm("r0");
        register u32 offset asm("r1");
        register u32 value asm("r1");
        bank ^= page;
        address = bank << 2;
        address += bank;
        address <<= 8;
        offset = row_index << 3;
        address += offset;
        screen_0_first = D_02000000;
        address += (u32)screen_0_first;
        value = (u32)clamp + 1;
        *(u16 *)address = value;
        }
        {
        register s32 clamp2 asm("r4");
        register u32 opposite_row asm("r5");
        register u32 start asm("r0") = 0x78;
        asm volatile("" : "+r"(start));
        clamp2 = start - var_r7;
        start = 0x50;
        opposite_row = start - var_r6;
        screen_0_second = screen_0_first;
        asm volatile("" : "+r"(screen_0_second));
        if (clamp2 < 0) {
            clamp2 = 0;
        } else if (clamp2 > 0xEF) {
            clamp2 = 0xEF;
        }
        {
        register u8 *page_ptr asm("r1") = (u8 *)0x03005F12;
        register u32 page asm("r0") = *page_ptr;
        register u32 bank asm("r1") = 1;
        register u32 address asm("r0");
        register u32 offset asm("r1");
        register u32 value asm("r1");
        bank ^= page;
        address = bank << 2;
        address += bank;
        address <<= 8;
        offset = opposite_row << 3;
        address += offset;
        address += (u32)screen_0_second;
        value = (u32)clamp2 << 8;
        screen_0_second = (u8 *)0xF0;
        value |= (u32)screen_0_second;
        *(u16 *)address = value;
        }
        }
    }
    }
    {
    register u32 column asm("r1") = var_r7 + 0x4F;
    if (column <= 0x4FU) {
        register s32 clamp3 asm("r4");
        register u32 column_index asm("r5");
        register u32 start_y asm("r0") = 0x77;
        asm volatile("" : "+r"(start_y));
        clamp3 = start_y - var_r6;
        column_index = column;
        asm volatile("" : "+r"(column_index));
        if (clamp3 < 0) {
            clamp3 = 0;
        } else if (clamp3 > 0xEF) {
            clamp3 = 0xEF;
        }
        {
        register u8 *page_ptr asm("r3") = (u8 *)0x03005F12;
        register u32 page asm("r0") = *page_ptr;
        register u32 bank asm("r1") = 1;
        register u32 address asm("r0");
        register u32 offset asm("r1");
        register u8 *base asm("r1");
        register u32 value asm("r1");
        register u32 high asm("r3");
        register u32 high_copy asm("r2");
        bank ^= page;
        address = bank << 2;
        address += bank;
        address <<= 8;
        offset = column_index << 3;
        address += offset;
        base = (u8 *)0x02000002;
        address += (u32)base;
        value = (u32)clamp3 + 1;
        high = 0x7800;
        asm volatile("" : "+r"(high));
        high_copy = high;
        asm volatile("" : "+r"(high_copy));
        value |= high_copy;
        *(u16 *)address = value;
        }
        {
        register s32 clamp4 asm("r4") = var_r6;
        register u32 opposite_column asm("r5");
        register u32 start asm("r0");
        register u8 *base asm("r3");
        clamp4 += 0x78;
        start = 0x50;
        opposite_column = start - var_r7;
        base = (u8 *)0x02000002;
        asm volatile("" : "+r"(base));
        if (clamp4 < 0) {
            clamp4 = 0;
        } else if (clamp4 > 0xEF) {
            clamp4 = 0xEF;
        }
        {
        register u8 *page_ptr asm("r1") = (u8 *)0x03005F12;
        register u32 page asm("r0") = *page_ptr;
        register u32 bank asm("r1") = 1;
        register u32 address asm("r0");
        register u32 offset asm("r1");
        register u32 value asm("r1");
        register u32 low asm("r2");
        bank ^= page;
        address = bank << 2;
        address += bank;
        address <<= 8;
        offset = opposite_column << 3;
        address += offset;
        address += (u32)base;
        value = (u32)clamp4 << 8;
        low = 0x78;
        value |= low;
        *(u16 *)address = value;
        }
        }
    }
    }
    }
    {
    register s32 flag asm("r3") = sp4;
    asm volatile("" : "+r"(flag));
    if (flag == 0) {
        var_r6 += 1;
    } else {
        var_r6 -= 1;
    }
    }
    var_ip_2 += var_r9;
    if (var_ip_2 >= var_r8) {
        register s32 flag asm("r4") = sp0;
        asm volatile("" : "+r"(flag));
        if (flag == 0) {
            var_r7 += 1;
        } else {
            var_r7 -= 1;
        }
        {
        register s32 acc asm("r0") = var_ip_2;
        register s32 major asm("r1") = var_r8;
        asm volatile("" : "+r"(acc), "+r"(major));
        asm volatile(".syntax unified\n\tsubs %0, %0, %1\n\t.syntax divided"
                     : "+r"(acc) : "r"(major) : "cc");
        var_ip_2 = acc;
        }
    }
    {
    register s32 decrement asm("r3") = 1;
    register s32 test asm("r4");
    asm volatile("" : "+r"(decrement));
    asm volatile(".syntax unified\n\tnegs %0, %0\n\tadd %1, %0\n\t.syntax divided"
                 : "+r"(decrement), "+r"(var_sl_2) : : "cc");
    test = var_sl_2;
    asm volatile("" : "+r"(test));
    if (test != 0) {
        goto loop_21;
    }
    }
}
