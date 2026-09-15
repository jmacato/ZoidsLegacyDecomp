#include "m2c_prelude.h"
extern u8 D_0300004C;
extern u8 D_03000074;
extern u8 D_03005EE8;
extern u8 D_03005EF4;
extern u8 D_03005EF8;
extern u8 D_03005EFA;
extern u8 D_03005F10;
extern u8 D_03005F11;
M2C_UNK func_8095494();                                /* extern */

void sub_0809564C(s8 arg0, s8 arg1, u8 arg2) {
    *(s8 *)((u32)&D_03005EE8) = arg2 | 5;
    *(u16 *)((u32)&D_0300004C) |= 0x6000;
    *(s8 *)((u32)&D_03005F10) = arg0;
    *(s8 *)((u32)&D_03005F11) = arg1;
    *(s16 *)((u32)&D_03005EF4) = 0;
    *(s16 *)((u32)&D_03005EF8) = 0;
    *(s16 *)((u32)&D_03005EFA) = 0x3F;
    func_8095494();
    *(u8 *)((u32)&D_03000074) |= 2;
}
