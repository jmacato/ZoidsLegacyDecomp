#include "m2c_prelude.h"

struct Map98754 {
    u32 flags;
    u8 pad4[4];
    u16 width;
    u16 height;
    u8 padC[7];
    u8 refresh_id;
    u8 pad14[6];
    u8 extra_width;
};

struct Map98754 *func_809716C(u8);
void func_8097240(u8);
void func_8097980(u16);

extern u32 D_02021664;
extern s32 D_02021670;

void sub_08098754(u8 map_id)
{
    register struct Map98754 *map asm("r6") = func_809716C(map_id);
    register u16 *tile asm("r4") = (u16 *)((u8 *)map + 0x1E);
    s32 y = 0;

    goto test_rows;
rows:
    {
        s32 x = 0;
        s32 next_y = y + 1;

        {
            register s32 entry_width asm("r2") = map->width;
            asm volatile("" : "+r"(entry_width));
            if (x >= entry_width) {
                goto columns_done;
            }
        }
        {
            register u32 *base asm("r3") = &D_02021664;
            u32 * volatile base_spill;

            do {
                register u32 tile_id asm("r1") = *tile;
                register u32 mask asm("r2") = 0x3FF;
                register u32 mask_copy asm("r0") = mask;
                register u32 saved_tile_id asm("r2");

                asm volatile("" : "+r"(tile_id));
                asm volatile("" : "+r"(mask));
                mask_copy = mask;
                asm volatile("" : "+r"(mask_copy));
                tile_id &= mask_copy;
                saved_tile_id = tile_id;

                if (tile_id < *base || tile_id >= *base + 0x40) {
                    u16 removal = (u16)(saved_tile_id - D_02021670);
                    base_spill = base;
                    func_8097980(removal);
                    base = base_spill;
                }
                *tile++ = *base;
                x++;
                {
                    register s32 bottom_width asm("r0") = map->width;
                    asm volatile("" : "+r"(bottom_width));
                    if (x < bottom_width) {
                        goto next_column;
                    }
                }
                goto columns_done;
next_column:
                ;
            } while (1);
        }
columns_done:
        y = next_y;
    }
test_rows:
    if (y < map->height) {
        goto rows;
    }

    {
        register u32 flags asm("r1") = map->flags;

        if (flags & 8) {
            register s32 y asm("r0") = 0;
            register u32 *base asm("r3") = &D_02021664;

            do {
                register s32 x asm("r5") = 0;
                register s32 next_y asm("r7") = y + 1;

                asm volatile("" : "+r"(x));
                asm volatile("" : "+r"(next_y));

                {
                    register s32 entry_width asm("r2") = map->extra_width;
                    asm volatile("" : "+r"(entry_width));
                    if (x >= entry_width) {
                        goto extra_columns_done;
                    }
                }
                {
                    register u32 *load_base asm("r2") = base;
                    asm volatile("" : "+r"(load_base));
                    do {
                        *tile++ = *load_base;
                        x++;
                    } while (x < map->extra_width);
                }
extra_columns_done:
                y = next_y;
                asm volatile("" : "+r"(y));
            } while (y <= 2);
        }

        map->flags = flags | 6;
    }
    func_8097240(map->refresh_id);
}
