#include "m2c_prelude.h"

M2C_UNK func_08095114(void *);                      /* extern */
M2C_UNK func_080D12A0(s32, s32);                    /* extern */
void *func_080D2450(void *, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_080D2660(void *, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_080D2790(s32);                         /* extern */
s32 func_080ECD5C(s32);                             /* extern */
s32 func_080ECD98(s32, s32);                        /* extern */
M2C_UNK jtbl_080DD804();                            /* static */

void sub_080DD7DC(void *arg0, M2C_UNK arg3) {
    volatile s32 sp14;
    volatile s32 sp18;
    volatile s32 sp1C;
    s32 *sp20;
    s32 frame_gap0;
    s32 frame_gap1;
    s32 sp2C;
    s32 frame_gap2;
    s32 *sp34;
    s32 *sp38;
    s32 temp_r1_2;
    s32 temp_r4_5;
    s32 *var_r1;
    s32 temp_r0_3;
    register void *temp_r0_4 asm("r0");
    s32 temp_r1;
    register s32 temp_r1_3 asm("r1");
    s32 temp_r4_2;
    s32 temp_r4_3;
    u16 temp_r4_4;
    u32 temp_r0;
    register s32 var_r6 asm("r6");
    register void *temp_r2_2 asm("r8");
    register u32 shared_sl asm("sl");

    temp_r0 = M2C_FIELD(arg0, u32 *, 0x8C);
    asm volatile("" : "=m"(sp20), "=m"(frame_gap0), "=m"(frame_gap1),
        "=m"(sp2C), "=m"(frame_gap2), "=m"(sp34), "=m"(sp38));
    switch (temp_r0) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, void **, 0xC) = func_080D2450(arg0, 0, 1, (s16) (M2C_FIELD(arg0, s32 *, 4) - 0x80), (s32) M2C_FIELD(arg0, s16 *, 8), 0x600, 0, 1);
        func_080D2790(0);
        goto increment_state;
    case 1:
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), u16 *, 0x14) != 4) {
            return;
        }
        M2C_FIELD(arg0, void **, 0x10) = func_080D2450(arg0, 5, 0, (s16) M2C_FIELD(arg0, s32 *, 4), (s32) M2C_FIELD(arg0, s16 *, 8), 0x400, 0, 0);
        goto increment_state;
    case 2: {
        register u32 saved_reg_r9 asm("r9");
        register s32 *rng_ptr_r8 asm("r8");

        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), u16 *, 0x14) != 5) {
            return;
        }
        {
            register s32 saved_a8 asm("r2") = M2C_FIELD(arg0, s32 *, 0xA8);
            sp14 = saved_a8;
        }
        M2C_FIELD(arg0, s32 *, 0xA8) = 0xC0;
        M2C_FIELD(arg0, void **, 0x14) = func_080D2450(arg0, 0, 1, (s16) (M2C_FIELD(arg0, s32 *, 4) + 0x80), ({
            register s32 guard_r2 asm("r2");
            s32 y_value;
            asm volatile("" : "=r"(guard_r2));
            y_value = M2C_FIELD(arg0, s16 *, 8);
            asm volatile("" : "+r"(guard_r2));
            y_value;
        }), 0x600, 0, 1);
        var_r6 = 0;
        {
            register u32 state_init asm("r2") = 0x8C;
            asm volatile("" : "+r"(state_init));
            state_init += (u32)arg0;
            shared_sl = state_init;
        }
        sp38 = arg0 + 0xA8;
        {
            register s32 guard_r2 asm("r2");
            asm volatile("" : "=r"(guard_r2));
            saved_reg_r9 = (u32)arg0 + 0xC;
            asm volatile("" : "+r"(guard_r2));
        }
        rng_ptr_r8 = (s32 *)0x03000010;
        do {
            register s32 temp_r4 asm("r4");
            register s32 temp_r0_2 asm("r0");
            s32 child_offset;
            void *spawned;

            {
                register s32 *rng_view asm("r2") = rng_ptr_r8;
                temp_r4 = func_080ECD5C(*rng_view);
            }
            sp18 = func_080ECD98(var_r6 << 6, 7);
            temp_r0_2 = ((u32) (temp_r4 * 9) >> 0xF) - 0x24;
            {
                register s32 guard_r2 asm("r2");
                asm volatile("" : "=r"(guard_r2));
                asm volatile("add %0, %2, %0"
                    : "+r"(temp_r0_2), "+r"(guard_r2) : "r"(sp18));
            }
            sp1C = temp_r0_2;
            {
                register s32 *rng_view asm("r2") = rng_ptr_r8;
                spawned = (void *)func_080D2660(arg0, 3, 0, (s16) M2C_FIELD(arg0, s32 *, 4), (s32) M2C_FIELD(arg0, s16 *, 8), 0x20, sp1C, ((u32) (func_080ECD5C(*rng_view) * 0x201) >> 0xF) + ({ register s32 base_r0 asm("r0") = 0x200; asm volatile("" : "+r"(base_r0)); base_r0; }), 0);
            }
            child_offset = var_r6 + 3;
            child_offset <<= 2;
            *(void **)(saved_reg_r9 + child_offset) = spawned;
            {
                register s32 next_r0 asm("r0") = var_r6 + 1;
                asm volatile("" : "+r"(next_r0));
                var_r6 = (u8) next_r0;
            }
        } while ((u32) var_r6 <= 7U);
        {
            register s32 restore_r1 asm("r1") = sp14;
            register s32 *restore_r2 asm("r2") = sp38;
            asm volatile("" : "+r"(restore_r1), "+r"(restore_r2));
            *restore_r2 = restore_r1;
        }
        func_080D12A0(6, 0);
        func_080D2790(1);
        var_r1 = (s32 *)shared_sl;
        goto increment_value;
    }
    case 3:
        if ((u32) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), u16 *, 0x14) <= 0x15U) {
            {
                register s32 *counter_ptr_r2 asm("r2") = arg0 + 0x90;
                asm volatile("" : "+r"(counter_ptr_r2));
                sp20 = counter_ptr_r2;
                asm volatile(
                    ".syntax unified\n\t"
                    "ldr r0, [%1]\n\t"
                    "mov %0, r0\n\t"
                    ".syntax divided"
                    : "=r"(temp_r1)
                    : "r"(counter_ptr_r2)
                    : "r0");
            }
            temp_r1 &= 3;
            asm volatile("" : : "r"(temp_r1));
            if (temp_r1 == 0) {
                register s32 *rng asm("sl");
                s32 retained_size;
                s32 rng_value;
                {
                    register s32 *rng_seed asm("r2") = (s32 *)0x03000010;
                    asm volatile("" : "+r"(rng_seed));
                    rng = rng_seed;
                    rng_value = *rng_seed;
                }
                temp_r4_2 = ((u32) (func_080ECD5C(rng_value) * 0x21) >> 0xF) + 0x80;
                {
                    register s32 *rng_r1 asm("r1") = rng;
                    asm volatile("" : "+r"(rng_r1));
                    func_080D2660(arg0, 4, 0, (s16) M2C_FIELD(arg0, s32 *, 4), (s32) (s16) (M2C_FIELD(arg0, s32 *, 8) - 4), ({
                        register s32 size_r2 asm("r2");
                        asm volatile("" : "=l"(retained_size));
                        asm volatile("" : : "l"(retained_size));
                        asm volatile(
                            ".syntax unified\n\t"
                            "movs %0, #160\n\t"
                            "lsls %0, %0, #3\n\t"
                            ".syntax divided"
                            : "=r"(size_r2));
                        size_r2;
                    }), temp_r4_2, ((u32) (func_080ECD5C(*rng_r1) * 0x101) >> 0xF) + 0x100, ({
                        register s32 mask_r0 asm("r0");
                        asm volatile(
                            ".syntax unified\n\t"
                            "mov %0, %1\n\t"
                            ".syntax divided"
                            : "=r"(mask_r0)
                            : "r"(temp_r1));
                        mask_r0;
                    }));
                }
                {
                    register s32 kill_r6 asm("r6");
                    asm volatile("" : "=r"(kill_r6));
                }
                {
                    register s32 *rng_r1 asm("r1") = rng;
                    asm volatile("" : "+r"(rng_r1));
                    temp_r4_3 = ((u32) (func_080ECD5C(*rng_r1) * 0x21) >> 0xF) + 0x60;
                }
                {
                    register s32 *rng_r2 asm("r2") = rng;
                    asm volatile("" : "+r"(rng_r2));
                    func_080D2660(arg0, 4, 0, ({
                        register s32 x_r3 asm("r3");
                        register s32 offset_r0 asm("r0") = 4;
                        asm volatile(
                            ".syntax unified\n\t"
                            "ldrsh %0, [%1, %2]\n\t"
                            ".syntax divided"
                            : "=r"(x_r3)
                            : "r"(arg0), "r"(offset_r0));
                        x_r3;
                    }), (s32) (s16) (M2C_FIELD(arg0, s32 *, 8) + 4), ({ register s32 size_r2 asm("r2"); asm volatile(".syntax unified\n\tmovs %0, #160\n\tlsls %0, %0, #3\n\t.syntax divided" : "=r"(size_r2)); size_r2; }), temp_r4_3, ((u32) (func_080ECD5C(*rng_r2) * 0x101) >> 0xF) + 0x100, ({
                        register s32 mask_r0 asm("r0");
                        asm volatile(
                            ".syntax unified\n\t"
                            "mov %0, %1\n\t"
                            ".syntax divided"
                            : "=r"(mask_r0)
                            : "r"(temp_r1));
                        mask_r0;
                    }));
                }
                asm volatile("" : "+r"(retained_size));
            }
            *sp20 += 1;
        }
        var_r6 = 0;
        if (M2C_FIELD(arg0, void **, 0xC) == 0) {
            var_r1 = (s32 *)((u8 *)arg0 + 0xC);
loop_20:
            {
                register s32 next_r0 asm("r0") = var_r6 + 1;
                asm volatile("" : "+r"(next_r0));
                var_r6 = (u8) next_r0;
            }
            if ((u32) var_r6 <= 0xAU) {
                register u32 case3_child_address asm("r0") = var_r6 * 4;
                asm volatile("add %0, %1, %0"
                    : "+r"(case3_child_address) : "r"(var_r1));
                if (*(void **)case3_child_address == 0) {
                    goto loop_20;
                }
            }
        }
        if (var_r6 != 0xB) {
            return;
        }
        var_r1 = (s32 *)((u8 *)arg0 + 0x90);
        *var_r1 = 0;
        var_r1 -= 1;
        goto increment_value;
    case 4: {
        register s32 *counter_init asm("r1") = arg0 + 0x90;
        register u32 counter asm("r2") = *counter_init;
        register u32 one asm("r0") = 1;
        register s32 priority_base_r9 asm("r9");

        counter &= one;
        shared_sl = counter;
        sp34 = counter_init;
        if (counter != 0) {

        } else {
            register s32 y_raw_r2 asm("r2");
            register s32 rng_result_r0 asm("r0");
            {
                register s32 *rng_view asm("r1") = (s32 *)0x03000010;
                temp_r4_4 = (M2C_FIELD(arg0, s32 *, 4) + ((u32) (func_080ECD5C(*rng_view) * 9) >> 0xF)) - 4;
            }
            {
                register s32 *rng_view asm("r2") = (s32 *)0x03000010;
                asm volatile("" : "+r"(rng_view));
                rng_result_r0 = func_080ECD5C(*rng_view);
            }
            y_raw_r2 = M2C_FIELD(arg0, s32 *, 8);
            asm volatile("" : "+r"(y_raw_r2), "+r"(rng_result_r0));
            y_raw_r2 += (u32) (rng_result_r0 * 9) >> 0xF;
            y_raw_r2 -= 4;
            asm volatile(
                ".syntax unified\n\t"
                "lsls %0, %0, #16\n\t"
                "asrs %0, %0, #16\n\t"
                "lsls r0, %4, #16\n\t"
                "asrs %1, r0, #16\n\t"
                "str %1, %2\n\t"
                ".syntax divided"
                : "=r"(temp_r4_5), "=r"(temp_r1_2), "=m"(sp2C)
                : "0"(temp_r4_4), "r"(y_raw_r2)
                : "r0");
            {
                register s32 zero_r2 asm("r2");
                temp_r0_4 = func_080D2450(arg0, 1, 0, temp_r4_5,
                    temp_r1_2, ({ zero_r2 = shared_sl; asm volatile("" : "+r"(zero_r2)); zero_r2; }), zero_r2, zero_r2);
            }
            temp_r1_3 = var_r6 * 4;
            temp_r2_2 = arg0 + 0xC;
            *(void **)((u8 *)temp_r2_2 + temp_r1_3) = temp_r0_4;
            {
                register s32 guard_r2 asm("r2");
                s32 rng_seed;
                s32 priority;
                asm volatile("" : "=r"(guard_r2));
                rng_seed = *(s32 *)0x03000010;
                asm volatile("" : "+r"(guard_r2));
                priority = (u32) (func_080ECD5C(rng_seed) * 0x401) >> 0xF;
                {
                    register s32 priority_base_r2 asm("r2") = 0x200;
                    asm volatile("" : "+r"(priority_base_r2));
                    priority_base_r9 = priority_base_r2;
                }
                priority += priority_base_r9;
                priority *= 2;
                temp_r0_4 = (void *)func_080D2660(arg0, 2, 0, temp_r4_5,
                    sp2C, 0x100, 0x80, priority, shared_sl);
                temp_r1_3 = var_r6 + 8;
                temp_r1_3 <<= 2;
                *(void **)((u8 *)temp_r2_2 + temp_r1_3) = temp_r0_4;
            }
            {
                register s32 kill_r5 asm("r5");
                asm volatile("" : "=r"(kill_r5));
            }
            {
                register s32 guard_r2 asm("r2");
                s32 rng_seed;
                s32 priority;
                asm volatile("" : "=r"(guard_r2));
                rng_seed = *(s32 *)0x03000010;
                asm volatile("" : "+r"(guard_r2));
                priority = (u32) (func_080ECD5C(rng_seed) * 0x201) >> 0xF;
                priority += priority_base_r9;
                priority *= 2;
                {
                    register s32 y_r2 asm("r2") = sp2C;
                    asm volatile("" : "+r"(y_r2));
                    temp_r0_4 = (void *)func_080D2660(arg0, 3, 0, temp_r4_5,
                        y_r2, 0x120, ({ register s32 guard_r2 asm("r2"); s32 width = 0x80; asm volatile("" : "=r"(guard_r2)); asm volatile("" : "+r"(width), "+r"(guard_r2)); width; }), priority, ({ register s32 zero_r1 asm("r1") = shared_sl; asm volatile("" : "+r"(zero_r1)); zero_r1; }));
                }
                temp_r1_3 = var_r6 + 0x10;
                temp_r1_3 <<= 2;
                *(void **)((u8 *)temp_r2_2 + temp_r1_3) = temp_r0_4;
            }
            {
                register s32 *a8_r5 asm("r5") = arg0 + 0xA8;
                register s32 saved_a8 asm("r2") = *a8_r5;
                asm volatile("" : "+r"(a8_r5));
                sp14 = saved_a8;
                *a8_r5 = 0xC0;
                {
                    register s32 guard_r2 asm("r2");
                    s32 rng_seed;
                    s32 priority;
                    asm volatile("" : "=r"(guard_r2));
                    rng_seed = *(s32 *)0x03000010;
                    asm volatile("" : "+r"(guard_r2));
                    priority = (u32) (func_080ECD5C(rng_seed) * 0x401)
                        >> 0xF;
                    priority += priority_base_r9;
                    priority *= 2;
                    {
                        register s32 y_r2 asm("r2") = sp2C;
                        register s32 zero_r0 asm("r0");
                        asm volatile("" : "+r"(y_r2));
                        temp_r0_4 = (void *)func_080D2660(arg0, 2, 0,
                            temp_r4_5, y_r2, ({ zero_r0 = shared_sl; asm volatile("" : "+r"(zero_r0)); zero_r0; }), zero_r0, priority,
                            zero_r0);
                    }
                }
                temp_r1_3 = var_r6 + 0x18;
                temp_r1_3 <<= 2;
                asm volatile("add %0, %1" : "+r"(temp_r2_2) : "r"(temp_r1_3));
                *(void **)temp_r2_2 = temp_r0_4;
                {
                    register s32 guard_r0 asm("r0");
                    register s32 guard_r1 asm("r1");
                    asm volatile("" : "=r"(guard_r0), "=r"(guard_r1));
                    *a8_r5 = sp14;
                    asm volatile("" : "+r"(guard_r0), "+r"(guard_r1));
                }
            }
            {
                register s32 *counter_r1 asm("r1") = sp34;
                asm volatile("" : "+r"(counter_r1));
                if (*counter_r1 == 0) {
                    func_080D12A0(6, 0);
                    func_080D2790(1);
                }
            }
        }
        {
            register s32 *counter_r2 asm("r2") = sp34;
            asm volatile("" : "+r"(counter_r2));
            temp_r0_3 = *counter_r2 + 1;
            *counter_r2 = temp_r0_3;
        }
        if (temp_r0_3 == 0x10) {
            goto increment_state;
        }
        return;
    }

    increment_state:
        var_r1 = (s32 *)((u8 *)arg0 + 0x8C);
increment_value:
        *var_r1 += 1;
        return;

    case 5:
        var_r6 = 0;
        if (M2C_FIELD(arg0, void **, 0xC) == 0) {
            var_r1 = (s32 *)((u8 *)arg0 + 0xC);
loop_34:
            {
                register s32 next_r0 asm("r0") = var_r6 + 1;
                asm volatile("" : "+r"(next_r0));
                var_r6 = (u8) next_r0;
            }
            if ((u32) var_r6 <= 0x1FU) {
                register u32 case5_child_address asm("r0") = var_r6 * 4;
                asm volatile("add %0, %1, %0"
                    : "+r"(case5_child_address) : "r"(var_r1));
                if (*(void **)case5_child_address == 0) {
                    goto loop_34;
                }
            }
        }
        if (var_r6 == 0x20) {
            func_08095114(arg0);
        }
        break;
    }
}
