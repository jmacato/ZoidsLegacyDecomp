#include "m2c_prelude.h"

u16 func_080E522C(s16, s16);
s32 func_080E74F0(s32, s32, s32);

struct Item {
    u16 unk0;
    u16 flags;
    u32 data;
    u8 unk8;
    u8 type;
    u16 bonus;
    u8 rest[12];
};

struct Zoid {
    u8 pad0[0xA];
    u16 fieldA;
    u16 fieldC;
    u8 padE[0x34];
    s16 field42;
    s16 field44;
    u8 pad46[4];
    u16 field4A;
    u8 pad4C[6];
    u16 slots[16];
};

extern struct Item D_087B2524[];

void sub_080E570C(struct Zoid *arg0, s32 arg1) {
    u8 i;

    arg0->fieldC = func_080E522C(arg0->field42, arg0->field44);
    i = 0;
    do {
        register s32 slot_value asm("r0");
        register u16 *slot asm("r1");

        slot_value = i << 2;
        asm volatile("" : "+r"(slot_value));
        slot_value = (s32)arg0 + slot_value;
        asm volatile("" : "+r"(slot_value));
        slot = (u16 *)slot_value;
        asm volatile("" : "+r"(slot));
        slot = (u16 *)((u8 *)slot + 0x52);
        asm volatile("" : "+r"(slot));
        slot_value = *slot;
        asm volatile("" : "+r"(slot_value));
        if (slot_value != 0) {
            register struct Item *item asm("r2");

            {
                register s32 item_index asm("r1");

                item_index = slot_value;
                asm volatile("" : "+r"(item_index));
                slot_value = item_index << 1;
                slot_value += item_index;
                slot_value <<= 3;
                asm volatile("" : "+r"(slot_value));
            }
            {
                register struct Item *base asm("r1");

                base = D_087B2524;
                asm volatile("" : "+r"(base));
                item = (struct Item *)(slot_value + (s32)base);
                asm volatile("" : "+r"(item));
            }
            if ((7 & item->flags) == 3 && item->type == 6) {
                u32 data;

                data = item->data;
                if (!(0x1F000000 & data)) {
                    u32 low;

                    low = 0xFF;
                    low &= data;
                    if (low != 0x16) {
                        asm volatile("" : "+r"(low));
                        if (low == 0xB) {
                            register u16 bonus asm("r0");
                            register u16 current asm("r1");

                            bonus = item->bonus;
                            asm volatile("" : "+r"(bonus));
                            current = arg0->fieldC;
                            asm volatile("" : "+r"(current));
                            bonus += current;
                            arg0->fieldC = bonus;
                        }
                    }
                }
            }
        }
        i += 1;
    } while ((u32)i <= 7U);

    arg0->fieldA = (u16)arg0->field42 + arg0->field4A;
    if ((func_080E74F0(arg1, 0xF, 0) << 16) != 0) {
        register u32 add asm("r2");
        register u32 sum asm("r0");
        register u32 current asm("r1");

        add = 0xFA;
        add <<= 1;
        asm volatile("" : "+r"(add));
        sum = add;
        asm volatile("" : "+r"(sum));
        current = arg0->fieldA;
        asm volatile("" : "+r"(current));
        sum += current;
        arg0->fieldA = sum;
    }
    if ((func_080E74F0(arg1, 0x10, 0) << 16) != 0) {
        register u32 add asm("r2");
        register u32 sum asm("r0");
        register u32 current asm("r1");

        add = 0xFA;
        add <<= 2;
        asm volatile("" : "+r"(add));
        sum = add;
        asm volatile("" : "+r"(sum));
        current = arg0->fieldA;
        asm volatile("" : "+r"(current));
        sum += current;
        arg0->fieldA = sum;
    }
}
