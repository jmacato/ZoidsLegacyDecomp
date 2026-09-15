/* M4A extended-command table dispatcher. */
.syntax unified
.thumb
.section .text
.global m4a_ext_dispatch
.thumb_func
m4a_ext_dispatch:
    push {lr}
    ldr r2, [r1, #64]
    ldrb r3, [r2, #0]
    adds r2, #1
    str r2, [r1, #64]
    ldr r2, [pc, #16]
    lsls r3, r3, #2
    adds r3, r3, r2
    ldr r2, [r3, #0]
    bl func_80ECD64
    pop {r0}
    bx r0
    .balign 4, 0
    .word 0x086A3418
