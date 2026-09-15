#include "m2c_prelude.h"

extern u8 func_080CA560(void);
extern u32 func_080ECD5C(u32);
extern void func_080CA238(void);
extern void func_080CA860(void);
extern void func_080CA1B4(s32, s32);

void sub_080CA650(void)
{
    register u8 *base asm("r6");
    register u8 **active_slot asm("r9");
    register u32 attempt asm("r8");

    attempt = 0;
    base = (u8 *)0x02034B4C;
    active_slot = (u8 **)(base + 0x27A8);
    do {
        if (func_080CA560()) {
            register u32 *rng asm("r10");
            register u32 random asm("r0");
            register u32 count asm("r1");
            register u32 selected asm("r4");
            register u8 *index_table asm("r0");
            register u8 *entry asm("r5");
            register s32 record_index asm("r1");
            register s32 record_stride asm("r0");
            register s32 record_offset asm("r2");
            register u32 row asm("r1");
            register s32 row_offset asm("r0");
            register u8 *record_base asm("r1");
            register u8 *record asm("r2");
            register s32 active_value asm("r3");
            register s32 base_value asm("r0");
            register s32 record_value asm("r1");
            u8 **slot_view;
            s32 off_rec;

            {
                register u32 *rng_lo asm("r3");
                rng_lo = (u32 *)0x03000010;
                asm volatile("" : "+r"(rng_lo));
                rng = rng_lo;
                random = func_080ECD5C(*rng_lo);
            }
            count = *(u8 *)0x0203EFA8;
            random *= count;
            random >>= 15;
            selected = (u8)random;
            index_table = (u8 *)0x0203EF70;
            asm volatile("" : "+r"(index_table));
            entry = (u8 *)(selected + (s32)index_table);
            record_index = *entry;
            asm volatile("" : "+r"(record_index));
            record_stride = 0xA8C;
            record_offset = record_index;
            record_offset *= record_stride;
            row = base[0xA1AF];
            row_offset = row << 3;
            row_offset -= row;
            row_offset <<= 5;
            row_offset += row;
            row_offset <<= 2;
            off_rec = 0x27C8;
            asm volatile("" : "+r"(off_rec));
            record_base = base + off_rec;
            row_offset += (s32)record_base;
            record_offset += row_offset;
            record = (u8 *)record_offset;
            slot_view = active_slot;
            asm volatile("" : "+r"(slot_view) : "r"(row_offset), "r"(record_base), "r"(off_rec));
            asm volatile("" :: "r"(row_offset), "r"(record_base), "r"(off_rec));
            active_value = *(s16 *)(*slot_view + 8);
            base_value = *(s16 *)0x0203EFB2;
            record_value = *(s16 *)(record + 8);
            base_value += record_value;
            if (active_value >= base_value) {
                register u32 replacement asm("r2");
                register u32 random_count asm("r1");
                register u32 argument asm("r0");
                register u32 table_offset asm("r1");

                {
                    register u32 *rng_view asm("r1");
                    rng_view = rng;
                    asm volatile("" : "+r"(rng_view));
                    random = func_080ECD5C(*rng_view);
                }
                {
                    register u8 *count_table asm("r1");
                    count_table = (u8 *)0x0203EFA9;
                    asm volatile("" : "+r"(count_table));
                    random_count = *(u8 *)(selected + (s32)count_table);
                }
                replacement = random;
                replacement *= random_count;
                replacement >>= 15;
                replacement = (u8)replacement;
                argument = *entry;
                {
                    register u8 *table asm("r3");
                    table = (u8 *)0x0203EF78;
                    asm volatile("" : "+r"(table));
                    table_offset = selected << 1;
                    table_offset += selected;
                    table_offset <<= 1;
                    replacement += table_offset;
                    replacement += (u32)table;
                }
                func_080CA1B4(argument, *(u8 *)replacement);
                return;
            }
        }
        {
            register u32 attempt_view asm("r3");
            attempt_view = attempt;
            asm volatile("" : "+r"(attempt_view));
            if (attempt_view == 0) {
                func_080CA238();
                func_080CA860();
                {
                    register u32 one asm("r7");
                    one = 1;
                    asm volatile("" : "+r"(one));
                    attempt = one;
                }
            } else {
                {
                    register s32 t asm("r0");
                    register s32 offa asm("r1");
                    register s32 offb asm("r3");
                    register u32 onev asm("r1");
                    offa = 0x27A4;
                    asm volatile("" : "+r"(offa));
                    t = (s32)(base + offa);
                    t = *(u8 *)t;
                    t <<= 2;
                    t += (s32)base;
                    offb = 0xA07C;
                    asm volatile("" : "+r"(offb));
                    t += offb;
                    onev = 1;
                    *(u8 *)t = onev;
                }
                return;
            }
        }
    } while (1);
}
