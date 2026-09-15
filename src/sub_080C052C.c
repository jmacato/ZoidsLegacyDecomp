#include "m2c_prelude.h"

M2C_UNK func_080BAF2C(u8, u8, u8, u8, s32, s32, s32);
M2C_UNK func_080BE560(u8, u8);
M2C_UNK func_080E8B08(u8, u8);
M2C_UNK func_080E90AC(u8, u8);
extern u8 D_02034B4C[];

void sub_080C052C(u8 arg0, u8 arg1) {
    u8 temp_r7;
    u8 temp_r6;
    u8 *temp_r5;
    u32 outer_offset;
    u32 inner_offset;
    u16 field;
    u16 replacement;
    s32 mask;
    s32 zero;

    temp_r7 = arg0;
    temp_r6 = arg1;
    outer_offset = temp_r7 * 0x1380;
    inner_offset = temp_r6 * 0x270;
    inner_offset += (u32)D_02034B4C;
    temp_r5 = (u8 *)(outer_offset + inner_offset);
    field = *(u16 *)(temp_r5 + 4);
    if (field & 8) {
        replacement = *(u16 *)(temp_r5 + 0x3A);
        zero = 0;
        *(u16 *)(temp_r5 + 6) = replacement;
        mask = 0xFFF7;
        mask &= field;
        *(u16 *)(temp_r5 + 4) = mask;
        func_080BE560(temp_r7, temp_r6);
        func_080E90AC(temp_r7, temp_r6);
        func_080E8B08(temp_r7, temp_r6);
        func_080BAF2C(temp_r5[0], temp_r5[1], temp_r5[0x38], temp_r7,
                     temp_r6, zero, zero);
    }
}
