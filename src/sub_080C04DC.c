#include "m2c_prelude.h"
M2C_UNK func_080C02B4(u8, u8);
M2C_UNK func_080CA0AC(s32, u8, u8, s32);
extern s8 D_02034B4C;

void sub_080C04DC(u8 arg0, u8 arg1) {
    u8 temp_r4;
    u8 temp_r5;
    void *temp_r1;
    s32 temp_r0;
    register u16 field asm("r2");
    register u16 mask asm("r0");

    temp_r4 = arg0;
    temp_r5 = arg1;
    temp_r1 = temp_r4 * 0x1380;
    temp_r0 = temp_r5 * 0x270;
    temp_r0 += (s32)&D_02034B4C;
    temp_r1 += temp_r0;
    field = M2C_FIELD(temp_r1, u16 *, 4);
    mask = 8;
    mask |= field;
    M2C_FIELD(temp_r1, u16 *, 4) = mask;
    func_080C02B4(temp_r4, temp_r5);
    func_080CA0AC(4, temp_r4, temp_r5, 0);
}
