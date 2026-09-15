#include "m2c_prelude.h"
s32 sub_080AC098(void *arg0) {
    s32 var_r1;
    u8 temp_r0;

    var_r1 = 0;
    temp_r0 = M2C_FIELD(arg0, u8 *, 4);
    if ((temp_r0 == 0x69) || (temp_r0 == 0x6E) || (temp_r0 == 0x6F) || (temp_r0 == 0x6A) || (temp_r0 == 0x6B) || (temp_r0 == 0x6C) || (temp_r0 == 0x8D) || (temp_r0 == 0x8E)) {
        var_r1 = 1;
    }
    return var_r1;
}
