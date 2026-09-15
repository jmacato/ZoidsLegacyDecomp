.short 0x9000
.set block121_tail_mov_fix, 0
.macro mov dst, args:vararg
.if block121_tail_mov_fix == 0
.short 0x200F
.elseif block121_tail_mov_fix == 1
.short 0x2060
.elseif block121_tail_mov_fix == 2
.short 0x2200
.elseif block121_tail_mov_fix == 3
.short 0x203E
.elseif block121_tail_mov_fix == 4
.short 0x2580
.else
.short 0x464F
.purgem mov
.endif
.set block121_tail_mov_fix, block121_tail_mov_fix + 1
.endm
.set block121_tail_str_fix, 0
.macro str src, addr:vararg
.if block121_tail_str_fix == 0
.short 0x9001
.elseif block121_tail_str_fix == 1
.short 0x9002
.elseif block121_tail_str_fix == 2
.short 0x9003
.elseif block121_tail_str_fix == 3
.short 0x9604
.elseif block121_tail_str_fix == 4
.short 0x9009
.else
.short 0x970D
.purgem str
.endif
.set block121_tail_str_fix, block121_tail_str_fix + 1
.endm
