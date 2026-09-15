/* M4A sound timer tail plus the alternate mplay-main entry prefix. */
.syntax unified
.thumb
.section .text
.global m4a_sound_timer
.thumb_func
m4a_sound_timer:
    ldr r0, [pc, #664]
    ldr r0, [r0, #0]
    ldr r2, [pc, #664]
    ldr r3, [r0, #0]
    subs r3, r3, r2
    cmp r3, #1
    bhi.n .Ltimer_done
    ldrb r1, [r0, #4]
    subs r1, #1
    strb r1, [r0, #4]
    bgt.n .Ltimer_done
    ldrb r1, [r0, #11]
    strb r1, [r0, #4]
    ldr r2, [pc, #24]
    ldr r1, [r2, #8]
    lsls r1, r1, #7
    bcc.n .Ltimer_dma_ready
    ldr r1, [pc, #20]
    str r1, [r2, #8]
.Ltimer_dma_ready:
    movs r1, #4
    lsls r1, r1, #8
    strh r1, [r2, #10]
    movs r1, #182
    lsls r1, r1, #8
    strh r1, [r2, #10]
.Ltimer_done:
    bx lr
    .word 0x040000BC
    .word 0x84400004

.global m4a_mplay_main_alt
.thumb_func
m4a_mplay_main_alt:
    ldr r2, [pc, #608]
    ldr r3, [r0, #52]
    cmp r2, r3
    beq.n .Lmplay_counter
    bx lr
.Lmplay_counter:
    adds r3, #1
    str r3, [r0, #52]
