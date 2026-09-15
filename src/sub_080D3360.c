#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void *func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32);
extern void func_080D2790(s32);

void sub_080D3360(void *arg0) {
    s32 temp_r5;
    void *temp_r0;
    temp_r5 = *(s32 *)((u8 *)arg0 + 0x8C);
    if (temp_r5 == 0) {
        *(void **)((u8 *)arg0 + 0xC) = func_080D2450(arg0, 0, 0, *(s16 *)((u8 *)arg0 + 4), *(s16 *)((u8 *)arg0 + 8), 0x400, temp_r5, temp_r5);
        temp_r0 = func_080D2450(arg0, 1, 0, *(s16 *)((u8 *)arg0 + 4), *(s16 *)((u8 *)arg0 + 8), 0x510, 0x080D2529, temp_r5);
        *(void **)((u8 *)arg0 + 0x10) = temp_r0;
        *(s32 *)((u8 *)temp_r0 + 0x28) = 0x10;
        func_080D2790(0);
        *(s32 *)((u8 *)arg0 + 0x8C) += 1;
        return;
    }
    if (*(void **)((u8 *)arg0 + 0xC) == 0 && *(void **)((u8 *)arg0 + 0x10) == 0) {
        func_08095114(arg0);
    }
}
