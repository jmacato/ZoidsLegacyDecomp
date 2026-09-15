#include "m2c_prelude.h"
struct A { s32 unk0; u16 unk4; };
struct P { s32 unk0; s32 unk4; };
struct B { struct P *unk0; u8 pad[8]; };
extern struct A D_086A46C4[];
extern struct B D_086A4694[];
void func_80EBE40(s32, s32);

void sub_080EB754(s32 arg0) {
    u16 i = (u16)arg0;
    register struct B *bb asm("r2") = D_086A4694;
    func_80EBE40((s32) bb[D_086A46C4[i].unk4].unk0, D_086A46C4[i].unk0);
}

void sub_080EB780(s32 arg0) {
    u16 i = (u16)arg0;
    register struct B *bb asm("r2") = D_086A4694;
    struct P *p = bb[D_086A46C4[i].unk4].unk0;
    s32 pv = p->unk0;
    s32 aval = D_086A46C4[i].unk0;
    if (pv != aval) {
        func_80EBE40((s32) p, aval);
    } else {
        s32 pu4s = *(s32 *)((s8 *)p + 4);
        u16 pu4u = *(u16 *)((s8 *)p + 4);
        if (pu4u == 0 || pu4s < 0) {
            func_80EBE40((s32) p, pv);
        }
    }
}
