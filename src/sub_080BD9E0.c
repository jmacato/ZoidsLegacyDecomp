#include "m2c_prelude.h"
__attribute__((naked)) void sub_080BD9E0(void) {
    asm("mov r3, r9");
    asm("str r0, [r3]");
    asm("bl func_80BE3D6");
}
