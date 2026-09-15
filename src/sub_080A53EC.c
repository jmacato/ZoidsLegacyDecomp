#include "m2c_prelude.h"
s32 func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08098248(M2C_UNK, s32, s32);           /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A1F8(u8, u8, s32, s32, s32, s32);  /* extern */
M2C_UNK func_0809A5B4(u8, u8, s32, s32, s32);       /* extern */
M2C_UNK func_0809A94C(u8, s32, u8, s32, s32);       /* extern */
M2C_UNK func_080A016C(s32, s32, s32);               /* extern */
M2C_UNK func_080BB224(s32, u8, s32, s32);           /* extern */
s32 func_080BB654();                                /* extern */
s32 func_080C0C54(s32, s32, s32);                   /* extern */
M2C_UNK func_080C2DB0();                            /* extern */
M2C_UNK func_080C2DD0(u8);                          /* extern */
M2C_UNK func_080C3050(u8);                          /* extern */
M2C_UNK func_080D0AF0(s32);                         /* extern */
M2C_UNK func_080D0F94(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_080D120C();                            /* extern */
s32 func_080D1C18();                                /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */
M2C_UNK jtbl_080A5444();                            /* static */
extern u8 D_020218E4[];

struct TailMetadata {
    u8 pad0[2];
    u8 value;
    u8 pad3[0x35];
};

extern struct TailMetadata D_087AFCC4[];

s32 sub_080A53EC(u8 arg0, void **arg1) {
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    void *sp38;
    s32 temp_r2_10;
    s32 temp_r2_7;
    s32 temp_r2_8;
    s32 temp_r3_4;
    s32 temp_r3_7;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r3_2;
    register s32 var_r6 asm("r6");
    register s32 var_r6_2 asm("r6");
    register s32 var_r8_2 asm("r8");
    register s32 var_r9 asm("r9");
    register s32 var_r9_2 asm("r9");
    register s32 var_sl asm("r10");
    s32 temp_r3_2;
    s32 temp_r3_5;
    register s32 temp_r6 asm("r6");
    register s32 temp_r6_2 asm("r6");
    register s32 var_r6_3 asm("r6");
    register s32 var_r6_4 asm("r6");
    register s32 var_r8 asm("r8");
    register s32 var_r8_3 asm("r8");
    u32 temp_r0;
    register s32 var_r8_4 asm("r8");
    register s32 var_r8_5 asm("r8");
    register u32 var_r8_6 asm("r8");
    register u32 var_r8_7 asm("r8");
    u8 temp_r1_2;
    u8 var_r2;
    u8 var_r5;
    void *temp_r1;
    void *temp_r2;
    s32 temp_r2_11;
    void *temp_r2_2;
    void *temp_r2_3;
    void *temp_r2_4;
    void *temp_r2_5;
    void *temp_r2_6;
    s32 temp_r2_9;
    void *temp_r3;
    void *temp_r3_3;
    void *temp_r3_6;
    void *temp_r4;
    void *temp_r4_2;
    u8 *var_r3;
    u8 *var_r3_3;
    register void *var_r3_4 asm("r3");
    register void *var_r3_5 asm("r3");
    void *var_r4;
    void *var_r4_2;
    register void *var_r4_3 asm("r4");
    register void *var_r4_4 asm("r4");
    register void *var_r4_5 asm("r4");
    register void *var_r9_3 asm("r9");
    register void *var_r9_4 asm("r9");
    void *var_r9_5;
    void *var_r9_6;
    register void *var_r2_12 asm("r2");
    register s32 var_r8_8 asm("r8");

    sp14 = (s32) arg0;
    func_080BB224(2, M2C_FIELD(*arg1, u8 *, 3), 0, 0);
    while ((func_080BB654() << 0x18) == 0) {
        func_080ED17C(1);
    }
    func_080C2DB0();
    var_sl = 0;
    temp_r0 = M2C_FIELD(*arg1, u8 *, 1) - 0x47;
    switch (temp_r0) {
    case 0x0:
        var_r8 = 0;
        var_r3 = (void *)0x02034B4C;
        var_r9 = 0x750;
        var_r6 = 0;
        var_r4 = (void *)0x02032F7C;
        do {
            if (func_080C0C54(4, M2C_FIELD(*arg1, u8 *, 3), var_r8) != 0) {
                M2C_FIELD(var_r4, u8 *, 0) = 0xFF;
                M2C_FIELD(var_r4, s8 *, 3) = var_r8;
                temp_r2 = *arg1;
                {
                    s32 case0_address = M2C_FIELD(temp_r2, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case0_address)
                        : "r"(var_r6)
                        : "cc");
                    case0_address += (s32)var_r3;
                    M2C_FIELD((void *)case0_address, u8 *, 0) = M2C_FIELD(temp_r2, u8 *, 1);
                }
                {
                    s32 case0_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    case0_address += var_r9;
                    case0_address += (s32)var_r3;
                    M2C_FIELD((void *)case0_address, s8 *, 0) = 0;
                }
                {
                    s32 case0_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case0_address)
                        : "r"(var_r6)
                        : "cc");
                    case0_address += (s32)var_r3;
                    var_r5 = M2C_FIELD((void *)case0_address, u8 *, 1);
                }
                {
                    register s32 success_r2 asm("r2") = 1;
                    asm volatile("" : "+r"(success_r2));
                    var_sl = success_r2;
                }
            }
            var_r9 += 0x270;
            var_r6 += 0x270;
            var_r4 += 1;
            var_r8 += 1;
        } while ((u32) var_r8 <= 2U);
        goto block_71;
    case 0x2F:
        var_r8_3 = 0;
        var_r3_3 = (void *)0x02034B4C;
        var_r9_2 = 0x750;
        var_r6_2 = 0;
        var_r4_2 = (void *)0x02032F7C;
        do {
            if (func_080C0C54(5, M2C_FIELD(*arg1, u8 *, 3), var_r8_3) != 0) {
                M2C_FIELD(var_r4_2, u8 *, 0) = 0xFF;
                M2C_FIELD(var_r4_2, s8 *, 3) = var_r8_3;
                temp_r2_2 = *arg1;
                {
                    s32 case2f_address = M2C_FIELD(temp_r2_2, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case2f_address)
                        : "r"(var_r6_2)
                        : "cc");
                    case2f_address += (s32)var_r3_3;
                    M2C_FIELD((void *)case2f_address, u8 *, 0) = M2C_FIELD(temp_r2_2, u8 *, 1);
                }
                {
                    s32 case2f_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    case2f_address += var_r9_2;
                    case2f_address += (s32)var_r3_3;
                    M2C_FIELD((void *)case2f_address, s8 *, 0) = 0;
                }
                {
                    s32 case2f_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case2f_address)
                        : "r"(var_r6_2)
                        : "cc");
                    case2f_address += (s32)var_r3_3;
                    var_r5 = M2C_FIELD((void *)case2f_address, u8 *, 1);
                }
                {
                    register s32 success_guard_r0 asm("r0");
                    register s32 success_guard_r1 asm("r1");
                    asm volatile("" : "=&r"(success_guard_r0), "=&r"(success_guard_r1));
                    var_sl = 1;
                    asm volatile("" : : "r"(success_guard_r0), "r"(success_guard_r1));
                }
            }
            var_r9_2 += 0x270;
            var_r6_2 += 0x270;
            var_r4_2 += 1;
            {
                register s32 case2f_step_r1 asm("r1") = 1;
                asm volatile("" : "+r"(case2f_step_r1));
                var_r8_3 += case2f_step_r1;
            }
        } while ((u32) ({
            register u32 case2f_compare_r2 asm("r2") = var_r8_3;
            asm volatile("" : "+r"(case2f_compare_r2));
            case2f_compare_r2;
        }) <= 2U);
        goto block_71;
    case 0x39:
        var_r8_4 = 0;
        var_r9_3 = (void *)0x02032F7C;
        asm volatile("" : "+r"(var_r9_3));
        var_r4_3 = (void *)0x02034B4C;
        sp28 = 0xC30;
        sp2C = 0x9C0;
        sp30 = 0x4E0;
        sp34 = 0x270;
        var_r3_4 = var_r9_3 + 1;
        asm volatile("" : : "r"(var_r3_4));
