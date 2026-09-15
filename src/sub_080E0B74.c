#include "m2c_prelude.h"
struct Foo {
    u8 pad0[0xc];
    s32 *field_c;
    u8 pad10[0x8c - 0x10];
    s32 field_8c;
};

void sub_080E0B74(struct Foo *a) {
    s32 v = a->field_8c;
    if (v == 1) {
        s32 *p = a->field_c;
        *p = *p & ~8;
        a->field_8c = 2;
    } else if (v == 2) {
        s32 *p = a->field_c;
        if (*p & 4) {
            a->field_8c = 0xff;
        }
    }
}
