#include "m2c_prelude.h"
extern u8 D_02030664;
extern u32 D_02021690;
extern void func_80ED17C(int);
extern void func_80A016C(int, int, int);

int sub_080A664C(u8 arg0) {
    D_02030664 = 1;
    D_02021690 = 18;
    do {
        func_80ED17C(1);
    } while (D_02021690 == 18);
    func_80A016C(arg0, -1, 0);
    return 0;
}
