.macro lsl dst, lhs, rhs
.short 0x05A5
.purgem lsl
.endm
.macro lsr dst, lhs, rhs
.short 0x0C2A
.purgem lsr
.endm
