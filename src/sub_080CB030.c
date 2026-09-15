#include "m2c_prelude.h"

extern u8 func_080CA570(u32, u32);

void sub_080CB030(void)
{
    register s32 maximum asm("r8");
    register u32 outer asm("r5");

    maximum = 0;
    outer = 0;
    {
        register u8 *count_load asm("r0");
        register u32 count asm("r1");

        count_load = (u8 *)0x0203EFA8;
        count = *count_load;
        if (outer < count) {
            u8 *counts;
            register u8 *row_slot asm("ip");
            register u8 *entry_table asm("r9");
            register u32 saved_count asm("sl");

            counts = (u8 *)0x0203EFA9;
            row_slot = (u8 *)0x0203ECFB;
            entry_table = (u8 *)0x0203EF78;
            saved_count = count;
            do {
                register u32 inner asm("r4");
                register u32 next_outer asm("r6");
                register u8 *cslot asm("r0");
                register u32 climit asm("r0");

                inner = 0;
                cslot = (u8 *)(outer + (s32)counts);
                next_outer = outer + 1;
                climit = *cslot;
                if (inner < climit) {
                    register u8 *indices asm("r1");
                    register u8 *islot asm("r0");
                    register s32 record_index asm("r1");
                    register s32 record_stride asm("r0");
                    register s32 record_offset asm("r2");
                    register u32 row asm("r1");
                    register s32 row_offset asm("r0");
                    register u8 *row_base asm("r1");
                    register u8 *record asm("r3");

                    indices = (u8 *)0x0203EF70;
                    asm volatile("" : "+r"(indices));
                    islot = (u8 *)(outer + (s32)indices);
                    record_index = *islot;
                    asm volatile("" : "+r"(record_index));
                    record_stride = 0xA8C;
                    record_offset = record_index;
                    record_offset *= record_stride;
                    row = *row_slot;
                    row_offset = row << 3;
                    row_offset -= row;
                    row_offset <<= 5;
                    row_offset += row;
                    row_offset <<= 2;
                    row_base = (u8 *)0x02037314;
                    row_offset += (s32)row_base;
                    record = (u8 *)(record_offset + row_offset);
inner_loop1:
                    {
                        register u32 entry_offset asm("r0");
                        register u32 entry_index asm("r1");
                        register s32 field_offset asm("r0");
                        register u8 *field asm("r2");
                        register s32 value asm("r2");
                        register u32 next asm("r0");

                        asm volatile("" : "+r"(outer));
                        entry_offset = outer << 1;
                        entry_offset += outer;
                        entry_offset <<= 1;
                        entry_offset = inner + entry_offset;
                        entry_offset += (u32)entry_table;
                        entry_index = *(u8 *)entry_offset;
                        field_offset = 0x94;
                        field_offset *= entry_index;
                        field_offset += 12;
                        field = record + field_offset;
                        value = *field;
                        if (maximum < value) {
                            maximum = value;
                        }
                        asm volatile("" : "+r"(counts));
                        next = inner + 1;
                        inner = (u8)next;
                        if (inner < *(u8 *)(outer + (s32)counts)) {
                            goto inner_loop1;
                        }
                    }
                }
                {
                    register u32 t asm("r0");
                    t = next_outer << 24;
                    outer = t >> 24;
                }
            } while (outer < saved_count);
        }
    }

    outer = 0;
    goto outer_test;
outer_loop:
    {
        register u32 inner asm("r4");
        register u8 *counts asm("r3");
        register u8 *cload asm("r0");
        register u8 *cslot asm("r1");
        register u32 climit asm("r1");

        inner = 0;
        cload = (u8 *)0x0203EFA9;
        asm volatile("" : "+r"(cload));
        cslot = (u8 *)(outer + (s32)cload);
        counts = cload;
        climit = *cslot;
        if (inner < climit) {
            register u8 *base asm("r6");
            register u8 *record_base asm("r9");
            u8 *entry_table;

            base = (u8 *)0x02034B4C;
            {
                register s32 rb asm("r1");
                rb = 0x27C8;
                asm volatile("" : "+r"(rb));
                rb += (s32)base;
                record_base = (u8 *)rb;
            }
            entry_table = (u8 *)0x0203EF78;
inner_loop:
            {
                register u8 *index_table asm("r0");
                register s32 record_index asm("r1");
                register s32 record_stride asm("r0");
                register s32 record_offset asm("r2");
                register s32 row_off asm("r1");
                register u8 *row_slot2 asm("r0");
                register u32 row asm("r1");
                register s32 row_offset asm("r0");
                register u32 entry_offset asm("r0");
                register u32 entry_index asm("r1");
                register s32 field_offset asm("r0");
                register u32 value asm("r0");

                asm volatile("" : "+r"(outer));
                index_table = (u8 *)0x0203EF70;
                asm volatile("" : "+r"(index_table));
                index_table = (u8 *)(outer + (s32)index_table);
                record_index = *index_table;
                asm volatile("" : "+r"(record_index));
                record_stride = 0xA8C;
                record_offset = record_index;
                record_offset *= record_stride;
                row_off = 0xA1AF;
                asm volatile("" : "+r"(row_off));
                row_slot2 = base + row_off;
                row = *row_slot2;
                row_offset = row << 3;
                row_offset -= row;
                row_offset <<= 5;
                row_offset += row;
                row_offset <<= 2;
                row_offset += (s32)record_base;
                record_offset += row_offset;
                entry_offset = outer << 1;
                entry_offset += outer;
                entry_offset <<= 1;
                entry_offset = inner + entry_offset;
                entry_offset += (u32)entry_table;
                entry_index = *(u8 *)entry_offset;
                field_offset = 0x94;
                field_offset *= entry_index;
                field_offset += 12;
                record_offset += field_offset;
                value = *(u8 *)record_offset;
                if (value != maximum) {
                    if (func_080CA570(outer, inner) == 0) {
                        register u32 t asm("r0");
                        t = outer - 1;
                        t <<= 24;
                        outer = t >> 24;
                        goto outer_next;
                    }
                    {
                        register u32 t2 asm("r0");
                        t2 = inner - 1;
                        t2 <<= 24;
                        inner = t2 >> 24;
                    }
                    counts = (u8 *)0x0203EFA9;
                }
                {
                    register u32 t3 asm("r0");
                    t3 = inner + 1;
                    t3 <<= 24;
                    inner = t3 >> 24;
                }
                if (inner < *(u8 *)(outer + (s32)counts)) {
                    goto inner_loop;
                }
            }
        }
    }
outer_next:
    {
        register u32 t4 asm("r0");
        t4 = outer + 1;
        t4 <<= 24;
        outer = t4 >> 24;
    }
outer_test:
    if (outer < *(u8 *)0x0203EFA8) {
        goto outer_loop;
    }
}
