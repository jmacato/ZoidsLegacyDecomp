#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void func_080D2790(s32);

void sub_080DE0F8(void *arg0) {
    register char *owner asm("r5") = arg0;
    register s32 *state_slot asm("r4") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;

    switch (state) {
    case 0: {
        register s32 selector asm("r6") = *(s32 *)(owner + 0x98);
        register s32 *x_slot asm("r4");
        register void *child asm("r0");

        if (selector == 0) {
            x_slot = (s32 *)(owner + 0x90);
            child = func_080D2450(owner, 2, 0,
                (s16)(*x_slot - 0x100), *(s16 *)(owner + 0x94),
                0x20, 0x080D63D1, 1);
            *(void **)(owner + 0xC) = child;
            *(void **)((char *)child + 0x28) = owner;
            *(s32 *)((char *)child + 0x2C) = selector;
            *(s32 *)((char *)child + 0x30) = *x_slot;
            *(s32 *)((char *)child + 0x34) = 2;
        } else {
            x_slot = (s32 *)(owner + 0x90);
            child = func_080D2450(owner, 0, 0,
                (s16)(*x_slot - 0x100),
                (s16)(*(s32 *)(owner + 0x94) - 0x80),
                0x20, 0x080D6E6D, 1);
            *(void **)(owner + 0xC) = child;
            *(void **)((char *)child + 0x28) = owner;
            *(s32 *)((char *)child + 0x2C) = 0;
            *(s32 *)((char *)child + 0x30) = *x_slot;
        }
        func_080D2790(0);
        {
            register s32 *slot asm("r1") = (s32 *)(owner + 0x8C);
            *slot = *slot + 1;
        }
        break;
    }
    case 1:
        if ((**(u32 **)(owner + 0xC) & 0x20000) == 0) {
            break;
        }
        {
            register char *coords asm("r0") = owner + 0x90;
            register s32 offset asm("r1");
            register s32 x_value asm("r3");

            asm volatile(
                "mov %1, #0\n\t"
                "ldrsh %2, [%0, %1]\n\t"
                "add %0, #4\n\t"
                "mov %1, #0\n\t"
                "ldrsh %0, [%0, %1]"
                : "+r"(coords), "=r"(offset), "=r"(x_value));
            *(void **)(owner + 0x10) = func_080D2450(owner, 4, 0,
                x_value, (s32)coords, 0, 0, 0);
        }
        func_080D12A0(6, 0);
        func_080D2790(1);
        *state_slot = *state_slot + 1;
        break;
    case 2: {
        register s32 index asm("r2") = 0x18;
        register void *child asm("r1") = *(void **)(owner + 0xC);
        register u32 raw_count asm("r0") = *(u32 *)((char *)child + 0x2C);
        register u32 bound asm("r3");

        raw_count >>= 1;
        bound = raw_count + 0x19;
        if (index < bound && *(s32 *)(owner + 0x6C) == 0) {
            register u32 scan_bound asm("r4") = bound;
            register char *slots asm("r3") = owner + 0xC;
            do {
                register s32 next asm("r0") = index + 1;
                next <<= 24;
                index = (u32)next >> 24;
            } while (index < scan_bound &&
                *(s32 *)(slots + (index << 2)) == 0);
        }
        if (index == ((*(u32 *)((char *)child + 0x2C) >> 1) + 0x19)
                && *(void **)(owner + 0x10) == 0) {
            func_08095114(owner);
        }
        break;
    }
    }
}
