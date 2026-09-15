#include "m2c_prelude.h"
u8 func_08093B7C();
M2C_UNK func_0809544C(s32, s32, s32, s32);
M2C_UNK func_080BB0B0();
M2C_UNK func_080BB474();
M2C_UNK func_080BB764();
M2C_UNK func_080ED17C(s32);

extern s32 D_03000054[];
extern s32 D_030033C4;

void sub_080BB8EC(void) {
    register s32 *temp_r5 asm("r5") = D_03000054;
    u8 temp_r4;
    s32 var_r0;
    s32 var_r1;

loop_1:
    func_080BB474();
    temp_r4 = func_08093B7C();
    func_080BB764();
    var_r0 = D_030033C4;
    if (var_r0 < 0) {
        var_r0 += 3;
    }
    temp_r5[0] = var_r0 >> 2;
    temp_r5[1] = (0x80 - temp_r4) << 8;
    var_r1 = 0xFF00;
    if (temp_r4 != 0xFF) {
        var_r1 = temp_r4;
    }
    func_0809544C(0xF0, var_r1, 0, 0);
    func_080BB0B0();
    func_080ED17C(1);
    goto loop_1;
}
