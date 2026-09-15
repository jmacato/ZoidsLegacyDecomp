#include "m2c_prelude.h"
struct S { s32 f0; s32 pad[2]; s32 *arr[32]; };
void func_8094554(s32 *);
void sub_08095114(struct S *arg0) {
    u8 var_r4; s32 *temp_r2;
    arg0->f0 &= ~1;
    var_r4 = 0;
    do {
        temp_r2 = arg0->arr[var_r4];
        if ((temp_r2 != 0) && (*temp_r2 & 1)) {
            func_8094554(temp_r2);
        }
        var_r4 += 1;
    } while ((u32) var_r4 <= 0x1FU);
}
