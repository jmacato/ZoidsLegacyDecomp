#include "m2c_prelude.h"
int func_80D22B4(int, int, int, int, int, int, int, int, int, int);

void sub_080E0D8C(void *arg0) {
    register int a1 asm("r2");
    *(u32 *)((s8 *)arg0 + 0x8C) = 0xFF;
    a1 = 0x087AA244;
    *(int *)((s8 *)arg0 + 12) = func_80D22B4(
        a1, 0x49, 0, 0xC0,
        0x40, 0, 0,
        (*(u32 *)arg0 & 2) ? 0x9288 : 0x1288,
        0,
        (*(u32 *)arg0 >> 1) & 1);
}
