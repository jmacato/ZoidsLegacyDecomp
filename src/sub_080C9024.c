#include "m2c_prelude.h"

struct ObjectC9024 {
    u8 pad0[0xA4];
    s32 fieldA4;
    s32 fieldA8;
};

struct SpriteC9024 {
    s32 flags;
    s16 x;
    u16 y;
    u16 field8;
    u16 fieldA;
    s16 scale;
};

extern s32 *D_02032E8C[][6];

s32 func_08093E30(s32 *, s16 *, s8 *);
struct SpriteC9024 *func_08094374(u32, u32, u32, u32, u32, u32, u32, u32,
    u32);

struct SpriteC9024 *sub_080C9024(struct ObjectC9024 *arg0, s32 arg1,
    s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7)
{
    register struct ObjectC9024 *object asm("ip") = arg0;
    register s32 type asm("r5");
    register u32 field12 asm("sl");
    register u32 x_offset asm("r9");
    register u32 stack_value asm("r0") = arg4;
    register u32 variant asm("r4") = arg5;
    register s32 *descriptor asm("r8");
    register u32 frame_offset asm("r6");
    s32 *side;
    register struct SpriteC9024 *sprite asm("r4");
    struct {
        s8 visible;
        u8 pad[3];
        volatile s32 saved_y;
    } locals;

    arg1 <<= 16;
    type = (u32)arg1 >> 16;
    arg2 <<= 16;
    arg2 = (u32)arg2 >> 16;
    field12 = arg2;
    arg3 <<= 16;
    arg3 = (u32)arg3 >> 16;
    x_offset = arg3;
    stack_value <<= 16;
    stack_value >>= 16;
    locals.saved_y = stack_value;
    variant <<= 24;
    variant >>= 24;

    descriptor = D_02032E8C[object->fieldA4][object->fieldA8];

    if ((u32)type <= 2) {
        frame_offset = 0;
    } else {
        switch (type) {
        case 3:
            frame_offset = 0;
            break;
        case 4:
            frame_offset = 0x20;
            break;
        case 5:
            frame_offset = 0x38;
            break;
        case 6:
            frame_offset = 0x58;
            break;
        }
    }

    {
        register u32 data asm("r3") = 0x087AD1D0;
        register s32 side_value asm("r2");
        register u32 frame_value asm("r1");
        register s32 *side_input asm("r0");
        u32 frame_arg;

        asm volatile("" : "+r"(data));
        sprite = func_08094374(data, type, field12, 0, 0,
            ({
                frame_value = frame_offset;
                side_input = &object->fieldA4;
                side_value = *side_input;
                side = side_input;
                if (side_value == 0) {
                    register u32 adjustment asm("r0") = 0xC0;

                    adjustment <<= 1;
                    frame_value = frame_offset + adjustment;
                }
                {
                    register u32 narrowed asm("r0") = frame_value << 16;

                    frame_arg = narrowed >> 16;
                }
                frame_arg;
            }),
            (variant <= 5 && side_value != 0) ?
                ({ asm volatile("" : "+r"(variant)); variant; }) :
                ({
                    register u32 fallback asm("r0") = variant + 6;

                    asm volatile("" : "+r"(fallback));
                    fallback;
                }),
            ({
                register s32 *descriptor_view asm("r2") = descriptor;
                register s32 call_flags asm("r1");

                asm volatile("" : "+r"(descriptor_view));
                call_flags = *descriptor_view;
                call_flags &= 0xC0;
                asm volatile("" : "+r"(call_flags));
                call_flags |= arg6;

                if (*side != 0) call_flags |= 0x8000;
                call_flags;
            }), 0);
    }
    sprite->scale = func_08093E30(descriptor + 10, &sprite->x,
        &locals.visible);

    {
        register s32 scale asm("r3");
        register s32 current_x asm("r1");
        register s32 phase asm("r2");
        s32 offset;
        s32 product;

        asm volatile("" : "=r"(current_x));
        asm volatile("" : "=r"(phase));
        {
            register u32 field asm("r0") = 12;

            scale = *(s16 *)((u8 *)sprite + field);
        }
        asm volatile("" : : "r"(current_x));
        asm volatile("" : : "r"(phase));
        {
            register u32 field asm("r2") = 4;

            current_x = *(s16 *)((u8 *)sprite + field);
        }

        if (*side == 0) {
            register u32 input asm("r2") = x_offset;

            offset = input << 16;
            offset >>= 16;
        } else {
            register u32 input asm("r2") = x_offset;

            offset = input << 16;
            offset >>= 16;
            offset = -offset;
        }
        product = offset * scale;
        if (product < 0) {
            product += 0xFF;
        }
        {
            register s32 adjusted_x asm("r0") =
                current_x + (product >> 8);

            asm volatile("" : "+r"(adjusted_x));
            sprite->x = adjusted_x;
        }
    }

    {
        register s32 saved asm("r1") = locals.saved_y;
        register s32 product asm("r0");

        product = saved << 16;
        product >>= 16;
        {
            register u32 field asm("r2") = 12;
            register s32 scale asm("r1") =
                *(s16 *)((u8 *)sprite + field);

            product *= scale;
        }

        if (product < 0) {
            product += 0xFF;
        }
        sprite->y = sprite->y + (product >> 8);
    }
    asm volatile("" : : "r"(frame_offset));
    return sprite;
}
