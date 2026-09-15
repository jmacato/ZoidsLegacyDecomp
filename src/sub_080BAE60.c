#include "m2c_prelude.h"
extern s16 func_8093E30(void *, void *, u8 *);

struct S {
    s32 f00;
    u8 f04;
    u8 _p05[7];
    s16 f0C;
    u8 _p0E[0x1a];
    u8 f28;
};

void sub_080BAE60(struct S *s) {
    u8 local;
    s32 v;
    v = func_8093E30(&s->f28, &s->f04, &local) / 2;
    s->f0C = v;
    if (local == 0 || v > 0x300) {
        s->f00 |= 0x20000;
    } else {
        s->f00 &= ~0x20000;
    }
}
