#include "m2c_prelude.h"
extern u8 D_0202ECF4[];
extern u8 D_020316F4;
extern void func_80A6148(void);
extern int func_80A016C(int, int, int);

s32 sub_080A63DC(u8 arg0, u8 **arg1) {
    D_0202ECF4[30] = (*arg1)[1] + 1;
    D_0202ECF4[31] = (*arg1)[2];
    D_0202ECF4[32] = (*arg1)[3];
    if (D_020316F4 == 0)
        func_80A6148();
    func_80A016C(arg0, -1, 0);
    return 0;
}
