#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void *func_080D2450(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_080D2790(s32);

void sub_080D7BE0(void *arg0)
{
    register void *owner asm("r4") = arg0;
    register s32 *phase_slot asm("r5") =
        (s32 *)((u8 *)owner + 0x8C);
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
        void *child;
        s32 x;

        x = *(s32 *)((u8 *)owner + 4);
        x += *(s32 *)((u8 *)owner + 0x94) * 2;
        child = func_080D2450(owner, 0, 0, (s16)x,
            *(s16 *)((u8 *)owner + 8), 0x20, 0x080D6E6D, 1);
        *(void **)((u8 *)owner + 0xC) = child;
        *(void **)((u8 *)child + 0x28) = owner;
        {
            register s32 zero asm("r1") = 0;

            *(s32 *)((u8 *)child + 0x2C) = zero;
            *(s32 *)((u8 *)child + 0x30) = zero;
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
        {
            void *second;
            s32 x;

            x = *(s32 *)((u8 *)owner + 4);
            x += *(s32 *)((u8 *)owner + 0x94) * 2;
            x += 0xF0;
            second = func_080D2450(owner, 2, 0, (s16)x,
                0x70, 0, 0, 0);
            *(void **)((u8 *)owner + 0x10) = second;
        }
    }
    phase = 1;

advance:
    func_080D2790(phase);
    *phase_slot += 1;
    return;

phase2:
    {
        u8 index = 0x18;
        register void *child_init asm("r1") =
            *(void **)((u8 *)owner + 0xC);
        register u32 raw_count asm("r0") =
            *(u32 *)((u8 *)child_init + 0x2C);
        register u32 bound asm("r3");
        register void *child asm("r5");

        raw_count >>= 1;
        asm volatile("" : "+r"(raw_count));
        bound = raw_count;
        bound += 0x19;
        child = child_init;
        if ((u32)index < bound &&
                *(s32 *)((u8 *)owner + 0x6C) == 0) {
            register u32 scan_bound asm("r1") = bound;
            register u8 *slots asm("r3") = (u8 *)owner + 0xC;

            do {
                index += 1;
            } while ((u32)index < scan_bound &&
                *(void **)(slots + (index << 2)) == 0);
        }
        if (index == ((*(volatile u32 *)((u8 *)child + 0x2C) >> 1)
                + 0x19) &&
                *(void **)((u8 *)owner + 0x10) == 0) {
            func_08095114(owner);
        }
    }
}
