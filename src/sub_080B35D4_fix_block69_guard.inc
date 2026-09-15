.purgem ldr
.purgem orr
.macro ldr dst, addr:vararg
.short 0x9B10
.purgem ldr
.endm
.macro ldrb dst, addr:vararg
.short 0x7818
.purgem ldrb
.endm
