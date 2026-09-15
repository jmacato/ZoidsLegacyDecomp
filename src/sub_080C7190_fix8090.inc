.short 0x1C01
.macro ldr dst, addr:vararg
.short 0x49B4
.macro add dst2, lhs, rhs
.short 0x1840
.purgem ldr
.purgem add
.endm
.endm
