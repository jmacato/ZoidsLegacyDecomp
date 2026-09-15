#include "m2c_prelude.h"
M2C_UNK func_8094554();

void sub_080CCBAC(void) {
    u8 i = 0;
    s32 *base = (s32 *)0x02033FB4;
    for (; i <= 5; i++) {
        if (base[i] != 0) {
            func_8094554();
        }
    }
}
