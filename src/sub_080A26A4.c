#include "m2c_prelude.h"

struct InputRecord {
    u8 pad0;
    u8 type;
    u8 value;
    u8 index;
    u8 x_low;
    u8 x_high;
    u8 y_low;
    u8 y_high;
    u8 elevated;
};

struct Object {
    u8 pad00[0x28];
    s32 x;
    s32 velocity_y;
    s32 y;
};

u8 func_080ECF00(u8, s32);
s32 func_080ECF78(u8, s32);
void func_0809A4CC(u8, u8, s32, u8);
struct Object *func_08094484(s32, s32, s32, s32);
void func_080A016C(s32, s32, s32);

s32 sub_080A26A4(s32 arg0, struct InputRecord **arg1) {
    register struct InputRecord **source_slot asm("r9");
    register s32 r4_web asm("r4");
    struct InputRecord *input;
    register u32 group asm("r6");
    register u32 slot asm("r8");
    struct Object *object;
    volatile s32 reserve0;
    volatile s32 reserve1;
    volatile s32 reserve2;
    volatile s32 reserve3;
    volatile s32 reserve4;
    volatile s32 saved_arg0;

    asm volatile("" : "=m"(reserve0),
                       "=m"(reserve1),
                       "=m"(reserve2),
                       "=m"(reserve3),
                       "=m"(reserve4));
    source_slot = arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    r4_web = (s32)*arg1;
    input = (struct InputRecord *)r4_web;
    {
        register u32 index asm("r5");
        register u32 result asm("r0");

        index = input->index;
        result = func_080ECF00(index, 6);
        result <<= 24;
        group = result >> 24;
        result = func_080ECF78(index, 6);
        result <<= 24;
        result >>= 24;
        slot = result;
        func_0809A4CC(input->type, input->value, index << 6, index);
    }

    {
        register u8 *metadata_base asm("r2");
        register s32 type asm("r1");
        register s32 metadata_offset asm("r0");
        register s32 metadata asm("r0");
        s32 asset_a;
        register s32 asset_b asm("r10");
        s32 callback;
        register struct InputRecord *call_input asm("r5");
        register volatile s32 *outgoing asm("sp");

        metadata_base = (u8 *)0x087AFCC4;
        asm volatile("" : "+r"(metadata_base));
        call_input = *source_slot;
        type = call_input->type;
        metadata_offset = type << 3;
        metadata_offset -= type;
        metadata_offset <<= 3;
        metadata_offset += (s32)metadata_base;
        metadata = *(u8 *)(metadata_offset + 2);

        if (metadata == 4) {
            register s32 asset_b_init asm("r1");

            asset_a = 0x0821024C;
            asset_b_init = 0x08210258;
            asm volatile("" : "+r"(asset_b_init));
            asset_b = asset_b_init;
            outgoing[0] = 0;
            outgoing[1] = call_input->index << 6;
            outgoing[2] = call_input->index;
            r4_web = 3;
            r4_web -= func_080ECF78(slot, 3);
            r4_web <<= 6;
            r4_web |= 0x00080308;
            if (call_input->elevated != 0) {
                r4_web |= 0x00008000;
            }
            outgoing[3] = r4_web;
            callback = 0x080BAE19;
        } else {
            register s32 asset_b_init asm("r2");

            asset_a = 0x0821024C;
            asset_b_init = 0x08210258;
            asm volatile("" : "+r"(asset_b_init));
            asset_b = asset_b_init;
            outgoing[0] = 0;
            outgoing[1] = call_input->index << 6;
            outgoing[2] = call_input->index;
            r4_web = 3;
            r4_web -= func_080ECF78(slot, 3);
            r4_web <<= 6;
            r4_web |= 0x00000308;
            if (call_input->elevated != 0) {
                r4_web |= 0x00008000;
            }
            outgoing[3] = r4_web;
            callback = 0x080BADD5;
        }
        outgoing[4] = callback;
        object = func_08094484(asset_a,
                               asset_b,
                               0,
                               0);
    }

    {
        struct Object **object_base;
        register u32 slot_copy asm("r1");
        register s32 slot_offset asm("r2");
        register s32 group_double asm("r3");
        register s32 object_offset asm("r1");
        register struct Object **object_slot asm("r1");
        register s32 retained_slot_offset asm("r7");
        register s32 retained_group_double asm("r5");

        r4_web = 0x02032E8C;
        asm volatile("" : "+r"(r4_web));
        object_base = (struct Object **)r4_web;
        slot_copy = slot;
        slot_offset = slot_copy << 2;
        group_double = group << 1;
        object_offset = group_double + group;
        object_offset <<= 3;
        object_offset = slot_offset + object_offset;
        object_slot = (struct Object **)(object_offset + (s32)object_base);
        *object_slot = object;
        retained_slot_offset = slot_offset;
        retained_group_double = group_double;
        asm volatile("" : "+r"(retained_slot_offset),
                             "+r"(retained_group_double));

        {
            register struct InputRecord *fresh_input asm("r2");
            register s32 high asm("r1");
            register s32 mask asm("r0");
            struct InputRecord *retained_input;
            register s32 r3_web asm("r3");
            register struct Object *x_object asm("r2");
            s32 coordinate;

            fresh_input = *source_slot;
            high = fresh_input->x_high;
            mask = 0x80;
            mask &= high;
            r4_web = (s32)fresh_input;
            retained_input = (struct InputRecord *)r4_web;
            if (mask == 0) {
                register s32 offset asm("r0");
                register struct Object **address asm("r0");
                register s32 upper asm("r0");
                register s32 lower asm("r1");

                r3_web = 0x02032E8C;
                offset = retained_group_double + group;
                offset <<= 3;
                offset = retained_slot_offset + offset;
                address = (struct Object **)(offset + r3_web);
                x_object = *address;
                asm volatile("" : : : "memory");
                upper = retained_input->x_high;
                upper <<= 8;
                lower = retained_input->x_low;
                coordinate = upper + lower;
            } else {
                register s32 offset asm("r0");
                register struct Object **address asm("r0");
                register s32 upper asm("r0");
                register s32 lower asm("r1");

                r3_web = 0x02032E8C;
                offset = retained_group_double + group;
                offset <<= 3;
                offset = retained_slot_offset + offset;
                address = (struct Object **)(offset + r3_web);
                x_object = *address;
                asm volatile("" : : : "memory");
                upper = retained_input->x_high;
                upper <<= 8;
                asm volatile("" : "+r"(upper));
                lower = retained_input->x_low;
                upper += lower;
                lower = -0x10000;
                coordinate = upper + lower;
            }
            x_object->x = coordinate << 8;
            asm volatile("" : "+r"(group) : "m"(x_object->x) : "memory");

            {
                register s32 offset asm("r0");
                register struct Object **address asm("r0");

                offset = retained_group_double + group;
                offset <<= 3;
                offset = retained_slot_offset + offset;
                address = (struct Object **)(offset + r3_web);
                r3_web = (s32)*address;
            }
            asm volatile("" : "+r"(retained_group_double));
            ((struct Object *)r3_web)->velocity_y = 0;

            {
                register s32 high asm("r1");
                register s32 mask asm("r0");
                s32 coordinate;

                high = retained_input->y_high;
                mask = 0x80;
                mask &= high;
                if (mask == 0) {
                    register s32 upper asm("r0");
                    register s32 lower asm("r1");

                    asm volatile("" : : : "memory");
                    upper = retained_input->y_high;
                    upper <<= 8;
                    lower = retained_input->y_low;
                    coordinate = upper + lower;
                    asm volatile("" : "+r"(coordinate));
                } else {
                    register s32 upper asm("r0");
                    register s32 lower asm("r1");
                    register s32 sign asm("r2");

                    asm volatile("" : : : "memory");
                    upper = retained_input->y_high;
                    upper <<= 8;
                    asm volatile("" : "+r"(upper));
                    lower = retained_input->y_low;
                    upper += lower;
                    sign = -0x10000;
                    asm volatile("" : "+r"(sign));
                    coordinate = upper + sign;
                }
                ((struct Object *)r3_web)->y = coordinate << 8;
            }
            asm volatile("" : "+r"(retained_group_double));
        }

        {
            register u8 *marker_base asm("r1");
            register s32 marker_offset asm("r0");
            register s32 zero asm("r3");

            marker_base = (u8 *)0x02032EEC;
            asm volatile("" : "+r"(marker_base));
            marker_offset = retained_group_double + group;
            marker_offset <<= 1;
            marker_offset += slot;
            marker_offset += (s32)marker_base;
            zero = 0;
            *(u8 *)marker_offset = zero;

            {
                register u8 *grid_base asm("r2");
                register u32 slot_copy asm("r0");
                register s32 column_offset asm("r1");
                register s32 row_offset asm("r0");
                register u8 *grid_address asm("r1");
                register struct InputRecord **slot_address asm("r2");
                register struct InputRecord *current_input asm("r0");
                register s32 value asm("r0");

                grid_base = (u8 *)0x02034B4C;
                asm volatile("" : "+r"(grid_base));
                slot_copy = slot;
                column_offset = retained_slot_offset + slot_copy;
                column_offset <<= 3;
                column_offset -= slot_copy;
                column_offset <<= 4;
                row_offset = group << 2;
                row_offset += group;
                row_offset <<= 3;
                row_offset -= group;
                row_offset <<= 7;
                column_offset += row_offset;
                grid_address = (u8 *)(column_offset + (s32)grid_base);
                slot_address = source_slot;
                current_input = *slot_address;
                value = current_input->type;
                grid_address[0] = value;
                current_input = *slot_address;
                value = current_input->value;
                grid_address[1] = value;
                *(u16 *)(grid_address + 4) = zero;
            }
        }
    }

    {
        register s32 callback_arg asm("r0");
        register s32 minus_one asm("r1");
        register s32 zero asm("r2");

        minus_one = 1;
        minus_one = -minus_one;
        asm volatile("" : "+r"(minus_one));
        callback_arg = saved_arg0;
        zero = 0;
        func_080A016C(callback_arg, minus_one, zero);
    }
    return 0;
}
