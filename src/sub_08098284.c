#include "m2c_prelude.h"

u8 func_080ECD30(s32, s32);                         /* extern */
s32 func_080ECD98(s32, s32);                        /* extern */

void sub_08098284(s32 arg0, s32 arg1, s32 arg2, s32 arg3_raw) {
    s32 sp0;
    u8 *arg3;
    s32 prefix_store;
    s32 case_store;
    s32 case_mode;
    register u8 *var_r0_2 asm("r0");
    register s32 var_r2 asm("r2");
    register s32 var_r2_2 asm("r2");
    s32 temp_r0;
    s32 var_r6;
    s32 var_r7;
    s32 var_sl;
    u8 *var_r1;
    s8 var_r0;
    register s32 var_r0_3 asm("r0");
    u32 var_r4;
    u8 temp_r1;
    u8 temp_r1_2;
    u8 temp_r2;
    u8 temp_r8;
    u8 var_r3;

    var_r6 = arg0;
    arg3 = (u8 *)arg3_raw;
    temp_r1 = (u8)arg1;
    var_r3 = (u8)arg2;
    var_sl = 0x3B9ACA00;
    sp0 = 0;
    var_r4 = 0;
    if (4 & var_r3) {
        if (var_r6 > 0) {
            if (!(8 & var_r3)) {
                var_r2 = 0x7B81;
                goto block_11;
            }
            var_r0 = 0x2B;
            goto block_13;
        }
        if (var_r6 < 0) {
            if (!(8 & var_r3)) {
                *(u16 *)arg3 = 0x7C81;
            } else {
                var_r0 = 0x2D;
                goto block_13;
            }
        } else if (!(8 & var_r3)) {
            var_r2 = 0x7D81;
block_11:
            prefix_store = var_r2;
            asm volatile("" : "+&r"(prefix_store) : "r"(var_r2));
            *(u16 *)arg3 = prefix_store;
        } else {
            var_r0 = 0x20;
block_13:
            *arg3 = var_r0;
        }
        var_r4 = (u8)(var_r4 + 1);
    }
    if (var_r6 < 0) {
        var_r6 = 0 - var_r6;
    }
    var_r7 = 0;
    temp_r8 = 8 & var_r3;
    do {
        if (var_r7 >= (s32) (0xA - temp_r1)) {
            temp_r2 = func_080ECD30(var_r6, var_sl);
            if ((temp_r2 != 0) || (sp0 != 0) || (var_r7 == 9)) {
                if (temp_r8 == 0) {
                    *(u16 *)(arg3 + var_r4 * 2) = (temp_r2 << 8) + 0x4F82;
                } else {
                    *(arg3 + var_r4) = temp_r2 + 0x30;
                }
                var_r4 = (u32) (u8) (var_r4 + 1);
                var_r6 -= var_sl * temp_r2;
                temp_r2 = 1;
                asm volatile("" : "+r"(temp_r2));
                sp0 = temp_r2;
            } else {
                temp_r0 = 3 & var_r3;
                if (temp_r0 == 2)
                    goto switch_case_2;
                if (temp_r0 <= 2)
                    goto switch_end;
                if (temp_r0 == 3)
                    goto switch_case_3;
                goto switch_end;
switch_case_2:
                    case_mode = temp_r8;
                    asm volatile("" : "+r"(case_mode));
                    if (case_mode == 0) {
                        var_r0_2 = (u8 *)((s32)(var_r4 * 2) + (s32)arg3);
                        var_r2_2 = 0x4081;
                        goto block_36;
                    } else {
                        var_r1 = arg3 + var_r4;
                        var_r0_3 = 0x20;
                        goto block_38;
                    }
switch_case_3:
                    if (temp_r8 != 0)
                        goto switch_case_3_byte;
                    var_r0_2 = (u8 *)((s32)(var_r4 * 2) + (s32)arg3);
                    var_r2_2 = 0x4F82;
block_36:
                    case_store = var_r2_2;
                    asm volatile("" : "+&r"(case_store) : "r"(var_r2_2));
                    *(u16 *)var_r0_2 = case_store;
                    goto block_39;
switch_case_3_byte:
                    var_r1 = arg3 + var_r4;
                    var_r0_3 = 0x30;
block_38:
                    *var_r1 = var_r0_3;
block_39:
                    var_r4 = (u32) (u8) (var_r4 + 1);
switch_end:
                ;
            }
        }
        var_sl = func_080ECD98(var_sl, 0xA);
        var_r7 = (s32) (u8) (var_r7 + 1);
    } while ((u32) var_r7 <= 9U);
    if ((3 & var_r3) == 1) {
        if (!(8 & var_r3)) {
            if (var_r4 < (u32) temp_r1) {
                do {
                    *(u16 *)(arg3 + var_r4 * 2) = 0x4081;
                    var_r4 = (u32) (u8) (var_r4 + 1);
                } while (var_r4 < (u32) temp_r1);
            }
        } else if (var_r4 < (u32) temp_r1) {
            do {
                *(arg3 + var_r4) = 0x20;
                var_r4 = (u32) (u8) (var_r4 + 1);
            } while (var_r4 < (u32) temp_r1);
        }
    }
    temp_r1_2 = 8 & var_r3;
    if (temp_r1_2 == 0) {
        *((var_r4 * 2) + arg3) = temp_r1_2;
        return;
    }
    *(arg3 + var_r4) = 0;
}
