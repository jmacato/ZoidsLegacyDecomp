#include "m2c_prelude.h"
void *func_0809716C();
M2C_UNK func_080971AC(u8);
M2C_UNK func_08097DA8(void *, M2C_UNK);

void sub_080981F0(M2C_UNK arg0, u8 arg1, u8 arg2, u16 arg3, u16 arg4) {
    s32 sp0;
    u8 temp_r1;
    void *temp_r0;
    temp_r1 = arg1;
    sp0 = (s32)temp_r1;
    temp_r0 = func_0809716C();
    M2C_FIELD(temp_r0, u16 *, 0xC) = arg3;
    M2C_FIELD(temp_r0, u16 *, 0xE) = (u16)arg4;
    M2C_FIELD(temp_r0, u8 *, 0x12) = sp0;
    func_08097DA8(temp_r0, arg0);
    M2C_FIELD(temp_r0, s32 *, 0) = (s32)(M2C_FIELD(temp_r0, s32 *, 0) | 2);
    func_080971AC(arg2);
}
