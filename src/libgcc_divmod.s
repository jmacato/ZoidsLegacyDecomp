/* GCC 2-era Thumb div/mod helpers, equivalent to agbcc/libgcc/lib1thumb.asm. */
.syntax unified
.thumb
.section .text
.balign 4, 0
.global __divsi3
.thumb_func
__divsi3:
    cmp r1, #0
    beq.n .L80ECE20
    push {r4}
    adds r4, r0, #0
    eors r4, r1
    mov ip, r4
    movs r3, #1
    movs r2, #0
    cmp r1, #0
    bpl.n .L80ECDAE
    negs r1, r1
.L80ECDAE:
    cmp r0, #0
    bpl.n .L80ECDB4
    negs r0, r0
.L80ECDB4:
    cmp r0, r1
    bcc.n .L80ECE12
    movs r4, #1
    lsls r4, r4, #28
.L80ECDBC:
    cmp r1, r4
    bcs.n .L80ECDCA
    cmp r1, r0
    bcs.n .L80ECDCA
    lsls r1, r1, #4
    lsls r3, r3, #4
    b.n .L80ECDBC
.L80ECDCA:
    lsls r4, r4, #3
.L80ECDCC:
    cmp r1, r4
    bcs.n .L80ECDDA
    cmp r1, r0
    bcs.n .L80ECDDA
    lsls r1, r1, #1
    lsls r3, r3, #1
    b.n .L80ECDCC
.L80ECDDA:
    cmp r0, r1
    bcc.n .L80ECDE2
    subs r0, r0, r1
    orrs r2, r3
.L80ECDE2:
    lsrs r4, r1, #1
    cmp r0, r4
    bcc.n .L80ECDEE
    subs r0, r0, r4
    lsrs r4, r3, #1
    orrs r2, r4
.L80ECDEE:
    lsrs r4, r1, #2
    cmp r0, r4
    bcc.n .L80ECDFA
    subs r0, r0, r4
    lsrs r4, r3, #2
    orrs r2, r4
.L80ECDFA:
    lsrs r4, r1, #3
    cmp r0, r4
    bcc.n .L80ECE06
    subs r0, r0, r4
    lsrs r4, r3, #3
    orrs r2, r4
.L80ECE06:
    cmp r0, #0
    beq.n .L80ECE12
    lsrs r3, r3, #4
    beq.n .L80ECE12
    lsrs r1, r1, #4
    b.n .L80ECDDA
.L80ECE12:
    adds r0, r2, #0
    mov r4, ip
    cmp r4, #0
    bpl.n .L80ECE1C
    negs r0, r0
.L80ECE1C:
    pop {r4}
    mov pc, lr
.L80ECE20:
    push {lr}
    bl __div0
    movs r0, #0
    pop {pc}
    movs r0, r0
.global __div0
.thumb_func
__div0:
    mov pc, lr
    movs r0, r0
.global __modsi3
.thumb_func
__modsi3:
    movs r3, #1
    cmp r1, #0
    beq.n .L80ECEF4
    bpl.n .L80ECE3A
    negs r1, r1
.L80ECE3A:
    push {r4}
    push {r0}
    cmp r0, #0
    bpl.n .L80ECE44
    negs r0, r0
.L80ECE44:
    cmp r0, r1
    bcc.n .L80ECEE8
    movs r4, #1
    lsls r4, r4, #28
.L80ECE4C:
    cmp r1, r4
    bcs.n .L80ECE5A
    cmp r1, r0
    bcs.n .L80ECE5A
    lsls r1, r1, #4
    lsls r3, r3, #4
    b.n .L80ECE4C
.L80ECE5A:
    lsls r4, r4, #3
.L80ECE5C:
    cmp r1, r4
    bcs.n .L80ECE6A
    cmp r1, r0
    bcs.n .L80ECE6A
    lsls r1, r1, #1
    lsls r3, r3, #1
    b.n .L80ECE5C
.L80ECE6A:
    movs r2, #0
    cmp r0, r1
    bcc.n .L80ECE72
    subs r0, r0, r1
.L80ECE72:
    lsrs r4, r1, #1
    cmp r0, r4
    bcc.n .L80ECE84
    subs r0, r0, r4
    mov ip, r3
    movs r4, #1
    rors r3, r4
    orrs r2, r3
    mov r3, ip
.L80ECE84:
    lsrs r4, r1, #2
    cmp r0, r4
    bcc.n .L80ECE96
    subs r0, r0, r4
    mov ip, r3
    movs r4, #2
    rors r3, r4
    orrs r2, r3
    mov r3, ip
.L80ECE96:
    lsrs r4, r1, #3
    cmp r0, r4
    bcc.n .L80ECEA8
    subs r0, r0, r4
    mov ip, r3
    movs r4, #3
    rors r3, r4
    orrs r2, r3
    mov r3, ip
.L80ECEA8:
    mov ip, r3
    cmp r0, #0
    beq.n .L80ECEB6
    lsrs r3, r3, #4
    beq.n .L80ECEB6
    lsrs r1, r1, #4
    b.n .L80ECE6A
.L80ECEB6:
    movs r4, #14
    lsls r4, r4, #28
    ands r2, r4
    beq.n .L80ECEE8
    mov r3, ip
    movs r4, #3
    rors r3, r4
    tst r2, r3
    beq.n .L80ECECC
    lsrs r4, r1, #3
    adds r0, r0, r4
.L80ECECC:
    mov r3, ip
    movs r4, #2
    rors r3, r4
    tst r2, r3
    beq.n .L80ECEDA
    lsrs r4, r1, #2
    adds r0, r0, r4
