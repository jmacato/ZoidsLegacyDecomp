#include "m2c_prelude.h"
M2C_UNK func_0809258C();                            /* extern */
M2C_UNK func_080925A4(M2C_UNK *);                   /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
s32 func_08094374(M2C_UNK, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32);                         /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080981F0(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_08098248(M2C_UNK, s32, s32);           /* extern */
M2C_UNK func_08098BB4(s32);                         /* extern */
M2C_UNK func_0809AA64(M2C_UNK, u8, s32, s32);       /* extern */
M2C_UNK func_0809AB44(s32, s32, s32, s32, s32);     /* extern */
M2C_UNK func_080ACDA8(s32, s32, s32);               /* extern */
M2C_UNK func_080ECD28(s32 *, M2C_UNK, M2C_UNK);     /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

struct SaveBlock { s32 words[4]; };

void sub_080E39C8(void) {
    struct SaveBlock sp18;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 temp_r4_2;
    s32 flags_index;
    s32 flags_mask;
    s32 *flags_word;
    s32 var_r5;
    s32 var_r6;
    register s32 var_sl asm("r10");
    u16 temp_r1;
    u16 temp_r4;
    s32 temp_r4_3;
    u8 temp_r5;
    u8 var_r0;
    u8 var_r7;
    u8 *menu_base;
    u32 selected_base;
    u32 selected_addr;
    u32 enabled_base;
    u32 enabled_addr;
    u32 description_base;
    s32 *flags_base;
    volatile u16 *display;
    volatile u16 *loop_display;

    sp18 = *(struct SaveBlock *)0x08109334;
    display = (volatile u16 *)0x0300004C;
    *display = 0x1A40;
    func_08096FBC(3, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_08094330();
    func_08094484(0x08105DF4, 0x08105E00, 0, 0xA0, 0x98, 0x399, 0xF, 8, 0);
    func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8, 0x98, 0x343, 0xF, 8, 0);
    func_0809AB44(1, 3, 0x40, 0xD, 0x18);
    func_08098BB4(0x08006962);
    func_08096308(0xF, 0);
    var_r7 = 1;
    menu_base = (u8 *)0x087A3E40;
    var_r5 = menu_base[1];
    func_08098BB4(({
        register s32 *table asm("r1") = (s32 *)0x087F2ACC;
        asm volatile("" : "+r"(table));
        table[var_r5];
    }));
    func_080972C8();
    sp2C = 0;
    var_r5 = 1;
    loop_display = display;
    while (1) {
        if ((temp_r4 = *(u16 *)0x0300000C & 0x100) != 0) {
            if (sp2C != 0) {
                *loop_display &= 0xF7FF;
                func_080925A4(&sp18);
                sp2C = 0;
                func_08094554(sp30);
            }
        } else {
            if (sp2C == 0) {
                *loop_display |= 0x800;
                func_0809258C();
                sp2C = 1;
                sp30 = func_08094484(0x08105E58, 0x08105E64, 0, 0x30, 0x78, 0x3A0, 0xF, 8, (s32) temp_r4);
            }
            temp_r1 = *(u16 *)0x0300000E;
            if (0x20 & temp_r1) {
                if (var_r7 == 1) {
                    var_r7 = M2C_FIELD((void *)0x087A3E40, u8 *, 0);
                } else {
                    var_r0 = var_r7 - 1;
                    var_r7 = var_r0;
                }
                var_r5 = 1;
                func_08092E84(0x40);
            } else if (0x10 & temp_r1) {
                if (var_r7 == M2C_FIELD((void *)0x087A3E40, u8 *, 0)) {
                    var_r7 = 1;
                } else {
                    var_r0 = var_r7 + 1;
                    var_r7 = var_r0;
                }
                var_r5 = 1;
                func_08092E84(0x40);
            } else if (({
                s32 test = 2;
                test &= temp_r1;
                test;
            })) {
                func_08092E84(0x3F);
                func_08096308(0x10, 0);
                break;
            }
            if (var_r5 != 0) {
                selected_base = 0x087A3E40;
                asm volatile("" : "+g"(selected_base));
                selected_addr = var_r7 + selected_base;
                temp_r5 = *(u8 *)selected_addr;
                func_08098BB4(0x080069EC);
                flags_base = (s32 *)0x020217B4;
                asm volatile("" : "+r"(flags_base));
                flags_index = temp_r5 >> 5;
                flags_index <<= 2;
                flags_base += 9;
                flags_index += (s32)flags_base;
                flags_word = (s32 *)flags_index;
                flags_mask = 1 << (0x1F & temp_r5);
                if (*flags_word & flags_mask) {
                    var_r6 = 1;
                    enabled_base = 0x087EE170;
                    asm volatile("" : "+g"(enabled_base));
                    temp_r4_2 = temp_r5 * 4;
                    enabled_addr = temp_r4_2 + enabled_base;
                    func_080981F0(*(s32 *)enabled_addr, 0, 1, 0, 0);
                    func_080ACDA8((temp_r5 * 0x18) + 0x087B2524, 1, 2);
                    description_base = 0x087F2ACC;
                    asm volatile("" : "+g"(description_base));
                    temp_r4_2 += description_base;
                    func_08098BB4(*(s32 *)temp_r4_2);
                } else {
                    var_r6 = 0;
                    func_08098248(0x08109344, 0, 0);
                    func_080981F0(0x08109360, 0, 1, 0, 0);
                    func_08098BB4(*(s32 *)0x087F2ACC);
                }
                if (({
                    register s32 test asm("r1") = var_sl;
                    asm volatile("" : "+r"(test));
                    test;
                }) != 0) {
                    func_08094554(var_sl);
                    func_080ED17C(1);
                }
                if ((u32) temp_r5 <= 0x64U) {
                    temp_r4_3 = (temp_r5 * 2) + 1;
                    func_0809AA64(0x087ABC6C, temp_r4_3, 0, 0);
                    if (var_r6 == 0) {
                        sp28 = var_r6;
                        func_080ECD28(&sp28, 0x05000200, 0x01000008);
                    }
                    var_sl = func_08094374(0x087AC2BC, ({
                        register s32 arg1 asm("r1") = temp_r4_3;
                        asm volatile("" : "+r"(arg1));
                        arg1;
                    }), 0, 0xB4, 0x40, 0, 0, 0x48, 0);
                }
                func_080972C8();
                var_r5 = 0;
            }
        }
        func_080ED17C(1);
    }
    while ((func_0809669C() << 0x18) == 0) {
        func_080ED17C(1);
    }
}
