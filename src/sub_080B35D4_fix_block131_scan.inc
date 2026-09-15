.short 0x2500
.macro ldr dst, addr:vararg
.short 0x4A0C
.purgem ldr
.endm
.set block131_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if block131_ldrb_fix == 0
.short 0x7810
.else
.short 0x7800
.purgem ldrb
.endif
.set block131_ldrb_fix, block131_ldrb_fix + 1
.endm
.set block131_cmp_fix, 0
.macro cmp lhs, rhs
.if block131_cmp_fix == 0
.short 0x2800
.elseif block131_cmp_fix == 1
.short 0x2D05
.elseif block131_cmp_fix == 2
.short 0x2800
.else
.short 0x2D05
.purgem cmp
.endif
.set block131_cmp_fix, block131_cmp_fix + 1
.endm
.set block131_add_fix, 0
.macro add dst, args:vararg
.if block131_add_fix == 0
.short 0x1C11
.elseif block131_add_fix == 1
.short 0x1C68
.else
.short 0x1868
.purgem add
.endif
.set block131_add_fix, block131_add_fix + 1
.endm
.macro lsl dst, lhs, rhs
.short 0x0600
.purgem lsl
.endm
.macro lsr dst, lhs, rhs
.short 0x0E05
.purgem lsr
.endm
