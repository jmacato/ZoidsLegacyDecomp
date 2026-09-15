.macro lsl dst, lhs, rhs
.short 0x05AC
.purgem lsl
.endm
.macro lsr dst, lhs, rhs
.short 0x0C22
.purgem lsr
.endm
