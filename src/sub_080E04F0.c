#include "m2c_prelude.h"

void func_08095114(void *);
void *func_080D2450(void *, s32, s32, s16, s32, s32, s32, s32);
void func_080D2790(s32);

void sub_080E04F0(void *arg0) {
    s32 *state;
    s32 temp_r1;
    s32 var_r0;

    state = (s32 *)((u8 *)arg0 + 0x8C);
    temp_r1 = *state;
    if (temp_r1 == 0) {
        M2C_FIELD(arg0, void **, 0xC) = func_080D2450(arg0, 0, 0,
            M2C_FIELD(arg0, s16 *, 4),
            (s32)M2C_FIELD(arg0, s16 *, 8),
            0x400, temp_r1, temp_r1);
        var_r0 = 0;
        goto block_5;
    }
    if (temp_r1 == 1) {
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), u16 *, 0x14) == 0x1A) {
            var_r0 = 1;
block_5:
            func_080D2790(var_r0);
            *state = *state + 1;
        }
    } else if (M2C_FIELD(arg0, void **, 0xC) == 0) {
        func_08095114(arg0);
    }
}
