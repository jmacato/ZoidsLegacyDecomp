#include "m2c_prelude.h"
extern int func_80BB224(int a, int b, int c, int d);
extern int func_80A016C(int a, int b, int c);

int sub_080A2F40(u8 arg0) {
    func_80BB224(8, 0, 0, 1);
    func_80A016C(arg0, -1, 0);
    return 0;
}
