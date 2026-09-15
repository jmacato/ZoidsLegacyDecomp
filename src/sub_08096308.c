#include "m2c_prelude.h"

/* Deterministically repaired m2c baseline. */
M2C_UNK func_080954D8(M2C_UNK, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080955A0(M2C_UNK, M2C_UNK, s32, s32);  /* extern */
M2C_UNK func_080955F4(s32, s32, s32);               /* extern */
M2C_UNK func_0809564C(u32, s32, s32);               /* extern */
M2C_UNK func_080956B4(s32, s32, s32);               /* extern */
M2C_UNK func_08096774();                            /* extern */

asm(".set sub_08096308_state70, 0x03005F70\n"
    ".set sub_08096308_state72, 0x03005F72\n"
    ".set sub_08096308_state7A, 0x03005F7A\n"
    ".set sub_08096308_state7B, 0x03005F7B\n"
    ".set sub_08096308_state71_a, 0x03005F71\n"
    ".set sub_08096308_state71_b, 0x03005F71\n"
    ".set sub_08096308_state71_c, 0x03005F71");
extern u8 sub_08096308_state70;
extern s8 sub_08096308_state72;
extern s8 sub_08096308_state7A;
extern s8 sub_08096308_state7B;
extern u8 sub_08096308_state71_a;
extern u8 sub_08096308_state71_b;
extern u8 sub_08096308_state71_c;

void sub_08096308(s32 arg0, s32 arg1) {
    s32 temp_r1;
    s32 temp_r1_3;
    s32 temp_r1_6;
    s32 temp_r2_2;
    s32 temp_r2_4;
    s32 var_r1;
    s32 var_r3;
    s32 var_r4;
    s8 temp_r0_2;
    s8 temp_r0_3;
    s8 temp_r1_5;
    s8 temp_r2_6;
    s8 temp_r3;
    s8 temp_r3_2;
    u16 var_r6;
    s32 temp_r2;
    u32 var_r0_2;
    u8 *var_r7;
    u8 *record_base;
    register u32 palette_zero asm("ip");
    register u32 normalized_arg1 asm("r1");
    u32 palette_mask;
    u32 palette_one;
    u8 temp_r0;
    u8 temp_r1_2;
    u8 temp_r4;
    u8 var_r0;
    u32 saved_arg1;
    void *temp_r0_4;
    void *temp_r1_4;
    void *temp_r1_7;
    void *temp_r2_3;
    void *temp_r2_5;
    u8 *high_dest;

    temp_r0 = arg0;
    normalized_arg1 = (u8)arg1;
    saved_arg1 = normalized_arg1;
    sub_08096308_state70 = (normalized_arg1 = temp_r0);
    asm volatile("" : "+r"(temp_r0));
    sub_08096308_state72 = 0;
    temp_r2 = 0x3F & temp_r0;
    temp_r0 = temp_r2;
    if (temp_r2 > 4U) {
        goto high_dispatch;
    }
    temp_r1_2 = 0x40 & normalized_arg1;
    if (temp_r1_2 == 0) {
        switch (temp_r2) {                          /* irregular */
        case 1:
            *(s16 *)0x03000052 = 0x10;
            goto block_14;
        case 2:
            *(s16 *)0x03000052 = (s16) temp_r1_2;
block_14:
            *(s16 *)0x0300004E = 0xFF;
            break;
        case 3:
            *(s16 *)0x03000052 = 0x10;
            goto block_17;
        case 4:
            *(s16 *)0x03000052 = (s16) temp_r1_2;
block_17:
            *(s16 *)0x0300004E = 0xBF;
            break;
        }
    } else {
        var_r7 = (u8 *)0x05000000;
        var_r6 = 0;
        record_base = (u8 *)0x02000F40;
        palette_zero = var_r6;
        palette_mask = 0x1F;
        palette_one = 1;
        do {
            {
                register s32 dispatch_mode asm("r0") = temp_r0;
                asm volatile("" : "+r"(dispatch_mode));
                if (dispatch_mode == 2) {
                    goto palette_case2;
                }
                if (dispatch_mode > 2) {
                    goto palette_high_dispatch;
                }
                if (dispatch_mode == 1) {
                    goto palette_case1;
                }
palette_default_low:
                var_r3 = var_r6 * 2;
                goto palette_common;
palette_high_dispatch:
                if (temp_r0 == 3) {
                    goto palette_case3;
                }
                if (temp_r0 == 4) {
                    goto palette_case4;
                }
palette_default_high:
                asm volatile("" : : "r"(dispatch_mode));
                var_r3 = var_r6 * 2;
                goto palette_common;
            }
palette_case1:
            var_r3 = var_r6 * 2;
            temp_r1_3 = var_r6 * 0xC;
            temp_r1_4 = temp_r1_3 + record_base;
            M2C_FIELD(temp_r1_4, s8 *, 0xB) = palette_zero;
            M2C_FIELD(temp_r1_4, s8 *, 7) = palette_zero;
            M2C_FIELD(temp_r1_4, s8 *, 3) = palette_zero;
            M2C_FIELD(temp_r1_4, s8 *, 0) = (s8) (palette_mask & *var_r7);
            M2C_FIELD(temp_r1_4, s8 *, 4) = (s8) ((*(u16 *)var_r7 >> 5) & palette_mask);
            M2C_FIELD(temp_r1_4, s8 *, 8) = (s8) ((*(u16 *)var_r7 >> 0xA) & palette_mask);
            M2C_FIELD(temp_r1_4, s8 *, 1) = palette_zero;
            M2C_FIELD(temp_r1_4, s8 *, 5) = palette_zero;
            M2C_FIELD(temp_r1_4, s8 *, 9) = palette_zero;
            goto palette_common;

palette_case2:
            var_r4 = var_r6 * 2;
            asm volatile("" : "+r"(var_r4));
            temp_r1_6 = var_r4 + var_r6;
            temp_r1_6 *= 4;
            temp_r1_7 = temp_r1_6 + record_base;
            temp_r3_2 = palette_mask & *var_r7;
            M2C_FIELD(temp_r1_7, s8 *, 3) = temp_r3_2;
            temp_r2_6 = (*(u16 *)var_r7 >> 5) & palette_mask;
            M2C_FIELD(temp_r1_7, s8 *, 7) = temp_r2_6;
            temp_r0_3 = (*(u16 *)var_r7 >> 0xA) & palette_mask;
            M2C_FIELD(temp_r1_7, s8 *, 0xB) = temp_r0_3;
            M2C_FIELD(temp_r1_7, s8 *, 0) = temp_r3_2;
            M2C_FIELD(temp_r1_7, s8 *, 4) = temp_r2_6;
            M2C_FIELD(temp_r1_7, s8 *, 8) = temp_r0_3;
            M2C_FIELD(temp_r1_7, s8 *, 1) = palette_one;
            M2C_FIELD(temp_r1_7, s8 *, 5) = palette_one;
            M2C_FIELD(temp_r1_7, s8 *, 9) = palette_one;
            goto palette_copy_r4;

palette_case3:
            var_r3 = var_r6 * 2;
            temp_r2_4 = var_r6 * 0xC;
            temp_r2_5 = temp_r2_4 + record_base;
            M2C_FIELD(temp_r2_5, s8 *, 0xB) = palette_mask;
            M2C_FIELD(temp_r2_5, s8 *, 7) = palette_mask;
            M2C_FIELD(temp_r2_5, s8 *, 3) = palette_mask;
            M2C_FIELD(temp_r2_5, s8 *, 0) = (s8) (palette_mask & ~*var_r7);
            M2C_FIELD(temp_r2_5, s8 *, 4) = (s8) (palette_mask & ~(*(u16 *)var_r7 >> 5));
            M2C_FIELD(temp_r2_5, s8 *, 8) = (s8) (palette_mask & ~(*(u16 *)var_r7 >> 0xA));
            M2C_FIELD(temp_r2_5, s8 *, 1) = palette_one;
            M2C_FIELD(temp_r2_5, s8 *, 5) = palette_one;
            M2C_FIELD(temp_r2_5, s8 *, 9) = palette_one;
            goto palette_common;

palette_case4:
            var_r4 = var_r6 * 2;
            temp_r2_2 = var_r6 * 0xC;
            temp_r2_3 = temp_r2_2 + record_base;
            temp_r3 = palette_mask & *var_r7;
            M2C_FIELD(temp_r2_3, s8 *, 3) = temp_r3;
            temp_r1_5 = (*(u16 *)var_r7 >> 5) & palette_mask;
            M2C_FIELD(temp_r2_3, s8 *, 7) = temp_r1_5;
            temp_r0_2 = (*(u16 *)var_r7 >> 0xA) & palette_mask;
            M2C_FIELD(temp_r2_3, s8 *, 0xB) = temp_r0_2;
            M2C_FIELD(temp_r2_3, s8 *, 0) = (s8) (palette_mask - temp_r3);
            M2C_FIELD(temp_r2_3, s8 *, 4) = (s8) (palette_mask - temp_r1_5);
            M2C_FIELD(temp_r2_3, s8 *, 8) = (s8) (palette_mask - temp_r0_2);
            M2C_FIELD(temp_r2_3, s8 *, 1) = palette_zero;
            M2C_FIELD(temp_r2_3, s8 *, 5) = palette_zero;
            M2C_FIELD(temp_r2_3, s8 *, 9) = palette_zero;
palette_copy_r4:
            var_r3 = var_r4;
palette_common:
            temp_r0_4 = ((var_r3 + var_r6) * 4) + record_base;
            M2C_FIELD(temp_r0_4, s8 *, 0xA) = palette_zero;
            M2C_FIELD(temp_r0_4, s8 *, 6) = palette_zero;
            M2C_FIELD(temp_r0_4, s8 *, 2) = palette_zero;
            var_r7 += 2;
            var_r6 += 1;
            asm volatile("" : "+r"(var_r6));
        } while ((u32) var_r6 <= 0x1FFU);
        goto palette_done;
    }
palette_done:
    asm volatile("" : "=r"(saved_arg1) : "0"((u8)saved_arg1));
    *(u8 *)0x03005F71 = saved_arg1;
    return;

high_dispatch:
    if (temp_r2 > 0x10U) {
        goto high_over16;
    }
    if ((u32) (u8) (temp_r2 - 5) <= 1U) {
        if (temp_r2 == 5) {
            func_080955F4(0x3F3F, 0, 8);
            *(s16 *)0x0300004E = 0;
        } else {
            func_080955F4(0, 0x3F, 8);
        }
        high_dest = &sub_08096308_state71_a;
        var_r0 = 0x21;
        goto high_store;
    }
    if ((u32) (u8) (temp_r2 - 7) <= 1U) {
        if (temp_r2 == 7) {
            register u32 base7 asm("r0") = 0x087ED854;
            register u32 off7 asm("r2") = 0xA0;
            asm volatile("" : "+r"(off7));
            func_080954D8(base7, 0, 0, base7 + (off7 << 2), 0, 0, 0x3F3F, 0, 8);
            *(s16 *)0x0300004E = 0;
        } else {
            register u32 base8 asm("r0") = 0x087ED854;
            register u32 off8 asm("r1") = 0xA0;
            asm volatile("" : "+r"(off8));
            func_080954D8(base8, 0, 0, base8 + (off8 << 2), 0, 0, 0, 0x3F, 8);
        }
        high_dest = &sub_08096308_state71_b;
        var_r0 = 0x24;
        goto high_store;
    }
    temp_r4 = temp_r2 - 9;
    if ((u32) temp_r4 <= 3U) {
        var_r0_2 = 0;
        if (temp_r2 != 9) {
            temp_r1 = 0xB ^ temp_r2;
            var_r0_2 = (u32) ((0 - temp_r1) | temp_r1) >> 0x1F;
        }
        var_r1 = 0;
        if ((u32) temp_r4 > 1U) {
            var_r1 = 1;
        }
        func_0809564C(var_r0_2, var_r1, 8);
        if ((u32) temp_r4 > 1U) {
            goto high_twenty;
        }
high_zero:
        *(s16 *)0x0300004E = 0;
        goto high_twenty;
    }
    if ((u32) (u8) (temp_r2 - 0xD) <= 1U) {
        if (temp_r2 == 0xD) {
            func_080955A0(0x03006020, 0x3F3F, 0, 8);
            goto high_zero;
        } else {
            func_080955A0(0x03006020, 0x3F3F, 0, 8);
        }
high_twenty:
        high_dest = &sub_08096308_state71_c;
        var_r0 = 0x20;
high_store:
        *high_dest = var_r0;
    }
    if ((u32) (u8) (temp_r0 - 0xF) <= 1U) {
        register u32 mode15 asm("r2") = temp_r0;
        asm volatile("" : "+r"(mode15));
        if (mode15 == 0xF) {
            func_080956B4(0x3F3F, 0, 8);
            *(s16 *)0x0300004E = 0;
        } else {
            func_080956B4(0, 0x3F, 8);
        }
        *(u8 *)0x03005F71 = 0x14U;
    }
    *(s16 *)0x05000000 = 0;
    return;

high_over16:
    if (temp_r0 == 0x11) {
        *(s16 *)0x0300004E = 0;
    }
    *(u8 *)0x03005F71 = 0x1C;
    sub_08096308_state7A = 0;
    sub_08096308_state7B = 1;
    func_08096774();
}
