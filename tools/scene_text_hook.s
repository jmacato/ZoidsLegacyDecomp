.syntax unified
.cpu arm7tdmi
.thumb
.section .text
.global scene_text_hook
.thumb_func
scene_text_hook:
    push {r2, r3, r4}
    ldr r0, [r6]
    adds r0, #1
    ldr r2, =0x08800040
lookup:
    ldr r4, [r2]
    cmp r4, #0
    beq store
    cmp r4, r0
    beq found
    adds r2, #8
    b lookup
found:
    ldr r0, [r2, #4]
store:
    ldr r1, =0x0200A888
    str r0, [r1]
    pop {r2, r3, r4}
    ldr r0, =0x080A1515
    bx r0
.ltorg
.org 0x40, 0xff
