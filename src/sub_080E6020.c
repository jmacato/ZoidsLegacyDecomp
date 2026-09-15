#include "m2c_prelude.h"

s32 sub_080E6020(s32 arg0) {
    register u32 normalized asm("r0");
    register u32 slot asm("r6");
    register u8 *base asm("r4");
    register s32 map_offset asm("r1");
    register u8 *map asm("r0");
    register u8 *map_slot asm("r3");
    register s32 entity_id asm("r0");

    normalized = arg0 << 24;
    normalized >>= 24;
    asm volatile("" : "+r"(normalized));
    slot = normalized;
    base = (u8 *)0x020218E4;
    map_offset = 0x690C;
    asm volatile("" : "+r"(base));
    asm volatile("" : "+r"(map_offset));
    map = (u8 *)((s32)base + map_offset);
    asm volatile("" : "+r"(map));
    map_slot = (u8 *)(slot + (s32)map);
    entity_id = *map_slot;
    if (entity_id != 0) {
        register s32 entity_copy asm("r1");
        register s32 entity_offset asm("r0");
        register u8 *entity_base asm("r1");
        register u8 *entity asm("r2");
        register s32 flags asm("r1");
        register s32 mask asm("r5");
        register s32 masked asm("r0");
        s32 zero;

        entity_copy = entity_id;
        entity_offset = entity_copy << 3;
        entity_offset -= entity_copy;
        entity_offset <<= 4;
        entity_base = base + 4;
        entity = (u8 *)(entity_offset + (s32)entity_base);
        flags = *(u16 *)(entity + 4);
        mask = 0xFFFB;
        masked = mask;
        masked &= flags;
        zero = 0;
        *(u16 *)(entity + 4) = masked;
        entity_id = entity[2];
        if (entity_id != 0) {
            register u8 *secondary asm("r0");
            register s32 secondary_offset asm("r1");
            register s32 secondary_flags asm("r2");
            register s32 secondary_mask asm("r1");

            entity_id <<= 6;
            secondary = (u8 *)(entity_id + (s32)base);
            secondary_offset = 0x5A96;
            asm volatile("" : "+r"(secondary_offset));
            secondary = (u8 *)((s32)secondary + secondary_offset);
            secondary_flags = *(u16 *)secondary;
            secondary_mask = mask;
            secondary_mask &= secondary_flags;
            *(u16 *)secondary = secondary_mask;
        }
        *map_slot = zero;
        {
            register s32 clear_offset asm("r1");
            register u8 *clear asm("r0");

            clear_offset = 0x691C;
            asm volatile("" : "+r"(clear_offset));
            clear = (u8 *)((s32)base + clear_offset);
            clear = (u8 *)(slot + (s32)clear);
            *clear = zero;
        }
        return 1;
    }
    return 0;
}
