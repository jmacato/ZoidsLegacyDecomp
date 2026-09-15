#include "m2c_prelude.h"
M2C_UNK func_80ED128(u8 *);

u8 *sub_08099F5C(u8 *arg0) {
    register u8 *var_r2 asm("r2") = arg0;
    u8 *temp_r4 = var_r2;
    if (*temp_r4 != 0) {
        do {
            var_r2 += 1;
        } while (*var_r2 != 0);
    }
    func_80ED128(var_r2);
    return temp_r4;
}
