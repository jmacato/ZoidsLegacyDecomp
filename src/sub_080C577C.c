#include "m2c_prelude.h"

extern void func_080BB224(s32, s32, s32, s32);
extern s32 func_080BB654(void);
extern s32 func_080E9D88(s32, s32);
extern void func_080ED038(void *, const void *, u32);
extern void func_080ED17C(s32);
extern u32 D_02032E8C[];
extern u32 D_02032EBC[];
extern u8 D_02032EEC[];
extern u8 D_02032FE4[];
extern u32 D_02033E84;
extern u32 D_02033E9C;

void sub_080C577C(u8 arg0)
{
    volatile u32 slot[7];
    register u32 side asm("sl");

    slot[0] = arg0;
    side = 0;
    do {
        u32 index = 0;

        {
            register u32 next_side asm("r1") = side;

            next_side += 1;
            slot[4] = next_side;
        }
        while (index <= 2 && (func_080E9D88(side, index) << 24) == 0) {
            register u32 next asm("r0") = index + 1;

            next <<= 24;
            index = next >> 24;
        }
        if (index == 3) {
            func_080BB224(2, side, 0, 0);
            {
                register u32 twice asm("r2") = side;

                asm volatile("" : "+r"(twice));
                twice <<= 1;
                slot[3] = twice;
            }
            while ((func_080BB654() << 24) == 0) {
                func_080ED17C(1);
            }

            index = 3;
            {
                u32 value = slot[3] + side;

                register u32 scaled asm("r4") = value << 3;

                slot[1] = scaled;
                slot[2] = (value << 1) - 3;
            }
inner_loop:
            {
                register s32 active asm("r0") = func_080E9D88(side, index);

                active <<= 24;
                {
                    register u32 next_index asm("r1") = index + 1;

                    slot[5] = next_index;
                }
                if (active == 0) {
                    goto inactive_entry;
                }
                {
                    register u32 destination asm("r9");
                    register u32 destination_init asm("r2");
                    register u32 side_view asm("r4");
                    register u32 side_offset asm("r5");
                    register u32 source asm("r6");
                    register u32 index_four asm("r4");
                    register u32 first_offset asm("r8");

                    destination_init = index;
                    destination_init -= 3;
                    asm volatile("" : "+r"(destination_init));
                    destination = destination_init;
                    side_view = side;
                    asm volatile("" : "+r"(side_view));

                    if (side_view == 0) {
                        register u8 *base asm("r0") = (u8 *)0x0203724C;
                        register u8 *source_byte asm("r2");
                        register u32 value asm("r0");

                        source_byte = (u8 *)(index + (u32)base);
                        asm volatile("ldrb %0, [%1]"
                                     : "=r"(value)
                                     : "r"(source_byte));
                        {
                            register u8 *temporary asm("r1") =
                                (u8 *)0x02033EB4;

                            *temporary = value;
                        }
                        {
                            register u8 *destination_byte asm("r1") =
                                (u8 *)0x0203724C;

                            asm volatile("add %0, %1"
                                         : "+r"(destination_byte)
                                         : "r"(destination));
                            value = *destination_byte;
                            *source_byte = value;
                            {
                                register u8 *temporary asm("r2") =
                                    (u8 *)0x02033EB4;

                                value = *temporary;
                            }
                            *destination_byte = value;
                        }
                    }

                    index_four = index << 2;
                    first_offset = index_four;
                    source = index_four + index;
                    source <<= 3;
                    source -= index;
                    source <<= 4;
                    {
                        register u32 current_side asm("r0") = side;

                        side_offset = current_side << 2;
                        side_offset += side;
                        side_offset <<= 3;
                        side_offset -= current_side;
                        side_offset <<= 7;
                    }
                    source += side_offset;
                    {
                        register u32 base asm("r1") = 0x02034B4C;

                        asm volatile("" : "+r"(base));
                        source += base;
                    }
                    {
                        register void *scratch asm("r0") = D_02032FE4;
                        register const void *source_view asm("r1") =
                            (const void *)source;
                        register u32 size asm("r2") = 156;

                        size <<= 2;
                        func_080ED038(scratch, source_view, size);
                    }
                    {
                        register u32 destination_view asm("r2") = destination;
                        register u32 destination_four asm("r3") =
                            destination_view << 2;
                        register u32 target asm("r4");

                        target = destination_four + destination_view;
                        target <<= 3;
                        target -= destination_view;
                        target <<= 4;
                        target += side_offset;
                        {
                            register u32 base asm("r0") = 0x02034B4C;

                            target += base;
                        }
                        {
                            register void *source_view asm("r0") =
                                (void *)source;
                            register const void *target_view asm("r1") =
                                (const void *)target;
                            register u32 size asm("r2") = 156;

                            size <<= 2;
                            slot[6] = destination_four;
                            func_080ED038(source_view, target_view, size);
                        }
                        {
                            register void *target_view asm("r0") =
                                (void *)target;
                            register const void *scratch asm("r1") =
                                D_02032FE4;
                            register u32 size asm("r2") = 156;

                            size <<= 2;
                            func_080ED038(target_view, scratch, size);
                        }

                        {
                            register u32 *base asm("r1") = D_02032E8C;
                            register u32 slot_offset asm("r2") = slot[1];
                            register u32 *first asm("r2");
                            register u32 second_offset asm("r3");
                            register u32 *temporary asm("r4");

                            first_offset += slot_offset;
                            {
                                register u32 offset_view asm("r4") =
                                    first_offset;

                                asm volatile("" : "+r"(offset_view));
                                first = (u32 *)((u32)offset_view +
                                                (u32)base);
                            }
                            {
                                register u32 value asm("r0") = *first;

                                temporary = &D_02033E84;
                                *temporary = value;
                            }
                            second_offset = slot[6];
                            {
                                register u32 local_offset asm("r0") = slot[1];

                                second_offset += local_offset;
                            }
                            base = (u32 *)((u32)second_offset + (u32)base);
                            *first = *base;
                            *base = *temporary;

                            {
                                register u32 *temporary asm("r2") =
                                    &D_02033E9C;
                                register u32 *second_base asm("r1") =
                                    D_02032EBC;
                                register u32 *first_view asm("r4");
                                register u32 value asm("r0");

                                first_offset += (u32)second_base;
                                asm volatile("" : "+r"(first_offset));
                                first_view = (u32 *)first_offset;
                                value = *first_view;
                                *temporary = value;
                                second_offset += (u32)second_base;
                                value = *(u32 *)second_offset;
                                *first_view = value;
                                value = *temporary;
                                *(u32 *)second_offset = value;
                            }
                        }
                    }

                    if (slot[0] != 0) {
                        register u32 scan asm("r4") = 0;
                        register u8 *first asm("r3") = (u8 *)0x0203725F;
                        register u8 *second asm("r5") = first + 1;
                        register u32 replacement asm("r1") = destination;

                        do {
                            register u8 *offset asm("r2") =
                                (u8 *)(scan << 1);
                            register u8 *probe asm("r0") = offset;

                            probe += (u32)first;
                            if (*probe == side) {
                                offset += (u32)second;
                                if (*offset == index) {
                                    *offset = replacement;
                                }
                            }
                            {
                                register u32 next asm("r0") = scan + 1;

                                next <<= 24;
                                scan = next >> 24;
                            }
                        } while (scan <= 35);
                    }
                    {
                        register u8 *address asm("r1");

                        {
                            register u8 *base asm("r0") = D_02032EEC;
                            register u32 offset asm("r2") = slot[2];

                            address = (u8 *)(index + offset);
                            address += (u32)base;
                        }
                        {
                            register u32 one asm("r0") = 1;

                            *address = one;
                        }
                    }
                }
inactive_entry:
                {
                    register u32 saved_index asm("r4") = slot[5];
                    register u32 normalized asm("r0") = saved_index << 24;

                    index = normalized >> 24;
                }
                if (index > 5) {
                    goto inner_done;
                }
                goto inner_loop;
            }
inner_done:

            {
                register u32 *states asm("r5");
                register u8 *flags asm("r4");
                register u32 *state asm("r6");
                register u8 *flag asm("r3");
                register u32 base_index asm("r1");

                states = D_02032E8C;
                base_index = slot[3];
                base_index += side;
                flags = D_02032EEC;
                {
                    register u32 flag_offset asm("r0") = base_index << 1;

                    flag = (u8 *)(flag_offset + (u32)flags);
                }
                base_index <<= 3;
                state = (u32 *)(base_index + (u32)states);

wait_loop:
                {
                    register u32 one asm("r0") = 1;

                    slot[6] = (u32)flag;
                    func_080ED17C(one);
                }
                index = 0;
                {
                    register u32 value asm("r0") = *state;

                    flag = (u8 *)slot[6];
                    if (value == 0) {
                        goto search_loop;
                    }
                    value = *flag;
                    if (value != 0) {
                        goto found_slot;
                    }
                }

search_loop:
                {
                    register u32 next asm("r0") = index + 1;

                    next <<= 24;
                    index = next >> 24;
                }
                if (index > 2) {
                    goto advance_side;
                }
                {
                    register u32 state_offset asm("r0") = index << 2;
                    register u32 current_base asm("r2") = slot[3];
                    register u32 scaled_base asm("r1");
                    register u32 value asm("r0");

                    current_base += side;
                    scaled_base = current_base << 3;
                    state_offset += scaled_base;
                    state_offset += (u32)states;
                    value = *(u32 *)state_offset;
                    if (value == 0) {
                        goto search_loop;
                    }
                    value = current_base << 1;
                    value = index + value;
                    value += (u32)flags;
                    value = *(u8 *)value;
                    if (value == 0) {
                        goto search_loop;
                    }
                }

found_slot:
                if (index <= 2) {
                    goto wait_loop;
                }
            }
        }
advance_side:
        {
            register u32 next_side asm("r1") = slot[4];
            register u32 normalized asm("r0") = next_side << 24;

            side = normalized >> 24;
        }
    } while (side <= 1);
}
