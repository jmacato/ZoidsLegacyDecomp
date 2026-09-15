#include "m2c_prelude.h"
extern void func_8092E84(int);
extern void func_80A016C(int, int, int);
extern u8 D_02031742;

int sub_080A2510(u8 arg0, u8 **arg1) {
    D_02031742 = (*arg1)[1];
    func_8092E84(D_02031742);
    func_80A016C(arg0, -1, 0);
    return 0;
}
