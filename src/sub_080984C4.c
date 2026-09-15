#include "m2c_prelude.h"
M2C_UNK func_8098284();
void *func_809716C(u8);
M2C_UNK func_80971AC(u8);
M2C_UNK func_8097DA8(void *, M2C_UNK);
void sub_080984C4(M2C_UNK arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    u8 temp_r6 = (u8) arg4;
    s32 c = 0x02021676;
    void *temp_r0;
    func_8098284(arg0, arg1, arg3);
    temp_r0 = func_809716C(temp_r6);
    M2C_FIELD(temp_r0, u8 *, 0x12) = arg2;
    func_8097DA8(temp_r0, c);
    M2C_FIELD(temp_r0, s32 *, 0) = (s32) (M2C_FIELD(temp_r0, s32 *, 0) | 2);
    func_80971AC(temp_r6);
}
