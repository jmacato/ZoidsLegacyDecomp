#include "m2c_prelude.h"

struct OwnerD3F6C {
    u32 flags;
    u16 x;
    u16 y;
    u8 pad_08[0x1C];
    s32 active;
    void *parent;
    u32 phase;
    u32 counter;
};

void *func_080D2660(void *, s32, s32, s32);
u8 func_080D2754(struct OwnerD3F6C *, s32, s32);
u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D3F6C(struct OwnerD3F6C *arg0)
{
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    register struct OwnerD3F6C *owner asm("r6") = arg0;
    void *parent = owner->parent;
    register s32 old_x asm("r2") = *(s16 *)&owner->x;
    register u32 direction_test asm("r0") = owner->flags;
    register u32 direction_mask asm("r1") = 0x80;
    register s32 moved_x asm("r0");

    asm volatile("" : "=m"(reserve0), "=m"(reserve1),
                       "=m"(reserve2), "=m"(reserve3),
                       "=m"(reserve4));
    direction_mask <<= 8;
    direction_test &= direction_mask;
    if (direction_test == 0) {
        moved_x = old_x;
        asm volatile("" : "+r"(moved_x));
        moved_x -= 0x10;
    } else {
        moved_x = old_x;
        asm volatile("" : "+r"(moved_x));
        moved_x += 0x10;
    }
    owner->x = moved_x;

    if ((owner->phase & 1) == 0) {
        register u32 *rng asm("r5") = &D_03000010;
        register s32 x asm("r4");
        register s32 y asm("r2");
        register u32 random asm("r0");
        register volatile s32 *outgoing asm("sp");
        void *created;

        random = func_080ECD5C(*rng);
        x = owner->x - 2;
        x += (random * 5) >> 15;
        x = (s16)x;
        random = func_080ECD5C(*rng);
        y = owner->y - 2;
        y += (random * 5) >> 15;
        y = (s16)y;

        outgoing[0] = y;
        outgoing[1] = 0x400;
        outgoing[2] = 0x7C;
        outgoing[3] = 0x40;
        outgoing[4] = 3;
        created = func_080D2660(parent, 1, 0, x);
        {
            register u32 offset asm("r1") = owner->phase;
            register u8 *children asm("r2");

            offset >>= 2;
            offset += 0x18;
            offset <<= 2;
            children = (u8 *)parent + 0xC;
            children += offset;
            *(void **)children = created;
        }
    }

    {
        register u32 counter asm("r2") = owner->counter;

        if (counter == 0) {
            register u32 test asm("r0") = owner->flags;
            register u32 mask asm("r1") = 0x80;

            mask <<= 8;
            test &= mask;
            if (test == 0) {
                if (*(s16 *)&owner->x >= 0) {
                    goto increment;
                }
            } else if (*(s16 *)&owner->x <= 0xEF) {
                goto increment;
            }
            if (counter == 0) {
                goto finished;
            }
        }
        if (func_080D2754(owner, counter - 0x20,
                *(s16 *)&owner->y) != 0) {
            goto finished;
        }
    }

increment:
    owner->phase += 1;
    return;

finished:
    owner->flags |= 0x20000;
    owner->active = 0;
}
