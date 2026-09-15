.set nav_mov_fix, 0
.macro mov dst, args:vararg
.if nav_mov_fix == 0
.short 0x464F
.elseif nav_mov_fix == 1
.short 0x2010
.elseif nav_mov_fix == 2
.short 0x4648
.endif
.set nav_mov_fix, nav_mov_fix + 1
.if nav_mov_fix == 4
.purgem mov
.endif
.endm
.set nav_cmp_fix, 0
.macro cmp lhs, rhs
.if nav_cmp_fix == 0
.short 0x2F02
.elseif nav_cmp_fix == 1
.short 0x2800
.elseif nav_cmp_fix == 2
.short 0x2802
.elseif nav_cmp_fix == 3
.short 0x2800
.else
.short 0x2900
.endif
.set nav_cmp_fix, nav_cmp_fix + 1
.if nav_cmp_fix == 5
.purgem cmp
.endif
.endm
.set nav_ldr_fix, 0
.macro ldr dst, addr:vararg
.if nav_ldr_fix == 0
.short 0x480E
.else
.short 0x990C
.purgem ldr
.endif
.set nav_ldr_fix, nav_ldr_fix + 1
.endm
.macro sub dst, args:vararg
.short 0x4648
.short 0x3803
.purgem sub
.endm
