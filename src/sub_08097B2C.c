#include "m2c_prelude.h"

s32 func_080979A4(s32, u16 *);
void func_0809795C(u16);
s32 func_08097A2C(s32, s32, s32, s32);
s32 func_080ECF00(s32, s32);

void sub_08097B2C(s32 arg0, s32 arg1, u16 *out)
{
    u16 selected[2];
    u16 *saved_out = out;
    register u32 normalized asm("r0");
    register u32 first asm("r4");
    register u32 second asm("r8");

    asm volatile("" : : "r"(saved_out));
    arg0 <<= 16;
    normalized = (u32)arg0 >> 16;
    asm volatile("" : : "r"(normalized));
    first = normalized;
    arg1 <<= 24;
    second = (u32)arg1 >> 24;
    if (first != 0x8140 &&
        (u8)func_080979A4(2, selected) != 0 &&
        (u8)func_08097A2C(first, second,
            *(s32 *)0x02021654 + ((u32)selected[0] << 5),
            *(s32 *)0x02021654 + ((u32)selected[1] << 5)) != 0) {
        register s32 *packed_base asm("r6");
        register u16 *field_base asm("r5");
        register u32 packed asm("r4");
        register u32 packed2 asm("r2");
        register u32 high asm("r0");
        register u32 high_with_base asm("r1");

        func_0809795C(selected[0]);
        func_0809795C(selected[1]);
        packed_base = (s32 *)0x02021670;
        packed = *packed_base;
        packed += selected[0];
        field_base = (u16 *)0x02021668;
        high = (u8)func_080ECF00(second, 3);
        high <<= 12;
        high_with_base = *field_base;
        high_with_base += high;
        packed |= high_with_base;
        saved_out[0] = packed;

        packed2 = *packed_base;
        packed2 += selected[1];
        high_with_base = *field_base;
        high_with_base += high;
        packed2 |= high_with_base;
        saved_out[1] = packed2;
    } else {
        register s32 *fallback_base asm("r3") = (s32 *)0x02021664;
        register u16 *field_base asm("r2");
        register u32 packed asm("r0");
        register u32 field asm("r1");

        packed = *fallback_base;
        packed += 1;
        field_base = (u16 *)0x02021668;
        field = *field_base;
        packed |= field;
        saved_out[0] = packed;
        packed = *fallback_base;
        packed += 1;
        field = *field_base;
        packed |= field;
        saved_out[1] = packed;
    }
}
