/* M4A repeat command handler using the sound driver's live-register ABI. */
.syntax unified
.thumb
.section .text
.global m4a_repeat
.thumb_func
m4a_repeat:
    push {lr}
    ldr r2, [r1, #64]
    ldrb r3, [r2, #0]
    cmp r3, #0
    bne.n .Lm4a_repeat_count
    adds r2, #1
    str r2, [r1, #64]
    b.n 0x080EAF02
.Lm4a_repeat_count:
    ldrb r3, [r1, #3]
    adds r3, #1
    strb r3, [r1, #3]
    mov ip, r3
    bl func_80EAEF4
    cmp ip, r3
    bcs.n .Lm4a_repeat_done
    b.n 0x080EAF02
.Lm4a_repeat_done:
    movs r3, #0
    strb r3, [r1, #3]
    adds r2, #5
    str r2, [r1, #64]
    pop {r0}
    bx r0
    .balign 4, 0
