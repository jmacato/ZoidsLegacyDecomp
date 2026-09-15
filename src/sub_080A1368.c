#include "m2c_prelude.h"

struct InputA1368 {
    u8 pad0;
    u8 type;
};

struct TableA1368 {
    u8 type;
    u8 bit;
} __attribute__((packed));

struct StateA1368 {
    u8 pad00[20];
    s32 x;
    s32 y;
    u8 pad1C;
    u8 variant;
};

void func_0809F7C8(s32);
void *func_080A9D78(s32, s32, s32, s32, s32, s32, s32, s32);
void func_080A016C(s32, s32, s32);

extern u8 D_020316FC[];
extern struct StateA1368 D_0202ECF4;

s32 sub_080A1368(s32 arg0, struct InputA1368 **arg1)
{
    register struct InputA1368 **source asm("r5") = arg1;
    register u32 saved_arg0 asm("r9");
    register u32 i asm("r4");
    struct InputA1368 *input;

    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    func_0809F7C8((*source)->type);

    i = 0;
    do {
        register u32 next asm("r0");

        D_020316FC[i] = 1;
        next = i + 1;
        asm volatile("" : "+r"(next));
        i = (u8)next;
    } while (i <= 0x45U);

    i = 0;
    {
        register struct TableA1368 *table_init asm("r0") =
            (struct TableA1368 *)0x087A1894;
        register u32 first_type asm("r1") = table_init->type;
        register struct InputA1368 *retained asm("ip");
        register struct TableA1368 *table asm("r6");

        asm volatile("" : "+r"(table_init), "+r"(first_type));
        input = *source;
        retained = input;
        table = table_init;

        if (first_type != 0) {
            struct InputA1368 *check = retained;
            register struct TableA1368 *scan asm("r5") = table;
            register u32 *bits asm("r8") = (u32 *)0x020217C8;

            do {
                register u32 entry_offset asm("r2") = i << 1;
                register u8 *entry asm("r1") =
                    (u8 *)(entry_offset + (u32)scan);

                if (check->type == entry[0]) {
                    register u8 *bit_address asm("r0") =
                        (u8 *)table + 1;
                    register u32 bit asm("r3");
                    register u32 *word asm("r2");
                    register u32 mask asm("r1");
                    register u32 value asm("r0");

                    bit_address = (u8 *)(entry_offset + (u32)bit_address);
                    bit = *bit_address;
                    word = (u32 *)((u32)bits + ((bit >> 5) << 2));
                    bit &= 0x1F;
                    mask = 1;
                    mask <<= bit;
                    value = *word;
                    value |= mask;
                    *word = value;
                }
                {
                    register u32 next asm("r0") = i + 1;

                    asm volatile("" : "+r"(next));
                    i = (u8)next;
                }
            } while (scan[i].type != 0);
        }

        {
            register struct InputA1368 *check asm("r1") = retained;

            if (check->type == 0x88) {
                D_0202ECF4.x = 0x81000;
                D_0202ECF4.y = 0xBE000;
                func_080A9D78(0x6C, 0xD, 0x81000, 0xBE000,
                    D_0202ECF4.variant, 2, 0xFF, 0);
            }
        }
    }

    func_080A016C(saved_arg0, -1, 0);
    return 0;
}
