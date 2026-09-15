#include "m2c_prelude.h"

struct ConfigA71E0 {
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

struct FrameA71E0 {
    void *sp14;
    void *sp18;
    s32 *sp1C;
    s32 sp20;
    s32 sp24;
    s32 *sp28;
};

extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;
extern s32 *D_02032E8C[];
extern struct ConfigA71E0 D_030033C4;

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
void *func_08094374(M2C_UNK, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(s32 *);                       /* extern */
M2C_UNK func_08094564(void *, s32);                 /* extern */
M2C_UNK func_08095208(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A4CC(s32, s32, s32, s32);          /* extern */
M2C_UNK func_0809A9C8(s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809AA64(s32, s32, s32, s32);          /* extern */
M2C_UNK func_080ECD28(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080A71E0(void) {
    struct FrameA71E0 frame;
    s32 *temp_r0;
    s32 *temp_r0_2;
    s32 *temp_r1;
    s32 *temp_r1_2;
    s32 *temp_r1_3;
    s32 *temp_r1_5;
    s32 *temp_r2_3;
    s32 temp_r1_4;
    s32 temp_r1_6;
    s32 temp_r1_7;
    s32 temp_r2_2;
    s32 temp_r2_4;
    s32 temp_r3;
    s32 temp_r3_3;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r6;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    s32 var_r0_8;
    register s32 var_r8 asm("r8");
    register s32 var_r8_2 asm("r8");
    u16 temp_r0_4;
    u16 temp_r0_7;
    u32 temp_r0_5;
    u32 temp_r0_8;
    register u32 var_r6 asm("r6");
    register u32 var_r6_2 asm("r6");
    register u32 var_r6_3 asm("r6");
    u8 var_r7;
    u8 var_r7_2;
    void *temp_r0_3;
    void *temp_r0_6;
    void *temp_r2;
    void *temp_r3_2;

    {
        register s32 zero_r4 asm("r4");
        register s32 zero_sl asm("sl");
        register void *tiles asm("r8");
        register void *layout asm("r9");
        register s32 **objects asm("r6");
        register u8 *states asm("r5");
        register s32 *object asm("r0");

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
            register struct ConfigA71E0 *config asm("r1");

            asm volatile("" : "+r"(color_mode));
            zero_r4 = 0;
            asm volatile("" : "+r"(zero_r4));
            value = 0x14;
            color_mode[1] = value;
            config = (struct ConfigA71E0 *)0x030033C4;
            asm volatile("" : "+r"(config));
            config->x = zero_r4;
            config->y = zero_r4;
            config->scale = 0x8000;
            zero_sl = 0;
            asm volatile("" : "+r"(zero_sl));
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
        tiles = (void *)0x0821024C;
        layout = (void *)0x08210258;
        asm volatile("" : "+r"(tiles), "+r"(layout));
        object = func_08094484(tiles, layout, 0, 0,
            zero_r4, zero_r4, zero_r4, 0x82C8, 0x080BAE19);
        objects = (s32 **)0x02032E8C;
        asm volatile("" : "+r"(objects));
        objects[0] = object;
        object[10] = 0xFFF80000;
        object[11] = zero_r4;
        object[12] = zero_r4;
        states = (u8 *)0x02032EEC;
        asm volatile("" : "+r"(states));
        states[0] = zero_sl;
        func_0809A4CC(0x87, 6, 0x40, 1);
        object = func_08094484(tiles, layout, 0, 0,
            zero_r4, 0x40, 1, 0x2C8, 0x080BADD5);
        objects[1] = object;
        object[10] = 0x10000;
        object[11] = zero_r4;
        object[12] = zero_r4;
        states[1] = zero_sl;
    }
    func_0809AA64(0x087AF9D4, 6, 0x80, 2);
    func_0809AA64(0x087AF9D4, 7, 0xC0, 3);
    func_08096308(1, 0x10);
    goto test_ready_1;
wait_ready_1:
    func_080ED17C(1);
test_ready_1:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_1;
    }
    D_0300004E = 0x740;
    D_03000050 = 0x810;
    if (M2C_FIELD(D_02032E8C[1], s32 *, 0x28) != 0) {
        do {
            temp_r1 = D_02032E8C[1];
            M2C_FIELD(temp_r1, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r1, s32 *, 0x28) + 0xFFFFF000);
            func_080ED17C(1);
        } while (M2C_FIELD(D_02032E8C[1], s32 *, 0x28) != 0);
    }
    frame.sp1C = func_08094484(0x08359850, 0x0835985C, 0, 8, 0x68, 0x3C2, 0xD, 8, 0);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(0x36, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018477);
    {
        register s32 *flags asm("r3") = frame.sp1C;
        asm volatile("" : "+r"(flags));
        *flags |= 0x20000;
    }
    func_08098BB4(0x08017BE6);
    {
        register s32 motion_zero asm("r0") = 0;
        asm volatile("" : "+r"(motion_zero));
        var_r8 = motion_zero;
    }
    {
        register s32 ramp_zero asm("r1") = 0;
        asm volatile("" : "+r"(ramp_zero));
        frame.sp20 = ramp_zero;
    }
    func_08092E84(0x68);
    {
    register s32 ramp_limit asm("r5") = -0x1000;
    register struct ConfigA71E0 *config asm("r4") = &D_030033C4;
    register s32 **ramp_objects asm("r6");

    asm volatile("" : "+r"(ramp_limit), "+r"(config));
    do {
        register s32 ramp_value asm("r2") = frame.sp20;

        asm volatile("" : "+r"(ramp_value));
        if (ramp_value > ramp_limit) {
            register s32 ramp_delta asm("r3") = -0x200;

            asm volatile("" : "+r"(ramp_delta));
            ramp_value += ramp_delta;
            frame.sp20 = ramp_value;
        }
        {
            register s32 motion_delta asm("r0") = -0x100;
            asm volatile("" : "+r"(motion_delta));
            var_r8 += motion_delta;
        }
        config->x += frame.sp20;
        {
            register s32 scale_value asm("r0") = config->scale;
            register s32 scale_delta asm("r2") = 0x100;

            asm volatile("" : "+r"(scale_value), "+r"(scale_delta));
            scale_value += scale_delta;
            config->scale = scale_value;
        }
        ramp_objects = D_02032E8C;
        asm volatile("" : "+r"(ramp_objects));
        temp_r1_2 = ramp_objects[1];
        M2C_FIELD(temp_r1_2, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r1_2, s32 *, 0x28) + var_r8);
        func_080ED17C(1);
    } while (var_r8 > ramp_limit);
    temp_r0_3 = func_08094374(0x087AFA94, 7, 0, 0, 0, 0xC0, 3, 0x7E0, 0x080BADD5);
    frame.sp14 = temp_r0_3;
    {
        register void *child_fields asm("r2") = temp_r0_3 + 0x28;
        register void *source_fields asm("r1") = ramp_objects[1];

        asm volatile("" : "+r"(temp_r0_3), "+r"(child_fields),
                     "+r"(source_fields));
        M2C_FIELD(child_fields, s32 *, 0) =
            M2C_FIELD(source_fields, s32 *, 0x28) + 0x8000;
        M2C_FIELD(child_fields, s32 *, 4) =
            M2C_FIELD(source_fields, s32 *, 0x2C);
        M2C_FIELD(child_fields, s32 *, 8) =
            M2C_FIELD(source_fields, s32 *, 0x30);
    }
    }
    frame.sp24 = -0x1000;
    func_080ECD28(0x05000220, 0x02002880, 8);
    var_r6 = 0;
    goto test_loop_35;
loop_35:
    {
        {
            register s32 *next_fade_target asm("r1") = frame.sp14 + 0x28;
            asm volatile("" : "+r"(next_fade_target));
            frame.sp28 = next_fade_target;
        }
        if (var_r6 <= 0x10U) {
            register u32 max_channel asm("r5");
            register u16 *output_base asm("sl");
            register u16 *output_copy asm("ip");
            register u32 next_outer asm("r9");
            u32 inner;

            inner = 0;
            {
                register u16 *output_seed asm("r2") = (u16 *)0x020028A0;
                asm volatile("" : "+r"(output_seed));
                output_base = output_seed;
                asm volatile("" : "+r"(output_base), "+r"(output_seed));
            }
            {
                register u32 next_seed asm("r3") = var_r6 + 1;
                asm volatile("" : "+r"(next_seed));
                next_outer = next_seed;
            }
            max_channel = 0x1F;
            asm volatile("" : "+r"(max_channel));
            output_copy = output_base;
            asm volatile("" : "+r"(output_copy));
first_inner_palette:
            {
                register u32 offset asm("r2") = inner << 1;
                register u16 *input_base asm("r1") = (u16 *)0x02002880;
                register u32 input_address asm("r0");
                register u32 color asm("r0");
                register u32 red asm("r3");
                register u32 green asm("r1");
                register u32 blue asm("r4");
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
                blue = (color >> 26) & max_channel;

                blend = (max_channel - red) * var_r6;
                if (blend < 0) {
                    blend += 0xF;
                }
                blend >>= 4;
                blend = red + blend;
                blend <<= 24;
                red = (u32)blend >> 24;

                blend = (max_channel - green) * var_r6;
                if (blend < 0) {
                    blend += 0xF;
                }
                blend >>= 4;
                blend = green + blend;
                blend <<= 24;
                green = (u32)blend >> 24;

                blend = (max_channel - blue) * var_r6;
                if (blend < 0) {
                    blend += 0xF;
                }
                blend >>= 4;
                blend = blue + blend;
                blend <<= 24;

                asm volatile("" : "+r"(offset), "+r"(output_copy));
                offset = (u32)((u8 *)output_copy + offset);
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
                goto first_inner_palette;
            }
            {
                register u16 *call_source asm("r0") = output_base;
                register u32 call_destination asm("r1") = 0x05000220;

                asm volatile("" : "+r"(call_source), "+r"(call_destination));
                func_08095208(call_source, call_destination, 0x20);
            }
            {
                register u32 restored_outer asm("r2") = next_outer;
                register u32 narrowed_outer asm("r0");
                asm volatile("" : "+r"(restored_outer));
                narrowed_outer = restored_outer << 24;
                var_r6 = narrowed_outer >> 24;
            }
        }
        {
        register void *flag_child asm("r1") = frame.sp14;

        asm volatile("" : "+r"(flag_child));
        if ((M2C_FIELD(flag_child, u16 *, 0x12) == 0) && (M2C_FIELD(flag_child, s32 *, 0) & 4)) {
            void *dismiss = *(void *volatile *)&frame.sp14;

            func_08094564(dismiss, 1);
            func_08094554(D_02032E8C[1]);
            {
                register s32 motion_reset asm("r3") = -0x1D00;
                asm volatile("" : "+r"(motion_reset));
                var_r8 = motion_reset;
            }
            func_08092E84(0x6B);
        }
        if (var_r8 < (s32)0xFFFFF000) {
            register s32 motion_step asm("r0") = 0x100;
            asm volatile("" : "+r"(motion_step));
            var_r8 += motion_step;
        }
        }
        D_030033C4.x += frame.sp20;
        {
        register void *motion_child asm("r3") = frame.sp14;
        asm volatile("" : "+r"(motion_child));
        if (M2C_FIELD(motion_child, u16 *, 0x12) == 0) {
            temp_r1_5 = D_02032E8C[1];
            M2C_FIELD(temp_r1_5, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r1_5, s32 *, 0x28) + var_r8);
        }
        D_030033C4.scale += 0x100;
        {
            register s32 *fade_target asm("r2") = frame.sp28;
            asm volatile("" : "+r"(fade_target));
            *fade_target += var_r8;
        }
        if (M2C_FIELD(motion_child, u16 *, 0x12) != 0) {
            register s32 fade_limit asm("r0") = (s32)0xFFFFE000;
            register s32 fade_value asm("r3") = frame.sp24;

            asm volatile("" : "+r"(fade_limit), "+r"(fade_value));
            if (fade_value > fade_limit) {
                fade_value -= 0x40;
                frame.sp24 = fade_value;
            }
        }
        }
        {
            register void *fade_child asm("r1") =
                *(void *volatile *)&frame.sp14;
            register s32 fade_round asm("r0") = frame.sp24;

            asm volatile("" : "+r"(fade_child), "+r"(fade_round));
            var_r0_4 = fade_round;
            if (var_r0_4 < 0) {
                var_r0_4 += 0xFF;
            }
            M2C_FIELD(fade_child, s16 *, 0xA) = (s16) (var_r0_4 >> 8);
        }
        func_080ED17C(1);
    }
test_loop_35:
    if (D_030033C4.scale <= 0xFFFF) {
        goto loop_35;
    }
    func_08094564(frame.sp14, 2);
    M2C_FIELD(frame.sp14, s32 *, 0) = (s32) (M2C_FIELD(frame.sp14, s32 *, 0) & ~0x30);
    temp_r0_6 = func_08094374(0x087AFA94, 6, 0, 0, 0, 0x80, 2, 0x7E0, 0x080A6DB1);
    frame.sp18 = temp_r0_6;
    {
        register void *child_fields asm("r3") = temp_r0_6 + 0x28;
        register void *source_fields asm("r2") = D_02032E8C[0];

        asm volatile("" : "+r"(temp_r0_6), "+r"(child_fields),
                     "+r"(source_fields));
        M2C_FIELD(child_fields, s32 *, 0) =
            M2C_FIELD(source_fields, s32 *, 0x28);
        M2C_FIELD(child_fields, s32 *, 4) =
            M2C_FIELD(source_fields, s32 *, 0x2C);
        M2C_FIELD(child_fields, s32 *, 8) =
            M2C_FIELD(source_fields, s32 *, 0x30);
        M2C_FIELD(temp_r0_6, s32 *, 0x34) = 0;
    }
    {
        register s32 motion_seed asm("r0") = 0xC00;
        asm volatile("" : "+r"(motion_seed));
        var_r8_2 = motion_seed;
    }
    func_080ECD28(0x05000200, 0x02002880, 8);
    var_r6_2 = 0;
    func_08092E84(0x54);
    do {
        {
        register s32 motion_test asm("r1") = var_r8_2;
        asm volatile("" : "+r"(motion_test));
        if (motion_test > 0) {
            register s32 motion_step asm("r2") = -0x80;
            asm volatile("" : "+r"(motion_step));
            var_r8_2 += motion_step;
        }
        }
        {
            register s32 *position asm("r0") = frame.sp18 + 0x28;
            asm volatile("" : "+r"(position));
            *position += var_r8_2;
        }
        temp_r1_6 = D_030033C4.x;
        var_r0_5 = 0xFFF80000 - temp_r1_6;
        if (var_r0_5 < 0) {
            var_r0_5 += 7;
        }
        D_030033C4.x = temp_r1_6 + (var_r0_5 >> 3);
        if (var_r6_2 <= 0x20U) {
            register u32 max_channel asm("r5");
            register u16 *output_base asm("sl");
            register u16 *output_copy asm("ip");
            register u32 next_outer asm("r9");
            u32 inner;

            inner = 0;
            {
                register u16 *output_seed asm("r3") = (u16 *)0x020028A0;
                asm volatile("" : "+r"(output_seed));
                output_base = output_seed;
                asm volatile("" : "+r"(output_base), "+r"(output_seed));
            }
            {
                register u32 next_seed asm("r0") = var_r6_2 + 1;
                asm volatile("" : "+r"(next_seed));
                next_outer = next_seed;
            }
            max_channel = 0x1F;
            asm volatile("" : "+r"(max_channel));
            var_r6_2 = max_channel - var_r6_2;
            output_copy = output_base;
            asm volatile("" : "+r"(output_copy));
second_inner_palette:
            {
                register u32 offset asm("r2") = inner << 1;
                register u16 *input_base asm("r1") = (u16 *)0x02002880;
                register u32 input_address asm("r0");
                register u32 color asm("r0");
                register u32 red asm("r3");
                register u32 green asm("r1");
                register u32 blue asm("r4");
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
                blue = (color >> 26) & max_channel;

                blend = (max_channel - red) * var_r6_2;
                if (blend < 0) {
                    blend += 0x1F;
                }
                blend >>= 5;
                blend = red + blend;
                blend <<= 24;
                red = (u32)blend >> 24;

                blend = (max_channel - green) * var_r6_2;
                if (blend < 0) {
                    blend += 0x1F;
                }
                blend >>= 5;
                blend = green + blend;
                blend <<= 24;
                green = (u32)blend >> 24;

                blend = (max_channel - blue) * var_r6_2;
                if (blend < 0) {
                    blend += 0x1F;
                }
                blend >>= 5;
                blend = blue + blend;
                blend <<= 24;

                asm volatile("" : "+r"(offset), "+r"(output_copy));
                offset = (u32)((u8 *)output_copy + offset);
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
                goto second_inner_palette;
            }
            {
                register u16 *call_source asm("r0") = output_base;
                register u32 call_destination asm("r1") = 0x05000200;

                asm volatile("" : "+r"(call_source), "+r"(call_destination));
                func_08095208(call_source, call_destination, 0x20);
            }
            {
                register u32 restored_outer asm("r2") = next_outer;
                register u32 narrowed_outer asm("r0");
                asm volatile("" : "+r"(restored_outer));
                narrowed_outer = restored_outer << 24;
                var_r6_2 = narrowed_outer >> 24;
            }
        }
        func_080ED17C(1);
    } while (var_r6_2 <= 0x1FU);
    {
        register s32 *flags asm("r3") = frame.sp1C;
        asm volatile("" : "+r"(flags));
        *flags &= 0xFFFDFFFF;
    }
    func_08098BB4(0x08017BD3);
    func_0809A9C8(0x17, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x0801850D);
    {
        register s32 *flag_load asm("r1") = frame.sp1C;
        register u32 flags asm("r0");

        asm volatile("" : "+r"(flag_load));
        flags = *flag_load;
        {
            register u32 flag_mask asm("r1") = 0x20000;
            asm volatile("" : "+r"(flag_mask));
            flags |= flag_mask;
        }
        {
            register s32 *flag_store asm("r2") =
                *(s32 *volatile *)&frame.sp1C;
            asm volatile("" : "+r"(flag_store));
            *flag_store = flags;
        }
    }
    func_08098BB4(0x08017BE6);
    func_08092D8C(4, 0x080A6E15);
    var_r6_3 = 0;
    do {
        register u32 next_delay asm("r0") = var_r6_3 + 1;
        asm volatile("" : "+r"(next_delay));
        next_delay <<= 24;
        var_r6_3 = next_delay >> 24;
        func_080ED17C(1);
    } while ((u32) var_r6_3 <= 0x3BU);
    {
        register s32 *flags asm("r3") = frame.sp1C;
        asm volatile("" : "+r"(flags));
        *flags &= 0xFFFDFFFF;
    }
    func_08098BB4(0x08017BD3);
    func_0809A9C8(0x16, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x0801854A);
    func_0809A9C8(0x1E, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018575);
    func_0809A9C8(0x39, 0, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x080185DE);
    func_0809A9C8(0x39, 2, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x08018737);
    func_0809A9C8(0x34, 2, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x080187CE);
    func_0809A9C8(0x34, 3, 0, 0x3C2, 0xD, 0x02002880);
    func_08098BB4(0x0801885A);
    func_08094554(frame.sp1C);
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
