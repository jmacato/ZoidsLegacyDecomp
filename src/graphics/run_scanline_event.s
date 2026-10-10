.syntax unified
.arm
.section .text
.balign 4, 0
.global run_scanline_event
.type run_scanline_event, %function
run_scanline_event:
    stmdb sp!, {lr}
    ldr r2, .Lirq_flags
    ldrh r1, [r2]
    bic r1, r1, #4
    strh r1, [r2]
    ldr r1, .Levent_head
    ldr r1, [r1]
    cmn r1, #1
    beq .Lacknowledge
    ldr r2, [r1, #4]
    mov lr, pc
    bx r2
    ldr r2, .Levent_head_after_callback
    ldr r1, [r2]
    mov r0, r1
    ldr r1, [r1, #0xc]
    str r1, [r2]
    cmn r1, #1
    beq .Lacknowledge
    ldr r2, .Ldisplay_status
    ldrb r3, [r2]
    and r3, r3, #0xff
    ldrb r1, [r1]
    orr r3, r3, r1, lsl #8
    strh r3, [r2]
.Lacknowledge:
    ldr r2, .Lbios_irq_flags
    mov r1, #4
    strh r1, [r2]
    ldm sp!, {lr}
    bx lr
.Lirq_flags:
    .word 0x04000202
.Levent_head:
    .word 0x03000884
.Levent_head_after_callback:
    .word 0x03000884
.Ldisplay_status:
    .word 0x04000004
.Lbios_irq_flags:
    .word 0x03007FF8
.size run_scanline_event, . - run_scanline_event
