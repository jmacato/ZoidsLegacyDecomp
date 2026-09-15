#include "m2c_prelude.h"
extern void func_80A0114(void);
extern u32 D_02021690;
extern u32 D_020315DC[];
extern u8 D_02030664;

int sub_080A098C(u8 arg0, u32 *arg1) {
    if (D_02021690 == 3) {
        func_80A0114();
        *arg1 = D_020315DC[arg0];
        D_02030664 = 0;
        return 0;
    }
    return 1;
}
