#include "m2c_prelude.h"
extern s32 func_809F818(s32);
extern s32 D_087EDFB4[];

s32 sub_080E9924(u8 arg0, u8 arg1) {
    if (arg1 == 1) {
        return arg0 * 0x12 + 0x0203EDE8;
    }
    if (arg1 == 2 || arg1 == 0x60 || arg1 == 0x61) {
        if ((func_809F818(2) << 24) == 0) {
            return 0x0810948C;
        }
    }
    if ((u8)(arg1 - 0x36) <= 1 && (func_809F818(0x1A) << 24) == 0) {
        return 0x081094AC;
    }
    return D_087EDFB4[arg1];
}
