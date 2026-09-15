#include "m2c_prelude.h"

extern u8 D_02032272;
extern u8 D_020321A4[];
extern u8 D_020218E4[];
extern u8 D_020218E8[];

u8 func_080B6160(void *, s32);

void sub_080B61C8(u16 required, u16 excluded, s32 mode)
{
    register u16 excluded_r8 asm("r8") = excluded;
    s32 mode_sp;
    s16 first_count;
    register s32 reserve_r7 asm("r7");

    mode_sp = (u8)mode;
    asm volatile("" :: "r"(mode_sp));
    asm volatile("" : "=r"(reserve_r7));
    D_02032272 = 0;
    {
        register u8 *catalog asm("r9");
        register u8 *records asm("r10");
        s16 i;
        u8 *countp;

        i = 0;
        catalog = D_020218E4;
        records = catalog + 4;
        countp = &D_02032272;
        do {
            register s32 signed_i asm("r0");
            register u8 *entry_base asm("r1");
            register u8 *entry asm("r4");
            u8 index;
            register u32 record_offset asm("r0");
            u8 *record_base;
            register u8 *record asm("r6");
            u16 flags;
            u16 match;

            signed_i = (s16)i;
            entry_base = catalog + 0x690C;
            entry = (u8 *)((u32)signed_i + (u32)entry_base);
            index = *entry;
            record_offset = index * 7;
            record_offset <<= 4;
            record_base = records;
            record = (u8 *)(record_offset + (u32)record_base);
            asm volatile("" : "+r"(i));

            if (index != 0 &&
                (mode_sp == 0 || func_080B6160(record, mode_sp))) {
                flags = *(u16 *)(record + 4);
                match = required;
                match &= flags;
                if (match == required &&
                    (flags & excluded_r8) == 0) {
                    D_020321A4[*countp] = *entry;
                    (*countp)++;
                }
            }
            i++;
        } while (i <= 5);
    }

    {
        register u8 *count_base asm("r0") = &D_02032272;

        first_count = *count_base;
        {
            s16 i;
            register u8 *countp asm("r4");
            u32 next2;

            i = 1;
            countp = count_base;
            do {
                register u32 i_shift_low asm("r2");
                register u32 i_shift asm("r10");
                register s32 signed_i2 asm("r1");
                register u32 record_offset2 asm("r0");
                register u8 *record_base2 asm("r1");
                register u8 *record asm("r6");
                u8 active;
                u16 flags;
                u16 match2;

                i_shift_low = (u16)i << 16;
                signed_i2 = (s32)i_shift_low >> 16;
                record_offset2 = signed_i2 * 7;
                record_offset2 <<= 4;
                record_base2 = D_020218E8;
                asm volatile("" : "+r"(record_base2));
                record = (u8 *)(record_offset2 + (u32)record_base2);
                active = record[0];
                i_shift = i_shift_low;

                if (active != 0) {
                    flags = *(u16 *)(record + 4);
                    if (!(flags & 4) &&
                        (mode_sp == 0 || func_080B6160(record, mode_sp))) {
                        flags = *(u16 *)(record + 4);
                        match2 = required;
                        match2 &= flags;
                        if (match2 == required &&
                            (flags & excluded_r8) == 0) {
                            D_020321A4[*countp] = i;
                            (*countp)++;
                        }
                    }
                }
                next2 = i_shift + 0x10000;
                i = (u16)(next2 >> 16);
            } while ((s32)next2 >> 16 <= 206);
        }
    }

    {
        u32 i;
        u32 first_shift;
        register u32 first_seed asm("r1");
        u32 initial_next;
        u32 next;
        register u32 outer_shift asm("r2");
        register s32 outer asm("r1");

        first_seed = (u16)first_count;
        first_shift = (u16)first_seed;
        first_shift <<= 16;
        asm volatile("" :: "r"(first_shift));
        asm volatile("" ::
            "r"((s32)(s16)first_count),
            "r"((s32)(s16)first_count),
            "r"((s32)(s16)first_count),
            "r"((s32)(s16)first_count));
        initial_next = first_shift + 0x10000;
        {
            register s32 i_guard_r4 asm("r4");
            asm volatile("" : "=r"(i_guard_r4));
            i = (u16)(initial_next >> 16);
            asm volatile("" :: "r"(i_guard_r4));
        }
        outer_shift = (u32)i << 16;
        asm volatile("" : "+r"(outer_shift));
        if ((s32)i < D_02032272) {
          do {
            u8 index;
            u8 *record;
            s16 j;
            u32 current_record_offset;
            register u8 *current_record_base asm("r7");
            register u32 retained_shift asm("r10");
            register s32 index_guard_r8 asm("r8");
            register s32 index_guard_r9 asm("r9");

            outer = (s32)outer_shift >> 16;
            asm volatile("" : "=r"(index_guard_r8), "=r"(index_guard_r9));
            index = D_020321A4[outer];
            current_record_offset = index * 0x70;
            current_record_base = D_020218E8;
            record = (u8 *)(current_record_offset + (u32)current_record_base);
            asm volatile("" :: "r"(index_guard_r8), "r"(index_guard_r9));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            asm volatile("" :: "r"(record));
            j = outer - 1;
            asm volatile("" :: "r"((s32)(s16)j));
            retained_shift = (u32)i << 16;

            while (j >= (s16)first_count) {
                register s32 previous_index asm("r4") = D_020321A4[j];
                u8 *previous = &D_020218E8[previous_index * 0x70];
                asm volatile("" :: "r"(previous));

                if ((record[0x36] & 0x3F) < (previous[0x36] & 0x3F) ||
                    ((record[0x36] & 0x3F) ==
                         (previous[0x36] & 0x3F) &&
                     record[0x37] < previous[0x37])) {
                    /* shift */
                } else {
                    break;
                }
                D_020321A4[j + 1] = previous_index;
                j--;
            }
            D_020321A4[j + 1] = index;
            next = retained_shift + 0x10000;
            i = (u16)(next >> 16);
            outer_shift = (u16)i;
            outer_shift <<= 16;
            asm volatile("" : "+r"(outer_shift));
          } while ((s32)outer_shift >> 16 < D_02032272);
        }
    }
}
