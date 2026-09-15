#include "m2c_prelude.h"

s32 func_08092A90(s16);                             /* extern */
s32 func_080ECD24(s16, s16);                        /* extern */
s16 func_080ECD30(s32, u16);                        /* extern */
u16 func_080ECD3C(s32);                             /* extern */

s32 sub_080939E8(void *arg0, void *arg1, void *arg2) {
    register s32 temp_r1_2 asm("r8");
    register s32 temp_r4 asm("r4");
    s32 temp_r4_2;
    s32 temp_r4_3;
    register s32 temp_r5_3 asm("r5");
    register s32 temp_r6_2 asm("r6");
    s32 var_r0;
    s32 length_product;
    register s32 square1 asm("r0");
    register s32 square2 asm("r1");
    s32 wrap_sum;
    u16 temp_r1;
    s32 temp_arg0_y;
    register s32 temp_r5 asm("r5");
    register s32 temp_r5_2 asm("r5");
    register s32 temp_r6 asm("r6");
    u16 temp_r9;
    u16 temp_sl;
    s32 var_r0_2;
    register u32 temp_r1_3 asm("r1");
    u32 temp_r7;

    temp_r5 = M2C_FIELD(arg1, u16 *, 0);
    temp_r4 = temp_r5 - M2C_FIELD(arg0, u16 *, 0);
    temp_r1_2 = M2C_FIELD(arg0, u16 *, 2);
    __asm__ volatile ("" : "+r" (temp_r1_2));
    temp_r1 = M2C_FIELD(arg1, u16 *, 2);
    temp_arg0_y = temp_r1_2;
    temp_arg0_y -= temp_r1;
    temp_r1_2 = temp_arg0_y;
    __asm__ volatile ("" : "+r" (temp_r1_2));
    temp_r5_2 = temp_r5;
    temp_r5_2 -= M2C_FIELD(arg2, u16 *, 0);
    temp_r5_2 = (u16)temp_r5_2;
    temp_r6 = M2C_FIELD(arg2, u16 *, 2) - temp_r1;
    temp_r6 = (u16)temp_r6;
    temp_r4 = (s16)temp_r4;
    square1 = temp_r4 * temp_r4;
    square2 = temp_r1_2;
    __asm__ volatile ("" : "+r" (square2));
    square2 <<= 16;
    square2 >>= 16;
    temp_r1_2 = square2;
    square2 = temp_r1_2 * temp_r1_2;
    temp_sl = func_080ECD3C(square1 + square2);
    temp_r5_3 = (s16)temp_r5_2;
    square1 = temp_r5_3 * temp_r5_3;
    temp_r6_2 = (s16)temp_r6;
    square2 = temp_r6_2 * temp_r6_2;
    temp_r9 = func_080ECD3C(square1 + square2);
    temp_r4 <<= 0xE;
    temp_r4_2 = func_080ECD30(temp_r4, temp_sl);
    __asm__ volatile ("" : : "r" (temp_r4_2));
    temp_r1_2 <<= 0xE;
    temp_r7 = (u32) (func_080ECD24(temp_r4_2, func_080ECD30(temp_r1_2, temp_sl)) << 0x10) >> 0x18;
    temp_r5_3 <<= 0xE;
    temp_r4_3 = func_080ECD30(temp_r5_3, temp_r9);
    __asm__ volatile ("" : : "r" (temp_r4_3));
    temp_r6_2 <<= 0xE;
    temp_r1_3 = (u32) (func_080ECD24(temp_r4_3, func_080ECD30(temp_r6_2, temp_r9)) << 0x10) >> 0x18;
    if (temp_r7 < temp_r1_3) {
        var_r0_2 = temp_r1_3 - temp_r7;
    } else {
        register s32 wrap asm("r2") = 0x100;
        __asm__ volatile ("" : "+r" (wrap));
        var_r0_2 = wrap;
        __asm__ volatile ("" : "+r" (var_r0_2));
        wrap_sum = temp_r1_3;
        wrap_sum += var_r0_2;
        var_r0_2 = wrap_sum;
        var_r0_2 -= temp_r7;
    }
    var_r0_2 = (u16)var_r0_2;
    __asm__ volatile ("" : "+r" (var_r0_2));
    var_r0 = func_08092A90((s16) var_r0_2);
    length_product = temp_sl * temp_r9;
    var_r0 = (s16)var_r0;
    var_r0 *= length_product;
    if (var_r0 < 0) {
        var_r0 += 0xFF;
    }
    return var_r0 >> 8;
}
