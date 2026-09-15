#include "m2c_prelude.h"
M2C_UNK func_08095114(void *);                      /* extern */
M2C_UNK func_080D1C70();                            /* extern */
u8 func_080D1E38();                                 /* extern */
M2C_UNK func_080D2790(s32);                         /* extern */

void sub_080DBE60(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x8C) == 0) {
        func_080D1C70();
        func_080D2790(0);
        M2C_FIELD(arg0, s32 *, 0x8C) = (s32) (M2C_FIELD(arg0, s32 *, 0x8C) + 1);
        return;
    }
    if (func_080D1E38() == 1) {
        func_08095114(arg0);
    }
}
