.short 0x2300
.macro ldr dst, addr:vararg
.short 0x4A16
.purgem ldr
.endm
.set b142_mov_fix, 0
.macro mov dst, args:vararg
.if b142_mov_fix == 0
.short 0x2400
.elseif b142_mov_fix == 1
.short 0x4692
.else
.short 0x4655
.endif
.set b142_mov_fix, b142_mov_fix + 1
.if b142_mov_fix == 3
.purgem mov
.endif
.endm
.macro add dst, args:vararg
.short 0x1960
.purgem add
.endm
