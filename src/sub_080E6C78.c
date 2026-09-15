#include "m2c_prelude.h"

extern u8 D_02027378[];
extern u8 D_087B70E4[];
extern s32 D_087B77C8[];
extern u8 D_087B7958[];
extern u8 D_020217B4[];

void func_080E6E04(u8, void *);
void func_080E705C(void *, s32);
s32 func_0809F818(s32);

u8 sub_080E6C78(u8 arg0) {
    register u8 slot_seed asm("r6");
    u32 slot;
    u8 id;
    u32 created;
    u8 *base;
    register u8 *base_load asm("r0");
    u8 *record;
    u8 initial_record;
    u8 *definition;
    register u32 value asm("r0");
    register u32 mask asm("r1");
    register u32 id_shift asm("r2");
    register u32 *flags asm("r2");

    id = arg0;
    created = 0;
    slot_seed = 1;
    slot = slot_seed;
    base_load = D_02027378;
    record = base_load;
    record += 0x40;
    initial_record = *record;
    base = base_load;
    if (initial_record != 0) {
find_match:
        {
            register u32 next asm("r0");
            next = slot + 1;
            next <<= 24;
            slot = next >> 24;
        }
        if (slot > 0x34) {
            goto match_search_done;
        }
        {
            register u32 offset asm("r0");
            offset = slot << 6;
            record = (u8 *)(offset + (u32)base);
        }
        if (*record != 0) {
            goto find_match;
        }
    }
check_match:
    if ((*(u16 *)(record + 2) >> 8) != id) {
        goto find_match;
    }
match_search_done:
    if (slot == 0x35) {
        slot = 1;
        record = base + 0x40;
        value = *(u32 *)(base + 0x40);
        mask = 0xFF0000FF;
        goto test_free;
advance_free:
        {
            register u32 next asm("r0");
            next = slot + 1;
            next <<= 24;
            slot = next >> 24;
        }
        if (slot > 0x34) {
            goto check_free;
        }
        {
            register u32 offset asm("r0");
            offset = slot << 6;
            record = (u8 *)(offset + (u32)base);
        }
        value = *(u32 *)record;
test_free:
        if ((value & mask) != 0) {
            goto advance_free;
        }
check_free:
        if (slot == 0x35) {
            return 0xFF;
        }
        created = 1;
    }

    {
        register u32 definition_offset asm("r0");
        register u8 *definition_base asm("r1");
        definition_offset = id << 4;
        definition_base = D_087B70E4;
        definition = (u8 *)(definition_offset + (u32)definition_base);
    }
    value = 0;
    record[0] = id;
    record[1] = value;
    id_shift = id << 8;
    if (created == 0) {
        mask = *(u16 *)(record + 2);
        value = 1;
        value &= mask;
    } else {
        value = 1;
    }
    *(u16 *)(record + 2) = value | id_shift;

    if (created != 0) {
        *(u32 *)(record + 4) = D_087B77C8[definition[0] - 1];
        {
            register u8 *field30 asm("r0");
            register u32 definition_type asm("r1");
            definition_type = definition[0];
            field30 = record;
            field30 += 0x30;
            *field30 = definition_type;
        }
        if (definition[1] != 0) {
            func_080E6E04(definition[1], record);
        }
        {
            register u8 *field32 asm("r3");
            u32 definition_subtype;
            definition_subtype = definition[2];
            field32 = record;
            field32 += 0x32;
            *field32 = definition_subtype;
        }
        {
            register u8 *attribute_table asm("r2");
            attribute_table = D_087B7958;
            asm volatile("" : : "r"(attribute_table));
        }
        *(u16 *)(record + 0x26) = *(u16 *)(D_087B7958 + (record[0x32] * 12));
        *(u16 *)(record + 0x28) = *(u16 *)(D_087B7958 + (record[0x32] * 12) + 2);
        *(u16 *)(record + 0x2A) = *(u16 *)(D_087B7958 + (record[0x32] * 12) + 4);
        *(u16 *)(record + 0x2C) = *(u16 *)(D_087B7958 + (record[0x32] * 12) + 6);
        *(u16 *)(record + 0x2E) = *(u16 *)(D_087B7958 + (record[0x32] * 12) + 8);
        *(u16 *)(record + 0x34) = *(u16 *)(definition + 4);
        *(u16 *)(record + 0x36) = *(u16 *)(definition + 6);
        *(u16 *)(record + 0x38) = *(u16 *)(definition + 8);
        *(u16 *)(record + 0x3A) = *(u16 *)(definition + 10);
        *(u16 *)(record + 0x3C) = *(u16 *)(definition + 12);
        func_080E705C(record, 1);
    }

    {
        register u8 *status_base asm("r4");
        register u32 flag_offset asm("r2");
        register u8 *flag_address asm("r0");
        status_base = D_020217B4;
        flag_offset = id >> 5;
        flag_offset <<= 2;
        flag_address = status_base;
        flag_address += 0x14;
        flag_offset += (u32)flag_address;
        flags = (u32 *)flag_offset;
        *flags |= 1 << (id & 0x1F);
        if ((u8)(id - 0x60) <= 1 && (func_0809F818(2) << 24) != 0) {
            *(u32 *)(status_base + 0x14) |= 4;
        }
        if (id == 0x5F) {
            register u8 *final_base asm("r0");
            register u32 final_flags asm("r1");
            final_base = D_020217B4;
            final_flags = *(u32 *)(final_base + 0x14);
            final_flags |= 0x40000000;
            *(u32 *)(final_base + 0x14) = final_flags;
        }
    }
    return slot;
}