loop_18:
        {
            register s32 selector_seed_r0 asm("r0") = 1;
            register s32 selector_index_r1 asm("r1") = var_r8_4;
            temp_r6 = selector_seed_r0 - selector_index_r1;
        }
        {
            s32 case39_result;
            register s32 case39_arg0 asm("r0");
            register s32 case39_arg1 asm("r1");
            register s32 case39_arg2 asm("r2");
            case39_arg1 = M2C_FIELD(*arg1, u8 *, 3);
            case39_arg0 = 1;
            case39_arg2 = temp_r6;
            asm volatile("str r3, [sp, #56]" : : "r"(case39_arg0), "r"(case39_arg1), "r"(case39_arg2) : "memory");
            case39_result = func_080C0C54(case39_arg0, case39_arg1, case39_arg2);
            asm volatile("ldr r3, [sp, #56]" : : : "memory");
        if (case39_result == 0) {

        } else {
            if (temp_r6 == 0) {
                {
                    register s32 status_r0 asm("r0");
                    register s32 status_r1 asm("r1");
                    register void *status_r2 asm("r2");
                    status_r0 = 1;
                    status_r2 = var_r9_3;
                    M2C_FIELD(status_r2, s8 *, 0) = status_r0;
                    status_r0 = 0xFF;
                    M2C_FIELD(status_r2, u8 *, 1) = status_r0;
                    status_r1 = 1;
                    M2C_FIELD(status_r2, s8 *, 3) = status_r1;
                    M2C_FIELD(status_r2, s8 *, 4) = status_r1;
                }
                M2C_FIELD(var_r4_3, s8 *, M2C_FIELD(*arg1, u8 *, 3) * 0x1380) = temp_r6;
                temp_r2_3 = *arg1;
                {
                    s32 case39_addr = (M2C_FIELD(temp_r2_3, u8 *, 3) * 0x1380) + 0x270;
                    M2C_FIELD((void *)case39_addr, u8 *, (s32)var_r4_3) = (u8) M2C_FIELD(temp_r2_3, u8 *, 1);
                }
                {
                    s32 case39_addr = (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0x750;
                    M2C_FIELD((void *)case39_addr, s8 *, (s32)var_r4_3) = temp_r6;
                }
                {
                    s32 case39_addr = (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0x9C0;
                    M2C_FIELD((void *)case39_addr, s8 *, (s32)var_r4_3) = temp_r6;
                }
                {
                    s32 final_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 final_offset_r2 asm("r2");
                    asm volatile("mov r2, #156\n\tlsl r2, r2, #2" : "=r"(final_offset_r2));
                    var_r0 = final_address + final_offset_r2;
                }
            } else {
                M2C_FIELD(var_r3_4, u8 *, 0) = 0xFF;
                M2C_FIELD(var_r3_4, s8 *, 1) = temp_r6;
                M2C_FIELD(var_r3_4, s8 *, 3) = temp_r6;
                M2C_FIELD(var_r3_4, s8 *, 4) = temp_r6;
                temp_r2_4 = *arg1;
                {
                    s32 case39_address = M2C_FIELD(temp_r2_4, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case39_address)
                        : "r"(sp34)
                        : "cc");
                    case39_address += (s32)var_r4_3;
                    M2C_FIELD((void *)case39_address, u8 *, 0) = (u8) M2C_FIELD(temp_r2_4, u8 *, 1);
                }
                {
                    s32 case39_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case39_address)
                        : "r"(sp30)
                        : "cc");
                    case39_address += (s32)var_r4_3;
                    {
                        register s32 zero_r1 asm("r1") = 0;
                        M2C_FIELD((void *)case39_address, s8 *, 0) = zero_r1;
                    }
                }
                {
                    s32 case39_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 case39_reload_guard_r1 asm("r1");
                    asm volatile("" : "=r"(case39_reload_guard_r1));
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case39_address)
                        : "r"(sp2C), "r"(case39_reload_guard_r1)
                        : "cc");
                    case39_address += (s32)var_r4_3;
                    {
                        register s32 zero_r1 asm("r1") = 0;
                        M2C_FIELD((void *)case39_address, s8 *, 0) = zero_r1;
                    }
                }
                {
                    s32 case39_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 case39_third_guard_r1 asm("r1");
                    asm volatile("" : "=r"(case39_third_guard_r1));
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case39_address)
                        : "r"(sp28), "r"(case39_third_guard_r1)
                        : "cc");
                    case39_address += (s32)var_r4_3;
                    {
                        register s32 zero_r1 asm("r1") = 0;
                        M2C_FIELD((void *)case39_address, s8 *, 0) = zero_r1;
                    }
                }
                {
                    s32 case39_final_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 case39_final_guard_r1 asm("r1");
                    asm volatile("" : "=r"(case39_final_guard_r1));
                    asm volatile("add %0, %1, %0"
                                 : "+l"(case39_final_address)
                                 : "r"(sp34), "r"(case39_final_guard_r1)
                                 : "cc");
                    var_r0 = case39_final_address;
                }
            }
            var_r5 = M2C_FIELD(var_r4_3, u8 *, var_r0 + 1);
            {
                register s32 case39_success_r0 asm("r0") = 1;
                asm volatile("" : "+r"(case39_success_r0));
                var_sl = case39_success_r0;
            }
        }
        }
        {
            register s32 first_backedge_value_r1 asm("r1") = sp28;
            register s32 backedge_delta_r2 asm("r2") = 0xFFFFFD90;
            asm volatile("" : "+r"(backedge_delta_r2));
            first_backedge_value_r1 += backedge_delta_r2;
            sp28 = first_backedge_value_r1;
            sp2C += backedge_delta_r2;
            sp30 += backedge_delta_r2;
            sp34 += backedge_delta_r2;
        }
        var_r3_4 -= 1;
        asm volatile("" : "+r"(var_r3_4));
        var_r8_4 += 1;
        if (var_r8_4 <= 1U) {
            goto loop_18;
        }
        goto block_71;
    case 0x3A:
        var_r8_5 = 0;
        var_r9_4 = (void *)0x02032F7C;
        asm volatile("" : "+r"(var_r9_4));
        var_r4_4 = (void *)0x02034B4C;
        sp18 = 0xC30;
        sp1C = 0x9C0;
        sp20 = 0x4E0;
        sp24 = 0x270;
        var_r3_5 = var_r9_4 + 1;
        asm volatile("" : : "r"(var_r3_5));
