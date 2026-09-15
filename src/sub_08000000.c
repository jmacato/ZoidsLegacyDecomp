#include "m2c_prelude.h"

/*
 * The CPU runs this reset vector before the C run-time environment exists.
 * The exact ARM branch must stay in assembly.
 */
__attribute__((naked)) void sub_08000000(void) {
    asm(".arm\n"
        "b 0x080000C0\n"
        ".thumb");
}
