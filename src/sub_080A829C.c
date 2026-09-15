#include "m2c_prelude.h"

extern s32 D_03000010;
extern u8 D_02033F36;

s32 func_080ECD5C(s32);
s32 *func_08094374(s32, u8, s32, s16, s32, s32, s32, s32, s32);
void func_08092E84(s32);
void func_080ED17C(s32);

void sub_080A829C(void)
{
    s32 frame_counter;
    s32 delay;
    u32 j;

    {
        s32 *counter;
        s32 zero;
        s32 **slots;

        j = 0;
        counter = (s32 *)0x02031C10;
        asm volatile("" : "+r"(counter));
        zero = 0;
        slots = (s32 **)0x02031C14;
        do {
            *slots++ = (s32 *)zero;
            j++;
        } while (j <= 31);
        *counter = 0;
    }

    frame_counter = 0;
    delay = 18;
mainloop:
    {
        s32 one;
        s32 **slot;

        j = 0;
        one = 1;
        slot = (s32 **)0x02031C14;
        do {
            s32 v = (s32)*slot;

            if (v != 0) {
                v = *(s32 *)v;
                v &= one;
                if (v == 0) {
                    *slot = (s32 *)v;
                }
            }
            slot++;
            asm volatile("" : : "r"(slot), "r"(slot), "r"(slot), "r"(slot), "r"(slot), "r"(slot), "r"(slot));
            j++;
        } while (j <= 31);
    }

    if (frame_counter == delay || delay == 0) {
        s32 *rng;
        register s32 **slot asm("r5");
        s32 offset;

        j = 0;
        rng = &D_03000010;
        slot = (s32 **)0x02031C14;
        offset = 0;
        do {
            s32 *entry = *slot;

            if (entry == 0) {
                register s32 frame asm("r8");
                register s32 angle asm("r6");
                s32 t;
                s32 visual;
                s32 *object;
                s32 mode;
                s32 *obj2;
                s32 scaled;

                frame = ((u32)(func_080ECD5C(*rng) * 3) >> 15) + 2;
                angle = (func_080ECD5C(*rng) << 8) >> 16;
                t = (u32)(func_080ECD5C(*rng) * 10) >> 15;
                visual = 0x348;
                if (t != 0) {
                    visual += 0x80;
                }
                object = func_08094374(0x087ACDD8, 0x77, (u16)frame, 0, angle,
                                       (s32)entry, (s32)entry, visual,
                                       0x080CCEF1);
                *slot = object;
                mode = D_02033F36;
                if (mode != 0) {
                    mode = 0xF000;
                }
                object[10] = mode;
                {
                    u8 *pA = (u8 *)0x02031C14;

                    asm volatile("" : "+r"(pA));
                    obj2 = *(s32 **)(pA + offset);
                }
                scaled = frame + 1;
                scaled <<= 10;
                obj2[11] = scaled;
                goto created;
            }
            slot++;
            offset += 4;
            j++;
        } while (j <= 31);
created:
        frame_counter = 0;
        if (delay != 0) {
            delay--;
            if (delay == 0) {
                func_08092E84(0x68);
            }
        }
    } else {
        frame_counter++;
    }

    {
        s32 c = *(s32 *)0x02031C10;

        if ((u32)c <= 0x12B) {
            *(s32 *)0x02031C10 = c + 1;
        }
    }
    func_080ED17C(1);
    goto mainloop;
}
