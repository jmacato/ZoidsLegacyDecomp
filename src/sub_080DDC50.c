#include "m2c_prelude.h"

extern void func_08095114(void *);
extern void func_080D12A0(s32, s32);
extern void *func_080D2450();
extern void *func_080D2660();
extern void func_080D2790(s32);
extern u32 func_080ECD5C(u32);
extern u32 D_03000010;

void sub_080DDC50(void *arg0) {
    char *owner = arg0;
    register s32 *state_slot asm("r4") = (s32 *)(owner + 0x8C);
    register u32 state asm("r2") = *state_slot;

    switch (state) {
    case 0:
        *(void **)(owner + 0xC) = func_080D2450(owner, 0, 1,
            (s16)(*(s32 *)(owner + 4) - 0x80), *(s16 *)(owner + 8),
            0x600, 0, 1);
        goto advance;
    case 1:
        if (*(u16 *)(*(char **)(owner + 0xC) + 0x14) != 4) {
            break;
        }
        *(void **)(owner + 0x10) = func_080D2450(owner, 1, 0,
            *(s16 *)(owner + 4), *(s16 *)(owner + 8), 0x400, 0, 0);
        goto advance;
    case 2:
        if (*(u16 *)(*(char **)(owner + 0xC) + 0x14) != 5) {
            break;
        }
        func_080D12A0(6, 0);
        func_080D2790(0);
        goto advance;
advance:
        *state_slot = *state_slot + 1;
        break;
    case 3: {
        register void *parent asm("r0") = *(void **)(owner + 0xC);
        register u32 status asm("r1") =
            *(u16 *)((char *)parent + 0x14);

        if (status <= 0x15) {
            register s32 *counter asm("r9") = (s32 *)(owner + 0x90);
            register s32 zero asm("r6") = *counter & state;

            if (zero == 0) {
                register u32 *rng asm("r5") = &D_03000010;
                register s32 priority_base asm("r8");
                register s32 size asm("sl");
                register s32 angle asm("r4");
                register s32 priority asm("r1");

                angle = (u32)(func_080ECD5C(*rng) * 0x21) >> 15;
                angle += 0x80;
                priority = (u32)(func_080ECD5C(*rng) * 0x101) >> 15;
                priority_base = 0x100;
                asm volatile("" : "+r"(priority_base));
                priority += priority_base;
                {
                    register volatile s32 *outgoing asm("sp");
                    register s32 x_offset asm("r0");
                    register s32 x_value asm("r3");
                    register s32 y_value asm("r0");
                    register char *call0 asm("r0");
                    register s32 call1 asm("r1");
                    register s32 call2 asm("r2");

                    asm volatile(
                        "mov %0, #4\n\t"
                        "ldrsh %1, [%2, %0]"
                        : "=r"(x_offset), "=r"(x_value)
                        : "r"(owner));
                    y_value = (s16)(*(s32 *)(owner + 8) - 4);
                    outgoing[0] = y_value;
                    size = 0x500;
                    outgoing[1] = size;
                    outgoing[2] = angle;
                    outgoing[3] = priority;
                    outgoing[4] = zero;
                    call0 = owner;
                    call1 = 2;
                    call2 = 0;
                    asm volatile("" : "+r"(call0), "+r"(call1),
                                       "+r"(call2), "+r"(x_value));
                    func_080D2660(call0, call1, call2, x_value);
                }

                angle = (u32)(func_080ECD5C(*rng) * 0x21) >> 15;
                angle += 0x60;
                priority = (u32)(func_080ECD5C(*rng) * 0x101) >> 15;
                priority += priority_base;
                func_080D2660(owner, 2, 0, *(s16 *)(owner + 4),
                    (s16)(*(s32 *)(owner + 8) + 4),
                    size, angle, priority, zero);
            }
            {
                register s32 *counter_view asm("r1") = counter;
                *counter_view = *counter_view + 1;
            }
            parent = *(void **)(owner + 0xC);
        }

        {
            u8 index = 0;
            if (parent == 0) {
                register char *children asm("r2") = owner + 0xC;
                do {
                    index = (u8)(index + 1);
                } while (index <= 0xA &&
                    *(s32 *)(children + (index << 2)) == 0);
            }
            if (index == 0xB) {
                func_08095114(owner);
            }
        }
        break;
    }
    }
    return;
}
