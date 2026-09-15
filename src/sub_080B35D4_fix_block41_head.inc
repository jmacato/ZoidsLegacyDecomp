.macro ldr dst, addr:vararg
.short 0x9E0B
.purgem ldr
.endm
.macro cmp lhs, rhs
.short 0x45B1
.purgem cmp
.endm
.set block41_mov_fix, 0
.macro mov dst, args:vararg
.if block41_mov_fix == 0
.short 0x46A2
.elseif block41_mov_fix == 1
.short 0x464F
.else
.short 0x4652
.purgem mov
.endif
.set block41_mov_fix, block41_mov_fix + 1
.endm
.macro lsl dst, lhs, rhs
.short 0x00B9
.purgem lsl
.endm
.macro add dst, args:vararg
.short 0x1888
.purgem add
.endm
