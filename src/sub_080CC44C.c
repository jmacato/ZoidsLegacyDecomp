#include "m2c_prelude.h"
extern u8 D_02034B4C[];
extern u8 *D_02033F38;
extern s16 D_087EC38C[];

void func_80CC400(s32, s16, s16);

void sub_080CC44C(void) {
    s16 *a;
    u8 *p;
    u8 *pb;
    u8 A;
    s32 t;
    a = D_087EC38C;
    p = D_02034B4C;
    pb = p + 0xA1B0;
    A = p[0xA1AF];
    t = (pb[A] << 2) + (*D_02033F38 << 5);
    func_80CC400(0, *(s16 *)((s8 *)a + t), *(s16 *)((s8 *)(a += 1) + t));
}
