.short 0x2500
.set block92_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block92_lsl_fix == 0
.short 0x00A8
.else
.short 0x03BF
.purgem lsl
.endif
.set block92_lsl_fix, block92_lsl_fix + 1
.endm
.macro mov dst, args:vararg
.short 0x2780
.purgem mov
.endm
.macro and dst, args:vararg
.short 0x4038
.purgem and
.endm
