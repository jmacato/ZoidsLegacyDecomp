#include "m2c_prelude.h"
struct S { u8 unk0; u8 unk1; u8 unk2; };

extern u8 func_080A9EF0(u8);
extern void func_08092D8C(s32, s32);
extern void func_080A016C(u8, s32, s32);

extern s8 D_02030664;
extern s32 D_0203174C[];
extern s32 D_020325A0[][0x12];
extern u16 D_020324A4[];
extern u8 D_02031754;
extern s8 D_02031749;

s32 sub_080A1DE4(u8 arg0, struct S **arg1) {
    s8 one;
    s32 t2;
    s32 t;
    u8 r;

    D_02030664 = one = 1;
    r = func_080A9EF0((*arg1)->unk1);
    if (r != 0xFF) {
        D_0203174C[0] = t2 = D_020325A0[r][2] + 0xFFFF8800;
        D_0203174C[1] = D_020325A0[r][3] + 0xFFFFB000;
        if (t2 < 0) D_0203174C[0] = 0;
        t = (D_020324A4[0] << 11) + 0xFFFF1000;
        if (D_0203174C[0] > t) D_0203174C[0] = t;
        if (D_0203174C[1] < 0) D_0203174C[1] = 0;
        t = (D_020324A4[1] << 11) + 0xFFFF6000;
        if (D_0203174C[1] > t) D_0203174C[1] = t;
        D_02031754 = (*arg1)->unk2;
        D_02031749 = one;
        func_08092D8C(4, 0x0809FD61);
    }
    func_080A016C(arg0, -1, 0);
    return 0;
}
