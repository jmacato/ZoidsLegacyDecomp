#include "m2c_prelude.h"
extern u16 D_030009EC;
extern s32 D_030009E8;
extern s32 D_03000014[];
extern volatile s32 D_040000D4[];
extern void func_08093008(s32);
extern void func_080930E8(void);
void sub_0809279C(void) {
    u16 local;
    u16 flags = D_030009EC;
    s32 f1 = 1 & flags;
    if (f1 != 0) {
        D_03000014[3] = 0x030031B5;
        D_030009E8 = 0;
        local = 0;
        D_040000D4[0] = (s32)&local;
        D_040000D4[1] = 0x03000998;
        D_040000D4[2] = 0x81000008;
        D_040000D4[2];
        local = 0;
        D_040000D4[0] = (s32)&local;
        D_040000D4[1] = 0x030009A8;
        D_040000D4[2] = 0x81000020;
        func_08093008(D_040000D4[2]);
        D_030009EC = (0xFFFE & D_030009EC) | 2;
        return;
    }
    {
        s32 m = 4;
        m &= flags;
        if (m != 0) {
            s32 *pe8;
            func_080930E8();
            pe8 = &D_030009E8;
            D_030009EC = f1;
            *pe8 = f1;
        }
    }
}
