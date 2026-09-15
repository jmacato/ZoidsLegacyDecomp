#include "m2c_prelude.h"
M2C_UNK func_8092E74(u16);
M2C_UNK func_80A016C(u8, s32, s32);
extern u8 D_02030667;

int sub_080A2474(u8 arg0, u8 **arg1) {
    D_02030667 = (*arg1)[1];
    func_8092E74(D_02030667);
    func_80A016C(arg0, -1, 0);
    return 0;
}
