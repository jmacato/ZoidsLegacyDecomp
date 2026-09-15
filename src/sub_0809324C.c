#include "m2c_prelude.h"
extern u8 D_030032D4;
void func_80ECD2C(int, void *, int);

void sub_0809324C(int arg0) {
    s8 *base;
    s32 var_r5;
    u16 *var_r1;
    u32 var_r2;

    var_r5 = 0;
    base = (s8 *)&D_030032D4;
    M2C_FIELD(M2C_FIELD(base, u8 * volatile *, 0x1C), u8 *, 0) = (u8) M2C_FIELD(base, u8 *, 0xB);
    M2C_FIELD(M2C_FIELD(base, u8 * volatile *, 0x1C), s8 *, 1) = (s8) (M2C_FIELD(base, u8 *, 2) ^ M2C_FIELD(base, u8 *, 3));
    M2C_FIELD(M2C_FIELD(base, u8 * volatile *, 0x1C), s16 *, 2) = var_r5;
    func_80ECD2C(arg0, M2C_FIELD(base, u8 * volatile *, 0x1C) + 4, 0x04000004);
    var_r2 = 0;
    var_r1 = (u16 *) M2C_FIELD(base, u8 * volatile *, 0x1C);
    do {
        var_r5 += *var_r1;
        var_r1 += 1;
        var_r2 += 1;
    } while (var_r2 <= 9U);
    M2C_FIELD(M2C_FIELD(base, u8 * volatile *, 0x1C), s16 *, 2) = (s16) (~var_r5 - 0xC);
    M2C_FIELD(base, s8 *, 4) = 1;
}
