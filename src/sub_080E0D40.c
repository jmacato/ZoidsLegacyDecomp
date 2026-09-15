#include "m2c_prelude.h"
struct T {
    u8 pad0[0xc];
    u32 *f0c;
    u32 *f10;
    u8 pad2[0x8c - 0x14];
    u32 f8c;
};

void sub_080E0D40(struct T *r3) {
    u32 *pf8c = &r3->f8c;
    u32 x = *pf8c;
    if (x == 1) {
        u32 *p;
        u32 t;
        register int m asm("r2");
        p = r3->f0c;
        t = *p;
        m = ~8;
        t &= m;
        *p = t;
        p = r3->f10;
        t = *p;
        t &= m;
        *p = t;
        *pf8c = 2;
    } else if (x == 2) {
        u32 a;
        int n;
        a = *r3->f0c;
        n = 4;
        if ((a & n) != 0) {
            a = *r3->f10;
            if ((a & n) != 0) {
                *pf8c = 0xff;
            }
        }
    }
}
