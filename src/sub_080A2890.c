#include "m2c_prelude.h"

struct InputRecord {
    u8 pad0;
    u8 key;
    u8 row;
    u8 column;
    u8 mode;
};

struct LookupEntry {
    u8 key;
    u8 entity_index;
    u8 pad02[62];
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

s32 sub_080A2890(s32 arg0, struct InputRecord **arg1) {
    register struct InputRecord *volatile *source_slot asm("r6");
    register u32 saved_arg0 asm("r9");
    register struct LookupEntry *matched_entry asm("r8");
    u32 index;
    struct LookupEntry *lookup_base;
    s32 lookup_offset;

    source_slot = arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    index = 1;
    lookup_base = (struct LookupEntry *)0x02027378;
    lookup_offset = 0x40;
    goto scan_entry;

scan_next:
    index++;
    if (index > 0x34) {
        goto done;
    }
    lookup_offset = index << 6;

scan_entry:
    lookup_offset += (s32)lookup_base;
    matched_entry = (struct LookupEntry *)lookup_offset;
    if (matched_entry->key != (*source_slot)->key) {
        goto scan_next;
    }
    if (index > 0x34) {
        goto done;
    }
    {
        register struct LookupEntry *entry_check asm("r1");
        register s32 entity_check asm("r0");

        entry_check = matched_entry;
        asm volatile("" : "+r"(entry_check));
        entity_check = entry_check->entity_index;
        if (entity_check == 0) {
            goto done;
        }
    }

    {
        register struct InputRecord *record asm("r4");
        register s32 mode asm("r5");

        record = *source_slot;
        mode = record->mode;
        switch (mode) {
        case 0: {
            register struct EntityRecord *entity_base asm("r2");
            register struct LookupEntry *entry asm("r1");
            register s32 entity_index asm("r0");
            register s32 entity_address asm("r1");
            register u32 type asm("r0");
            register u32 call_value asm("r1");
            register s32 metadata_value asm("r2");
            register u8 *metadata asm("r3");

            entity_base = (struct EntityRecord *)0x020218E4;
            asm volatile("" : "+r"(entity_base));
            entry = matched_entry;
            entity_index = entry->entity_index;
            entity_address = entity_index << 3;
            entity_address -= entity_index;
            entity_address <<= 4;
            entity_address += (s32)entity_base;
            type = ((struct EntityRecord *)entity_address)->type;
            call_value = ((struct EntityRecord *)entity_address)->value;
            metadata = (u8 *)0x087AFCC4;
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
            s32 row;
            register s32 flag_left asm("r0");
            register s32 flag_right asm("r1");

            row = record->row;
            if (row == 0) {
                register struct EntityRecord *entity_base asm("r2");
                register struct LookupEntry *entry asm("r1");
                register s32 entity_index asm("r0");
                register s32 entity_address asm("r1");
                register u32 type asm("r0");
                register u32 call_value asm("r1");
                register s32 metadata_value asm("r2");
                register u8 *metadata asm("r3");

                asm volatile("" : "+r"(row));
                entity_base = (struct EntityRecord *)0x020218E4;
                asm volatile("" : "+r"(entity_base));
                entry = matched_entry;
                entity_index = entry->entity_index;
                entity_address = entity_index << 3;
                entity_address -= entity_index;
                entity_address <<= 4;
                entity_address += (s32)entity_base;
                type = ((struct EntityRecord *)entity_address)->type;
                call_value = ((struct EntityRecord *)entity_address)->value;
                metadata = (u8 *)0x087AFCC4;
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
                register struct EntityRecord *entity_base asm("r2");
                register struct LookupEntry *entry asm("r1");
                register s32 entity_index asm("r0");
                register s32 entity_address asm("r1");
                register u32 type asm("r0");
                register u32 call_value asm("r1");
                register s32 metadata_value asm("r2");
                register u8 *metadata asm("r3");

                entity_base = (struct EntityRecord *)0x020218E4;
                asm volatile("" : "+r"(entity_base));
                entry = matched_entry;
                entity_index = entry->entity_index;
                entity_address = entity_index << 3;
                entity_address -= entity_index;
                entity_address <<= 4;
                entity_address += (s32)entity_base;
                type = ((struct EntityRecord *)entity_address)->type;
                call_value = ((struct EntityRecord *)entity_address)->value;
                metadata = (u8 *)0x087AFCC4;
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
            register u8 *grid asm("r3");
            register struct EntityRecord *entity_base asm("r4");

            grid = (u8 *)0x02034B4C;
            {
                register struct InputRecord *current asm("r2");
                register s32 column asm("r0");
                register s32 offset asm("r1");
                register s32 row_value asm("r2");
                register s32 row_offset asm("r0");
                register struct LookupEntry *entry asm("r0");
                register s32 entity_index asm("r2");
                register s32 entity_offset asm("r0");
                register s32 value asm("r0");

                current = *source_slot;
                column = current->column;
                offset = column << 2;
                offset += column;
                offset <<= 3;
                offset -= column;
                offset <<= 4;
                row_value = current->row;
                row_offset = row_value << 2;
                row_offset += row_value;
                row_offset <<= 3;
                row_offset -= row_value;
                row_offset <<= 7;
                offset += row_offset;
                offset += (s32)grid;
                entity_base = (struct EntityRecord *)0x020218E4;
                entry = matched_entry;
                entity_index = entry->entity_index;
                entity_offset = entity_index << 3;
                entity_offset -= entity_index;
                entity_offset <<= 4;
                entity_offset += (s32)entity_base;
                value = ((struct EntityRecord *)entity_offset)->type;
                mode = 0;
                *(u8 *)offset = value;
            }
            {
                register struct InputRecord *current asm("r2");
                register s32 column asm("r0");
                register s32 offset asm("r1");
                register s32 row_value asm("r2");
                register s32 row_offset asm("r0");
                register struct LookupEntry *entry asm("r0");
                register s32 entity_index asm("r2");
                register s32 entity_offset asm("r0");
                register s32 value asm("r0");

                current = *source_slot;
                column = current->column;
                offset = column << 2;
                offset += column;
                offset <<= 3;
                offset -= column;
                offset <<= 4;
                row_value = current->row;
                row_offset = row_value << 2;
                row_offset += row_value;
                row_offset <<= 3;
                row_offset -= row_value;
                row_offset <<= 7;
                offset += row_offset;
                offset += (s32)grid;
                entry = matched_entry;
                entity_index = entry->entity_index;
                entity_offset = entity_index << 3;
                entity_offset -= entity_index;
                entity_offset <<= 4;
                entity_offset += (s32)entity_base;
                value = ((struct EntityRecord *)entity_offset)->value;
                *(u8 *)(offset + 1) = value;
            }
            {
                register struct InputRecord *current asm("r2");
                register s32 column asm("r0");
                register s32 offset asm("r1");
                register s32 row_value asm("r2");
                register s32 row_offset asm("r0");

                current = *source_slot;
                column = current->column;
                offset = column << 2;
                offset += column;
                offset <<= 3;
                offset -= column;
                offset <<= 4;
                row_value = current->row;
                row_offset = row_value << 2;
                row_offset += row_value;
                row_offset <<= 3;
                row_offset -= row_value;
                row_offset <<= 7;
                offset += row_offset;
                offset += (s32)grid;
                *(u16 *)(offset + 4) = mode;
            }
        }
    }

done:
    {
        register s32 minus_one asm("r1");

        minus_one = -1;
        func_080A016C(saved_arg0, minus_one, 0);
    }
    return 0;
}
