#include "m2c_prelude.h"
void func_80D2328();
void func_80D0B60();

void sub_080D0F94(u8 arg0, u8 arg1, u16 arg2) {
    u8 *base = (u8 *)0x02033FD0;
    s32 zero = 0;
    *(s8 *)(base + 13) = 5;
    func_80D2328();
    *(s16 *)(base + 10) = 0x40;
    func_80D0B60((arg2 * 0x60) + 0x087D818C, arg0, arg1, arg2, zero, zero);
}
