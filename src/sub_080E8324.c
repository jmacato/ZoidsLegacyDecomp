#include "m2c_prelude.h"
u8 func_080E7BCC(u8, u8, u8, u8);

s32 sub_080E8324(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    u8 temp_r2;
    s32 ret;

    temp_r2 = func_080E7BCC(arg0, arg1, arg2, arg3);
    ret = 0;
    switch (arg4) {
    case 0:
        if (temp_r2 <= 1) ret = 1;
        break;
    case 1:
        if (temp_r2 <= 2) ret = 1;
        break;
    case 2:
        if (temp_r2 <= 3) ret = 1;
        break;
    case 3:
        if (temp_r2 == 2) ret = 1;
        break;
    case 4:
        if ((u8) (temp_r2 - 2) <= 1) ret = 1;
        break;
    case 5:
        if (temp_r2 == 3) ret = 1;
        break;
    }
    return ret;
}
