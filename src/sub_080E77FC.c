#include "m2c_prelude.h"

struct DecodeResult {
    u8 category;
    u8 pad01[9];
    u8 types[10];
    u16 values[10];
};

void func_080E5EBC(s32);

void sub_080E77FC(struct DecodeResult *result) {
    u8 index;
    u8 *value_table;
    register u8 *type_table asm("r6");

    index = 0;
    type_table = (u8 *)0x087B924C;
    value_table = type_table + 2;
    do {
        register s32 entry_offset asm("r3");
        register s32 category asm("r1");
        register s32 row_offset asm("r0");
        register u8 *type_slot asm("r0");
        register s32 type asm("r1");
        register s32 signed_type asm("r0");
        register s32 zero asm("r2");

        entry_offset = index << 2;
        category = result->category;
        row_offset = category << 2;
        row_offset += category;
        row_offset <<= 3;
        row_offset = entry_offset + row_offset;
        type_slot = (u8 *)(row_offset + (s32)type_table);
        type = *(u16 *)type_slot;
        zero = 0;
        signed_type = *(s16 *)(type_slot + zero);
        if (signed_type == 0x1A) {
            func_080E5EBC(0x26);
        } else if (signed_type == 0x1B) {
            func_080E5EBC(0x25);
        } else {
            register u8 *type_output asm("r0");
            register s32 value_index asm("r0");
            register u8 *value_output asm("r2");
            register s32 category2 asm("r1");
            register s32 value_row asm("r0");

            type_output = (u8 *)result;
            type_output += 10;
            type_output += index;
            *type_output = type;

            value_index = index << 1;
            value_output = (u8 *)result;
            value_output += 20;
            value_output += value_index;
            category2 = result->category;
            value_row = category2 << 2;
            value_row += category2;
            value_row <<= 3;
            value_row = entry_offset + value_row;
            value_row += (s32)value_table;
            *(u16 *)value_output = *(u16 *)value_row;
        }
        index = (u8)(index + 1);
    } while (index <= 9);
}
