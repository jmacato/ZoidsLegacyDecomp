#include "m2c_prelude.h"
void sub_08092C48(u16 arg0, u16 *arg1, s32 arg2) {
    s32 var_r2;
    u16 *var_r1;

    var_r1 = arg1;
    var_r2 = arg2 - 1;
    if (var_r2 != -1) {
        do {
            *var_r1 = arg0;
            var_r1 += 1;
            var_r2 -= 1;
        } while (var_r2 != -1);
    }
}
