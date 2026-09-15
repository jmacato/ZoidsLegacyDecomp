#include "m2c_prelude.h"

extern void func_08094554(void *);
extern void func_08094564(void *, s32);
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;
extern u16 D_0300004E;
extern u16 D_03000050;
extern u16 D_03000052;

void sub_080DFB64(void *arg0) {
    char *owner = arg0;
    s32 *state_slot = (s32 *)(owner + 0x8C);
    register s32 *increment_slot asm("r1");
    u32 state;

    if ((u32)*state_slot <= 2) {
        u32 random = func_080ECD5C(D_03000010) >> 7;
        u32 priority =
            ((u32)(func_080ECD5C(D_03000010) * 0x101) >> 15) + 0x200;

        func_080D2660(owner, 1, 0, 0x78, 0x40, 0x400,
            random, priority, 2);
    }

    state = *state_slot;
    switch (state) {
    case 0:
        *(void **)(owner + 0xC) =
            func_080D2450(owner, 0, 0, 0x78, 0x40, 0x520, 0, 2);
        func_080D12A0(6, 0);
        func_080D2790(0);
        goto select_state_slot;

    case 1:
        if ((**(u32 **)(owner + 0xC) & 4) == 0) {
            return;
        }
        *(void **)(owner + 0x10) =
            func_080D2450(owner, 2, 0, 0x78, 0x80, 0x110, 0, 2);
        func_080D2790(1);
        goto select_state_slot;

    case 2: {
        u32 *child = *(u32 **)(owner + 0x10);

        if ((*child & 4) == 0) {
            return;
        }
        func_08094564(child, 1);
        child = *(u32 **)(owner + 0x10);
        *child = (*child & ~0x30) | 0x20;
        func_08094554(*(void **)(owner + 0xC));
        increment_slot = (s32 *)(owner + 0x90);
        *increment_slot = 0;
        increment_slot -= 1;
        goto increment_selected;
    }

    case 3: {
        s32 *counter_slot = (s32 *)(owner + 0x90);
        s32 counter = *counter_slot + 1;

        *counter_slot = counter;
        if (counter != 60) {
            return;
        }
        D_0300004E = 0xD95;
        D_03000050 = 0x10;
        D_03000052 = 0;
        **(u32 **)0x02033F50 |= 0x400;
        *counter_slot = 0;
        goto select_state_slot;
    }

    case 4: {
        s32 *counter_slot = (s32 *)(owner + 0x90);
        s32 counter = *counter_slot + 1;

        *counter_slot = counter;
        D_03000052 = (u16)((u32)counter >> 2);
        if (counter != 64) {
            return;
        }
        func_08094554(*(void **)(owner + 0x10));
        *counter_slot = 0;
        goto select_state_slot;
    }

select_state_slot:
        increment_slot = (s32 *)(owner + 0x8C);
increment_selected:
        *increment_slot = *increment_slot + 1;
        return;

    case 5: {
        s32 random =
            (s32)(func_080ECD5C(D_03000010) * 0x1E0) >> 16;
        s32 priority =
            (s32)(func_080ECD5C(D_03000010) << 8) >> 16;
        s32 *counter_slot;
        s32 counter;

        func_080D2450(owner, 3, 0, random, priority, 0x400, 0, 2);
        counter_slot = (s32 *)(owner + 0x90);
        if ((*counter_slot & 7) == 0) {
            func_080D2790(2);
        }
        counter = *counter_slot + 1;
        *counter_slot = counter;
        if (counter == 60) {
            func_08095114(owner);
        }
        break;
    }
    }
    return;
}
