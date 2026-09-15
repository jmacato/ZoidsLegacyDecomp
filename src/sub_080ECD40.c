#include "m2c_prelude.h"

/*
 * This reset routine writes interrupt flags, sets the stack pointer, and calls BIOS services.
 * C cannot express this control transfer.
 */
__attribute__((naked)) void sub_080ECD40(void) {
    asm("ldr r3, [pc, #16]\n"
        "movs r2, #0\n"
        "strb r2, [r3]\n"
        "ldr r3, [pc, #16]\n"
        "movs r2, #0\n"
        "strb r2, [r3]\n"
        ".hword 0x3BFA\n"
        "mov sp, r3\n"
        "svc #1\n"
        "svc #0\n"
        ".word 0x04000208\n"
        ".word 0x03007FFA");
}
