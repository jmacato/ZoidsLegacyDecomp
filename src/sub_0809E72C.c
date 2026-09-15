#include "m2c_prelude.h"

struct Actor9E72C {
    u32 unk00;
    u8 kind;
    u8 pad05[3];
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    u8 pad18[6];
    u8 flags;
};

struct Availability9E72C {
    u8 pad00[4];
    u8 available;
};

extern u32 func_080ECD5C(u32);
extern u16 func_080ECF00(u32, u32);
extern struct Actor9E72C *D_02032990;
extern u16 D_0202ECF4;
extern u16 D_020324A4;
extern s32 D_020324A8;
extern s32 D_020324AC;
extern u8 D_020324B7;
extern u8 D_0203055C[];
extern u32 D_03000010;
extern u16 D_08478FA0[];
extern u8 D_087B9454[];
extern u16 D_087C3864[];
extern u8 D_087C3884[];

s32 sub_0809E72C(void)
{
    u8 candidates[20];
    register struct Actor9E72C *actor asm("r4") = D_02032990;
    register s32 *map_position asm("r3");
    u32 encounter;
    register u32 threshold asm("r8");

    if ((u8)(actor->kind - 0x69) > 2) {
        goto fail;
    }
    if (actor->dx == 0 && actor->dy == 0) {
        goto fail;
    }
    map_position = &D_020324A8;
    asm volatile("" : "+r"(map_position));
    if ((*map_position & ~0xF) == (D_020324AC & ~0xF)) {
        goto fail;
    }
    if (actor->flags & 0x40) {
        goto fail;
    }

    if (D_0202ECF4 == 0) {
        s32 x = actor->x;
        s32 y;
        u32 cell_x;
        register u32 byte_mask asm("r5");
        u32 cell_y;
        u32 tile_offset;
        u16 map_width;
        u8 *tiles;
        u16 tile;

        if (x < 0) {
            x += 0xFFF;
        }
        cell_x = x >> 12;
        byte_mask = 0xFF;
        cell_x &= byte_mask;
        y = actor->y;
        if (y < 0) {
            y += 0xFFF;
        }
        cell_y = (y >> 12) & byte_mask;
        map_width = D_020324A4;
        tile_offset = (((cell_y * map_width) >> 1) + cell_x) << 1;
        tiles = (u8 *)D_08478FA0;
        tile = *(u16 *)(tiles + tile_offset);
        threshold = D_087C3864[tile >> 8];
        encounter = byte_mask;
        encounter &= tile;
    } else {
        register u8 *encounter_table asm("r2") = D_087C3884;
        register u32 offset asm("r1");
        register u8 *threshold_base asm("r0");

        asm volatile("" : "+r"(encounter_table));
        offset = D_020324B7 * 6;
        threshold_base = encounter_table + 2;
        threshold_base = (u8 *)(offset + (u32)threshold_base);
        threshold = *(u16 *)threshold_base;
        encounter_table += 4;
        offset += (u32)encounter_table;
        encounter = *(u16 *)offset;
    }

    if (encounter == 0) {
        goto fail;
    }

    {
        register u32 mask asm("r6");
        register u32 *rng asm("r5");
        register u32 chance asm("r4");
        register u32 *late_rng asm("ip");
        register u32 shift asm("r0");
        u16 required;

        shift = *map_position;
        asm volatile("" : "+r"(shift));
        shift <<= 12;
        mask = (u32)shift >> 16;
        if (mask > 7) {
            mask = 1;
        } else {
            mask = (u16)(0x100 >> mask);
        }

        rng = &D_03000010;
        chance = ((u32)(func_080ECD5C(*rng) * 1000)) >> 15;
        required = func_080ECF00(threshold, mask);
        late_rng = rng;
        asm volatile("" : "+r"(late_rng));
        if ((s32)chance >= (s32)required) {
            goto fail;
        }

        D_0203055C[3] = encounter;
        {
            register u32 count asm("r6") = 0;
            register u32 outer asm("r4") = 0;
            register u32 category_offset asm("r2");
            register u8 *table asm("r5");
            register u32 hundred asm("r8");
            register u32 category asm("r0");

            category = encounter << 5;
            asm volatile("" : "+r"(category));
            table = D_087B9454;
            hundred = 100;
            category -= encounter;
            category <<= 2;
            category += encounter;
            category_offset = category << 4;
outer_loop:
            {
                register u32 inner asm("r1") = 0;
                register u32 next_outer asm("r7") = outer + 1;
                u32 row_offset = hundred * outer;

scan_loop:
                {
                    u32 offset = inner << 4;
                    struct Availability9E72C *entry;

                    offset += row_offset;
                    offset += category_offset;
                    offset += (u32)table;
                    entry = (struct Availability9E72C *)offset;
                    if (entry->available != 0) {
                        register u8 *stack_base asm("r1") = candidates;
                        register u8 *destination asm("r0");
                        register u32 next_count asm("r0");

                        asm volatile("" : "+r"(stack_base));
                        destination = stack_base + count;
                        asm volatile("" : "+r"(destination));
                        *destination = outer;
                        next_count = count + 1;
                        asm volatile("" : "+r"(next_count));
                        count = (u8)next_count;
                        goto next_row;
                    }
                }
                {
                    register u32 next_inner asm("r0") = inner + 1;

                    asm volatile("" : "+r"(next_inner));
                    inner = (u8)next_inner;
                }
                if (inner <= 5) {
                    goto scan_loop;
                }
next_row:
                {
                    register u32 normalized_outer asm("r0");

                    normalized_outer = next_outer << 24;
                    asm volatile("" : "+r"(normalized_outer));
                    outer = normalized_outer >> 24;
                }
            }
            if (outer <= 0x13) {
                goto outer_loop;
            }
            {
                register u32 *late_rng_view asm("r1") = late_rng;

                asm volatile("" : "+r"(late_rng_view));
                D_0203055C[4] = candidates[
                    (u32)(func_080ECD5C(*late_rng_view) * count) >> 15];
            }
        }
    }
    return 1;

fail:
    return 0;
}
