#include "m2c_prelude.h"

void func_08094564(void *, u16);
u16 func_080A9A54(void *);

void sub_080AAF80(u8 *state)
{
    register u8 *callback_target asm("r4");

    asm volatile("" : "=r"(callback_target));
    {
        u32 value = *(u32 *)(state + 0x38) + *(s32 *)(state + 0x28);
        *(u32 *)(state + 0x38) = value;
    }
    *(u32 *)(state + 0x3C) += *(s32 *)(state + 0x2C);

    while (*(u32 *)(state + 0x38) >= *(u32 *)(state + 0x40)) {
        u8 *object;

        if (*(s32 *)(state + 0x30) == 0) {
            object = *(u8 **)(state + 0x20);
            (*(u16 *)(object + 8))++;
            object = *(u8 **)(state + 0x24);
            if (object != 0) {
                (*(u16 *)(object + 8))++;
            }
        } else {
            object = *(u8 **)(state + 0x20);
            (*(u16 *)(object + 8))--;
            object = *(u8 **)(state + 0x24);
            if (object != 0) {
                (*(u16 *)(object + 8))--;
            }
        }
        *(u32 *)(state + 0x38) =
            *(u32 *)(state + 0x38) - *(u32 *)(state + 0x40);
    }

    {
        register u32 y asm("r0") = *(u32 *)(state + 0x3C);
        register u32 period asm("r1") = *(u32 *)(state + 0x40);

        asm volatile("" : "+r"(y), "+r"(period));
        while (y >= period) {
            u8 *object;

            if (*(s32 *)(state + 0x34) == 0) {
                object = *(u8 **)(state + 0x20);
                (*(u16 *)(object + 0xA))++;
                object = *(u8 **)(state + 0x24);
                if (object != 0) {
                    (*(u16 *)(object + 0xA))++;
                }
            } else {
                object = *(u8 **)(state + 0x20);
                (*(u16 *)(object + 0xA))--;
                object = *(u8 **)(state + 0x24);
                if (object != 0) {
                    (*(u16 *)(object + 0xA))--;
                }
            }
            y = *(u32 *)(state + 0x3C);
            period = *(u32 *)(state + 0x40);
            asm volatile("" : "+r"(y), "+r"(period));
            y -= period;
            *(u32 *)(state + 0x3C) = y;
        }

        y = *(volatile u32 *)(state + 0x44) + 1;
        *(u32 *)(state + 0x44) = y;
        if (y != period) {
            return;
        }
    }
    {
        register u32 zero asm("r6");
        register u32 clear asm("r2");

        *(u32 *)state &= ~0x10;
        {
            register u8 *object asm("r0") = *(u8 **)(state + 0x20);

            clear = 0;
            zero = 0;
            *(u16 *)(object + 8) = zero;
            asm volatile("" ::: "memory");
        }
        {
            register u8 *object asm("r1") = *(u8 **)(state + 0x20);
            register u32 value asm("r0") = 0xFFFE;

            *(u16 *)(object + 0xA) = value;
        }
        {
            register u8 *object asm("r0") = *(u8 **)(state + 0x24);

            if (object != 0) {
                *(u16 *)(object + 8) = zero;
                asm volatile("" ::: "memory");
                {
                    register u8 *again asm("r1") =
                        *(u8 **)(state + 0x24);
                    register u32 value asm("r0") = 0xE;

                    *(u16 *)(again + 0xA) = value;
                }
            }
        }
        state[0x19] = clear;
        state[0x18] = clear;
        callback_target = *(u8 **)(state + 0x20);
        func_08094564(callback_target, func_080A9A54(state));
        *(u32 *)(state + 0x14) = zero;
        *(u32 *)(state + 0x10) = zero;
    }
}
