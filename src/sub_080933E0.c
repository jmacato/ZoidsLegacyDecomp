#include "m2c_prelude.h"

extern u8 D_030032D4[];

void sub_080933E0(void) {
    u32 packet[2];
    volatile u32 *packet_source;
    u32 first;
    u32 second;
    u8 *initial_state;
    u8 *state;
    u32 serial_value;
    u32 serial_bit;
    s32 zero;
    s32 magic;
    u16 incoming;

    packet_source = (volatile u32 *)0x04000120;
    second = packet_source[1];
    first = packet_source[0];
    packet[0] = first;
    packet[1] = second;

    initial_state = D_030032D4;
    serial_value = *(volatile u32 *)0x04000128;
    serial_bit = (serial_value << 25) >> 31;
    asm volatile("" : "+r"(serial_bit));
    zero = 0;
    initial_state[7] = serial_bit;
    incoming = *(u16 *)packet;
    magic = 0xFEFE;
    state = initial_state;
    if (incoming == magic && *(volatile s32 *)(state + 0x18) > 9) {
        s32 temp;
        volatile u16 *ime;
        volatile u16 *ie;

        *(volatile s32 *)(state + 0x18) = -1;
        temp = *(s32 *)(state + 0x28);
        *(s32 *)(state + 0x28) = *(s32 *)(state + 0x24);
        *(s32 *)(state + 0x24) = temp;
        if (state[4] != 0) {
            temp = *(s32 *)(state + 0x20);
            *(s32 *)(state + 0x20) = *(s32 *)(state + 0x1C);
            *(s32 *)(state + 0x1C) = temp;
            state[4] = zero;
            *(volatile s32 *)(state + 0x14) = zero;
        }
        ime = (volatile u16 *)0x04000208;
        *ime = zero;
        ie = (volatile u16 *)0x03007FF8;
        *ie |= 0x80;
        *ime = 1;
    }

    {
        register s32 index asm("r0");
        register u8 *value_base asm("r1");
        u16 value;
        register volatile u16 *serial_output asm("r2");

        index = *(volatile s32 *)(state + 0x14);
        if (index <= 9) {
            serial_output = (volatile u16 *)0x04000128;
            asm volatile("" : "+r"(serial_output));
            value_base = *(u8 * volatile *)(state + 0x20);
            asm volatile("" : "+r"(index), "+r"(value_base));
            value = *(u16 *)(value_base + index * 2);
            serial_output[1] = value;
        }
    }
    {
        s32 index;

        index = *(volatile s32 *)(state + 0x14);
        if (index <= 10) {
            *(volatile s32 *)(state + 0x14) = index + 1;
        }
    }
    asm volatile("" : : : "memory");

    {
        register s32 receive_index asm("r0");
        register u16 *destination asm("r1");
        register u16 *source asm("r2");
        s32 count;

        receive_index = *(volatile s32 *)(state + 0x18);
        if (receive_index >= 0) {
            destination = (u16 *)*(u8 * volatile *)(state + 0x24);
            source = (u16 *)packet;
            asm volatile("" : "+r"(receive_index), "+r"(destination), "+r"(source));
            destination = (u16 *)((u8 *)destination + receive_index * 2);
            count = 1;
            do {
                *destination = *source;
                source++;
                destination = (u16 *)((u8 *)destination + 0x18);
                count--;
            } while (count >= 0);
            if (*(volatile s32 *)(state + 0x18) == 9) {
                state[5] = 1;
            }
        }
    }
    {
        s32 receive_index;

        receive_index = *(volatile s32 *)(state + 0x18);
        if (receive_index <= 10) {
            *(volatile s32 *)(state + 0x18) = receive_index + 1;
        }
    }
    asm volatile("" : : : "memory");

    {
        u8 mode;

        mode = state[0];
        if (mode != 0) {
            *(volatile u16 *)0x0400010E = 0;
        }
        if (*(volatile s32 *)(state + 0x14) <= 10 && mode != 0) {
            volatile u16 *serial_half;

            serial_half = (volatile u16 *)0x04000128;
            serial_half[0] |= 0x80;
            *(volatile u16 *)0x0400010E = 0xC0;
        }
    }
    state[9] = 0;
}
