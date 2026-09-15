#include "m2c_prelude.h"
s32 sub_080D1E38(void) {
    register s32 var_r0 asm("r0");
    register u8 temp_r1 asm("r1");

    temp_r1 = *(u8 *)0x02034863;
    if (temp_r1 != 0) {
        var_r0 = 0;
        if (temp_r1 == 2) {
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_r0;
    }
    var_r0 = 2;
    return var_r0;
}
