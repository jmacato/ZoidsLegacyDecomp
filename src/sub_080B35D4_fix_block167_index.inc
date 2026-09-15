.macro ldr dst, addr:vararg
.short 0x9B0D
.purgem ldr
.endm
.macro sub dst, lhs, rhs
.short 0x1A18
.purgem sub
.endm
