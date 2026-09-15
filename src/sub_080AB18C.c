#include "m2c_prelude.h"
extern u8 D_020324B0;

s32 sub_080AB18C(u8 arg0, u16 arg1) {
    if (D_020324B0 & 4) {
        if (arg1 & 0x20) {
            return 1;
        }
    }
    switch (arg1 & 0x1F) {
        case 4:
        case 6:
        case 7:
        case 9:
            if ((u8)(arg0 - 0x69) <= 2) {
                return 1;
            }
            return 0;
        case 8:
        case 10:
            if (arg0 == 0x69) {
                return 1;
            }
            return 0;
        case 11:
            if ((u8)(arg0 - 0x69) <= 1) {
                return 1;
            }
            return 0;
        case 0:
        case 12:
        default:
            return 0;
    }
}
