#include "m2c_prelude.h"

extern void func_08094554(void *);
extern void func_08095114(void *);
extern void func_08095208(void *, void *, s32);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_080D2790(s32);
extern void func_080DCDC4(void *);

extern s32 D_02034034;
extern s32 D_020348B4;
extern s32 D_03000054[];
extern u8 D_087A2AF0[];
extern u8 D_087A2A50[];

void sub_080DCEC0(void *arg0) {
    char *owner = arg0;
    register s32 *state_slot asm("r7") = (s32 *)(owner + 0x8C);
    u32 state = *state_slot;
    u32 frame;
    register s32 *slot asm("r6");

    if (state <= 1) {
        goto pre;
    }
    slot = state_slot;
    if (state != 2) {
        goto dispatch;
    }
    frame = *(u16 *)(*(char **)(owner + 0xC) + 0x14);
    if (frame > 7) {
        goto post;
    }
pre:
    {
        s32 *counter = (s32 *)(owner + 0x90);
        if ((*counter & 1) == 0) {
            func_080DCDC4(owner);
        }
        *counter += 1;
        slot = state_slot;
        if (*counter == 60) {
            *slot += 1;
        }
        goto dispatch;
    }
post:
    if (frame == 9) {
        u8 i = 1;
        char *children = owner + 0xC;
        do {
            void *p = *(void **)(children + (i << 2));
            if (p != 0) {
                func_08094554(p);
            }
            i = (u8)(i + 1);
        } while (i <= 31);
    }

dispatch:
    {
    u32 sv = *slot;
    switch (sv) {
    case 0:
        if (*(s32 *)(owner + 0x90) == 1) {
            func_080D2790(0);
        }
        break;
    case 1:
        *(void **)(owner + 0xC) = func_080D2450(owner, 0, 0, *(s16 *)(owner + 4), *(s16 *)(owner + 8), 0x500, 0, 0);
        goto advance;
    case 2: {
        char *child = *(char **)(owner + 0xC);
        if (child == 0) {
            goto advance;
        }
        if (*(u16 *)(child + 0x16) == 0) {
            func_08095208(&D_087A2A50[D_087A2AF0[*(u16 *)(child + 0x14)] << 4],
                (void *)((D_020348B4 << 5) + 0x05000200), 0x10);
        }
        break;
    }
    case 3: {
        s32 *t = (s32 *)(owner + 0x94);
        *t += 1;
        if (*t != 30) {
            break;
        }
        goto advance;
    }
    case 4: {
        s32 xv = *(s32 *)(owner + 4);
        s32 tx = D_02034034 / 0x100 - 0x80;
        s32 x = (s16)(xv + tx);
        s32 y = (s16)(*(s32 *)(owner + 8) + D_03000054[1] / 0x100);
        *(void **)(owner + 0xC) = func_080D2450(owner, 2, 0, x, y, 0x1500, 0, 0);
        func_080D12A0(12, 0);
        func_080D2790(1);
    advance:
        *slot += 1;
        break;
    }
    case 5:
        if (*(void **)(owner + 0xC) == 0) {
            func_08095114(owner);
        }
        break;
    }
    }
}
