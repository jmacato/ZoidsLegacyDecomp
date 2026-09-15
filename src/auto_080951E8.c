#include "m2c_prelude.h"
void sub_080951E8(void) {
    u8 var_r1;

    var_r1 = 0;
    do {
        M2C_FIELD((var_r1 * 0x10), s32 *, 0x03005DE8) = 0;
        var_r1 += 1;
    } while ((u32) var_r1 <= 0xFU);
}
