#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void *func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32);
extern void func_080D2790(s32);

void sub_080D3870(void *arg0) {
    switch (*(u32 *)((u8 *)arg0 + 0x8C)) {
    case 0:
        *(void **)((u8 *)arg0 + 0xC) = func_080D2450(arg0, 0, 0, *(s16 *)((u8 *)arg0 + 4), *(s16 *)((u8 *)arg0 + 8), 0x400, 0, 0);
        func_080D2790(0);
        *(u32 *)((u8 *)arg0 + 0x8C) += 1;
        break;
    case 1:
        if (*(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0xC) + 0x14) == 2) {
            *(void **)((u8 *)arg0 + 0x10) = func_080D2450(arg0, 1, 0, *(s16 *)((u8 *)arg0 + 4), *(s16 *)((u8 *)arg0 + 8), 0x510, 0, 0);
            *(u32 *)((u8 *)arg0 + 0x8C) += 1;
        }
        break;
    case 2:
        if (*(s32 *)((u8 *)*(void **)((u8 *)arg0 + 0xC) + 0x14) == 4) {
            void *r1 = *(void **)((u8 *)arg0 + 0x10);
            *(s32 *)((u8 *)r1 + 0x24) = 0x080D2529;
            *(s32 *)((u8 *)r1 + 0x28) = 0x10;
            *(u32 *)((u8 *)arg0 + 0x8C) += 1;
        }
        break;
    case 3:
        if (*(void **)((u8 *)arg0 + 0xC) == 0 && *(void **)((u8 *)arg0 + 0x10) == 0) {
            func_08095114(arg0);
        }
        break;
    }
}
