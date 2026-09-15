#include "m2c_prelude.h"
extern void func_80D0B60(s32, u8, u8, u16, s32, s32);
extern void func_80D2328(void);
extern void func_80D04A0(u8, s32);

struct S02033FD0 { u8 _p[0xA]; s16 fA; u8 _p2; s8 fD; };
extern struct S02033FD0 D_02033FD0;
extern u8 D_0203055C[];
extern u8 D_02034056;

void sub_080D0D50(u8 arg0, u8 arg1, u16 arg2, u8 arg3) {
    D_02033FD0.fD = 1;
    func_80D2328();
    D_02033FD0.fA = 0x40;
    if (D_0203055C[2] != 0xD) {
        func_80D0B60((arg2 * 0x60) + 0x087D81A4, arg0, arg1, arg2, 0, arg3);
    } else {
        func_80D0B60((arg2 * 0x60) + 0x087D81B0, arg0, arg1, arg2, 0, arg3);
    }
    if (D_02034056 != 8) {
        func_80D04A0(arg1, 8);
    }
}
