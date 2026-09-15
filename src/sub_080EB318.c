#include "m2c_prelude.h"

/*
 * This dispatch veneer branches through r3.
 * The words after the branch are data, so their positions must stay exact.
 */
__attribute__((naked)) void sub_080EB318(void) {
    asm(".syntax unified\n"
        "bx r3\n"
        ".short 0\n"
        ".word 0x086A33E4\n"
        ".word 0x03007FF0\n"
        ".word 0x68736D53\n"
        ".syntax divided");
}
