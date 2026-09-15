#include "m2c_prelude.h"
void sub_080B6810(u8 *arg0) {
    u8 temp_r1;
    u8 var_r3;
    register u8 *counter asm("r2");
    u8 *base;
    u8 *out;
    u8 *dest;

    counter = (u8 *)0x02032492;
    *counter = 0;
    var_r3 = 0;
    base = arg0 + 10;
    out = (u8 *)0x02032488;
    do {
        temp_r1 = base[var_r3];
        if (temp_r1 != 0) {
            dest = (u8 *)(u32)*counter;
            dest += (u32)out;
            *dest = temp_r1;
            *counter += 1;
        }
        var_r3 += 1;
    } while ((u32)var_r3 <= 9U);
}
