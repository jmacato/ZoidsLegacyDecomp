#include "m2c_prelude.h"
extern u16 D_03005EFC, D_03005EFE, D_03005F00, D_03005F02;
void sub_0809544C(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    if ((arg0 != 0) && (arg1 != 0)) {
        D_03005EFC = arg0;
        D_03005EFE = arg1;
    }
    if ((arg2 != 0) && (arg3 != 0)) {
        D_03005F00 = arg2;
        D_03005F02 = arg3;
    }
}
