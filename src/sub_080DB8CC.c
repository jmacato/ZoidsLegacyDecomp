#include "m2c_prelude.h"
extern s32 D_03000054[];
extern int func_080D2450();
extern void func_080D2790();
extern void func_080D12A0();
extern void func_08095114();

void sub_080DB8CC(void *arg0) {
    u32 *p8C = (u32 *)((char *)arg0 + 0x8C);
    s32 var_r0_2;
    s32 a, b;
    switch (*p8C) {
    case 0:
        a = *(s32 *)((char *)arg0 + 4);
        b = *(s32 *)0x02034034 / 256 + 0x40;
        *(s32 *)((char *)arg0 + 0xC) = func_080D2450(arg0, 0, 0,
            (s16)(a + b),
            (s16)(*(s32 *)((char *)arg0 + 8) + D_03000054[1]),
            0x1400, 0, 0);
        var_r0_2 = 0;
        goto shared;
    case 1:
        if (*(u16 *)(*(s32 *)((char *)arg0 + 0xC) + 0x14) == 8) {
            func_080D12A0(0xA, 0);
            var_r0_2 = 1;
        shared:
            func_080D2790(var_r0_2);
            *p8C = *p8C + 1;
        }
        break;
    case 2:
        if (*(s32 *)((char *)arg0 + 0xC) == 0) {
            func_08095114(arg0);
        }
        break;
    }
}

void sub_080DB964(void *arg0) {
    *(s32 *)arg0 = *(s32 *)arg0 ^ 0x20000;
}

void sub_080DB970(void *arg0) {
    *(s32 *)((char *)arg0 + 0x8C) = 0;
}

void sub_080DB978(void *arg0) {
    s32 temp_r1;
    temp_r1 = *(s32 *)((char *)arg0 + 0x8C);
    if (temp_r1 == 0) {
        *(s32 *)0x02033F4C = func_080D2450(arg0, 0, 0,
            *(s16 *)((char *)arg0 + 4), *(s16 *)((char *)arg0 + 8),
            0x10, sub_080DB964, temp_r1);
        func_080D2790(0);
        *(s32 *)((char *)arg0 + 0x8C) = *(s32 *)((char *)arg0 + 0x8C) + 1;
        return;
    }
    if (*(*(s32 **)0x02033F4C) & 4) {
        *(s32 *)arg0 = *(s32 *)arg0 & ~1;
    }
}
