#include "m2c_prelude.h"
extern void func_8095494(void);
extern s32 D_03005F04[];
extern u16 D_03005EEA[];
extern u16 D_03005EEE[];
extern u16 D_03005EF8;
extern u16 D_03005EFA;

void sub_080954D8(s32 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4, u16 arg5, u16 arg6, u16 arg7, u8 arg8) {
    *(u8 *)0x03005EE8 = arg8 | 2;
    D_03005F04[0] = arg0;
    D_03005EEA[0] = arg1;
    D_03005EEE[0] = arg2;
    if (arg0 != 0) {
        *(u16 *)0x0300004C |= 0x2000;
    }
    D_03005F04[1] = arg3;
    D_03005EEA[1] = arg4;
    D_03005EEE[1] = arg5;
    if (arg3 != 0) {
        *(u16 *)0x0300004C |= 0x4000;
    }
    D_03005EF8 = arg6;
    D_03005EFA = arg7;
    func_8095494();
    *(u8 *)0x03000074 |= 2;
}
