#include "m2c_prelude.h"

extern volatile u16 D_0300004E;
extern volatile u16 D_03000050;
extern void *D_02032E8C[];

struct ConfigA9344 {
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

extern struct ConfigA9344 D_030033C4;

M2C_UNK func_08092D8C(s32, M2C_UNK);                /* extern */
M2C_UNK func_08092E0C(s32);                         /* extern */
M2C_UNK func_08092E84(s32);                         /* extern */
M2C_UNK func_08092EA0(s32);                         /* extern */
M2C_UNK func_08094330();                            /* extern */
void *func_08094374(M2C_UNK, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
void *func_08094484(M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_08094554(void *);                      /* extern */
M2C_UNK func_08094564(void *, s32);                 /* extern */
M2C_UNK func_08095208(M2C_UNK, M2C_UNK, s32);       /* extern */
M2C_UNK func_08096308(s32, s32);                    /* extern */
s32 func_0809669C();                                /* extern */
M2C_UNK func_08098BB4(M2C_UNK);                     /* extern */
M2C_UNK func_0809A4CC(s32, s32, s32, s32);          /* extern */
M2C_UNK func_0809A9C8(s32, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_0809AA64(s32, s32, s32, s32);          /* extern */
M2C_UNK func_080ECD28(s32 *, s32, s32);             /* extern */
M2C_UNK func_080ED17C(s32);                         /* extern */

void sub_080A9344(void) {
    s32 sp14;
    void *sp18;
    void *sp1C;
    s32 sp20;
    s32 sp24;
    s32 *sp28;
    s32 temp_r0_6;
    s32 temp_r1_6;
    s32 ramp_limit;
    s32 var_r0_6;
    s32 var_r0_7;
    register s32 var_r9 asm("r9");
    register u32 var_r5_2 asm("r5");
    register u32 var_r5_3 asm("r5");
    register u32 var_r7_2 asm("r7");
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r1_5;
    void *temp_r5;
    register s32 zero_r4 asm("r4");

    asm volatile("" : "=m"(sp14), "=m"(sp18), "=m"(sp1C),
                  "=m"(sp20), "=m"(sp24), "=m"(sp28));
    *(s32 *)0x02021690 = 9;
    *(s32 *)0x02030558 = 0xFF10;
    {
        register s8 *color_mode asm("r0") = (s8 *)0x0203055C;
        register struct ConfigA9344 *config asm("r1");

        zero_r4 = 0;
        asm volatile("" : "+r"(color_mode), "+r"(zero_r4));
        color_mode[1] = zero_r4;
        config = &D_030033C4;
        asm volatile("" : "+r"(config));
        config->x = zero_r4;
        config->y = zero_r4;
        config->scale = 0x8000;
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
    {
    register s32 menu asm("r7") = 0x087AF9D4;
    register void *template_a asm("r9");
    register void *template_b_r1 asm("r1");
    register void *template_b asm("r10");
    register void **sprite_slots asm("r6");
    register s32 scene_y asm("r8");
    asm volatile("" : "+r"(menu));
    func_0809AA64(menu, 0x13, 0, 0);
    template_a = (void *)0x0821024C;
    template_b_r1 = (void *)0x08210258;
    template_b = template_b_r1;
    asm volatile("" : "+r"(template_a), "+r"(template_b_r1), "+r"(template_b));
    temp_r0 = func_08094484(template_a, template_b_r1, 0, 0, zero_r4,
        zero_r4, zero_r4, ({
            register s32 scene_y_seed asm("r2") = 0x2C8;
            asm volatile("" : "+r"(scene_y_seed));
            scene_y = scene_y_seed;
            asm volatile("" : "+r"(scene_y), "+r"(scene_y_seed));
            scene_y_seed;
        }), 0x080BAE19);
    sprite_slots = D_02032E8C;
    asm volatile("" : "+r"(sprite_slots));
    sprite_slots[0] = temp_r0;
    M2C_FIELD(temp_r0, s32 *, 0x28) = 0xFFF80000;
    M2C_FIELD(temp_r0, s32 *, 0x2C) = zero_r4;
    M2C_FIELD(temp_r0, s32 *, 0x30) = zero_r4;
    {
        register u8 *state asm("r5") = (u8 *)0x02032EEC;

        asm volatile("" : "+r"(state));
        {
            register s32 zero asm("r3") = 0;
            asm volatile("" : "+r"(zero));
            state[0] = zero;
        }
        func_0809A4CC(0x74, 0, 0x40, 1);
        temp_r0_2 = func_08094484(template_a, template_b, 0, 0, zero_r4,
            0x40, 1, ({
                register s32 scene_y_copy asm("r0") = scene_y;
                asm volatile("" : "+r"(scene_y_copy));
                scene_y_copy;
            }), 0x080BADD5);
        sprite_slots[1] = temp_r0_2;
        M2C_FIELD(temp_r0_2, s32 *, 0x28) = 0x10000;
        M2C_FIELD(temp_r0_2, s32 *, 0x2C) = zero_r4;
        M2C_FIELD(temp_r0_2, s32 *, 0x30) = zero_r4;
        {
            register s32 zero asm("r1") = 0;
            asm volatile("" : "+r"(zero));
            state[1] = zero;
        }
    }
    func_0809AA64(menu, 7, 0x80, 2);
    }
    func_0809AA64(0x087AC9F8, 0x16, 0x100, 4);
    func_08096308(1, 0x10);
    goto test_ready_2;
wait_ready_2:
    func_080ED17C(1);
test_ready_2:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_2;
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
    {
    void *asset_a = (void *)0x08359850;
    void *asset_b = (void *)0x0835985C;
    register s32 scene_x asm("r6");

    asm volatile("" : "+r"(asset_a), "+r"(asset_b));
    temp_r5 = func_08094484(asset_a, asset_b, 0, 8, 0x68,
        ({ scene_x = 0x3C2; scene_x; }), 0xD, 8, 0);
    func_08098BB4(0x08017BD3);
    func_0809A9C8(1, 3, 0, scene_x, 0xD, 0x02002880);
    }
    func_08098BB4(0x08018AF8);
    func_08094554(temp_r5);
    func_08098BB4(0x08017BE6);
    var_r9 = 0;
    {
        register s32 ramp_zero asm("r0") = 0;

        asm volatile("" : "+r"(ramp_zero));
        sp20 = ramp_zero;
    }
    func_08092E84(0x68);
    ramp_limit = (s32)0xFFFFF000;
    asm volatile("" : : "r"(ramp_limit));
    do {
        {
        register s32 ramp_value asm("r1") = sp20;

        asm volatile("" : "+r"(ramp_value));
        if (ramp_value > ramp_limit) {
            register s32 ramp_delta asm("r2") = 0xFFFFFE00;

            asm volatile("" : "+r"(ramp_delta));
            ramp_value += ramp_delta;
            sp20 = ramp_value;
        }
        }
        {
            register s32 motion_delta asm("r3") = 0xFFFFFF00;

            asm volatile("" : "+r"(motion_delta));
            var_r9 += motion_delta;
        }
        D_030033C4.x += sp20;
        {
            register s32 scale_value asm("r0") = D_030033C4.scale;
            register s32 scale_delta asm("r2");

            asm volatile("" : "+r"(scale_value));
            scale_delta = 0x100;
            asm volatile("" : "+r"(scale_delta));
            scale_value += scale_delta;
            D_030033C4.scale = scale_value;
        }
        temp_r1_2 = D_02032E8C[1];
        M2C_FIELD(temp_r1_2, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r1_2, s32 *, 0x28) + var_r9);
        func_080ED17C(1);
    } while (var_r9 > ramp_limit);
    temp_r0_3 = func_08094374(0x087AFA94, 7, 0, 0, 0, 0x80, 2, 0x7E0, 0x080BADD5);
    sp18 = temp_r0_3;
    {
        register void *child_fields asm("r2") = temp_r0_3 + 0x28;
        register void *source_fields asm("r1") = D_02032E8C[1];

        asm volatile("" : "+r"(temp_r0_3), "+r"(child_fields),
                     "+r"(source_fields));
        M2C_FIELD(child_fields, s32 *, 0) =
            M2C_FIELD(source_fields, s32 *, 0x28) + 0x8000;
        M2C_FIELD(child_fields, s32 *, 4) =
            M2C_FIELD(source_fields, s32 *, 0x2C);
        M2C_FIELD(child_fields, s32 *, 8) =
            M2C_FIELD(source_fields, s32 *, 0x30);
    }
    sp24 = -0x1000;
    func_080ECD28((s32 *)0x05000220, 0x02002880, 8);
    {
    u32 outer = 0;
    register u16 *output_base asm("r8");
    register u32 next_outer asm("r10");
    register u32 max_channel asm("r6");
    goto test_loop_40;
loop_40:
    {
        {
            register s32 *next_fade_target asm("r1") = sp18 + 0x28;

            asm volatile("" : "+r"(next_fade_target));
            sp28 = next_fade_target;
        }
        if (outer <= 0x10U) {
            register u32 inner asm("r5") = 0;
            register u16 *output_copy asm("ip");
            register u32 output_guard0 asm("r0");
            register u32 output_guard1 asm("r1");

            asm volatile("" : "=r"(output_guard0), "=r"(output_guard1));
            output_base = (u16 *)0x020028A0;
            asm volatile("" : "+r"(output_base)
                         : "r"(output_guard0), "r"(output_guard1));
            next_outer = outer + 1;
            max_channel = 0x1F;
            output_copy = output_base;
            asm volatile("" : "+r"(output_copy));
            do {
                register u32 offset asm("r2") = inner << 1;
                register u16 *input_base asm("r1") = (u16 *)0x02002880;
                register u32 input_address asm("r0");
                register u32 color asm("r0");
                register u32 red asm("r3");
                register u32 green asm("r1");
                register u32 blue asm("r4");
                s32 blend;

                asm volatile("" : "+r"(offset), "+r"(input_base));
                input_address = offset + (u32)input_base;
                asm volatile("" : "+r"(input_address));
                color = *(u16 *)input_address;
                red = max_channel;
                red &= color;
                color <<= 16;
                green = (color >> 21) & max_channel;
                blue = (color >> 26) & max_channel;
                blend = (max_channel - red) * outer;
                if (blend < 0) {
                    blend += 0xF;
                }
                blend >>= 4;
                asm volatile("add %0, %1, %0"
                             : "+r"(blend) : "r"(red));
                blend <<= 24;
                red = (u32)blend >> 24;
                blend = (max_channel - green) * outer;
                if (blend < 0) {
                    blend += 0xF;
                }
                blend >>= 4;
                asm volatile("add %0, %1, %0"
                             : "+r"(blend) : "r"(green));
                blend <<= 24;
                green = (u32)blend >> 24;
                blend = (max_channel - blue) * outer;
                if (blend < 0) {
                    blend += 0xF;
                }
                blend >>= 4;
                asm volatile("add %0, %1, %0"
                             : "+r"(blend) : "r"(blue));
                blend <<= 24;
                asm volatile("" : "+r"(offset), "+r"(output_copy));
                offset = (u32)((u8 *)output_copy + offset);
                green <<= 5;
                red |= green;
                blend = (u32)blend >> 14;
                red |= blend;
                *(u16 *)offset = red;
                {
                    register u32 next_inner asm("r0") = inner + 1;

                    asm volatile("" : "+r"(next_inner));
                    next_inner <<= 24;
                    inner = next_inner >> 24;
                }
            } while (inner <= 0xFU);
            {
                register u16 *call_source asm("r0") = output_base;
                register u32 call_destination asm("r1");

                asm volatile("" : "+r"(call_source));
                call_destination = 0x05000220;
                asm volatile("" : "+r"(call_destination));
                func_08095208(call_source, call_destination, 0x20);
            }
            {
                register u32 restored_outer asm("r2") = next_outer;
                register u32 narrowed_outer asm("r0");

                asm volatile("" : "+r"(restored_outer));
                narrowed_outer = restored_outer << 24;
                outer = narrowed_outer >> 24;
            }
        }
        if ((M2C_FIELD(sp18, u16 *, 0x12) == 0) && (M2C_FIELD(sp18, s32 *, 0) & 4)) {
            void *dismiss = *(void *volatile *)&sp18;

            func_08094564(dismiss, 1);
            func_08094554(D_02032E8C[1]);
            {
                register s32 motion_reset asm("r3") = -0x1D00;

                asm volatile("" : "+r"(motion_reset));
                var_r9 = motion_reset;
            }
            func_08092E84(0x6B);
        }
        if (var_r9 < (s32)0xFFFFF000) {
            register s32 motion_step asm("r0") = 0x100;

            asm volatile("" : "+r"(motion_step));
            var_r9 += motion_step;
        }
        {
            register struct ConfigA9344 *motion_config asm("r0") =
                &D_030033C4;
            register s32 motion_x asm("r2");
            register s32 motion_limit asm("r1");
            register struct ConfigA9344 *motion_store asm("r3");
            register s32 next_x asm("r0");

            asm volatile("" : "+r"(motion_config));
            motion_x = motion_config->x;
            asm volatile("" : "+r"(motion_x));
            motion_limit = (s32)0xFFF8E000;
            asm volatile("" : "+r"(motion_limit));
            motion_store = motion_config;
            asm volatile("" : "+r"(motion_store));
            if (motion_x > motion_limit) {
                register s32 ramp asm("r1") = sp20;

                asm volatile("" : "+r"(ramp));
                next_x = motion_x + ramp;
            } else {
                next_x = 0xFFF86000 - motion_x;
                if (next_x < 0) {
                    next_x += 7;
                }
                next_x >>= 3;
                next_x = motion_x + next_x;
            }
            motion_store->x = next_x;
            {
            register void *flag_child asm("r2") = sp18;

            asm volatile("" : "+r"(flag_child));
            if (M2C_FIELD(flag_child, u16 *, 0x12) == 0) {
                temp_r1_5 = D_02032E8C[1];
                M2C_FIELD(temp_r1_5, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r1_5, s32 *, 0x28) + var_r9);
            }
            motion_store->scale += 0x100;
            {
            register s32 *fade_target asm("r3") = sp28;

            asm volatile("" : "+r"(fade_target));
            *fade_target += var_r9;
            }
        if (M2C_FIELD(flag_child, u16 *, 0x12) != 0) {
            register s32 fade_limit asm("r0") = (s32)0xFFFFE000;
            register s32 fade_value asm("r1") = sp24;

            asm volatile("" : "+r"(fade_limit), "+r"(fade_value));
            if (fade_value > fade_limit) {
                fade_value -= 0x40;
                sp24 = fade_value;
            }
        }
        {
            register void *fade_child asm("r1") =
                *(void *volatile *)&sp18;
            register s32 fade_round asm("r0") = sp24;

            asm volatile("" : "+r"(fade_child), "+r"(fade_round));
            var_r0_6 = fade_round;
            if (var_r0_6 < 0) {
                var_r0_6 += 0xFF;
            }
            M2C_FIELD(fade_child, s16 *, 0xA) =
                (s16) (var_r0_6 >> 8);
            }
            }
        }
        func_080ED17C(1);
    }
test_loop_40:
    {
        register struct ConfigA9344 *loop_config asm("r0") = &D_030033C4;
        register s32 loop_scale asm("r1");

        asm volatile("" : "+r"(loop_config));
        loop_scale = loop_config->scale;
        if (loop_scale <= 0xFFFF) {
            goto loop_40;
        }
    }
    }
    func_08094564(sp18, 2);
    M2C_FIELD(sp18, s32 *, 0) = (s32) (M2C_FIELD(sp18, s32 *, 0) & ~0x30);
    sp1C = func_08094374(0x087ACDD8, 0x16, 0, 0, 0x38, 0x100, 4, 0x85C0, 0);
    var_r7_2 = 0;
    func_08092E84(0x72);
    do {
        temp_r1_6 = D_030033C4.x;
        var_r0_7 = 0xFFF86000 - temp_r1_6;
        if (var_r0_7 < 0) {
            var_r0_7 += 7;
        }
        temp_r0_6 = temp_r1_6 + (var_r0_7 >> 3);
        D_030033C4.x = temp_r0_6;
        {
            register void *position_child asm("r1");
            register s32 position_delta asm("r0");

            position_child = sp1C;
            asm volatile("" : "+r"(position_child));
            position_delta = 0xFFF86000 - temp_r0_6;
            asm volatile("" : "+r"(position_delta));
            if (position_delta < 0) {
                position_delta += 0x1FF;
            }
            position_delta >>= 9;
            position_delta += 0x68;
            M2C_FIELD(position_child, s16 *, 4) = (s16)position_delta;
        }
        {
            register u32 next_position_frame asm("r0") = var_r7_2 + 1;

            asm volatile("" : "+r"(next_position_frame));
            next_position_frame <<= 24;
            var_r7_2 = next_position_frame >> 24;
        }
        func_080ED17C(1);
    } while ((u32) var_r7_2 <= 0x1FU);
    func_08092D8C(5, 0x0809FF55);
    func_08092E84(0x85);
    func_08092E84(0x4A);
    var_r5_2 = 0;
    do {
        register u32 next_delay_frame asm("r0");

        func_080ED17C(1);
        next_delay_frame = var_r5_2 + 1;
        asm volatile("" : "+r"(next_delay_frame));
        next_delay_frame <<= 24;
        var_r5_2 = next_delay_frame >> 24;
    } while ((u32) var_r5_2 <= 0x3BU);
    func_08096308(4, 0x78);
    goto test_ready_53;
wait_ready_53:
    func_080ED17C(1);
test_ready_53:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_53;
    }
    func_08092E0C(5);
    func_08094330();
    sp14 = 0;
    func_080ECD28(&sp14, 0x06000000, 0x01004000);
    *(s16 *)0x05000000 = 0x7FFF;
    var_r5_3 = 0;
    do {
        register u32 next_clear_frame asm("r0");

        func_080ED17C(1);
        next_clear_frame = var_r5_3 + 1;
        asm volatile("" : "+r"(next_clear_frame));
        next_clear_frame <<= 24;
        var_r5_3 = next_clear_frame >> 24;
    } while ((u32) var_r5_3 <= 0x77U);
    func_08096308(2, 0x78);
    goto test_ready_58;
wait_ready_58:
    func_080ED17C(1);
test_ready_58:
    if ((func_0809669C() << 0x18) == 0) {
        goto wait_ready_58;
    }
    func_08092EA0(0x4A);
    *(s32 *)0x02021690 = -1;
    func_080ED17C(1);
}
