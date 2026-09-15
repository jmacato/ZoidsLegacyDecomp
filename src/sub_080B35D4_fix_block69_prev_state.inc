.macro ldr dst, addr:vararg
.short 0x4C13
.purgem ldr
.endm
.set block69_prev_add_fix, 0
.macro add dst, args:vararg
.if block69_prev_add_fix == 0
.short 0x1910
.elseif block69_prev_add_fix == 1
.short 0x1940
.elseif block69_prev_add_fix == 2
.short 0x303C
.else
.short 0x1900
.purgem add
.endif
.set block69_prev_add_fix, block69_prev_add_fix + 1
.endm
