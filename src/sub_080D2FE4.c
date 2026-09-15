#include "m2c_prelude.h"
s32 func_080ECD5C(s32);

void sub_080D2FE4(void *arg0) {
    register s32 result asm("r0");
    register s32 *out asm("r3");
    register s32 value asm("r2");

    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    result = func_080ECD5C(*(s32 *)0x03000010);
    out = (s32 *)((u8 *)arg0 + 0x90);
    asm volatile("" : "+r"(out));
    value = M2C_FIELD(arg0, s32 *, 8) - 0x10;
    asm volatile("" : "+r"(value));
    *out = value + ((u32)(result * 0x21) >> 0xF);
}
