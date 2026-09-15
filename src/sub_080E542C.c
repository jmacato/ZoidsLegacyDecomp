#include "m2c_prelude.h"

void sub_080E542C(void *arg0) {
    u8 *base = (u8 *)arg0;
    u8 i;
    u32 f4;

    i = 0;
    do {
        register s32 sv asm("r0");
        register u16 *slot asm("r1");

        sv = i << 2;
        asm volatile("" : "+r"(sv));
        sv = (s32)base + sv;
        asm volatile("" : "+r"(sv));
        slot = (u16 *)sv;
        asm volatile("" : "+r"(slot));
        slot = (u16 *)((u8 *)slot + 0x52);
        sv = *slot;
        if (sv != 0) {
            register s32 t asm("r1");
            register s32 off asm("r0");
            register u8 *cat asm("r1");
            u8 *e;

            t = sv;
            asm volatile("" : "+r"(t));
            off = t << 1;
            off += t;
            off <<= 3;
            cat = (u8 *)0x087B2524;
            asm volatile("" : "+r"(cat));
            e = (u8 *)(off + (s32)cat);
            if ((*(u16 *)(e + 2) & 7) == 3
                && *(u8 *)(e + 9) == 6
                && (*(u32 *)(e + 4) & 0x1F000000) == 0) {
                f4 = *(u32 *)(e + 4);
                if ((f4 & 0xFF) != 0x16) {
                    switch (f4 & 0xFF) {
                    case 2:
                        *(u16 *)(base + 0x48) += *(u16 *)(e + 12);
                    case 1:
                        *(u16 *)(base + 0x46) += *(u16 *)(e + 10);
                        break;
                    case 5:
                        *(u16 *)(base + 0x44) += *(u16 *)(e + 12);
                    case 3:
                        *(u16 *)(base + 0x42) += *(u16 *)(e + 10);
                        break;
                    case 4:
                        *(u16 *)(base + 0x44) += *(u16 *)(e + 10);
                        break;
                    case 6:
                    case 8:
                        *(u16 *)(base + 0x4A) += *(u16 *)(e + 10);
                        break;
                    case 10:
                        *(u16 *)(base + 0x40) += *(u16 *)(e + 10);
                        break;
                    case 15:
                        *(u16 *)(base + 0x3E) += *(u16 *)(e + 12);
                    case 13:
                        *(u16 *)(base + 0x3A) += *(u16 *)(e + 10);
                        break;
                    case 14:
                        *(u16 *)(base + 0x3E) += *(u16 *)(e + 10);
                        break;
                    }
                }
            }
        }
        i = i + 1;
    } while (i <= 7);
}
