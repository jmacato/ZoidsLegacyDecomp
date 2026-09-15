#include "m2c_prelude.h"
extern u8 D_02030664;
extern int func_809FBA8(int);
extern void func_80A016C(u8, int, u8);

int sub_080A0C70(u8 arg0, int *arg1) {
    int r;
    D_02030664 = 1;
    r = func_809FBA8(*arg1 + 2);
    func_80A016C(arg0, 18, r);
    return 0;
}
