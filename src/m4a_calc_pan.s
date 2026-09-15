/* M4A channel pan/volume calculation with channel and track in r4/r5. */
.syntax unified
.thumb
.section .text
.global m4a_calc_pan
.thumb_func
m4a_calc_pan:
    ldrb r1, [r4, #18]
    movs r0, #20
    ldrsb r2, [r4, r0]
    movs r3, #128
    adds r3, r3, r2
    muls r3, r1
    ldrb r0, [r5, #16]
    muls r0, r3
    asrs r0, r0, #14
    cmp r0, #255
    bls.n .Lm4a_calc_pan_left
    movs r0, #255
.Lm4a_calc_pan_left:
    strb r0, [r4, #2]
    movs r3, #127
    subs r3, r3, r2
    muls r3, r1
    ldrb r0, [r5, #17]
    muls r0, r3
    asrs r0, r0, #14
    cmp r0, #255
    bls.n .Lm4a_calc_pan_right
    movs r0, #255
.Lm4a_calc_pan_right:
    strb r0, [r4, #3]
    bx lr
