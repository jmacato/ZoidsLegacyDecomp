#include "m2c_prelude.h"
extern s32 D_03000010;
s32 func_80ECD5C();

void sub_080D701C(s32 *arg0) {
    s32 *p8c = (s32 *)((u8 *)arg0 + 0x8c);
    s32 *p98 = (s32 *)((u8 *)arg0 + 0x98);
    *p98 = 0;
    *p8c = 0;
    *(s32 *)((u8 *)arg0 + 0x90) =
        (arg0[1] + (s32)((u32)(func_80ECD5C(D_03000010) * 65) >> 15)) - 0x20;
    {
        s32 r = func_80ECD5C(D_03000010);
        s32 *p94 = (s32 *)((u8 *)arg0 + 0x94);
        s32 v = arg0[2] - 0x10;
        *p94 = v + (s32)((u32)(r * 33) >> 15);
    }
}
