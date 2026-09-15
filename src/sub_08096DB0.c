#include "m2c_prelude.h"

extern u8 D_02002740[];
extern u16 D_03005F78;
extern u8 D_03005F71;
void func_08094290(s32, s32);
void func_080942E0(s32);
void func_080ECD28(s32, s32, s32);

void sub_08096DB0(u8 arg0)
{
    u8 state = *(u8 *)0x03005F70;
    u32 t;

    if (state == 0) {
        return;
    }
    t = 0x3F;
    t &= state;
    if ((u32)(u8)(t - 17) <= 1U) {
        if (arg0 != 0) {
            u8 *mode = (u8 *)0x03005F7B;
            register u32 value asm("r6") = *mode;
            u32 zero;

            if (value == 1) {
                register volatile u16 *ime asm("r4") = (u16 *)0x04000208;

                zero = 0;
                *ime = zero;
                func_08094290(2, 0x03005F7C);
                *ime = value;
                goto clear;
            }
            if (value == 2) {
                register volatile u16 *ime asm("r4") = (u16 *)0x04000208;

                zero = 0;
                *ime = zero;
                func_080942E0(2);
                *ime = 1;
clear:
                *mode = zero;
            }
            *(u8 *)0x03005F7A ^= 1;
        }
        if (*(u8 *)0x03005F7B == 0 && D_02002740[*(u8 *)0x03005F7A * 160] == 0) {
            register volatile u16 *p asm("r1") = (volatile u16 *)0x04000054;

            *p = 16;
            p -= 2;
            *p = 0xFF;
            p -= 4;
            *(volatile u32 *)p = 0x3F3F3F3F;
        }
    }
    if (arg0 != 0) {
        u8 flags = *(u8 *)0x03005F70;
        u32 m = 0x80;
        u8 *sp;

        m &= flags;
        sp = (u8 *)0x03005F70;

        if (m != 0) {
            u16 mosaic = D_03005F78;

            if (mosaic != 0) {
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
                *(u16 *)0x0400004C = mosaic;
            } else {
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
        }
        if ((*sp & 0x40) != 0) {
            func_080ECD28(0x02000B40, 0x05000000, 0x100);
        }
        {
            u8 *cnt = (u8 *)0x03005F72;
            u32 nv = *cnt + 1;

            *cnt = nv;
            if ((u8)nv > D_03005F71) {
                *sp = 0;
            }
        }
    }
}
