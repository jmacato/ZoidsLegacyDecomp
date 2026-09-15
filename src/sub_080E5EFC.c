#include "m2c_prelude.h"

struct EquipmentSlotE5EFC {
    u16 flags;
    u16 item;
};

struct ZoidE5EFC {
    u8 pad0[2];
    u8 object_index;
    u8 pad3[0x4D];
    struct EquipmentSlotE5EFC slots[8];
};

struct ItemE5EFC {
    u16 unk0;
    u16 flags;
    u8 pad4[20];
};

void func_080E5880(void *, s32);
void func_080E5CE4(u16, s32);
void func_080E5D38(u8, s32);

void sub_080E5EFC(u8 item, u8 zoid_index, u8 slot_index)
{
    register u8 *record_base asm("r1");
    register struct ZoidE5EFC *zoid asm("r6");
    register s32 effect;
    register struct EquipmentSlotE5EFC *slot asm("r5");

    if (item != 0) {
        register u8 *status_base asm("r0") = (u8 *)0x020218E4;
        register u32 status_offset asm("r3") = 0x6934;
        asm volatile("" : "+r"(status_base));
        asm volatile("" : "+r"(status_offset));
        status_base += status_offset;
        status_base = (u8 *)((u32)item + (u32)status_base);
        if (*status_base == 0) {
            return;
        }
    }

    {
        register s32 record_offset asm("r0");
        record_offset = zoid_index << 3;
        record_offset -= zoid_index;
        record_offset <<= 4;
        record_base = (u8 *)0x020218E8;
        asm volatile("" : "+r"(record_base));
        zoid = (struct ZoidE5EFC *)(record_offset + (s32)record_base);
    }
    {
        register u32 object_index asm("r0") = zoid->object_index;
        if (object_index != 0) {
            object_index <<= 6;
            {
                register u32 effect_offset asm("r3") = 0x5A90;
                asm volatile("" : "+r"(effect_offset));
                record_base += effect_offset;
                effect = object_index + (s32)record_base;
            }
        } else {
            effect = 0;
        }
    }
    {
        register u32 slot_offset asm("r0") = slot_index << 2;
        slot_offset += 0x50;
        slot = (struct EquipmentSlotE5EFC *)((u8 *)zoid + slot_offset);
    }

    if (item == 0) {
        goto replace;
    }
    {
        register struct ItemE5EFC *catalog asm("r1") =
            (struct ItemE5EFC *)0x087B2524;
        register u32 item_offset asm("r0");
        register u32 flags asm("r1");
        register u32 one asm("r2");
        register u32 allowed asm("r0");
        register u32 slot_flags asm("r1");

        asm volatile("" : "+r"(catalog));
        item_offset = item << 1;
        item_offset += item;
        item_offset <<= 3;
        item_offset += (u32)catalog;
        flags = ((struct ItemE5EFC *)item_offset)->flags;
        asm volatile("" : "+r"(flags));
        one = 1;
        allowed = one;
        allowed &= flags;
        if (allowed != 0) {
            goto use_two;
        }
        slot_flags = slot->flags;
        allowed = one;
        goto test_allowed;
use_two:
        slot_flags = slot->flags;
        allowed = 2;
test_allowed:
        allowed &= slot_flags;
        if (allowed == 0) {
            return;
        }
    }
    asm volatile("" : "+r"(item));
    if (item == 0) {
        goto replace;
    }
    func_080E5D38(item, 1);

replace:
    if (slot->item != 0) {
        func_080E5CE4(slot->item, 1);
    }
    slot->item = item;
    func_080E5880(zoid, effect);
}
