#include "m2c_prelude.h"
extern s32 func_08092A90(u8);
extern s32 func_08092ADC(u8);
extern void func_08095114(void *);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern s32 func_080ECD24(s32, s32);
extern u16 func_080ECD3C(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D9F6C(void *arg0) {
    register char *owner asm("r8") = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *p8C;
    u8 index;

    if (state <= 7) {
        register s32 *children asm("r10");
        s32 * volatile state_slot;
        s32 *base;
        s32 post_state;
        s32 child_off;
        register s32 x asm("r3");
        void *created;
        register char *owner1 asm("r1") = owner;

        x = *(s32 *)(owner1 + 4);
        state <<= 5;
        x -= state;
        x = (s16)x;
        created = func_080D2450(owner, 0, 0, x,
            (s32)*(s16 *)(owner1 + 8), 0x500, 0, 0);
        post_state = *p8C;
        child_off = post_state << 2;
        base = (s32 *)(owner + 0xC);
        *(s32 *)((char *)base + child_off) = (s32)created;
        state_slot = p8C;
        children = base;

        if (post_state == 0) {
            register u32 *rng asm("r9");

            index = 0;
            rng = &D_03000010;
            do {
                register s32 value_r6 asm("r6");
                register s32 value_r4 asm("r4");
                register s32 value_r5 asm("r5");
                register s32 scaled asm("r0");
                void *spawned;

                {
                    register u32 *rng1 asm("r1") = rng;
                    register u32 random asm("r0");
                    register s32 base_angle asm("r2");
                    register s32 perturb asm("r1");
                    random = func_080ECD5C(*rng1);
                    base_angle = index << 4;
                    perturb = (random * 0x11) >> 15;
                    perturb -= 8;
                    base_angle += perturb;
                    base_angle <<= 24;
                    value_r6 = (u32)base_angle >> 24;
                }
                value_r4 = func_08092ADC(value_r6);
                __asm__ volatile ("" : "+r" (value_r4));
                value_r4 <<= 16;
                value_r4 >>= 16;
                {
                    register s32 cosine asm("r0");
                    cosine = func_08092A90(value_r6);
                    cosine = (s16)cosine;
                    value_r5 = (cosine * 2) + cosine;
                }
                {
                    register s32 arg1 asm("r1") = value_r5;
                    register s32 arg_first asm("r0");
                    arg1 = (s16)arg1;
                    __asm__ volatile ("" : "+r" (arg1));
                    arg_first = value_r4;
                    value_r6 = (u32)(func_080ECD24(arg_first, arg1) << 16) >> 24;
                }
                value_r4 = (u16)func_080ECD3C(
                    (value_r4 * value_r4) + (value_r5 * value_r5));
                {
                    register u32 *rng2 asm("r2") = rng;
                    scaled = value_r4 *
                        ((func_080ECD5C(*rng2) * 0x81) >> 15);
                }
                if (scaled < 0) {
                    scaled += 0xFF;
                }
                value_r4 -= scaled >> 8;
                {
                    register s16 *spawn_owner asm("r0") = (s16 *)owner;
                    register s32 spawn_x asm("r3");
                    s32 spawn_y;
                    spawn_x = spawn_owner[2];
                    spawn_y = spawn_owner[4];
                    spawned = func_080D2660(owner, 1, 0, spawn_x,
                        spawn_y, 0x500, value_r6, value_r4, 0);
                }
                {
                    register s32 child_off asm("r1") = index;
                    child_off += 8;
                    child_off <<= 2;
                    *(s32 *)((char *)children + child_off) = (s32)spawned;
                }
                index = (u8)(index + 1);
            } while ((u32)index <= 0xF);
            func_080D2790(0);
        }
        {
            s32 *slot = state_slot;
            *slot = *slot + 1;
        }
    } else {
        register char *owner2 asm("r2");

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
