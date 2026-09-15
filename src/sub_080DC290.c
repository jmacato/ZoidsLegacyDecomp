#include "m2c_prelude.h"

extern s16 func_08092A90(s32);
extern void func_08095114(void *);
extern void *func_080D2660(void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;
extern s32 D_03000054[];

void sub_080DC290(void *arg0) {
    char *owner = arg0;

    switch (*(u32 *)(owner + 0x8C)) {
    case 0: {
        s32 x;
        s32 trig;
        s32 v;
        s32 y;

        x = (s16)(*(s32 *)(owner + 4) + ((func_080ECD5C(D_03000010) * 0x41) >> 15) - 0x20);
        trig = (s16)func_08092A90(0x36);
        v = trig << 1;
        v += trig;
        v <<= 6;
        if (v < 0) {
            v += 0xFF;
        }
        v >>= 8;
        v = 0x80 - v;
        if (*(s32 *)(owner + 0x90) != 0) {
            y = (s16)(v - 0x10);
        } else {
            y = (s16)v;
        }
        *(void **)(owner + 0xC) = func_080D2660(owner, 0, 0, x, y, 0x120, 0x4A, 0xC00, 1);
        *(s32 *)(owner + 0x8C) += 1;
        break;
    }
    case 1: {
        s32 *counter = (s32 *)(owner + 0x98);
        char *child;
        s32 x;
        s32 zero;

        *counter += 1;
        if (*counter != 0x10) {
            break;
        }
        if ((*(s32 *)owner & 2) == 0) {
            child = *(char **)(owner + 0xC);
            x = *(s16 *)(child + 4);
        } else {
            register char *c asm("r2") = *(char **)(owner + 0xC);
            x = (s16)(0xF0 - *(u16 *)(c + 4));
            child = c;
            asm volatile("" : "+&r"(child) : "r"(c));
        }
        *(void **)(owner + 0x10) = func_080D2660(owner, 1, 0, x, *(s16 *)(child + 6), 0x400, 0xC0, 0x100, (zero = 0));
        {
            char *c1 = *(char * volatile *)(owner + 0xC);
            *(u16 *)(c1 + 4) = D_03000054[4] / 0x100 + *(u16 *)(c1 + 4);
        }
        {
            char *c2 = *(char * volatile *)(owner + 0xC);
            *(u16 *)(c2 + 6) = D_03000054[5] / 0x100 + *(u16 *)(c2 + 6);
        }
        {
            char *c3 = *(char * volatile *)(owner + 0xC);
            *(s32 *)c3 |= 0x5000;
            *(s32 *)(c3 + 0x24) = zero;
        }
        *(s32 *)(owner + 0x8C) += 1;
        break;
    }
    case 2: {
        char *child = *(char **)(owner + 0xC);

        if (child == 0) {
            goto kill;
        }
        if ((*(s32 *)owner & 2) == 0) {
            if (*(s16 *)(child + 4) - D_03000054[4] / 0x100 > 0x100) {
                goto kill;
            }
            break;
        } else {
            if (*(s16 *)(child + 4) - D_03000054[4] / 0x100 >= -0x10) {
                break;
            }
        }
    kill:
        func_08095114(owner);
        break;
    }
    }
}
