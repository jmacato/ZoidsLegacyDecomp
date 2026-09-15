#include "m2c_prelude.h"
void sub_08094564(void *arg0, s16 arg1) {
    s32 z = 0;
    *(s16 *)((u8 *)arg0 + 0x12) = arg1;
    *(s16 *)((u8 *)arg0 + 0x14) = z;
    *(s16 *)((u8 *)arg0 + 0x16) = z;
    *(s32 *)arg0 = *(s32 *)arg0 & -5;
}
