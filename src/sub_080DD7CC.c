#include "m2c_prelude.h"
void sub_080DD7CC(void *arg0) {
    register s32 *var_r2 asm("r2");
    register s32 *var_r0 asm("r0");
    register s32 var_r1 asm("r1");

    var_r2 = arg0;
    var_r2 += 0x23;
    var_r0 = arg0;
    var_r0 += 0x24;
    var_r1 = 0;
    *var_r0 = var_r1;
    *var_r2 = var_r1;
}
