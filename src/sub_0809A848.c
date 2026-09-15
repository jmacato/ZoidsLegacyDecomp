#include "m2c_prelude.h"

void func_0809A1BC(s32, s32, s32);
void func_080ECD34(s32, s32);

void sub_0809A848(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    register u32 table_offset asm("r5") = arg0;
    register u32 tile_index asm("r4") = arg2;
    register u32 second_index asm("r8") = arg3;
    register u32 palette_index asm("r9");
    register u32 resource_base asm("r6");
    register u32 vram_base asm("sl");
    register u32 stacked_arg asm("r0");
    u16 *tiles;
    u32 value;

    asm volatile("" : "+r"(table_offset));
    asm volatile("" : "+r"(tile_index));
    asm volatile("" : "+r"(second_index));
    stacked_arg = *(volatile u32 *)&arg4;
    asm volatile("" : "+r"(stacked_arg));
    table_offset <<= 24;
    arg1 <<= 24;
    tile_index <<= 24;
    tile_index >>= 24;
    {
        register u32 temp asm("r2") = second_index;

        asm volatile("" : "+r"(temp));
        temp <<= 24;
        temp >>= 24;
        second_index = temp;
    }
    stacked_arg <<= 24;
    stacked_arg >>= 24;
    palette_index = stacked_arg;

    resource_base = 0x087AF614;
    table_offset >>= 20;
    {
        register u32 resource asm("r0");
        register u32 call_offset asm("r1");
        register u32 base asm("r2");

        resource = table_offset + resource_base;
        resource = *(u32 *)resource;
        asm volatile("" : "+r"(resource));
        call_offset = (u32)arg1 >> 10;
        base = 0xC0;
        base <<= 19;
        asm volatile("" : "+r"(base));
        vram_base = base;
        call_offset += vram_base;
        func_080ECD34(resource, call_offset);
    }
    {
        register u32 resource asm("r0") = resource_base;
        register u32 palette asm("r1");
        register u32 work asm("r2");

        resource += 4;
        resource = table_offset + resource;
        resource = *(u32 *)resource;
        asm volatile("" : "+r"(resource));
        palette = 0xA0;
        palette <<= 19;
        asm volatile("" : "+r"(palette));
        work = 0x02002880;
        func_0809A1BC(resource, palette, work);
    }

    tile_index <<= 11;
    {
        register u32 base asm("r0") = vram_base;

        asm volatile("" : "+r"(base));
        tiles = (u16 *)(tile_index + base);
    }
    value = 0x100;
    {
        register u32 outer asm("r1") = 0;
        u32 second_offset;
        register u32 palette_offset asm("r8");
        register u32 increment asm("r5");
        register u32 tile_base asm("r4");

        vram_base = resource_base;
        resource_base = table_offset;
        {
            register u32 temp asm("r0") = second_index;

            second_offset = temp << 14;
        }
        {
            register u32 temp asm("r0") = palette_index;

            palette_offset = temp << 11;
        }
        {
            register u32 increment_source asm("r0") = 0x202;

            asm volatile("" : "+r"(increment_source));
            increment = increment_source;
        }

        do {
            register u32 inner asm("r4") = 0;

            do {
                    tiles[0] = value;
                    tiles[4] = value;
                    tiles[0x40] = value;
                    tiles[0x44] = value;
                    tiles++;
                    {
                        register u32 next asm("r0") = value + increment;

                        next <<= 16;
                        value = next >> 16;
                    }
                    {
                        register u32 next asm("r0") = inner + 1;

                        next <<= 24;
                        inner = next >> 24;
                    }
                } while (inner <= 3);
            tiles += 4;
            {
                register u32 next asm("r0") = outer + 1;

                next <<= 24;
                outer = next >> 24;
            }
        } while (outer <= 7);

        {
            register u32 resource asm("r0") = vram_base;
            register u32 target asm("r1");

            resource += 8;
            resource = resource_base + resource;
            resource = *(u32 *)resource;
            asm volatile("" : "+r"(resource));
            tile_base = 0xC0;
            tile_base <<= 19;
            target = second_offset + tile_base;
            func_080ECD34(resource, target);
        }
        {
            register u32 resource asm("r0") = vram_base;
            register u32 palette asm("r1");
            register u32 work asm("r2");

            resource += 12;
            resource = resource_base + resource;
            resource = *(u32 *)resource;
            asm volatile("" : "+r"(resource));
            palette = 0x05000080;
            work = 0x02002880;
            func_0809A1BC(resource, palette, work);
        }

        {
            register u32 offset asm("r0") = palette_offset;

            tiles = (u16 *)(offset + tile_base);
        }
        value = 0;
        outer = 0;
        do {
            register u32 inner asm("r4") = 0;

            outer += 1;
            do {
                tiles[0] = value;
                tiles[0x10] = value;
                tiles++;
                {
                    register u32 next asm("r0") = value + 1;

                    next <<= 16;
                    value = next >> 16;
                }
                {
                    register u32 next asm("r0") = inner + 1;

                    next <<= 24;
                    inner = next >> 24;
                }
            } while (inner <= 0xF);
            tiles += 0x10;
            {
                register u32 narrowed asm("r0") = outer << 24;

                outer = narrowed >> 24;
            }
        } while (outer <= 0xF);
    }
}
