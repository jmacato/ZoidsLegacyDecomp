.syntax unified
.arm
.section .text
.balign 4, 0
.global swap_serial_receive_buffers
.type swap_serial_receive_buffers, %function
swap_serial_receive_buffers:
    push {r8, sb, sl, fp}
    mov ip, #0x4000000
    ldr fp, .Lserial_state
    add sl, fp, #0x28
    mov sb, #1
    mov r8, #0
    strb r8, [ip, #0x208]
    ldm sl, {r0, r1}
    stm sl!, {r1}
    stm sl!, {r0}
    ldrb r0, [fp, #5]
    strb r8, [fp, #5]
    strb sb, [ip, #0x208]
    pop {r8, sb, sl, fp}
    bx lr
.Lserial_state:
    .word 0x030032D4
.size swap_serial_receive_buffers, . - swap_serial_receive_buffers
