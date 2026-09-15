#include "m2c_prelude.h"
extern void func_809534C(void);
extern void func_8092E0C(s32);
extern void func_80A016C(s32, s32, s32);
extern u8 D_0203055C[];

s32 sub_080A3998(u8 arg0, u8 **arg1) {
    if (D_0203055C[2] == 0xFF) {
        func_809534C();
        func_8092E0C(7);
        *(u16 *)0x0300004C = 0x1D40;
        *(u16 *)0x04000008 = 0x4085;
        *(u16 *)0x0400000C = 0x028F;
    }
    D_0203055C[2] = (*arg1)[1];
    func_80A016C(arg0, -1, 0);
    return 0;
}
