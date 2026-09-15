#include "m2c_prelude.h"
extern u8 D_020322B1;
extern u8 D_020217F4[];
extern u8 D_020322A8[];

void sub_080B654C(void) {
    u8 var_r2;
    u8 var_r3;

    D_020322B1 = 0;
    var_r3 = 1;
    do {
        if ((u32) (u8) (var_r3 - 1) <= 2U) {
            var_r2 = 4 - var_r3;
        } else {
            var_r2 = var_r3;
        }
        if (D_020217F4[var_r2] != 0) {
            D_020322A8[D_020322B1] = var_r2;
            D_020322B1 += 1;
        }
        var_r3 += 1;
    } while ((u32) var_r3 <= 9U);
}
