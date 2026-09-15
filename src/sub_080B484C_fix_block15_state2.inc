.macro mov dst, src
.short 0x4656
.purgem mov
.endm
.set b15_add_fix, 0
.macro add dst, args:vararg
.if b15_add_fix == 0
.short 0x19A8
.elseif b15_add_fix == 1
.short 0x3004
.elseif b15_add_fix == 2
.short 0x19A8
.elseif b15_add_fix == 3
.short 0x4448
.elseif b15_add_fix == 4
.short 0x1820
.elseif b15_add_fix == 5
.short 0x1C38
.else
.short 0x1869
.purgem add
.endif
.set b15_add_fix, b15_add_fix + 1
.endm
.set b15_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b15_ldr_fix == 0
.short 0x4E09
.elseif b15_ldr_fix == 1
.short 0x4806
.elseif b15_ldr_fix == 2
.short 0x4805
.elseif b15_ldr_fix == 3
.short 0x4803
.else
.short 0x490B
.purgem ldr
.endif
.set b15_ldr_fix, b15_ldr_fix + 1
.endm
