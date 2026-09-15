/* MP2K SoundMain entry and handoff to the copied IWRAM mixer. */
.syntax unified
.thumb
.section .text
.global m4a_sound_main
.thumb_func
m4a_sound_main:
    ldr r0, [pc, #104]
    ldr r0, [r0, #0]
    ldr r2, [pc, #104]
    ldr r3, [r0, #0]
    cmp r2, r3
    beq.n .Lsound_locked
    bx lr
.Lsound_locked:
    adds r3, #1
    str r3, [r0, #0]
    push {r4, r5, r6, r7, lr}
    mov r1, r8
    mov r2, r9
    mov r3, sl
    mov r4, fp
    push {r0, r1, r2, r3, r4}
    sub sp, #24
    ldrb r1, [r0, #12]
    cmp r1, #0
    beq.n .Ltiming_ready
    ldr r2, [pc, #80]
    ldrb r2, [r2, #0]
    cmp r2, #160
    bcs.n .Ltiming_add
    adds r2, #228
.Ltiming_add:
    adds r1, r1, r2
.Ltiming_ready:
    str r1, [sp, #20]
    ldr r3, [r0, #32]
    cmp r3, #0
    beq.n .Lsecond_callback
    ldr r0, [r0, #36]
    bl func_80EAE52
    ldr r0, [sp, #24]
.Lsecond_callback:
    ldr r3, [r0, #40]
    bl func_80EAE52
    ldr r0, [sp, #24]
    ldr r3, [r0, #16]
    mov r8, r3
    ldr r5, [pc, #44]
    adds r5, r5, r0
    ldrb r4, [r0, #4]
    subs r7, r4, #1
    bls.n .Lbuffer_ready
    ldrb r1, [r0, #11]
    subs r1, r1, r7
    mov r2, r8
    muls r2, r1
    adds r5, r5, r2
.Lbuffer_ready:
    str r5, [sp, #8]
    ldr r6, [pc, #24]
    ldr r3, [pc, #12]
    bx r3
    .short 0
    .word 0x03007FF0
    .word 0x68736D53
    .word 0x03007759
    .word 0x04000006
    .word 0x00000350
    .word 0x00000630
