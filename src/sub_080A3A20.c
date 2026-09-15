#include "m2c_prelude.h"
extern u8 D_020317D9;
extern int func_80A016C();

int sub_080A3A20(u8 arg) {
    D_020317D9 = 1;
    func_80A016C(arg, -1, 0);
    return 0;
}
