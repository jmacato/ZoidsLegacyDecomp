#include "m2c_prelude.h"

struct SpriteA9AFC {
    u8 pad0[8];
    u16 x;
    u16 y;
};

struct ObjA9AFC {
    u32 flags;
    u8 type;
    u8 variant;
    u16 kind;
    s32 x;
    s32 y;
    u8 pad10[9];
    s8 state;
    u8 selected;
    u8 pad1B[5];
    struct SpriteA9AFC *sprite;
    struct SpriteA9AFC *secondary;
    u32 bit_index;
};

struct DescriptorA9AFC {
    void *callback;
    u8 pad4[12];
};

struct FourWordsA9AFC {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
};

extern s32 func_080A9A54(struct ObjA9AFC *);
extern struct SpriteA9AFC *func_08094374(void *, u32, u32, s32,
    s32, s32, s32, void *, s32);
extern struct SpriteA9AFC *func_08094484(s32, s32, s32, s32,
    s32, s32, s32, s32, s32);

extern struct DescriptorA9AFC D_087AD208[];
extern s32 D_087A1B98[][2];

void sub_080A9AFC(struct ObjA9AFC *obj)
{
    register u32 enabled asm("r6");
    s32 x;

    if (obj->kind != 5) {
        s32 result = func_080A9A54(obj);

        enabled = (u32)(result << 16) >> 16;
    } else {
        register u32 bit_index asm("r2");
        register u32 bitset_base asm("r0") = 0x0202ECF4;
        u32 word_offset;
        u32 addend;
        u32 *word;
        s32 masked;

        asm volatile("" :: "r"(bitset_base));
        bit_index = obj->bit_index;
        word_offset = (bit_index >> 5) * 4;
        addend = 0x170;
        bitset_base += addend;
        word = (u32 *)(word_offset + bitset_base);
        bit_index &= 0x1F;
        bitset_base = 1;
        bitset_base <<= bit_index;
        masked = *word;
        masked &= bitset_base;
        bitset_base = -masked;
        bitset_base |= masked;
        enabled = bitset_base >> 31;
    }

    {
    register u32 object_type asm("r0") = obj->type;

    if (object_type != 0x4B) {
        void *descriptor;
        register u32 type asm("r5");
        register s32 descriptor_value asm("r2");
        register u32 type_copy asm("r2");
        register s32 x_work asm("r0");
        s32 y;
        u8 descriptor_index;
        struct DescriptorA9AFC *descriptor_base;
        struct DescriptorA9AFC *entry;
        register u32 entry_addr asm("r0");
        void *callback;
        register void *comparison asm("r0");

        descriptor_base = D_087AD208;
        type_copy = object_type;
        entry_addr = type_copy << 4;
        entry_addr += (u32)descriptor_base;
        entry = (struct DescriptorA9AFC *)entry_addr;
        callback = entry->callback;

        comparison = (void *)0x0827A0C4;
        descriptor = descriptor_base;
        type = type_copy;
        descriptor_index = object_type;
        if (callback == comparison) {
            descriptor_value = 0xD0;
            descriptor_index = obj->variant;
        } else {
            comparison = (void *)0x0827A28C;
            if (callback == comparison) {
                descriptor_value = 0x110;
                descriptor_index = obj->variant;
            } else {
                descriptor_value = obj->variant << 4;
                descriptor_index = obj->variant;
            }
        }

        x_work = obj->x;
        if (x_work < 0) {
            x_work += 0xFF;
        }
        x_work <<= 8;
        x = x_work >> 16;
        y = obj->y;
        if (y < 0) {
            y += 0xFF;
        }
        y = (y << 8) >> 16;
        obj->sprite = func_08094374(descriptor, type, enabled, x, y,
            descriptor_value, descriptor_index,
            obj->kind != 5 ? (void *)0x004410E0 : (void *)0x004410D0, 0);
    } else {
        register struct FourWordsA9AFC *dst asm("r2") =
            (struct FourWordsA9AFC *)0x0203299C;
        register u8 *src_base asm("r0") = (u8 *)D_087AD208;
        register struct FourWordsA9AFC *copy_dst asm("r1") = dst;
        register u32 src_offset asm("r5") = 150;
        register s32 x_work asm("r0");
        s32 y;

        src_offset <<= 3;
        src_base += src_offset;
        *copy_dst = *(const struct FourWordsA9AFC *)src_base;
        {
            s32 *values = (s32 *)0x087A1C08;
            register u8 *selection_base asm("r0") = (u8 *)0x020218E4;
            register u32 selection_addend asm("r7") = 0x6809;

            asm volatile("" :: "r"(selection_base));
            selection_base += selection_addend;
            dst->wordC = values[*selection_base];
        }
        x_work = obj->x;
        if (x_work < 0) {
            x_work += 0xFF;
        }
        x_work <<= 8;
        x = x_work >> 16;
        y = obj->y;
        if (y < 0) {
            y += 0xFF;
        }
        y = (y << 8) >> 16;
        obj->sprite = func_08094374(dst, 0, enabled, x, y,
            obj->variant << 4, obj->variant,
            obj->kind != 5 ? (void *)0x004410E0 : (void *)0x004410D0, 0);
    }
    }

    if (obj->kind != 2 && obj->kind != 4 && obj->kind != 5 &&
        obj->type != 0x4B && obj->type != 0x49 && obj->type != 0x69 &&
        obj->type != 0x6A && obj->type != 0x6B &&
        (u8)(obj->type - 0x6E) > 0x1E) {
        struct SpriteA9AFC *secondary;
        register s32 x_work asm("r0");
        s32 first_table = 0x0832BB9C;
        s32 second_table = 0x0832BBA8;
        s32 y;

        asm volatile("" :: "r"(first_table), "r"(second_table));
        x_work = obj->x;
        if (x_work < 0) {
            x_work += 0xFF;
        }
        x_work <<= 8;
        x = x_work >> 16;
        y = obj->y;
        if (y < 0) {
            y += 0xFF;
        }
        y = (y << 8) >> 16;
        secondary = func_08094484(first_table, second_table, 0, x, y,
            0x3B2, 0xF, 0x11C8, 0);
        obj->secondary = secondary;
        secondary->y += 0xE;
    } else {
        obj->secondary = 0;
    }

    if (obj->kind != 2) {
        if (obj->kind == 5) {
            obj->sprite->y = 8;
        } else if ((u8)(obj->type - 0x69) > 2 && obj->type != 0x6E &&
                   obj->type != 0x6F) {
            if (obj->type == 0x6C || obj->type == 0x8D ||
                obj->type == 0x8E) {
                if (obj->kind != 0xFF) {
                    obj->sprite->y = 0xFFF0;
                }
            } else if (obj->kind != 4) {
                if (obj->type != 0x4B) {
                    obj->sprite->y -= 2;
                } else {
                    obj->sprite->y += 2;
                }
            } else {
                struct SpriteA9AFC *sprite = obj->sprite;
                s32 value = D_087A1B98[obj->selected][0];

                if (value < 0) {
                    value += 0xF;
                }
                sprite->x -= value >> 4;
                sprite = obj->sprite;
                value = D_087A1B98[obj->selected][1];
                if (value < 0) {
                    value += 0xF;
                }
                sprite->y -= value >> 4;
            }
        }
    }
    obj->state = 0;
}
