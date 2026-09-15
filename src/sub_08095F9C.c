#include "m2c_prelude.h"

extern u8 D_02000000[];

s32 func_080ECF00(u8, s32);
u8 func_080ECF78(u8, s32);

void sub_08095F9C(void)
{
    u8 buffer;
    s32 *entry;
    u8 *count;
    u8 mode;
    u8 i;
    register u8 *count_load asm("r0");

    buffer = 1 ^ *(u8 *)0x03005F12;
    entry = (s32 *)(D_02000000 + buffer * 0x500);
    count_load = (u8 *)0x03005EF6;
    mode = *count_load;
    count = count_load;
    if (mode <= 0x27) {
        i = 0;
        do {
            s32 value;

            if (func_080ECF78(i, 0x28) <= *count) {
                register s32 result asm("r0");

                result = func_080ECF00(i, 0x28);
                asm volatile("" : "+r"(result));
                result &= 1;
                if (result == 0) {
                    register s32 selected asm("r0") = 0x78B4003C;
                    asm volatile("" : "+r"(selected));
                    value = selected;
                } else {
                    register s32 selected asm("r0") = 0xB4F03C78;
                    asm volatile("" : "+r"(selected));
                    value = selected;
                }
            } else {
                value = 0;
            }
            *entry = value;
            entry += 2;
            i = (u8)(i + 1);
        } while (i <= 0x9F);
        return;
    }
    if (mode <= 0x4F) {
        i = 0;
        do {
            s32 value;

            if ((s32)func_080ECF78(i, 0x28) > (s32)(0x50 - *count)) {
                register s32 selected asm("r0") = 0x00F000F0;
                asm volatile("" : "+r"(selected));
                value = selected;
            } else {
                register s32 result asm("r0");

                result = func_080ECF00(i, 0x28);
                asm volatile("" : "+r"(result));
                result &= 1;
                if (result == 0) {
                    register s32 selected asm("r0") = 0x78B4003C;
                    asm volatile("" : "+r"(selected));
                    value = selected;
                } else {
                    register s32 selected asm("r0") = 0xB4F03C78;
                    asm volatile("" : "+r"(selected));
                    value = selected;
                }
            }
            *entry = value;
            entry += 2;
            i = (u8)(i + 1);
        } while (i <= 0x9F);
        return;
    }
    {
        register s32 value asm("r1");

        i = 0;
        value = 0x00F000F0;
        asm volatile("" : "+r"(value));
        do {
            *entry = value;
            entry += 2;
            i = (u8)(i + 1);
        } while (i <= 0x9F);
    }
}
