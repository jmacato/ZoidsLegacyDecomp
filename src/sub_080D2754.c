#include "m2c_prelude.h"
s32 sub_080D2754(void *arg0, s32 arg1, s32 arg2) {
    if (!(M2C_FIELD(arg0, s32 *, 0) & 0x8000)) {
        if (M2C_FIELD(arg0, s16 *, 4) == (0xF0 - arg1)) {
            goto block_4;
        }
        goto block_6;
    }
    if (M2C_FIELD(arg0, s16 *, 4) == arg1) {
block_4:
        if (M2C_FIELD(arg0, s16 *, 6) == arg2) {
            return 1;
        }
        goto block_6;
    }
block_6:
    return 0;
}
