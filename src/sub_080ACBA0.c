#include "m2c_prelude.h"
M2C_UNK func_8094554(s32);
void sub_080ACBA0(u8 arg0) {
    u8 i = 0;
    if (i < arg0) {
        s32 *a = (s32 *)0x02032A88;
        do {
            func_8094554(a[i]);
            func_8094554(*(s32 *)(0x02032AA8 + i * 4));
            i++;
        } while (i < arg0);
    }
}
