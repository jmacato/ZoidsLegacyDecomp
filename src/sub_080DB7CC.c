#include "m2c_prelude.h"

void func_08095114(void *);
void *func_080D2450(void *, s32, s32, s32);
void *func_080D2660(void *, s32, s32, s32);
void func_080D2790(s32);
u32 func_080ECD5C(u32);

extern u32 D_03000010;

void sub_080DB7CC(void *arg0)
{
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    register char *owner = arg0;
    register u32 *state_slot asm("r8") = (u32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;

    asm volatile("" : "=m"(reserve0), "=m"(reserve1),
                       "=m"(reserve2), "=m"(reserve3),
                       "=m"(reserve4));

    switch (state) {
    case 0: {
        register volatile s32 *outgoing asm("sp");
        register s32 call_x asm("r3") = *(s16 *)(owner + 4);

        asm volatile("" : "+r"(call_x));
        outgoing[0] = *(s16 *)(owner + 8);
        outgoing[1] = 0x400;
        outgoing[2] = 0;
        outgoing[3] = 0;
        *(void **)(owner + 0xC) = func_080D2450(owner, 0, 0, call_x);
        func_080D2790(0);
        goto advance;
    }

    case 1: {
        register u32 *count_slot asm("r6") = (u32 *)(owner + 0x90);
        register u32 *rng asm("r5");
        register s32 x asm("r4");
        register u32 random asm("r0");
        register s32 priority asm("r1");
        register volatile s32 *outgoing asm("sp");
        void *created;

        *count_slot = *count_slot + 1;
        rng = &D_03000010;
        asm volatile("" : "+r"(rng));
        random = func_080ECD5C(*rng);
        x = *(s32 *)(owner + 4) - 0x40;
        x += (random * 0x81) >> 15;
        x = (s16)x;

        random = func_080ECD5C(*rng);
        priority = (random * 0x101) >> 15;
        priority += 0x80;

        outgoing[0] = (s16)(*(s32 *)(owner + 8) - 0xF);
        outgoing[1] = 0x400;
        outgoing[2] = 0xC0;
        outgoing[3] = priority;
        outgoing[4] = 0;
        created = func_080D2660(owner, 1, 0, x);

        {
            register u32 index asm("r3") = *count_slot;
            register u32 offset asm("r2") = index << 2;
            register u8 *slots asm("r1") = (u8 *)(owner + 0xC);

            *(void **)(slots + offset) = created;
            if (index != 31) {
                break;
            }
        }

advance: {
            register u32 *state_view asm("r1") = state_slot;
            register u32 state_value asm("r0");

            asm volatile("" : "+r"(state_view));
            state_value = *state_view;
            state_value += 1;
            *state_view = state_value;
        }
        break;
    }

    case 2: {
        register u32 i asm("r1") = 0;

        if (*(void **)(owner + 0xC) == 0) {
            register void **slots asm("r2") = (void **)(owner + 0xC);

            do {
                register u32 next asm("r0") = i + 1;

                next <<= 24;
                i = next >> 24;
                if (i > 31U) {
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
        if (i == 32) {
            func_08095114(owner);
        }
        break;
    }
    }
}
