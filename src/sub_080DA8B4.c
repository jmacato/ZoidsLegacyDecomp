#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DA8B4(void *arg0) {
    register char *owner asm("r6") = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    u32 state = *p8C;
    register s32 index asm("r5");

    if (state == 0) {
        register s32 *state_slot asm("r10");
        register s32 *children asm("r8");
        u32 *rng;
        register s32 seven asm("r9");
        void *created;

        created = func_080D2450(owner, 0, 0,
            *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
            0x400, 0, 1);
        *(void **)(owner + 0xC) = created;
        index = 0;
        state_slot = p8C;
        children = (s32 *)(owner + 0xC);
        rng = &D_03000010;
        seven = 7;
        do {
            register s32 random_r4 asm("r4");
            register s32 angle_r0 asm("r0");
            register s32 angle_r4 asm("r4");
            register s32 perturb_r1 asm("r1");
            register s32 priority_random_r0 asm("r0");
            register s32 priority_work_r1 asm("r1");
            register s32 priority_seed asm("r2");
            register s32 priority_r1 asm("r1");
            register s32 child_off asm("r1");
            register s32 next asm("r2");
            void *spawned;

            random_r4 = func_080ECD5C(*rng);
            angle_r0 = func_080ECD98(index << 5, 7);
            perturb_r1 = (u32)(random_r4 * 5) >> 15;
            perturb_r1 += 110;
            angle_r4 = angle_r0 + perturb_r1;
            priority_random_r0 = func_080ECD5C(*rng);
            priority_work_r1 = priority_random_r0 << 8;
            priority_work_r1 += priority_random_r0;
            priority_seed = (u32)priority_work_r1 >> 15;
            if ((u32)index <= 3) {
                register s32 index_part asm("r1") = index << 8;
                register s32 base asm("r3") = 0x300;
                register s32 base_sum asm("r0") = priority_seed + base;
                priority_r1 = index_part + base_sum;
            } else {
                register s32 reverse asm("r0") = seven - index;
                register s32 base asm("r3") = 0x300;
                reverse <<= 8;
                priority_r1 = priority_seed + base;
                priority_r1 = reverse + priority_r1;
            }
            spawned = func_080D2660(owner, 1, 0,
                *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                0x20, angle_r4, priority_r1, 0);
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 7);

        index = 0;
        rng = &D_03000010;
        seven = 7;
        do {
            register s32 random_r4 asm("r4");
            register s32 angle_r0 asm("r0");
            register s32 angle_r4 asm("r4");
            register s32 perturb_r1 asm("r1");
            register s32 priority_random_r0 asm("r0");
            register s32 priority_work_r1 asm("r1");
            register s32 priority_seed asm("r2");
            register s32 priority_r1 asm("r1");
            register s32 child_off asm("r1");
            register s32 next asm("r0");
            void *spawned;

            random_r4 = func_080ECD5C(*rng);
            angle_r0 = func_080ECD98(index << 5, 7);
            perturb_r1 = (u32)(random_r4 * 5) >> 15;
            perturb_r1 += 110;
            angle_r4 = angle_r0 + perturb_r1;
            priority_random_r0 = func_080ECD5C(*rng);
            priority_work_r1 = priority_random_r0 << 8;
            priority_work_r1 += priority_random_r0;
            priority_seed = (u32)priority_work_r1 >> 15;
            if ((u32)index <= 3) {
                register s32 index_part asm("r1") = index << 8;
                register s32 base asm("r3") = 0x300;
                register s32 base_sum asm("r0") = priority_seed + base;
                priority_r1 = index_part + base_sum;
            } else {
                register s32 reverse asm("r0") = seven - index;
                register s32 base asm("r3") = 0x300;
                reverse <<= 8;
                priority_r1 = priority_seed + base;
                priority_r1 = reverse + priority_r1;
            }
            spawned = func_080D2660(owner, 2, 0,
                *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                0x400, angle_r4, priority_r1, 0);
            child_off = index + 9;
            child_off <<= 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next = index + 1;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 7);
        func_080D12A0(8, 0);
        func_080D2790(0);
        {
            register s32 *slot asm("r3") = state_slot;
            *slot = *slot + 1;
        }
    } else {
        index = 0;
        if (*(s32 *)(owner + 0xC) == 0) {
            s32 *children = (s32 *)(owner + 0xC);
            s32 off;
            do {
                register s32 next asm("r0") = index + 1;
                next <<= 24;
                index = (u32)next >> 24;
            } while ((u32)index <= 0x10 &&
                (off = index << 2,
                 *(s32 *)((char *)children + off)) == 0);
        }
        if (index == 0x11) {
            func_08095114(owner);
        }
    }
}
