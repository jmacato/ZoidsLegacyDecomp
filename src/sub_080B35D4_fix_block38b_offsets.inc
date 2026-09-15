.set block38b_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block38b_ldr_fix == 0
.short 0x4818
.else
.short 0x9F0A
.purgem ldr
.endif
.set block38b_ldr_fix, block38b_ldr_fix + 1
.endm
.set block38b_strh_fix, 0
.macro strh src, addr:vararg
.if block38b_strh_fix == 0
.short 0x8138
.else
.short 0x8178
.purgem strh
.endif
.set block38b_strh_fix, block38b_strh_fix + 1
.endm
