#include "m2c_prelude.h"
struct P { u8 unk0; u8 unk1; u8 unk2; u8 unk3; u8 unk4; };
extern s8 D_02030664;
extern s32 D_0203174C[];
extern s32 D_03000054[];
extern u8 D_02031754;
extern s8 D_02031749;
extern s16 func_08092A90(int);
extern s16 func_08092ADC(int);
extern void func_08092D8C(int, int);
extern int func_080A016C(int, int, int);

s32 sub_080A1D3C(u8 arg0, struct P **arg1) {
    struct P *p;
    D_02030664 = 1;
    D_0203174C[0] = D_03000054[0] + (func_08092A90((*arg1)->unk1 << 5) * (((p = *arg1)->unk3 << 8) + p->unk2));
    D_0203174C[1] = D_03000054[1] - (func_08092ADC(p->unk1 << 5) * (((p = *arg1)->unk3 << 8) + p->unk2));
    D_02031754 = p->unk4;
    D_02031749 = 1;
    func_08092D8C(4, 0x0809FD61);
    func_080A016C(arg0, -1, 0);
    return 0;
}
