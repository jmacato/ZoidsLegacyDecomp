#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DA3F4(void *arg0) {
    char *owner = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    u32 state = *p8C;
    register s32 index asm("r6");

    if (state == 0) {
        register s32 *state_slot asm("r10");
        register s32 *children asm("r9");
        register u32 *rng asm("r5");
        void *created;

        created = func_080D2450(owner, 0, 0,
            *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
            0x400, state, 1);
        *(void **)(owner + 0xC) = created;
        index = 0;
        state_slot = p8C;
        children = (s32 *)(owner + 0xC);
        rng = &D_03000010;
        do {
            register s32 angle_r4 asm("r4");
            register s32 random_r0 asm("r0");
            register s32 perturb_r1 asm("r1");
            register s32 child_off asm("r1");
            register s32 next asm("r2");
            s32 priority;
            void *spawned;

            random_r0 = func_080ECD5C(*rng);
            angle_r4 = index << 4;
            perturb_r1 = (u32)(random_r0 * 0x11) >> 15;
            perturb_r1 += 56;
            angle_r4 += perturb_r1;
            priority = (func_080ECD5C(*rng) * 0x81) >> 15;
            priority += 0x80;
            spawned = func_080D2660(owner, 1, 0,
                *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                0x500, angle_r4, priority, 0);
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 7);
        index = 0;
        rng = &D_03000010;
        do {
            register s32 angle_r4 asm("r4");
            register s32 random_r0 asm("r0");
            register s32 perturb_r1 asm("r1");
            register s32 child_off asm("r1");
            register s32 next asm("r0");
            s32 priority;
            void *spawned;

            random_r0 = func_080ECD5C(*rng);
            angle_r4 = index << 3;
            perturb_r1 = (u32)(random_r0 * 9) >> 15;
            perturb_r1 -= 68;
            angle_r4 += perturb_r1;
            priority = (func_080ECD5C(*rng) * 0x101) >> 15;
            priority += 0x100;
            spawned = func_080D2660(owner, 1, 0,
                *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                0x500, angle_r4, priority, 0);
            child_off = index + 9;
            child_off <<= 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next = index + 1;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 0xF);
        index = 0;
        {
            register u32 *rng3 asm("r8") = &D_03000010;
            do {
                register s32 random_r4 asm("r4");
                register s32 angle_r5 asm("r5");
                register s32 perturb_r0 asm("r0");
                register s32 priority_base asm("r0");
                register s32 child_off asm("r1");
                register s32 next asm("r0");
                s32 priority;
                void *spawned;

                {
                    register u32 *rng_view asm("r1") = rng3;
                    random_r4 = func_080ECD5C(*rng_view);
                }
                angle_r5 = func_080ECD98(index << 6, 6);
                perturb_r0 = (u32)(random_r4 * 9) >> 15;
                perturb_r0 += 108;
                angle_r5 += perturb_r0;
                {
                    register u32 *rng_view asm("r2") = rng3;
                    priority = (func_080ECD5C(*rng_view) * 0x201) >> 15;
                }
                priority_base = 0x200;
                __asm__ volatile ("" : "+r" (priority_base));
                priority += priority_base;
                spawned = func_080D2660(owner, 2, 0,
                    *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                    0x20, angle_r5, priority, 0);
                child_off = index + 25;
                child_off <<= 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;
                next = index + 1;
                next <<= 24;
                index = (u32)next >> 24;
            } while ((u32)index <= 6);
        }
        func_080D12A0(8, 0);
        func_080D2790(0);
        {
            register s32 *slot asm("r1") = state_slot;
            *slot = *slot + 1;
        }
    } else {
        index = 0;
        if (*(s32 *)(owner + 0xC) == 0) {
            s32 *children2 = (s32 *)(owner + 0xC);
            s32 off;
            do {
                register s32 next asm("r0") = index + 1;
                next <<= 24;
                index = (u32)next >> 24;
            } while ((u32)index <= 0x1F &&
                (off = index << 2,
                 *(s32 *)((char *)children2 + off)) == 0);
        }
        if (index == 0x20) {
            func_08095114(owner);
        }
    }
}
