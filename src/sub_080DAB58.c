#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern s32 func_080ECD98(s32, s32);
extern u32 D_03000010;

void sub_080DAB58(void *arg0) {
    register char *owner asm("r6") = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    register s32 state asm("r1") = *p8C;
    u8 index;

    if (state == 0) {
        register s32 *state_slot asm("sl");
        register s32 *children asm("r9");
        register u32 *rng asm("r8");

        *(void **)(owner + 0xC) = func_080D2450(owner, 0, 0,
            (s16)(*(s32 *)(owner + 4) - 0x80), *(s16 *)(owner + 8),
            state, state, 1);
        index = 0;
        state_slot = p8C;
        {
            register s32 *children_init asm("r0") = (s32 *)0xC;
            asm volatile("" : "+r"(children_init));
            children_init = (s32 *)((char *)children_init + (s32)owner);
            children = children_init;
        }
        {
            register u32 *rng_init asm("r1") = &D_03000010;
            asm volatile("" : "+r"(rng_init));
            rng = rng_init;
        }
        do {
            register s32 random asm("r4");
            register s32 angle asm("r5");
            register s32 perturb asm("r0");
            register s32 priority asm("r1");
            register s32 priority_base asm("r2");
            register s32 next asm("r2");
            register s32 child_offset asm("r1");
            void *spawned;

            {
                register u32 *rng_view asm("r2") = rng;
                random = func_080ECD5C(*rng_view);
            }
            angle = func_080ECD98(index << 5, 7);
            perturb = (u32)(random * 9) >> 15;
            perturb += 0x6C;
            angle += perturb;
            {
                register u32 *rng_view asm("r1") = rng;
                priority = (u32)(func_080ECD5C(*rng_view) * 0x201) >> 15;
            }
            priority_base = 0x200;
            asm volatile("" : "+r"(priority_base));
            priority += priority_base;
            {
                register s32 x_offset asm("r0");
                register s32 x_value asm("r3");

                asm volatile(
                    "mov %0, #4\n\t"
                    "ldrsh %1, [%2, %0]"
                    : "=r"(x_offset), "=r"(x_value)
                    : "r"(owner));
                spawned = func_080D2660(owner, 1, 0,
                    x_value, *(s16 *)(owner + 8),
                    0x500, angle, priority, 0);
            }
            next = index + 1;
            child_offset = next << 2;
            asm volatile("add %0, %1" : "+r"(child_offset)
                         : "r"(children));
            *(void **)child_offset = spawned;
            next <<= 24;
            index = (u32)next >> 24;
        } while (index <= 7);

        index = 0;
        rng = &D_03000010;
        do {
            register s32 random asm("r5");
            register s32 angle asm("r4");
            register s32 perturb asm("r0");
            register s32 priority asm("r1");
            register s32 priority_base asm("r0");
            register s32 child_offset asm("r1");
            void *spawned;

            {
                register u32 *rng_view asm("r1") = rng;
                random = func_080ECD5C(*rng_view);
            }
            angle = func_080ECD98(index << 5, 7);
            angle += 0x6C;
            perturb = (u32)(random * 9) >> 15;
            angle += perturb;
            angle = (u8)angle;
            {
                register u32 *rng_view asm("r2") = rng;
                priority = (u32)(func_080ECD5C(*rng_view) * 0x201) >> 15;
            }
            priority_base = 0x200;
            asm volatile("" : "+r"(priority_base));
            priority += priority_base;
            spawned = func_080D2660(owner, 2, 0,
                *(s16 *)(owner + 4), *(s16 *)(owner + 8),
                0x500, angle, priority, 0);
            child_offset = index + 9;
            child_offset <<= 2;
            asm volatile("add %0, %1" : "+r"(child_offset)
                         : "r"(children));
            *(void **)child_offset = spawned;
            asm volatile("add %0, #128" : "+r"(angle));
            *(s8 *)((char *)spawned + 0x11) = angle;
            index = (u8)(index + 1);
        } while (index <= 7);

        func_080D2790(0);
        {
            register s32 *slot asm("r1") = state_slot;
            *slot = *slot + 1;
        }
    } else {
        index = 0;
        if (*(s32 *)(owner + 0xC) == 0) {
            register char *children_view asm("r1") = owner + 0xC;
            do {
                index = (u8)(index + 1);
            } while (index <= 0x10 &&
                *(s32 *)(children_view + (index << 2)) == 0);
        }
        if (index == 0x11) {
            func_08095114(owner);
        }
    }
}
