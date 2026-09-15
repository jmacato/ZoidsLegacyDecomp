#include "m2c_prelude.h"
extern u8 D_02032E60;
extern u8 D_02032E64;
extern u8 D_02032E65;
extern u8 D_02032E68;
s32 func_8094484(M2C_UNK, M2C_UNK, s32, s16, s32, s32, s32, s32, s32); /* extern */
void *func_809716C(u8);                                /* extern */
M2C_UNK func_80E2C24();                                /* extern */

void sub_080E2DCC(u8 arg0, s32 arg1) {
    u8 temp_r4;
    void *temp_r5;

    temp_r4 = arg0;
    temp_r5 = func_809716C(temp_r4);
    *(s32 *)((u32)&D_02032E60) = arg1;
    *(u8 *)((u32)&D_02032E64) = temp_r4;
    *(s8 *)((u32)&D_02032E65) = 0;
    M2C_FIELD((void *)((u32)&D_02032E68), s32 *, 0) = func_8094484(0x080ED578, 0x080ED5A0, 0, (s16) (((M2C_FIELD(temp_r5, u16 *, 4) + M2C_FIELD(temp_r5, u16 *, 8)) - 1) * 8), (s32) (s16) ((M2C_FIELD(temp_r5, u16 *, 6) + 1) * 8), 0x3E6, 0xF, 0x20430, 0);
    M2C_FIELD((void *)((u32)&D_02032E68), s32 *, 4) = func_8094484(0x080ED620, 0x080ED648, 0, (s16) (((M2C_FIELD(temp_r5, u16 *, 4) + M2C_FIELD(temp_r5, u16 *, 8)) - 1) * 8), (s32) (s16) (((M2C_FIELD(temp_r5, u16 *, 6) + M2C_FIELD(temp_r5, u16 *, 0xA)) - 2) * 8), 0x3E8, 0xF, 0x20430, 0);
    func_80E2C24();
}
