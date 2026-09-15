#include "m2c_prelude.h"
M2C_UNK func_0809A1BC(s32, s32, M2C_UNK);
M2C_UNK func_080ECD34(s32, s32);
extern u32 D_06010000;
extern u32 D_05000200;
extern u32 D_02002880;

void sub_0809AA64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_r5;

    arg1 = arg1 << 0x18;
    arg2 = arg2 << 0x10;
    arg3 = arg3 << 0x10;
    arg3 = (u32)arg3 >> 0x10;
    temp_r5 = arg0 + ((u32)arg1 >> 0x15);
    func_080ECD34(M2C_FIELD(temp_r5, s32 *, 0), ((u32)arg2 >> 0xB) + (s32)&D_06010000);
    func_0809A1BC(M2C_FIELD(temp_r5, s32 *, 4), (arg3 << 5) + (s32)&D_05000200, (s32)&D_02002880);
}
