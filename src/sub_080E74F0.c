#include "m2c_prelude.h"

struct E74F0RecordSet {
    u8 pad[8];
    u8 types[10];
    s16 entries[10];
};

s32 sub_080E74F0(struct E74F0RecordSet *arg0, s32 arg1, s32 arg2) {
    register struct E74F0RecordSet *records asm("ip") = arg0;
    register s32 mask asm("r4") = arg2;
    register u32 type asm("r9") = (u8)arg1;
    register u32 index asm("r6") = 0;
    register u32 fallback asm("r8");

scan_entries:
    if (records->types[index] != type) {
        goto increment;
    }
    fallback = 0;
    switch (type - 3) {
        case 0:
        case 1:
        case 2: {
            register u32 scan asm("r2") = 0;
            register u8 *table asm("r5") = (u8 *)0x087A5810;
            register u32 entry_offset asm("r1") = index << 1;
            register s16 *entry_base asm("r0") = records->entries;
            s16 *entry = (s16 *)((u8 *)entry_base + entry_offset);
            register s32 row asm("r1") = *entry;
            register s32 offset asm("r0") = row * 0x1A;

            if (*(u8 *)(offset + (s32)table) != mask) {
                register s16 *loop_entry asm("r1") = entry;
                register s32 stride asm("r3") = 0x1A;

                do {
                    register u32 next asm("r0") = scan + 1;
                    next <<= 24;
                    scan = next >> 24;
                    if (scan > 0x19) {
                        break;
                    }
                } while (*(u8 *)(scan + (*loop_entry * stride) +
                                 (s32)table) != mask);
            }
            if (scan == 0x1A) {
                goto check_fallback;
            }
            goto return_entry;
        }
        case 3:
        case 4:
        case 5:
        case 20:
        case 29:
            if ((mask & 0x10) != 0) {
                goto check_fallback;
            }
            goto return_entry;
        case 6:
        case 7:
        case 8:
        case 17:
        case 21:
        case 28:
        case 30:
            if ((mask & 0x10) == 0) {
                goto check_fallback;
            }
            goto return_entry;
        case 22:
        case 23:
        case 31:
        case 32:
            goto check_fallback;
        case 24:
        case 33:
            if ((mask & 2) == 0) {
                goto check_fallback;
            }
            goto return_entry;
        case 25:
        case 34:
            if ((mask & 4) == 0) {
                goto check_fallback;
            }
            goto return_entry;
        case 26:
        case 35:
            if ((mask & 8) == 0) {
                goto check_fallback;
            }
            goto return_entry;
        case 27:
        case 36:
            if ((mask & 1) == 0) {
                goto check_fallback;
            }
            goto return_entry;
        default:
            fallback = 1;
            goto check_fallback;
    }

check_fallback:
    if (fallback == 0) {
        goto increment;
    }

return_entry:
    {
        register u32 entry_offset asm("r0") = index << 1;
        register s16 *entry_base asm("r1") = records->entries;
        register s16 *entry asm("r1") =
            (s16 *)((u8 *)entry_base + entry_offset);
        register s32 value asm("r0") = *entry;
        if (value == 0) {
            value = 1;
        }
        return value;
    }

increment:
    {
        register u32 next asm("r0") = index + 1;
        next <<= 24;
        index = next >> 24;
    }
    if (index <= 9) {
        goto scan_entries;
    }
    return 0;
}
