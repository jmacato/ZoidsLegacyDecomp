#include "m2c_prelude.h"
extern void func_80ECD34(s32, s32);
extern void func_809A1BC(s32, s32, s32);
extern s32 D_087AA70C[];
extern s32 D_087AA96C[][8];

void sub_0809A4CC(u8 arg0, u8 arg1, int arg2, int arg3)
{
    arg2 = arg2 << 0x10;
    arg3 = arg3 << 0x18;
    arg3 = (u32)arg3 >> 0x18;
    func_80ECD34(D_087AA70C[arg0], ((u32)arg2 >> 0xB) + 0x06010000);
    func_809A1BC(D_087AA96C[arg0][arg1], (arg3 << 5) + 0x05000200, 0x02002880);
}
