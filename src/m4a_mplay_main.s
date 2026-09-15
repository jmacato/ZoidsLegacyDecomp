/* M4A/MP2K assembly routine from the game's sound driver. */
.syntax unified
.thumb
.section .text
.balign 2, 0
.global m4a_mplay_main
.thumb_func
m4a_mplay_main:
    push {r0, lr}
    ldr r3, [r0, #56]
    cmp r3, #0
    beq.n .L80EB0DC
    ldr r0, [r0, #60]
    bl .L80EB318
.L80EB0DC:
    pop {r0}
    push {r4, r5, r6, r7}
    mov r4, r8
    mov r5, r9
    mov r6, sl
    mov r7, fp
    push {r4, r5, r6, r7}
    adds r7, r0, #0
    ldr r0, [r7, #4]
    cmp r0, #0
    bge.n .L80EB0F4
    b.n .L80EB308
.L80EB0F4:
    ldr r0, [pc, #552]
    ldr r0, [r0, #0]
    mov r8, r0
    adds r0, r7, #0
    bl func_80EBF64
    ldr r0, [r7, #4]
    cmp r0, #0
    bge.n .L80EB108
    b.n .L80EB308
.L80EB108:
    ldrh r0, [r7, #34]
    ldrh r1, [r7, #32]
    adds r0, r0, r1
    b.n .L80EB258
.L80EB110:
    ldrb r6, [r7, #8]
    ldr r5, [r7, #44]
    movs r3, #1
    movs r4, #0
.L80EB118:
    ldrb r0, [r5, #0]
    movs r1, #128
    tst r1, r0
    bne.n .L80EB122
    b.n .L80EB234
.L80EB122:
    mov sl, r3
    orrs r4, r3
    mov fp, r4
    ldr r4, [r5, #32]
    cmp r4, #0
    beq.n .L80EB156
.L80EB12E:
    ldrb r1, [r4, #0]
    movs r0, #199
    tst r0, r1
    beq.n .L80EB14A
    ldrb r0, [r4, #16]
    cmp r0, #0
    beq.n .L80EB150
    subs r0, #1
    strb r0, [r4, #16]
    bne.n .L80EB150
    movs r0, #64
    orrs r1, r0
    strb r1, [r4, #0]
    b.n .L80EB150
.L80EB14A:
    adds r0, r4, #0
    bl func_80EBAA8
.L80EB150:
    ldr r4, [r4, #52]
    cmp r4, #0
    bne.n .L80EB12E
.L80EB156:
    ldrb r3, [r5, #0]
    movs r0, #64
    tst r0, r3
    beq.n .L80EB1D4
    adds r0, r5, #0
    bl func_80EBABC
    movs r0, #128
    strb r0, [r5, #0]
    movs r0, #2
    strb r0, [r5, #15]
    movs r0, #64
    strb r0, [r5, #19]
    movs r0, #22
    strb r0, [r5, #25]
    movs r0, #1
    adds r1, r5, #6
    strb r0, [r1, #30]
    b.n .L80EB1D4
.L80EB17C:
    ldr r2, [r5, #64]
    ldrb r1, [r2, #0]
    cmp r1, #128
    bcs.n .L80EB188
    ldrb r1, [r5, #7]
    b.n .L80EB192
.L80EB188:
    adds r2, #1
    str r2, [r5, #64]
    cmp r1, #189
    bcc.n .L80EB192
    strb r1, [r5, #7]
.L80EB192:
    cmp r1, #207
    bcc.n .L80EB1A8
    mov r0, r8
    ldr r3, [r0, #56]
    adds r0, r1, #0
    subs r0, #207
    adds r1, r7, #0
    adds r2, r5, #0
    bl .L80EB318
    b.n .L80EB1D4
.L80EB1A8:
    cmp r1, #176
    bls.n .L80EB1CA
    adds r0, r1, #0
    subs r0, #177
    strb r0, [r7, #10]
    mov r3, r8
    ldr r3, [r3, #52]
    lsls r0, r0, #2
    ldr r3, [r3, r0]
    adds r0, r7, #0
    adds r1, r5, #0
    bl .L80EB318
    ldrb r0, [r5, #0]
    cmp r0, #0
    beq.n .L80EB230
    b.n .L80EB1D4
.L80EB1CA:
    ldr r0, [pc, #336]
    subs r1, #128
    adds r1, r1, r0
    ldrb r0, [r1, #0]
    strb r0, [r5, #1]
.L80EB1D4:
    ldrb r0, [r5, #1]
    cmp r0, #0
    beq.n .L80EB17C
    subs r0, #1
    strb r0, [r5, #1]
    ldrb r1, [r5, #25]
    cmp r1, #0
    beq.n .L80EB230
    ldrb r0, [r5, #23]
    cmp r0, #0
    beq.n .L80EB230
    ldrb r0, [r5, #28]
    cmp r0, #0
    beq.n .L80EB1F6
    subs r0, #1
    strb r0, [r5, #28]
    b.n .L80EB230
.L80EB1F6:
    ldrb r0, [r5, #26]
    adds r0, r0, r1
    strb r0, [r5, #26]
    adds r1, r0, #0
    subs r0, #64
    lsls r0, r0, #24
    bpl.n .L80EB20A
    lsls r2, r1, #24
    asrs r2, r2, #24
    b.n .L80EB20E
.L80EB20A:
    movs r0, #128
    subs r2, r0, r1
.L80EB20E:
    ldrb r0, [r5, #23]
    muls r0, r2
    asrs r2, r0, #6
    ldrb r0, [r5, #22]
    eors r0, r2
    lsls r0, r0, #24
    beq.n .L80EB230
    strb r2, [r5, #22]
    ldrb r0, [r5, #0]
    ldrb r1, [r5, #24]
    cmp r1, #0
    bne.n .L80EB22A
    movs r1, #12
    b.n .L80EB22C
.L80EB22A:
    movs r1, #3
.L80EB22C:
    orrs r0, r1
    strb r0, [r5, #0]
.L80EB230:
    mov r3, sl
    mov r4, fp
.L80EB234:
    subs r6, #1
    ble.n .L80EB240
    movs r0, #80
    adds r5, r5, r0
    lsls r3, r3, #1
    b.n .L80EB118
.L80EB240:
    ldr r0, [r7, #12]
    adds r0, #1
    str r0, [r7, #12]
    cmp r4, #0
    bne.n .L80EB252
    movs r0, #128
    lsls r0, r0, #24
    str r0, [r7, #4]
    b.n .L80EB308
.L80EB252:
    str r4, [r7, #4]
    ldrh r0, [r7, #34]
    subs r0, #150
.L80EB258:
    strh r0, [r7, #34]
    cmp r0, #150
    bcc.n .L80EB260
    b.n .L80EB110
.L80EB260:
    ldrb r2, [r7, #8]
    ldr r5, [r7, #44]
.L80EB264:
    ldrb r0, [r5, #0]
    movs r1, #128
    tst r1, r0
    beq.n .L80EB2FE
    movs r1, #15
    tst r1, r0
    beq.n .L80EB2FE
    mov r9, r2
    adds r0, r7, #0
    adds r1, r5, #0
    bl func_80EC02C
    ldr r4, [r5, #32]
    cmp r4, #0
    beq.n .L80EB2F4
.L80EB282:
    ldrb r1, [r4, #0]
    movs r0, #199
    tst r0, r1
    bne.n .L80EB292
    adds r0, r4, #0
    bl func_80EBAA8
    b.n .L80EB2EE
.L80EB292:
    ldrb r0, [r4, #1]
    movs r6, #7
    ands r6, r0
    ldrb r3, [r5, #0]
    movs r0, #3
    tst r0, r3
    beq.n .L80EB2B0
    bl func_80EB36C
    cmp r6, #0
    beq.n .L80EB2B0
    ldrb r0, [r4, #29]
    movs r1, #1
    orrs r0, r1
    strb r0, [r4, #29]
.L80EB2B0:
    ldrb r3, [r5, #0]
    movs r0, #12
    tst r0, r3
    beq.n .L80EB2EE
    ldrb r1, [r4, #8]
    movs r0, #8
    ldrsb r0, [r5, r0]
    adds r2, r1, r0
    bpl.n .L80EB2C4
    movs r2, #0
.L80EB2C4:
    cmp r6, #0
    beq.n .L80EB2E2
    mov r0, r8
    ldr r3, [r0, #48]
    adds r1, r2, #0
    ldrb r2, [r5, #9]
    adds r0, r6, #0
    bl .L80EB318
    str r0, [r4, #32]
    ldrb r0, [r4, #29]
    movs r1, #2
    orrs r0, r1
    strb r0, [r4, #29]
    b.n .L80EB2EE
.L80EB2E2:
    adds r1, r2, #0
    ldrb r2, [r5, #9]
    ldr r0, [r4, #36]
    bl func_80EB62C
    str r0, [r4, #32]
.L80EB2EE:
    ldr r4, [r4, #52]
    cmp r4, #0
    bne.n .L80EB282
.L80EB2F4:
    ldrb r0, [r5, #0]
    movs r1, #240
    ands r0, r1
    strb r0, [r5, #0]
    mov r2, r9
.L80EB2FE:
    subs r2, #1
    ble.n .L80EB308
    movs r0, #80
    adds r5, r5, r0
    bgt.n .L80EB264
.L80EB308:
    ldr r0, [pc, #24]
    str r0, [r7, #52]
    pop {r0, r1, r2, r3, r4, r5, r6, r7}
    mov r8, r0
    mov r9, r1
    mov sl, r2
    mov fp, r3
    pop {r3}
.L80EB318:
    bx r3
    .short 0
    .word 0x086A33E4
    .word 0x03007FF0
    .word 0x68736D53
