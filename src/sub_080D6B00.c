#include "m2c_prelude.h"
extern int func_80ECD5C(int);
extern u32 D_03000010;

void sub_080D6B00(int arg) {
    *(s32 *)(arg + 0x8c) = 0;
    *(s32 *)(arg + 0x94) = ((u32)func_80ECD5C(D_03000010) * 33 >> 15) - 16;
}
