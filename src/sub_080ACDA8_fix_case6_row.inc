.macro sub dst, lhs, rhs
.short 0x1A72
.purgem sub
.endm
.macro lsl dst, lhs, rhs
.short 0x0092
.purgem lsl
.endm
