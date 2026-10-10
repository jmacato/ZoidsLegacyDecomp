.syntax unified
.arm
.section .text
.balign 4, 0
.global next_engine_random
.type next_engine_random, %function
next_engine_random:
    ldr r3, .Lrandom_seed
    ldr r1, [r3]
    ldr r2, .Lmultiplier
    mul r0, r1, r2
    ldr r1, .Lincrement
    add r0, r0, r1
    str r0, [r3]
    lsr r0, r0, #0x10
    bic r0, r0, #0x8000
    bx lr
.Lrandom_seed:
    .word 0x03000990
.Lmultiplier:
    .word 0x41C64E6D
.Lincrement:
    .word 0x00003039
.size next_engine_random, . - next_engine_random
