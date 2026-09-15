#include "m2c_prelude.h"

/*
 * This interrupt veneer changes the processor from Thumb state to ARM state.
 * The target address and instruction alignment must stay exact.
 */
__attribute__((naked)) void sub_080ED17C(void) {
    asm("bx pc\n"
        "nop\n"
        ".arm\n"
        "b 0x0800026C\n"
        ".thumb");
}
