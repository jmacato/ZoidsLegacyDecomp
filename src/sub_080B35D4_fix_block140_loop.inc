.short 0x2500
.set block140_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block140_ldr_fix == 0
.short 0x4F1B
.elseif block140_ldr_fix == 1
.short 0x4E1B
.elseif block140_ldr_fix == 2
.short 0x4B1B
.elseif block140_ldr_fix == 3
.short 0x6820
.elseif block140_ldr_fix == 4
.short 0x6800
.elseif block140_ldr_fix == 5
.short 0x4A18
.elseif block140_ldr_fix == 6
.short 0x6800
.elseif block140_ldr_fix == 7
.short 0x6822
.elseif block140_ldr_fix == 8
.short 0x6811
.elseif block140_ldr_fix == 9
.short 0x480F
.elseif block140_ldr_fix == 10
.short 0x9809
.elseif block140_ldr_fix == 11
.short 0x980A
.else
.short 0x9C0E
.purgem ldr
.endif
.set block140_ldr_fix, block140_ldr_fix + 1
.endm
.set block140_mov_fix, 0
.macro mov dst, args:vararg
.if block140_mov_fix == 0
.short 0x2180
.elseif block140_mov_fix == 1
.short 0x2100
.elseif block140_mov_fix == 2
.short 0x2203
.elseif block140_mov_fix == 3
.short 0x2300
.elseif block140_mov_fix == 4
.short 0x203F
.else
.short 0x2300
.purgem mov
.endif
.set block140_mov_fix, block140_mov_fix + 1
.endm
.set block140_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block140_lsl_fix == 0
.short 0x00A8
.elseif block140_lsl_fix == 1
.short 0x0389
.elseif block140_lsl_fix == 2
.short 0x00C8
.elseif block140_lsl_fix == 3
.short 0x0100
.elseif block140_lsl_fix == 4
.short 0x0080
.elseif block140_lsl_fix == 5
.short 0x0069
.elseif block140_lsl_fix == 6
.short 0x0600
.elseif block140_lsl_fix == 7
.short 0x00E0
.else
.short 0x0100
.purgem lsl
.endif
.set block140_lsl_fix, block140_lsl_fix + 1
.endm
.set block140_add_fix, 0
.macro add dst, args:vararg
.if block140_add_fix == 0
.short 0x18C4
.elseif block140_add_fix == 1
.short 0x18A8
.elseif block140_add_fix == 2
.short 0x1980
.elseif block140_add_fix == 3
.short 0x19C0
.else
.short 0x1C68
.purgem add
.endif
.set block140_add_fix, block140_add_fix + 1
.endm
.set block140_str_fix, 0
.macro str src, addr:vararg
.if block140_str_fix == 0
.short 0x9100
.elseif block140_str_fix == 1
.short 0x6011
.else
.short 0x930C
.purgem str
.endif
.set block140_str_fix, block140_str_fix + 1
.endm
.set block140_and_fix, 0
.macro and dst, args:vararg
.if block140_and_fix == 0
.short 0x4008
.else
.short 0x4001
.purgem and
.endif
.set block140_and_fix, block140_and_fix + 1
.endm
.set block140_cmp_fix, 0
.macro cmp lhs, rhs
.if block140_cmp_fix == 0
.short 0x2800
.else
.short 0x2D05
.purgem cmp
.endif
.set block140_cmp_fix, block140_cmp_fix + 1
.endm
.set block140_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if block140_ldrb_fix == 0
.short 0x7801
.else
.short 0x7900
.purgem ldrb
.endif
.set block140_ldrb_fix, block140_ldrb_fix + 1
.endm
.set block140_sub_fix, 0
.macro sub dst, lhs, rhs
.if block140_sub_fix == 0
.short 0x1A40
.else
.short 0x1B00
.purgem sub
.endif
.set block140_sub_fix, block140_sub_fix + 1
.endm
.macro lsr dst, lhs, rhs
.short 0x0E05
.purgem lsr
.endm
