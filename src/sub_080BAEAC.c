#include "m2c_prelude.h"
struct S {
    u32 f0;
    u16 f4;
    u16 f6;
    u8 pad[0x28 - 8];
    struct S *f28;
    u32 f2c;
};

void sub_080BAEAC(struct S *r2) {
    u32 v = r2->f0 & 0xFFFDFFFF;
    r2->f0 = v;
    if (r2->f2c == 0) {
        struct S *o = r2->f28;
        u32 fo = o->f0;
        u32 m = 0x20000;
        if ((fo & m) == 0) {
            r2->f4 = o->f4 - 0x30;
            r2->f6 = o->f6;
        } else {
            r2->f0 = v | m;
        }
    } else {
        r2->f0 = v | r2->f2c;
    }
}
