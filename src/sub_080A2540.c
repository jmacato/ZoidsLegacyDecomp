#include "m2c_prelude.h"
extern void func_8092EA0(int);
extern void func_80A016C(int, int, int);
extern u8 D_02031742;

int sub_080A2540(u8 arg0) {
    func_8092EA0(D_02031742);
    func_80A016C(arg0, -1, 0);
    return 0;
}
