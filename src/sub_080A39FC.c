#include "m2c_prelude.h"
extern u8 D_020317D8;
extern void func_080A016C(int, int, int);

u8 sub_080A39FC(u8 arg0, u8 **arg1) {
    D_020317D8 = **arg1;
    func_080A016C(arg0, -1, 0);
    return 0;
}
