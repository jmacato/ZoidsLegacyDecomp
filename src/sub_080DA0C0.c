#include "m2c_prelude.h"
extern void func_080D2790(s32);
extern s32 func_080ECD5C(s32);

void sub_080DA0C0(void *arg0) {
    s32 temp_r0;
    s32 temp_r1;
    s32 temp_r2;
    s32 *temp_r3;

    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = (s32)((M2C_FIELD(arg0, s32 *, 4) + ((u32)(func_080ECD5C(*(s32 *)0x03000010) * 0x41) >> 0xF)) - 0x20);
    temp_r0 = func_080ECD5C(*(s32 *)0x03000010);
    temp_r3 = (s32 *)arg0 + 0x25;
    temp_r2 = M2C_FIELD(arg0, s32 *, 8) - 0x10;
    temp_r1 = (u32)(temp_r0 * 0x21) >> 0xF;
    *temp_r3 = temp_r2 + temp_r1;
    func_080D2790(0);
}
