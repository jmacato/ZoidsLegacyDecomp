.short 0x2500
.set block64_mov_fix, 0
.macro mov dst, args:vararg
.if block64_mov_fix == 0
.short 0x2280
.elseif block64_mov_fix == 1
.short 0x2100
.elseif block64_mov_fix == 2
.short 0x2203
.elseif block64_mov_fix == 3
.short 0x2300
.else
.short 0x464F
.purgem mov
.endif
.set block64_mov_fix, block64_mov_fix + 1
.endm
.set block64_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block64_ldr_fix == 0
.short 0x9808
.elseif block64_ldr_fix == 1
.short 0x4F38
.elseif block64_ldr_fix == 2
.short 0x4E39
.elseif block64_ldr_fix == 3
.short 0x4939
.elseif block64_ldr_fix == 4
.short 0x6820
.elseif block64_ldr_fix == 5
.short 0x6800
.elseif block64_ldr_fix == 6
.short 0x4B35
.elseif block64_ldr_fix == 7
.short 0x6800
.elseif block64_ldr_fix == 8
.short 0x6822
.elseif block64_ldr_fix == 9
.short 0x6811
.elseif block64_ldr_fix == 10
.short 0x482C
.elseif block64_ldr_fix == 11
.short 0x4D24
.else
.short 0x4E28
.purgem ldr
.endif
.set block64_ldr_fix, block64_ldr_fix + 1
.endm
.set block64_add_fix, 0
.macro add dst, args:vararg
.if block64_add_fix == 0
.short 0x3038
.elseif block64_add_fix == 1
.short 0x1844
.elseif block64_add_fix == 2
.short 0x18E8
.elseif block64_add_fix == 3
.short 0x1980
.elseif block64_add_fix == 4
.short 0x19C0
.elseif block64_add_fix == 5
.short 0x1C68
.elseif block64_add_fix == 6
.short 0x19AC
.else
.short 0x1938
.purgem add
.endif
.set block64_add_fix, block64_add_fix + 1
.endm
.set block64_str_fix, 0
.macro str src, addr:vararg
.if block64_str_fix == 0
.short 0x9010
.elseif block64_str_fix == 1
.short 0x9100
.else
.short 0x6011
.purgem str
.endif
.set block64_str_fix, block64_str_fix + 1
.endm
.set block64_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block64_lsl_fix == 0
.short 0x00A8
.elseif block64_lsl_fix == 1
.short 0x0392
.elseif block64_lsl_fix == 2
.short 0x00C8
.elseif block64_lsl_fix == 3
.short 0x0100
.elseif block64_lsl_fix == 4
.short 0x0080
.elseif block64_lsl_fix == 5
.short 0x0069
.else
.short 0x0600
.purgem lsl
.endif
.set block64_lsl_fix, block64_lsl_fix + 1
.endm
.set block64_and_fix, 0
.macro and dst, args:vararg
.if block64_and_fix == 0
.short 0x4010
.else
.short 0x4001
.purgem and
.endif
.set block64_and_fix, block64_and_fix + 1
.endm
.set block64_cmp_fix, 0
.macro cmp lhs, rhs
.if block64_cmp_fix == 0
.short 0x2800
.elseif block64_cmp_fix == 1
.short 0x2D05
.else
.short 0x2800
.purgem cmp
.endif
.set block64_cmp_fix, block64_cmp_fix + 1
.endm
.set block64_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if block64_ldrb_fix == 0
.short 0x7801
.elseif block64_ldrb_fix == 1
.short 0x7900
.else
.short 0x7800
.purgem ldrb
.endif
.set block64_ldrb_fix, block64_ldrb_fix + 1
.endm
.macro sub dst, lhs, rhs
.short 0x1A40
.purgem sub
.endm
.macro lsr dst, lhs, rhs
.short 0x0E05
.purgem lsr
.endm
