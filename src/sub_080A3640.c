#include "m2c_prelude.h"
extern u8 D_02034B4C[];
extern u8 D_000027BE[];
extern u8 D_02033F36;

extern void func_08095114(s32);
extern void func_080A016C(u8, s32, s32);
extern void func_080CD110(void);
extern void func_080D0CA0(u8, u8, s32, u8, s32);
extern s32 func_080D1C18(void);
extern void func_080D1D44(void);
extern u8 func_080D1E38(void);
extern void func_080D2200(void);
extern s32 func_080D222C(void);
extern void func_080ED17C(s32);

s32 sub_080A3640(u8 arg0, void **arg1) {
    u8 *temp_r4;
    u8 *p;
    u8 *pidx;
    int t;

    if (func_080D1E38() == 1) {
        func_080D1D44();
        while ((u32)func_080D1E38() <= 1U) {
            func_080ED17C(1);
        }
    }
    if ((func_080D222C() << 0x18) == 0) {
        func_080D2200();
        while ((func_080D222C() << 0x18) == 0) {
            func_080ED17C(1);
        }
    }
    p = D_02034B4C;
    pidx = &D_02033F36;
    p += (int)D_000027BE;
    if (p[*pidx] != 0) {
        func_08095114(*(s32 *)0x020316F8);
        func_080CD110();
    }
    func_080D0CA0(*pidx, *(u8 *)0x020317D6, (temp_r4 = (u8 *)*arg1, t = temp_r4[3] << 8, temp_r4[2] | t), temp_r4[1], 0);
    while ((func_080D1C18() << 0x18) == 0) {
        func_080ED17C(1);
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
