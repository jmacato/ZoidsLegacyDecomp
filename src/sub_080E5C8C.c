#include "m2c_prelude.h"
extern u8 D_020218E4[];
u8 func_80E5A18(u8, u8);
u8 func_80E6C78(u8);
M2C_UNK func_80E6FA0(u8, u8);
s32 sub_080E5C8C(u8 arg0, u8 arg1, u8 arg2) {
    u8 temp_r5 = func_80E5A18(arg0, arg1);
    u8 temp_r0 = func_80E6C78(arg2);
    if ((temp_r5 != 0xFF) && (temp_r0 != 0xFF)) {
        func_80E6FA0(temp_r0, temp_r5);
        {
        register s32 b asm("r1");
        void *p;
        b = (s32)D_020218E4;
        p = (void *)(temp_r5 * 0x70 + b);
        M2C_FIELD(p, u16 *, 0xA) = M2C_FIELD(p, u16 *, 0x3E);
        M2C_FIELD(p, u16 *, 0xC) = M2C_FIELD(p, u16 *, 0x42);
        }
        return 1;
    }
    return 0;
}
