#include "m2c_prelude.h"
extern s32 D_02032E8C[][6];
extern s32 D_087A288C[];
void func_80C9164();

void sub_080C9204(s32 *arg0) {
    s32 *pcnt = &arg0[0x23];
    s32 idx = *pcnt;
    if ((u32)idx <= 8) {
        s32 *p = (s32 *)D_02032E8C[arg0[0x29]][arg0[0x2a]];
        p[10] += D_087A288C[idx];
        *pcnt += 1;
    }
    func_80C9164(arg0);
}
