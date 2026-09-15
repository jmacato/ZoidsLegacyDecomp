#include "m2c_prelude.h"

void func_08094290(s32, s32);
void func_080942E0(s32);

void sub_080BA94C(s32 active)
{
    if ((active << 24) != 0) {
        register u8 *mode asm("r6") = (u8 *)0x02032B9C;
        register u32 value asm("r5") = *mode;

        if (value == 1) {
            register volatile u16 *interrupt asm("r4") =
                (u16 *)0x04000208;

            *interrupt = 0;
            func_08094290(1, 0x030060FC);
            {
                register volatile u16 *display asm("r1") =
                    (u16 *)0x04000008;
                register u32 mask asm("r2");
                u32 current;

                current = *display;
                mask = 0x40;
                current |= mask;
                *display = current;
                display++;
                current = *display;
                current |= mask;
                *display = current;
                display++;
                current = *display;
                current |= mask;
                *display = current;
                display++;
                current = *display;
                current |= mask;
                *display = current;
            }
            *interrupt = value;
            *mode = 2;
            goto toggle;
        }
        if (value == 3) {
            register volatile u16 *interrupt asm("r4") =
                (u16 *)0x04000208;

            value = 0;
            *interrupt = value;
            func_080942E0(1);
            {
                register volatile u16 *display asm("r3") =
                    (u16 *)0x04000008;
                register u32 mask asm("r1");
                register u32 current asm("r2");
                register u32 result asm("r0");

                current = *display;
                asm volatile("" : "+r"(current));
                mask = 0xFFBF;
                asm volatile("" : "+r"(mask));
                result = mask;
                asm volatile("" : "+r"(result));
                result &= current;
                *display = result;
                display++;
                current = *display;
                asm volatile("" : "+r"(current));
                result = mask;
                asm volatile("" : "+r"(result));
                result &= current;
                *display = result;
                display++;
                current = *display;
                asm volatile("" : "+r"(current));
                result = mask;
                asm volatile("" : "+r"(result));
                result &= current;
                *display = result;
                {
                    register volatile u16 *last asm("r2") =
                        (u16 *)0x0400000E;
                    register u32 last_value asm("r0") = *last;

                    mask &= last_value;
                    *last = mask;
                }
            }
            *(u8 *)0x03000074 &= 0xF7;
            *interrupt = 1;
            *mode = value;
            return;
        }
toggle:
        *(u8 *)0x02032B9E ^= 1;
    }

    if (*(u8 *)0x02032B9C == 2) {
        register volatile u16 *display asm("r3") = (u16 *)0x0400004C;
        register u16 *table asm("r2") = (u16 *)0x02032BA0;
        register u8 *toggle asm("r0") = (u8 *)0x02032B9E;
        register u32 selected asm("r1") = *toggle;
        register u32 offset asm("r0") = selected << 2;

        asm volatile("" : "+r"(table));
        offset += selected;
        offset <<= 6;
        offset += (u32)table;
        *display = *(u16 *)offset;
    }
}
