#include "m2c_prelude.h"
extern void func_80C8F48(int, void *, int);

void sub_080C9B40(void *arg0) {
    func_80C8F48(0x08108220, arg0, 0);
    *(s32 *)((char *)arg0 + 0x8c) = 0;
}
