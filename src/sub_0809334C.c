#include "m2c_prelude.h"

extern u8 D_030032D4[];

void sub_0809334C(void) {
    u8 *state;
    register s32 mode asm("r1");

    state = D_030032D4;
    mode = state[0];
    if (mode != 0) {
        if (state[4] != 0 && state[1] != 0 && state[6] != 0) {
            s32 temp;
            volatile u16 *serial;
            volatile u16 *timer;
            u32 serial_value;
            s32 zero;

            *(s32 *)(state + 0x18) = -1;
            temp = *(s32 *)(state + 0x28);
            *(s32 *)(state + 0x28) = *(s32 *)(state + 0x24);
            *(s32 *)(state + 0x24) = temp;
            temp = *(s32 *)(state + 0x20);
            *(s32 *)(state + 0x20) = *(s32 *)(state + 0x1C);
            *(s32 *)(state + 0x1C) = temp;
            zero = 0;
            state[4] = zero;
            *(s32 *)(state + 0x14) = zero;

            serial = (volatile u16 *)0x04000128;
            serial_value = *(volatile u32 *)serial;
            state[7] = (serial_value << 25) >> 31;
            {
                register s32 serial_high asm("r0");

                serial_high = 0xFEFE;
                asm volatile("" : "+r"(serial_high));
                serial[1] = serial_high;
            }
            serial[0] |= 0x80;
            timer = (volatile u16 *)0x0400010E;
            *timer = 0xC0;
        }
    } else {
        u8 count;

        count = state[9];
        if ((u32)count <= 3) {
            state[9] = count + 1;
        } else {
            volatile u16 *ime;
            volatile u16 *ie;

            ime = (volatile u16 *)0x04000208;
            *ime = mode;
            ie = (volatile u16 *)0x03007FF8;
            *ie |= 0x80;
            *ime = 1;
        }
    }
}
