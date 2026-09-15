#include "m2c_prelude.h"
extern u8 func_80A9EF0(u8);
extern void func_8094554(s32);

struct S {
    s32 f00;
    u8 _pad04[0x1c];
    s32 f20;
    s32 f24;
    u8 _pad28[0x20];
};

extern struct S D_020325A0[];
extern struct S *D_02032990;

void sub_080A9F40(u8 arg0) {
    struct S *p = &D_020325A0[func_80A9EF0(arg0)];
    func_8094554(p->f20);
    if (p->f24 != 0) {
        func_8094554(p->f24);
    }
    p->f00 = p->f00 & ~1;
    if (p == D_02032990) {
        D_02032990 = 0;
    }
}
