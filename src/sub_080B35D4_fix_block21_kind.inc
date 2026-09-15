.set block21_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.short 0x7808
.if block21_ldrb_fix == 1
.purgem ldrb
.endif
.set block21_ldrb_fix, block21_ldrb_fix + 1
.endm
.set block21_cmp_fix, 0
.macro cmp lhs, rhs
.if block21_cmp_fix == 0
.short 0x2800
.else
.short 0x2804
.purgem cmp
.endif
.set block21_cmp_fix, block21_cmp_fix + 1
.endm
.set block21_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block21_lsl_fix == 0
.short 0x00C1
.else
.short 0x0109
.purgem lsl
.endif
.set block21_lsl_fix, block21_lsl_fix + 1
.endm
.macro sub dst, lhs, rhs
.short 0x1A09
.purgem sub
.endm
.set block21_add_fix, 0
.macro add dst, args:vararg
.if block21_add_fix == 0
.short 0x18C9
.else
.short 0x313C
.purgem add
.endif
.set block21_add_fix, block21_add_fix + 1
.endm
