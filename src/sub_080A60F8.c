#include "m2c_prelude.h"
extern void func_080A016C(int, int, int);
extern u8 D_0202ECF4[];

u8 sub_080A60F8(u8 arg0) {
    D_0202ECF4[0x21] &= 0xFD;
    func_080A016C(arg0, -1, 0);
    return 0;
}
