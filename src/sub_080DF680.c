#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DF680(void *arg0) {
    char *owner = arg0;
    register s32 *p8C asm("r8") = (s32 *)(owner + 0x8C);
    register s32 *increment_ptr asm("r2");
    u32 state = *p8C;

    switch (state) {
    case 0:
        {
            register s32 *p90 asm("r4") = (s32 *)(owner + 0x90);
            register s32 zero asm("r1");
            void *created;
            register s32 x asm("r3");

            x = *p90;
            x -= 0x100;
            x = (s16)x;
            created = func_080D2450(owner, 0, 0, x,
                (s16)(*(s32 *)(owner + 0x94) + 0x80),
                0x20, 0x080D6D85, 1);
            *(void **)(owner + 0xC) = created;
            *(void **)((char *)created + 0x28) = owner;
            zero = 0;
            *(s32 *)((char *)created + 0x2C) = zero;
            *(s32 *)((char *)created + 0x30) = *p90;
            func_080D2790(0);
            increment_ptr = p8C;
            goto increment_state;
        }
        return;
    case 1:
        if ((*(s32 *)*(void **)(owner + 0xC) & 0x20000) != 0) {
            register s16 *p90 asm("r5") = (s16 *)(owner + 0x90);
            register s16 *p94 asm("r4");
            register s32 index asm("r6");
            register s32 *children asm("r8");
            register s32 *child_base asm("r4");
            register u32 *rng asm("r5");
            register s32 spawn_x asm("r3");
            register s32 coord_off asm("r4");
            s32 * volatile state_slot;
            volatile s32 angle_home;
            register s16 *saved_p90 asm("r10");
            register s16 *saved_p94 asm("r9");
            void *created;

            coord_off = 0;
            spawn_x = p90[coord_off];
            p94 = (s16 *)(owner + 0x94);
            created = func_080D2450(owner, 2, 0,
                spawn_x, (s32)*p94, 0, 0, 0);
            *(void **)(owner + 0x10) = created;
            index = 0;
            increment_ptr = p8C;
            state_slot = increment_ptr;
            saved_p90 = p90;
            saved_p94 = p94;
            child_base = (s32 *)0xC;
            child_base = (s32 *)((s32)child_base + (s32)owner);
            children = child_base;
            rng = &D_03000010;
            do {
                register s32 random_r0 asm("r0");
                register s32 index_part asm("r1");
                register s32 angle_r4 asm("r4");
                register u32 priority_r0 asm("r0");
                void *spawned;
                s32 child_off;

                random_r0 = func_080ECD5C(*rng);
                index_part = index - 2;
                index_part <<= 3;
                angle_r4 = (u32)(random_r0 * 9) >> 15;
                angle_r4 += index_part;
                angle_r4 += 233;
                angle_home = angle_r4;
                priority_r0 = func_080ECD5C(*rng);
                priority_r0 >>= 7;
                priority_r0 += 0x100;
                __asm__ volatile ("" : : "r" (angle_r4));
                {
                    register s32 spawn_x2 asm("r3");
                    register s32 spawn_y asm("r1");
                    register s16 *coord_view asm("r2");
                    coord_view = saved_p90;
                    __asm__ volatile ("" : "+r" (coord_view));
                    angle_r4 = 0;
                    spawn_x2 = coord_view[angle_r4];
                    coord_view = saved_p94;
                    __asm__ volatile ("" : "+r" (coord_view));
                    angle_r4 = 0;
                    spawn_y = coord_view[angle_r4];
                    spawned = func_080D2660(owner, 3, 0,
                        spawn_x2, spawn_y, 0x20,
                        angle_home, priority_r0, 0);
                }
                child_off = index + 2;
                child_off <<= 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;
                {
                    register s32 next asm("r0") = index + 1;
                    next <<= 24;
                    next = (u32)next >> 24;
                    index = next;
                }
            } while ((u32)index <= 4);
            func_080D12A0(6, 0);
            func_080D2790(1);
            increment_ptr = state_slot;
            goto increment_state;
        }
        return;

increment_state:
        *increment_ptr = *increment_ptr + 1;
        return;

    case 2:
        {
            register s32 index asm("r6") = 0x18;
            register void *child asm("r1") = *(void **)(owner + 0xC);
            u32 child_count;
            u32 bound;
            s32 off;

            child_count = *(u32 *)((char *)child + 0x2C);
            bound = (child_count >> 1) + 0x19;
            if ((u32)index < bound && *(s32 *)(owner + 0x6C) == 0) {
                u32 scan_bound = bound;
                s32 *children = (s32 *)(owner + 0xC);
                do {
                    register s32 next asm("r0") = index + 1;
                    next <<= 24;
                    next = (u32)next >> 24;
                    index = next;
                } while ((u32)index < scan_bound &&
                    (off = index << 2,
                     *(s32 *)((char *)children + off)) == 0);
            }
            if (index == ((*(volatile u32 *)((char *)child + 0x2C) >> 1) + 0x19)) {
                index = 1;
                if (*(s32 *)(owner + 0x10) == 0) {
                    s32 *children = (s32 *)(owner + 0xC);
                    do {
                        register s32 next asm("r0") = index + 1;
                        next <<= 24;
                        next = (u32)next >> 24;
                        index = next;
                    } while ((u32)index <= 6 &&
                        (off = index << 2,
                         *(s32 *)((char *)children + off)) == 0);
                }
                if (index == 7) {
                    func_08095114(owner);
                }
            }
        }
        return;
    }
    return;
}
