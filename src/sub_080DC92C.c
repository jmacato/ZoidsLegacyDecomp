#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void *func_080D2450();
extern void func_080D2790(s32);
extern u16 D_0300004E;
extern u16 D_03000050;

void sub_080DC92C(void *arg0) {
    register char *owner asm("r5") = arg0;
    register s32 *state_slot asm("r6") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;

    switch (state) {
    case 0: {
        register s32 zero asm("r4");
        void *created;

        created = func_080D2450(owner, 0, 0,
            (s16)(*(s32 *)(owner + 4) - 0x80),
            (s32)*(s16 *)(owner + 8), 0x320,
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
        D_0300004E = 0x740;
        D_03000050 = 0x1010;
        {
            s32 *flags = *(s32 **)(owner + 0xC);
            *flags = (*flags & 0xFFFDFFFF) | 0x400;
        }
        *state_slot = *state_slot + 1;
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
