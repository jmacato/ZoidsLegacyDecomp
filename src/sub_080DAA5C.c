#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DAA5C(void *arg0)
{
    register char *owner asm("r6") = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    register s32 state asm("r1") = *p8C;
    register s32 index;

    if (state == 0) {
        register s32 *state_slot asm("r10");
        register s32 *children asm("r9");
        register u32 *rng asm("r8");
        void *created;

        created = func_080D2450(owner, 0, 0,
            (s16)(*(s32 *)(owner + 4) - 0x80),
            (s32)*(s16 *)(owner + 8), state, state, 1);
        *(void **)(owner + 0xC) = created;
        index = 0;
        state_slot = p8C;
        children = (s32 *)(owner + 0xC);
        {
            register u32 *rng_init asm("r1") = &D_03000010;

            asm volatile("" : "+r"(rng_init));
            rng = rng_init;
        }
        do {
            register s32 random_r4 asm("r4");
            register s32 angle_r5 asm("r5");
            register s32 perturb_r0 asm("r0");
            register s32 priority_random_r0 asm("r0");
            register s32 priority_r1 asm("r1");
            register s32 priority_base asm("r2");
            register s32 next asm("r2");
            register s32 child_off asm("r1");
            void *spawned;

            {
                register u32 *rng_view asm("r2") = rng;

                random_r4 = func_080ECD5C(*rng_view);
            }
            angle_r5 = func_080ECD98(index << 5, 7);
            perturb_r0 = (u32)(random_r4 * 9) >> 15;
            perturb_r0 += 108;
            angle_r5 += perturb_r0;
            {
                register u32 *rng_view asm("r1") = rng;

                priority_random_r0 = func_080ECD5C(*rng_view);
            }
            priority_r1 = priority_random_r0 << 9;
            priority_r1 += priority_random_r0;
            priority_r1 = (u32)priority_r1 >> 15;
            priority_base = 0x200;
            asm volatile("" : "+r"(priority_base));
            priority_r1 += priority_base;
            {
                register s32 spawn_x asm("r3");

                priority_random_r0 = 4;
                spawn_x = *(s16 *)(owner + priority_random_r0);
                asm volatile("" :: "r"(priority_base));
                {
                    register s32 y_off asm("r2") = 8;
                    register s32 spawn_y asm("r0");

                    spawn_y = *(s16 *)(owner + y_off);
                    spawned = func_080D2660(owner, 1, 0, spawn_x, spawn_y,
                        0x500, angle_r5, priority_r1, 0);
                }
            }
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 7);
        func_080D2790(0);
        {
            register s32 *slot asm("r1") = state_slot;

            *slot = *slot + 1;
        }
        return;
    }

    index = 0;
    if (*(s32 *)(owner + 0xC) == 0) {
        s32 *children = (s32 *)(owner + 0xC);
        s32 off;

        do {
            register s32 next asm("r0") = index + 1;

            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 8 &&
            (off = index << 2,
             *(s32 *)((char *)children + off)) == 0);
    }
    if (index == 9) {
        func_08095114(owner);
    }
}
