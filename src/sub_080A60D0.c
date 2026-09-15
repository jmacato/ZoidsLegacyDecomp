#include "m2c_prelude.h"
extern int func_80A016C(int, int, int);
extern u8 D_0202ECF4[];

int sub_080A60D0(u8 arg) {
    D_0202ECF4[0x21] |= 1;
    func_80A016C(arg, -1, 0);
    return 0;
}
