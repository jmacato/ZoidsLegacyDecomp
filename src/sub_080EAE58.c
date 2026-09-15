#include "m2c_prelude.h"

/*
 * This MP2K routine clears 64 bytes with four unrolled stmia instructions.
 * Stock agbcc does not combine C stores into this exact instruction sequence.
 */
__attribute__((naked)) void sub_080EAE58(void) {
    asm(".syntax unified\n"
        "mov ip, r4\n"
        "movs r1, #0\n"
        "movs r2, #0\n"
        "movs r3, #0\n"
        "movs r4, #0\n"
        "stmia r0!, {r1, r2, r3, r4}\n"
        "stmia r0!, {r1, r2, r3, r4}\n"
        "stmia r0!, {r1, r2, r3, r4}\n"
        "stmia r0!, {r1, r2, r3, r4}\n"
        "mov r4, ip\n"
        "bx lr\n"
        ".syntax divided");
}
