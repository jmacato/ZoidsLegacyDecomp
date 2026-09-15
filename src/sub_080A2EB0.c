#include "m2c_prelude.h"
extern int func_80BB224(int, int, int, int);
extern int func_80A016C(int, int, int);

int sub_080A2EB0(u8 arg0, u8 **arg1) {
    u8 *p = *arg1;
    func_80BB224(5, p[1], p[2], 0);
    func_80A016C(arg0, -1, 0);
    return 0;
}
