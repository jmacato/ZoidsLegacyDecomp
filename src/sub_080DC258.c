#include "m2c_prelude.h"
extern u32 func_080ECD5C(s32);
extern s32 D_03000010;

void sub_080DC258(void *arg0) {
    register s32 *var_r2 asm("r2") = (s32 *)((s32)arg0 + 0x8C);
    register s32 *var_r1 asm("r1") = (s32 *)((s32)arg0 + 0x98);
    u32 temp_r0;
    *var_r1 = 0;
    *var_r2 = 0;
    temp_r0 = func_080ECD5C(D_03000010);
    var_r1 = (s32 *)((s32)arg0 + 0x90);
    temp_r0 = temp_r0 >> 0xE;
    *var_r1 = temp_r0;
    var_r1 += 6;
    var_r2 = (s32 *)0xC0;
    if (temp_r0 == 0) var_r2 = (s32 *)0x40;
    *var_r1 = (s32)var_r2;
}
