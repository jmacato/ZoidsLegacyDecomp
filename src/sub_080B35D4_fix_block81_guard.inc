.purgem ldr
.purgem add
.purgem orr
.purgem str
.set block81_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block81_ldr_fix == 0
.short 0x4914
.elseif block81_ldr_fix == 1
.short 0x680A
.else
.short 0x9F0B
.purgem ldr
.endif
.set block81_ldr_fix, block81_ldr_fix + 1
.endm
.set block81_cmp_fix, 0
.macro cmp lhs, rhs
.if block81_cmp_fix == 0
.short 0x2800
.else
.short 0x454F
.purgem cmp
.endif
.set block81_cmp_fix, block81_cmp_fix + 1
.endm
