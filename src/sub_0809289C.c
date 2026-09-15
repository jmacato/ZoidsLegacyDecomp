#include "m2c_prelude.h"
struct Node { s32 unk0; s32 unk4; s32 unk8; u8 unk12; u8 pad[3]; };

void sub_0809289C(void) {
    void *base;
    void *var_r1;
    void *temp_r0;
    s32 var_r2;

    base = (void *)0x030009F0;
    var_r1 = base;
    var_r2 = 7;
    do {
        temp_r0 = (s8 *)var_r1 + 0x10;
        *(void **)var_r1 = temp_r0;
        var_r1 = temp_r0;
        var_r2 -= 1;
    } while (var_r2 >= 0);
    *(void **)var_r1 = 0;
    var_r1 = base;
    {
        s32 v = -1;
        var_r2 = 8;
        do {
            *(s32 *)((s8 *)var_r1 + 4) = v;
            var_r1 = (s8 *)var_r1 + 0x10;
            var_r2 -= 1;
        } while (var_r2 >= 0);
    }
}

void *sub_080928D0(s32 arg0, s32 arg1) {
    struct Node *n = (struct Node *)0x030009F0;
    if (n->unk0 != 0) {
        do {
            if (n->unk4 == -1) {
                n->unk4 = arg0;
                n->unk8 = arg1;
                n->unk12 = 0;
                return n;
            }
            n = (struct Node *)((s8 *)n + 16);
        } while (n->unk0 != 0);
    }
    return (void *)-1;
}
