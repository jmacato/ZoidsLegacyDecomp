#include "m2c_prelude.h"

struct InputRecord {
    u8 pad0;
    u8 table_row;
    u8 table_column;
    u8 row;
    u8 mode;
};

struct LookupRecord {
    u8 pad0[4];
    u8 type;
    u8 value;
};

void func_080BAF2C(s32, s32, s32, s32, s32, s32, s32);
void func_080A016C(s32, s32, s32);

s32 sub_080A2BB0(s32 arg0, struct InputRecord **arg1) {
    struct InputRecord **source_slot;
    volatile s32 saved_arg0;
    u32 outer;
    register u8 *lookup_base asm("r4");
    register s32 column_offset asm("r9");
    register s32 entry_offset asm("r8");
    register u8 *grid asm("r10");
    register u8 *grid_init asm("r0");

    source_slot = arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    outer = 0;
    asm volatile("" : "+r"(outer));
    lookup_base = (u8 *)0x087B9454;
    column_offset = outer;
    entry_offset = outer;
    grid_init = (u8 *)0x02034B4C;
    asm volatile("" : "+r"(grid_init));
    grid = grid_init;

slot_loop:
    {
        register struct InputRecord *input asm("r3");
        register s32 table_column asm("r0");
        register s32 hundred asm("r1");
        register s32 address asm("r2");
        register s32 table_row asm("r1");
        register s32 row_offset asm("r0");
        register struct LookupRecord *entry asm("r2");
        register s32 active asm("r0");

        input = *source_slot;
        table_column = input->table_column;
        asm volatile("" : "+r"(table_column));
        hundred = 100;
        address = table_column;
        address *= hundred;
        address += entry_offset;
        table_row = input->table_row;
        row_offset = table_row << 5;
        row_offset -= table_row;
        row_offset <<= 2;
        row_offset += table_row;
        row_offset <<= 4;
        address += row_offset;
        address += (s32)lookup_base;
        entry = (struct LookupRecord *)address;
        active = entry->type;
        if (active == 0) {
            goto next_slot;
        }

        {
            register s32 mode asm("r5");

            mode = input->mode;
            switch (mode) {
            case 0: {
                register s32 type asm("r0");
                register s32 value asm("r1");
                register s32 metadata asm("r2");
                register u8 *metadata_base asm("r4");
                register s32 row asm("r3");

                type = entry->type;
                value = entry->value;
                metadata = type << 3;
                metadata -= type;
                metadata <<= 3;
                metadata_base = (u8 *)0x087AFCC4;
                asm volatile("" : "+r"(metadata_base));
                metadata += (s32)metadata_base;
                metadata = *(u8 *)(metadata + 2);
                row = input->row;
                func_080BAF2C(type,
                              value,
                              metadata,
                              row,
                              outer,
                              mode,
                              mode);
                break;
            }
            case 1: {
                s32 marker_address;
                register s32 row asm("r4");

                row = input->row;
                if (row == 0) {
                    register s32 type asm("r0");
                    register s32 value asm("r1");
                    register s32 metadata asm("r2");
                    register u8 *metadata_base asm("r3");

                    type = entry->type;
                    value = entry->value;
                    metadata = type << 3;
                    metadata -= type;
                    metadata <<= 3;
                    metadata_base = (u8 *)0x087AFCC4;
                    asm volatile("" : "+r"(metadata_base));
                    metadata += (s32)metadata_base;
                    metadata = *(u8 *)(metadata + 2);
                    func_080BAF2C(type,
                                  value,
                                  metadata,
                                  0,
                                  outer,
                                  0x10000,
                                  row);
                    {
                        register s32 marker_zero asm("r0");

                        marker_zero = 0x02032EEC;
                        asm volatile("" : "+r"(marker_zero));
                        marker_address = outer + marker_zero;
                    }
                } else {
                    register s32 type asm("r0");
                    register s32 value asm("r1");
                    register s32 metadata asm("r2");
                    register u8 *metadata_base asm("r4");

                    type = entry->type;
                    value = entry->value;
                    metadata = type << 3;
                    metadata -= type;
                    metadata <<= 3;
                    metadata_base = (u8 *)0x087AFCC4;
                    asm volatile("" : "+r"(metadata_base));
                    metadata += (s32)metadata_base;
                    metadata = *(u8 *)(metadata + 2);
                    func_080BAF2C(type,
                                  value,
                                  metadata,
                                  1,
                                  outer,
                                  -0x10000,
                                  0);
                    {
                        register s32 marker_nonzero asm("r4");

                        marker_nonzero = 0x02032EF2;
                        asm volatile("" : "+r"(marker_nonzero));
                        marker_address = outer + marker_nonzero;
                    }
                }
                *(u8 *)marker_address = mode;
                break;
            }
            }
        }

        {
            register s32 hundred asm("r4");

            {
                register struct InputRecord *current asm("r2");
                register s32 row asm("r0");
                register s32 destination asm("r3");
                register s32 table_column asm("r0");
                register s32 source_address asm("r1");
                register s32 table_row asm("r2");
                register s32 row_offset asm("r0");
                register u8 *base asm("r0");
                register s32 value asm("r0");

                current = *source_slot;
                row = current->row;
                destination = row << 2;
                destination += row;
                destination <<= 3;
                destination -= row;
                destination <<= 7;
                destination += column_offset;
                destination += (s32)grid;
                table_column = current->table_column;
                asm volatile("" : "+r"(table_column));
                hundred = 100;
                source_address = table_column;
                source_address *= hundred;
                source_address += entry_offset;
                table_row = current->table_row;
                row_offset = table_row << 5;
                row_offset -= table_row;
                row_offset <<= 2;
                row_offset += table_row;
                row_offset <<= 4;
                source_address += row_offset;
                base = (u8 *)0x087B9454;
                asm volatile("" : "+r"(base));
                source_address += (s32)base;
                value = ((struct LookupRecord *)source_address)->type;
                *(u8 *)destination = value;
            }
            {
                register struct InputRecord *current asm("r2");
                register s32 row asm("r0");
                register s32 destination asm("r3");
                register s32 table_column asm("r0");
                register s32 source_address asm("r1");
                register s32 table_row asm("r2");
                register s32 row_offset asm("r0");
                register u8 *base asm("r4");
                register s32 value asm("r0");

                current = *source_slot;
                row = current->row;
                destination = row << 2;
                destination += row;
                destination <<= 3;
                destination -= row;
                destination <<= 7;
                destination += column_offset;
                destination += (s32)grid;
                table_column = current->table_column;
                asm volatile("" : "+r"(table_column));
                source_address = table_column;
                source_address *= hundred;
                source_address += entry_offset;
                table_row = current->table_row;
                row_offset = table_row << 5;
                row_offset -= table_row;
                row_offset <<= 2;
                row_offset += table_row;
                row_offset <<= 4;
                source_address += row_offset;
                base = (u8 *)0x087B9454;
                asm volatile("" : "+r"(base));
                source_address += (s32)base;
                value = ((struct LookupRecord *)source_address)->value;
                *(u8 *)(destination + 1) = value;
            }
        }
        {
            register struct InputRecord *current asm("r0");
            register s32 row asm("r1");
            register s32 destination asm("r0");
            register s32 zero asm("r1");

            current = *source_slot;
            row = current->row;
            destination = row << 2;
            destination += row;
            destination <<= 3;
            destination -= row;
            destination <<= 7;
            destination += column_offset;
            destination += (s32)grid;
            zero = 0;
            *(u16 *)(destination + 4) = zero;
        }
    }

next_slot:
    {
        register s32 column_increment asm("r3");
        register s32 entry_increment asm("r0");

        column_increment = 0x9C;
        column_increment <<= 2;
        asm volatile("" : "+r"(column_increment));
        column_offset += column_increment;
        entry_increment = 0x10;
        entry_offset += entry_increment;
    }
    outer++;
    if (outer <= 5) {
        goto slot_loop;
    }

    func_080A016C(saved_arg0, -1, 0);
    return 0;
}
