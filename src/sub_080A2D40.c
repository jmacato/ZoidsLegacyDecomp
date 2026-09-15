#include "m2c_prelude.h"

struct InputRecord {
    u8 pad0;
    u8 mode;
    u8 pad2;
    u8 row;
};

struct EntityRecord {
    u8 pad00[4];
    u8 type;
    u8 value;
    u8 pad06[2];
    u16 flags;
    u8 pad0A[0x32];
    u8 metadata;
    u8 pad3D[0x33];
};

void func_080BAF2C(s32, s32, s32, s32, s32, s32, s32);
void func_080A016C(s32, s32, s32);

s32 sub_080A2D40(s32 arg0, struct InputRecord **arg1) {
    struct InputRecord **source_slot;
    volatile s32 saved_arg0;
    u32 outer;
    register u32 next_outer asm("r10");

    source_slot = arg1;
    arg0 <<= 24;
    saved_arg0 = (u32)arg0 >> 24;
    outer = 0;
outer_loop:
    {
        register u8 *outer_table asm("r0");
        register u32 active asm("r0");
        register u32 next_value asm("r1");

        outer_table = (u8 *)0x087A18E0;
        asm volatile("" : "+r"(outer_table));
        active = *(u8 *)(outer + (s32)outer_table);
        next_value = outer + 1;
        asm volatile("" : "+r"(next_value));
        next_outer = next_value;
        if (active != 0) {
            u32 scan_index;
            register struct EntityRecord *records asm("r4");
            register s32 zero asm("r9");
            register u8 *grid asm("r8");
            s32 record_offset;

            scan_index = 0;
            records = (struct EntityRecord *)0x020218E4;
            zero = 0;
            grid = (u8 *)0x02034B4C;
            record_offset = 0;
inner_loop:
            {
                register struct EntityRecord *current asm("r2");

                current = (struct EntityRecord *)
                    (record_offset + (s32)records);
                if (current->type == ((u8 *)0x087A18E0)[outer] &&
                    (current->flags & 0x10) != 0) {
                    s32 mode;

                    mode = (*source_slot)->mode;
                    switch (mode) {
                    case 0:
                        func_080BAF2C(current->type,
                                      current->value,
                                      current->metadata,
                                      0,
                                      outer,
                                      mode,
                                      mode);
                        break;
                    case 1:
                        func_080BAF2C(current->type,
                                      current->value,
                                      current->metadata,
                                      0,
                                      outer,
                                      0x10000,
                                      zero);
                        {
                            register u8 *marker asm("r0");

                            marker = (u8 *)0x02032EEC;
                            asm volatile("" : "+r"(marker));
                            marker = (u8 *)(outer + (s32)marker);
                            *marker = mode;
                        }
                        break;
                    }

                    {
                        register s32 column_offset asm("r2");
                        register struct InputRecord *input asm("r0");
                        register s32 row asm("r1");
                        register s32 row_offset asm("r0");
                        register s32 address asm("r0");
                        register struct EntityRecord *matched asm("r3");
                        register s32 value asm("r1");

                        column_offset = outer << 2;
                        column_offset += outer;
                        column_offset <<= 3;
                        column_offset -= outer;
                        column_offset <<= 4;
                        input = *source_slot;
                        row = input->row;
                        row_offset = row << 2;
                        row_offset += row;
                        row_offset <<= 3;
                        row_offset -= row;
                        row_offset <<= 7;
                        address = column_offset + row_offset;
                        address += (s32)grid;
                        matched = (struct EntityRecord *)0x020218E4;
                        asm volatile("" : "+r"(matched));
                        matched = (struct EntityRecord *)
                            (record_offset + (s32)matched);
                        value = matched->type;
                        *(u8 *)address = value;

                        input = *source_slot;
                        row = input->row;
                        row_offset = row << 2;
                        row_offset += row;
                        row_offset <<= 3;
                        row_offset -= row;
                        row_offset <<= 7;
                        address = column_offset + row_offset;
                        address += (s32)grid;
                        value = matched->value;
                        *(u8 *)(address + 1) = value;

                        input = *source_slot;
                        row = input->row;
                        row_offset = row << 2;
                        row_offset += row;
                        row_offset <<= 3;
                        row_offset -= row;
                        row_offset <<= 7;
                        column_offset += row_offset;
                        column_offset += (s32)grid;
                        {
                            register s32 zero_value asm("r0");

                            zero_value = zero;
                            *(u16 *)(column_offset + 4) = zero_value;
                        }
                    }
                    goto outer_continue;
                }
            }
            record_offset += 0x70;
            scan_index++;
            if (scan_index <= 0xCE) {
                goto inner_loop;
            }
        }
    }
outer_continue:
    outer = next_outer;
    if (outer <= 5) {
        goto outer_loop;
    }
    func_080A016C(saved_arg0, -1, 0);
    return 0;
}
