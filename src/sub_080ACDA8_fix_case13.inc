.set acd_case13_mov, 0
.macro mov dst, src
.if acd_case13_mov == 0
.short 0x464A
.else
.short 0x210A
.purgem mov
.endif
.set acd_case13_mov, acd_case13_mov + 1
.endm
.macro ldrsh dst, addr:vararg
.short 0x5E50
.purgem ldrsh
.endm
