#include "m2c_prelude.h"
extern void func_08095114();
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790();
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D8DEC(void *arg0) {
    char *owner = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    register s32 state asm("r1") = *p8C;
    register s32 index asm("r8");

    if (state == 0) {
        register s32 *children asm("r10");
        register u32 *rng asm("r9");
        s32 *state_slot;
        void *created;

        created = func_080D2450(owner, 0, 0, *(s16 *)(owner + 4),
            (s32)*(s16 *)(owner + 8), 0x20, 0x080D8B71, state);
        *(void **)(owner + 0xC) = created;
        index = 0;
        state_slot = p8C;
        children = (s32 *)(owner + 0xC);
        rng = &D_03000010;
        do {
            register s32 x asm("r6");
            register s32 y asm("r4");
            register s32 angle asm("r5");
            s32 priority;
            void *spawned;
            s32 next;
            s32 child_off;

            {
                register u32 *rng4 asm("r4") = rng;
                register u32 random asm("r0");
                random = func_080ECD5C(*rng4);
                x = *(s32 *)(owner + 4) - 2;
                x += (random * 5) >> 15;
                x = (s16)x;
                random = func_080ECD5C(*rng4);
                y = *(s32 *)(owner + 8) - 2;
                y += (random * 5) >> 15;
                y = (s16)y;
            }
            {
                register u32 *rng1 asm("r1") = rng;
                angle = (func_080ECD5C(*rng1) * 0x11) >> 15;
            }
            {
                register u32 *rng2 asm("r2") = rng;
                priority = ((func_080ECD5C(*rng2) * 0x41) >> 15) + 0x40;
            }
            spawned = func_080D2660(owner, 2, 0, x, y,
                0x400, angle, priority, 0);
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            {
                register s32 w asm("r2") = next;
                w <<= 24;
                w = (u32)w >> 24;
                index = w;
            }
        } while ((u32)index <= 3);
        created = *(void **)(owner + 0xC);
        *(void **)((char *)created + 0x28) = owner;
        *(s32 *)((char *)created + 0x2C) = 0;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
        return;
    }
    {
        register void *t asm("r0") = *(void **)(owner + 0xC);
        s32 c = *(s32 *)t & 0x20000;
        register void *child asm("r3") = t;

        if (c) {
            u32 bound;

            index = 1;
            bound = (*(u32 *)((char *)child + 0x2C) >> 1) + 6;
            if ((u32)index < bound && *(s32 *)(owner + 0x10) == 0) {
                u32 scan_bound = bound;
                s32 *children = (s32 *)(owner + 0xC);
                do {
                    register s32 w asm("r0");
                    w = index;
                    w += 1;
                    w <<= 24;
                    w = (u32)w >> 24;
                    index = w;
                } while ((u32)index < scan_bound &&
                    *(s32 *)((char *)children + (index << 2)) == 0);
            }
            if (index == ((*(volatile u32 *)((char *)child + 0x2C) >> 1) + 6)) {
                func_08095114(owner);
            }
        }
    }
}
