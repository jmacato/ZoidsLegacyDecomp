#include "m2c_prelude.h"
s32 sub_080E6664(u8 arg0) {
    s32 var_r0;

    var_r0 = *(s32 *)0x0202F090 & (1 << arg0);
    if (var_r0 != 0) {
        var_r0 = 1;
    }
    return var_r0;
}
