#include "m2c_prelude.h"
u8 func_80E523C(u8);
void sub_080B6768(void *arg0) {
    u8 var_r4;
    u8 *base;
    *(u8 *)0x02032472 = 0;
    var_r4 = 0;
    base = (u8 *)0x0203246C;
    do {
        if ((((s32) M2C_FIELD(arg0, u8 *, 3) >> var_r4) & 1) && (func_80E523C(M2C_FIELD(arg0, u8 *, 0)) != var_r4)) {
            *(u8 *)(*(u8 *)0x02032472 + (s32)base) = var_r4;
            *(u8 *)0x02032472 += 1;
        }
        var_r4 += 1;
    } while ((u32) var_r4 <= 5U);
}
