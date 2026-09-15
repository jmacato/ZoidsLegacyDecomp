.set loop3_add_fix, 0
.macro add dst, args:vararg
.if loop3_add_fix == 1
.short 0x19C8
.elseif loop3_add_fix == 2
.short 0x19C8
.purgem add
.endif
.set loop3_add_fix, loop3_add_fix + 1
.endm
.set loop3_mov_fix, 0
.macro mov dst, args:vararg
.if loop3_mov_fix == 0
.short 0x4657
.elseif loop3_mov_fix == 1
.short 0x2700
.else
.short 0x2700
.purgem mov
.endif
.set loop3_mov_fix, loop3_mov_fix + 1
.endm
.set loop3_ldrsh_fix, 0
.macro ldrsh dst, addr:vararg
.if loop3_ldrsh_fix == 0
.short 0x5FC3
.else
.short 0x5FC0
.purgem ldrsh
.endif
.set loop3_ldrsh_fix, loop3_ldrsh_fix + 1
.endm
.set loop3_ldr_fix, 0
.macro ldr dst, addr:vararg
.if loop3_ldr_fix == 0
.short 0x4F21
.else
.short 0x9C11
.purgem ldr
.endif
.set loop3_ldr_fix, loop3_ldr_fix + 1
.endm
.macro lsr dst, lhs, rhs
.short 0x0C20
.purgem lsr
.endm
.macro ldrb dst, addr:vararg
.short 0x7820
.short 0x1C0C
.purgem ldrb
.endm
