#include "m2c_prelude.h"

struct Object9885C {
    u8 pad0[0xA];
    u16 half_a;
    s16 half_c;
    u16 half_e;
    u8 pad10[3];
    u8 category;
    u8 limit;
};

void func_08097DA8(struct Object9885C *, s32);

void sub_0809885C(struct Object9885C *obj) {
    register u8 *category_table asm("r0");
    register u8 *category_entry asm("r1");
    register s32 category asm("r3");
    register s32 current asm("r0");
    s32 limit;

    category_table = (u8 *)0x0200E6C4;
    asm volatile("" : "+r"(category_table));
    category = obj->category;
    asm volatile("" : "+r"(category));
    category_entry = (u8 *)(category + (s32)category_table);
    asm volatile("" : "+r"(category_entry));
    current = *category_entry;
    asm volatile("" : "+r"(current));
    limit = obj->limit;
    if ((u32)current >= (u32)limit) {
        s32 threshold;
        register s32 current_saved asm("r5");

        current_saved = current;
        asm volatile("" : "+r"(current_saved));
        threshold = obj->half_a;
        threshold -= 2;
        threshold += (u32)threshold >> 31;
        threshold >>= 1;
        threshold += limit;
        if (current_saved < threshold) {
            register s32 category_term asm("r1");
            s32 table_index;
            s32 record_index;
            register u8 *value_table asm("r2");
            register s32 record_base_r2 asm("r2");

            category_term = category * 0x1E5A;
            value_table = (u8 *)0x0200DE90;
            asm volatile("" : "+r"(value_table));
            table_index = 0xD2;
            table_index *= category;
            asm volatile("add %0, %1, %0"
                         : "+r"(table_index)
                         : "r"(current_saved));
            table_index += (s32)value_table;
            record_index = *(u8 *)table_index;
            record_index *= 0x25;
            record_base_r2 = 0x0200E6CE;
            asm volatile("" : "+r"(record_base_r2));
            asm volatile("add %0, %0, %1"
                         : "+r"(record_index)
                         : "r"(record_base_r2));
            category_term += record_index;
            func_08097DA8(obj, category_term);
            obj->half_c = 0;
            obj->half_e += 2;
        }
    }
}
