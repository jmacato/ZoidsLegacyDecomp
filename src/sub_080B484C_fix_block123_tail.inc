.set b123_tail_add_fix, 0
.macro add dst, args:vararg
.if b123_tail_add_fix == 0
.short 0x4448
.else
.short 0xAD0B
.endif
.set b123_tail_add_fix, b123_tail_add_fix + 1
.endm
.macro ldrb dst, addr:vararg
.short 0x782D
.endm
.set b123_tail_strb_fix, 0
.macro strb src, addr:vararg
.if b123_tail_strb_fix == 0
.short 0x7005
.else
.short 0x7006
.purgem strb
.endif
.set b123_tail_strb_fix, b123_tail_strb_fix + 1
.endm
.macro mov dst, args:vararg
.short 0x2600
.purgem mov
.endm
.set b123_tail_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b123_tail_ldr_fix == 0
.short 0x481A
.elseif b123_tail_ldr_fix == 1
.short 0x481A
.else
.short 0x9F0F
.purgem ldr
.endif
.set b123_tail_ldr_fix, b123_tail_ldr_fix + 1
.endm
.macro lsr dst, lhs, rhs
.short 0x0C3A
.purgem lsr
.endm
