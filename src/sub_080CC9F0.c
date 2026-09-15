#include "m2c_prelude.h"
M2C_UNK func_8094554(s32);

void sub_080CC9F0(void) {
    u8 i = 0;
    s32 *base = (s32 *)0x02033F58;
    for (; i <= 6; i++) {
        func_8094554(base[i]);
    }
}
