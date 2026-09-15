#include "m2c_prelude.h"
extern void func_80EB694(void *);
extern void func_80EBE40(void *, s32);

struct Node { s32 f0; s32 f4; };
struct Slot { s32 f0; u16 f4; u16 f6; };
struct Bank { struct Node *ptr; u8 pad[8]; };

extern struct Slot D_086A46C4[];
extern struct Bank D_086A4694[];

void sub_080EB7CC(u16 arg0) {
    register struct Bank *bank asm("r2") = D_086A4694;
    struct Slot *slots = D_086A46C4;
    struct Slot *e = &slots[arg0];
    struct Node *p = bank[e->f4].ptr;
    s32 r3 = p->f0;
    s32 r2 = e->f0;
    if (r3 != r2) {
        func_80EBE40(p, r2);
        return;
    }
    if ((u16)p->f4 == 0) {
        func_80EBE40(p, r3);
        return;
    }
    if (p->f4 < 0) {
        func_80EB694(p);
    }
}
