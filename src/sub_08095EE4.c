#include "m2c_prelude.h"

extern u8 D_02000000[];

void sub_08095EE4(void)
{
    u8 buffer = 1 ^ *(u8 *)0x03005F12;
    u16 *entry = (u16 *)(D_02000000 + buffer * 0x500);
    u8 i;
    register u8 *mode;
    register u16 *offset;
    register u8 *packed asm("r5");
    register u32 limit asm("r4");

    i = 0;
    asm volatile("" : "+r"(i));
    mode = (u8 *)0x03005F10;
    offset = (u16 *)0x03005EF4;
    limit = 240;
    packed = (u8 *)0x03005F11;

    do {
        u32 value;

        if (*mode == 0) {
            s32 position = limit - *offset;

            if (i <= 79) {
                position += 80;
                position -= i;
            } else {
                position -= 80;
                position += i;
            }
            {
                register u32 narrowed asm("r0") = (u16)position;
                asm volatile("" : "+r"(narrowed));
                value = narrowed;
            }
            asm volatile("" : "+r"(value));
            {
                register s32 signed_value asm("r0") = (s16)value;
                asm volatile("" : "+r"(signed_value));
                if (signed_value < 0) {
                    value = 0;
                } else if (signed_value > 240) {
                    value = 240;
                }
            }
            if (*packed == 0) {
                goto plain;
            }
        } else {
            s32 position = *offset;

            if (i <= 79) {
                position -= 80;
                position += i;
            } else {
                position += 80;
                position -= i;
            }
            {
                register u32 narrowed asm("r0") = (u16)position;
                asm volatile("" : "+r"(narrowed));
                value = narrowed;
            }
            asm volatile("" : "+r"(value));
            {
                register s32 signed_value asm("r0") = (s16)value;
                asm volatile("" : "+r"(signed_value));
                if (signed_value < 0) {
                    value = 0;
                } else if (signed_value > 240) {
                    value = 240;
                }
            }
            if (*packed != 0) {
                goto plain;
            }
        }
        asm volatile("" : "+r"(value));
        {
            register s32 packed_value asm("r0");
            asm volatile("lsl %0, %1, #16\n\t"
                         "asr %0, %0, #8"
                         : "=r"(packed_value)
                         : "r"(value));
            packed_value |= limit;
            *entry = packed_value;
        }
        goto next;
plain:
        *entry = value;
next:
        entry += 4;
        i++;
    } while (i <= 159);
}
