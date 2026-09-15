/* M4A sound-table initializer. */
.syntax unified
.thumb
.section .text
.global m4a_init_table
.thumb_func
m4a_init_table:
    push {r4, r5, lr}
    ldr r0, [pc, #32]
    lsls r0, r0, #16
    lsrs r0, r0, #16
    cmp r0, #0
    beq.n .Lm4a_init_table_done
    ldr r5, [pc, #24]
    adds r4, r0, #0
.Lm4a_init_table_loop:
    ldr r0, [r5, #0]
    bl func_80EB694
    adds r5, #12
    subs r4, #1
    cmp r4, #0
    bne.n .Lm4a_init_table_loop
.Lm4a_init_table_done:
    pop {r4, r5}
    pop {r0}
    bx r0
    .word 0x00000004
    .word 0x086A4694
