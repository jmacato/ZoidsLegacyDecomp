#include "m2c_prelude.h"
extern s32 func_08092A90(u8);
extern s32 func_08092ADC(u8);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern s32 func_080ECD24(s32, s32);
extern u16 func_080ECD3C(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DA110(void *arg0) {
    register char *owner asm("r8") = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    u32 state = *p8C;
    u8 index;

    if (state <= 7) {
        register s32 x asm("r3");
        s32 post_state;
        s32 child_off;
        s32 *base;
        void *created;

        x = *(s32 *)(owner + 0x90);
        x += 0xFF20;
        x += state << 5;
        x = (s16)x;
        created = func_080D2450(owner, 0, 0, x,
            (s32)*(s16 *)(owner + 0x94), 0x400, 0, 1);
        post_state = *p8C;
        child_off = post_state << 2;
        base = (s32 *)(owner + 0xC);
        *(s32 *)((char *)base + child_off) = (s32)created;
        *p8C = post_state + 1;
    } else if (state == 8) {
        register s32 *children asm("r10");
        register u32 *rng asm("r9");
        register s32 zero asm("r6");
        s32 * volatile state_slot;
        s16 * volatile saved_p90;
        s16 * volatile saved_p94;

        index = 0;
        state_slot = p8C;
        {
            register s16 *p90 asm("r2") = (s16 *)(owner + 0x90);
            saved_p90 = p90;
        }
        {
            register s16 *p94 asm("r4") = (s16 *)(owner + 0x94);
        saved_p94 = p94;
        }
        {
            register s32 *child_base asm("r0") = (s32 *)0xC;
            __asm__ volatile ("" : "+r" (child_base));
            child_base = (s32 *)((s32)child_base + (s32)owner);
            children = child_base;
        }
        {
            register u32 *rng_init asm("r1") = &D_03000010;
            __asm__ volatile ("" : "+r" (rng_init));
            rng = rng_init;
        }
        zero = 0;
        do {
            register s32 random_r4 asm("r4");
            register s32 angle_r5 asm("r5");
            register s32 perturb_r0 asm("r0");
            register s32 priority_base asm("r0");
            s32 priority;
            void *spawned;
            s32 child_off;

            {
                register u32 *rng_view asm("r2") = rng;
                random_r4 = func_080ECD5C(*rng_view);
            }
            angle_r5 = func_080ECD98(index << 4, 7);
            perturb_r0 = (u32)(random_r4 * 5) >> 15;
            perturb_r0 -= 10;
            angle_r5 += perturb_r0;
            {
                register u32 *rng_view asm("r4") = rng;
                priority = (func_080ECD5C(*rng_view) * 0x401) >> 15;
            }
            priority_base = 0x200;
            __asm__ volatile ("" : "+r" (priority_base));
            priority += priority_base;
            {
                register s16 *coord_view asm("r2");
                register s32 coord_off asm("r4");
                register s32 spawn_x asm("r3");
                register s32 spawn_y asm("r0");
                coord_view = saved_p90;
                coord_off = 0;
                spawn_x = coord_view[coord_off];
                coord_view = saved_p94;
                coord_off = 0;
                spawn_y = coord_view[coord_off];
                spawned = func_080D2660(owner, 1, 0,
                    spawn_x, spawn_y,
                    zero, angle_r5, priority, zero);
            }
            child_off = index + 8;
            child_off <<= 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            index = (u8)(index + 1);
        } while ((u32)index <= 7);
        index = 0;
        {
            register u32 *rng2 asm("r6") = &D_03000010;
            do {
                register s32 random_r4 asm("r4");
                register s32 angle_r5 asm("r5");
                register s32 perturb_r0 asm("r0");
                s32 priority;
                void *spawned;
                s32 child_off;

                random_r4 = func_080ECD5C(*rng2);
                angle_r5 = func_080ECD98(index << 5, 7);
                perturb_r0 = (u32)(random_r4 * 9) >> 15;
                perturb_r0 -= 20;
                angle_r5 += perturb_r0;
                priority = (func_080ECD5C(*rng2) * 0x201) >> 15;
                priority += 0x200;
                {
                    register s16 *coord_view asm("r2");
                    register s32 coord_off asm("r4");
                    register s32 spawn_x asm("r3");
                    register s32 spawn_y asm("r0");
                    coord_view = saved_p90;
                    coord_off = 0;
                    spawn_x = coord_view[coord_off];
                    coord_view = saved_p94;
                    coord_off = 0;
                    spawn_y = coord_view[coord_off];
                    spawned = func_080D2660(owner, 2, 0,
                        spawn_x, spawn_y,
                        0x20, angle_r5, priority, 0);
                }
                child_off = index + 0x10;
                child_off <<= 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;
                index = (u8)(index + 1);
            } while ((u32)index <= 7);
        }
        index = 0;
        rng = &D_03000010;
        do {
            register s32 angle_r6 asm("r6");
            register s32 sine_r4 asm("r4");
            register s32 cosine3_r5 asm("r5");
            register s32 radius asm("r4");
            s32 scaled;

            {
                register u32 *rng_view asm("r1") = rng;
                register s32 random asm("r0");
                register s32 base_angle asm("r2");
                register s32 perturb asm("r1");
                random = func_080ECD5C(*rng_view);
                base_angle = index << 4;
                perturb = (u32)(random * 0x11) >> 15;
                perturb -= 8;
                base_angle += perturb;
                base_angle <<= 24;
                angle_r6 = (u32)base_angle >> 24;
            }
            sine_r4 = func_08092ADC(angle_r6);
            __asm__ volatile ("" : "+r" (sine_r4));
            sine_r4 <<= 16;
            sine_r4 >>= 16;
            {
                register s32 cosine asm("r0");
                cosine = func_08092A90(angle_r6);
                cosine = (s16)cosine;
                cosine3_r5 = (cosine * 2) + cosine;
            }
            angle_r6 = (u32)(func_080ECD24(sine_r4,
                (s16)cosine3_r5) << 16) >> 24;
            radius = (u16)func_080ECD3C(
                (sine_r4 * sine_r4) + (cosine3_r5 * cosine3_r5));
            {
                register u32 *rng_view asm("r2") = rng;
                scaled = radius *
                    ((func_080ECD5C(*rng_view) * 0x81) >> 15);
            }
            if (scaled < 0) {
                scaled += 0xFF;
            }
            radius -= scaled >> 8;
            {
                register s16 *x_view asm("r0") = saved_p90;
                register s16 *y_view asm("r2");
                register s32 coord_off asm("r1");
                register s32 spawn_x asm("r3");
                register s32 spawn_y asm("r0");
                coord_off = 0;
                spawn_x = x_view[coord_off];
                y_view = saved_p94;
                coord_off = 0;
                spawn_y = y_view[coord_off];
                func_080D2660(owner, 3, 0,
                    spawn_x, spawn_y,
                    0x500, angle_r6, radius, 0);
            }
            index = (u8)(index + 1);
        } while ((u32)index <= 0xF);
        func_080D12A0(6, 0);
        func_080D2790(1);
        {
            register s32 *slot asm("r2") = state_slot;
            *slot = *slot + 1;
        }
    } else {
        register char *owner2 asm("r4");

        index = 0;
        owner2 = owner;
        if (*(s32 *)(owner2 + 0xC) == 0) {
            register s32 *children asm("r1") = (s32 *)(owner + 0xC);
            s32 off;
            do {
                index = (u8)(index + 1);
            } while ((u32)index <= 0x17 &&
                (off = index << 2,
                 *(s32 *)((char *)children + off)) == 0);
        }
        if (index == 0x18) {
            func_08095114(owner);
        }
    }
}
