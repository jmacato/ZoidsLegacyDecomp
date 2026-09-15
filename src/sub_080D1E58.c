#include "m2c_prelude.h"

extern volatile u8 D_02034862;
extern volatile u8 D_02034863;
extern volatile s16 D_02034864;
extern volatile s16 D_02034866;
extern volatile u8 D_02034868;
extern s32 D_03000054[];

void sub_080D1E58(void)
{
    register volatile u8 *state_address asm("r0") = &D_02034863;
    register s32 mode asm("r1") = *state_address;
    register volatile u8 *state asm("r8") = state_address;

    switch (mode) {
    case 1:
        {
            register volatile s16 *phase_address asm("r0") = &D_02034864;
            register u32 current asm("r2") = *(u16 *)phase_address;
            register u32 phase_offset asm("r3");
            register s32 phase_value asm("r1");
            register volatile s16 *phase asm("ip");

            asm volatile(
                "mov %1, #0\n\t"
                "ldrsh %0, [%2, %1]"
                : "=r"(phase_value), "=&l"(phase_offset)
                : "l"(phase_address));
            phase = phase_address;
            if (phase_value <= 0x3F) {
                {
                    register u32 incremented asm("r0") = current + 1;
                    register volatile s16 *store_base asm("r7") = phase;

                    asm volatile("strh %1, [%0]"
                                 :
                                 : "l"(store_base), "l"(incremented)
                                 : "memory");
                }
                {
                    register s32 index asm("r4") = 0;
                    register u32 one_source asm("r0") = 1;
                    register u32 one asm("r9") = one_source;
                    register volatile u8 *mask_base asm("r6") =
                        (volatile u8 *)0x0203EE70;
                    register volatile u8 *bank asm("r5") = &D_02034868;
                    register volatile s16 *phase_view asm("r1") = phase;

                    do {
                    register u32 parity asm("r0") = 1;
                    register volatile u8 *output asm("r2");
                    register u32 value asm("r3");

                    parity &= index;
                    if (parity == 0) {
                        register u32 address asm("r0") = *bank;

                        {
                            register u32 one_view asm("r2") = one;

                            address ^= one_view;
                        }
                        address <<= 7;
                        address = index + address;
                        asm volatile("add %0, %1, %2"
                                     : "=l"(output)
                                     : "l"(address), "l"(mask_base));
                        value = 0;
                        {
                            register u32 offset asm("r7");
                            register s32 width asm("r0");

                            asm volatile(
                                "mov %1, #0\n\t"
                                "ldrsh %0, [%2, %1]"
                                : "=r"(width), "=&l"(offset)
                                : "l"(phase_view));
                            width <<= 1;
                            if (index > width) {
                                value = 1;
                            }
                        }
                    } else {
                        register u32 address asm("r0") = *bank;

                        {
                            register u32 one_view asm("r2") = one;

                            asm volatile("" : "+r"(one_view));
                            address ^= one_view;
                        }
                        address <<= 7;
                        address = index + address;
                        asm volatile("add %0, %1, %2"
                                     : "=l"(output)
                                     : "l"(address), "l"(mask_base));
                        value = 0;
                        {
                            register u32 offset asm("r7");
                            register s32 width asm("r0");

                            asm volatile(
                                "mov %1, #0\n\t"
                                "ldrsh %0, [%2, %1]"
                                : "=r"(width), "=&l"(offset)
                                : "l"(phase_view));
                            width <<= 1;
                            width = -width;
                            width += 0x7F;
                            if (index < width) {
                                value = 1;
                            }
                        }
                    }
                    asm volatile("strb %1, [%0]"
                                 :
                                 : "l"(output), "l"(value)
                                 : "memory");
                    index = (u8)(index + 1);
                    } while ((s8)index >= 0);
                }
            } else {
                register s32 negative_sixteen asm("r1") = 0x10;
                register s32 store_value asm("r0");

                negative_sixteen = -negative_sixteen;
                asm volatile("" : "+r"(negative_sixteen));
                store_value = negative_sixteen;
                {
                    register volatile s16 *store_base asm("r2") = phase;

                    *store_base = store_value;
                }
                {
                    register volatile s16 *phase_b asm("r1") = &D_02034866;
                    register u32 zero asm("r0") = 0;

                    *phase_b = zero;
                }
                {
                    register u32 two asm("r0") = 2;
                    register volatile u8 *state_view asm("r3") = state;

                    *state_view = two;
                }
            }
        }
        break;
    case 2:
        {
            register volatile s16 *phase_a_address asm("r1") = &D_02034864;
            register s32 phase_a_value asm("r0") =
                *(u16 *)phase_a_address;
            register volatile s16 *phase_a asm("ip");

            phase_a_value += 1;
            *phase_a_address = phase_a_value;
            phase_a_value <<= 16;
            phase_a_value >>= 16;
            phase_a = phase_a_address;
            if (phase_a_value == 0x80) {
                register s32 negative_sixteen asm("r7") = 0x10;
                register s32 store_value asm("r0");

                negative_sixteen = -negative_sixteen;
                store_value = negative_sixteen;
                *phase_a_address = store_value;
            }
            {
                register volatile s16 *phase_b_address asm("r0") =
                    &D_02034866;
                register u32 phase_b_value asm("r1") =
                    *(u16 *)phase_b_address;
                register u32 compare_value asm("r2") = 0x80;
                register volatile s16 *phase_b asm("r5");

                phase_b_value += 1;
                *phase_b_address = phase_b_value;
                phase_b_value <<= 16;
                compare_value <<= 17;
                phase_b = phase_b_address;
                if (phase_b_value == compare_value) {
                    *phase_b = 0;
                }
                {
                    register s32 index asm("r4") = 0;
                    register volatile u8 *bank_source asm("r0");
                    register volatile u8 *bank asm("r9");
                    register volatile u8 *mask_base asm("r6");

                    bank_source = &D_02034868;
                    asm volatile("" : "+r"(bank_source));
                    bank = bank_source;
                    mask_base = (volatile u8 *)0x0203EE70;
                    do {
                        register volatile u8 *bank_view asm("r1") = bank;
                        register u32 bank_value asm("r0") = *bank_view;
                        register u32 address asm("r1") = 1;
                        volatile u8 *output;
                        register u32 value asm("r3");

                        address ^= bank_value;
                        address <<= 7;
                        address = index + address;
                        output = (volatile u8 *)((u32)address +
                                                 (u32)mask_base);
                        value = 0;
                        if (bank_value & 1) {
                            register volatile s16 *phase_view = phase_a;
                            register u32 offset asm("r1");
                            register s32 lower asm("r0");

                            asm volatile(
                                "mov %1, #0\n\t"
                                "ldrsh %0, [%2, %1]"
                                : "=r"(lower), "=&l"(offset)
                                : "l"(phase_view));
                            if (index >= lower) {
                                lower += 0x10;
                                if (index <= lower) {
                                    goto case2_active;
                                }
                            }
                        }
                        {
                            register u32 offset asm("r7");
                            register s32 half_phase asm("r0");

                            asm volatile(
                                "mov %1, #0\n\t"
                                "ldrsh %0, [%2, %1]"
                                : "=r"(half_phase), "=&l"(offset)
                                : "l"(phase_b));
                            half_phase /= 2;
                            if (index != half_phase) {
                                goto case2_write;
                            }
                        }
case2_active:
                        value = 1;
case2_write:
                        *output = value;
                        index = (u8)(index + 1);
                    } while ((s8)index >= 0);
                }
            }
        }
        break;
    case 3:
        {
            register volatile s16 *phase asm("r1") = &D_02034864;
            register u32 current asm("r2") = *(u16 *)phase;
            register u32 phase_offset asm("r3");
            register s32 phase_value asm("r0");

            asm volatile(
                "mov %1, #0\n\t"
                "ldrsh %0, [%2, %1]"
                : "=r"(phase_value), "=&l"(phase_offset)
                : "l"(phase));
            if (phase_value > 0) {
                {
                    register u32 decremented asm("r0") = current - 1;

                    *phase = decremented;
                }
                {
                    register s32 index asm("r4") = 0;
                    register u32 one_source asm("r7") = 1;
                    register u32 one asm("r9");
                    register volatile u8 *mask_base asm("r6");
                    register volatile u8 *bank asm("r5");
                    register volatile s16 *phase_view asm("r3");

                    asm volatile("" : "+r"(one_source));
                    one = one_source;
                    mask_base = (volatile u8 *)0x0203EE70;
                    bank = &D_02034868;
                    phase_view = phase;
                    do {
                    register u32 parity asm("r0") = 1;
                    register volatile u8 *output asm("r1");
                    register u32 value asm("r2");

                    parity &= index;
                    if (parity != 0) {
                        register u32 address asm("r0") = *bank;

                        {
                            register u32 one_view asm("r1") = one;

                            address ^= one_view;
                        }
                        address <<= 7;
                        address = index + address;
                        asm volatile("add %0, %1, %2"
                                     : "=l"(output)
                                     : "l"(address), "l"(mask_base));
                        value = 0;
                        {
                            register u32 offset asm("r7");
                            register s32 width asm("r0");

                            asm volatile(
                                "mov %1, #0\n\t"
                                "ldrsh %0, [%2, %1]"
                                : "=r"(width), "=&l"(offset)
                                : "l"(phase_view));
                            width <<= 1;
                            if (index > width) {
                                value = 1;
                            }
                        }
                    } else {
                        register u32 address asm("r0") = *bank;

                        {
                            register u32 one_view asm("r1") = one;

                            asm volatile("" : "+r"(one_view));
                            address ^= one_view;
                        }
                        address <<= 7;
                        address = index + address;
                        asm volatile("add %0, %1, %2"
                                     : "=l"(output)
                                     : "l"(address), "l"(mask_base));
                        value = 0;
                        {
                            register u32 offset asm("r7");
                            register s32 width asm("r0");

                            asm volatile(
                                "mov %1, #0\n\t"
                                "ldrsh %0, [%2, %1]"
                                : "=r"(width), "=&l"(offset)
                                : "l"(phase_view));
                            width <<= 1;
                            width = -width;
                            width += 0x7F;
                            if (index < width) {
                                value = 1;
                            }
                        }
                    }
                    asm volatile("strb %1, [%0]"
                                 :
                                 : "l"(output), "l"(value)
                                 : "memory");
                    index = (u8)(index + 1);
                    } while ((s8)index >= 0);
                }
            } else {
                D_02034862 = 2;
            }
        }
        break;
    }

    {
        register volatile u8 *state_view asm("r1") = state;
        register u32 active asm("r0") = *state_view;

        if (active != 0) {
            register s32 *camera asm("r1") = D_03000054;
            register s32 value asm("r0") = camera[4];
            register u32 step asm("r2") = 0x80;

            step <<= 5;
            value += step;
            camera[2] = value;
        }
    }
}
