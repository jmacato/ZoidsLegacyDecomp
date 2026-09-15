#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_080D2790(s32);

void sub_080D558C(void *arg0)
{
    register char *owner asm("r4") = arg0;
    register u32 *state asm("r5") = (u32 *)(owner + 0x8C);
    register u32 state_value asm("r0") = *state;

    if (state_value <= 7U) {
        if (state_value == 0) {
            void *child;

            child = func_080D2450(owner, 1, 0,
                (s16)(*(s32 *)(owner + 4) - 0x100),
                (s32)*(s16 *)(owner + 8), 0x10, 0x080D2529, 1);
            *(void **)(owner + 0xC) = child;
            *(s32 *)((u8 *)child + 0x28) = 0x20;
            func_080D2790(0);
        }

        {
            void *child;
            register u32 next asm("r2");
            register u32 offset asm("r3");
            register void **slot asm("r1");

            child = func_080D2450(owner, 0, 0,
                (s16)(*(s32 *)(owner + 4) + 0xFF00 + (*state << 5)),
                (s32)*(s16 *)(owner + 8), 0x400, 0, 1);
            next = *state;
            next += 1;
            asm volatile("" : "+r"(next));
            offset = next << 2;
            asm volatile("" : "+r"(offset));
            slot = (void **)(owner + 0xC);
            asm volatile("" : "+r"(slot));
            slot = (void **)((u8 *)slot + offset);
            *slot = child;
            *state = next;
        }
        return;
    }

    if (state_value == 8) {
        *(void **)(owner + 0x30) = func_080D2450(owner, 2, 0,
            *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
            0x400, 0, 0);
        func_080D12A0(6, 0);
        func_080D2790(1);
        *state = *state + 1;
        return;
    }

    if (state_value == 9) {
        register u32 i asm("r1") = 0;

        if (*(void **)(owner + 0xC) == 0) {
            register void **slots asm("r2") = (void **)(owner + 0xC);

            do {
                register u32 next asm("r0") = i + 1;

                next <<= 24;
                i = next >> 24;
                if (i > 8U) {
                    break;
                }
                {
                    register u32 offset asm("r0") = i << 2;
                    register void **slot asm("r0");

                    slot = (void **)((u32)slots + offset);
                    asm volatile("" : "+r"(slot));
                    if (*slot != 0) {
                        break;
                    }
                }
            } while (1);
        }
        if (i == 9) {
            func_08095114(owner);
        }
    }
}
