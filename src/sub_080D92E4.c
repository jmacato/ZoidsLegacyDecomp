#include "m2c_prelude.h"
extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080D92E4(void *arg0) {
    register char *owner asm("r5") = arg0;
    register s32 *state_slot asm("r6") = (s32 *)(owner + 0x8C);
    register u32 state asm("r0") = *state_slot;

    switch (state) {
    case 0: {
        register s32 *x_slot asm("r4") = (s32 *)(owner + 0x90);
        register s32 x asm("r3") = *x_slot - 0x100;
        register s32 y asm("r0");
        void *created;

        x = (s16)x;
        asm volatile("" : "+r"(x));
        y = *(s32 *)(owner + 0x94) - 0x80;
        y = (s16)y;
        created = func_080D2450(owner, 0, 0, x, y,
            0x20, 0x080D8D21, 1);
        *(void **)(owner + 0xC) = created;
        *(void **)((char *)created + 0x28) = owner;
        *(s32 *)((char *)created + 0x2C) = 0;
        *(s32 *)((char *)created + 0x30) = *x_slot;
        func_080D2790(0);
        *state_slot = *state_slot + 1;
        break;
    }
    case 1:
        if ((**(u32 **)(owner + 0xC) & 0x20000) == 0) {
            break;
        }
        {
            register s32 *counter_init asm("r1") = (s32 *)(owner + 0x98);
            register s32 *counter_slot asm("r6");
            register u32 counter asm("r2") = *counter_init;
            register u32 masked asm("r0") = counter & 3;

            counter_slot = counter_init;

            if (masked == 0) {
                register s32 x_base asm("r4") = *(s32 *)(owner + 0x90);
                s32 x;
                register s32 y_base asm("r4");
                register s32 y asm("r0");
                void *created;

                if (counter != 0) {
                    register u32 random asm("r0") =
                        func_080ECD5C(D_03000010);
                    register s32 value asm("r2") = x_base - 0x10;
                    value += (u32)(random * 0x21) >> 15;
                    x = (s16)value;
                } else {
                    register s32 x_bits asm("r0");
                    asm volatile(
                        "lsl %1, %2, #16\n\t"
                        "asr %0, %1, #16"
                        : "=&r"(x), "=&r"(x_bits) : "r"(x_base));
                }
                y_base = *(s32 *)(owner + 0x94);
                if (*counter_slot != 0) {
                    register u32 random asm("r0") =
                        func_080ECD5C(D_03000010);
                    register s32 value asm("r2") = y_base - 0x10;
                    value += (u32)(random * 0x21) >> 15;
                    asm volatile(
                        "lsl %1, %1, #16\n\t"
                        "asr %0, %1, #16"
                        : "=r"(y), "+r"(value));
                } else {
                    asm volatile(
                        "lsl %0, %1, #16\n\t"
                        "asr %0, %0, #16"
                        : "=&r"(y) : "r"(y_base));
                }
                created = func_080D2450(owner, 2, 0, x, y,
                    0x400, 0, 0);
                {
                    register u32 slot_index asm("r1") =
                        ((u32)*counter_slot >> 2) + 1;
                    register char *children asm("r2");
                    slot_index <<= 2;
                    children = owner + 0xC;
                    asm volatile("add %0, %0, %1"
                        : "+r"(children) : "r"(slot_index));
                    *(void **)children = created;
                }
            }
            if (*counter_slot == 0) {
                func_080D2790(1);
            }
            {
                register s32 next asm("r0") = *counter_slot + 1;
                *counter_slot = next;
                if (next == 0x14) {
                    func_080D12A0(6, 0);
                    {
                        register s32 *state1_slot asm("r1") =
                            (s32 *)(owner + 0x8C);
                        *state1_slot = *state1_slot + 1;
                    }
                }
            }
        }
        break;
    case 2: {
        register u32 index asm("r2") = 0x10;
        register char *parent asm("r1") = *(char **)(owner + 0xC);
        register u32 raw_bound asm("r0") =
            *(u32 *)(parent + 0x2C) >> 1;
        register u32 bound asm("r3") = raw_bound;
        asm volatile("" : "+r"(raw_bound));
        bound += 0x11;

        if (index < bound && *(s32 *)(owner + 0x4C) == 0) {
            register u32 scan_bound asm("r4") = bound;
            register char *children asm("r3") = owner + 0xC;
            do {
                register u32 next asm("r0") = index + 1;
                next <<= 24;
                index = next >> 24;
            } while (index < scan_bound &&
                *(s32 *)(children + (index << 2)) == 0);
        }
        if (index == ((*(u32 *)(parent + 0x2C) >> 1) + 0x11)) {
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
}
