#include "m2c_prelude.h"
void sub_080DCEA8(void *arg0) {
    register s32 *var_r3 asm("r3");
    register s32 *var_r2 asm("r2");
    register s32 *var_r1 asm("r1");
    register s32 var_r0 asm("r0");

    var_r3 = arg0;
    var_r3 += 0x23;
    var_r2 = arg0;
    var_r2 += 0x24;
    var_r1 = arg0;
    var_r1 += 0x25;
    var_r0 = 0;
    *var_r1 = var_r0;
    *var_r2 = var_r0;
    *var_r3 = var_r0;
}
