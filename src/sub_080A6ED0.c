#include "m2c_prelude.h"

struct ConfigA6ED0 {
    s32 x;
    s32 y;
    s32 scale;
    s16 width;
    s16 unk0E;
    s16 unk10;
    u8 pad12[2];
    s32 center_x;
    s32 center_y;
    s32 size;
    u8 pad20[0x40];
    s32 flags;
};

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
s32 *func_08094374(M2C_UNK, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32 *);                       /* extern */
M2C_UNK func_08095208(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A4CC(s32, s32, s32, s32);          /* extern */
M2C_UNK func_0809A9C8(s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809AA64(M2C_UNK, s32, s32, s32);      /* extern */
M2C_UNK func_080ECD28(M2C_UNK, s32, s32);           /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080A6ED0(void) {
    s32 *frame[2];
    s32 *temp_r0;
    s32 *temp_r0_2;
    register u8 *temp_r0_3 asm("r0");
    register s32 *temp_r9 asm("r9");
    register u32 var_r5 asm("r5");
    register s32 zero_r4 asm("r4");

    asm volatile("" : : "m"(frame[1]));
    {
        register s32 *mode asm("r1") = (s32 *)0x02021690;
        asm volatile("" : "+r"(mode));
        *mode = 9;
    }
    {
        register s32 *color asm("r1") = (s32 *)0x02030558;
        register s32 value asm("r0") = 0xFF10;
        asm volatile("" : "+r"(color), "+r"(value));
        *color = value;
    }
    {
        register s8 *color_mode asm("r1") = (s8 *)0x0203055C;
        register s32 value asm("r0");
        register struct ConfigA6ED0 *config asm("r1");
        asm volatile("" : "+r"(color_mode));
        zero_r4 = 0;
        asm volatile("" : "+r"(zero_r4));
        value = 0x14;
        color_mode[1] = value;
        config = (struct ConfigA6ED0 *)0x030033C4;
        asm volatile("" : "+r"(config));
        config->x = zero_r4;
        config->y = zero_r4;
        config->scale = 0x10000;
        var_r5 = 0;
        config->width = 0x20;
        asm volatile(
            "strh r4, [r1, #16]\n\t"
            "strh r4, [r1, #14]"
            : : "r"(zero_r4), "r"(config) : "memory");
        config->center_x = 0x78;
        config->center_y = 0x58;
        config->size = 0x80;
        config->flags = 0x20000;
    }
    func_080ED17C(1);
    func_0809A4CC(0x91, 0, 0, 0);
    temp_r0 = func_08094484(0x0821024C, 0x08210258, 0, 0,
        zero_r4, zero_r4, zero_r4, 0x82C8, 0x080BAE19);
    *(s32 **)0x02032E8C = temp_r0;
    M2C_FIELD(temp_r0, s32 *, 0x28) = zero_r4;
    M2C_FIELD(temp_r0, s32 *, 0x2C) = zero_r4;
    M2C_FIELD(temp_r0, s32 *, 0x30) = zero_r4;
    *(s8 *)0x02032EEC = var_r5;
    func_0809AA64(0x087AF9D4, 6, 0x40, 1);
    temp_r0_2 = func_08094374(0x087AFA94, 6, 0, 0,
        zero_r4, 0x40, 1, 0x7E0, 0x080A6DB1);
    frame[0] = temp_r0_2;
    temp_r0_3 = (u8 *)temp_r0_2;
    temp_r0_3 += 0x28;
    *(s32 *)temp_r0_3 = 0x6000;
    *(s32 *)(temp_r0_3 + 4) = zero_r4;
    *(s32 *)(temp_r0_3 + 8) = zero_r4;
    func_08096308(1, 0x10);
    goto test_ready_1;
wait_ready_1:
    func_080ED17C(1);
test_ready_1:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_1;
    }
    temp_r9 = func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, 0);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(0x34, 2, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018272);
    func_0809A9C8(0x34, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x0801829D);
    {
        register s32 *load_flags asm("r1") = temp_r9;
        register u32 flags asm("r0");
        register s32 *store_flags asm("r1");
        asm volatile("" : "+r"(load_flags));
        flags = *load_flags;
        flags |= 0x20000;
        store_flags = temp_r9;
        asm volatile("" : "+r"(store_flags));
        *store_flags = flags;
    }
    func_08098BB4(0x08017BE6);
    {
        register s32 *fade asm("r5") = (s32 *)((u8 *)frame[0] + 0x28);
        asm volatile("" : "+r"(fade));
        if (*fade != 0) {
            register s32 *current asm("r4");
            do {
                current = fade;
                asm volatile("" : "+r"(current));
                *fade += 0xFFFFFF00;
                func_080ED17C(1);
            } while (*current != 0);
        }
    }
    func_08094554(frame[0]);
    {
        register s32 target asm("r0") = 0x05000200;
        register s32 palette asm("r4");
        asm volatile("" : "+r"(target));
        palette = 0x02002880;
        asm volatile("" : "+r"(palette));
        func_080ECD28(target, palette, 8);
    }
    var_r5 = 0;
    func_08092E84(0x54);
    {
        register u32 max_channel asm("r6") = 0x1F;
        register u16 *output_base asm("sl") = (u16 *)0x020028A0;
        register u32 next_outer asm("r8");
        u32 inner;
        register s32 factor asm("r4");

        asm volatile("" : "+r"(max_channel), "+r"(output_base));
outer_palette:
        inner = 0;
        next_outer = var_r5 + 1;
        factor = max_channel - var_r5;
inner_palette:
        {
            register u32 offset asm("r2") = inner << 1;
            register u16 *input_base asm("r1") = (u16 *)0x02002880;
            register u32 input_address asm("r0");
            register u32 color asm("r0");
            register u32 red asm("r3");
            register u32 green asm("r1");
            register s32 blend asm("r0");

            asm volatile("" : "+r"(offset), "+r"(input_base));
            input_address = offset + (u32)input_base;
            asm volatile("" : "+r"(input_address));
            color = *(u16 *)input_address;
            red = max_channel;
            asm volatile("" : "+r"(red));
            red &= color;
            color <<= 16;
            green = (color >> 21) & max_channel;
            var_r5 = (color >> 26) & max_channel;

            blend = (max_channel - red) * factor;
            if (blend < 0) {
                blend += 0x1F;
            }
            blend >>= 5;
            blend = red + blend;
            blend <<= 24;
            red = (u32)blend >> 24;

            blend = (max_channel - green) * factor;
            if (blend < 0) {
                blend += 0x1F;
            }
            blend >>= 5;
            blend = green + blend;
            blend <<= 24;
            green = (u32)blend >> 24;

            blend = (max_channel - var_r5) * factor;
            if (blend < 0) {
                blend += 0x1F;
            }
            blend >>= 5;
            blend = var_r5 + blend;
            blend <<= 24;

            asm volatile("" : "+r"(offset), "+r"(output_base));
            offset = (u32)((u8 *)output_base + offset);
            green <<= 5;
            red |= green;
            blend = (u32)blend >> 14;
            red |= blend;
            *(u16 *)offset = red;
        }
        {
            register u32 next_inner asm("r0") = inner + 1;
            asm volatile("" : "+r"(next_inner));
            next_inner <<= 24;
            inner = next_inner >> 24;
        }
        if (inner <= 0xF) {
            goto inner_palette;
        }
        func_08095208(0x020028A0, 0x05000200, 0x20);
        {
            register u32 restored_outer asm("r1") = next_outer;
            register u32 narrowed_outer asm("r0");
            asm volatile("" : "+r"(restored_outer));
            narrowed_outer = restored_outer << 24;
            var_r5 = narrowed_outer >> 24;
        }
        func_080ED17C(1);
        if (var_r5 <= 0x1F) {
            goto outer_palette;
        }
    }
    func_08092D8C(4, 0x080A6E15);
    {
        register s32 *load_flags asm("r1") = temp_r9;
        register u32 flags asm("r0");
        register s32 *store_flags asm("r1");
        asm volatile("" : "+r"(load_flags));
        flags = *load_flags;
        flags &= 0xFFFDFFFF;
        store_flags = temp_r9;
        asm volatile("" : "+r"(store_flags));
        *store_flags = flags;
    }
    func_08098BB4(0x08017BD3);
    func_0809A9C8(1, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x080182F9);
    func_0809A9C8(0x34, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018315);
    func_08094554(temp_r9);
    func_08098BB4(0x08017BE6);
    func_08096308(2, 0x10);
    goto test_ready_2;
wait_ready_2:
    func_080ED17C(1);
test_ready_2:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_2;
    }
    func_08092E0C(4);
    *(s32 *)0x02021690 = -1;
    func_080ED17C(1);
}
