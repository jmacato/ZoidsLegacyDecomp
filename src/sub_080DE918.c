#include "m2c_prelude.h"

void func_08095208(s32, s32, s32);
void func_080D2790(s32);
void func_080ECD28(s32, s32, s32);
void func_080ECD2C(void *, s32, s32);

void sub_080DE918(u8 *owner)
{
    u16 colors[2];
    register s32 palette_a asm("r9");
    register s32 palette_b asm("r8");
    register s32 buffer_a asm("r5");
    register s32 buffer_b asm("r4");
    register u32 color asm("r6");

    *(s32 *)(owner + 0x8C) = 0;

    palette_a = 0xA0;
    palette_a <<= 19;
    buffer_a = 0x02034934;
    func_080ECD28(palette_a, buffer_a, 0x20);

    {
        register s32 palette_b_source asm("r1") = 0x05000200;
        asm volatile("" : "+r"(palette_b_source));
        palette_b = palette_b_source;
        asm volatile("" : : "r"(palette_b));
    }
    buffer_b = 0x02034A34;
    func_080ECD28(palette_b, buffer_b, 0x18);

    {
        register u16 *first_color asm("r0") = &colors[0];
        register u32 color_source asm("r1") = 0x7FFF;
        asm volatile("" : "+r"(first_color));
        asm volatile("" : "+r"(color_source));
        color = color_source;
        asm volatile("" : : "r"(color));
        *first_color = color;
        buffer_a += 0x80;
        func_080ECD2C(first_color, buffer_a, 0x01000040);
    }

    {
        register u16 *second_color asm("r0") = &colors[1];
        asm volatile("" : "+r"(second_color));
        *second_color = color;
        buffer_b += 0x60;
        func_080ECD2C(second_color, buffer_b, 0x01000030);
    }

    func_08095208(buffer_a, palette_a, 0x80);
    func_08095208(buffer_b, palette_b, 0x60);
    func_080D2790(0);
}
