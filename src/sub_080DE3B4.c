#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void *func_080D2450();
extern void func_080D2790(s32);

void sub_080DE3B4(void *arg0) {
    register char *owner asm("r4") = arg0;

    if (*(s32 *)(owner + 0x90) == 0) {
        register s32 *phase_slot asm("r6") = (s32 *)(owner + 0x8C);
        register u32 phase asm("r5") = *phase_slot;

        if (phase == 0) {
            register void *child asm("r0");
            child = func_080D2450(owner, 2, 0, *(s16 *)(owner + 4),
                (s16)(*(s32 *)(owner + 0x94) + 0x50),
                0x20, 0x080D63D1, 1);
            *(void **)(owner + 0xC) = child;
            *(void **)((char *)child + 0x28) = owner;
            *(s32 *)((char *)child + 0x2C) = phase;
            *(s32 *)((char *)child + 0x30) = phase;
            *(s32 *)((char *)child + 0x34) = 2;
            func_080D2790(0);
            *phase_slot = *phase_slot + 1;
            return;
        }
        {
            register void *child_init asm("r0") = *(void **)(owner + 0xC);
            register u32 flags asm("r1") = *(u32 *)child_init;
            register u32 mask asm("r2") = 0x20000;
            register void *child asm("r5");
            flags &= mask;
            child = child_init;
            if (flags == 0) {
                return;
            }
            {
                register s32 index asm("r2") = 0x18;
                register u32 raw_count asm("r0") =
                    *(u32 *)((char *)child + 0x2C);
                register u32 bound asm("r1");
                raw_count >>= 1;
                bound = raw_count + 0x19;
                if ((u32)index < bound && *(s32 *)(owner + 0x6C) == 0) {
                    register u32 scan_bound asm("r3") = bound;
                    register char *slots asm("r1") = owner + 0xC;
                    do {
                        register s32 next asm("r0") = index + 1;
                        next <<= 24;
                        index = (u32)next >> 24;
                    } while ((u32)index < scan_bound &&
                        *(s32 *)(slots + (index << 2)) == 0);
                }
                if (index ==
                        ((*(volatile u32 *)((char *)child + 0x2C) >> 1)
                         + 0x19)) {
                    func_08095114(owner);
                }
            }
        }
        return;
    }

    {
        register s32 *phase_slot asm("r5") = (s32 *)(owner + 0x8C);
        register u32 phase asm("r0") = *phase_slot;

        switch (phase) {
        case 0: {
            register void *child asm("r0");
            register s32 x asm("r3") = *(s32 *)(owner + 4);
            x += *(s32 *)(owner + 0x94) * 2;
            child = func_080D2450(owner, 0, 0, (s16)x,
                *(s16 *)(owner + 8), 0x20, 0x080D6E6D, 1);
            *(void **)(owner + 0xC) = child;
            *(void **)((char *)child + 0x28) = owner;
            {
                register s32 zero asm("r1") = 0;
                *(s32 *)((char *)child + 0x2C) = zero;
                *(s32 *)((char *)child + 0x30) = zero;
            }
            phase = 0;
            goto advance;
        }
        case 1:
            if ((**(u32 **)(owner + 0xC) & 0x20000) == 0) {
                return;
            }
            {
                register s32 x asm("r3") = *(s32 *)(owner + 4);
                x += *(s32 *)(owner + 0x94) * 2;
                x += 0xF0;
                *(void **)(owner + 0x10) = func_080D2450(owner, 4, 0,
                    (s16)x, 0x70, 0, 0, 0);
            }
            phase = 1;
advance:
            func_080D2790(phase);
            *phase_slot = *phase_slot + 1;
            return;
        case 2: {
            register s32 index asm("r2") = 0x18;
            register void *child_init asm("r1") = *(void **)(owner + 0xC);
            register u32 raw_count asm("r0") =
                *(u32 *)((char *)child_init + 0x2C);
            register u32 bound asm("r3");
            register void *child asm("r5");
            raw_count >>= 1;
            asm volatile("" : "+r"(raw_count));
            bound = raw_count + 0x19;
            child = child_init;
            if ((u32)index < bound && *(s32 *)(owner + 0x6C) == 0) {
                register u32 scan_bound asm("r3") = bound;
                register char *slots asm("r1") = owner + 0xC;
                do {
                    register s32 next asm("r0") = index + 1;
                    next <<= 24;
                    index = (u32)next >> 24;
                } while ((u32)index < scan_bound &&
                    *(s32 *)(slots + (index << 2)) == 0);
            }
            if (index ==
                    ((*(u32 *)((char *)child + 0x2C) >> 1) + 0x19) &&
                    *(void **)(owner + 0x10) == 0) {
                func_08095114(owner);
            }
            break;
        }
        }
    }
}
