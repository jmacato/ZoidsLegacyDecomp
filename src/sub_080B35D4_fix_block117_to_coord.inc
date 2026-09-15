.short 0x1C01
.set block117_coord_mov_fix, 0
.macro mov dst, args:vararg
.if block117_coord_mov_fix == 0
.short 0x203E
.elseif block117_coord_mov_fix == 1
.short 0x2001
.elseif block117_coord_mov_fix == 2
.short 0x2500
.elseif block117_coord_mov_fix == 3
.short 0x2004
.elseif block117_coord_mov_fix == 4
.short 0x2004
.elseif block117_coord_mov_fix == 5
.short 0x464A
.else
.short 0x4653
.purgem mov
.endif
.set block117_coord_mov_fix, block117_coord_mov_fix + 1
.endm
.set block117_coord_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if block117_coord_lsl_fix == 0
.short 0x0091
.else
.short 0x041B
.purgem lsl
.endif
.set block117_coord_lsl_fix, block117_coord_lsl_fix + 1
.endm
.set block117_coord_add_fix, 0
.macro add dst, args:vararg
.if block117_coord_add_fix == 0
.short 0x18C8
.else
.short 0x1909
.purgem add
.endif
.set block117_coord_add_fix, block117_coord_add_fix + 1
.endm
.set block117_coord_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block117_coord_ldr_fix == 0
.short 0x9809
.elseif block117_coord_ldr_fix == 1
.short 0x990F
.elseif block117_coord_ldr_fix == 2
.short 0x9809
.else
.short 0x4C0E
.purgem ldr
.endif
.set block117_coord_ldr_fix, block117_coord_ldr_fix + 1
.endm
