#include "m2c_prelude.h"

void func_08095114(void *);
void *func_080D2450(void *, s32, s32, s32);
void func_080D12A0(s32, s32);
void func_080D2790(s32);
u32 func_080ECD5C(u32);

extern u32 D_03000010;

struct OwnerE0060 {
    u8 pad_0[4];
    s32 x;
    s32 y;
    void *slots[32];
    s32 state;
    u32 count;
};

void sub_080DFF84(struct OwnerE0060 *arg0)
{
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    register struct OwnerE0060 *owner asm("r6") = arg0;
    register s32 *state_slot asm("r8") = &owner->state;
    s32 state = *state_slot;

    asm volatile("" : "=m"(reserve0), "=m"(reserve1),
                       "=m"(reserve2), "=m"(reserve3));

    if (state == 0) {
        register u32 *rng asm("r5") = &D_03000010;
        register s32 x asm("r4");
        register s32 y asm("r2");
        void *created;
        u32 *count_slot;
        register u32 index asm("r3");
        register u32 random asm("r0");
        register volatile s32 *outgoing asm("sp");

        random = func_080ECD5C(*rng);
        x = owner->x - 0x20;
        x += (random * 0x41) >> 15;
        x = (s16)x;
        random = func_080ECD5C(*rng);
        y = owner->y - 0x20;
        y += (random * 0x41) >> 15;
        y = (s16)y;
        outgoing[0] = y;
        outgoing[1] = state;
        outgoing[2] = state;
        outgoing[3] = state;
        {
            register void *call_owner asm("r0") = owner;
            register s32 call_zero1 asm("r1") = 0;
            register s32 call_zero2 asm("r2") = 0;
            register s32 call_x asm("r3");

            asm volatile("" : "+r"(call_owner));
            asm volatile("" : "+r"(call_zero1));
            asm volatile("" : "+r"(call_zero2));
            call_x = x;
            asm volatile("" : "+r"(call_x));
            created = func_080D2450(call_owner, call_zero1, call_zero2, call_x);
        }

        count_slot = &owner->count;
        index = *count_slot;
        {
            register s32 offset asm("r2") = index << 2;
            register u8 *slots asm("r1") = (u8 *)&owner->slots[0];
            asm volatile("" : "+r"(slots), "+r"(offset), "+r"(index));
            *(void **)(slots + offset) = created;
        }
        if (index == 0) {
            func_080D12A0(6, 0);
            func_080D2790(0);
        }
        *count_slot += 1;
        if (*count_slot == 16) {
            register s32 *state_view asm("r1") = state_slot;
            register s32 state_value asm("r0");

            asm volatile("" : "+r"(state_view));
            state_value = *state_view;
            state_value += 1;
            *state_view = state_value;
        }
        return;
    }

    {
        register u32 i asm("r1") = 0;

        if (owner->slots[0] == 0) {
            register void **slots asm("r2") = &owner->slots[0];

            asm volatile("" : "+r"(slots));
            do {
                register u32 next asm("r0") = i + 1;

                next <<= 24;
                i = next >> 24;
                if (i > 15U) {
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
        if (i == 16) {
            func_08095114(owner);
        }
    }
}
