#include "m2c_prelude.h"

struct InputRecord {
    u8 pad0;
    u8 row;
    u8 mode;
};

struct EntityRecord {
    u8 pad00[4];
    u8 type;
    u8 value;
    u8 pad06[0x36];
    u8 metadata;
    u8 pad3D[0x33];
};

void func_080BAF2C(s32, s32, s32, s32, s32, s32, s32);
void func_080A016C(s32, s32, s32);

s32 sub_080A2A58(s32 arg0, struct InputRecord **arg1) {
    struct InputRecord **source_slot;
    volatile s32 saved_arg0;
    u32 outer;
    register struct EntityRecord *entity_base asm("r8");
    register u8 *grid asm("r10");
    register s32 column_offset asm("r9");
    register u8 *grid_init asm("r1");

    source_slot = arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    outer = 0;
    entity_base = (struct EntityRecord *)0x020218E4;
    grid_init = (u8 *)0x02034B4C;
    asm volatile("" : "+r"(grid_init));
    grid = grid_init;
    asm volatile("" : "+r"(outer));
    column_offset = outer;

slot_loop:
    {
        register s32 index_offset asm("r0");
        register u8 *index_ptr asm("r1");
        register s32 entity_id asm("r0");

        index_offset = 0x690C;
        index_offset += (s32)entity_base;
        index_ptr = (u8 *)(outer + index_offset);
        entity_id = *index_ptr;
        if (entity_id == 0) {
            goto next_slot;
        }
        {
            register struct InputRecord *record asm("r3");
            register s32 mode asm("r5");

            record = *source_slot;
            mode = record->mode;
            switch (mode) {
            case 0: {
                register s32 entity_offset asm("r2");
                register struct EntityRecord *entity asm("r2");
                register s32 type asm("r0");
                register s32 value asm("r1");
                register s32 metadata asm("r2");

                entity_id = *index_ptr;
                entity_offset = entity_id << 3;
                entity_offset -= entity_id;
                entity_offset <<= 4;
                entity_offset += (s32)entity_base;
                entity = (struct EntityRecord *)entity_offset;
                type = entity->type;
                value = entity->value;
                entity = (struct EntityRecord *)((s32)entity + 0x3C);
                metadata = *(u8 *)entity;
                func_080BAF2C(type,
                              value,
                              metadata,
                              record->row,
                              outer,
                              mode,
                              mode);
                break;
            }
            case 1: {
                s32 row;
                s32 marker_address;

                row = record->row;
                if (row == 0) {
                    register s32 entity_offset asm("r2");
                    register struct EntityRecord *entity asm("r2");
                    register s32 type asm("r0");
                    register s32 value asm("r1");
                    register s32 metadata asm("r2");

                    entity_id = *index_ptr;
                    entity_offset = entity_id << 3;
                    entity_offset -= entity_id;
                    entity_offset <<= 4;
                    entity_offset += (s32)entity_base;
                    entity = (struct EntityRecord *)entity_offset;
                    type = entity->type;
                    value = entity->value;
                    entity = (struct EntityRecord *)((s32)entity + 0x3C);
                    metadata = *(u8 *)entity;
                    asm volatile("" : "+r"(row));
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
                    register s32 entity_offset asm("r2");
                    register struct EntityRecord *entity asm("r2");
                    register s32 type asm("r0");
                    register s32 value asm("r1");
                    register s32 metadata asm("r2");

                    entity_id = *index_ptr;
                    entity_offset = entity_id << 3;
                    entity_offset -= entity_id;
                    entity_offset <<= 4;
                    entity_offset += (s32)entity_base;
                    entity = (struct EntityRecord *)entity_offset;
                    type = entity->type;
                    value = entity->value;
                    entity = (struct EntityRecord *)((s32)entity + 0x3C);
                    metadata = *(u8 *)entity;
                    func_080BAF2C(type,
                                  value,
                                  metadata,
                                  1,
                                  outer,
                                  -0x10000,
                                  0);
                    {
                        register s32 marker_nonzero asm("r1");

                        marker_nonzero = 0x02032EF2;
                        asm volatile("" : "+r"(marker_nonzero));
                        marker_address = outer + marker_nonzero;
                    }
                }
                *(u8 *)marker_address = mode;
                break;
            }
            }

            {
                register u8 *id_ptr asm("r3");

                {
                    register struct InputRecord *input asm("r0");
                    register s32 row asm("r0");
                    register s32 address asm("r1");
                    register s32 id_base asm("r3");
                    register s32 id asm("r2");
                    register s32 entity_offset asm("r0");
                    register s32 value asm("r0");

                    input = *source_slot;
                    row = input->row;
                    address = row << 2;
                    address += row;
                    address <<= 3;
                    address -= row;
                    address <<= 7;
                    address += column_offset;
                    address += (s32)grid;
                    id_base = 0x690C;
                    id_base += (s32)entity_base;
                    id_ptr = (u8 *)(outer + id_base);
                    id = *id_ptr;
                    entity_offset = id << 3;
                    entity_offset -= id;
                    entity_offset <<= 4;
                    entity_offset += (s32)entity_base;
                    value = ((struct EntityRecord *)entity_offset)->type;
                    *(u8 *)address = value;
                }
                {
                    register struct InputRecord *input asm("r0");
                    register s32 row asm("r0");
                    register s32 address asm("r1");
                    register s32 id asm("r2");
                    register s32 entity_offset asm("r0");
                    register s32 value asm("r0");

                    input = *source_slot;
                    row = input->row;
                    address = row << 2;
                    address += row;
                    address <<= 3;
                    address -= row;
                    address <<= 7;
                    address += column_offset;
                    address += (s32)grid;
                    id = *id_ptr;
                    entity_offset = id << 3;
                    entity_offset -= id;
                    entity_offset <<= 4;
                    entity_offset += (s32)entity_base;
                    value = ((struct EntityRecord *)entity_offset)->value;
                    *(u8 *)(address + 1) = value;
                }
                {
                    register struct InputRecord *input asm("r0");
                    register s32 row asm("r1");
                    register s32 address asm("r0");
                    register s32 zero asm("r3");

                    input = *source_slot;
                    row = input->row;
                    address = row << 2;
                    address += row;
                    address <<= 3;
                    address -= row;
                    address <<= 7;
                    address += column_offset;
                    address += (s32)grid;
                    zero = 0;
                    *(u16 *)(address + 4) = zero;
                }
            }
        }
    }

next_slot:
    {
        register s32 increment asm("r0");

        increment = 0x9C;
        increment <<= 2;
        column_offset += increment;
    }
    outer++;
    if (outer <= 5) {
        goto slot_loop;
    }

    func_080A016C(saved_arg0, -1, 0);
    return 0;
}
