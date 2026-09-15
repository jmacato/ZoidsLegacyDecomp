#include "m2c_prelude.h"
struct Node { s32 flags; };
struct Obj { u8 pad[12]; struct Node *arr[32]; };

extern void func_8095114();

void sub_080C9164(struct Obj *arg0) {
    u8 i;
    struct Node *p;
    for (i = 0; i < 0x20; i++) {
        p = arg0->arr[i];
        if (p != 0 && (p->flags & 1))
            break;
    }
    if (i == 0x20)
        func_8095114(arg0);
}
