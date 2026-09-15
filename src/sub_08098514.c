#include "m2c_prelude.h"

struct Map98514 {
    u32 flags;
    s16 x;
    s16 y;
    u16 width;
    u16 height;
    s16 offset_x;
    s16 offset_y;
    u8 pad10[2];
    u8 unk12;
    u8 slot;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    s16 unk1C;
    u16 tiles[1];
};

extern struct Map98514 *func_0809716C(u8);
extern void func_080971AC(u8);
extern void func_08097DA8(struct Map98514 *, void *);
extern u32 D_02021664;
extern u16 D_02021668;
extern u8 D_0200E6C4[];
extern u8 D_0200DE90[];

void sub_08098514(s32 map_id, s32 x, s32 y, s32 width, s32 height, volatile s32 flags)
{
    register u32 saved_map_id asm("r9");
    register u32 saved_x asm("r7");
    register u32 saved_y asm("r5");
    register u32 saved_width asm("r4") = width;
    register u32 loaded_height asm("r3") = height;
    register u32 saved_height asm("r8");
    register struct Map98514 *map asm("r6");
    register u16 *tile asm("r2");
    u32 row;
    u32 frame_pad;

    map_id <<= 24;
    map_id = (u32)map_id >> 24;
    saved_map_id = map_id;
    x <<= 24;
    saved_x = (u32)x >> 24;
    y <<= 24;
    saved_y = (u32)y >> 24;
    saved_width <<= 24;
    saved_width = (u32)saved_width >> 24;
    loaded_height <<= 24;
    loaded_height = (u32)loaded_height >> 24;
    saved_height = loaded_height;
    asm volatile("" : : "m"(frame_pad));
    map = func_0809716C(map_id);
    map->x = saved_x;
    map->y = saved_y;
    map->width = saved_width;
    map->height = saved_height;
    map->offset_y = 0;
    map->offset_x = 0;
    map->unk12 = 0;
    map->unk1A = 0;
    map->unk19 = 0;
    map->unk1C = 0;
    map->unk1B = 0;
    {
        register s32 one asm("r0") = 1;
        register s32 loaded_flags asm("r5");

        asm volatile("" : "+r"(one));
        loaded_flags = flags;
        asm volatile("" : "+r"(loaded_flags));
        map->flags = loaded_flags | one;
    }

    tile = map->tiles;
    asm volatile("" : "+r"(tile));
    row = 0;
    if (row < saved_height) {
        u32 *base = &D_02021664;
        u16 *attribute = &D_02021668;

        do {
            u32 column = 0;
            u32 next_row = row + 1;

            asm volatile("" : :
                "r"(row), "r"(row), "r"(row),
                "r"(row), "r"(row), "r"(row),
                "r"(row), "r"(row), "r"(row));
            if (column < map->width) {
                register u32 *row_base asm("r4") = base;
                register u16 *row_attribute asm("r3") = attribute;

                asm volatile("" : "+r"(row_base), "+r"(row_attribute));
                do {
                    register u32 value asm("r0");

                    if (row == 0) {
                        if (column == 0) {
                            value = *row_base + 2;
                        } else if (column != map->width - 1) {
                            value = *row_base + 6;
                        } else {
                            value = *row_base + 3;
                        }
                    } else if (row != map->height - 1) {
                        if (column == 0) {
                            value = *row_base + 8;
                        } else if (column != map->width - 1) {
                            value = *row_base + 1;
                        } else {
                            value = *row_base + 9;
                        }
                    } else if (column == 0) {
                        value = *row_base + 4;
                    } else if (column != map->width - 1) {
                        value = *row_base + 7;
                    } else {
                        value = *row_base + 5;
                    }

                    asm volatile("" : "+r"(value));
                    *tile = value | *row_attribute;
                    tile++;
                    asm volatile("" : "+r"(tile));
                    {
                        u32 next_column = column + 1;

                        column = (u8)next_column;
                    }
                } while (column < map->width);
            }
            row = (u8)next_row;
        } while (row < map->height);
    }

    if (map->flags & 0x80) {
        D_0200E6C4[map->slot] = 0;
        D_0200DE90[map->slot * 0xD2] = 0;
        map->unk16 = 0;
        map->unk14 = 0;
        map->unk15 = 0;
        map->unk17 = 0xFF;
    }

    if (map->flags & 0x100) {
        register s16 zero16 asm("r4");
        register u8 zero8 asm("r7");
        s32 offset_x;

        offset_x = (map->width - 2) / 2 - 1;
        zero8 = 0;
        zero16 = 0;
        asm volatile("" : "+r"(zero8), "+r"(zero16));
        map->offset_x = offset_x;
        map->offset_y = map->height - 6;
        func_08097DA8(map, (void *)0x080ED930);

        map->offset_x = (map->width - 2) / 2 - 1;
        map->offset_y = map->height - 4;
        func_08097DA8(map, (void *)0x080ED938);

        map->offset_y = zero16;
        map->offset_x = zero16;
        map->unk16 = zero8;
    }

    func_080971AC(saved_map_id);
}
