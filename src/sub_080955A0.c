#include "m2c_prelude.h"
extern u8 D_0300004C;
extern u8 D_03000074;
extern u8 D_03005EE8;
extern u8 D_03005EF8;
extern u8 D_03005EFA;
extern u8 D_03005F0C;
M2C_UNK func_8095494();                                /* extern */

void sub_080955A0(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    *(s8 *)((u32)&D_03005EE8) = arg3 | 3;
    *(u16 *)((u32)&D_0300004C) |= 0x6000;
    *(s32 *)((u32)&D_03005F0C) = arg0;
    *(s16 *)((u32)&D_03005EF8) = arg1;
    *(s16 *)((u32)&D_03005EFA) = arg2;
    func_8095494();
    *(u8 *)((u32)&D_03000074) |= 2;
}
