#include "m2c_prelude.h"

void *func_08094484(s32, s32, s32, s32);

extern void *D_02032A88[];
extern void *D_02032AA8[];

void sub_080ACA8C(s32 arg0, s32 arg1, s32 arg2)
{
    u32 count;
    u32 i;
    register s32 fifteen asm("r9");
    register s32 zero asm("r8");
    register s32 first_x asm("sl");
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    volatile s32 saved_arg2;
    volatile s32 second_x;

    asm volatile("" : "=m"(reserve0), "=m"(reserve1), "=m"(reserve2),
                       "=m"(reserve3), "=m"(reserve4));

    arg0 <<= 24;
    count = (u32)arg0 >> 24;
    arg1 <<= 16;
    arg1 = (u32)arg1 >> 16;
    arg2 <<= 16;
    saved_arg2 = (u32)arg2 >> 16;
    i = 0;

    if (i < count) {
        {
            register s32 signed_arg1 asm("r1") = arg1;

            signed_arg1 <<= 16;
            signed_arg1 >>= 16;
            arg1 = signed_arg1;
        }
        fifteen = 15;
        zero = i;
        second_x = (arg1 - 1) << 19;
        first_x = arg1 << 19;
        do {
            register s32 coordinate asm("r4");
            register s32 offset asm("r5");
            register volatile s32 *outgoing asm("sp");

            {
                register s32 saved asm("r5") = saved_arg2;

                coordinate = (s16)(((s32)(saved << 16) >> 13) + (i << 4));
            }
            outgoing[0] = coordinate;
            outgoing[1] = 0x2C2;
            {
                register s32 value asm("r0") = fifteen;

                outgoing[2] = value;
            }
            outgoing[3] = 0x108;
            {
                register s32 value asm("r5") = zero;

                outgoing[4] = value;
            }
            {
                register s32 call0 asm("r0") = 0x081053C4;
                register s32 call1 asm("r1") = 0x081053D0;
                register s32 call2 asm("r2") = 0;
                register s32 call3 asm("r3");
                register s32 value asm("r5") = first_x;

                asm volatile("" : "+r"(value));
                call3 = value >> 16;
                asm volatile("" : "+r"(call0), "+r"(call1),
                                   "+r"(call2), "+r"(call3));
                D_02032A88[(offset = i << 2) >> 2] =
                    func_08094484(call0, call1, call2, call3);
            }
            outgoing[0] = coordinate;
            outgoing[1] = 0x2C4;
            outgoing[2] = fifteen;
            outgoing[3] = 0x00200108;
            {
                register s32 value asm("r4") = zero;

                outgoing[4] = value;
            }
            {
                register s32 call0 asm("r0") = 0x081053EC;
                register s32 call1 asm("r1") = 0x081053F8;
                register s32 call2 asm("r2") = 0;
                register s32 call3 asm("r3");
                register s32 value asm("r4") = second_x;

                asm volatile("" : "+r"(value));
                call3 = value >> 16;
                asm volatile("" : "+r"(call0), "+r"(call1),
                                   "+r"(call2), "+r"(call3));
                *(void **)(offset + (s32)D_02032AA8) =
                    func_08094484(call0, call1, call2, call3);
            }
            i = (u8)(i + 1);
        } while (i < count);
    }
}