loop_29:
        {
            register s32 selector_seed_r0 asm("r0") = 1;
            register s32 selector_index_r1 asm("r1") = var_r8_5;
            temp_r6_2 = selector_seed_r0 - selector_index_r1;
        }
        {
            s32 case3a_result;
            register s32 case3a_arg0 asm("r0");
            register s32 case3a_arg1 asm("r1");
            register s32 case3a_arg2 asm("r2");
            case3a_arg1 = M2C_FIELD(*arg1, u8 *, 3);
            case3a_arg0 = 2;
            case3a_arg2 = temp_r6_2;
            asm volatile("str r3, [sp, #56]" : : "r"(case3a_arg0), "r"(case3a_arg1), "r"(case3a_arg2) : "memory");
            case3a_result = func_080C0C54(case3a_arg0, case3a_arg1, case3a_arg2);
            asm volatile("ldr r3, [sp, #56]" : : : "memory");
        if (case3a_result == 0) {

        } else {
            if (temp_r6_2 == 0) {
                {
                    register s32 status_r0 asm("r0");
                    register s32 status_r1 asm("r1");
                    register void *status_r2 asm("r2");
                    status_r0 = 1;
                    status_r2 = var_r9_4;
                    M2C_FIELD(status_r2, s8 *, 0) = status_r0;
                    status_r0 = 0xFF;
                    M2C_FIELD(status_r2, u8 *, 1) = status_r0;
                    status_r1 = 1;
                    M2C_FIELD(status_r2, s8 *, 3) = status_r1;
                    M2C_FIELD(status_r2, s8 *, 4) = status_r1;
                }
                M2C_FIELD(var_r4_4, s8 *, M2C_FIELD(*arg1, u8 *, 3) * 0x1380) = temp_r6_2;
                temp_r2_5 = *arg1;
                {
                    s32 case3a_addr = (M2C_FIELD(temp_r2_5, u8 *, 3) * 0x1380) + 0x270;
                    M2C_FIELD((void *)case3a_addr, u8 *, (s32)var_r4_4) = (u8) M2C_FIELD(temp_r2_5, u8 *, 1);
                }
                {
                    s32 case3a_addr = (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0x750;
                    M2C_FIELD((void *)case3a_addr, s8 *, (s32)var_r4_4) = temp_r6_2;
                }
                {
                    s32 case3a_addr = (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0x9C0;
                    M2C_FIELD((void *)case3a_addr, s8 *, (s32)var_r4_4) = temp_r6_2;
                }
                {
                    s32 final_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 final_offset_r2 asm("r2");
                    asm volatile("mov r2, #156\n\tlsl r2, r2, #2" : "=r"(final_offset_r2));
                    var_r0_2 = final_address + final_offset_r2;
                }
            } else {
                M2C_FIELD(var_r3_5, u8 *, 0) = 0xFF;
                M2C_FIELD(var_r3_5, s8 *, 1) = temp_r6_2;
                M2C_FIELD(var_r3_5, s8 *, 3) = temp_r6_2;
                M2C_FIELD(var_r3_5, s8 *, 4) = temp_r6_2;
                temp_r2_6 = *arg1;
                {
                    s32 case3a_address = M2C_FIELD(temp_r2_6, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case3a_address)
                        : "r"(sp24)
                        : "cc");
                    case3a_address += (s32)var_r4_4;
                    M2C_FIELD((void *)case3a_address, u8 *, 0) = (u8) M2C_FIELD(temp_r2_6, u8 *, 1);
                }
                {
                    s32 case3a_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case3a_address)
                        : "r"(sp20)
                        : "cc");
                    case3a_address += (s32)var_r4_4;
                    {
                        register s32 zero_r1 asm("r1") = 0;
                        M2C_FIELD((void *)case3a_address, s8 *, 0) = zero_r1;
                    }
                }
                {
                    s32 case3a_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 case3a_reload_guard_r1 asm("r1");
                    asm volatile("" : "=r"(case3a_reload_guard_r1));
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case3a_address)
                        : "r"(sp1C), "r"(case3a_reload_guard_r1)
                        : "cc");
                    case3a_address += (s32)var_r4_4;
                    {
                        register s32 zero_r1 asm("r1") = 0;
                        M2C_FIELD((void *)case3a_address, s8 *, 0) = zero_r1;
                    }
                }
                {
                    s32 case3a_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 case3a_third_guard_r1 asm("r1");
                    asm volatile("" : "=r"(case3a_third_guard_r1));
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case3a_address)
                        : "r"(sp18), "r"(case3a_third_guard_r1)
                        : "cc");
                    case3a_address += (s32)var_r4_4;
                    {
                        register s32 zero_r1 asm("r1") = 0;
                        M2C_FIELD((void *)case3a_address, s8 *, 0) = zero_r1;
                    }
                }
                {
                    s32 case3a_final_address = M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    register s32 case3a_final_guard_r1 asm("r1");
                    asm volatile("" : "=r"(case3a_final_guard_r1));
                    asm volatile("add %0, %1, %0"
                                 : "+l"(case3a_final_address)
                                 : "r"(sp24), "r"(case3a_final_guard_r1)
                                 : "cc");
                    var_r0_2 = case3a_final_address;
                }
            }
            var_r5 = M2C_FIELD(var_r4_4, u8 *, var_r0_2 + 1);
            {
                register s32 case3a_success_r0 asm("r0") = 1;
                asm volatile("" : "+r"(case3a_success_r0));
                var_sl = case3a_success_r0;
            }
        }
        }
        {
            register s32 first_backedge_value_r1 asm("r1") = sp18;
            register s32 backedge_delta_r2 asm("r2") = 0xFFFFFD90;
            asm volatile("" : "+r"(backedge_delta_r2));
            first_backedge_value_r1 += backedge_delta_r2;
            sp18 = first_backedge_value_r1;
            sp1C += backedge_delta_r2;
            sp20 += backedge_delta_r2;
            sp24 += backedge_delta_r2;
        }
        var_r3_5 -= 1;
        asm volatile("" : "+r"(var_r3_5));
        var_r8_5 += 1;
        if (var_r8_5 <= 1U) {
            goto loop_29;
        }
        goto block_71;
    case 0x3B:
        if (func_080C0C54(3, M2C_FIELD(*arg1, u8 *, 3), 0) == 0) {
            goto block_71;
        }
        var_r2_12 = (void *)0x02032F7C;
        var_r8_8 = 0;
        M2C_FIELD(var_r2_12, s8 *, 0) = 1;
        M2C_FIELD(var_r2_12, u8 *, 1) = 0xFF;
        M2C_FIELD(var_r2_12, s8 *, 2) = 1;
        M2C_FIELD(var_r2_12, s8 *, 3) = 1;
        M2C_FIELD(var_r2_12, s8 *, 4) = 1;
        M2C_FIELD(var_r2_12, s8 *, 5) = 1;
        var_r4_5 = (void *)0x02034B4C;
        M2C_FIELD(var_r4_5, s8 *, M2C_FIELD(*arg1, u8 *, 3) * 0x1380) = var_r8_8;
        {
            register s32 case3b_next_row_r0 asm("r0") = var_r6_2 + 1;
            temp_r2_7 = case3b_next_row_r0 * 0x270;
        }
        temp_r3 = *arg1;
        {
            s32 case3b_address = M2C_FIELD(temp_r3, u8 *, 3) * 0x1380;
            asm volatile(
                ".syntax unified\n\t"
                "adds %0, %1, %0\n\t"
                ".syntax divided"
                : "+l"(case3b_address)
                : "r"(temp_r2_7)
                : "cc");
            case3b_address += (s32)var_r4_5;
            M2C_FIELD((void *)case3b_address, u8 *, 0) = (u8) M2C_FIELD(temp_r3, u8 *, 1);
        }
        M2C_FIELD(var_r4_5, s8 *, (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0x4E0) = var_r8_8;
        M2C_FIELD(var_r4_5, s8 *, (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0x750) = var_r8_8;
        M2C_FIELD(var_r4_5, s8 *, (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0x9C0) = var_r8_8;
        M2C_FIELD(var_r4_5, s8 *, (M2C_FIELD(*arg1, u8 *, 3) * 0x1380) + 0xC30) = var_r8_8;
        temp_r2_7 += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
        temp_r2_7 += (s32)var_r4_5;
        var_r5 = M2C_FIELD((void *)temp_r2_7, u8 *, 1);
        goto block_73;
    case 0x3C:
        var_r8_6 = 0;
        var_r9_5 = (void *)0x02034B4C;
loop_44:
        if (var_r8_6 <= 1U) {
            register s32 selector_seed_r0 asm("r0") = 1;
            var_r6_3 = selector_seed_r0 - var_r8_6;
        } else {
            register s32 selector_seed_r0 asm("r0") = 6;
            var_r6_3 = selector_seed_r0 - var_r8_6;
        }
        if (func_080C0C54(0, M2C_FIELD(*arg1, u8 *, 3), var_r6_3) != 0) {
            if ((var_r6_3 == 0) || (var_r6_3 == 3)) {
                register u8 *status_base_r1 asm("r1") = (u8 *)0x02032F7C;
                register u8 *status_slot_r0 asm("r0");
                asm volatile(
                    ".syntax unified\n\t"
                    "adds %0, %1, %2\n\t"
                    ".syntax divided"
                    : "=l"(status_slot_r0)
                    : "r"(var_r6_3), "r"(status_base_r1)
                    : "cc");
                temp_r3_2 = var_r6_3 + 1;
                *status_slot_r0 = temp_r3_2;
                asm volatile(
                    ".syntax unified\n\t"
                    "adds %0, %1, %0\n\t"
                    ".syntax divided"
                    : "+l"(status_base_r1)
                    : "r"(temp_r3_2)
                    : "cc");
                *status_base_r1 = 0xFF;
                {
                    s32 case3c_row = var_r6_3 * 0x270;
                    case3c_row += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    case3c_row += (s32)var_r9_5;
                    {
                        register s32 zero_r2 asm("r2") = 0;
                        M2C_FIELD((void *)case3c_row, s8 *, 0) = zero_r2;
                    }
                }
                temp_r2_8 = temp_r3_2 * 0x270;
                temp_r3_3 = *arg1;
                {
                    s32 case3c_address = M2C_FIELD(temp_r3_3, u8 *, 3) * 0x1380;
                    asm volatile(
                        ".syntax unified\n\t"
                        "adds %0, %1, %0\n\t"
                        ".syntax divided"
                        : "+l"(case3c_address)
                        : "r"(temp_r2_8)
                        : "cc");
                    case3c_address += (s32)var_r9_5;
                    M2C_FIELD((void *)case3c_address, u8 *, 0) = (u8) M2C_FIELD(temp_r3_3, u8 *, 1);
                }
                temp_r2_8 += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                temp_r2_8 += (s32)var_r9_5;
                var_r5 = M2C_FIELD((void *)temp_r2_8, u8 *, 1);
            } else {
                {
                    register u8 *status_base_r0 asm("r0") = (u8 *)0x02032F7C;
                    register u8 *status_slot_r1 asm("r1");
                    asm volatile("add %0, %1, %2"
                                 : "=l"(status_slot_r1)
                                 : "r"(var_r6_3), "r"(status_base_r0)
                                 : "cc");
                    {
                        register u32 status_value_r0 asm("r0") = 0xFF;
                        *status_slot_r1 = status_value_r0;
                    }
                }
                temp_r2_9 = var_r6_3 + 1;
                {
                    register u8 *status_base_r1 asm("r1") = (u8 *)0x02032F7C;
                    register u8 *status_slot_r0 asm("r0");
                    asm volatile("add %0, %1, %2"
                                 : "=l"(status_slot_r0)
                                 : "r"(temp_r2_9), "r"(status_base_r1)
                                 : "cc");
                    *status_slot_r0 = var_r6_3;
                }
                temp_r3_4 = var_r6_3 * 0x270;
                temp_r4 = *arg1;
                {
                    s32 case3c_address = M2C_FIELD(temp_r4, u8 *, 3) * 0x1380;
                    asm volatile(
                        "add %0, %1, %0"
                        : "+l"(case3c_address)
                        : "r"(temp_r3_4)
                        : "cc");
                    case3c_address += (s32)var_r9_5;
                    M2C_FIELD((void *)case3c_address, u8 *, 0) = (u8) M2C_FIELD(temp_r4, u8 *, 1);
                }
                {
                    s32 case3c_next_row = temp_r2_9 * 0x270;
                    case3c_next_row += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    case3c_next_row += (s32)var_r9_5;
                    {
                        register s32 zero_r2 asm("r2") = 0;
                        M2C_FIELD((void *)case3c_next_row, s8 *, 0) = zero_r2;
                    }
                }
                temp_r3_4 += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                temp_r3_4 += (s32)var_r9_5;
                var_r5 = M2C_FIELD((void *)temp_r3_4, u8 *, 1);
            }
            var_sl = 1;
        }
        var_r8_6 += 1;
        if (var_r8_6 <= 3U) {
            goto loop_44;
        }
        goto block_71;
    case 0x50:
        var_r8_7 = 0;
        var_r9_6 = (void *)0x02034B4C;
loop_59:
        if (var_r8_7 <= 1U) {
            register s32 selector_seed_r0 asm("r0") = 1;
            var_r6_4 = selector_seed_r0 - var_r8_7;
        } else {
            register s32 selector_seed_r0 asm("r0") = 6;
            register s32 selector_index_r1 asm("r1") = var_r8_7;
            asm volatile("" : "+r"(selector_seed_r0), "+r"(selector_index_r1));
            var_r6_4 = selector_seed_r0 - selector_index_r1;
        }
        if (func_080C0C54(7, M2C_FIELD(*arg1, u8 *, 3), var_r6_4) != 0) {
            if ((var_r6_4 == 0) || (var_r6_4 == 3)) {
                register u8 *status_base_r2 asm("r2") = (u8 *)0x02032F7C;
                register u8 *status_slot_r0 asm("r0");
                asm volatile("add %0, %1, %2"
                             : "=l"(status_slot_r0)
                             : "r"(var_r6_4), "r"(status_base_r2)
                             : "cc");
                temp_r3_5 = var_r6_4 + 1;
                *status_slot_r0 = temp_r3_5;
                {
                    register u8 *status_next_r1 asm("r1");
                    asm volatile("add %0, %1, %2"
                                 : "=l"(status_next_r1)
                                 : "r"(temp_r3_5), "r"(status_base_r2)
                                 : "cc");
                    *status_next_r1 = 0xFF;
                }
                {
                    s32 case50_row = var_r6_4 * 0x270;
                    case50_row += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    case50_row += (s32)var_r9_6;
                    {
                        register s32 zero_r0 asm("r0") = 0;
                        M2C_FIELD((void *)case50_row, s8 *, 0) = zero_r0;
                    }
                }
                temp_r2_10 = temp_r3_5 * 0x270;
                temp_r3_6 = *arg1;
                {
                    s32 case50_address = M2C_FIELD(temp_r3_6, u8 *, 3) * 0x1380;
                    asm volatile("add %0, %1, %0"
                                 : "+l"(case50_address)
                                 : "r"(temp_r2_10)
                                 : "cc");
                    case50_address += (s32)var_r9_6;
                    M2C_FIELD((void *)case50_address, u8 *, 0) = (u8) M2C_FIELD(temp_r3_6, u8 *, 1);
                }
                temp_r2_10 += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                temp_r2_10 += (s32)var_r9_6;
                var_r5 = M2C_FIELD((void *)temp_r2_10, u8 *, 1);
            } else {
                {
                    register u8 *status_base_r2 asm("r2") = (u8 *)0x02032F7C;
                    register u8 *status_slot_r1 asm("r1");
                    asm volatile("add %0, %1, %2"
                                 : "=l"(status_slot_r1)
                                 : "r"(var_r6_4), "r"(status_base_r2)
                                 : "cc");
                    {
                        register u32 status_value_r0 asm("r0") = 0xFF;
                        *status_slot_r1 = status_value_r0;
                    }
                }
                temp_r2_11 = var_r6_4 + 1;
                {
                    register u8 *status_base_r1 asm("r1") = (u8 *)0x02032F7C;
                    register u8 *status_slot_r0 asm("r0");
                    asm volatile("add %0, %1, %2"
                                 : "=l"(status_slot_r0)
                                 : "r"(temp_r2_11), "r"(status_base_r1)
                                 : "cc");
                    *status_slot_r0 = var_r6_4;
                }
                temp_r3_7 = var_r6_4 * 0x270;
                temp_r4_2 = *arg1;
                {
                    s32 case50_address = M2C_FIELD(temp_r4_2, u8 *, 3) * 0x1380;
                    asm volatile("add %0, %1, %0"
                                 : "+l"(case50_address)
                                 : "r"(temp_r3_7)
                                 : "cc");
                    case50_address += (s32)var_r9_6;
                    M2C_FIELD((void *)case50_address, u8 *, 0) = (u8) M2C_FIELD(temp_r4_2, u8 *, 1);
                }
                {
                    s32 case50_next_row = temp_r2_11 * 0x270;
                    case50_next_row += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                    case50_next_row += (s32)var_r9_6;
                    {
                        register s32 zero_r2 asm("r2") = 0;
                        M2C_FIELD((void *)case50_next_row, s8 *, 0) = zero_r2;
                    }
                }
                temp_r3_7 += M2C_FIELD(*arg1, u8 *, 3) * 0x1380;
                temp_r3_7 += (s32)var_r9_6;
                var_r5 = M2C_FIELD((void *)temp_r3_7, u8 *, 1);
            }
            var_sl = 1;
        }
        var_r8_7 += 1;
        if (var_r8_7 <= 3U) {
            goto loop_59;
        }
        goto block_71;
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    default:
block_71:
        if (var_sl == 0) {

        } else {
block_73:
            func_080C2DD0(M2C_FIELD(*arg1, u8 *, 3));
            var_r8 = 0x02030666;
            *(s8 *)var_r8 = 0;
            {
                register void *state_base_r2 asm("r2") = (void *)0x02031744;
                var_r9 = (s32)state_base_r2;
                *(s32 *)state_base_r2 = 0;
            }
            var_r6 = 0x0203055C;
            M2C_FIELD((void *)var_r6, u8 *, 2) = (u8) M2C_FIELD((void *)var_r6, u8 *, 1);
            *(s8 *)0x020317D8 = 0;
            *(s32 *)0x02021690 = 0xA;
            *(s8 *)0x02033F34 = 0;
            func_080ED17C(1);
            *(s8 *)var_r8 = 0;
            {
                register s32 *state_store_r1 asm("r1") = (s32 *)var_r9;
                *state_store_r1 = 0;
            }
            temp_r1 = *arg1;
            func_0809A1F8(M2C_FIELD(temp_r1, u8 *, 1), var_r5, 1, 0, (s32) M2C_FIELD(temp_r1, u8 *, 3), 0x02002880);
            {
                register u8 *status_base_r2 asm("r2") = (u8 *)0x02033F36;
                var_r8 = (s32)status_base_r2;
                *status_base_r2 = M2C_FIELD(*arg1, u8 *, 3);
            }
            {
                register u8 *unit_base_r0 asm("r0") = (u8 *)0x020317D6;
                register u8 unit_value_r0 asm("r0");
                register u8 *unit_store_r1 asm("r1");
                asm volatile("" : "+r"(unit_base_r0));
                var_r9 = (s32)unit_base_r0;
                unit_value_r0 = M2C_FIELD(*arg1, u8 *, 1);
                unit_store_r1 = (u8 *)var_r9;
                *unit_store_r1 = unit_value_r0;
            }
            *(s8 *)0x020317D7 = 0;
            func_080D0AF0(0x10);
            func_0809A5B4(M2C_FIELD((void *)var_r6, u8 *, 2), D_087AFCC4[*(u8 *)var_r9].value, 3, 2, 1);
            {
                register u8 *status_test_r2 asm("r2") = (u8 *)var_r8;
                if (*status_test_r2 == 0) {
                    func_08098BB4(0x08004037);
                } else {
                    func_08098BB4(0x08004047);
                }
            }
            temp_r1_2 = M2C_FIELD(*arg1, u8 *, 2);
            if (temp_r1_2 == 0x4B) {
                var_r2 = D_020218E4[0x6809];
            } else {
                var_r2 = 0;
            }
            func_0809A94C(temp_r1_2, 0, var_r2, 0x3DC, 0xF);
            if (*(u8 *)0x02033F36 == 0) {
                *(s32 *)0x02031744 = func_08094484(0x08359850, 0x0835985C,
                    0, -1, 0x72, 0x3DC, 0xF, 8, 0);
            } else {
                *(s32 *)0x02031744 = func_08094484(0x08359850, 0x0835985C,
                    0, 0xC1, 0x72, 0x3DC, 0xF, 8, 0);
            }
            func_080D0F94(*(u8 *)0x02033F36, *(u8 *)0x020317D6, 0x321);
            func_08096308(3, 0x20);
            var_r8_2 = 0;
            while ((func_080D1C18() << 0x18) == 0) {
                if (((func_0809669C() << 0x18) != 0) && (var_r8_2 == 0)) {
                    func_08098248(0x08103E00, 0, 1);
                    var_r8_2 = 1;
                }
                func_080ED17C(1);
            }
            func_08096308(0x12, 0x20);
            while ((func_0809669C() << 0x18) == 0) {
                if (*(u8 *)0x03005F72 == *(u8 *)0x03005F71) {
                    func_080D120C();
                }
                func_080ED17C(1);
            }
            {
                register s32 final_flag_guard_r5 asm("r5");
                asm volatile("" : "=r"(final_flag_guard_r5));
                *(s8 *)0x02030666 = 0;
                {
                    register void *state_base_r2 asm("r2") = (void *)0x02031744;
                    var_r8 = (s32)state_base_r2;
                    *(s32 *)state_base_r2 = 0;
                }
                *(s32 *)0x02021690 = 9;
                *(s32 *)0x02030558 = 0xFF10;
                func_080ED17C(1);
                *(s8 *)0x02030666 = 0;
                asm volatile("" : : "r"(final_flag_guard_r5));
            }
            *(s32 *)var_r8 = 0;
            func_080C3050(M2C_FIELD(*arg1, u8 *, 3));
        }
        break;
    }
    func_080A016C(sp14, -1, 0);
    return 0;
}
