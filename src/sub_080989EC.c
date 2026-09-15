#include "m2c_prelude.h"

typedef struct {
    u32 flags;
    u16 unk4;
    u16 unk6;
    u16 count;
    u16 span;
    u16 saved_c;
    u16 saved_e;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unit;
    u8 start;
} Record;

extern u8 D_0200DE90[];
extern u8 D_0200E6CE[];
extern Record *func_0809716C(s32 unit);
extern void func_08097DA8(Record *record, void *data);
extern u8 func_08098B58(void *data);

void sub_080989EC(s32 unit, s32 row, u8 *stream)
{
    register s32 unit_saved asm("r12");
    s32 row_saved;
    register u8 *stream_ptr asm("r2");
    register s32 index asm("r5");
    register u8 value asm("r3");
    register u8 *grid_base asm("r10");
    register u8 *row_base asm("r9");

    {
        register s32 unit_input asm("r0") = unit;

        asm volatile("lsl %0, %0, #24\n\tlsr %0, %0, #24"
                     : "+r"(unit_input));
        unit_saved = unit_input;
    }
    row_saved = (u8)row;
    stream_ptr = stream;
    index = 0;
    value = *stream_ptr;
    grid_base = D_0200E6CE;
    row_base = D_0200DE90;

    if ((u32)index < (u32)value) {
        register u8 *grid asm("r8") = grid_base;
        register u8 *row_data asm("r6");
        register s32 grid_offset asm("r4");
        register s32 row_offset asm("r0");
        register u8 *row_base_copy asm("r1");

        row_offset = unit_saved * 0xD2;
        asm volatile("add %0, %1, %0"
                     : "+r"(row_offset)
                     : "r"(row_saved));
        row_base_copy = row_base;
        asm volatile("" : "+r"(row_base_copy));
        asm volatile("add %0, %1, %2"
                     : "=r"(row_data)
                     : "r"(row_offset), "r"(row_base_copy));
        grid_offset = unit_saved * 0x1E5A;
        do {
            s32 condition;
            register s32 destination asm("r0");

            destination = row_data[0] * 0x25;
            asm volatile("add %0, %1, %0"
                         : "+r"(destination)
                         : "r"(index));
            destination += grid_offset;
            destination += (s32)grid;
            *(u8 *)destination = value;
            condition = *stream_ptr;
            if (condition <= 3) {
                asm volatile("cmp %0, #2\n\tbge 1f"
                             :
                             : "r"(condition)
                             : "cc");
                if (condition == 1) {
                    register s32 destination asm("r0");

                    stream_ptr++;
                    {
                        register s32 next_index asm("r0") = index + 1;

                        asm volatile("" : "+r"(next_index));
                        index = (u8)next_index;
                    }
                    destination = row_data[0] * 0x25;
                    asm volatile("add %0, %1, %0"
                                 : "+r"(destination)
                                 : "r"(index));
                    destination += grid_offset;
                    destination += (s32)grid;
                    *(u8 *)destination = *stream_ptr;
                }
                asm volatile("1:");
            }
            stream_ptr++;
            {
                register s32 next_index asm("r0") = index + 1;

                asm volatile("" : "+r"(next_index));
                index = (u8)next_index;
            }
            value = *stream_ptr;
        } while ((u32)index < (u32)value);
    }

    {
        register s32 zero asm("r8");
        register s32 row_stride asm("r6");
        s32 grid_stride;
        register s32 destination asm("r0");

        row_stride = 0xD2;
        destination = unit_saved * row_stride;
        asm volatile("add %0, %1, %0"
                     : "+r"(destination)
                     : "r"(row_saved));
        destination += (s32)row_base;
        destination = *(u8 *)destination * 0x25;
        asm volatile("add %0, %1, %0"
                     : "+r"(destination)
                     : "r"(index));
        grid_stride = 0x1E5A;
        destination += unit_saved * grid_stride;
        destination += (s32)grid_base;
        zero = 0;
        *(u8 *)destination = zero;

        {
            register Record *record asm("r4") = func_0809716C(unit_saved);

            if ((u32)row_saved >= (u32)record->start) {
                u8 start = record->start;
                u32 half_span = record->span - 2;

                if ((s32)row_saved < (s32)(start + ((s32)(half_span + (half_span >> 31)) >> 1))) {
                    u32 homes[2];
                    u8 result;

                    {
                        register u32 saved_c asm("r1") = record->saved_c;

                        asm volatile("" : "+r"(saved_c));
                        homes[0] = saved_c;
                    }
                    {
                        register u32 saved_e asm("r0") = record->saved_e;

                        asm volatile("" : "+r"(saved_e));
                        homes[1] = saved_e;
                    }
                    {
                        register s32 zero_copy asm("r1") = zero;

                        asm volatile("" : "+r"(zero_copy));
                        record->saved_c = zero_copy;
                    }
                    record->saved_e = (row_saved - start) * 2;
                    {
                        register s32 row_address asm("r0") = record->unit;
                        register s32 grid_address asm("r1") = row_address;
                        register s32 tile asm("r2");

                        asm volatile("" : "+r"(row_address), "+r"(grid_address));
                        grid_address *= grid_stride;
                        row_address *= row_stride;
                        asm volatile("add %0, %1, %0"
                                     : "+r"(row_address)
                                     : "r"(row_saved));
                        row_address += (s32)row_base;
                        tile = *(u8 *)row_address;
                        row_address = tile * 0x25;
                        row_address += (s32)grid_base;
                        grid_address += row_address;
                        func_08097DA8(record, (void *)grid_address);
                    }
                    {
                        register s32 row_address asm("r1") = record->unit;
                        register s32 grid_address asm("r0") = row_address;
                        register s32 tile asm("r2");

                        asm volatile("" : "+r"(row_address), "+r"(grid_address));
                        grid_address *= grid_stride;
                        row_address *= row_stride;
                        asm volatile("add %0, %1, %0"
                                     : "+r"(row_address)
                                     : "r"(row_saved));
                        row_address += (s32)row_base;
                        tile = *(u8 *)row_address;
                        row_address = tile * 0x25;
                        row_address += (s32)grid_base;
                        grid_address += row_address;
                        result = func_08098B58((void *)grid_address);
                    }
                    while ((s32)result < (s32)(record->count - 2)) {
                        func_08097DA8(record, (void *)0x080ED940);
                        result++;
                    }
                    {
                        register u16 restored_c asm("r0");

                        asm volatile("mov %0, sp\n\t"
                                     "ldrh %0, [%0, #0]"
                                     : "=r"(restored_c)
                                     : "m"(homes[0]));
                        record->saved_c = restored_c;
                    }
                    {
                        register u16 restored_e asm("r1");

                        asm volatile("mov %0, sp\n\t"
                                     "ldrh %0, [%0, #4]"
                                     : "=r"(restored_e)
                                     : "m"(homes[1]));
                        record->saved_e = restored_e;
                    }
                    record->flags |= 2;
                }
            }
        }
    }
}
