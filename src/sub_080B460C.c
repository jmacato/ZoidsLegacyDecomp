#include "m2c_prelude.h"

struct GridRecordB460C {
    u8 asset;
    u8 rest[0x26F];
};

s32 func_080981F0(s32, s32, s32, s32, s32);
void func_080986B4(s32);

s32 sub_080B460C(void) {
    u32 index;
    u8 *grid_base;
    s32 *asset_table;
    register s32 callback_result asm("r0");

    func_080986B4(3);
    index = 0;
    grid_base = (u8 *)0x02034B4C;
    asset_table = (s32 *)0x087EDD54;
    do {
        register s32 map_offset asm("r1");
        register u8 *map asm("r0");
        register u8 *slot asm("r1");
        register s32 row_id asm("r0");

        map_offset = 0xA084;
        map = (u8 *)((s32)grid_base + map_offset);
        slot = (u8 *)(index + (s32)map);
        row_id = *slot;
        if (row_id != 0xFF) {
            register s32 row_copy asm("r1");
            register s32 row_offset asm("r0");
            register struct GridRecordB460C *row asm("r0");
            register s32 asset_offset asm("r0");
            register s32 asset asm("r0");

            row_copy = row_id;
            row_offset = row_copy << 2;
            row_offset += row_copy;
            row_offset <<= 3;
            row_offset -= row_copy;
            row_offset <<= 4;
            row = (struct GridRecordB460C *)(row_offset + (s32)grid_base);
            asset_offset = row->asset << 2;
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
