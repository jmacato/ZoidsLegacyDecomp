.purgem ldr
.purgem orr
.set block73_mov_fix, 0
.macro mov dst, args:vararg
.if block73_mov_fix == 0
.short 0x4648
.else
.short 0x2280
.purgem mov
.endif
.set block73_mov_fix, block73_mov_fix + 1
.endm
.set block73_add_fix, 0
.macro add dst, args:vararg
.if block73_add_fix == 0
.short 0x3001
.elseif block73_add_fix == 1
.short 0x19D0
.elseif block73_add_fix == 2
.short 0x18C0
.elseif block73_add_fix == 3
.short 0x303C
.else
.short 0x1840
.purgem add
.endif
.set block73_add_fix, block73_add_fix + 1
.endm
.set block73_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block73_lsl_fix == 0
.short 0x0600
.elseif block73_lsl_fix == 1
.short 0x00C8
.elseif block73_lsl_fix == 2
.short 0x0100
.elseif block73_lsl_fix == 3
.short 0x0090
.else
.short 0x0392
.purgem lsl
.endif
.set block73_lsl_fix, block73_lsl_fix + 1
.endm
.macro lsr dst, lhs, rhs
.short 0x0E02
.purgem lsr
.endm
.set block73_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block73_ldr_fix == 0
.short 0x4B0C
.elseif block73_ldr_fix == 1
.short 0x4F0D
.elseif block73_ldr_fix == 2
.short 0x4905
.elseif block73_ldr_fix == 3
.short 0x6801
.else
.short 0x6808
.purgem ldr
.endif
.set block73_ldr_fix, block73_ldr_fix + 1
.endm
.set block73_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if block73_ldrb_fix == 0
.short 0x7801
.else
.short 0x7800
.purgem ldrb
.endif
.set block73_ldrb_fix, block73_ldrb_fix + 1
.endm
.set block73_cmp_fix, 0
.macro cmp lhs, rhs
.if block73_cmp_fix == 0
.short 0x2900
.else
.short 0x2800
.purgem cmp
.endif
.set block73_cmp_fix, block73_cmp_fix + 1
.endm
.macro sub dst, lhs, rhs
.short 0x1A40
.purgem sub
.endm
.macro orr dst, args:vararg
.short 0x4310
.purgem orr
.endm
