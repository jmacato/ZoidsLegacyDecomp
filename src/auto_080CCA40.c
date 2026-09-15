#include "m2c_prelude.h"
void sub_080CCA40(void) {
    s32 *temp_r1;
    u8 var_r2;

    var_r2 = 0;
    do {
        temp_r1 = M2C_FIELD((var_r2 * 4), s32 **, 0x02033F58);
        *temp_r1 |= 0x20000;
        var_r2 += 1;
    } while ((u32) var_r2 <= 6U);
}
