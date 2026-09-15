/* M4A/MP2K assembly routine from the game's sound driver. */
.syntax unified
.thumb
.section .text
.balign 4, 0
.global m4a_track_stop
.thumb_func
m4a_track_stop:
    push {r4, r5, r6, lr}
    adds r5, r1, #0
    ldrb r1, [r5, #0]
    movs r0, #128
    tst r0, r1
    beq.n .L80EB360
    ldr r4, [r5, #32]
    cmp r4, #0
    beq.n .L80EB35E
    movs r6, #0
.L80EB33C:
    ldrb r0, [r4, #0]
    cmp r0, #0
    beq.n .L80EB356
    ldrb r0, [r4, #1]
    movs r3, #7
    ands r0, r3
    beq.n .L80EB354
    ldr r3, [pc, #28]
    ldr r3, [r3, #0]
    ldr r3, [r3, #44]
    bl func_80EB318
.L80EB354:
    strb r6, [r4, #0]
.L80EB356:
    str r6, [r4, #44]
    ldr r4, [r4, #52]
    cmp r4, #0
    bne.n .L80EB33C
.L80EB35E:
    str r4, [r5, #32]
.L80EB360:
    pop {r4, r5, r6}
    pop {r0}
    bx r0
    .balign 4, 0
    .word 0x03007ff0
