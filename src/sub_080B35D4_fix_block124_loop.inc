.short 0x2500
.set block124_mov_fix, 0
.macro mov dst, args:vararg
.if block124_mov_fix == 0
.short 0x4648
.elseif block124_mov_fix == 1
.short 0x4680
.elseif block124_mov_fix == 2
.short 0x464A
.elseif block124_mov_fix == 3
.short 0x4692
.elseif block124_mov_fix == 4
.short 0x2780
.elseif block124_mov_fix == 5
.short 0x1C08
.elseif block124_mov_fix == 6
.short 0x2380
.elseif block124_mov_fix == 7
.short 0x2001
.elseif block124_mov_fix == 8
.short 0x4648
.elseif block124_mov_fix == 9
.short 0x4656
.else
.short 0x464B
.purgem mov
.endif
.set block124_mov_fix, block124_mov_fix + 1
.endm
.set block124_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block124_lsl_fix == 0
.short 0x0080
.elseif block124_lsl_fix == 1
.short 0x0592
.elseif block124_lsl_fix == 2
.short 0x02BF
.elseif block124_lsl_fix == 3
.short 0x00AE
.elseif block124_lsl_fix == 4
.short 0x039B
.else
.short 0x0600
.purgem lsl
.endif
.set block124_lsl_fix, block124_lsl_fix + 1
.endm
.set block124_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block124_ldr_fix == 0
.short 0x9908
.elseif block124_ldr_fix == 1
.short 0x4B25
.elseif block124_ldr_fix == 2
.short 0x6822
.elseif block124_ldr_fix == 3
.short 0x6811
.elseif block124_ldr_fix == 4
.short 0x4821
.elseif block124_ldr_fix == 5
.short 0x6821
.elseif block124_ldr_fix == 6
.short 0x6808
.elseif block124_ldr_fix == 7
.short 0x481D
.elseif block124_ldr_fix == 8
.short 0x6801
.elseif block124_ldr_fix == 9
.short 0x6808
.elseif block124_ldr_fix == 10
.short 0x990C
.elseif block124_ldr_fix == 11
.short 0x9C08
.elseif block124_ldr_fix == 12
.short 0x6801
.elseif block124_ldr_fix == 13
.short 0x6808
.elseif block124_ldr_fix == 14
.short 0x4A0F
.elseif block124_ldr_fix == 15
.short 0x480D
.elseif block124_ldr_fix == 16
.short 0x6800
.elseif block124_ldr_fix == 17
.short 0x6801
.else
.short 0x9F10
.purgem ldr
.endif
.set block124_ldr_fix, block124_ldr_fix + 1
.endm
.set block124_add_fix, 0
.macro add dst, args:vararg
.if block124_add_fix == 0
.short 0x3138
.elseif block124_add_fix == 1
.short 0x18F4
.elseif block124_add_fix == 2
.short 0x1C28
.elseif block124_add_fix == 3
.short 0x1830
.elseif block124_add_fix == 4
.short 0x1C68
.else
.short 0x4440
.endif
.set block124_add_fix, block124_add_fix + 1
.if block124_add_fix == 7
.purgem add
.endif
.endm
.set block124_str_fix, 0
.macro str src, addr:vararg
.if block124_str_fix == 0
.short 0x9110
.elseif block124_str_fix == 1
.short 0x6011
.elseif block124_str_fix == 2
.short 0x6008
.elseif block124_str_fix == 3
.short 0x6008
.elseif block124_str_fix == 4
.short 0x6008
.else
.short 0x6001
.purgem str
.endif
.set block124_str_fix, block124_str_fix + 1
.endm
.set block124_and_fix, 0
.macro and dst, args:vararg
.if block124_and_fix == 0
.short 0x4018
.elseif block124_and_fix == 1
.short 0x4001
.elseif block124_and_fix == 2
.short 0x4010
.elseif block124_and_fix == 3
.short 0x4011
.else
.short 0x4008
.purgem and
.endif
.set block124_and_fix, block124_and_fix + 1
.endm
.set block124_cmp_fix, 0
.macro cmp lhs, rhs
.if block124_cmp_fix == 0
.short 0x2800
.elseif block124_cmp_fix == 1
.short 0x2D05
.else
.short 0x2800
.purgem cmp
.endif
.set block124_cmp_fix, block124_cmp_fix + 1
.endm
.set block124_orr_fix, 0
.macro orr dst, args:vararg
.short 0x4338
.set block124_orr_fix, block124_orr_fix + 1
.if block124_orr_fix == 2
.purgem orr
.endif
.endm
.set block124_lsr_fix, 0
.macro lsr dst, lhs, rhs
.if block124_lsr_fix == 0
.short 0x0E05
.else
.short 0x0C32
.purgem lsr
.endif
.set block124_lsr_fix, block124_lsr_fix + 1
.endm
.set block124_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if block124_ldrb_fix == 0
.short 0x7820
.elseif block124_ldrb_fix == 1
.short 0x7861
.else
.short 0x7839
.purgem ldrb
.endif
.set block124_ldrb_fix, block124_ldrb_fix + 1
.endm
