/* M4A/MP2K assembly routine from the game's sound driver. */
.syntax unified
.thumb
.section .text
.balign 4, 0
.global m4a_ply_endtie
.thumb_func
m4a_ply_endtie:
    push {r4, r5}
    ldr r2, [r1, #64]
    ldrb r3, [r2, #0]
    cmp r3, #128
    bcs.n .L80EB5AE
    strb r3, [r1, #5]
    adds r2, #1
    str r2, [r1, #64]
    b.n .L80EB5B0
.L80EB5AE:
    ldrb r3, [r1, #5]
.L80EB5B0:
    ldr r1, [r1, #32]
    cmp r1, #0
    beq.n .L80EB5D8
    movs r4, #131
    movs r5, #64
.L80EB5BA:
    ldrb r2, [r1, #0]
    tst r2, r4
    beq.n .L80EB5D2
    tst r2, r5
    bne.n .L80EB5D2
    ldrb r0, [r1, #17]
    cmp r0, r3
    bne.n .L80EB5D2
    movs r0, #64
    orrs r2, r0
    strb r2, [r1, #0]
    b.n .L80EB5D8
.L80EB5D2:
    ldr r1, [r1, #52]
    cmp r1, #0
    bne.n .L80EB5BA
.L80EB5D8:
    pop {r4, r5}
    bx lr
