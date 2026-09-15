#include "m2c_prelude.h"
struct A { s32 unk0; u16 unk4; };
struct B { s32 *unk0; u8 pad[8]; };
extern struct A D_086A46C4[];
extern struct B D_086A4694[];
void func_80EBF24(s32 *);
void func_80EB694(s32 *);

void sub_080EB820(s32 arg0) {
    s32 *temp_r2;
    u16 i = (u16)arg0;
    register struct B *bb asm("r2") = D_086A4694;
    temp_r2 = bb[D_086A46C4[i].unk4].unk0;
    if (*temp_r2 == D_086A46C4[i].unk0) {
        func_80EBF24(temp_r2);
    }
}

void sub_080EB854(s32 arg0) {
    s32 *temp_r2;
    u16 i = (u16)arg0;
    register struct B *bb asm("r2") = D_086A4694;
    temp_r2 = bb[D_086A46C4[i].unk4].unk0;
    if (*temp_r2 == D_086A46C4[i].unk0) {
        func_80EB694(temp_r2);
    }
}
