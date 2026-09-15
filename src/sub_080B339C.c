#include "m2c_prelude.h"

struct EntityB339C {
    u8 pad00[4];
    u8 asset;
    u8 rest[0x6B];
};

s32 func_080981F0(s32, s32, s32, s32, s32);
void func_080986B4(s32);

s32 sub_080B339C(void) {
    u32 index;
    u8 *entity_base;
    s32 *asset_table;
    register s32 callback_result asm("r0");

    func_080986B4(3);
    index = 0;
    entity_base = (u8 *)0x020218E4;
    asset_table = (s32 *)0x087EDD54;
    do {
        register s32 map_offset asm("r1");
        register u8 *map asm("r0");
        register u8 *slot asm("r1");
        register s32 entity_id asm("r0");

        map_offset = 0x690C;
        map = (u8 *)((s32)entity_base + map_offset);
        slot = (u8 *)(index + (s32)map);
        entity_id = *slot;
        if (entity_id != 0) {
            register s32 entity_copy asm("r1");
            register s32 entity_offset asm("r0");
            register struct EntityB339C *entity asm("r0");
            register s32 asset_offset asm("r0");
            register s32 asset asm("r0");

            entity_copy = entity_id;
            entity_offset = entity_copy << 3;
            entity_offset -= entity_copy;
            entity_offset <<= 4;
            entity = (struct EntityB339C *)(entity_offset + (s32)entity_base);
            asset_offset = entity->asset << 2;
            asset = *(s32 *)(asset_offset + (s32)asset_table);
            callback_result = func_080981F0(asset, 0, 3, 0, index << 1);
        } else {
            callback_result = func_080981F0(0x081061A8, 0, 3, 0, index << 1);
        }
        {
            register u32 next_index asm("r1");

            next_index = index + 1;
            next_index <<= 24;
            index = next_index >> 24;
        }
    } while (index <= 5);
    return callback_result;
}
