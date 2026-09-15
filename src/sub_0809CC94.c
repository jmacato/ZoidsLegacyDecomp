#include "m2c_prelude.h"

struct PointerRecord {
    u32 unused;
    void *value;
};

extern void func_08092E84(s32);
extern s32 func_080940AC(void);
extern void func_08094330(void);
extern void func_08094484();
extern void func_0809534C(void);
extern void func_0809538C(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_08096308(s32, s32);
extern s32 func_0809669C(void);
extern void func_08096FBC();
extern void func_080972C8(void);
extern void func_080981F0();
extern void func_08098BB4(s32);
extern void func_0809A94C(s32, s32, s32, s32, s32);
extern void func_0809AB44(s32, s32, s32, s32, s32);
extern void func_0809C45C(void);
extern void func_0809C5C8(s32, s32, s32, s32);
extern s32 func_0809C7B0(void);
extern void func_080ED128(void *, void *);
extern void func_080ED17C(s32);
extern u16 D_02021774[];

void sub_0809CC94(u8 arg0) {
    s32 *retry_pointer;
    s32 *p1;
    s32 *p2;
    s32 *p3;
    s32 input;
    s32 mask;
    s32 zero;
    s32 call_r1;
    s32 call_r2;

    *(s16 *)0x0300004C = 0x1140;
    func_08094330();
    func_08096FBC(0, 1, 0, 0x3C0, 0x3C0, 0, 0xE, 0, 0x3E6, 0xF);
    func_0809AB44(2, 3, 0, 0, 1);
    func_08098BB4(0x08000CF5);
    func_0809C5C8(0x02021774, 8, 3, 0xC);
    func_08094484(0x081058DC, 0x08105918,
        0, 0x60, 0x38, 0x36, 0xF, 8, 0);
    func_08094484(0x081058DC, 0x08105918,
        4, 0xA0, 0x38, 0x36, 0xF, 8, 0);
    func_0809A94C(1, 0, 0, 0x3C2, 0xE);
    func_08094484(0x08359850, 0x0835985C,
        0, 8, 8, 0x3C2, 0xE, 8, 0);
    func_08096308(0xF, 0x10);
    while ((func_0809669C() << 24) == 0) {
        func_080ED17C(1);
    }

    mask = 0x20000;
retry:
    call_r1 = 0x30C0;
    call_r2 = 0x2850;
    if ((func_0809C7B0() << 24) == 0) {
        goto retry_wait;
    }
    p1 = *(s32 **)0x020216F8;
    *p1 |= mask;
    p2 = *(s32 **)0x020216FC;
    *p2 |= mask;
    p3 = *(s32 **)0x02021700;
    *p3 |= mask;

    zero = 0;
    func_0809538C(1, call_r1, call_r2, 0, 0, 0, 0x2F, 0x3F);
    func_08098BB4(0x08000D0F);
    if (D_02021774[0] == 0) {
        func_080ED128(D_02021774,
            ((struct PointerRecord *)0x087EDFB4)->value);
        func_0809C45C();
    }
    func_080981F0(D_02021774, 2, 4, 0, zero);
    func_08098BB4(0x08000D3B);
    func_080972C8();
    func_0809534C();
    if (*(u8 *)0x0200A882 != 1) {
        goto retry_clear;
    }
    if (*(u8 *)0x0200A880 != 0) {
        goto retry_clear;
    }
    if (arg0 != 0) {
        input = func_080940AC();
        *(u8 *)0x0202169A = input;
        if ((input << 24) == 0) {
            func_080ED17C(1);
            func_08092E84(0x58);
            func_08098BB4(0x08000D92);
        }
    }
    goto final_wait;

retry_clear:
    retry_pointer = *(s32 **)0x020216F8;
    *retry_pointer &= 0xFFFDFFFF;
retry_wait:
    func_080ED17C(1);
    goto retry;

final_wait:
    func_08096308(0x10, 0x10);
    while ((func_0809669C() << 24) == 0) {
        func_080ED17C(1);
    }
}
