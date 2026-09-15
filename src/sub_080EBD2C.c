#include "m2c_prelude.h"
extern void func_80ECD2C(void *, void *, s32, s32);
extern s32 *D_03007FF0;
extern s32 D_040000C4;
extern s16 D_040000C6;

void sub_080EBD2C(void) {
    s32 local;
    s32 *p = D_03007FF0;
    s32 v = *p;
    if ((u32)(v + 0x978C92AD) <= 1U) {
        *p = v + 0xA;
        if (D_040000C4 & 0x02000000) {
            D_040000C4 = 0x84400004;
        }
        D_040000C6 = 0x400;
        local = 0;
        func_80ECD2C(&local, (u8 *)p + 0x350, 0x0500018C, 0x400);
    }
}
