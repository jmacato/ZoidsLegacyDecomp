/* SoundMain supplies the custom stack frame and saved registers. */
.syntax unified
.section .text
.balign 4, 0
.global m4a_sound_mixer
.type m4a_sound_mixer, %function
.thumb
.thumb_func
m4a_sound_mixer:
.thumb
    ldrb r3, [r0, #5]
    cmp r3, #0
    beq .Lclear_buffer
    adr r1, .Lreverb_arm
    bx r1
    .short 0
.arm
.Lreverb_arm:
    cmp r4, #2
    addeq r7, r0, #0x350
    addne r7, r5, r8
    mov r4, r8
.Lreverb_sample:
    ldrsb r0, [r5]
    ldrsb r1, [r7], #1
    add r0, r0, r1
    mul r1, r0, r3
    asr r0, r1, #8
    tst r0, #0x80
    addne r0, r0, #1
    strb r0, [r5], #1
    subs r4, r4, #1
    bgt .Lreverb_sample
    add r0, pc, #(.Lbegin_channels + 1 - . - 8)
    bx r0
.thumb
.Lclear_buffer:
    movs r0, #0
    mov r1, r8
    lsrs r1, r1, #3
    blo .Lclear_pairs
    stm r5!, {r0}
.Lclear_pairs:
    lsrs r1, r1, #1
    blo .Lclear_block
    stm r5!, {r0}
    stm r5!, {r0}
.Lclear_block:
    stm r5!, {r0}
    stm r5!, {r0}
    stm r5!, {r0}
    stm r5!, {r0}
    subs r1, #1
    bgt .Lclear_block
.Lbegin_channels:
    ldr r4, [sp, #0x18]
    ldr r0, [r4, #0x18]
    mov ip, r0
    ldrb r0, [r4, #6]
    adds r4, #0x50
.Lchannel_count:
    str r0, [sp, #4]
    ldr r3, [r4, #0x24]
    ldr r0, [sp, #0x14]
    cmp r0, #0
    beq .Lprocess_channel
    ldr r1, .Lvcount
    ldrb r1, [r1]
    cmp r1, #0xa0
    bhs .Lscanline_ready
    adds r1, #0xe4
.Lscanline_ready:
    cmp r1, r0
    blo .Lprocess_channel
    b .Lfinish
    .short 0
.Lvcount:
    .word 0x04000006
.Lprocess_channel:
    ldrb r6, [r4]
    movs r0, #0xc7
    tst r0, r6
    bne .Lactive_channel
    b .Ladvance_channel
.Lactive_channel:
    movs r0, #0x80
    tst r0, r6
    beq .Lresume_envelope
    movs r0, #0x40
    tst r0, r6
    bne .Lstop_channel
    movs r6, #3
    strb r6, [r4]
    adds r0, r3, #0
    adds r0, #0x10
    str r0, [r4, #0x28]
    ldr r0, [r3, #0xc]
    str r0, [r4, #0x18]
    movs r5, #0
    strb r5, [r4, #9]
    str r5, [r4, #0x1c]
    ldrb r2, [r3, #3]
    movs r0, #0xc0
    tst r0, r2
    beq .Lattack
    movs r0, #0x10
    orrs r6, r0
    strb r6, [r4]
    b .Lattack
.Lresume_envelope:
    ldrb r5, [r4, #9]
    movs r0, #4
    tst r0, r6
    beq .Lcheck_release
    ldrb r0, [r4, #0xd]
    subs r0, #1
    strb r0, [r4, #0xd]
    bhi .Lsave_envelope
.Lstop_channel:
    movs r0, #0
    strb r0, [r4]
    b .Ladvance_channel
.Lcheck_release:
    movs r0, #0x40
    tst r0, r6
    beq .Lcheck_envelope_phase
    ldrb r0, [r4, #7]
    muls r5, r0, r5
    lsrs r5, r5, #8
    ldrb r0, [r4, #0xc]
    cmp r5, r0
    bhi .Lsave_envelope
.Lrelease_end:
    ldrb r5, [r4, #0xc]
    cmp r5, #0
    beq .Lstop_channel
    movs r0, #4
    orrs r6, r0
    strb r6, [r4]
    b .Lsave_envelope
.Lcheck_envelope_phase:
    movs r2, #3
    ands r2, r6
    cmp r2, #2
    bne .Lcheck_attack
    ldrb r0, [r4, #5]
    muls r5, r0, r5
    lsrs r5, r5, #8
    ldrb r0, [r4, #6]
    cmp r5, r0
    bhi .Lsave_envelope
    adds r5, r0, #0
    beq .Lrelease_end
    subs r6, #1
    strb r6, [r4]
    b .Lsave_envelope
.Lcheck_attack:
    cmp r2, #3
    bne .Lsave_envelope
.Lattack:
    ldrb r0, [r4, #4]
    adds r5, r5, r0
    cmp r5, #0xff
    blo .Lsave_envelope
    movs r5, #0xff
    subs r6, #1
    strb r6, [r4]
.Lsave_envelope:
    strb r5, [r4, #9]
    ldr r0, [sp, #0x18]
    ldrb r0, [r0, #7]
    adds r0, #1
    muls r0, r5, r0
    lsrs r5, r0, #4
    ldrb r0, [r4, #2]
    ldrb r1, [r4, #3]
    adds r0, r0, r1
    muls r0, r5, r0
    lsrs r0, r0, #9
    strb r0, [r4, #0xa]
    movs r0, #0x10
    ands r0, r6
    str r0, [sp, #0x10]
    beq .Lmix_channel
    adds r0, r3, #0
    adds r0, #0x10
    ldr r1, [r3, #8]
    adds r0, r0, r1
    str r0, [sp, #0xc]
    ldr r0, [r3, #0xc]
    subs r0, r0, r1
    str r0, [sp, #0x10]
.Lmix_channel:
    ldr r5, [sp, #8]
    ldr r2, [r4, #0x18]
    ldr r3, [r4, #0x28]
    adr r0, .Lpcm_arm
    bx r0
    .short 0
.arm
.Lpcm_arm:
    str r8, [sp]
    ldrb sl, [r4, #0xa]
    lsl sl, sl, #0x10
    ldrb r0, [r4, #1]
    tst r0, #8
    beq .Lbegin_interpolation
.Ldirect_loop:
    cmp r2, #4
    ble .Ldirect_tail
    subs r2, r2, r8
    movgt lr, #0
    bgt .Ldirect_block
    mov lr, r8
    add r2, r2, r8
    sub r8, r2, #4
    sub lr, lr, r8
    ands r2, r2, #3
    moveq r2, #4
.Ldirect_block:
    ldr r6, [r5]
.Ldirect_sample:
    ldrsb r0, [r3], #1
    mul r1, sl, r0
    bic r1, r1, #0xff0000
    add r6, r1, r6, ror #8
    adds r5, r5, #0x40000000
    blo .Ldirect_sample
    str r6, [r5], #4
    subs r8, r8, #4
    bgt .Ldirect_block
    adds r8, r8, lr
    beq .Lsave_pcm_position
.Ldirect_tail:
    ldr r6, [r5]
.Ldirect_tail_sample:
    ldrsb r0, [r3], #1
    mul r1, sl, r0
    bic r1, r1, #0xff0000
    add r6, r1, r6, ror #8
    subs r2, r2, #1
    beq .Ldirect_wrap
.Ladvance_direct_output:
    adds r5, r5, #0x40000000
    blo .Ldirect_tail_sample
    str r6, [r5], #4
    subs r8, r8, #4
    bgt .Ldirect_loop
    b .Lsave_pcm_position
.Linterpolated_wrap:
    ldr r0, [sp, #0x18]
    cmp r0, #0
    beq .Lstop_interpolation
    ldr r3, [sp, #0x14]
    rsb sb, r2, #0
.Lwrap_again:
    adds r2, r0, r2
    bgt .Linterpolated_step
    sub sb, sb, r0
    b .Lwrap_again
.Lstop_interpolation:
    pop {r4, ip}
    mov r2, #0
    b .Lstop_pcm
.Ldirect_wrap:
    ldr r2, [sp, #0x10]
    cmp r2, #0
    ldrne r3, [sp, #0xc]
    bne .Ladvance_direct_output
.Lstop_pcm:
    strb r2, [r4]
    lsr r0, r5, #0x1e
    bic r5, r5, #0xc0000000
    rsb r0, r0, #3
    lsl r0, r0, #3
    ror r6, r6, r0
    str r6, [r5], #4
    b .Lreturn_thumb
.Lbegin_interpolation:
    push {r4, ip}
    ldr lr, [r4, #0x1c]
    ldr r1, [r4, #0x20]
    mul r4, ip, r1
    ldrsb r0, [r3]
    ldrsb r1, [r3, #1]!
    sub r1, r1, r0
.Linterpolated_block:
    ldr r6, [r5]
.Linterpolated_sample:
    mul sb, lr, r1
    add sb, r0, sb, asr #23
    mul ip, sl, sb
    bic ip, ip, #0xff0000
    add r6, ip, r6, ror #8
    add lr, lr, r4
    lsrs sb, lr, #0x17
    beq .Ladvance_interpolated_output
    bic lr, lr, #0x3f800000
    subs r2, r2, sb
    ble .Linterpolated_wrap
    subs sb, sb, #1
    addeq r0, r0, r1
.Linterpolated_step:
    ldrsbne r0, [r3, sb]!
    ldrsb r1, [r3, #1]!
    sub r1, r1, r0
.Ladvance_interpolated_output:
    adds r5, r5, #0x40000000
    blo .Linterpolated_sample
    str r6, [r5], #4
    subs r8, r8, #4
    bgt .Linterpolated_block
    sub r3, r3, #1
    pop {r4, ip}
    str lr, [r4, #0x1c]
.Lsave_pcm_position:
    str r2, [r4, #0x18]
    str r3, [r4, #0x28]
.Lreturn_thumb:
    ldr r8, [sp]
    add r0, pc, #(.Ladvance_channel + 1 - . - 8)
    bx r0
.thumb
.Ladvance_channel:
    ldr r0, [sp, #4]
    subs r0, #1
    ble .Lfinish
    adds r4, #0x40
    b .Lchannel_count
.Lfinish:
    ldr r0, [sp, #0x18]
    ldr r3, [pc, #0x10]
    str r3, [r0]
    add sp, #0x1c
    pop {r0, r1, r2, r3, r4, r5, r6, r7}
    mov r8, r0
    mov sb, r1
    mov sl, r2
    mov fp, r3
    pop {r3}
    bx r3
.size m4a_sound_mixer, . - m4a_sound_mixer
