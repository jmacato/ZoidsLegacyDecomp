#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080DB1D8(void *arg0)
{
    register char *owner asm("r5") = arg0;
    register s32 *p8C asm("r4") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *p8C;
    register s32 index asm("r6");

    switch (state) {
    case 0:
        goto phase0;
    case 1:
        goto phase1;
    case 2:
        goto phase2;
    default:
        return;
    }

phase0:
    *(void **)(owner + 0xC) = func_080D2450(owner, 0, 0,
        *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8), 0x400, 0, 1);
    *p8C = *p8C + 1;
    return;

phase1:
    if (*(u16 *)(*(char **)(owner + 0xC) + 0x14) == 5) {
        register s32 *state_slot asm("r9");
        register s32 *children asm("r8");
        register u32 *rng;

        index = 0;
        state_slot = p8C;
        children = (s32 *)(owner + 0xC);
        rng = &D_03000010;
        do {
            register s32 angle_r4 asm("r4");
            register s32 random_r0 asm("r0");
            register s32 priority_r1 asm("r1");
            register s32 priority_base asm("r0");
            register s32 next asm("r2");
            register s32 child_off asm("r1");
            void *spawned;

            random_r0 = func_080ECD5C(*rng);
            angle_r4 = random_r0 << 1;
            angle_r4 += random_r0;
            angle_r4 <<= 4;
            angle_r4 += random_r0;
            angle_r4 = (u32)angle_r4 >> 15;
            angle_r4 += 0x80;
            random_r0 = func_080ECD5C(*rng);
            priority_r1 = random_r0 << 9;
            priority_r1 += random_r0;
            priority_r1 = (u32)priority_r1 >> 15;
            priority_base = 0x200;
            priority_r1 += priority_base;
            spawned = func_080D2660(owner, 1, 0,
                *(s16 *)(owner + 4), (s32)*(s16 *)(owner + 8),
                0x500, angle_r4, priority_r1, 0);
            next = index + 1;
            child_off = next << 2;
            *(s32 *)((char *)children + child_off) = (s32)spawned;
            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 7);
        func_080D12A0(8, 0);
        func_080D2790(0);
        {
            register s32 *slot asm("r1") = state_slot;

            *slot = *slot + 1;
        }
    }
    return;

phase2:
    index = 0;
    if (*(s32 *)(owner + 0xC) == 0) {
        s32 *children = (s32 *)(owner + 0xC);
        s32 off;

        do {
            register s32 next asm("r0") = index + 1;

            next <<= 24;
            index = (u32)next >> 24;
        } while ((u32)index <= 8 &&
            (off = index << 2,
             *(s32 *)((char *)children + off)) == 0);
    }
    if (index == 9) {
        func_08095114(owner);
    }
}
