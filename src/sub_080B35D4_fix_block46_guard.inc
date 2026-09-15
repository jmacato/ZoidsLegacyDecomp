.purgem ldrh
.macro ldr dst, addr:vararg
.short 0x9F0C
.purgem ldr
.endm
.macro cmp lhs, rhs
.short 0x2F00
.purgem cmp
.endm
