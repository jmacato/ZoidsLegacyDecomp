#include "m2c_prelude.h"

extern u8 D_03000A84[];
extern s32 D_03000E14[];
extern s32 D_03000E3C[];

void sub_08092D9C(s32 arg0, s32 arg1, s32 arg2) {
    register s32 index asm("r4");
    register u8 *base asm("r5");
    register s32 normalized asm("r3");
    s32 value1;
    s32 value2;
    s32 offset;

    value1 = arg1;
    value2 = arg2;
    normalized = (u8)arg0;
    index = normalized;
    base = D_03000A84;

    if (normalized != 0) {
        register s32 *field4 asm("r0");
        register s32 *destination asm("r2");
        register s32 table_offset asm("r0");
        register s32 *table asm("r1");

        offset = normalized * 0x4C;
        field4 = (s32 *)(base + 4);
        destination = (s32 *)(offset + (s32)field4);
        asm volatile("" : "+r"(destination));
        *destination = normalized * 0x380 + 0x03000E68;
        table = D_03000E14;
        table_offset = (normalized - 1) * 4;
        asm volatile("" : "+r"(table), "+r"(table_offset));
        *(s32 *)(table_offset + (s32)table) = value1;
        table = D_03000E3C;
        asm volatile("" : "+r"(table), "+r"(table_offset));
        *(s32 *)(table_offset + (s32)table) = value2;
    }

    {
        register s32 *destination asm("r1");
        register s32 *catalog asm("r3");
        register u8 *record asm("r2");
        s32 loaded;

        offset = index * 0x4C;
        destination = (s32 *)(base + 8);
        destination = (s32 *)(offset + (s32)destination);
        asm volatile("" : "+r"(destination), "+r"(offset), "+r"(base));
        catalog = (s32 *)0x087A0A14;
        asm volatile("" : "+r"(catalog));
        loaded = *(s32 *)(index * 4 + (s32)catalog);
        asm volatile("" : : "r"(index));
        *destination = loaded;
        record = (u8 *)(offset + (s32)base);
        asm volatile("" : "+r"(record));
        record[1] = 1;
    }
}
