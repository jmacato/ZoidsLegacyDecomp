#include "m2c_prelude.h"
extern s32 func_80D2450(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_80D2790(s32);
extern void func_8095114(void *);

void sub_080D5708(s32 *arg0) {
    s32 *field = &arg0[0x23];
    s32 v = *field;
    if (v == 0) {
        arg0[3] = func_80D2450(arg0, 0, 0,
            ((s16 *)arg0)[2], ((s16 *)arg0)[4], 0x400, v, 1);
        func_80D2790(0);
        *field += 1;
    } else if (arg0[3] == 0) {
        func_8095114(arg0);
    }
}

void sub_080D575C(s32 *p) {
    p[0x23] = 0;
}
