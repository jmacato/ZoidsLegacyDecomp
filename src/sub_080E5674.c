#include "m2c_prelude.h"

struct ItemE5674 {
    u8 pad0[0x12];
    u16 value;
    u8 pad14[4];
};

struct ZoidE5674 {
    u8 pad0[0xE];
    u16 total;
    u8 pad10[0x32];
    s16 first;
    s16 second;
    u8 pad46[6];
    s16 limit;
    u8 pad4E[4];
    u16 slots[4];
};

extern struct ItemE5674 D_087B2524[];
s16 func_080ECD98(s32, s32);

void sub_080E5674(struct ZoidE5674 *arg0)
{
    register struct ZoidE5674 *owner asm("r5") = arg0;
    register u32 index asm("r2");
    register struct ItemE5674 *items asm("r3");

    owner->total = 0;
    index = 0;
    items = D_087B2524;
    do {
        register s32 slot_value asm("r0");
        register u16 *slot asm("r1");

        slot_value = index << 2;
        asm volatile("" : "+r"(slot_value));
        slot_value = (s32)owner + slot_value;
        asm volatile("" : "+r"(slot_value));
        slot = (u16 *)slot_value;
        asm volatile("" : "+r"(slot));
        slot = (u16 *)((u8 *)slot + 0x52);
        slot_value = *slot;
        if (slot_value != 0) {
            register s32 item_offset asm("r1");
            register struct ItemE5674 *item asm("r1");
            register u32 value asm("r0");
            register u32 total asm("r1");

            item_offset = slot_value << 1;
            item_offset += slot_value;
            item_offset <<= 3;
            item = (struct ItemE5674 *)(item_offset + (s32)items);
            value = item->value;
            total = owner->total;
            value += total;
            owner->total = value;
        }
        {
            register u32 next_index asm("r0") = index + 1;
            asm volatile("" : "+r"(next_index));
            index = (u8)next_index;
        }
    } while (index <= 3);

    {
        register s16 *limit_ptr asm("r6") = &owner->limit;
        register s32 total asm("r1");
        register s32 limit asm("r0");
        register s32 reserve_r0 asm("r0");
        register s32 reserve_r3 asm("r3");

        asm volatile("" : "=r"(reserve_r0), "=r"(reserve_r3));
        total = M2C_FIELD(owner, s16 *, 0xE);
        asm volatile("" : "+r"(total) : "r"(reserve_r0), "r"(reserve_r3));
        limit = M2C_FIELD(limit_ptr, s16 *, 0);
        asm volatile("" : "+r"(limit));

        if (total > limit) {
            register s32 saved_total asm("r3") = total;
            register s32 saved_limit asm("r2") = limit;
            register s32 difference asm("r0") = saved_total - saved_limit;
            asm volatile("" : "+r"(saved_total));
            asm volatile("" : "+r"(saved_limit));
            asm volatile("" : "+r"(difference));

            if (difference < saved_limit) {
                register s16 *value_ptr asm("r4") = &owner->first;
                register s32 value asm("r1");
                register s32 factor asm("r0");
                register s32 divisor asm("r1");

                value = M2C_FIELD(value_ptr, s16 *, 0);
                asm volatile("" : "+r"(value));
                factor = saved_limit << 1;
                factor -= saved_total;
                factor *= value;
                divisor = saved_limit;
                *value_ptr = func_080ECD98(factor, divisor);

                value_ptr++;
                {
                    register s32 second_value asm("r3");
                    register s32 second_limit asm("r1");
                    register s32 second_factor asm("r0");
                    register s32 second_total asm("r2");
                    register s32 hold_r0 asm("r0");
                    register s32 hold_r2 asm("r2");

                    asm volatile("" : "=r"(hold_r0), "=r"(hold_r2));
                    second_value = M2C_FIELD(value_ptr, s16 *, 0);
                    asm volatile("" : "+r"(second_value) : "r"(hold_r0), "r"(hold_r2));
                    second_limit = M2C_FIELD(limit_ptr, s16 *, 0);
                    asm volatile("" : "+r"(second_limit) : "r"(hold_r0));
                    second_factor = second_limit << 1;
                    second_total = M2C_FIELD(owner, s16 *, 0xE);
                    asm volatile("" : "+r"(second_total));
                    second_factor -= second_total;
                    second_factor *= second_value;
                    *value_ptr = func_080ECD98(second_factor, second_limit);
                }
            } else {
                register s16 *clear_ptr asm("r0") = &owner->second;
                register s32 clear asm("r1") = 0;
                asm volatile("" : "+r"(clear_ptr));
                asm volatile("" : "+r"(clear));
                *clear_ptr = clear;
                clear_ptr--;
                *clear_ptr = clear;
            }
        }
    }
}
