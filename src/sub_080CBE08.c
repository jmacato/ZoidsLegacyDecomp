#include "m2c_prelude.h"

s32 sub_080CBE08(s32 arg0, s32 arg1) {
    u8 secondary;
    s32 arg0_work;
    s32 offset;
    s32 extra;
    s32 next_slot;
    register s32 arg0_offset asm("r12");
    s32 arg1_offset;
    register s32 state_offset asm("r6");
    register u8 *base asm("r5");
    register s32 state asm("r4");
    register s32 state_work asm("r0");
    register s32 slot asm("r3");

    arg0 <<= 24;
    arg0 = (u32)arg0 >> 24;
    slot = 0;
    base = (u8 *)0x02034B4C;
    arg0_work = arg0 << 3;
    arg0_work += arg0;
    arg0_offset = arg0_work << 3;
    arg1 <<= 24;
    arg1 >>= 24;
    arg1_offset = arg1 * 0x94;
    state = base[0xA1AF];
    state_work = state << 3;
    state_work -= state;
    state_work <<= 5;
    state_work += state;
    state_offset = state_work << 2;
loop:
        offset = slot << 1;
        offset += slot;
        offset <<= 2;
        offset += arg0_offset;
        offset += arg1_offset;
        offset += state_offset;
        {
            register u8 *secondary_ptr asm("r1");

            secondary_ptr = base + 0xA1B0;
            secondary = *(u8 *)((s32)state + (s32)secondary_ptr);
        }
        extra = secondary * 0xA8C;
        offset += extra;
        offset += (s32)base;
        offset += 0x27D8;
        if (*(u16 *)offset & 1) {
            goto done;
        }
        next_slot = slot + 1;
        next_slot <<= 24;
        asm volatile("" :: "r"(slot));
        slot = (u32)next_slot >> 24;
        if ((u32)slot <= 5) {
            goto loop;
        }
done:
    return (u32)slot <= 5;
}
