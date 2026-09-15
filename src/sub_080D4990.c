#include "m2c_prelude.h"

void func_08095114(void *);
void func_080D12A0(s32, s32);
void *func_080D2450();
void *func_080D2660();
void func_080D2790(s32);
u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D4990(char *arg0)
{
    s32 sp14;
    char *sp18;
    s32 *sp1C;
    s32 *sp20;
    s32 *sp24;
    volatile s32 outgoing_reserve;
    s32 temp_r1_2;
    register s32 temp_r2 asm("r8");
    register s32 temp_r4 asm("r4");
    register s32 temp_r6 asm("r6");
    register s32 var_r0 asm("r0");
    register u16 temp_r0_4 asm("r0");
    register u16 temp_r8 asm("r8");
    u32 temp_r0;
    u32 temp_r1;
    register s32 var_r4 asm("r4");
    u8 var_r5;
    u8 var_r5_2;
    register u8 var_r5_3 asm("r5");
    register s32 zero asm("sl");
    register s32 x_shift asm("r6");
    register s32 outer_temp asm("r2");
    register s32 y_shift asm("r9");
    register s32 y_signed asm("r5");
    register s32 outer_word asm("r5");
    register s32 x_base asm("r0");
    register s32 x_offset asm("r1");
    register s32 nonzero asm("r0");
    register void *spawned asm("r0");
    register s32 slot_base asm("r2");
    register s32 child_index asm("r1");
    register s32 terminal_index asm("r1");
    register s32 saved_outer asm("r1");
    register s32 narrowed_outer asm("r0");
    register s32 *state_reload asm("r2");
    char *temp_r0_2;
    char *temp_r0_3;

    asm volatile("" : "=m"(outgoing_reserve));
    temp_r0 = M2C_FIELD(arg0, u32 *, 0x8C);
    switch (temp_r0) {
    case 0:
        temp_r0_3 = func_080D2450(arg0, 0, 0,
            (s16)(M2C_FIELD(arg0, s32 *, 0x90) - 0x100),
            (s32)M2C_FIELD(arg0, s16 *, 0x94), 0x20, 0x080D3F6D, 1);
        M2C_FIELD(arg0, char **, 0xC) = temp_r0_3;
        M2C_FIELD(temp_r0_3, char **, 0x28) = arg0;
        M2C_FIELD(temp_r0_3, s32 *, 0x2C) = 0;
        M2C_FIELD(temp_r0_3, s32 *, 0x30) = M2C_FIELD(arg0, s32 *, 0x90);
        func_080D2790(0);
        M2C_FIELD(arg0, u32 *, 0x8C) += 1;
        return;

    case 1:
        if (!(M2C_FIELD(M2C_FIELD(arg0, char **, 0xC), s32 *, 0) & 0x20000)) {
            return;
        }
        var_r5_3 = 0;
        sp1C = (s32 *)(arg0 + 0x8C);
        sp20 = (s32 *)(arg0 + 0x90);
        sp24 = (s32 *)(arg0 + 0x94);
        sp18 = arg0 + 0xC;
        asm volatile("mov %0, %1" : "=r"(zero) : "r"(var_r5_3));
        asm volatile("" : "=r"(outer_word) : "0"(var_r5_3));
        do {
            x_base = *sp20;
            x_offset = outer_word << 3;
            x_base += x_offset;
            x_base <<= 16;
            x_base = (u32)x_base >> 16;
            temp_r8 = x_base;
            nonzero = -outer_word;
            nonzero |= outer_word;
            temp_r4 = (nonzero >> 31) & 8;
            temp_r6 = *sp24;
            temp_r1_2 = ((u32)(func_080ECD5C(D_03000010) * 9) >> 15) - 4;
            if (1 & outer_word) {
                var_r0 = -temp_r4;
                asm volatile("" : "+r"(var_r0));
                var_r0 = temp_r6 + var_r0;
            } else {
                var_r0 = temp_r6 + temp_r4;
            }
            var_r0 += temp_r1_2;
            asm volatile("lsl %0, %0, #16\n\tlsr %0, %0, #16"
                         : "+r"(var_r0));
            temp_r0_4 = var_r0;
            var_r4 = 0;
            x_shift = temp_r8 << 16;
            outer_temp = outer_word << 2;
            temp_r2 = outer_temp;
            outer_word += 1;
            sp14 = outer_word;
            var_r0 = temp_r0_4 << 16;
            y_signed = var_r0 >> 16;
            y_shift = var_r0;
loop_14:
            {
                register volatile s32 *outgoing asm("sp");
                s32 priority;

                priority = ((u32)(func_080ECD5C(D_03000010) * 0x41) >> 15)
                    + 0xC0;
                outgoing[0] = y_signed;
                outgoing[1] = 0x400;
                outgoing[2] = (var_r4 * 0xC) - 0xC;
                outgoing[3] = priority;
                outgoing[4] = zero;
                {
                    register char *call0 asm("r0") = arg0;
                    register s32 call1 asm("r1") = 2;
                    register s32 call2 asm("r2") = 0;
                    register s32 call3 asm("r3");
                    register s32 value asm("r6") = x_shift;

                    asm volatile("" : "+r"(value));
                    call3 = value >> 16;
                    asm volatile("" : "+r"(call0), "+r"(call1),
                                       "+r"(call2), "+r"(call3));
                    spawned = func_080D2660(call0, call1, call2, call3);
                }
            }
            slot_base = temp_r2;
            child_index = slot_base + var_r4;
            child_index += 1;
            child_index <<= 2;
            asm volatile("add %0, %1, %0"
                         : "+r"(child_index) : "r"(sp18));
            *(void **)child_index = spawned;
            {
                register s32 next_inner asm("r0") = var_r4 + 1;

                next_inner <<= 24;
                var_r4 = (u32)next_inner >> 24;
            }
            if ((u32)var_r4 <= 2U) {
                goto loop_14;
            }
            spawned = func_080D2450(arg0, 3, 0, x_shift >> 16,
                y_shift >> 16, zero, zero, zero);
            terminal_index = temp_r2;
            terminal_index += 4;
            terminal_index <<= 2;
            asm volatile("add %0, %1, %0"
                         : "+r"(terminal_index) : "r"(sp18));
            *(void **)terminal_index = spawned;
            saved_outer = sp14;
            narrowed_outer = saved_outer << 24;
            var_r5_3 = (u32)narrowed_outer >> 24;
        } while ((u32)var_r5_3 <= 4U);
        func_080D12A0(6, 0);
        func_080D2790(1);
        state_reload = sp1C;
        *state_reload += 1;
        return;

    case 2:
        {
            register char *t asm("r0") = M2C_FIELD(arg0, char **, 0xC);
            s32 active = M2C_FIELD(t, s32 *, 0) & 0x20000;
            register char *child asm("r3") = t;

            if (active) {
                register s32 scan asm("r5");
                u32 child_count;
                u32 bound;
                s32 off;

                scan = 0x18;
                asm volatile("" : "+r"(scan));
                child_count = M2C_FIELD(child, u32 *, 0x2C);
                bound = (child_count >> 2) + 0x19;
                if ((u32)scan < bound && M2C_FIELD(arg0, s32 *, 0x6C) == 0) {
                    u32 scan_bound = bound;
                    s32 *children = (s32 *)(arg0 + 0xC);

                    do {
                        register s32 next asm("r0");

                        next = scan + 1;
                        next <<= 24;
                        scan = (u32)next >> 24;
                    } while ((u32)scan < scan_bound &&
                        (off = scan << 2,
                         *(s32 *)((char *)children + off)) == 0);
                }
                if (scan == ((*(volatile u32 *)(child + 0x2C) >> 2) + 0x19)) {
                    scan = 1;
                    if (M2C_FIELD(arg0, s32 *, 0x10) == 0) {
                        s32 *children = (s32 *)(arg0 + 0xC);

                        do {
                            register s32 next asm("r0");

                            next = scan + 1;
                            next <<= 24;
                            scan = (u32)next >> 24;
                        } while ((u32)scan <= 20 &&
                            (off = scan << 2,
                             *(s32 *)((char *)children + off)) == 0);
                    }
                    if (scan == 21) {
                        func_08095114(arg0);
                    }
                }
            }
        }
        return;
    }
}
