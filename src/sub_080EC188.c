#include "m2c_prelude.h"
void sub_080EC188(u8 arg0) {
    s8 *var_r1;
    s8 var_r0;

    switch (arg0) {
    case 1:
        var_r1 = (s8 *)0x04000063;
        *var_r1 = 8;
        var_r1 += 2;
        goto block_12;
    case 2:
        var_r1 = (s8 *)0x04000069;
        goto block_11;
    case 3:
        var_r1 = (s8 *)0x04000070;
        var_r0 = 0;
        goto store;
    default:
        var_r1 = (s8 *)0x04000079;
block_11:
        *var_r1 = 8;
        var_r1 += 4;
block_12:
        var_r0 = 0x80;
store:
        *var_r1 = var_r0;
    }
}
