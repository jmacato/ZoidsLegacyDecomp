#include "m2c_prelude.h"

struct InputRecord {
    u8 value;
    u8 category;
    u8 x;
    u8 y;
};

struct TableEntry {
    u16 value;
    u16 x;
    u16 y;
    u16 unused;
};

extern struct TableEntry D_02030668[][32];
extern u8 D_020316F4;

u8 func_080A9EF0(u8);
void func_080A016C(u8, s32, s32);

s32 sub_080A1EB0(s32 arg0, struct InputRecord **arg1) {
    register struct InputRecord * volatile *source_slot asm("r5");
    register s32 saved_arg0 asm("r8");
    register s32 category asm("r1");
    register s32 mapped asm("r0");

    source_slot = (struct InputRecord * volatile *)arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    mapped = func_080A9EF0((*source_slot)->category);
    mapped <<= 24;
    category = (u32)mapped >> 24;
    if (category != 0xFF) {
        register u32 index asm("r3");
        s32 base;
        s32 row_offset;
        register struct TableEntry *row asm("r4");
        register s32 base_source asm("r0");
        register s32 row_source asm("r1");
        register u32 first_value asm("r2");

        index = 0;
        base_source = (s32)D_02030668;
        row_source = category << 8;
        row = (struct TableEntry *)(row_source + base_source);
        first_value = row->value;
        base = base_source;
        row_offset = row_source;
        if (first_value != 0) {
            register struct TableEntry *scan asm("r1");

            scan = row;
            do {
                scan += 1;
                index += 1;
                if (index > 0x1F) {
                    break;
                }
            } while (scan->value != 0);
        }
        if (index != 0x20) {
            register s32 slot_offset asm("r2");
            register s32 combined asm("r3");
            register struct TableEntry *entry asm("r1");
            struct InputRecord *input;

            slot_offset = index * 8;
            combined = slot_offset + row_offset;
            entry = (struct TableEntry *)(combined + base);
            entry->value = (*source_slot)->value;
            input = *source_slot;
            if ((u8)(input->value - 0x3C) <= 2 && D_020316F4 == 0) {
                register s32 address asm("r1");

                address = base + 2;
                address = combined + address;
                *(u16 *)address = input->x * 2;
                address = base + 4;
                address = combined + address;
                *(u16 *)address = (*source_slot)->y * 2;
            } else {
                register s32 fallback asm("r2");
                register s32 address asm("r0");
                register s32 value asm("r1");

                fallback = slot_offset;
                fallback += row_offset;
                address = base + 2;
                address = fallback + address;
                value = (*source_slot)->x;
                *(u16 *)address = value;
                address = base + 4;
                fallback += address;
                *(u16 *)fallback = (*source_slot)->y;
            }
        }
    }
    {
        register s32 minus_one asm("r1");

        minus_one = -1;
        func_080A016C(saved_arg0, minus_one, 0);
    }
    return 0;
}
