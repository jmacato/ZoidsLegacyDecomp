#include "m2c_prelude.h"
void func_8095114(void);
u8 func_80D1E38(void);
void func_80D1D5C(void);
s32 func_80D222C(void);
void func_80D220C(void);

void sub_080D120C(void) {
    u8 var_r4;
    s8 *p = (s8 *)0x02033FD0;
    s32 *arr;
    *p = 0;
    var_r4 = 0;
    arr = (s32 *)(p + 0x20);
    do {
        if (arr[var_r4] != 0) {
            func_8095114();
        }
        var_r4 += 1;
    } while ((u32) var_r4 <= 0xF);
    if ((u32) func_80D1E38() <= 1) {
        func_80D1D5C();
    }
    if ((func_80D222C() << 0x18) == 0) {
        func_80D220C();
    }
    if (*(u8 *)0x02034860 != 0) {
        *(u16 *)0x0300004C = (0xFDFF & *(u16 *)0x0300004C) | 0x400;
        *(u8 *)0x02034860 = 0;
    }
    if (*(u8 *)0x02034861 != 0) {
        *(u16 *)0x0300004C = 0xFDFF & *(u16 *)0x0300004C;
        *(u8 *)0x02034861 = 0;
    }
}
