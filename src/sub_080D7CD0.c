#include "m2c_prelude.h"
s32 func_080ECD5C(s32);                             /* extern */

void sub_080D7CD0(s32 *arg0) {
    s32 *p8c = (s32 *)((u8 *)arg0 + 0x8C);
    s32 *p90 = (s32 *)((u8 *)arg0 + 0x90);
    *p90 = 0;
    *p8c = 0;
    arg0[0x94 / 4] = arg0[1] + ((u32)(func_080ECD5C(*(s32 *)0x03000010) * 0x41) >> 15) - 0x20;
}
