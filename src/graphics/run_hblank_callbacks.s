.syntax unified
.arm
.section .text
.balign 4, 0
.global run_hblank_callbacks
.type run_hblank_callbacks, %function
run_hblank_callbacks:
    stmdb sp!, {lr}
    ldr r2, .Lcallback0
    ldr r1, [r2]
    mov lr, pc
    bx r1
    ldr r2, .Lcallback1
    ldr r1, [r2]
    mov lr, pc
    bx r1
    ldr r2, .Lcallback2
    ldr r1, [r2]
    mov lr, pc
    bx r1
    ldr r2, .Lbios_irq_flags
    mov r1, #2
    strh r1, [r2]
    ldm sp!, {lr}
    bx lr
.Lcallback0:
    .word 0x03000000
.Lcallback1:
    .word 0x03000004
.Lcallback2:
    .word 0x03000008
.Lbios_irq_flags:
    .word 0x03007FF8
.size run_hblank_callbacks, . - run_hblank_callbacks
