#include "m2c_prelude.h"
extern s32 D_087AA70C[];
extern s32 D_087AA96C[][8];
extern void func_80ECD38();
extern void func_8095208();

void sub_0809A52C(u8 arg0, u8 arg1, u16 arg2, u8 arg3, s32 arg4) {
    s32 t2;
    s32 sz;
    s32 idx;
    func_80ECD38(D_087AA70C[arg0], arg4);
    idx = D_087AA96C[arg0][arg1];
    sz = 0x800;
    t2 = arg4 + sz;
    func_80ECD38(idx, t2);
    func_8095208(arg4, (arg2 << 5) + 0x06010000, sz);
    func_8095208(t2, (arg3 << 5) + 0x05000200, 0x20);
}
