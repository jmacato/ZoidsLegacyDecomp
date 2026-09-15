#include "m2c_prelude.h"
extern void func_8094564(s32 *, s32);

struct S {
    u8 pad0[0xc];
    s32 *w0c;
    s32 *w10;
    u8 pad14[0x78];
    s32 w8c;
    s32 w90;
};

void sub_080E0EE0(struct S *arg0) {
    s32 *p8c;
    s32 v;
    s32 m;
    s32 mask;
    s32 *pa;
    s32 r;
    s32 x;

    p8c = &arg0->w8c;
    v = *p8c;
    if (v == 1) {
        pa = arg0->w0c;
        r = *pa;
        m = ~8;
        *pa = r & m;
        *arg0->w10 &= m;
        if (arg0->w90 != 0) {
            func_8094564(pa, 2);
            func_8094564(arg0->w10, 3);
        }
        *p8c = 2;
    } else if (v == 2) {
        x = *arg0->w0c;
        mask = 4;
        if ((x & mask) != 0) {
            if ((*arg0->w10 & mask) != 0) {
                *p8c = 0xff;
            }
        }
    }
}
