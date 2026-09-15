#include "m2c_prelude.h"
void sub_080C9EE0(void) {
    u8 var_r1;

    var_r1 = 0;
    do {
        M2C_FIELD((var_r1 * 4), s32 *, 0x02032F64) = 0;
        var_r1 += 1;
    } while ((u32) var_r1 <= 5U);
}
