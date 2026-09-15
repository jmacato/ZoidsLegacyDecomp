#include "m2c_prelude.h"

M2C_UNK func_080ECD28(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
extern u8 D_02000000[];

void sub_08095864(void) {
    s32 sp0;
    s32 sp4;
    u32 sp8;
    s32 spC;
    register s16 *var_r9 asm("r9");
    register s32 var_r0 asm("r0");
    s32 var_r0_2;
    s32 var_r0_5;
    s32 var_r0_7;
    register s32 var_r1 asm("r1");
    register s32 var_r3 asm("r3");
    s32 temp_r0_3;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_6;
    register s32 var_r4 asm("r4");
    register s32 var_r5 asm("r5");
    register s32 var_r6 asm("r6");
    register s32 var_r8 asm("r8");
    register u16 *var_r1_2 asm("r1");
    register u32 temp_r0_4 asm("r0");
    register u32 var_ip_2 asm("ip");
    register u32 var_ip_3 asm("ip");
    register u32 var_r7_2 asm("r7");
    register u32 temp_r0_5 asm("r0");
    register u32 temp_r3 asm("r3");
    register u32 temp_r5_2 asm("r5");
    register u32 temp_r6 asm("r6");
    register u8 *var_r2 asm("r2");
    void *var_r2_2;
    register u16 *var_r2_3 asm("r2");
    register s16 *var_sl asm("sl");

    asm volatile("" : "=m"(sp0), "=m"(sp4), "=m"(sp8), "=m"(spC));
    {
        register u32 clear_index asm("ip") = 0;
        register s16 **shape_source asm("r7") = (s16 **)0x03005F0C;
        register u8 *screen_base asm("r6") = D_02000000;
        register u8 *page_select asm("r5") = (u8 *)0x03005F12;
        register u32 one asm("r4") = 1;
        register s32 empty asm("r3") = -1;
        asm volatile(
            "1:\n\t"
            "mov r1, ip\n\t"
            "lsl r2, r1, #3\n\t"
            "ldrb r0, [r5]\n\t"
            "mov r1, r4\n\t"
            "eor r1, r0\n\t"
            "lsl r0, r1, #2\n\t"
            "add r0, r1\n\t"
            "lsl r0, r0, #8\n\t"
            "add r2, r0\n\t"
            "add r2, r6\n\t"
            "str r3, [r2]\n\t"
            "mov r2, #1\n\t"
            "add ip, r2\n\t"
            "mov r0, ip\n\t"
            "cmp r0, #159\n\t"
            "bls 1b"
            : "+r"(clear_index)
            : "r"(shape_source), "r"(screen_base), "r"(page_select),
              "r"(one), "r"(empty)
            : "r0", "r1", "r2", "cc", "memory");
        shape_source = (s16 **)*shape_source;
        var_r9 = (s16 *)shape_source;
    }
    {
        register s16 *shape asm("r1") = var_r9;
        register s32 zero asm("r2") = 0;
        asm volatile("ldrsh %0, [%1, %2]"
            : "=r"(var_r0) : "r"(shape), "r"(zero));
        if (var_r0 == 0) {
            return;
        }
    }
loop_4:
    sp0 = 0xFF00FF00;
    {
        register M2C_UNK *call_arg0 asm("r0") = &sp0;
        register u32 call_arg1 asm("r1") = 0x02000A00;
        register u32 call_arg2 asm("r2") = 0x01000050;
        asm volatile("" : "+r"(call_arg0), "+r"(call_arg1), "+r"(call_arg2));
        func_080ECD28(call_arg0, call_arg1, call_arg2);
    }
    {
        register u32 zero asm("r4") = 0;
        asm volatile("" : "+r"(zero));
        var_ip_2 = zero;
    }
    {
        register s16 *shape asm("r7") = var_r9;
        register s32 zero asm("r1") = 0;
        asm volatile("ldrsh %0, [%1, %2]"
            : "=r"(var_r0) : "r"(shape), "r"(zero));
    }
    if (var_ip_2 >= (u32)var_r0) {
        goto raster_done;
    }
    {
        asm volatile(
            "mov r2, #2\n\t"
            "add r2, r9\n\t"
            "mov sl, r2"
            : "=r"(var_sl) : "r"(var_r9) : "r2");
    }
loop_7:
        var_r0 -= 1;
        asm volatile(
            "mov r7, #0\n\t"
            "cmp ip, r0\n\t"
            "bcs 1f\n\t"
            "mov r7, ip\n\t"
            "add r7, #1\n"
            "1:\n\t"
            "mov r4, sl\n\t"
            "mov r0, #0\n\t"
            "ldrsh r3, [r4, r0]\n\t"
            "mov r2, #2\n\t"
            "ldrsh r1, [r4, r2]\n\t"
            "lsl r0, r7, #2\n\t"
            "add r0, r9\n\t"
            "mov r4, #2\n\t"
            "ldrsh r5, [r0, r4]\n\t"
            "mov r7, #4\n\t"
            "ldrsh r4, [r0, r7]"
            : "+r"(var_r0), "=r"(var_r3), "=r"(var_r1),
              "=r"(var_r5), "=r"(var_r4)
            : "r"(var_ip_2), "r"(var_sl), "r"(var_r9)
            : "r2", "r7", "cc");
        if ((var_r3 == var_r5) && (var_r1 == var_r4)) {

        } else {
            var_r5 -= var_r3;
            var_r4 -= var_r1;
            if (var_r5 >= 0) {
                asm volatile(
                    "mov r0, #0\n\t"
                    "mov r8, r0"
                    : "=r"(var_r8) : : "r0");
            } else {
                var_r5 = 0 - var_r5;
                asm volatile(
                    "mov r2, #1\n\t"
                    "mov r8, r2"
                    : "=r"(var_r8) : : "r2");
            }
            if (var_r4 >= 0) {
                register s32 y_forward asm("r7") = 0;
                asm volatile("str r7, %0" : "=m"(sp4) : "r"(y_forward));
            } else {
                var_r4 = 0 - var_r4;
                sp4 = 1;
            }
            var_r6 = 0;
            if (var_r5 >= var_r4) {
                if (var_r4 == 0) {
                    if ((u32) var_r1 > 0x9FU) {

                    } else {
                        register s32 row_offset asm("r0") = var_r1 << 1;
                        register u8 *scratch_base asm("r1") = (u8 *)0x02000A00;
                        asm volatile("" : "+r"(row_offset), "+r"(scratch_base));
                        asm volatile("add r2, r0, r1"
                            : "=r"(var_r2) : "r"(row_offset), "r"(scratch_base));
                        asm volatile("mov r4, r8" : "=r"(var_r4) : "r"(var_r8));
                        if (var_r4 == 0) {
                            var_r0_2 = var_r3;
                            if ((s32) var_r0_2 < 0) {
                                var_r0_2 = 0;
                            } else if ((s32) var_r0_2 > 0xEF) {
                                var_r0_2 = 0xEF;
                            }
                            *(u16 *)var_r2 = (u16) (var_r0_2 << 8);
                            {
                                register s32 forward_end asm("r0") = var_r3 + var_r5;
                                asm volatile("" : "+&r"(forward_end), "+r"(var_r3));
                                var_r0_3 = forward_end;
                            }
                            if (var_r0_3 < 0) {
                                goto block_35;
                            }
                            asm volatile("" : : : "memory");
                            goto block_36;
                        }
                        var_r0_4 = var_r3 - var_r5;
                        if (var_r0_4 < 0) {
                            var_r0_4 = 0;
                        } else if (var_r0_4 > 0xEF) {
                            var_r0_4 = 0xEF;
                        }
                        *(u16 *)var_r2 = (u16) (var_r0_4 << 8);
                        {
                            register s32 final_x asm("r0") = var_r3;
                            asm volatile("" : "+r"(final_x));
                            var_r0_3 = final_x;
                        }
                        if (var_r0_3 < 0) {
block_35:
                            var_r0_3 = 0;
                        } else {
block_36:
                            if (var_r0_3 > 0xEF) {
                                var_r0_3 = 0xEF;
                            }
                        }
                        *(u16 *)var_r2 = (u16) ((var_r0_3 + 1) | *(u16 *)var_r2);
                    }
                } else {
                    {
                        register s32 row_offset asm("r0") = var_r1 << 1;
                        register u8 *scratch_base asm("r7") = (u8 *)0x02000A00;
                        asm volatile("" : "+r"(row_offset), "+r"(scratch_base));
                        asm volatile("add r2, r0, r7"
                            : "=r"(var_r2) : "r"(row_offset), "r"(scratch_base));
                    }
                    spC = 0;
                    if (var_r6 < var_r5) {
loop_40:
                        if ((u32) var_r1 <= 0x9FU) {
                            var_r0_5 = var_r3;
                            if ((s32) var_r0_5 < 0) {
                                var_r0_5 = 0;
                            } else if ((s32) var_r0_5 > 0xEF) {
                                var_r0_5 = 0xEF;
                            }
                            if ((s32) var_r0_5 < (s32) M2C_FIELD(var_r2, u8 *, 1)) {
                                M2C_FIELD(var_r2, u8 *, 1) = (u8) var_r0_5;
                            }
                            if ((s32) var_r0_5 >= (s32) M2C_FIELD(var_r2, u8 *, 0)) {
                                M2C_FIELD(var_r2, u8 *, 0) = (u8) (var_r0_5 + 1);
                            }
                        }
                        if (var_r8 == 0) {
                            var_r3 += 1;
                        } else {
                            var_r3 -= 1;
                        }
                        var_r6 += var_r4;
                        if (var_r6 >= var_r5) {
                            register s32 y_direction asm("r7") = sp4;
                            asm volatile("" : "+r"(y_direction));
                            if (y_direction == 0) {
                                if ((s32) var_r1 <= 0x9E) {
                                    var_r1 += 1;
                                    var_r2 += 2;
                                    goto block_58;
                                }
                            } else if ((s32) var_r1 > 0) {
                                var_r1 -= 1;
                                var_r2 -= 2;
block_58:
                                var_r6 -= var_r5;
                                goto block_59;
                            }
                        } else {
block_59:
                            temp_r0_3 = spC + 1;
                            spC = temp_r0_3;
                            if (temp_r0_3 >= var_r5) {

                            } else {
                                goto loop_40;
                            }
                        }
                    }
                }
            } else {
                var_r2_2 = (var_r1 * 2) + 0x02000A00;
                var_r0_6 = 0;
                goto steep_test;
steep_up:
                var_r1 += 1;
                var_r2_2 += 2;
                goto steep_after_y;
steep_down:
                if (var_r1 <= 0) {
                    goto segment_done;
                }
                var_r1 -= 1;
                var_r2_2 -= 2;
steep_after_y:
                var_r6 += var_r5;
                if (var_r6 >= var_r4) {
                    register s32 x_direction asm("r7") = var_r8;
                    asm volatile("" : "+r"(x_direction));
                    if (x_direction == 0) {
                        var_r3 += 1;
                    } else {
                        var_r3 -= 1;
                    }
                    var_r6 -= var_r4;
                }
                var_r0_6 = spC + 1;
steep_test:
                spC = var_r0_6;
                asm volatile("" : : : "memory");
                {
                    register s32 steep_count asm("r7") = spC;
                    if (steep_count >= var_r4) {
                        goto segment_done;
                    }
                }
                if ((u32) var_r1 <= 0x9FU) {
                    var_r0_7 = var_r3;
                    if ((s32) var_r0_7 < 0) {
                        var_r0_7 = 0;
                    } else if ((s32) var_r0_7 > 0xEF) {
                        var_r0_7 = 0xEF;
                    }
                    if ((s32) var_r0_7 < (s32) M2C_FIELD(var_r2_2, u8 *, 1)) {
                        M2C_FIELD(var_r2_2, u8 *, 1) = (u8) var_r0_7;
                    }
                    if ((s32) var_r0_7 >= (s32) M2C_FIELD(var_r2_2, u8 *, 0)) {
                        M2C_FIELD(var_r2_2, u8 *, 0) = (u8) (var_r0_7 + 1);
                    }
                }
                if (sp4 != 0) {
                    goto steep_down;
                }
                if (var_r1 <= 0x9E) {
                    goto steep_up;
                }
                goto segment_done;
            }
        }
segment_done:
        asm volatile(
            "mov r1, #4\n\t"
            "add sl, r1\n\t"
            "mov r2, #1\n\t"
            "add ip, r2"
            : "+r"(var_sl), "+r"(var_ip_2) : : "r1", "r2");
        asm volatile(
            "mov r4, r9\n\t"
            "mov r7, #0\n\t"
            "ldrsh r0, [r4, r7]"
            : "=r"(var_r0) : "r"(var_r9) : "r4", "r7");
        if (var_ip_2 < (u32) var_r0) {
            goto loop_7;
        }
raster_done:
    var_r1_2 = (u16 *)(D_02000000 + ((1 ^ *(u8 *)0x03005F12) * 0x500));
    var_r2_3 = (u16 *)0x02000A00;
    {
        register u32 zero asm("r0");
        register s16 *empty_interval asm("r4");
        asm volatile(
            "mov r0, #0\n\t"
            "mov ip, r0"
            : "=r"(zero), "=r"(var_ip_3));
        empty_interval = (s16 *)0xFFFF;
        asm volatile("" : "+r"(empty_interval));
        var_sl = empty_interval;
    }
merge_scanline:
    {
        var_r7_2 = 0;
        temp_r0_4 = M2C_FIELD(var_r2_3, u16 *, 0);
        temp_r3 = temp_r0_4;
        sp8 = var_ip_3 + 1;
        var_ip_3 = temp_r0_4;
        var_r8 = (s32)(var_r2_3 + 1);
        {
            register u32 invalid_interval asm("r4") = 0xFF00;
            if ((temp_r3 != invalid_interval) && (temp_r3 != 1) && (temp_r3 != 0xEFF0)) {
            if (*var_r1_2 == (u32)var_sl) {
                asm volatile(
                    "mov r0, ip\n\t"
                    "strh r0, %0"
                    : "=m"(*var_r1_2) : "r"(var_ip_3) : "r0");
                goto merge_done;
            }
            goto merge_values;
merge_word:
            asm volatile(
                "mov r2, ip\n\t"
                "strh r2, %0"
                : "=m"(*var_r1_2) : "r"(var_ip_3) : "r2");
            goto merge_done;
merge_low:
            M2C_FIELD(var_r1_2, u8 *, 0) = temp_r3;
            goto merge_done;
merge_high:
            M2C_FIELD(var_r1_2, u8 *, 1) = temp_r6;
            goto merge_done;
merge_values:
loop_96:
                temp_r6 = M2C_FIELD(var_r2_3, u8 *, 1);
                temp_r5_2 = M2C_FIELD(var_r1_2, u8 *, 1);
                var_r4 = temp_r6;
                temp_r3 = M2C_FIELD(var_r2_3, u8 *, 0);
                temp_r0_5 = M2C_FIELD(var_r1_2, u8 *, 0);
                if ((temp_r5_2 > (u32)var_r4) || (temp_r3 > temp_r0_5)) {
                    if (((u32)var_r4 > temp_r5_2) || (temp_r0_5 > temp_r3)) {
                        if (((u32)var_r4 > temp_r0_5) || (temp_r3 <= temp_r0_5)) {
                            if ((temp_r3 < temp_r5_2) || ((u32)var_r4 >= temp_r5_2)) {
                                var_r1_2 += 1;
                                var_r7_2 += 1;
                                if (var_r7_2 <= 1U) {
                                    if (*var_r1_2 == (u32)var_sl) {
                                        asm volatile(
                                            "mov r4, ip\n\t"
                                            "strh r4, %0"
                                            : "=m"(*var_r1_2) : "r"(var_ip_3) : "r4");
                                    } else {
                                        goto loop_96;
                                    }
                                }
                            } else {
                                goto merge_high;
                            }
                        } else {
                            goto merge_low;
                        }
                    } else {
                        goto merge_word;
                    }
                }
        }
        }
merge_done:
        var_r1_2 = (u16 *)((u8 *)var_r1_2 + ((4 - var_r7_2) * 2));
        var_r2_3 = (u16 *)var_r8;
        {
            register u32 next_row asm("r7") = sp8;
            register u32 row_test asm("r0");
            var_ip_3 = next_row;
            asm volatile("mov %0, ip" : "=r"(row_test));
            if (row_test <= 0x9F) {
                goto merge_scanline;
            }
        }
    }
    asm volatile(
        "mov r1, r9\n\t"
        "mov r2, #0\n\t"
        "ldrsh r0, [r1, r2]"
        : "=r"(var_r0) : "r"(var_r9) : "r1", "r2");
    var_r0 <<= 2;
    var_r0 += 2;
    var_r9 = (s16 *)((u8 *)var_r9 + var_r0);
    asm volatile(
        "mov r4, r9\n\t"
        "mov r7, #0\n\t"
        "ldrsh r0, [r4, r7]"
        : "=r"(var_r0) : "r"(var_r9) : "r4", "r7");
    if (var_r0 != 0) {
        goto loop_4;
    }
}
