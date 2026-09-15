.set block181_cmp_fix, 0
.macro cmp lhs, rhs
.if block181_cmp_fix == 0
.short 0x2B00
.else
.short 0x2C00
.purgem cmp
.endif
.set block181_cmp_fix, block181_cmp_fix + 1
.endm
.macro ldr dst, addr:vararg
.short 0x9C07
.purgem ldr
.endm
