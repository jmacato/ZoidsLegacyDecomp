#include "m2c_prelude.h"
void sub_080B6728(void) {
    void *var_r2;

    *(u8 *)0x0203246B = 0;
    var_r2 = (void *)1;
    do {
        if (M2C_FIELD(var_r2, u8 *, 0x020217FE) != 0) {
            M2C_FIELD(*(u8 *)0x0203246B, s8 *, 0x02032412) = (s8) var_r2;
            *(u8 *)0x0203246B += 1;
        }
        var_r2 = (void *) (u8) (var_r2 + 1);
    } while ((u32) var_r2 <= 0x59U);
}
