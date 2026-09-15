/* Original MP2K CgbSound assembly routine. */
.syntax unified
.text
.thumb
.align 2, 0
.global sub_080EC240
.thumb_func
sub_080EC240:
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, r9
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #28
	ldr r0, =0x03007FF0
	ldr r0, [r0, #0]
	str r0, [sp, #4]
	ldrb r0, [r0, #10]
	cmp r0, #0
	beq .L80EC264
	subs r0, #1
	ldr r1, [sp, #4]
	strb r0, [r1, #10]
	b .L80EC26A
	.pool
.L80EC264:
	movs r0, #14
	ldr r2, [sp, #4]
	strb r0, [r2, #10]
.L80EC26A:
	movs r6, #1
	ldr r0, [sp, #4]
	ldr r4, [r0, #28]
.L80EC270:
	ldrb r1, [r4, #0]
	movs r0, #199
	ands r0, r1
	adds r2, r6, #1
	mov sl, r2
	movs r2, #64
	adds r2, r2, r4
	mov r9, r2
	cmp r0, #0
	bne .L80EC286
	b .L80EC670
.L80EC286:
	cmp r6, #2
	beq .L80EC2B8
	cmp r6, #2
	bgt .L80EC294
	cmp r6, #1
	beq .L80EC29A
	b .L80EC2F0
.L80EC294:
	cmp r6, #3
	beq .L80EC2D0
	b .L80EC2F0
.L80EC29A:
	ldr r0, =0x04000060
	str r0, [sp, #8]
	ldr r7, =0x04000062
	ldr r2, =0x04000063
	str r2, [sp, #12]
	adds r0, #4
	str r0, [sp, #16]
	adds r2, #2
	b .L80EC300
	.pool
.L80EC2B8:
	ldr r0, =0x04000061
	str r0, [sp, #8]
	ldr r7, =0x04000068
	ldr r2, =0x04000069
	b .L80EC2F8
	.pool
.L80EC2D0:
	ldr r0, =0x04000070
	str r0, [sp, #8]
	ldr r7, =0x04000072
	ldr r2, =0x04000073
	str r2, [sp, #12]
	adds r0, #4
	str r0, [sp, #16]
	adds r2, #2
	b .L80EC300
	.pool
.L80EC2F0:
	ldr r0, =0x04000071
	str r0, [sp, #8]
	ldr r7, =0x04000078
	ldr r2, =0x04000079
.L80EC2F8:
	str r2, [sp, #12]
	adds r0, #11
	str r0, [sp, #16]
	adds r2, #4
.L80EC300:
	str r2, [sp, #20]
	ldr r0, [sp, #4]
	ldrb r0, [r0, #10]
	str r0, [sp, #0]
	ldr r2, [sp, #12]
	ldrb r0, [r2, #0]
	mov r8, r0
	adds r2, r1, #0
	movs r0, #128
	ands r0, r2
	cmp r0, #0
	beq .L80EC3F6
	movs r3, #64
	adds r0, r3, #0
	ands r0, r2
	lsls r0, r0, #24
	lsrs r5, r0, #24
	adds r0, r6, #1
	mov sl, r0
	movs r1, #64
	adds r1, r1, r4
	mov r9, r1
	cmp r5, #0
	bne .L80EC41A
	movs r0, #3
	strb r0, [r4, #0]
	strb r0, [r4, #29]
	adds r0, r4, #0
	str r3, [sp, #24]
	bl func_080EC1D8
	ldr r3, [sp, #24]
	cmp r6, #2
	beq .L80EC368
	cmp r6, #2
	bgt .L80EC35C
	cmp r6, #1
	beq .L80EC362
	b .L80EC3BC
	.pool
.L80EC35C:
	cmp r6, #3
	beq .L80EC374
	b .L80EC3BC
.L80EC362:
	ldrb r0, [r4, #31]
	ldr r2, [sp, #8]
	strb r0, [r2, #0]
.L80EC368:
	ldr r0, [r4, #36]
	lsls r0, r0, #6
	ldrb r1, [r4, #30]
	adds r0, r1, r0
	strb r0, [r7, #0]
	b .L80EC3C8
.L80EC374:
	ldr r1, [r4, #36]
	ldr r0, [r4, #40]
	cmp r1, r0
	beq .L80EC39C
	ldr r2, [sp, #8]
	strb r3, [r2, #0]
	ldr r1, =0x04000090
	ldr r2, [r4, #36]
	ldr r0, [r2, #0]
	str r0, [r1, #0]
	adds r1, #4
	ldr r0, [r2, #4]
	str r0, [r1, #0]
	adds r1, #4
	ldr r0, [r2, #8]
	str r0, [r1, #0]
	adds r1, #4
	ldr r0, [r2, #12]
	str r0, [r1, #0]
	str r2, [r4, #40]
.L80EC39C:
	ldr r0, [sp, #8]
	strb r5, [r0, #0]
	ldrb r0, [r4, #30]
	strb r0, [r7, #0]
	ldrb r0, [r4, #30]
	cmp r0, #0
	beq .L80EC3B4
	movs r0, #192
	b .L80EC3D6
	.pool
.L80EC3B4:
	movs r1, #128
	negs r1, r1
	strb r1, [r4, #26]
	b .L80EC3D8
.L80EC3BC:
	ldrb r0, [r4, #30]
	strb r0, [r7, #0]
	ldr r0, [r4, #36]
	lsls r0, r0, #3
	ldr r2, [sp, #16]
	strb r0, [r2, #0]
.L80EC3C8:
	ldrb r0, [r4, #4]
	adds r0, #8
	mov r8, r0
	ldrb r0, [r4, #30]
	cmp r0, #0
	beq .L80EC3D6
	movs r0, #64
.L80EC3D6:
	strb r0, [r4, #26]
.L80EC3D8:
	ldrb r1, [r4, #4]
	movs r2, #0
	strb r1, [r4, #11]
	movs r0, #255
	ands r0, r1
	adds r1, r6, #1
	mov sl, r1
	movs r1, #64
	adds r1, r1, r4
	mov r9, r1
	cmp r0, #0
	bne .L80EC3F2
	b .L80EC52E
.L80EC3F2:
	strb r2, [r4, #9]
	b .L80EC55C
.L80EC3F6:
	movs r0, #4
	ands r0, r2
	cmp r0, #0
	beq .L80EC428
	ldrb r0, [r4, #13]
	subs r0, #1
	strb r0, [r4, #13]
	movs r2, #255
	ands r0, r2
	lsls r0, r0, #24
	adds r1, r6, #1
	mov sl, r1
	movs r2, #64
	adds r2, r2, r4
	mov r9, r2
	cmp r0, #0
	ble .L80EC41A
	b .L80EC56E
.L80EC41A:
	lsls r0, r6, #24
	lsrs r0, r0, #24
	bl func_080EC188
	movs r0, #0
	strb r0, [r4, #0]
	b .L80EC66C
.L80EC428:
	movs r0, #64
	ands r0, r1
	adds r2, r6, #1
	mov sl, r2
	movs r2, #64
	adds r2, r2, r4
	mov r9, r2
	cmp r0, #0
	beq .L80EC468
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	beq .L80EC468
	movs r0, #252
	ands r0, r1
	movs r2, #0
	strb r0, [r4, #0]
	ldrb r1, [r4, #7]
	strb r1, [r4, #11]
	movs r0, #255
	ands r0, r1
	cmp r0, #0
	beq .L80EC49A
	movs r0, #1
	ldrb r1, [r4, #29]
	orrs r0, r1
	strb r0, [r4, #29]
	cmp r6, #3
	beq .L80EC55C
	ldrb r2, [r4, #7]
	mov r8, r2
	b .L80EC55C
.L80EC468:
	ldrb r0, [r4, #11]
	cmp r0, #0
	bne .L80EC55C
	cmp r6, #3
	bne .L80EC47A
	movs r0, #1
	ldrb r1, [r4, #29]
	orrs r0, r1
	strb r0, [r4, #29]
.L80EC47A:
	adds r0, r4, #0
	bl func_080EC1D8
	movs r0, #3
	ldrb r2, [r4, #0]
	ands r0, r2
	cmp r0, #0
	bne .L80EC4CE
	ldrb r0, [r4, #9]
	subs r0, #1
	strb r0, [r4, #9]
	movs r1, #255
	ands r0, r1
	lsls r0, r0, #24
	cmp r0, #0
	bgt .L80EC4CA
.L80EC49A:
	ldrb r2, [r4, #12]
	ldrb r1, [r4, #10]
	adds r0, r2, #0
	muls r0, r1
	adds r0, #255
	asrs r0, r0, #8
	movs r1, #0
	strb r0, [r4, #9]
	lsls r0, r0, #24
	cmp r0, #0
	beq .L80EC41A
	movs r0, #4
	ldrb r2, [r4, #0]
	orrs r0, r2
	strb r0, [r4, #0]
	movs r0, #1
	ldrb r1, [r4, #29]
	orrs r0, r1
	strb r0, [r4, #29]
	cmp r6, #3
	beq .L80EC56E
	movs r2, #8
	mov r8, r2
	b .L80EC56E
.L80EC4CA:
	ldrb r0, [r4, #7]
	b .L80EC55A
.L80EC4CE:
	cmp r0, #1
	bne .L80EC4DA
.L80EC4D2:
	ldrb r0, [r4, #25]
	strb r0, [r4, #9]
	movs r0, #7
	b .L80EC55A
.L80EC4DA:
	cmp r0, #2
	bne .L80EC51E
	ldrb r0, [r4, #9]
	subs r0, #1
	strb r0, [r4, #9]
	movs r1, #255
	ands r0, r1
	lsls r0, r0, #24
	ldrb r2, [r4, #25]
	lsls r1, r2, #24
	cmp r0, r1
	bgt .L80EC51A
.L80EC4F2:
	ldrb r0, [r4, #6]
	cmp r0, #0
	bne .L80EC502
	movs r0, #252
	ldrb r1, [r4, #0]
	ands r0, r1
	strb r0, [r4, #0]
	b .L80EC49A
.L80EC502:
	ldrb r0, [r4, #0]
	subs r0, #1
	strb r0, [r4, #0]
	movs r0, #1
	ldrb r2, [r4, #29]
	orrs r0, r2
	strb r0, [r4, #29]
	cmp r6, #3
	beq .L80EC4D2
	movs r0, #8
	mov r8, r0
	b .L80EC4D2
.L80EC51A:
	ldrb r0, [r4, #5]
	b .L80EC55A
.L80EC51E:
	ldrb r0, [r4, #9]
	adds r0, #1
	strb r0, [r4, #9]
	movs r1, #255
	ands r0, r1
	ldrb r2, [r4, #10]
	cmp r0, r2
	bcc .L80EC558
.L80EC52E:
	ldrb r0, [r4, #0]
	subs r0, #1
	movs r2, #0
	strb r0, [r4, #0]
	ldrb r1, [r4, #5]
	strb r1, [r4, #11]
	movs r0, #255
	ands r0, r1
	cmp r0, #0
	beq .L80EC4F2
	movs r0, #1
	ldrb r1, [r4, #29]
	orrs r0, r1
	strb r0, [r4, #29]
	ldrb r0, [r4, #10]
	strb r0, [r4, #9]
	cmp r6, #3
	beq .L80EC55C
	ldrb r2, [r4, #5]
	mov r8, r2
	b .L80EC55C
.L80EC558:
	ldrb r0, [r4, #4]
.L80EC55A:
	strb r0, [r4, #11]
.L80EC55C:
	ldrb r0, [r4, #11]
	subs r0, #1
	strb r0, [r4, #11]
	ldr r0, [sp, #0]
	cmp r0, #0
	bne .L80EC56E
	subs r0, #1
	str r0, [sp, #0]
	b .L80EC468
.L80EC56E:
	movs r0, #2
	ldrb r1, [r4, #29]
	ands r0, r1
	cmp r0, #0
	beq .L80EC5E6
	cmp r6, #3
	bgt .L80EC5AE
	movs r0, #8
	ldrb r2, [r4, #1]
	ands r0, r2
	cmp r0, #0
	beq .L80EC5AE
	ldr r0, =0x04000089
	ldrb r0, [r0, #0]
	cmp r0, #63
	bgt .L80EC5A0
	ldr r0, [r4, #32]
	adds r0, #2
	ldr r1, =0x000007FC
	b .L80EC5AA
	.pool
.L80EC5A0:
	cmp r0, #127
	bgt .L80EC5AE
	ldr r0, [r4, #32]
	adds r0, #1
	ldr r1, =0x000007FE
.L80EC5AA:
	ands r0, r1
	str r0, [r4, #32]
.L80EC5AE:
	cmp r6, #4
	beq .L80EC5C0
	ldr r0, [r4, #32]
	ldr r1, [sp, #16]
	strb r0, [r1, #0]
	b .L80EC5CE
	.pool
.L80EC5C0:
	ldr r2, [sp, #16]
	ldrb r0, [r2, #0]
	movs r1, #8
	ands r1, r0
	ldr r0, [r4, #32]
	orrs r0, r1
	strb r0, [r2, #0]
.L80EC5CE:
	movs r0, #192
	ldrb r1, [r4, #26]
	ands r0, r1
	adds r1, r4, #0
	adds r1, #33
	ldrb r1, [r1, #0]
	adds r0, r1, r0
	strb r0, [r4, #26]
	movs r2, #255
	ands r0, r2
	ldr r1, [sp, #20]
	strb r0, [r1, #0]
.L80EC5E6:
	movs r0, #1
	ldrb r2, [r4, #29]
	ands r0, r2
	cmp r0, #0
	beq .L80EC66C
	ldr r1, =0x04000081
	ldrb r0, [r1, #0]
	ldrb r2, [r4, #28]
	bics r0, r2
	ldrb r2, [r4, #27]
	orrs r0, r2
	strb r0, [r1, #0]
	cmp r6, #3
	bne .L80EC638
	ldr r0, =0x086A33D4
	ldrb r1, [r4, #9]
	adds r0, r1, r0
	ldrb r0, [r0, #0]
	ldr r2, [sp, #12]
	strb r0, [r2, #0]
	movs r1, #128
	adds r0, r1, #0
	ldrb r2, [r4, #26]
	ands r0, r2
	cmp r0, #0
	beq .L80EC66C
	ldr r0, [sp, #8]
	strb r1, [r0, #0]
	ldrb r0, [r4, #26]
	ldr r1, [sp, #20]
	strb r0, [r1, #0]
	movs r0, #127
	ldrb r2, [r4, #26]
	ands r0, r2
	strb r0, [r4, #26]
	b .L80EC66C
	.pool
.L80EC638:
	movs r0, #15
	mov r1, r8
	ands r1, r0
	mov r8, r1
	ldrb r2, [r4, #9]
	lsls r0, r2, #4
	add r0, r8
	ldr r1, [sp, #12]
	strb r0, [r1, #0]
	movs r2, #128
	ldrb r0, [r4, #26]
	orrs r0, r2
	ldr r1, [sp, #20]
	strb r0, [r1, #0]
	cmp r6, #1
	bne .L80EC66C
	ldr r0, [sp, #8]
	ldrb r1, [r0, #0]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	bne .L80EC66C
	ldrb r0, [r4, #26]
	orrs r0, r2
	ldr r1, [sp, #20]
	strb r0, [r1, #0]
.L80EC66C:
	movs r0, #0
	strb r0, [r4, #29]
.L80EC670:
	mov r6, sl
	mov r4, r9
	cmp r6, #4
	bgt .L80EC67A
	b .L80EC270
.L80EC67A:
	add sp, #28
	pop {r3, r4, r5}
	mov r8, r3
	mov r9, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
