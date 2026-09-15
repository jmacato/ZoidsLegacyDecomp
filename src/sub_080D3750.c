#include "m2c_prelude.h"
void *func_80D2450(void *, int, int, int, int, int, int, int);
void func_80D2790(int);
void func_8095114(void *);

void sub_080D3750(void *arg0) {
    u32 *p8c;
    void *r;

    p8c = (u32 *)((s8 *)arg0 + 0x8C);
    if (*p8c == 0) {
        r = func_80D2450(arg0, 0, 0, (s16)(*(int *)((s8 *)arg0 + 4) - 16),
                         *(s16 *)((s8 *)arg0 + 0x90), 0x410, 0x080D2529, 1);
        *(void **)((s8 *)arg0 + 12) = r;
        *(int *)((s8 *)r + 40) = 16;
        func_80D2790(0);
        *p8c += 1;
    } else if (*(int *)((s8 *)arg0 + 12) == 0) {
        func_8095114(arg0);
    }
}

void sub_080D37B8(void *arg0) {
    *(u32 *)((s8 *)arg0 + 0x8C) = 0;
}
