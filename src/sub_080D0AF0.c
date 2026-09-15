#include "m2c_prelude.h"
extern void func_80D0480(void);
extern void func_80D12A0(s32, s32);
extern void func_80D1C38(void);
extern void func_80D2180(void);
extern void func_80D2328(void);
extern s8 D_02033FD0;
extern s32 D_02034034;
extern s32 D_02034038;
extern s32 D_0203403C;
extern s32 D_02034040;
extern s32 D_02034044;
extern s32 D_02034048;
extern s8 D_02034860;
extern s8 D_02034861;

void sub_080D0AF0(s32 arg0) {
    s8 *pfd0 = &D_02033FD0;
    s32 z = 0;
    *pfd0 = z;
    func_80D12A0(1, 0);
    D_02034034 = arg0 << 8;
    D_02034038 = z;
    { s32 *lo = &D_0203403C; s32 *hi = &D_02034040; *hi = z; *lo = z; }
    { s32 *lo = &D_02034044; s32 *hi = &D_02034048; *hi = z; *lo = z; }
    func_80D0480();
    func_80D2328();
    func_80D1C38();
    func_80D2180();
    D_02034860 = z;
    D_02034861 = z;
}
