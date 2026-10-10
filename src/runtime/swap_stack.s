/* Accepts the new stack in r0 and returns the old stack in r0. */
.syntax unified
.arm
.section .text
.balign 4, 0
.global swap_stack
.type swap_stack, %function
swap_stack:
    stmdb sp!, {r0}
    stmdb sp!, {sp}
    ldm sp!, {r0}
    ldm sp!, {sp}
    add r0, r0, #4
    bx lr
.size swap_stack, . - swap_stack
