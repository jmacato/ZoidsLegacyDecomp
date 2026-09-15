#include "m2c_prelude.h"

extern u8 D_030032D4[];

u8 func_809329C(s32);

s32 sub_08093138(s32 arg0) {
    register s32 saved_arg asm("r12");
    register volatile u32 *serial asm("r6");
    register u32 serial_value asm("r5");
    u8 *state;
    u8 *state_temp;
    register s32 phase asm("r2");

    saved_arg = arg0;
    asm volatile("" : "+r"(saved_arg));
    serial = (volatile u32 *)0x04000128;
    serial_value = *serial;
    state_temp = D_030032D4;
    phase = state_temp[1];
    state = state_temp;
    asm volatile("" : "+r"(serial), "+r"(serial_value), "+r"(state), "+r"(phase));
    switch (phase) {
    case 0: {
        register u32 status asm("r4");
        register u32 masked asm("r0");
        register u32 mask asm("r1");

        mask = 0x30;
        masked = serial_value;
        asm volatile("" : "+r"(masked), "+r"(mask));
        masked &= mask;
        if (masked == 0) {
            {
                register u32 mask88 asm("r0");

                mask88 = 0x88;
                status = serial_value;
                asm volatile("" : "+r"(status), "+r"(mask88));
                status &= mask88;
            }
            if (status != 8) {
                break;
            }
            {
                register s32 bit4_work asm("r0");
                register s32 bit4_mask asm("r1");
                u8 bit4;

                bit4_mask = 4;
                bit4_work = serial_value;
                asm volatile("" : "+r"(bit4_work), "+r"(bit4_mask));
                bit4_work &= bit4_mask;
                bit4 = bit4_work;
                if (bit4 == 0 && *(s32 *)(state + 0x14) == 0xC) {
                    volatile u16 *ime;
                    volatile u16 *display;
                    volatile u8 *serial_bytes;
                    volatile u32 *timer;

                    ime = (volatile u16 *)0x04000208;
                    *ime = bit4;
                    display = (volatile u16 *)0x04000200;
                    *display &= 0xFF7F;
                    *display |= 0x40;
                    *ime = 1;
                    serial_bytes = (volatile u8 *)serial;
                    {
                        s32 mask;
                        u8 serial_high;

                        serial_high = serial_bytes[1];
                        mask = 0x41;
                        mask = -mask;
                        serial_high &= mask;
                        serial_bytes[1] = serial_high;
                    }
                    {
                        register volatile u32 *timer_r1 asm("r1");
                        register s32 timer_value asm("r0");

                        timer_r1 = (volatile u32 *)0x0400010C;
                        timer_value = 0xABFB;
                        asm volatile("" : "+r"(timer_r1), "+r"(timer_value));
                        *timer_r1 = timer_value;
                        timer = timer_r1;
                    }
                    *(volatile u16 *)((u8 *)timer + 0xF6) = 0xC0;
                    state[0] = status;
                }
            }
        }
        state[1] = 1;
    }
        /* fallthrough */
    case 1: {
        u8 *case_state;

        case_state = D_030032D4;
        if (case_state[2] != 0) {
            u8 count;

            count = case_state[8];
            if ((u32)count <= 7) {
                case_state[8] = count + 1;
            } else {
                case_state[1] = 2;
            }
        }
    }
        /* fallthrough */
    case 2:
        func_809329C(saved_arg);
        break;
    }

    {
        u8 *end_base;
        register s32 low asm("r3");
        register s32 result asm("r2");
        register s32 second asm("r0");
        register s32 output asm("r0");
        s32 upper;
        s32 merged;
        s32 mode;

        end_base = D_030032D4;
        asm volatile("" : "+r"(end_base));
        end_base[11]++;
        low = end_base[3];
        second = end_base[2];
        result = second << 8;
        mode = end_base[0];
        state = end_base;
        asm volatile("" : "+r"(low), "+r"(result), "+r"(state));
        if (mode == 8) {
            merged = 0x80;
            merged |= result;
            merged |= low;
        } else {
            merged = low;
            merged |= result;
        }
        result = merged;
        if (state[7] != 0) {
            result |= 0x1000;
        }
        upper = (state[8] >> 3) << 15;
        asm volatile("" : "+r"(upper), "+r"(result));
        {
            u32 serial_bits;

            serial_bits = (serial_value << 26) >> 30;
            asm volatile("" : : "r"(serial_value));
            if (serial_bits <= 1) {
                goto low_result;
            }
        }
        output = 0x80;
        output <<= 6;
        output |= upper;
        output |= result;
        goto return_result;

low_result:
        output = result;
        output |= upper;
return_result:
        return output;
    }
}
