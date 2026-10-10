/* Runs in IRQ mode, then calls the selected handler in system mode. */
.syntax unified
.arm
.section .text
.balign 4, 0
.global rom_irq_handler
.type rom_irq_handler, %function
rom_irq_handler:
    mov r3, #0x4000000
    add r3, r3, #0x200
    ldr r2, [r3]
    ldrh r1, [r3, #8]
    mrs r0, spsr
    push {r0, r1, r2, r3, lr}
    mov r0, #1
    strh r0, [r3, #8]
    and r1, r2, r2, lsr #16
    mov ip, #0
    ands r0, r1, #1
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #2
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #4
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0xc0
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #8
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x10
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x20
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x100
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x200
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x400
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x800
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x1000
    bne .Ldispatch
    add ip, ip, #4
    ands r0, r1, #0x2000
    strbne r0, [r3, #-0x17c]
.Lcartridge_removed:
    bne .Lcartridge_removed
.Ldispatch:
    strh r0, [r3, #2]
    ldr r1, .Lirq_mask
    cmp r0, #2
    beq .Lset_irq_mask
    orr r1, r1, #0xc0
.Lset_irq_mask:
    and r1, r1, r2
    strh r1, [r3]
    mrs r3, cpsr
    bic r3, r3, #0xdf
    orr r3, r3, #0x1f
    msr cpsr_fc, r3
    ldr r1, .Lirq_callbacks
    add r1, r1, ip
    ldr r0, [r1]
    stmdb sp!, {lr}
    add lr, pc, #0
    bx r0
    ldm sp!, {lr}
    mrs r3, cpsr
    bic r3, r3, #0xdf
    orr r3, r3, #0x92
    msr cpsr_fc, r3
    pop {r0, r1, r2, r3, lr}
    strh r1, [r3, #8]
    ldrh r1, [r3]
    and r1, r1, #6
    bic r2, r2, #6
    orr r1, r1, r2
    strh r1, [r3]
    msr spsr_fc, r0
    bx lr
.Lirq_mask:
    .word 0x00002006
.Lirq_callbacks:
    .word 0x03000014
.size rom_irq_handler, . - rom_irq_handler
