#include "m2c_prelude.h"
extern void func_80A9F40(u8);
extern void func_80A016C(u8, s32, s32);

s32 sub_080A08C0(u8 arg0, u8 **arg1) {
    func_80A9F40((*arg1)[1]);
    func_80A016C(arg0, -1, 0);
    return 0;
}
