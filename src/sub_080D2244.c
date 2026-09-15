#include "m2c_prelude.h"
extern u8 D_02034869;
extern u8 D_0203486A;
extern s32 D_03000054[];
s16 func_08092A90(s32);
void func_080D220C(void);

void sub_080D2244(void) {
    s32 temp_r1;
    s32 temp_r2;
    s32 temp_r3;
    s32 var_r0;
    s32 first;
    s32 *base;
    u8 *ctrl;

    if (D_02034869 == 1) {
        goto block_6;
    }
    if (D_02034869 == 2) {
        first = D_0203486A;
        temp_r1 = 0x7F;
        temp_r1 &= first;
        if ((temp_r1 == 0) || (temp_r1 == 0x40)) {
            func_080D220C();
            return;
        }
block_6:
        base = D_03000054;
        ctrl = &D_0203486A;
        temp_r2 = (s16)func_08092A90(*ctrl * 2);
        temp_r3 = base[0];
        if (*ctrl & 1) {
            var_r0 = temp_r3 - (temp_r2 * 8);
        } else {
            var_r0 = temp_r3 + (temp_r2 * 8);
        }
        base[2] = var_r0;
        D_0203486A++;
    }
}
