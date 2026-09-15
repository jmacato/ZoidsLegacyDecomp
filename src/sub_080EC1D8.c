#include "m2c_prelude.h"

void sub_080EC1D8(void *arg0) {
    register u8 *base asm("r1");
    register s32 value asm("r0");
    register s32 left asm("r2");
    register s32 right asm("r3");
    register s32 normalized asm("r4");

    base = arg0;
    value = base[2];
    left = value << 24;
    normalized = (u32)left >> 24;
    right = base[3];
    value = right << 24;
    right = (u32)value >> 24;
    if ((u32)normalized >= (u32)right) {
        value = (u32)left >> 25;
        if ((u32)value >= (u32)right) {
            base[0x1B] = 0x0F;
            goto clamp_sum;
        }
    } else {
        value = (u32)value >> 25;
        if ((u32)value >= (u32)normalized) {
            base[0x1B] = 0xF0;
            goto clamp_sum;
        }
    }
    base[0x1B] = 0xFF;
    left = base[3];
    right = base[2];
    value = (u32)(left + right) >> 4;
    goto store_sum;

clamp_sum:
    left = base[3];
    right = base[2];
    value = (u32)(left + right) >> 4;
    base[0x0A] = value;
    if ((u32)value <= 0x0F) {
        goto finish_sum;
    }
    value = 0x0F;
store_sum:
    base[0x0A] = value;
finish_sum:
    left = base[6];
    asm volatile("" : "+r"(left));
    right = base[0x0A];
    value = left;
    value *= right;
    value += 0x0F;
    asm volatile("" : "+r"(value));
    value >>= 4;
    base[0x19] = value;
    value = base[0x1C];
    left = base[0x1B];
    value &= left;
    base[0x1B] = value;
}
