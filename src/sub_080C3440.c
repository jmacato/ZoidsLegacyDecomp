#include "m2c_prelude.h"

M2C_UNK func_080C02B4(u8, u8);
extern u8 D_02034B4C[];
extern u8 D_02032F7C[];

void sub_080C3440(u8 arg0, u8 arg1, u8 arg2) {
    u8 temp_r0;
    u8 temp_r6;
    u8 temp_r4;
    u8 index;
    u8 *base;
    u8 *map;
    u8 *dest;
    u32 inner_offset;
    u32 outer_offset;

    temp_r0 = arg0;
    temp_r6 = arg1;
    temp_r4 = arg2;
    base = D_02034B4C;
    inner_offset = temp_r4 * 0x270;
    outer_offset = temp_r0 * 0x1380;
    base[inner_offset + outer_offset] = 0;
    func_080C02B4(temp_r0, temp_r4);
    map = base + 0x2700;
    dest = base + 0x2706;
    index = map[temp_r4];
    dest[index] = map[temp_r6];
    D_02032F7C[temp_r4] = temp_r6;
}
