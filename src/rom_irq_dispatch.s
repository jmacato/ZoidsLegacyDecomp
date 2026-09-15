/* ARM-mode interrupt dispatcher: pushes the interrupted context into the
 * handler's frame chain, walks the chain for a matching entry, and either
 * restores a saved frame or resets the stack. Hand-written assembly in the
 * original, so it is assembled directly rather than compiled. */
.syntax unified
.arm
.section .text
.balign 4, 0
.global rom_irq_dispatch
rom_irq_dispatch:
    ldr r3, [pc, #360]
    ldr r2, [pc, #360]
    str r2, [r3]
    ldr r3, [pc, #356]
    str lr, [r3]
    ldr r3, [pc, #352]
    str sp, [r3]
    mov r0, #1
    stmfd sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr, pc}
    mrs r0, SPSR
    stmfd sp!, {r0}
    ldr r3, [pc, #332]
    ldr r5, [pc, #332]
    ldr r2, [r3]
    ldr r1, [pc, #328]
    ldr r0, [r2, #8]
    cmp r0, r1
    beq .Lreset_stack
    mov r0, lr
    str r0, [r2, #8]
    ldmfd sp!, {r0}
    str r0, [r2, #12]
    ldmfd sp!, {r0}
    str r0, [r2, #16]
    strb r0, [r2, #1]
    ldmfd sp!, {r0}
    str r0, [r2, #20]
    ldmfd sp!, {r0}
    str r0, [r2, #24]
    ldmfd sp!, {r0}
    str r0, [r2, #28]
    ldmfd sp!, {r0}
    str r0, [r2, #32]
    ldmfd sp!, {r0}
    str r0, [r2, #36]
    ldmfd sp!, {r0}
    str r0, [r2, #40]
    ldmfd sp!, {r0}
    str r0, [r2, #44]
    ldmfd sp!, {r0}
    str r0, [r2, #48]
    ldmfd sp!, {r0}
    str r0, [r2, #52]
    ldmfd sp!, {r0}
    str r0, [r2, #56]
    ldmfd sp!, {r0}
    str r0, [r2, #60]
    ldmfd sp!, {r0}
    str r0, [r2, #64]
    ldmfd sp!, {r0}
    str r0, [r2, #68]
    ldmfd sp!, {r0}
    str r0, [r2, #72]
    str sp, [r2, #4]
    b .Lnext_entry
.Lreset_stack:
    add sp, sp, #64
.Lnext_entry:
    add r2, r2, #76
    str r2, [r3]
    ldrb r0, [r2]
    cmp r0, #12
    beq .Lrestore_root
    ldr lr, [r2, #8]
    cmp lr, r1
    beq .Lnext_entry
    ldrb r4, [r2, #1]
    subs r4, r4, #1
    strbne r4, [r2, #1]
    bne .Lnext_entry
    sub r0, r0, #1
    strb r0, [r5]
    ldr r0, [r2, #12]
    msr SPSR_fc, r0
    ldr r0, [r2, #16]
    ldr r1, [r2, #24]
    ldr r3, [r2, #28]
    ldr r4, [r2, #32]
    ldr r5, [r2, #36]
    ldr r6, [r2, #40]
    ldr r7, [r2, #44]
    ldr r8, [r2, #48]
    ldr r9, [r2, #52]
    ldr sl, [r2, #56]
    ldr fp, [r2, #60]
    ldr ip, [r2, #64]
    ldr sp, [r2, #4]
    ldr r2, [r2, #20]
    bx lr
.Lrestore_root:
    ldr r3, [pc, #40]
    ldr sp, [r3]
    ldr r3, [pc, #36]
    ldr lr, [r3]
    bx lr
