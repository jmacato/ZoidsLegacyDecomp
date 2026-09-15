#include "m2c_prelude.h"
struct A { s32 unk0; u16 unk4; };
struct P { s32 unk0; s32 unk4; };
struct B { struct P *p; u8 pad[8]; };
extern struct A D_086A46C4[];
extern struct B D_086A4694[];
void func_80EC6B4(s32, u16, u16);
s32 func_80ECD98(s32, s32);
void func_80EB8EC(s32, u16);
void func_08092E84(u16);
void func_80ED17C(s32);

s32 sub_08092EB0(s32 arg0) {
    u16 i = (u16)arg0;
    if (D_086A4694[D_086A46C4[i].unk4].p->unk4 < 0) {
        return 1;
    }
    return 0;
}

s32 sub_08092EE4(s32 arg0) {
    u16 i = (u16)arg0;
    if (D_086A4694[i].p->unk4 < 0) {
        return 1;
    }
    return 0;
}

void sub_08092F0C(s32 arg0, s32 arg1) {
    u16 i = (u16)arg0;
    u16 a1 = (u16)arg1;
    struct P *p = D_086A4694[D_086A46C4[i].unk4].p;
    func_80EC6B4((s32) p, (u16) p->unk4, a1);
}

void sub_08092F3C(s32 arg0, s32 arg1) {
    u16 i = (u16)arg0;
    u32 t = (u32) (arg1 << 16);
    struct P *p = D_086A4694[D_086A46C4[i].unk4].p;
    u16 r = (u16) func_80ECD98((s32) (t >> 12), 60);
    func_80EB8EC((s32) p, r);
}

void sub_08092F7C(s32 arg0) {
    u16 a = (u16)arg0;
    func_08092E84(a);
    do {
        func_80ED17C(1);
    } while (sub_08092EB0(a) == 0);
}
