/* M4A pitch update for the matching sound object type. */
.syntax unified
.thumb
.section .text
.global m4a_set_pitch
.thumb_func
m4a_set_pitch:
    push {r4, lr}
    adds r2, r0, #0
    lsls r1, r1, #16
    lsrs r1, r1, #16
    ldr r3, [r2, #52]
    ldr r0, [pc, #24]
    cmp r3, r0
    bne.n .Lm4a_set_pitch_done
    strh r1, [r2, #30]
    ldrh r4, [r2, #28]
    adds r0, r1, #0
    muls r0, r4
    asrs r0, r0, #8
    strh r0, [r2, #32]
.Lm4a_set_pitch_done:
    pop {r4}
    pop {r0}
    bx r0
    .balign 4, 0
    .word 0x68736D53
