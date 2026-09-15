#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DAED8(void *arg0) {
    char *owner = arg0;
    register s32 *p8C asm("r8") = (s32 *)(owner + 0x8C);
    u32 state = *p8C;
    register s32 index asm("r6");

    if (state == 0) {
        register s16 *p90_stage asm("r5") = (s16 *)(owner + 0x90);
        register s16 *p94_stage asm("r4");
        register s16 *p90 asm("r10");
        register s16 *p94 asm("r9");
        register s32 *children asm("r8");
        s32 * volatile state_slot;
        register s32 x asm("r3");
        void *created;

        x = *(s32 *)p90_stage;
        x -= 0x80;
        x <<= 16;
        x >>= 16;
        p94_stage = (s16 *)(owner + 0x94);
        created = func_080D2450(owner, 0, 0, x, (s32)*p94_stage,
            0, 0, 1);
        *(void **)(owner + 0xC) = created;
        index = 0;
        state_slot = p8C;
        p90 = p90_stage;
        p94 = p94_stage;
        {
            register s32 *child_base asm("r1") = (s32 *)0xC;
            __asm__ volatile ("" : "+r" (child_base));
            child_base = (s32 *)((s32)child_base + (s32)owner);
            children = child_base;
        }
        do {
            register s32 random_r4 asm("r4");
            register s32 angle_r0 asm("r0");
            register s32 angle_r4 asm("r4");
            register s32 perturb_r1 asm("r1");
            register s32 priority_base asm("r0");
            register s32 child_off asm("r1");
            register s32 next asm("r2");
            register s32 priority_r1 asm("r1");
            void *spawned;

            {
                register u32 *rng_view asm("r2") = &D_03000010;
                random_r4 = func_080ECD5C(*rng_view);
            }
            angle_r0 = func_080ECD98(index << 5, 7);
            angle_r0 += 108;
            perturb_r1 = (u32)(random_r4 * 9) >> 15;
            angle_r0 += perturb_r1;
            angle_r0 <<= 24;
            angle_r4 = (u32)angle_r0 >> 24;
            {
                register u32 *rng_view asm("r5") = &D_03000010;
                priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
            }
            priority_base = 0x200;
            priority_r1 += priority_base;
            {
                register s16 *coord_view asm("r2");
                register s32 coord_off asm("r5");
                register s32 spawn_x asm("r3");
                register s32 spawn_y asm("r0");
                coord_view = p90;
                coord_off = 0;
                spawn_x = coord_view[coord_off];
                coord_view = p94;
                coord_off = 0;
                __asm__ volatile ("" : "+r" (priority_base));
                spawn_y = coord_view[coord_off];
                spawned = func_080D2660(owner, 1, 0, spawn_x, spawn_y,
                    0x500, angle_r4, priority_r1, 0);
            }
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            {
                register s32 byte_value asm("r1") = angle_r4;
                byte_value += 0x80;
                *(u8 *)((char *)spawned + 0x11) = byte_value;
            }
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 7);

        index = 0;
        do {
            register s32 random_r4 asm("r4");
            register s32 angle_r5 asm("r5");
            register s32 perturb_r0 asm("r0");
            register s32 priority_base asm("r4");
            register s32 child_off asm("r1");
            register s32 next asm("r0");
            register s32 priority_r1 asm("r1");
            void *spawned;

            {
                register u32 *rng_view asm("r1") = &D_03000010;
                random_r4 = func_080ECD5C(*rng_view);
            }
            angle_r5 = func_080ECD98(index << 5, 7);
            perturb_r0 = (u32)(random_r4 * 9) >> 15;
            perturb_r0 += 108;
            angle_r5 += perturb_r0;
            {
                register u32 *rng_view asm("r2") = &D_03000010;
                priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
            }
            priority_base = 0x200;
            __asm__ volatile ("" : "+r" (priority_base));
            priority_r1 += priority_base;
            {
                register s16 *x_view asm("r0") = p90;
                register s16 *y_view asm("r4");
                register s32 coord_off asm("r2");
                register s32 spawn_x asm("r3");
                register s32 spawn_y asm("r0");
                coord_off = 0;
                spawn_x = x_view[coord_off];
                y_view = p94;
                coord_off = 0;
                __asm__ volatile ("" : "+r" (y_view));
                spawn_y = y_view[coord_off];
                spawned = func_080D2660(owner, 2, 0, spawn_x, spawn_y,
                    0x500, angle_r5, priority_r1, 0);
            }
            child_off = index + 9;
            child_off <<= 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next = index + 1;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 7);
        func_080D12A0(6, 0);
        func_080D2790(0);
        {
            register s32 *slot asm("r4") = state_slot;
            *slot = *slot + 1;
        }
    } else if (state == 1) {
        if (*(u16 *)(*(char **)(owner + 0xC) + 0x14) == 3) {
            register s16 *p90 asm("r10");
            register s16 *p94 asm("r9");
            register s32 *children asm("r8");
            s32 * volatile state_slot;

            index = 0;
            {
                register s32 *state_view asm("r5") = p8C;
                state_slot = state_view;
            }
            {
                register s16 *p90_init asm("r0") = (s16 *)0x90;
                __asm__ volatile ("" : "+r" (p90_init));
                p90_init = (s16 *)((s32)p90_init + (s32)owner);
                p90 = p90_init;
            }
            {
                register s16 *p94_init asm("r1") = (s16 *)0x94;
                __asm__ volatile ("" : "+r" (p94_init));
                p94_init = (s16 *)((s32)p94_init + (s32)owner);
                p94 = p94_init;
            }
            {
                register s32 *child_base asm("r2") = (s32 *)0xC;
                __asm__ volatile ("" : "+r" (child_base));
                child_base = (s32 *)((s32)child_base + (s32)owner);
                children = child_base;
            }
            do {
                register s32 random_r4 asm("r4");
                register s32 angle_r0 asm("r0");
                register s32 angle_r4 asm("r4");
                register s32 perturb_r1 asm("r1");
                register s32 priority_base asm("r0");
                register s32 child_off asm("r1");
                register s32 next asm("r0");
                register s32 priority_r1 asm("r1");
                void *spawned;

                {
                    register u32 *rng_view asm("r4") = &D_03000010;
                    random_r4 = func_080ECD5C(*rng_view);
                }
                angle_r0 = func_080ECD98(index << 5, 7);
                angle_r0 += 108;
                perturb_r1 = (u32)(random_r4 * 9) >> 15;
                angle_r0 += perturb_r1;
                angle_r0 <<= 24;
                angle_r4 = (u32)angle_r0 >> 24;
                {
                    register u32 *rng_view asm("r5") = &D_03000010;
                    priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
                }
                priority_base = 0x200;
                priority_r1 += priority_base;
                {
                    register s16 *coord_view asm("r2");
                    register s32 coord_off asm("r5");
                    register s32 spawn_x asm("r3");
                    register s32 spawn_y asm("r0");
                    coord_view = p90;
                    coord_off = 0;
                    spawn_x = coord_view[coord_off];
                    coord_view = p94;
                    coord_off = 0;
                    __asm__ volatile ("" : "+r" (priority_base));
                    spawn_y = coord_view[coord_off];
                    spawned = func_080D2660(owner, 1, 0, spawn_x, spawn_y,
                        0x500, angle_r4, priority_r1, 0);
                }
                child_off = index + 17;
                child_off <<= 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;
                {
                    register s32 byte_value asm("r1") = angle_r4;
                    byte_value += 0x80;
                    *(u8 *)((char *)spawned + 0x11) = byte_value;
                }
                next = index + 1;
                next <<= 24;
                index = (u32)next >> 24;
            } while ((u32)index <= 7);

            index = 0;
            do {
                register s32 random_r4 asm("r4");
                register s32 angle_r5 asm("r5");
                register s32 perturb_r0 asm("r0");
                register s32 priority_base asm("r4");
                register s32 child_off asm("r1");
                register s32 next asm("r0");
                register s32 priority_r1 asm("r1");
                void *spawned;

                {
                    register u32 *rng_view asm("r1") = &D_03000010;
                    random_r4 = func_080ECD5C(*rng_view);
                }
                angle_r5 = func_080ECD98(index << 5, 6);
                perturb_r0 = (u32)(random_r4 * 9) >> 15;
                perturb_r0 += 108;
                angle_r5 += perturb_r0;
                {
                    register u32 *rng_view asm("r2") = &D_03000010;
                    priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
                }
                priority_base = 0x200;
                __asm__ volatile ("" : "+r" (priority_base));
                priority_r1 += priority_base;
                {
                    register s16 *x_view asm("r0") = p90;
                    register s16 *y_view asm("r4");
                    register s32 coord_off asm("r2");
                    register s32 spawn_x asm("r3");
                    register s32 spawn_y asm("r0");
                    coord_off = 0;
                    spawn_x = x_view[coord_off];
                    y_view = p94;
                    coord_off = 0;
                    __asm__ volatile ("" : "+r" (y_view));
                    spawn_y = y_view[coord_off];
                    spawned = func_080D2660(owner, 2, 0, spawn_x, spawn_y,
                        0x500, angle_r5, priority_r1, 0);
                }
                child_off = index + 25;
                child_off <<= 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;
                next = index + 1;
                next <<= 24;
                index = (u32)next >> 24;
            } while ((u32)index <= 6);
            {
                register s32 *slot asm("r4") = state_slot;
                *slot = *slot + 1;
            }
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
            } while ((u32)index <= 0x1F &&
                (off = index << 2,
                 *(s32 *)((char *)children + off)) == 0);
        }
        if (index == 0x20) {
            func_08095114(owner);
        }
    }
}
