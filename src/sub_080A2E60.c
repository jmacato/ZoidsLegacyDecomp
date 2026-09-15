#include "m2c_prelude.h"
M2C_UNK func_080A016C(u8, s32, s32);
M2C_UNK func_080BB05C(u8, u8);
extern s8 D_02034B4C;

s32 sub_080A2E60(u8 arg0, void **arg1) {
    void *temp_r1;
    void *temp_r2;
    s8 *table;
    u8 row;
    s32 index;

    temp_r1 = *arg1;
    func_080BB05C(M2C_FIELD(temp_r1, u8 *, 1), M2C_FIELD(temp_r1, u8 *, 2));
    table = &D_02034B4C;
    temp_r2 = *arg1;
    row = M2C_FIELD(temp_r2, u8 *, 2);
    index = row * 0x270;
    index += M2C_FIELD(temp_r2, u8 *, 1) * 0x1380;
    table[index] = 0;
    func_080A016C(arg0, -1, 0);
    return 0;
}
