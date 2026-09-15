#include "m2c_prelude.h"

/*
 * The sub_080EAEDA symbol enters this owner after the first instruction.
 * Stock agbcc inserts cmp instructions after both shifts.
 * The extra instructions change the ROM bytes.
 */
void sub_080EAED8(void) {
    asm volatile(
        "ldrb r3, [r2, #0]\n\t"
        "push {r0}\n\t"
        "lsr r0, r2, #25\n\t"
        "bne 1f\n\t"
        "ldr r0, =0x086A3170\n\t"
        "cmp r2, r0\n\t"
        "bcc 2f\n\t"
        "lsr r0, r2, #14\n\t"
        "beq 1f\n\t"
        "2:\n\t"
        "mov r3, #0\n\t"
        "1:\n\t"
        "pop {r0}"
        :
        :
        : "r0", "r3", "cc", "memory");
}
