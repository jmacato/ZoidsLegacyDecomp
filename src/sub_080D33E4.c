#include "m2c_prelude.h"
extern s32 D_03000010;
extern s32 func_080ECD5C(s32);

void sub_080D33E4(void *arg0) {
    register s32 temp_r0 asm("r0");
    register s32 temp_r1 asm("r1");
    register s32 temp_r2 asm("r2");
    register s32 temp_r3 asm("r3");

    *(s32 *)((u8 *)arg0 + 0x8C) = 0;
    temp_r0 = func_080ECD5C(D_03000010);
    temp_r2 = (s32)arg0;
    temp_r2 += 0x90;
    temp_r1 = temp_r0 << 6;
    temp_r1 += temp_r0;
    temp_r1 = (u32)temp_r1 >> 0xF;
    temp_r0 = *(s32 *)((u8 *)arg0 + 4) + temp_r1;
    temp_r0 -= 0x20;
    *(s32 *)temp_r2 = temp_r0;
    temp_r0 = func_080ECD5C(D_03000010);
    temp_r3 = (s32)arg0;
    temp_r3 += 0x94;
    temp_r2 = *(s32 *)((u8 *)arg0 + 8);
    temp_r2 -= 0x10;
    temp_r1 = temp_r0 << 5;
    temp_r1 += temp_r0;
    temp_r1 = (u32)temp_r1 >> 0xF;
    temp_r2 += temp_r1;
    *(s32 *)temp_r3 = temp_r2;
}
