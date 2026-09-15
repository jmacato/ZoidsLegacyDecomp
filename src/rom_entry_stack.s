/* ARM-mode ROM entry stub: sets up the IRQ and system stacks, publishes the
 * IRQ handler address, then enters the C runtime. Hand-written assembly in the
 * original, so it is assembled directly rather than compiled. */
.syntax unified
.arm
.section .text
.balign 4, 0
.global rom_entry_stack
rom_entry_stack:
    mov r0, #0x12
    msr CPSR_fc, r0
    ldr sp, [pc, #48]
    mov r0, #0x1F
    msr CPSR_fc, r0
    ldr sp, [pc, #32]
    ldr r1, [pc, #20]
    add r0, pc, #32
    str r0, [r1]
    ldr r1, [pc, #12]
    mov lr, pc
    bx r1
