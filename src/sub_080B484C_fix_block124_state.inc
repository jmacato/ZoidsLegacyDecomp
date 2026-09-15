.set b124_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b124_ldr_fix == 0
.short 0x4B33
.else
.short 0x682A
.endif
.set b124_ldr_fix, b124_ldr_fix + 1
.if b124_ldr_fix == 2
.purgem ldr
.endif
.endm
.macro add dst, args:vararg
.short 0x18F5
.purgem add
.endm
