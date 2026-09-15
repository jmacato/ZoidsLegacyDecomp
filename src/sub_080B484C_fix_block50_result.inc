.short 0x930E
.set b50_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if b50_lsl_fix == 0
.short 0x1C01
.short 0x0608
.elseif b50_lsl_fix == 1
.short 0x00F6
.else
.short 0x0600
.endif
.set b50_lsl_fix, b50_lsl_fix + 1
.if b50_lsl_fix == 3
.purgem lsl
.endif
.endm
.set b50_lsr_fix, 0
.macro lsr dst, lhs, rhs
.if b50_lsr_fix == 0
.short 0x0E00
.else
.short 0x0E02
.endif
.set b50_lsr_fix, b50_lsr_fix + 1
.if b50_lsr_fix == 2
.purgem lsr
.endif
.endm
.macro cmp lhs, rhs
.short 0x2801
.purgem cmp
.endm
.macro sub dst, lhs, rhs
.short 0x1A50
.purgem sub
.endm
.macro add dst, args:vararg
.short 0x3001
.purgem add
.endm
.set b50_mov_fix, 0
.macro mov dst, args:vararg
.if b50_mov_fix == 0
.short 0x4648
.elseif b50_mov_fix == 1
.short 0x2103
.elseif b50_mov_fix == 2
.short 0x2680
.elseif b50_mov_fix == 3
.short 0x1C30
.elseif b50_mov_fix == 4
.short 0x464A
.elseif b50_mov_fix == 5
.short 0x23E0
.elseif b50_mov_fix == 6
.short 0x2201
.elseif b50_mov_fix == 7
.short 0x4648
.elseif b50_mov_fix == 8
.short 0x4648
.elseif b50_mov_fix == 9
.short 0x2680
.elseif b50_mov_fix == 10
.short 0x2202
.elseif b50_mov_fix == 11
.short 0x2200
.elseif b50_mov_fix == 12
.short 0x20FF
.elseif b50_mov_fix == 13
.short 0x2400
.elseif b50_mov_fix == 14
.short 0x4682
.endif
.set b50_mov_fix, b50_mov_fix + 1
.if b50_mov_fix == 16
.purgem mov
.endif
.endm
