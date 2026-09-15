#include "m2c_prelude.h"
extern void func_080C8F48();
extern u8 D_081081D4[];

void sub_080C99EC(int arg0) {
    func_080C8F48(D_081081D4, arg0, 0);
    *(u32 *)(arg0 + 0x8c) = 0;
}
