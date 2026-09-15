#include "m2c_prelude.h"
extern void func_80A016C(int, int, int);
extern u8 D_0202ECF4[];

int sub_080A6120(u8 arg0) {
    D_0202ECF4[0x21] |= 2;
    func_80A016C(arg0, -1, 0);
    return 0;
}
