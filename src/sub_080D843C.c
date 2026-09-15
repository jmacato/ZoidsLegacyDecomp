#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void func_080D2790(s32);

void sub_080D843C(void *arg0) {
    register char *owner asm("r6") = arg0;
    register u32 state asm("r0") = *(u32 *)(owner + 0x8C);

    switch (state) {
    case 0: {
        register s32 *coord asm("r4") = (s32 *)(owner + 0x94);
        register s32 x asm("r3") = *coord - 0x100;
        void *created;

        created = func_080D2450(owner, 0, 0, (s16)x,
            -0x10, 0x20, 0x080D6E6D, 1);
        *(void **)(owner + 0xC) = created;
        *(void **)((char *)created + 0x28) = owner;
        *(s32 *)((char *)created + 0x2C) = 0;
        *(s32 *)((char *)created + 0x30) = *coord;
        func_080D2790(0);
        goto advance;
    }
    case 1:
        if ((**(u32 **)(owner + 0xC) & 0x20000) == 0) {
            break;
        }
        {
            register s16 *coord asm("r0") = (s16 *)(owner + 0x94);
            register s32 coord_offset asm("r1") = 0;
            register s32 x asm("r3") = coord[coord_offset];
            register volatile s32 *outgoing asm("sp");
            register s32 zero asm("r4");

            outgoing[0] = 0x70;
            outgoing[1] = 0x200;
            zero = 0;
            outgoing[2] = zero;
            outgoing[3] = zero;
            *(void **)(owner + 0x10) = func_080D2450(owner, 2, 1, x);
            func_080D12A0(6, 0);
            func_080D2790(1);
            *(s32 *)(owner + 0x90) = zero;
            goto advance;
    }
    case 2: {
        s32 *timer = (s32 *)(owner + 0x90);
        *timer = *timer + 1;
        if (*timer != 4) {
            break;
        }
        {
            register s32 *coord asm("r5") = (s32 *)(owner + 0x94);
            register s32 zero asm("r4");
            register s32 x asm("r3") = *coord - 0x10;
            register volatile s32 *outgoing asm("sp");

            x = (s16)x;
            outgoing[0] = 0x6C;
            zero = 0;
            outgoing[1] = zero;
            outgoing[2] = zero;
            outgoing[3] = zero;
            *(void **)(owner + 0x14) = func_080D2450(owner, 2, 2, x);
            x = *coord + 0x14;
            x = (s16)x;
            outgoing[0] = 0x58;
            outgoing[1] = zero;
            outgoing[2] = zero;
            outgoing[3] = zero;
            *(void **)(owner + 0x18) = func_080D2450(owner, 2, 2, x);
            *timer = zero;
            goto advance;
        }
    }
    case 3: {
        register s32 *timer asm("r1") = (s32 *)(owner + 0x90);
        *timer = *timer + 1;
        if (*timer != 4) {
            break;
        }
        {
            register s32 *coord asm("r5") = (s32 *)(owner + 0x94);
            register s32 zero asm("r4");
            register s32 x asm("r3") = *coord - 8;
            register volatile s32 *outgoing asm("sp");
            void *created;

            x = (s16)x;
            outgoing[0] = 0x48;
            outgoing[1] = 0x80100;
            zero = 0;
            outgoing[2] = zero;
            outgoing[3] = zero;
            created = func_080D2450(owner, 2, 0, x);
            *(void **)(owner + 0x1C) = created;
            {
                register u32 field asm("r1") = 0x200;
                *(u16 *)((char *)created + 0xC) = field;
            }
            x = *coord - 8;
            x = (s16)x;
            outgoing[0] = 0x40;
            outgoing[1] = zero;
            outgoing[2] = zero;
            outgoing[3] = zero;
            *(void **)(owner + 0x20) = func_080D2450(owner, 2, 2, x);
            goto advance;
        }
    }
advance:
    {
        register s32 *state_slot asm("r1") = (s32 *)(owner + 0x8C);
        *state_slot = *state_slot + 1;
    }
    break;

    case 4: {
        register u32 index asm("r2") = 0x18;
        register char *parent asm("r1") = *(char **)(owner + 0xC);
        register u32 raw_bound asm("r0") = *(u32 *)(parent + 0x2C) >> 1;
        register u32 bound asm("r3") = raw_bound;
        asm volatile("" : "+r"(raw_bound));
        bound += 0x19;

        if (index < bound && *(s32 *)(owner + 0x6C) == 0) {
            register u32 scan_bound asm("r4") = bound;
            register char *children asm("r3") = owner + 0xC;
            do {
                register u32 next asm("r0") = index + 1;
                next <<= 24;
                index = next >> 24;
            } while (index < scan_bound &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == ((*(u32 *)(parent + 0x2C) >> 1) + 0x19)) {
            index = 1;
            if (*(s32 *)(owner + 0x10) == 0) {
                register char *children asm("r1") = owner + 0xC;
                do {
                    register u32 next asm("r0") = index + 1;
                    next <<= 24;
                    index = next >> 24;
                } while (index <= 5 &&
                    *(s32 *)(children + (index << 2)) == 0);
            }
            if (index == 6) {
                func_08095114(owner);
            }
        }
        break;
    }
    }
    return;
}
