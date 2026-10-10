.syntax unified
.arm
.section .text
.balign 4, 0
.global perspective_scanline_callback
.type perspective_scanline_callback, %function
perspective_scanline_callback:
    ldr r0, .Lvcount
    ldrh r0, [r0]
    add r0, r0, #1
    cmp r0, #0xa0
    bxge lr
    lsl r2, r0, #4
    ldr r0, .Lbuffer_bank
    ldrb r0, [r0]
    lsl r0, r0, #9
    add r3, r0, r0, lsl #2
    add r1, r2, r3
    ldr r0, .Lbuffer_pointer
    ldr r0, [r0]
    add r1, r0, r1
    ldr r2, .Lbg2_affine
    ldr r0, [r1]
    str r0, [r2]
    ldr r0, [r1, #4]
    str r0, [r2, #4]
    ldr r0, [r1, #8]
    str r0, [r2, #8]
    ldr r0, [r1, #0xc]
    str r0, [r2, #0xc]
    bx lr
.Lvcount:
    .word 0x04000006
.Lbuffer_bank:
    .word 0x0300342C
.Lbuffer_pointer:
    .word 0x03003428
.Lbg2_affine:
    .word 0x04000020
.size perspective_scanline_callback, . - perspective_scanline_callback
