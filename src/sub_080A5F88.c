#include "m2c_prelude.h"
extern void func_80A016C();

s32 sub_080A5F88(u8 arg0) {
    u8 t;
    s32 *q;
    if (*(s32 *)0x02021690 == 3) {
        t = *(u8 *)0x020316F4;
        if (t == 0 || t == 0x40) {
            *(s8 *)0x020324B0 = 0;
            *(u16 *)0x0300004C &= 0xFDFF;
            *(u16 *)0x0400000E = 0x300;
            q = (s32 *)0x03000054;
            q[7] = 0;
            q[6] = 0;
        }
    }
    func_80A016C(arg0, -1, 0);
    return 0;
}
