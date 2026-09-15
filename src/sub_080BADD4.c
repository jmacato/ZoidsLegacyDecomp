#include "m2c_prelude.h"
s32 func_8093E30();

void sub_080BADD4(u32 *arg0) {
    u8 local;
    s32 ret;
    ret = func_8093E30((u8 *)arg0 + 0x28, arg0 + 1, &local);
    *(s16 *)((u8 *)arg0 + 12) = ret;
    if (local == 0 || (ret << 16) > 0x3000000) {
        arg0[0] |= 0x20000;
    } else {
        arg0[0] &= 0xFFFDFFFF;
    }
}
