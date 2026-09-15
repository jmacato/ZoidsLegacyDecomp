#include "m2c_prelude.h"
struct T {
    u32 flags;
    u16 h4;
    u16 h6;
};

struct S {
    u32 w0;
    u16 h4;
    u16 h6;
    u8 pad[0x20];
    struct T *p28;
    u32 w2c;
};

void sub_080BAEEC(struct S *p) {
    u32 v;
    u32 t;
    u32 mask;
    u32 fl;
    struct T *q;

    v = p->w0;
    v &= 0xFFFDFFFF;
    p->w0 = v;
    t = p->w2c;
    if (t == 0) {
        q = p->p28;
        fl = q->flags;
        mask = 0x20000;
        if ((fl & mask) == 0) {
            p->h4 = q->h4 + 16;
            p->h6 = q->h6;
        } else {
            v |= mask;
            p->w0 = v;
        }
    } else {
        v |= t;
        p->w0 = v;
    }
}
