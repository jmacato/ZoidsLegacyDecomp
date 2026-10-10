.syntax unified
.arm
.section .text
.balign 4, 0
.global battle_mask_scanline_callback
.type battle_mask_scanline_callback, %function
battle_mask_scanline_callback:
    ldr r0, .Lvcount
    ldrh r0, [r0]
    cmp r0, #0x80
    bxge lr
    ldr r1, .Lbuffer_bank
    ldrb r1, [r1]
    lsl r1, r1, #7
    add r0, r0, r1
    ldr r1, .Lmask_buffer
    add r0, r0, r1
    ldrb r0, [r0]
    cmp r0, #0
    beq .Lmasked_line
    mov r0, #0x4000000
    ldrh r1, [r0]
    bic r1, r1, #0x8200
    strh r1, [r0]
    ldr r0, .Lblend_control
    mov r1, #0
    strh r1, [r0]
    ldr r0, .Lblend_control_shadow
    strh r1, [r0]
    bx lr
.Lmasked_line:
    mov r0, #0x4000000
    ldrh r1, [r0]
    orr r1, r1, #0x8200
    strh r1, [r0]
    ldr r0, .Lblend_control
    ldr r1, .Lmasked_blend_control
    strh r1, [r0]
    ldr r0, .Lblend_control_shadow_again
    strh r1, [r0]
    bx lr
.Lvcount:
    .word 0x04000006
.Lbuffer_bank:
    .word 0x02034868
.Lmask_buffer:
    .word 0x0203EE70
.Lblend_control:
    .word 0x04000050
.Lblend_control_shadow:
    .word 0x0300004E
.Lmasked_blend_control:
    .word 0x00000643
.Lblend_control_shadow_again:
    .word 0x0300004E
.size battle_mask_scanline_callback, . - battle_mask_scanline_callback
