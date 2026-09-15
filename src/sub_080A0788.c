#include "m2c_prelude.h"

struct RecordA0788 {
    s32 flags;
    u8 field4;
    u8 field5;
    u16 field6;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
    u8 field18;
    u8 field19;
    u8 field1A;
    u8 pad1B[0x2D];
};

void func_080A016C(s32, s32, s32);
void *func_080A9D78(u8, u8, s32, s32, s32, s32, s32, s32);
u8 func_080A9EF0(u8);
void func_080ED17C(s32);

s32 sub_080A0788(s32 arg0, void **arg1)
{
    register void **command_slot asm("r5") = arg1;
    register u32 caller;
    register u32 active asm("r6");
    register u32 index asm("r2");
    register struct RecordA0788 *record asm("r4");

    arg0 <<= 24;
    caller = (u32)arg0 >> 24;
    active = 0;
    {
        register u32 result asm("r0");

        result = func_080A9EF0(((u8 *)*command_slot)[1]);
        result <<= 24;
        index = result >> 24;
    }
    if (index != 0xFF) {
        register u32 offset asm("r0");
        register struct RecordA0788 *base asm("r1") =
            (struct RecordA0788 *)0x020325A0;
        register u32 old asm("r3");
        register u8 *command asm("r0");

        offset = index << 3;
        offset += index;
        offset <<= 3;
        record = (struct RecordA0788 *)(offset + (u32)base);
        command = *command_slot;
        old = record->field6;
        if (old != command[2]) {
            record->flags &= ~2;
            if (old == 0) {
                *(u32 *)0x02032990 = active;
                if (record->field4 == 1) {
                    register u32 test asm("r1");
                    register u32 nonzero asm("r0");

                    nonzero = func_080A9EF0(0xD);
                    nonzero <<= 24;
                    index = nonzero >> 24;
                    test = 0xFF;
                    test ^= index;
                    nonzero = 0 - test;
                    nonzero |= test;
                    active = nonzero >> 31;
                }
            }

            record->field6 = ((u8 *)*command_slot)[2];
            record->field14 = 0;
            record->field10 = 0;
            if (record->field18 != 4) {
                record->field18 = 0;
            }

            if (active != 0) {
                register struct RecordA0788 *replacement asm("r2");
                register u32 offset asm("r0");
                register struct RecordA0788 *base asm("r1") =
                    (struct RecordA0788 *)0x020325A0;

                asm volatile("" : "+r"(base));
                offset = index << 3;
                offset += index;
                offset <<= 3;
                replacement = (struct RecordA0788 *)(offset + (u32)base);
                replacement->field6 = 9;
                *(u8 *)0x02030664 = 1;
                if (replacement->flags & 1) {
                    register struct RecordA0788 *poll_record asm("r5") =
                        replacement;

                    do {
                        func_080ED17C(1);
                    } while (poll_record->flags & 1);
                }
            }

            if (record->field6 == 0) {
                *(struct RecordA0788 **)0x02032990 = record;
                if (record->field4 == 1) {
                    register u32 scan asm("r2") = 1;
                    register u8 *base asm("r3") = (u8 *)0x020218E4;
                    register s32 zero asm("r5") = 0;

scan_next:
                    {
                        register u32 offset asm("r0") = scan << 6;
                        register u8 *entry asm("r1") =
                            (u8 *)((u32)offset + (u32)base);
                        register u32 field_offset asm("r6") = 0x5A94;
                        register u8 *field asm("r0");

                        field = entry + field_offset;
                        if (*field == 1) {
                            field_offset += 0x31;
                            field = entry + field_offset;
                            if (*field == 1) {
                                register u32 result asm("r0");

                                result = func_080A9EF0(0xD);
                                result <<= 24;
                                scan = result >> 24;
                                if (scan == 0xFF) {
                                    *(void **)0x02032994 = func_080A9D78(
                                        0x4B, 0xD, record->field8,
                                        record->fieldC, record->field1A,
                                        zero, 8, zero);
                                }
                                goto finished;
                            }
                        }
                    }
                    scan += 1;
                    if (scan <= 0x34) {
                        goto scan_next;
                    }
                }
            }
        }
    }

finished:
    {
        register u32 final_caller asm("r0");
        register s32 minus_one asm("r1");

        minus_one = 1;
        minus_one = -minus_one;
        asm volatile("" : "+r"(minus_one));
        final_caller = caller;
        func_080A016C(final_caller, minus_one, 0);
    }
    return 0;
}
