#include "m2c_prelude.h"
void sub_080BAA40(s32 arg0, u8 *arg1) {
    register s32 selected asm("r6");
    s32 started;
    register s32 counter asm("r5");
    register volatile u8 *cursor asm("r2");
    register s32 aux asm("r4");

    cursor = arg1;
    selected = (u8)arg0;
    {
        register s32 started_input asm("r7");

        started_input = 0;
        started = started_input;
    }
    counter = 10;
    do {
        if (selected != 0xFF) {
            if (selected + 10 <= counter) {
                started = 1;
            }
            if (!({
                register s32 parity asm("r0");

                parity = 1;
                parity &= counter;
                parity;
                })) {
                if (started) {
                    register s32 value asm("r0");
                    register s32 byte asm("r1");

                    cursor[0] = (0xF0 & cursor[0]) | 3;
                    byte = cursor[4];
                    asm volatile("add r0, r3, #0" : "=r"(value));
                    value &= byte;
                    aux = 10;
                    value |= aux;
                    cursor[4] = value;
                    if ((u32)counter > 0x10) {
                        cursor[8] = (0xF0 & cursor[8]) | aux;
                    }
                }
                goto next;
            }
            if (started) {
                register s32 mask asm("r3");
                register s32 value asm("r0");
                register s32 byte asm("r1");

                byte = cursor[0];
                mask = 0xF;
                value = mask;
                asm volatile("" : "+r"(value));
                value &= byte;
                byte = 0x30;
                value |= byte;
                cursor[0] = value;
                byte = cursor[4];
                value = mask;
                asm volatile("" : "+r"(value));
                value &= byte;
                aux = 0xA0;
                value |= aux;
                cursor[4] = value;
                if ((u32)counter > 0x10) {
                    byte = cursor[8];
                    value = mask;
                    asm volatile("" : "+r"(value));
                    value &= byte;
                    value |= aux;
                    cursor[8] = value;
                }
            }
            if ((u32)(counter & 7) <= 6) {
                goto selected_advance_byte;
            }
            goto selected_advance_row;
selected_advance_byte:
            cursor += 1;
            goto next;
selected_advance_row:
            cursor += 0x1D;
            goto next;
        } else if (!({
            register s32 parity asm("r0");

            parity = 1;
            parity &= counter;
            parity;
        })) {
            register s32 value asm("r0");
            register s32 byte asm("r1");
            register s32 nibble asm("r3");

            byte = cursor[0];
            aux = 0xF0;
            value = aux;
            asm volatile("" : "+r"(value));
            value &= byte;
            nibble = 0xE;
            value |= nibble;
            cursor[0] = value;
            byte = cursor[4];
            value = aux;
            asm volatile("" : "+r"(value));
            value &= byte;
            value |= nibble;
            cursor[4] = value;
            if ((u32)counter > 0x10) {
                byte = cursor[8];
                value = aux;
                asm volatile("" : "+r"(value));
                value &= byte;
                value |= nibble;
                cursor[8] = value;
            }
            goto next;
        } else {
            register s32 value asm("r0");
            register s32 byte asm("r1");
            register s32 nibble asm("r3");

            byte = cursor[0];
            aux = 0xF;
            value = aux;
            asm volatile("" : "+r"(value));
            value &= byte;
            nibble = 0xE0;
            value |= nibble;
            cursor[0] = value;
            byte = cursor[4];
            value = aux;
            asm volatile("" : "+r"(value));
            value &= byte;
            value |= nibble;
            cursor[4] = value;
            if ((u32)counter > 0x10) {
                byte = cursor[8];
                value = aux;
                asm volatile("" : "+r"(value));
                value &= byte;
                value |= nibble;
                cursor[8] = value;
            }
            if ((u32)(counter & 7) <= 6) {
                cursor += 1;
            } else {
                cursor += 0x1D;
            }
            goto next;
        }
next:
        {
            register u8 next_counter asm("r0");

            next_counter = counter + 1;
            asm volatile("" : "+r"(next_counter));
            counter = next_counter;
        }
    } while ((u32)counter <= 0x1D);
}
