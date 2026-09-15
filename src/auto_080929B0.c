#include "m2c_prelude.h"
M2C_UNK func_080ECD64(s32, s32, s32);               /* extern */

void sub_080929B0(void *arg0) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 4);
    func_080ECD64(temp_r1, temp_r1, M2C_FIELD(arg0, s32 *, 0));
}
