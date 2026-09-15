#include "m2c_prelude.h"
extern void func_08095114();
extern int func_080D2450();
extern void func_080D2790();

void sub_080DBA3C(void *arg0) {
    s32 temp_r1;
    temp_r1 = *(s32 *)((char *)arg0 + 0x8C);
    if (temp_r1 == 0) {
        *(s32 *)((char *)arg0 + 0xC) = func_080D2450(arg0, 0, 0,
            *(s16 *)((char *)arg0 + 4), *(s16 *)((char *)arg0 + 8),
            0x400, temp_r1, temp_r1);
        func_080D2790(0);
        *(s32 *)((char *)arg0 + 0x8C) = *(s32 *)((char *)arg0 + 0x8C) + 1;
        return;
    }
    if (*(s32 *)((char *)arg0 + 0xC) == 0) {
        func_08095114(arg0);
    }
}
