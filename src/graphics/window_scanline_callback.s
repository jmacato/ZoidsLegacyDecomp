.syntax unified
.arm
.section .text
.balign 4, 0
.global window_scanline_callback
.type window_scanline_callback, %function
window_scanline_callback:
    ldr r0, .Lvcount
    ldrh r0, [r0]
    cmp r0, #0xa0
    bxge lr
    lsl r2, r0, #3
    ldr r0, .Lbuffer_bank
    ldrb r0, [r0]
    lsl r0, r0, #8
    add r3, r0, r0, lsl #2
    add r1, r2, r3
    ldr r0, .Lwindow_buffer
    add r1, r0, r1
    ldr r2, .Lwindow_bounds
    ldr r0, [r1]
    str r0, [r2]
    ldr r0, [r1, #4]
    str r0, [r2, #4]
    bx lr
.Lvcount:
    .word 0x04000006
.Lbuffer_bank:
    .word 0x03005F12
.Lwindow_buffer:
    .word 0x02000000
.Lwindow_bounds:
    .word 0x04000040
.size window_scanline_callback, . - window_scanline_callback