.L80ECEDA:
    mov r3, ip
    movs r4, #1
    rors r3, r4
    tst r2, r3
    beq.n .L80ECEE8
    lsrs r4, r1, #1
    adds r0, r0, r4
.L80ECEE8:
    pop {r4}
    cmp r4, #0
    bpl.n .L80ECEF0
    negs r0, r0
.L80ECEF0:
    pop {r4}
    mov pc, lr
.L80ECEF4:
    push {lr}
    bl __div0
    movs r0, #0
    pop {pc}
    movs r0, r0
.global __udivsi3
.thumb_func
__udivsi3:
    cmp r1, #0
    beq.n .L80ECF6E
    movs r3, #1
    movs r2, #0
    push {r4}
    cmp r0, r1
    bcc.n .L80ECF68
    movs r4, #1
    lsls r4, r4, #28
.L80ECF12:
    cmp r1, r4
    bcs.n .L80ECF20
    cmp r1, r0
    bcs.n .L80ECF20
    lsls r1, r1, #4
    lsls r3, r3, #4
    b.n .L80ECF12
.L80ECF20:
    lsls r4, r4, #3
.L80ECF22:
    cmp r1, r4
    bcs.n .L80ECF30
    cmp r1, r0
    bcs.n .L80ECF30
    lsls r1, r1, #1
    lsls r3, r3, #1
    b.n .L80ECF22
.L80ECF30:
    cmp r0, r1
    bcc.n .L80ECF38
    subs r0, r0, r1
    orrs r2, r3
.L80ECF38:
    lsrs r4, r1, #1
    cmp r0, r4
    bcc.n .L80ECF44
    subs r0, r0, r4
    lsrs r4, r3, #1
    orrs r2, r4
.L80ECF44:
    lsrs r4, r1, #2
    cmp r0, r4
    bcc.n .L80ECF50
    subs r0, r0, r4
    lsrs r4, r3, #2
    orrs r2, r4
.L80ECF50:
    lsrs r4, r1, #3
    cmp r0, r4
    bcc.n .L80ECF5C
    subs r0, r0, r4
    lsrs r4, r3, #3
    orrs r2, r4
.L80ECF5C:
    cmp r0, #0
    beq.n .L80ECF68
    lsrs r3, r3, #4
    beq.n .L80ECF68
    lsrs r1, r1, #4
    b.n .L80ECF30
.L80ECF68:
    adds r0, r2, #0
    pop {r4}
    mov pc, lr
.L80ECF6E:
    push {lr}
    bl __div0
    movs r0, #0
    pop {pc}
.global __umodsi3
.thumb_func
__umodsi3:
    cmp r1, #0
    beq.n .L80ED02E
    movs r3, #1
    cmp r0, r1
    bcs.n .L80ECF84
    mov pc, lr
.L80ECF84:
    push {r4}
    movs r4, #1
    lsls r4, r4, #28
.L80ECF8A:
    cmp r1, r4
    bcs.n .L80ECF98
    cmp r1, r0
    bcs.n .L80ECF98
    lsls r1, r1, #4
    lsls r3, r3, #4
    b.n .L80ECF8A
.L80ECF98:
    lsls r4, r4, #3
.L80ECF9A:
    cmp r1, r4
    bcs.n .L80ECFA8
    cmp r1, r0
    bcs.n .L80ECFA8
    lsls r1, r1, #1
    lsls r3, r3, #1
    b.n .L80ECF9A
.L80ECFA8:
    movs r2, #0
    cmp r0, r1
    bcc.n .L80ECFB0
    subs r0, r0, r1
.L80ECFB0:
    lsrs r4, r1, #1
    cmp r0, r4
    bcc.n .L80ECFC2
    subs r0, r0, r4
    mov ip, r3
    movs r4, #1
    rors r3, r4
    orrs r2, r3
    mov r3, ip
.L80ECFC2:
    lsrs r4, r1, #2
    cmp r0, r4
    bcc.n .L80ECFD4
    subs r0, r0, r4
    mov ip, r3
    movs r4, #2
    rors r3, r4
    orrs r2, r3
    mov r3, ip
.L80ECFD4:
    lsrs r4, r1, #3
    cmp r0, r4
    bcc.n .L80ECFE6
    subs r0, r0, r4
    mov ip, r3
    movs r4, #3
    rors r3, r4
    orrs r2, r3
    mov r3, ip
.L80ECFE6:
    mov ip, r3
    cmp r0, #0
    beq.n .L80ECFF4
    lsrs r3, r3, #4
    beq.n .L80ECFF4
    lsrs r1, r1, #4
    b.n .L80ECFA8
.L80ECFF4:
    movs r4, #14
    lsls r4, r4, #28
    ands r2, r4
    bne.n .L80ED000
    pop {r4}
    mov pc, lr
.L80ED000:
    mov r3, ip
    movs r4, #3
    rors r3, r4
    tst r2, r3
    beq.n .L80ED00E
    lsrs r4, r1, #3
    adds r0, r0, r4
.L80ED00E:
    mov r3, ip
    movs r4, #2
    rors r3, r4
    tst r2, r3
    beq.n .L80ED01C
    lsrs r4, r1, #2
    adds r0, r0, r4
.L80ED01C:
    mov r3, ip
    movs r4, #1
    rors r3, r4
    tst r2, r3
    beq.n .L80ED02A
    lsrs r4, r1, #1
    adds r0, r0, r4
.L80ED02A:
    pop {r4}
    mov pc, lr
.L80ED02E:
    push {lr}
    bl __div0
    movs r0, #0
    pop {pc}
