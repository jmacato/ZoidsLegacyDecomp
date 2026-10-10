.syntax unified
.arm
.section .text
.balign 4, 0
.global mosaic_scanline_callback
.type mosaic_scanline_callback, %function
mosaic_scanline_callback:
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
    ldr r0, .Lmosaic_buffer
    add r1, r0, r1
    ldr r2, .Lmosaic
    ldrh r0, [r1]
    strh r0, [r2]
    bx lr
.Lvcount:
    .word 0x04000006
.Lbuffer_bank:
    .word 0x02032B9E
.Lmosaic_buffer:
    .word 0x02032BA0
.Lmosaic:
    .word 0x0400004C
.size mosaic_scanline_callback, . - mosaic_scanline_callback
