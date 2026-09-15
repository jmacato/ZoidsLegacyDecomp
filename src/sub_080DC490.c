#include "m2c_prelude.h"

void func_08095114(void *);
void *func_080D2660(void *, s32, s32, s32);
u32 func_080ECD5C(u32);

extern u32 D_03000010;

struct OwnerDC490 {
    u8 pad_0[4];
    s32 x;
    s32 y;
    void *slots[32];
    u32 count;
};

void sub_080DC490(struct OwnerDC490 *arg0)
{
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    register struct OwnerDC490 *owner asm("r6") = arg0;
    register u32 count asm("r0") = owner->count;

    asm volatile("" : "=m"(reserve0), "=m"(reserve1),
                       "=m"(reserve2), "=m"(reserve3),
                       "=m"(reserve4));

    if (count <= 31U) {
        u32 variant = 1;
        register u32 *rng asm("r5");
        register s32 x asm("r8");
        register s32 x_low asm("r2");
        register s32 y asm("r4");
        register u32 random asm("r0");
        register s32 priority asm("r1");
        register volatile s32 *outgoing asm("sp");
        void *created;

        variant &= count;
        rng = &D_03000010;
        random = func_080ECD5C(*rng);
        x_low = owner->x;
        x_low += (random * 0x41) >> 15;
        x_low -= 0x20;
        x_low = (s16)x_low;
        x = x_low;
        random = func_080ECD5C(*rng);
        y = owner->y;
        y += (random * 0x41) >> 15;
        y -= 0x20;
        y = (s16)y;
        random = func_080ECD5C(*rng);
        priority = (random * 0x101) >> 15;
        priority += 0x200;

        outgoing[0] = y;
        if (variant == 0) {
            outgoing[1] = 0x420;
        } else {
            outgoing[1] = 0x400;
        }
        outgoing[2] = 0;
        outgoing[3] = priority;
        outgoing[4] = 0;
        {
            register void *call_owner asm("r0") = owner;
            register s32 call_variant asm("r1") = variant;
            register s32 call_zero asm("r2") = 0;
            register s32 call_x asm("r3") = x;

            created = func_080D2660(call_owner, call_variant, call_zero, call_x);
        }

        {
            register u32 *count_slot asm("r4") = &owner->count;
            register u32 index asm("r2") = *count_slot;
            register u32 offset asm("r3") = index << 2;
            register u8 *slots asm("r1") = (u8 *)&owner->slots[0];

            *(void **)(slots + offset) = created;
            index += 1;
            *count_slot = index;
        }
        return;
    }

    {
        register u32 i asm("r1") = 0;

        if (owner->slots[0] == 0) {
            register void **slots asm("r2") = &owner->slots[0];

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
    }
}
