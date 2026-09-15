/* M4A/MP2K assembly routine from the game's sound driver. */
.syntax unified
.thumb
.section .text
.balign 4, 0
.global m4a_ply_note
.thumb_func
m4a_ply_note:
    push {r4, r5, r6, r7, lr}
    mov r4, r8
    mov r5, r9
    mov r6, sl
    mov r7, fp
    push {r4, r5, r6, r7}
    sub sp, #24
    str r1, [sp, #0]
    adds r5, r2, #0
    ldr r1, [pc, #484]
    ldr r1, [r1, #0]
    str r1, [sp, #4]
    ldr r1, [pc, #480]
    adds r0, r0, r1
    ldrb r0, [r0, #0]
    strb r0, [r5, #4]
    ldr r3, [r5, #64]
    ldrb r0, [r3, #0]
    cmp r0, #128
    bcs.n .L80EB3E2
    strb r0, [r5, #5]
    adds r3, #1
    ldrb r0, [r3, #0]
    cmp r0, #128
    bcs.n .L80EB3E0
    strb r0, [r5, #6]
    adds r3, #1
    ldrb r0, [r3, #0]
    cmp r0, #128
    bcs.n .L80EB3E0
    ldrb r1, [r5, #4]
    adds r1, r1, r0
    strb r1, [r5, #4]
    adds r3, #1
.L80EB3E0:
    str r3, [r5, #64]
.L80EB3E2:
    movs r0, #0
    str r0, [sp, #20]
    adds r4, r5, #0
    adds r4, #36
    ldrb r2, [r4, #0]
    movs r0, #192
    tst r0, r2
    beq.n .L80EB434
    ldrb r3, [r5, #5]
    movs r0, #64
    tst r0, r2
    beq.n .L80EB402
    ldr r1, [r5, #44]
    adds r1, r1, r3
    ldrb r0, [r1, #0]
    b.n .L80EB404
.L80EB402:
    adds r0, r3, #0
.L80EB404:
    lsls r1, r0, #1
    adds r1, r1, r0
    lsls r1, r1, #2
    ldr r0, [r5, #40]
    adds r1, r1, r0
    mov r9, r1
    mov r6, r9
    ldrb r1, [r6, #0]
    movs r0, #192
    tst r0, r1
    beq.n .L80EB41C
    b.n .L80EB582
.L80EB41C:
    movs r0, #128
    tst r0, r2
    beq.n .L80EB438
    ldrb r1, [r6, #3]
    movs r0, #128
    tst r0, r1
    beq.n .L80EB430
    subs r1, #192
    lsls r1, r1, #1
    str r1, [sp, #20]
.L80EB430:
    ldrb r3, [r6, #1]
    b.n .L80EB438
.L80EB434:
    mov r9, r4
    ldrb r3, [r5, #5]
.L80EB438:
    str r3, [sp, #8]
    ldr r6, [sp, #0]
    ldrb r1, [r6, #9]
    ldrb r0, [r5, #29]
    adds r0, r0, r1
    cmp r0, #255
    bls.n .L80EB448
    movs r0, #255
.L80EB448:
    str r0, [sp, #16]
    mov r6, r9
    ldrb r0, [r6, #0]
    movs r6, #7
    ands r6, r0
    str r6, [sp, #12]
    beq.n .L80EB488
    ldr r0, [sp, #4]
    ldr r4, [r0, #28]
    cmp r4, #0
    bne.n .L80EB460
    b.n .L80EB582
.L80EB460:
    subs r6, #1
    lsls r0, r6, #6
    adds r4, r4, r0
    ldrb r1, [r4, #0]
    movs r0, #199
    tst r0, r1
    beq.n .L80EB4DC
    movs r0, #64
    tst r0, r1
    bne.n .L80EB4DC
    ldrb r1, [r4, #19]
    ldr r0, [sp, #16]
    cmp r1, r0
    bcc.n .L80EB4DC
    beq.n .L80EB480
    b.n .L80EB582
.L80EB480:
    ldr r0, [r4, #44]
    cmp r0, r5
    bcs.n .L80EB4DC
    b.n .L80EB582
.L80EB488:
    ldr r6, [sp, #16]
    adds r7, r5, #0
    movs r2, #0
    mov r8, r2
    ldr r4, [sp, #4]
    ldrb r3, [r4, #6]
    adds r4, #80
.L80EB496:
    ldrb r1, [r4, #0]
    movs r0, #199
    tst r0, r1
    beq.n .L80EB4DC
    movs r0, #64
    tst r0, r1
    beq.n .L80EB4B0
    cmp r2, #0
    bne.n .L80EB4B4
    adds r2, #1
    ldrb r6, [r4, #19]
    ldr r7, [r4, #44]
    b.n .L80EB4CE
.L80EB4B0:
    cmp r2, #0
    bne.n .L80EB4D0
.L80EB4B4:
    ldrb r0, [r4, #19]
    cmp r0, r6
    bcs.n .L80EB4C0
    adds r6, r0, #0
    ldr r7, [r4, #44]
    b.n .L80EB4CE
.L80EB4C0:
    bhi.n .L80EB4D0
    ldr r0, [r4, #44]
    cmp r0, r7
    bls.n .L80EB4CC
    adds r7, r0, #0
    b.n .L80EB4CE
.L80EB4CC:
    bcc.n .L80EB4D0
.L80EB4CE:
    mov r8, r4
.L80EB4D0:
    adds r4, #64
    subs r3, #1
    bgt.n .L80EB496
    mov r4, r8
    cmp r4, #0
    beq.n .L80EB582
.L80EB4DC:
    adds r0, r4, #0
    bl func_80EBAA8
    movs r1, #0
    str r1, [r4, #48]
    ldr r3, [r5, #32]
    str r3, [r4, #52]
    cmp r3, #0
    beq.n .L80EB4F0
    str r4, [r3, #48]
.L80EB4F0:
    str r4, [r5, #32]
    str r5, [r4, #44]
    ldrb r0, [r5, #27]
    strb r0, [r5, #28]
    cmp r0, r1
    beq.n .L80EB502
    adds r1, r5, #0
    bl func_80EB5DC
.L80EB502:
    ldr r0, [sp, #0]
    adds r1, r5, #0
    bl func_80EC02C
    ldr r0, [r5, #4]
    str r0, [r4, #16]
    ldr r0, [sp, #16]
    strb r0, [r4, #19]
    ldr r0, [sp, #8]
    strb r0, [r4, #8]
    ldr r0, [sp, #20]
    strb r0, [r4, #20]
    mov r6, r9
    ldrb r0, [r6, #0]
    strb r0, [r4, #1]
    ldr r7, [r6, #4]
    str r7, [r4, #36]
    ldr r0, [r6, #8]
    str r0, [r4, #4]
    ldrh r0, [r5, #30]
    strh r0, [r4, #12]
    bl func_80EB36C
    ldrb r1, [r4, #8]
    movs r0, #8
    ldrsb r0, [r5, r0]
    adds r3, r1, r0
    bpl.n .L80EB53C
    movs r3, #0
.L80EB53C:
    ldr r6, [sp, #12]
    cmp r6, #0
    beq.n .L80EB56A
    mov r6, r9
    ldrb r0, [r6, #2]
    strb r0, [r4, #30]
    ldrb r1, [r6, #3]
    movs r0, #128
    tst r0, r1
    bne.n .L80EB556
    movs r0, #112
    tst r0, r1
    bne.n .L80EB558
.L80EB556:
    movs r1, #8
.L80EB558:
    strb r1, [r4, #31]
    ldrb r2, [r5, #9]
    adds r1, r3, #0
    ldr r0, [sp, #12]
    ldr r3, [sp, #4]
    ldr r3, [r3, #48]
    bl func_80EB318
    b.n .L80EB574
.L80EB56A:
    ldrb r2, [r5, #9]
    adds r1, r3, #0
    adds r0, r7, #0
    bl func_80EB62C
.L80EB574:
    str r0, [r4, #32]
    movs r0, #128
    strb r0, [r4, #0]
    ldrb r1, [r5, #0]
    movs r0, #240
    ands r0, r1
    strb r0, [r5, #0]
.L80EB582:
    add sp, #24
    pop {r0, r1, r2, r3, r4, r5, r6, r7}
    mov r8, r0
    mov r9, r1
    mov sl, r2
    mov fp, r3
    pop {r0}
    bx r0
    .balign 4, 0
    .word 0x03007ff0
    .word 0x086a33e4
