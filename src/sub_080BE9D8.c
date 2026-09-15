#include "m2c_prelude.h"

u8 func_080BF464(s32, s32, s32);                    /* extern */
s32 func_080E522C(s32, s32);                        /* extern */
extern u8 D_02034B4C[];
M2C_UNK jtbl_080BEAC8();                            /* static */
M2C_UNK jtbl_080BECC8();                            /* static */

#define RUN_LOOKUP(field_offset) do {                                      \
    register s32 call_value asm("r0") = (s16)var_r6;                       \
    register u8 *case_base asm("r3") = D_02034B4C;                         \
    register s32 case_col asm("r2") = temp_r7 * 0x270;                     \
    register s32 row_seed asm("r6") = temp_r0;                             \
    register s32 case_row asm("r1") = (row_seed * 4) + temp_r0;            \
    asm volatile("" : "+r"(call_value), "+r"(case_base),                 \
                 "+r"(case_col), "+r"(row_seed), "+r"(case_row));       \
    case_row = ((case_row * 8) - row_seed) * 0x80;                          \
    case_col += case_row;                                                   \
    case_col += (s32)case_base;                                             \
    case_col += (field_offset);                                             \
    var_r6 = func_080E522C(call_value, *(s16 *)case_col + 0x64);            \
} while (0)

#define BUILD_LOOKUP2(field_offset) do {                                   \
    register s32 call_value asm("r0") = (s16)var_r6;                       \
    register u8 *case_base asm("r3") = D_02034B4C;                         \
    register s32 case_col asm("r2") = temp_r7 * 0x270;                     \
    register s32 row_seed asm("r6") = temp_r0;                             \
    register s32 case_row asm("r1") = (row_seed * 4) + temp_r0;            \
    asm volatile("" : "+r"(call_value), "+r"(case_base),                 \
                 "+r"(case_col), "+r"(row_seed), "+r"(case_row));       \
    case_row = ((case_row * 8) - row_seed) * 0x80;                          \
    case_col += case_row;                                                   \
    case_col += (s32)case_base;                                             \
    case_col += (field_offset);                                             \
    lookup2_value = call_value;                                             \
    lookup2_address = (s16 *)case_col;                                      \
    goto block_30;                                                          \
} while (0)

void sub_080BE9D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                  s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    register s32 hold8 asm("r8") = arg8;
    register s32 hold9 asm("r9") = arg9;
    volatile s32 sp0;
    volatile s32 sp4;
    s32 sp8;
    s32 spC;
    s32 temp_r2;
    s32 var_r0_2;
    s32 var_r7;
    s32 lookup2_value;
    s16 *lookup2_address;
    u16 temp_r1;
    u32 temp_r1_2;
    u16 temp_r5;
    u16 var_r0;
    u16 var_r6;
    u32 temp_r0_3;
    u32 temp_r0_4;
    register s32 temp_r0 asm("sl");
    u8 temp_r7;
    u8 var_r3;
    void *temp_r0_2;
    void *var_r4;
    register u32 shared_mask_r7 asm("r7");
    register u32 shared_copy_r0 asm("r0");
    register u32 shared_zero_r2 asm("r2");
    register u32 shared_result_r1 asm("r1");
    register u32 case24_mask_r3 asm("r3");

    temp_r0 = (u8)arg0;
    temp_r7 = (u8)arg1;
    sp0 = (s32)(u8)arg2;
    sp4 = (s32)(u16)arg3;
    sp8 = (s32) (u8) arg5;
    temp_r5 = (u16) arg6;
    var_r6 = (u16) arg7;
    {
        register s32 normalized8 asm("r0") = hold8;
        asm volatile("" : "+r"(normalized8));
        spC = (s32)(u16)normalized8;
    }
    {
        register s32 normalized9 asm("r1") = hold9;
        asm volatile("" : "+r"(normalized9));
        temp_r1 = (u16)normalized9;
    }
    var_r3 = 0;
    {
        register s32 initial_row asm("r2") = temp_r0 * 0x1218;
        register s32 initial_col asm("r0") = temp_r7 * 0x304;
        register s32 initial_base asm("r1") = 0x0203C774;
        asm volatile("" : "+r"(initial_row), "+r"(initial_col),
                     "+r"(initial_base));
        initial_col += initial_base;
        temp_r2 = initial_row + initial_col;
    }
    var_r4 = temp_r2 + 4;
    goto loop_test;
