#include "m2c_prelude.h"
struct Vec { s32 a, b, c; };
struct S { struct Vec v; s32 x, y; };
extern u8 D_02032EF9;
extern struct S D_02032EFC;
extern struct S D_030033C4;
extern u8 D_02032F62;

void sub_080BB424(struct Vec *arg0, s32 *arg1, u8 arg2) {
    s32 t0, t1;
    D_02032EF9 = 7;
    D_02032EFC.v = *arg0;
    t0 = arg1[0];
    t1 = arg1[1];
    D_02032EFC.x = t0;
    D_02032EFC.y = t1;
    if (arg2 == 1) {
        s32 u0, u1;
        D_030033C4.v = D_02032EFC.v;
        u0 = D_02032EFC.x;
        u1 = D_02032EFC.y;
        D_030033C4.x = u0;
        D_030033C4.y = u1;
    }
    D_02032F62 = 0;
}
