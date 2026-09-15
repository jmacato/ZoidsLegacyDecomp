#include "m2c_prelude.h"
extern u8 D_02032379;
extern u8 D_02028218[];
extern s8 D_020322B2[];

void sub_080B65A4(void) {
    u8 var_r2;
    D_02032379 = 0;
    var_r2 = 1;
    do {
        if (D_02028218[var_r2] != 0) {
            D_020322B2[D_02032379] = var_r2;
            D_02032379 += 1;
        }
        var_r2 += 1;
    } while ((u32)var_r2 <= 0xC7U);
}
