#include "m2c_prelude.h"
extern u8 D_02030664;
extern u32 D_087A1B6C[];
extern void func_80ECD5C(u32);
extern void func_80A016C(u8, s32, s32);

s32 sub_080A53B0(u8 arg0, u8 **arg1) {
    D_02030664 = 1;
    func_80ECD5C(D_087A1B6C[(*arg1)[1]]);
    func_80A016C(arg0, -1, 0);
    return 0;
}
