#include "m2c_prelude.h"
struct Slot {
    s32 used;
    s32 a;
    s32 b;
    s32 c;
};

extern struct Slot D_03005DE8[];

s32 sub_08095208(s32 arg0, s32 arg1, u16 arg2) {
    u8 i;
    struct Slot *p;

    i = 0;
    p = D_03005DE8;
    if (D_03005DE8[0].used & 1) {
        do {
            i++;
            if (i > 15) break;
            p = &D_03005DE8[i];
        } while (p->used & 1);
    }
    if (i == 16) {
        return 0;
    }
    p->used = 1;
    p->a = arg0;
    p->b = arg1;
    p->c = arg2;
    return 1;
}
