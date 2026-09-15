#include "m2c_prelude.h"

s32 sub_080E5FA8(s32 arg0, s32 arg1) {
    register u32 action asm("r5");
    register u32 slot asm("r6");
    register u8 *entity asm("r1");
    register s32 entity_offset asm("r0");

    arg0 <<= 24;
    action = (u32)arg0 >> 24;
    arg1 <<= 24;
    slot = (u32)arg1 >> 24;
    entity_offset = slot << 3;
    entity_offset -= slot;
    entity_offset <<= 4;
    entity = (u8 *)0x020218E8;
    asm volatile("" : "+r"(entity));
    entity = (u8 *)(entity_offset + (s32)entity);
    if (entity[2] != 0) {
        register u8 *state asm("r0");

        state = entity;
        state += 0x38;
        if (*state != 4 || action == 1 || action == 4) {
            register s32 flags asm("r0");
            register s32 mask asm("r3");
            register s32 zero asm("r4");
            register u8 *base asm("r2");
            register s32 entity_id asm("r0");
            register u8 *secondary asm("r0");
            register s32 secondary_offset asm("r1");
            register s32 secondary_flags asm("r1");
            register s32 map_offset asm("r1");
            register u8 *map asm("r0");
            register s32 clear_offset asm("r0");
            register u8 *clear asm("r2");

            flags = *(u16 *)(entity + 4);
            mask = 4;
            zero = 0;
            flags |= mask;
            *(u16 *)(entity + 4) = flags;

            base = (u8 *)0x020218E4;
            asm volatile("" : "+r"(base));
            entity_id = entity[2];
            entity_id <<= 6;
            secondary = (u8 *)(entity_id + (s32)base);
            asm volatile("" : "+r"(secondary));
            secondary_offset = 0x5A96;
            asm volatile("" : "+r"(secondary_offset));
            secondary = (u8 *)((s32)secondary + secondary_offset);
            secondary_flags = *(u16 *)secondary;
            secondary_flags |= mask;
            *(u16 *)secondary = secondary_flags;

            map_offset = 0x690C;
            asm volatile("" : "+r"(map_offset));
            map = (u8 *)((s32)base + map_offset);
            asm volatile("" : "+r"(map));
            map = (u8 *)(action + (s32)map);
            *map = slot;
            clear_offset = 0x691C;
            asm volatile("" : "+r"(clear_offset));
            clear = (u8 *)((s32)base + clear_offset);
            asm volatile("" : "+r"(clear));
            clear = (u8 *)(action + (s32)clear);
            *clear = zero;
            return 1;
        }
    }
    return 0;
}
