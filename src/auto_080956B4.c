#include "m2c_prelude.h"
M2C_UNK func_8095494();                                /* extern */

void sub_080956B4(s16 arg0, s16 arg1, u8 arg2) {
    *(s8 *)0x03005EE8 = arg2 | 6;
    *(u16 *)0x0300004C |= 0x6000;
    *(s8 *)0x03005EF6 = 0;
    *(s16 *)0x03005EF8 = arg0;
    *(s16 *)0x03005EFA = arg1;
    func_8095494();
    *(u8 *)0x03000074 |= 2;
}
