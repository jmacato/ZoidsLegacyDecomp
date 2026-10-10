/* Preserves r1-r7 and rounds signed fixed-point products toward zero. */
.syntax unified
.arm
.section .text
.balign 4, 0
.global multiply_fixed12
.type multiply_fixed12, %function
multiply_fixed12:
    push {r1, r2, r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x20
    mov r7, sp
    str r0, [r7]
    str r1, [r7, #4]
    cmp r0, #0
    beq .Lreturn
    cmp r1, #0
    moveq r0, #0
    beq .Lreturn
    mov r2, #0
    mov r3, #0
    cmp r0, #0x80000000
    subhs r0, r3, r0
    addhs r2, r2, #1
    str r0, [r7, #8]
    cmp r1, #0x80000000
    subhs r1, r3, r1
    addhs r2, r2, #1
    str r1, [r7, #0xc]
    lsr r0, r0, #0xc
    str r0, [r7, #0x10]
    lsr r1, r1, #0xc
    str r1, [r7, #0x14]
    ldr r3, .Lfraction_mask
    ldr r0, [r7, #8]
    and r0, r3, r0
    str r0, [r7, #8]
    ldr r1, [r7, #0xc]
    and r1, r3, r1
    str r1, [r7, #0xc]
    ldr r0, [r7, #0x10]
    ldr r1, [r7, #0x14]
    mul r1, r0, r1
    lsl r1, r1, #0xc
    str r1, [r7, #0x18]
    ldr r1, [r7, #0xc]
    mul r0, r1, r0
    str r0, [r7, #0x1c]
    ldr r0, [r7, #0x14]
    ldr r1, [r7, #8]
    mul r3, r1, r0
    ldr r0, [r7, #0xc]
    mul r0, r1, r0
    lsr r1, r0, #0xc
    add r0, r1, r3
    ldr r1, [r7, #0x1c]
    add r0, r1, r0
    ldr r1, [r7, #0x18]
    add r0, r1, r0
    cmp r2, #1
    moveq r1, #0
    subeq r0, r1, r0
.Lreturn:
    add sp, sp, #0x20
    pop {r1, r2, r3, r4, r5, r6, r7}
    ldm sp!, {lr}
    bx lr
.Lfraction_mask:
    .word 0x00000FFF
.size multiply_fixed12, . - multiply_fixed12
