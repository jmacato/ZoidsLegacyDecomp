#include "m2c_prelude.h"

M2C_UNK func_080BE560(u8, u8);
extern u8 D_02034B4C;

void sub_080BE600(void) {
    u8 outer;
    u8 inner;
    s32 next_outer;
    s32 outer_work;
    s32 outer_offset;
    s32 inner_offset;
    u8 *base;

    outer = 0;
    base = &D_02034B4C;
    do {
        inner = 0;
        outer_work = outer << 2;
        next_outer = outer + 1;
        outer_work += outer;
        outer_work <<= 3;
        outer_work -= outer;
        outer_offset = outer_work << 7;
        do {
            func_080BE560(outer, inner);
            inner_offset = inner << 2;
            inner_offset += inner;
            inner_offset <<= 3;
            inner_offset -= inner;
            inner_offset <<= 4;
            inner_offset += outer_offset;
            inner_offset += (s32)base;
            *(u16 *)(inner_offset + 0x266) = 0;
            inner += 1;
        } while ((u32)inner <= 5);
        outer = next_outer;
    } while ((u32)outer <= 1);
}
