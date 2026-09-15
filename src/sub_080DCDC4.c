#include "m2c_prelude.h"

extern s32 D_03000010;

s16 func_08092A90(s32);
s16 func_08092ADC(s32);
void *func_080D2660(void *, s32, s32, s32);
s32 func_080ECD5C(s32);
s32 func_080ECD98(s32, s32);

void sub_080DCDC4(void *arg0, s32 arg1, s32 arg2)
{
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    volatile s32 saved_arg1;
    volatile void **saved_slot;
    register void *owner asm("r6");
    register u32 i asm("r2");
    register s32 *rng asm("r4");
    register volatile s32 *outgoing asm("sp");

    asm("" : "=m"(reserve0), "=m"(reserve1), "=m"(reserve2),
             "=m"(reserve3), "=m"(reserve4));

    owner = arg0;
    arg1 <<= 24;
    saved_arg1 = (u32)arg1 >> 24;
    i = 1;
    rng = &D_03000010;
    do {
        register u32 slot_offset asm("r1");
        register u8 *slot_base asm("r0");
        void **slot;
        register void *old asm("r9");

        slot_offset = i << 2;
        slot_base = owner;
        slot_base += 0xC;
        slot = (void **)(slot_base + slot_offset);
        saved_slot = slot;
        old = *slot;
        if (old == 0) {
            register u16 radius asm("r5");
            register u16 radius_copy asm("sl");
            register u32 angle asm("r4");
            register u32 angle_copy asm("r8");
            s32 x;
            s32 random_value;

            {
                register u32 value asm("r1");

                value = (u32)(func_080ECD5C(*rng) * 0x15) >> 15;
                value += 0x30;
                value <<= 16;
                radius = value >> 16;
                radius_copy = radius;
            }
            {
                register u32 value asm("r0");

                value = (u32)(func_080ECD5C(*rng) * 0x56) >> 15;
                value += 0x55;
                value <<= 24;
                angle = value >> 24;
                angle_copy = angle;
            }
            {
                register s32 product asm("r0");
                s32 base;

                product = func_08092ADC(angle);
                base = *(s32 *)((u8 *)owner + 4);
                product = (s16)product;
                product *= radius;
                if (product < 0) {
                    product += 0xFF;
                }
                product >>= 8;
                product = base + product;
                product <<= 16;
                x = product >> 16;
            }
            {
                register s32 product asm("r0");
                s32 base;

                product = func_08092A90(angle);
                base = *(s32 *)((u8 *)owner + 8);
                product = (s16)product;
                product *= radius;
                if (product < 0) {
                    product += 0xFF;
                }
                product >>= 8;
                product = base + product;
                product <<= 16;
                outgoing[0] = product >> 16;
            }
            outgoing[1] = 0x400;
            outgoing[2] = angle_copy + 0x80;
            {
                register s32 saved asm("r1") = saved_arg1;
                register s32 shifted asm("r0");
                register s32 numerator asm("r1");
                register s32 call_value asm("r0");

                shifted = saved << 8;
                numerator = radius_copy;
                numerator *= shifted;
                call_value = numerator;
                random_value = func_080ECD98(call_value, 0x30);
            }
            outgoing[3] = random_value;
            outgoing[4] = (s32)old;
            {
                register void *call_owner asm("r0") = owner;
                register s32 call_one asm("r1") = 1;
                register s32 call_zero asm("r2") = 0;
                register s32 call_x asm("r3");

                asm volatile("" : "+r"(call_owner), "+r"(call_one),
                                  "+r"(call_zero));
                call_x = x;
                *saved_slot = func_080D2660(call_owner, call_one, call_zero,
                                            call_x);
            }
            return;
        }
        {
            register u32 next asm("r0") = i + 1;
            i = (u8)next;
        }
    } while (i <= 0x1F);
}
