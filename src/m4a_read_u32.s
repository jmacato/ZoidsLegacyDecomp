/* M4A stream reader with an alternate table-dispatched entry. */
.syntax unified
.thumb
.section .text
.global m4a_read_u32
.thumb_func
m4a_read_u32:
    push {lr}
    ldr r2, [r1, #64]
    ldrb r0, [r2, #3]
    lsls r0, r0, #8
    ldrb r3, [r2, #2]
    orrs r0, r3
    lsls r0, r0, #8
    ldrb r3, [r2, #1]
    orrs r0, r3
    lsls r0, r0, #8
    bl func_80EAED8
    orrs r0, r3
    str r0, [r1, #64]
    pop {r0}
    bx r0
.Lm4a_read_u32_alt:
    ldrb r2, [r1, #2]
    cmp r2, #3
    bcs.n .Lm4a_read_u32_done
    lsls r2, r2, #2
    adds r3, r1, r2
    ldr r2, [r1, #64]
    adds r2, #4
    str r2, [r3, #68]
    ldrb r2, [r1, #2]
    adds r2, #1
    strb r2, [r1, #2]
    b.n m4a_read_u32
.Lm4a_read_u32_done:
    b.n 0x080EAE90
    .balign 4, 0
