.set acd_case14_mov, 0
.macro mov dst, src
.if acd_case14_mov == 0
.short 0x4649
.else
.short 0x220C
.purgem mov
.endif
.set acd_case14_mov, acd_case14_mov + 1
.endm
.macro ldrsh dst, addr:vararg
.short 0x5E88
.purgem ldrsh
.endm
