/* M4A byte-stream word loader with the original mask sequence. */
.syntax unified
.thumb
.section .text
.global m4a_load_word
.thumb_func
m4a_load_word:
    push {r4, lr}
    ldr r2, [r1, #64]
    ldr r0, [pc, #48]
    ands r4, r0
    ldrb r0, [r2, #0]
    orrs r4, r0
    ldrb r0, [r2, #1]
    lsls r3, r0, #8
    ldr r0, [pc, #40]
    ands r4, r0
    orrs r4, r3
    ldrb r0, [r2, #2]
    lsls r3, r0, #16
    ldr r0, [pc, #36]
    ands r4, r0
    orrs r4, r3
    ldrb r0, [r2, #3]
    lsls r3, r0, #24
    ldr r0, [pc, #28]
    ands r4, r0
    orrs r4, r3
    str r4, [r1, #40]
    adds r2, #4
    str r2, [r1, #64]
    pop {r4}
    pop {r0}
    bx r0
    .balign 4, 0
    .word 0xFFFFFF00
    .word 0xFFFF00FF
    .word 0xFF00FFFF
    .word 0x00FFFFFF
