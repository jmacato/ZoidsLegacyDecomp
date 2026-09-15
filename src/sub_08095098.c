#include "m2c_prelude.h"

struct Record95098 {
    u32 flags;
    u8 pad04[8];
    u32 slots[32];
    u8 pad8C[0x20];
    s32 fieldAC;
    s32 fieldB0;
};

struct Record95098 *sub_08095098(s32 arg0, s32 arg1, s32 arg2) {
    s32 saved_arg0;
    s32 saved_arg1;
    register s32 saved_arg2 asm("r12");
    register u32 index asm("r3");
    struct Record95098 *records;
    register struct Record95098 *initial asm("r0");
    register s32 initial_flags asm("r1");
    register s32 initial_mask asm("r2");

    saved_arg0 = arg0;
    saved_arg1 = arg1;
    saved_arg2 = arg2;
    index = 0;
    initial = (struct Record95098 *)0x030034A4;
    initial_flags = initial->flags;
    initial_mask = 1;
    initial_flags &= initial_mask;
    records = initial;
    if (initial_flags != 0) {
        register u8 *loop_records asm("r4");
        register s32 stride asm("r2");
        register s32 mask asm("r1");

        loop_records = (u8 *)records;
        stride = 0xB4;
        mask = 1;
        do {
            register u32 next_index asm("r0");
            register s32 scan_offset asm("r0");
            register s32 scan_flags asm("r0");

            next_index = index + 1;
            next_index <<= 24;
            index = next_index >> 24;
            if (index > 15) {
                break;
            }
            scan_offset = index;
            scan_offset *= stride;
            scan_offset += (s32)loop_records;
            scan_flags = *(u32 *)scan_offset;
            scan_flags &= mask;
            if (scan_flags == 0) {
                break;
            }
        } while (1);
    }
    if (index == 16) {
        return (struct Record95098 *)0;
    }
    {
        register s32 record_offset asm("r0");
        register struct Record95098 *record asm("r1");
        register u32 slot asm("r3");
        register u32 *clear_base asm("r2");
        register s32 clear_zero asm("r4");

        record_offset = 0xB4;
        record_offset *= index;
        record = (struct Record95098 *)(record_offset + (s32)records);
        record->flags = saved_arg0 | 1;
        slot = 0;
        clear_base = record->slots;
        clear_zero = 0;
        do {
            register u32 next_slot asm("r0");
            register s32 slot_offset asm("r0");
            register u32 *clear_address asm("r0");

            slot_offset = slot << 2;
            clear_address = (u32 *)((s32)clear_base + slot_offset);
            *clear_address = clear_zero;
            next_slot = slot + 1;
            next_slot <<= 24;
            slot = next_slot >> 24;
        } while (slot <= 31);
        {
            register u8 *tail asm("r0");
            register s32 final_arg asm("r2");

            tail = (u8 *)record;
            tail += 0xAC;
            *(s32 *)tail = saved_arg1;
            asm volatile("" : "+r"(tail));
            tail += 4;
            asm volatile("" : "+r"(tail));
            final_arg = saved_arg2;
            *(s32 *)tail = final_arg;
        }
        return record;
    }
}
