#include "m2c_prelude.h"
extern void func_809E204(s32, s32, s32, s32);
extern void func_80ECD2C(void *, void *, s32);
extern s32 D_020217B4[];
extern u8 D_0202ECF4[];

void sub_0809A048(void) {
    s32 local = 0;
    u8 *r4 = D_0202ECF4;
    register s32 v asm("r0");
    func_80ECD2C(&local, r4, 0x05000073);
    r4[2] = 0x69;
    D_020217B4[4] |= 0x80000;
    *(s32 *)(r4 + 0xC) = 0xCB000;
    *(s32 *)(r4 + 0x10) = 0xF1000;
    func_809E204(0, 0, 0, 0);
    v = 0xFFFF;
    *(u16 *)(r4 + 0x26) = v;
}
