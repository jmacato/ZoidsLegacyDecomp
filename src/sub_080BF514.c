#include "m2c_prelude.h"

struct TransferRecord {
    u32 word0;
    u16 kind;
    s16 value;
    u32 word8;
};

extern u8 D_02034B4C[];

u8 func_080BF464(u32, u32, s32);
s32 func_080E522C(s32, s32);

#define APPLY_ADJUST(slot_stride, group_stride, field_offset) do {       \
    register s32 current asm("r0") = destination->value;                \
    register u8 *stat_base asm("r3") = D_02034B4C;                      \
    register u32 stat_address asm("r2") = slot * (slot_stride);         \
    register u32 group_offset asm("r1") = group * (group_stride);       \
    register s32 stat asm("r1");                                       \
    stat_address += group_offset;                                       \
    stat_address += (u32)stat_base;                                     \
    stat_address += (field_offset);                                     \
    stat = *(s16 *)stat_address;                                        \
    destination->value = func_080E522C(current, stat + 100);            \
} while (0)

void sub_080BF514(u32 arg0, u32 arg1, u32 arg2)
{
    register u32 group asm("r5") = (u8)arg0;
    register u32 slot asm("r4") = (u8)arg1;
    register u32 item asm("r2") = (u8)arg2;
    register struct TransferRecord *source asm("r8");
    register u32 index asm("r6");
    struct TransferRecord *destination;
    register u8 *base asm("ip");
    register u8 *source_base asm("r3");
    register u32 bank asm("r3");
    register u32 slot_twice asm("r2");
    register u32 offset asm("r0");
    register u32 source_kind asm("r1");

    {
        register u32 group_offset asm("r1") = group * 0x1380;
        register u32 slot_offset asm("r0") = slot * 0x270;
        register u32 item_offset asm("r0");
        register struct TransferRecord *source_init asm("r1");

        source_base = D_02034B4C;
        slot_offset += (u32)source_base;
        group_offset += slot_offset;
        item_offset = item * 12 + 0xE4;
        group_offset += item_offset;
        source_init = (struct TransferRecord *)group_offset;
        source = source_init;
        source_kind = source_init->kind;
    }
    {
        register u32 masked_kind asm("r0") = 0x7F;
        masked_kind &= source_kind;
        base = source_base;
        if (masked_kind == 0x1A) {
            goto done;
        }
    }
    {
        index = 0;
        bank = group * 0x1218;
        slot_twice = slot << 1;
        {
            register u32 bank_slot asm("r0") = slot_twice + slot;
            register u8 *bank_base asm("r1");

            bank_slot <<= 6;
            bank_slot += slot;
            bank_slot <<= 2;
            bank_base = base + 0x7C28;
            bank_slot += (u32)bank_base;
            bank += bank_slot;
        }
        offset = 0x184;
        goto scan_test;

scan_advance:
        {
            register u32 next asm("r0") = index + 1;
            next <<= 24;
            index = next >> 24;
        }
        if (index > 31) {
            goto done;
        }
        offset = index * 12 + 0x184;

scan_test:
        destination = (struct TransferRecord *)(bank + offset);
        if (destination->kind != 0) {
            goto scan_advance;
        }

        if (index <= 31) {
            u16 *active;
            register u32 active_slot asm("r1") = slot_twice + slot;
            register u32 active_group asm("r0");
            register u32 active_bits asm("r2");
            register u32 marked asm("r0");

            active_slot <<= 6;
            active_slot += slot;
            active_slot <<= 2;
            active_group = group * 0x1218;
            active_slot += active_group;
            active_slot += (u32)base;
            active = (u16 *)(active_slot + 0x7C28);
            active_bits = *active;
            marked = 1;
            marked |= active_bits;
            *active = marked;
            *destination = *source;

            if (func_080BF464(group, slot, 0x18) == 0xFF) {
                switch (destination->kind & 0x7F) {
                case 2:
                    APPLY_ADJUST(0x270, 0x1380, 0xA4);
                    break;
                case 8:
                    APPLY_ADJUST(0x270, 0x1380, 0xA6);
                    break;
                case 11:
                    APPLY_ADJUST(0x270, 0x1380, 0xA8);
                    break;
                case 16:
                    APPLY_ADJUST(0x270, 0x1380, 0xAA);
                    break;
                case 3:
                    APPLY_ADJUST(0x270, 0x1380, 0xAC);
                    break;
                }
            }

            if (func_080BF464(group, slot, 0x17) != 0xFF) {
                switch (destination->kind & 0x7F) {
                case 15:
                    APPLY_ADJUST(0x270, 0x1380, 0xDC);
                    break;
                case 11:
                    APPLY_ADJUST(0x270, 0x1380, 0xDE);
                    break;
                case 7:
                    APPLY_ADJUST(0x270, 0x1380, 0xE0);
                    break;
                case 9:
                    APPLY_ADJUST(0x270, 0x1380, 0xE2);
                    break;
                }
            }
        }
    }

done:
    {
        register u16 result asm("r0") = 0;
        register struct TransferRecord *clear_source asm("r6") = source;

        asm volatile("" : : "r"(result));
        clear_source->kind = result;
    }
}
