#include "m2c_prelude.h"

struct T {
    u8 pad0[0x27A8];
    s32 fP;
    u8 pad1[0x7A04];
    u8 fArr[1];
};

extern u8 D_02034B4C[];
extern s32 D_087EE170[];
extern void func_080981F0(s32, s32, u8, s32, s32);
extern void func_08098BB4(s32);

void sub_080CCE24(u8 arg0) {
    u8 temp_r4;
    s32 *tblA;
    struct T *b;
    s32 P;
    u8 idx;
    u16 h;
    s32 val;

    temp_r4 = arg0;
    switch (temp_r4) {
    case 0:
        func_08098BB4(0x08004132);
        break;
    case 1:
        func_08098BB4(0x08004148);
        break;
    case 2:
        func_08098BB4(0x0800415E);
        break;
    }
    tblA = D_087EE170;
    b = (struct T *)D_02034B4C;
    P = b->fP;
    idx = b->fArr[temp_r4];
    h = *(u16 *)(P + (idx << 2) + 0x52);
    val = tblA[h];
    func_080981F0(val, 0, (u8)(temp_r4 + 4), 0, 0);
}
