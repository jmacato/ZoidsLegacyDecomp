#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_080D2790(s32);

void sub_080D65E0(void *arg0)
{
    register void *owner asm("r5") = arg0;
    register s32 *phase_slot asm("r6") = (s32 *)((u8 *)owner + 0x8C);
    register u32 phase asm("r0") = *phase_slot;

    switch (phase) {
    case 0:
        goto phase0;
    case 1:
        goto phase1;
    case 2:
        goto phase2;
    default:
        return;
    }

phase0:
    {
        register s32 *x_slot asm("r4") = (s32 *)((u8 *)owner + 0x90);
        void *child;
        s32 x;

        x = *x_slot - 0x100;
        child = func_080D2450(owner, 0, 0, (s16)x,
            *(s16 *)((u8 *)owner + 0x94), 0x20, 0x080D63D1, 1);
        *(void **)((u8 *)owner + 0xC) = child;
        *(void **)((u8 *)child + 0x28) = owner;
        {
            register s32 zero asm("r2") = 0;
            register s32 value asm("r1");

            *(s32 *)((u8 *)child + 0x2C) = zero;
            value = *x_slot;
            *(s32 *)((u8 *)child + 0x30) = value;
            *(s32 *)((u8 *)child + 0x34) = zero;
        }
    }
    phase = 0;
    goto advance;

phase1:
    {
        void *child = *(void **)((u8 *)owner + 0xC);

        if ((*(u32 *)child & 0x20000) == 0) {
            return;
        }
        *(void **)((u8 *)owner + 0x10) = func_080D2450(owner, 2, 0,
            *(s16 *)((u8 *)owner + 0x90),
            *(s16 *)((u8 *)owner + 0x94), 0, 0, 0);
        func_080D12A0(6, 0);
    }
    phase = 1;

advance:
    func_080D2790(phase);
    *phase_slot += 1;
    return;

phase2:
    {
        u8 index = 0x18;
        register void *child asm("r1") = *(void **)((u8 *)owner + 0xC);
        register u32 raw_count asm("r0") = *(u32 *)((u8 *)child + 0x2C);
        register u32 bound asm("r3");

        raw_count >>= 1;
        asm volatile("" : "+r"(raw_count));
        bound = raw_count;
        bound += 0x19;
        if ((u32)index < bound && *(s32 *)((u8 *)owner + 0x6C) == 0) {
            register u32 scan_bound asm("r4") = bound;
            register u8 *slots asm("r3") = (u8 *)owner + 0xC;

            do {
                index += 1;
            } while ((u32)index < scan_bound &&
                *(void **)(slots + (index << 2)) == 0);
        }
        if (index == ((*(volatile u32 *)((u8 *)child + 0x2C) >> 1)
                + 0x19) && *(void **)((u8 *)owner + 0x10) == 0) {
            func_08095114(owner);
        }
    }
}
