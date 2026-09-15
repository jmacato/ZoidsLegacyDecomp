#include "m2c_prelude.h"
extern void func_80ECD2C(void *, void *, s32);
extern void func_80EAEC0(s32);
extern void func_80EBB9C(s32);

void sub_080EBAD0(void *arg0) {
    s32 sp0;
    s32 z = 0;
    M2C_FIELD(arg0, s32 *, 0) = z;
    if (*(s32 *)0x040000C4 & 0x02000000) {
        *(s32 *)0x040000C4 = 0x84400004;
    }
    *(s16 *)0x040000C6 = 0x400;
    *(s16 *)0x04000084 = 0x8F;
    *(s16 *)0x04000082 = 0xB0E;
    *(u8 *)0x04000089 = (0x3F & *(u8 *)0x04000089) | 0x40;
    M2C_FIELD((void *)0x040000BC, void **, 0) = (void *) ((s8 *)arg0 + 0x350);
    M2C_FIELD((void *)0x040000BC, s32 *, 4) = 0x040000A0;
    *(void **)0x03007FF0 = arg0;
    sp0 = z;
    func_80ECD2C(&sp0, arg0, 0x05000260);
    M2C_FIELD(arg0, s8 *, 6) = 8;
    M2C_FIELD(arg0, s8 *, 7) = 0xF;
    M2C_FIELD(arg0, s32 *, 0x38) = 0x080EB39D;
    M2C_FIELD(arg0, s32 *, 0x28) = 0x080ECB79;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0x080ECB79;
    M2C_FIELD(arg0, s32 *, 0x30) = 0x080ECB79;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0x080ECB79;
    func_80EAEC0(0x030074B0);
    M2C_FIELD(arg0, s32 *, 0x34) = 0x030074B0;
    func_80EBB9C(0x40000);
    M2C_FIELD(arg0, s32 *, 0) = 0x68736D53;
}
