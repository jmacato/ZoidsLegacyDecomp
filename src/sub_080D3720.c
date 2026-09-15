#include "m2c_prelude.h"
extern u32 D_03000010;
u32 func_080ECD5C();

void sub_080D3720(int arg) {
    u32 r;
    s32 t;
    s32 *p;
    *(s32 *)(arg + 0x8c) = 0;
    r = func_080ECD5C(D_03000010);
    p = (s32 *)(arg + 0x90);
    t = *(s32 *)(arg + 8) - 16;
    *p = t + ((r * 33) >> 15);
}
