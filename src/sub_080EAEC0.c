#include "m2c_prelude.h"

/*
 * This MP2K loop branches directly on the flags from subs.
 * Stock agbcc inserts cmp before bgt, which changes the ROM bytes.
 */
__attribute__((naked)) void sub_080EAEC0(void) {
    asm(".syntax unified\n"
        "mov ip, lr\n"
        "movs r1, #0x24\n"
        "ldr r2, [pc, #40]\n"
        "1:\n"
        "ldr r3, [r2]\n"
        "bl func_80EAEDA\n"
        "stmia r0!, {r3}\n"
        "adds r2, #4\n"
        "subs r1, #1\n"
        "bgt 1b\n"
        "bx ip\n"
        ".syntax divided");
}
