#include "m2c_prelude.h"
extern u8 D_0203237A[]; extern s32 D_087EDD54[];
void func_80988C8(u8, s32);
void sub_080AC6B8(u8 arg0) {
    u8 i = 0;
    if (i < *(u8 *)0x02032411) {
        do {
            func_80988C8(arg0, D_087EDD54[D_0203237A[i]]);
            i += 1;
        } while (i < *(u8 *)0x02032411);
    }
}
