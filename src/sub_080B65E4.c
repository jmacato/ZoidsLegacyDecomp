#include "m2c_prelude.h"

typedef struct {
    u8 type;
    u8 value;
    u8 pad[10];
} FilterRecord;

typedef struct {
    u8 type;
    u8 value;
    u8 pad[54];
} SortRecord;

extern u8 D_0203237A[];

void sub_080B65E4(u8 mode) {
    SortRecord *const sort_records = (SortRecord *)0x087AFCC4;
    u8 *const count = (u8 *)0x02032411;
    const u32 *enabled = (const u32 *)0x02021858;
    s16 index;

    *count = 0;
    index = 1;
    asm volatile("" : "+r"(enabled));
    for (; index <= 151; index++) {
        if ((enabled[index / 32] & (1 << (index % 32))) != 0) {
            FilterRecord *record;

            record = &((FilterRecord *)0x087B1E04)[index];
            asm volatile("" : "+r"(record));
            if (mode == 0 ||
                (mode == 1 && record->type != 200 &&
                 record->type != 201) ||
                (mode == 2 && (u8)(record->type + 56) <= 1)) {
                u8 *selected = D_0203237A;
                register u8 *slot asm("r1");
                asm volatile("" : "+r"(selected));
                slot = (u8 *)(u32)*count + (u32)selected;
                asm volatile("" : "+r"(slot));
                *slot = (u8)index;
                (*count)++;
            }
        }
    }

    index = 0;
    if (index < *count) {
        do {
        register u8 *inner_seed asm("r1");
        register u8 *inner_selected asm("r8");
        u8 current;
        SortRecord *current_record;
        u16 previous;

        current = D_0203237A[index];
        current_record = &sort_records[current];
        asm volatile("" : "+r"(current_record));
        previous = (u16)(index - 1);
        if ((s16)previous >= 0) {
            inner_seed = D_0203237A;
            asm volatile("" : "+r"(inner_seed));
            inner_selected = inner_seed;
            asm volatile("" : "+r"(inner_selected));
            asm volatile("mov r2, #63\n\tmov r9, r2"
                         :
                         :
                         : "r2", "r9");
        }
        while ((s16)previous >= 0) {
            SortRecord *earlier_record;
            register u8 earlier asm("r4");
            s32 signed_previous;
            signed_previous = (s16)previous;
            asm volatile("" : "+r"(signed_previous));
            {
                register u32 earlier_address asm("r0");

                asm volatile("mov r3, r8\n\tadd %0, %1, r3"
                             : "=r"(earlier_address)
                             : "r"(signed_previous)
                             : "r3");
                earlier = *(u8 *)earlier_address;
            }
            earlier_record = &sort_records[earlier];
            asm volatile("" : "+r"(earlier_record));
            {
                register u32 current_type asm("r0") = current_record->type;
                register u32 earlier_type asm("r1") = earlier_record->type;
                register u32 current_key asm("r2");

                asm volatile("mov %0, r9\n\t"
                             "and %0, %1\n\t"
                             "mov %1, r9\n\t"
                             "and %1, %2"
                             : "=r"(current_key), "+r"(current_type)
                             : "r"(earlier_type));
                if (current_key < current_type ||
                    (current_key == current_type &&
                     current_record->value < earlier_record->value)) {
                    u32 shift_address = signed_previous + 1;
                    shift_address += (u32)inner_selected;
                    *(u8 *)shift_address = earlier;
                    previous = (u16)(signed_previous - 1);
                } else {
                    break;
                }
            }
        }
        {
            u32 final_address = (s16)previous + 1;
            register u8 *final_selected asm("r2") = D_0203237A;
            asm volatile("" : "+r"(final_selected));
            final_address += (u32)final_selected;
            *(u8 *)final_address = current;
        }
        index++;
        } while (index < ({
          register u8 *tail_count asm("r1") = count;
          asm volatile("" : "+r"(tail_count));
          *tail_count;
      }));
    }
}
