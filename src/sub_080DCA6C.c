#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;
extern u16 D_0300004E;
extern u16 D_03000050;

void sub_080DCA6C(void *arg0) {
    register char *owner asm("r6") = arg0;
    register s32 *state_slot asm("r5") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;
    register s32 index asm("r7");

    switch (state) {
    case 0: {
        register s32 zero asm("r4");
        void *created;

        created = func_080D2450(owner, 0, 0,
            (s16)(*(s32 *)(owner + 4) - 0x80),
            (s32)*(s16 *)(owner + 8), 0x20,
            ({ zero = 0; zero; }), zero);
        *(void **)(owner + 0xC) = created;
        D_0300004E = 0x2044;
        D_03000050 = 0x1004;
        *(u16 *)0x05000000 = zero;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
        break;
    }
    case 1: {
        register s32 *counter_slot asm("r4") = (s32 *)(owner + 0x94);
        register s32 old_counter asm("r0") = *counter_slot;
        register s32 counter asm("r3") = old_counter + 2;

        *counter_slot = counter;
        {
            register u16 *display asm("r2") = &D_03000050;
            *display = (old_counter + 6) | 0x1000;
        }
        if (counter == 8) {
            s32 *flags = *(s32 **)(owner + 0xC);
            *flags |= 0x20000;
        }
        if (*counter_slot == 10) {
            *state_slot = *state_slot + 1;
        }
        break;
    }
    case 2: {
        register s32 *saved_state_slot asm("r10");
        register s32 *children asm("r8");
        register u32 *rng asm("r5");

        index = 0;
        saved_state_slot = state_slot;
        children = (s32 *)(owner + 0xC);
        rng = &D_03000010;
        do {
            register s32 angle asm("r4");
            register s32 random_r0 asm("r0");
            register s32 perturb_r1 asm("r1");
            register s32 priority_random_r0 asm("r0");
            register s32 priority_r1 asm("r1");
            register s32 child_off asm("r1");
            register s32 next asm("r2");
            void *spawned;

            random_r0 = func_080ECD5C(*rng);
            angle = index << 4;
            perturb_r1 = (u32)(random_r0 * 9) >> 15;
            angle += perturb_r1;
            angle -= 4;
            priority_random_r0 = func_080ECD5C(*rng);
            priority_r1 = priority_random_r0 << 8;
            priority_r1 += priority_random_r0;
            priority_r1 = (u32)priority_r1 >> 15;
            priority_r1 += 0x200;
            __asm__ volatile ("" : "+r" (index));
            spawned = func_080D2660(owner, 1, 0,
                *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                0x500, angle, priority_r1, 0);
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 15);

        index = 0;
        {
            register u32 *rng_init asm("r4") = &D_03000010;
            register u32 *rng2 asm("r9") = rng_init;
            do {
                register s32 random_r5 asm("r5");
                register s32 angle asm("r4");
                register s32 angle_arg asm("r0");
                register s32 perturb_r0 asm("r0");
                register s32 priority_random_r0 asm("r0");
                register s32 priority_r1 asm("r1");
                register s32 priority_base asm("r0");
                register s32 child_off asm("r1");
                register s32 next asm("r0");
                void *spawned;

                {
                    register u32 *rng_view asm("r1") = rng2;
                    random_r5 = func_080ECD5C(*rng_view);
                }
                angle_arg = 107;
                angle_arg *= index;
                angle = func_080ECD98(angle_arg, 7);
                angle += 81;
                perturb_r0 = (u32)(random_r5 * 9) >> 15;
                angle += perturb_r0;
                angle = (u8)angle;
                {
                    register u32 *rng_view asm("r2") = rng2;
                    priority_random_r0 = func_080ECD5C(*rng_view);
                }
                priority_r1 = priority_random_r0 << 8;
                priority_r1 += priority_random_r0;
                priority_r1 = (u32)priority_r1 >> 15;
                priority_base = 0x100;
                priority_r1 += priority_base;
                {
                    register s32 spawn_x asm("r3");
                    __asm__ volatile ("" : "+r" (index));
                    spawn_x = *(s16 *)(owner + 4);
                    __asm__ volatile ("" : "+r" (priority_base));
                    spawned = func_080D2660(owner, 2, 0,
                        spawn_x, (s32)*(s16 *)(owner + 8),
                        0x500, angle, priority_r1, 0);
                }
                child_off = index + 9;
                child_off <<= 2;
                *(s32 *)((char *)children + child_off) = (s32)spawned;
                angle += 0x80;
                *(u8 *)((char *)spawned + 0x11) = angle;
                next = index + 1;
                next <<= 24;
                index = (u32)next >> 24;
            } while ((u32)index <= 7);
        }
        func_080D12A0(6, 0);
        func_080D2790(1);
        D_0300004E = 0x740;
        D_03000050 = 0x1010;
        {
            s32 *flags = *(s32 **)(owner + 0xC);
            *flags = (*flags & 0xFFFDFFFF) | 0x400;
        }
        {
            register s32 *slot asm("r1") = saved_state_slot;
            *slot = *slot + 1;
        }
        break;
    }
    case 3: {
        s32 *counter_slot = (s32 *)(owner + 0x90);
        s32 counter = *counter_slot + 1;
        *counter_slot = counter;
        D_03000050 = (16 - ((u32)counter >> 1)) | 0x1000;
        if (counter == 32) {
            func_08095114(owner);
        }
        break;
    }
    }
}
