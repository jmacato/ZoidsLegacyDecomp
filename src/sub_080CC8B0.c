#include "m2c_prelude.h"
struct Slot {
    u8 pad0[4];
    s16 x;
    s16 y;
};

void sub_080CC8B0(void)
{
    u8 *counters;
    struct Slot **slots;
    s16 *from;
    s16 *to;
    u8 mode;
    s32 value;
    u8 i;
    struct Slot *frame_slot;

    {
        u8 *first_counters = (u8 *)0x02033FAC;
        u8 count = first_counters[0];

        counters = first_counters;
        if (count <= 7)
            counters[0] = count + 1;
    }

    {
        struct Slot **first_slots = (struct Slot **)0x02033F58;
        struct Slot *first = first_slots[0];
        s16 *first_from;
        s16 *first_to;

        asm volatile("" : "+r"(first));
        first_from = (s16 *)0x02033F74;
        first_to = (s16 *)0x02033F90;

        value = (first_to[0] - first_from[0]) * counters[0];
        asm volatile("" :: "r"(first_from), "r"(first_to));
        slots = first_slots;
        from = first_from;
        to = first_to;
        asm volatile("" :: "r"(from));
        asm volatile("" :: "r"(to));
        asm volatile("" :: "r"(to));
        if (value < 0)
            value += 7;
        first->x = from[0] + (value >> 3);
    }
    {
        register struct Slot *second asm("r5") =
            *(struct Slot *volatile *)slots;

        value = (to[1] - from[1]) * counters[0];
        if (value < 0)
            value += 7;
        {
            s32 shifted = value >> 3;
            register u32 carrier asm("r1") = (u32)from;
            carrier = *(u16 *)(carrier + 2);
            second->y = (u32)((u8 *)shifted + carrier);
            asm volatile("" :: "r"(carrier));
        }
    }

    mode = *(u8 *)0x02033FB3;
    switch (mode) {
    case 0: {
        register struct Slot **case_slots asm("r6");

        i = 6;
        case_slots = slots;
        asm volatile("" : "+r"(case_slots));
        do {
            register s32 previous asm("r3");
            register struct Slot **current_ref asm("r2");
            register struct Slot **previous_ref asm("r1");
            struct Slot *current_slot;

            current_ref = (struct Slot **)(i * 4 + (u32)case_slots);
            current_slot = *(struct Slot *volatile *)current_ref;
            previous = i - 1;
            asm volatile("" : "+r"(previous));
            previous_ref =
                (struct Slot **)(previous * 4 + (u32)case_slots);
            current_slot->x = (*(struct Slot *volatile *)previous_ref)->x;
            (*(struct Slot *volatile *)current_ref)->y =
                (*(struct Slot *volatile *)previous_ref)->y;
            i = previous;
        } while (i != 0);
        asm volatile("" :: "r"(i), "r"(i), "r"(i), "r"(i));
        break;
    }
    case 1:
        for (i = 1; i <= 6; i++) {
            register u8 *counter asm("r4");
            u8 count;
            {
                register u8 *counter_base asm("r2") = counters;
                asm volatile("" : "+r"(counter_base));
                counter = (u8 *)((u32)i + (u32)counter_base);
            }
            count = *counter;
            if (count <= 7)
                *counter = count + 1;
            {
                register u32 offset asm("r2");
                register struct Slot **slot_ref asm("r6");
                struct Slot *second_slot;

                offset = i * 4;
                asm volatile("" : "+r"(offset));
                {
                    register u32 guard0 asm("r0");
                    register u32 guard1 asm("r1");
                    asm volatile("" : "=r"(guard0), "=r"(guard1));
                    slot_ref = (struct Slot **)(offset + (u32)slots);
                    asm volatile("" :: "r"(guard0), "r"(guard1));
                }
                asm volatile("" : "+r"(slot_ref));
                frame_slot = *(struct Slot *volatile *)slot_ref;
                {
                    register s16 *from_ref asm("r3");
                    register s16 *to_ref asm("r0");
                    register s32 delta asm("r1");

                    from_ref = (s16 *)(offset + (u32)from);
                    to_ref = (s16 *)(offset + (u32)to);
                    delta = *to_ref;
                    asm volatile("" : "+r"(delta));
                    delta -= *from_ref;
                    value = delta * *counter;
                    if (value < 0)
                        value += 7;
                    frame_slot->x = *from_ref + (value >> 3);
                }
                second_slot = *(struct Slot *volatile *)slot_ref;
                {
                    register s16 *from_ref asm("r3");
                    register u32 base asm("r0");

                    base = (u32)from;
                    asm volatile("" : "+r"(base));
                    base += 2;
                    asm volatile("" : "+r"(base));
                    from_ref = (s16 *)(offset + base);
                    base = (u32)to;
                    asm volatile("" : "+r"(base));
                    base += 2;
                    asm volatile("" : "+r"(base));
                    base = offset + base;
                    asm volatile("" : "+r"(base));
                    value = (*(s16 *)base - *from_ref) * *counter;
                    if (value < 0)
                        value += 7;
                    second_slot->y = *from_ref + (value >> 3);
                }
            }
        }
        break;
    default:
        break;
    }
}
