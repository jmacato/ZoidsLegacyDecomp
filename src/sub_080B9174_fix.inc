.macro B9174_FIX_ITEM_LOOKUP
.set b9174_item_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b9174_item_ldr_fix == 0
.short 0x9B09
.elseif b9174_item_ldr_fix == 1
.short 0x4B0B
.else
.short 0x9A09
.purgem ldr
.endif
.set b9174_item_ldr_fix, b9174_item_ldr_fix + 1
.endm

.set b9174_item_add_fix, 0
.macro add dst, args:vararg
.if b9174_item_add_fix == 0
.short 0x1818
.elseif b9174_item_add_fix == 1
.short 0x1C3C
.elseif b9174_item_add_fix == 2
.short 0x341E
.elseif b9174_item_add_fix == 3
.short 0x1820
.elseif b9174_item_add_fix == 4
.short 0x3101
.elseif b9174_item_add_fix == 5
.short 0x1840
.elseif b9174_item_add_fix == 6
.short 0x3204
.elseif b9174_item_add_fix == 7
.short 0x1838
.elseif b9174_item_add_fix == 8
.short 0x3052
.elseif b9174_item_add_fix == 9
.short 0x1840
.else
.short 0x18C0
.purgem add
.endif
.set b9174_item_add_fix, b9174_item_add_fix + 1
.endm

.set b9174_item_lsl_fix, 0
.macro lsl dst, args:vararg
.if b9174_item_lsl_fix == 0
.short 0x0600
.elseif b9174_item_lsl_fix == 1
.short 0x0148
.elseif b9174_item_lsl_fix == 2
.short 0x0080
.elseif b9174_item_lsl_fix == 3
.short 0x0080
.elseif b9174_item_lsl_fix == 4
.short 0x0090
.elseif b9174_item_lsl_fix == 5
.short 0x0048
.else
.short 0x00C0
.purgem lsl
.endif
.set b9174_item_lsl_fix, b9174_item_lsl_fix + 1
.endm

.set b9174_item_mov_fix, 0
.macro mov dst, src
.if b9174_item_mov_fix == 0
.short 0x1C15
.else
.purgem mov
.endif
.set b9174_item_mov_fix, b9174_item_mov_fix + 1
.endm

.set b9174_item_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if b9174_item_ldrb_fix == 0
.short 0x7801
.else
.short 0x7A40
.short 0x4691
.purgem ldrb
.endif
.set b9174_item_ldrb_fix, b9174_item_ldrb_fix + 1
.endm

.macro str src, addr:vararg
.short 0x940B
.purgem str
.endm
.endm

.macro B9174_FIX_FIRST_CONFIRM_FLAGS
.set b9174_confirm_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if b9174_confirm_ldrb_fix == 0
.short 0x7806
.else
.short 0x7804
.purgem ldrb
.endif
.set b9174_confirm_ldrb_fix, b9174_confirm_ldrb_fix + 1
.endm
.set b9174_confirm_cmp_fix, 0
.macro cmp lhs, rhs
.if b9174_confirm_cmp_fix == 0
.short 0x2E01
.else
.short 0x2C00
.purgem cmp
.endif
.set b9174_confirm_cmp_fix, b9174_confirm_cmp_fix + 1
.endm
.endm

.macro B9174_FIX_FIRST_MONEY
.set b9174_money_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b9174_money_ldr_fix == 0
.short 0x4825
.elseif b9174_money_ldr_fix == 1
.short 0x4926
.else
.short 0x6808
.purgem ldr
.endif
.set b9174_money_ldr_fix, b9174_money_ldr_fix + 1
.endm
.macro add dst, args:vararg
.short 0x1809
.purgem add
.endm
.macro mov dst, src
.short 0x4688
.purgem mov
.endm
.endm

.macro B9174_FIX_FIRST_MESSAGE_ADD
.macro add dst, args:vararg
.short 0x1838
.purgem add
.endm
.endm

.macro B9174_FIX_FIRST_MONEY_CALL
.macro mov dst, src
.short 0x4643
.purgem mov
.endm
.macro ldr dst, addr:vararg
.short 0x6818
.purgem ldr
.endm
.set b9174_money_str_fix, 0
.macro str src, addr:vararg
.if b9174_money_str_fix == 0
.short 0x9600
.elseif b9174_money_str_fix == 1
.short 0x9601
.else
.short 0x9402
.purgem str
.endif
.set b9174_money_str_fix, b9174_money_str_fix + 1
.endm
.endm

