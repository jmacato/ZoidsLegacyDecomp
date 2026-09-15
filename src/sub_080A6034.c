#include "m2c_prelude.h"
extern void func_80A016C();
extern void func_80ECD34();
extern u8 D_0202ECF4[];

s32 sub_080A6034(u8 arg0) {
    u8 t;
    s32 *p;
    if (*(s32 *)0x02021690 == 3) {
        t = *(u8 *)0x020316F4;
        if (t == 0) {
            func_80ECD34(0x08420F28, 0x0600C000);
            func_80ECD34(0x0842115C, 0x06000800);
            p = (s32 *)0x03000054;
            p[2] = t;
            p[3] = 0xFFFFC000;
            *(u8 *)0x020324B0 = (0xFC & *(u8 *)0x020324B0) | 2;
        }
    }
    func_80A016C(arg0, -1, 0);
    return 0;
}

s32 sub_080A60A8(u8 arg0) {
    D_0202ECF4[0x21] &= 0xFE;
    func_80A016C(arg0, -1, 0);
    return 0;
}