loop_next:
    var_r3 += 1;
    if ((u32) var_r3 <= 0x1FU) {
        var_r4 = temp_r2 + ({
            register s32 record_offset asm("r0") = var_r3 * 0xC;
            asm volatile("" : "+r"(record_offset));
            record_offset += 4;
            record_offset;
        });
loop_test:
        if (M2C_FIELD(var_r4, u16 *, 4) != 0) {
            goto loop_next;
        }
    }
    if (var_r3 == 0x20) {
        return;
    }
    {
        register u8 *status_base asm("r2") = D_02034B4C;
        register s32 status_col asm("r0") = temp_r7 * 0x304;
        register s32 status_factor asm("r1") = 0x1218;
        register s32 status_row asm("r3") = temp_r0;
        asm volatile("" : "+r"(status_base), "+r"(status_col),
                     "+r"(status_factor), "+r"(status_row));
        asm volatile("mul %0, %1" : "+l"(status_row) : "l"(status_factor) : "cc");
        status_factor = status_row;
        asm volatile("" : "+r"(status_factor));
        status_col += status_factor;
        status_col += (s32)status_base;
        status_factor = 0x7C28;
        asm volatile("" : "+r"(status_factor));
        status_col += status_factor;
        temp_r0_2 = (void *)status_col;
    }
    {
        register u32 status_value asm("r2") = M2C_FIELD(temp_r0_2, u16 *, 0);
        register u32 status_one asm("r1") = 1;
        asm volatile("" : "+r"(status_value), "+r"(status_one));
        status_one |= status_value;
        M2C_FIELD(temp_r0_2, u16 *, 0) = (u16)status_one;
    }
    if (func_080BF464(temp_r0, temp_r7, 0x18) != 0xFF) {

    } else {
        temp_r0_3 = temp_r5 - 2;
        switch (temp_r0_3) {                        /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            RUN_LOOKUP(0xA4);
            break;
        case 6:                                     /* switch 1 */
            RUN_LOOKUP(0xA6);
            break;
        case 9:                                     /* switch 1 */
            RUN_LOOKUP(0xA8);
            break;
        case 14:                                    /* switch 1 */
            RUN_LOOKUP(0xAA);
            break;
        case 1:                                     /* switch 1 */
            RUN_LOOKUP(0xAC);
            break;
        }
    }
    if (func_080BF464(temp_r0, temp_r7, 0x17) != 0xFF) {
        switch (temp_r5) {                          /* switch 2; irregular */
        case 15:                                    /* switch 2 */
            BUILD_LOOKUP2(0xDC);
        case 11:                                    /* switch 2 */
            BUILD_LOOKUP2(0xDE);
        case 7:                                     /* switch 2 */
            BUILD_LOOKUP2(0xE0);
        case 9:                                     /* switch 2 */
            BUILD_LOOKUP2(0xE2);
        }
        goto block_31;
block_30:
        var_r6 = func_080E522C(lookup2_value, *lookup2_address + 0x64);
block_31:;
    }
    temp_r0_4 = ({
        register u32 format_mask asm("r0") = 0x38;
        register u32 format_flags asm("r1") = sp4;
        asm volatile("" : "+r"(format_mask));
        asm volatile("" : "+r"(format_flags));
        format_mask &= format_flags;
        format_mask;
    });
    switch (temp_r0_4) {                            /* switch 3; irregular */
    case 0:                                         /* switch 3 */
        M2C_FIELD(var_r4, u16 *, 4) = temp_r5;
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        if (({
            register u32 case0_mask asm("r0") = 2;
            register u32 case0_flags asm("r3") = sp4;
            asm volatile("" : "+r"(case0_mask));
            asm volatile("" : "+r"(case0_flags));
            case0_mask & case0_flags;
        })) {
            var_r0 = 0;
block_45:
            M2C_FIELD(var_r4, u16 *, 8) = var_r0;
        } else {
            asm volatile("" : : "g"(spC));
            asm volatile("mov r6, sp\n\tldrh r6, [r6, #12]\n\t"
                         "strh r6, [r4, #8]");
            asm volatile("");
        }
        break;
    case 8:                                         /* switch 3 */
        shared_mask_r7 = 0x2000;
        asm volatile("" : "+r"(shared_mask_r7));
        goto block_42;
    case 16: {                                      /* switch 3 */
        register u32 case16_mask asm("r0") = 0x4000;
        register u32 case16_copy asm("r1");
        register u32 case16_result asm("r0");
        asm volatile("" : "+r"(case16_mask));
        case16_copy = case16_mask;
        asm volatile("" : "+r"(case16_copy));
        case16_result = temp_r5;
        asm volatile("" : "+r"(case16_result));
        case16_result |= case16_copy;
        M2C_FIELD(var_r4, u16 *, 4) = (u16)case16_result;
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        {
            register u32 case16_tail asm("r1") = temp_r1;
            asm volatile("" : "+r"(case16_tail));
            M2C_FIELD(var_r4, u16 *, 8) = (u16)case16_tail;
        }
        asm volatile("");
        break;
    }
    case 24:                                        /* switch 3 */
        case24_mask_r3 = 0x6000;
        asm volatile("" : "+r"(case24_mask_r3));
        shared_copy_r0 = case24_mask_r3;
        asm volatile("" : "+r"(shared_copy_r0));
        goto block_43;
    case 32:                                        /* switch 3 */
        shared_mask_r7 = 0x8000;
        asm volatile("" : "+r"(shared_mask_r7));
block_42:
        shared_copy_r0 = shared_mask_r7;
        asm volatile("" : "+r"(shared_copy_r0));
block_43:
        shared_zero_r2 = 0;
        shared_result_r1 = temp_r5;
        asm volatile("" : "+r"(shared_zero_r2));
        asm volatile("" : "+r"(shared_result_r1));
        shared_result_r1 |= shared_copy_r0;
        M2C_FIELD(var_r4, u16 *, 4) = (u16)shared_result_r1;
        M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        M2C_FIELD(var_r4, u16 *, 8) = (u16)shared_zero_r2;
        break;
    case 40: {                                      /* switch 3 */
        {
            register u32 case40_mask asm("r1") = 0xA000;
            register u32 case40_copy asm("r0");
            register u32 case40_result asm("r1");
            asm volatile("" : "+r"(case40_mask));
            case40_copy = case40_mask;
            asm volatile("" : "+r"(case40_copy));
            case40_result = temp_r5;
            asm volatile("" : "+r"(case40_result));
            case40_result |= case40_copy;
            M2C_FIELD(var_r4, u16 *, 4) = (u16)case40_result;
            M2C_FIELD(var_r4, u16 *, 6) = var_r6;
        }
        {
            register s32 case40_input asm("r3") = temp_r1;
            register s32 case40_signed asm("r0");
            asm volatile("" : "+r"(case40_input));
            case40_signed = (s16)case40_input;
            asm volatile("" : "+r"(case40_signed));
            case40_signed = -case40_signed;
            M2C_FIELD(var_r4, u16 *, 8) = (u16)case40_signed;
        }
        break;
    }
    }
    temp_r1_2 = (({
        register u32 tail_mask asm("r0") = 0xF;
        register u32 tail_value asm("r6");
        asm volatile("" : "+r"(tail_mask));
        asm volatile("" : "=r"(tail_value) : "0"(sp0));
        tail_mask &= tail_value;
        tail_mask;
    }) << 8) | M2C_FIELD(var_r4, u16 *, 4);
    M2C_FIELD(var_r4, u16 *, 4) = temp_r1_2;
    temp_r7 = (u8)sp8;
    asm volatile("" : "+r"(temp_r7));
    if (temp_r7 != 0) {
        M2C_FIELD(var_r4, u16 *, 4) = (u16) (temp_r1_2 | 0x80);
    }
    M2C_FIELD(var_r4, s32 *, 0) = arg4;
}
