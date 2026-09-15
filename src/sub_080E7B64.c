#include "m2c_prelude.h"
extern u8 func_809F818(int);
extern u32 D_087EDFB4[];

int sub_080E7B64(u8 arg0) {
    if (arg0 == 1) {
        return 0x02021774;
    }
    if (arg0 == 2 || arg0 == 0x60 || arg0 == 0x61) {
        if (func_809F818(2) == 0) {
            return 0x08109414;
        }
    }
    if ((u8)(arg0 - 0x36) <= 1) {
        if (func_809F818(0x1a) == 0) {
            return 0x08109434;
        }
    }
    return D_087EDFB4[arg0];
}
