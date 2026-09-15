#include "m2c_prelude.h"
struct S033 {
    u8 pad0[0xA];
    s16 fA;
    u8 padC;
    s8 fD;
};
extern struct S033 D_02033FD0;
extern struct S033 D_02033FD0b;

struct S7B { u8 p0; u8 p1; u16 f2; u8 rest[0x14]; };
extern struct S7B D_087B2524[];
extern u8 D_087ED68C[];
extern u8 D_087D818C[];

extern void func_80D2328(void);
extern void func_80D0B60(s32, u8, u8, u16, s32, s32);
extern void func_80D04A0(u8, u8);

void sub_080D0CA0(u8 arg0, u8 arg1, u16 arg2, u8 arg3, u8 arg4) {
    s32 var_r2;
    struct S7B *pb7;
    register s32 idx asm("r0");
    register s32 pbase asm("r1");
    register s32 var_r2_2 asm("r2");
    D_02033FD0.fD = 0;
    func_80D2328();
    if (arg3 <= 2 && (pb7 = D_087B2524, var_r2 = arg2 * 2, (pb7[arg2].f2 & 1) == 0)) {
        D_02033FD0.fA = D_087ED68C[arg3 + arg1 * 3] << 6;
    } else {
        D_02033FD0b.fA = 0x40;
        var_r2 = arg2 * 2;
    }
    idx = (var_r2 + arg2) << 5;
    pbase = (s32)D_087D818C;
    var_r2_2 = idx + pbase;
    if ((u8)(arg3 - 1) <= 2) {
        var_r2_2 += 0xC;
    }
    func_80D0B60(var_r2_2, arg0, arg1, arg2, arg3, arg4);
    func_80D04A0(arg1, arg3);
}
