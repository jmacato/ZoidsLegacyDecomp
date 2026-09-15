#include "m2c_prelude.h"

struct RecordAC3B8 {
    u8 type;
    u8 pad1;
    u16 flags;
    u8 pad4[0x3C];
};

void func_80ED038(void *, const void *, u32);
void *func_80E7B64(u8);
void func_8099F5C(void *, void *);
void func_80988C8(s32, void *);

void sub_080AC3B8(s32 arg0, s32 flags, s32 wanted_type)
{
    register u32 saved_arg0 asm("r10") = (u8)arg0;
    register u32 saved_flags asm("r9") = (u16)flags;
    register u32 saved_type asm("r8") = (u8)wanted_type;
    u8 i = 0;

    if (i < *(u8 *)0x020322A7) {
        register u8 *output = (u8 *)0x02030564;
        register u8 *text = output + 2;

        do {
            register struct RecordAC3B8 *record asm("r4");
            register u8 *mapping asm("r0") = (u8 *)0x02032273;
            register u32 record_offset asm("r0");

            asm volatile("" : "+r"(mapping));
            asm volatile("add %0, %1, %0"
                         : "+r"(mapping)
                         : "r"((u32)i));
            record_offset = *mapping;
            record_offset <<= 6;
            {
                register struct RecordAC3B8 *records asm("r1") =
                    (struct RecordAC3B8 *)0x02027378;
                asm volatile("" : "+r"(records));
                record = (struct RecordAC3B8 *)(record_offset + (u32)records);
            }
            if (record->type == saved_type) {
                goto special_marker;
            }
            {
                register u32 one asm("r2") = 1;
                if (saved_flags & one) {
                    if (record->flags & 2) {
                        goto special_marker;
                    }
                }
                *(u16 *)output = one;
                goto format;
            }
special_marker:
            {
                register u32 special asm("r0") = 0x401;
                asm volatile("" : "+r"(special));
                *(u16 *)output = special;
            }
format:
            func_80ED038(text, (void *)0x081061C4, 3);
            func_8099F5C(text, func_80E7B64(record->type));
            func_80988C8(saved_arg0, text - 2);
            i++;
        } while (i < *(u8 *)0x020322A7);
    }
}
