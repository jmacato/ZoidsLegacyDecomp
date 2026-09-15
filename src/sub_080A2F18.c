#include "m2c_prelude.h"
extern int func_80BB224(int, int, int, int);
extern int func_80A016C(int, int, int);

int sub_080A2F18(u8 arg) {
    func_80BB224(6, 0, 0, 0);
    func_80A016C(arg, -1, 0);
    return 0;
}
