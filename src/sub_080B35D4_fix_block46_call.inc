.macro ldrb dst, addr:vararg
.short 0x7808
.endm
.set b46_cmp_fix, 0
.macro cmp lhs, rhs
.if b46_cmp_fix == 0
.short 0x2800
.else
.short 0x2801
.endif
.set b46_cmp_fix, b46_cmp_fix + 1
.if b46_cmp_fix == 2
.purgem cmp
.endif
.endm
.set b46_lsl_fix, 0
.macro lsl dst, lhs, rhs
.if b46_lsl_fix == 0
.short 0x1C01
.short 0x00C8
.elseif b46_lsl_fix == 1
.short 0x0100
.elseif b46_lsl_fix == 2
.short 0x1C01
.short 0x0608
.elseif b46_lsl_fix == 3
.short 0x00F6
.elseif b46_lsl_fix == 4
.short 0x0600
.elseif b46_lsl_fix == 5
.short 0x00C1
.elseif b46_lsl_fix == 6
.short 0x0109
.elseif b46_lsl_fix == 7
.short 0x009B
.elseif b46_lsl_fix == 8
.short 0x00C1
.elseif b46_lsl_fix == 9
.short 0x0109
.elseif b46_lsl_fix == 10
.short 0x00C1
.elseif b46_lsl_fix == 11
.short 0x0109
.elseif b46_lsl_fix == 12
.short 0x00F6
.else
.short 0x0438
.endif
.set b46_lsl_fix, b46_lsl_fix + 1
.if b46_lsl_fix == 14
.purgem lsl
.endif
.endm
.set b46_lsr_fix, 0
.macro lsr dst, lhs, rhs
.if b46_lsr_fix == 0
.short 0x0E00
.else
.short 0x0E02
.endif
.set b46_lsr_fix, b46_lsr_fix + 1
.if b46_lsr_fix == 2
.purgem lsr
.endif
.endm
.set b46_sub_fix, 0
.macro sub dst, lhs, rhs
.if b46_sub_fix == 0
.short 0x1A40
.else
.short 0x1A50
.endif
.set b46_sub_fix, b46_sub_fix + 1
.if b46_sub_fix == 2
.purgem sub
.endif
.endm
.set b46_add_fix, 0
.macro add dst, args:vararg
.if b46_add_fix == 0
.short 0x1D29
.elseif b46_add_fix == 1
.short 0x1840
.elseif b46_add_fix == 2
.short 0x1C30
.elseif b46_add_fix == 3
.short 0x3001
.elseif b46_add_fix == 4
.short 0x1911
.elseif b46_add_fix == 5
.short 0x1949
.elseif b46_add_fix == 6
.short 0x313C
.elseif b46_add_fix == 7
.short 0x1C18
.elseif b46_add_fix == 8
.short 0x1C3C
.elseif b46_add_fix == 9
.short 0x1901
.elseif b46_add_fix == 10
.short 0x1949
.elseif b46_add_fix == 11
.short 0x313C
.elseif b46_add_fix == 12
.short 0x3001
.elseif b46_add_fix == 13
.short 0x1901
.elseif b46_add_fix == 14
.short 0x1949
.elseif b46_add_fix == 15
.short 0x313C
.else
.short 0x1C30
.endif
.set b46_add_fix, b46_add_fix + 1
.if b46_add_fix == 17
.purgem add
.endif
.endm
.macro ldr dst, addr:vararg
.short 0x9F0F
.purgem ldr
.endm
.set b46_orr_fix, 0
.macro orr dst, args:vararg
.if b46_orr_fix == 0
.short 0x4307
.elseif b46_orr_fix == 1
.short 0x4304
.else
.short 0x4307
.endif
.set b46_orr_fix, b46_orr_fix + 1
.if b46_orr_fix == 3
.purgem orr
.endif
.endm
.set b46_mov_fix, 0
.macro mov dst, args:vararg
.if b46_mov_fix == 0
.short 0x2100
.elseif b46_mov_fix == 1
.short 0x2303
.elseif b46_mov_fix == 2
.short 0x4648
.elseif b46_mov_fix == 3
.short 0x2103
.elseif b46_mov_fix == 4
.short 0x2680
.elseif b46_mov_fix == 5
.short 0x9F0F
.elseif b46_mov_fix == 6
.short 0x464A
.elseif b46_mov_fix == 7
.short 0x23E0
.elseif b46_mov_fix == 8
.short 0x2201
.elseif b46_mov_fix == 9
.short 0x4648
.elseif b46_mov_fix == 10
.short 0x4648
.elseif b46_mov_fix == 11
.short 0x2680
.elseif b46_mov_fix == 12
.short 0x2202
.elseif b46_mov_fix == 13
.short 0x2200
.else
.short 0x2000
.short 0x1C11
.endif
.set b46_mov_fix, b46_mov_fix + 1
.if b46_mov_fix == 15
.purgem mov
.endif
.endm
