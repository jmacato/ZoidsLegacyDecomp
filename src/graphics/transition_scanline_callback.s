.syntax unified
.arm
.section .text
.balign 4, 0
.global transition_scanline_callback
.type transition_scanline_callback, %function
transition_scanline_callback:
    ldr r0, .Lvcount
    ldrh r0, [r0]
    cmp r0, #0xa0
    bxge lr
    ldr r1, .Lbuffer_bank
    ldrb r2, [r1]
    lsl r1, r2, #7
    add r1, r1, r2, lsl #5
    add r0, r0, r1
    ldr r1, .Lmask_buffer
    add r0, r0, r1
    ldrb r0, [r0]
    cmp r0, #0
    beq .Lmasked_line
    ldr r0, .Lblend_control_shadow
    ldrh r1, [r0]
    ldr r0, .Lblend_y_shadow
    ldrh r2, [r0]
    ldr r0, .Lwindow_control_shadow
    ldr r3, [r0]
    ldr r0, .Lblend_control
    strh r1, [r0]
    strh r2, [r0, #4]
    str r3, [r0, #-8]
    bx lr
.Lmasked_line:
    mov r1, #0xff
    mov r2, #0x10
    ldr r3, .Lmasked_window_control
    ldr r0, .Lblend_control
    strh r1, [r0]
    strh r2, [r0, #4]
    str r3, [r0, #-8]
    bx lr
.Lvcount:
    .word 0x04000006
.Lbuffer_bank:
    .word 0x03005F7A
.Lmask_buffer:
    .word 0x02002740
.Lblend_control_shadow:
    .word 0x0300004E
.Lblend_y_shadow:
    .word 0x03000052
.Lwindow_control_shadow:
    .word 0x03005EF8
.Lblend_control:
    .word 0x04000050
.Lmasked_window_control:
    .word 0x3F3F3F3F
.size transition_scanline_callback, . - transition_scanline_callback
