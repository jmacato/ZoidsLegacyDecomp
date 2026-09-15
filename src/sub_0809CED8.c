#include "m2c_prelude.h"

extern void func_08092E84(s32);
extern s32 func_080940AC(void);
extern void func_08094330(void);
extern void func_08094484(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_08096308(s32, s32);
extern s32 func_0809669C(void);
extern void func_08096FBC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_08098BB4(s32);
extern void func_0809AB44(s32, s32, s32, s32, s32);
extern void func_0809C45C(void);
extern void func_0809C5C8(s32, s32, s32, s32);
extern s32 func_0809C7B0(void);
extern void func_080ED128(void *, s32);
extern void func_080ED17C(s32);
extern u16 D_02021774[];

void sub_0809CED8(void) {
    s32 *retry_p;
    s32 *p1;
    s32 *p2;
    s32 input;
    s32 mask;

    *(s16 *)0x0300004C = 0x1140;
    func_08094330();
    func_08096FBC(0, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_0809AB44(2, 3, 0, 0, 1);
    func_08098BB4(0x08000D40);
    func_0809C5C8(0x02021786, 0x16, 0, 1);
    func_08094484(0x08106180, 0x08106198, 0, 8, 0x38, 0x122, 0xF, 8, 0);
    func_08094484(0x08106180, 0x08106198, 1, 0xB8, 0x38, 0x122, 0xF, 8, 0);
    func_08096308(0xF, 0x10);
    while ((func_0809669C() << 24) == 0) {
        func_080ED17C(1);
    }
    mask = 0x20000;
retry:
    if ((func_0809C7B0() << 24) == 0) {
        goto retry_no_clear;
    }
    {
        register s32 *first asm("r1");
        first = *(s32 **)0x020216F8;
        *first |= mask;
    }
    p1 = *(s32 **)0x020216FC;
    *p1 |= mask;
    p2 = *(s32 **)0x02021700;
    *p2 |= mask;
    if (D_02021774[9] == 0) {
        func_080ED128(&D_02021774[9], 0x080248A0);
        func_0809C45C();
    }
    func_08098BB4(0x08000D4F);
    if (*(u8 *)0x0200A882 != 1) {
        goto retry_clear;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto retry_clear;
    }
    input = func_080940AC();
    *(u8 *)0x0202169A = input;
    if ((input << 24) == 0) {
        func_08092E84(0x58);
        func_08098BB4(0x08000E00);
    }
    goto final_wait;

retry_clear:
    retry_p = *(s32 **)0x020216F8;
    *retry_p &= 0xFFFDFFFF;
retry_no_clear:
    func_080ED17C(1);
    goto retry;

final_wait:
    func_08096308(0x10, 0x10);
    while ((func_0809669C() << 24) == 0) {
        func_080ED17C(1);
    }
}
