#include "m2c_prelude.h"
extern u32 func_80ECD5C(u32);
extern u32 D_03000010;

struct S {
    u8 _p00[4];
    s32 f04;
    s32 f08;
    u8 _p0c[0x80];
    s32 f8c;
    s32 f90;
    s32 f94;
    s32 f98;
};

void sub_080D6590(struct S *s) {
    s->f8c = s->f98 = 0;
    s->f90 = s->f04 + (func_80ECD5C(D_03000010) * 65 >> 15) - 32;
    {
        u32 r = func_80ECD5C(D_03000010);
        s32 *p = &s->f94;
        s32 a = s->f08 - 16;
        *p = a + (r * 33 >> 15);
    }
}
