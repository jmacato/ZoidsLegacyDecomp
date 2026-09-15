#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08094564(s32 *, s32);                  /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_080986B4(s32);                         /* extern */
s32 func_0809C434();                                /* extern */
M2C_UNK func_0809C45C();                            /* extern */
M2C_UNK func_0809C540(u8, u8);                      /* extern */
u8 func_080ECE30(s32, u8);                          /* extern */

extern s32 D_020216F8;
extern s32 D_020216FC;
extern s32 D_02021700;
extern u8 D_020216F5;
extern u8 D_02021704;
extern u8 D_02021706;
extern u8 D_02021708;
extern u16 *D_0202170C;
extern volatile u8 D_02021710;
extern s32 D_02021714[];
extern u8 D_0202176C;
extern u16 D_087A11D8[][0x83];

s32 sub_0809C7B0(void) {
    s32 *temp_r2;
    s32 *temp_r2_4;
    s32 temp_r1_5;
    s32 var_r0_6;
    s32 var_r0_7;
    register s32 var_r4 asm("r4");
    register u16 *var_r2 asm("r2");
    u16 *var_r3;
    u16 *var_r3_3;
    u16 temp_r0_6;
    u16 temp_r0_7;
    u16 temp_r1_3;
    register u16 temp_r2_2 asm("r2");
    u16 temp_r3;
    u16 var_r7;
    register u16 *temp_r1_2 asm("r1");
    u16 *temp_r1_6;
    u32 temp_r4;
    u16 *var_r2_2;
    u8 *var_r1;
    u8 temp_r0;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r0_4;
    u8 temp_r0_5;
    u8 temp_r0_8;
    u8 temp_r1;
    u8 temp_r1_4;
    u8 temp_r2_3;
    u8 temp_r8;
    u8 temp_r9;
    u8 temp_sl;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r0_3;
    u8 var_r0_4;
    s32 var_r0_5;
    u8 var_r3_2;
    s16 *temp_r1_7;

    temp_r9 = *(u8 *)0x02021708;
    temp_r8 = *(u8 *)0x020216F5;
    temp_sl = *(u8 *)0x020216F6;
    {
        s32 *items;
        u8 *selected;

        items = D_02021714;
        selected = &D_0202176C;
        func_08094564((s32 *)items[*selected], 2);
        *(u32 *)items[*selected] &= 0xFFDFFFFF;
    }
    if (0x40 & *(u16 *)0x03006034) {
        temp_r0 = *(u8 *)0x02021706;
        if (temp_r0 != 0) {
            *(u8 *)0x02021706 = temp_r0 - 1;
            func_08092E84(0x40);
        } else {
            temp_r0_2 = *(u8 *)0x02021708;
            if (temp_r0_2 != 0) {
                *(u8 *)0x02021708 = temp_r0_2 - 1;
                func_08094564(*(s32 **)0x020216FC, 1);
                func_08092E84(0x40);
            }
        }
    }
    if (0x80 & *(u16 *)0x03006034) {
        temp_r0_3 = *(u8 *)0x02021706;
        if ((u32) temp_r0_3 <= 3U) {
            *(u8 *)0x02021706 = (u8) (temp_r0_3 + 1);
            func_08092E84(0x40);
        } else {
            temp_r1 = *(u8 *)0x02021708;
            if ((s32) temp_r1 < (s32) (*(u8 *)0x02021709 - 5)) {
                *(u8 *)0x02021708 = (u8) (temp_r1 + 1);
                func_08094564(*(s32 **)0x02021700, 1);
                func_08092E84(0x40);
            }
        }
    }
    if (0x20 & *(u16 *)0x03006034) {
        u8 *position;
        s32 next;

        position = (u8 *)0x02021704;
        next = *position;
        if (next != 0) {
            next -= 1;
        } else {
            next = 0xC;
        }
        *position = next;
        func_08092E84(0x40);
    }
    if (0x10 & *(u16 *)0x03006034) {
        u8 *position;
        s32 next;

        position = (u8 *)0x02021704;
        next = *position;
        if ((u32) next <= 0xBU) {
            next += 1;
        } else {
            next = 0;
        }
        *position = next;
        func_08092E84(0x40);
    }
    temp_r2_2 = *(u16 *)0x0300000E;
    if (!(1 & temp_r2_2)) {
        goto no_confirm;
    }
    {
        u8 *position;

        position = &D_02021704;
        temp_r4 = (0xD * (D_02021706 + D_02021708)) + *position;
    }
    if ((func_0809C434() << 0x18) == 0) {
        if (temp_r4 < (u32)D_087A11D8[D_020216F5][0]) {
            var_r7 = D_087A11D8[D_020216F5][temp_r4 + 1];
        } else {
            var_r7 = 0x4081;
        }
    }
    if ((*(u8 *)0x020216F5 != 5) || (*(u8 *)0x020216F6 != 0xFF)) {
        if (var_r7 != 0x4081) {
            register u8 *selected asm("r1");

            var_r2_2 = *(u16 **)0x0202170C;
            var_r4 = 0;
            var_r3_2 = 0;
            selected = &D_0202176C;
            if (var_r4 < (s32)(*selected + 1)) {
                do {
                    if (*(u8 *)var_r2_2 == 0) {
                        var_r4 = 1;
                    }
                    if (var_r4 != 0) {
                        *var_r2_2 = 0x4081;
                    }
                    var_r2_2 += 1;
                    var_r3_2 += 1;
                } while ((s32)var_r3_2 < (s32)(*selected + 1));
            }
            *(var_r2_2 - 1) = var_r7;
            if (var_r4 == 0) {
                goto after_list_update;
            }
            goto block_49;
        } else {
            var_r2_2 = D_0202170C + D_0202176C;
            M2C_FIELD(var_r2_2, u16 *, 0) = var_r7;
            if (M2C_FIELD(var_r2_2, u8 *, 2) == 0) {
                temp_r1_6 = D_0202170C;
                if (var_r2_2 > temp_r1_6) {
                    var_r3_3 = var_r2_2 - 1;
                    temp_r0_7 = *var_r3_3;
                    if (temp_r0_7 == var_r7) {
                        register u32 copy_source asm("r0");

                        asm volatile("" : "=r"(copy_source));
                        var_r4 = copy_source;
loop_47:
                        var_r2_2 = var_r3_3;
                        if (var_r2_2 > temp_r1_6) {
                            var_r3_3 = var_r2_2 - 1;
                            if (*var_r3_3 == var_r4) {
                                goto loop_47;
                            }
                        }
                    }
                }
block_49:
                *var_r2_2 = 0;
            }
        }
after_list_update:
        func_080986B4(0);
        func_0809C45C();
        func_080972C8();
        D_0202176C = func_080ECE30(D_0202176C + 1, D_02021710);
    }
    func_08092E84(0x3E);
    goto block_88;
no_confirm:
    if (2 & temp_r2_2) {
        if ((func_0809C434() << 0x18) != 0) {
            *(u8 *)0x020216F6 = 0xFFU;
            D_02021704 = *(u8 *)0x02021705;
            D_02021706 = *(u8 *)0x02021707;
        } else {
            register u8 *selected asm("r1");

            {
                register u8 *selected_source asm("r0");

                selected_source = &D_0202176C;
                temp_r2_3 = *selected_source;
                selected = selected_source;
            }
            {
                s32 previous;

                if (temp_r2_3 != 0) {
                    previous = temp_r2_3 - 1;
                } else {
                    previous = D_02021710 - 1;
                }
                *selected = previous;
            }
            {
                u16 **list_address;
                register u32 selected_offset asm("r0");

                list_address = &D_0202170C;
                selected_offset = *selected;
                selected_offset <<= 1;
                temp_r1_2 = *list_address;
                var_r2 = (u16 *)((u8 *)temp_r1_2 + selected_offset);
                if (M2C_FIELD(var_r2, u8 *, 0) != 0) {
                register s32 marker_source asm("r0");

                marker_source = 0x4081;
                asm volatile("" : "+r"(marker_source));
                var_r4 = marker_source;
                *var_r2 = var_r4;
                if (M2C_FIELD(var_r2, u8 *, 2) == 0) {
                    asm volatile("" ::: "memory");
                    temp_r1_2 = *list_address;
                    if (var_r2 > temp_r1_2) {
                        var_r3 = var_r2 - 1;
                        temp_r0_6 = *var_r3;
                        if (temp_r0_6 == var_r4) {
                            var_r4 = temp_r0_6;
loop_65:
                            var_r2 = var_r3;
                            if (var_r2 > temp_r1_2) {
                                var_r3 = var_r2 - 1;
                                if (*var_r3 == var_r4) {
                                    goto loop_65;
                                }
                            }
                        }
                    }
                    *var_r2 = 0;
                }
                }
            }
            func_080986B4(0);
            func_0809C45C();
            func_080972C8();
        }
        func_08092E84(0x3F);
        goto block_88;
    }
    temp_r1_3 = *(u16 *)0x03006034;
    temp_r3 = 0x200 & temp_r1_3;
    if (temp_r3 != 0) {
        var_r1 = (s8 *)0x0202176C;
        var_r0_4 = *(u8 *)0x0202176C;
        if (var_r0_4 == 0) {
            var_r0_4 = *(u8 *)0x02021710;
        }
        var_r0_5 = var_r0_4 - 1;
        goto block_83;
    }
    {
        s32 right_test;

        right_test = 0x100;
        right_test &= temp_r1_3;
        if (right_test != 0) {
            temp_r1_4 = *(u8 *)0x0202176C;
            if ((s32) temp_r1_4 < (s32) (*(u8 *)0x02021710 - 1)) {
                *(u8 *)0x0202176C = (u8) (temp_r1_4 + 1);
            } else {
                *(u8 *)0x0202176C = (u8) temp_r3;
            }
            goto block_84;
        }
    }
    if (4 & temp_r2_2) {
        *(u8 *)0x020216F5 = func_080ECE30(*(u8 *)0x020216F5 + 1, 3U);
        if (temp_r8 == 5) {
            var_r1 = (u8 *)0x020216F6;
            var_r0_5 = 0xFF;
block_83:
            *var_r1 = var_r0_5;
        }
block_84:
        func_08092E84(0x40);
        goto block_88;
    }
    if (8 & temp_r2_2) {
        func_08092E84(0x3E);
        return 1;
    }
block_88:
    {
        u8 page;
        u8 *category;
        u8 *subtype;

        page = D_02021708;
        category = &D_020216F5;
        subtype = (u8 *)0x020216F6;
        if ((page != temp_r9) || (*category != temp_r8) || (*subtype != temp_sl)) {
            func_0809C540(*category, *subtype);
            func_080972C8();
        }
    }
    temp_r1_7 = (s16 *)D_020216F8;
    temp_r1_7[2] = (D_02021704 * 0x10) + 8;
    temp_r1_7[3] = (D_02021706 * 0x10) + 0x48;
    {
        u32 *window;
        register u32 flags asm("r0");

        if (D_02021708 != 0) {
            window = (u32 *)D_020216FC;
            flags = *window & 0xFFFDFFFF;
        } else {
            window = (u32 *)D_020216FC;
            flags = *window | 0x20000;
        }
        *window = flags;
    }
    {
        register u8 *count_address asm("r2");

        count_address = (u8 *)0x02021709;
        temp_r0_8 = *count_address;
    }
    {
        u32 *window;
        register u32 flags asm("r0");

        if (((u32) temp_r0_8 > 5U) && ((s32) D_02021708 < (s32) (temp_r0_8 - 5))) {
            window = (u32 *)D_02021700;
            flags = *window & 0xFFFDFFFF;
        } else {
            window = (u32 *)D_02021700;
            flags = *window | 0x20000;
        }
        *window = flags;
    }
    {
        s32 *items;
        u8 *selected;

        items = D_02021714;
        selected = &D_0202176C;
        func_08094564((s32 *)items[*selected], 1);
        *(u32 *)items[*selected] |= 0x200000;
    }
    return 0;
}
