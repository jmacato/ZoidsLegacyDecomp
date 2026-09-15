.set b69_mov_fix, 0
.macro mov dst, args:vararg
.if b69_mov_fix == 0
.short 0x464F
.else
.short 0x4823
.purgem mov
.endif
.set b69_mov_fix, b69_mov_fix + 1
.endm
.set b69_add_fix, 0
.macro add dst, args:vararg
.if b69_add_fix == 0
.short 0x1938
.else
.short 0x4440
.purgem add
.endif
.set b69_add_fix, b69_add_fix + 1
.endm
