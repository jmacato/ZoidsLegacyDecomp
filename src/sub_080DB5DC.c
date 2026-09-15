#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DB5DC(void *arg0) {
    register char *owner asm("r6") = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *p8C;
    s32 index;

    switch (state) {
    case 0: {
        void *created = func_080D2450(owner, 0, 0,
            *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
            0, 0, 1);
        *(void **)(owner + 0xC) = created;
        *p8C = *p8C + 1;
        break;
    }
    case 1: {
        if (*(u16 *)(*(char **)(owner + 0xC) + 0x14) == 5) {
            register u32 *rng asm("r8");
            register s32 zero asm("r10");
            register s32 *children asm("r9");
            s32 * volatile saved_children;
            s32 * volatile state_slot;
            register s32 *child_base asm("r2");

            index = 0;
            state_slot = p8C;
            child_base = (s32 *)(owner + 0xC);
            saved_children = child_base;
            {
                register u32 *rng_init asm("r0") = &D_03000010;
                rng = rng_init;
            }
            {
                register s32 zero_init asm("r1") = 0;
                __asm__ volatile ("" : "+r" (zero_init));
                zero = zero_init;
            }
            children = child_base;
            do {
                register s32 random_r0 asm("r0");
                register s32 angle_r4 asm("r4");
                register s32 next asm("r5");
                register s32 child_off asm("r1");
                register s32 priority_r1 asm("r1");
                register s32 priority_base_r2 asm("r2");
                void *spawned;

                {
                    register u32 *rng_view asm("r2") = rng;
                    random_r0 = func_080ECD5C(*rng_view);
                }
                angle_r4 = random_r0 << 1;
                angle_r4 += random_r0;
                angle_r4 <<= 4;
                angle_r4 += random_r0;
                angle_r4 = (u32)angle_r4 >> 15;
                angle_r4 += 168;
                {
                    register u32 *rng_view asm("r1") = rng;
                    priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
                }
                priority_base_r2 = 0x200;
                priority_r1 += priority_base_r2;
                {
                    register s32 spawn_x asm("r3");
                    spawn_x = *(s16 *)(owner + 4);
                    __asm__ volatile ("" : "+r" (priority_base_r2));
                    spawned = func_080D2660(owner, 1, 0,
                        spawn_x, (s32)*(s16 *)(owner + 8),
                        ({
                            register s32 flags asm("r0") = 0x500;
                            flags;
                        }),
                        angle_r4, priority_r1,
                        ({
                            register s32 zero_view asm("r1") = zero;
                            __asm__ volatile ("" : "+r" (zero_view));
                            zero_view;
                        }));
                }
                next = index + 1;
                child_off = next << 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;

                {
                    register u32 *rng_view asm("r2") = rng;
                    random_r0 = func_080ECD5C(*rng_view);
                }
                angle_r4 = random_r0 << 1;
                angle_r4 += random_r0;
                angle_r4 <<= 4;
                angle_r4 += random_r0;
                angle_r4 = (u32)angle_r4 >> 15;
                angle_r4 += 40;
                {
                    register u32 *rng_view asm("r1") = rng;
                    priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
                }
                {
                    register s32 priority_base asm("r2") = 0x200;
                    __asm__ volatile ("" : "+r" (priority_base));
                    priority_r1 += priority_base;
                }
                spawned = func_080D2660(owner, 1, 0,
                    *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                    ({
                        register s32 flags asm("r0") = 0x500;
                        flags;
                    }),
                    angle_r4, priority_r1,
                    ({
                        register s32 zero_view asm("r1") = zero;
                        __asm__ volatile ("" : "+r" (zero_view));
                        zero_view;
                    }));
                child_off = index + 9;
                child_off <<= 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;
                next <<= 24;
                index = (u32)next >> 24;
            } while ((u32)index <= 7);

            index = 0;
            {
                register u32 *rng_init asm("r2") = &D_03000010;
                __asm__ volatile ("" : "+r" (rng_init));
                rng = rng_init;
            }
            do {
                register s32 random_r4 asm("r4");
                register s32 angle_r5 asm("r5");
                register s32 perturb_r0 asm("r0");
                register s32 priority_base asm("r0");
                register s32 child_off asm("r1");
                s32 priority;
                void *spawned;

                {
                    register u32 *rng_view asm("r1") = rng;
                    random_r4 = func_080ECD5C(*rng_view);
                }
                angle_r5 = func_080ECD98(index << 6, 7);
                perturb_r0 = (u32)(random_r4 * 9) >> 15;
                perturb_r0 -= 36;
                angle_r5 += perturb_r0;
                {
                    register u32 *rng_view asm("r2") = rng;
                    priority = (func_080ECD5C(*rng_view) * 0x201) >> 15;
                }
                priority_base = 0x200;
                priority += priority_base;
                {
                    register s32 spawn_x asm("r3");
                    spawn_x = *(s16 *)(owner + 4);
                    spawned = func_080D2660(owner, 2, 0,
                        spawn_x, (s32)*(s16 *)(owner + 8),
                        0x20, angle_r5, priority, 0);
                }
                child_off = index + 17;
                child_off <<= 2;
                {
                    register s32 *base_view asm("r2") = saved_children;
                    *(s32 *)((char *)base_view + child_off) = (s32)spawned;
                }
                index = (u8)(index + 1);
            } while ((u32)index <= 7);

            func_080D12A0(8, 0);
            func_080D2790(0);
            {
                register s32 *slot asm("r1") = state_slot;
                *slot = *slot + 1;
            }
        }
        break;
    }
    case 2: {
        index = 0;
        if (*(s32 *)(owner + 0xC) == 0) {
            s32 *children = (s32 *)(owner + 0xC);
            s32 off;
            do {
                index = (u8)(index + 1);
            } while ((u32)index <= 0x18 &&
                (off = index << 2,
                 *(s32 *)((char *)children + off)) == 0);
        }
        if (index == 0x19) {
            func_08095114(owner);
        }
        break;
    }
    }
}
