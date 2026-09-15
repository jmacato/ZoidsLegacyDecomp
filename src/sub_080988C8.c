#include "m2c_prelude.h"
extern u8 D_0200DE90[];
extern u8 D_0200E6C4[];
extern u8 D_0200E6CE[];
extern s32 *func_0809716C(u8);
extern void func_0809885C(void);

void sub_080988C8(s32 arg0, u8 *arg1)
{
    register u8 *stream asm("r2");
    register s32 index asm("r5");
    register u8 *lookup asm("r10");
    u8 count;
    u8 value;

    stream = arg1;
    index = (u8)((u32)arg0 << 24 >> 24);
    count = 0;
    value = *stream;
    lookup = D_0200DE90;
    if (value != 0) {
        register u8 *output asm("r9");
        register u8 *lookup_copy asm("r8");
        register u8 *index_table asm("r12");
        s32 bank;
        register s32 offset asm("r6");
        s32 condition;
        s32 slot;

        output = D_0200E6CE;
        lookup_copy = lookup;
        index_table = D_0200E6C4 + index;
        bank = index * 0xD2;
        offset = index * 0x1E5A;
        do {
            {
                register u8 *index_entry asm("r1");

                index_entry = index_table;
                asm volatile("" : "+r"(index_entry));
                slot = *index_entry + bank;
            }
            {
                register s32 destination asm("r0");

                destination = lookup_copy[slot] * 0x25;
                asm volatile("add %0, %1, %0"
                             : "+r"(destination)
                             : "r"(count));
                output[destination + offset] = value;
            }
            condition = *stream;
            if (condition > 3) {
                goto next_character;
            }
            asm volatile("cmp %0, #2\n\tbge 1f"
                         :
                         : "r"(condition)
                         : "cc");
            if (condition != 1) {
                goto next_character;
            }
            stream += 1;
            count += 1;
            {
                register u8 *index_entry asm("r1");
                register s32 destination asm("r0");

                index_entry = index_table;
                asm volatile("" : "+r"(index_entry));
                slot = *index_entry + bank;
                destination = count + lookup_copy[slot] * 0x25 + offset;
                asm volatile("add %0, %1"
                             : "+r"(destination)
                             : "r"(output));
                *(u8 *)destination = *stream;
            }
            asm volatile("1:");
next_character:
            stream += 1;
            count += 1;
            value = *stream;
        } while (value != 0);
    }
    {
        register u8 *table_base asm("r0");
        register u8 *index_table asm("r3");
        register s32 bank asm("r2");
        s32 slot;

        table_base = D_0200E6C4;
        asm volatile("add %0, %1, %2"
                     : "=r"(index_table)
                     : "r"(index), "r"(table_base));
        slot = *index_table;
        bank = index * 0xD2;
        slot += bank;
        {
            register s32 destination asm("r0");

            destination = lookup[slot] * 0x25;
            asm volatile("add %0, %1, %0"
                         : "+r"(destination)
                         : "r"(count));
            D_0200E6CE[destination + index * 0x1E5A] = 0;
        }
        if (count <= 0x24) {
            register s32 table_value asm("r0");
            register s32 destination_slot asm("r1");

            table_value = *index_table;
            destination_slot = bank + 1;
            asm volatile("add %0, %1, %0"
                         : "+r"(destination_slot)
                         : "r"(table_value));
            lookup[destination_slot] = lookup[table_value + bank] + 1;
        } else {
            register s32 table_value asm("r0");
            register s32 destination_slot asm("r1");

            table_value = *index_table;
            destination_slot = bank + 1;
            asm volatile("add %0, %1, %0"
                         : "+r"(destination_slot)
                         : "r"(table_value));
            lookup[destination_slot] = lookup[table_value + bank] + 2;
        }
    }
    {
        s32 *result;

        result = func_0809716C(index);
        func_0809885C();
        {
            register u8 *counter asm("r1");

            counter = D_0200E6C4 + index;
            *counter += 1;
        }
        *result |= 2;
    }
}
