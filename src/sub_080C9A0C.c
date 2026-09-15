#include "m2c_prelude.h"
extern void func_80C8F48();
extern u8 D_081081E0;

void sub_080C9A0C(void *arg) {
    func_80C8F48(&D_081081E0, arg, 0);
    *(s32 *)((s32)arg + 0x8c) = 0;
}
