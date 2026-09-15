#include "m2c_prelude.h"
__attribute__((naked)) void sub_080EAEF4(void) {
    asm(".syntax unified");
    asm("ldr r2, [r1, #0x40]");
    asm("adds r3, r2, #1");
    asm("str r3, [r1, #0x40]");
    asm("ldrb r3, [r2]");
    asm("b func_80EAEDA");
    asm(".syntax divided");
}
