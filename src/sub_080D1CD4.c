#include "m2c_prelude.h"
M2C_UNK func_080D1E58();
extern s8 D_02034863;
extern s16 D_02034864;
extern s16 D_02034866;
extern u8 D_03000074;
extern s32 D_03000054[];
extern u16 D_0300004C;
extern u16 D_0400000A;
extern u16 D_0400000C;
extern s8 D_02034862;

void sub_080D1CD4(void) {
    D_02034863 = 2;
    D_02034864 = -0x10;
    D_02034866 = 0;
    D_03000074 |= 4;
    D_03000054[3] = 0;
    D_0300004C |= 0x200;
    D_0400000A = D_0400000C;
    D_02034862 = 1;
    func_080D1E58();
}
