.short 0x2232, 0x5EA0
.set c7190_mov_fix, 0
.macro mov dst, src
.if c7190_mov_fix == 0
.short 0x4653
.elseif c7190_mov_fix == 1
.short 0x464C
.elseif c7190_mov_fix == 2
.short 0x2103
.elseif c7190_mov_fix == 3
.short 0x2200
.else
.short 0x230A
.endif
.set c7190_mov_fix, c7190_mov_fix + 1
.if c7190_mov_fix == 5
.purgem mov
.endif
.endm
.set c7190_str_fix, 0
.macro str src, addr:vararg
.if c7190_str_fix == 0
.short 0x9300
.elseif c7190_str_fix == 1
.short 0x9501
.else
.short 0x9402
.endif
.set c7190_str_fix, c7190_str_fix + 1
.if c7190_str_fix == 3
.purgem str
.endif
.endm
