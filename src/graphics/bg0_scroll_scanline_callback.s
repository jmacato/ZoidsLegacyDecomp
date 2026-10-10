.syntax unified
.arm
.section .text
.balign 4, 0
.global bg0_scroll_scanline_callback
.type bg0_scroll_scanline_callback, %function
bg0_scroll_scanline_callback:
    ldr r0, .Lvcount
    ldrh r0, [r0]
    cmp r0, #0xa0
    bxge lr
    lsl r2, r0, #1
    ldr r0, .Lbuffer_bank
    ldrb r0, [r0]
    lsl r0, r0, #6
    add r3, r0, r0, lsl #2
    add r1, r2, r3
    ldr r0, .Lscroll_buffer
    add r1, r0, r1
    ldr r2, .Lbg0_vertical_scroll
    ldrh r0, [r1]
    strh r0, [r2]
    bx lr
.Lvcount:
    .word 0x04000006
.Lbuffer_bank:
    .word 0x0203198D
.Lscroll_buffer:
    .word 0x0203198E
.Lbg0_vertical_scroll:
    .word 0x04000012
.size bg0_scroll_scanline_callback, . - bg0_scroll_scanline_callback
