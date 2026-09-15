#include "m2c_prelude.h"
extern u8 D_02030667;
extern void func_8092EA0(int);
extern void func_80A016C(int, int, int);

int sub_080A24E4(u8 arg0) {
    func_8092EA0(D_02030667);
    D_02030667 = 0;
    func_80A016C(arg0, -1, 0);
    return 0;
}
