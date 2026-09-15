#include "m2c_prelude.h"

M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
void *func_08094374(s32, u8, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_08094564(void *, u16);                 /* extern */
M2C_UNK func_08095208(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080972C8();                            /* extern */
M2C_UNK func_08098BB4(s32);                         /* extern */
M2C_UNK func_0809A9C8(u8, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080E2DCC(s32, s32);                    /* extern */
M2C_UNK func_080E2EA4();                            /* extern */
M2C_UNK func_080E2F30();                            /* extern */
M2C_UNK func_080ECD28(s32 *, M2C_UNK, M2C_UNK);     /* extern */
M2C_UNK func_080ECD34(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080E364C(u8 *arg0) {
    s32 sp18;
    register s32 *temp_r9 asm("r9");
    s32 temp_r1_2;
    s32 temp_r4;
    s32 temp_r4_2;
    register s32 var_r0_3 asm("r0");
    s32 var_r4;
    s32 var_r6;
    s32 flags_index;
    s32 flags_mask;
    s32 *flags_base;
    s32 *flags_word;
    s32 *description_base;
    s32 *names_base;
    s32 preview_base;
    s32 animation_base;
    s32 temp_r1;
    u8 var_r0;
    u8 var_r5;
    s32 var_sl;
    s32 *var_r7;

    *(s16 *)0x0300004C = 0x1840;
    func_08096FBC(3, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_08094330();
    func_08094484(0x08105DF4, 0x08105E00, 0, 0xA0, 0x98, 0x399, 0xF, 8, 0);
    func_08094484(0x08105A20, 0x08105A2C, 0, 0xD8, 0x98, 0x343, 0xF, 8, 0);
    func_08098BB4(0x08006845);
    func_08096308(0xF, 0);
    var_sl = 1;
    var_r5 = arg0[1];
    description_base = (s32 *)0x087F2928;
    asm volatile("" : "+r"(description_base));
    temp_r4 = var_r5 * 4;
    func_08098BB4(*(s32 *)(temp_r4 + (s32)description_base));
    names_base = (s32 *)0x087A38C0;
    asm volatile("" : "+r"(names_base));
    func_080E2DCC(6, *(s32 *)(temp_r4 + (s32)names_base));
    func_080972C8();
    var_r7 = 0;
    func_080ECD34(0x0832BB4C, 0x06010200);
    temp_r9 = func_08094484(0x0832BB9C, 0x0832BBA8, 0, 0x60, 0x30, 0x10, 0xF, 0x108, 0);
    func_08094484(0x08359850, 0x0835985C, 0, 8, 8, 0x20, 2, 8, 0);
    var_r4 = 1;
    while (1) {
    temp_r1 = *(u16 *)0x0300000E;
    if (0x20 & temp_r1) {
        if (var_sl == 1) {
            var_sl = arg0[0];
        } else {
            var_r0 = var_sl - 1;
            var_sl = var_r0;
        }
        var_r4 = 1;
        func_08092E84(0x40);
    } else if (0x10 & temp_r1) {
        if (var_sl == arg0[0]) {
            var_sl = 1;
        } else {
            var_r0 = var_sl + 1;
            var_sl = var_r0;
        }
        var_r4 = 1;
        func_08092E84(0x40);
    } else if (({
        s32 test = 2;
        test &= temp_r1;
        test;
    })) {
        func_08092E84(0x3F);
        func_08096308(0x10, 0);
        break;
    } else {
        func_080E2EA4();
    }
    if (var_r4 != 0) {
            var_r5 = arg0[var_sl];
            func_08098BB4(0x080068C7);
            func_080E2F30();
            flags_base = (s32 *)0x020217B4;
            asm volatile("" : "+r"(flags_base));
            flags_index = (var_r5 >> 5) * 4;
            flags_base += 5;
            flags_index += (s32)flags_base;
            asm volatile("" : "+r"(flags_index));
            flags_word = (s32 *)flags_index;
            flags_mask = 1 << (0x1F & var_r5);
            if (*flags_word & flags_mask) {
                var_r6 = 1;
                description_base = (s32 *)0x087F2928;
                asm volatile("" : "+r"(description_base));
                temp_r4_2 = var_r5 * 4;
                func_08098BB4(*(s32 *)(temp_r4_2 + (s32)description_base));
                names_base = (s32 *)0x087A38C0;
                asm volatile("" : "+r"(names_base));
                func_080E2DCC(6, *(s32 *)(temp_r4_2 + (s32)names_base));
            } else {
                var_r6 = 0;
                func_08098BB4(*(s32 *)0x087F2928);
                func_080E2DCC(6, *(s32 *)0x087A38C0);
            }
            func_0809A9C8(var_r5, 0, 0, 0x20, 2, 0x02002880);
            if (var_r6 == 0) {
                func_08095208(0x087A3E20, 0x05000240, 0x20);
            }
            if (var_r7 != 0) {
                func_08094554(var_r7);
            }
            func_080ED17C(1);
            preview_base = 0x087AD208;
            if ((*(s32 *)((var_r5 * 0x10) + preview_base) != 0) && (var_r5 != 0xA) && (var_r5 != 0xB) && (var_r5 != 0x10) && (var_r5 != 0x11) && (var_r5 != 0x3F) && (var_r5 != 0x46) && (var_r5 != 0x47) && (var_r5 != 0x48)) {
                var_r7 = (s32 *)func_08094374(preview_base, var_r5, 0, 0x60, 0x20, 0, 0, 0x400020, 0);
                if (var_r6 == 0) {
                    sp18 = var_r6;
                    func_080ECD28(&sp18, 0x05000200, 0x01000008);
                }
                if ((var_r5 != 0x4B) && (var_r5 != 0x49)) {
                    var_r0_3 = *({
                        register s32 *bits asm("r1") = temp_r9;
                        bits;
                    }) & 0xFFFDFFFF;
                } else {
                    goto block_42;
                }
            } else {
                var_r7 = 0;
block_42:
                var_r0_3 = *({
                    register s32 *bits asm("r1") = temp_r9;
                    bits;
                }) | 0x20000;
            }
            *({
                register s32 *bits asm("r2") = temp_r9;
                bits;
            }) = var_r0_3;
            func_080972C8();
            var_r4 = 0;
        }
        if (M2C_FIELD(var_r7, s32 *, 0) & 4) {
            animation_base = 0x087AD208;
            asm volatile("" : "+r"(animation_base));
            temp_r1_2 = *(s32 *)((var_r5 * 0x10) + animation_base);
            if ((temp_r1_2 == 0x08279A64) || (temp_r1_2 == 0x0827A0C4)) {
                func_08094564(var_r7, (u16) ((M2C_FIELD(var_r7, u16 *, 0x12) + 1) % 16));
            } else if (temp_r1_2 == 0x08279EE4) {
                func_08094564(var_r7, (u16) ((M2C_FIELD(var_r7, u16 *, 0x12) + 1) % 8));
            }
        }
        func_080ED17C(1);
    }
    while ((func_0809669C() << 0x18) == 0) {
        func_080ED17C(1);
    }
    func_080E2F30();
}
