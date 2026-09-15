#include "m2c_prelude.h"
struct Entry {
    s32 flags;
    s32 f4;
    s32 f8;
    u16 fC;
    u16 fE;
};

extern struct Entry D_03005DE8[];

s32 sub_08095254(s32 arg0, s32 arg1, u16 arg2, u16 arg3) {
    struct Entry *p;
    u8 i;
    i = 0;
    p = &D_03005DE8[0];
    if (D_03005DE8[0].flags & 1) {
        do {
            i = i + 1;
            if (i > 15) break;
            p = &D_03005DE8[i];
        } while (p->flags & 1);
    }
    if (i == 16) {
        return 0;
    }
    p->flags = 3;
    p->f4 = arg0;
    p->f8 = arg1;
    p->fC = arg2;
    p->fE = arg3;
    return 1;
}
