/* M4A/MP2K assembly routine from the game's sound driver. */
.syntax unified
.thumb
.section .text
.balign 4, 0
.global m4a_ply_fine
.thumb_func
m4a_ply_fine:
    push {r4, r5, lr}
    adds r5, r1, #0
    ldr r4, [r5, #32]
    cmp r4, #0
    beq.n .L80EAEB4
.L80EAE9A:
    ldrb r1, [r4, #0]
    movs r0, #199
    tst r0, r1
    beq.n .L80EAEA8
    movs r0, #64
    orrs r1, r0
    strb r1, [r4, #0]
.L80EAEA8:
    adds r0, r4, #0
    bl func_80EAE70
    ldr r4, [r4, #52]
    cmp r4, #0
    bne.n .L80EAE9A
.L80EAEB4:
    movs r0, #0
    strb r0, [r5, #0]
    pop {r4, r5}
    pop {r0}
    bx r0
    .balign 4, 0
