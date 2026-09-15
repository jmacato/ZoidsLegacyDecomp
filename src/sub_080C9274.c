#include "m2c_prelude.h"
extern void func_080C8F48(void *a, void *b, int c);
extern u8 D_08108124[];

void sub_080C9274(void *arg0) {
    func_080C8F48(D_08108124, arg0, 0);
    *(s32 *)((u8 *)arg0 + 0x8c) = 0;
}
