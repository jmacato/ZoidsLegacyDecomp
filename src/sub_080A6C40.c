#include "m2c_prelude.h"

extern void func_08092E84(u16);
extern s16 func_08092A90(s16);
extern s16 func_08092ADC(s16);
extern void func_0809534C(void);
extern void func_080955A0(void *, s16, s16, u8);
extern s32 func_080ECD98(s32, s32);
extern void func_080ED17C(s32);
extern volatile s16 D_03005EF8;
extern volatile s16 D_03005EFA;
extern volatile s16 D_03000052;

void sub_080A6C40(void)
{
    s16 records[21];
    u8 frame;
    register s32 phase asm("r9");

    func_08092E84(0x56);
    func_080955A0(records, 0x3F3F, 0x1F1F, 8);
    *(s16 *)0x0300004E = 0xBF;
    *(s16 *)0x05000000 = 0x7FFF;
    frame = 0;
    *(u8 *)0x03000075 = 2;

loop:
    {
        frame++;
        if (frame <= 31) {
            phase = frame >> 1;
            *(s16 *)0x03000052 = phase;
        } else {
            register u32 frame_view asm("r0") = frame;

            if (frame_view > 61) {
                register s32 new_phase asm("r1") = 16;
                register volatile s16 *scroll_target asm("r1");
                s32 scroll;

                phase = new_phase;
                D_03005EF8 = 0;
                D_03005EFA = 0x3F3F;
                scroll_target = &D_03000052;
                scroll = frame;
                scroll -= 60;
                if (scroll < 0) {
                    scroll += 3;
                }
                *scroll_target = scroll >> 2;
            }
        }

        {
            u8 column = 0;

            do {
                s32 index = column * 7;
                register s32 value asm("r5");

                records[index] = 3;
                records[index + 1] = 120;
                records[index + 2] = 32;
                value = func_080ECD98(column << 8, 3);
                asm("" : "+r"(value));
                value += (s32)frame * 4;
                {
                    register s32 phase_add asm("r0") = phase;
                    register s32 plus asm("r4");
                    register s32 phase_sub asm("r1");

                    plus = value + phase_add;
                    plus = (s16)plus;
                    records[index + 3] = func_08092ADC(plus) + 120;
                    records[index + 4] = func_08092A90(plus) + 32;
                    phase_sub = phase;
                    value -= phase_sub;
                    value = (s16)value;
                    records[index + 5] = func_08092ADC(value) + 120;
                    records[index + 6] = func_08092A90(value) + 32;
                }
                column++;
            } while (column <= 2);
            records[column * 7] = 0;
        }
    }
    func_080ED17C(1);
    {
        register u32 frame_view asm("r0") = frame;

        if (frame_view != 126) {
            goto loop;
        }
    }
    *(u8 *)0x03000075 = 1;
    func_0809534C();
}
