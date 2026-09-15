#include "m2c_prelude.h"
extern void func_80D1E58(void);
extern s32 D_03000054[];
extern u16 D_0300004C;

void sub_080D1C70(void)
{
    *(s8 *)0x02034863 = 1;
    *(s16 *)0x02034864 = 0;
    *(u8 *)0x03000074 |= 4;
    D_03000054[3] = 0;
    D_0300004C |= 0x200;
    *(u16 *)0x0400000A = *(u16 *)0x0400000C;
    *(s8 *)0x02034862 = 1;
    func_80D1E58();
}