.macro B9174_FIX_SELECTION_INDEX_ADD
.macro add dst, args:vararg
.short 0x1838
.purgem add
.endm
.endm

.macro B9174_FIX_SELECTION_MASK_LOAD
.macro ldr dst, addr:vararg
.short 0x9B05
.purgem ldr
.endm
.macro ldrh dst, addr:vararg
.short 0x8858
.purgem ldrh
.endm
.endm

.macro B9174_FIX_SELECTION_PRICE_ADDRESS
.macro ldr dst, addr:vararg
.short 0x9909
.purgem ldr
.endm
.set b9174_select_add_fix, 0
.macro add dst, args:vararg
.if b9174_select_add_fix == 0
.short 0x1808
.elseif b9174_select_add_fix == 1
.short 0x1C39
.elseif b9174_select_add_fix == 2
.short 0x311E
.else
.short 0x1809
.purgem add
.endif
.set b9174_select_add_fix, b9174_select_add_fix + 1
.endm
.set b9174_select_ldrb_fix, 0
.macro ldrb dst, addr:vararg
.if b9174_select_ldrb_fix == 0
.short 0x7838
.else
.short 0x7808
.purgem ldrb
.endif
.set b9174_select_ldrb_fix, b9174_select_ldrb_fix + 1
.endm
.endm

.macro B9174_FIX_SECOND_PRICE_SCALE
.macro mov dst, src
.short 0x2300
.purgem mov
.endm
.macro ldrsh dst, addr:vararg
.short 0x5EC1
.purgem ldrsh
.endm
.set b9174_price_lsl_fix, 0
.macro lsl dst, args:vararg
.if b9174_price_lsl_fix == 0
.short 0x0148
.elseif b9174_price_lsl_fix == 1
.short 0x0080
.else
.short 0x00C0
.purgem lsl
.endif
.set b9174_price_lsl_fix, b9174_price_lsl_fix + 1
.endm
.macro sub dst, args:vararg
.short 0x1A40
.purgem sub
.endm
.set b9174_price_add_fix, 0
.macro add dst, args:vararg
.if b9174_price_add_fix == 0
.short 0x3007
.else
.short 0x1840
.purgem add
.endif
.set b9174_price_add_fix, b9174_price_add_fix + 1
.endm
.endm

.macro B9174_FIX_THIRD_PRICE_SCALE
.macro mov dst, src
.short 0x2300
.purgem mov
.endm
.macro ldrsh dst, addr:vararg
.short 0x5EC1
.purgem ldrsh
.endm
.set b9174_third_price_lsl_fix, 0
.macro lsl dst, args:vararg
.if b9174_third_price_lsl_fix == 0
.short 0x0088
.else
.short 0x0040
.purgem lsl
.endif
.set b9174_third_price_lsl_fix, b9174_third_price_lsl_fix + 1
.endm
.set b9174_third_price_add_fix, 0
.macro add dst, args:vararg
.if b9174_third_price_add_fix == 0
.short 0x300D
.else
.short 0x1840
.purgem add
.endif
.set b9174_third_price_add_fix, b9174_third_price_add_fix + 1
.endm
.endm

.macro B9174_FIX_LATER_MONEY
.macro add dst, args:vararg
.short 0x1809
.purgem add
.endm
.macro mov dst, src
.short 0x4688
.purgem mov
.endm
.macro ldr dst, addr:vararg
.short 0x6808
.purgem ldr
.endm
.endm

.macro B9174_FIX_FLAG_AND
.set b9174_flag_and_fix, 0
.macro and dst, args:vararg
.if b9174_flag_and_fix == 0
.short 0x4001
.else
.short 0x4008
.purgem and
.endif
.set b9174_flag_and_fix, b9174_flag_and_fix + 1
.endm
.macro cmp lhs, rhs
.short 0x2800
.purgem cmp
.endm
.endm

.macro B9174_FIX_ZERO_PAIR
.set b9174_zero_pair_mov_fix, 0
.macro mov dst, src
.if b9174_zero_pair_mov_fix == 0
.short 0x2300
.else
.short 0x2000
.purgem mov
.endif
.set b9174_zero_pair_mov_fix, b9174_zero_pair_mov_fix + 1
.endm
.set b9174_zero_pair_str_fix, 0
.macro str src, addr:vararg
.if b9174_zero_pair_str_fix == 0
.short 0x9308
.else
.short 0x9007
.purgem str
.endif
.set b9174_zero_pair_str_fix, b9174_zero_pair_str_fix + 1
.endm
.endm

