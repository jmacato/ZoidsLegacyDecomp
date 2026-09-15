/* M4A byte-copy helper with the original hardware-control update. */
.syntax unified
.thumb
.section .text
.global m4a_copy_control
.thumb_func
m4a_copy_control:
    push {r4, r5, lr}
    adds r5, r0, #0
    adds r4, r1, #0
    adds r3, r2, #0
    ldr r2, [pc, #44]
    ldrh r0, [r2, #0]
    ldr r1, [pc, #44]
    ands r0, r1
    movs r1, #3
    orrs r0, r1
    strh r0, [r2, #0]
    subs r3, #1
    movs r0, #1
    negs r0, r0
    cmp r3, r0
    beq.n .Lm4a_copy_control_done
    adds r1, r0, #0
.Lm4a_copy_control_loop:
    ldrb r0, [r5, #0]
    strb r0, [r4, #0]
    adds r5, #1
    adds r4, #1
    subs r3, #1
    cmp r3, r1
    bne.n .Lm4a_copy_control_loop
.Lm4a_copy_control_done:
    pop {r4, r5}
    pop {r0}
    bx r0
    .balign 4, 0
    .word 0x04000204
    .word 0x0000FFFC
