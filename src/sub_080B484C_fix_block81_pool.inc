.purgem mov
.purgem lsl
.purgem orr
.set b81_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b81_ldr_fix == 0
.short 0x4914
.elseif b81_ldr_fix == 1
.short 0x680A
.elseif b81_ldr_fix == 2
.short 0x9F0A
.else
.short 0x4D0C
.purgem ldr
.endif
.set b81_ldr_fix, b81_ldr_fix + 1
.endm