.macro B9174_FIX_ZERO_SP20
.macro mov dst, src
.short 0x2300
.purgem mov
.endm
.macro str src, addr:vararg
.short 0x9308
.purgem str
.endm
.endm

.macro B9174_FIX_NULL_SL
.set b9174_null_sl_mov_fix, 0
.macro mov dst, src
.if b9174_null_sl_mov_fix == 0
.short 0x2300
.else
.short 0x469A
.purgem mov
.endif
.set b9174_null_sl_mov_fix, b9174_null_sl_mov_fix + 1
.endm
.endm

.macro B9174_FIX_S16_FIELD_LOAD
.macro mov dst, src
.short 0x2100
.purgem mov
.endm
.macro ldrsh dst, addr:vararg
.short 0x5E40
.purgem ldrsh
.endm
.endm

.macro B9174_FIX_THIRD_ITEM_POINTER
.set b9174_third_item_mov_fix, 0
.macro mov dst, src
.if b9174_third_item_mov_fix == 0
.short 0x2218
.else
.short 0x4690
.purgem mov
.endif
.set b9174_third_item_mov_fix, b9174_third_item_mov_fix + 1
.endm
.macro add dst, args:vararg
.short 0x19D2
.purgem add
.endm
.endm

.macro B9174_FIX_FINAL_SELECTION_COMPARE
.macro ldr dst, addr:vararg
.short 0x9B0A
.purgem ldr
.endm
.macro ldrb dst, addr:vararg
.short 0x7878
.purgem ldrb
.endm
.macro cmp lhs, rhs
.short 0x4283
.purgem cmp
.endm
.endm

.macro B9174_FIX_FIXED_PRICE_500
.set b9174_fixed_price_mov_fix, 0
.macro mov dst, src
.if b9174_fixed_price_mov_fix == 0
.short 0x21FA
.else
.short 0x4688
.purgem mov
.endif
.set b9174_fixed_price_mov_fix, b9174_fixed_price_mov_fix + 1
.endm
.macro lsl dst, args:vararg
.short 0x0049
.purgem lsl
.endm
.endm

.macro B9174_FIX_FINAL_SELECTION_STORE
.macro add dst, args:vararg
.short 0xAB0A
.purgem add
.endm
.macro ldrb dst, addr:vararg
.short 0x781B
.purgem ldrb
.endm
.macro strb src, addr:vararg
.short 0x707B
.purgem strb
.endm
.endm

.macro B9174_FIX_SECOND_MESSAGE_MONEY_CALL
.set b9174_second_message_mov_fix, 0
.macro mov dst, src
.if b9174_second_message_mov_fix == 0
.short 0x2101
.elseif b9174_second_message_mov_fix == 1
.short 0x2209
.else
.short 0x4642
.purgem mov
.endif
.set b9174_second_message_mov_fix, b9174_second_message_mov_fix + 1
.endm
.set b9174_second_message_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b9174_second_message_ldr_fix == 0
.short 0x6800
.elseif b9174_second_message_ldr_fix == 1
.short 0x481A
.else
.short 0x6810
.purgem ldr
.endif
.set b9174_second_message_ldr_fix, b9174_second_message_ldr_fix + 1
.endm
.endm

.macro B9174_FIX_THIRD_MESSAGE_MONEY_CALL
.set b9174_third_message_mov_fix, 0
.macro mov dst, src
.if b9174_third_message_mov_fix == 0
.short 0x2101
.elseif b9174_third_message_mov_fix == 1
.short 0x2209
.else
.short 0x4642
.purgem mov
.endif
.set b9174_third_message_mov_fix, b9174_third_message_mov_fix + 1
.endm
.set b9174_third_message_ldr_fix, 0
.macro ldr dst, addr:vararg
.if b9174_third_message_ldr_fix == 0
.short 0x6800
.elseif b9174_third_message_ldr_fix == 1
.short 0x4819
.else
.short 0x6810
.purgem ldr
.endif
.set b9174_third_message_ldr_fix, b9174_third_message_ldr_fix + 1
.endm
.endm
