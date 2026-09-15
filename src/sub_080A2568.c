#include "m2c_prelude.h"

struct InputRecord {
    u8 pad0;
    u8 type;
    u8 value;
    u8 row;
    u8 column;
    u8 mode;
};

struct MetadataEntry {
    u8 pad0[2];
    u8 value;
    u8 pad3[53];
};

extern struct MetadataEntry D_087AFCC4[];

void func_080BAF2C(s32, s32, s32, s32, s32, s32, s32);
void func_080A016C(u8, s32, s32);

s32 sub_080A2568(s32 arg0, struct InputRecord **arg1) {
    struct InputRecord *volatile *source_slot;
    register u32 saved_arg0 asm("r8");
    register struct InputRecord *record asm("r4");
    register s32 mode asm("r5");

    source_slot = arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    record = *source_slot;
    mode = record->mode;
    switch (mode) {
    case 0: {
        register u32 type asm("r0");
        register u32 call_value asm("r1");
        register s32 metadata_value asm("r2");
        register struct MetadataEntry *metadata asm("r3");

        type = record->type;
        call_value = record->value;
        metadata = (struct MetadataEntry *)0x087AFCC4;
        asm volatile("" : "+r"(metadata));
        metadata_value = type << 3;
        metadata_value -= type;
        metadata_value <<= 3;
        metadata_value += (s32)metadata;
        metadata_value = *(u8 *)(metadata_value + 2);
        func_080BAF2C(type,
                      call_value,
                      metadata_value,
                      record->row,
                      record->column,
                      mode,
                      mode);
        break;
    }
    case 1: {
        register s32 row asm("r6");
        register s32 flag_left asm("r0");
        register s32 flag_right asm("r1");

        row = record->row;
        if (row == 0) {
            register u32 type asm("r0");
            register u32 call_value asm("r1");
            register s32 metadata_value asm("r2");
            register struct MetadataEntry *metadata asm("r3");

            type = record->type;
            call_value = record->value;
            metadata = (struct MetadataEntry *)0x087AFCC4;
            asm volatile("" : "+r"(metadata));
            metadata_value = type << 3;
            metadata_value -= type;
            metadata_value <<= 3;
            metadata_value += (s32)metadata;
            metadata_value = *(u8 *)(metadata_value + 2);
            func_080BAF2C(type,
                          call_value,
                          metadata_value,
                          0,
                          record->column,
                          0x10000,
                          row);
            flag_right = 0x02032EEC;
            asm volatile("" : "+r"(flag_right));
            flag_left = (s32)*source_slot;
            flag_left = ((struct InputRecord *)flag_left)->column;
        } else {
            register u32 type asm("r0");
            register u32 call_value asm("r1");
            register s32 metadata_value asm("r2");
            register struct MetadataEntry *metadata asm("r3");

            type = record->type;
            call_value = record->value;
            metadata = (struct MetadataEntry *)0x087AFCC4;
            asm volatile("" : "+r"(metadata));
            metadata_value = type << 3;
            metadata_value -= type;
            metadata_value <<= 3;
            metadata_value += (s32)metadata;
            metadata_value = *(u8 *)(metadata_value + 2);
            func_080BAF2C(type,
                          call_value,
                          metadata_value,
                          1,
                          record->column,
                          -0x10000,
                          0);
            flag_left = 0x02032EEC;
            asm volatile("" : "+r"(flag_left));
            flag_right = (s32)*source_slot;
            flag_left += 6;
            flag_right = ((struct InputRecord *)flag_right)->column;
        }
        flag_left += flag_right;
        *(u8 *)flag_left = mode;
        break;
    }
    }

    {
        register u8 *grid asm("r4");

        grid = (u8 *)0x02034B4C;
        {
            register struct InputRecord *current asm("r3");
            register s32 column asm("r0");
            register s32 offset asm("r1");
            register s32 row asm("r2");
            register s32 row_offset asm("r0");
            register s32 value asm("r0");

            current = *source_slot;
            column = current->column;
            offset = column << 2;
            offset += column;
            offset <<= 3;
            offset -= column;
            offset <<= 4;
            row = current->row;
            row_offset = row << 2;
            row_offset += row;
            row_offset <<= 3;
            row_offset -= row;
            row_offset <<= 7;
            offset += row_offset;
            offset += (s32)grid;
            value = current->type;
            mode = 0;
            *(u8 *)offset = value;
        }
        {
            register struct InputRecord *current asm("r3");
            register s32 column asm("r0");
            register s32 offset asm("r1");
            register s32 row asm("r2");
            register s32 row_offset asm("r0");
            register s32 value asm("r0");

            current = *source_slot;
            column = current->column;
            offset = column << 2;
            offset += column;
            offset <<= 3;
            offset -= column;
            offset <<= 4;
            row = current->row;
            row_offset = row << 2;
            row_offset += row;
            row_offset <<= 3;
            row_offset -= row;
            row_offset <<= 7;
            offset += row_offset;
            offset += (s32)grid;
            value = current->value;
            *(u8 *)(offset + 1) = value;
        }
        {
            register struct InputRecord *current asm("r2");
            register s32 column asm("r0");
            register s32 offset asm("r1");
            register s32 row asm("r2");
            register s32 row_offset asm("r0");

            current = *source_slot;
            column = current->column;
            offset = column << 2;
            offset += column;
            offset <<= 3;
            offset -= column;
            offset <<= 4;
            row = current->row;
            row_offset = row << 2;
            row_offset += row;
            row_offset <<= 3;
            row_offset -= row;
            row_offset <<= 7;
            offset += row_offset;
            offset += (s32)grid;
            *(u16 *)(offset + 4) = mode;
        }
    }

    {
        register s32 minus_one asm("r1");

        minus_one = -1;
        func_080A016C(saved_arg0, minus_one, 0);
    }
    return 0;
}
