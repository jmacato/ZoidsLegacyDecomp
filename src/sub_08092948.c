#include "m2c_prelude.h"
M2C_UNK func_080ECD2C(s32, s32, u32);
void sub_08092948(void *arg0) {
    register s32 temp_r3 asm("r3") = M2C_FIELD(arg0, s32 *, 0);
    register s32 temp_r1 asm("r1") = M2C_FIELD(arg0, s32 *, 4);
    register u32 temp_r2 asm("r2") = M2C_FIELD(arg0, u32 *, 8);
    func_080ECD2C(temp_r3, temp_r1, (u32)((temp_r2 + (temp_r2 >> 31)) << 10) >> 11);
}
