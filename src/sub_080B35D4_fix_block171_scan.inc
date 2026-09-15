.set block171_scan_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block171_scan_ldr_fix == 0
.short 0x9B0E
.else
.short 0x9F0E
.purgem ldr
.endif
.set block171_scan_ldr_fix, block171_scan_ldr_fix + 1
.endm
.set block171_scan_cmp_fix, 0
.macro cmp lhs, rhs
.if block171_scan_cmp_fix == 0
.short 0x4298
.elseif block171_scan_cmp_fix == 1
.short 0x2D05
.else
.short 0x42B8
.purgem cmp
.endif
.set block171_scan_cmp_fix, block171_scan_cmp_fix + 1
.endm
