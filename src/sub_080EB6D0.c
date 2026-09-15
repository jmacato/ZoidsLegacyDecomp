#include "m2c_prelude.h"
extern void func_80ECD2C();
extern void func_80EBAD0();
extern void func_80EB98C();
extern void func_80EBC40();
extern void func_80EBDC8();
extern u8 D_086A4694[];
extern u8 D_080EAB29[];
extern u8 D_00000004[];

void sub_080EB6D0(void) {
    u8 *p;
    u16 n;
    u32 c;
    void *r4;
    func_80ECD2C((s32)D_080EAB29 & ~1, 0x03007758, 0x040000E0);
    func_80EBAD0(0x03006B30);
    func_80EB98C(0x03007540);
    func_80EBC40(0x0099E800);
    n = (u16)(u32)D_00000004;
    if (n != 0) {
        p = D_086A4694;
        c = n;
        do {
            r4 = *(void **)p;
            func_80EBDC8(r4, *(s32 *)(p + 4), *(u8 *)(p + 8));
            *(s8 *)((char *)r4 + 0xB) = *(u16 *)(p + 0xA);
            *(s32 *)((char *)r4 + 0x18) = 0x03007700;
            p += 0xC;
            c -= 1;
        } while (c != 0);
    }
}
