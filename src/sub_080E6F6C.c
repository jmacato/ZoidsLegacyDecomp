#include "m2c_prelude.h"
extern u8 D_02027378[];
void func_80E5C34(u8); void func_80E6E98(u8);
void sub_080E6F6C(u8 arg0) {
    s32 off = arg0 << 6;
    u8 *p = D_02027378 + off;
    if (2 & *(u16 *)(p + 2)) {
        func_80E5C34(*(u8 *)(p + 1));
        D_02027378[off] = 0;
        return;
    }
    func_80E6E98(arg0);
}
