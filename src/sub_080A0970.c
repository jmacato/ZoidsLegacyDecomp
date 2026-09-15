#include "m2c_prelude.h"
s32 sub_080A0970(int arg0, u8 **arg1) {
    u8 *p = *arg1;
    *(u32 *)arg1 = p[1] | (p[2] << 8) | (p[3] << 16) | (p[4] << 24);
    return 0;
}
