#include "m2c_prelude.h"

/*
 * This veneer changes the processor from Thumb state to ARM state.
 * A C function cannot preserve this mixed instruction layout.
 */
__attribute__((naked)) void sub_080EAA94(void) {
    asm(".syntax unified\n"
        "add r2, pc, #0\n"
        "bx r2\n"
        ".arm\n"
        ".word 0xE0832190\n"
        ".word 0xE2830000\n"
        ".word 0xE12FFF1E\n"
        ".thumb\n"
        ".syntax divided");
}
