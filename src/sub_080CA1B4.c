#include "m2c_prelude.h"

void sub_080CA1B4(s32 arg0, s32 arg1) {
    u8 index;
    s32 offset;
    u8 *base;
    u8 *entry;
    u8 *state_ptr;
    u16 *total;

    arg0 <<= 24;
    arg0 = (u32)arg0 >> 24;
    base = (u8 *)0x02034B4C;

    index = base[0x27A4];
    entry = base + (index << 2);
    asm volatile("" : "+r"(entry));
    entry += 0xA07C;
    *entry = 0;

    state_ptr = base + 0xA1AF;
    entry = base + 0xA1B0;
    entry[*state_ptr] = arg0;
    entry = base + 0xA1B3;
    entry[*state_ptr] = arg1;

    total = (u16 *)0x0203EFB2;
    index = *state_ptr;
    offset = index << 3;
    offset -= index;
    offset <<= 5;
    offset += index;
    offset <<= 2;
    arg0 *= 0xA8C;
    offset += arg0;
    offset += (s32)base;
    offset += 0x27D0;
    *total += *(u16 *)offset;
    *state_ptr += 1;
}
