#include "m2c_prelude.h"

extern u8 D_02000000[];
extern s16 *D_03005F04[];
extern u16 D_03005EEA[];
extern u16 D_03005EEE[];
s16 func_080ECD30(s32, s32);

void sub_0809570C(void)
{
    u8 buffer = 1 ^ *(u8 *)0x03005F12;
    u16 *entry = (u16 *)(D_02000000 + buffer * 0x500);
    u8 outer;

    outer = 0;
    do {
        s16 *values = D_03005F04[outer];
        u32 next = outer + 1;

        if (values != 0) {
            u32 mult = D_03005EEA[outer];
            u32 div = D_03005EEE[outer];
            s16 i;

            if (mult == 0 || div == 0) {
                i = 0;
                do {
                    *entry = 0;
                    entry += 4;
                    i++;
                } while (i <= 159);
            } else {
                s32 coord;
                s16 *value;

                div = (u16)func_080ECD30(0x10000, div);
                coord = -(div * 80) + 0x5000;
                i = 0;
                do {
                    coord += div;
                    if ((u32)coord > 0x9FFF) {
                        *entry = 0;
                        asm volatile("" : "=r"(value));
                    } else {
                        s32 tmp = coord;
                        u16 raw;
                        s32 a, b;

                        asm volatile("" : "+r"(tmp));
                        if (coord < 0) {
                            tmp += 255;
                        }
                        value = (s16 *)((tmp >> 8) * 4 + ({
                            register s32 vbase asm("r1") = (s32)values;
                            asm volatile("" : "+r"(vbase));
                            vbase;
                        }));
                        raw = value[0];
                        asm volatile("" : "+r"(raw));
                        a = (s16)raw;
                        asm volatile("" :: "r"(raw));
                        b = value[1];

                        if (a < b) {
                            u16 left, right;

                            tmp = a - 120;
                            tmp *= mult;
                            if (tmp < 0) {
                                tmp += 255;
                            }
                            left = (tmp >> 8) + 120;
                            tmp = b - 120;
                            tmp *= mult;
                            if (tmp < 0) {
                                tmp += 255;
                            }
                            right = (tmp >> 8) + 120;
                            if ((s16)left < 0) {
                                left = 0;
                            } else if ((s16)left > 240) {
                                left = 240;
                            }
                            if ((s16)right < 0) {
                                right = 0;
                            } else if ((s16)right > 240) {
                                right = 240;
                            }
                            asm volatile("" :: "r"(left));
                            asm volatile("" :: "r"(left));
                            asm volatile("" :: "r"(left));
                            {
                                s32 packed = (s16)left << 8;
                                s32 packed2 = (s16)right | packed;

                                asm volatile("" : "+r"(packed2));
                                *entry = packed2;
                            }
                        } else {
                            *entry = 0;
                        }
                    }
                    entry += 4;
                    i++;
                } while (i <= 159);
            }
            entry -= 0x27F;
        }
        outer = next;
    } while (outer <= 1);
}
