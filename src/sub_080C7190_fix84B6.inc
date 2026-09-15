.macro mov dst, src
.short 0x4643, 0x0198
.macro lsl dst2, src2, amount
.purgem mov
.purgem lsl
.endm
.endm
