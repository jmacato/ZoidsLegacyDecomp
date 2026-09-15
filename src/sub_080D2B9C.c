#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void func_080D2790(s32);
extern u32 func_080ECD5C(s32);
extern void *func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32);
extern void *func_080D2660(void *, s32, s32, s16, s32, s32, s32, s32, s32);
void sub_080D2B9C(void *arg0) {
    u32 *state = (u32 *)((u8 *)arg0 + 0x8C);
    switch (*state) {
    case 0: {
        register void *child asm("r0");
        child = func_080D2450(arg0, 0, 0, (s16)(*(s32 *)((u8 *)arg0 + 0x90) - 0x100), *(s16 *)((u8 *)arg0 + 0x94), 0x100, 0x080D2529, 1);
        *(void **)((u8 *)arg0 + 0xC) = child;
        *(s32 *)((u8 *)child + 0x28) = 0x10;
        func_080D2790(0);
        *state += 1;
        return;
    }
    case 1: {
        register void *child asm("r0");
        u32 r;
        if (*(void **)((u8 *)arg0 + 0xC) != 0) return;
        *(void **)((u8 *)arg0 + 0xC) = func_080D2450(arg0, 1, 0, *(s16 *)((u8 *)arg0 + 0x90), *(s16 *)((u8 *)arg0 + 0x94), 0, 0, 0);
        r = ((func_080ECD5C(*(s32 *)0x03000010) * 0x41) >> 15) - 0x20;
        child = func_080D2660(arg0, 2, 0, *(s16 *)((u8 *)arg0 + 0x90), *(s16 *)((u8 *)arg0 + 0x94), 0x100, r, 0x800, 0);
        *(void **)((u8 *)arg0 + 0x10) = child;
        *(s8 *)((u8 *)child + 0x11) = r;
        func_080D12A0(6, 0);
        func_080D2790(1);
        *state += 1;
        return;
    }
    case 2:
        if (!*(void **)((u8 *)arg0 + 0xC) && !*(void **)((u8 *)arg0 + 0x10)) func_08095114(arg0);
    }
}
