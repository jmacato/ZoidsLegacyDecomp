#include "m2c_prelude.h"
extern void func_80C8F48(void *a, int b, int c);
extern u8 D_0810812C[];

void sub_080C9394(int arg0) {
    func_80C8F48(D_0810812C, arg0, 0);
    *(int *)(arg0 + 0x8c) = 0;
}
