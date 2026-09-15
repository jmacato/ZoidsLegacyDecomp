#include "m2c_prelude.h"
void func_80EB328(void *, s32);

void sub_080EBF24(void *arg0) {
    s32 temp_r1;
    s32 var_r4;
    s32 var_r5;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_r1 == 0x68736D53) {
        M2C_FIELD(arg0, s32 *, 0x34) = temp_r1 + 1;
        M2C_FIELD(arg0, s32 *, 4) = M2C_FIELD(arg0, s32 *, 4) | 0x80000000;
        var_r4 = M2C_FIELD(arg0, u8 *, 8);
        var_r5 = M2C_FIELD(arg0, s32 *, 0x2C);
        if (var_r4 > 0) {
            do {
                func_80EB328(arg0, var_r5);
                var_r4 -= 1;
                var_r5 += 0x50;
            } while (var_r4 > 0);
        }
        M2C_FIELD(arg0, s32 *, 0x34) = 0x68736D53;
    }
}
