#include "m2c_prelude.h"
extern u8 D_02030664;
extern void func_0809FF54(void);
extern void func_8092D8C();
extern void func_80A016C();

int sub_080A2238(u8 arg0) {
    D_02030664 = 1;
    func_8092D8C(5, func_0809FF54);
    func_80A016C(arg0, -1, 0);
    return 0;
}
