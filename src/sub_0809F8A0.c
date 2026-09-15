#include "m2c_prelude.h"

extern u8 D_020317DA;
extern u16 D_020317DC[];
extern u16 D_020317FC[];
extern u16 D_0203181C[];
extern u16 D_0203183C;
extern u16 D_0203183E;

void func_809AA64(s32, s32, s32, s32);

struct ItemEntryF8A0 {
    const u8 *data;
    u32 unk4;
};

void sub_0809F8A0(u8 item)
{
    register u32 saved_item asm("r6") = item;
    register u32 count asm("r0") = D_020317DA;

    if (count <= 15) {
        u8 i = 0;

        if (i < count) {
            register u16 *items asm("r4") = D_020317DC;
            register u32 wanted asm("r3") = saved_item;
            register u32 limit asm("r2") = count;

            do {
                if (items[i] == wanted) {
                    return;
                }
                i++;
            } while (i < limit);
        }

        asm volatile("" : "+r"(saved_item));

        {
            const struct ItemEntryF8A0 *table =
                (const struct ItemEntryF8A0 *)0x087AF9D4;
            const u8 *data = table[saved_item].data;
            u32 value;

            value = data[1];
            value |= data[2] << 8;
            value |= data[3] << 16;
            {
                register u16 *remaining_cost asm("r4") = &D_0203183C;
                value >>= 5;
                *remaining_cost -= value;
                {
                    register u16 *remaining_slots asm("r5") = &D_0203183E;
                    *remaining_slots -= 1;

                    func_809AA64((s32)table, saved_item,
                        *remaining_cost, *remaining_slots);
                    D_020317DC[D_020317DA] = saved_item;
                    D_020317FC[D_020317DA] = *remaining_cost;
                    D_0203181C[D_020317DA] = *remaining_slots;
                    D_020317DA++;
                }
            }
        }
    }
}
