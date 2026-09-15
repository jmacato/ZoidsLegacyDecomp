#include "m2c_prelude.h"
extern s32 func_80D22B4(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_087AA244[];

void sub_080E0CA4(s32 *arg0) {
    arg0[0x23] = 0;
    arg0[3] = func_80D22B4(D_087AA244, 0x41, 0, 0x90, 0x59, 0, 0,
                           (*arg0 & 2) ? 0x9298 : 0x1298,
                           0, ((u32)*arg0 >> 1) & 1);
    arg0[4] = func_80D22B4(D_087AA244, 0x41, 0, 0x7C, 0x59, 0, 0,
                           (*arg0 & 2) ? 0x90D8 : 0x10D8,
                           0, ((u32)*arg0 >> 1) & 1);
}
