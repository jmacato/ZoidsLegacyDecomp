#include "m2c_prelude.h"
M2C_UNK func_080ECD2C(M2C_UNK *, s32, s32);

void sub_08092964(void *arg0) {
    register u16 *var_r2 asm("r2");
    register s32 var_r1 asm("r1");
    u32 temp_r2;
    s32 subroutine_arg0;

    var_r2 = (u16 *)&subroutine_arg0;
    *var_r2 = M2C_FIELD(arg0, u16 *, 0);
    var_r1 = M2C_FIELD(arg0, s32 *, 4);
    temp_r2 = M2C_FIELD(arg0, u32 *, 8);
    func_080ECD2C(&subroutine_arg0, var_r1, ((u32)((temp_r2 + (temp_r2 >> 0x1F)) << 0xA) >> 0xB) | 0x01000000);
}
