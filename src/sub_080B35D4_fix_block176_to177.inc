.set block177_ldr_fix, 0
.macro ldr dst, addr:vararg
.if block177_ldr_fix == 0
.short 0x6802
.elseif block177_ldr_fix == 1
.short 0x6810
.elseif block177_ldr_fix == 2
.short 0x4818
.elseif block177_ldr_fix == 3
.short 0x6809
.elseif block177_ldr_fix == 4
.short 0x6808
.elseif block177_ldr_fix == 5
.short 0x980D
.elseif block177_ldr_fix == 6
.short 0x990E
.elseif block177_ldr_fix == 7
.short 0x9908
.elseif block177_ldr_fix == 8
.short 0x9B0D
.elseif block177_ldr_fix == 9
.short 0x480E
.elseif block177_ldr_fix == 10
.short 0x6801
.elseif block177_ldr_fix == 11
.short 0x6808
.elseif block177_ldr_fix == 12
.short 0x4A0E
.elseif block177_ldr_fix == 13
.short 0x480C
.elseif block177_ldr_fix == 14
.short 0x6800
.elseif block177_ldr_fix == 15
.short 0x6801
.else
.short 0x9A10
.purgem ldr
.endif
.set block177_ldr_fix, block177_ldr_fix + 1
.endm
.set block177_add_fix, 0
.macro add dst, args:vararg
.if block177_add_fix == 0
.short 0x1808
.elseif block177_add_fix == 1
.short 0x1809
.else
.short 0x1820
.endif
.set block177_add_fix, block177_add_fix + 1
.if block177_add_fix == 4
.purgem add
.endif
.endm
.set block177_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if block177_ldrb_fix == 0
.short 0x7808
.elseif block177_ldrb_fix == 1
.short 0x7849
.else
.short 0x7811
.purgem ldrb
.endif
.set block177_ldrb_fix, block177_ldrb_fix + 1
.endm
