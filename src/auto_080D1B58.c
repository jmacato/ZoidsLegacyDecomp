#include "m2c_prelude.h"
s32 sub_080D1B58(void) {
    s32 var_r1;

    var_r1 = 0;
    if ((u32) (u8) (*(u8 *)0x02034861 - 1) > 0x3FU) {
        var_r1 = 1;
    }
    return var_r1;
}
