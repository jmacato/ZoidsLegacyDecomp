#include "m2c_prelude.h"

extern s16 func_08092A90(s16);
extern void func_08095208(void *, void *, s32);
extern u8 func_080ECE30(s32, s32);
extern void func_080ED17C(s32);

extern u8 D_02031C99;
extern u8 D_02031C9A[];

void sub_080A8FAC(void)
{
    register u32 elapsed asm("r6");
    register s32 frame asm("r4");
    register u32 column asm("r5");
    register s32 angle asm("r8");
    register s32 next_angle asm("r10");
    register u8 *buffer asm("r9");
    u8 *toggle;

    elapsed = 0;
    frame = 0;
    buffer = D_02031C9A;
    toggle = &D_02031C99;
    asm volatile("" : "+r"(buffer), "+r"(toggle));
loop:
    column = 0;
    next_angle = angle + 1;
    {
        s32 homes[2];
        register s32 upload_view asm("r0");

        upload_view = frame << 5;
        asm volatile("" : "+r"(upload_view));
        homes[1] = upload_view;
        homes[0] = frame + 1;
        asm volatile("" : : "m"(homes[0]), "m"(homes[1]));

    do {
        u8 mode = *(u8 *)0x020321A0;
        if (mode == 0) {
            goto zero;
        }
        if (mode == 1) {
            goto one;
        }
        frame = column << 2;
        goto sine;
zero:
        {
            register s32 bank asm("r1");
            register s32 zero_offset asm("r2") = column << 2;
            register u32 address asm("r0");

            asm volatile("ldrb r0, [%1]\n\tmov %0, #1\n\teor %0, r0"
                         : "=r"(bank)
                         : "r"(toggle)
                         : "r0");
            address = bank << 2;
            address += bank;
            address <<= 7;
            asm volatile("add %0, %1, %0" : "+r"(address) : "r"(zero_offset));
            address += (u32)buffer;
            *(u16 *)address = mode;
            frame = zero_offset;
        }
        goto sine;
one:
        {
            s32 threshold = 0x9F - column;
            frame = column << 2;
            if (elapsed >= threshold) {
                s32 value = elapsed;
                u16 height;
                register s32 bank asm("r1");
                register u32 address asm("r0");

                value -= 0x9F;
                value += column;
                height = value * 4;
                if ((s16)(value * 4) > 0x100) {
                    height = 0x100;
                }
                bank = 1;
                if (mode & column) {
                    height = (u32)(0 - ((u32)height << 16)) >> 16;
                }
                asm volatile("ldrb r0, [%1]\n\teor %0, r0"
                             : "+r"(bank)
                             : "r"(toggle)
                             : "r0");
                address = bank * 0x280;
                asm volatile("add %0, %1, %0" : "+r"(address) : "r"(frame));
                address += (u32)buffer;
                *(u16 *)address = height;
            }
        }
sine:

        {
            register s16 sine asm("r3") = func_08092A90((s16)((column + angle) * 2));
            register u16 *sine_destination asm("r2");

            {
                register s32 bank asm("r1");
                register u32 address asm("r0");
                register u8 *sine_base asm("r1");

                asm volatile("ldrb r0, [%1]\n\tmov %0, #1\n\teor %0, r0"
                             : "=r"(bank)
                             : "r"(toggle)
                             : "r0");
                address = bank * 0x280;
                asm volatile("add %0, %1, %0" : "+r"(address) : "r"(frame));
                sine_base = (u8 *)0x02031C9C;
                asm volatile("" : "+r"(sine_base));
                sine_destination = (u16 *)(address + (u32)sine_base);
                asm volatile("" : "+r"(sine_destination));
            }
            {
                register s32 a asm("r0") = *(s32 *)0x0203219C;

                if (a < 0) {
                    a += 0xFF;
                }
                {
                    register s32 quotient asm("r1") = a >> 8;
                    register s32 sine_value asm("r0") = (s16)sine;
                    register s32 result asm("r0");

                    if (sine_value < 0) {
                        sine_value += 0x3F;
                    }
                    result = quotient + (sine_value >> 6);
                    *sine_destination = result;
                }
            }
        }
        {
            register s32 next_column asm("r0");

            next_column = column + 1;
            column = (u8)next_column;
        }
    } while (column <= 0x9F);

    {
        register s32 angle_view asm("r1");
        register s32 narrowed_angle asm("r0");

        angle_view = next_angle;
        asm volatile("" : "+r"(angle_view));
        narrowed_angle = (u8)angle_view;
        asm volatile("" : "+r"(narrowed_angle));
        angle = narrowed_angle;
    }
    if (*(u8 *)0x020321A0 != 0) {
        elapsed++;
        if (elapsed == 0xE0) {
            *(u8 *)0x020321A0 = 2;
        }
    }
    {
        register u8 *upload_source asm("r0");
        register s32 upload_view asm("r1");

        upload_source = (u8 *)0x08103E18;
        asm volatile("" : "+r"(upload_source));
        upload_view = homes[1];
        asm volatile("" : "+r"(upload_view));
        upload_source = (u8 *)((u32)upload_view + (u32)upload_source);
        func_08095208(upload_source, (void *)0x05000180, 0x20);
    }
    frame = (u8)func_080ECE30(homes[0], 0x1E);
    func_080ED17C(1);
    }
    goto loop;
}
