#include "m2c_prelude.h"
M2C_UNK func_80A016C();
extern u32 D_02021690;
extern u8 D_020316F4;
extern u8 D_020324B1;

s32 sub_080A5FF4(u8 arg0) {
    u8 v;
    if (D_02021690 == 3) {
        v = D_020316F4;
        if (v == 0 || v == 0x40) {
            D_020324B1 = 0;
        }
    }
    func_80A016C(arg0, -1, 0);
    return 0;
}
