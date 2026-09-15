#include "m2c_prelude.h"

struct ObjAA1E4 {
    u32 flags;
    u8 type;
    u8 kind;
    u16 state;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    u8 status;
    u8 pad19;
    u8 direction;
    u8 pad1B[5];
    s32 callback;
    u8 pad24[4];
    u32 bit_index;
    u8 pad2C[0x1C];
};

extern volatile u16 D_0300000C;
extern volatile u16 D_0300000E;
extern s32 D_020324A8;
extern s32 D_020324AC;
extern struct ObjAA1E4 D_020325A0[];
extern u8 D_02032998;
extern u8 D_0202ECF4;

void func_08094564(s32);
void func_080AAE60(struct ObjAA1E4 *);

void sub_080AA1E4(struct ObjAA1E4 *object)
{
    register s32 i asm("r5");
    register s32 hit asm("r8");
    register s32 object_base asm("ip");
    s32 index8;
    register volatile u16 *buttons_ptr asm("r9");
    register u32 two asm("r4");
    register u32 initial_flags asm("r2");

    initial_flags = object->flags;
    two = 2;
    asm volatile("" : "+r"(two), "+r"(initial_flags));
    initial_flags &= two;
    if (initial_flags) {
        object->status = 0;
        return;
    }

    {
        register u8 *direction_table asm("r1") = (u8 *)0x087A1BD8;
        register volatile u16 *input_ptr asm("r0") = &D_0300000C;
        register s32 input_value asm("r3");
        u8 direction;

        asm volatile("" : "+r"(direction_table), "+r"(input_ptr));
        input_value = *input_ptr;
        direction = *(u8 *)((s32)((u32)(input_value & 0xF0) >> 4)
            + (s32)direction_table);
        if (direction != 0xFF) {
            object->direction = direction;
            {
                register s32 input_mask asm("r0") = two;
                asm volatile("" : "+r"(input_mask));
                input_mask &= input_value;
                if (!input_mask) {
                    object->status = 2;
                    D_020324AC = D_020324A8;
                    D_020324A8++;
                } else {
                    object->status = 3;
                    D_020324AC = D_020324A8;
                    D_020324A8 += 2;
                }
            }
        } else {
            object->status = initial_flags;
        }
    }

    {
        register volatile u16 *initial_buttons asm("r2") = &D_0300000E;
        register u32 masked_buttons asm("r0");
        register u16 buttons_value asm("r1");
        asm volatile("" : "+r"(initial_buttons));
        buttons_value = *initial_buttons;
        masked_buttons = 3;
        masked_buttons &= buttons_value;
        buttons_ptr = initial_buttons;
        if (!masked_buttons) {
            return;
        }
    }

    {
        register s32 zero asm("r0") = 0;
        asm volatile("" : "+r"(zero));
        hit = zero;
    }
    i = 0;
    {
        register s32 base_value asm("r2") = (s32)D_020325A0;
        asm volatile("" : "+r"(base_value));
        object_base = base_value;
    }
scan:
    {
        register s32 initial_index8 asm("r2");
        register s32 object_index_sum asm("r0");
        register s32 object_offset asm("r4");
        register s32 address_base asm("r7");
        register struct ObjAA1E4 *other asm("r3");
        register u32 object_flags asm("r1");
        register u32 one asm("r0");
        register s32 x_distance asm("r3");
        register s32 y_distance asm("r2");

        initial_index8 = i << 3;
        object_index_sum = initial_index8 + i;
        object_offset = object_index_sum << 3;
        address_base = object_base;
        asm volatile("" : "+r"(address_base));
        other = (struct ObjAA1E4 *)(object_offset + address_base);
        object_flags = other->flags;
        one = 1;
        object_flags &= one;
        index8 = initial_index8;
        if (!object_flags || object == other || other->kind == 0xD) {
            goto next;
        }

        {
            register s32 field_base asm("r0") = object_base + 8;
            register s32 *field_address asm("r0");
            register s32 other_coordinate asm("r1");
            register s32 own_coordinate asm("r0");
            asm volatile("" : "+r"(field_base));
            field_address = (s32 *)(object_offset + field_base);
            other_coordinate = *field_address;
            own_coordinate = object->x;
            x_distance = other_coordinate - own_coordinate;
        }
        {
            register s32 field_base asm("r0") = object_base + 12;
            register s32 *field_address asm("r0");
            register s32 other_coordinate asm("r1");
            register s32 own_coordinate asm("r0");
            asm volatile("" : "+r"(field_base));
            field_address = (s32 *)(object_offset + field_base);
            other_coordinate = *field_address;
            own_coordinate = object->y;
            y_distance = other_coordinate - own_coordinate;
        }
        switch (object->direction) {
        case 0: {
            register s32 x_addend asm("r0") = 0x800;
            register u32 adjusted_x asm("r1") = x_distance + x_addend;
            asm volatile("" : "+r"(adjusted_x));
            if (adjusted_x > 0x1000U) goto next;
            if (y_distance < -0x1800) goto next;
            if (y_distance > 0) goto next;
            goto collide;
        }
        case 2:
            if ((u32)x_distance > 0x1800U) goto next;
            if (y_distance < -0x800) goto next;
            if (y_distance > 0x800) goto next;
            goto collide;
        case 4: {
            register s32 x_addend asm("r0") = 0x800;
            register u32 adjusted_x asm("r1") = x_distance + x_addend;
            asm volatile("" : "+r"(adjusted_x));
            if (adjusted_x > 0x1000U) goto next;
            if (y_distance < 0) goto next;
            if (y_distance > 0x1800) goto next;
            goto collide;
        }
        case 6: {
            register s32 x_addend asm("r1") = 0x1800;
            register u32 adjusted_x asm("r0") = x_distance + x_addend;
            asm volatile("" : "+r"(adjusted_x));
            if (adjusted_x > 0x1800U) goto next;
            if (y_distance < -0x800) goto next;
            if (y_distance > 0x800) goto next;
            goto collide;
        }
        case 1: {
            register s32 x_addend asm("r4") = 0x800;
            register u32 adjusted_x asm("r1") = x_distance + x_addend;
            asm volatile("" : "+r"(adjusted_x));
            if (adjusted_x > 0x2000U) goto next;
            if (y_distance < -0x1800) goto next;
            if (y_distance > x_addend) goto next;
            goto collide;
        }
        case 3: {
            register s32 x_addend asm("r0") = 0x800;
            register u32 adjusted_x asm("r1") = x_distance + x_addend;
            asm volatile("" : "+r"(adjusted_x));
            if (adjusted_x > 0x2000U) goto next;
            if (y_distance < -0x800) goto next;
            if (y_distance > 0x1800) goto next;
            goto collide;
        }
        case 5: {
            register s32 x_addend asm("r4") = 0x1800;
            register u32 adjusted_x asm("r1") = x_distance + x_addend;
            asm volatile("" : "+r"(adjusted_x));
            if (adjusted_x > 0x2000U) goto next;
            if (y_distance < -0x800) goto next;
            if (y_distance > x_addend) goto next;
            goto collide;
        }
        case 7: {
            register s32 x_addend asm("r0") = 0x1800;
            register u32 adjusted_x asm("r1") = x_distance + x_addend;
            asm volatile("" : "+r"(adjusted_x));
            if (adjusted_x <= 0x2000U && y_distance >= -0x1800 &&
                y_distance <= 0x800) {
                register s32 found asm("r2") = 1;
                asm volatile("" : "+r"(found));
                hit = found;
            }
            break;
        }
        }

next:
        {
            register s32 hit_test asm("r0") = hit;
            asm volatile("" : "+r"(hit_test));
            if (!hit_test) {
                goto increment;
            }
        }
    }

collide:
    {
        register u32 one asm("r9");
        register s32 one_seed asm("r0");
        register s32 collision_buttons asm("r2");

        collision_buttons = *buttons_ptr;
        one_seed = 1;
        one = one_seed;
        if (collision_buttons & one_seed) {
            register s32 collision_sum asm("r0") = index8 + i;
            register s32 collision_offset asm("r3");
            register s32 collision_base asm("r2");
            register struct ObjAA1E4 *other asm("r4");
            register s32 state asm("r1");

            collision_offset = collision_sum << 3;
            asm volatile("" : "=r"(collision_base) : "0"(object_base));
            other = (struct ObjAA1E4 *)(collision_offset + collision_base);
            state = other->state;
            if ((u16)(state - 1) <= 3) {
                D_02032998 = other->kind;
                object->flags |= 2;
                if (other->state != 2 && other->state != 4) {
                    register s32 direction_value asm("r1") = object->direction;
                    register s32 direction_sum asm("r3") = direction_value + 4;
                    register s32 reduced_direction asm("r0") = direction_sum;
                    asm volatile("" : "+r"(reduced_direction));
                    reduced_direction >>= 3;
                    asm volatile("" : "+r"(reduced_direction));
                    reduced_direction <<= 3;
                    asm volatile("" : "+r"(reduced_direction));
                    reduced_direction = direction_sum - reduced_direction;
                    other->direction = reduced_direction;
                }
                {
                    register s32 rebuilt_sum asm("r0");
                    register s32 rebuilt_offset asm("r0");
                    register struct ObjAA1E4 *rebuilt_other asm("r0");

                    asm volatile("" : "+r"(index8), "+r"(i) : : "memory");
                    rebuilt_sum = index8 + i;
                    rebuilt_offset = rebuilt_sum << 3;
                    rebuilt_other = (struct ObjAA1E4 *)(rebuilt_offset + object_base);
                    rebuilt_other->flags |= 2;
                }
                return;
            }
            {
                register s32 state_test asm("r0") = (u16)state;
                asm volatile("" : "+r"(state_test));
                if (state_test == 5) {
                    register s32 scene_base asm("r1") = (s32)&D_0202ECF4;
                    register u32 *bitset_base asm("r8");
                    register s32 bit_index_field_base asm("r0");
                    register u32 *bit_index_ptr asm("r5");
                    register u32 bit_index asm("r2");
                    register u32 bitset_address asm("r7");
                    register u32 mask_limit asm("r7");
                    register u32 *word asm("r0");
                    register u32 mask asm("r1");

                    asm volatile("" : "+r"(scene_base));
                    bit_index_field_base = object_base + 0x28;
                    bit_index_ptr = (u32 *)(collision_offset + bit_index_field_base);
                    bit_index = *bit_index_ptr;
                    word = (u32 *)((bit_index >> 5) << 2);
                    asm volatile("" : "+r"(word));
                    bitset_address = 0x170;
                    bitset_address = bitset_address - (0 - scene_base);
                    bitset_base = (u32 *)bitset_address;
                    word = (u32 *)((s32)word + (s32)bitset_base);
                    mask_limit = 0x1F;
                    mask = one << (bit_index & mask_limit);
                    if (!(*word & mask)) {
                        register s32 callback_field_base asm("r0");
                        register s32 callback asm("r0");

                        D_02032998 = other->kind;
                        object->flags |= 2;
                        callback_field_base = object_base + 0x20;
                        callback = *(s32 *)(collision_offset + callback_field_base);
                        func_08094564(callback);
                        {
                            register u32 current_index asm("r0") = *bit_index_ptr;
                            register u32 *current_word asm("r2");
                            register u32 current_mask asm("r1");

                            current_word = &bitset_base[current_index >> 5];
                            current_mask = one << (current_index & mask_limit);
                            *current_word |= current_mask;
                        }
                        return;
                    }
                }
            }
        } else if (collision_buttons & 2) {
            register s32 other_sum asm("r0") = index8 + i;
            register s32 other_offset asm("r0");
            register s32 other_base asm("r2") = object_base;
            register struct ObjAA1E4 *button_other asm("r1");

            other_offset = other_sum << 3;
            button_other = (struct ObjAA1E4 *)(other_offset + other_base);
            if (button_other->state == 1) {
                func_080AAE60(object);
                return;
            }
        }
    }
    goto done;

increment:
    {
        register s32 next_i asm("r0") = i + 1;
        asm volatile("" : "+r"(next_i));
        i = (u8)next_i;
    }
    if ((u32)i <= 13) {
        goto scan;
    }
done:
    return;
}
