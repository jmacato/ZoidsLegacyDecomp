#include "m2c_prelude.h"
M2C_UNK func_80BB224(s32, u8, s32, s32);
M2C_UNK func_80A016C(u8, s32, s32);

s32 sub_080A2EDC(u8 arg0, u8 **arg1) {
    if ((*arg1)[1] == 0) {
        func_80BB224(2, 0, 0, 0);
    } else {
        func_80BB224(2, 1, 0, 0);
    }
    func_80A016C(arg0, -1, 0);
    return 0;
}
