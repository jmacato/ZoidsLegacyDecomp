.set b44_sp28_ldr, 0
.macro ldr dst, addr:vararg
.if b44_sp28_ldr == 0
.short 0x9E0A
.endif
.set b44_sp28_ldr, b44_sp28_ldr + 1
.endm
.macro cmp lhs, rhs
.short 0x2E00
.endm
.set b44_sp28_strh, 0
.macro strh src, addr:vararg
.if b44_sp28_strh == 0
.short 0x80B2
.else
.short 0x80F0
.endif
.set b44_sp28_strh, b44_sp28_strh + 1
.endm
.macro ldrh dst, addr:vararg
.short 0x88D8
.endm
