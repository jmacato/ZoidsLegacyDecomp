.set block185_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block185_lsl_fix == 0
.short 0x00AC
.else
.short 0x0600
.purgem lsl
.endif
.set block185_lsl_fix, block185_lsl_fix + 1
.endm
.set block185_add_fix, 0
.macro add dst, args:vararg
.if block185_add_fix == 0
.short 0x19A0
.elseif block185_add_fix == 1
.short 0x1824
.else
.short 0x1C68
.purgem add
.endif
.set block185_add_fix, block185_add_fix + 1
.endm
.set block185_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block185_ldr_fix == 0
.short 0x6800
.elseif block185_ldr_fix == 1
.short 0x4812
.else
.short 0x6820
.purgem ldr
.endif
.set block185_ldr_fix, block185_ldr_fix + 1
.endm
.macro bls target
.short 0xD9F0
.purgem bls
.endm
