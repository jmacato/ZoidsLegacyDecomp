#include "m2c_prelude.h"

extern void func_0809A9C8(s32, s32, s32, s32, s32, s32);
extern void *func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_080A016C(u8, s32, s32);

struct Event {
    u8 pad0;
    u8 kind;
    u8 value;
};

s32 sub_080A1550(u8 arg0, struct Event **event_slot) {
    register u8 saved_arg0 asm("r8") = arg0;
    if (*(s32 *)0x02021690 != 10) {
        register struct Event *event asm("r0") = *event_slot;
        register s32 kind asm("r3") = event->kind;
        register s32 value asm("r1") = event->value;
        register s32 special asm("r2");
        register s32 screen asm("r4");
        register s32 layer asm("r5");
        register s32 *slot asm("r6");

        if (kind == 75) {
            register u32 special_base asm("r0") = 0x020218E4;
            register u32 special_offset asm("r2") = 0x6809;
            asm volatile("" : "+r"(special_base), "+r"(special_offset));
            special = *(u8 *)(special_base + special_offset);
        } else {
            special = 0;
        }
        screen = 0x3C2;
        layer = 14;
        func_0809A9C8(kind, value, special, screen, layer,
            0x02002880);
        slot = (s32 *)0x02031744;
        if (*slot == 0) {
            *slot = (s32)func_08094484(0x08359850, 0x0835985C, 0, 8,
                104, screen, layer, 8, 0);
        }
    } else {
        register struct Event *event asm("r0") = *event_slot;
        register s32 kind asm("r3") = event->kind;
        register s32 value asm("r1") = event->value;
        register s32 special asm("r2");
        s32 *slot;
        register s32 screen asm("r5");
        register s32 layer asm("r6");
        register s32 empty asm("r4");

        if (kind == 75) {
            register u32 special_base asm("r0") = 0x020218E4;
            register u32 special_offset asm("r2") = 0x6809;
            asm volatile("" : "+r"(special_base), "+r"(special_offset));
            special = *(u8 *)(special_base + special_offset);
        } else {
            special = 0;
        }
        screen = 0x3DC;
        layer = 15;
        func_0809A9C8(kind, value, special, screen, layer,
            0x02002880);
        slot = (s32 *)0x02031744;
        empty = *slot;
        if (empty == 0) {
            if (*(u8 *)0x02031748 == 0) {
                if (*(u8 *)0x02033F36 == 0) {
                    *slot = (s32)func_08094484(0x08359850, 0x0835985C,
                        0, -1, 104 + 10, screen, layer, 8, empty);
                } else {
                    *slot = (s32)func_08094484(0x08359850, 0x0835985C,
                        0, 193, 104 + 10, screen, layer, 8, empty);
                }
            } else {
                *slot = (s32)func_08094484(0x08359850, 0x0835985C, 0, 8,
                    104, screen, layer, 8, empty);
            }
        }
    }
    {
        register s32 minus_one asm("r1") = 1;
        register u8 callback_arg asm("r0");

        minus_one = -minus_one;
        callback_arg = saved_arg0;
        func_080A016C(callback_arg, minus_one, 0);
    }
    return 0;
}
