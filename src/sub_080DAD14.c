#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DAD14(void *arg0) {
    char *owner = arg0;
    register s32 *p8C asm("r8") = (s32 *)(owner + 0x8C);
    u32 state = *p8C;
    register s32 index asm("r6");

    if (state == 0) {
        register s16 *p90_stage asm("r5") = (s16 *)(owner + 0x90);
        register s16 *p94_stage asm("r4");
        register s32 *state_slot asm("r10");
        register s16 *p90 asm("r9");
        register s16 *p94 asm("r8");
        register s32 *children asm("r5");
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
        children = (s32 *)((char *)p90_stage - 132);
        do {
            register s32 random_r4 asm("r4");
            register s32 angle_r0 asm("r0");
            register s32 angle_r4 asm("r4");
            register s32 perturb_r1 asm("r1");
            register s32 priority_base asm("r2");
            register s32 priority_r1 asm("r1");
            register s32 child_off asm("r1");
            register s32 next asm("r2");
            void *spawned;

            {
                register u32 *rng_view asm("r3") = &D_03000010;
                random_r4 = func_080ECD5C(*rng_view);
            }
            angle_r0 = func_080ECD98(index << 5, 7);
            angle_r0 += 108;
            perturb_r1 = (u32)(random_r4 * 9) >> 15;
            angle_r0 += perturb_r1;
            angle_r0 <<= 24;
            angle_r4 = (u32)angle_r0 >> 24;
            {
                register u32 *rng_view asm("r1") = &D_03000010;
                priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
            }
            priority_base = 0x200;
            priority_r1 += priority_base;
            {
                register s16 *x_view asm("r3") = p90;
                register s16 *y_view asm("r2");
                register s32 x_off asm("r0") = 0;
                register s32 y_off asm("r3");
                register s32 x_r3 asm("r3");
                register s32 spawn_x asm("r12");
                register s32 spawn_y asm("r0");
                x_r3 = x_view[x_off];
                __asm__ volatile ("" : "+r" (priority_base));
                spawn_x = x_r3;
                y_view = p94;
                y_off = 0;
                __asm__ volatile ("" : "+r" (y_view));
                spawn_y = y_view[y_off];
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
        func_080D2790(0);
        func_080D12A0(6, 0);
        {
            register s32 *slot asm("r1") = state_slot;
            *slot = *slot + 1;
        }
    } else if (state == 1) {
        if (*(u16 *)(*(char **)(owner + 0xC) + 0x14) == 3) {
            register s32 *state_slot asm("r10");
            register s16 *p90 asm("r9");
            register s16 *p94 asm("r8");
            register s32 *children asm("r5");

            index = 0;
            state_slot = p8C;
            {
                register s16 *p90_init asm("r2") = (s16 *)0x90;
                __asm__ volatile ("" : "+r" (p90_init));
                p90_init = (s16 *)((s32)p90_init + (s32)owner);
                p90 = p90_init;
            }
            {
                register s16 *p94_init asm("r3") = (s16 *)0x94;
                __asm__ volatile ("" : "+r" (p94_init));
                p94_init = (s16 *)((s32)p94_init + (s32)owner);
                p94 = p94_init;
            }
            children = (s32 *)(owner + 0xC);
            do {
                register s32 random_r4 asm("r4");
                register s32 angle_r0 asm("r0");
                register s32 angle_r4 asm("r4");
                register s32 perturb_r1 asm("r1");
                register s32 priority_base asm("r3");
                register s32 priority_r1 asm("r1");
                register s32 child_off asm("r1");
                register s32 next asm("r0");
                void *spawned;

                {
                    register u32 *rng_view asm("r1") = &D_03000010;
                    random_r4 = func_080ECD5C(*rng_view);
                }
                angle_r0 = func_080ECD98(index << 5, 7);
                angle_r0 += 108;
                perturb_r1 = (u32)(random_r4 * 9) >> 15;
                angle_r0 += perturb_r1;
                angle_r0 <<= 24;
                angle_r4 = (u32)angle_r0 >> 24;
                {
                    register u32 *rng_view asm("r2") = &D_03000010;
                    priority_r1 = (func_080ECD5C(*rng_view) * 0x201) >> 15;
                }
                priority_base = 0x200;
                priority_r1 += priority_base;
                {
                    register s16 *x_view asm("r0") = p90;
                    register s16 *y_view asm("r3");
                    register s32 coord_off asm("r2");
                    register s32 x_r0 asm("r0");
                    register s32 spawn_x asm("r12");
                    register s32 spawn_y asm("r0");
                    coord_off = 0;
                    x_r0 = x_view[coord_off];
                    __asm__ volatile ("" : "+r" (priority_base));
                    spawn_x = x_r0;
                    y_view = p94;
                    coord_off = 0;
                    __asm__ volatile ("" : "+r" (y_view));
                    spawn_y = y_view[coord_off];
                    spawned = func_080D2660(owner, 1, 0, spawn_x, spawn_y,
                        0x500, angle_r4, priority_r1, 0);
                }
                child_off = index + 9;
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
            {
                register s32 *slot asm("r3") = state_slot;
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
            } while ((u32)index <= 0x10 &&
                (off = index << 2,
                 *(s32 *)((char *)children + off)) == 0);
        }
        if (index == 0x11) {
            func_08095114(owner);
        }
    }
}
