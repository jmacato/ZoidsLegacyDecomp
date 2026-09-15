#include "m2c_prelude.h"

extern void func_08092E84(s32);
extern s32 func_08094484(const void *, const void *, s32, u32, u32, s32,
    s32, s32, s32);
extern void func_08094554(s32);
extern void func_08094564(void *, s32);
extern void func_0809F850(void);
extern void func_0809F8A0(u8);
extern void func_0809F94C(s32, u32, s32, u32, u32, s32);
extern void func_0809FB78(u8);
extern void func_080A016C(s32, s32, s32);
extern void func_080A6148(void);
extern void func_080ED17C(s32);

struct EventData {
    u8 pad_0;
    u8 type;
    u8 x;
    u8 y;
};

struct EventContext {
    struct EventData *data;
};

struct DisplayObject {
    u32 flags;
    u8 pad_4[6];
    s16 position;
};

struct DisplayState {
    struct DisplayObject *primary;
    struct DisplayObject *secondary;
};

struct PaletteOffsets {
    u32 pad_0;
    s32 value_4;
    u32 pad_8;
    s32 value_12;
    u32 pad_16;
    s32 value_20;
    u32 pad_24;
    s32 value_28;
};

s32 sub_080A61B0(u8 argument, struct EventContext *context)
{
    volatile u8 *scene;
    struct EventData *data;
    register s32 x_fixed asm("r8");
    register s32 y_fixed asm("r9");
    register s32 carrier_r5 asm("r5");
    register s32 carrier_r6 asm("r6");
    s32 carrier_r7;
    register s32 carrier_r4 asm("r4");
    register struct DisplayState *display asm("r10");
    volatile u8 frame_padding[16];
    volatile s32 saved_argument = argument;

    scene = (volatile u8 *)0x0202ECF4;

    scene[30] = context->data->type + 1;
    scene[31] = context->data->x;
    {
        u8 scene_y = context->data->y;

        scene += 32;
        *scene = scene_y;
    }
    if (*(u8 *)0x020316F4 == 0) {
        *(u8 *)0x02030664 = 1;
        func_0809F8A0(4);
        func_0809F8A0(context->data->type + 12);

        data = context->data;
        x_fixed = data->x << 12;
        y_fixed = data->y << 12;
        carrier_r5 = -0x6400;
        carrier_r6 = 0;
        {
            register u32 raw_type asm("r0") = data->type + 12;
            register u32 type_argument asm("r1");
            register s32 x_source asm("r3");

            type_argument = (u8)raw_type;
            x_source = x_fixed;
            asm volatile("" : "+r"(x_source));
            carrier_r7 = (u32)x_source >> 8;
            carrier_r4 = y_fixed;
            asm volatile("" : "+r"(carrier_r4));
            carrier_r4 = (u32)carrier_r4 >> 8;
            func_0809F94C(0, type_argument, 0, carrier_r7, carrier_r4, 1);
        }
        carrier_r7 = func_08094484((const void *)0x0832BB9C,
            (const void *)0x0832BBA8, 0, carrier_r7, carrier_r4, 0x3B2, 15,
            0x11C8, carrier_r6);
        {
            register s32 limit_copy asm("r0") = -0x800;

            carrier_r4 = limit_copy;

            do {
                register struct DisplayState *display_copy asm("r0");
                register struct DisplayObject *primary asm("r1");

                carrier_r6 += 0x40;
                carrier_r5 += carrier_r6;
                if (carrier_r5 > carrier_r4) {
                    carrier_r5 = limit_copy;
                }
                display_copy = (struct DisplayState *)0x02031940;
                display = display_copy;
                primary = display->primary;
                {
                    register s32 rounded_position asm("r0") = carrier_r5;

                    if (carrier_r5 < 0) {
                        rounded_position += 0xFF;
                    }
                    primary->position = rounded_position >> 8;
                }
                func_080ED17C(1);
                limit_copy = carrier_r4;
            } while (carrier_r5 < carrier_r4);
        }

        {
            register struct DisplayState *display_copy asm("r1") = display;

            func_08094564(display_copy->primary, 3);
        }
        func_08094554(carrier_r7);

        {
            register s32 x_source asm("r3") = x_fixed;
            register s32 y_source asm("r0");
            register s32 first_x asm("r3");

            asm volatile("" : "+r"(x_source));
            carrier_r5 = x_source >> 8;
            first_x = carrier_r5;
            first_x -= 12;
            y_source = y_fixed;
            asm volatile("" : "+r"(y_source));
            y_source >>= 8;
            asm volatile("" : "+r"(y_source));
            carrier_r6 = y_source;
            func_0809F94C(1, 4, 0, first_x, carrier_r6, ({
                carrier_r7 = 0;
                carrier_r7;
            }));
        }
        {
            register s32 second_x asm("r3") = carrier_r5 - 4;

            carrier_r4 = carrier_r6 + 4;
            func_0809F94C(2, 4, 0, second_x, carrier_r4, carrier_r7);
        }
        func_0809F94C(3, 4, 0, carrier_r5 + 4, carrier_r4, carrier_r7);
        func_0809F94C(4, 4, 0, carrier_r5 + 12, carrier_r6,
            carrier_r7);
        func_08092E84(124);

        carrier_r6 = 0;
        {
            register struct DisplayState *display_check asm("r1") = display;

            if ((display_check->secondary->flags & 1) != 0) {
            register struct PaletteOffsets *palette asm("r4") =
                (struct PaletteOffsets *)0x03000054;

            do {
                if (carrier_r6 <= 8) {
                    register volatile s32 *amount_base asm("r0") =
                        (volatile s32 *)0x087A18E8;
                    register u32 amount asm("r2");

                    asm volatile("" : "+r"(amount_base));
                    amount = carrier_r6 << 2;
                    amount += (u32)amount_base;
                    palette->value_4 += *(volatile s32 *)amount;
                    palette->value_12 += *(volatile s32 *)amount;
                    palette->value_20 += *(volatile s32 *)amount;
                    palette->value_28 += *(volatile s32 *)amount;
                    carrier_r6++;
                }
                func_080ED17C(1);
            } while ((((struct DisplayState *)0x02031940)->secondary->flags &
                1) != 0);
            }
        }

        {
            register struct DisplayState *display_base asm("r4") =
                (struct DisplayState *)0x02031940;
            register struct DisplayObject *primary asm("r0");
            register u32 flags asm("r1");
            register u32 flag_mask asm("r2");

            primary = display_base->primary;
            flags = primary->flags;
            flag_mask = ~0x30;
            flags &= flag_mask;
            flag_mask = 0x10;
            flags |= flag_mask;
            primary->flags = flags;
            func_08094564(primary, 1);
            func_08092E84(79);
            if ((display_base->primary->flags & 4) == 0) {
                register struct DisplayState *poll_base asm("r5") =
                    display_base;
                register u32 mask asm("r4") = 4;

                do {
                    func_080ED17C(1);
                } while ((poll_base->primary->flags & mask) == 0);
            }
        }

        {
            u8 cleanup_index = 0;

            do {
                func_0809FB78(cleanup_index);
                cleanup_index++;
            } while ((u32)cleanup_index <= 15);
        }
        func_0809F850();
        func_080A6148();
    }

    {
        register s32 second_argument asm("r1") = -1;
        register s32 first_argument asm("r0");

        first_argument = saved_argument;
        func_080A016C(first_argument, second_argument, 0);
    }
    return 0;
}
