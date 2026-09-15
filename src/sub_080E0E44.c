#include "m2c_prelude.h"
extern s32 func_80D22B4(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_087AA244[];

void sub_080E0E44(s32 *arg0) {
    arg0[0x23] = 0;
    arg0[3] = func_80D22B4(D_087AA244, 0x74, 0, 0x80, 0x80, 0, 0,
                           (*arg0 & 2) ? 0x9298 : 0x1298,
                           0, ((u32)*arg0 >> 1) & 1);
    arg0[4] = func_80D22B4(D_087AA244, 0x74, 1, 0x80, 0x80, 0, 0,
                           (*arg0 & 2) ? 0x90D8 : 0x10D8,
                           0, ((u32)*arg0 >> 1) & 1);
}
