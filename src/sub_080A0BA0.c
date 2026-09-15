#include "m2c_prelude.h"
extern u8 D_02030664;
extern u8 D_03000075;
void func_80ED17C(int);
int func_80A016C(int, int, int);

int sub_080A0BA0(u8 arg0, u8 **arg1) {
    u32 total;
    D_02030664 = 1;
    total = 0;
    while (total < (*arg1)[1]) {
        func_80ED17C(1);
        total += D_03000075;
    }
    func_80A016C(arg0, -1, 0);
    return 0;
}
