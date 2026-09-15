#include "m2c_prelude.h"
extern s8 D_03005EE8;
extern u16 D_0300004C;
extern u16 D_03005EFC;
extern u16 D_03005EFE;
extern u16 D_03005F00;
extern u16 D_03005F02;
extern u16 D_03005EF8;
extern u16 D_03005EFA;
extern u8 D_03000074;

void sub_0809538C(u8 arg0, u16 arg1, u16 arg2, u8 arg3, u16 arg4, u16 arg5, u16 arg6, u16 arg7) {
    D_03005EE8 = 1;
    if (arg0 != 0) {
        D_0300004C |= 0x2000;
        D_03005EFC = arg1;
        D_03005EFE = arg2;
    }
    if (arg3 != 0) {
        D_0300004C = (u16)(D_0300004C | 0x4000);
        D_03005F00 = arg4;
        D_03005F02 = arg5;
    }
    D_03005EF8 = arg6;
    D_03005EFA = arg7;
    D_03000074 |= 2;
}
