#include "m2c_prelude.h"

M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08097CEC(u8, s32, u16 *);              /* extern */
M2C_UNK func_080ECD28(s32 *, s32, s32);             /* extern */
M2C_UNK func_080ECD34(M2C_UNK, s32);                /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_0809B180(void) {
    struct {
        s32 word;
        u16 color;
    } locals;
    s32 temp_r0;
    s32 var_r0;
    s32 *result_ptr;
    u16 *var_r6;
    u16 var_r4_2;
    u16 var_r4_4;
    u32 var_r4_3;
    u32 var_r4_5;
    u32 var_r4_6;
    u8 *var_r4;
    u8 temp_r1;
    u32 var_r2;

    *(s16 *)0x0300004C = 0x1140;
    *(s16 *)0x04000008 = 4;
    {
        s32 *state = (s32 *)0x03000054;
        state[1] = 0;
        state[0] = 0;
    }
    temp_r1 = *(u8 *)0x02021694;
    if (temp_r1 == 0) {
        func_08096FBC(0, 1, 0, 0x3C0, 0x3C0, (s32) temp_r1, 0xE, (s32) temp_r1, 0x3E6, 0xF);
        func_080ECD28((s32 *)0x087A0F08, 0x050001C0, 8);
        locals.word = 0xE3C1E3C1;
        func_080ECD28(&locals.word, 0x06000000, 0x01000200);
        {
            register u32 index_seed asm("r2") = 0;
            asm volatile("" : "+r"(index_seed));
            var_r2 = index_seed;
        }
        do {
            temp_r0 = var_r2 * 0x1F;
            var_r4 = temp_r0 + 0x087A0F28;
            var_r6 = (var_r2 << 6) + 0x06000000;
            if (M2C_FIELD(temp_r0, u8 *, 0x087A0F28) != 0) {
                u16 *converted = &locals.color;
                do {
                    func_08097CEC(*var_r4, 0, converted);
                    *var_r6 = *converted;
                    var_r4 += 1;
                    var_r6 += 1;
                } while (*var_r4 != 0);
            }
            var_r2 = (u8) (var_r2 + 1);
        } while ((u32) var_r2 <= 0x13U);
        func_08096308(3, 0x10);
        while ((func_0809669C() << 0x18) == 0) {
            func_080ED17C(1);
        }
        var_r4_2 = 0;
        do {
            func_080ED17C(1);
            var_r4_2 += 1;
        } while ((u32) var_r4_2 <= 0xB3U);
        func_08096308(2, 0x10);
        while ((func_0809669C() << 0x18) == 0) {
            func_080ED17C(1);
        }
    }
    func_080ECD34(0x080F172C, 0x06004000);
    func_080ECD34(0x080F1D74, 0x05000000);
    func_080ECD34(0x080F1D9C, 0x06000000);
    func_08096308(1, 0x10);
    if (*(u8 *)0x02021694 == 0) {
        var_r4_3 = 0;
        while ((var_r4_3 <= 0xB3U) &&
               (((func_0809669C() << 0x18) == 0) || !(8 & *(u16 *)0x0300000E))) {
            func_080ED17C(1);
            var_r4_3 = (u32) (u16) (var_r4_3 + 1);
        }
    } else {
        var_r4_4 = 0;
        do {
            func_080ED17C(1);
            var_r4_4 += 1;
        } while ((u32) var_r4_4 <= 0x257U);
    }
    func_08096308(2, 0x10);
    while ((func_0809669C() << 0x18) == 0) {
        func_080ED17C(1);
    }
    if (*(u8 *)0x02021694 != 0) {
        goto block_50;
    }
    func_080ECD34(0x080F1F48, 0x06004000);
    func_080ECD34(0x080F2B0C, 0x05000000);
    func_080ECD34(0x080F2B34, 0x06000000);
    func_08096308(1, 0x10);
    var_r4_5 = 0;
    while ((var_r4_5 <= 0xB3U) &&
           (((func_0809669C() << 0x18) == 0) || !(8 & *(u16 *)0x0300000E))) {
        func_080ED17C(1);
        var_r4_5 = (u32) (u16) (var_r4_5 + 1);
    }
    func_08096308(2, 0x10);
    while ((func_0809669C() << 0x18) == 0) {
        func_080ED17C(1);
    }
    if (*(u8 *)0x02021694 == 0) {
        func_080ECD34(0x080F2D30, 0x06004000);
        func_080ECD34(0x080F355C, 0x05000000);
        func_080ECD34(0x080F3584, 0x06000000);
        func_08096308(1, 0x10);
        var_r4_6 = 0;
        while ((var_r4_6 <= 0xB3U) &&
               (((func_0809669C() << 0x18) == 0) || !(8 & *(u16 *)0x0300000E))) {
            func_080ED17C(1);
            var_r4_6 = (u32) (u16) (var_r4_6 + 1);
        }
        func_08096308(2, 0x10);
        while ((func_0809669C() << 0x18) == 0) {
            func_080ED17C(1);
        }
        if (*(u8 *)0x02021694 == 0) {
            result_ptr = (s32 *)0x02021690;
            var_r0 = 0x11;
        } else {
            goto block_50;
        }
    } else {
block_50:
        result_ptr = (s32 *)0x02021690;
        var_r0 = -1;
    }
    *result_ptr = var_r0;
}
