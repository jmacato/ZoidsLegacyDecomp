/* Scheduler callback with a live phase value in r5. */
.syntax unified
.thumb
.section .text
.global wave_scroll_callback
.thumb_func
wave_scroll_callback:
    push {r4, r5, r6, r7, lr}
    ldr r7, [pc, #72]
.Lframe:
    movs r4, #0
    adds r6, r5, #1
.Lcolumn:
    adds r0, r4, r5
    lsls r0, r0, #17
    asrs r0, r0, #16
    bl func_08092A90
    lsls r3, r4, #1
    ldr r1, [pc, #56]
    ldrb r1, [r1, #0]
    movs r2, #1
    eors r2, r1
    lsls r1, r2, #2
    adds r1, r1, r2
    lsls r1, r1, #6
    adds r3, r3, r1
    adds r3, r3, r7
    lsls r0, r0, #16
    asrs r0, r0, #16
    cmp r0, #0
    bge.n .Lround
    adds r0, #63
.Lround:
    asrs r0, r0, #6
    subs r0, #16
    strh r0, [r3, #0]
    adds r0, r4, #1
    lsls r0, r0, #24
    lsrs r4, r0, #24
    cmp r4, #159
    bls.n .Lcolumn
    lsls r0, r6, #24
    lsrs r5, r0, #24
    movs r0, #1
    bl func_080ED17C
    b.n .Lframe
    .word 0x0203198E
    .word 0x0203198D
