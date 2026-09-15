.set block35_store_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block35_store_ldr_fix == 0
.short 0x4805
.elseif block35_store_ldr_fix == 1
.short 0x9909
.else
.short 0x9B0C
.purgem ldr
.endif
.set block35_store_ldr_fix, block35_store_ldr_fix + 1
.endm
.macro strh src, addr:vararg
.short 0x8148
.purgem strh
.endm
.set block35_store_mov_fix, 0
.macro mov dst, args:vararg
.if block35_store_mov_fix == 0
.short 0x2100
.elseif block35_store_mov_fix == 1
.short 0x2200
.else
.short 0x2200
.purgem mov
.endif
.set block35_store_mov_fix, block35_store_mov_fix + 1
.endm
.set block35_store_str_fix, 0
.macro str src, addr:vararg
.if block35_store_str_fix == 0
.short 0x9009
.elseif block35_store_str_fix == 1
.short 0x920A
.else
.short 0x9008
.purgem str
.endif
.set block35_store_str_fix, block35_store_str_fix + 1
.endm
.set block38_index_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block38_index_lsl_fix == 0
.short 0x00D8
.else
.short 0x0100
.purgem lsl
.endif
.set block38_index_lsl_fix, block38_index_lsl_fix + 1
.endm
.macro sub dst, lhs, rhs
.short 0x1AC0
.purgem sub
.endm
.macro add dst, lhs, rhs
.short 0x1840
.purgem add
.endm
.macro ldrb dst, addr:vararg
.short 0x7800
.purgem ldrb
.endm
