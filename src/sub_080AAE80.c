#include "m2c_prelude.h"

s32 func_8094564(void *, u16);
u16 func_80A9A54(void *);
u16 func_80ECD24(s16, s16);
u16 func_80ECD3C(s32);

#define VF(off, ty) (*(volatile ty *)((s8 *)arg0 + (off)))
#define VFP(off) ((void *) *(volatile s32 *)((s8 *)arg0 + (off)))

void sub_080AAE80(void *arg0) {
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r1_2;
    s32 temp_r2;
    u32 temp_r6;
    s32 temp_r7;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 temp_r0;
    u16 temp_r0_5;
    u16 temp_r1_3;
    u32 var_r0_5;
    u32 sh;
    void *temp_r1;
    void *temp_r2_2;
    void *temp_r2_3;
    void *temp_r2_4;
    void *temp_r4;

    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0) & ~8) | 0x10);
    temp_r6 = VF(0x40, u32);
    temp_r7 = VF(0x44, s32);
    var_r0 = temp_r6 - M2C_FIELD(arg0, u32 *, 8);
    if (var_r0 < 0) {
        var_r0 += 0xFF;
    }
    temp_r2 = var_r0 >> 8;
    M2C_FIELD(arg0, s32 *, 0x28) = temp_r2;
    var_r0_2 = temp_r7 - M2C_FIELD(arg0, s32 *, 0xC);
    if (var_r0_2 < 0) {
        var_r0_2 += 0xFF;
    }
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (var_r0_2 >> 8);
    temp_r1 = VFP(0x20);
    M2C_FIELD(temp_r1, u16 *, 8) = (u16) (M2C_FIELD(temp_r1, u16 *, 8) - temp_r2);
    temp_r2_2 = VFP(0x20);
    M2C_FIELD(temp_r2_2, u16 *, 0xA) = (u16) (M2C_FIELD(temp_r2_2, u16 *, 0xA) - VF(0x2C, s32));
    temp_r2_3 = VFP(0x24);
    if (temp_r2_3 != 0) {
        M2C_FIELD(temp_r2_3, u16 *, 8) = (u16) (M2C_FIELD(temp_r2_3, u16 *, 8) - VF(0x28, s32));
        temp_r2_4 = VFP(0x24);
        M2C_FIELD(temp_r2_4, u16 *, 0xA) = (u16) (M2C_FIELD(temp_r2_4, u16 *, 0xA) - VF(0x2C, s32));
    }
    {
        register u32 raw asm("r0");
        register u32 normalized asm("r1");
        register s32 bias asm("r2");
        register u32 sum asm("r0");
        register s32 quotient asm("r1");
        register s32 remainder asm("r0");

        raw = func_80ECD24((s16)(0 - VF(0x2C, s32)),
                           (s16)M2C_FIELD(arg0, s32 *, 0x28));
        raw <<= 16;
        normalized = raw >> 16;
        bias = 0x80;
        bias <<= 5;
        sum = normalized + bias;
        asm volatile("" : "+r"(sum));
        quotient = (s32)sum >> 0xD;
        remainder = quotient;
        asm volatile("" : "+r"(remainder));
        remainder >>= 3;
        remainder <<= 3;
        remainder = quotient - remainder;
        temp_r0 = remainder;
    }
    M2C_FIELD(arg0, s8 *, 0x1B) = temp_r0;
    M2C_FIELD(arg0, s8 *, 0x1A) = temp_r0;
    temp_r0_2 = VF(0x28, s32);
    if (temp_r0_2 >= 0) {
        var_r0_3 = 0;
    } else {
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) (0 - temp_r0_2);
        var_r0_3 = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x30) = var_r0_3;
    temp_r0_3 = VF(0x2C, s32);
    if (temp_r0_3 >= 0) {
        var_r0_4 = 0;
    } else {
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (0 - temp_r0_3);
        var_r0_4 = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x34) = var_r0_4;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    temp_r0_4 = M2C_FIELD(arg0, s32 *, 0x28);
    {
        register s32 product asm("r1");
        register s32 sum asm("r0");

        product = temp_r0_4;
        product *= temp_r0_4;
        asm volatile("" : "+r"(product));
        sum = product;
        asm volatile("" : "+r"(sum));
        temp_r0_4 = sum;
    }
    temp_r0_5 = func_80ECD3C(temp_r0_4 + (M2C_FIELD(arg0, s32 *, 0x2C) * M2C_FIELD(arg0, s32 *, 0x2C)));
    sh = (u32) temp_r0_5 << 0x10;
    temp_r1_3 = sh >> 0x10;
    M2C_FIELD(arg0, u32 *, 0x40) = (u32) temp_r1_3;
    if (M2C_FIELD(arg0, u8 *, 0x18) == 1) {
        var_r0_5 = temp_r1_3 * 2;
    } else {
        M2C_FIELD(arg0, u8 *, 0x18) = 3U;
        var_r0_5 = sh >> 0x11;
    }
    M2C_FIELD(arg0, u32 *, 0x40) = var_r0_5;
    temp_r4 = VFP(0x20);
    func_8094564(temp_r4, func_80A9A54(arg0));
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, u32 *, 8) = temp_r6;
    M2C_FIELD(arg0, s32 *, 0xC) = temp_r7;
}
