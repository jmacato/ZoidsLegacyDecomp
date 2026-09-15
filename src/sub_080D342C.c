#include "m2c_prelude.h"
extern void *func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32);
extern s32 func_080D2754(void *, s32, s32);
extern void func_080D2790(s32);
extern void func_08094554(void *);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);

void sub_080D342C(void *arg0) {
    u32 *p8c = (u32 *)((u8 *)arg0 + 0x8C);
    s32 var_r0;
    void *r;
    switch (*p8c) {
    case 0:
        {
        s32 t = *(s32 *)((u8 *)arg0 + 0x90) + 0xFFFFFF00;
        r = func_080D2450(arg0, 0, 0,
            t,
            *(s16 *)((u8 *)arg0 + 0x94),
            0x410, 0x080D2529, 1);
        }
        *(void **)((u8 *)arg0 + 0xC) = r;
        *(s32 *)((u8 *)r + 0x28) = 0x10;
        var_r0 = 0;
        goto block_7;
    case 1:
        {
        register s32 *p90 asm("r5");
        register s32 *p94 asm("r6");
        if ((func_080D2754(*(void **)((u8 *)arg0 + 0xC),
                *(p90 = (s32 *)((u8 *)arg0 + 0x90)) - 16,
                *(p94 = (s32 *)((u8 *)arg0 + 0x94))) << 24) != 0) {
            func_08094554(*(void **)((u8 *)arg0 + 0xC));
            *(void **)((u8 *)arg0 + 0xC) = func_080D2450(arg0, 1, 0,
                *(s16 *)p90, *(s16 *)p94, 0, 0, 0);
            func_080D12A0(6, 0);
            var_r0 = 1;
            goto block_7;
        }
        }
        return;
    block_7:
        func_080D2790(var_r0);
        *p8c += 1;
        return;
    case 2:
        if (*(void **)((u8 *)arg0 + 0xC) == 0) {
            func_08095114(arg0);
        }
        break;
    }
}
