#include "m2c_prelude.h"

struct Object9B9E4 {
    u32 flags;
    u8 pad_04[0x24];
    s32 x;
    s32 y;
    s32 z;
};

struct Object9B9E4 *func_08094484(s32, s32, s32, s32);
u32 func_080ECD5C(u32);
void func_080ED17C(s32);

extern u32 D_020216F0;
extern struct Object9B9E4 *D_020216B0[16];
extern u32 D_03000010;

void sub_0809B9E4(void)
{
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    register s32 target asm("r6") = 0;
    register s32 tick asm("r4") = 0;

    asm volatile("" : "=m"(reserve0), "=m"(reserve1),
                       "=m"(reserve2), "=m"(reserve3),
                       "=m"(reserve4));
    D_020216F0 = 0x60;

loop:
    {
        s32 next_tick = tick + 1;

        if (tick == target) {
            register u32 i asm("r2") = 0;
            register struct Object9B9E4 **slots asm("r4") = D_020216B0;
            register u32 one asm("r3") = 1;

            do {
                register u32 offset asm("r0") = i << 2;
                register struct Object9B9E4 **slot asm("r0");
                struct Object9B9E4 *object;

                slot = (struct Object9B9E4 **)(offset + (u32)slots);
                object = *slot;
                if (object != 0) {
                    u32 alive = object->flags & one;

                    if (alive == 0) {
                        *slot = (struct Object9B9E4 *)alive;
                    }
                }
                {
                    register u32 next asm("r0") = i + 1;

                    next <<= 24;
                    i = next >> 24;
                }
            } while (i <= 15U);

            i = 0;
            {
                register struct Object9B9E4 **slot_base asm("r1") = D_020216B0;
                register struct Object9B9E4 **slot asm("r4");
                register struct Object9B9E4 *object asm("r5");
search:
                {
                    register u32 offset asm("r0") = i << 2;

                    slot = (struct Object9B9E4 **)(offset + (u32)slot_base);
                    object = *slot;
                    if (object == 0) {
                        goto spawn;
                    }
                    {
                        register u32 next asm("r0") = i + 1;

                        next <<= 24;
                        i = next >> 24;
                    }
                    if (i <= 15U) {
                        goto search;
                    }
                }

schedule:
                {
                    register u32 *interval_slot asm("r1") = &D_020216F0;
                    register u32 interval asm("r0") = *interval_slot;

                    if (interval > 0x10U) {
                        target += interval;
                        interval -= 0x10;
                        *interval_slot = interval;
                        goto advance;
                    }
                    goto add16;
                }

spawn:
                {
                    register volatile s32 *outgoing asm("sp");

                    outgoing[0] = (s32)object;
                    outgoing[1] = 0x3B1;
                    outgoing[2] = 0xB;
                    outgoing[3] = 0x440;
                    outgoing[4] = 0x0809B971;
                    *slot = func_08094484(0x081039D0, 0x08103A34, 0, 0);
                    {
                        register u32 random asm("r0") = func_080ECD5C(D_03000010);
                        register struct Object9B9E4 *created asm("r2") = *slot;

                        created->x = ((random * 0x401) >> 15) + 0x7A00;
                        created->y = 0x5000;
                        created->z = (s32)object;
                    }
                    goto schedule;
                }
            }
add16:
            target += 0x10;
        }
advance:
        tick = next_tick;
    }
    func_080ED17C(1);
    goto loop;
}
