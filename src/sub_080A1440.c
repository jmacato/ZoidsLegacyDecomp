#include "m2c_prelude.h"
extern void func_809F7F0(int);
extern int func_80A016C(int, int, int);
extern u8 D_020316FC[];

int sub_080A1440(u8 arg0, u8 **arg1) {
    u8 i;
    for (i = 0; i <= 0x45; i++) {
        D_020316FC[i] = 1;
    }
    func_809F7F0((*arg1)[1]);
    func_80A016C(arg0, -1, 0);
    return 0;
}
