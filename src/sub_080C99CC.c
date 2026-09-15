#include "m2c_prelude.h"
extern void func_80C8F48();
extern u8 D_081081C8;

void sub_080C99CC(int arg) {
    func_80C8F48(&D_081081C8, arg, 0);
    *(u32 *)(arg + 0x8c) = 0;
}
