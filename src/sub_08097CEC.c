#include "m2c_prelude.h"

s32 func_080979A4(s32, u16 *);
void func_0809795C(u16);
s32 func_08097C24(s32, s32, s32);
s32 func_080ECF00(s32, s32);

void sub_08097CEC(s32 arg0, s32 arg1, u16 *out)
{
    u16 selected;
    register u16 *saved_out asm("r6") = out;
    register u16 *base asm("r5");
    register u32 normalized asm("r0");
    register u32 first asm("r4");
    u32 second;

    asm volatile("" : : "r"(saved_out));
    arg0 <<= 24;
    normalized = (u32)arg0 >> 24;
    asm volatile("" : : "r"(normalized));
    first = normalized;
    arg1 <<= 24;
    second = (u32)arg1 >> 24;
    if (first != 0x20 &&
        (u8)func_080979A4(1, &selected) != 0 &&
        (u8)func_08097C24(first, second,
            *(s32 *)0x02021654 + ((u32)selected << 5)) != 0) {
        u32 packed;
        u32 high;

        func_0809795C(selected);
        packed = *(s32 *)0x02021670;
        asm volatile("" : "+r"(packed));
        packed += selected;
        base = (u16 *)0x02021668;
        high = (u8)func_080ECF00(second, 3);
        high <<= 12;
        high += *base;
        packed |= high;
        *saved_out = packed;
    } else {
        *saved_out = (*(s32 *)0x02021664 + 1) | *(u16 *)0x02021668;
    }
}
