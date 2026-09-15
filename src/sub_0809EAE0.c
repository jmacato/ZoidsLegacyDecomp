#include "m2c_prelude.h"
struct S {
    s8 a;
    u8 b;
    s16 c;
    s32 d;
    s32 e;
    s32 f;
};

extern struct S D_020314A4;
extern u8 D_03000074;
extern s8 D_020324B8;
extern void func_80925A4(void);

void sub_0809EAE0(void) {
    register s32 x asm("r1");
    struct S *p;
    s32 z;
    s32 fld;
    u8 t;
    p = &D_020314A4;
    z = 0;
    x = 0x5F;
    p->a = x;
    fld = p->b;
    x -= 0x61;
    x &= fld;
    p->b = x;
    p->c = z;
    p->d = 0x0809EA8D;
    p->f = z;
    p->e = z;
    func_80925A4();
    t = D_03000074;
    t |= 0x10;
    D_03000074 = t;
    D_020324B8 = 1;
}
