#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D4C84(void *arg0)
{
    register char *owner asm("r5") = arg0;
    u32 *state_slot = (u32 *)(owner + 0x8C);
    register u32 state asm("r1") = *state_slot;

    if (state <= 7U) {
        register u32 *saved_state;
        register s32 *children asm("r6");

        saved_state = state_slot;
        children = (s32 *)(owner + 0xC);
        if (state == 0) {
            register s32 index asm("r4");
            void *created;

            created = func_080D2450(owner, 1, 0,
                *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                0x10, 0x080D2529, state);
            *(void **)(owner + 0xC) = created;
            *(s32 *)((u8 *)created + 0x28) = 0x20;

            index = 0;
            do {
                u32 random;
                register s32 priority asm("r1");
                void *spawned;

                random = func_080ECD5C(D_03000010);
                priority = (random * 0x41) >> 15;
                priority += 0xC0;
                spawned = func_080D2660(owner, 2, 0,
                    *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                    0x400, (index << 2) - 0xA, priority, 0);
                *(void **)((u8 *)children + ((index + 9) << 2)) = spawned;
                {
                    register u32 next asm("r0") = index + 1;

                    next <<= 24;
                    index = next >> 24;
                }
            } while ((u32)index <= 5);
            func_080D2790(0);
            func_080D12A0(5, 0);
        }

        {
            void *child;
            register u32 next asm("r2");
            register u32 offset asm("r1");

            child = func_080D2450(owner, 0, 0,
                (s16)(*(s32 *)(owner + 4) - (*saved_state << 5)),
                (s32)*(s16 *)(owner + 8), 0x400, 0, 0);
            next = *saved_state;
            next += 1;
            offset = next << 2;
            *(void **)((u8 *)children + offset) = child;
            *saved_state = next;
        }
        return;
    }

    {
        register u32 i asm("r4") = 0;

        if (*(void **)(owner + 0xC) == 0) {
            register void **slots asm("r1") = (void **)(owner + 0xC);

            do {
                register u32 next asm("r0") = i + 1;

                next <<= 24;
                i = next >> 24;
                if (i > 14U) {
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
        if (i == 15) {
            func_08095114(owner);
        }
    }
}
