.set b44_sp24_ldr, 0
.macro ldr dst, addr:vararg
.if b44_sp24_ldr == 0
.short 0x9B09
.elseif b44_sp24_ldr == 1
.short 0x4C11
.endif
.set b44_sp24_ldr, b44_sp24_ldr + 1
.endm
.set b44_sp24_strh, 0
.macro strh src, addr:vararg
.if b44_sp24_strh == 0
.short 0x809A
.else
.short 0x80D8
.endif
.set b44_sp24_strh, b44_sp24_strh + 1
.endm
.macro add dst, args:vararg
.short 0x1908
.endm
