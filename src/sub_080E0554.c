#include "m2c_prelude.h"
s32 func_080ECD5C(s32);
extern s32 D_03000010;
void sub_080E0554(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = M2C_FIELD(arg0, s32 *, 4) + ((u32)(func_080ECD5C(D_03000010) * 0x41) >> 15) - 0x20;
    {
        s32 sine = func_080ECD5C(D_03000010);
        register s32 *dst asm("r3") = (s32 *)((u8 *)arg0 + 0x94);
        register s32 value asm("r2") = M2C_FIELD(arg0, s32 *, 8);
        register u32 scaled asm("r1");
        value -= 0x10;
        scaled = (u32)(sine * 0x21) >> 15;
        value += scaled;
        *dst = value;
    }
}
